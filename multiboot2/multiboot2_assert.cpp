#include "multiboot2.h"


static_assert(__is_standard_layout(multiboot2::request_header), "multiboot2::request_header is not standard layout");

static_assert(__is_standard_layout(multiboot2::information_header), "multiboot2::information_header is not standard layout");

static_assert(__is_standard_layout(multiboot2::information_entry_base), "multiboot2::information_entry_base is not standard layout");
