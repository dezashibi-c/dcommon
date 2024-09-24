// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: _da.c
//    Date: 2024-09-10
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more
//     information about the licensing of this work. If you have any questions
//     or concerns, please feel free to contact me at the email address provided
//     above.
// ***************************************************************************************
// *  Description: private implementation file for definition of common helper
// *               functions
// *               DO NOT LINK TO THIS DIRECTLY
// ***************************************************************************************

#ifndef __DC_BYPASS_PRIVATE_PROTECTION
#error                                                                         \
    "You cannot link to this source (_da.c) directly, please consider including dcommon.h"
#endif

#include "_headers/aliases.h"
#include "_headers/general.h"
#include "_headers/macros.h"

DCResultBool dc_dv_as_bool(DCDynValue* dv)
{
    dc_res_bool();

    if (!dv) dc_res_ret_e(1, "got NULL DCDynValue");

#define type_to_bool(TYPE)                                                     \
    case dc_dvt(TYPE):                                                         \
        dc_res_ret_ok(dc_as_bool(TYPE, dv->value.TYPE##_val));

    switch (dv->type)
    {
        type_to_bool(u8);
        type_to_bool(u16);
        type_to_bool(u32);
        type_to_bool(u64);
        type_to_bool(i8);
        type_to_bool(i16);
        type_to_bool(i32);
        type_to_bool(i64);
        type_to_bool(f32);
        type_to_bool(f64);
        type_to_bool(uptr);
        type_to_bool(char);
        type_to_bool(string);
        type_to_bool(voidptr);
        type_to_bool(size);
        type_to_bool(usize);

        default:
            break;
    };

    dc_res_ret_e(3, "unkown dynamic value type");
#undef type_to_bool
}

// Function to initialize the dynamic array
DCResultVoid dc_da_init(DCDynArr* darr, DCDynValFreeFn element_free_fn)
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    darr->cap = DC_DYNARR_INITIAL_CAP;
    darr->count = 0;
    darr->multiplier = DC_DYNARR_CAP_MULTIPLIER;

    darr->element_free_fn = element_free_fn;

    darr->elements = malloc(DC_DYNARR_INITIAL_CAP * sizeof(DCDynValue));
    if (darr->elements == NULL)
    {
        dc_dbg_log("Memory allocation failed");

        dc_res_ret_e(2, "Memory allocation failed");
    }

    dc_res_ret();
}

DCResultVoid dc_da_init_custom(DCDynArr* darr, usize capacity,
                               usize capacity_grow_multiplier,
                               DCDynValFreeFn element_free_fn)
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    darr->cap = capacity;
    darr->count = 0;
    darr->multiplier = capacity_grow_multiplier;

    darr->element_free_fn = element_free_fn;

    darr->elements = malloc(capacity * sizeof(DCDynValue));

    if (darr->elements == NULL)
    {
        dc_dbg_log("Memory allocation failed");

        dc_res_ret_e(2, "Memory allocation failed");
    }

    dc_res_ret();
}


DCResultDa dc_da_new(DCDynValFreeFn element_free_fn)
{
    dc_res_da();

    DCDynArr* darr = malloc(sizeof(DCDynArr));
    if (darr == NULL)
    {
        dc_dbg_log("Memory allocation failed");

        dc_res_ret_e(2, "Memory allocation failed");
    }

    dc_try_fail_temp(DCResultVoid, dc_da_init(darr, element_free_fn));

    dc_res_ret_ok(darr);
}

DCResultDa dc_da_new_custom(usize capacity, usize capacity_grow_multiplier,
                            DCDynValFreeFn element_free_fn)
{
    dc_res_da();

    DCDynArr* darr = malloc(sizeof(DCDynArr));
    if (darr == NULL)
    {
        dc_dbg_log("Memory allocation failed");

        dc_res_ret_e(2, "Memory allocation failed");
    }

    dc_try_fail_temp(DCResultVoid,
                     dc_da_init_custom(darr, capacity, capacity_grow_multiplier,
                                       element_free_fn));

    dc_res_ret_ok(darr);
}

// Function to initialize the dynamic array with initial values
DCResultVoid __dc_da_init_with_values(DCDynArr* darr, usize count,
                                      DCDynValFreeFn element_free_fn,
                                      DCDynValue values[])
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    darr->cap = count;
    darr->count = 0;
    darr->multiplier = DC_DYNARR_CAP_MULTIPLIER;

    darr->element_free_fn = element_free_fn;

    darr->elements = malloc((count == 0 ? DC_DYNARR_INITIAL_CAP : count) *
                            sizeof(DCDynValue));
    if (darr->elements == NULL)
    {
        dc_dbg_log("Memory allocation failed");

        dc_res_ret_e(2, "Memory allocation failed");
    }

    for (usize i = 0; i < count; ++i)
    {
        dc_try_fail(dc_da_push(darr, values[i]));
    }

    dc_res_ret();
}

