#ifndef _SFS_LOG_H_
#define _SFS_LOG_H_

#include <stdarg.h>
#include <stdio.h>

#include "sfs_parameters.h"
#include "sfs_volume.h"

void init_log(const char* path);
void LOG(const char* format, ...);
void LOG_inode(int nb);

#endif // _SFS_LOG_H_
