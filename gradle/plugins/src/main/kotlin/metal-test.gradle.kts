plugins {
    id("br.dev.pedrolamarao.metal.application")
    id("br.dev.pedrolamarao.metal.cxx")
}

val createImage = project.tasks.register<MultibootCreateImageTask>("make-main-image") {
    inputFile = tasks.link.flatMap { it.output }
}

tasks.register("image") {
    group = "metal"
    dependsOn(createImage)
}

val testImage = project.tasks.register<MultibootTestImageTask>("test-main-image") {
    imageFile = createImage.flatMap { it.outputFile }
    executableFile = tasks.link.flatMap { it.output }
}

tasks.check.configure {
    dependsOn(testImage)
}