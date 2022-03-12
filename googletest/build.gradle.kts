import dev.nokee.platform.nativebase.NativeBinary

plugins {
    id("psys-component")
}

library {
    targetLinkages.add(linkages.static)
    publicHeaders.from("include")
    privateHeaders.from(".")
    binaries.configureEach {
        if (this is NativeBinary) {
            compileTasks.configureEach {
                compilerArgs.addAll("-std=c++17", "-flto")
            }
        }
    }
}