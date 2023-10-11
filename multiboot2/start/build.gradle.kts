plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cxx")
}

group = "br.dev.pedrolamarao.metal.multiboot2"

dependencies {
    api(project(":psys"))
    api(project(":multiboot2:foo"))
    api(project(":x86"))
}

metal {
    compileOptions = listOf("-fasm-blocks","-g","-std=c++20")
}

// TODO: Gradle Metal incorrectly tries to link empty source set

tasks.named("link-test") { enabled = false }

// TODO: Gradle Metal incorrectly tries to run nonexistent link output

tasks.named("run-test") { enabled = false }