// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: macros.h
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
// *  Description: private header file for definition of common macros
// *               DO NOT USE THIS DIRECTLY
// ***************************************************************************************

#ifndef DC_MACROS_H
#define DC_MACROS_H

#ifndef __DC_BYPASS_PRIVATE_PROTECTION
#error "You cannot use this header (macros.h) directly, please consider including dcommon.h"
#endif

// ***************************************************************************************
// * DETECT OPERATING SYSTEM MACROS
// *    This sections define proper operating system and operating system_arch
// *    macros
// ***************************************************************************************

// clang-format off
#if defined(_WIN32) || defined(_WIN64)
    #define DC_WINDOWS
    #if defined(_M_X64)
        #define DC_WINDOWS_X64
    #elif defined(_M_IX86)
        #define DC_WINDOWS_X86
    #elif defined(_M_ARM64)
        #define DC_WINDOWS_ARM64
    #elif defined(_M_ARM)
        #define DC_WINDOWS_ARM
    #endif
#elif defined(__APPLE__) && defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC == 1
        #define DC_MACOS
        #if defined(__x86_64__) || defined(__aarch64__)
            #define DC_MACOS_X64
        #else
            #define DC_MACOS_X86
        #endif
    #endif
#elif defined(__linux__)
    #define DC_LINUX
    #if defined(__x86_64__)
        #define DC_LINUX_X64
    #elif defined(__aarch64__)
        #define DC_LINUX_ARM64
    #elif defined(__arm__)
        #define DC_LINUX_ARM
    #else
        #define DC_LINUX_X86
    #endif
#elif defined(__ANDROID__)
    #define DC_ANDROID
    #if defined(__x86_64__)
        #define DC_ANDROID_X64
    #elif defined(__aarch64__)
        #define DC_ANDROID_ARM64
    #elif defined(__arm__)
        #define DC_ANDROID_ARM
    #else
        #define DC_ANDROID_X86
    #endif
#elif defined(__unix__)
    #define DC_UNIX
    #if defined(__x86_64__)
        #define DC_UNIX_X64
    #elif defined(__aarch64__)
        #define DC_UNIX_ARM64
    #elif defined(__arm__)
        #define DC_UNIX_ARM
    #else
        #define DC_UNIX_X86
    #endif
#endif
// clang-format on

// ***************************************************************************************
// * PRIMITIVE TYPES TO BOOLEAN CONVERTER MACROS
// ***************************************************************************************

/**
 * Returns boolean equivalent value (true/false or 1/0) for given type and
 * value.
 *
 * @example dc_as_bool(u8, 10); // true
 * @example dc_as_bool(voidptr, NULL); // false
 */
#define dc_as_bool(TYPE, VAL) dc_##TYPE##_as_bool(VAL)

#define dc_u8_as_bool(VAL) ((bool)(VAL))
#define dc_u16_as_bool(VAL) ((bool)(VAL))
#define dc_u32_as_bool(VAL) ((bool)(VAL))
#define dc_u64_as_bool(VAL) ((bool)(VAL))
#define dc_i8_as_bool(VAL) ((bool)(VAL))
#define dc_i16_as_bool(VAL) ((bool)(VAL))
#define dc_i32_as_bool(VAL) ((bool)(VAL))
#define dc_i64_as_bool(VAL) ((bool)(VAL))
#define dc_f32_as_bool(VAL) ((bool)(VAL))
#define dc_f64_as_bool(VAL) ((bool)(VAL))

#define dc_uptr_as_bool(VAL) ((VAL) != 0)
#define dc_char_as_bool(VAL) ((VAL) != '\0')
#define dc_string_as_bool(VAL) ((VAL) != NULL && *(VAL) != '\0')
#define dc_voidptr_as_bool(VAL) ((VAL) != NULL)
#define dc_fileptr_as_bool(VAL) ((VAL) != NULL)
#define dc_size_as_bool(VAL) ((VAL) != 0)
#define dc_usize_as_bool(VAL) ((VAL) != 0)

/**
 * Default value of boolean based on u8 dynamic value of 1
 */
#define DC_DV_TRUE dc_dv(u8, true)

/**
 * Default value of boolean based on u8 dynamic value of 0
 */
#define DC_DV_FALSE dc_dv(u8, false)

/**
 * Default value of boolean based on voidptr dynamic value of NULL
 */
#define DC_DV_NULL dc_dv(voidptr, NULL)

// ***************************************************************************************
// * STOPPER AND STOPPER CHECKERS
// *    These are values that can be used as a stopping point in an array
// ***************************************************************************************

#define DC_STOPPER_i8 INT8_MAX
#define DC_STOPPER_i16 INT16_MAX
#define DC_STOPPER_i32 INT32_MAX
#define DC_STOPPER_i64 INT64_MAX

#define DC_STOPPER_u8 UINT8_MAX
#define DC_STOPPER_u16 UINT16_MAX
#define DC_STOPPER_u32 UINT32_MAX
#define DC_STOPPER_u64 UINT64_MAX

#define DC_STOPPER_f32 NAN
#define DC_STOPPER_f64 NAN

#define DC_STOPPER_uptr (uptr) NULL
#define DC_STOPPER_string NULL
#define DC_STOPPER_voidptr NULL
#define DC_STOPPER_fileptr NULL

#define DC_STOPPER_char '\0'

#define DC_STOPPER_size -1
#define DC_STOPPER_usize SIZE_MAX

#define DC_IS_ARR_TERMINATOR_i8(EL) (EL == DC_STOPPER_i8)
#define DC_IS_ARR_TERMINATOR_i16(EL) (EL == DC_STOPPER_i16)
#define DC_IS_ARR_TERMINATOR_i32(EL) (EL == DC_STOPPER_i32)
#define DC_IS_ARR_TERMINATOR_i64(EL) (EL == DC_STOPPER_i64)


#define DC_IS_ARR_TERMINATOR_u8(EL) (EL == DC_STOPPER_u8)
#define DC_IS_ARR_TERMINATOR_u16(EL) (EL == DC_STOPPER_u16)
#define DC_IS_ARR_TERMINATOR_u32(EL) (EL == DC_STOPPER_u32)
#define DC_IS_ARR_TERMINATOR_u64(EL) (EL == DC_STOPPER_u64)

#define DC_IS_ARR_TERMINATOR_f32(EL) (isnan(EL))
#define DC_IS_ARR_TERMINATOR_f64(EL) (isnan(EL))

#define DC_IS_ARR_TERMINATOR_uptr(EL) (EL == DC_STOPPER_uptr)
#define DC_IS_ARR_TERMINATOR_string(EL) (EL == DC_STOPPER_string)
#define DC_IS_ARR_TERMINATOR_voidptr(EL) (EL == DC_STOPPER_voidptr)
#define DC_IS_ARR_TERMINATOR_fileptr(EL) (EL == DC_STOPPER_fileptr)

#define DC_IS_ARR_TERMINATOR_char(EL) (EL == DC_STOPPER_char)

#define DC_IS_ARR_TERMINATOR_size(EL) (EL == DC_STOPPER_size)
#define DC_IS_ARR_TERMINATOR_usize(EL) (EL == DC_STOPPER_usize)

/**
 * Provides proper stopper for given type
 *
 * NOTE: These are values that can be used as a stopping point in an array
 */
#define dc_stopper(TYPE) (DC_STOPPER_##TYPE)

/**
 * Checks if the given value is an stopper for the given type
 */
#define dc_is_arr_terminator(TYPE, VALUE) (DC_IS_ARR_TERMINATOR_##TYPE(VALUE))

// ***************************************************************************************
// * UTILITY MACROS
// ***************************************************************************************

#if defined(__GNUC__) || defined(__clang__)
#define __dc_attribute(A) __attribute__(A)
#else
#define __dc_attribute(A)
#endif

#if defined(DC_WINDOWS)
#define DC_BASE_PATH '\\'
#else
#define DC_BASE_PATH '/'
#endif


#define __BASE_FILE (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

/**
 * General macro that returns current __FILE__ filename only
 */
#define __FILENAME__ (strrchr(__BASE_FILE, '/') ? strrchr(__BASE_FILE, '/') + 1 : __BASE_FILE)

/**
 * Creates temporary string of given format and data and runs it under the
 * system and keeps the returned value in the OUT_VAL
 */
#define dc_system(OUT_VAL, ...)                                                                                                \
    do                                                                                                                         \
    {                                                                                                                          \
        string __cmd_string;                                                                                                   \
        dc_sprintf(&__cmd_string, __VA_ARGS__);                                                                                \
        OUT_VAL = system(__cmd_string);                                                                                        \
        free(__cmd_string);                                                                                                    \
    } while (0)

