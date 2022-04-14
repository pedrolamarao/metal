Date: 2022-04-14

# tools

The build driver requires a JDK 17 in either `JAVA_HOME` or `PATH`.

Generally, tools will be found in the system `PATH`.

Custom paths may be configured in `tools.properties` in the root project folder.
Available configuration is listed in `tools.properties.default`.

For assembling main components, LLVM 13 is sufficient.

For assembling Multiboot2 system test programs, GNU GRUB 2 is required.

For running system test programs, QEMU 6 is required.

## ubuntu

Ubuntu 21.10 has been verified to work.

Quick start:

```shell
sudo apt install \
 clang \
 grub2 \
 libstdc++-11-dev \
 lld \
 llvm \
 openjdk-17-jdk-headless \
 qemu-system
```

## windows

Windows 10 and 11 have been verified to work.

Quick start:

1. Install any JDK 17
2. Set `JAVA_HOME` to JDK 17
3. Install LLVM 13 for Windows from https://github.com/llvm/llvm-project/releases
4. Install GNU GRUB 2.06 for Windows from https://ftp.gnu.org/gnu/grub/
5. Install QEMU for Windows from https://qemu.weilnetz.de/w64/
6. Edit `tools.properties` with appropriate values