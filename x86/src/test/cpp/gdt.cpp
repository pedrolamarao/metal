#include <x86/gdt.h>

#include <gtest/gtest.h>

namespace
{
    TEST(gdt, segment_descriptor)
    {
        auto null_segment = x86::segment_descriptor { 0, 0, 0, 0, false, false, false, false };
        ASSERT_EQ( 0U, null_segment.base() );
        ASSERT_EQ( 0U, null_segment.limit() );
        ASSERT_FALSE( null_segment.is_available() );
        ASSERT_FALSE( null_segment.is_present() );
        ASSERT_FALSE( null_segment.is_4kb() );
        ASSERT_FALSE( null_segment.is_32bit() );
        ASSERT_FALSE( null_segment.is_64bit() );

        auto flat_code_segment = x86::segment_descriptor {
            0, 0xFFFFF,
            0b1000, 0,
            true, true, true, true
        };
        ASSERT_EQ( 0, flat_code_segment.base() );
        ASSERT_EQ( 0xFFFFF, flat_code_segment.limit() );
        ASSERT_TRUE( flat_code_segment.is_available() );
        ASSERT_TRUE( flat_code_segment.is_present() );
        ASSERT_TRUE( flat_code_segment.is_4kb() );
        ASSERT_TRUE( flat_code_segment.is_32bit() );
        ASSERT_FALSE( flat_code_segment.is_64bit() );
    }

    TEST(gdt, code_segment)
    {
        ASSERT_EQ( 0b1000, x86::code_segment(false, false, false) );
        ASSERT_EQ( 0b1100, x86::code_segment(true, false, false) );
        ASSERT_EQ( 0b1010, x86::code_segment(false, true, false) );
        ASSERT_EQ( 0b1001, x86::code_segment(false, false, true) );
        ASSERT_EQ( 0b1111, x86::code_segment(true, true, true) );
    }

    TEST(gdt, data_segment)
    {
        ASSERT_EQ( 0b0000, x86::data_segment(false, false, false) );
        ASSERT_EQ( 0b0100, x86::data_segment(true, false, false) );
        ASSERT_EQ( 0b0010, x86::data_segment(false, true, false) );
        ASSERT_EQ( 0b0001, x86::data_segment(false, false, true) );
        ASSERT_EQ( 0b0111, x86::data_segment(true, true, true) );
    }
}