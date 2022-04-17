import dev.nokee.platform.cpp.CppApplication
import dev.nokee.platform.nativebase.ExecutableBinary

plugins {
    base
}

subprojects {
    apply(plugin = "psys-test")

    project.extensions.configure<CppApplication> {
        targetMachines.addAll(
            // #XXX: build on any for x86_32-elf-multiboot2
            machines.os("host").architecture("-x86_32-multiboot2-elf"),
        )

        dependencies {
            implementation(project(":pc"))
            implementation(project(":psys:start"))
            implementation(project(":x86"))
        }

        val baseArgs = listOf(
            "-std=c++20", "-flto", "-fasm-blocks",
            "-mno-red-zone", "-mno-mmx", "-mno-sse", "-mno-sse2"
        )

        binaries.configureEach {
            if (this is ExecutableBinary) {
                compileTasks.configureEach {
                    compilerArgs.addAll(baseArgs)
                }
                linkTask {
                    linkerArgs.addAll(baseArgs)
                }
            }
        }
    }
}
