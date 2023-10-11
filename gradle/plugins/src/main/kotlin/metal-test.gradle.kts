plugins {
    id("br.dev.pedrolamarao.metal.application")
    id("br.dev.pedrolamarao.metal.cxx")
}

val linkExecutable = metal.applications.named("main").flatMap { it.linkTask }

val createImage = project.tasks.register<MultibootCreateImageTask>("make-main-image") {
    dependsOn(linkExecutable)
    inputFile = linkExecutable.flatMap { it.output }
}

tasks.register("image") {
    group = "metal"
    dependsOn(createImage)
}

val testImage = project.tasks.register<MultibootTestImageTask>("test-main-image") {
    imageFile = createImage.flatMap { it.outputFile }
    executableFile = linkExecutable.flatMap { it.output }
}

tasks.named("test") {
    dependsOn(testImage)
}