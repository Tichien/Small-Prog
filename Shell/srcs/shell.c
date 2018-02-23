#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "check.h"
#include "shell.h"

//////////////////////////// LES SIGNAUX /////////////////////////////

void sh_signal_handler(int status){
	printf("Signal %d reçu\n", status);
	exit(status);	
}

//////////////////////////// LES COMMANDES /////////////////////////////

struct Builtin builtins[] =
{
	{ "cd", &sh_cd },
    { "help", &sh_help },
    { "exit", &sh_exit }
};

int sh_cd(char *line){

	char* home = getenv("HOME"); 
	char command[1024] = "";
	char path[1024] = "";
	char newpath[1024] = "";
	char *found = NULL;

	sscanf(line, "%s%s", command, path);

	/* si on trouve le symbole "~" on le remplace par "home" */
	if((found = strstr(path, "~"))){
		strcat(newpath, home);
		strcat(newpath, found + 1);

		chdir(newpath);
	}
	else{
		chdir(path);
	}

	return EXIT_SUCCESS;
}

int sh_help(char *line){
	printf("%s\n", line);
	return EXIT_SUCCESS;
}

int sh_exit(char *line){
	printf("exit\n%s\n", line);
	return -1;
}

int sh_builtins_num(){
	return sizeof(builtins) / sizeof(struct Builtin);
}

int sh_execute(char* line){

	for(int i = 0 ; i < sh_builtins_num() ; i++){
		if(strstr(line, builtins[i].name)){
			return builtins[i].func(line);
		}
	}

	system(line);
	return EXIT_SUCCESS;
}

//////////////////////////// LES AFFICHAGES /////////////////////////////

void sh_print_state(int canal, int outputfd){
	char *username = NULL;
	char state[1024] = "";

	username = getenv("USER");
	
	sprintf(state, "Vous etes connecté sur le terminal de %s via le canal N°%d\n", username, canal);

	write(outputfd, state, sizeof(state));
}

void sh_print_prompt(int outputfd){
	
	char *path = NULL;
	char *username = NULL;
	char cwd[1024] = ""; 
	char userline[1024] = "";

	username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	
	sprintf(userline, "%s@%s:", username, username);

	path = strstr(cwd, username);

	if(path){
		strcat(userline, "~");
		strcat(userline, path + strlen(username));
	}
	else{
		strcat(userline, cwd);
	}

	strcat(userline, "> ");

	write(outputfd, userline, sizeof(userline));
}

//////////////////////////// LES VERIFICATION /////////////////////////////

bool align(const char* reference, int length, int* rang, char c){

	if(reference[*rang] == c)
		(*rang)++;
	else if(reference[0] == c)
		*rang = 1;
	else
		*rang = 0;

	return length == *rang;
}

bool sh_check_server(const char* serverpath){
	char requestpath[1024] = "";

	sprintf(requestpath, "%s/request", serverpath);

	/* si le fichier "requestpath" exist */
	if(access(requestpath, F_OK) != -1){
		return true;
	}

	return false;
}


//////////////////////////// LES COMMUNICATIONS /////////////////////////////


int sh_send_request(const char* requestpath, int canal){
    int requestfd = open(requestpath, O_WRONLY);
    CHECK_FD(requestfd, requestpath)

    write(requestfd, &canal, sizeof(canal));
    
    close(requestfd);
    return EXIT_SUCCESS;
}

int sh_read_request(const char* requestpath, int* canal){
    int requestfd = open(requestpath, O_RDONLY);
    CHECK_FD(requestfd, requestpath)

    read(requestfd, canal, sizeof(canal));
    
    close(requestfd);
    return EXIT_SUCCESS;
}

int sh_transfer(int inputfd, int outputfd){

	char c;
	int error;
	int rang = 0;
	char exit[] = "exit\n";
	int length = strlen(exit);

	while(1){
		error = read(inputfd, &c, sizeof(c));
		CHECK_ERROR(error)

		write(outputfd, &c, sizeof(c));

		if(align(exit, length, &rang, c)){
			return EXIT_SUCCESS;
		}
	}
}

//////////////////////////// LE SHELL /////////////////////////////

int sh_loop(int inputfd, int outputfd){

	char line[1024] = "";

	FILE* input = fdopen(inputfd, "r");
	
	/* redirection de stdin vers inputfd */
	close(0); dup(inputfd);

	/* redirection de stdout vers ouputfd */
	close(1); dup(outputfd);

	/* redirection de stderr vers outputfd */
	close(2); dup(outputfd);

	while(1){
		fgets(line, sizeof(line), input);
		
		if(sh_execute(line) < 0){
			break;
		}
		sh_print_prompt(outputfd);
	}

	fclose(input);

	//implementer la restoration des sortie stdin stdout stderr 

	return EXIT_SUCCESS;
}

