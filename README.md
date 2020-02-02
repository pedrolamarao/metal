Date: 2020-01-31

# summary

Welcome to the Aasgard project!

Aasgard is a collection of components for programming the bare metal.

It is designed for integration with state of the art tools.

Try: `./gradlew build`

# index

0. summary
1. assemble
2. check
3. use
4. architecture
5. references

# assemble

These are the required tools.

- GNU `binutils` version 2.33.1 target (see below)
- GNU `gcc` version 9.2 target (see below)
- OpenJDK version 11 host

OpenJDK is required to run Gradle.
We suggest AdoptOpenJDK builds.

Currently, the only useful target for Aasgard is `i686-pc-elf`.
Meaningful support for `x86_64-pc-elf` is coming.

The following instructions for building the required tools works with MSYS2.

## binutils 2.33.1

```sh
../binutils-2.33.1/configure --target=i686-pc-elf --with-sysroot --disable-nls --prefix=/opt/gnu-i686-pc-elf
make
make -j2 install
```

## gcc 9.2

*TODO*: consider the "red zone" problem for libgcc for x86_64.

```sh
PATH=/opt/gnu-i686-pc-elf:$PATH ../gcc-9.2.0/configure --target=i686-pc-elf --enable-languages=c,c++ --without-headers --disable-nls --prefix=/opt/gnu-i686-pc-elf
make -j2 all-gcc all-target-libgcc
make -j2 install-gcc install-target-libgcc
```

## grub 2.04

```sh
.../grub-2.04/configure --prefix=/opt/gnu-i686-pc-elf --disable-werror
make -j2
make install
```

## issues

- Gradle: [Assembler language support](https://github.com/gradle/gradle-native/issues/172)
- Gradle: [Built in support for mingw multi-architecture compilation](https://github.com/gradle/gradle-native/issues/969) 

# check

*TODO*: apply some technique for pure testing: running test programs in the host system with googletest. Requires multi tool support from Gradle.

*TODO*: apply some technique for emulator testing: running test programs in an emulator, somehow verifying post conditions. Requires emulator support.

*TODO*: apply some technique for integration testing: runnin test programs in actual metal, somehow verifying post conditions. Epic!

# use

## targets

These are the currently supported targets:

- `i686-pc-elf`

## gradle

Aasgard is currently set up for Gradle multi-project builds.

Gradle 6.1 is capable of full dependency management for Aasgard components.

To reuse one of the components, you must add a dependency on it, like below:

```
dependencies {
    implementation project(':multiboot2')
}
```

# architecture

The collection includes the following components:

* [acpi](acpi/README.md)
* [multiboot2](multiboot2/README.md)
* [pc](pc/README.md)
* [x86](x86/README.md)

# references

_TODO_
