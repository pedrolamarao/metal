Date: 2023-09-16

# tools

The build driver requires a JDK 17 in either `JAVA_HOME` or `PATH`.

Generally, tools will be found in the system `PATH`.

Custom paths may be configured in `tools.properties` in the root project folder.
Available configuration is listed in `tools.properties.default`.

For assembling main components, LLVM 16 is sufficient.

For assembling Multiboot2 system test programs, GNU GRUB 2 is required.

For running system test programs, QEMU 6.0.0 is required.

## windows

Windows 10 and 11 have been verified to work.

Quick start:

1. Install any JDK 17
2. Set `JAVA_HOME` to JDK 17
3. Install Visual Studio Build Tools 2022
4. Install LLVM 16 for Windows from https://github.com/llvm/llvm-project/releases
5. Install GNU GRUB 2.06 for Windows from https://ftp.gnu.org/gnu/grub/
6. Install QEMU for Windows (qemu-w64-setup-20210505) from https://qemu.weilnetz.de/w64/
7. Edit `tools.properties` with appropriate values