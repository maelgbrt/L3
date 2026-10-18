#include "sfs_shell.h"

////////////////////////////////////////////////////////
// global variable to randomize inodes and blocks search
extern int sfs_randomize;

// global variale for currently mounted filesystem
char SFS_CURRENT[128] = "";

/////////////////////
// available commands
struct command COMMAND[] = {
    { "help", 0, do_help, "                        display help message" },
    { "?", 0, do_help, "                           display help message" },
    { "exit", 0, do_exit, "                        exit from the SFS shell" },
    { "info", 0, do_info,
        "                        show the parameters of SFS" },

    { "mkfs", 1, do_mkfs,
        " FILE                   create (and mount) a new SFS filesystem "
        "inside ``FILE``" },
    { "mount", 1, do_mount,
        " FILE                  mount SFS filesystem from Unix file "
        "``FILE``" },
    { "umount", 0, do_umount,
        "                      unmount current SFS filesystem" },
    { "sync", 0, do_sync,
        "                        synchronise current SFS filesystem on "
        "disk" },

    { "randomize", 1, do_randomize,
        " STATE             set randomization (STATE can be 0, 1 or ?)" },

    { "block", 2, do_block,
        " BLOCK STATE           set / display current state of block (STATE "
        "can be 0, 1 or ?)" },
    { "bitmap", 0, do_bitmap,
        "                      display current bitmap for free blocks" },
    { "B", 0, do_bitmap,
        "                           display current bitmap for free blocks" },

    { "show_inode", 1, do_show_inode,
        " INODE            show information about inode" },
    { "I", 1, do_show_inode,
        " INODE                     show information about inode" },
    { "inode_table", 0, do_table,
        "                 display current table for free inodes" },
    { "T", 0, do_table,
        "                           display current table for free inodes" },

    { "dump_hexa", 1, do_dump_hexa,
        " BLOCK             dump the bytes (hexadecimal) from block" },
    { "H", 1, do_dump_hexa,
        " BLOCK                     dump the bytes (hexadecimal) from "
        "block" },
    { "dump_data", 1, do_dump_data,
        " BLOCK             dump the bytes (ASCII) from block" },
    { "D", 1, do_dump_data,
        " BLOCK                     dump the bytes (ASCII) from block" },
    { "dump_entries", 1, do_dump_entries,
        " BLOCK          dump the directory entries from block" },
    { "E", 1, do_dump_entries,
        " BLOCK                     dump the directory entries from block" },
    { "dump_addresses", 1, do_dump_addresses,
        " BLOCK        dump the addresses (block numbers) from block" },
    { "A", 1, do_dump_addresses,
        " BLOCK                     dump the addresses (block numbers) from "
        "block" },

    { "create_file", 0, do_create_file,
        "                 create empty file" },
    { "truncate", 2, do_truncate,
        " INODE SIZE         truncate inode to given size" },
    { "read", 3, do_read,
        " INODE N OFFSET         read ``N`` characters from inode at given "
        "offset" },
    { "write", 3, do_write,
        " INODE STR OFFSET      write ``STR`` inside inode at given offset" },

    { "localize", 1, do_localize,
        " PATH               get inode number from path" },

    { "add_entry", 3, do_add_entry,
        " DIR_INODE NAME INODE  add an entry with given name and inode in "
        "directory" },
    { "remove_entry", 2, do_remove_entry,
        " DIR_INODE INODE    remove entry with given inode from directory" },

    { "writelink", 1, do_writelink,
        " TARGET            create a symbolic link in new inode" },
    { "readlink", 1, do_readlink,
        " INODE              get the target of a symbolic link" },

    { "link", 3, do_link,
        " DIR_INODE NAME INODE   create a physical link in given directory" },
    { "unlink", 3, do_unlink,
        " DIR_INODE INODE NAME remove a pair inode,name from a directory" },

    { "test", -1, do_test, "...                     run the test function" },

    { NULL, 0, NULL, NULL },
};

