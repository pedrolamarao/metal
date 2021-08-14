Date: 2021-08-05

# summary

Welcome to the Psys project!

Psys is a research project on "bare metal" software engineering.

For more information, see [GOAL](doc/GOAL.md).

# index

0. summary
1. prepare
2. assemble
3. check
4. use
5. architecture
6. references

# prepare

Psys is built with an LLVM based toolset.

You must configure the toolset by defining file `tools.properties`
based on `tools.properties.default`.

These tools are required:

- GNU grub version 2
- GNU gdb
- GNU mtools
- LLVM (clang, lld, llvm-ar) version 13
- QEMU

For more information, see [TOOLS](doc/TOOLS.md).

# build

Psys is built using Gradle, Nokee and a JDK version 11.

To build: `./gradlew build`

To clean: `./gradlew clean`

# verify

Psys is verified by automated tests.

For more information, see [TEST](doc/TEST.md).

To check: `./gradlew --no-parallel check`

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
