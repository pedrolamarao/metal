plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.cxx")
}

dependencies {
    api(project(":psys"))
}

metal {
    compileOptions = listOf("-std=c++20")
}

// ----

dependencies {
    implementation(project(":googletest"))
}

metal {
    cxx {
        create("test") {
            includable( cpp.named("main").map { it.sources.sourceDirectories } )
        }
    }
    applications {
        create("test") {
            linkOptions = listOf("-fuse-ld=lld","-static")
            source( cxx.named("test").map { it.outputs } )
        }
    }
}

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