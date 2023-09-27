// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <psys/integer.h>
#include <psys/move.h>
#include <psys/port.h>

/**
 * PC UART.
 *
 * Implementation for Texas Instruments PC16550D.
 */

namespace pc::uart
{
  using ps::move;
  using ps::size1;
  using ps::size2;

  //! Data types.
  //! @{

  //! Interrupt Enable Register.

  class ier
  {
  public:

    constexpr
    ier ();

    constexpr explicit
    ier (size1 value);

    constexpr explicit
    operator size1 () const;

    //! Received Data Available Interrupt enabled.

    auto erbfi () const -> bool;

    //! Transmitter Holding Register Empty Interrupt enabled.

    auto etbei () const -> bool;

    //! Receiver Line Status Interrupt enabled.

    auto elsi () const -> bool;

    //! MODEM Status Interrupt enabled.

    auto edssi () const -> bool;

  private:

      size1 _value;

  };

  //! Interrupt Identity Register.

  struct iir
  {
  public:

    constexpr
    iir ();

    constexpr explicit
    iir (size1 value);

    //! Interrupt Pending

    auto pending () const -> bool;

    //! Interrupt ID

    auto identifier () const -> size1;

  private:

    size1 _value;

  };

  //! FIFO Control Register.

  struct fcr
  {
  public:

    constexpr
    fcr ();

    constexpr explicit
    fcr (size1 value);

    constexpr explicit
    operator size1 () const;

    //! FIFO enabled.

    auto enabled () const -> bool ;

    //! FIFO enabled.

    auto enabled (bool) -> fcr&& ;

    //! Receiver reset

    auto receiver_reset () const -> bool ;

    //! Receiver reset

    auto receiver_reset (bool) -> fcr&& ;

    //! Transmitter reset

    auto transmitter_reset () const -> bool ;

    //! Transmitter reset

    auto transmitter_reset (bool) -> fcr&& ;

    //! DMA mode

    auto dma () const -> bool ;

    //! Trigger thresold

    auto trigger () const -> size1 ;

    //! Trigger thresold

    auto trigger (size1) -> fcr&& ;

  private:

    size1 _value;

  };

  //! Line Control Register.

  class lcr
  {
  public:

    constexpr
    lcr ();

    constexpr explicit
    lcr (size1 value);

    constexpr explicit
    operator size1 () const;

    //! Word Length

    auto word () const -> size1 ;

    //! Word Length

    auto word (size1) -> lcr&& ;

    //! Stop Bits

    auto stop () const -> bool ;

    //! Stop Bits

    auto stop (bool) -> lcr&& ;

    //! Parity Enable

    auto parity () const -> bool ;

    //! Parity Enable

    auto parity (bool) -> lcr&& ;

    //! Even Parity

    auto even () const -> bool;

    //! Sticky Parity

    auto sticky () const -> bool;

    //! Break Control

    auto break_ () const -> bool;

    //! Get Divisor Latch Access.

    auto dlab () const -> bool;

    //! Set Divisor Latch Access.

    auto dlab (bool) -> lcr&&;

  private:

    size1 _value;

  };

  //! Line Status Register.

  class lsr
  {
  public:

    constexpr
    lsr ();

    constexpr explicit
    lsr (size1 value);

    //! Data Ready

    auto dr () const -> bool;

    //! Overrun Error

    auto oe () const -> bool;

    //! Parity Error

    auto pe () const -> bool;

    //! Framing Error

    auto fe () const -> bool;

    //! Break Interrupt

    auto bi () const -> bool;

    //! Transmitter Holding Register Empty

    auto thre () const -> bool;

    //! Transmitter Shift Register Empty

    auto temt () const -> bool;

    //! Error in Receiver FIFO

    auto lsr7 () const -> bool;

  private:

    size1 _value;

  };

  //! Modem Control Register.

  class mcr
  {
  public:

    constexpr
    mcr ();

    constexpr explicit
    mcr (size1 value);

    constexpr explicit
    operator size1 () const;

    //! Loopback enabled.

    auto loopback () const -> bool ;

    //! Loopback enabled.

    auto loopback (bool) -> mcr &&;

  private:

    size1 _value;

  };

  //! @}

  //! Interface types.
  //! @{

  //! UART interface.

  template <template <unsigned Width> class Port>
    requires ps::is_port<Port, 1>
  class uart
  {
  public:

    using port_address = typename Port<1>::address_type;

    constexpr explicit
    uart (port_address base);

    //! Set Receiver Buffer Register.

    auto rbr () -> size1;

    //! Set Transmitter Holding Register.

    void thr (size1 value);

    //! Get Interrupt Enable Register.

    auto ier () -> pc::uart::ier;

    //! Set Interrupt Enable Register.

    void ier (pc::uart::ier value);

    //! Get Interrupt Identity Register.

    auto iir () -> pc::uart::iir;

    //! Set FIFO Control Register.

    void fcr (pc::uart::fcr value);

    //! Get Line Control Register.

    auto lcr () -> pc::uart::lcr;

    //! Set Line Control Register.

    void lcr (pc::uart::lcr value);

    //! Get MODEM Control Register.

    auto mcr () -> pc::uart::mcr;

    //! Set MODEM Control Register.

