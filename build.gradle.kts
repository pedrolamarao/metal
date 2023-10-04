plugins {
    id("br.dev.pedrolamarao.metal.commands")
}

allprojects {
    group = "br.dev.pedrolamarao.metal"
    version = "0.6.0-SNAPSHOT"
}

dependencies {
    commands(project(":elf"))
    commands(project(":multiboot2:foo"))
    commands(project(":multiboot2:start"))
    commands(project(":pc"))
    commands(project(":psys"))
    commands(project(":psys:start"))
    commands(project(":x86"))
}

tasks.wrapper.configure {
    gradleVersion = "8.4-rc-3"
}