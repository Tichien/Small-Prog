#define CHECK_FD(FD, FDNAME) 														\
if(FD < 0){																			\
	fprintf(stderr, "Erreur : Problème à l'ouverture du fichier %s\n", FDNAME); 	\
	fprintf(stderr, "%s", strerror(FD));											\
	return EXIT_FAILURE; 															\
}																					\

#define CHECK_FILE(F, FNAME) 													\
if(F == NULL){																	\
	fprintf(stderr, "Erreur : Problème à l'ouverture du fichier %s\n", FNAME);	\
	return EXIT_FAILURE; 														\
}																				\

#define CHECK_ERROR(ERRNO) 									\
if((ERRNO) < 0){											\
	fprintf(stderr, "%s\n", strerror(ERRNO));				\
	return EXIT_FAILURE; 									\
}															\

int writer(int inputfd, int outputfd);

bool removeFromFile(std::string filepath, std::string toremove, size_t ntime = 1);

void injectOnFile(std::string filepath, std::string toadd, bool overwrite = false, size_t ntime = 1);