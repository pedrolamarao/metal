import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

plugins {
    `kotlin-dsl`
}

val nokee = "0.4.0-202112012027.ff552c41"

java.sourceCompatibility = JavaVersion.VERSION_11

dependencies {
    implementation("br.dev.pedrolamarao.gdb:core:1.0.0-SNAPSHOT")
    implementation("br.dev.pedrolamarao.gdb:gradle:1.0.0-SNAPSHOT")
    implementation("dev.nokee:languageCpp:${nokee}")
    implementation("dev.nokee.cpp-application:dev.nokee.cpp-application.gradle.plugin:${nokee}")
    implementation("dev.nokee.cpp-library:dev.nokee.cpp-library.gradle.plugin:${nokee}")
    implementation("dev.nokee.native-unit-testing:dev.nokee.native-unit-testing.gradle.plugin:${nokee}")
}

tasks.withType<KotlinCompile> {
    kotlinOptions {
        jvmTarget = "11"
    }
}