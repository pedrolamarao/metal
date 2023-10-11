import br.dev.pedrolamarao.gradle.metal.base.MetalExtension
import br.dev.pedrolamarao.gradle.metal.base.MetalSourceTask

plugins {
    id("metal-test") apply(false)
}

val x86_32_elf_multiboot2_ld = rootProject.file("multiboot2/x86_32-elf.ld")
val x86_64_elf_multiboot2_ld = rootProject.file("multiboot2/x86_64-elf.ld")

subprojects {
    group = "br.dev.pedrolamarao.metal.multiboot2.test"
    pluginManager.withPlugin("metal-test") {
        dependencies {
            add("implementation",project(":multiboot2:foo"))
        }
        extensions.configure<MetalExtension>() {
            compileOptions = listOf(
                "-flto", "-fasm-blocks",
                "-gdwarf",
                "-mno-red-zone", "-mno-mmx", "-mno-sse", "-mno-sse2",
                "-std=c++20"
            )
            linkOptions = listOf(
                "-gdwarf",
                "-nostdlib",
                "-static",
                "-Wl,--script=${x86_32_elf_multiboot2_ld}"
            )
        }
    }

    // TODO: enhance Gradle Metal with target includes/excludes support
    afterEvaluate {
        val metal: MetalExtension by extensions
        val targets = listOf("x86_64-elf","i686-elf")
        val targetEnabled = targets.contains(metal.target.get())
        tasks.withType<MetalSourceTask>().configureEach { enabled = targetEnabled }
        tasks.withType<MultibootCreateImageTask>().configureEach { enabled = targetEnabled }
        tasks.withType<MultibootRunImageTask>().configureEach { enabled = targetEnabled }
        tasks.withType<MultibootTestImageTask>().configureEach { enabled = targetEnabled }
        tasks.named("test") { enabled = targetEnabled }
    }
}
