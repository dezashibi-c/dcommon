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
#error                                                                         \
    "You cannot use this header (macros.h) directly, please consider including dcommon.h"
#endif

// ***************************************************************************************
// * PRIMITIVE TYPES MACROS
// ***************************************************************************************

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
#define dc_size_as_bool(VAL) ((VAL) != 0)
#define dc_usize_as_bool(VAL) ((VAL) != 0)

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

#define DC_STOPPER_char '\0'

#define DC_STOPPER_size -1
#define DC_STOPPER_usize SIZE_MAX

#define dc_stopper(TYPE) (DC_STOPPER_##TYPE)

// Terminator checks for each type
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

#define DC_IS_ARR_TERMINATOR_char(EL) (EL == DC_STOPPER_char)

#define DC_IS_ARR_TERMINATOR_size(EL) (EL == DC_STOPPER_size)
#define DC_IS_ARR_TERMINATOR_usize(EL) (EL == DC_STOPPER_usize)

#define dc_is_arr_terminator(TYPE, VALUE) (DC_IS_ARR_TERMINATOR_##TYPE(VALUE))

// ***************************************************************************************
// * UTILITY MACROS
// ***************************************************************************************

#if defined(__GNUC__) || defined(__clang__)
#define __dc_attribute(A) __attribute__(A)
#else
#define __dc_attribute(A)
#endif

#define dc_system(OUT_VAL, ...)                                                \
    do                                                                         \
    {                                                                          \
        string __cmd_string;                                                   \
        dc_sprintf(&__cmd_string, __VA_ARGS__);                                \
        OUT_VAL = system(__cmd_string);                                        \
        free(__cmd_string);                                                    \
    } while (0)

#define dc_str_case(ITEM)                                                      \
    case ITEM:                                                                 \
        return #ITEM

#define dc_tostr_bool(B) ((B) ? "true" : "false")

// ***************************************************************************************
// * DETECT OPERATING SYSTEM MACROS
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
// * INTERNAL LOG MACROS MACROS
// ***************************************************************************************

#define __dc_log(CAT, ...)                                                     \
    do                                                                         \
    {                                                                          \
        fprintf(dc_error_logs ? dc_error_logs : stderr, "[%s] %s:%d: ", CAT,   \
                __FILE__, __LINE__);                                           \
        fprintf(dc_error_logs ? dc_error_logs : stderr, __VA_ARGS__);          \
        fprintf(dc_error_logs ? dc_error_logs : stderr, "\n");                 \
    } while (0)

#define __dc_log_if(CAT, CONDITION, ...)                                       \
    do                                                                         \
    {                                                                          \
        if (CONDITION)                                                         \
        {                                                                      \
            __dc_log(CAT, __VA_ARGS__);                                        \
        }                                                                      \
    } while (0)

#define __dc_action_on(CAT, CONDITION, FAILURE_ACTION, ...)                    \
    do                                                                         \
    {                                                                          \
        if (CONDITION)                                                         \
        {                                                                      \
            __dc_log(CAT, __VA_ARGS__);                                        \
            if (dc_error_mode == DC_HALT_MODE_ABORT)                           \
            {                                                                  \
                abort();                                                       \
            }                                                                  \
            else                                                               \
            {                                                                  \
                FAILURE_ACTION;                                                \
            }                                                                  \
        }                                                                      \
    } while (0)


// ***************************************************************************************
// * RESULT MACROS
// ***************************************************************************************

#define dc_res()                                                               \
    DCResult __dc_res;                                                         \
    __dc_res.status = DC_RESULT_OK

#define dc_res2(DC_RESULT_TYPE)                                                \
    DC_RESULT_TYPE __dc_res;                                                   \
    __dc_res.status = DC_RESULT_OK

#define dc_res_bool() dc_res2(DCResultBool)
#define dc_res_void() dc_res2(DCResultVoid)
#define dc_res_sv() dc_res2(DCResultSv)
#define dc_res_da() dc_res2(DCResultDa)
#define dc_res_ht() dc_res2(DCResultHt)
#define dc_res_dv() dc_res2(DCResultDv)

