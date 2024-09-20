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

#define DC_DEBUG
#define DCOMMON_IMPL
#include "../src/dcommon/dcommon.h"

dc_ht_hash_func_decl(string_hash)
{
    string str = (string)_key;
    u32 hash = 5381;
    i32 c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

dc_ht_key_comp_func_decl(string_key_cmp)
{
    return strcmp((string)_key1, (string)_key2) == 0;
}

int main()
{
    dc_global_cleanups_init(10);
    dc_local_cleanup_decl(int, 0, 10);

    DCHashTable* table = dc_ht_create(10, string_hash, string_key_cmp, NULL);
    dc_dbg_log("hash table address: %p", (voidptr)table);
    dc_cleanups_push(table, dc_ht_free__);
    dc_cleanups_push(table, free);

    string key1 = "navid";
    dc_ht_set(table, key1, dc_dv(u8, 30));

    string key2 = "james";
    dc_ht_set(table, key2, dc_dv(u8, 40));

    string key3 = "bob";
    dc_ht_set(table, key3, dc_dv(u8, 50));

    DCDynValue* found = NULL;
    usize found_index = dc_ht_find_by_key(table, key1, &found);

    dc_action_on(table->key_count != 3, dc_return(1), "key_count must be 3");

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key1, dc_dv_as(*found, u8));
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
        printf("Found value for key '%s': %d\n", key2, dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key2);
    }

    dc_ht_delete(table, key2);

    dc_action_on(table->key_count != 2, dc_return(1), "key_count must be 2");

    found = NULL;
    found_index = dc_ht_find_by_key(table, key2, &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key2, dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key2);
    }

    dc_ht_set(table, key1, dc_dv(u8, 36));
    dc_ht_set(table, key2, dc_dv(u8, 100));

    dc_action_on(table->key_count != 3, dc_return(1), "key_count must be 3");

    found = NULL;
    found_index = dc_ht_find_by_key(table, key1, &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key1, dc_dv_as(*found, u8));
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
        printf("Found value for key '%s': %d\n", key2, dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key2);
    }

    dc_ht_set_multiple(table,

                       dc_ht_entry("robert", dc_dv(u8, 20)),
                       dc_ht_entry("albert", dc_dv(u8, 6)),
                       dc_ht_entry("boris", dc_dv(u8, 12)),
                       dc_ht_entry("navid", dc_dv(u8, 29))

    );

    found = NULL;
    found_index = dc_ht_find_by_key(table, key1, &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key1, dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key1);
    }

    found = NULL;
    found_index = dc_ht_find_by_key(table, "boris", &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", "boris", dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", "boris");
    }

    DCHashTable table2;
    dc_ht_init(&table2, 10, string_hash, string_key_cmp, NULL);
    dc_local_cleanups_push_ht(&table2);

    dc_ht_set_multiple(&table2,

                       {"maria", dc_dv(u8, 20)}, {"jesse", dc_dv(u8, 6)},
                       {"sophia", dc_dv(u8, 12)}, {"erisa", dc_dv(u8, 20)});

    dc_ht_merge(table, &table2);

    found = NULL;
    found_index = dc_ht_find_by_key(table, "erisa", &found);

    printf("Found index: %zu\n", found_index);

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", "erisa", dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", "erisa");
    }

    // get all keys
    voidptr* all_keys = NULL;
    usize len = dc_ht_keys(table, &all_keys);
    dc_dbg_log("all keys address: %p", (voidptr)all_keys);
    dc_cleanups_push(all_keys, free);

    printf("=========\n got %zu keys\n=========\n", len);
    dc_foreach(all_keys, voidptr)
    {
        printf("- %s\n", (string)(*_it));
    }

    dc_def_local_cleanups_label();
}
