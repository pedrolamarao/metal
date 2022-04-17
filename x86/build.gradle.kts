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
        machines.windows.x86_64,
        // #XXX: build on any for x86_32-elf
        machines.os("host").architecture("-x86_32-elf"),
        // #XXX: build on any for x86_32-elf-multiboot2
        machines.os("host").architecture("-x86_32-elf-multiboot2"),
        // #XXX: build on any for x86_64-elf
        machines.os("host").architecture("-x86_64-elf"),
        // #XXX: build on any for x86_64-elf-multiboot2
        machines.os("host").architecture("-x86_64-elf-multiboot2"),
    )

    dependencies {
      api(project(":psys"))
    }

    val baseArgs = listOf(
        "-std=c++20", "-flto", "-fasm-blocks",
        "-mno-red-zone", "-mno-mmx", "-mno-sse", "-mno-sse2"
    )

    binaries.configureEach {
        if (this is NativeBinary) {
            compileTasks.configureEach {
                compilerArgs.addAll(baseArgs)
            }
        }
    }
}

testSuites {
    register("test", NativeTestSuite::class.java) {
        testedComponent(library)

        dependencies {
            // #XXX: Nokee does not transitively include main `api` dependencies
            implementation(project(":psys"))
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