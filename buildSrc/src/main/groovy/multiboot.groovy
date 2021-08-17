import org.gradle.api.DefaultTask
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.tasks.Input
import org.gradle.api.tasks.InputFile
import org.gradle.api.tasks.OutputFile
import org.gradle.api.tasks.TaskAction
import org.gradle.workers.WorkerExecutor

import javax.inject.Inject
import java.time.Duration
import java.util.concurrent.ForkJoinPool
import java.util.concurrent.TimeUnit

abstract class CreateMultibootImage extends DefaultTask
{
    @InputFile abstract RegularFileProperty getInputFile ()

    @Input abstract RegularFileProperty getCommand ()

    @OutputFile abstract RegularFileProperty getOutputFile ()

    CreateMultibootImage ()
    {
        final layout = project.layout
        final providers = project.providers
        final tools = project.rootProject.ext.tools

        final grubPath = tools['br.dev.pedrolamarao.psys.grub.path']

        command.convention = providers.provider { new File("${grubPath}/grub-mkstandalone") }

        outputFile.convention = inputFile.flatMap { layout.buildDirectory.file("grub/standalone/${it.asFile.name}/image") }
    }

    static final String grub_cfg =
        "default=0\r\n" +
        "timeout=0\r\n" +
        "\r\n" +
        "menuentry psys {\r\n" +
        "   multiboot2 (memdisk)/program\r\n" +
        "}\r\n"

    @TaskAction void action ()
    {
        final configurationFile = new File(temporaryDir, 'grub.cfg').tap {
            createNewFile()
            withReader { write(grub_cfg) }
        }

        final builder = project.objects.newInstance(GrubMakeImageBuilder)
        builder.command = command
        builder.platform = 'i386-pc'
        builder.imageFile = outputFile
        builder.installModules = [ 'configfile', 'memdisk', 'multiboot2', 'normal' ]
        builder.source '/boot/grub/grub.cfg', configurationFile
        builder.source '/program', inputFile

        project.exec {
            commandLine builder.build()
            errorOutput = new File(temporaryDir, 'err.txt').tap{createNewFile()}.newOutputStream()
            standardOutput = new File(temporaryDir, 'out.txt').tap{createNewFile()}.newOutputStream()
        }
    }
}

abstract class RunMultibootImage extends DefaultTask
{
    @Input abstract RegularFileProperty getCommand ()

    @InputFile abstract RegularFileProperty getImageFile ()

    RunMultibootImage ()
    {
        final layout = project.layout
        final providers = project.providers

        final qemu = project.rootProject.ext.tools['br.dev.pedrolamarao.psys.qemu.path']

        command.convention = providers.provider { new File("${qemu}/qemu-system-i386") }
    }

    @TaskAction void action ()
    {
        final qemuCommand = project.objects.newInstance(QemuCommandBuilder)
        qemuCommand.command = command
        qemuCommand.debugFile = new File(temporaryDir, 'qemu.debug.txt')
        qemuCommand.kernel = imageFile
        qemuCommand.gdb = 'tcp:localhost:12345'
        qemuCommand.machine = 'q35'
        qemuCommand.stop = true

        project.exec { commandLine qemuCommand.build() }
    }
}

abstract class TestMultibootImage extends DefaultTask
{
    @InputFile abstract RegularFileProperty getExecutableFile ()

    @Input abstract RegularFileProperty getGdbExecutable ()

    @InputFile abstract RegularFileProperty getImageFile ()

    @Input abstract RegularFileProperty getQemuExecutable ()

    @Inject abstract WorkerExecutor getWorkers ()

    TestMultibootImage ()
    {
        final layout = project.layout
        final providers = project.providers

        final gdbPath = project.rootProject.ext.tools['br.dev.pedrolamarao.psys.gdb.path']
        final qemuPath = project.rootProject.ext.tools['br.dev.pedrolamarao.psys.qemu.path']

        gdbExecutable.convention = providers.provider { new File("${gdbPath}/gdb")}
        qemuExecutable.convention = providers.provider { new File("${qemuPath}/qemu-system-i386") }
    }

