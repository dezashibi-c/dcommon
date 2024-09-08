// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: aliases.h
//    Date: 2024-09-08
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more
//     information about the licensing of this work. If you have any questions
//     or concerns, please feel free to contact me at the email address provided
//     above.
// ***************************************************************************************
// *  Description: private header file for definition of common type aliases
// *               DO NOT USE THIS DIRECTLY
// ***************************************************************************************

#ifndef DC_ALIASES_H
#define DC_ALIASES_H

#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>

typedef uint8_t u8;
typedef int32_t i32;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef uintptr_t uptr;

typedef char byte;
typedef ptrdiff_t size;
typedef size_t usize;

typedef byte* string;

typedef enum
{
    DC_ERR_MODE_CONTINUE,
    DC_ERR_MODE_STOP,
} DC_ERROR_MODE;

#define DC_ARR_TERMINATOR_u8 UINT8_MAX   // 255
#define DC_ARR_TERMINATOR_i32 INT32_MAX  // 2147483647
#define DC_ARR_TERMINATOR_u32 UINT32_MAX // 4294967295
#define DC_ARR_TERMINATOR_u64 UINT64_MAX // 18446744073709551615

#define DC_ARR_TERMINATOR_f32 NAN
#define DC_ARR_TERMINATOR_f64 NAN

#define DC_ARR_TERMINATOR_uptr NULL
#define DC_ARR_TERMINATOR_string NULL

#define DC_ARR_TERMINATOR_byte '\0'

#define DC_ARR_TERMINATOR_size (size) - 1
#define DC_ARR_TERMINATOR_usize (usize) - 1

// Terminator checks for each type
#define DC_IS_ARR_TERMINATOR_u8(EL) (EL == DC_ARR_TERMINATOR_u8)
#define DC_IS_ARR_TERMINATOR_i32(EL) (EL == DC_ARR_TERMINATOR_i32)
#define DC_IS_ARR_TERMINATOR_u32(EL) (EL == DC_ARR_TERMINATOR_u32)
#define DC_IS_ARR_TERMINATOR_u64(EL) (EL == DC_ARR_TERMINATOR_u64)

#define DC_IS_ARR_TERMINATOR_f32(EL) (isnan(EL))
#define DC_IS_ARR_TERMINATOR_f64(EL) (isnan(EL))

#define DC_IS_ARR_TERMINATOR_uptr(EL) (EL == DC_ARR_TERMINATOR_uptr)
#define DC_IS_ARR_TERMINATOR_string(EL) (EL == DC_ARR_TERMINATOR_string)
#define DC_IS_ARR_TERMINATOR_byte(EL) (EL == DC_ARR_TERMINATOR_byte)

#define DC_IS_ARR_TERMINATOR_size(EL) (EL == DC_ARR_TERMINATOR_size)
#define DC_IS_ARR_TERMINATOR_usize(EL) (EL == DC_ARR_TERMINATOR_usize)

#endif // DC_ALIASES_H
