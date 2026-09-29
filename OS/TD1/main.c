/**
 * compilation
 * gcc -m32 -fno-pie -c mylibc.c -o mylibc.o
 * gcc -m32 -nostdlib -fno-pie -no-pie main.c mylibc.o -o main
 *
 */

#include "mylibc.h"

void _start(void)
{
    asm volatile (
        "call main\n"
        "movl %eax, %ebx\n"
        "movl $1, %eax\n"
        "int $0x80\n"
    );
}

void main(void){
	my_write(1,"Hello\n", 6) ; 
}
