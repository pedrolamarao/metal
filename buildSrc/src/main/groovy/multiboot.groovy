import org.gradle.api.DefaultTask
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.Input
import org.gradle.api.tasks.InputFile
import org.gradle.api.tasks.OutputFile
import org.gradle.api.tasks.TaskAction
import org.gradle.workers.WorkerExecutor

import javax.inject.Inject
import java.nio.file.Path
import java.time.Duration
import java.util.concurrent.ForkJoinPool
import java.util.concurrent.TimeUnit

abstract class CreateMultibootRescue extends DefaultTask
{
    @InputFile abstract RegularFileProperty getInputFile ()

    @Input abstract Property<String> getMkrescue ()

    @OutputFile abstract RegularFileProperty getOutputFile ()

    @Input abstract ListProperty<String> getPrologue ()

    CreateMultibootRescue()
    {
        final layout = project.layout
        final providers = project.providers
        final tools = project.rootProject.ext.tools

        final grubPrologue = tools['br.dev.pedrolamarao.psys.grub.prologue']
        final grubPath = tools['br.dev.pedrolamarao.psys.grub.path']

        prologue.convention "${grubPrologue}".split(' ').collect()

        mkrescue.convention "${grubPath}/grub-mkrescue"

        outputFile.convention = inputFile.flatMap { layout.buildDirectory.file("grub/bin/${it.asFile.name}/rescue/image") }
    }

    private static final String cdrom_cfg =
        "default=0\r\n" +
        "timeout=0\r\n" +
        "\r\n" +
        "menuentry psys {\r\n" +
        "   multiboot2 (cd)/program\r\n" +
        "}\r\n"

    @TaskAction void action ()
    {
        final configurationFile = new File(temporaryDir, 'grub.cfg').tap {
            createNewFile()
            withReader { write(CreateMultibootRescue.cdrom_cfg) }
        }
        final stderrFile = new File(temporaryDir, 'err.txt').tap { createNewFile() }
        final stdoutFile = new File(temporaryDir, 'out.txt').tap { createNewFile() }
        final inputFile = this.inputFile.get().asFile
        final outputFile = this.outputFile.get().asFile

        final projectPath = project.projectDir.toPath()
        final configurationPath = projectPath.relativize( configurationFile.toPath() )
        final inputPath = projectPath.relativize( inputFile.toPath() )
        final outputPath = projectPath.relativize( outputFile.toPath() )

        final command = []
        command.addAll prologue.get()
        command.add mkrescue.get()
        command.addAll '-o', toUnixString(outputPath)
        command.add "/boot/grub/grub.cfg=" + toUnixString(configurationPath)
        command.add "/program=" + toUnixString(inputPath)

        project.exec {
            commandLine command
            errorOutput = new File(temporaryDir, 'err.txt').tap{createNewFile()}.newOutputStream()
            standardOutput = new File(temporaryDir, 'out.txt').tap{createNewFile()}.newOutputStream()
        }
    }

    static String toUnixString(Path path)
    {
        return path.toString().replace('\\', '/');
    }
}

abstract class RunMultibootRescue extends DefaultTask
{
    @InputFile abstract RegularFileProperty getImageFile ()

    @Input abstract RegularFileProperty getQemuExecutable ()

    RunMultibootRescue ()
    {
        final layout = project.layout
        final providers = project.providers

        final qemu = project.rootProject.ext.tools['br.dev.pedrolamarao.psys.qemu.path']

        qemuExecutable.convention = providers.provider { qemu + '/qemu-system-i386' }
            .map { project.file(it) }
            .tap { layout.file(it) }
    }

    @TaskAction void action ()
    {
        final imageQemuDrive = project.objects.newInstance(QemuDriveWriter)
        imageQemuDrive.media = 'cdrom'
        imageQemuDrive.file = imageFile

        final qemuCommand = project.objects.newInstance(QemuCommandBuilder)
        qemuCommand.command = qemuExecutable
        qemuCommand.drives.add "${imageQemuDrive}"
        qemuCommand.gdb = 'tcp:localhost:12345'
        qemuCommand.machine = 'q35'
        qemuCommand.stop = true

        project.exec { commandLine qemuCommand.build() }
    }
}

abstract class TestMultibootRescue extends DefaultTask
{
    @InputFile abstract RegularFileProperty getExecutableFile ()

    @Input abstract RegularFileProperty getGdbExecutable ()

    @InputFile abstract RegularFileProperty getImageFile ()

    @Input abstract RegularFileProperty getQemuExecutable ()

    @Inject abstract WorkerExecutor getWorkers ()

    TestMultibootRescue ()
    {
        final layout = project.layout
        final providers = project.providers

        final gdbPath = project.rootProject.ext.tools['br.dev.pedrolamarao.psys.gdb.path']
        final qemuPath = project.rootProject.ext.tools['br.dev.pedrolamarao.psys.qemu.path']

        gdbExecutable.convention = providers.provider { gdbPath + '/gdb' }
            .map { project.file(it) }
            .tap { layout.file(it) }

        qemuExecutable.convention = providers.provider { qemuPath + '/qemu-system-i386' }
            .map { project.file(it) }
            .tap { layout.file(it) }
    }

    @TaskAction void action ()
    {
        logger.info "${project.path}:${this.name}: executableFile = ${executableFile.get()}"
        logger.info "${project.path}:${this.name}: imageFile = ${imageFile.get()}"

        final gdb = project.gdb.exec {
            command = "${gdbExecutable.get()}"
            timeLimit = Duration.ofSeconds(10)
        }

        final imageQemuDrive = project.objects.newInstance(QemuDriveWriter)
        imageQemuDrive.media = 'cdrom'
        imageQemuDrive.file = imageFile

        final qemuCommand = project.objects.newInstance(QemuCommandBuilder)
        qemuCommand.command = qemuExecutable
        qemuCommand.display = 'none'
        qemuCommand.drives.add "${imageQemuDrive}"
        qemuCommand.gdb = 'tcp:localhost:12345'
        qemuCommand.machine = 'q35'
        qemuCommand.stop = true

        final qemu = new ProcessBuilder()
            .command( qemuCommand.build() )
            .start()

        // Handle breakpoint-hit on _test_finish

        gdb.handle { message ->
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

        // Handle watchpoint-trigger on _test_control

        gdb.handle { message ->
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
}