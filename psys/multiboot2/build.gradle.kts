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
        machines.linux.architecture("-multiboot-x86_32"),
        machines.windows.architecture("-multiboot-x86_32"),
        // #XXX: build on any for x86_32-elf-multiboot2
        machines.linux.architecture("-multiboot-x86_64"),
        machines.windows.architecture("-multiboot-x86_64"),
    )

    dependencies {
        api(project(":psys"))
        api(project("::multiboot2"))
    }

    binaries.configureEach {
        if (this is NativeBinary) {
            compileTasks.configureEach {
                compilerArgs.addAll("-std=c++20", "-flto", "-fasm-blocks")
            }
        }
    }
}