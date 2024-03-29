plugins {
    id("psys-application")
}

application {
    targetMachines.addAll(
        machines.os("host").architecture("-x86_32-multiboot2-elf"),
    )

    dependencies {
        implementation(project(":elf"))
        implementation(project(":multiboot2:start"))
        implementation(project(":x86"))
    }

    val args = listOf("-std=c++20", "-fasm-blocks", "-flto", "-mno-red-zone", "-mno-mmx", "-mno-sse", "-mno-sse2")

    binaries.configureEach {
        if (this is dev.nokee.platform.nativebase.ExecutableBinary) {
            compileTasks.configureEach {
                compilerArgs.addAll(args)
            }
            linkTask {
                linkerArgs.addAll(args)
            }
        }
    }
}

val modules: Configuration by configurations.creating {
    isCanBeConsumed = false
    isCanBeResolved = true
}

dependencies {
    modules(project(":sandbox:modular:module-32"))
    modules(project(":sandbox:modular:module-64"))
}

afterEvaluate {
    application.binaries.get().forEach { binary ->
        if (binary is dev.nokee.platform.nativebase.ExecutableBinary) {
            val name = binary.linkTask.name
            val create = project.tasks.register<MultibootCreateImageTask>("image-${name}") {
                group = "psys"
                inputFile.set( binary.linkTask.flatMap { it.linkedFile })
                moduleFiles.from( modules )
            }
            project.tasks.register<MultibootRunImageTask>("run-image-${name}") {
                group = "psys"
                imageFile.set( create.flatMap { it.outputFile } )
                qemuArgs.debug.set("cpu_reset,int")
            }
        }
    }
}
