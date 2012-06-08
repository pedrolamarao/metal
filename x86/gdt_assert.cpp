#include "gdt.h"


static_assert(__is_standard_layout(x86::segment_descriptor), "x86::segment_descriptor is not standard layout");

static_assert(__is_trivial(x86::segment_descriptor), "x86::segment_descriptor is not trivial");
