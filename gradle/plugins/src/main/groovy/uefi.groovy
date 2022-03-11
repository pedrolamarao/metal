import org.gradle.api.DefaultTask
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.tasks.Input
import org.gradle.api.tasks.InputFile
import org.gradle.api.tasks.OutputFile
import org.gradle.api.tasks.TaskAction
import org.gradle.process.ExecOperations

import javax.inject.Inject

abstract class CreateUefi extends DefaultTask
{
    @InputFile abstract RegularFileProperty getInputFile ()

    @Input abstract RegularFileProperty getMformat ()

    @Input abstract RegularFileProperty getMmd ()

    @Input abstract RegularFileProperty getMcopy ()

    @OutputFile abstract RegularFileProperty getOutputFile ()

    @Inject abstract ExecOperations getExecOperations ()

    CreateUefi ()
    {
        final layout = project.layout
        final providers = project.providers
        final mtools = project.rootProject.ext.tools['br.dev.pedrolamarao.psys.mtools.path']

        mformat.convention = providers.provider { mtools + '/mformat' }
            .map { project.file(it) }
            .tap { layout.file(it) }

        mmd.convention = providers.provider { mtools + '/mmd' }
            .map { project.file(it) }
            .tap { layout.file(it) }

        mcopy.convention = providers.provider { mtools + '/mcopy' }
            .map { project.file(it) }
            .tap { layout.file(it) }
    }

    @TaskAction void action ()
    {
        logger.info "${project.path}:${this.name}: inputFile = ${inputFile.get()}"
        project.mkdir inputFile.get().asFile.parent
        execOperations.exec {
            commandLine mformat.get(), '-C', '-f', '1440', '-i', outputFile.get(), '::'
            standardOutput = new File(temporaryDir, 'mformat.out.txt').newOutputStream()
            errorOutput = new File(temporaryDir, 'mformat.err.txt').newOutputStream()
        }
        execOperations.exec {
            commandLine mmd.get(), '-i', outputFile.get(), '::/EFI', '::/EFI/BOOT'
            standardOutput = new File(temporaryDir, 'mmd.out.txt').newOutputStream()
            errorOutput = new File(temporaryDir, 'mmd.err.txt').newOutputStream()
        }
        execOperations.exec {
            commandLine mcopy.get(), '-i', outputFile.get(), inputFile.get(), '::/EFI/BOOT/BOOTX64.EFI'
            standardOutput = new File(temporaryDir, 'mcopy.out.txt').newOutputStream()
            errorOutput = new File(temporaryDir, 'mcopy.err.txt').newOutputStream()
        }
    }
}

abstract class RunUefi extends DefaultTask
{
    @InputFile abstract RegularFileProperty getImageFile ()

    @Input abstract RegularFileProperty getOvmfImage ()

    @Input abstract RegularFileProperty getQemuExecutable ()

    @Inject abstract ExecOperations getExecOperations ()

    RunUefi ()
    {
        final layout = project.layout
        final providers = project.providers
        final ovmf = project.rootProject.ext.tools['br.dev.pedrolamarao.psys.ovmf.path']
        final qemu = project.rootProject.ext.tools['br.dev.pedrolamarao.psys.qemu.path']

        ovmfImage.convention = providers.provider { ovmf + '/DEBUGX64_OVMF.fd' }
            .map { project.file(it) }
            .tap { layout.file(it) }

        qemuExecutable.convention = providers.provider { qemu + '/qemu-system-x86_64' }
            .map { project.file(it) }
            .tap { layout.file(it) }
    }

    @TaskAction void action ()
    {
        final imageQemuDrive = project.objects.newInstance(QemuDriveWriter)
        imageQemuDrive.type = 'ide'
        imageQemuDrive.format = 'raw'
        imageQemuDrive.file = imageFile

        final qemuArgs = project.objects.newInstance(QemuCommandEditor)
        qemuArgs.bios = ovmfImage
        qemuArgs.drives.add "${imageQemuDrive}"
        qemuArgs.machine = 'q35'

        execOperations.exec {
            executable qemuExecutable.get()
            args qemuArgs.build()
            standardOutput = new File(temporaryDir, 'qemu.out.txt').newOutputStream()
            errorOutput = new File(temporaryDir, 'qemu.err.txt').newOutputStream()
        }
    }
}