/////////////////////////////////////////////////////////////
// call the appropriate command function depending on ``cmd``
void do_cmd(char* cmd, int argc, char** args)
{
    struct command* CMD = COMMAND;
    while ((CMD->cmd != NULL) && (0 != strcmp(CMD->cmd, cmd))) {
        CMD += 1;
    }

    if (CMD->cmd == NULL) {
        printf("*** ERROR: command '%s' not found\n", cmd);
        return;
    }

    if (CMD->argc >= 0 && argc != CMD->argc) {
        printf("*** ERROR: command '%s' received %d arguments but expects %d "
               "argument(s)\n",
            cmd, argc, CMD->argc);
        return;
    }

    if ((*CMD->fun)(args) < 0) {
        printf("*** ERROR during command '%s'\n", cmd);
    }
}

////////////////////
// command functions

int do_help(char** args)
{
    struct command* CMD = COMMAND;
    while (CMD->cmd) {
        printf("  %s %s\n", CMD->cmd, CMD->description);
        CMD += 1;
    }
    return 0;
}

int do_exit(char** args)
{
    if (strlen(SFS_CURRENT) != 0) {
        do_umount(NULL);
    }
    exit(0);
}

int do_info(char** args)
{
    printf("total size of filesystem: %d bytes\n", TOTAL_SIZE);

    printf("blocks of %d bytes\n", BLOCK_SIZE);
    printf("bitmap segment: %d bytes (%d blocks)\n", BITMAP_SIZE_BYTES,
        BITMAP_SIZE);
    printf("%d blocks are unused\n", sfs_count_free_blocks());

    printf("single inode of %zu bytes\n", sizeof(struct inode));
    printf("inode table: %d blocks (%d bytes), containing %d inodes\n",
        INODE_TABLE_SIZE, INODE_TABLE_SIZE * BLOCK_SIZE, NB_INODES);
    printf("%d inodes are unused\n", sfs_count_free_inodes());

    printf("data segment: %d blocks (%d bytes)\n", DATA_SIZE,
        DATA_SIZE * BLOCK_SIZE);

    /* int max_size = BLOCK_SIZE*NB_DIRECT_BLOCKS; */
    /* printf("maximal size for files: %d bytes, ie %d kibibytes\n", max_size,
     * max_size/1024); */

    int max_size
        = (int)(BLOCK_SIZE * (NB_DIRECT_BLOCKS + BLOCK_SIZE / sizeof(int)));
    printf("maximal size for files: %d bytes, ie %d kibibytes\n", max_size,
        max_size / 1024);

    return 0;
}

int do_mkfs(char** args)
{
    if (strlen(SFS_CURRENT) != 0) {
        do_umount(NULL);
    }
    if (sfs_mkfs(args[0]) < 0) {
        return -1;
    } else {
        return do_mount(args);
    }
}

int do_mount(char** args)
{
    if (strlen(SFS_CURRENT) != 0) {
        printf(">>> unmounting previous filesystem (%s)...\n", SFS_CURRENT);
        if (-1 == sfs_umount()) {
            printf("*** ERROR during command umount...\n");
            return -1;
        } else {
            strcpy(SFS_CURRENT, "");
            return 0;
        }
    }
    if (sfs_mount(args[0]) < 0) {
        strcpy(SFS_CURRENT, "");
        return -1;
    } else {
        strncpy(SFS_CURRENT, args[0], 128);
        SFS_CURRENT[127] = 0;
        return 0;
    }
}

int do_umount(char** args)
{
    if (strlen(SFS_CURRENT) != 0) {
        if (sfs_umount() < 0) {
            return -1;
        } else {
            strcpy(SFS_CURRENT, "");
            return 0;
        }
    } else {
        printf("*** ERROR: no filesystem mounted...\n");
        return -1;
    }
}

int do_sync(char** args)
{
    if (strlen(SFS_CURRENT) != 0) {
        if (-1 == sfs_sync()) {
            return -1;
        } else {
            return 0;
        }
    } else {
        printf("*** ERROR: no filesystem mounted...\n");
        return 0;
    }
}

int do_bitmap(char** args)
{
    for (int k = 0; k < DATA_SIZE; k++) {
        if (k % 64 == 0)
            printf("\n0x%08x: ", k);
        printf("%d", sfs_block_in_use(k));
    }
    printf("\n");
    return 0;
}

