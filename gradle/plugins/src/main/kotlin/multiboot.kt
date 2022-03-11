import org.gradle.api.DefaultTask
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.Input
import org.gradle.api.tasks.InputFile
import org.gradle.api.tasks.OutputFile
import org.gradle.api.tasks.TaskAction
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