dependencyResolutionManagement {
    repositories {
        maven() {
            name = "Sonatype Open Source Snapshot Repository"
            url = uri("https://s01.oss.sonatype.org/content/repositories/snapshots/")
        }
        mavenLocal()
        gradlePluginPortal()
    }
}