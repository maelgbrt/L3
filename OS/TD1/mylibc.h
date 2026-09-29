/**
 * Compilation: 
 * 	gcc -m32 -fno-pie -c mylibc.c -o mylibc.o
 * 	gcc -m32 -nostdlib -fno-pie -no-pie main.c mylibc.o -o main
 *
 *
 */

#ifndef MYLIBC_H
#define MYLIBC_H

int my_read(int fd, char *buf, int len);

int my_write(int fd, const char *buf, int len);

int my_open(const char *pathname, int flags, int mode);

int my_close(int fd);

#endif
