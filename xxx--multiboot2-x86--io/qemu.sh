#!/bin/bash

SRC=xxx--multiboot2-x86--io
BIN=xxx--multiboot2-x86--io.bin

cp -f ${BIN}/aasgard image/iso/boot/kernel

rm image/iso.img

grub2-mkrescue -o image/iso.img image/iso

/usr/bin/qemu-system-i386 -cdrom image/iso.img -s -S &

gdb -x ${SRC}/gdbinit