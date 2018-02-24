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

/*  problème a régler : mettre un timeout lors de la creation des shell 
    pour eviter qu'ils restent actif dans le vide lorsque le client se
    termine anormalement */

/* Ce programme va creer un shell de communication à distance qui s'execute en parallèle, à chaque fois qu'elle lis une entrée dans le tube nommé "pipename". 
 * Pour cela, chaque entrée dans le pipe "pipename" doit être composée de 2 noms separé par un blanc.
 * Ces noms sont necessaires pour la fonction de creation de shell. */
int main(/*int argc , char const *argv[]*/) {

    char path[1024] = "";
    char permission[1024] = "chmod 777 ";
    char requestpath[1024] = "";
    //char workingpath[1024] = "working";

    sh_install_path(path, sizeof(path));

    sprintf(requestpath, "%s/request", path);

    //sh_clean_up();

    mkfifo(requestpath, 0666);

    system(strcat(permission, requestpath));

    while(1){
        int canal = -1;

        printf("En attente de requetes...\n");

        /* Le programme ce met en pause jusqu'à ce que une requete arrive */
        sh_read_request(requestpath, &canal);
                
        if(canal >= 0){

            pid_t pid = fork();
            CHECK_ERROR(pid);

            if(pid == 0){
                printf("Creation d'un shell sur le canal N°%d\n", canal);
                
                //sh_add_entry("working", canal);

                sh_create(canal);
                
                //sh_remove_entry("working", canal);

                printf("Fermeture d'un shell sur le canal N°%d\n", canal);   
                                
                exit(EXIT_SUCCESS);
            }
        }
        else{
            printf("Erreur : creation du shell sur le canal N°%d impossible\n", canal);
        }
    }

	return EXIT_SUCCESS;
}
