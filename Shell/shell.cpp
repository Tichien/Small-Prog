#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "file.h"

using namespace std;

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