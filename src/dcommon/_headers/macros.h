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

#define dc_halt_when(CONDITION, FAILURE_ACTION, ...)                           \
    do                                                                         \
    {                                                                          \
        if (CONDITION)                                                         \
        {                                                                      \
            fprintf(dc_error_logs ? dc_error_logs : stderr, __VA_ARGS__);      \
            fprintf(dc_error_logs ? dc_error_logs : stderr, "\n");             \
            if (dc_error_mode == DC_ERR_MODE_ABORT)                            \
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
// * NON-POINTER ARRAY MACROS
// ***************************************************************************************

#define dc_arr_lit(TYPE, ...)                                                  \
    (TYPE[])                                                                   \
    {                                                                          \
        __VA_ARGS__, DC_ARR_TERMINATOR_##TYPE                                  \
    }

#define dc_array(NAME, TYPE, ...)                                              \
    TYPE NAME[] = {__VA_ARGS__, DC_ARR_TERMINATOR_##TYPE}

#define dc_count(ARR) (size)(sizeof(ARR) / sizeof(*(ARR)))

#define dc_len(ARR) (dc_count(ARR) - 1)

#define dc_last(ARR) ARR[(dc_len(ARR) - 1)]

#define dc_foreach(ARR, TYPE, IT)                                              \
    for (TYPE* IT = ARR; !DC_IS_ARR_TERMINATOR_##TYPE(*IT); ++IT)

#define dc_oneach(ARR, TYPE, FN) dc_foreach(ARR, TYPE, ARR_item) FN(ARR_item)

#define dc_foreach_lit(TYPE, IT, ...)                                          \
    for (TYPE* IT = dc_arr_lit(TYPE, __VA_ARGS__);                             \
         !DC_IS_ARR_TERMINATOR_##TYPE(*IT); ++IT)

#define dc_oneach_lit(TYPE, FN, ...)                                           \
    dc_foreach_lit(TYPE, item, __VA_ARGS__) FN(item)


// ***************************************************************************************
// * POINTER ARRAY MACROS
// ***************************************************************************************

#define dc_parr_lit(TYPE, ...)                                                 \
    (TYPE[])                                                                   \
    {                                                                          \
        __VA_ARGS__, DC_ARR_TERMINATOR_PTR                                     \
    }
#define dc_parray(NAME, TYPE, ...) TYPE** NAME = dc_parr_lit(TYPE*, __VA_ARGS__)

#define dc_pforeach(ARR, TYPE, IT)                                             \
    for (TYPE** IT = ARR; !DC_IS_ARR_TERMINATOR_PTR(*IT); ++IT)

#define dc_poneach(ARR, TYPE, FN) dc_pforeach(ARR, TYPE, ARR_item) FN(ARR_item)

#define dc_pforeach_lit(TYPE, IT, ...)                                         \
    for (TYPE* IT = dc_parr_lit(TYPE, __VA_ARGS__);                            \
         !DC_IS_ARR_TERMINATOR_PTR(*IT); ++IT)

#define dc_poneach_lit(TYPE, FN, ...)                                          \
    dc_pforeach_lit(TYPE*, item, __VA_ARGS__) FN(*item)

#endif // DC_MACROS_H
