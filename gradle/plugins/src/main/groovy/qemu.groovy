import org.gradle.api.Action
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.MapProperty
import org.gradle.api.provider.Property

import javax.inject.Inject

abstract class QemuBase
{
    static <T> void ifPresent (Property<T> property, Action<? super T> action)
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

abstract class QemuDeviceDriverEditor extends QemuBase
{
    abstract MapProperty<String, String> getOptions ()

    abstract Property<String> getType ()

    @Override String toString ()
    {
        final list = []
        list.add type.get()
        options.get().forEach { key, value -> list.add "${key}=${value}" }
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

abstract class QemuCommandEditor extends QemuBase
{
    abstract ListProperty<String> getAccelerators ()

    abstract RegularFileProperty getBios ()

    abstract ListProperty<String> getBlockDrivers ()

    abstract ListProperty<String> getCharacterDrivers ()

    abstract Property<String> getCpu ()

    abstract Property<String> getDebug ()

    abstract Property<String> getDebugConsole ()

    abstract RegularFileProperty getDebugFile ()

    abstract ListProperty<String> getDevices ()

    abstract Property<String> getDisplay ()

    abstract ListProperty<String> getDrives ()

    abstract Property<String> getGdb ()

    abstract RegularFileProperty getKernel ()

    abstract Property<String> getMachine ()

    abstract Property<String> getRtc ()

    abstract Property<Boolean> getStop ()

    @Inject abstract ObjectFactory getObjects ()

    QemuCommandEditor()
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

    void blockDriver ( String type, Action<? super QemuDeviceDriverEditor> configure )
    {
        final editor = objects.newInstance(QemuDeviceDriverEditor)
        editor.type.convention type
        configure.execute editor
        blockDrivers.add editor.toString()
    }

    void characterDriver ( String type, Action<? super QemuDeviceDriverEditor> configure )
    {
        final editor = objects.newInstance(QemuDeviceDriverEditor)
        editor.type.convention type
        configure.execute editor
        characterDrivers.add editor.toString()
    }

    void device ( String type, Action<? super QemuDeviceDriverEditor> configure )
    {
        final editor = objects.newInstance(QemuDeviceDriverEditor)
        editor.type.convention type
        configure.execute editor
        devices.add editor.toString()
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

    List<String> build ()
    {
        final List<String> list = []
        // machine
        ifPresent machine, { list.addAll '-machine', it.toString() }
        ifPresent cpu, { list.addAll '-cpu', it.toString() }
        accelerators.get().forEach { list.addAll '-accel', it.toString() }
        // drivers
        characterDrivers.get().forEach { list.addAll '-chardev', it.toString() }
        blockDrivers.get().forEach { list.addAll '-blockdev', it.toString() }
        // devices
        ifPresent debugConsole, { list.addAll '-debugcon', it.toString() }
        devices.get().forEach { list.addAll '-device', it.toString() }
        ifPresent display, { list.addAll '-display', it.toString() }
        drives.get().forEach { list.addAll '-drive', it.toString() }
        ifPresent rtc, { list.addAll '-rtc', it.toString() }
        // software
        ifPresent bios, { list.addAll '-bios', it.toString() }
        ifPresent kernel, { list.addAll '-kernel', it.toString() }
        // support
        ifPresent debug, { list.addAll '-d', it.toString() }
        ifPresent debugFile, { list.addAll '-D', it.toString() }
        ifPresent gdb, { list.addAll '-gdb', it.toString() }
        ifPresent stop, { if (it) list.add '-S' }
        return list
    }
}