/**
 * Simple macro to create a switch case for an enum and returning the string
 * literal of it
 */
#define dc_str_case(ITEM)                                                                                                      \
    case ITEM:                                                                                                                 \
        return #ITEM

/**
 * returns "true" or "false" as strings for given expression
 */
#define dc_tostr_bool(B) ((B) ? "true" : "false")

// ***************************************************************************************
// * INTERNAL LOG MACROS MACROS
// ***************************************************************************************

#define __dc_log(CAT, ...)                                                                                                     \
    do                                                                                                                         \
    {                                                                                                                          \
        fileptr __dc_stream = (dc_error_logs ? dc_error_logs : stderr);                                                        \
        fprintf(__dc_stream, "[%s] (", CAT);                                                                                   \
        dc_now(__dc_stream);                                                                                                   \
        fprintf(__dc_stream, ") \"%s:%d\" ", __FILENAME__, __LINE__);                                                          \
        fprintf(__dc_stream, __VA_ARGS__);                                                                                     \
        fprintf(__dc_stream, "\n");                                                                                            \
    } while (0)

#define __dc_log_if(CAT, CONDITION, ...)                                                                                       \
    do                                                                                                                         \
    {                                                                                                                          \
        if (CONDITION)                                                                                                         \
        {                                                                                                                      \
            __dc_log(CAT, __VA_ARGS__);                                                                                        \
        }                                                                                                                      \
    } while (0)

#define __dc_action_on(CAT, CONDITION, FAILURE_ACTION, ...)                                                                    \
    do                                                                                                                         \
    {                                                                                                                          \
        if (CONDITION)                                                                                                         \
        {                                                                                                                      \
            __dc_log(CAT, __VA_ARGS__);                                                                                        \
            do                                                                                                                 \
            {                                                                                                                  \
                FAILURE_ACTION;                                                                                                \
            } while (0);                                                                                                       \
        }                                                                                                                      \
    } while (0)


// ***************************************************************************************
// * RESULT MACROS
// ***************************************************************************************

/**
 * Defines the main result variable (__dc_res) as DCResult and initiates it as
 * DC_RES_OK
 */
#define DC_RES()                                                                                                               \
    DCResult __dc_res;                                                                                                         \
    __dc_res.status = DC_RES_OK

/**
 * Defines the main result variable (__dc_res) as the given result type and
 * initiates it as DC_RES_OK
 */
#define DC_RES2(DC_RESULT_TYPE)                                                                                                \
    DC_RESULT_TYPE __dc_res;                                                                                                   \
    __dc_res.status = DC_RES_OK

/**
 * Defines the main result variable (__dc_res) as DCResultBool type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_bool() DC_RES2(DCResultBool)

/**
 * Defines the main result variable (__dc_res) as DCResultVoid type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_void() DC_RES2(DCResultVoid)

/**
 * Defines the main result variable (__dc_res) as DCResultSv type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_sv() DC_RES2(DCResultSv)

/**
 * Defines the main result variable (__dc_res) as DCResultDa type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_da() DC_RES2(DCResultDa)

/**
 * Defines the main result variable (__dc_res) as DCResultHt type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_ht() DC_RES2(DCResultHt)

/**
 * Defines the main result variable (__dc_res) as DCResultDv type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_dv() DC_RES2(DCResultDv)

/**
 * Defines the main result variable (__dc_res) as DCResultI8 type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_i8() DC_RES2(DCResultI8)

/**
 * Defines the main result variable (__dc_res) as DCResultI16 type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_i16() DC_RES2(DCResultI16)

/**
 * Defines the main result variable (__dc_res) as DCResultI32 type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_i32() DC_RES2(DCResultI32)

/**
 * Defines the main result variable (__dc_res) as DCResultI64 type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_i64() DC_RES2(DCResultI64)

/**
 * Defines the main result variable (__dc_res) as DCResultU8 type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_u8() DC_RES2(DCResultU8)

/**
 * Defines the main result variable (__dc_res) as DCResultU16 type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_u16() DC_RES2(DCResultU16)

/**
 * Defines the main result variable (__dc_res) as DCResultU32 type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_u32() DC_RES2(DCResultU32)

/**
 * Defines the main result variable (__dc_res) as DCResultU64 type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_u64() DC_RES2(DCResultU64)

/**
 * Defines the main result variable (__dc_res) as DCResultF32 type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_f32() DC_RES2(DCResultF32)

/**
 * Defines the main result variable (__dc_res) as DCResultF64 type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_f64() DC_RES2(DCResultF64)

/**
 * Defines the main result variable (__dc_res) as DCResultUptr type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_uptr() DC_RES2(DCResultUptr)

/**
 * Defines the main result variable (__dc_res) as DCResultSize type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_size() DC_RES2(DCResultSize)

/**
 * Defines the main result variable (__dc_res) as DCResultUsize type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_usize() DC_RES2(DCResultUsize)

/**
 * Defines the main result variable (__dc_res) as DCResultString type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_string() DC_RES2(DCResultString)

/**
 * Defines the main result variable (__dc_res) as DCResultVoidptr type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_voidptr() DC_RES2(DCResultVoidptr)

/**
 * Defines the main result variable (__dc_res) as DCResultFileptr type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_fileptr() DC_RES2(DCResultFileptr)

/**
 * Defines the main result variable (__dc_res) as DCResultFileptr type and
 * initiates it as DC_RES_OK
 */
#define DC_RES_fileptr() DC_RES2(DCResultFileptr)

/**
 * Sets the main result variable (__dc_res) status to DC_RES_ERR and
 * initiates the error value with given error code (NUM) and literal string
 *
 * NOTE: MSG must be literal string not an allocated string variable (see
 * dc_res_ea)
 */
#define dc_res_e(NUM, MSG)                                                                                                     \
    do                                                                                                                         \
    {                                                                                                                          \
        __dc_res.status = DC_RES_ERR;                                                                                          \
        __dc_res.data.e = (DCError){NUM, MSG, 0};                                                                              \
    } while (0)

/**
 * Sets the main result variable (__dc_res) status to DC_RES_ERR and
 * initiates the error value with given error code (NUM), it also create
 * formatted string (allocated) and sets the error message
 *
 * NOTE: Allocates memory
 */
#define dc_res_ea(NUM, ...)                                                                                                    \
    do                                                                                                                         \
    {                                                                                                                          \
        string __err;                                                                                                          \
        dc_sprintf(&__err, __VA_ARGS__);                                                                                       \
        __dc_res.status = DC_RES_ERR;                                                                                          \
        __dc_res.data.e = (DCError){NUM, __err, 1};                                                                            \
    } while (0)

/**
 * Copies error data from RES2 to RES1
 *
 * NOTE: Treat to this like a move semantic, so if you free the original or the
 * copy that would be fine
 *
 * NOTE: Does Nothing on successful results
 */
#define dc_res_err_cpy2(RES1, RES2)                                                                                            \
    do                                                                                                                         \
    {                                                                                                                          \
        if ((RES2).status == DC_RES_ERR)                                                                                       \
        {                                                                                                                      \
            (RES1).status = DC_RES_ERR;                                                                                        \
            (RES1).data.e = (RES2).data.e;                                                                                     \
        }                                                                                                                      \
    } while (0)

/**
 * Copies error data from RES to the main result variable (__dc_res)
 *
 * NOTE: Treat to this like a move semantic, so if you free the original or
 * the copy that would be fine
 *
 * NOTE: Does Nothing on successful results
 */
#define dc_res_err_cpy(RES) dc_res_err_cpy2(__dc_res, RES)

/**
 * Sets the main result variable (__dc_res) status to DC_RES_OK and also
 * initiates the value with the given VALUE
 */
#define dc_res_ok(VALUE)                                                                                                       \
    do                                                                                                                         \
    {                                                                                                                          \
        __dc_res.status = DC_RES_OK;                                                                                           \
        __dc_res.data.v = VALUE;                                                                                               \
    } while (0)

/**
 * In case the result is of type DCResult this is a shortcut to create a literal
 * dynamic value and setting it to the success value on the fly
 *
 * NOTE: The value must not be allocated (see dc_res_ok_dva)
 */
#define dc_res_ok_dv(TYPE, VALUE) dc_res_ok(dc_dv(TYPE, VALUE))

/**
 * In case the result is of type DCResult this is a shortcut to create a literal
 * dynamic value and setting it to the success value on the fly
 *
 * NOTE: The value must be allocated (see dc_res_ok_dv)
 */
#define dc_res_ok_dva(TYPE, VALUE) dc_res_ok(dc_dva(TYPE, VALUE))

/**
 * Returns the main result variable (__dc_res)
 */
#define dc_res_ret() return __dc_res