    @TaskAction void action ()
    {
        logger.info "${project.path}:${this.name}: executableFile = ${executableFile.get()}"
        logger.info "${project.path}:${this.name}: imageFile = ${imageFile.get()}"

        final gdb = project.gdb.exec {
            command = "${gdbExecutable.get()}"
            timeLimit = Duration.ofSeconds(10)
        }

        final qemuCommand = project.objects.newInstance(QemuCommandBuilder).tap {
            command = qemuExecutable
            display = 'none'
            kernel = imageFile
            it.gdb = 'tcp:localhost:12345'
            machine = 'q35'
            rtc {
                base = '2020-07-24T22:46:00'
            }
            stop = true
        }

        final qemu = new ProcessBuilder()
            .command( qemuCommand.build() )
            .start()

        // Handle breakpoint-hit on _test_finish

        gdb.handle { message -> handleTestFinish(gdb, message) }

        // Handle watchpoint-trigger on _test_control

        gdb.handle { message -> handleTestControl(gdb, message) }

        // Handle watchpoint-trigger on _test_debug

        gdb.handle { message -> handleTestDebug(gdb, message) }

        try
        {
            gdb.gdbSet 'confirm', 'off', {}
            gdb.gdbSet 'mi-async', 'on', {}
            gdb.gdbSet 'osabi', 'none', {}
            gdb.gdbSet 'output-radix', '10', {}
            gdb.fileExecAndSymbols executableFile.get().toString().replace('\\', '/'), {}
            gdb.targetSelectTcp 'localhost', '12345', {}
            gdb.breakInsertAtSymbol '_test_finish', { it.hardware() }
            gdb.breakWatch '_test_control', {}
            gdb.breakWatch '_test_debug', {}
            gdb.execContinue {}
            final complete = qemu.waitFor 5, TimeUnit.SECONDS
            if (! complete) { logger.lifecycle "${project.path}:${this.name}: [FAILURE]: timeout" }
        }
        finally
        {
            qemu.destroyForcibly()
            gdb.close()
        }

        logger.info "${project.path}:${this.name}: QEMU completed with status = ${qemu.exitValue()}"
        logger.info "${project.path}:${this.name}: GDB completed with status = ${gdb.exitValue()}"
    }

    void handleTestControl (final gdb, final message)
    {
        // #XXX: appropriately filter on GdbMiRecord!
        final content = message.content
        if (content instanceof String) { return }
        final properties = content.properties();
        final reason = properties.get('reason', String)
        if (reason != 'watchpoint-trigger') { return }
        final wpt = properties.get('wpt', Object)
        if (wpt == null) { return }
        final exp = wpt.get('exp', String)
        if (exp != '_test_control') { return }
        final value = properties.get('value', Object)
        final _old = value.get('old', String)
        final _new = value.get('new', String)
        if (_old == null) { return }
        if (_new == null) { return }
        logger.info "${project.path}:${this.name}: [CONTROL]: ${_old} -> ${_new}"
        if (_old == '0') {
            logger.info "${project.path}:${this.name}: [ENTER]: ${_new}"
        }
        else if (_new == '0') {
            logger.lifecycle "${project.path}:${this.name}: [FAILURE]: ${_old}"
        }
        else {
            logger.lifecycle "${project.path}:${this.name}: [SUCCESS]: ${_old}"
            logger.info "${project.path}:${this.name}: [ENTER]: ${_new}"
        }
        ForkJoinPool.commonPool().submit { gdb.execContinue {} }
    }

    void handleTestDebug (final gdb, final message)
    {
        // #XXX: appropriately filter on GdbMiRecord!
        final content = message.content
        if (content instanceof String) { return }
        final properties = content.properties();
        final reason = properties.get('reason', String)
        if (reason != 'watchpoint-trigger') { return }
        final wpt = properties.get('wpt', Object)
        if (wpt == null) { return }
        final exp = wpt.get('exp', String)
        if (exp != '_test_debug') { return }
        final value = properties.get('value', Object)
        final _old = value.get('old', String)
        final _new = value.get('new', String)
        if (_old == null) { return }
        if (_new == null) { return }
        logger.info "${project.path}:${this.name}: [DEBUG]: ${_old} -> ${_new}"
        ForkJoinPool.commonPool().submit { gdb.execContinue {} }
    }

    void handleTestFinish (final gdb, final message)
    {
        // #XXX: appropriately filter on GdbMiRecord!
        final content = message.content
        if (content instanceof String) { return }
        final properties = content.properties();
        final reason = properties.get('reason', String)
        if (reason != 'breakpoint-hit') { return }
        final frame = properties.get('frame', Object)
        if (frame == null) { return }
        final func = frame.get('func', String)
        if (func != '_test_finish') { return }
        logger.info "${project.path}:${this.name}: [FINISH]"
        ForkJoinPool.commonPool().submit {
            gdb.interpreterExec 'mi', 'kill'
            gdb.gdbExit {}
        }
    }
}