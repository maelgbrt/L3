#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
//#include <strerror.h>

void main()
{   
    const char * name;
    const char * desc;
    for (int i = 0; i < 256; i++) {
        name = strerrorname_np(i);
        desc = strerrordesc_np(i);
        if (name && desc) {
            printf("ID ERROR : %d\n NAME : %s\n DESC : %s\n\n", i, name, desc);
        }
    }
}