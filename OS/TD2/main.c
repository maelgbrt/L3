/**
 * compilation
 * gcc -m32 -fno-pie -c mylibc.c -o mylibc.o
 * gcc -m32 -fno-pie -c myerrno.c -o myerrno.o
 * gcc -m32 -nostdlib -fno-pie -no-pie main.c mylibc.o myerrno.o -o main
 *
 * Exemple de macro d'ouverture :
 * O_RDONLY 0 
 * O_WRONLY 1 
 * O_RDWR 2
 *
 */

#include "mylibc.h"
#include "myerrno.h"

void _start(void)
{
    asm volatile (
        "call main\n"
        "movl %eax, %ebx\n"
        "movl $1, %eax\n"
        "int $0x80\n"
    );
}

int strlen(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}


void main(void){
	const char* errname ; 
	const char* errdesc ; 
	
	int fd=my_open("titi", 0, 0644) ;	//ENOENT titi n existe pas 
	if(fd<0){
	 	errname=strerrorname(errno) ;			
	 	my_write(1,errname,strlen(errname)) ;
	 	
		errdesc=strerrordesc(errno) ;			
	 	my_write(1,errdesc,strlen(errdesc)) ;
	}

    if(my_write(13,"TOTO",4)<0){
        errname=strerrorname(errno);
        my_write(1,errname,strlen(errname));
    }

}
