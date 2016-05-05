#!/bin/bash

SRC=xxx--multiboot2-x86--minimal
BIN=xxx--multiboot2-x86--minimal.bin

cp -f ${BIN}/aasgard image/iso/boot/kernel

rm image/iso.img

grub2-mkrescue -o image/iso.img image/iso

/usr/bin/qemu-system-i386 -m 512 -cdrom image/iso.img -s -S &

gdb -x ${SRC}/gdbinit