DCResultVoid dc_da_grow(DCDynArr* darr)
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    if (darr->cap > (SIZE_MAX / darr->multiplier) / sizeof(DCDynValue))
    {
        dc_dbg_log("Array size too large, cannot allocate more memory");

        dc_res_ret_e(2, "Array size too large, cannot allocate more memory");
    }

    // Resize the array if needed (double the capacity by default)
    DCDynValue* resized = realloc(darr->elements, darr->cap * darr->multiplier *
                                                      sizeof(DCDynValue));

    if (resized == NULL)
    {
        dc_dbg_log("Memory re-allocation failed");

        dc_res_ret_e(2, "Memory re-allocation failed");
    }

    darr->elements = resized;
    darr->cap *= darr->multiplier;

    dc_res_ret();
}

DCResultVoid dc_da_grow_by(DCDynArr* darr, usize amount)
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    DCDynValue* resized =
        realloc(darr->elements, (darr->cap + amount) * sizeof(DCDynValue));

    if (resized == NULL)
    {
        dc_dbg_log("Memory re-allocation failed");

        dc_res_ret_e(2, "Memory re-allocation failed");
    }

    darr->cap += amount;
    darr->elements = resized;

    dc_res_ret();
}

DCResultVoid dc_da_grow_to(DCDynArr* darr, usize amount)
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    DCDynValue* resized = realloc(darr->elements, amount * sizeof(DCDynValue));

    if (resized == NULL)
    {
        dc_dbg_log("Memory re-allocation failed");

        dc_res_ret_e(2, "Memory re-allocation failed");
    }

    darr->cap = amount;
    darr->elements = resized;

    dc_res_ret();
}

DCResultVoid dc_da_trunc(DCDynArr* darr)
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    if (darr->count < darr->cap)
    {
        DCDynValue* resized =
            realloc(darr->elements, darr->count * sizeof(DCDynValue));

        if (resized == NULL)
        {
            dc_dbg_log("Memory re-allocation failed");

            dc_res_ret_e(2, "Memory re-allocation failed");
        }

        darr->cap = darr->count;
        darr->elements = resized;
    }

    dc_res_ret();
}

DCResultVoid dc_da_pop(DCDynArr* darr, usize count, DCDynValue** out_popped,
                       bool truncate)
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    if (count > darr->count)
    {
        dc_dbg_log("Try to pop elements more than actual number of elements");

        dc_res_ret_e(4,
                     "Try to pop elements more than actual number of elements");
    }

    if (out_popped != NULL)
    {
        *out_popped = (DCDynValue*)malloc(count * sizeof(DCDynValue));

        if (!out_popped)
        {
            dc_dbg_log("Memory re-allocation failed");

            dc_res_ret_e(2, "Memory re-allocation failed");
        }
    }

    usize last_item_index = darr->count - 1;

    for (i32 i = count - 1; i >= 0; --i)
    {
        if (out_popped) (*out_popped)[i] = darr->elements[last_item_index - i];

        dc_try_fail(dc_dv_free(&darr->elements[last_item_index - i],
                               darr->element_free_fn));

        darr->count--;
    }

    if (truncate) dc_try_fail(dc_da_trunc(darr));

    dc_res_ret();
}

// Function to add an element to the dynamic array
DCResultVoid dc_da_push(DCDynArr* darr, DCDynValue value)
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    if (darr->count >= darr->cap) dc_try_fail(dc_da_grow(darr));

    // Add the new element with its type and value
    darr->elements[darr->count] = value;
    darr->count++;

    dc_res_ret();
}

DCResultVoid __dc_da_append_values(DCDynArr* darr, usize count,
                                   DCDynValue values[])
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    if ((count + darr->count) > darr->cap)
        dc_try_fail(dc_da_grow_to(darr, count + darr->count));

    for (usize i = 0; i < count; ++i)
    {
        dc_try_fail(dc_da_push(darr, values[i]));
    }

    dc_res_ret();
}

DCResultVoid dc_da_append(DCDynArr* darr, DCDynArr* from)
{
    dc_res_void();

    if (!darr || !from) dc_res_ret_e(1, "got NULL DCDynArr");

    dc_try_fail(__dc_da_append_values(darr, from->count, from->elements));

    dc_res_ret();
}

