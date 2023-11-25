import br.dev.pedrolamarao.gradle.metal.base.MetalCompileTask

plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.cxx")
    id("br.dev.pedrolamarao.metal.ixx")
}

group = "br.dev.pedrolamarao.metal.x86"

dependencies {
    api(project(":psys"))
    testImplementation(project(":googletest"))
}

metal {
    compileOptions = listOf("-fasm-blocks","-g","-std=c++20","-Wno-unused-command-line-argument")

    applications { test { targets = setOf("x86_64-pc-linux-gnu","x86_64-pc-windows-msvc") } }
    ixx { main { public = true } }
}

// #TODO: Gradle Metal DSL does not allow filtering

tasks.named<MetalCompileTask>("compile-main-cxx") {
    include("*")
    when (target.get()) {
        "i686-elf" -> include("x86_32/*")
        "x86_64-elf",
        "x86_64-pc-linux-gnu",
        "x86_64-pc-windows-msvc" -> include("x86_64/*")
    }
}