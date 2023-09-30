plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.cxx")
}

group = "br.dev.pedrolamarao.metal.x86"

dependencies {
    api(project(":psys"))
}

metal {
    compileOptions = listOf("-fasm-blocks","-g","-std=c++20")
}