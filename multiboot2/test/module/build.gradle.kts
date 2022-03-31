plugins {
    id("dev.nokee.cpp-application")
}

apply(plugin ="psys-targets")

application {
    targetMachines.addAll(
        // #XXX: build on any for x86_32-elf
        machines.os("host").architecture("-x86_32-elf")
    )

    val args = listOf("-std=c++20", "-flto", "-mno-red-zone", "-mno-mmx", "-mno-sse", "-mno-sse2")

    binaries.configureEach {
        if (this is dev.nokee.platform.nativebase.ExecutableBinary) {
            compileTasks.configureEach {
                compilerArgs.addAll(args)
            }
            linkTask {
                linkerArgs.addAll(args)
            }
        }
    }
}