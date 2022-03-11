import org.gradle.api.Action
import org.gradle.api.file.RegularFile
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property

import javax.inject.Inject

abstract class GrubBase
{
    final <T> void ifPresent (Property<T> property, Action<? super T> action)
    {
        if (property.isPresent()) { action.execute(property.get()) }
    }
}

abstract class GrubMakeImageBuilder extends QemuBase
{
    abstract ListProperty<String> getInstallModules ()

    abstract RegularFileProperty getImageFile ()

    abstract ListProperty<String> getSources ()

    abstract Property<String> getPlatform ()

    @Inject abstract ObjectFactory getObjects ()

    void source ( String path, File file )
    {
        sources.add "${path}=${file}"
    }

    void source ( String path, RegularFile file )
    {
        source path, file.asFile
    }

    void source ( String path, RegularFileProperty file )
    {
        source path, file.get().asFile
    }

    String[] build ()
    {
        final ArrayList<String> args = []
        args.addAll '-O', platform.get()
        args.addAll '-o', imageFile.get()
        args.add '--themes='
        args.add '--fonts='
        args.add '--locales='
        args.add "--install-modules=${ String.join(" ", installModules.get()) }"
        args.addAll sources.get()
        args.add '-v'
        return args
    }
}