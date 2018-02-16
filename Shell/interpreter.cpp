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
/* Chemin absolue */
static string execpath(getenv("PWD"));
static string commandpath(execpath + "/command");
static string readpath(execpath + "/read");
static string printpath(execpath + "/print");
static string historypath(commandpath + ".history");
static string outputpath(execpath + "/output");

void signal_handler(int sig){
	remove("input");
	remove("output");
	exit(EXIT_SUCCESS);
}



int main(int argc , char const *argv[]) {

	char c;
	int inputfd;
	int outputfd;
	char line[1024];
	const char *inputname = "input";
	const char *outputname = "output";

	signal(SIGINT, signal_handler);

    /* Creation des pipes input output (impossible de mettre les permission au dessus de 666 à cause du umask) */
	mkfifo(inputname, 0666);
	mkfifo(outputname, 0666);
    /* Changement des droit des pipes input output à 777 */
	system(("chmod 777 " + string(inputname)).c_str());
	system(("chmod 777 " + string(outputname)).c_str());

	cout << "Connexion en cours..." << endl;

	inputfd = open(inputname, O_RDONLY);
	CHECK_FD(inputfd, inputname)

	outputfd = open(outputname, O_WRONLY);
	CHECK_FD(outputfd, outputname)

	cout << "Connexion reussi" << endl;

	int fd[2];
	int errorp = pipe(fd);
	CHECK_ERROR(errorp)

	pid_t pid = fork();
	CHECK_ERROR(pid)

	if(pid == 0){
		close(fd[0]);
		interpreter(inputfd, fd[1]);
	}
	else{
		close(fd[1]);
		writer(fd[0], outputfd);
	}

	close(inputfd);
	close(outputfd);

	remove("input");
	remove("output");
	return 0;
}

/*
int main(int argc , char const *argv[]) {

	while(true){

		if(fileExist(readpath)){
			string commandfile(commandpath);
			ifstream file(commandfile.c_str());
			ofstream history((commandfile + ".history").c_str(), ios::app);
			//ofstream output(outputpath.c_str());

			if(!file.is_open()){
				ERREUR_OUVERTURE(commandfile);
				return EXIT_FAILURE;
			}

			if(!history.is_open()){
				ERREUR_OUVERTURE(commandfile + ".history");
				return EXIT_FAILURE;
			}

			string line;

			while(getline(file, line)){

				size_t found = line.find("cd");
				
				if(found != string::npos){
					stringstream ss(line); string path; 
		    		ss >> path >> path;
					chdir(path.c_str());
					//output << "cd" << endl;
					system(("cd > " + outputpath + " 2>&1").c_str());
				}
				else{
					system((line + " > " + outputpath + " 2>&1").c_str());	
				}
				//removeFromFile(commandfile, line);
				//history << line << endl;
			}

			file.close();
			history.close();
			remove(readpath.c_str());
			fileCreate(printpath);
			cout << "En attente de commande..." << endl;
			cout << get_current_dir_name() << endl;
			//cout << parampath << endl;

		}
		else{
			usleep(250000);
			//cout << "fin" << endl;
		}	
	}


	return 0;
}
*/