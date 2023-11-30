import br.dev.pedrolamarao.gradle.metal.MetalApplication

plugins {
    id("metal-test") apply(false)
}

val x86_32_elf_multiboot2_ld = rootProject.file("multiboot2/x86_32-elf.ld")
val x86_64_elf_multiboot2_ld = rootProject.file("multiboot2/x86_64-elf.ld")

subprojects {
    group = "br.dev.pedrolamarao.metal.multiboot2.test"

    pluginManager.apply("br.dev.pedrolamarao.metal.application")

    val application: MetalApplication by extensions
    application.targets = listOf("x86_64-elf","i686-elf")

    pluginManager.withPlugin("metal-test") {
        dependencies {
            add("implementation",project(":multiboot2:foo"))
        }
        application.compileOptions = listOf(
            "-flto", "-fasm-blocks",
            "-gdwarf",
            "-mno-red-zone", "-mno-mmx", "-mno-sse", "-mno-sse2",
            "-std=c++20"
        )
        application.linkOptions = listOf(
            "-gdwarf",
            "-nostdlib",
            "-static",
            "-Wl,--script=${x86_32_elf_multiboot2_ld}"
        )
    }
}
