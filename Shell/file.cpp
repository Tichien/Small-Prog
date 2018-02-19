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


/* Enleve la ligne ou se trouve le motif dans le fichier n fois
 * renvoie vrai si la ligne a été trouvé faux sinon
 */
bool removeFromFile(std::string filepath, std::string toremove, size_t ntime){

	std::ifstream file(filepath.c_str());
	
	size_t n = 0;
	bool found = false;
	std::string line;

	if(!file.is_open()){
		//CHECK_FILE(file, filepath);
		return false;
	}

	std::ofstream temp((filepath + ".temp").c_str());

	if(!temp.is_open()){
		//CHECK_FILE(file, filepath + ".temp");
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
		//CHECK_FILE(file, filepath);
		return;
	}

	for(int i = 0 ; i < (int)ntime ; i++){
		file << toadd << std::endl;
	}

	file.close();
}

