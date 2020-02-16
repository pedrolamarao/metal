Date: 2020-02-01

# summary

This program demonstrates doing interrupt driven I/O on i686-pc-elf soon after loading.

# build

Build development artifacts including GRUB images:

```sh
./gradlew assemble
```

We link the `.text` section at 0x1000 to ease the burden on emulators &mdash; a small amount of RAM will be enough.

# launch

QEMU with `pc` image:

```sh
qemu-system-i386 -kernel build/grub/mainDebugLinux/pc/image
```

QEMU with `qemu` image:

```sh
qemu-system-i386 -kernel build/grub/mainDebugLinux/qemu/image
```

QEMU with `rescue` image:

```sh
qemu-system-i386 -cdrom build/grub/mainDebugLinux/rescue/image
```

# architecture

_TODO_
