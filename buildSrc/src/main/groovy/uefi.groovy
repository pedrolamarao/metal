import org.gradle.api.DefaultTask
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.tasks.Input
import org.gradle.api.tasks.InputFile
import org.gradle.api.tasks.OutputFile
import org.gradle.api.tasks.TaskAction

abstract class CreateUefi extends DefaultTask
{
    @InputFile abstract RegularFileProperty getInputFile ()

    @Input abstract RegularFileProperty getMformat ()

    @Input abstract RegularFileProperty getMmd ()

    @Input abstract RegularFileProperty getMcopy ()

    @OutputFile abstract RegularFileProperty getOutputFile ()

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
        logger.info "${project.path}${project.name}${this.name}: inputFile = ${inputFile.get()}"
        project.mkdir inputFile.get().asFile.parent
        project.exec { commandLine mformat.get(), '-C', '-f', '1440', '-i', outputFile.get(), '::' }
        project.exec { commandLine mmd.get(), '-i', outputFile.get(), '::/EFI' }
        project.exec { commandLine mmd.get(), '-i', outputFile.get(), '::/EFI/BOOT' }
        project.exec { commandLine mcopy.get(), '-i', outputFile.get(), inputFile.get(), '::/EFI/BOOT/BOOTX64.EFI' }
    }
}

abstract class RunUefi extends DefaultTask
{
    @InputFile abstract RegularFileProperty getImageFile ()

    @Input abstract RegularFileProperty getOvmfImage ()

    @Input abstract RegularFileProperty getQemuExecutable ()

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

        final qemuCommand = project.objects.newInstance(QemuCommandBuilder)
        qemuCommand.command = qemuExecutable
        qemuCommand.bios = ovmfImage
        qemuCommand.drives.add "${imageQemuDrive}"
        qemuCommand.machine = 'q35'

        project.exec { commandLine qemuCommand.build() }
    }
}
