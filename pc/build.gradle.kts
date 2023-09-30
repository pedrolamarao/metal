plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.cxx")
}

group = "br.dev.pedrolamarao.metal.pc"

dependencies {
    api(project(":psys"))
}

metal {
    cxx {
        named("main") {
            compileOptions = listOf("-g","-std=c++20")
        }
    }
}