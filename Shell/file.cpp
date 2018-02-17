#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "file.h"

using namespace std;

/* read from inputfd and write to ouputfd */
int writer(int inputfd, int outputfd){

	char c;
	int error;

	while(1){
		error = read(inputfd, &c, sizeof(c));
		CHECK_ERROR(error)
		write(outputfd, &c, sizeof(c));
	}
}

int parseline(char* line){

	/* découpe la ligne jusqu'au delimiteur ";" */
	char *token = strtok(line, ";");

	/* tant que la chaine peu encore etre découpé */
	while(token != NULL){

		string strline(token);
		size_t found = strline.find("cd");

		if(strline.find("exit") != string::npos){
			//kill(getppid(), SIGINT);
			//exit(EXIT_SUCCESS);
			cout << "exit" << endl;
		}
		else if(found != string::npos){
			stringstream ss(token); string path; 
			ss >> path >> path;
			chdir(path.c_str());
			system("pwd");
		}
		else{
			/* le resultat de la commande est envoyé dans outputfd grace a la redirection */
			system("pwd");
			system(token);
		}
		/* decoupe la chaine jusqu'au prochain delimiteur */
		token = strtok(NULL, ";");
	}

}

/* interprete une commande venant de inputfd et affiche le resultat sur ouputfd */
int interpreter(int inputfd, int outputfd){
	char c;
	int error;
	char line[1024] = "";
	char cwd[1024] = "";
	
	FILE* input = fdopen(inputfd, "r");
	
	/* redirection de stdin vers inputfd */
	close(0); dup(inputfd);

	/* redirection de stdout vers ouputfd */
	close(1); dup(outputfd);

	/* redirection de stderr vers outputfd */
	close(2); dup(outputfd);

	while(1){
		fgets(line, sizeof(line), input);
		//getcwd(cwd, sizeof(cwd));
		//cout << cwd << " ";
		parseline(line);
	}
}

/* interprete une commande venant de inputfd et affiche le resultat sur ouputfd */
int shellinterpreter(int inputfd, int outputfd){
	char c;
	int error;
	char line[1024];
	
	FILE* input = fdopen(inputfd, "r");
	FILE* output = fdopen(outputfd, "w");

	while(1){
		fgets(line, sizeof(line), input);

		string strline(line);
		size_t found = strline.find("cd");

		if(strline.find("exit") != string::npos){
			fputs(line, output);
			kill(getppid(), SIGINT);
			exit(EXIT_SUCCESS);
		}
		else{
			fputs(line, output);
		}
	}
}


/* Enleve la ligne ou se trouve le motif dans le fichier n fois
 * renvoie vrai si la ligne a été trouvé faux sinon
 */
bool removeFromFile(std::string filepath, std::string toremove, size_t ntime){

	std::ifstream file(filepath.c_str());
	
	size_t n = 0;
	bool found = false;
	std::string line;

	if(!file.is_open()){
		ERREUR_OUVERTURE(filepath);
		return false;
	}

	std::ofstream temp((filepath + ".temp").c_str());

	if(!temp.is_open()){
		ERREUR_OUVERTURE(filepath + ".temp");
		return false;
	}

	while(getline(file, line)){

		found = line.find(toremove) != std::string::npos;

		if(found && n < ntime){
			n++;
		}
		else{
			temp << line << std::endl;
		}
	}

	file.close();
	temp.close();

	if(found){
		std::remove(filepath.c_str());
		std::rename((filepath + ".temp").c_str(), filepath.c_str());
	}
	else{
		std::remove((filepath + ".temp").c_str());
	}

	return found;
}

void injectOnFile(std::string filepath, std::string toadd, bool overwrite, size_t ntime){

	std::ofstream file;

	if(overwrite)
		file.open(filepath.c_str());
	else
		file.open(filepath.c_str(), std::ios::app);
	
	std::string line;

	if(!file.is_open()){
		ERREUR_OUVERTURE(filepath);
		return;
	}

	for(int i = 0 ; i < (int)ntime ; i++){
		file << toadd << std::endl;
	}

	file.close();
}

