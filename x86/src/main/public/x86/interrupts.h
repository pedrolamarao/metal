// Copyright (C) 2012,2013,2014,2015,2016,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>

#include <x86/_32/interrupts.h>
#include <x86/_64/interrupts.h>


//! Declarations

namespace x86
{
    //! Operators.
    //! @{

    //! Enable interrupts on this processor.

    void enable_interrupts ();

    //! Disables interrupts on this processor.

    void cli ();

    //! Interrupt this processor.

    template <unsigned N>
    void interrupt ();

    //! @}
}

//! Definitions

namespace x86
{
  template <unsigned N>
  inline
  void interrupt ()
  {
    __asm__ volatile ("int %0" : : "N"(N) : "cc", "memory");
  }
}