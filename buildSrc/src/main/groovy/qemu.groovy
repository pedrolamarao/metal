import org.gradle.api.Action
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property

import javax.inject.Inject

abstract class QemuBase
{
    protected <T> void ifPresent (Property<T> property, Action<? super T> action)
    {
        if (property.isPresent()) { action.execute(property.get()) }
    }
}

abstract class QemuAcceleratorWriter extends QemuBase
{
    abstract Property<String> getKernelIrqchip ()

    abstract Property<String> getName ()

    @Override String toString ()
    {
        final list = []
        ifPresent name, { list.add "${it}" }
        ifPresent kernelIrqchip, { list.add "kernel-irqchip=${it}" }
        return String.join(',', list)
    }
}

abstract class QemuDriveWriter extends QemuBase
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
}

abstract class QemuMachineWriter extends QemuBase
{
    abstract Property<String> getType ()

    @Override String toString ()
    {
        final list = []
        ifPresent type, { list.add "${it}" }
        return String.join(',', list)
    }
}

abstract class QemuRtcWriter extends QemuBase
{
    abstract Property<String> getBase ()

    @Override String toString ()
    {
        final list = []
        ifPresent base, { list.add "base=${it}" }
        return String.join(',', list)
    }
}

abstract class QemuCommandBuilder extends QemuBase
{
    abstract ListProperty<String> getAccelerators ()

    abstract RegularFileProperty getBios ()

    abstract RegularFileProperty getCommand ()

    abstract Property<String> getCpu ()

    abstract Property<String> getDebug ()

    abstract Property<String> getDebugConsole ()

    abstract RegularFileProperty getDebugFile ()

    abstract Property<String> getDisplay ()

    abstract ListProperty<String> getDrives ()

    abstract Property<String> getGdb ()

    abstract RegularFileProperty getKernel ()

    abstract Property<String> getMachine ()

    abstract Property<String> getRtc ()

    abstract Property<Boolean> getStop ()

    @Inject abstract ObjectFactory getObjects ()

    QemuCommandBuilder ()
    {
        stop.convention false
    }

    void accelerator ( String name, Action<? super QemuAcceleratorWriter> configure )
    {
        final writer = objects.newInstance(QemuAcceleratorWriter)
        writer.name = name;
        configure.execute(writer)
        accelerators.add( writer.toString() )
    }

    void drive ( Action<? super QemuDriveWriter> configure )
    {
        final writer = objects.newInstance(QemuDriveWriter)
        configure.execute(writer)
        drives.add( writer.toString() )
    }

    void machine ( Action<? super QemuMachineWriter> configure )
    {
        final writer = objects.newInstance(QemuMachineWriter)
        configure.execute(writer)
        getMachine().set( writer.toString() )
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
        // machine
        ifPresent machine, { list.addAll '-machine', it }
        ifPresent cpu, { list.addAll '-cpu', it }
        accelerators.get().forEach { list.addAll '-accel', it }
        // devices
        ifPresent bios, { list.addAll '-bios', it }
        ifPresent debugConsole, { list.addAll '-debugcon', it }
        ifPresent display, { list.addAll '-display', it }
        drives.get().forEach { list.addAll '-drive', it }
        ifPresent kernel, { list.addAll '-kernel', it }
        ifPresent rtc, { list.addAll '-rtc', it }
        // support
        ifPresent debug, { list.addAll '-d', it }
        ifPresent debugFile, { list.addAll '-D', it }
        ifPresent gdb, { list.addAll '-gdb', it }
        ifPresent stop, { if (it) list.add '-S' }
        return list
    }
}