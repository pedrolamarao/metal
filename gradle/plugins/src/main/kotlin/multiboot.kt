import org.gradle.api.DefaultTask
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.*
import org.gradle.kotlin.dsl.get
import org.gradle.kotlin.dsl.newInstance
import org.gradle.process.ExecOperations
import java.io.File
import javax.inject.Inject

abstract class MultibootCreateImageTask : DefaultTask()
{
    @get:InputFile
    abstract val inputFile: RegularFileProperty

    @get:Input
    abstract val command: Property<String>

    @get:OutputFile
    abstract val outputFile: RegularFileProperty

    @get:Inject
    abstract val execOperations: ExecOperations

    init
    {
        val layout = project.layout
        val tools = project.rootProject.extensions["tools"] as java.util.Properties
        val grubPath = tools["br.dev.pedrolamarao.psys.grub.path"]
        command.convention( if (grubPath != null) "${grubPath}/grub-mkstandalone" else "grub-mkstandalone" )
        outputFile.convention( inputFile.flatMap { layout.buildDirectory.file("grub/standalone/${it.asFile.name}/image") } )
    }

    val grub_cfg =
        "default=0\r\n" +
        "timeout=0\r\n" +
        "\r\n" +
        "menuentry psys {\r\n" +
        "   multiboot2 (memdisk)/program\r\n" +
        "}\r\n"

    @TaskAction
    fun action ()
    {
        val configurationFile = File(temporaryDir, "grub.cfg").apply {
            createNewFile()
            appendText(grub_cfg)
        }

        val builder = project.objects.newInstance<GrubMakeImageEditor>()
        builder.platform.set("i386-pc")
        builder.imageFile.set(outputFile)
        builder.installModules.addAll("configfile", "memdisk", "multiboot2", "normal")
        builder.source("/boot/grub/grub.cfg", configurationFile)
        builder.source("/program", inputFile)

        execOperations.exec {
            executable = command.get()
            argumentProviders += builder
            errorOutput = File(temporaryDir, "grub-mkstandalone.err.txt").outputStream()
            standardOutput = File(temporaryDir, "grub-mkstandalone.out.txt").outputStream()
        }
    }
}

abstract class MultibootRunImageTask : DefaultTask()
{
    @get:InputFile
    abstract val imageFile : RegularFileProperty

    @get:Nested
    abstract val qemuArgs : QemuSystemEditor

    @get:Nested
    abstract val qemuExecutable : Property<String>

    @get:Inject
    abstract val execOperations : ExecOperations

    init
    {
        val tools = project.rootProject.extensions["tools"] as java.util.Properties
        val path = tools["br.dev.pedrolamarao.psys.qemu.path"]
        qemuExecutable.convention( if (path != null) "${path}/qemu-system-i386" else "qemu-system-i386" )

        qemuArgs.debugConsole.convention("vc")
        qemuArgs.kernel.convention(imageFile)
        qemuArgs.gdb.convention("tcp:localhost:12345")
        qemuArgs.machine.convention("q35")
        qemuArgs.stop.convention(true)
    }

    @TaskAction
    fun action ()
    {
        execOperations.exec {
            executable = qemuExecutable.get()
            argumentProviders += qemuArgs
            errorOutput = File(temporaryDir, "qemu.err.txt").outputStream()
            standardOutput = File(temporaryDir, "qemu.out.txt").outputStream()
        }
    }
}