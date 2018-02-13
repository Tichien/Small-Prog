#include <iostream>
#include <fstream>
#include <string>

void removeFromFile(std::string filepath, std::string toremove){

	std::ifstream file(filepath.c_str());
	std::ofstream temp((filepath + ".temp").c_str());
	
	std::string line;

	if(!file.is_open()){
		std::cerr << "Erreur : Ouverture du fichier impossible" << std::endl;
		return;
	}

	if(!temp.is_open()){
		std::cerr << "Erreur : Ouverture du fichier impossible" << std::endl;
		return;
	}

	while(getline(file, line)){

		if(line.find(toremove, 0)){
			temp << line << std::endl;
		}
	}

	file.close();
	temp.close();

	std::remove(filepath.c_str());
	std::rename((filepath + ".temp").c_str(), filepath.c_str());
}

void injectOnFile(std::string filepath, std::string toadd){

	std::ofstream file(filepath.c_str(), std::ios::app);
	
	std::string line;

	if(!file.is_open()){
		std::cerr << "Erreur : Ouverture du fichier impossible" << std::endl;
		return;
	}

	file << toadd << std::endl;

	file.close();
}