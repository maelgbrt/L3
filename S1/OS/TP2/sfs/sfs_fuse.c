#include "sfs_fuse.h"

////////////////////////////////////////////////////////
// global variable to randomize inodes and blocks search
extern int sfs_randomize;

///////////////////
// init and destroy
void* fuse_sfs_init(struct fuse_conn_info* conn)
{
    LOG("fuse => *******************************************************\n");
    LOG("fuse => v v v v v v v v v v v v v v v v v v v v v v v v v v v v\n");
    LOG("fuse => init: mounting '%s': ", SFS_DATA->sfsfile);
    sfs_mount(SFS_DATA->sfsfile);
    LOG(" OK\n");
    return SFS_DATA;
}

void fuse_sfs_destroy(void* userdata)
{
    LOG("fuse => destroy: \n  - sync: ");
    sfs_sync();
    LOG(" OK\n  - unmount: ");
    sfs_umount();
    LOG(" OK\n");
    LOG("fuse => ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^\n");
    LOG("fuse => *******************************************************\n");
}

//////////////////////////
// POSIX like system calls
int fuse_sfs_statfs(const char* path, struct statvfs* buf)
{
    LOG("fuse => statfs(%s, ...)\n", path);
    int r = sfs_statvfs(path, buf);
    if (r < 0) {
        LOG("fuse => PROBLEM\n");
        return MINUS_ERRNO;
    }
    return 0;
}

int fuse_sfs_getattr(const char* path, struct stat* buf)
{
    LOG("fuse => getattr(%s, ...) => ", path);
    int r = sfs_stat(path, buf);
    if (r < 0) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        LOG(" OK\n", path);
        return 0;
    }
}

int fuse_sfs_create(const char* path, mode_t mode, struct fuse_file_info* fi)
{
    LOG("fuse => create(%s, %o): ", path, mode);
    sfs_file_t* f = sfs_open(path, O_CREAT | O_WRONLY | O_TRUNC);
    if (f == NULL) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        LOG(" OK\n", path);
        fi->fh = (intptr_t)f;
        return 0;
    }
}

int fuse_sfs_unlink(const char* path)
{
    LOG("fuse => unlink(%s): ", path);
    int r = sfs_unlink(path);
    LOG(" OK (%d)\n", r);
    if (r < 0) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        LOG(" OK\n", path);
        return 0;
    }
}

int fuse_sfs_link(const char* path, const char* newpath)
{
    LOG("fuse => link(%s, %s): ", path, newpath);
    int r = sfs_link(path, newpath);
    LOG(" OK (%d)\n", r);
    if (r < 0) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        LOG(" OK\n", path);
        return 0;
    }
}

int fuse_sfs_open(const char* path, struct fuse_file_info* fi)
{
    LOG("fuse => open(%s, %o): ", path, fi->flags);
    sfs_file_t* f = sfs_open(path, fi->flags);
    if (f == NULL) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        fi->fh = (intptr_t)f;
        LOG(" OK\n", path);
        return 0;
    }
}

int fuse_sfs_read(const char* path, char* buf, size_t size, off_t offset,
    struct fuse_file_info* fi)
{
    LOG("fuse => read(%s, ..., %d, %d):", path, size, offset);
    int r = sfs_pread((sfs_file_t*)fi->fh, buf, size, offset);
    if (r < 0) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        LOG(" OK (%d bytes read)\n", r);
        return r;
    }
}

int fuse_sfs_write(const char* path, const char* buf, size_t size,
    off_t offset, struct fuse_file_info* fi)
{
    LOG("fuse => write(%s, ..., %d, %d): ", path, size, offset);
    int r = sfs_pwrite((sfs_file_t*)fi->fh, buf, size, offset);
    if (r < 0) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        LOG(" OK (%d bytes written)\n", r);
        return r;
    }
}

int fuse_sfs_close(const char* path, struct fuse_file_info* fi)
{
    LOG("fuse => close(%s, ...): ", path);
    sfs_file_t* f = (sfs_file_t*)fi->fh;
    LOG("fuse => <file:%p, inode:%d> ", f, f->inode);
    int r = sfs_close((sfs_file_t*)f);
    if (r < 0) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        LOG(" OK\n");
        return 0;
    }
}

