#include<unistd.h>
#include<stdio.h>
void main(void){
        int pid=fork();
        if(pid){
               printf("\n\e[1;42m Pour le pere: pid = %d \e[0m\n", pid) ;           
        } else {
                sleep(10) ;
                printf("\n\e[1;41m Pour le fils: pid  = %d \e[0m\n", pid) ;
        }
        
        while(1) ; 
}
