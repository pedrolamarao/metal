plugins {
    `kotlin-dsl`
}

val gdb = "1.0.0-SNAPSHOT"
val nokee = "[0.4.0, 0.5.0)"

kotlin.jvmToolchain {
    (this as JavaToolchainSpec).languageVersion.set(JavaLanguageVersion.of(17))
}

dependencies {
    implementation("br.dev.pedrolamarao.gdb:core:${gdb}")
    implementation("br.dev.pedrolamarao.gdb:gradle:${gdb}")
    implementation("dev.nokee:languageCpp:${nokee}")
    implementation("dev.nokee.cpp-application:dev.nokee.cpp-application.gradle.plugin:${nokee}")
    implementation("dev.nokee.cpp-library:dev.nokee.cpp-library.gradle.plugin:${nokee}")
    implementation("dev.nokee.native-unit-testing:dev.nokee.native-unit-testing.gradle.plugin:${nokee}")
    testImplementation("org.junit.jupiter:junit-jupiter:5.8.2")
}

tasks.test {
    useJUnitPlatform()
}
