plugins {
    `kotlin-dsl`
}

group = "br.dev.pedrolamarao.metal.plugins"

val elf = "1.0.0-SNAPSHOT"
val gdb = "1.0.0-SNAPSHOT"
val metal = "0.2"

kotlin.jvmToolchain {
    languageVersion.set(JavaLanguageVersion.of(17))
}

dependencies {
    implementation("br.dev.pedrolamarao.elf:api:${elf}")
    implementation("br.dev.pedrolamarao.gdb:rsp:${gdb}")
    implementation("br.dev.pedrolamarao.gradle.metal:plugins:${metal}")
    testImplementation("org.junit.jupiter:junit-jupiter:5.8.2")
}

tasks.test {
    useJUnitPlatform()
}
