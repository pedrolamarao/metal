plugins {
    `kotlin-dsl`
}

val nokee = "0.4.0-202112012027.ff552c41"

dependencies {
    implementation("br.dev.pedrolamarao.gdb:core:1.0.0-SNAPSHOT")
    implementation("br.dev.pedrolamarao.gdb:gradle:1.0.0-SNAPSHOT")
    implementation("dev.nokee.cpp-library:dev.nokee.cpp-library.gradle.plugin:${nokee}")
    implementation("dev.nokee.native-unit-testing:dev.nokee.native-unit-testing.gradle.plugin:${nokee}")
}