int fuse_sfs_mkdir(const char* path, mode_t mode)
{
    LOG("fuse => mkdir(%s, ...): ", path);
    int r = sfs_mkdir(path);
    if (r < 0) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        LOG(" OK\n");
        return 0;
    }
}

int fuse_sfs_rmdir(const char* path)
{
    LOG("fuse => rmdir(%s, ...): ", path);
    int r = sfs_rmdir(path);
    if (r < 0) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        LOG(" OK\n");
        return 0;
    }
}

int fuse_sfs_opendir(const char* path, struct fuse_file_info* fi)
{
    LOG("fuse => opendir(%s, ...): ", path);
    sfs_dir_t* f = sfs_opendir(path);
    if (f == NULL) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        fi->fh = (intptr_t)f;
        LOG("fuse => <dir:%p, inode:%d> ", f, f->inode);
        LOG(" OK\n", path);
        return 0;
    }
}

int fuse_sfs_readdir(const char* path, void* buf, fuse_fill_dir_t filler,
    off_t offset, struct fuse_file_info* fi)
{
    LOG("fuse => readdir(%s, ..., %d, ...):\n", path, offset);

    int retstat = 0;
    struct dirent* de;

    sfs_dir_t* dp = (sfs_dir_t*)fi->fh;

    // Every directory contains at least two entries: . and ..  If my
    // first call to the system readdir() returns NULL I've got an
    // error; near as I can tell, that's the only condition under
    // which I can get an error from readdir()
    de = sfs_readdir(dp);
    if (de == 0) {
        LOG("fuse => PROBLEM!\n");
        return MINUS_ERRNO;
    }
    // This will copy the entire directory into the buffer.  The loop exits
    // when either the system readdir() returns NULL, or filler()
    // returns something non-zero.  The first case just means I've
    // read the whole directory; the second means the buffer is full.
    do {
        LOG("fuse =>    ... calling filler with name %s (inode %d)\n",
            de->d_name, de->d_ino);
        if (filler(buf, de->d_name, NULL, 0) != 0) {
            LOG("fuse =>     ERROR bb_readdir filler:  buffer full");
            return MINUS_ERRNO;
        }
    } while ((de = sfs_readdir(dp)) != NULL);

    LOG("fuse => readdir: OK\n");

    return retstat;
}

int fuse_sfs_closedir(const char* path, struct fuse_file_info* fi)
{
    LOG("fuse => closedir(%s, ...): ", path);
    sfs_dir_t* f = (sfs_dir_t*)fi->fh;
    if (f == NULL) {
        LOG("fuse => PROBLEM\n", path);
        return MINUS_ERRNO;
    } else {
        LOG("fuse => <dir:%p, inode:%d> ", f, f->inode);
        sfs_closedir((sfs_dir_t*)fi->fh);
        LOG(" OK\n");
        return 0;
    }
}

int fuse_sfs_truncate(const char* path, off_t offset)
{
    LOG("fuse => truncate(%s, %d):", path, offset);
    int r = sfs_truncate(path, offset);
    if (r < 0) {
        LOG("fuse => PROBLEM\n");
        return MINUS_ERRNO;
    }
    LOG(" OK\n");
    return 0;
}

int fuse_sfs_rename(const char* path, const char* newpath)
{
    LOG("fuse => rename(%s, %d):", path, newpath);
    int r = sfs_rename(path, newpath);
    if (r < 0) {
        LOG("fuse => PROBLEM\n");
        return MINUS_ERRNO;
    }
    LOG(" OK\n");
    return 0;
}

int fuse_sfs_symlink(const char* path, const char* link)
{
    LOG("fuse => symlink(%s, %s):", path, link);
    int r = sfs_symlink(path, link);
    if (r < 0) {
        LOG("fuse => PROBLEM\n");
        return MINUS_ERRNO;
    }
    LOG(" OK\n");
    return 0;
}

