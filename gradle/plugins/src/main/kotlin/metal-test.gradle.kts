plugins {
    id("br.dev.pedrolamarao.metal.application")
    id("br.dev.pedrolamarao.metal.cxx")
}

val linkExecutable = metal.applications.named("main").flatMap { it.output }

val createImage = project.tasks.register<MultibootCreateImageTask>("make-main-image") {
    inputFile = linkExecutable
    dependsOn("link-main")
}

tasks.register("image") {
    group = "metal"
    dependsOn(createImage)
}

val testImage = project.tasks.register<MultibootTestImageTask>("test-main-image") {
    imageFile = createImage.flatMap { it.outputFile }
    executableFile = linkExecutable
}

tasks.test.configure {
    dependsOn(testImage)
}