import dev.nokee.platform.nativebase.NativeBinary

plugins {
    id("psys-component")
}

// #XXX: Gradle cannot disambiguate subprojects with the same group and name
group = "oops"

library {
    targetLinkages.add(linkages.static)

    targetMachines.addAll(
        // #XXX: build on any for x86_32-elf-multiboot2
        machines.os("host").architecture("-x86_32-elf-multiboot2"),
        // #XXX: build on any for x86_64-elf-multiboot2
        machines.os("host").architecture("-x86_64-elf-multiboot2"),
    )

    dependencies {
        api(project(":multiboot2"))
    }

    binaries.configureEach {
        if (this is NativeBinary) {
            compileTasks.configureEach {
                compilerArgs.addAll("-std=c++20", "-flto", "-fasm-blocks")
            }
        }
    }
}