import org.ajoberstar.grgit.Grgit
import org.gradle.nativeplatform.platform.internal.DefaultNativePlatform
import java.nio.file.Files
import java.nio.file.Paths

plugins {
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.prebuilt")
    id("org.ajoberstar.grgit") version("5.2.0") apply(false)
}

val source = layout.projectDirectory.dir("src")
val build = layout.buildDirectory.dir("release").get()

// TODO: expose Gradle Metal locateToolFile utility
fun locateExecutableFile (list: String, name: String): File {
    for (item in list.split(File.pathSeparator.toRegex()).dropLastWhile { it.isEmpty() }.toTypedArray()) {
        val directory = Paths.get(item)
        if (! Files.isDirectory(directory)) continue
        val file = directory.resolve(name)
        if (Files.isExecutable(file)) return file.toFile()
        val file_exe = file.resolveSibling("$name.exe")
        if (Files.isExecutable(file_exe)) return file_exe.toFile()
    }
    throw GradleException("executable file not found: $name")
}

val metalPath = providers.gradleProperty("metal.path")
    .orElse(providers.environmentVariable("PATH"))

val cmake = metalPath.map { locateExecutableFile(it,"cmake") }

val clone = tasks.register("clone") {
    outputs.dir(source)
    doLast {
        if (! source.asFile.exists()) {
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

// TODO: enhance Gradle Metal with platform conventional prefixes and suffixes
val archivePrefix = if (DefaultNativePlatform.getCurrentOperatingSystem().isWindows) "" else "lib"
val archiveSuffix = if (DefaultNativePlatform.getCurrentOperatingSystem().isWindows) ".lib" else ".a"

metal {
    prebuilt {
        includable(source.dir("googletest/include")) { builtBy(clone) }
        linkable(build.file("lib/${archivePrefix}gtest${archiveSuffix}")) { builtBy(make) }
    }
}