    void mcr (pc::uart::mcr value);

    //! Get Line Status Register.

    auto lsr () -> pc::uart::lsr;

    //! Set Line Status Register.

    void lsr (pc::uart::lsr value);

    //! Get MODEM Status Register.

    auto msr () -> ps::size1;

    //! Set MODEM Status Register.

    void msr (ps::size1 value);

    //! Get Scratch Register.

    auto scr () -> ps::size1;

    //! Set Scratch Register.

    void scr (ps::size1 value);

    //! Get Divisor Latch (least-significant).

    auto dll () -> ps::size1;

    //! Set Divisor Latch (least-significant).

    void dll (ps::size1 value);

    //! Get Divisor Latch (most-significant).

    auto dlm () -> ps::size1;

    //! Set Divisor Latch (most-significant).

    void dlm (ps::size1 value);

  private:

    Port<1> _port_0;
    Port<1> _port_1;
    Port<1> _port_2;
    Port<1> _port_3;
    Port<1> _port_4;
    Port<1> _port_5;
    Port<1> _port_6;
    Port<1> _port_7;

  };

  //! @}

  //! Procedures.
  //! @{

  template <typename UART>
  void set_divisor_latch (UART & uart, size2 value);

  //! @}
}

// Definitions

namespace pc::uart
{
  // Data types.

  // Interrupt Enable Register.

  constexpr inline
  ier::ier () = default;

  constexpr inline
  ier::operator size1 () const { return _value; }

  // FIFO Control Register.

  constexpr inline
  fcr::fcr () = default;

  constexpr inline
  fcr::operator size1 () const { return _value; }

  inline
  auto fcr::enabled (bool value) -> fcr&& { _value |= value << 0; return move(*this); }

  inline
  auto fcr::receiver_reset (bool value) -> fcr&& { _value |= value << 1; return move(*this); }

  inline
  auto fcr::transmitter_reset (bool value) -> fcr&& { _value |= value << 2; return move(*this); }

  inline
  auto fcr::trigger (size1 value) -> fcr&& { _value |= (value & 0x03) << 6; return move(*this); }

  // Line Control Register.

  constexpr inline
  lcr::lcr () = default;

  constexpr inline
  lcr::operator size1 () const { return _value; }

  inline
  auto lcr::word (size1 value) -> lcr&& { _value |= (value & 0x03) << 0; return move(*this); }

  inline
  auto lcr::dlab (bool value) -> lcr&& { _value |= value << 7; return move(*this); }
  
  //! Modem Control Register.

  constexpr inline
  mcr::mcr () = default;

  constexpr inline
  mcr::operator size1 () const { return _value; }

  inline
  auto mcr::loopback (bool value) -> mcr&& { _value |= value << 4; return move(*this); }

  // Interface types.

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  constexpr
  uart<Port>::uart (port_address base) :
    _port_0(base+0), _port_1(base+1), _port_2(base+2), _port_3(base+3),
    _port_4(base+4), _port_5(base+5), _port_6(base+6), _port_7(base+7)
  { }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  auto uart<Port>::rbr () -> size1
  {
    return _port_0.read();
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  void uart<Port>::thr (size1 value)
  {
    _port_0.write(value);
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  auto uart<Port>::ier () -> pc::uart::ier
  {
    return pc::uart::ier{ _port_1.read() };
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  void uart<Port>::ier (pc::uart::ier value)
  {
    _port_1.write( size1{value} );
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  auto uart<Port>::iir () -> pc::uart::iir
  {
    return pc::uart::iir{ _port_2.read() };
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  void uart<Port>::fcr (pc::uart::fcr value)
  {
    _port_2.write( size1{value} );
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  auto uart<Port>::lcr () -> pc::uart::lcr
  {
    return pc::uart::lcr{ _port_3.read() };
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  void uart<Port>::lcr (pc::uart::lcr value)
  {
    _port_3.write( size1{value} );
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  auto uart<Port>::mcr () -> pc::uart::mcr
  {
    return pc::uart::mcr{ _port_4.read() };
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  void uart<Port>::mcr (pc::uart::mcr value)
  {
    _port_4.write( size1{value} );
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  auto uart<Port>::lsr () -> pc::uart::lsr
  {
    return pc::uart::lsr{ _port_5.read() };
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  void uart<Port>::lsr (pc::uart::lsr value)
  {
    _port_5.write(value);
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  auto uart<Port>::scr () -> size1
  {
    return _port_5.read();
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  void uart<Port>::scr (size1 value)
  {
    _port_5.write(value);
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  auto uart<Port>::dll () -> size1
  {
    return _port_0.read();
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  void uart<Port>::dll (size1 value)
  {
    _port_0.write(value);
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  auto uart<Port>::dlm () -> size1
  {
    return _port_1.read();
  }

  template <template <unsigned With> class Port>
    requires ps::is_port<Port, 1>
  void uart<Port>::dlm (size1 value)
  {
    _port_1.write(value);
  }

  // Procedures.

  template <typename UART>
  void set_divisor_latch (UART & uart, size2 value)
  {
    auto least = (value >> 0) & 0x00FF;
    auto most  = (value >> 8) & 0x00FF;
    uart.dll(least);
    uart.dlm(most);
  }
}