int do_table(char** args)
{
    inode_t* nd;
    for (int i = 0; i < NB_INODES; i++) {
        if (i % 32 == 0)
            printf("\n0x%08x: ", i);
        nd = sfs_get_inode(i);
        printf("%d", nd->nlinks);
    }
    printf("\n");
    return 0;
}

int do_block(char** args)
{
    int nb = atoi(args[0]);
    char* state = args[1];
    if (0 == strcmp(state, "?")) {
        printf(">>> block %d: %d\n", nb, sfs_block_in_use(nb));
    } else if (0 == strcmp(state, "0")) {
        sfs_free_block(nb);
        printf(">>> block %d is now free\n", nb);
    } else if (0 == strcmp(state, "1")) {
        sfs_use_block(nb);
        printf(">>> block %d is now used\n", nb);
    } else {
        printf("*** ERROR: invalid argument, use 0, 1 or ?\n");
        return -1;
    }
    return 0;
}

int do_free_block(char** args)
{
    printf(">>> next free block at position %d\n", sfs_find_free_block());
    return 0;
}

int do_free_inode(char** args)
{
    printf(">>> next free inode is %d\n", sfs_find_free_inode());
    return 0;
}

int do_dump_data(char** args)
{
    int nb = atoi(args[0]);
    block_t* b = sfs_get_block(nb);
    byte c;
    int i;
    for (i = 0; i < BLOCK_SIZE; i++) {
        if (i % 64 == 0)
            printf("0x%04x: ", i);
        c = ((byte*)b)[i];
        if (0x20 <= c && c <= 0x7e) {
            printf("%c", c);
        } else if (c == 0) {
            printf(".");
        } else {
            printf("?");
        }
        if ((i + 1) % 64 == 0)
            printf("\n");
    }
    if (i % 64 != 0)
        printf("\n");
    return 0;
}

