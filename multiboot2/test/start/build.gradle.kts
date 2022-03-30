plugins {
    id("psys-test")
}

application {
    dependencies {
        implementation(project(":multiboot2:start"))
    }
}