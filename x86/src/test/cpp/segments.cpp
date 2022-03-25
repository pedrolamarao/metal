#include <gtest/gtest.h>

#include <x86/_32/segment.h>
#include <x86/_64/segment.h>


namespace
{
    TEST(segment_32, base)
    {
        auto base = 0x76543210;

        ASSERT_EQ(0x76, (base >> 24) & 0xFF);
        ASSERT_EQ(0x54, (base >> 16) & 0xFF);
        ASSERT_EQ(0x32, (base >>  8) & 0xFF);
        ASSERT_EQ(0x10, (base >>  0) & 0xFF);

        ps::size1 bytes [8] {
            0x00, 0x00, 0x10, 0x32,
            0x54, 0x00, 0x00, 0x76,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(base,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, limit)
    {
        auto limit = 0x0EDCBA;

        ASSERT_EQ(0x0E, (limit >> 16) & 0xFF);
        ASSERT_EQ(0xDC, (limit >>  8) & 0xFF);
        ASSERT_EQ(0xBA, (limit >>  0) & 0xFF);

        ps::size1 bytes [8] {
            0xBA, 0xDC, 0x00, 0x00,
            0x00, 0x00, 0x0E, 0x00,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(limit,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, is_present)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b10000000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_TRUE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, privilege)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b01000000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(2,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, is_system)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b00010000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, type)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b00001000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(8,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, is_4kb)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0, 0b10000000, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_32, is_32bit)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0, 0b01000000, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, max)
    {
        ps::size1 bytes [8] {
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0xFFFFFFFF,descriptor.base());
        ASSERT_EQ(0xFFFFF,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_32, zero)
    {
        x86::_32::segment_descriptor descriptor {};
        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, flat)
    {
        x86::_32::segment_descriptor descriptor { 0, 0xFFFFF, 15, 3, true, true, true, true, };
        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0xFFFFF,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_32, weird)
    {
        x86::_32::segment_descriptor descriptor { 0x76543210, 0x0EDCBA, 15, 3, true, true, true, true, };
        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0x76543210,descriptor.base());
        ASSERT_EQ(0x0EDCBA,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_64, base)
    {
        auto base = 0xFEDCBA9876543210;

        ASSERT_EQ(0xFE, (base >> 56) & 0xFF);
        ASSERT_EQ(0xDC, (base >> 48) & 0xFF);
        ASSERT_EQ(0xBA, (base >> 40) & 0xFF);
        ASSERT_EQ(0x98, (base >> 32) & 0xFF);
        ASSERT_EQ(0x76, (base >> 24) & 0xFF);
        ASSERT_EQ(0x54, (base >> 16) & 0xFF);
        ASSERT_EQ(0x32, (base >>  8) & 0xFF);
        ASSERT_EQ(0x10, (base >>  0) & 0xFF);

        ps::size1 bytes [16] {
            0x00, 0x00, 0x10, 0x32,
            0x54, 0x00, 0x00, 0x76,
            0x98, 0xBA, 0xDC, 0xFE,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(base,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, limit)
    {
        auto limit = 0x0EDCBA;

        ASSERT_EQ(0x0E, (limit >> 16) & 0xFF);
        ASSERT_EQ(0xDC, (limit >>  8) & 0xFF);
        ASSERT_EQ(0xBA, (limit >>  0) & 0xFF);

        ps::size1 bytes [16] {
            0xBA, 0xDC, 0x00, 0x00,
            0x00, 0x00, 0x0E, 0x00,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(limit,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, is_present)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b10000000, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_TRUE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, privilege)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b01000000, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(2,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, is_system)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b00010000, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, type)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b00001000, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(8,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, is_4kb)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0, 0b10000000, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_64, is_32bit)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0, 0b01000000, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, max)
    {
        ps::size1 bytes [16] {
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0xFFFFFFFFFFFFFFFF,descriptor.base());
        ASSERT_EQ(0xFFFFF,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_64, zero)
    {
        x86::_64::segment_descriptor descriptor {};
        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, flat)
    {
        x86::_64::segment_descriptor descriptor { 0, 0xFFFFF, 15, 3, true, true, true, true, };
        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0xFFFFF,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_64, weird)
    {
        x86::_64::segment_descriptor descriptor { 0xFEDCBA9876543210, 0x0EDCBA, 15, 3, true, true, true, true, };
        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0xFEDCBA9876543210,descriptor.base());
        ASSERT_EQ(0x0EDCBA,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }
}