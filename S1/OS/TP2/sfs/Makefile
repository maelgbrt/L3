CC := gcc
# CC := clang

CFLAGS := --std=gnu99 -D_FILE_OFFSET_BITS=64 -Wall -Wextra -pedantic -Werror -Wno-unused-parameter

C_FILES := sfs_log.c sfs_volume.c sfs_low_level.c sfs_posix.c
H_FILES := sfs_parameters.h $(C_FILES:.c=.h)
O_FILES := $(C_FILES:.c=.o)


all: sfs_shell sfs_fuse

gcc: CC = gcc
gcc: clean all

clang: CC = clang
clang: clean all

%.o: %.c $(H_FILES)
	$(CC) $(CFLAGS) -c $<


sfs_shell: $(O_FILES) sfs_shell.o
	$(CC) -o sfs_shell $(O_FILES) sfs_shell.o

sfs_fuse: $(O_FILES) sfs_fuse.o
	$(CC) -o sfs_fuse $(O_FILES) sfs_fuse.o -lfuse

clean:
	rm -f *.o a.out *.log

veryclean: clean
	fusermount -u TEST ; true
	rm -rf sfs_shell sfs_fuse TEST TEST.sfs *~


remove_code: sfs_low_level.c
	sed -e '/\/\/ REMOVE/d' -e 's/\/\/ ADD //g' sfs_low_level.c > /tmp/sfs_low_level.c


.PHONY: veryclean clean all gcc clang remove_code
