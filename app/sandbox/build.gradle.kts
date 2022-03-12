import dev.nokee.platform.nativebase.ExecutableBinary

plugins {
    id("psys-application")
}

application {
    // #XXX: Nokee can't cross compile to system "none"
    val none = org.gradle.internal.os.OperatingSystem.current().getName()
    targetMachines.add( machines.os(none).architecture("-multiboot-x86_32") )

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

val create = project.tasks.register<MultibootCreateImageTask>("image") {
    group = "psys"
    description = "creates image"
    dependsOn(project.tasks.assemble)
    inputFile.set(
        project.provider {
            val executable = application.binaries.get().stream().findAny().get() as ExecutableBinary
            executable.linkTask.get().linkedFile.get()
        }
    )
}

project.tasks.register<MultibootRunImageTask>("run-image") {
    group = "psys"
    description = "runs image"
    imageFile.set( create.flatMap { it.outputFile } )
}
