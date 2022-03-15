import dev.nokee.platform.nativebase.NativeBinary
import org.gradle.internal.os.OperatingSystem

plugins {
    id("psys-component")
}

// #XXX: Gradle cannot disambiguate subprojects with the same group and name
group = "oops"

library {
    targetLinkages.add(linkages.static)

    // #XXX: Nokee can't cross compile to system "none"
    val none = OperatingSystem.current().getName()
    targetMachines.addAll(
        machines.os(none).architecture("-multiboot-x86_32"),
        machines.os(none).architecture("-multiboot-x86_64")
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