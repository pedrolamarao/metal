# Aasgard &mdash; boot on i686-pc-elf with a Multiboot2 loader

This program demonstrates booting a program on i686-pc-elf with a Multiboot2 loader.

## Build

To build this program from the root directory:

```sh
SRC="x86/gdt.S x86/idt.S xxx--multiboot2-x86--minimal/start.S xxx--multiboot2-x86--minimal/main.cpp" \
BIN="xxx--multiboot2-x86--minimal.bin/aasgard" \
CPPFLAGS="-nostdinc -Ic++-x86 -I." \
CXXFLAGS="-std=c++14 -ffreestanding -O0 -g" \
LDFLAGS="-m32 -nostdlib -Ttext 0x1000" \
i686-pc-elf-g++ ${CPPFLAGS} ${CXXFLAGS} ${LDFLAGS} -o ${BIN} ${SRC}
```

We link the `.text` section at 0x1000 to ease the burden on emulators &mdash; a small amount of RAM will be enough.

## Structure

This program must satisfy Multiboot2's requirements for a boot request.

1. The Multiboot2 header must be present in the initial 32kb of the program image.
2. Instructions must be present for the loader to locate the program's entry point.

Requirement (1) is easily satisfied in such a small example, since the program image itself is smaller than 32kb.

The Multiboot2 header is computed in C++ using the Aasgard's multiboot2 library. The object is defined in namespace scope with static storage duration in [`main.cpp`](main.cpp). It is constant initialized by a `constexpr` constructor. Therefore, the object shall be placed value initialized, not zero initialized, in the program image.

Requirement (2) is satisfied by the ELF image. The default ELF entry point, `_start`, is provided. The Multiboot2 loader shall parse the ELF image to locate the entry point.

All conditions fulfilled, the Multiboot2 loader shall transfer control to the program's entry point. Multiboot2's "calling convention" is not supported by C++ compilers. Therefore, `_start` is defined in assemby in [`start.S`](start.S). This routine shall set up a small stack, reset EFLAGS and make a `[[gnu::fastcall]]` with Multiboot2's arguments to `main`, defined in [`main.cpp`](main.cpp).