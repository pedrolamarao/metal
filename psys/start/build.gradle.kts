plugins {
    id("br.dev.pedrolamarao.metal.library")
    id("br.dev.pedrolamarao.metal.cxx")
}

group = "br.dev.pedrolamarao.metal.psys"

dependencies {
    api(project(":multiboot2:start"))
}

library {
    compileOptions = listOf("-std=c++20", "-flto", "-fasm-blocks", "-gdwarf")
}