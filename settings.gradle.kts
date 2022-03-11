pluginManagement {
    includeBuild("gradle/plugins")
    repositories {
        maven() {
            name = "Nokee Release Repository"
            url = uri("https://repo.nokee.dev/release")
            mavenContent() {
                includeGroupByRegex("dev\\.nokee.*")
                includeGroupByRegex("dev\\.gradleplugins.*")
            }
        }
        maven() {
            name = "Nokee Snapshot Repository"
            url = uri("https://repo.nokee.dev/snapshot")
            mavenContent() {
                includeGroupByRegex("dev\\.nokee.*")
                includeGroupByRegex("dev\\.gradleplugins.*")
            }
        }
        maven() {
            name = "Sonatype Open Source Snapshot Repository"
            url = uri("https://s01.oss.sonatype.org/content/repositories/snapshots/")
        }
        gradlePluginPortal()
    }
}

rootProject.name = "psys"

// components

include("acpi")

include("googletest")

include("multiboot2")
rootProject.projectDir.resolve("multiboot2/test/x86_32-elf").toPath().apply {
    java.nio.file.Files.list(this).forEach {
        if (java.nio.file.Files.isDirectory(it))
            include("multiboot2:test:x86_32-elf:${it.fileName}")
    }
}

include("pc")
rootProject.projectDir.resolve("pc/test/x86_32-elf-multiboot2").toPath().apply {
    java.nio.file.Files.list(this).forEach {
        if (java.nio.file.Files.isDirectory(it))
            include("pc:test:x86_32-elf-multiboot2:${it.fileName}")
    }
}

include("psys")

include("x86")
rootProject.projectDir.resolve("x86/test/x86_32-elf-multiboot2").toPath().apply {
    java.nio.file.Files.list(this).forEach {
        if (java.nio.file.Files.isDirectory(it))
            include("x86:test:x86_32-elf-multiboot2:${it.fileName}")
    }
}

// applications

include("app:sandbox")