plugins {
    id("psys-test")
}

val modules: Configuration by configurations.creating {
    isCanBeConsumed = false
    isCanBeResolved = true
}

dependencies {
    modules(project(":multiboot2:test:module"))
}

application {
    dependencies {
        implementation(project(":multiboot2:start"))
    }
}

tasks.withType<MultibootCreateImageTask> {
    moduleFiles.from( modules )
}
