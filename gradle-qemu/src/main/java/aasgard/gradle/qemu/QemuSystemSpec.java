package aasgard.gradle.qemu;

import org.gradle.api.Action;
import org.gradle.api.file.RegularFileProperty;
import org.gradle.api.provider.MapProperty;
import org.gradle.api.provider.Property;

public abstract class QemuSystemSpec
{
	// life
	
	public QemuSystemSpec ()
	{
		getStart().convention(true);
	}
	
	// properties

	public abstract Property<String> getArchitecture ();
	
	public abstract RegularFileProperty getBios ();
	
	public abstract RegularFileProperty getCdrom ();

	public abstract MapProperty<String, String> getEnvironment ();
	
	public abstract Property<String> getGdb ();
	
	public abstract RegularFileProperty getKernel ();

	public abstract Property<String> getProcessor ();

	public abstract Property<Boolean> getStart ();
	
	// utilities
	
	public void configure (Action<? super QemuSystemSpec> action)
	{
		action.execute(this);
	}
}