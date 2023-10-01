pluginManagement {
    includeBuild("gradle/plugins")
    plugins {
        val metalVersion = "0.1+a43c5d5f65"
        id("br.dev.pedrolamarao.metal.archive") version(metalVersion)
        id("br.dev.pedrolamarao.metal.base") version(metalVersion)
        id("br.dev.pedrolamarao.metal.commands") version(metalVersion)
        id("br.dev.pedrolamarao.metal.cpp") version(metalVersion)
        id("br.dev.pedrolamarao.metal.cxx") version(metalVersion)
    }
    repositories {
        maven() {
            name = "Sonatype Open Source Snapshot Repository"
            url = uri("https://s01.oss.sonatype.org/content/repositories/snapshots/")
        }
        mavenLocal()
    }
}

rootProject.name = "metal"

// components

include("pc")
include("pc:test:cmos")
include("pc:test:pic")
include("pc:test:pit")
include("pc:test:uart")
include("elf")
include("googletest")
include("multiboot2:foo")
include("multiboot2:start")
include("multiboot2:test:entry")
include("multiboot2:test:layout")
include("multiboot2:test:minimal")
include("multiboot2:test:modular")
include("multiboot2:test:module")
include("multiboot2:test:start")
include("psys")
include("psys:start")
include("x86")
include("x86:test:cpuid")
include("x86:test:exceptions")
include("x86:test:interrupts")
//include("x86:test:long")
include("x86:test:main")
include("x86:test:msr")
include("x86:test:pages")
include("x86:test:segments")