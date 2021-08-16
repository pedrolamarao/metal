Date: 2021-08-16

# tools

The build driver requires a JDK 11 in either `JAVA_HOME` or `PATH`.

Build tools must be configured in file `tools.properties` in the root project folder.

Configuration properties are listed in `tools.properties.default`.

For assembling main components, LLVM is sufficient.

For assembling Multiboot2 system test programs, GNU GRUB is required.

For assembling UEFI system test programs, GNU mtools is required.

For running system test programs, QEMU and GNU GDB are required.

## windows

Quick start:

0. Install any JDK 11 -- ensure it is accessible via JAVA_HOME or PATH
1. Install LLVM 13 for Windows from https://github.com/llvm/llvm-project/releases
2. Install GNU GRUB 2.06 for Windows from https://ftp.gnu.org/gnu/grub/
3. Install QEMU 6.1 for Windows from https://qemu.weilnetz.de/w64/
4. Install MSYS2 from https://www.msys2.org/
5. With MSYS2, install package `mingw-w64-x86_64-gdb`
6. With MSYS2 ming64 shell, build and install GNU mtools 4.0.33 from https://www.gnu.org/software/mtools/
7. Create `tools.properties` from `tools.properties.default` with appropriate values

The LLVM project provides builds for Windows.
Version 13 has been verified to work.

The GNU GRUB project provides builds for Windows.
Version 2.06 has been verified to work.

The QEMU project provides builds for Windows.
Version 6.1 has been verified to work.

You may use GDB from MSYS2 with advantage.
Version 10.2 from MSYS2 mingw64 has verified to work.

GNU mtools must be built from source.
Version 4.0.33 built from MSYS2 minw64 shell has verified to work.
