#include "patch.h"
#include <cstdlib>

using namespace std;

void depatch(const string filepath){
		//changement des droits du fichier
		string command("chmod 755 " + filepath);
		system(command.c_str());
		
		//Suppression du code NewXhost dans le fichier
		removeNewXhost(filepath);
}

int main(int argc, char const *argv[])
{
	string home(getenv("HOME"));

	if(argc > 1){
		
		system("command xhost -");

		for(int i = 1 ; i < argc ; i++){
			string filepath(argv[i]);
			depatch(filepath);
		}
	}
	else{
		cout << "Usage: " << argv[0] << " fichier1 fichier2..." << endl;
	}

	return 0;
}