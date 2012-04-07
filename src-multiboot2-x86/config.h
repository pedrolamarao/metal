#pragma once

#if __cplusplus < 201103L
# define constexpr
# define nullptr (static_cast<void*>(0))
#endif

typedef signed char int8_t ;

typedef signed short int int16_t ;

typedef signed int int32_t ;

typedef signed long int int64_t ;

typedef unsigned char uint8_t ;

typedef unsigned short int uint16_t ;

typedef unsigned int uint32_t ;

typedef unsigned long int uint64_t ;

typedef decltype((char*)(0) - (char*)(0)) size_t ;
