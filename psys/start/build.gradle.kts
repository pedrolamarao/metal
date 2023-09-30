plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.cxx")
}

group = "br.dev.pedrolamarao.metal.psys"

dependencies {
    api(project(":multiboot2:start"))
}

metal {
    cxx {
       named("main") {
            compileOptions = listOf("-std=c++20", "-flto", "-fasm-blocks", "-gdwarf")
        }
    }
}
