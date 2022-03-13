Date: 2022-03-13

![ubuntu-latest](https://github.com/pedrolamarao/psys/actions/workflows/ubuntu.yml/badge.svg)
![windows-latest](https://github.com/pedrolamarao/psys/actions/workflows/windows.yml/badge.svg)

# summary

Welcome to the Psys project!

Psys is a research project on "bare metal" software engineering.

For more information on this project's mission, ambitions and aims, see [GOAL](doc/GOAL.md).

# prepare

Psys is built with an LLVM based toolset.

These tools are required:

- GNU grub
- GNU gdb
- LLVM (clang, lld, llvm-ar)
- QEMU

You may configure tools in `tools.properties`.

For more information, see [TOOLS](doc/TOOLS.md).

# build

Psys is built using Gradle, Nokee and a JDK version 11.

To build: `./gradlew build`

To clean: `./gradlew clean`

# play

To play around, mess with the [sandbox application](app/sandbox).

To run: `./gradlew :app:sandbox:runImage`

# verify

Psys is verified by automated tests.

For more information, see [TEST](doc/TEST.md).

To verify: `./gradlew check`
