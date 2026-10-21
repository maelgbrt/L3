#include <stdio.h>
#include <stdlib.h>

/**
 * A utiliser avec la directive de compilation -m32
 *
 */

/* 
 * ces variables sont ajoutées par le linker
 */
extern char etext; // Fin de .text 
extern char edata; // Fin de .data
extern char end;   // Fin de .bss

char *ch1="123456789abcdefg"; 
char ch2[]="123456789abcdefg";






void question12(void){
char *Blk1 = malloc(1024);
char *Blk2 = malloc(1024);
char *Blk3 = malloc(1024);
  
    printf("\n---QUESTION 1.2---\n");
    printf("@Blk1 = %p et Blk1 = %p \n", &Blk1, Blk1);
    printf("@Blk2 = %p et Blk2 = %p \n", &Blk2, Blk2);
    printf("@Blk3 = %p et Blk3 = %p \n", &Blk3, Blk3);
}



void f(){
    char *Blk1 = malloc(1024);
    printf("@Blk1 = %p et Blk1 = %p \n", &Blk1, Blk1);
    g();
}
void g(){
    char *Blk2 = malloc(1024);
    printf("@Blk1 = %p et Blk1 = %p \n", &Blk2, Blk2);
    h();
}
void h(){
    char *Blk3 = malloc(1024);
    printf("@Blk1 = %p et Blk1 = %p \n", &Blk3, Blk3);
}

int main() {
    char *ch3="123456789abcdefg";
    char ch4[]="123456789abcdefg";

    printf("Segment----------------------------------\n") ; 
    printf(".bss          : %p\n", (void*)&end); 	//global ni
    printf(".data         : %p\n", (void*)&edata); 	//global
    printf(".text	  : %p\n", (void*)&etext); 	//code

    // Cas 1 : Le pointeur global
    printf("String----------------------------------\n") ; 
    printf("@ch1: %p -> stocké dans .data\n", (void*)&ch1);  //@ch1 global => data
    printf("ch1: %p -> stocké dans .rodata\n", (void*)ch1);  //ch1 @ => CONTIENT UNE @de rodata (non mutable)
    printf("@ch2: %p -> stocké dans .data\n", (void*)&ch2);  //@ch2 global => data 
    printf("ch2: %p -> stocké dans .data\n", (void*)ch2);    //ch2 @ => contient une @ de data 

    // Cas 3 : Le pointeur local
    printf("@ch3: %p -> stocké dans la STACK\n", (void*)&ch3);
    printf("ch3: %p -> pointe vers .rodata\n", (void*)ch3);
    printf("@ch4: %p -> stocké dans la STACK\n", (void*)&ch4);
    printf("ch4: %p -> stocké dans la STACK\n", (void*)ch4);

    //Test de mutabilite
    //ch3[2]='5'; 
    question12();
    printf("-----question 1.3---------\n");
    f();
    
    return 0;
}




