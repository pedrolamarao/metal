#include <gtest/gtest.h>

#include <x86/_32/interrupts.h>
#include <x86/_64/interrupts.h>


namespace
{
    TEST(interrupt_32, zero)
    {
        ps::size1 bytes [8] {
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
        };

        auto& descriptor = reinterpret_cast<x86::short_interrupt_gate_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{},descriptor.segment());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_trap());
    }

    TEST(interrupt_32, max)
    {
        ps::size1 bytes [8] {
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
        };

        auto& descriptor = reinterpret_cast<x86::short_interrupt_gate_descriptor&>(bytes);

        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0xFFFFFFFF,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{0xFFFF},descriptor.segment());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_trap());
    }

    TEST(interrupt_32, offset)
    {
        auto offset = 0x76543210;

        ASSERT_EQ(0x76, (offset >> 24) & 0xFF);
        ASSERT_EQ(0x54, (offset >> 16) & 0xFF);
        ASSERT_EQ(0x32, (offset >>  8) & 0xFF);
        ASSERT_EQ(0x10, (offset >>  0) & 0xFF);

        ps::size1 bytes [8] {
            0x10, 0x32, 0x00, 0x00,
            0x00, 0x00, 0x54, 0x76,
        };

        auto& descriptor = reinterpret_cast<x86::short_interrupt_gate_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(offset,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{},descriptor.segment());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_trap());
    }

    TEST(interrupt_32, segment)
    {
        ps::size2 segment = 0x3210;

        ASSERT_EQ(0x32, (segment >> 8) & 0xFF);
        ASSERT_EQ(0x10, (segment >> 0) & 0xFF);

        ps::size1 bytes [8] {
            0x00, 0x00, 0x10, 0x32,
            0x00, 0x00, 0x00, 0x00,
        };

        auto& descriptor = reinterpret_cast<x86::short_interrupt_gate_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{segment},descriptor.segment());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_trap());
    }

    TEST(interrupt_32, is_32bit)
    {
        ps::size1 bytes [8] {
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x04, 0x00, 0x00,
        };

        auto& descriptor = reinterpret_cast<x86::short_interrupt_gate_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(4,descriptor.type());
        ASSERT_EQ(0,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{},descriptor.segment());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_trap());
    }

    TEST(interrupt_32, is_trap)
    {
        ps::size1 bytes [8] {
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x01, 0x00, 0x00,
        };

        auto& descriptor = reinterpret_cast<x86::short_interrupt_gate_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(1,descriptor.type());
        ASSERT_EQ(0,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{},descriptor.segment());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_trap());
    }

    TEST(interrupt_64, zero)
    {
        ps::size1 bytes [16] {
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
        };

        auto& descriptor = reinterpret_cast<x86::long_interrupt_gate_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{},descriptor.segment());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_trap());
    }

    TEST(interrupt_64, max)
    {
        ps::size1 bytes [16] {
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
        };

        auto& descriptor = reinterpret_cast<x86::long_interrupt_gate_descriptor&>(bytes);

        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0xFFFFFFFFFFFFFFFF,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{0xFFFF},descriptor.segment());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_trap());
    }

    TEST(interrupt_64, offset)
    {
        ps::size8 offset = 0xFEDCBA9876543210;

        ASSERT_EQ(0xFE, (offset >> 56) & 0xFF);
        ASSERT_EQ(0xDC, (offset >> 48) & 0xFF);
        ASSERT_EQ(0xBA, (offset >> 40) & 0xFF);
        ASSERT_EQ(0x98, (offset >> 32) & 0xFF);
        ASSERT_EQ(0x76, (offset >> 24) & 0xFF);
        ASSERT_EQ(0x54, (offset >> 16) & 0xFF);
        ASSERT_EQ(0x32, (offset >>  8) & 0xFF);
        ASSERT_EQ(0x10, (offset >>  0) & 0xFF);

        ps::size1 bytes [16] {
            0x10, 0x32, 0x00, 0x00,
            0x00, 0x00, 0x54, 0x76,
            0x98, 0xBA, 0xDC, 0xFE,
            0x00, 0x00, 0x00, 0x00,
        };

        auto& descriptor = reinterpret_cast<x86::long_interrupt_gate_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(offset,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{},descriptor.segment());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_trap());
    }

    TEST(interrupt_64, segment)
    {
        ps::size2 segment = 0x3210;

        ASSERT_EQ(0x32, (segment >> 8) & 0xFF);
        ASSERT_EQ(0x10, (segment >> 0) & 0xFF);

        ps::size1 bytes [16] {
            0x00, 0x00, 0x10, 0x32,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
        };

        auto& descriptor = reinterpret_cast<x86::long_interrupt_gate_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{segment},descriptor.segment());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_trap());
    }

    TEST(interrupt_64, is_32bit)
    {
        ps::size1 bytes [16] {
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x04, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
        };

        auto& descriptor = reinterpret_cast<x86::long_interrupt_gate_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(4,descriptor.type());
        ASSERT_EQ(0,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{},descriptor.segment());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_trap());
    }

    TEST(interrupt_64, is_trap)
    {
        ps::size1 bytes [16] {
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x01, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
        };

        auto& descriptor = reinterpret_cast<x86::long_interrupt_gate_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(1,descriptor.type());
        ASSERT_EQ(0,descriptor.offset());
        ASSERT_EQ(x86::segment_selector{},descriptor.segment());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_trap());
    }
}