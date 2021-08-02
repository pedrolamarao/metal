Date: 2021-08-02

# summary

Welcome to the Psys project!

Psys is a collection of components for programming the bare metal.

It is designed for integration with state-of-the-art tools and techniques.

# index

0. summary
1. prepare
2. assemble
3. check
4. use
5. architecture
6. references

# prepare

Psys is built by an LLVM based toolset.
These tools are required:

- LLVM (clang, lld, llvm-ar)
- GNU mtools
- GNU grub
- GNU gdb

The toolset is described in the `tools.properties` file.
This file is required by the build tool.
Configuration properties are documented in `tools.properties.default`.
Property keys named `path` work as-if the environment `PATH` variable.
Currently, all keys must be defined.

# build

Aasgard's build system is based on Gradle, Nokee and custom plugins.
This system requires a JDK version 11.

To build: `./gradlew build`

To clean: `./gradlew clean`

# verify

Psys is verified by a technique orchestrating QEMU and GDB to watch for "asserts".
In short, the image stores into a known symbol which the test driver "watches" by driving GDB.
We are in the middle of improving this by publishing Gradle plugins for each tool.

To check: `./gradlew check`

# use

Psys is reusable as a set of Gradle projects.
Each project describes a single module.
Gradle should compute the required variants from the build configuration.

To reuse a modules, add a dependency on it:

```gradle
dependencies {
    implementation project(':uefi')
}
```

# architecture

The collection includes the following components:

* [acpi](acpi/README.md)
* [multiboot2](multiboot2/README.md)
* [pc](pc/README.md)
* uefi
* [x86](x86/README.md)

# references

_TODO_
