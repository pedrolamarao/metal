import dev.nokee.platform.nativebase.ExecutableBinary

plugins {
    id("br.dev.pedrolamarao.gdb")
    id("psys-application")
}

apply(plugin ="psys-targets")

val testAll = project.tasks.register("test-image") {
    group = "psys"
}

project.afterEvaluate {
    application.binaries.get().forEach { binary ->
        if (binary is ExecutableBinary) {
            val name = binary.linkTask.name
            val executable = binary.linkTask.flatMap { it.linkedFile }
            val create = project.tasks.register<MultibootCreateImageTask>("image-${name}") {
                group = "psys"
                description = "creates image"
                inputFile.set(executable)
            }
            project.tasks.assemble { dependsOn(create) }
            val image = create.flatMap { it.outputFile }
            project.tasks.register<MultibootRunImageTask>("run-image-${name}") {
                group = "psys"
                description = "runs image"
                imageFile.set(image)
            }
            val test = project.tasks.register<MultibootTestImageTask>("test-image-${name}") {
                group = "psys"
                description = "tests image"
                gdbArchitecture.set("i386:x86-64")
                imageFile.set(image)
                executableFile.set(executable)
            }
            testAll { dependsOn(test) }
        }
    }
}
