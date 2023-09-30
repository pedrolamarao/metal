plugins {
    id("br.dev.pedrolamarao.metal.application")
    id("br.dev.pedrolamarao.metal.cxx")
}

val options = listOf(
    "-gdwarf",
    "-flto",
    "-mno-red-zone", "-mno-mmx", "-mno-sse", "-mno-sse2",
    "-nostdlib",
    "-std=c++20"
)

metal {
    cxx {
        named("main") {
            compileOptions = options
        }
    }
    applications {
        named("main") {
            linkOptions = options
        }
    }
}