int fuse_sfs_readlink(const char* path, char* link, size_t size)
{
    LOG("fuse => readlink(%s, ..., %d):", path, size);
    int r = sfs_readlink(path, link, size);
    if (r < 0) {
        LOG("fuse => PROBLEM\n");
        return MINUS_ERRNO;
    }
    LOG(" OK\n");
    return 0;
}

/*
int fuse_sfs_access(const char *path, int mode) {
    LOG("fuse => access(%s): OK\n", path);
    return 0;
}

int fuse_sfs_chown(const char *path, uid_t owner, gid_t group) {
    LOG("fuse => chown(%s): OK\n", path);
    return 0;
}

int fuse_sfs_chmod(const char *path, mode_t mode) {
    LOG("fuse => chmod(%s): OK\n", path);
    return 0;
}
*/

//////////////////////////////////////
// recording the relevant system calls
struct fuse_operations sfs_oper = {

    .init = fuse_sfs_init,
    .destroy = fuse_sfs_destroy,

    .getattr = fuse_sfs_getattr,
    .statfs = fuse_sfs_statfs,
    .create = fuse_sfs_create,
    .unlink = fuse_sfs_unlink,
    .link = fuse_sfs_link,
    .open = fuse_sfs_open,
    .read = fuse_sfs_read,
    .write = fuse_sfs_write,
    .release = fuse_sfs_close,
    .mkdir = fuse_sfs_mkdir,
    .rmdir = fuse_sfs_rmdir,
    .opendir = fuse_sfs_opendir,
    .readdir = fuse_sfs_readdir,
    .releasedir = fuse_sfs_closedir,
    .truncate = fuse_sfs_truncate,
    .rename = fuse_sfs_rename,
    .symlink = fuse_sfs_symlink,
    .readlink = fuse_sfs_readlink,

    //    .access     = fuse_sfs_access,
    //    .chmod      = fuse_sfs_chmod,
    //    .chown      = fuse_sfs_chown,

    //    .ftruncate = fuse_sfs_ftruncate,
    //    .fgetattr = fuse_sfs_fgetattr,
    //    .mknod    = fuse_sfs_mknod,

    /*    // the remaining function aren't really necessary
        .fsync      = fuse_sfs_fsync,
        .fsyncdir = fuse_sfs_fsyncdir,

    #ifdef HAVE_POSIX_FALLOCATE
        .fallocate  = fuse_sfs_fallocate,
    #endif

    #ifdef HAVE_UTIMENSAT
        .utimens    = fuse_sfs_utimens,
    #endif

    #ifdef HAVE_SETXATTR
        .setxattr   = fuse_sfs_setxattr,
        .getxattr   = fuse_sfs_getxattr,
        .listxattr  = fuse_sfs_listxattr,
        .removexattr    = fuse_sfs_removexattr,
    #endif
    */
};

////////////////////////////////
int main(int argc, char* argv[])
{
    srand(time(NULL));
    init_log("sfs.log");

    sfs_randomize = 1;

    if ((getuid() == 0) || (geteuid() == 0)) {
        fprintf(stderr,
            "Running SFS as root opens unnacceptable security holes\n");
        return 1;
    }

    fprintf(stderr, "Fuse library version %d.%d\n", FUSE_MAJOR_VERSION,
        FUSE_MINOR_VERSION);

    if ((argc < 3) || (argv[argc - 2][0] == '-')
        || (argv[argc - 1][0] == '-')) {
        fprintf(stderr,
            "usage:  %s [FUSE and mount options] S_IFREG MOUNT_DIR\n",
            argv[0]);
        exit(EXIT_FAILURE);
    }

    int fuse_stat;
    struct sfs_state* sfs_data;

    sfs_data = malloc(sizeof(struct sfs_state));

    // Pull the SFS file out of the argument list and save it in my
    // internal data
    sfs_data->sfsfile = realpath(argv[argc - 2], NULL);
    argv[argc - 2] = argv[argc - 1];
    argv[argc - 1] = NULL;
    argc--;

    // turn over control to fuse
    fprintf(stderr, "calling fuse_main\n");
    fuse_stat = fuse_main(argc, argv, &sfs_oper, sfs_data);

    return fuse_stat;
}

// vim: foldmethod=syntax
