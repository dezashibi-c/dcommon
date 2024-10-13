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
#error "You cannot use this header (aliases.h) directly, please consider including dcommon.h"
#endif

// ***************************************************************************************
// * RESULT TYPE DECLARATIONS
// ***************************************************************************************

/**
 * Enum for two possible result status, ok and error
 */
typedef enum
{
    DC_RES_OK,
    DC_RES_ERR,
} DCResStatus;

/**
 * Holds error data when the result is an error
 *
 * Notes:
 *
 * 1. There are reserved codes (Not mandatory but `dcommon` follows that)
 * - '1' Null Value detected
 * - '2' Memory management failed, malloc, calloc, realloc, etc.
 * - '3' Unknown type or un-matched type detected
 * - '4' Index out of bound
 * - '5' Internal errors
 * - '6' Not Found
 *
 * NOTE: You can use macros `dc_err` and `dc_err_msg`
 *
 * 2. If message is allocated the `allocated` field must be set to true.
 */
typedef struct
{
    i8 code;
    string message;
    bool allocated;
} DCError;

/**
 * Macro to define new Result type
 *
 * NOTE: See (alias.h) for usage in definition of default result types
 */
#define DCResType(TYPE, NAME)                                                                                                  \
    typedef struct                                                                                                             \
    {                                                                                                                          \
        DCResStatus status;                                                                                                    \
        union                                                                                                                  \
        {                                                                                                                      \
            DCError e;                                                                                                         \
            TYPE v;                                                                                                            \
        } data;                                                                                                                \
    } NAME

/**
 * Minimum structure to be able to be cased and used as a Result is DCResVoid
 */
typedef struct
{
    DCResStatus status;
    union
    {
        DCError e;
    } data;
} DCResVoid;

// ***************************************************************************************
// * DEFAULT PRIMITIVE RESULT TYPE DECLARATIONS
// ***************************************************************************************
DCResType(i8, DCResI8);
DCResType(i16, DCResI16);
DCResType(i32, DCResI32);
DCResType(i64, DCResI64);
DCResType(u8, DCResU8);
DCResType(u16, DCResU16);
DCResType(u32, DCResU32);
DCResType(u64, DCResU64);
DCResType(f32, DCResF32);
DCResType(f64, DCResF64);
DCResType(uptr, DCResUptr);
DCResType(size, DCResSize);
DCResType(usize, DCResUsize);
DCResType(string, DCResString);
DCResType(voidptr, DCResVoidptr);
DCResType(fileptr, DCResFileptr);

DCResType(bool, DCResBool);

// ***************************************************************************************
// * DYNAMIC ARRAY TYPE DECLARATIONS
// ***************************************************************************************

/**
 * All the types that DCDynVal can accept
 */
typedef enum
{
    dc_dvt(i8),
    dc_dvt(i16),
    dc_dvt(i32),
    dc_dvt(i64),

    dc_dvt(u8),
    dc_dvt(u16),
    dc_dvt(u32),
    dc_dvt(u64),

    dc_dvt(f32),
    dc_dvt(f64),

    dc_dvt(uptr),
    dc_dvt(char),
    dc_dvt(size),
    dc_dvt(usize),
    dc_dvt(string),
    dc_dvt(voidptr),
    dc_dvt(fileptr),

#ifdef DC_DV_EXTRA_TYPES
    DC_DV_EXTRA_TYPES
#endif

} DCDynValType;

/**
 * Dynamic value type with ability to keep track of holding allocated string or
 * voidptr for further cleanup
 */
typedef struct
{
    DCDynValType type;
    bool allocated;
    union
    {
        dc_dvf_decl(i8);
        dc_dvf_decl(i16);
        dc_dvf_decl(i32);
        dc_dvf_decl(i64);

        dc_dvf_decl(u8);
        dc_dvf_decl(u16);
        dc_dvf_decl(u32);
        dc_dvf_decl(u64);

        dc_dvf_decl(f32);
        dc_dvf_decl(f64);

        dc_dvf_decl(uptr);
        dc_dvf_decl(char);
        dc_dvf_decl(string);
        dc_dvf_decl(voidptr);
        dc_dvf_decl(fileptr);

        dc_dvf_decl(size);
        dc_dvf_decl(usize);

#ifdef DC_DV_EXTRA_FIELDS
        DC_DV_EXTRA_FIELDS
#endif
    } value;
} DCDynVal;

