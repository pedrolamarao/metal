// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <elf/elf.h>

#include <multiboot2/information.h>
#include <multiboot2/start.h>

#include <x86/identification.h>
#include <x86/instructions.h>
#include <x86/interrupts.h>
#include <x86/msr.h>
#include <x86/pages.h>
#include <x86/segments.h>


namespace x86
{
    // segments.

    struct
    {
        size8                   null_descriptor    {};
        data_segment_descriptor data_segment       { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true };
        code_segment_descriptor short_code_segment { 0, 0xFFFFF, true, true, true, 0, true, 0, false, true, true };
        code_segment_descriptor long_code_segment  { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true, true };
    }
    global_descriptor_table;

    // interrupts.

    extern
    _32::interrupt_gate_descriptor interrupt_descriptor_table_32 [ 256 ];

    [[gnu::naked]]
    void interrupt_handler_32 ();

    extern
    _64::interrupt_gate_descriptor interrupt_descriptor_table_64 [ 256 ];

    [[gnu::naked]]
    void interrupt_handler_64 ();

    // pages.

    extern
    long_page_table_entry page_table [ 0x200 ];

    extern
    long_small_page_directory_entry page_directory [ 0x200 ];

    extern
    long_small_page_directory_pointer_entry page_directory_pointers [ 0x200 ];

    extern
    long_page_map_entry page_map [ 0x200 ];

    // operators.

    void abort ()
    {
        cli();
        while (true)
            halt();
    }
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

namespace
{
    void debug ( char const * s );
}

void multiboot2::main ( ps::size4 magic, multiboot2::information_list & response )
{
    using namespace ps;
    using namespace x86;
    using namespace multiboot2;

    // Test if loaded from the expected loader.

    if (magic != information_magic) {
        debug("?");
        abort();
    }

    // Find module: assumes exactly one.

    auto module_information = find_module(response);
    if (module_information == nullptr) {
        debug("?");
        abort();
    }

    // Load module.

    auto module = load_module(module_information);
    if (module.entry == 0) {
        debug("?");
        abort();
    }

    // Prepare x86 segments.

    auto code_segment_32 = segment_selector{2,false,0};
    auto code_segment_64 = segment_selector{3,false,0};
    set_global_descriptor_table(&global_descriptor_table,sizeof(global_descriptor_table));
    set_data_segments(segment_selector{1,false,0});
    set_code_segment(code_segment_32);

    // Call module entry point.

    if (module.bitness == 32) // call 32-bit entry
    {
        // Prepare x86 interrupts.

        for (auto i = 0U, j = 256U; i != j; ++i) {
            interrupt_descriptor_table_32[i] = { code_segment_32, interrupt_handler_32, true, true, 0, true };
        }
        set_interrupt_descriptor_table(interrupt_descriptor_table_32);

        debug("32>");
        far_call( segment_selector{2,false,0}, reinterpret_cast<void (*)()>(module.entry) );
        debug("!");
    }
    else if (module.bitness == 64) // call 64-bit entry
    {
        if (! has_long_mode()) { return; }

        // Prepare x86 interrupts.

        for (auto i = 0U, j = 256U; i != j; ++i) {
            interrupt_descriptor_table_64[i] = { code_segment_64, interrupt_handler_64, true, true, 0, true };
        }
        set_interrupt_descriptor_table(interrupt_descriptor_table_64);

        // prepare long mode pages.

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

        // enable long mode.

        set_msr(msr::EFER, get_msr(msr::EFER) | (1 << 8));

        // is long mode enabled?

        if ((get_msr(msr::EFER) & (1 << 8)) == 0) { return; }

        // activate long mode.

        enable_paging();

        // is long mode active?

        if ((get_msr(msr::EFER) & (1 << 10)) == 0) { return; }

        debug("64>");
        far_call( segment_selector{3,false,0}, reinterpret_cast<void (*)()>(module.entry) );
        debug("!");
    }
    else // !!!
    {
        debug("?");
        abort();
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
    // interrupts.

    constinit
    _32::interrupt_gate_descriptor interrupt_descriptor_table_32 [ 256 ]
    { };

    [[gnu::naked]]
    void interrupt_handler_32 ()
    {
        __asm__
        {
            cli
        loop:
            hlt
            jmp loop
        }
    }

    constinit
    _64::interrupt_gate_descriptor interrupt_descriptor_table_64 [ 256 ]
    { };

    [[gnu::naked]]
    void interrupt_handler_64 ()
    {
        __asm__
        {
            .code64
            cli
        loop:
            hlt
            jmp loop
        }
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
}

namespace
{
    char table [16] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    void debug ( char const * s )
    {
        while (*s != 0) x86::out1(0xE9, *s++);
    }
}