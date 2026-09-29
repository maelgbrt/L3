#include"myerrno.h"

int errno=0 ;

// Tableaux de chaînes de caractères indexés directement par le code d'erreur
static const char *const error_names[] = {
    "SUCCESS",     // Indice 0 (Pas d'erreur)
    "EPERM",       // Indice 1
    "ENOENT",      // Indice 2
    "ESRCH",       // Indice 3
    "EINTR",       // Indice 4
    "EIO",         // Indice 5
    "ENXIO",       // Indice 6
    "E2BIG",       // Indice 7
    "ENOEXEC",     // Indice 8
    "EBADF",       // Indice 9
    "ECHILD",      // Indice 10
    "EAGAIN",      // Indice 11
    "ENOMEM",      // Indice 12
    "EACCES",      // Indice 13
    "EFAULT",      // Indice 14
    "ENOTBLK",     // Indice 15
    "EBUSY",       // Indice 16
    "EEXIST",      // Indice 17
    "EXDEV",       // Indice 18
    "ENODEV",      // Indice 19
    "ENOTDIR",     // Indice 20
    "EISDIR",      // Indice 21
    "EINVAL",      // Indice 22
    "ENFILE",      // Indice 23
    "EMFILE",      // Indice 24
    "ENOTTY",      // Indice 25
    "ETXTBSY",     // Indice 26
    "EFBIG",       // Indice 27
    "ENOSPC",      // Indice 28
    "ESPIPE",      // Indice 29
    "EROFS",       // Indice 30
    "MLINK",       // Indice 31
    "EPIPE",       // Indice 32
    "EDOM",        // Indice 33
    "ERANGE"       // Indice 34
};

static const char *const error_descs[] = {
    "Success",                                // Indice 0
    "Operation not permitted",                 // Indice 1
    "No such file or directory",               // Indice 2
    "No such process",                         // Indice 3
    "Interrupted system call",                 // Indice 4
    "I/O error",                               // Indice 5
    "No such device or address",               // Indice 6
    "Argument list too long",                  // Indice 7
    "Exec format error",                       // Indice 8
    "Bad file number",                         // Indice 9
    "No child processes",                      // Indice 10
    "Try again",                               // Indice 11
    "Out of memory",                           // Indice 12
    "Permission denied",                       // Indice 13
    "Bad address",                             // Indice 14
    "Block device required",                   // Indice 15
    "Device or resource busy",                 // Indice 16
    "File exists",                             // Indice 17
    "Cross-device link",                       // Indice 18
    "No such device",                          // Indice 19
    "Not a directory",                         // Indice 20
    "Is a directory",                          // Indice 21
    "Invalid argument",                        // Indice 22
    "File table overflow",                     // Indice 23
    "Too many open files",                     // Indice 24
    "Not a typewriter",                        // Indice 25
    "Text file busy",                          // Indice 26
    "File too large",                          // Indice 27
    "No space left on device",                 // Indice 28
    "Illegal seek",                            // Indice 29
    "Read-only file system",                   // Indice 30
    "Too many links",                          // Indice 31
    "Broken pipe",                             // Indice 32
    "Math argument out of domain of func",     // Indice 33
    "Math result not representable"            // Indice 34
};

#define ERR_NB 35

const char *strerrorname(int err) {
    if (err >= 0 && err < ERR_NB ) {
        return error_names[err];
    }
    return "UNKNOWN ERROR";
}

const char *strerrordesc(int err) {
    if (err >= 0 && err < ERR_NB) {
        return error_descs[err];
    }
    return "UNKNOWN ERROR";
}

