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

void signal_handler(int sig){
    exit(EXIT_SUCCESS);
}

int main(int argc , char const *argv[]) {

    int c;
	int inputfd;
	int outputfd;
    char line[1024];
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
        inputfd = open(inputname, O_WRONLY);
        cout << "open inputfd done" << endl;

        CHEK_FD(inputfd, inputname)

        fgets(line, sizeof(line), stdin);      
        
        write(inputfd, line, sizeof(line));
        
        close(inputfd);

        outputfd = open(outputname, O_RDONLY);
        cout << "open outputfd done" << endl;

        while(read(outputfd, &c, sizeof(c))){
            putc(c, stdout);
        }
        close(outputfd);
  }
  return 0;
}

/*

int main(int argc , char const *argv[]) {

    while(true){
    	string prompt  = "> ", commandline;

    	cout << prompt;
    	getline(cin, commandline);

    	if(commandline == "exit"){
    		remove("print");
    		remove("output");
    		return EXIT_SUCCESS;
    	}

    	injectOnFile("command", commandline, true);
    	fileCreate("read");

    	bool exist = false;

    	while(!fileExist("print")){
			usleep(250000);
  		}
    	
    	system("cat output");
    	remove("print");
    }
    return 0;
}
 */