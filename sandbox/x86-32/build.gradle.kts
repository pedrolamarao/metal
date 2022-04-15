import dev.nokee.platform.nativebase.ExecutableBinary

plugins {
    id("psys-application")
}

application {
    targetMachines.add( machines.os("host").architecture("-x86_32-elf-multiboot2") )

    dependencies {
        implementation(project(":psys:start"))
        implementation(project(":x86"))
    }

    val baseArgs = listOf("-std=c++20", "-fasm-blocks", "-flto")

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
                qemuArgs.stop.set(false)
            }
        }
    }
}