/**
 * Sets the main result variable (__dc_res) to error and returns it right away.
 *
 * NOTE: MSG must be literal string not an allocated string variable
 * (see dc_res_ret_ea)
 */
#define dc_res_ret_e(NUM, MSG)                                                                                                 \
    do                                                                                                                         \
    {                                                                                                                          \
        dc_res_e(NUM, MSG);                                                                                                    \
        dc_res_ret();                                                                                                          \
    } while (0)

/**
 * Sets the main result variable (__dc_res) to error and returns it right away.
 *
 * NOTE: Allocates memory (see dc_res_ret_e)
 */
#define dc_res_ret_ea(NUM, ...)                                                                                                \
    do                                                                                                                         \
    {                                                                                                                          \
        dc_res_ea(NUM, __VA_ARGS__);                                                                                           \
        dc_res_ret();                                                                                                          \
    } while (0)

/**
 * Sets the main result variable (__dc_res) to success and returns it right
 * away.
 */
#define dc_res_ret_ok(VALUE)                                                                                                   \
    do                                                                                                                         \
    {                                                                                                                          \
        dc_res_ok(VALUE);                                                                                                      \
        dc_res_ret();                                                                                                          \
    } while (0)

/**
 * Sets the main result variable (__dc_res) to success and returns it right
 * away.
 *
 * NOTE: The main result variable must be of type DCResult
 *
 * NOTE: The VALUE must not be allocated (see dc_res_ret_ok_dva)
 */
#define dc_res_ret_ok_dv(TYPE, VALUE)                                                                                          \
    do                                                                                                                         \
    {                                                                                                                          \
        dc_res_ok_dv(TYPE, VALUE);                                                                                             \
        dc_res_ret();                                                                                                          \
    } while (0)

/**
 * Sets the main result variable (__dc_res) to success and returns it right
 * away.
 *
 * NOTE: The main result variable must be of type DCResult
 *
 * NOTE: The VALUE must be allocated (see dc_res_ret_ok_dv)
 */
#define dc_res_ret_ok_dva(TYPE, VALUE)                                                                                         \
    do                                                                                                                         \
    {                                                                                                                          \
        dc_res_ok_dva(TYPE, VALUE);                                                                                            \
        dc_res_ret();                                                                                                          \
    } while (0)

/**
 * Renders an if statements that checks if main result variable (__dc_res)
 * status is error and if so returns it
 */
#define dc_res_fail_if_err()                                                                                                   \
    if (__dc_res.status == DC_RES_ERR) return __dc_res

/**
 * Expands to a new result variable declaration initialized with the CALL
 * and returning error with failure actions in case of errors
 */
#define dc_try_or_fail_with3(RES_TYPE, RES, CALL, FAILURE_ACTIONS)                                                             \
    RES_TYPE RES = CALL;                                                                                                       \
    dc_res_ret_if_err2(RES, FAILURE_ACTIONS)

/**
 * Expands to assigning an existing result variable with the CALL
 * and returning error with failure actions in case of errors
 */
#define dc_try_or_fail_with2(RES, CALL, FAILURE_ACTIONS)                                                                       \
    RES = CALL;                                                                                                                \
    dc_res_ret_if_err2(RES, FAILURE_ACTIONS)

/**
 * Expands to assigning main result variable (__dc_res) to the CALL
 * and returning error with failure actions in case of errors
 */
#define dc_try_or_fail_with(CALL, FAILURE_ACTIONS) dc_try_or_fail_with2(__dc_res, CALL, FAILURE_ACTIONS)

/**
 * Checks if the main result variable (__dc_result) is error does
 * PRE_RETURN_ACTIONS and then return __dc_res
 */
#define dc_res_ret_if_err(PRE_RETURN_ACTIONS)                                                                                  \
    do                                                                                                                         \
    {                                                                                                                          \
        if (dc_res_is_err())                                                                                                   \
        {                                                                                                                      \
            do                                                                                                                 \
            {                                                                                                                  \
                PRE_RETURN_ACTIONS;                                                                                            \
            } while (0);                                                                                                       \
            return __dc_res;                                                                                                   \
        }                                                                                                                      \
    } while (0)

/**
 * Assigns the main result variable (__dc_res) to the provided function call
 */
#define dc_try(CALL) __dc_res = CALL

/**
 * First it assigns the main result variable (__dc_res) to the provided function
 * call then it checks if it has error and in that case will return __dc_res
 */
#define dc_try_fail(CALL)                                                                                                      \
    do                                                                                                                         \
    {                                                                                                                          \
        __dc_res = CALL;                                                                                                       \
        dc_res_fail_if_err();                                                                                                  \
    } while (0)

/**
 * Checks provided result variable and if its status is error populates the main
 * result variable (__dc_res) error and returns it
 */
#define dc_res_fail_if_err2(RES)                                                                                               \
    do                                                                                                                         \
    {                                                                                                                          \
        if ((RES).status == DC_RES_ERR)                                                                                        \
        {                                                                                                                      \
            dc_res_err_cpy(RES);                                                                                               \
            dc_res_ret();                                                                                                      \
        }                                                                                                                      \
    } while (0)

/**
 * Checks if the given result variable is error copies the error data and does
 * PRE_RETURN_ACTIONS and then return __dc_res
 */
#define dc_res_ret_if_err2(RES, PRE_RETURN_ACTIONS)                                                                            \
    do                                                                                                                         \
    {                                                                                                                          \
        if (dc_res_is_err2(RES))                                                                                               \
        {                                                                                                                      \
            do                                                                                                                 \
            {                                                                                                                  \
                PRE_RETURN_ACTIONS;                                                                                            \
            } while (0);                                                                                                       \
            dc_res_err_cpy(RES);                                                                                               \
            return __dc_res;                                                                                                   \
        }                                                                                                                      \
    } while (0)

/**
 * In case you want to call a function that returns a result type and you don't
 * care it's return type (might be DCResultVoid as an example) but you do care
 * if the result is error and you want to halt the process this macro is the
 * solution
 *
 * @brief Creates temporary result type assign it with the function call (CALL)
 * and return of the temporary result is an error
 */
#define dc_try_fail_temp(RES_TYPE, CALL)                                                                                       \
    do                                                                                                                         \
    {                                                                                                                          \
        RES_TYPE __temp_res = CALL;                                                                                            \
        dc_res_fail_if_err2(__temp_res);                                                                                       \
    } while (0)

/**
 * There are places that at the beginning of a function we might need to define
 * and initiate the main result variable (__dc_res) and exactly call to a
 * function and fail if it is error or hold the success data in the main result
 * variable (__dc_res) in that situation this is the macro we want to use
 *
 * @brief First initialize the main result variable with DCResult then try
 * calling the CALL and fail if it has error
 */
#define DC_TRY_DEF(CALL)                                                                                                       \
    DC_RES();                                                                                                                  \
    dc_try_fail(CALL)

/**
 * There are places that at the beginning of a function we might need to define
 * and initiate the main result variable (__dc_res) and exactly call to a
 * function and fail if it is error or hold the success data in the main result
 * variable (__dc_res) in that situation this is the macro we want to use
 *
 * @brief First initialize the main result variable with given result type then
 * try calling the CALL and fail if it has error
 */
#define DC_TRY_DEF2(DC_RESULT_TYPE, CALL)                                                                                      \
    DC_RES2(DC_RESULT_TYPE);                                                                                                   \
    dc_try_fail(CALL)

/**
 * Can be used to get specific type from main result variable (__dc_res) under
 * two condition:
 *
 * - The main result variable (__dc_res) is of type DCResult
 * - The result status is ok
 */
#define dc_res_as(TYPE) dc_dv_as(__dc_res.data.v, TYPE)

/**
 * Returns true if main result variable (__dc_res) status is ok
 */
#define dc_res_is_ok() (__dc_res.status == DC_RES_OK)

/**
 * Returns true if the given result variable status is ok
 */
#define dc_res_is_ok2(RES) ((RES).status == DC_RES_OK)

/**
 * Returns true if main result variable (__dc_res) status is error
 */
#define dc_res_is_err() (__dc_res.status == DC_RES_ERR)

/**
 * Returns true if the given result variable status is error
 */
#define dc_res_is_err2(RES) ((RES).status == DC_RES_ERR)

/**
 * Retrieves the value of the main result variable (__dc_res)
 *
 * NOTE: You must have already checked to make sure the current status is ok
 */
#define dc_res_val() (__dc_res.data.v)

/**
 * Retrieves the value of the given result variable
 *
 * NOTE: You must have already checked to make sure the current status is ok
 */
#define dc_res_val2(RES) ((RES).data.v)

/**
 * Expands to current status of the main result variable (__dc_res)
 */
