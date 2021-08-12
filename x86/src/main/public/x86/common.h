// Copyright (C) 2012,2013,2014,2015,2016,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>


//! Declarations

namespace x86
{
  //! System table registers
  //!
  //! Value for system table registers.

  struct [[gnu::packed]] system_table_register
  {
    ps::size2 size;
    ps::size4 offset;
  };

  static_assert(sizeof(system_table_register) == 6, "unexpected size of system_table_register");

  bool operator== (system_table_register x, system_table_register y);
}

//! Definitions

namespace x86
{
  inline
  bool operator== ( system_table_register x, system_table_register y )
  {
    return x.size == y.size && x.offset == y.offset;
  }

  inline
  bool operator!= ( system_table_register x, system_table_register y )
  {
    return x.size != y.size || x.offset != y.offset;
  }
}