DCResultDv dc_da_get(DCDynArr* darr, usize index)
{
    dc_res_dv();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    if (index >= darr->count)
    {
        dc_dbg_log("Index out of bound - try to get index='%" PRIuMAX
                   "' out of actual '%" PRIuMAX "' elements.",
                   index, darr->count);

        dc_res_ret_e(4, "Index out of bound");
    }

    dc_res_ret_ok(&darr->elements[index]);
}

DCResultBool dc_dv_eq(DCDynValue* dv1, DCDynValue* dv2)
{
    dc_res2(DCResultBool);

    if (!dv1 || !dv2) dc_res_ret_e(1, "cannot compare DCDynValue with NULL");

    if (dv1->type != dv2->type) dc_res_ret_ok(false);

#define check_eq(TYPE)                                                         \
    case dc_dvt(TYPE):                                                         \
        if (dv1->value.TYPE##_val == dv2->value.TYPE##_val)                    \
            dc_res_ret_ok(true);                                               \
        break

    switch (dv1->type)
    {
        check_eq(i8);
        check_eq(i16);
        check_eq(i32);
        check_eq(i64);

        check_eq(u8);
        check_eq(u16);
        check_eq(u32);
        check_eq(u64);

        check_eq(f32);
        check_eq(f64);

        check_eq(uptr);
        check_eq(char);

        case dc_dvt(string):
        {
            if (strcmp(dv1->value.string_val, dv2->value.string_val) == 0)
                dc_res_ret_ok(true);
            break;
        }

            // clang-format off
        check_eq(voidptr);
        check_eq(size);
        check_eq(usize);
            // clang-format on

        default:
            break;
    }

    dc_res_ret_ok(false);

#undef check_eq
}

// Function to find an element in the dynamic array
DCResultDv dc_da_find(DCDynArr* darr, DCDynValue* el)
{
    dc_res_dv();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

#define find_if(TYPE)                                                          \
    case dc_dvt(TYPE):                                                         \
        if (element->value.TYPE##_val == el->value.TYPE##_val)                 \
            dc_res_ret_ok(element);                                            \
        break
    for (usize i = 0; i < darr->count; i++)
    {
        DCDynValue* element = &darr->elements[i];
        if (element->type != el->type)
        {
            continue; // Skip if the type doesn't match
        }

        // check the actual value based on the type
        switch (el->type)
        {
            find_if(i8);
            find_if(i16);
            find_if(i32);
            find_if(i64);

            find_if(u8);
            find_if(u16);
            find_if(u32);
            find_if(u64);

            find_if(f32);
            find_if(f64);

            find_if(uptr);
            find_if(char);

            case dc_dvt(string):
            {
                if (strcmp(element->value.string_val, el->value.string_val) ==
                    0)
                    dc_res_ret_ok(element);
                break;
            }

                // clang-format off
            find_if(voidptr);
            find_if(size);
            find_if(usize);
                // clang-format on

            default:
                break;
        }
    }
#undef find_if

    dc_res_ret_ok(NULL); // Not Found
}

DCResultVoid dc_dv_free(DCDynValue* element, DCDynValFreeFn custom_free)
{
    dc_res_void();

    if (!element) dc_res_ret();

    switch (element->type)
    {
        case DC_DYN_VAL_TYPE_string:
        {
            if (custom_free)
                dc_try_fail_temp(DCResultVoid, custom_free(element));

            if (dc_dv_is_allocated(*element) &&
                dc_dv_as(*element, string) != NULL)
                free(dc_dv_as(*element, string));
            break;
        }

        case DC_DYN_VAL_TYPE_voidptr:
        {
            if (custom_free)
                dc_try_fail_temp(DCResultVoid, custom_free(element));

            if (dc_dv_is_allocated(*element) &&
                dc_dv_as(*element, voidptr) != NULL)
                free(dc_dv_as(*element, voidptr));
            break;
        }

        // Do nothing for literal types (integer, float, etc.)
        default:
            break;
    }

    dc_res_ret();
}

DCResultVoid __dc_dv_free(voidptr dv)
{
    dc_res_void();

    if (!dv) dc_res_ret_e(1, "got NULL voidptr");

    return dc_dv_free((DCDynValue*)dv, NULL);
}

// Function to free the dynamic array
DCResultVoid dc_da_free(DCDynArr* darr)
{
    dc_res_void();

    if (!darr) dc_res_ret();

    for (usize i = 0; i < darr->count; ++i)
    {
        dc_try_fail_temp(DCResultVoid,
                         dc_dv_free(&darr->elements[i], darr->element_free_fn));
    }

    free(darr->elements);

    darr->elements = NULL;
    darr->cap = 0;
    darr->count = 0;

    dc_res_ret();
}

DCResultVoid __dc_da_free(voidptr darr)
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL voidptr");

    return dc_da_free((DCDynArr*)darr);
}

DCResultBool dc_da_delete(DCDynArr* darr, usize index)
{
    dc_res_bool();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    if (index >= darr->count)
    {
        dc_dbg_log("Index out of bound - try to get index='%" PRIuMAX
                   "' out of actual '%" PRIuMAX "' elements.",
                   index, darr->count);

        dc_res_ret_e(4, "Index out of bound");
    }

    // Free the element at the specified index
    dc_try_fail_temp(DCResultVoid,
                     dc_dv_free(&darr->elements[index], darr->element_free_fn));

    // Shift the elements after the deleted one to fill the gap
    memmove(&darr->elements[index], &darr->elements[index + 1],
            (darr->count - index - 1) * sizeof(DCDynValue));

    darr->count--;

    dc_res_ret_ok(true);
}

DCResultVoid dc_da_insert(DCDynArr* darr, usize index, DCDynValue value)
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    if (index > darr->count)
    {
        dc_dbg_log("Index out of bound - try to get index='%" PRIuMAX
                   "' out of actual '%" PRIuMAX "' elements.",
                   index, darr->count);

        dc_res_ret_e(4, "Index out of bound");
    }

    if (darr->count >= darr->cap)
        dc_try_fail_temp(DCResultVoid, dc_da_grow(darr));

    // No need to memmove if inserting at the end
    if (index < darr->count)
    {
        // Shift elements starting from index to index + 1
        memmove(&darr->elements[index + 1], &darr->elements[index],
                (darr->count - index) * sizeof(DCDynValue));
    }

    // Add the new value at the desired index
    darr->elements[index] = value;
    darr->count++;

    dc_res_ret();
}

