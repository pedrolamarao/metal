plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cpp")
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