#define dc_res_status() (__dc_res.status)

/**
 * Expands to the status of the given result variable
 */
#define dc_res_status2(RES) ((RES).status)

/**
 * Retrieves the error data of the main result variable (__dc_res)
 *
 * NOTE: You must have already checked to make sure the current status is error
 */
#define dc_res_err() (__dc_res.data.e)

/**
 * Retrieves the error data of the given result variable
 *
 * NOTE: You must have already checked to make sure the current status is error
 */
#define dc_res_err2(RES) ((RES).data.e)

/**
 * Retrieves the error code of the main result variable (__dc_res)
 *
 * NOTE: You must have already checked to make sure the current status is error
 */
#define dc_res_err_code() (__dc_res.data.e.code)

/**
 * Retrieves the error code of the given result variable
 *
 * NOTE: You must have already checked to make sure the current status is error
 */
#define dc_res_err_code2(RES) ((RES).data.e.code)

/**
 * Retrieves the error message of the main result variable (__dc_res)
 *
 * NOTE: You must have already checked to make sure the current status is error
 */
#define dc_res_err_msg() (__dc_res.data.e.message)

/**
 * Retrieves the error message of the given result variable
 *
 * NOTE: You must have already checked to make sure the current status is error
 */
#define dc_res_err_msg2(RES) ((RES).data.e.message)

/**
 * Debug logs the given result's error result with provided string literal
 * message prepended
 *
 * NOTE: The result must be error
 */
#define dc_res_err_dbg_log2(RES, PRE_MSG) dc_dbg_log(PRE_MSG ": (code %d) %s", dc_res_err_code2(RES), dc_res_err_msg2(RES))

/**
 * Debug logs main result variable (__dc_res) with provided string literal
 * message prepended
 *
 * NOTE: The result must be error
 */
#define dc_res_err_dbg_log(PRE_MSG) dc_res_err_dbg_log2(__dc_res, PRE_MSG)

/**
 * Logs the given result's error result with provided string literal
 * message prepended
 *
 * NOTE: The result must be error
 */
#define dc_res_err_log2(RES, PRE_MSG) dc_log(PRE_MSG ": (code %d) %s", dc_res_err_code2(RES), dc_res_err_msg2(RES))

/**
 * Logs main result variable (__dc_res) with provided string literal
 * message prepended
 *
 * NOTE: The result must be error
 */
#define dc_res_err_log(PRE_MSG) dc_res_err_log2(__dc_res, PRE_MSG)


// ***************************************************************************************
// * LOG MACROS
// ***************************************************************************************

/**
 * Logs to `stderr` or global `dc_error_logs` if not `NULL` with `["LOG"]`
 * prefix
 */
#define dc_log(...) __dc_log("LOG", __VA_ARGS__)

/**
 * Logs to `stderr` or global `dc_error_logs` if not `NULL` with `["LOG"]`
 * prefix if the CONDITION is met
 */
#define dc_log_if(CONDITION, ...) __dc_log_if("LOG", CONDITION, __VA_ARGS__)

/**
 * Checks whether the CONDITION is true and performs FAILURE_ACTION and
 * logs to `stderr` or global `dc_error_logs` if not `NULL` with `["LOG"]`
 * prefix
 */
#define dc_action_on(CONDITION, FAILURE_ACTION, ...) __dc_action_on("LOG", CONDITION, FAILURE_ACTION, __VA_ARGS__)


#ifdef DC_DEBUG

/**
 * If `DC_DEBUG` is defined logs to `stderr` or global `dc_error_logs` if not
 * `NULL` with `["LOG"]` prefix
 */
#define dc_dbg_log(...) __dc_log("DEBUG", __VA_ARGS__)

/**
 * If `DC_DEBUG` is defined logs to `stderr` or global `dc_error_logs` if not
 * `NULL` with `["LOG"]` prefix if the CONDITION is met
 */
#define dc_dbg_log_if(CONDITION, ...) __dc_log_if("DEBUG", CONDITION, __VA_ARGS__)

/**
 * If `DC_DEBUG` is defined checks whether the CONDITION is true and performs
 * FAILURE_ACTION and logs to `stderr` or global `dc_error_logs` if not `NULL`
 * with `["LOG"]` prefix
 *
 * NOTE: It doesn't do anything when `DC_DEBUG` is not defined, not that it
 * won't just output anything
 */
#define dc_dbg_action_on(CONDITION, FAILURE_ACTION, ...) __dc_action_on("DEBUG", CONDITION, FAILURE_ACTION, __VA_ARGS__)

#else

/**
 * If `DC_DEBUG` is defined logs to `stderr` or global `dc_error_logs` if not
 * `NULL` with `["LOG"]` prefix
 */
#define dc_dbg_log(...)

/**
 * If `DC_DEBUG` is defined logs to `stderr` or global `dc_error_logs` if not
 * `NULL` with `["LOG"]` prefix if the CONDITION is met
 */
#define dc_dbg_log_if(CONDITION, ...)

/**
 * If `DC_DEBUG` is defined checks whether the CONDITION is true and performs
 * FAILURE_ACTION and logs to `stderr` or global `dc_error_logs` if not `NULL`
 * with `["LOG"]` prefix
 *
 * NOTE: It doesn't do anything when `DC_DEBUG` is not defined, not that it
 * won't just output anything
 */
#define dc_dbg_action_on(CONDITION, FAILURE_ACTION, ...)

#endif

// ***************************************************************************************
// * NON-POINTER ARRAY MACROS
// ***************************************************************************************

/**
 * Creates a literal array of the given type that is terminated by the specific
 * stopper for that type
 */
#define dc_arr_lit(TYPE, ...)                                                                                                  \
    (TYPE[])                                                                                                                   \
    {                                                                                                                          \
        __VA_ARGS__, dc_stopper(TYPE)                                                                                          \
    }

/**
 * Defines a variable of the given `TYPE`[] and initialize it with given data
 * terminated with proper stopper
 */
#define DC_ARRAY(NAME, TYPE, ...) TYPE NAME[] = {__VA_ARGS__, dc_stopper(TYPE)}

/**
 * Expands to actual number of elements in a literal array
 *
 * NOTE: For strings and stopper terminated array this will shows +1
 */
#define dc_count(ARR) (size)(sizeof(ARR) / sizeof(*(ARR)))

/**
 * Expands to actual useful elements in a stopper terminated array
 */
#define dc_len(ARR) (dc_count(ARR) - 1)

/**
 * Expands to the last item in a stopper terminated array
 */
#define dc_last(ARR) ARR[(dc_len(ARR) - 1)]

/**
 * Iterator in a stopper terminated array provided with pointer to the current
 * element in each iteration as `_it`
 */
#define dc_foreach(ARR, TYPE) for (TYPE* _it = ARR; !dc_is_arr_terminator(TYPE, *_it); ++_it)

/**
 * Iterator that perform given `FN` on each element in a stopper terminated
 * array
 */
#define dc_oneach(ARR, TYPE, FN) dc_foreach(ARR, TYPE) FN(_it)

/**
 * Expands to an iterator over a literal array of given data and returns pointer
 * to current element in each iteration as `_it`
 *
 * @example dc_foreach_lit(u8, 1, 2, 3, 4) printf("%d\n", *_it);
 */
#define dc_foreach_lit(TYPE, ...) for (TYPE* _it = dc_arr_lit(TYPE, __VA_ARGS__); !dc_is_arr_terminator(TYPE, *_it); ++_it)

/**
 * Iterator that performs given `FN` on each provided element
 */
#define dc_oneach_lit(TYPE, FN, ...) dc_foreach_lit(TYPE, __VA_ARGS__) FN(_it)


// ***************************************************************************************
// * POINTER ARRAY MACROS
// ***************************************************************************************

/**
 * Creates a literal array of the given pointer type that is terminated by NULL
 *
 * @example dc_parr_lit(MyStruct*, &s1, &s2, &s3);
 *
 * NOTE: You need to include `*` in the type
 */
#define dc_parr_lit(TYPE, ...)                                                                                                 \
    (TYPE[])                                                                                                                   \
    {                                                                                                                          \
        __VA_ARGS__, DC_STOPPER_voidptr                                                                                        \
    }

/**
 * Defines a literal array of pointer to the given type
 *
 * @example DC_PARRAY(my_arr, MyStruct, &s1, &s2, &s3);
 *
 * NOTE: You don't need to include `*` in the type
 */
#define DC_PARRAY(NAME, TYPE, ...) TYPE** NAME = dc_parr_lit(TYPE*, __VA_ARGS__)

/**
 * Iterates over a literal array of pointers to given type and provide
 * pointer to the current element as `_it`
 *
 * NOTE: You don't need to include `*` in the type
 */
