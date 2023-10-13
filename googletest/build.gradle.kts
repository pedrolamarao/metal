import org.ajoberstar.grgit.Grgit

plugins {
    id("br.dev.pedrolamarao.metal.prebuilt")
    id("org.ajoberstar.grgit") version("5.2.0") apply(false)
}

val source = layout.projectDirectory.dir("src")
val build = layout.buildDirectory.dir("release").get()

val metalPath = providers.gradleProperty("metal.path")
    .orElse(providers.environmentVariable("PATH"))

val cmake = metal.locateTool("cmake")

val clone = tasks.register("clone") {
    doLast {
        if (! source.dir(".git").asFile.exists()) {
            Grgit.clone {
                depth = 1
                dir = source
                uri = "https://github.com/google/googletest"
            }
        }
    }
}

val configure = tasks.register<Exec>("configure") {
    dependsOn(clone)
    inputs.dir(source)
    outputs.file(build.file("CMakeCache.txt"))
    environment("PATH" to metalPath.get())
    executable(cmake.get())
    args(
        "-B",build,
        "-DCMAKE_BUILD_TYPE=Release",
        "-DCMAKE_TOOLCHAIN_FILE=${projectDir}/llvm.cmake",
        "-G","Ninja",
        "-S",source
    )
}

val make = tasks.register<Exec>("make") {
    dependsOn(configure)
    environment("PATH" to metalPath.get())
    executable(cmake.get())
    args("--build",build)
}

metal {
    prebuilt {
        includable( source.dir("googletest/include") ) { builtBy(clone) }
        linkable( metal.archiveFileName("gtest").map { build.file("lib/${it}") } ) { builtBy(make) }
    }
}