#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void question1(void) {
    const char *name;
    const char *description;

    for (int i = 0; i < 256; i++) {
        name = strerrorname_np(i);
        description = strerrordesc_np(i);

        if (name && description) {
            printf("%d : %s : %s\n", i, name, description);
        }
    }

}



int main(void) {
//     question1();
// 
// 
//     const char* errname;
//     int fd=my_open("toto.txt",0,0644);
//     int fd=my_open("titi.txt",0,0644);
//     if(fd<0){
        // errname = 
//     }

    /* Code fork commenté
    int pid = fork();
    if (pid > 0) {
        printf("\n\e[1;42m Pour le pere: pid = %d \e[0m\n", pid);
    } else if (pid == 0) {
        sleep(10);
        printf("\n\e[1;41m Pour le fils: pid = %d \e[0m\n", pid);
    } else {
        perror("fork");
    }

    while (1);
    */

    return 0;
}