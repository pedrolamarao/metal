#pragma once


#include <stdint.h>


#if __cplusplus < 201103L
# define constexpr
# define nullptr (static_cast<void*>(0))
#endif


template <typename T>
inline constexpr
auto is_aligned ( T * address, uint32_t alignment ) -> bool
{
  return ((uint32_t)(address) & (alignment - 1)) == 0 ;
}
