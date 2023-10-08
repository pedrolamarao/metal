// Copyright (C) 2022,2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

import br.dev.pedrolamarao.metal.elf;
import br.dev.pedrolamarao.metal.multiboot2;
import br.dev.pedrolamarao.metal.multiboot2.start;
import br.dev.pedrolamarao.metal.psys;
import br.dev.pedrolamarao.metal.x86;

namespace x86
{
    // segments.

    extern
    segment_selector code_segment_32;

    extern
    segment_selector code_segment_64;

    void install_segments ();

    // pages.

    void install_pages ();

    // operators.

    void abort ()
    {
        cli();
        while (true)
            halt();
    }

    void trampoline_call_32 ( segment_selector segment, size target );

    void trampoline_call_64 ( segment_selector segment, size target );
}

namespace multiboot2
{
    using size = ps::size;

    auto find_module ( information_list & information ) -> modules_information const * ;

    struct module_type
    {
        unsigned bitness;
        size start;
        size entry;
        size end;
    };

    auto load_module ( modules_information const * module ) -> module_type;
}

void multiboot2::main ( ps::size4 magic, multiboot2::information_list & information )
{
    using namespace ps;
    using namespace x86;
    using namespace multiboot2;

    // Test if loaded from the expected loader.

    if (magic != information_magic) {
        abort();
        return;
    }

    // Test if has cpuid.

    if (! has_cpuid()) {
        abort();
        return;
    }

    // Test if has long mode.

    if (! has_long_mode()) {
        abort();
        return;
    }

    // Prepare x86 segments.

    install_segments();

    // Install long mode pages.

    install_pages();

    // Enable long mode.

    set_msr(msr::EFER, get_msr(msr::EFER) | (1 << 8));

    // Activate long mode.

    enable_paging();

    // Find modules.

    for (auto i = begin(information), j = end(information); i != j; i = next(i))
    {
        if (i->type != information_type::modules) continue;
        auto module_information = reinterpret_cast<modules_information const *>(i);

        // Load module.

        auto module = load_module(module_information);
        if (module.entry == 0) continue;

        // Call module entry point.

        if (module.bitness == 32) // call 32-bit entry
        {
            trampoline_call_32(code_segment_32, module.entry);
        }
        else if (module.bitness == 64) // call 64-bit entry
        {
            trampoline_call_64(code_segment_64, module.entry);
        }
        else // !!!
        {
            abort();
        }
    }
}

namespace elf
{
    struct module_type
    {
        size start;
        size entry;
        size end;
    };

    auto load_module_32 ( size address )
    {
        auto header = reinterpret_cast<header_32 const *>(address);

        for (int i = 0; i != header->phnum; ++i)
        {
            auto segment = reinterpret_cast<segment_32 const *>(address + header->phoff + (header->phentsize * i));

            if (segment->type != elf::segment::load) continue;

            auto file = reinterpret_cast<size1 *>(address + segment->offset);
            auto memory = reinterpret_cast<size1 *>(segment->vaddr);
            for (int i = 0; i != segment->filesz; ++i)
                memory[i] = file[i];
            for (int i = segment->filesz; i != segment->memsz; ++i)
                memory[i] = 0;
        }

        return module_type { 0, header->entry, 0 };
    }

    auto load_module_64 ( size address )
    {
        auto header = reinterpret_cast<header_64 const *>(address);

        for (int i = 0; i != header->phnum; ++i)
        {
            auto segment = reinterpret_cast<segment_64 const *>(address + header->phoff + (header->phentsize * i));

            if (segment->type != elf::segment::load) continue;

            auto file = reinterpret_cast<size1 *>(address + segment->offset);
            auto memory = reinterpret_cast<size1 *>(segment->vaddr);
            for (int i = 0; i != segment->filesz; ++i)
                memory[i] = file[i];
            for (int i = segment->filesz; i != segment->memsz; ++i)
                memory[i] = 0;
        }

        if (header->entry > 0xFFFFFFFF) x86::abort();
        auto narrow = static_cast<size>(header->entry);

        return module_type { 0, narrow, 0 };
    }

