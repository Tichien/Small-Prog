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

	int inputfd;
	int outputfd;
	char line[1024];
	char msg[1024] = "Test";
	const char *inputname = "input";
	const char *outputname = "output";

	signal(SIGINT, signal_handler);

    /* Creation des pipes input output (impossible de mettre les permission au dessus de 666 à cause du umask) */
	mkfifo(inputname, 0666);
	mkfifo(outputname, 0666);
    /* Changement des droit pipes input output à 777 */
	system(("chmod 777 " + string(inputname)).c_str());
	system(("chmod 777 " + string(outputname)).c_str());

	cout << "mkfifo done" << endl;

	while(true){
		inputfd = open(inputname, O_RDONLY);
		cout << "open inputfd done" << endl;

		CHEK_FD(inputfd, inputname)

		read(inputfd, line, sizeof(line));
		close(inputfd);

		outputfd = open(outputname, O_WRONLY);
		cout << "open outputfd done" << endl;

		CHEK_FD(outputfd, outputname)
		cout << "check outputfd done" << endl;

		//dup2(outputfd, 0); 
		dup2(outputfd, 1);
		CHEK_FD(outputfd, "output");
		cout << "check dup done" << endl;

		//dup2(outputfd, 2);
		cout << "dup2 outputfd done" << endl;

		dprintf(outputfd, "%s\n", line);
		dprintf(1, "%s\n", line);
		fflush(stdout);
		//printf("%s\n", line);
		//cout << line << endl;
		close(outputfd);

		//system(line);
		//write(outputfd, msg, sizeof(msg));
		cout << "fin de boucle" << endl;

	}

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