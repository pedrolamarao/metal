// Copyright (C) 2016,2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

import br.dev.pedrolamarao.metal.psys;

namespace pc
{
    enum class pic_buffering : ps::size1
    {
        none   = 0,
        slave  = 0x08,
        master = 0x0C,
    };

    enum class pic_read : ps::size1
    {
        ignore = 0,
        ir     = 2,
        is     = 3,
    };

    enum class pic_mask : ps::size1
    {
        ignore = 0,
        unset  = 0x20,
        set    = 0x30,
    };

    //! @brief PIC controller

    template <template <unsigned Width> typename Port>
        requires ps::is_port<Port, 1>
    class pic
    {
    protected:

        Port<1> _command;
        Port<1> _data;

    public:

        using port_address = typename Port<1>::address_type;

        //! @brief Object
        //! @{

        constexpr
        pic (port_address command, port_address data) : _command { command }, _data { data } {}

        //! @}

        //! @brief Initialization
        //! @{

        //! @brief Initialization command word 1 (ICW1) — initialize

        void icw1 (bool icw4, bool single, bool level)
        {
            ps::size1 value = (icw4 ? 1 : 0) | (single ? 2 : 0) | (level ? 8 : 0) | 16;
            _command.write(value);
        }

        //! @brief Initialization command word 2 (ICW2) — interrupt offset

        void icw2 (ps::size1 offset)
        {
            _data.write(offset);
        }

        //! @brief Initialization command word 4 (ICW4) — miscellaneous

        void icw4 (bool x86, bool aeoi, pic_buffering buffering, bool sfnm)
        {
            ps::size1 value = (x86 ? 1 : 0) | (aeoi ? 2 : 0) | (ps::size1(buffering) & 0x0C) | (sfnm ? 16 : 0);
            _data.write(value);
        }

        //! @}

        //! @brief Operation
        //! @{

        //! @brief Operational command word 1 (OCW1) — interrupt masking

        void ocw1 (ps::size1 mask)
        {
            _data.write(mask);
        }

        //! @brief Operational command word 2 (OCW2) — end of interrupt

        void ocw2 (ps::size1 level, bool eoi, bool specific, bool rotate)
        {
            ps::size1 value = (level & 0x07) | (eoi ? 8 : 0) | (specific ? 16 : 0) | (rotate ? 32 : 0);
            _command.write(value);
        }

        //! @brief Operational command word 3 (OCW3) — register access

        void ocw3 (pic_read read, bool poll, pic_mask mask)
        {
            ps::size1 value = (ps::size1(read) & 0x03) | (poll ? 4 : 0) | 8 | (ps::size1(mask) & 0x30);
            _command.write(value);
        }

        //! @}

        //! @brief Properties
        //! @{

        ps::size1 in_service ()
        {
            ocw3(pic_read::is, true, pic_mask::ignore);
            // #XXX: wait? how?
            return _command.read();
        }

        ps::size1 mask ()
        {
            return _data.read();
        }

        void mask (ps::size1 value)
        {
            _data.write(value);
        }

        //! @}
    };

    template <template <unsigned Width> typename Port>
    class master_pic : public pic<Port>
    {
    public:

        using port_address = typename pic<Port>::port_address;

        constexpr
        master_pic (port_address command, port_address data) : pic<Port> { command, data } { }

        //! @brief Initialization command word 3 (ICW3) — slave lines

        void icw3 (ps::size1 slaves)
        {
            pic<Port>::_data.write(slaves);
        }

    };

    template <template <unsigned Width> typename Port>
    class slave_pic : public pic<Port>
    {
    public:

        using port_address = typename pic<Port>::port_address;

        constexpr
        slave_pic (port_address command, port_address data) : pic<Port> { command, data } { }

        //! @brief Initialization command word 3 (ICW3) — slave id

        void icw3 (ps::size1 id)
        {
            ps::size1 value = (id & 7);
            pic<Port>::_data.write(value);
        }

    };
}
