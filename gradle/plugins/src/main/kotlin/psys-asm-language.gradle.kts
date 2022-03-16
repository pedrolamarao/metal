import dev.nokee.platform.cpp.CppLibrary
import dev.nokee.platform.nativebase.StaticLibraryBinary
import dev.nokee.platform.nativebase.tasks.internal.CreateStaticLibraryTask

abstract class AsmExtension
{
    abstract val source : ConfigurableFileCollection
}

val asm = project.extensions.create<AsmExtension>("asm")

project.extensions.configure<CppLibrary> {
    binaries.configureEach {
        if (this is StaticLibraryBinary) {
            val createTask = createTask.get()
            if (createTask is CreateStaticLibraryTask) {
                asm.source.asFileTree.forEach { asmSource ->
                    val asmTask = project.tasks.register<Assemble>("asm-${name}-${asmSource.hashCode()}") {
                        assemblerArgs = emptyList()
                        objectFileDir = file("${buildDir}/asm/main")
                        source(asmSource)
                        targetPlatform.set(createTask.targetPlatform)
                        toolChain.set(createTask.toolChain)
                    }
                    createTask.source(asmTask.get().outputs.files.asFileTree)
                }
                createTask.doLast { createTask.source.files.forEach { logger.lifecycle("${name}: ${it}") } }
            }
        }
    }
}