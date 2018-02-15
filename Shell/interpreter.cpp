#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <csignal>
#include "file.h"

using namespace std;
/* Chemin absolue */
static string execpath(getenv("PWD"));
static string commandpath(execpath + "/command");
static string readpath(execpath + "/read");
static string printpath(execpath + "/print");
static string historypath(commandpath + ".history");
static string outputpath(execpath + "/output");

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
					system()
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