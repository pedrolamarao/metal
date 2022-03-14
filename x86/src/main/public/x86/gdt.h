// Copyright (C) 2012,2013,2014,2015,2016,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>

#include <x86/common.h>

#include <x86/_32/segment.h>
#include <x86/_64/segment.h>


// Interface.

namespace x86
{
  using ps::size1;
  using ps::size2;
  using ps::size4;

  //! Types.
  //! @{

  //! Code segment descriptor type.

  constexpr
  auto code_segment ( bool conforming, bool readable, bool accessed ) -> descriptor_type ;

  //! Data segment descriptor type.

  constexpr
  auto data_segment ( bool downwards, bool writable, bool accessed ) -> descriptor_type ;

  //! @}

  //! Operators.
  //! @{

  //! Get code segment register.

  auto get_code_segment_register () -> segment_selector ;

  //! Set code segment register.

  void set_code_segment_register ( segment_selector value );

  //! Set data segment register.

  void set_data_segment_register ( segment_selector value );

  //! Set stack segment register.

  void set_stack_segment_register ( segment_selector value );

  //! Set extra segment registers.

  void set_extra_segment_registers ( segment_selector value );

  //! @}
}

// Implementation.

namespace x86
{
  constexpr inline
  auto code_segment ( bool conforming, bool readable, bool accessed ) -> descriptor_type {
    return (1 << 3) | (conforming << 2) | (readable << 1) | accessed;
  }

  constexpr inline
  auto data_segment ( bool downwards, bool writable, bool accessed ) -> descriptor_type {
    return (0 << 3) | (downwards << 2) | (writable << 1) | accessed;
  }
}