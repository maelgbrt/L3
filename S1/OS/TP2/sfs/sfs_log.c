#include "sfs_log.h"

FILE* logfile;

void init_log(const char* path)
{
    // TODO error handling
    logfile = fopen(path, "a");
}

// log message to logfile
void LOG(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(logfile, format, ap);
    fflush(logfile);
}

void LOG_inode(int nb) { fprint_inode(logfile, nb); }
