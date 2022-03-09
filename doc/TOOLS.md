Date: 2021-10-12

# tools

The build driver requires a JDK 11 in either `JAVA_HOME` or `PATH`.

Generally, tools will be found in the system `PATH`.

Custom paths may be configured in `tools.properties` in the root project folder.
Available configuration is listed in `tools.properties.default`.

For assembling main components, LLVM is sufficient.

For assembling Multiboot2 system test programs, GNU GRUB is required.

For running system test programs, QEMU and GNU GDB are required.

## ubuntu

Ubuntu 21.04 has been verified to work.

Quick start:

```shell
sudo apt install \
 gdb \
 grub2 \
 libstdc++-11-dev \
 openjdk-11-jdk-headless \
 qemu-system

sudo wget -O - https://github.com/llvm/llvm-project/releases/download/llvmorg-13.0.0-rc2/clang+llvm-13.0.0-rc2-x86_64-linux-gnu-ubuntu-21.04.tar.xz | sudo tar -xJf - -C /opt
```

Edit `tools.properties` with appropriate values for LLVM.
Alternatively, add LLVM to `PATH`.

## windows

Windows 10 and 11 have been verified to work.

Quick start:

0. Install any JDK 11 -- ensure it is accessible via `JAVA_HOME` or `PATH`
1. Install LLVM [13, 14] for Windows from https://github.com/llvm/llvm-project/releases
2. Install GNU GRUB 2.06 for Windows from https://ftp.gnu.org/gnu/grub/
3. Install QEMU [6.1, 6.2] for Windows from https://qemu.weilnetz.de/w64/
4. Install MSYS2 from https://www.msys2.org/
5. With MSYS2, install package `mingw-w64-x86_64-gdb`
7. Edit `tools.properties` with appropriate values