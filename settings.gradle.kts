import java.nio.file.Files

pluginManagement {
    includeBuild("gradle/plugins")
    repositories {
        maven {
            name = "Nokee Release Repository"
            url = uri("https://repo.nokee.dev/release")
            mavenContent() {
                includeGroupByRegex("dev\\.nokee.*")
                includeGroupByRegex("dev\\.gradleplugins.*")
            }
        }
        maven {
            name = "Nokee Snapshot Repository"
            url = uri("https://repo.nokee.dev/snapshot")
            mavenContent() {
                includeGroupByRegex("dev\\.nokee.*")
                includeGroupByRegex("dev\\.gradleplugins.*")
            }
        }
        maven {
            name = "Sonatype Open Source Snapshot Repository"
            url = uri("https://s01.oss.sonatype.org/content/repositories/snapshots/")
        }
        gradlePluginPortal()
    }
}

rootProject.name = "psys"

// components

include("elf")

include("googletest")

include("multiboot2:foo")
include("multiboot2:start")
rootProject.projectDir.resolve("multiboot2/test").toPath().apply {
    Files.list(this).forEach {
        if (Files.isDirectory(it))
            include("multiboot2:test:${it.fileName}")
    }
}

include("pc")
rootProject.projectDir.resolve("pc/test/x86_32-elf-multiboot2").toPath().apply {
    Files.list(this).forEach {
        if (Files.isDirectory(it))
            include("pc:test:x86_32-elf-multiboot2:${it.fileName}")
    }
}

include("psys")
include("psys:start")

include("x86")
rootProject.projectDir.resolve("x86/test/x86_32-elf-multiboot2").toPath().apply {
    Files.list(this).forEach {
        if (Files.isDirectory(it))
            include("x86:test:x86_32-elf-multiboot2:${it.fileName}")
    }
}

// applications

rootProject.projectDir.resolve("app").toPath().apply {
    Files.list(this).forEach {
        if (Files.isDirectory(it))
            include("app:${it.fileName}")
    }
}