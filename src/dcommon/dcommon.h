// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: dcommon.h
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
// *  Description: Main `dcommon` library entry point
// ***************************************************************************************

#ifndef DC_MAIN_HEADER_H
#define DC_MAIN_HEADER_H

#define __DC_BYPASS_PRIVATE_PROTECTION

#include "_headers/general.h"

#include "_headers/aliases.h"

#include "_headers/macros.h"

// ***************************************************************************************
// * FUNCTION DECLARATIONS
// ***************************************************************************************

DCResultI8 dc_str_to_i8(const string str);
DCResultI16 dc_str_to_i16(const string str);
DCResultI32 dc_str_to_i32(const string str);
DCResultI64 dc_str_to_i64(const string str);

DCResultU8 dc_str_to_u8(const string str);
DCResultU16 dc_str_to_u16(const string str);
DCResultU32 dc_str_to_u32(const string str);
DCResultU64 dc_str_to_u64(const string str);

DCResultF32 dc_str_to_f32(const string str);
DCResultF64 dc_str_to_f64(const string str);

DCResultBool dc_dv_as_bool(DCDynValue* dv);

DCResultVoid dc_da_init(DCDynArr* darr, DCDynValFreeFn element_free_fn);
DCResultVoid dc_da_init_custom(DCDynArr* darr, usize capacity,
                               usize capacity_grow_multiplier,
                               DCDynValFreeFn element_free_fn);
DCResultDa dc_da_new(DCDynValFreeFn element_free_fn);
DCResultDa dc_da_new_custom(usize capacity, usize capacity_grow_multiplier,
                            DCDynValFreeFn element_free_fn);
DCResultVoid __dc_da_init_with_values(DCDynArr* darr, usize count,
                                      DCDynValFreeFn element_free_fn,
                                      DCDynValue values[]);
DCResultVoid dc_da_grow(DCDynArr* darr);
DCResultVoid dc_da_grow_by(DCDynArr* darr, usize amount);
DCResultVoid dc_da_grow_to(DCDynArr* darr, usize amount);
DCResultVoid dc_da_trunc(DCDynArr* darr);
DCResultVoid dc_da_pop(DCDynArr* darr, usize count, DCDynValue** out_popped,
                       bool truncate);
DCResultVoid dc_da_push(DCDynArr* darr, DCDynValue value);
DCResultVoid __dc_da_append_values(DCDynArr* darr, usize count,
                                   DCDynValue values[]);
DCResultVoid dc_da_append(DCDynArr* darr, DCDynArr* from);
DCResultDv dc_da_get(DCDynArr* darr, usize index);
DCResultBool dc_dv_eq(DCDynValue* dv1, DCDynValue* dv2);
DCResultDv dc_da_find(DCDynArr* darr, DCDynValue* el);
DCResultVoid dc_dv_free(DCDynValue* element, DCDynValFreeFn custom_free);
DCResultVoid __dc_dv_free(voidptr dv);
DCResultVoid dc_da_free(DCDynArr* darr);
DCResultVoid __dc_da_free(voidptr darr);
DCResultBool dc_da_delete(DCDynArr* darr, usize index);
DCResultVoid dc_da_insert(DCDynArr* darr, usize index, DCDynValue value);
DCResultVoid __dc_da_insert_values(DCDynArr* darr, usize start_index,
                                   usize count, DCDynValue values[]);
DCResultVoid dc_da_insert_from(DCDynArr* darr, usize start_index,
                               DCDynArr* from);

__dc_da_converters_decl(i8);
__dc_da_converters_decl(i16);
__dc_da_converters_decl(i32);
__dc_da_converters_decl(i64);

__dc_da_converters_decl(u8);
__dc_da_converters_decl(u16);
__dc_da_converters_decl(u32);
__dc_da_converters_decl(u64);

__dc_da_converters_decl(f32);
__dc_da_converters_decl(f64);

__dc_da_converters_decl(uptr);
__dc_da_converters_decl(char);
__dc_da_converters_decl(size);
__dc_da_converters_decl(usize);
__dc_da_converters_decl(string);
__dc_da_converters_decl(voidptr);

DCResultVoid dc_ht_init(DCHashTable* ht, usize capacity, DCHashFn hash_fn,
                        DCKeyCompFn key_cmp_fn, DCDynValFreeFn element_free_fn);
DCResultHt dc_ht_new(usize capacity, DCHashFn hash_fn, DCKeyCompFn key_cmp_fn,
                     DCDynValFreeFn element_free_fn);
DCResultVoid dc_ht_free(DCHashTable* ht);
DCResultVoid __dc_ht_free(voidptr ht);
DCResultUsize dc_ht_find_by_key(DCHashTable* ht, voidptr key,
                                DCDynValue** out_result);
DCResultVoid dc_ht_set(DCHashTable* ht, voidptr key, DCDynValue value);
DCResultVoid __dc_ht_set_multiple(DCHashTable* ht, usize count,
                                  DCHashEntry entries[]);
DCResultVoid dc_ht_merge(DCHashTable* ht, DCHashTable* from);
DCResultBool dc_ht_delete(DCHashTable* ht, voidptr key);
DCResultUsize dc_ht_keys(DCHashTable* ht, voidptr** out_arr);

DCResultSv dc_sv_create(string base, usize start, usize length);
DCResultString dc_sv_as_cstr(DCStringView* sv);
DCResultVoid dc_sv_free(DCStringView* sv);

DCResultUsize dc_sprintf(string* str, string fmt, ...)
    __dc_attribute((format(printf, 2, 3)));
DCResultUsize dc_sappend(string* str, const string fmt, ...)
    __dc_attribute((format(printf, 2, 3)));
DCResultString dc_strdup(const string in);
DCResultVoid dc_normalize_path_to_posix(string path);
DCResultString dc_replace_file_in_path(const string path,
                                       const string file_name);
string dc_get_home_dir_path();
string dc_get_username();
string dc_get_os();
string dc_get_arch();

void __dc_handle_signal(int sig);
DCResultVoid __dc_perform_cleanup(DCCleanups* cleanups_arr);
DCResultVoid dc_perform_cleanup(void);
DCResultVoid __dc_cleanups_custom_push(DCCleanups* cleanup_arr, voidptr element,
                                       DCCleanupFn cleanup_fn);
DCResultVoid dc_free(voidptr variable);

DCResultVoid dc_result_free(voidptr res_ptr);

// ***************************************************************************************
// * IMPLEMENTATIONS
// ***************************************************************************************

#ifdef DCOMMON_IMPL

FILE* dc_error_logs = NULL;
DCHaltMode dc_error_mode = DC_HALT_MODE_CONTINUE;
DCCleanups dc_cleanups = {0};
DCResultVoid dc_cleanups_res;

#include "_dynarr.c"
#include "_dynht.c"
#include "_lit_val.c"
#include "_string_view.c"
#include "_utils.c"

#else

extern FILE* dc_error_logs;
extern DCHaltMode dc_error_mode;
extern DCCleanups dc_cleanups;
extern DCResultVoid dc_cleanups_res;

#endif

#endif // DC_MAIN_HEADER_H
