#include <x86/segments.h>

#include <gtest/gtest.h>

namespace
{
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