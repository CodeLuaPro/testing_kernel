#!/bin/sh
int_re='^[0-9]+$'

num_procs=1

if ! [ $# -eq 0 ] && echo "$1" | grep -Eq "$int_re" ; then
  $num_procs = $1
fi

set -e
. ./headers.sh

for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install -j $num_procs)
done
