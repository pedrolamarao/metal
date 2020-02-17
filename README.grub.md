Date: 2020-02-08

# summary

This is a collection of tips for using GRUB 2.

They assume you have the necessary toolset as per [README.md](README.md).

# index

0. summary
1. configuration
2. `grub-mkstandalone`
3. `grub-mkrescue`

# `grub-mkstandalone`

`grub-mkstandalone` generates a standalone image.

## `i386-qemu`

GRUB `i386-qemu` images are meant to replace the PC BIOS.

The following should start GRUB normal shell.

```sh
grub-mkstandalone -O i386-qemu -o image
qemu-system-i386 -bios image
```

> `grub-mkstandalone` by default includes all modules in the image, but, doesn't load any.

## `i386-pc`

GRUB `i386-pc` images are meant to be run by the PC BIOS.

There are size limitations on this platform, therefore, it is necessary to trim down the image 

The following should start GRUB rescue shell.

```sh
grub-mkstandalone -O i386-pc -o image --install-modules= --locales= --font= --themes=
qemu-system-i386 -kernel image
```

> The instruction above includes no modules, no locales, no fonts and no themes.

# `grub-mkrescue`

`grub-mkrescue` generates a rescue image.

GRUB rescue images are meant to boot from a CD-ROM drive.

The following should start GRUB normal shell.

```sh
grub-mkrescue -o image
qemu-system-i386 -cdrom image
```

# modules

`at_keyboard` supports input via PC AT keyboard.

`help` contains the help command for `normal`.

`normal` contains the default GRUB shell.

# references

- [GRUB Manual](https://www.gnu.org/software/grub/manual/grub/grub.html)
