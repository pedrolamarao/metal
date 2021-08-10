import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.provider.Provider
import org.gradle.internal.service.ServiceRegistry
import org.gradle.model.Finalize
import org.gradle.model.RuleSource
import org.gradle.nativeplatform.toolchain.Clang
import org.gradle.nativeplatform.toolchain.NativeToolChainRegistry

class ToolchainRules implements Plugin<Project>
{
    private static Provider<String> llvmPath;

    void apply (Project project)
    {
        llvmPath = project.providers.provider { project.rootProject.ext.tools['br.dev.pedrolamarao.psys.llvm.path'] }
    }

    static class Rules extends RuleSource
    {
        @Finalize
        void configure (NativeToolChainRegistry toolChains, ServiceRegistry serviceRegistry)
        {
            toolChains.create 'i386-elf', Clang.class, {
                path(llvmPath)
                eachPlatform { platform ->
                    platform.assembler.executable = 'clang'
                    platform.assembler.withArguments { addAll '-target', 'i386-elf' }
                    platform.cCompiler.executable = 'clang'
                    platform.cCompiler.withArguments { addAll '-target', 'i386-elf', '-nostdinc', '-ffreestanding' }
                    platform.cppCompiler.executable = 'clang++'
                    platform.cppCompiler.withArguments { addAll '-target', 'i386-elf', '-nostdinc', '-ffreestanding' }
                    platform.linker.executable = 'clang'
                    // #XXX: clang can't link target i386-elf with lld
                    platform.linker.withArguments { addAll '-target', 'i386-linux-elf', '-fuse-ld=lld', '-nostdlib' }
                    platform.staticLibArchiver.executable = 'llvm-ar'
                }
            }
            toolChains.create 'x86_64-unknown-windows', Clang.class, {
                path(llvmPath)
                target 'windows-uefi-amd64', { platform ->
                    platform.assembler.executable = 'clang'
                    platform.assembler.withArguments { addAll '-target', 'x86_64-unknown-windows' }
                    platform.cCompiler.executable = 'clang'
                    platform.cCompiler.withArguments {
                        addAll '-target', 'x86_64-unknown-windows',
                                '-nostdinc', '-ffreestanding', '-fshort-wchar'
                    }
                    platform.cppCompiler.executable = 'clang++'
                    platform.cppCompiler.withArguments {
                        addAll '-target', 'x86_64-unknown-windows',
                                '-nostdinc', '-ffreestanding', '-fshort-wchar'
                    }
                    platform.linker.executable = 'clang'
                    // #XXX: clang can't link target i386-elf with lld
                    platform.linker.withArguments {
                        addAll '-target', 'x86_64-unknown-windows', '-fuse-ld=lld',
                                '-nostdlib', '-Wl,-entry:efi_main', '-Wl,-subsystem:efi_application'
                    }
                    platform.staticLibArchiver.executable = 'llvm-ar'
                }
            }
        }
    }
}