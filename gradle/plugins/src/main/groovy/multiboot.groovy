import org.gradle.api.DefaultTask
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.Input
import org.gradle.api.tasks.InputFile
import org.gradle.api.tasks.Nested
import org.gradle.api.tasks.TaskAction
import org.gradle.workers.WorkerExecutor

import javax.inject.Inject
import java.time.Duration
import java.util.concurrent.ForkJoinPool
import java.util.concurrent.ThreadLocalRandom
import java.util.concurrent.TimeUnit

abstract class TestMultibootImage extends DefaultTask
{
    @InputFile abstract RegularFileProperty getExecutableFile ()

    @Input abstract Property<String> getGdbExecutable ()

    @InputFile abstract RegularFileProperty getImageFile ()

    @Nested abstract QemuCommandEditor getQemuArgs ()

    @Nested abstract Property<String> getQemuExecutable ()

    @Inject abstract WorkerExecutor getWorkers ()

    TestMultibootImage ()
    {
        final gdbPath = project.rootProject.ext.tools['br.dev.pedrolamarao.psys.gdb.path']
        final qemuPath = project.rootProject.ext.tools['br.dev.pedrolamarao.psys.qemu.path']

        gdbExecutable.convention gdbPath != null ? "${gdbPath}/gdb" : 'gdb'
        qemuExecutable.convention qemuPath != null ? "${qemuPath}/qemu-system-i386" : 'qemu-system-i386'
    }

    @TaskAction void action ()
    {
        logger.info "${project.path}:${this.name}: executableFile = ${executableFile.get()}"
        logger.info "${project.path}:${this.name}: imageFile = ${imageFile.get()}"

        final gdb = project.gdb.exec {
            command = "${gdbExecutable.get()}"
            debugOutput = new File(temporaryDir, 'gdb.mi.txt').newOutputStream()
            timeLimit = Duration.ofSeconds(10)
        }

        final port = ThreadLocalRandom.current().nextInt(20000, 40000)

        qemuArgs.with {
            display.set 'none'
            kernel.set imageFile
            it.gdb.set "tcp:localhost:${port}"
            machine.set 'q35'
            rtc {
                base = '2020-07-24T22:46:00'
            }
            characterDriver 'file', {
                options.put 'path', new File(temporaryDir, 'qemu.debugcon.txt').toString()
                options.put 'id', 'debugcon'
            }
            debugConsole.set 'chardev:debugcon'
            stop.set true
        }

        final List<String> qemuCommand = []
        qemuCommand.add qemuExecutable.get()
        qemuCommand.addAll qemuArgs.build()

        final qemuProcess = new ProcessBuilder()
            .command( qemuCommand )
            .redirectError( new File(temporaryDir, 'qemu.error.txt') )
            .redirectOutput( new File(temporaryDir, 'qemu.out.txt'))
            .start()

        // Handle break at _test_start

        gdb.handle { message -> handleTestStart(gdb, message) }

        // Handle break at _test_finish

        gdb.handle { message -> handleTestFinish(gdb, message) }

        // Handle watch on _test_control

        gdb.handle { message -> handleTestControl(gdb, message) }

        // Handle watch on _test_debug

        gdb.handle { message -> handleTestDebug(gdb, message) }

        try
        {
            gdb.gdbSet 'mi-async', 'on', {}
            gdb.gdbSet 'confirm', 'off', {}
            gdb.gdbSet 'osabi', 'none', {}
            gdb.gdbSet 'output-radix', '10', {}
            gdb.fileExecAndSymbols executableFile.get().toString().replace('\\', '/'), {}
            gdb.targetSelectTcp 'localhost', "${port}", {}
            gdb.breakInsertAtSymbol '_test_start', {}
            gdb.execContinue {}
            final complete = qemuProcess.waitFor 5, TimeUnit.SECONDS
            if (! complete) { logger.error "${project.path}:${this.name}: [FAILURE]: timeout" }
        }
        finally
        {
            qemuProcess.destroyForcibly()
            gdb.close()
        }

        logger.info "${project.path}:${this.name}: QEMU completed with status = ${qemuProcess.exitValue()}"
        logger.info "${project.path}:${this.name}: GDB completed with status = ${gdb.exitValue()}"
    }

    void handleTestStart (final gdb, final message)
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
        if (func != '_test_start') { return }
        logger.info "${project.path}:${this.name}: [START]"
        ForkJoinPool.commonPool().submit {
            gdb.breakInsertAtSymbol '_test_finish', {}
            gdb.breakWatch '_test_control', {}
            gdb.breakWatch '_test_debug', {}
            gdb.execContinue {}
        }
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
            logger.error "${project.path}:${this.name}: [FAILURE]: ${_old}"
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