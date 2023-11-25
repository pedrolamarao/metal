plugins {
    id("br.dev.pedrolamarao.metal.application")
    id("br.dev.pedrolamarao.metal.cxx")
}

val mainExecutable = metal.applications.named("main").flatMap { it.output }

val createImage = project.tasks.register<MultibootCreateImageTask>("make-main-image") {
    dependsOn("link-main")
    inputFile = mainExecutable
}

tasks.register("image") {
    group = "metal"
    dependsOn(createImage)
}

val testImage = project.tasks.register<MultibootTestImageTask>("test-main-image") {
    imageFile = createImage.flatMap { it.outputFile }
    executableFile = mainExecutable
}

tasks.test {
    dependsOn(testImage)
}