#define dc_pforeach(ARR, TYPE) for (TYPE** _it = ARR; !DC_IS_ARR_TERMINATOR_voidptr(*_it); ++_it)

/**
 * Iterates over the given pointer array of `TYPE` and pass each
 * element to `FN`
 */
#define dc_poneach(ARR, TYPE, FN) dc_pforeach(ARR, TYPE) FN(_it)

/**
 * Iterates over the given pointers of `TYPE` and provide pointer to the current
 * element as `_it`
 */
#define dc_pforeach_lit(TYPE, ...) for (TYPE* _it = dc_parr_lit(TYPE, __VA_ARGS__); !DC_IS_ARR_TERMINATOR_voidptr(*_it); ++_it)

/**
 * Iterates over the given pointers of `TYPE` and pass them to `FN`
 *
 * @example dc_poneach_lit(MyStruct, print_my_struct, &m1, &m2, &m3);
 */
#define dc_poneach_lit(TYPE, FN, ...) dc_pforeach_lit(TYPE*, __VA_ARGS__) FN(*_it)

// ***************************************************************************************
// * STRUCT ARRAY MACROS
// ***************************************************************************************

/**
 * Creates literal array for the given struct type
 *
 * NOTE: The array is not terminated with stoppers
 */
#define dc_sarr_lit(TYPE, ...)                                                                                                 \
    (TYPE[])                                                                                                                   \
    {                                                                                                                          \
        __VA_ARGS__                                                                                                            \
    }

/**
 * Defines the given NAME as an array of given TYPE with given data
 *
 * NOTE: The array is note terminated with stoppers
 */
#define DC_SARRAY(NAME, TYPE, ...) TYPE NAME[] = {__VA_ARGS__}

/**
 * Iterates over an array of structs and stops when the TERMINATION_CONDITION is
 * met
 *
 * The pointer to the current item in each iteration is provided as `_it`
 *
 * NOTE: You can use `_it` in the condition as well
 */
#define dc_sforeach(ARR, TYPE, TERMINATION_CONDITION) for (TYPE* _it = ARR; TERMINATION_CONDITION; ++_it)

/**
 * Iterates over an array of structs and pass pointer to each element to `FN`
 *
 * Iteration will be stopped when the TERMINATION_CONDITION is met
 *
 * The pointer to the current item in each iteration is provided as `_it`
 *
 * NOTE: You can use `_it` in the condition as well
 */
#define dc_soneach(ARR, TYPE, TERMINATION_CONDITION, FN) dc_sforeach(ARR, TYPE, TERMINATION_CONDITION) FN(_it)

/**
 * Iterates over given struct items of same TYPE and stops when the
 * TERMINATION_CONDITION is met
 *
 * The pointer to the current item in each iteration is provided as `_it`
 *
 * NOTE: You can use `_it` in the condition as well
 */
#define dc_sforeach_lit(TYPE, TERMINATION_CONDITION, ...)                                                                      \
    for (TYPE* _it = dc_sarr_lit(TYPE, __VA_ARGS__); TERMINATION_CONDITION; ++_it)

/**
 * Iterates over given struct items of same TYPE and pass pointer to each
 * element to `FN`
 *
 * Iteration will be stopped when the TERMINATION_CONDITION is met
 *
 * The pointer to the current item in each iteration is provided as `_it`
 *
 * NOTE: You can use `_it` in the condition as well
 */
#define dc_soneach_lit(TYPE, TERMINATION_CONDITION, FN, ...) dc_sforeach_lit(TYPE, TERMINATION_CONDITION, __VA_ARGS__) FN(_it)

// ***************************************************************************************
// * DYNAMIC ARRAY MACROS
// ***************************************************************************************

#ifndef DC_DA_INITIAL_CAP

/**
 * Default initial capacity for dynamic array
 *
 * NOTE: You can define it with your desired amount before including `dcommon.h`
 */
#define DC_DA_INITIAL_CAP 4

#endif

#ifndef DC_DA_CAP_MULTIPLIER

/**
 * Default initial capacity multiplier for dynamic array
 *
 * NOTE: You can define it with your desired amount before including `dcommon.h`
 */
#define DC_DA_CAP_MULTIPLIER 2

#endif

/**
 * Macro to define custom free function for dynamic values
 */
#define DC_DV_FREE_FN_DECL(NAME) DCResultVoid NAME(DCDynVal* _value)

/**
 * Expands to proper enum value for given type that is used in dynamic values
 */
#define dc_dvt(TYPE) DC_DYN_VAL_TYPE_##TYPE

/**
 * Defines a dynamic value literal which holds given type and value and is
 * marked as not allocated
 *
 * NOTE: The value must not be an allocated value
 */
#define dc_dv(TYPE, VALUE)                                                                                                     \
    (DCDynVal)                                                                                                                 \
    {                                                                                                                          \
        .type = dc_dvt(TYPE), .value.TYPE##_val = VALUE, .allocated = false                                                    \
    }

/**
 * Defines a dynamic value literal which holds given type and value and is
 * marked as allocated
 *
 * NOTE: The value must be an allocated value
 */
#define dc_dva(TYPE, VALUE)                                                                                                    \
    (DCDynVal)                                                                                                                 \
    {                                                                                                                          \
        .type = dc_dvt(TYPE), .value.TYPE##_val = VALUE, .allocated = true                                                     \
    }

/**
 * Defines new variable of NAME with given type, value and allocation status
 */
