import java.nio.file.Files

pluginManagement {
    includeBuild("gradle/plugins")
    plugins {
        id("br.dev.pedrolamarao.metal.archive") version("1.0-SNAPSHOT")
        id("br.dev.pedrolamarao.metal.base") version("1.0-SNAPSHOT")
        id("br.dev.pedrolamarao.metal.commands") version("1.0-SNAPSHOT")
        id("br.dev.pedrolamarao.metal.cpp") version("1.0-SNAPSHOT")
        id("br.dev.pedrolamarao.metal.cxx") version("1.0-SNAPSHOT")
    }
    repositories {
        mavenLocal()
    }
}

rootProject.name = "metal"

// components

include("pc")
include("elf")
include("googletest")
include("multiboot2:foo")
include("multiboot2:start")
include("psys")
include("x86")