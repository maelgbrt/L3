#ifndef _SFS_LOW_LEVEL_H_
#define _SFS_LOW_LEVEL_H_

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "sfs.h"
#include "sfs_log.h"
#include "sfs_parameters.h"
#include "sfs_volume.h"

// maximum length of filenames (not including the final '\0')
#define SFS_NAME_MAX 31

// maximum length of path (not including the final '\0')
#define SFS_PATH_MAX 255

// entry inside directory listing
typedef struct dir_entry {
    char name[SFS_NAME_MAX + 1];
    int inode_nb;
} dir_entry_t;

// number of entries per block
#define ENTRIES_PER_BLOCK ((int)(BLOCK_SIZE / sizeof(dir_entry_t)))

int sfs_count_free_blocks();
int sfs_count_free_inodes();
int sfs_count_used_blocks_inode(int nb);

int sfs_create_empty_file(int parent_nb, const char* name);
int sfs_truncate_inode(int nb, int length);
int sfs_deallocate_inode(int nb);
int sfs_unlink_inode(int nb, const char* name, int parent_nb);
int sfs_link_inode(int parent, int nb, const char* name);
int sfs_write_to_inode(int nb, int offset, const void* buf, int nbyte);
int sfs_read_from_inode(int nb, int offset, void* buf, int nbyte);

int sfs_add_entry(int dir_n, const char* name, int inode_nb);
int sfs_remove_entry(int dir_n, const char* name);
int sfs_find_entry(int dir_nb, const char* name);

int sfs_dir_init(int parent, int self);
int sfs_mkdir_inode(int parent_nb, const char* name);
int sfs_unlink_dir_inode(int nb, const char* dir_name, int parent_nb);

int sfs_symlink_inode(int parent_nb, const char* target, const char* name);
int sfs_writelink_inode(const char* target);
int sfs_readlink_inode(int nb, char* buf, int bufsize);

int sfs_localize(const char* path);

int sfs_write_to_block(
    int nb, int block_idx, int offset, const byte* buf, int size);
int sfs_read_from_block(
    int nb, int block_idx, int offset, byte* buf, int size);

#endif // _SFS_LOW_LEVEL_H_
