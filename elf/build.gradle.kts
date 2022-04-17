import dev.nokee.platform.nativebase.ExecutableBinary
import dev.nokee.platform.nativebase.NativeBinary
import dev.nokee.testing.nativebase.NativeTestSuite
import dev.nokee.testing.nativebase.internal.DefaultNativeTestSuiteComponent

plugins {
    id("psys-component")
}

library {
    targetLinkages.add(linkages.static)

    targetMachines.addAll(
        // #XXX: build on any for same
        machines.linux.x86_64,
        machines.macOS.x86_64,
        machines.windows.x86_64,
        // #XXX: build on any for x86_32-elf
        machines.os("host").architecture("-x86_32-elf"),
        // #XXX: build on any for x86_32-elf-multiboot2
        machines.os("host").architecture("-x86_32-multiboot2-elf"),
        // #XXX: build on any for x86_64-elf
        machines.os("host").architecture("-x86_64-elf"),
        // #XXX: build on any for x86_64-elf-multiboot2
        machines.os("host").architecture("-x86_64-multiboot2-elf"),
    )

    dependencies {
        implementation(project(":psys"))
    }

    binaries.configureEach {
        if (this is NativeBinary) {
            compileTasks.configureEach {
                compilerArgs.addAll("-std=c++20", "-flto")
            }
        }
    }
}

testSuites {
    register("test", NativeTestSuite::class.java) {
        testedComponent(library)

        dependencies {
            implementation(project(":googletest"))
        }

        if (this is DefaultNativeTestSuiteComponent) {
            binaries.configureEach {
                if (this is ExecutableBinary) {
                    compileTasks.configureEach {
                        compilerArgs.addAll("-std=c++20", "-flto")
                    }
                    linkTask {
                        // #XXX: Nokee ignores toolchain linker arguments
                        linkerArgs.addAll("-fuse-ld=lld", "-flto")
                    }
                }
            }
        }
    }
}