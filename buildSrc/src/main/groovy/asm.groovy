import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.logging.Logger
import org.gradle.api.logging.Logging
import org.gradle.api.tasks.TaskProvider
import org.gradle.language.assembler.tasks.Assemble
import org.gradle.language.cpp.*

class AsmLanguage implements Plugin<Project>
{
    private Logger logger;

    void apply (Project project)
    {
        logger = Logging.getLogger(AsmLanguage.class);

        project.afterEvaluate { p ->
            find(p, CppLibrary).ifPresent { component ->
                component.binaries.whenElementFinalized { binary ->
                    if (binary instanceof CppStaticLibrary) apply(p, binary)
                }
            }
            find(p, CppApplication).ifPresent { component ->
                component.binaries.whenElementFinalized { binary ->
                    if (binary instanceof CppExecutable) apply(p, binary)
                }
            }
            find(p, dev.nokee.platform.cpp.CppApplication).ifPresent { component ->
                component.binaries.configureEach { binary ->
                    apply(p, binary)
                }
            }
            find(p, dev.nokee.platform.cpp.CppLibrary).ifPresent { component ->
                component.binaries.configureEach { binary ->
                    apply(p, binary)
                }
            }
        }
    }

    void apply (Project project, CppStaticLibrary binary)
    {
        logger.info("psys.asm-language: apply: ${binary.name}")
        final compileAsm = create(project, binary)
        final link = binary.createTask.get()
        link.dependsOn(compileAsm)
        link.source compileAsm.map { asm ->
            return project.fileTree(asm.objectFileDir, { file ->
                file.include("**/*.o", "**/*.obj")
            })
        }
    }

    void apply (Project project, CppExecutable binary)
    {
        logger.info("psys.asm-language: apply: ${binary.name}");
        final compileAsm = create(project, binary);
        final link = binary.linkTask.get();
        link.dependsOn(compileAsm);
        link.source compileAsm.map { asm ->
            return project.fileTree(asm.objectFileDir, { file ->
                file.include("**/*.o", "**/*.obj")
            })
        }
    }

    void apply (Project project, dev.nokee.platform.nativebase.ExecutableBinary binary)
    {
        logger.info("psys.asm-language: apply: ${binary}")
        final compile = create(project, binary)
        binary.linkTask.get().with {
            dependsOn compile
            source compile.map { asm ->
                return project.fileTree(asm.objectFileDir, { file ->
                    file.include("**/*.o", "**/*.obj")
                })
            }
        }
    }

    void apply (Project project, dev.nokee.platform.nativebase.StaticLibraryBinary binary)
    {
        logger.info("psys.asm-language: apply: ${binary}")
        final compile = create(project, binary)
        binary.createTask.get().with {
            dependsOn compile
            source compile.map { asm ->
                return project.fileTree(asm.objectFileDir, { file ->
                    file.include("**/*.o", "**/*.obj")
                })
            }
        }
    }

    TaskProvider<Assemble> create (Project project, CppBinary binary)
    {
        final name = String.format("compileAsm${binary.name}")
        return project.tasks.register(name, Assemble.class, { task ->
            logger.info("psys.asm-language: ${task.name}")
            task.targetPlatform = binary.getCompileTask().get().getTargetPlatform()
            task.toolChain = binary.getToolChain()
            task.includes.from project.file("src/main/public")
            task.includes.from project.file("src/main/headers")
            task.assemblerArgs = Collections.emptyList()
            task.source.from project.fileTree("src/main/asm", { tree -> tree.include("**/*.s") })
            final tmp = "asm/${binary.name}"
            task.objectFileDir = project.layout.buildDirectory.dir(tmp).get().getAsFile()
        })
    }

    TaskProvider<Assemble> create (Project project, dev.nokee.platform.nativebase.internal.ExecutableBinaryInternal binary)
    {
        final name = String.format("compileAsm${binary}")
        return project.tasks.register(name, Assemble.class, { task ->
            logger.info("psys.asm-language: ${task.name}")
            task.targetPlatform = binary.targetPlatform
            task.toolChain = binary.linkTask.get().getToolChain()
            task.includes.from project.file("src/main/public")
            task.includes.from project.file("src/main/headers")
            task.assemblerArgs = Collections.emptyList()
            task.source.from project.fileTree("src/main/asm", { tree -> tree.include("**/*.s") })
            final tmp = "asm/${binary}"
            task.objectFileDir = project.layout.buildDirectory.dir(tmp).get().getAsFile()
        })
    }

    TaskProvider<Assemble> create (Project project, dev.nokee.platform.nativebase.internal.StaticLibraryBinaryInternal binary)
    {
        final name = String.format("compileAsm${binary}")
        return project.tasks.register(name, Assemble.class, { task ->
            logger.info("psys.asm-language: ${task.name}")
            task.targetPlatform = binary.targetPlatform
            task.toolChain = binary.createTask.get().getToolChain()
            task.includes.from project.file("src/main/public")
            task.includes.from project.file("src/main/headers")
            task.assemblerArgs = Collections.emptyList()
            task.source.from project.fileTree("src/main/asm", { tree -> tree.include("**/*.s") })
            final tmp = "asm/${binary}"
            task.objectFileDir = project.layout.buildDirectory.dir(tmp).get().getAsFile()
        })
    }

    static <T> Optional<T> find (Project project, Class<T> type)
    {
        return Optional.ofNullable( project.extensions.findByType(type) )
    }
}
