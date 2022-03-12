import dev.nokee.platform.nativebase.NativeBinary

plugins {
    id("psys-component")
}

library {
    targetLinkages.add(linkages.static)

    // #XXX: Nokee can't cross compile to system "none"
    val os = org.gradle.internal.os.OperatingSystem.current().getName()
    targetMachines.addAll( machines.os(os).architecture("-multiboot-x86_32") )

    dependencies {
        api(project(":psys"))
        implementation(project(":multiboot2"))
    }

    binaries.configureEach {
        if (this is NativeBinary) {
            compileTasks.configureEach {
                compilerArgs.addAll("-std=c++20", "-fasm-blocks", "-flto")
            }
        }
    }
}

tasks.check { dependsOn(":pc:test:x86_32-elf-multiboot2:check") }