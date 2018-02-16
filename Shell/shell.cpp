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

    char c;
    int inputfd;
    int outputfd;
    char line[1024];
    const char *inputname = "input";
    const char *outputname = "output";

    inputfd = open(inputname, O_WRONLY);
    CHECK_FD(inputfd, inputname)

    outputfd = open(outputname, O_RDONLY);
    CHECK_FD(outputfd, outputname)

    int fd[2];
    int errorp = pipe(fd);
    CHECK_ERROR(errorp)

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