#define dc_res_i8() dc_res2(DCResultI8)
#define dc_res_i16() dc_res2(DCResultI16)
#define dc_res_i32() dc_res2(DCResultI32)
#define dc_res_i64() dc_res2(DCResultI64)
#define dc_res_u8() dc_res2(DCResultU8)
#define dc_res_u16() dc_res2(DCResultU16)
#define dc_res_u32() dc_res2(DCResultU32)
#define dc_res_u64() dc_res2(DCResultU64)
#define dc_res_f32() dc_res2(DCResultF32)
#define dc_res_f64() dc_res2(DCResultF64)
#define dc_res_uptr() dc_res2(DCResultUptr)
#define dc_res_size() dc_res2(DCResultSize)
#define dc_res_usize() dc_res2(DCResultUsize)
#define dc_res_string() dc_res2(DCResultString)
#define dc_res_voidptr() dc_res2(DCResultVoidptr)

#define dc_res_e(NUM, MSG)                                                     \
    do                                                                         \
    {                                                                          \
        __dc_res.status = DC_RESULT_ERR;                                       \
        __dc_res.data.e = (DCError){NUM, MSG, 0};                              \
    } while (0)

#define dc_res_ea(NUM, ...)                                                    \
    do                                                                         \
    {                                                                          \
        string __err;                                                          \
        dc_sprintf(&__err, __VA_ARGS__);                                       \
        __dc_res.status = DC_RESULT_ERR;                                       \
        __dc_res.data.e = (DCError){NUM, __err, 1};                            \
    } while (0)

#define dc_res_ok(VALUE)                                                       \
    do                                                                         \
    {                                                                          \
        __dc_res.status = DC_RESULT_OK;                                        \
        __dc_res.data.v = VALUE;                                               \
    } while (0)

#define dc_res_ok_dv(TYPE, VALUE) dc_res_ok(dc_dv(TYPE, VALUE))

#define dc_res_ok_dva(TYPE, VALUE) dc_res_ok(dc_dva(TYPE, VALUE))

#define dc_res_ret() return __dc_res

#define dc_res_ret_e(NUM, MSG)                                                 \
    do                                                                         \
    {                                                                          \
        dc_res_e(NUM, MSG);                                                    \
        dc_res_ret();                                                          \
    } while (0)

#define dc_res_ret_ea(NUM, ...)                                                \
    do                                                                         \
    {                                                                          \
        dc_res_ea(NUM, __VA_ARGS__);                                           \
        dc_res_ret();                                                          \
    } while (0)

#define dc_res_ret_ok(VALUE)                                                   \
    do                                                                         \
    {                                                                          \
        dc_res_ok(VALUE);                                                      \
        dc_res_ret();                                                          \
    } while (0)

#define dc_res_ret_ok_dv(TYPE, VALUE)                                          \
    do                                                                         \
    {                                                                          \
        dc_res_ok_dv(TYPE, VALUE);                                             \
        dc_res_ret();                                                          \
    } while (0)

#define dc_res_ret_ok_dva(TYPE, VALUE)                                         \
    do                                                                         \
    {                                                                          \
        dc_res_ok_dva(TYPE, VALUE);                                            \
        dc_res_ret();                                                          \
    } while (0)

#define dc_ret_if_err()                                                        \
    if (__dc_res.status == DC_RESULT_ERR) return __dc_res

#define dc_try(CALL) __dc_res = CALL

#define dc_try_fail(CALL)                                                      \
    do                                                                         \
    {                                                                          \
        __dc_res = CALL;                                                       \
        dc_ret_if_err();                                                       \
    } while (0)

#define dc_fail_if_res(RES)                                                    \
    do                                                                         \
    {                                                                          \
        if ((RES).status == DC_RESULT_ERR)                                     \
        {                                                                      \
            dc_res_ea((RES).data.e.code, "%s", (RES).data.e.message);          \
            dc_result_free(&RES);                                              \
            dc_res_ret();                                                      \
        }                                                                      \
    } while (0)

#define dc_try_fail_temp(RES_TYPE, CALL)                                       \
    do                                                                         \
    {                                                                          \
        RES_TYPE __temp_res = CALL;                                            \
        dc_fail_if_res(__temp_res);                                            \
    } while (0)

