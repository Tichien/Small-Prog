#ifndef CHECK_H
#define CHECK_H

#define CHECK_FD(FD, FDNAME) 														\
if(FD < 0){																			\
	fprintf(stderr, "Erreur : Problème à l'ouverture du fichier %s\n", FDNAME); 	\
	fprintf(stderr, "%s\n", strerror(FD));											\
	return FD; 																		\
}																					\

#define CHECK_FILE(F, FNAME) 													\
if(F == NULL){																	\
	fprintf(stderr, "Erreur : Problème à l'ouverture du fichier %s\n", FNAME);	\
	return -1; 																	\
}																				\

#define CHECK_ERROR(ERRNO) 									\
if(ERRNO < 0){												\
	fprintf(stderr, "%s\n", strerror(ERRNO));				\
	return ERRNO;											\
}															\

#endif