plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.cxx")
}

dependencies {
    nativeImplementation(project(":psys"))
    nativeImplementation(project(":multiboot2:foo"))
    nativeImplementation(project(":x86"))
}

metal {
    cxx {
        named("main") {
            compileOptions = listOf("-fasm-blocks","-g","-std=c++20")
        }
    }
}