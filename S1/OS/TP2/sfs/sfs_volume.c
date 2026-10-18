#include "sfs_volume.h"

////////////////////////////////////////////////////////
// global variable to randomize inodes and blocks search
int sfs_randomize = 1;

// global variable containing a pointer to the blocks of the mounted
// filesystem
block_t* sfs_blocks = NULL;

//////////////////////////////
// dealing with SFS partitions

// create a new SFS filesystem inside a Unix file
int sfs_mkfs(const char* path)
{
    int fd;
    if (-1 == (fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644))) {
        return -1;
    }
    // on creation, the file is "sparse": it contains a single byte 0 at the
    // end...
    char c = 0;
    if (-1 == lseek(fd, TOTAL_SIZE - 1, SEEK_SET)) {
        return -1;
    }
    if (-1 == write(fd, &c, 1)) {
        return -1;
    }
    if (-1 == close(fd)) {
        return -1;
    }
    // we now need to create the root directory
    sfs_mount(path);
    inode_t* nd;

    // the special inode for badblocks
    nd = sfs_get_inode(BADBLOCKS_INODE);
    nd->type = S_IFREG;
    nd->size = 0;
    nd->nlinks = 1;

    // the root directory
    nd = sfs_get_inode(ROOT_INODE);
    nd->type = S_IFDIR;
    nd->nlinks = 2;
    nd->size = BLOCK_SIZE;
    int nb = sfs_dir_init(ROOT_INODE, ROOT_INODE);
    nd->blocks[0] = nb;

    block_t* b = sfs_get_block(ZERO_BLOCK);
    sfs_use_block(ZERO_BLOCK);
    memset(*b, 0, BLOCK_SIZE);

    sfs_umount();

    return 0;
}

// mount an existing SFS filesystem from a Unix file
int sfs_mount(const char* path)
{
    int fd = open(path, O_RDWR);
    if (-1 == fd) {
        return -1;
    }
    // check that the file of the Unix file is indeed the expected size of an
    // SFS filesystem
    struct stat sb;
    fstat(fd, &sb);
    assert(sb.st_size == TOTAL_SIZE);

    // mmap the file into memory
    // NOTE: sfs_blocks is a global variable
    sfs_blocks
        = mmap(NULL, TOTAL_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (MAP_FAILED == sfs_blocks) {
        return -1;
    }
    // close file
    // NOTE: changes are written to disk when umounting the partition, or when
    // calling sfs_sync()
    if (-1 == close(fd)) {
        return -1;
    }

    return 0;
}

// synchronize mounted filesystem to disk
int sfs_sync()
{
    if (-1 == msync(sfs_blocks, TOTAL_SIZE, MS_SYNC)) {
        return -1;
    }
    return 0;
}

// unmount current filesystem
int sfs_umount()
{
    if (-1 == munmap(sfs_blocks, TOTAL_SIZE)) {
        return -1;
    }
    sfs_blocks = NULL;
    return 0;
}

///////////////////////////////
// SFS bitmap for free blocks

// get data block from datablock_number
inline block_t* sfs_get_block(int nb)
{
    // recall that data blocks come __after__ the bitmap for free
    // blocks and the inode table
    return sfs_blocks + BITMAP_SIZE + INODE_TABLE_SIZE + nb;
}

// check if data block number ``n`` is used
int sfs_block_in_use(int nb)
{
    // the byte for block ``n``
    byte c = ((byte*)sfs_blocks)[nb / 8];

    return BIT(nb % 8, c);
}

// free data block by putting its corresponding bit to 0 in the bitmap
void sfs_free_block(int nb)
{
    // do not deallocate dummy zero block
    if (nb == ZERO_BLOCK)
        return;

    // the byte for block ``n``
    byte* c = ((byte*)sfs_blocks) + (nb / 8);

    *c &= ~(1 << (nb % 8));
}

// allocate data block by putting its corresponding bit to 1 in the bitmap
void sfs_use_block(int nb)
{
    // the byte for block ``n``
    byte* c = ((byte*)sfs_blocks) + (nb / 8);

    *c |= 1 << (nb % 8);
}

// look for a free data block
int sfs_find_free_block()
{
    int start = sfs_randomize ? rand() % DATA_SIZE : 0;
    int n;
    for (int i = 0; i < DATA_SIZE; i++) {
        n = (start + i) % DATA_SIZE;
        if (n == ZERO_BLOCK)
            continue; // don't use block 0
        if (sfs_block_in_use(n) == 0)
            return (start + i) % DATA_SIZE;
    }
    // if we reach this point, we haven't found a free block
    errno = ENOSPC;
    return -1;
}

//////////////
// SFS inodes

// get inode from inode number
inline inode_t* sfs_get_inode(int nb)
{
    // recall that inode table comes __after__ the bitmap for free blocks
    return (inode_t*)(sfs_blocks + BITMAP_SIZE) + nb;
}

// look for an unused inode
int sfs_find_free_inode()
{
    inode_t* nd;
    int n;
    int start = sfs_randomize ? rand() % NB_INODES : 0;
    for (int nb = ROOT_INODE; nb < NB_INODES; nb++) {
        n = (start + nb) % NB_INODES;
        if (n < ROOT_INODE)
            continue; // don't use inodes before root number
        nd = sfs_get_inode(n);
        if (nd->nlinks == 0) {
            return (start + nb) % NB_INODES;
        }
    }
    // if we reach this point, we haven't found a free inode
    // FIXME: is ENOSPC the appropriate error code?
    errno = ENOSPC;
    return -1;
}

// log
void fprint_inode(FILE* f, int nb)
{
    inode_t* nd = sfs_get_inode(nb);
    fprintf(f, "inode n° %d (%s)\n", nb, nd->nlinks == 0 ? "free" : "used");
    if (nd->nlinks == 0)
        return;

    fprintf(f, "  - type: ");
    if (nd->type == S_IFREG)
        fprintf(f, "regular file\n");
    else if (nd->type == S_IFDIR)
        fprintf(f, "directory\n");
    else if (nd->type == S_IFLNK)
        fprintf(f, "symbolic link\n");
    else
        fprintf(f, "???\n");
    fprintf(f, "  - size: %d byte(s)\n", nd->size);
    fprintf(f, "  - nlinks: %d\n", nd->nlinks);
    fprintf(f, "  - pointers to data blocks:\n");
    for (int i = 0; i < NB_DIRECT_BLOCKS + 1; i++) {
        fprintf(f, "       blocks[%2d] = %-6d", i, nd->blocks[i]);
        if (i >= nd->size / BLOCK_SIZE + (nd->size % BLOCK_SIZE != 0)) {
            fprintf(f, " unused");
        } else {
            fprintf(f, " (0x%x)", nd->blocks[i]);
        }
        fprintf(f, "\n");
    }
}
// vim: foldmethod=syntax
