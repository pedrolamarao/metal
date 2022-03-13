plugins {
    base
}

val tools = java.util.Properties()
try { tools.load(java.io.FileReader(file("tools.properties"))) } catch (_: Exception) { }
ext["tools"] = tools
extensions.add("tools", tools)

allprojects {
    group = "br.dev.pedrolamarao.psys"
    version = "0.5.0-SNAPSHOT"
}

gradle.includedBuilds.forEach {
    project.tasks.assemble { dependsOn(it.task(":assemble")) }
    project.tasks.build { dependsOn(it.task(":build")) }
    project.tasks.check { dependsOn(it.task(":check")) }
    project.tasks.clean { dependsOn(it.task(":clean")) }
}