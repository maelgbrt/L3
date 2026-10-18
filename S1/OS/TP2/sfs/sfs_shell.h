#ifndef _SFS_SHELL_H_
#define _SFS_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sfs_log.h"
#include "sfs_low_level.h"
#include "sfs_parameters.h"
#include "sfs_volume.h"

// type for shell commands
struct command {
    char* cmd;               // name of the command
    int argc;                // expected number of arguments
    int (*fun)(char** args); // pointer to the command function
    char* description;       // description
};

// global variable containing all the available commands
struct command COMMAND[];

// call the appropriate command function depending on ``cmd``
void do_cmd(char* cmd, int argc, char** args);

// all the available command functions
int do_help(char** args);
int do_exit(char** args);
int do_info(char** args);

int do_mkfs(char** args);
int do_mount(char** args);
int do_umount(char** args);
int do_sync(char** args);

int do_randomize(char** args);

int do_block(char** args);
int do_bitmap(char** args);
int do_table(char** args);

int do_dump_data(char** args);
int do_dump_hexa(char** args);
int do_dump_entries(char** args);
int do_dump_addresses(char** args);
int do_show_inode(char** args);

int do_localize(char** args);
int do_create_file(char** args);
int do_truncate(char** args);
int do_write(char** args);
int do_read(char** args);

int do_add_entry(char** args);
int do_remove_entry(char** args);

int do_writelink(char** args);
int do_readlink(char** args);

int do_unlink(char** args);
int do_link(char** args);

int do_test(char** args);

#endif // _SFS_SHELL_H_
