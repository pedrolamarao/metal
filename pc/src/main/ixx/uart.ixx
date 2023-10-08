// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <pc/uart.h>

export module br.dev.pedrolamarao.metal.pc:uart;

export namespace pc::uart
{
  using ::pc::uart::ier;
  using ::pc::uart::iir;
  using ::pc::uart::fcr;
  using ::pc::uart::lcr;
  using ::pc::uart::lsr;
  using ::pc::uart::mcr;
  using ::pc::uart::uart;
  using ::pc::uart::set_divisor_latch;
}