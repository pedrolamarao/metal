plugins {
    id("br.dev.pedrolamarao.metal.archive")
    id("br.dev.pedrolamarao.metal.cpp")
    id("br.dev.pedrolamarao.metal.cxx")
}

group = "br.dev.pedrolamarao.metal.elf"

dependencies {
    api(project(":psys"))
}

metal {
    compileOptions = listOf("-g","-std=c++20")
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
            source( cxx.named("test").map { it.outputs } )
        }
    }
}

tasks.register<Exec>("run-test") {
    dependsOn( metal.applications.named("test").flatMap { it.linkTask } )
    executable( metal.applications.named("test").flatMap { it.linkTask }.flatMap { it.output }.get() )
}

tasks.create("test") {
    group = "verification"
    dependsOn("run-test")
}

tasks.check.configure {
    dependsOn("test")
}