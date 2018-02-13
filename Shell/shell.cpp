#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc , char const *argv[]) {

    while(true){
    	string prompt  = "$ ", commandline;

    	cout << prompt;
    	getline(cin, commandline);

    	if(commandline == "exit")
    		return EXIT_SUCCESS;

    	system(commandline.c_str());
    }
    return 0;
}