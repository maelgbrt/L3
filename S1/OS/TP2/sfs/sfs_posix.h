#ifndef _S_IFREGS_H_
#define _S_IFREGS_H_

#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/statvfs.h>

#include "sfs_log.h"
#include "sfs_low_level.h"
#include "sfs_parameters.h"
#include "sfs_volume.h"

////////////////////
// file descriptors
typedef struct file_descriptor {
    int inode;  // number of the opened inode
    int cursor; // current pointer inside the file
    int mode;   // mode
} sfs_file_t;

typedef struct dir_descriptor {
    int inode;            // number of the corresponding inode
    int entry_idx;        // index to current entry
    struct dirent dirent; // placeholder for dirent information
} sfs_dir_t;

int sfs_statvfs(const char* path, struct statvfs* buf);
int sfs_stat(const char* path, struct stat* buf);

int sfs_creat(const char* path);
int sfs_link(const char* src, const char* dest);
int sfs_unlink(const char* path);
int sfs_rename(const char* path, const char* link);
int sfs_truncate(const char* path, int length);
sfs_file_t* sfs_open(const char* path, int mode);
int sfs_close(sfs_file_t* file);
int sfs_seek(sfs_file_t* file, int offset, int whence);
int sfs_read(sfs_file_t* file, char* buffer, int nbyte);
int sfs_pread(sfs_file_t* file, char* buffer, int nbyte, int offset);
int sfs_write(sfs_file_t* file, const char* buffer, int nbyte);
int sfs_pwrite(sfs_file_t* file, const char* buffer, int nbyte, int offset);

int sfs_mkdir(const char* path);
sfs_dir_t* sfs_opendir(const char* path);
struct dirent* sfs_readdir(sfs_dir_t* dirp);
int sfs_closedir(sfs_dir_t* dir);
int sfs_rmdir(const char* path);

int sfs_symlink(const char* path, const char* link);
int sfs_readlink(const char* path, char* buf, int bufsize);

#endif // _S_IFREGS_H_
