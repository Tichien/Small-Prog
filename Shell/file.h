#define CHECK_FD(FD, FDNAME) 																\
if((FD) < 0){																				\
	std::cerr << "Erreur : Problème à l'ouverture du fichier " << (FDNAME) << std::endl; 	\
	std::cerr << strerror(FD) << std::endl;													\
	return EXIT_FAILURE; 																	\
}																							\

#define CHECK_FILE(F, FNAME) 												\
if((F == NULL)){															\
	std::cerr << "Erreur : Ouverture du fichier impossible" << std::endl;	\
	return EXIT_FAILURE; 													\
}																			\

#define CHECK_ERROR(ERRNO) 						\
if((ERRNO) < 0){								\
	std::cerr << strerror(ERRNO) << std::endl;	\
	return EXIT_FAILURE; 						\
}												\


#define ERREUR_OUVERTURE(F) \
std::cout << "Erreur: ouverture du fichier " << (F) << " impossible" << std::endl;	

int writer(int inputfd, int outputfd);

int interpreter(int inputfd, int outputfd);

int shellinterpreter(int inputfd, int outputfd);

bool removeFromFile(std::string filepath, std::string toremove, size_t ntime = 1);

void injectOnFile(std::string filepath, std::string toadd, bool overwrite = false, size_t ntime = 1);