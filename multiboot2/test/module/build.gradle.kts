plugins {
    id("dev.nokee.cpp-application")
}

apply(plugin ="psys-targets")

application {
    targetMachines.addAll(
        // #XXX: build on any for x86_32-elf
        machines.os("host").architecture("-x86_32-elf")
    )
}