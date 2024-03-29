import org.gradle.api.Action
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.MapProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.Input
import org.gradle.api.tasks.InputFile
import org.gradle.api.tasks.Optional
import org.gradle.kotlin.dsl.newInstance
import org.gradle.process.CommandLineArgumentProvider
import javax.inject.Inject

private fun <T> ifPresent (property : Property<T>, action : Action<T>)
{
    val value = if (property.isPresent) property.get() else null;
    if (value != null) action.execute(value)
}

abstract class QemuDeviceEditor
{
    abstract val options : MapProperty<String, String>

    abstract val type : Property<String>

    override fun toString () : String
    {
        val list = mutableListOf<String>()
        list += type.get()
        options.get().forEach { (key, value) -> list += "${key}=${value}" }
        return list.joinToString(",")
    }
}

abstract class QemuDriveEditor
{
    abstract val file : RegularFileProperty

    abstract val format : Property<String>

    abstract val media : Property<String>

    abstract val readOnly : Property<Boolean>

    abstract val type : Property<String>

    override fun toString () : String
    {
        val list = mutableListOf<String>()
        ifPresent(type) { list += "if=${this}" }
        ifPresent(format) { list += "format=${this}" }
        ifPresent(media) { list += "media=${this}" }
        ifPresent(readOnly) { list += "readonly=${this}" }
        ifPresent(file) { list += "file=${this}" }
        return list.joinToString(",")
    }
}

abstract class QemuRtcEditor
{
    abstract val base : Property<String>

    override fun toString () : String
    {
        val list = mutableListOf<String>()
        ifPresent(base) { list += "base=${this}" }
        return list.joinToString(",")
    }
}

abstract class QemuSystemEditor : CommandLineArgumentProvider
{
    @get:Input @get:Optional
    abstract val accelerators : ListProperty<String>

    @get:InputFile @get:Optional
    abstract val bios : RegularFileProperty

    @get:Input @get:Optional
    abstract val blockDevices : ListProperty<String>

    @get:Input @get:Optional
    abstract val characterDevices : ListProperty<String>

    @get:Input @get:Optional
    abstract val cpu : Property<String>

    @get:Input @get:Optional
    abstract val debug : Property<String>

    @get:Input @get:Optional
    abstract val debugConsole : Property<String>

    @get:InputFile @get:Optional
    abstract val debugFile : RegularFileProperty

    @get:Input @get:Optional
    abstract val devices : ListProperty<String>

    @get:Input @get:Optional
    abstract val display : Property<String>

    @get:Input @get:Optional
    abstract val drives : ListProperty<String>

    @get:Input @get:Optional
    abstract val gdb : Property<String>

    @get:InputFile @get:Optional
    abstract val kernel : RegularFileProperty

    @get:Input @get:Optional
    abstract val machine : Property<String>

    @get:Inject
    abstract val objects : ObjectFactory

    @get:Input @get:Optional
    abstract val rtc : Property<String>

    @get:Input @get:Optional
    abstract val stop : Property<Boolean>

    init
    {
        stop.convention(false)
    }

    fun characterDevice (type : String, action : Action<in QemuDeviceEditor>)
    {
        val editor = objects.newInstance<QemuDeviceEditor>()
        editor.type.set(type)
        action.execute(editor)
        characterDevices.add(editor.toString())
    }

    fun rtc (action : Action<in QemuRtcEditor>)
    {
        val editor = objects.newInstance<QemuRtcEditor>()
        action.execute(editor)
        rtc.set(editor.toString())
    }

    override fun asArguments (): Iterable<String>?
    {
        return build()
    }

    fun build () : List<String>
    {
        val list = mutableListOf<String>()
        // machine
        ifPresent(machine) { list += arrayOf("-machine", this) }
        ifPresent(cpu) { list += arrayOf("-cpu", this) }
        accelerators.get().forEach { list += arrayOf("-accel", it) }
        // drivers
        characterDevices.get().forEach { list += arrayOf("-chardev", it) }
        blockDevices.get().forEach { list += arrayOf("-blockdev", it) }
        // devices
        ifPresent(debugConsole) { list += arrayOf("-debugcon", this) }
        devices.get().forEach { list += arrayOf("-device", it) }
        ifPresent(display) { list += arrayOf("-display", this) }
        drives.get().forEach { list += arrayOf("-drive", it) }
        ifPresent(rtc) { list += arrayOf("-rtc", this) }
        // software
        ifPresent(bios) { list += arrayOf("-bios", this.toString()) }
        ifPresent(kernel) { list += arrayOf("-kernel", this.toString()) }
        // support
        ifPresent(debug) { list += arrayOf("-d", this) }
        ifPresent(debugFile) { list += arrayOf("-D", this.toString()) }
        ifPresent(gdb) { list += arrayOf("-gdb", this) }
        ifPresent(stop) { if (this) list += "-S" }
        return list
    }
}