#define dc_try_def(CALL)                                                       \
    dc_res();                                                                  \
    dc_try_fail(CALL)

#define dc_try_def2(DC_RESULT_TYPE, CALL)                                      \
    dc_res2(DC_RESULT_TYPE);                                                   \
    dc_try_fail(CALL)

#define dc_res_as(TYPE) dc_dv_as(__dc_res.data.v, TYPE)

#define dc_res_is_ok() (__dc_res.status == DC_RESULT_OK)
#define dc_res_is_ok2(RES) ((RES).status == DC_RESULT_OK)

#define dc_res_is_err() (__dc_res.status == DC_RESULT_ERR)
#define dc_res_is_err2(RES) ((RES).status == DC_RESULT_ERR)

#define dc_res_val() (__dc_res.data.v)
#define dc_res_val2(RES) ((RES).data.v)

#define dc_res_status() (__dc_res.status)
#define dc_res_status2(RES) ((RES).status)

#define dc_res_err() (__dc_res.data.e)
#define dc_res_err2(RES) ((RES).data.e)

#define dc_res_err_code() (__dc_res.data.e.code)
#define dc_res_err_code2(RES) ((RES).data.e.code)

#define dc_res_err_msg() (__dc_res.data.e.message)
#define dc_res_err_msg2(RES) ((RES).data.e.message)


// ***************************************************************************************
// * LOG MACROS
// ***************************************************************************************

#define dc_log(...) __dc_log("LOG", __VA_ARGS__)

#define dc_log_if(CONDITION, ...) __dc_log_if("LOG", CONDITION, __VA_ARGS__)

#define dc_action_on(CONDITION, FAILURE_ACTION, ...)                           \
    __dc_action_on("LOG", CONDITION, FAILURE_ACTION, __VA_ARGS__)


#ifdef DC_DEBUG

#define dc_dbg_log(...) __dc_log("DEBUG", __VA_ARGS__)

#define dc_dbg_log_if(CONDITION, ...)                                          \
    __dc_log_if("DEBUG", CONDITION, __VA_ARGS__)

#define dc_dbg_action_on(CONDITION, FAILURE_ACTION, ...)                       \
    __dc_action_on("DEBUG", CONDITION, FAILURE_ACTION, __VA_ARGS__)

#else

#define dc_dbg_log(...)

#define dc_dbg_log_if(CONDITION, ...)

#define dc_dbg_action_on(CONDITION, FAILURE_ACTION, ...)

#endif

// ***************************************************************************************
// * NON-POINTER ARRAY MACROS
// ***************************************************************************************


#define dc_arr_lit(TYPE, ...)                                                  \
    (TYPE[])                                                                   \
    {                                                                          \
        __VA_ARGS__, dc_stopper(TYPE)                                          \
    }

#define dc_array(NAME, TYPE, ...) TYPE NAME[] = {__VA_ARGS__, dc_stopper(TYPE)}

#define dc_count(ARR) (size)(sizeof(ARR) / sizeof(*(ARR)))

#define dc_len(ARR) (dc_count(ARR) - 1)

#define dc_last(ARR) ARR[(dc_len(ARR) - 1)]

#define dc_foreach(ARR, TYPE)                                                  \
    for (TYPE* _it = ARR; !dc_is_arr_terminator(TYPE, *_it); ++_it)

#define dc_oneach(ARR, TYPE, FN) dc_foreach(ARR, TYPE) FN(_it)

#define dc_foreach_lit(TYPE, ...)                                              \
    for (TYPE* _it = dc_arr_lit(TYPE, __VA_ARGS__);                            \
         !dc_is_arr_terminator(TYPE, *_it); ++_it)

#define dc_oneach_lit(TYPE, FN, ...) dc_foreach_lit(TYPE, __VA_ARGS__) FN(_it)


// ***************************************************************************************
// * POINTER ARRAY MACROS
// ***************************************************************************************

#define dc_parr_lit(TYPE, ...)                                                 \
    (TYPE[])                                                                   \
    {                                                                          \
        __VA_ARGS__, DC_STOPPER_voidptr                                        \
    }
