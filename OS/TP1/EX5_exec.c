#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

/* Lancement de la commande date */
int main(void){
	char *argv[]={"date", (char*)NULL } ; 
	execvp(argv[0], argv) ; 
	
	/*ne parvient pas a cette instruction en cas de succes*/
	fprintf(stderr, "Exec error: %d\n", errno) ; 
	return (0) ; 
}
