plugins {
    id("br.dev.pedrolamarao.metal.library")
    id("br.dev.pedrolamarao.metal.cxx")
}

group = "br.dev.pedrolamarao.metal.psys"

dependencies {
    testImplementation(project(":googletest"))
}

library {
    compileOptions = listOf("-fasm-blocks","-g","-std=c++20")
}