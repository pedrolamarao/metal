// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>
#include <psys/port.h>


namespace pc
{
    enum class pit_counter : ps::size1
    {
        zero      = 0x01,
        one       = 0x02,
        two       = 0x04,
    };

    enum class pit_access : ps::size1
    {
        low           = 0x10,
        high          = 0x20,
        low_high      = 0x30,
    };

    enum class pit_mode : ps::size1
    {
        interrupt_on_terminal_count     = 0x00,
        hardware_retriggerable_one_shot = 0x02,
        rate_generator                  = 0x04,
        square_wave_generator           = 0x06,
        software_triggered_strobe       = 0x08,
        hardware_triggered_strobe       = 0x0A,
    };

    enum class pit_format : ps::size1
    {
        binary  = 0,
        decimal = 1,
    };

    constexpr inline
    auto pit_configure_command (pit_counter counter, pit_access access, pit_mode mode, pit_format format) -> ps::size1
    {
        return ((static_cast<ps::size1>(counter) << 5) & 0xC0)
                | static_cast<ps::size1>(access)
                | static_cast<ps::size1>(mode)
                | static_cast<ps::size1>(format);
    }

    constexpr inline
    auto pit_latch_command (pit_counter counter) -> ps::size1
    {
        return static_cast<ps::size1>(counter) << 5;
    }

    constexpr inline
    auto pit_read_back_command (bool latch_counter, bool latch_status, pit_counter counter)
    {
        return 0xC0
            | (latch_counter ? 0x20 : 0x00)
            | (latch_status  ? 0x10 : 0x00)
            | (static_cast<ps::size1>(counter) << 1);
    }

    //! @brief Programmable Interval Timer

    template <template <unsigned Width> typename Port>
        requires ps::is_port<Port, 1>
    class pit
    {
    public:

        using port_address = typename Port<1>::address_type;

        pit (port_address counter_0, port_address counter_1, port_address counter_2, port_address command) :
            _counter_0{counter_0}, _counter_1{counter_1}, _counter_2{counter_2}, _command{command}
        { }

        void configure (pit_counter counter, pit_access access, pit_mode mode, pit_format format)
        {
            auto message = pit_configure_command(counter, access, mode, format);
            _command.write(message);
        }

        void latch (pit_counter counter)
        {
            auto message = pit_latch_command(counter);
            _command.write(message);
        }

        void read_back (bool latch_status, bool latch_counter, pit_counter counter)
        {
            auto message = pit_read_back_command(latch_status, latch_counter, counter);
            _command.write(message);
        }

        auto counter_0 ()
        {
            return _counter_0.read();
        }

        void counter_0 (ps::size1 value)
        {
            _counter_0.write(value);
        }

        auto counter_1 ()
        {
            return _counter_1.read();
        }

        void counter_1 (ps::size1 value)
        {
            _counter_1.write(value);
        }

        auto counter_2 ()
        {
            return _counter_2.read();
        }

        void counter_2 (ps::size1 value)
        {
            _counter_2.write(value);
        }

    private:

        Port<1> _counter_0;
        Port<1> _counter_1;
        Port<1> _counter_2;
        Port<1> _command;

    };
}
