// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <elf/elf.h>

#include <multiboot2/information.h>
#include <multiboot2/start.h>


void multiboot2::main ( ps::size4 magic, multiboot2::information_list & response )
{
    using namespace ps;

    // Test if loaded from the expected loader.

    if (magic != information_magic) {
        return;
    }

    // Find module: expect exactly one.

    unsigned count { 0 };
    modules_information * module {};

    for (auto i = begin(response), j = end(response); i != j; i = next(i))
    {
        using type = multiboot2::information_type;
        switch (i->type)
        {
        case type::modules:
            ++count;
            module = reinterpret_cast<modules_information*>(i);
            break;
        default:
            break;
        }
    }

    if (count != 1) {
        return;
    }

    // Locate module entry point.

    void (*entry)() {};

    // Validate module prologue.

    auto elf = reinterpret_cast<elf::prologue const *>(module->start);
    if (elf->mag0 != 0x7F) { return; }
    if (elf->mag1 != 'E') { return; }
    if (elf->mag2 != 'L') { return; }
    if (elf->mag3 != 'F') { return; }

    if (elf->type == 1) // ELF32
    {
        // Validate module header.

        auto elf_32 = reinterpret_cast<elf::header_32 const *>(module->start);
        if (elf_32->machine != elf::machine::EM_386) { return; }
        if (elf_32->phoff == 0) { return; }
        if (elf_32->entry == 0) { return; }

        // Load module segments.

        for (int i = 0; i != elf_32->phnum; ++i) {
            auto segment = reinterpret_cast<elf::segment_32 const *>(module->start + elf_32->phoff + (elf_32->phentsize * i));
            if (segment->type != elf::segment::load) continue;
            auto file = reinterpret_cast<size1 *>(module->start + segment->offset);
            auto memory = reinterpret_cast<size1 *>(segment->vaddr);
            for (int i = 0; i != segment->filesz; ++i)
                memory[i] = file[i];
            for (int i = segment->filesz; i != segment->memsz; ++i)
                memory[i] = 0;
        }

        // Bind entry point.

        entry = reinterpret_cast<void (*)()>(elf_32->entry);
    }
    else if (elf->type == 2) // ELF64
    {
        // Validate module header.

        auto elf_64 = reinterpret_cast<elf::header_64 const *>(module->start);
        if (elf_64->machine != elf::machine::EM_X86_64) { return; }
        if (elf_64->phoff == 0) { return; }
        if (elf_64->entry == 0) { return; }

        // Load module segments.

        for (int i = 0; i != elf_64->phnum; ++i) {
            auto segment = reinterpret_cast<elf::segment_64 const *>(module->start + elf_64->phoff + (elf_64->phentsize * i));
            if (segment->type != elf::segment::load) continue;
            auto file = reinterpret_cast<size1 *>(module->start + segment->offset);
            auto memory = reinterpret_cast<size1 *>(segment->vaddr);
            for (int i = 0; i != segment->filesz; ++i)
                memory[i] = file[i];
            for (int i = segment->filesz; i != segment->memsz; ++i)
                memory[i] = 0;
        }

        // Bind entry point.

        entry = reinterpret_cast<void (*)()>(elf_64->entry);
    }
    else // ???
    {
        return;
    }

    // Prepare x86 segments.
    // #TODO

    // Prepare x86 interrupts.
    // #TODO

    // Prepare x86 long mode.
    // #TODO

    // Activate x86 long mode.
    // #TODO

    // Call module entry point.

    if (elf->type == 1) // call 32-bit entry
    {
        entry();
    }
    else if (elf->type == 2) // call 64-bit entry
    {
        // #TODO: far call into 64-bit code segment
        entry();
    }
    else // ???
    {
    }
}