#define dc_parray(NAME, TYPE, ...) TYPE** NAME = dc_parr_lit(TYPE*, __VA_ARGS__)

#define dc_pforeach(ARR, TYPE)                                                 \
    for (TYPE** _it = ARR; !DC_IS_ARR_TERMINATOR_voidptr(*_it); ++_it)

#define dc_poneach(ARR, TYPE, FN) dc_pforeach(ARR, TYPE) FN(_it)

#define dc_pforeach_lit(TYPE, ...)                                             \
    for (TYPE* _it = dc_parr_lit(TYPE, __VA_ARGS__);                           \
         !DC_IS_ARR_TERMINATOR_voidptr(*_it); ++_it)

#define dc_poneach_lit(TYPE, FN, ...)                                          \
    dc_pforeach_lit(TYPE*, __VA_ARGS__) FN(*_it)

// ***************************************************************************************
// * STRUCT ARRAY MACROS
// ***************************************************************************************

#define dc_sarr_lit(TYPE, ...)                                                 \
    (TYPE[])                                                                   \
    {                                                                          \
        __VA_ARGS__                                                            \
    }
#define dc_sarray(NAME, TYPE, ...) TYPE NAME[] = {__VA_ARGS__}

#define dc_sforeach(ARR, TYPE, TERMINATION_CONDITION)                          \
    for (TYPE* _it = ARR; TERMINATION_CONDITION; ++_it)

#define dc_soneach(ARR, TYPE, TERMINATION_CONDITION, FN)                       \
    dc_sforeach(ARR, TYPE, TERMINATION_CONDITION) FN(_it)

#define dc_sforeach_lit(TYPE, TERMINATION_CONDITION, ...)                      \
    for (TYPE* _it = dc_sarr_lit(TYPE, __VA_ARGS__); TERMINATION_CONDITION;    \
         ++_it)

#define dc_soneach_lit(TYPE, TERMINATION_CONDITION, FN, ...)                   \
    dc_sforeach_lit(TYPE, TERMINATION_CONDITION, __VA_ARGS__) FN(_it)

// ***************************************************************************************
// * DYNAMIC ARRAY MACROS
// ***************************************************************************************

#ifndef DC_DYNARR_INITIAL_CAP
#define DC_DYNARR_INITIAL_CAP 4
#endif

#ifndef DC_DYNARR_CAP_MULTIPLIER
#define DC_DYNARR_CAP_MULTIPLIER 2
#endif

#define dc_dv_free_fn_decl(NAME) void NAME(DCDynValue* _value)

#define dc_dvt(TYPE) DC_DYN_VAL_TYPE_##TYPE

#define dc_dv(TYPE, VALUE)                                                     \
    (DCDynValue)                                                               \
    {                                                                          \
        .type = dc_dvt(TYPE), .value.TYPE##_val = VALUE, .allocated = false    \
    }

#define dc_dva(TYPE, VALUE)                                                    \
    (DCDynValue)                                                               \
    {                                                                          \
        .type = dc_dvt(TYPE), .value.TYPE##_val = VALUE, .allocated = true     \
    }

#define dc_dv_def(NAME, TYPE, VALUE, ALLOC)                                    \
    DCDynValue NAME = {                                                        \
        .type = dc_dvt(TYPE), .value.TYPE##_val = VALUE, .allocated = ALLOC}

#define dc_dv_set(NAME, TYPE, VALUE)                                           \
    (NAME).type = dc_dvt(TYPE);                                                \
    (NAME).value.TYPE##_val = VALUE

#define dc_dv_mark_alloc(NAME) (NAME).allocated = true

#define dc_dv_seta(NAME, TYPE, VALUE)                                          \
    dc_dv_set(NAME, TYPE, VALUE);                                              \
    dc_dv_mark_alloc(NAME)

#define dc_dv_is(NAME, TYPE) ((NAME).type == dc_dvt(TYPE))

#define dc_dv_is_not(NAME, TYPE) ((NAME).type != dc_dvt(TYPE))

#define dc_dv_as(NAME, TYPE) ((NAME).value.TYPE##_val)

#define dc_dv_is_allocated(NAME) ((NAME).allocated)

#define dc_da_get_as(DYNARR, INDEX, TYPE)                                      \
    dc_dv_as(*dc_res_val2(dc_da_get(DYNARR, INDEX)), TYPE)

#define dc_da_is(DYNARR, INDEX, TYPE) dc_dv_is((DYNARR).elements[INDEX], TYPE)

#define dc_da_is_not(DYNARR, INDEX, TYPE)                                      \
    dc_dv_is_not((DYNARR).elements[INDEX], TYPE)

#define dc_da_for(DYNARR) for (usize _idx = 0; _idx < (DYNARR).count; _idx++)

// Function to initialize the dynamic array with initial values
#define dc_da_init_with_values(DYNARRPTR, FREE_FUNC, ...)                      \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        __dc_da_init_with_values(DYNARRPTR, dc_count(__initial_values),        \
                                 FREE_FUNC, __initial_values);                 \
    } while (0)

