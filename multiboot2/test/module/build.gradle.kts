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
    compileOptions = options
    linkOptions = options
}