#ifndef _SFS_VOLUME_H_
#define _SFS_VOLUME_H_

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "sfs_log.h"
#include "sfs_low_level.h"
#include "sfs_parameters.h"

//////////////////////////////////////////////////////////////////////////////
// a type synomym for blocks of bytes, and a global variable for the blocks in
// the partition
typedef byte block_t[BLOCK_SIZE];

// block 0 is only used for sparse files containing zero blocks
#define ZERO_BLOCK 0

//////////
// inodes

// number of direct blocks pointed to by each inode
#define NB_DIRECT_BLOCKS 11

// index of the block containing indirect blocks
// (unused for directories / symlinks)
#define INDIRECT_BLOCKS NB_DIRECT_BLOCKS

// inode structure
typedef struct inode {
    int type;   // inode type: S_IFREG, S_IFDIR, S_IFLNK
    int size;   // size, in bytes of the corresponding file
    int nlinks; // number of hard links to this inode (0 means the inode is
                // free)
    int blocks[NB_DIRECT_BLOCKS
        + 2]; // blocks for the data (last 2 blocks for single / double
              // indirection blocks)

    int mtime; // modification time (unused)
} inode_t;

// special inodes
#define BADBLOCKS_INODE 1 // inode number for collecting badblocks
#define ROOT_INODE 2      // inode number for root directory

int sfs_mkfs(const char* path);
int sfs_mount(const char* path);
int sfs_sync();
int sfs_umount();

block_t* sfs_get_block(int nb);
int sfs_block_in_use(int nb);
void sfs_free_block(int nb);
void sfs_use_block(int nb);
int sfs_find_free_block();

inode_t* sfs_get_inode(int nb);
int sfs_find_free_inode();

void fprint_inode(FILE* f, int nb);

#endif // _SFS_VOLUME_H_
