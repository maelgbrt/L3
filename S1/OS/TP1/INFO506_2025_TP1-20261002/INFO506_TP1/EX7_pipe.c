#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>

/* 
 * Communication par un pipe 
 */
int main(void){
	char buffer[100] ;
	int pid ; 
	int pfds[2] ; //pipe fd[0] RD, fd[1] WR
	
	//1- creer le pipe pour avoir le deux fd
	if(pipe(pfds)!=0){
		exit(EXIT_FAILURE) ; 
	} 

	/* Le pere ecrit, le fils lit*/
	pid=fork() ;
	if(pid<0)
		exit(EXIT_FAILURE) ; 
		
	
	if(pid>0){
		//ferme la lecture
		close(pfds[0]) ;
		dup2(pfds[1],1) ; 
		printf("Ton pid est %d", pid);
		close(pfds[1]) ;
	} else {
		close(pfds[1]) ;
		dup2(pfds[0],0) ; 
		//read(0, buffer, 20) ;
		fgets(buffer, 20, stdin); 
		printf("Message de mon pere: %s\n", buffer);
	}

	return (0) ; 
}