#define dc_try_da_init_with_values(RES, DYNARRPTR, FREE_FUNC, ...)             \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        RES = __dc_da_init_with_values(DYNARRPTR, dc_count(__initial_values),  \
                                       FREE_FUNC, __initial_values);           \
    } while (0)

#define dc_try_fail_da_init_with_values(DYNARRPTR, FREE_FUNC, ...)             \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        dc_try_fail(__dc_da_init_with_values(DYNARRPTR,                        \
                                             dc_count(__initial_values),       \
                                             FREE_FUNC, __initial_values));    \
    } while (0)

#define dc_try_fail_temp_da_init_with_values(DYNARRPTR, FREE_FUNC, ...)        \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        dc_try_fail_temp(                                                      \
            DCResultVoid,                                                      \
            __dc_da_init_with_values(DYNARRPTR, dc_count(__initial_values),    \
                                     FREE_FUNC, __initial_values));            \
    } while (0)

#define dc_da_append_values(DYNARRPTR, ...)                                    \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        __dc_da_append_values(DYNARRPTR, dc_count(__initial_values),           \
                              __initial_values);                               \
    } while (0)

#define dc_try_da_append_values(RES, DYNARRPTR, ...)                           \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        RES = __dc_da_append_values(DYNARRPTR, dc_count(__initial_values),     \
                                    __initial_values);                         \
    } while (0)

#define dc_try_fail_da_append_values(DYNARRPTR, ...)                           \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        dc_try_fail(__dc_da_append_values(                                     \
            DYNARRPTR, dc_count(__initial_values), __initial_values));         \
    } while (0)

#define dc_try_fail_temp_da_append_values(DYNARRPTR, ...)                      \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        dc_try_fail_temp(DCResultVoid,                                         \
                         __dc_da_append_values(DYNARRPTR,                      \
                                               dc_count(__initial_values),     \
                                               __initial_values));             \
    } while (0)

#define dc_da_insert_values(DYNARRPTR, INDEX, ...)                             \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        __dc_da_insert_values(DYNARRPTR, INDEX, dc_count(__initial_values),    \
                              __initial_values);                               \
    } while (0)

#define dc_try_da_insert_values(RES, DYNARRPTR, INDEX, ...)                    \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        RES = __dc_da_insert_values(                                           \
            DYNARRPTR, INDEX, dc_count(__initial_values), __initial_values);   \
    } while (0)

#define dc_try_fail_da_insert_values(DYNARRPTR, INDEX, ...)                    \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        dc_try_fail(__dc_da_insert_values(                                     \
            DYNARRPTR, INDEX, dc_count(__initial_values), __initial_values));  \
    } while (0)

#define dc_try_fail_temp_da_insert_values(DYNARRPTR, INDEX, ...)               \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCDynValue, __VA_ARGS__);                  \
        dc_try_fail_temp(DCResultVoid,                                         \
                         __dc_da_insert_values(DYNARRPTR, INDEX,               \
                                               dc_count(__initial_values),     \
                                               __initial_values));             \
    } while (0)

#define __dc_da_converters_decl(TYPE)                                          \
    DCResultUsize dc_##TYPE##_da_to_flat_arr(DCDynArr* arr, TYPE** out_arr,    \
                                             bool must_fail)

