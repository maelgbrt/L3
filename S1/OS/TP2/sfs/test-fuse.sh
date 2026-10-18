#!/bin/sh

## small script to compile SFS, create SFS filesystem and mount it in TEST
## directory via libfuse

DIR=$(pwd)

if [ -z "$1" ]
then
    VOLUME="TEST.sfs"
else
    VOLUME="$1"
fi

SFS_DIR="TEST"

fusermount -u $SFS_DIR

make || exit

[ -d ./$SFS_DIR ] || mkdir $SFS_DIR
[ -f "./$VOLUME" ] || echo "mkfs $VOLUME" | ./sfs_shell

./sfs_fuse -o use_ino "$VOLUME" "$SFS_DIR" && cd "$SFS_DIR" && LANG=C rlwrap sh

cd "$DIR"
echo "unmount $SFS_DIR from $(pwd)"

fusermount -u $SFS_DIR
