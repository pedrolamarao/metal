import org.gradle.api.file.RegularFile
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.process.CommandLineArgumentProvider
import java.io.File

class GrubConfigurationEntryEditor
{
    var name : String = ""

    val commands : MutableList<String> = mutableListOf()

    fun multiboot2 (path : String, vararg args : String) {
        commands.add( if (args.isEmpty()) "multiboot2 $path" else "multiboot2 $path ${args.joinToString(" ")}" )
    }

    fun module2 (path : String, vararg args : String) {
        commands.add( if (args.isEmpty()) "module2 $path" else "module2 $path ${args.joinToString(" ")}" )
    }

    override fun toString () = "menuentry $name {\r\n${commands.map{"$it\r\n"}.joinToString("")}}"
}

class GrubConfigurationEditor
{
    val options : MutableMap<String,String> = mutableMapOf()

    val entries : MutableList<GrubConfigurationEntryEditor> = mutableListOf()

    override fun toString () = options.map{(k,v) -> "$k=$v"}.joinToString("\r\n", "", "\r\n") +
        entries.joinToString("\r\n", "", "\r\n")
}

abstract class GrubMakeImageEditor : CommandLineArgumentProvider
{
    abstract val installModules : ListProperty<String>

    abstract val imageFile : RegularFileProperty

    abstract val sources : ListProperty<String>

    abstract val platform : Property<String>

    fun source ( path : String, file : File)
    {
        sources.add("${path}=${file}")
    }

    fun source ( path : String, file : RegularFile)
    {
        source(path, file.asFile)
    }

    fun source ( path : String, file : RegularFileProperty)
    {
        source(path, file.get().asFile)
    }

    override fun asArguments (): Iterable<String>?
    {
        return build()
    }

    fun build () : List<String>
    {
        val args = mutableListOf<String>()
        args += arrayOf("-O", platform.get())
        args += arrayOf("-o", imageFile.get().toString())
        args += "--themes="
        args += "--fonts="
        args += "--locales="
        args += "--install-modules=${installModules.get().joinToString(separator = " ")}"
        args += sources.get()
        args += "-v"
        return args
    }
}