#define __dc_da_converters_impl(TYPE)                                          \
    dc_res_usize();                                                            \
    if (!arr || arr->count == 0 || !out_arr)                                   \
    {                                                                          \
        dc_res_ret_e(1,                                                        \
                     "arr is empty or not provided/initialized or out_var is " \
                     "not provided");                                          \
    }                                                                          \
    *out_arr = (TYPE*)malloc((arr->count + 1) * sizeof(TYPE));                 \
    if (!(*out_arr))                                                           \
    {                                                                          \
        dc_res_ret_e(2, "memory allocation failed");                           \
    }                                                                          \
    usize dest_index = 0;                                                      \
    for (usize i = 0; i < arr->count; ++i)                                     \
    {                                                                          \
        DCDynValue* elem = &arr->elements[i];                                  \
        if (elem->type != dc_dvt(TYPE))                                        \
        {                                                                      \
            if (must_fail)                                                     \
            {                                                                  \
                free(*out_arr);                                                \
                *out_arr = NULL;                                               \
                dc_res_ret_e(-1,                                               \
                             "failed as it got type other than '" #TYPE "'");  \
            }                                                                  \
            continue;                                                          \
        }                                                                      \
        (*out_arr)[dest_index] = dc_dv_as((*elem), TYPE);                      \
        dest_index++;                                                          \
    }                                                                          \
    (*out_arr)[dest_index] = dc_stopper(TYPE);                                 \
    dc_res_ret_ok(dest_index)

// todo:: inspect why dc_stopper returns stupid value

// ***************************************************************************************
// * HASH TABLE MACROS
// ***************************************************************************************

#define dc_ht_hash_fn_decl(NAME) DCResultU32 NAME(voidptr _key)
#define dc_ht_key_comp_fn_decl(NAME)                                           \
    DCResultBool NAME(voidptr _key1, voidptr _key2)

#define dc_ht_get_hash(VAR_NAME, HT, KEY)                                      \
    u32 VAR_NAME;                                                              \
    do                                                                         \
    {                                                                          \
        DCResultU32 __hash_res = (HT).hash_fn((KEY));                          \
        VAR_NAME = (__hash_res.data.v) % (HT).cap;                             \
    } while (0)

#define dc_try_ht_get_hash(RES, VAR_NAME, HT, KEY)                             \
    u32 VAR_NAME;                                                              \
    do                                                                         \
    {                                                                          \
        RES = (HT).hash_fn((KEY));                                             \
        VAR_NAME = ((RES).data.v) % (HT).cap;                                  \
    } while (0)

#define dc_try_fail_ht_get_hash(VAR_NAME, HT, KEY)                             \
    u32 VAR_NAME;                                                              \
    do                                                                         \
    {                                                                          \
        __dc_res = (HT).hash_fn((KEY));                                        \
        dc_fail_if_res(__dc_res);                                              \
        VAR_NAME = (__dc_res.data.v) % (HT).cap;                               \
    } while (0)

#define dc_try_fail_temp_ht_get_hash(VAR_NAME, HT, KEY)                        \
    u32 VAR_NAME;                                                              \
    do                                                                         \
    {                                                                          \
        DCResultU32 __hash_res = (HT).hash_fn((KEY));                          \
        dc_fail_if_res(__hash_res);                                            \
        VAR_NAME = (__hash_res.data.v) % (HT).cap;                             \
    } while (0)

#define dc_ht_get_container_row(VAR_NAME, HT, HASH)                            \
    DCDynArr* VAR_NAME = &((HT).container[HASH])

#define dc_ht_entry(KEY, VAL)                                                  \
    (DCHashEntry)                                                              \
    {                                                                          \
        .key = (KEY), .value = (VAL)                                           \
    }

#define dc_ht_set_multiple(HT, ...)                                            \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCHashEntry, __VA_ARGS__);                 \
        __dc_ht_set_multiple(HT, dc_count(__initial_values),                   \
                             __initial_values);                                \
    } while (0)

#define dc_try_ht_set_multiple(RES, HT, ...)                                   \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCHashEntry, __VA_ARGS__);                 \
        RES = __dc_ht_set_multiple(HT, dc_count(__initial_values),             \
                                   __initial_values);                          \
    } while (0)

