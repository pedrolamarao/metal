package aasgard.gradle.asm;

import java.util.Collections;
import java.util.Optional;

import org.gradle.api.Plugin;
import org.gradle.api.Project;
import org.gradle.api.logging.Logger;
import org.gradle.api.logging.Logging;
import org.gradle.api.tasks.TaskProvider;
import org.gradle.language.assembler.tasks.Assemble;
import org.gradle.language.cpp.CppApplication;
import org.gradle.language.cpp.CppBinary;
import org.gradle.language.cpp.CppExecutable;
import org.gradle.language.cpp.CppLibrary;
import org.gradle.language.cpp.CppStaticLibrary;

public class GradleAsmPlugin implements Plugin<Project>
{
	private Logger logger;
	
    public void apply (Project project) 
    {
    	logger = Logging.getLogger(GradleAsmPlugin.class);
    	
    	project.afterEvaluate(p -> 
    	{
    		find(p, CppLibrary.class).ifPresent(library -> {
        		library.getBinaries().whenElementFinalized(binary -> {
        			if (binary instanceof CppStaticLibrary) {
        				apply(p, (CppStaticLibrary) binary);
        			}
        		});
    		});
    		find(p, CppApplication.class).ifPresent(application -> {
            	application.getBinaries().whenElementFinalized(binary -> {
            		if (binary instanceof CppExecutable) {
            			apply(p, (CppExecutable) binary);
            		}
            	});
    		});
    	});
    }
    
    public void apply (Project project, CppStaticLibrary binary)
    {    	
    	logger.info("aasgard.asm: apply: {}", binary.getName());
    	
        var compileAsm = create(project, binary);

        var obj = project.fileTree(compileAsm.get().getObjectFileDir());
    	obj.include("**/*.obj");
        
        var link = binary.getCreateTask().get();
        link.dependsOn(compileAsm);
        link.source(obj);
    }
    
    public void apply (Project project, CppExecutable binary)
    {
    	logger.info("aasgard.asm: apply: {}", binary.getName());
    	
        var compileAsm = create(project, binary);

        var obj = project.fileTree(compileAsm.get().getObjectFileDir());
    	obj.include("**/*.obj");
        
        var link = binary.getLinkTask().get();
        link.dependsOn(compileAsm);
        link.source(obj);
    }
    
    public TaskProvider<Assemble> create (Project project, CppBinary binary)
    {
    	var name = String.format("compileAsm%s", binary.getName());
        return project.getTasks().register(name, Assemble.class, asm -> 
        {    		
    		asm.getTargetPlatform().set(binary.getCompileTask().get().getTargetPlatform());
            asm.getToolChain().set(binary.getToolChain());
            asm.getIncludes().from(project.file("src/main/public"));
            asm.getIncludes().from(project.file("src/main/headers"));
            asm.setAssemblerArgs(Collections.emptyList());
            asm.getSource().from(project.fileTree("src/main/asm", tree -> tree.include("**/*.s")));
            var tmp = String.format("asm/%s", binary.getName());
            asm.setObjectFileDir(project.getLayout().getBuildDirectory().dir(tmp).get().getAsFile());
        });    	
    }
    
    public static <T> Optional<T> find (Project project, Class<T> type)
    {
    	return Optional.ofNullable( project.getExtensions().findByType(type) );
    }
}
