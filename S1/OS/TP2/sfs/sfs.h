#ifndef _SFS_H_
#define _SFS_H_

// type synonym for "raw" bytes
typedef unsigned char byte;

// macro to get ``i``-th bit of byte ``c``
#define BIT(i, c) (((c) >> i) & 1)

#endif // _SFS_H_
