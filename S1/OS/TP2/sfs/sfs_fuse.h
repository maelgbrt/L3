#ifndef _SFS_FUSE_H_
#define _SFS_FUSE_H_

#define FUSE_USE_VERSION 29
//#define _XOPEN_SOURCE 500         // unnecessary when compiling with
//--std=gnu99

#include <errno.h>
#include <fuse.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sfs_log.h"
#include "sfs_parameters.h"
#include "sfs_posix.h"
#include "sfs_volume.h"

#define MINUS_ERRNO                                                          \
    (errno > 0 ? (LOG("      => errno: %s\n", strerror(errno)), -errno)      \
               : (LOG("     => NO errno\n"), -1))

////////////////////
// fuse privata data
struct sfs_state {
    char* sfsfile; // path to file containing sfs filesystem
};
#define SFS_DATA ((struct sfs_state*)fuse_get_context()->private_data)

///////////////////
// init and destroy
void* fuse_sfs_init(struct fuse_conn_info* conn);
void fuse_sfs_destroy(void* userdata);

//////////////////////////
// POSIX like system calls
int fuse_sfs_statfs(const char* path, struct statvfs* buf);
int fuse_sfs_getattr(const char* path, struct stat* buf);
int fuse_sfs_create(const char* path, mode_t mode, struct fuse_file_info* fi);
int fuse_sfs_unlink(const char* path);
int fuse_sfs_link(const char* path, const char* newpath);
int fuse_sfs_open(const char* path, struct fuse_file_info* fi);
int fuse_sfs_read(const char* path, char* buf, size_t size, off_t offset,
    struct fuse_file_info* fi);
int fuse_sfs_write(const char* path, const char* buf, size_t size,
    off_t offset, struct fuse_file_info* fi);
int fuse_sfs_close(const char* path, struct fuse_file_info* fi);
int fuse_sfs_mkdir(const char* path, mode_t mode);
int fuse_sfs_rmdir(const char* path);
int fuse_sfs_opendir(const char* path, struct fuse_file_info* fi);
int fuse_sfs_readdir(const char* path, void* buf, fuse_fill_dir_t filler,
    off_t offset, struct fuse_file_info* fi);
int fuse_sfs_closedir(const char* path, struct fuse_file_info* fi);
int fuse_sfs_truncate(const char* path, off_t offset);
int fuse_sfs_rename(const char* path, const char* newpath);
int fuse_sfs_symlink(const char* path, const char* link);
int fuse_sfs_readlink(const char* path, char* link, size_t size);

#endif // _SFS_FUSE_H_
