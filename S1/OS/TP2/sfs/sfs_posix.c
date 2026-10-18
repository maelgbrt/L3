#include "sfs_posix.h"

int sfs_statvfs(const char* path, struct statvfs* buf)
{

    buf->f_bsize = BLOCK_SIZE; // Filesystem block size: optimal block size
                               // for IO calls

    buf->f_frsize = BLOCK_SIZE; // Fragment size: minimum allocation unit

    buf->f_blocks = DATA_SIZE; // Size of fs in f_frsize units

    buf->f_bfree = sfs_count_free_blocks(); // Number of free blocks

    buf->f_bavail
        = buf->f_bfree; // Number of free blocks for unprivileged users

    buf->f_files = NB_INODES; // Number of inodes

    buf->f_ffree = sfs_count_free_inodes(); // Number of free inodes

    buf->f_favail
        = buf->f_ffree; // Number of free inodes for unprivileged users

    buf->f_namemax = SFS_NAME_MAX; // Maximum filename length

    buf->f_fsid = 0; // Filesystem ID... UNUSED

    buf->f_flag = 0; // Mount flags... UNUSED

    return 0;
}

int sfs_stat(const char* path, struct stat* buf)
{
    // TODO: EFAULT? ELOOP? ENAMETOOLONG? ENOMEM? EOVERFLOW?
    // ENOENT ENOTDIR
    int nb = sfs_localize(path);
    if (nb == -1) {
        return -1;
    }
    inode_t* nd = sfs_get_inode(nb);

    buf->st_ino = nb;

    if (nd->nlinks == 0)
        return -1;

    if (S_ISDIR(nd->type))
        buf->st_mode = nd->type | 0755;
    else
        buf->st_mode = nd->type | 0644;

    buf->st_nlink = nd->nlinks;
    buf->st_size = nd->size;

    buf->st_blocks = (sfs_count_used_blocks_inode(nb) * BLOCK_SIZE) / 512;

    buf->st_uid = getuid();
    buf->st_gid = getgid();

    /*
       fields ignored by fuse:
       dev_t st_dev            Device ID of device containing file.
       blksize_t st_blksize    A file system-specific preferred I/O block size
       for this object. In some file system types, this
       may vary from file to file.

       other fields:
       dev_t st_rdev           Device ID (if file is character or block
       special). struct timespec st_atim Last data access timestamp. struct
       timespec st_mtim Last data modification timestamp. struct timespec
       st_ctim Last file status change timestamp.
     */

    return 0;
}

// NOTE: ``dir`` and ``name`` must contain at least SFS_PATH_MAX+1 and
// SFS_NAME_MAX+1 characters
int decompose_path(const char* path, char* dir, char* name)
{
    if (strlen(path) > SFS_PATH_MAX) {
        errno = ENAMETOOLONG; // FIXME: ???
        return -1;
    }
    char dir_tmp[SFS_PATH_MAX + 1];
    strncpy(dir_tmp, path, SFS_PATH_MAX + 1);
    char name_tmp[SFS_PATH_MAX + 1];
    strncpy(name_tmp, path, SFS_PATH_MAX + 1);

    char* dir_p = dirname(dir_tmp);
    char* name_p = basename(name_tmp);
    if (strlen(name_p) > SFS_NAME_MAX) {
        errno = ENAMETOOLONG; // FIXME: ???
        return -1;
    }
    strncpy(dir, dir_p, SFS_NAME_MAX + 1);
    strncpy(name, name_p, SFS_NAME_MAX + 1);
    return 0;
}

// TODO: this returns a positive number (inode number) on success, instead of
// 0 as in POSIX
int sfs_creat(const char* path)
{
    char dir[SFS_PATH_MAX + 1];
    char name[SFS_NAME_MAX + 1];
    if (decompose_path(path, dir, name) < 0) {
        return -1;
    }

    int parent = sfs_localize(dir);
    if (parent < 0) {
        // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG, ELOOP?
        return -1;
    }

    int nb = sfs_create_empty_file(parent, name);
    if (nb < 0) {
        // TODO errno
        return -1;
    }

    return nb;
}

