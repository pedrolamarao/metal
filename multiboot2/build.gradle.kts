import dev.nokee.platform.nativebase.NativeBinary
import dev.nokee.testing.nativebase.NativeTestSuite
import dev.nokee.testing.nativebase.internal.DefaultNativeTestSuiteComponent
import org.gradle.internal.os.OperatingSystem

plugins {
    id("psys-component")
}

library {
    targetLinkages.add(linkages.static)

    // #XXX: Nokee can't cross compile to system "none"
    val none = OperatingSystem.current().getName()
    targetMachines.addAll(
        machines.os(none).architecture("-multiboot-x86_32"),
        machines.os(none).architecture("-multiboot-x86_64"),
        machines.linux.x86_64,
        machines.windows.x86_64,
    )

    dependencies { api(project(":psys")) }

    binaries.configureEach {
        if (this is NativeBinary) {
            compileTasks.configureEach {
                compilerArgs.addAll("-std=c++20", "-flto")
            }
        }
    }
}

testSuites {
    register("test", NativeTestSuite::class.java).get().apply {
        testedComponent(library)

        dependencies {
            implementation(project(":googletest"))
        }

        if (this is DefaultNativeTestSuiteComponent) {
            binaries.configureEach {
                if (this is dev.nokee.platform.nativebase.ExecutableBinary) {
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

tasks.check { dependsOn(":multiboot2:test:check") }