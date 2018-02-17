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

char* username = getenv("USER");

void signal_handler(int sig){

	//exit(EXIT_SUCCESS);
}

int shs_print_dir(int outputfd){
	
	char cwd[1024]; 
	getcwd(cwd, sizeof(cwd));

	char userline[1024] = "";
	
	string scwd(cwd);
	string suser(user);
	string path;

	size_t found = scwd.find(suser);

	if(found != string::npos){
		path = scwd.substr(found + suser.length(), scwd.length());
	}
	else{
		path = scwd;
	}

	strcpy(userline, (suser + "@:~" + path + "$ ").c_str());
	write(outputfd, userline, sizeof(userline));
}

int main(int argc , char const *argv[]) {

	char c;
	int inputfd;
	int outputfd;
	char line[1024];
	const char *inputname = "input";
	const char *outputname = "output";

	unlink(inputname);
	unlink(outputname);

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

	return 0;
}