#define DC_DV_DEF(NAME, TYPE, VALUE, ALLOC)                                                                                    \
    DCDynVal NAME = {.type = dc_dvt(TYPE), .value.TYPE##_val = VALUE, .allocated = ALLOC}

/**
 * Expands to setting type and value of an existing dynamic value variable and
 * reset the allocation status to false
 *
 * NOTE: The VALUE must not be allocated
 */
#define dc_dv_set(NAME, TYPE, VALUE)                                                                                           \
    do                                                                                                                         \
    {                                                                                                                          \
        (NAME).type = dc_dvt(TYPE);                                                                                            \
        (NAME).allocated = false;                                                                                              \
        (NAME).value.TYPE##_val = VALUE;                                                                                       \
    } while (0)

/**
 * Marks given dynamic value variable as allocated
 */
#define dc_dv_mark_alloc(NAME) (NAME).allocated = true

/**
 * Expands to setting type and value of an existing dynamic value variable and
 * set the allocation status to true
 *
 * NOTE: The VALUE must be allocated
 */
#define dc_dv_seta(NAME, TYPE, VALUE)                                                                                          \
    do                                                                                                                         \
    {                                                                                                                          \
        dc_dv_set(NAME, TYPE, VALUE);                                                                                          \
        dc_dv_mark_alloc(NAME);                                                                                                \
    } while (0)

/**
 * Expands to type checking for the given dynamic value variable
 */
#define dc_dv_is(NAME, TYPE) ((NAME).type == dc_dvt(TYPE))

/**
 * Expands to negative type checking for the given dynamic value variable
 */
#define dc_dv_is_not(NAME, TYPE) ((NAME).type != dc_dvt(TYPE))

/**
 * Retrieves the value of the given dynamic value for the given type
 */
#define dc_dv_as(NAME, TYPE) ((NAME).value.TYPE##_val)

/**
 *  Checks if the dynamic value is marked as allocated
 */
#define dc_dv_is_allocated(NAME) ((NAME).allocated)

/**
 * Checks if the given index is correct according to the dynamic array number of
 * elements
 */
#define dc_da_check_boundary(DARR, INDEX) ((DARR).count <= (INDEX))

/**
 * Retrieves dynamic value element at certain index as is
 *
 * NOTE: There is no boundary check in this macro, you have to do it beforehand
 */
#define dc_da_get2(DARR, INDEX) ((DARR).elements[INDEX])

/**
 * Retrieves dynamic value element at certain index and return the wanted type
 *
 * NOTE: There is no boundary check in this macro, you have to do it beforehand
 */
#define dc_da_get_as(DARR, INDEX, TYPE) dc_dv_as(dc_da_get2(DARR, INDEX), TYPE)

/**
 * Checks if element at certain index is of the given type
 *
 * NOTE: There is no boundary check in this macro, you have to do it beforehand
 */
#define dc_da_is(DARR, INDEX, TYPE) dc_dv_is((DARR).elements[INDEX], TYPE)

/**
 * Checks if element at certain index is not of the given type
 *
 * NOTE: There is no boundary check in this macro, you have to do it beforehand
 */
#define dc_da_is_not(DARR, INDEX, TYPE) dc_dv_is_not((DARR).elements[INDEX], TYPE)

/**
 * Expands to a for loop for the given dynamic array, index can be accessed by
 * `_idx`
 */
#define dc_da_for(DARR) for (usize _idx = 0; _idx < (DARR).count; _idx++)

/**
 * Macro to initialize the dynamic array with initial values without providing
 * the count
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_da_init_with_values(DARRPTR, FREE_FUNC, ...)                                                                        \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        __dc_da_init_with_values(DARRPTR, dc_count(__initial_values), FREE_FUNC, __initial_values);                            \
    } while (0)

/**
 * Tries to initialize the dynamic array with initial values without providing
 * the count and saves the result (ok or error) in the given RES
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_try_da_init_with_values(RES, DARRPTR, FREE_FUNC, ...)                                                               \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        RES = __dc_da_init_with_values(DARRPTR, dc_count(__initial_values), FREE_FUNC, __initial_values);                      \
    } while (0)

/**
 * Tries to initialize the dynamic array with initial values without providing
 * the count and saves the result (ok or error) in the main result variable
 * (__dc_res) and returns if it encounter error
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_try_fail_da_init_with_values(DARRPTR, FREE_FUNC, ...)                                                               \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        dc_try_fail(__dc_da_init_with_values(DARRPTR, dc_count(__initial_values), FREE_FUNC, __initial_values));               \
    } while (0)

/**
 * Tries to initialize the dynamic array with initial values without providing
 * the count and saves the result (ok or error) in a temporary result variable
 * and returns if it encounter error
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_try_fail_temp_da_init_with_values(DARRPTR, FREE_FUNC, ...)                                                          \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        dc_try_fail_temp(DCResultVoid,                                                                                         \
                         __dc_da_init_with_values(DARRPTR, dc_count(__initial_values), FREE_FUNC, __initial_values));          \
    } while (0)

/**
 * Macro to append given data to the dynamic array without providing the count
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_da_append_values(DARRPTR, ...)                                                                                      \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        __dc_da_append_values(DARRPTR, dc_count(__initial_values), __initial_values);                                          \
    } while (0)

/**
 * Tries to append given data to the dynamic array without providing the count
 * and saves the result (ok or error) in the given RES
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_try_da_append_values(RES, DARRPTR, ...)                                                                             \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        RES = __dc_da_append_values(DARRPTR, dc_count(__initial_values), __initial_values);                                    \
    } while (0)

/**
 * Tries to append given data to the dynamic array without providing the count
 * and saves the result (ok or error) in the main result variable
 * (__dc_res) and returns if it encounter error
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_try_fail_da_append_values(DARRPTR, ...)                                                                             \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        dc_try_fail(__dc_da_append_values(DARRPTR, dc_count(__initial_values), __initial_values));                             \
    } while (0)

/**
 * Tries to append given data to the dynamic array without providing the count
 * and saves the result (ok or error) in a temporary result variable and returns
 * if it encounter error
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_try_fail_temp_da_append_values(DARRPTR, ...)                                                                        \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        dc_try_fail_temp(DCResultVoid, __dc_da_append_values(DARRPTR, dc_count(__initial_values), __initial_values));          \
    } while (0)

/**
 * Macro to insert given data to the dynamic array at certain index without
 * providing the count
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_da_insert_values(DARRPTR, INDEX, ...)                                                                               \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        __dc_da_insert_values(DARRPTR, INDEX, dc_count(__initial_values), __initial_values);                                   \
    } while (0)

/**
 * Tries to insert given data to the dynamic array at certain index without
 * providing the count and saves the result (ok or error) in the given RES
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_try_da_insert_values(RES, DARRPTR, INDEX, ...)                                                                      \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        RES = __dc_da_insert_values(DARRPTR, INDEX, dc_count(__initial_values), __initial_values);                             \
    } while (0)

/**
 * Tries to insert given data to the dynamic array at certain index without
 * providing the count and saves the result (ok or error) in the main result
 * variable (__dc_res) and returns if it encounter error
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_try_fail_da_insert_values(DARRPTR, INDEX, ...)                                                                      \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        dc_try_fail(__dc_da_insert_values(DARRPTR, INDEX, dc_count(__initial_values), __initial_values));                      \
    } while (0)

/**
 * Tries to insert given data to the dynamic array at certain index without
 * providing the count and saves the result (ok or error) in a temporary result
 * variable (__dc_res) and returns if it encounter error
 *
 * @param DARRPTR address of the array to be initialized (DCDynArr*)
 */
#define dc_try_fail_temp_da_insert_values(DARRPTR, INDEX, ...)                                                                 \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCDynVal, __VA_ARGS__);                                                                    \
        dc_try_fail_temp(DCResultVoid, __dc_da_insert_values(DARRPTR, INDEX, dc_count(__initial_values), __initial_values));   \
    } while (0)

/**
 * Internal macro to generate code for dynamic array to flat array conversion
 */
#define __DC_DA_CONVERT_IMPL(TYPE)                                                                                             \
    DC_RES_usize();                                                                                                            \
    if (!arr || arr->count == 0 || !out_arr)                                                                                   \
    {                                                                                                                          \
        dc_dbg_log("arr is empty or not provided/initialized or out_var is "                                                   \
                   "not provided");                                                                                            \
        dc_res_ret_e(1, "arr is empty or not provided/initialized or out_var is "                                              \
                        "not provided");                                                                                       \
    }                                                                                                                          \
    *out_arr = (TYPE*)malloc((arr->count + 1) * sizeof(TYPE));                                                                 \
    if (!(*out_arr))                                                                                                           \
    {                                                                                                                          \
        dc_dbg_log("memory allocation failed");                                                                                \
        dc_res_ret_e(2, "memory allocation failed");                                                                           \
    }                                                                                                                          \
    usize dest_index = 0;                                                                                                      \
    for (usize i = 0; i < arr->count; ++i)                                                                                     \
    {                                                                                                                          \
        DCDynVal* elem = &arr->elements[i];                                                                                    \
        if (elem->type != dc_dvt(TYPE))                                                                                        \
        {                                                                                                                      \
            if (must_fail)                                                                                                     \
            {                                                                                                                  \
                free(*out_arr);                                                                                                \
                *out_arr = NULL;                                                                                               \
                dc_dbg_log("failed as it got type other than '" #TYPE "'");                                                    \
                dc_res_ret_e(3, "failed as it got type other than '" #TYPE "'");                                               \
            }                                                                                                                  \
            continue;                                                                                                          \
        }                                                                                                                      \
        (*out_arr)[dest_index] = dc_dv_as((*elem), TYPE);                                                                      \
        dest_index++;                                                                                                          \
    }                                                                                                                          \
    (*out_arr)[dest_index] = dc_stopper(TYPE);                                                                                 \
    dc_res_ret_ok(dest_index)

// ***************************************************************************************
// * HASH TABLE MACROS
// ***************************************************************************************

/**
 * Expands to standard hash function declaration
 */
#define DC_HT_HASH_FN_DECL(NAME) DCResultU32 NAME(voidptr _key)

/**
 * Expands to standard hash key comparison function declaration
 */
#define DC_HT_KEY_CMP_FN_DECL(NAME) DCResultBool NAME(voidptr _key1, voidptr _key2)

/**
 * Gets the results of hash table's hash function for the given key
 *
 * And saves the results to the temporary variable of type DCResultU32 then
 * extracts the u32 value of it without checking if the result was an OK or an
 * error
 *
 * NOTE: This assumes operations in the hash function is always OK not error
 */
#define dc_ht_get_hash(VAR_NAME, HT, KEY)                                                                                      \
    u32 VAR_NAME;                                                                                                              \
    do                                                                                                                         \
    {                                                                                                                          \
        DCResultU32 __hash_res = (HT).hash_fn((KEY));                                                                          \
        VAR_NAME = (__hash_res.data.v) % (HT).cap;                                                                             \
    } while (0)

/**
 * Gets the results of hash table's hash function for the given key
 *
 * And saves the results to the main result variable (__dc_res) then
 * extracts the u32 value of it only checking if the result was an OK otherwise
 * it will return the error
 */
#define dc_try_fail_ht_get_hash(VAR_NAME, HT, KEY)                                                                             \
    u32 VAR_NAME;                                                                                                              \
    do                                                                                                                         \
    {                                                                                                                          \
        __dc_res = (HT).hash_fn((KEY));                                                                                        \
        dc_res_fail_if_err2(__dc_res);                                                                                         \
        VAR_NAME = (__dc_res.data.v) % (HT).cap;                                                                               \
    } while (0)

/**
 * Gets the results of hash table's hash function for the given key
 *
 * And saves the results to the temporary variable of type DCResultU32 then
 * extracts the u32 value of it only checking if the result was an OK otherwise
 * it will return the error
 */
#define dc_try_fail_temp_ht_get_hash(VAR_NAME, HT, KEY)                                                                        \
    u32 VAR_NAME;                                                                                                              \
    do                                                                                                                         \
    {                                                                                                                          \
        DCResultU32 __hash_res = (HT).hash_fn((KEY));                                                                          \
        dc_res_fail_if_err2(__hash_res);                                                                                       \
        VAR_NAME = (__hash_res.data.v) % (HT).cap;                                                                             \
    } while (0)

/**
 * Defines VAR_NAME as a pointer to the row of hash table container that the
 * hash indexes to
 *
 * NOTE: VAR_NAME would be DCDynArr*
 */
#define dc_ht_get_container_row(VAR_NAME, HT, HASH) DCDynArr* VAR_NAME = &((HT).container[HASH])

/**
 * Creates a literal hash table key/value pair (entry)
 */
#define dc_ht_entry(KEY, VAL)                                                                                                  \
    (DCHashEntry)                                                                                                              \
    {                                                                                                                          \
        .key = (KEY), .value = (VAL)                                                                                           \
    }

/**
 * Sets multiple key value pairs in a hash table without providing the count
 *
 * NOTE: It does not check whether the result of the success is OK or error
 */
#define dc_ht_set_multiple(HT, ...)                                                                                            \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCHashEntry, __VA_ARGS__);                                                                 \
        __dc_ht_set_multiple(HT, dc_count(__initial_values), __initial_values);                                                \
    } while (0)

/**
 * Tries to sets multiple key value pairs in a hash table without providing the
 * count and saves the result in the given RES (must be defined beforehand of
 * type DCResultVoid)
 *
 * NOTE: It does not check whether the result of the success is OK or error
 */
#define dc_try_ht_set_multiple(RES, HT, ...)                                                                                   \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCHashEntry, __VA_ARGS__);                                                                 \
        RES = __dc_ht_set_multiple(HT, dc_count(__initial_values), __initial_values);                                          \
    } while (0)

