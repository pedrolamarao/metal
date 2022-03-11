import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.file.RegularFile
import org.gradle.api.provider.Provider
import org.gradle.nativeplatform.toolchain.Clang

class ToolchainRules implements Plugin<Project>
{
    private Provider<String> llvmPath

    private File x86_32_elf_multiboot2_ld

    void apply (Project project)
    {
        llvmPath = project.providers.provider { project.rootProject.ext.tools['br.dev.pedrolamarao.psys.llvm.path'] }

        x86_32_elf_multiboot2_ld = project.rootProject.file('multiboot2/x86_32-elf.ld')

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

    final host = {
        assembler.executable = 'clang'
        cCompiler.executable = 'clang'
        cppCompiler.executable = 'clang++'
        linker.executable = 'clang'
        linker.withArguments { '-fuse-ld=lld' }
        staticLibArchiver.executable = 'llvm-ar'
    }

    final multiboot_x86_32 = {
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
            addAll '-target', 'i386-linux-elf', '-fuse-ld=lld', '-gdwarf', '-nostdlib', '-static',
                "-Wl,--script=${x86_32_elf_multiboot2_ld}"
        }
        staticLibArchiver.executable = 'llvm-ar'
    }

    final uefi_x86_64 = {
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