#!/bin/bash

cp -f "bin-multiboot2-x86/aasgard" image/iso/boot/kernel

rm image/iso.img

grub2-mkrescue -o image/iso.img image/iso

/usr/bin/qemu-system-i386 -m 512 -cdrom image/iso.img -no-kvm -s