/**
 * Tries to sets multiple key value pairs in a hash table without providing the
 * count and saves the result in the given main result variable (__dc_res) and
 * returns if the result is a failure
 */
#define dc_try_fail_ht_set_multiple(HT, ...)                                                                                   \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCHashEntry, __VA_ARGS__);                                                                 \
        dc_try_fail(__dc_ht_set_multiple(HT, dc_count(__initial_values), __initial_values));                                   \
    } while (0)

/**
 * Tries to sets multiple key value pairs in a hash table without providing the
 * count and saves the result in a temporary variable of type DCResultVoid) and
 * returns if the result is a failure
 */
#define dc_try_fail_temp_ht_set_multiple(HT, ...)                                                                              \
    do                                                                                                                         \
    {                                                                                                                          \
        DC_SARRAY(__initial_values, DCHashEntry, __VA_ARGS__);                                                                 \
        dc_try_fail_temp(__dc_ht_set_multiple(HT, dc_count(__initial_values), __initial_values));                              \
    } while (0)

// ***************************************************************************************
// * STRING VIEW MACROS
// ***************************************************************************************

/**
 * Format specifier for string views to be used in printf, dc_sprintf, etc.
 *
 * NOTE: If used `dc_sv_fmt` must be provided to provide proper data for this
 * format specifier
 *
 * @example printf("Hello " DCPRIsv "!", dc_sv_fmt(my_string_view));
 */
#define DCPRIsv "%.*s"

/**
 * If DCPRIsv is used as format specifier this macro should be used to provide
 * both length and pointer to the base string
 *
 * @example printf("Hello " DCPRIsv "!", dc_sv_fmt(my_string_view));
 */
#define dc_sv_fmt(SV) (u32)((SV).len), (SV).str

/**
 * Checks if a string view and a given string are equal or not
 */
#define dc_sv_str_eq(SV, STR) ((strlen(STR) == (SV).len) && (strncmp((SV).str, STR, (SV).len) == 0))

/**
 * Checks if two given string views are equal
 */
#define dc_sv_sv_eq(SV1, SV2) (((SV1).len == (SV2).len) && (strncmp((SV1).str, (SV2).str, (SV1).len) == 0))

// ***************************************************************************************
// * COLOR MACROS
// ***************************************************************************************

#define DC_FG_BLACK "\x1B[30m"
#define DC_FG_RED "\x1B[31m"
#define DC_FG_GREEN "\x1B[32m"
#define DC_FG_YELLOW "\x1B[33m"
#define DC_FG_BLUE "\x1B[34m"
#define DC_FG_MAGENTA "\x1B[35m"
#define DC_FG_CYAN "\x1B[36m"
#define DC_FG_WHITE "\x1B[37m"
#define DC_FG_GRAY "\x1B[90m"
#define DC_FG_LRED "\x1B[91m"
#define DC_FG_LGREEN "\x1B[92m"
#define DC_FG_LYELLOW "\x1B[93m"
#define DC_FG_LBLUE "\x1B[94m"
#define DC_FG_LMAGENTA "\x1B[95m"
#define DC_FG_LCYAN "\x1B[96m"
#define DC_FG_LWHITE "\x1B[97m"

#define DC_BG_BLACK "\x1B[40m"
#define DC_BG_RED "\x1B[41m"
#define DC_BG_GREEN "\x1B[42m"
#define DC_BG_YELLOW "\x1B[43m"
#define DC_BG_BLUE "\x1B[44m"
#define DC_BG_MAGENTA "\x1B[45m"
#define DC_BG_CYAN "\x1B[46m"
#define DC_BG_WHITE "\x1B[47m"
#define DC_BG_GRAY "\x1B[100m"
#define DC_BG_LRED "\x1B[101m"
#define DC_BG_LGREEN "\x1B[102m"
#define DC_BG_LYELLOW "\x1B[103m"
#define DC_BG_LBLUE "\x1B[104m"
#define DC_BG_LMAGENTA "\x1B[105m"
#define DC_BG_LCYAN "\x1B[106m"
#define DC_BG_LWHITE "\x1B[107m"

#define DC_COLOR_RESET "\x1B[0m"

/**
 * Colorizes given literal string by adding background and foreground string at
 * the beginning and color reset at the end
 *
 * NOTE: Just provide color name in ALL CAPS like RED, LRED, ...
 *
 * NOTE: This is not a string allocation process this is simply putting string
 * literals together
 */
#define dc_colorize(BG_COLOR, FG_COLOR, TEXT) DC_BG_##BG_COLOR DC_FG_##FG_COLOR TEXT DC_COLOR_RESET

/**
 * Colorizes given literal string by adding foreground string at
 * the beginning and color reset at the end
 *
 * NOTE: Just provide color name in ALL CAPS like RED, LRED, ...
 *
 * NOTE: This is not a string allocation process this is simply putting string
 * literals together
 */
#define dc_colorize_fg(FG_COLOR, TEXT) DC_FG_##FG_COLOR TEXT DC_COLOR_RESET

/**
 * Colorizes given literal string by adding background string at
 * the beginning and color reset at the end
 *
 * NOTE: Just provide color name in ALL CAPS like RED, LRED, ...
 *
 * NOTE: This is not a string allocation process this is simply putting string
 * literals together
 */
#define dc_colorize_bg(BG_COLOR, TEXT) DC_BG_##BG_COLOR TEXT DC_COLOR_RESET

// ***************************************************************************************
// * CLEANUP MACROS
// ***************************************************************************************

/**
 * Constant for DC_EXIT_SECTION and dc_cleanup_pool_run
 *
 * It means the exit section will trigger dc_cleanup_pool_run in cleaning up
 * the whole pool mode
 */
#define DC_CLEANUP_POOL -1

/**
 * Constant for DC_EXIT_SECTION and dc_cleanup_pool_run
 *
 * It means the exit section will trigger dc_cleanup_pool_run to holdup and
 * does nothing
 */
#define DC_NO_CLEANUP -2

/**
 * Expands to standard function declarations for cleanup process
 */
#define DC_CLEANUP_FN_DECL(NAME) DCResultVoid NAME(voidptr _value)

/**
 * Runs the cleanup process of a cleanup job entry
 */
#define dc_cleanup_job_run(ENTRY) (ENTRY).cleanup_fn(((ENTRY).element))

/**
 * Initializes a cleanup batch with batch capacity only if it is not initialized
 * yet
 */
#define DC_CLEANUP_BATCH_INIT(CLEANUP_BATCH, BATCH_CAPACITY)                                                                   \
    if ((CLEANUP_BATCH).cap == 0) dc_da_init2(&(CLEANUP_BATCH), BATCH_CAPACITY, 3, NULL)

/**
 * Internal macro to register the signals
 */
