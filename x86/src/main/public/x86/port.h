// Copyright (C) 2016, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

//! @brief Declarations

namespace x86
{
  //! @brief I/O port

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
}

//! @brief Inline definitions

namespace x86
{
  namespace internal
  {
    extern "C" [[gnu::fastcall]] auto __x86_port_read_08 ( ps::size2 address ) -> ps::size1;
    extern "C" [[gnu::fastcall]] auto __x86_port_read_16 ( ps::size2 address ) -> ps::size2;
    extern "C" [[gnu::fastcall]] auto __x86_port_read_32 ( ps::size2 address ) -> ps::size4;
    extern "C" [[gnu::fastcall]] void __x86_port_write_08 ( ps::size1 data, ps::size2 address );
    extern "C" [[gnu::fastcall]] void __x86_port_write_16 ( ps::size2 data, ps::size2 address );
    extern "C" [[gnu::fastcall]] void __x86_port_write_32 ( ps::size4 data, ps::size2 address );
  }

  template <>
  inline
  auto port<1>::read () -> data_type
  {
    return internal::__x86_port_read_08(_address);
  }

  template <>
  inline
  void port<1>::write (data_type data)
  {
    internal::__x86_port_write_08(data, _address);
  }

  template <>
  inline
  auto port<2>::read () -> data_type
  {
    return internal::__x86_port_read_16(_address);
  }

  template <>
  inline
  void port<2>::write (data_type data)
  {
    internal::__x86_port_write_16(data, _address);
  }

  template <>
  inline
  auto port<4>::read () -> data_type
  {
    return internal::__x86_port_read_32(_address);
  }

  template <>
  inline
  void port<4>::write (data_type data)
  {
    internal::__x86_port_write_32(data, _address);
  }
}
