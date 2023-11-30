import br.dev.pedrolamarao.gradle.metal.MetalApplication

plugins {
    id("metal-test") apply(false)
}

val x86_32_elf_multiboot2_ld = rootProject.file("multiboot2/x86_32-elf.ld")
val x86_64_elf_multiboot2_ld = rootProject.file("multiboot2/x86_64-elf.ld")

subprojects.filter { it.name != "module" }.forEach {

    group = "br.dev.pedrolamarao.metal.multiboot2.test"

    pluginManager.apply("metal-test")

    dependencies {
        add("implementation",project(":multiboot2:foo"))
    }

    val application: MetalApplication by extensions
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
    application.targets = listOf("x86_64-elf","i686-elf")
}