#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/testos.kernel isodir/boot/testos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "testos" {
	multiboot /boot/testos.kernel
}
EOF
grub-mkrescue -o testos.iso isodir
