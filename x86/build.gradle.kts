plugins {
    id("br.dev.pedrolamarao.metal.library")
    id("br.dev.pedrolamarao.metal.cxx")
}

group = "br.dev.pedrolamarao.metal.x86"

dependencies {
    api(project(":psys"))
    testImplementation(project(":googletest"))
}

library {
    compileOptions = listOf("-fasm-blocks","-g","-std=c++20","-Wno-unused-command-line-argument")
}

test {
    targets = listOf(metal.host.get())
}

// #TODO: Gradle Metal DSL does not allow filtering

tasks.compileCxx.configure {
    include("*")
    when (metal.target.get()) {
        "i686-elf" -> include("x86_32/*")
        "x86_64-elf",
        "x86_64-pc-linux-gnu",
        "x86_64-pc-windows-msvc" -> include("x86_64/*")
    }
}