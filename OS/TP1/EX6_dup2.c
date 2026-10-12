#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(void){
	
	int nvfd=open("nvfic.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP  ); 
	
	/* le nouveau descripteur de fichier remplace le
	 * descripteur 1 (stdout: sortie standard) */
	dup2(nvfd,1); 
	
	
	printf("La sortie de ce processus est redirigé vers un fichier\n") ; 
	
	return 0 ;
}
