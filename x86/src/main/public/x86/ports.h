// Copyright (C) 2016,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/instructions.h>


//! Interface

namespace x86
{
  //! Interface types.
  //! @{

  //! I/O port.

  template <unsigned ByteWidth>
    requires (ByteWidth == 1 || ByteWidth == 2 || ByteWidth == 4)
  class port
  {
  public:

    using address_type = unsigned _ExtInt(16);

    using data_type = unsigned _ExtInt(ByteWidth * 8);

    constexpr
    port ( address_type address ) : _address{address} {}

    auto read () -> data_type;

    void write (data_type data);

  private:

    address_type _address;

  };

  //! @}
}

//! @brief Inline definitions

namespace x86
{
  template <>
  inline
  auto port<1>::read () -> data_type
  {
    return in1(_address);
  }

  template <>
  inline
  void port<1>::write (data_type data)
  {
    out1(_address, data);
  }

  template <>
  inline
  auto port<2>::read () -> data_type
  {
    return in2(_address);
  }

  template <>
  inline
  void port<2>::write (data_type data)
  {
    out2(_address, data);
  }

  template <>
  inline
  auto port<4>::read () -> data_type
  {
    return in4(_address);
  }

  template <>
  inline
  void port<4>::write (data_type data)
  {
    out4(_address, data);
  }
}
