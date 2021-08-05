Date: 2021-08-05

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

- GNU grub
- GNU gdb
- GNU mtools
- LLVM (clang, lld, llvm-ar)

The toolset is described in the `tools.properties` file.
This file is required by the build tool.
Configuration properties are documented in `tools.properties.default`.
Property keys named `path` work as-if the environment `PATH` variable.
Currently, all keys must be defined.

# build

Psys' build system is based on Gradle, Nokee and custom plugins.
This system requires a JDK version 11.

To build: `./gradlew build`

To clean: `./gradlew clean`

# verify

Psys is verified by a technique described below.

To check: `./gradlew check`

## Psys Test Protocol

Psys tests start when control reaches `_test_start` and finish when control reaches `_test_finish`.
During test execution, Psys tests progress when the value stored into `_test_control` changes.

When `_test_control` changes, let `old` be the old value and `new` be the new value.
If `old` is zero then test has entered stage `new`.
Else, if `new` is zero then test stage `old` has failed.
Else, test stage `old` has succeeded.

## Psys Test Driver

This project implements Psys test protocol orchestrating QEMU and GDB.
While QEMU executes the program, GDB watches for `_test_start`, `_test_finish` and `_test_control`.
The test driver controls GDB via MI to react appropriately.

This technique is implemented as Gradle tasks with Groovy source in `buildSrc`.
For Multiboot programs, see `TestMultibootRescue` in `multiboot.groovy`.

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
