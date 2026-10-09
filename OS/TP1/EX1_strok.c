#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CMD_LINE_LENGTH 100


int main(void){
	char str[]= "UN DEUX TROIS QUATRE" ; 
	char *element;

	element=strtok(str, " ") ;
	puts(element) ; 

	while( (element=strtok(NULL, " ")) ){
		puts(element) ; 
        }

	return (0) ;
}
