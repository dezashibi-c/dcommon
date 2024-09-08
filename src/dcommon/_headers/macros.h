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
            fprintf(dc_error_log ? dc_error_log : stderr, __VA_ARGS__);        \
            fprintf(dc_error_log ? dc_error_log : stderr, "\n");               \
            if (dc_error_mode == DC_ERR_MODE_STOP)                             \
            {                                                                  \
                abort();                                                       \
            }                                                                  \
            else                                                               \
            {                                                                  \
                FAILURE_ACTION                                                 \
            }                                                                  \
        }                                                                      \
    } while (0)


#define dc_list_make(NAME, TYPE, ...)                                          \
    TYPE NAME[] = {__VA_ARGS__, DC_LST_TERMINATOR_##TYPE}

#define dc_list_count(ARR) (size)(sizeof(ARR) / sizeof(*(ARR)))

#define dc_list_len(ARR) (dc_list_count(ARR) - 1)

#define dc_list_get_last(LST) LST[(dc_list_len(LST) - 1)]

#define dc_list_for_each(LST, TYPE, IT)                                        \
    for (TYPE* IT = LST; !DC_IS_LST_TERMINATOR_##TYPE(*IT); ++IT)

#define dc_list_on_each(LST, TYPE, FN)                                         \
    dc_list_for_each(LST, TYPE, lst_item) FN(lst_item)

#define dc_list_lit_for_each(TYPE, IT, ...)                                    \
    for (TYPE* IT = (TYPE[]){__VA_ARGS__, DC_LST_TERMINATOR_##TYPE};           \
         !DC_IS_LST_TERMINATOR_##TYPE(*IT); ++IT)

#define dc_list_lit_on_each(TYPE, FN, ...)                                     \
    dc_list_lit_for_each(TYPE, item, __VA_ARGS__) FN(item)

#endif // DC_MACROS_H
