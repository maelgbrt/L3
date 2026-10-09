#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/**
 * Executez le programme en lui passant un argument Un, deux ou Trois
 *
 */
int main(int argc, char *argv[]){
	char *usage = "Usage: EX2_strcmp [ 1 | 2 | 3 ]\n" ; 
	if(argc==1){
		puts(usage)  ;
		exit(1) ;
	}

	if(strcmp(argv[1],"1")==0){
		printf("Un\n"); 		
	} 
	else if(strcmp(argv[1],"2")==0){
		printf("Deux\n"); 		
	} 
	else if(strcmp(argv[1],"3")==0){
		printf("Trois\n"); 		
	} else {
		printf("Argument non reconnu!!!\n") ; 
	}

	return 0; 
}
