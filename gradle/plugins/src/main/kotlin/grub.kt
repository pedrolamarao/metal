import org.gradle.api.file.RegularFile
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.process.CommandLineArgumentProvider
import java.io.File

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