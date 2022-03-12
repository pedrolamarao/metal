import dev.nokee.platform.nativebase.ExecutableBinary

plugins {
    base
}

subprojects {
    apply(plugin = "psys-test")

    project.extensions.configure<dev.nokee.platform.cpp.CppApplication> {
        // #XXX: Nokee can't cross compile to system "none"
        val none = org.gradle.internal.os.OperatingSystem.current().getName()
        targetMachines.addAll(
            machines.os(none).architecture("-multiboot-x86_32")
        )

        dependencies {
            implementation(project(":multiboot2"))
            implementation(project(":pc"))
            implementation(project(":pc:test"))
            implementation(project(":x86"))
        }

        val baseArgs = listOf("-std=c++20", "-flto", "-fasm-blocks")

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
