import org.gradle.api.DefaultTask
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.Input
import org.gradle.api.tasks.InputFile
import org.gradle.api.tasks.OutputFile
import org.gradle.api.tasks.TaskAction

import java.nio.file.Path

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
        final configurationFile = new File(temporaryDir, "grub.cfg").tap {
            createNewFile()
            withReader { write(CreateMultibootRescue.cdrom_cfg) }
        }
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

        project.exec { commandLine command }
    }

    static String toUnixString(Path path)
    {
        return path.toString().replace('\\', '/');
    }
}