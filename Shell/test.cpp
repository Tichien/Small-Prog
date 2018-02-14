#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(int argc , char const *argv[]) {

    while(true){
    	string prompt  = "> ", commandline;

    	cout << prompt;
    	getline(cin, commandline);

    	if(commandline == "exit")
    		return EXIT_SUCCESS;

        size_t found = commandline.find("cd");
        stringstream ss(commandline); string path;
        ss >> path >> path;
        
        if(found != string::npos){
            chdir((path).c_str());
        }
        else{
            system(commandline.c_str());    
        }
    }
    return 0;
}