    auto load_module ( size address ) -> module_type
    {
        auto prologue = reinterpret_cast<elf::prologue const *>(address);
        if (prologue->type == 1) return load_module_32(address);
        else if (prologue->type == 2) return load_module_64(address);
        else return {};
    }
}

namespace multiboot2
{
    auto find_module ( information_list & information ) -> modules_information const *
    {
        modules_information const * it {};
        for (auto i = begin(information), j = end(information); i != j; i = next(i))
        {
            switch (i->type)
            {
            case information_type::modules:
                it = reinterpret_cast<modules_information const *>(i);
                 break;
            default:
                break;
            }
        }
        return it;
    }

    auto load_module ( modules_information const * module ) -> module_type
    {
        auto elf = reinterpret_cast<elf::prologue const *>(module->start);
        auto is_elf = (elf->mag0 == 0x7F)
            && (elf->mag1 == 'E')
            && (elf->mag2 == 'L')
            && (elf->mag3 == 'F');
        if (is_elf) {
            size bitness = (elf->type == 1) ? 32 : ((elf->type == 2) ? 64 : 0);
            auto [start,entry,end] = elf::load_module(module->start);
            return { bitness, start, entry, end };
        }
        return {};
    }
}

namespace x86
{
    // segments.

    struct
    {
        size8                   null_descriptor    {};
        size8                   oops_descriptor    {};
        data_segment_descriptor data_segment       { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true };
        code_segment_descriptor short_code_segment { 0, 0xFFFFF, true, true, true, 0, true, 0, false, true, true };
        code_segment_descriptor long_code_segment  { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true, true };
    }
    global_descriptor_table;

    constinit
    segment_selector data_segment { 2, false, 0 };

    constinit
    segment_selector code_segment_32 { 3, false, 0 };

    constinit
    segment_selector code_segment_64 { 4, false, 0 };

    void install_segments ()
    {
        set_global_descriptor_table(&global_descriptor_table,sizeof(global_descriptor_table));
        set_data_segments(data_segment);
        set_code_segment(code_segment_32);
    }

    // pages.

    alignas(0x1000) constinit
    long_page_table_entry page_table [ 0x200 ];

    alignas(0x1000) constinit
    long_small_page_directory_entry page_directory [ 0x200 ];

    alignas(0x1000) constinit
    long_small_page_directory_pointer_entry page_directory_pointers [ 0x200 ];

    alignas(0x1000) constinit
    long_page_map_entry page_map [ 0x200 ];

    void install_pages ()
    {
        for (size i = 0; i != 0x200; ++i) {
            page_table[i] = {
                true, true, true, false, false, false, false, 0, false, 0, (0x1000 * i), 0, false
            };
        }
        for (size i = 0; i != 0x200; ++i) {
            page_directory[i] = {
                true, true, true, false, false, false, 0, reinterpret_cast<size8>(page_table), false
            };
        }
        for (size i = 0; i != 0x200; ++i) {
            page_directory_pointers[i] = {
                true, true, true, false, false, false, 0, reinterpret_cast<size8>(page_directory), false
            };
        }
        for (size i = 0; i != 0x200; ++i) {
            page_map[i] = {
                true, true, true, false, false, false, 0, reinterpret_cast<size8>(page_directory_pointers), false
            };
        }
        enable_large_pages();
        enable_long_addresses();
        set_paging( extended_paging { {}, false, false, reinterpret_cast<size4>(page_map) } );
    }

    // operators.

    constinit
    unsigned long trampoline_target_32 {};

    [[gnu::naked]]
    void trampoline_32 ()
    {
        __asm__
        {
            .code32
            push eax
            mov eax, trampoline_target_32
            call eax
            pop eax
            retf
        }
    }

    void trampoline_call_32 ( segment_selector segment, size target )
    {
        trampoline_target_32 = target; // #TODO: use stack
        far_call(segment, trampoline_32);
    }

    constinit
    unsigned long long trampoline_target_64 {};

    [[gnu::naked]]
    void trampoline_64 ()
    {
        __asm__
        {
            .code64
            push rax
            mov rax, trampoline_target_64
            call rax
            pop rax
            retf
        }
    }

    void trampoline_call_64 ( segment_selector segment, size target )
    {
        trampoline_target_64 = target; // #TODO: use stack
        far_call(segment, trampoline_64);
    }
}
