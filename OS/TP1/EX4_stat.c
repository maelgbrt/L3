#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

/* Affiche la taille du binaire EX5_stat */
int main(int argc, char *argv[]){
	(void)argc ;	//Werror unused argc 

	//1 va contenir le info sur le fichier  
	struct stat statbuf ; 
       
	//2 info sur le fichier lui meme
	stat(argv[0], &statbuf);

	//3 affiche la taille du fichier 
	printf("%s: %lu octets\n", argv[0], statbuf.st_size) ; 

	return (0) ; 
}
