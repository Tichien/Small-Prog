#ifndef SHELL_H
#define SHELL_H

typedef int bool;
#define true 1
#define false 0

//////////////////////////// LES SIGNAUX /////////////////////////////

void sh_signal_handler(int status);

//////////////////////////// LES COMMANDES /////////////////////////////

/* Une structure representant une commande custom pour le shell */
struct Builtin
{
	const char *name;
	int (*func) (char*);
};

/* Les commandes custom disponible */
int sh_cd(char* line);
int sh_help(char* line);
int sh_exit(char* line);

/* Renvoie le nombre de commande definis dans le tableau builtins */
int sh_builtins_num();

/* Execute la commande bash passé en argument ou bien la commande custom correspondante (défini dans le tableau builtins[]) */
int sh_execute(char* line);

//////////////////////////// LES AFFICHAGES /////////////////////////////

/* Affiche l'etat de connexion dans le descripteur de fichier outputfd. */
void sh_print_state(int canal, int outputfd);

/* Affiche le prompt du terminal dans le descripteur de ficher ouputfd. */
void sh_print_prompt(int outputfd);


//////////////////////////// LES VERIFICATION /////////////////////////////

/* Renvoie vrai si le rang est egal à la longueur de la chaine "reference", ce qui signifie que les caractères successif rentré par "c" forme la chaine "reference". */
bool align(const char* reference, int length, int* rang, char c);

/* Renvoie vrai si un serveur shell est dans chemin passé en paramètre */
bool sh_check_server(const char* serverpath);

//////////////////////////// LES COMMUNICATIONS /////////////////////////////

/* Envoie dans le tuyau de nom "requestpath" le numero de canal dans lequel on veut creer un shell. */
int sh_send_request(const char* requestpath, int canal);

/* Lit dans le tuyau de nom "requestpath" le canal dans lequel on veut creer un shell. Le resultat est stocker dans la variable "canal". */
int sh_read_request(const char* requestpath, int* canal);

/* Transfer les données de inputfd vers ouputfd et se termine quand il reçoit d'affiler les caractères 'e' 'x' 'i' 't' '\n' */
int sh_transfer(int inputfd, int ouputfd);

//////////////////////////// LE SHELL /////////////////////////////

/* Simule un shell qui va lire ses commande via le descripteur de fichier "inputfd", et afficher le resultat de leurs executions dans le descripteur de fichier "ouputfd". */
int sh_loop(int inputfd, int outputfd);

/* Creer un shell qui pourra communiquer avec un autre programme, en creant un tube nommé "inputname" pour recevoir des données en entrée et un tube nommé "outputname" pour envoyer les données traitées à ce programme. */
int sh_create(int canal);

/* Efface les fichiers crées lors des precedentes execution du server shell. */
int sh_clean_up();

//////////////////////////// AUTRE /////////////////////////////

/* Renvoie le chemin du dossier d'installation du programme */
int sh_install_path(char* path, size_t size);

/* Rajoute dans le fichier "workingpath" le canal utilisé "canal". */
int sh_add_entry(const char* workingpath, int canal);

/* Enlève du fichier "workingpath" le canal utilisé "canal". */
int sh_remove_entry(const char* workingpath, int canal);

#endif
