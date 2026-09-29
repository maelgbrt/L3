#include "mylibc.h"
#include <errno.h>

int my_write(int fd, const char *buf, int len)
{
    int ret;

    asm volatile (
        "movl $4, %%eax\n"
        "int $0x80\n"
        : "=a"(ret)
        : "b"(fd), "c"(buf), "d"(len)
        : "memory"
    );

    // Code erroné dans le sujet :
if (ret < 0) {
    errno = -ret;
    return -1;
}
return ret;
}

int my_read(int fd, char *buf, int len)
{
    int ret;

    asm volatile (
        "movl $3, %%eax\n"
        "int $0x80\n"
        : "=a"(ret)
        : "b"(fd), "c"(buf), "d"(len)
        : "memory"
    );

    return ret;
}

int my_open(const char *pathname, int flags, int mode)
{
    int ret;

    asm volatile (
        "movl $5, %%eax\n"
        "int $0x80\n"
        : "=a"(ret)
        : "b"(pathname), "c"(flags), "d"(mode)
        : "memory"
    );

    return ret;
}

int my_close(int fd)
{
    int ret;

    asm volatile (
        "movl $6, %%eax\n"
        "int $0x80\n"
        : "=a"(ret)
        : "b"(fd)
        : "memory"
    );

    return ret;
}