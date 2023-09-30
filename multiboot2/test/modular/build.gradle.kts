import br.dev.pedrolamarao.gradle.metal.base.MetalCapability

plugins {
    id("metal-test")
}

val multibootModule = configurations.dependencyScope("multibootModule").get()

dependencies {
    implementation(project(":elf"))
    implementation(project(":multiboot2:start"))
    multibootModule(project(":multiboot2:test:module"))
}

val multibootModuleDependencies = configurations.resolvable("multibootModuleDependencies") {
    attributes { attribute(MetalCapability.ATTRIBUTE,MetalCapability.EXECUTABLE) }
    extendsFrom(multibootModule);
}

tasks.withType<MultibootCreateImageTask> {
    moduleFiles.from(multibootModuleDependencies)
}