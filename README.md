Date: 2023-09-16

![ubuntu-latest](https://github.com/pedrolamarao/psys/actions/workflows/ubuntu.yml/badge.svg)
![windows-latest](https://github.com/pedrolamarao/psys/actions/workflows/windows.yml/badge.svg)

# summary

Welcome to the Psys project!

Psys is a research project on "bare metal" software engineering.

For more information on this project's mission, ambitions and aims, see [GOAL](doc/GOAL.md).

# quick start

Put JDK 17 and LLVM 16 in your `${PATH}`.

From the source root, run: `./gradlew build`

To play with code, look inside the `sandbox` folder for a variety of projects you can play with!

# prepare

Psys is built with an LLVM based toolset.

These tools are required to build all artifacts:

- GNU grub
- GNU gdb
- LLVM
- QEMU

You may configure tools in `tools.properties`.

For more information, see [TOOLS](doc/TOOLS.md).

# build

Psys is built using Gradle.

To assemble all artifacts: `./gradlew assemble`

To clean all artifacts: `./gradlew clean`

# verify

Psys is verified by automated tests.

For more information, see [TEST](doc/TEST.md).

To verify all unit tests: `./gradlew check`

To verify all psys tests: `./gradlew test-image`
