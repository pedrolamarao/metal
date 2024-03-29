import dev.nokee.platform.nativebase.ExecutableBinary

plugins {
    id("psys-application")
}

application {
    targetMachines.add( machines.os("host").architecture("-x86_64-multiboot2-elf") )

    dependencies {
        implementation(project(":multiboot2:start"))
    }

    val baseArgs = listOf("-std=c++20", "-fasm-blocks", "-flto", "-mno-mmx", "-mno-sse", "-mno-sse2")

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
                qemuArgs.debug.set("cpu_reset,int")
                qemuArgs.stop.set(false)
            }
        }
    }
}
