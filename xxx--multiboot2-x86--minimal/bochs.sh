#!/bin/bash

SRC=xxx--multiboot2-x86--minimal
BIN=xxx--multiboot2-x86--minimal.bin

cp -f ${BIN}/aasgard image/iso/boot/kernel

rm image/iso.img

grub2-mkrescue -o image/iso.img image/iso

/opt/bochs/bin/bochs -f ${SRC}/bochsrc -q >/dev/null 2>&1 &

gdb -x ${SRC}/gdbinit