#include <multiboot2/header.h>


namespace
{
  using namespace multiboot2;

  struct
  {
    header_prologue prologue;
    end_request     end;
  }
  constexpr request __attribute__(( used, section(".multiboot2") )) =
  {
    { architecture_type::x86, sizeof(request), },
    { },
  };
}