/**
 * Custom function type for cleaning up a dynamic value
 *
 * As an example a Dynamic value might contain a voidptr to another struct that
 * holds allocated fields and they need to be de-allocated before the actual
 * voidptr value to be freed
 *
 * NOTE: Also the voidptr might be marked as allocated=false but still it's
 * corresponding value that it is pointing to might need to have a clean up
 * process (see dc_dv_free)
 */
typedef DCResVoid (*DCDynValFreeFn)(DCDynVal*);

/**
 * Function type for checking equality of two given pointer to dynamic values
 */
DCDynValOpFnType(DCResBool, DCDVEqFn);

/**
 * Dynamic array with ability to keep any number of dynamic values
 *
 * Initial capacity and multiplication on grow is also customizable
 *
 * Dynamic arrays or Darr for short can be grown, truncated, popped, etc.
 */
typedef struct
{
    DCDynVal* elements;
    usize cap;
    usize count;
    usize multiplier;

    DCDynValFreeFn element_free_fn;
} DCDynArr;

// ***************************************************************************************
// * STRING VIEW TYPE DECLARATION
// ***************************************************************************************

/**
 * It is used to address a portion of a string without memory allocation.
 *
 * NOTE: cstr when initiated will be allocated to the exact copy of the string
 * piece SV pointing to
 */
typedef struct
{
    string str;
    usize len;
    string cstr;
} DCStringView;

// ***************************************************************************************
// * HASH TABLE TYPE DECLARATIONS
// ***************************************************************************************

/**
 * Each entry of a hash table can have a dynamic value
 *
 * NOTE: The key is dynamic value and the correctness of the passed values and types
 *       must be checked in hash and key comparaison functions
 */
typedef struct
{
    DCDynVal key;
    DCDynVal value;
} DCHashEntry;

/**
 * Function pointer type as an acceptable hash function for an Hash Table
 */
typedef DCResU32 (*DCHashFn)(DCDynVal*);

/**
 * Key comparison function type for an Hash Table
 */
typedef DCResBool (*DCKeyCompFn)(DCDynVal*, DCDynVal*);

/**
 * A Hash Table with track of capacity and number of registered keys
 *
 * Container is a fixed (one time allocated) array of dynamic arrays which will
 * help in case any collision happen with different keys
 */
typedef struct
{
    DCDynArr* container;
    usize cap;
    usize key_count;

    DCHashFn hash_fn;
    DCKeyCompFn key_cmp_fn;
    DCDynValFreeFn element_free_fn;
} DCHashTable;

// ***************************************************************************************
// * MEMORY CLEANUP TYPE DECLARATIONS
// ***************************************************************************************

/**
 * It is an alias for regular dynamic array that holds voidptr to multiple
 * DCCleanupJob (a batch of cleanup jobs)
 */
typedef DCDynArr DCCleanupBatch;

/**
 * Is a pool of cleanups that can be triggered at any phase of program life
 * cycle. (a pool of cleanup batches)
 *
 * As an example you might separate your program into multiple phases and
 * you want to have separate batch for each phase, you can use this method.
 *
 * NOTE: The default batch is batch index 0
 */
typedef struct
{
    DCCleanupBatch* pool;
    usize count;
} DCCleanupPool;

/**
 * Function pointer type for acceptable functions in cleanup process
 *
 * NOTE: If a dynamic value has a complex cleanup process you need to create
 * proper function with this signature and register it with the created function
 */
typedef DCResVoid (*DCCleanupFn)(voidptr);

/**
 * Is a memory allocated object that needs to be managed
 */
typedef struct
{
    voidptr element;
    DCCleanupFn cleanup_fn;
} DCCleanupJob;

// ***************************************************************************************
// * DCOMMON CUSTOM TYPES RESULT TYPE DECLARATIONS
// ***************************************************************************************

DCResType(DCDynVal, DCRes);
DCResType(DCStringView, DCResSv);
DCResType(DCDynArr*, DCResDa);
DCResType(DCHashTable*, DCResHt);
DCResType(DCDynVal*, DCResDv);

#endif // DC_ALIASES_H
