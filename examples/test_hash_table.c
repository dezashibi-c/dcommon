// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: test_hash_table.h
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
// *  Description:
// ***************************************************************************************

#define DCOMMON_IMPL
#include "../src/dcommon/dcommon.h"

u32 string_hash(void* key)
{
    string str = (string)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

bool string_key_cmp(void* key1, void* key2)
{
    return strcmp((string)key1, (string)key2) == 0;
}

int main()
{
    DCHashTable* table = dc_ht_create(10, string_hash, string_key_cmp, NULL);

    string key1 = "navid";
    dc_ht_set(table, key1, dc_dynval_lit(u8, 30));

    string key2 = "james";
    dc_ht_set(table, key2, dc_dynval_lit(u8, 40));

    string key3 = "bob";
    dc_ht_set(table, key3, dc_dynval_lit(u8, 50));

    DCDynValue* found = NULL;
    usize found_index = dc_ht_find_by_key(table, key1, &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key1,
               dc_dynval_get(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key1);
    }

    found = NULL;
    found_index = dc_ht_find_by_key(table, key2, &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key2,
               dc_dynval_get(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key2);
    }

    dc_ht_delete(table, key2);

    found = NULL;
    found_index = dc_ht_find_by_key(table, key2, &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key2,
               dc_dynval_get(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key2);
    }

    dc_ht_set(table, key1, dc_dynval_lit(u8, 36));
    dc_ht_set(table, key2, dc_dynval_lit(u8, 100));

    found = NULL;
    found_index = dc_ht_find_by_key(table, key1, &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key1,
               dc_dynval_get(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key1);
    }

    found = NULL;
    found_index = dc_ht_find_by_key(table, key2, &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key2,
               dc_dynval_get(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key2);
    }

    dc_ht_free(table);
}
