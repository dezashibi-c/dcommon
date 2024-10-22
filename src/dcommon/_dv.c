// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: _dv.c
//    Date: 2024-10-20
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
#error "You cannot link to this source (_dv.c) directly, please consider including dcommon.h"
#endif

#include "_headers/aliases.h"
#include "_headers/general.h"
#include "_headers/macros.h"

void dc_dv_set_value(DCDynVal* dv, DCDynValType type, const voidptr src, size_t size, size_t total_count, size_t start,
                     size_t count, bool allocated)
{
    if (size > DC_DV_DATA_SIZE)
    {
        dc_dbg_log("Error: Not enough space for dynamic value, need='" dc_fmt(usize) "', got='" dc_fmt(u16) "'\n", size,
                   DC_DV_DATA_SIZE);
        exit(dc_e_code(MEM));
    }

    if (src) memcpy(dv->value, src, size);

    dv->type = type;
    dv->size = size;
    dv->start = start;
    dv->count = count;
    dv->total_count = total_count;
    dv->allocated = allocated;
}

DCDynVal dc_dv_create(DCDynValType type, const voidptr src, size_t size, size_t total_count, size_t start, size_t count,
                      bool allocated)
{
    DCDynVal new_dv = {0};
    dc_dv_set_value(&new_dv, type, src, size, total_count, start, count, allocated);
    return new_dv;
}

string dc_dv_fmt(DCDynVal* dv)
{
    if (!dv) return "";

#define dv_fmt_case(TYPE)                                                                                                      \
    case dc_dvt(TYPE):                                                                                                         \
        return dc_fmt(TYPE)

    switch (dv->type)
    {
        dv_fmt_case(u8);
        dv_fmt_case(u16);
        dv_fmt_case(u32);
        dv_fmt_case(u64);
        dv_fmt_case(i8);
        dv_fmt_case(i16);
        dv_fmt_case(i32);
        dv_fmt_case(i64);
        dv_fmt_case(f32);
        dv_fmt_case(f64);
        dv_fmt_case(uptr);
        dv_fmt_case(char);

        dv_fmt_case(voidptr);
        dv_fmt_case(fileptr);
        dv_fmt_case(size);
        dv_fmt_case(usize);

        case dc_dvt(string):
            return DCPRIstr_slice;

        default:
            return dc_fmt(string);
    };
#undef dv_fmt_case
}

string dc_tostr_dvt(DCDynVal* dv)
{
    if (!dv) return "(null dynamic value)";

#define dvt_case(TYPE)                                                                                                         \
    case dc_dvt(TYPE):                                                                                                         \
        return #TYPE

    switch (dv->type)
    {
        dvt_case(u8);
        dvt_case(u16);
        dvt_case(u32);
        dvt_case(u64);
        dvt_case(i8);
        dvt_case(i16);
        dvt_case(i32);
        dvt_case(i64);
        dvt_case(f32);
        dvt_case(f64);
        dvt_case(uptr);
        dvt_case(char);
        dvt_case(string);
        dvt_case(voidptr);
        dvt_case(fileptr);
        dvt_case(size);
        dvt_case(usize);

        dvt_case(DCPair_ptr);
        dvt_case(DCDynVal_ptr);

        default:
            return "unknown or unimplemented";
    };

#undef dvt_case
}

DCResString dc_tostr_dv(DCDynVal* dv)
{
    DC_RES_string();

    if (!dv) dc_ret_e(1, "got NULL dynamic value");

    if (dc_dv_is(*dv, string))
    {
        string result = NULL;
        dc_sprintf(&result, DCPRIstr_slice, dc_dv_str_fmt(*dv));
        dc_ret_ok(result);
    }

#define stringify(TYPE)                                                                                                        \
    case dc_dvt(TYPE):                                                                                                         \
        dc_sappend(&result, dc_fmt(TYPE), dc_dv_offset_as(*dv, TYPE, _idx));                                                   \
        break

#define stringify_ptr(TYPE)                                                                                                    \
    case dc_dvt(TYPE):                                                                                                         \
        dc_sappend(&result, "(%s)", #TYPE);                                                                                    \
        break

    string result = NULL;

    for (usize _idx = 0; _idx < dv->count; ++_idx)
    {
        switch (dv->type)
        {
            stringify(u8);
            stringify(u16);
            stringify(u32);
            stringify(u64);
            stringify(i8);
            stringify(i16);
            stringify(i32);
            stringify(i64);
            stringify(f32);
            stringify(f64);
            stringify(uptr);
            stringify(char);
            stringify_ptr(voidptr);
            stringify_ptr(fileptr);
            stringify(size);
            stringify(usize);

            default:
                dc_sappend(&result, "(%s)", dc_tostr_dvt(dv));
                break;
        };

        if (_idx < dv->count - 1) dc_sappend(&result, "%s", ", ");
    }

    dc_ret_ok(result);

#undef stringify
#undef stringify_ptr
}

DCResVoid dc_dv_print(DCDynVal* dv)
{
    DC_RES_void();

    dc_try_or_fail_with3(DCResString, res, dc_tostr_dv(dv), {});

    printf("%s", dc_unwrap2(res));

    if (dc_unwrap2(res)) free(dc_unwrap2(res));

    dc_ret();
}

DCResVoid dc_dv_println(DCDynVal* dv)
{
    DC_TRY_DEF2(DCResVoid, dc_dv_print(dv));

    printf("%s", "\n");

    dc_ret();
}

DCResBool dc_dv_as_bool(DCDynVal* dv)
{
    DC_RES_bool();

    // NULL DCDynVal is going to turn into false value
    if (!dv) dc_ret_ok(false);

    if (dv->total_count == 0 || dv->count == 0) dc_ret_ok(false);

    if (dv->total_count != dv->count) dc_ret_ok(true);

#define type_to_bool(TYPE)                                                                                                     \
    case dc_dvt(TYPE):                                                                                                         \
        dc_ret_ok(dc_as_bool(TYPE, dc_dv_as(*dv, TYPE)));

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
        type_to_bool(voidptr);
        type_to_bool(fileptr);
        type_to_bool(size);
        type_to_bool(usize);

        case dc_dvt(string):
            dc_ret_ok(dc_as_bool(string, dc_dv_as_string(*dv)));

        default:
            break;
    };

    dc_dbg_log("Exiting Function on an unknown type");
    dc_ret_e(3, "unknown dynamic value type");
#undef type_to_bool
}

DCResBool dc_dv_eq(DCDynVal* dv1, DCDynVal* dv2)
{
    DC_RES_bool();

    if (!dv1 || !dv2)
    {
        dc_dbg_log("cannot compare DCDynVal with NULL");

        dc_ret_e(1, "cannot compare DCDynVal with NULL");
    }

    if (dv1->type != dv2->type || dv1->size != dv2->size || dv1->start != dv2->start || dv1->count != dv2->count ||
        dv1->total_count != dv2->total_count)
        dc_ret_ok(false);

    dc_ret_ok(memcmp(dv1->value, dv2->value, dv1->size) == 0);
}

DCResBool dc_dv_eq2(DCDynVal* dv1, DCDynVal dv2)
{
    return dc_dv_eq(dv1, &dv2);
}

DCResBool dc_dv_eq3(DCDynVal dv1, DCDynVal dv2)
{
    return dc_dv_eq(&dv1, &dv2);
}
