plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cxx")
}

group = "br.dev.pedrolamarao.metal.psys"

dependencies {
    api(project(":multiboot2:start"))
}

metal {
    compileOptions = listOf("-std=c++20", "-flto", "-fasm-blocks", "-gdwarf")
}

// TODO: Gradle Metal incorrectly tries to link empty source set

tasks.named("link-test") { enabled = false }

// TODO: Gradle Metal incorrectly tries to run nonexistent link output

tasks.named("run-test") { enabled = false }