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

abstract class UefiCreateImageTask : DefaultTask()
{
    @get:InputFile
    abstract val inputFile : RegularFileProperty

    @get:Input
    abstract val mformat : Property<File>

    @get:Input
    abstract val mmd : Property<File>

    @get:Input
    abstract val mcopy : Property<File>

    @get:OutputFile
    abstract val outputFile : RegularFileProperty

    @get:Inject
    abstract val execOperations : ExecOperations

    init
    {
        val tools = project.rootProject.extensions["tools"] as java.util.Properties
        val mtools = tools["br.dev.pedrolamarao.psys.mtools.path"]

        mformat.convention( project.file("${mtools}/mformat") )
        mmd.convention( project.file("${mtools}/mmd") )
        mcopy.convention( project.file("${mtools}/mcopy") )
    }

    @TaskAction
    fun action ()
    {
        logger.info("${project.path}:${this.name}: inputFile = ${inputFile.get()}")
        project.mkdir(inputFile.get().asFile.parent)
        execOperations.exec {
            commandLine( arrayOf(mformat.get().toString(), "-C", "-f", "1440", "-i", outputFile.get().toString(), "::") )
            standardOutput = File(temporaryDir, "mformat.out.txt").outputStream()
            errorOutput = File(temporaryDir, "mformat.err.txt").outputStream()
        }
        execOperations.exec {
            commandLine( arrayOf(mmd.get().toString(), "-i", outputFile.get().toString(), "::/EFI", "::/EFI/BOOT") )
            standardOutput = File(temporaryDir, "mmd.out.txt").outputStream()
            errorOutput = File(temporaryDir, "mmd.err.txt").outputStream()
        }
        execOperations.exec {
            commandLine( arrayOf(mcopy.get().toString(), "-i", outputFile.get().toString(), inputFile.get().toString(), "::/EFI/BOOT/BOOTX64.EFI") )
            standardOutput = File(temporaryDir, "mcopy.out.txt").outputStream()
            errorOutput = File(temporaryDir, "mcopy.err.txt").outputStream()
        }
    }
}

abstract class RunUefi : DefaultTask()
{
    @get:InputFile
    abstract val imageFile : RegularFileProperty

    @get:Input
    abstract val ovmfImage : Property<File>

    @get:Input
    abstract val qemuExecutable : Property<File>

    @get:Inject
    abstract val execOperations : ExecOperations

    init
    {
        val tools = project.rootProject.extensions["tools"] as java.util.Properties
        val ovmf = tools["br.dev.pedrolamarao.psys.ovmf.path"]
        val qemu = tools["br.dev.pedrolamarao.psys.qemu.path"]

        ovmfImage.convention( project.file("${ovmf}/DEBUGX64_OVMF.fd") )
        qemuExecutable.convention( project.file("${qemu}/qemu-system-x86_64") )
    }

    @TaskAction fun action ()
    {
        val imageQemuDrive = project.objects.newInstance<QemuDriveEditor>()
        imageQemuDrive.type.set("ide")
        imageQemuDrive.format.set("raw")
        imageQemuDrive.file.set(imageFile)

        val qemuArgs = project.objects.newInstance<QemuSystemEditor>()
        qemuArgs.bios.set(ovmfImage.get())
        qemuArgs.drives.add("${imageQemuDrive}")
        qemuArgs.machine.set("q35")

        execOperations.exec {
            executable = qemuExecutable.get().toString()
            argumentProviders += qemuArgs
            standardOutput = File(temporaryDir, "qemu.out.txt").outputStream()
            errorOutput = File(temporaryDir, "qemu.err.txt").outputStream()
        }
    }
}