int sfs_link(const char* src, const char* dest)
{
    int src_n = sfs_localize(src);
    if (src_n < 0) {
        // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG, ELOOP?
        return -1;
    }

    char dir[SFS_PATH_MAX + 1];
    char name[SFS_NAME_MAX + 1];
    if (decompose_path(dest, dir, name) < 0) {
        return -1;
    }

    int parent = sfs_localize(dir);
    if (parent < 0) {
        // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG, ELOOP?
        return -1;
    }

    if (sfs_link_inode(parent, src_n, name) < 0) {
        // TODO errno
        return -1;
    }

    return 0;
}

int sfs_unlink(const char* path)
{
    int file_n = sfs_localize(path);
    if (file_n < 0) {
        // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG, ELOOP?
        return -1;
    }
    char dir[SFS_PATH_MAX + 1];
    char name[SFS_NAME_MAX + 1];
    if (decompose_path(path, dir, name) < 0) {
        return -1;
    }
    int dir_n = sfs_localize(dir);
    if (dir_n < 0) {
        // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG, ELOOP?
        return -1;
    }
    if (sfs_unlink_inode(file_n, name, dir_n) < 0) {
        return -1;
    }
    return 0;
}

int sfs_rename(const char* path, const char* link)
{
    if (sfs_link(path, link) < 0) {
        return -1;
    }
    if (sfs_unlink(path) < 0) {
        return -1;
    }
    return 0;
}

int sfs_truncate(const char* path, int length)
{
    int nb = sfs_localize(path);
    if (nb < 0) {
        // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG, ELOOP?
        return -1;
    }
    return sfs_truncate_inode(nb, length);
}

sfs_file_t* sfs_open(const char* path, int mode)
{
    int nb = sfs_localize(path);
    if (nb == -1) {

        // other errors : EBADF, ENOTDIR, ENOENT
        if (errno == ELOOP || errno == ENAMETOOLONG) {
            return NULL;
        }
        if ((mode & O_CREAT) == 0) {
            errno = ENOENT;
            return NULL;
        }
        nb = sfs_creat(path);
        if (nb < 0) {
            // TODO errno ???
            return NULL;
        }
    }

    inode_t* nd = sfs_get_inode(nb);
    if (nd->type != S_IFREG) {
        errno = ENOENT;
        return NULL;
    }

    sfs_file_t* file = malloc(sizeof(sfs_file_t));
    file->inode = nb;
    file->mode = mode;
    if ((mode & O_APPEND) == 0) {
        file->cursor = 0;
    } else {
        file->cursor = nd->size;
    }

    return file;
}

int sfs_close(sfs_file_t* file)
{
    if (file->inode < ROOT_INODE || file->inode >= NB_INODES) {
        errno = EBADF;
        return -1;
    }
    /* sfs_sync(); */
    free(file);
    return 0;
}

int sfs_seek(sfs_file_t* file, int offset, int whence)
{
    if (whence == SEEK_SET) {
        if (offset < 0) {
            errno = EINVAL;
            return -1;
        }
        file->cursor = whence;
        return file->cursor;
    } else if (whence == SEEK_CUR) {
        if (file->cursor + whence < 0) {
            errno = EINVAL;
            return -1;
        }
        file->cursor += whence;
        return file->cursor;
    } else if (whence == SEEK_END) {
        inode_t* nd = sfs_get_inode(file->inode);
        if (nd->size + whence < 0) {
            errno = EINVAL;
            return -1;
        }
        file->cursor = nd->size + whence;
        return file->cursor;
    } else {
        errno = EINVAL;
        return -1;
    }
}

int sfs_read(sfs_file_t* file, char* buffer, int nbyte)
{
    // ENOMEM???
    int nb = sfs_read_from_inode(file->inode, file->cursor, buffer, nbyte);
    if (nb < 0) {
        // errno = EBADF, EINVAL, EISDIR
        return -1;
    }
    file->cursor += nb;
    return nb;
}

int sfs_pread(sfs_file_t* file, char* buffer, int nbyte, int offset)
{
    // ENOMEM???
    int nb = sfs_read_from_inode(file->inode, offset, buffer, nbyte);
    if (nb < 0) {
        // errno = EBADF, EINVAL, EISDIR
        return -1;
    }
    return nb;
}

int sfs_write(sfs_file_t* file, const char* buffer, int nbyte)
{
    // EBADF, EFBIG ENOSPC
    int nb = sfs_write_to_inode(file->inode, file->cursor, buffer, nbyte);
    if (nb < 0) {
        // errno = EBADF, EINVAL, ENOSPC, EFBIG
        return -1;
    }
    file->cursor += nb;
    return nb;
}