int sh_create(int canal){
	
	pid_t pid;
	int error;
	int inputfd;
	int outputfd;
	int pipefd[2];
	
	char permission[1024] = "";
	char canalpath[1024] = "";
	char inputpath[1024] = "";
	char outputpath[1024] = "";

	sprintf(canalpath, "canals/%d", canal);
	sprintf(inputpath, "%s/input", canalpath);
	sprintf(outputpath, "%s/output", canalpath);

	/* Supprime les tuyaux si deja existant */
	unlink(inputpath);
	unlink(outputpath);

    mkdir("canals", 0777);
	mkdir(canalpath, 0777);

	/* Creation des tuyaux input et output (impossible de mettre les permission au dessus de 666 de base à cause du umask) */
	mkfifo(inputpath, 0777);
	mkfifo(outputpath, 0777);

	/* Changement des permissions des tuyaux input output à 777 */
	sprintf(permission, "chmod 777 %s", inputpath);
	system(permission);

	strcpy(permission, "");

	sprintf(permission, "chmod 777 %s", outputpath);
	system(permission);

	printf("Connexion sur le canal N°%d en cours...\n", canal);

	/* Ouverture du tuyau inputfd en lecture */
	inputfd = open(inputpath, O_RDONLY);
	CHECK_FD(inputfd, inputpath)

	/* Ouverture du tuyau outputfd en ecriture */
	outputfd = open(outputpath, O_WRONLY);
	CHECK_FD(outputfd, outputpath)

	printf("Connexion reussi\n");	
	
	sh_print_state(canal, outputfd);
	sh_print_prompt(outputfd);

	error = pipe(pipefd);
	CHECK_ERROR(error)

	pid = fork();
	CHECK_ERROR(pid)

	/* Le processus fils traite les commandes arrivant sur inputfd et renvoi le resultat au père via un tuyau. */
	if(pid == 0){

		close(outputfd);
		close(pipefd[0]);

		sh_loop(inputfd, pipefd[1]);

		close(inputfd);
		close(pipefd[1]);

		exit(EXIT_SUCCESS);
	}
	/* Le processus père transfer les données arrivant du tuyau vers outputfd. */
	else{
		close(inputfd); 
		close(pipefd[1]);

		sh_transfer(pipefd[0], outputfd);

		close(outputfd);
		close(pipefd[0]);

		/* Le père attend que le fils se termine */
		wait(NULL);
	}

	return EXIT_SUCCESS;
}

int sh_clean_up(){
	system("rm -r canals > /dev/null 2>&1");
	system("rm working > /dev/null 2>&1");
	system("rm request > /dev/null 2>&1");
	return EXIT_SUCCESS;
}

//////////////////////////// AUTRE /////////////////////////////

int sh_add_entry(const char* workingpath, int canal){
	
	int current = 0;
	bool writen = false;
	char temppath[1024] = "";
	sprintf(temppath, "%s.temp", workingpath);

	FILE* workingfile = fopen(workingpath, "r");

	if(!workingfile){
		workingfile = fopen(workingpath, "w");
		CHECK_FILE(workingfile, workingpath)

		fputc(canal, workingfile);

		fclose(workingfile);
		return EXIT_SUCCESS;
	}
	
    FILE* temp = fopen(temppath, "w");
    CHECK_FILE(temp, temppath);

    while((current = fgetc(workingfile)) != EOF){
    	if(current > canal){
    		printf("Ecriture canal %d dans temp\n", canal);
    		writen = true;
    		fputc(canal, temp);
    	}
    	printf("Ecriture current %d dans temp\n", current);
    	fputc(current, temp);
    }

    if(!writen){
    	printf("Ecriture canal %d dans temp\n", canal);
    	fputc(canal, temp);
    }

    fclose(workingfile);
    fclose(temp);

    remove(workingpath);
    rename(temppath, workingpath);
	
    return EXIT_SUCCESS;
}

int sh_remove_entry(const char* workingpath, int canal){
	int current = 0;
	char temppath[1024] = "";
	sprintf(temppath, "%s.temp", workingpath);

	FILE* workingfile = fopen(workingpath, "r");
    CHECK_FILE(workingfile, workingpath);

    FILE* temp = fopen(temppath, "w");
    CHECK_FILE(temp, temppath);

    while((current = fgetc(workingfile)) != EOF){
    	if(current == canal)
    		continue;
    	fputc(current, temp);
    }

    fclose(workingfile);
    fclose(temp);

    remove(workingpath);
    rename(temppath, workingpath);

    return EXIT_SUCCESS;
}