int do_dump_hexa(char** args)
{
    int nb = atoi(args[0]);
    block_t* b = sfs_get_block(nb);
    byte c;
    int i;
    for (i = 0; i < BLOCK_SIZE; i++) {
        if (i % 16 == 0)
            printf("0x%06x: ", i);
        c = ((byte*)b)[i];
        printf("%02x ", c);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    if (i % 16 != 0)
        printf("\n");
    return 0;
}

int do_dump_addresses(char** args)
{
    int nb = atoi(args[0]);
    block_t* b = sfs_get_block(nb);
    int p;
    int i;
    for (i = 0; i < (int)(BLOCK_SIZE / sizeof(int)); i++) {
        if (i % 10 == 0)
            printf("%06d: ", i);
        p = ((int*)b)[i];
        printf("%9d ", p);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
    if (i % 10 != 0)
        printf("\n");
    return 0;
}

int do_dump_entries(char** args)
{
    int nb = atoi(args[0]);
    dir_entry_t* entries = (dir_entry_t*)sfs_get_block(nb);
    for (int i = 0; i < ENTRIES_PER_BLOCK; i++) {
        printf("%06d => %s\n", entries[i].inode_nb, entries[i].name);
    }
    return 0;
}

int do_show_inode(char** args)
{
    int nb = atoi(args[0]);
    fprint_inode(stdout, nb);
    return 0;
}

int do_create_file(char** args)
{
    int nb = sfs_find_free_inode();
    if (nb < 0) {
        return -1;
    }
    inode_t* nd = sfs_get_inode(nb);
    nd->type = S_IFREG;
    nd->size = 0;
    nd->nlinks = 1;
    printf(">>> using inode %d for an empty regular file\n", nb);
    return 0;
}

int do_localize(char** args)
{
    char* path = args[0];
    int nb = sfs_localize(path);
    if (nb < 0) {
        return -1;
    }
    printf(">>> path '%s' is at inode %d\n", path, nb);
    return 0;
}

int do_write(char** args)
{
    int nb = atoi(args[0]);
    char* s = args[1];
    int t = strlen(s);
    int offset = atoi(args[2]);
    int r = sfs_write_to_block(
        nb, offset / BLOCK_SIZE, offset % BLOCK_SIZE, (byte*)s, t);
    if (r < 0) {
        return -1;
    }
    printf(">>> %d bytes written to inode %d\n", r, nb);
    return 0;
}

int do_read(char** args)
{
    //{"read_string", 3, do_read_string, " NB M OFFSET     read ``M``
    // characters from inode ``NB``"},
    int nb = atoi(args[0]);
    int m = atoi(args[1]);
    int offset = atoi(args[2]);
    char* s = malloc(m + 1);
    int nbyte = sfs_read_from_block(
        nb, offset / BLOCK_SIZE, offset % BLOCK_SIZE, (byte*)s, m);
    if (nbyte < 0) {
        return -1;
    }
    printf("%.*s", nbyte, s);
    free(s);
    printf("\n");
    return 0;
}

int do_randomize(char** args)
{
    if (0 == strcmp(args[0], "0")) {
        sfs_randomize = 0;
    } else if (0 == strcmp(args[0], "1")) {
        sfs_randomize = 1;
    } else if (0 == strcmp(args[0], "?")) {
        printf(">>> randomize = %s\n", sfs_randomize ? "1" : "0");
    } else {
        printf("*** ERROR: invalid argument, use 0, 1 or ?\n");
        return -1;
    }
    return 0;
}

int do_add_entry(char** args)
{
    int dir_nb = atoi(args[0]);
    char* name = args[1];
    int nb = atoi(args[2]);
    return sfs_add_entry(dir_nb, name, nb);
}

int do_remove_entry(char** args)
{
    int dir_nb = atoi(args[0]);
    return sfs_remove_entry(dir_nb, args[1]);
}

int do_truncate(char** args)
{
    int nb = atoi(args[0]);
    int size = atoi(args[1]);
    int s = sfs_truncate_inode(nb, size);
    if (s < 0) {
        return -1;
    }
    printf(">>> inode truncated to size %d\n", s);
    return 0;
}

int do_writelink(char** args)
{
    char* target = args[0];
    int nb = sfs_writelink_inode(target);
    if (nb < 0) {
        return -1;
    }
    printf(">>> symbolic link created at inode %d\n", nb);
    return 0;
}

int do_readlink(char** args)
{
    int nb = atoi(args[0]);
    char target[SFS_PATH_MAX];
    int s = sfs_readlink_inode(nb, target, SFS_PATH_MAX);
    if (s < 0) {
        return -1;
    }
    printf(">>> target of symbolic link is '%s'", target);
    return 0;
}

int do_link(char** args)
{
    int dir_nb = atoi(args[0]);
    char* name = args[1];
    int nb = atoi(args[2]);
    return sfs_link_inode(dir_nb, nb, name);
}

int do_unlink(char** args)
{
    int dir_nb = atoi(args[0]);
    int nb = atoi(args[1]);
    char* name = args[2];
    return sfs_unlink_inode(dir_nb, name, nb);
}

int do_test(char** args)
{
    int nb = atoi(args[0]);
    int size = atoi(args[1]);
    char* name = args[2];
    printf("running test function with nb=%d, size=%d and name='%s'\n", nb,
        size, name);
    return 0;
}

////////////////
// main function
int main(int argc, char** args)
{
    srand(time(NULL));
    init_log("sfs.log");

    sfs_randomize = 1;

    if (argc > 1) {
        strncpy(SFS_CURRENT, args[1], 128);
        SFS_CURRENT[127] = 0;

        if (-1 == sfs_mount(SFS_CURRENT)) {
            printf("*** ERROR while mounting filesystem\n");
            strcpy(SFS_CURRENT, "");
        }
    }

    char line[256];
    char* tmp_line;
    char* tokens[32];
    int nb_tokens;

    while (1) {
        printf("(%s)%% ", strlen(SFS_CURRENT) == 0 ? "NULL" : SFS_CURRENT);
        fflush(stdout);
        if (NULL == fgets(line, 255, stdin)) {
            if (strlen(SFS_CURRENT) != 0) {
                do_umount(NULL);
            }
            return 0;
        }

        nb_tokens = 0;
        tmp_line = line;
        while ((tokens[nb_tokens] = strtok(tmp_line, " \n\t"))
            && nb_tokens < 32) {
            tmp_line = NULL;
            nb_tokens++;
        }
        if (nb_tokens == 0) {
            continue;
        }

        do_cmd(tokens[0], nb_tokens - 1, tokens + 1);
    }
    return 0;
}

// vim: foldmethod=syntax
