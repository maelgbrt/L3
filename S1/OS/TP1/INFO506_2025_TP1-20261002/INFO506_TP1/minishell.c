// TP 1 INFO506

// Hania Boudjaj
// Maël Gaborit

#include <stddef.h>
#include <string.h>
#include <stdio.h>

//------------ Question 1 -------------- //
int get_cmd_args ( char * cmdline , char ** cmdargs ) {

	char *element;
	int i = 0;
	element = strtok(cmdline, " ") ;
	
	while(element != NULL){
		cmdargs[i] = element;
		i++;                   
		element = strtok(NULL, " ") ;
    }
	cmdargs[i] = NULL;         
	return (0) ;
}



int main(void) {
    
    char ch[] = "grep toto fic.txt";
    char *tab[10];

    int rep = get_cmd_args(ch,tab);

	for (int i = 0; tab[i] != NULL; i++){
		puts(tab[i]);
	}
}