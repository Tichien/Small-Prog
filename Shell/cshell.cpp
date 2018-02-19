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
    exit(EXIT_SUCCESS);
}

int main(int argc , char const *argv[]) {

    int inputfd;
    int outputfd;
    const char *shellpath = "";
    const char *inputpipe = "input";
    const char *outputpipe = "output";

    inputfd = open(inputpipe, O_WRONLY);
    CHECK_FD(inputfd, inputpipe)

    outputfd = open(outputpipe, O_RDONLY);
    CHECK_FD(outputfd, outputpipe)

    pid_t pid = fork();
    CHECK_ERROR(pid)

    if(pid == 0){
        writer(STDIN_FILENO, inputfd);
    }
    else{
        writer(outputfd, STDOUT_FILENO);
    }

    close(inputfd);
    close(outputfd);

    return 0;
}
