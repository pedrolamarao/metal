import br.dev.pedrolamarao.gdb.gradle.GdbExec
import br.dev.pedrolamarao.gdb.gradle.GdbExtension
import br.dev.pedrolamarao.gdb.mi.GdbMiMessage
import br.dev.pedrolamarao.gdb.mi.GdbMiProperties
import org.gradle.api.DefaultTask
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.*
import org.gradle.kotlin.dsl.get
import org.gradle.kotlin.dsl.newInstance
import org.gradle.process.ExecOperations
import org.gradle.workers.WorkerExecutor
import java.io.File
import java.time.Duration
import java.util.concurrent.ForkJoinPool
import java.util.concurrent.ThreadLocalRandom
import java.util.concurrent.TimeUnit
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

abstract class MultibootTestImageTask : DefaultTask()
{
    @get:InputFile
    abstract val executableFile : RegularFileProperty

    @get:Input
    abstract val gdbExecutable : Property<String>

    @get:InputFile
    abstract val imageFile : RegularFileProperty

    @get:Nested
    abstract val qemuArgs : QemuSystemEditor

    @get:Nested
    abstract val qemuExecutable : Property<String>

    @get:Inject
    abstract val workers : WorkerExecutor

    init
    {
        val tools = project.rootProject.extensions["tools"] as java.util.Properties
        val gdbPath = tools["br.dev.pedrolamarao.psys.gdb.path"]
        val qemuPath = tools["br.dev.pedrolamarao.psys.qemu.path"]

        gdbExecutable.convention( if (gdbPath != null) "${gdbPath}/gdb" else "gdb" )
        qemuExecutable.convention( if (qemuPath != null) "${qemuPath}/qemu-system-i386" else "qemu-system-i386" )
    }

    @TaskAction
    fun action ()
    {
        logger.info("${project.path}:${this.name}: executableFile = ${executableFile.get()}")
        logger.info("${project.path}:${this.name}: imageFile = ${imageFile.get()}")

        val port = ThreadLocalRandom.current().nextInt(20000, 40000)

        qemuArgs.apply {
            display.set("none")
            kernel.set(imageFile)
            this.gdb.set("tcp:localhost:${port}")
            machine.set("q35")
            rtc {
                base.set("2020-07-24T22:46:00")
            }
            characterDevice("file") {
                options.put("path", File(temporaryDir, "qemu.debugcon.txt").toString())
                options.put("id", "debugcon")
            }
            debugConsole.set("chardev:debugcon")
            stop.set(true)
        }

        val qemuCommand = mutableListOf<String>()
        qemuCommand += qemuExecutable.get()
        qemuCommand += qemuArgs.build()

        val qemuProcess = ProcessBuilder()
            .command(qemuCommand)
            .redirectError( File(temporaryDir, "qemu.error.txt") )
            .redirectOutput( File(temporaryDir, "qemu.out.txt") )
            .start()

        val gdb = (project.extensions["gdb"] as GdbExtension).exec {
            command.set(gdbExecutable)
            debugOutput.set(File(temporaryDir,"gdb.mi.txt").outputStream())
            timeLimit.set(Duration.ofSeconds(10))
        }

        gdb.handle { onTestStart(gdb, this) }
        gdb.handle { onTestControl(gdb, this) }
        gdb.handle { onTestFinish(gdb, this) }

        try
        {
            gdb.gdbSet("mi-async", "on") {}
            gdb.gdbSet("confirm", "off") {}
            gdb.gdbSet("osabi", "none") {}
            gdb.gdbSet("output-radix", "10") {}
            gdb.fileExecAndSymbols(executableFile.get().toString().replace("\\", "/")) {}
            gdb.targetSelectTcp("localhost", "${port}") {}
            gdb.breakInsertAtSymbol("_test_start") {}
            gdb.execContinue() {}
            val complete = qemuProcess.waitFor(5, TimeUnit.SECONDS)
            if (! complete) { logger.error("${project.path}:${this.name}: [FAILURE]: timeout") }
        }
        finally
        {
            qemuProcess.destroyForcibly()
            gdb.close()
        }

        logger.info("${project.path}:${this.name}: QEMU completed with status = ${qemuProcess.exitValue()}")
        logger.info("${project.path}:${this.name}: GDB completed with status = ${gdb.exitValue()}")
    }

    private fun onTestStart (gdb : GdbExec, message : GdbMiMessage)
    {
        if (message !is GdbMiMessage.RecordMessage) return
        val properties = message.content().properties()
        if (properties.get("reason", String::class.java) != "breakpoint-hit") return
        val frame = properties.get("frame", GdbMiProperties::class.java) ?: return
        if (frame.get("func", String::class.java) != "_test_start") return
        logger.info("${project.path}:${this.name}: [START]")
        ForkJoinPool.commonPool().submit {
            gdb.breakInsertAtSymbol("_test_finish") {}
            gdb.breakWatch("_test_control") {}
            gdb.breakWatch("_test_debug") {}
            gdb.execContinue {}
        }
    }

    fun onTestControl (gdb : GdbExec, message : GdbMiMessage)
    {
        if (message !is GdbMiMessage.RecordMessage) return
        val properties = message.content().properties()
        if (properties.get("reason", String::class.java) != "watchpoint-trigger") return
        val wpt = properties.get("wpt", GdbMiProperties::class.java) ?: return
        if (wpt.get("exp", String::class.java) != "_test_control") return
        val value = properties.get("value", GdbMiProperties::class.java) ?: return
        val old = value.get("old", String::class.java) ?: return
        val new = value.get("new", String::class.java) ?: return
        logger.info("${project.path}:${this.name}: [CONTROL]: ${old} -> ${new}")
        if (old == "0") {
            logger.info("${project.path}:${this.name}: [ENTER]: ${new}")
        }
        else if (new == "0") {
            logger.error("${project.path}:${this.name}: [FAILURE]: ${old}")
        }
        else {
            logger.lifecycle("${project.path}:${this.name}: [SUCCESS]: ${old}")
            logger.info("${project.path}:${this.name}: [ENTER]: ${new}")
        }
        ForkJoinPool.commonPool().submit { gdb.execContinue {} }
    }

    private fun onTestFinish (gdb : GdbExec, message : GdbMiMessage)
    {
        if (message !is GdbMiMessage.RecordMessage) return
        val properties = message.content().properties()
        if (properties.get("reason", String::class.java) != "breakpoint-hit") return
        val frame = properties.get("frame", GdbMiProperties::class.java) ?: return
        if (frame.get("func", String::class.java) != "_test_finish") return
        logger.info("${project.path}:${this.name}: [FINISH]")
        ForkJoinPool.commonPool().submit {
            gdb.interpreterExec("mi", "kill")
            gdb.gdbExit() {}
        }
    }
}