Date: 2020-02-01

# summary

The `x86` component supports programming the IA32 processor architecture.

In the future, support for AMD64 shall be added here.

# use

## GDT

In the following example, we define a minimal GDT for x86 protected mode flat memory model. It contains the required null segment descriptor, two segment descriptors (code and data) for ring 0 and two segment descriptors (code and data) for ring 3.

```c++
#include <x86/gdt.h>

using namespace x86;

namespace
{
  constexpr segment_descriptor global_descriptor_table [5] __attribute__(( used, section(".gdt") )) =
  {
    segment_descriptor { },
    segment_descriptor { 0, 0xFFFFFFFF, code_segment_access(true, false, 0), segment_granularity(false, true, true) },
    segment_descriptor { 0, 0xFFFFFFFF, data_segment_access(true, false, 0), segment_granularity(false, true, true) },
    segment_descriptor { 0, 0xFFFFFFFF, code_segment_access(true, false, 3), segment_granularity(false, true, true) },
    segment_descriptor { 0, 0xFFFFFFFF, data_segment_access(true, false, 3), segment_granularity(false, true, true) },
  };
}
```

# architecture

All names are declared in `namespace x86`.

* `cpuid.h`
  * `cpuid`
* `msr.h`
  * `msr`
* `gdt.h`
  * `segment_selector` 
  * `segment_descriptor`
  * `load_global_descriptor_table`
* `idt.h`
* `port.h`

## references

* AMD, "AMD64 Architecture Programmer�s Manual Volume 1: Application Programming" [link](http://support.amd.com/TechDocs/24592.pdf)
* AMD, "AMD64 Architecture Programmer�s Manual Volume 2: System Programming" [link](http://support.amd.com/TechDocs/24593.pdf)
* Intel "Intel� 64 and IA-32 architectures software developer's manual volume 1: Basic architecture" [link](https://software.intel.com/en-us/download/intel-64-and-ia-32-architectures-software-developers-manual-volume-1-basic-architecture)
