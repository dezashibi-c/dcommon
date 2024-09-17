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

u32 string_hash(voidptr key)
{
    string str = (string)key;
    u32 hash = 5381;
    i32 c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

bool string_key_cmp(voidptr key1, voidptr key2)
{
    return strcmp((string)key1, (string)key2) == 0;
}

int main()
{
    DCHashTable table;
    dc_ht_init(&table, 10, string_hash, string_key_cmp, NULL);

    string key1 = "navid";
    dc_ht_set(&table, key1, dc_dynval_lit(u8, 30));

    string key2 = "james";
    dc_ht_set(&table, key2, dc_dynval_lit(u8, 40));

    string key3 = "bob";
    dc_ht_set(&table, key3, dc_dynval_lit(u8, 50));

    DCDynValue* found = NULL;
    usize found_index = dc_ht_find_by_key(&table, key1, &found);

    assert(table.key_count == 3);

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
    found_index = dc_ht_find_by_key(&table, key2, &found);

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

    dc_ht_delete(&table, key2);

    assert(table.key_count == 2);

    found = NULL;
    found_index = dc_ht_find_by_key(&table, key2, &found);

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

    dc_ht_set(&table, key1, dc_dynval_lit(u8, 36));
    dc_ht_set(&table, key2, dc_dynval_lit(u8, 100));

    assert(table.key_count == 3);

    found = NULL;
    found_index = dc_ht_find_by_key(&table, key1, &found);

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
    found_index = dc_ht_find_by_key(&table, key2, &found);

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

    dc_ht_set_multiple(&table,

                       dc_ht_entry("robert", dc_dynval_lit(u8, 20)),
                       dc_ht_entry("albert", dc_dynval_lit(u8, 6)),
                       dc_ht_entry("boris", dc_dynval_lit(u8, 12)),
                       dc_ht_entry("navid", dc_dynval_lit(u8, 29))

    );

    found = NULL;
    found_index = dc_ht_find_by_key(&table, key1, &found);

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
    found_index = dc_ht_find_by_key(&table, "boris", &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", "boris",
               dc_dynval_get(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", "boris");
    }

    DCHashTable table2;
    dc_ht_init(&table2, 10, string_hash, string_key_cmp, NULL);

    dc_ht_set_multiple(&table2,

                       dc_ht_entry("maria", dc_dynval_lit(u8, 20)),
                       dc_ht_entry("jesse", dc_dynval_lit(u8, 6)),
                       dc_ht_entry("sophia", dc_dynval_lit(u8, 12)),
                       dc_ht_entry("erisa", dc_dynval_lit(u8, 20))

    );

    dc_ht_merge(&table, &table2);

    found = NULL;
    found_index = dc_ht_find_by_key(&table, "erisa", &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", "erisa",
               dc_dynval_get(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", "erisa");
    }

    // get all keys
    voidptr* all_keys = NULL;
    usize len = dc_ht_keys(&table, &all_keys);

    printf("=========\n got %zu elements\n=========\n", len);

    for (usize i = 0; i < len; ++i)
    {
        printf("key #%zu -> %s\n", i, (string)all_keys[i]);
    }

    // Don't forget to free all_keys!
    free(all_keys);

    // and the hash table
    dc_ht_free(&table);
    dc_ht_free(&table2);
}
