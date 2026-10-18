#ifndef _SFS_PARAMETERS_H_
#define _SFS_PARAMETERS_H_

////////////////////////////////////////////////////////////////////////////
// static information that would usually be found in super bloc at beginning
// of partition...

// size (in bytes) of blocks
// should probably be a multiple of 512 bytes
#define BLOCK_SIZE 512

// size (in blocks) of data partition
#define DATA_SIZE 2048

// total number of inodes
#define NB_INODES 512

////////////////////////////////////////////////////////////
// the other constant are computed from the previous ones...
// DO NOT CHANGE THEM

// size (in bytes) of bitmap for free blocks: ceiling(DATA_SIZE/8)
#define BITMAP_SIZE_BYTES (DATA_SIZE / 8 + (DATA_SIZE % 8 != 0))

// size (in blocks) of bitmap for free blocks: ceiling(BITMAP_SIZE_BYTES/BLOCK_SIZE)
#define BITMAP_SIZE (BITMAP_SIZE_BYTES / BLOCK_SIZE + (BITMAP_SIZE_BYTES % BLOCK_SIZE != 0))

// size (in blocks) of inode table: ceiling(NB_INODES*sizeof(inode_t) / BLOCK_SIZE)
#define INODE_TABLE_SIZE ((int)(NB_INODES * sizeof(inode_t)) / BLOCK_SIZE + ((NB_INODES * sizeof(inode_t)) % BLOCK_SIZE != 0))

// total size (in bytes) of the partition
#define TOTAL_SIZE ((BITMAP_SIZE + INODE_TABLE_SIZE + DATA_SIZE) * BLOCK_SIZE)

#endif // _SFS_PARAMETERS_H_
