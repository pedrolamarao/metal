// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <x86/pages.h>

export module br.dev.pedrolamarao.metal.x86:pages;

export namespace x86
{
    using ::x86::short_page_table_entry;
    using ::x86::short_small_page_directory_entry;
    using ::x86::short_large_page_directory_entry;
    using ::x86::extended_page_table_entry;
    using ::x86::extended_small_page_directory_entry;
    using ::x86::extended_large_page_directory_entry;
    using ::x86::extended_page_directory_pointer_entry;
    using ::x86::short_paging;
    using ::x86::extended_paging;
    using ::x86::long_page_table_entry;
    using ::x86::long_small_page_directory_entry;
    using ::x86::long_small_page_directory_pointer_entry;
    using ::x86::long_page_map_entry;
    using ::x86::long_paging;
    using ::x86::get_short_paging;
    using ::x86::get_extended_paging;
    using ::x86::get_long_paging;
    using ::x86::set_paging;
    using ::x86::set_paging;
    using ::x86::set_paging;
    using ::x86::disable_large_pages;
    using ::x86::disable_long_addresses;
    using ::x86::disable_paging;
    using ::x86::enable_large_pages;
    using ::x86::enable_long_addresses;
    using ::x86::enable_paging;
    using ::x86::is_large_pages;
    using ::x86::is_long_addresses;
    using ::x86::is_paging;
}