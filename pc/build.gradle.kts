plugins {
    id("br.dev.pedrolamarao.metal.library")
    id("br.dev.pedrolamarao.metal.cxx")
}

group = "br.dev.pedrolamarao.metal.pc"

dependencies {
    api(project(":psys"))
    testImplementation(project(":googletest"))
}

library {
    compileOptions = listOf("-fasm-blocks","-g","-std=c++20","-Wno-unused-command-line-argument")
}