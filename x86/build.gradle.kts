plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.cxx")
    id("br.dev.pedrolamarao.metal.ixx")
}

group = "br.dev.pedrolamarao.metal.x86"

dependencies {
    api(project(":psys"))
}

metal {
    compileOptions = listOf("-fasm-blocks","-g","-std=c++20")
}

// TODO: enhance Gradle Metal with conventional test application

dependencies {
    implementation(project(":googletest"))
}

metal {
    cxx {
        create("test") {
            includable( cpp.named("main").map { it.sources.sourceDirectories } )
            importable( ixx.named("main").map { it.outputDirectory } )
        }
    }
    applications {
        create("test") {
            linkOptions = listOf("-fuse-ld=lld","-static")
            source( cxx.named("main").map { it.outputs } )
            source( cxx.named("test").map { it.outputs } )
        }
    }
}

tasks.named("compile-test-cxx") { dependsOn("compile-main-ixx") }

tasks.register<Exec>("run-test") {
    group = "metal"
    val linkTask = metal.applications.named("test").flatMap { it.linkTask }
    dependsOn(linkTask)
    executable( linkTask.flatMap{ it.output }.get() )
}

tasks.create("test") {
    group = "verification"
    dependsOn("run-test")
}

tasks.check.configure {
    dependsOn("test")
}

// TODO: enhance Gradle Metal with target includes/excludes support
afterEvaluate {
    val targets = listOf("default")
    val targetEnabled = providers.gradleProperty("metal.target").orElse("default").map{ targets.contains(it) }
    tasks.named("compile-test-cxx") { enabled = targetEnabled.get() }
    tasks.named("link-test") { enabled = targetEnabled.get() }
    tasks.named("run-test") { enabled = targetEnabled.get() }
    tasks.named("test") { enabled = targetEnabled.get() }
}