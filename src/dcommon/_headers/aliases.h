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

#ifndef __DC_BYPASS_PRIVATE_PROTECTION
#error                                                                         \
    "You cannot use this header (aliases.h) directly, please consider including dcommon.h"
#endif

#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>

// ***************************************************************************************
// * GENERAL DECLARATIONS
// ***************************************************************************************

typedef enum
{
    DC_HALT_MODE_CONTINUE,
    DC_HALT_MODE_ABORT,
} DCHaltMode;

// ***************************************************************************************
// * PRIMITIVE TYPES DECLARATIONS
// ***************************************************************************************

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef uintptr_t uptr;

typedef ptrdiff_t size;
typedef size_t usize;

typedef char* string;

typedef void* voidptr;

// ***************************************************************************************
// * DYNAMIC ARRAY TYPE DECLARATIONS
// ***************************************************************************************

typedef enum
{
    DC_DYN_VAL_TYPE_i8,
    DC_DYN_VAL_TYPE_i16,
    DC_DYN_VAL_TYPE_i32,
    DC_DYN_VAL_TYPE_i64,

    DC_DYN_VAL_TYPE_u8,
    DC_DYN_VAL_TYPE_u16,
    DC_DYN_VAL_TYPE_u32,
    DC_DYN_VAL_TYPE_u64,

    DC_DYN_VAL_TYPE_f32,
    DC_DYN_VAL_TYPE_f64,

    DC_DYN_VAL_TYPE_uptr,
    DC_DYN_VAL_TYPE_char,
    DC_DYN_VAL_TYPE_string,
    DC_DYN_VAL_TYPE_voidptr,
    DC_DYN_VAL_TYPE_size,
    DC_DYN_VAL_TYPE_usize,
} DCDynValueType;

typedef struct
{
    DCDynValueType type;
    bool allocated;
    union
    {
        i8 i8_val;
        i16 i16_val;
        i32 i32_val;
        i64 i64_val;

        u8 u8_val;
        u16 u16_val;
        u32 u32_val;
        u64 u64_val;

        f32 f32_val;
        f64 f64_val;

        uptr uptr_val;
        char char_val;
        string string_val;
        voidptr voidptr_val;

        size size_val;
        usize usize_val;
    } value;
} DCDynValue;

typedef void (*DCDynValFreeFunc)(DCDynValue*);

typedef struct
{
    DCDynValue* elements;
    usize cap;
    usize count;
    usize multiplier;

    DCDynValFreeFunc element_free_func;
} DCDynArr;

// ***************************************************************************************
// * STRING VIEW TYPE DECLARATION
// ***************************************************************************************

typedef struct
{
    string str;
    usize len;
    string cstr;
} DCStringView;

// ***************************************************************************************
// * HASH TABLE TYPE DECLARATIONS
// ***************************************************************************************

typedef struct
{
    voidptr key;
    DCDynValue value;
} DCHashEntry;

typedef u32 (*DCHashFunc)(voidptr);
typedef bool (*DCKeyCompFunc)(voidptr, voidptr);

typedef struct
{
    DCDynArr* container;
    usize cap;
    usize key_count;

    DCHashFunc hash_func;
    DCKeyCompFunc key_cmp_func;
    DCDynValFreeFunc element_free_func;
} DCHashTable;

// ***************************************************************************************
// * MEMORY CLEANUP TYPE DECLARATIONS
// ***************************************************************************************

typedef DCDynArr DCCleanups;

typedef void (*DCCleanupFunc)(voidptr);

typedef struct
{
    voidptr element;
    DCCleanupFunc cleanup_func;
} DCCleanupEntry;

// ***************************************************************************************
// * RETURN TYPE DECLARATIONS
// ***************************************************************************************

typedef enum
{
    DC_RESULT_OK,
    DC_RESULT_ERR,
} DCResultStatus;

typedef struct
{
    u8 code;
    string message;
    bool allocated;
} DCError;

typedef struct
{
    DCResultStatus status;
    union
    {
        DCDynValue value;
        DCError error;
    } data;
} DCResult;

#endif // DC_ALIASES_H
