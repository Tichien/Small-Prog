#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "file.h"

using namespace std;

void signal_handler(int sig){

	//exit(EXIT_SUCCESS);
}

int ssh_cd(char *line){
	char path[1024] = "";

	sscanf(line, "%s", path);
	sscanf(line, "%s", path);

	chdir(path);
	return 0;
}

int ssh_help(char *line){
	return 0;
}

int ssh_exit(char *line){
	return 0;
}

struct Builtin
{
	const char *name;
	int (*func) (char*);
};

struct Builtin builtins[] =
{
	{ "cd", &ssh_cd },
    { "help", &ssh_help },
    { "exit", &ssh_exit }
};

int ssh_builtins_num(){
	return sizeof(builtins) / sizeof(struct Builtin);
}

/* Affiche le repertoire courant, ainsi que des informations sur l'utilisateur dans le descripteur de fichier "outputfd". */
int ssh_print_dir(int outputfd){
	
	char *path = NULL;
	char *username = NULL;
	char cwd[1024] = ""; 
	char userline[1024] = "";

	username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	
	strcat(userline, username);
	strcat(userline, "@");
	strcat(userline, username);
	strcat(userline, ":");

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
	return 0;
}

/* Execute la commande bash passé en argument ou bien une des commandes custom défini dans le tableau builtins[] */
int ssh_execute(char* line){

	for(int i = 0 ; i < ssh_builtins_num() ; i++){
		if(strstr(line, builtins[i].name)){
			return builtins[i].func(line);
		}
	}

	system(line);
	return 0;
}

/* Simule un shell qui va lire ses commande via le descripteur de fichier "inputfd", et afficher le resultat de leurs executions dans le descripteur de fichier "ouputfd". */
int ssh_shell_loop(int inputfd, int outputfd){

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
		
		ssh_execute(line);

		ssh_print_dir(outputfd);
	}
}
/* Creer un shell qui pourra communiquer avec un autre programme, en creant un tube nommé "inputname" pour recevoir des données en entrée et un tube nommé "outputname" pour envoyer les données traitées à ce programme. */
int ssh_create_shell(const char* inputname, const char* outputname){
	
	pid_t pid;
	int error;
	int inputfd;
	int outputfd;
	int pipefd[2];
	char command[1024] = "";

	/* Supprime les pipes si déja existante */
	unlink(inputname);
	unlink(outputname);

	/* Creation des pipes input et output (impossible de mettre les permission au dessus de 666 à cause du umask) */
	mkfifo(inputname, 0666);
	mkfifo(outputname, 0666);

	/* Changement des permissions des pipes input output à 777 */
	strcat(command, "chmod 777 ");
	strcat(command, inputname);

	system(command);

	strcpy(command, "");

	strcat(command, "chmod 777 ");
	strcat(command, outputname);

	system(command);

	printf("En attente de connexion...\n");

	/* Ouverture du pipe input en lecture */
	inputfd = open(inputname, O_RDONLY);
	CHECK_FD(inputfd, inputname)

	/* Ouverture du pipe ouput en ecriture */
	outputfd = open(outputname, O_WRONLY);
	CHECK_FD(outputfd, outputname)

	printf("Connexion reussi !\n");	

	ssh_print_dir(outputfd);

	error = pipe(pipefd);
	CHECK_ERROR(error)

	pid = fork();
	CHECK_ERROR(pid)

	if(pid == 0){
		close(pipefd[0]);
		ssh_shell_loop(inputfd, pipefd[1]);
	}
	else{
		close(pipefd[1]);
		writer(pipefd[0], outputfd);
	}

	printf("Deconnexion reussi !\n");	

	close(inputfd);
	close(outputfd);

	unlink(inputname);
	unlink(outputname);
	return 0;
}


int ssh_controler_loop(const char* pipename){
	
	pid_t pid;
	FILE* pipe;
	char command[1024] = "";
	char inputname[1024] = "";
	char outputname[1024] = "";

	unlink(pipename);

	mkfifo(pipename, 0666);

	strcat(command, "chmod 777 ");

	system(strcat(command, pipename));

	while(true){
		pipe = fopen(pipename, "r");
		CHECK_FILE(pipe, pipename)

		fscanf(pipe, "%s", inputname);
		fscanf(pipe, "%s", outputname);

		if(!strcmp(inputname, "") || !strcmp(outputname, "")){
			printf("Erreur : Au moins un nom de pipe n'est pas valide\n");
		}
		else{
			pid = fork();

			if(pid == 0){
				ssh_create_shell(inputname, outputname);
			}
		}
	
		fclose(pipe); 
	}

	return 1;
}

/* Cette fonction va creer un shell de communication à distance qui s'execute en parallèle, à chaque fois qu'elle lis une entrée dans le tube nommé "pipename". 
 * Pour cela, chaque entrée dans le pipe "pipename" doit être composée de 2 noms separé par un blanc.
 * Ces noms sont necessaires pour la fonction de creation de shell. */
int main(int argc , char const *argv[]) {

	const char* pipename = "names";
	ssh_create_shell("input", "output");

	return 0;
}
