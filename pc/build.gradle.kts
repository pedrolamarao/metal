plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.cxx")
}

dependencies {
    nativeImplementation(project(":psys"))
}

metal {
    cxx {
        named("main") {
            compileOptions = listOf("-g","-std=c++20")
        }
    }
}