int sfs_pwrite(sfs_file_t* file, const char* buffer, int nbyte, int offset)
{
    int nb = sfs_write_to_inode(file->inode, offset, buffer, nbyte);
    if (nb < 0) {
        // errno = EBADF, EINVAL, ENOSPC, EFBIG
        return -1;
    }
    return nb;
}

int sfs_mkdir(const char* path)
{
    // TODO: EMLINK?
    // TODO: link number for directories
    char dir[SFS_PATH_MAX + 1];
    char name[SFS_NAME_MAX + 1];
    if (decompose_path(path, dir, name) < 0) {
        return -1;
    }

    int parent = sfs_localize(dir);
    if (parent < 0) {
        // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG, ELOOP?
        return -1;
    }

    if (strlen(name) > SFS_NAME_MAX) {
        errno = ENAMETOOLONG;
        return -1;
    }

    int inode_nb = sfs_mkdir_inode(parent, name);

    if (inode_nb < 0) {
        return -1;
    }

    return 0;
}

sfs_dir_t* sfs_opendir(const char* path)
{
    // TODO: ENOENT ENOTDIR
    int nb = sfs_localize(path);
    if (nb < 0) {
        // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG, ELOOP?
        return NULL;
    }

    inode_t* nd = sfs_get_inode(nb);
    if (nd->type != S_IFDIR) {
        errno = ENOTDIR;
        return NULL;
    }

    sfs_dir_t* dir = malloc(sizeof(sfs_dir_t));

    dir->inode = nb;
    dir->entry_idx = 0;

    return dir;
}

struct dirent* sfs_readdir(sfs_dir_t* dirp)
{
    // TODO EBADF
    int nb = dirp->inode;
    inode_t* nd = sfs_get_inode(nb);

    block_t* b;
    dir_entry_t* entries;

    int i, k;

    int idx = dirp->entry_idx;
    for (i = idx / ENTRIES_PER_BLOCK; i < nd->size / BLOCK_SIZE; i++) {
        b = sfs_get_block(nd->blocks[i]);
        entries = (dir_entry_t*)b;
        for (k = idx % ENTRIES_PER_BLOCK; k < ENTRIES_PER_BLOCK; k++) {
            dirp->entry_idx++;
            if (0 != entries[k].inode_nb) {
                dirp->dirent.d_ino = entries[k].inode_nb;
                strncpy(dirp->dirent.d_name, entries[k].name, SFS_NAME_MAX);
                return &dirp->dirent;
            }
        }
        idx = 0;
    }
    return NULL;
}

int sfs_closedir(sfs_dir_t* dir)
{
    if (dir->inode < ROOT_INODE || dir->inode >= NB_INODES) {
        errno = EBADF;
        return -1;
    }
    /* sfs_sync(); */
    free(dir);
    return 0;
}

int sfs_rmdir(const char* path)
{
    int dir_n = sfs_localize(path);
    if (dir_n < 0) {
        // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG, ELOOP?
        return -1;
    }

    char dir[SFS_PATH_MAX + 1];
    char name[SFS_NAME_MAX + 1];
    if (decompose_path(path, dir, name) < 0) {
        return -1;
    }

    int parent_n = sfs_localize(dir);
    assert(dir_n > 0);
    if (sfs_unlink_dir_inode(dir_n, name, parent_n) < 0) {
        return -1;
    }
    return 0;
}

int sfs_symlink(const char* target, const char* path)
{
    char dir[SFS_PATH_MAX + 1];
    char name[SFS_NAME_MAX + 1];
    if (decompose_path(path, dir, name) < 0) {
        return -1;
    }

    int parent = sfs_localize(dir);
    if (parent < 0) {
        // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG, ELOOP?
        return -1;
    }

    int nb = sfs_symlink_inode(parent, target, name);
    if (nb < 0) {
        // TODO errno
        return -1;
    }

    return nb;
}

int sfs_readlink(const char* path, char* buf, int bufsize)
{
    int nb = sfs_localize(path);
    if (nb < 0) {
        // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG, ELOOP?
        return -1;
    }
    inode_t* nd = sfs_get_inode(nb);
    if (nd->type != S_IFLNK) {
        errno = EINVAL;
        return -1;
    }
    return sfs_readlink_inode(nb, buf, bufsize);
}

// vim: foldmethod=syntax
