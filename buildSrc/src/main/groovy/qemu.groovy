import org.gradle.api.Action
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property

abstract class QemuDriveWriter
{
    abstract RegularFileProperty getFile ()

    abstract Property<String> getFormat ()

    abstract Property<Boolean> getReadOnly ()

    abstract Property<String> getType ()

    @Override String toString ()
    {
        final list = []
        ifPresent type, { list.add "if=${it}" }
        ifPresent format, { list.add "format=${it}" }
        ifPresent readOnly, { list.add "readonly=${it}" }
        ifPresent file, { list.add "file=${it}" }
        return String.join(',', list)
    }
    static <T> void ifPresent (Property<T> property, Action<? super T> action)
    {
        if (property.isPresent()) { action.execute(property.get()) }
    }
}

abstract class QemuCommandBuilder
{
    abstract RegularFileProperty getBios ()

    abstract RegularFileProperty getCommand ()

    abstract ListProperty<String> getDrives ()

    abstract Property<String> getGdb ()

    abstract Property<String> getMachine ()

    abstract Property<Boolean> getStop ()

    QemuCommandBuilder ()
    {
        stop.convention false
    }

    String[] build ()
    {
        final ArrayList<String> list = []
        list.add command.get()
        ifPresent bios, { list.addAll '-bios', it }
        drives.get().forEach { list.addAll '-drive', it }
        ifPresent gdb, { list.addAll '-gdb', it }
        ifPresent machine, { list.addAll '-machine', it }
        ifPresent stop, { if (it) list.add '-S' }
        return list
    }

    static <T> void ifPresent (Property<T> property, Action<? super T> action)
    {
        if (property.isPresent()) { action.execute(property.get()) }
    }
}