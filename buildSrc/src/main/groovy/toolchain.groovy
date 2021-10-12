import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.provider.Provider
import org.gradle.nativeplatform.toolchain.Clang

class ToolchainRules implements Plugin<Project>
{
    private static Provider<String> llvmPath

    void apply (Project project)
    {
        llvmPath = project.providers.provider { project.rootProject.ext.tools['br.dev.pedrolamarao.psys.llvm.path'] }

        project.model
        {
            toolChains
            {
                llvm(Clang)
                {
                    if (llvmPath.isPresent()) { path(llvmPath) }
                    // host
                    eachPlatform(host)
                    // multiboot-x86_32
                    target('linux-multiboot-x86_32', multiboot_x86_32)
                    target('windows-multiboot-x86_32', multiboot_x86_32)
                    // uefi-x86_64
                    target('linux-uefi-x86_64', uefi_x86_64)
                    target('windows-uefi-x86_64', uefi_x86_64)
                }
            }
        }
    }

    static final host = {
        assembler.executable = 'clang'
        cCompiler.executable = 'clang'
        cppCompiler.executable = 'clang++'
        linker.executable = 'clang'
        linker.withArguments { '-fuse-ld=lld' }
        staticLibArchiver.executable = 'llvm-ar'
    }

    static final multiboot_x86_32 = {
        assembler.executable = 'clang'
        assembler.withArguments {
            addAll '-target', 'i386-elf', '-gdwarf'
        }
        cCompiler.executable = 'clang'
        cCompiler.withArguments {
            addAll '-target', 'i386-elf', '-ffreestanding', '-gdwarf', '-nostdinc'
        }
        cppCompiler.executable = 'clang++'
        cppCompiler.withArguments {
            addAll '-target', 'i386-elf', '-ffreestanding', '-gdwarf', '-nostdinc'
        }
        linker.executable = 'clang'
        // #XXX: clang can't link target i386-elf with lld
        linker.withArguments {
            addAll '-target', 'i386-linux-elf',
                    '-fuse-ld=lld', '-gdwarf', '-nostdlib',
                    '-Wl,--entry=multiboot2_start'
        }
        staticLibArchiver.executable = 'llvm-ar'
    }

    static final uefi_x86_64 = {
        assembler.executable = 'clang'
        assembler.withArguments { addAll '-target', 'x86_64-unknown-windows' }
        cCompiler.executable = 'clang'
        cCompiler.withArguments {
            addAll '-target', 'x86_64-unknown-windows',
                    '-ffreestanding', '-fshort-wchar', '-nostdinc'
        }
        cppCompiler.executable = 'clang++'
        cppCompiler.withArguments {
            addAll '-target', 'x86_64-unknown-windows',
                '-ffreestanding', '-fshort-wchar', '-nostdinc'
        }
        linker.executable = 'clang'
        // #XXX: clang can't link target i386-elf with lld
        linker.withArguments {
            addAll '-target', 'x86_64-unknown-windows', '-fuse-ld=lld',
                '-nostdlib', '-Wl,-entry:efi_main', '-Wl,-subsystem:efi_application'
        }
        staticLibArchiver.executable = 'llvm-ar'
    }
}