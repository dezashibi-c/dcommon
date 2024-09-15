// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: _dynht.c
//    Date: 2024-09-15
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more
//     information about the licensing of this work. If you have any questions
//     or concerns, please feel free to contact me at the email address provided
//     above.
// ***************************************************************************************
// *  Description: private implementation file for definition of Hash Table
// *               Functionalities
// *               DO NOT LINK TO THIS DIRECTLY
// ***************************************************************************************

#ifndef __DC_BYPASS_PRIVATE_PROTECTION
#error                                                                         \
    "You cannot link to this source (_dynht.c) directly, please consider including dcommon.h"
#endif

#include "dcommon.h"

DCHashTable* dc_ht_create(usize capacity, DCHashFunc hash_func,
                          DCKeyCompFunc key_cmp_func,
                          DCDynValFreeFunc element_free_func)
{
    DCHashTable* ht = (DCHashTable*)malloc(sizeof(DCHashTable));

    ht->elements = (DCDynArr*)calloc(capacity, sizeof(DCDynArr));

    ht->cap = capacity;

    ht->hash_func = hash_func;
    ht->key_cmp_func = key_cmp_func;
    ht->element_free_func = element_free_func;

    return ht;
}

void dc_ht_free(DCHashTable* ht)
{
    for (usize i = 0; i < ht->cap; ++i)
    {
        dc_ht_get_element(darr, *ht, i);

        dc_dynarr_free(darr);
    }

    free(ht->elements);
    free(ht);
}

usize dc_ht_find_by_key(DCHashTable* ht, voidptr key, DCDynValue** out_result)
{
    dc_ht_get_hash(_index, *ht, key);

    dc_ht_get_element(darr, *ht, _index);

    dc_dynarr_for(*darr)
    {
        DCDynValue* element = &darr->elements[_idx];
        if (element->type != dc_value_type(voidptr))
        {
            fprintf(stderr, "Wrong type other than voidptr\n");
            exit(EXIT_FAILURE);
        }

        voidptr element_key = ((DCHashEntry*)element->value.voidptr_val)->key;
        if (ht->key_cmp_func(element_key, key))
        {
            *out_result = &((DCHashEntry*)element->value.voidptr_val)->value;
            return _idx;
        }
    }

    *out_result = NULL;
    return 0;
}

void dc_ht_set(DCHashTable* ht, voidptr key, DCDynValue value)
{
    dc_ht_get_hash(_index, *ht, key);

    DCHashEntry* new_entry = (DCHashEntry*)malloc(sizeof(DCHashEntry));
    if (new_entry == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_entry->key = key;
    new_entry->value = value;

    dc_ht_get_element(current, *ht, _index);

    if (current->cap == 0)
    {
        dc_dynarr_init(current, ht->element_free_func);
        dc_dynarr_push(current, dc_dynval_lit(voidptr, new_entry));

        return;
    }

    DCDynValue* existed = NULL;
    usize existed_index = dc_ht_find_by_key(ht, key, &existed);

    if (existed != NULL)
    {
        dc_dynval_free(&current->elements[existed_index],
                       ht->element_free_func);
        current->elements[existed_index] = dc_dynval_lit(voidptr, new_entry);

        return;
    }

    dc_dynarr_push(current, dc_dynval_lit(voidptr, new_entry));
}

bool dc_ht_delete(DCHashTable* ht, voidptr key)
{
    dc_ht_get_hash(_index, *ht, key);

    dc_ht_get_element(current, *ht, _index);

    if (current->count == 0) return false;

    DCDynValue* existed = NULL;
    usize existed_index = dc_ht_find_by_key(ht, key, &existed);

    if (existed == NULL) return false;

    dc_dynarr_delete(current, existed_index);

    return true;
}
