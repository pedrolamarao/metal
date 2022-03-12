import dev.nokee.platform.nativebase.ExecutableBinary

plugins {
    id("br.dev.pedrolamarao.gdb")
    id("psys-application")
}

apply(plugin ="psys-targets")

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

val run = project.tasks.register<MultibootRunImageTask>("run-image") {
    group = "psys"
    description = "runs image"
    imageFile.set( create.flatMap { it.outputFile } )
}

val test = project.tasks.register<MultibootTestImageTask>("test-image") {
    group = "psys"
    description = "tests image"
    imageFile.set( create.flatMap { it.outputFile } )
    executableFile.set(
        project.provider {
            val executable = application.binaries.get().stream().findAny().get() as ExecutableBinary
            executable.linkTask.get().linkedFile.get()
        }
    )
}

tasks.check { dependsOn(test) }