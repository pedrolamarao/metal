import org.gradle.internal.service.ServiceRegistry
import org.gradle.model.Finalize
import org.gradle.model.RuleSource
import org.gradle.nativeplatform.toolchain.Clang
import org.gradle.nativeplatform.toolchain.NativeToolChainRegistry

class ToolchainRules extends RuleSource
{
    @Finalize
    void configure (NativeToolChainRegistry toolChains, ServiceRegistry serviceRegistry)
    {
        toolChains.create 'i686_elf_clang', Clang.class, { toolchain ->
            toolchain.path('E:/tools/llvm-12.0.1-win64/bin')
            toolchain.eachPlatform { platform ->
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
    }
}
