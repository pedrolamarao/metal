# Aasgard &mdash; interrupt driven I/O on i686-pc-elf

This program demonstrates doing interrupt driven I/O on i686-pc-elf soon after loading.

## Build

To build this program from the root directory:

```sh
SRC="x86/gdt.S x86/idt.S xxx--multiboot2-x86--io/start.S xxx--multiboot2-x86--irq/main.cpp" \
BIN="xxx--multiboot2-x86--io.bin/aasgard" \
CPPFLAGS="-nostdinc -Ic++-x86 -I." \
CXXFLAGS="-std=c++14 -ffreestanding -O0 -g" \
LDFLAGS="-nostdlib -Ttext 0x1000" \
i686-pc-elf-g++ ${CPPFLAGS} ${CXXFLAGS} ${LDFLAGS} -o ${BIN} ${SRC}
```

We link the `.text` section at 0x1000 to ease the burden on emulators &mdash; a small amount of RAM will be enough.

## Structure

TODO