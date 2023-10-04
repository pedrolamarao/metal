// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <elf/elf.h>

#include <multiboot2/information.h>
#include <multiboot2/start.h>

#include <psys/test.h>


//! Modular application test.

namespace multiboot2
{
    void main ( ps::size4 magic, multiboot2::information_list & response )
    {
        using namespace ps;

        _test_start();
        unsigned step { 1 };

        // Test if loaded from the expected loader.

        _test_control = step++;
        if (magic != information_magic) {
            _test_control = 0;
            return;
        }

        // Find module: expect exactly one.

        _test_control = step++;

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
            _test_control = 0;
            return;
        }

        // Validate module: ELF32, x86_32 machine, segments, entry.

        _test_control = step++;
        auto elf = reinterpret_cast<elf::prologue const *>(module->start);
        if (elf->mag0 != 0x7F) { _test_control = 0; return; }
        if (elf->mag1 != 'E') { _test_control = 0; return; }
        if (elf->mag2 != 'L') { _test_control = 0; return; }
        if (elf->mag3 != 'F') { _test_control = 0; return; }

        _test_control = step++;
        if (elf->type != 1) { _test_control = 0; return; }

        _test_control = step++;
        auto elf_32 = reinterpret_cast<elf::header_32 const *>(module->start);
        if (elf_32->machine != elf::machine::EM_386) { _test_control = 0; return; }

        _test_control = step++;
        if (elf_32->phoff == 0) { _test_control = 0; return; }

        _test_control = step++;
        if (elf_32->entry == 0) { _test_control = 0; return; }

        // Load module segments.

        _test_control = step++;
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

        // Call module entry point: expect nonnull C++ void (*)().

        _test_control = step++;
        auto entry = reinterpret_cast<void (*)()>(elf_32->entry);
        entry();

        _test_control = -1;
        _test_finish();
    }
}