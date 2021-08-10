import org.gradle.api.Action
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property

import javax.inject.Inject

abstract class QemuDriveWriter
{
    abstract RegularFileProperty getFile ()

    abstract Property<String> getFormat ()

    abstract Property<String> getMedia ()

    abstract Property<Boolean> getReadOnly ()

    abstract Property<String> getType ()

    @Override String toString ()
    {
        final list = []
        ifPresent type, { list.add "if=${it}" }
        ifPresent format, { list.add "format=${it}" }
        ifPresent media, { list.add "media=${it}" }
        ifPresent readOnly, { list.add "readonly=${it}" }
        ifPresent file, { list.add "file=${it}" }
        return String.join(',', list)
    }
    static <T> void ifPresent (Property<T> property, Action<? super T> action)
    {
        if (property.isPresent()) { action.execute(property.get()) }
    }
}

abstract class QemuRtcWriter
{
    abstract Property<String> getBase ()

    @Override String toString ()
    {
        final list = []
        ifPresent base, { list.add "base=${it}" }
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

    abstract Property<String> getDisplay ()

    abstract ListProperty<String> getDrives ()

    abstract Property<String> getGdb ()

    abstract Property<String> getMachine ()

    abstract Property<String> getRtc ()

    abstract Property<Boolean> getStop ()

    @Inject abstract ObjectFactory getObjects ()

    QemuCommandBuilder ()
    {
        stop.convention false
    }

    void drive ( Action<? super QemuDriveWriter> configure )
    {
        final writer = objects.newInstance(QemuDriveWriter)
        configure.execute(writer)
        getDrives().add( writer.toString() )
    }

    void rtc ( Action<? super QemuRtcWriter> configure )
    {
        final writer = objects.newInstance(QemuRtcWriter)
        configure.execute(writer)
        getRtc().set( writer.toString() )
    }

    String[] build ()
    {
        final ArrayList<String> list = []
        list.add command.get()
        ifPresent bios, { list.addAll '-bios', it }
        ifPresent display, { list.addAll '-display', it }
        drives.get().forEach { list.addAll '-drive', it }
        ifPresent gdb, { list.addAll '-gdb', it }
        ifPresent machine, { list.addAll '-machine', it }
        ifPresent rtc, { list.addAll '-rtc', it }
        ifPresent stop, { if (it) list.add '-S' }
        return list
    }

    static <T> void ifPresent (Property<T> property, Action<? super T> action)
    {
        if (property.isPresent()) { action.execute(property.get()) }
    }
}