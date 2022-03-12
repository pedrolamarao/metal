import dev.nokee.platform.nativebase.ExecutableBinary

plugins {
    id("psys-application")
}

application {
    // #XXX: Nokee can't cross compile to system "none"
    val none = org.gradle.internal.os.OperatingSystem.current().getName()
    targetMachines.addAll(
        machines.os(none).architecture("-multiboot-x86_32"),
        machines.os(none).architecture("-multiboot-x86_64")
    )

    dependencies {
        implementation(project(":multiboot2"))
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

afterEvaluate {
    application.binaries.get().forEach { binary ->
        if (binary is ExecutableBinary) {
            val name = binary.linkTask.name
            val create = project.tasks.register<MultibootCreateImageTask>("image-${name}") {
                group = "psys"
                inputFile.set( binary.linkTask.flatMap { it.linkedFile })
            }
            project.tasks.register<MultibootRunImageTask>("run-image-${name}") {
                group = "psys"
                imageFile.set( create.flatMap { it.outputFile } )
            }
        }
    }
}
