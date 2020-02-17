package aasgard.gradle.grub;

import org.gradle.api.DefaultTask;
import org.gradle.api.file.ConfigurableFileCollection;
import org.gradle.api.file.RegularFileProperty;
import org.gradle.api.provider.ListProperty;
import org.gradle.api.provider.Property;
import org.gradle.api.tasks.Input;
import org.gradle.api.tasks.InputFiles;
import org.gradle.api.tasks.OutputFile;
import org.gradle.api.tasks.TaskAction;

public abstract class GrubRescueCompile extends DefaultTask
{
	@Input
	public abstract ListProperty<String> getFonts ();

	@Input
	public abstract ListProperty<String> getInstall ();

	@Input
	public abstract ListProperty<String> getLoad ();
	
	@Input
	public abstract ListProperty<String> getLocales ();
	
	@Input
	public abstract Property<String> getBinaryName ();
	
	@InputFiles
	public abstract ConfigurableFileCollection getSources ();
	
	@Input
	public abstract ListProperty<String> getThemes ();
	
	@OutputFile
	public abstract RegularFileProperty getTarget ();
	
	public GrubRescueCompile ()
	{
		final var project = getProject();
		final var layout = project.getLayout();
		final var build = layout.getBuildDirectory();
		final var target = getBinaryName().flatMap(s -> build.file("grub/" + s + "/rescue/image"));
		getTarget().set(target);
	}
	
	public void install (String... value)
	{
		getInstall().addAll(value);
	}
	
	public void load (String... value)
	{
		getLoad().addAll(value);
	}
	
	public void binaryName (String value)
	{
		getBinaryName().set(value);
	}
	
	public void sources (Object... value)
	{
		getSources().from(value);
	}
	
	@TaskAction
	public void action ()
	{
		var project = getProject();
		project.mkdir(getTarget().get().getAsFile().getParentFile());
		project.exec(e -> {
			e.executable("/opt/i686-pc-elf/bin/grub-mkrescue");
            e.args("-o", getTarget().get());
            e.args("--fonts=" + String.join(" ", getFonts().get()));
            if (! getInstall().get().isEmpty()) { e.args("--install-modules=" + String.join(" ", getInstall().get())); }
            if (! getLoad().get().isEmpty()) { e.args("--modules=" + String.join(" ", getLoad().get())); }
            e.args("--locales=" + String.join(" ", getLocales().get())); 
            e.args("--themes=" + String.join(" ", getThemes().get())); 
            getSources().forEach(e::args);
		});
	}
}