#define __DC_CLEANUP_REGISTER_SIGNALS                                                                                          \
    signal(SIGINT, __dc_handle_signal);                                                                                        \
    signal(SIGTERM, __dc_handle_signal);                                                                                       \
    signal(SIGSEGV, __dc_handle_signal)

/**
 * Expands to initializing pool with one default batch
 */
#define dc_cleanup_pool_init(BATCH_CAPACITY) dc_cleanup_pool_init2(1, BATCH_CAPACITY)

/**
 * Declares __dc_res with given type and initial value
 *
 * NOTE: This is useful for non-result types, for result type you can use
 * DC_RES() or DC_RES_<type>()
 */
#define DC_RET_VAL_INIT(RETVAL_TYPE, RETVAL_INIT) RETVAL_TYPE __dc_res = RETVAL_INIT

/**
 * Pushes an allocated memory address (ELEMENT) and its corresponding cleanup
 * function pointer to the given batch index
 */
#define dc_cleanup_pool_push(BATCH_INDEX, ELEMENT, CLEAN_FUNC)                                                                 \
    do                                                                                                                         \
    {                                                                                                                          \
        dc_dbg_log("cleanup push to batch index [%d]: %p", BATCH_INDEX, (voidptr)ELEMENT);                                     \
        dc_cleanup_push2(&dc_cleanup_pool.pool[BATCH_INDEX], ELEMENT, CLEAN_FUNC);                                             \
    } while (0)

/**
 * Flushes (frees) selected batch index
 *
 * NOTE: No bound check for BATCH_INDEX warning
 *
 * @return nothing or error
 */
#define dc_cleanup_batch_flush(BATCH_INDEX) dc_da_free(&dc_cleanup_pool.pool[BATCH_INDEX])

/**
 * Pops last n elements from the selected batch index
 *
 * NOTE: No bound check for BATCH_INDEX warning
 *
 * @return nothing or error
 */
#define dc_cleanup_batch_pop(BATCH_INDEX, COUNT) dc_da_pop(&dc_cleanup_pool.pool[BATCH_INDEX], COUNT, NULL, false)

/**
 * Pushes an allocated memory address (ELEMENT) and its corresponding cleanup
 * function pointer to the default batch index which is 0
 */
#define dc_cleanup_default_pool_push(ELEMENT, CLEAN_FUNC) dc_cleanup_pool_push(0, ELEMENT, CLEAN_FUNC)

/**
 * Pushes given hash table address with default standard hash table cleanup in
 * the default batch (index 0)
 */
#define dc_cleanup_push_ht(ELEMENT) dc_cleanup_default_pool_push(ELEMENT, __dc_ht_free)

/**
 * Pushes given hash table address with default standard hash table cleanup in
 * the given batch index
 */
#define dc_cleanup_push_ht2(BATCH_INDEX, ELEMENT) dc_cleanup_pool_push(BATCH_INDEX, ELEMENT, __dc_ht_free)

/**
 * Pushes given dynamic array address with default standard dynamic array
 * cleanup in the default batch (index 0)
 */
#define dc_cleanup_push_da(ELEMENT) dc_cleanup_default_pool_push(ELEMENT, __dc_da_free)

/**
 * Pushes given dynamic array address with default standard dynamic array
 * cleanup in the given batch index
 */
#define dc_cleanup_push_da2(BATCH_INDEX, ELEMENT) dc_cleanup_pool_push(BATCH_INDEX, ELEMENT, __dc_da_free)

/**
 * Pushes given dynamic value address with default standard dynamic value
 * cleanup in the default batch (index 0)
 *
 * NOTE: If your dynamic value has complex cleanup process you need to implement
 * your own standard cleanup function for that and use regular cleanup push or
 * push2 for it
 */
#define dc_cleanup_push_dv(ELEMENT) dc_cleanup_default_pool_push(ELEMENT, __dc_dv_free)

/**
 * Pushes given dynamic value address with default standard dynamic value
 * cleanup in the given batch index
 *
 * NOTE: If your dynamic value has complex cleanup process you need to implement
 * your own standard cleanup function for that and use regular cleanup push or
 * push2 for it
 */
#define dc_cleanup_push_dv2(BATCH_INDEX, ELEMENT) dc_cleanup_pool_push(BATCH_INDEX, ELEMENT, __dc_dv_free)

/**
 * Pushes given result variable address with default standard result variable
 * cleanup in the default batch (index 0)
 */
#define dc_cleanup_push_res(ELEMENT) dc_cleanup_default_pool_push(ELEMENT, dc_result_free)

/**
 * Pushes given result variable address with default standard result variable
 * cleanup in the given batch index
 */
#define dc_cleanup_push_res2(BATCH_INDEX, ELEMENT) dc_cleanup_pool_push(BATCH_INDEX, ELEMENT, dc_result_free)

/**
 * Pushes given allocated memory address with default standard allocated memory
 * cleanup (free) in the default batch (index 0)
 */
#define dc_cleanup_push_free(ELEMENT) dc_cleanup_default_pool_push(ELEMENT, dc_free)

/**
 * Pushes given allocated memory address with default standard allocated memory
 * cleanup (free) in the given batch index
 */
#define dc_cleanup_push_free2(BATCH_INDEX, ELEMENT) dc_cleanup_pool_push(BATCH_INDEX, ELEMENT, dc_free)

/**
 * Pushes given allocated memory address with `fclose` in the default batch
 * (index 0)
 */
#define dc_cleanup_push_file(ELEMENT) dc_cleanup_default_pool_push(ELEMENT, dc_free_file)

/**
 * Pushes given allocated memory address with `fclose` in the given batch index
 */
#define dc_cleanup_push_file2(BATCH_INDEX, ELEMENT) dc_cleanup_pool_push(BATCH_INDEX, ELEMENT, dc_free_file)

/**
 * Defines a label that first triggers the cleanup of choice and then returns
 * the current value of __dc_res
 *
 * NOTE: For scopes that the __dc_res is of result type you don't want to use
 * any direct try_fail stuff as you want to catch the error and jump to the exit
 * point using dc_return or dc_return_with_val
 *
 * @param SELECTION can be `DC_CLEANUP_POOL` or -1 to trigger cleaning up the
 * whole pool and `DC_NO_CLEANUP` or -2 for no cleanup at all, otherwise you can
 * choose to set a valid index for a batch like 0, 1, ... (as long as you've
 * already initialized the pool with correct number of batches)
 */
#define DC_EXIT_SECTION(SELECTION)                                                                                             \
    __dc_exit_label:                                                                                                           \
    dc_cleanup_pool_run(SELECTION);                                                                                            \
    return __dc_res;

/**
 * Jumps to the __dc_exit_label
 *
 * NOTE: DC_EXIT_SECTION must also be used at the end of current scope
 */
#define dc_return() goto __dc_exit_label

/**
 * Sets the __dc_res and jumps to the __dc_exit_label
 *
 * NOTE: DC_EXIT_SECTION must also be used at the end of current scope
 */
#define dc_return_with_val(RETVAL)                                                                                             \
    do                                                                                                                         \
    {                                                                                                                          \
        __dc_res = RETVAL;                                                                                                     \
        dc_return();                                                                                                           \
    } while (0)

/**
 * If provided RES is an error result it catches the error by copying it to
 * __dc_res does PRE_RETURN_ACTIONS and the jumps to __dc_exit_label
 *
 * NOTE: DC_EXIT_SECTION must also be used at the end of current scope
 */
#define dc_return_if_err(RES, PRE_RETURN_ACTIONS)                                                                              \
    do                                                                                                                         \
    {                                                                                                                          \
        if (dc_res_is_err2(RES))                                                                                               \
        {                                                                                                                      \
            do                                                                                                                 \
            {                                                                                                                  \
                PRE_RETURN_ACTIONS;                                                                                            \
            } while (0);                                                                                                       \
            dc_res_err_cpy(RES);                                                                                               \
            dc_return();                                                                                                       \
        }                                                                                                                      \
    } while (0)

/**
 * If provided RES is an error result it does the PRE_RETURN_ACTIONS then sets
 * the __dc_res to RET_VAL and the jumps to __dc_exit_label
 *
 * NOTE: DC_EXIT_SECTION must also be used at the end of current scope
 */
#define dc_return_if_err2(RES, RET_VAL, PRE_RETURN_ACTIONS)                                                                    \
    do                                                                                                                         \
    {                                                                                                                          \
        if (dc_res_is_err2(RES))                                                                                               \
        {                                                                                                                      \
            do                                                                                                                 \
            {                                                                                                                  \
                PRE_RETURN_ACTIONS;                                                                                            \
            } while (0);                                                                                                       \
            dc_return_with_val(RET_VAL);                                                                                       \
        }                                                                                                                      \
    } while (0)

#endif // DC_MACROS_H
