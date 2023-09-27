plugins {
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.prebuilt")
}

metal {
    prebuilt {
        includable( layout.projectDirectory.dir("src/googletest/include") )
        linkable( layout.projectDirectory.file("src/lib/Release/gtest.lib") )
    }
}