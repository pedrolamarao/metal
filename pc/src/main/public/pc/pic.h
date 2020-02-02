// Copyright (C) 2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <cstdint>


namespace pc
{
  //! @brief Command words
  //! @{

  //! @brief ICW1 &mdash; initialization command word 1

  constexpr static
  auto icw1 (bool icw4, bool single, bool level) -> std::uint8_t
  {
    return (icw4 ? 1 : 0) | (single ? 2 : 0) | (level ? 8 : 0) | 16;
  }

  //! @brief ICW2 &mdash; initialization command word 2

  constexpr static
  auto icw2 (std::uint8_t offset) -> std::uint8_t
  {
    return offset;
  }

  //! @brief ICW3 &mdash; initialization command word 3

  constexpr static
  auto icw3 (std::uint8_t level_or_id) -> std::uint8_t
  {
    return level_or_id;
  }

  enum icw4_buffering
  {
    no_buffering     = 0,
    slave_buffering  = 0x08,
    master_buffering = 0x0C,
  };

  //! @brief ICW4 &mdash; initialization command word 4

  constexpr static
  auto icw4 (bool x86, bool aeoi, icw4_buffering buffering, bool sfnm) -> std::uint8_t
  {
    return (x86 ? 1 : 0) | (aeoi ? 2 : 0) | (buffering & 0x0C) | (sfnm ? 16 : 0);
  }

  //! @brief OCW1 &mdash; operational command word 1, interrupt masking

  constexpr static
  auto ocw1 (std::uint8_t mask) -> std::uint8_t
  {
    return (mask & 0x7F);
  }

  //! @brief OCW2 &mdash; operational command word 1, end of interrupt

  constexpr static
  auto ocw2 (std::uint8_t level, bool eoi, bool specific, bool rotate) -> std::uint8_t
  {
    return (level & 0x07) | (eoi ? 8 : 0) | (specific ? 16 : 0) | (rotate ? 32 : 0);
  }

  enum ocw3_mask : std::uint8_t
  {
    ignore_mask = 0,
    unset_mask  = 0x20,
    set_mask    = 0x30,
  };

  enum ocw3_read : std::uint8_t
  {
    ignore_read = 0,
    ir_read     = 2,
    is_read     = 3,
  };

  //! @brief OCW3 &mdash; operational command word 3, register access

  constexpr static
  auto ocw3 (ocw3_read read, bool poll, ocw3_mask mask) -> std::uint8_t
  {
    return (read & 0x03) | (poll ? 4 : 0) | 8 | (mask & 0x30);
  }

  //! @}
}
