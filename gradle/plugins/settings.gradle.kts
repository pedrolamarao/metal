dependencyResolutionManagement {
    repositories {
        maven() {
            name = "Nokee Release Repository"
            url = uri("https://repo.nokee.dev/release")
            mavenContent {
                includeGroupByRegex("dev\\.nokee.*")
                includeGroupByRegex("dev\\.gradleplugins.*")
            }
        }
        maven() {
            name = "Nokee Snapshot Repository"
            url = uri("https://repo.nokee.dev/snapshot")
            mavenContent {
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