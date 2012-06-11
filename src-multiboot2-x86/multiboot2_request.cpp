#include <multiboot2/multiboot2.h>


using namespace multiboot2;


//! Multiboot2 information request object

struct
{
  request_header     header;
  request_entry_base last;
}
request __attribute__(( used, aligned(8), section(".multiboot2") )) =
{
  {
    request_magic,
    request_architecture::x86,
    sizeof(request),
    (- (request_magic + (uint32_t)(request_architecture::x86) + sizeof(request))),
  },
  {
    request_type::end,
    request_flag::none,
    8,
  },
};
