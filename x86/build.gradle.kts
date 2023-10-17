plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.cxx")
    id("br.dev.pedrolamarao.metal.ixx")
}

group = "br.dev.pedrolamarao.metal.x86"

dependencies {
    api(project(":psys"))
}

metal {
    compileOptions = listOf("-fasm-blocks","-g","-std=c++20","-Wno-unused-command-line-argument")

    applications { test { targets = setOf("x86_64-pc-linux-gnu","x86_64-pc-windows-msvc") } }
    ixx { main { public = true } }
}

// TODO: enhance Gradle Metal with component-specific dependencies

dependencies {
    implementation(project(":googletest"))
}