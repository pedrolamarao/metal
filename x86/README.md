# aasgard &mdash; Intel x86 Library

## Example

### GDT

In the following example, we define a minimal GDT for x86 protected mode flat memory model. It contains the required null segment descriptor, two segment descriptors (code and data) for ring 0 and two segment descriptors (code and data) for ring 3.

```c++
#include <x86/gdt.h>

using namespace x86;

namespace
{
  constexpr segment_descriptor global_descriptor_table [5] __attribute__(( used, aligned(8), section(".gdt") )) =
  {
    segment_descriptor { },
    segment_descriptor { 0, 0xFFFFFFFF, code_segment_access(true, false, 0), segment_granularity(false, true, true) },
    segment_descriptor { 0, 0xFFFFFFFF, data_segment_access(true, false, 0), segment_granularity(false, true, true) },
    segment_descriptor { 0, 0xFFFFFFFF, code_segment_access(true, false, 3), segment_granularity(false, true, true) },
    segment_descriptor { 0, 0xFFFFFFFF, data_segment_access(true, false, 3), segment_granularity(false, true, true) },
  };
}
```

## Components

All components are declared in `namespace x86`.

* `cpuid.h`
  * `cpuid`
* `msr.h`
  * `msr`
* `gdt.h`
  * `segment_selector` 
  * `segment_descriptor`
  * `load_global_descriptor_table`


## References

* [Intel] &mdash; "Intel 64 and IA-32 Architectures Software Developer's Manual", [:link:](http://www.intel.com/products/processor/manuals/)
* [AMD] &mdash; "AMD64 Architecture Programmer's Manual", [:link:](http://developer.amd.com/resources/documentation-articles/developer-guides-manuals/)
