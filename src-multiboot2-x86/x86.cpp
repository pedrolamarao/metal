// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <aasgard/x86/gdt.h>

#include "x86.h"

using namespace x86;

//! Global descriptor table adequate for SYSENTER/SYSEXIT

segment_descriptor global_descriptor_table [5] __attribute__(( used, aligned(8), section(".gdt") )) =
{
  segment_descriptor { },
  segment_descriptor { 0, 0xFFFFFFFF, code_segment_access(true, false, 0), segment_granularity(false, true, true) },
  segment_descriptor { 0, 0xFFFFFFFF, data_segment_access(true, false, 0), segment_granularity(false, true, true) },
  segment_descriptor { 0, 0xFFFFFFFF, code_segment_access(true, false, 3), segment_granularity(false, true, true) },
  segment_descriptor { 0, 0xFFFFFFFF, data_segment_access(true, false, 3), segment_granularity(false, true, true) },
};

void load_global_descriptor_table ()
{
  x86::load_global_descriptor_table(global_descriptor_table, 5);
  x86::reload_segment_registers(1, 2);
}
