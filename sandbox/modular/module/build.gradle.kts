plugins {
    id("psys-application")
}

apply(plugin ="psys-targets")

application {
    targetMachines.addAll(
        machines.os("host").architecture("-x86_64-elf")
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