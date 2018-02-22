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

int inputfd;
int outputfd;

void signal_handler(int status);

int main(int argc , char const *argv[]) {

    if(argc < 2){
        printf("Usage : %s [SERVER_DIR] ([CANAL])\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int canal; 

    if(argc == 2)
        canal = 0;
    else
        canal = atoi(argv[2]);

    signal(SIGINT, signal_handler);

    char serverpath[1024] = "";
    char canalpath[1024] = "";
    char requestpath[1024] = "";

    char inputpath[1024] = "";
    char outputpath[1024] = "";

    sprintf(serverpath, "%s", argv[1]);
    sprintf(canalpath, "%s/canals/%d", serverpath, canal);
    sprintf(requestpath, "%s/request", serverpath);

    sprintf(inputpath, "%s/input", canalpath);
    sprintf(outputpath, "%s/output", canalpath);

    if(!sh_check_server(serverpath)){
        printf("Erreur : le serveur shell n'est pas dans ce dossier ou alors il n'est pas actif.\n");
        return EXIT_FAILURE;
    }

    printf("Demande de shell en cours...\n");

    /* Envoie une demande de shell sur le canal "canal" au server */
    sh_send_request(requestpath, canal);

    printf("Connexion au shell en cours...\n");

    /* Attend une seconde, ce qui laisse le temps au serveur de creer le canal et le shell demandé */
    sleep(1);

    inputfd = open(inputpath, O_WRONLY);
    CHECK_FD(inputfd, inputpath)

    outputfd = open(outputpath, O_RDONLY);
    CHECK_FD(outputfd, outputpath)

    pid_t pid = fork();
    CHECK_ERROR(pid)

    if(pid == 0){

        close(outputfd);
        
        sh_transfer(STDIN_FILENO, inputfd);
        
        close(inputfd);

        exit(EXIT_SUCCESS);
    }
    else{
        close(inputfd);
        
        sh_transfer(outputfd, STDOUT_FILENO);
       
        close(outputfd);

        wait(NULL);
    }

    printf("Fin de la connexion au canal N°%d\n", canal);

    return 0;
}

void signal_handler(int status){
    printf("%d\n", status);
    char exitcommand[] = "exit\n";

    write(inputfd, exitcommand, sizeof(exitcommand));

    exit(EXIT_SUCCESS);
}