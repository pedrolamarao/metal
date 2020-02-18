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

QEMU `-bios` loading `qemu` image:

```sh
../gradlew qemuQemuMainDebug
```

QEMU `-kernel` loading `pc` image:

```sh
../gradlew qemuPcMainDebug
```

QEMU `-cdrom` loading `rescue` image:

```sh
../gradlew qemuRescueMainDebug
```

# architecture

_TODO_