DCResultVoid __dc_da_insert_values(DCDynArr* darr, usize start_index,
                                   usize count, DCDynValue values[])
{
    dc_res_void();

    if (!darr) dc_res_ret_e(1, "got NULL DCDynArr");

    if (start_index > darr->count)
    {
        dc_dbg_log("Index out of bound - try to get index='%" PRIuMAX
                   "' out of actual '%" PRIuMAX "' elements.",
                   start_index, darr->count);

        dc_res_ret_e(4, "Index out of bound");
    }

    if ((count + darr->count) > darr->cap)
        dc_try_fail_temp(DCResultVoid,
                         dc_da_grow_to(darr, count + darr->count));

    // No need to memmove if inserting at the end
    if (start_index < darr->count)
    {
        // Shift elements starting from index to index + 1
        memmove(&darr->elements[start_index + count],
                &darr->elements[start_index],
                (darr->count - start_index) * sizeof(DCDynValue));
    }

    for (usize i = 0; i < count; ++i)
    {
        darr->elements[start_index + i] = values[i];
    }

    darr->count += count;

    dc_res_ret();
}

DCResultVoid dc_da_insert_from(DCDynArr* darr, usize start_index,
                               DCDynArr* from)
{
    dc_res_void();

    if (!darr || !from) dc_res_ret_e(1, "got NULL DCDynArr");

    dc_try_fail(
        __dc_da_insert_values(darr, start_index, from->count, from->elements));

    dc_res_ret();
}

__dc_da_converters_decl(i8)
{
    __dc_da_converters_impl(i8);
}
__dc_da_converters_decl(i16)
{
    __dc_da_converters_impl(i16);
}
__dc_da_converters_decl(i32)
{
    __dc_da_converters_impl(i32);
}
__dc_da_converters_decl(i64)
{
    __dc_da_converters_impl(i64);
}
__dc_da_converters_decl(u8)
{
    __dc_da_converters_impl(u8);
}
__dc_da_converters_decl(u16)
{
    __dc_da_converters_impl(u16);
}
__dc_da_converters_decl(u32)
{
    __dc_da_converters_impl(u32);
}
__dc_da_converters_decl(u64)
{
    __dc_da_converters_impl(u64);
}
__dc_da_converters_decl(f32)
{
    __dc_da_converters_impl(f32);
}
__dc_da_converters_decl(f64)
{
    __dc_da_converters_impl(f64);
}
__dc_da_converters_decl(uptr)
{
    __dc_da_converters_impl(uptr);
}
__dc_da_converters_decl(char)
{
    __dc_da_converters_impl(char);
}
__dc_da_converters_decl(size)
{
    __dc_da_converters_impl(size);
}
__dc_da_converters_decl(usize)
{
    __dc_da_converters_impl(usize);
}
__dc_da_converters_decl(string)
{
    __dc_da_converters_impl(string);
}
__dc_da_converters_decl(voidptr)
{
    __dc_da_converters_impl(voidptr);
}
