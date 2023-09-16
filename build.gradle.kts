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

tasks.wrapper.configure {
    gradleVersion = "8.0.2"
}