#define dc_try_fail_ht_set_multiple(HT, ...)                                   \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCHashEntry, __VA_ARGS__);                 \
        dc_try_fail(__dc_ht_set_multiple(HT, dc_count(__initial_values),       \
                                         __initial_values));                   \
    } while (0)

#define dc_try_fail_temp_ht_set_multiple(HT, ...)                              \
    do                                                                         \
    {                                                                          \
        dc_sarray(__initial_values, DCHashEntry, __VA_ARGS__);                 \
        dc_try_fail_temp(__dc_ht_set_multiple(HT, dc_count(__initial_values),  \
                                              __initial_values));              \
    } while (0)

// ***************************************************************************************
// * STRING VIEW MACROS
// ***************************************************************************************

#define DC_SV_FMT "%.*s"
#define dc_sv_fmt_val(SV) (u32)((SV).len), (SV).str

#define dc_sv_str_eq(SV, STR)                                                  \
    ((strlen(STR) == (SV).len) && (strncmp((SV).str, STR, (SV).len) == 0))

#define dc_sv_sv_eq(SV1, SV2)                                                  \
    (((SV1).len == (SV2).len) &&                                               \
     (strncmp((SV1).str, (SV2).str, (SV1).len) == 0))

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

#define dc_colorize(BG_COLOR, FG_COLOR, TEXT)                                  \
    DC_BG_##BG_COLOR operator DC_FG_##FG_COLOR TEXT operator DC_COLOR_RESET

#define dc_colorize_fg(FG_COLOR, TEXT) DC_FG_##FG_COLOR TEXT DC_COLOR_RESET

#define dc_colorize_bg(BG_COLOR, TEXT) DC_BG_##BG_COLOR TEXT DC_COLOR_RESET

// ***************************************************************************************
// * CLEANUP MACROS
// ***************************************************************************************

#define dc_cleanups_fn_decl(NAME) void NAME(voidptr _value)

#define dc_cleanup_do(ENTRY) (ENTRY).cleanup_fn(((ENTRY).element))

#define __dc_cleanups_arr_init(CLEANUPS, CAPACITY)                             \
    if ((CLEANUPS).cap == 0) dc_da_init_custom(&(CLEANUPS), CAPACITY, 3, NULL)

#define dc_global_cleanups_init(CAPACITY)                                      \
    do                                                                         \
    {                                                                          \
        __dc_cleanups_arr_init(dc_cleanups, CAPACITY);                         \
        signal(SIGINT, __dc_handle_signal);                                    \
        signal(SIGTERM, __dc_handle_signal);                                   \
        signal(SIGSEGV, __dc_handle_signal);                                   \
    } while (0)

#define dc_ret_val_decl(RETVAL_TYPE, RETVAL_INIT)                              \
    RETVAL_TYPE __dc_ret_val = RETVAL_INIT

#define dc_cleanups_push(ELEMENT, CLEAN_FUNC)                                  \
    dc_dbg_log("global cleanup push: %p", (voidptr)ELEMENT);                   \
    dc_cleanups_res =                                                          \
        __dc_cleanups_custom_push(&dc_cleanups, ELEMENT, CLEAN_FUNC)

#define dc_cleanups_push_ht(ELEMENT) dc_cleanups_push(ELEMENT, __dc_ht_free)

#define dc_cleanups_push_da(ELEMENT) dc_cleanups_push(ELEMENT, __dc_da_free)

#define dc_cleanups_push_dv(ELEMENT) dc_cleanups_push(ELEMENT, __dc_dv_free)

#define dc_cleanups_push_res(ELEMENT) dc_cleanups_push(ELEMENT, dc_result_free)

#define dc_cleanups_push_free(ELEMENT) dc_cleanups_push(ELEMENT, dc_free)

#define dc_def_exit_label()                                                    \
    __dc_exit_label:                                                           \
    dc_perform_cleanup();                                                      \
    return __dc_ret_val;

#define dc_return(RETVAL)                                                      \
    __dc_ret_val = RETVAL;                                                     \
    goto __dc_exit_label

#endif // DC_MACROS_H
