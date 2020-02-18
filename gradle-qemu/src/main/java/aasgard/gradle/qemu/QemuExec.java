package aasgard.gradle.qemu;

import org.gradle.api.DefaultTask;
import org.gradle.api.file.RegularFileProperty;
import org.gradle.api.provider.Property;
import org.gradle.api.tasks.Input;
import org.gradle.api.tasks.InputFile;
import org.gradle.api.tasks.Optional;
import org.gradle.api.tasks.TaskAction;

public abstract class QemuExec extends DefaultTask
{
	// properties
	
	@Input
	public abstract Property<String> getSystem ();
	
	@Optional
	@InputFile
	public abstract RegularFileProperty getBios ();
	
	@Optional
	@InputFile
	public abstract RegularFileProperty getKernel ();
	
	@Optional
	@InputFile
	public abstract RegularFileProperty getCdrom ();
	
	// accessors
	
	public void system (String value)
	{
		getSystem().set(value);
	}
	
	public void bios (RegularFileProperty value)
	{
		getBios().set(value);
	}
	
	public void cdrom (RegularFileProperty value)
	{
		getCdrom().set(value);
	}
	
	public void kernel (RegularFileProperty value)
	{
		getKernel().set(value);		
	}
	
	@TaskAction
	public void action ()
	{
		var project = getProject();
		project.exec(exec -> {
			exec.executable(getSystem().map(it -> "qemu-system-" + it).get());
			if (getBios().isPresent()) { exec.args("-bios", getBios().get().getAsFile().toString()); }
			if (getKernel().isPresent()) { exec.args("-kernel", getKernel().get().getAsFile().toString()); }
			if (getCdrom().isPresent()) { exec.args("-cdrom", getCdrom().get().getAsFile().toString()); }
		});
	}
}
