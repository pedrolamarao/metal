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
            toolChains.create 'multiboot-x86_32', Clang.class, {
                path(llvmPath)
                target('windows-multiboot-x86_32', multiboot_x86_32)
                target('linux-multiboot-x86_32', multiboot_x86_32)
            }
            toolChains.create 'uefi-x86_64', Clang.class, {
                path(llvmPath)
                target('linux-uefi-x86_64', uefi_x86_64)
                target('windows-uefi-x86_64', uefi_x86_64)
            }
        }

        static final multiboot_x86_32 = { platform ->
            platform.assembler.executable = 'clang'
            platform.assembler.withArguments { addAll '-target', 'i386-elf' }
            platform.cCompiler.executable = 'clang'
            platform.cCompiler.withArguments { addAll '-target', 'i386-elf', '-ffreestanding', '-nostdinc' }
            platform.cppCompiler.executable = 'clang++'
            platform.cppCompiler.withArguments { addAll '-target', 'i386-elf', '-ffreestanding', '-nostdinc' }
            platform.linker.executable = 'clang'
            // #XXX: clang can't link target i386-elf with lld
            platform.linker.withArguments { addAll '-target', 'i386-linux-elf', '-fuse-ld=lld', '-nostdlib' }
            platform.staticLibArchiver.executable = 'llvm-ar'
        }

        static final uefi_x86_64 = { platform ->
            platform.assembler.executable = 'clang'
            platform.assembler.withArguments { addAll '-target', 'x86_64-unknown-windows' }
            platform.cCompiler.executable = 'clang'
            platform.cCompiler.withArguments {
                addAll '-target', 'x86_64-unknown-windows',
                    '-ffreestanding', '-fshort-wchar', '-nostdinc'
            }
            platform.cppCompiler.executable = 'clang++'
            platform.cppCompiler.withArguments {
                addAll '-target', 'x86_64-unknown-windows',
                    '-ffreestanding', '-fshort-wchar', '-nostdinc'
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