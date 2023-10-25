import br.dev.pedrolamarao.gradle.metal.base.MetalCompileTask

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
    targets = setOf("i686-elf","x86_64-elf")
}

// #TODO: Gradle Metal DSL does not allow filtering

tasks.named<MetalCompileTask>("compile-main-cxx") {
    when (target.get()) {
        "i686-elf" -> include("x86_32-elf/*")
        "x86_64-elf" -> include("x86_64-elf/*")
    }
}