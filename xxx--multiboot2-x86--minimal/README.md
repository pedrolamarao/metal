Date: 2020-02-01

# summary

This program demonstrates booting a program with a Multiboot2 loader.

# build

Build development artifacts including GRUB images:

```sh
./gradlew assemble
```

We link the `.text` section at `0x1000` to ease the burden on emulators — a small amount of RAM will be enough.

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

This program must satisfy Multiboot2's requirements for a boot request.

1. The Multiboot2 header must be present in the initial 32kb of the program image.
2. Instructions must be present for the loader to locate the program's entry point.

Requirement (1) is easily satisfied in such a small example, since the program image itself is smaller than 32kb.

The Multiboot2 header is computed in C++ using the `multiboot2` component. The object is defined in namespace scope with static storage duration in [`main.cpp`](main.cpp). It is constant initialized by a `constexpr` constructor. Therefore, the object shall be placed value initialized, not default initialized, in the program image.

Requirement (2) is satisfied by the ELF image. The default ELF entry point, `_start`, is provided. The Multiboot2 loader shall parse the ELF image to locate the entry point.

All conditions fulfilled, the Multiboot2 loader shall transfer control to the program's entry point. Multiboot2's "calling convention" is not supported by C++ compilers. Therefore, `_start` is defined in assemby in [`start.S`](start.S). This routine shall set up a small stack, reset EFLAGS and make a `[[gnu::fastcall]]` with Multiboot2's arguments to `main`, defined in [`main.cpp`](main.cpp).
