#include <iostream>
#include <fstream>
#include <string>


#define CHEK_FD(FD, FDNAME) 		\
if((FD) < 0){						\
	cerr << "Erreur : Problème à l'ouverture du fichier " << (FDNAME) << endl; \
	cerr << strerror(FD) << endl;	\
	return EXIT_FAILURE; 			\
}									\

#define ERREUR_OUVERTURE(F) \
std::cout << "Erreur: ouverture du fichier " << (F) << " impossible" << std::endl;

/* Enleve la ligne ou se trouve le motif dans le fichier n fois
 * renvoie vrai si la ligne a été trouvé faux sinon
 */
bool removeFromFile(std::string filepath, std::string toremove, size_t ntime = 1){

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

void injectOnFile(std::string filepath, std::string toadd, bool overwrite = false, size_t ntime = 1){

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

	for(int i = 0 ; i < ntime ; i++){
		file << toadd << std::endl;
	}

	file.close();
}

bool fileExist(std::string filepath)
{
	std::ifstream file(filepath.c_str());
	return file.good();
}

void fileCreate(std::string filepath, bool overwrite = false){
	std::ofstream file(filepath.c_str());
	return;
}

bool fileEmpty(std::string filepath){
	std::ifstream file(filepath.c_str());
	return file.peek() == std::ifstream::traits_type::eof();
}