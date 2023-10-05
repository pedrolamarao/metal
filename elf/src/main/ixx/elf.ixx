module;

#include <elf/elf.h>

export module br.dev.pedrolamarao.metal.elf;

export namespace elf
{
    using ::elf::machine;
    using ::elf::segment;
    using ::elf::prologue;
    using ::elf::header_32;
    using ::elf::segment_32;
    using ::elf::header_64;
    using ::elf::segment_64;
}