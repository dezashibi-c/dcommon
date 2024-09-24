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

dc_ht_hash_fn_decl(string_hash)
{
    dc_res_u32();

    string str = (string)_key;
    u32 hash = 5381;
    i32 c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    dc_res_ret_ok(hash);
}

dc_ht_key_comp_fn_decl(string_key_cmp)
{
    dc_res_bool();

    dc_res_ret_ok(strcmp((string)_key1, (string)_key2) == 0);
}

int main()
{
    dc_global_cleanups_init(10);
    dc_ret_val_decl(u8, 0);

    DCResultHt table_res = dc_ht_new(10, string_hash, string_key_cmp, NULL);
    dc_action_on(dc_res_is_err2(table_res),
                 dc_return(dc_res_err_code2(table_res)), "%s",
                 dc_res_err_msg2(table_res));

    dc_cleanups_push_res(&table_res);

    dc_action_on(dc_res_is_err2(dc_cleanups_res),
                 dc_return(dc_res_err_code2(dc_cleanups_res)), "%s",
                 dc_res_err_msg2(dc_cleanups_res));

    DCHashTable* table = dc_res_val2(table_res);

    dc_dbg_log("hash table address: %p", (voidptr)table);

    // we don't this as we have a shortcut for it
    // dc_cleanups_push(table, __dc_ht_free);
    dc_cleanups_push_ht(table);

    dc_action_on(dc_res_is_err2(dc_cleanups_res),
                 dc_return(dc_res_err_code2(dc_cleanups_res)), "%s",
                 dc_res_err_msg2(dc_cleanups_res));

    // we also need this as after we cleaned the hash table we need to free
    // local allocated hash table
    dc_cleanups_push_free(table);

    dc_action_on(dc_res_is_err2(dc_cleanups_res),
                 dc_return(dc_res_err_code2(dc_cleanups_res)), "%s",
                 dc_res_err_msg2(dc_cleanups_res));

    string key1 = "navid";
    dc_ht_set(table, key1, dc_dv(u8, 30));

    string key2 = "james";
    dc_ht_set(table, key2, dc_dv(u8, 40));

    string key3 = "bob";
    dc_ht_set(table, key3, dc_dv(u8, 50));

    DCDynValue* found = NULL;
    DCResultUsize usize_res = dc_ht_find_by_key(table, key1, &found);

    dc_action_on(dc_res_is_err2(usize_res),
                 dc_return(dc_res_err_code2(usize_res)), "%s",
                 dc_res_err_msg2(usize_res));

    dc_cleanups_push_res(&usize_res);

    dc_action_on(dc_res_is_err2(dc_cleanups_res),
                 dc_return(dc_res_err_code2(dc_cleanups_res)), "%s",
                 dc_res_err_msg2(dc_cleanups_res));

    dc_action_on(table->key_count != 3, dc_return(1), "key_count must be 3");

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key1, dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key1);
    }

    found = NULL;
    usize_res = dc_ht_find_by_key(table, key2, &found);

    dc_action_on(dc_res_is_err2(usize_res),
                 dc_return(dc_res_err_code2(usize_res)), "%s",
                 dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key2, dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key2);
    }

    DCResultBool del_res = dc_ht_delete(table, key2);
    dc_action_on(dc_res_is_err2(del_res), dc_return(dc_res_err_code2(del_res)),
                 "%s", dc_res_err_msg2(del_res));

    dc_cleanups_push_res(&del_res);

    dc_action_on(dc_res_is_err2(dc_cleanups_res),
                 dc_return(dc_res_err_code2(dc_cleanups_res)), "%s",
                 dc_res_err_msg2(dc_cleanups_res));

    dc_action_on(table->key_count != 2, dc_return(1), "key_count must be 2");

    found = NULL;
    usize_res = dc_ht_find_by_key(table, key2, &found);

    dc_action_on(dc_res_is_err2(usize_res),
                 dc_return(dc_res_err_code2(usize_res)), "%s",
                 dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key2, dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key2);
    }

    DCResultVoid void_res = dc_ht_set(table, key1, dc_dv(u8, 36));
    dc_action_on(dc_res_is_err2(void_res),
                 dc_return(dc_res_err_code2(void_res)), "%s",
                 dc_res_err_msg2(void_res));

    void_res = dc_ht_set(table, key2, dc_dv(u8, 100));
    dc_action_on(dc_res_is_err2(void_res),
                 dc_return(dc_res_err_code2(void_res)), "%s",
                 dc_res_err_msg2(void_res));

    dc_action_on(table->key_count != 3, dc_return(1), "key_count must be 3");

    found = NULL;
    usize_res = dc_ht_find_by_key(table, key1, &found);
    dc_action_on(dc_res_is_err2(usize_res),
                 dc_return(dc_res_err_code2(usize_res)), "%s",
                 dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key1, dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key1);
    }

    found = NULL;
    usize_res = dc_ht_find_by_key(table, key2, &found);
    dc_action_on(dc_res_is_err2(usize_res),
                 dc_return(dc_res_err_code2(usize_res)), "%s",
                 dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key2, dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key2);
    }

    dc_try_ht_set_multiple(void_res, table,

                           dc_ht_entry("robert", dc_dv(u8, 20)),
                           dc_ht_entry("albert", dc_dv(u8, 6)),
                           dc_ht_entry("boris", dc_dv(u8, 12)),
                           dc_ht_entry("navid", dc_dv(u8, 29))

    );
    dc_action_on(dc_res_is_err2(void_res),
                 dc_return(dc_res_err_code2(void_res)), "%s",
                 dc_res_err_msg2(void_res));

    found = NULL;
    usize_res = dc_ht_find_by_key(table, key1, &found);
    dc_action_on(dc_res_is_err2(usize_res),
                 dc_return(dc_res_err_code2(usize_res)), "%s",
                 dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", key1, dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", key1);
    }

    found = NULL;
    usize_res = dc_ht_find_by_key(table, "boris", &found);
    dc_action_on(dc_res_is_err2(usize_res),
                 dc_return(dc_res_err_code2(usize_res)), "%s",
                 dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", "boris", dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", "boris");
    }

    DCHashTable table2;
    void_res = dc_ht_init(&table2, 10, string_hash, string_key_cmp, NULL);

    dc_action_on(dc_res_is_err2(void_res),
                 dc_return(dc_res_err_code2(void_res)), "%s",
                 dc_res_err_msg2(void_res));

    dc_cleanups_push_ht(&table2);

    dc_try_ht_set_multiple(void_res, &table2,

                           {"maria", dc_dv(u8, 20)}, {"jesse", dc_dv(u8, 6)},
                           {"sophia", dc_dv(u8, 12)}, {"erisa", dc_dv(u8, 20)});

    dc_action_on(dc_res_is_err2(void_res),
                 dc_return(dc_res_err_code2(void_res)), "%s",
                 dc_res_err_msg2(void_res));

    void_res = dc_ht_merge(table, &table2);
    dc_action_on(dc_res_is_err2(void_res),
                 dc_return(dc_res_err_code2(void_res)), "%s",
                 dc_res_err_msg2(void_res));

    found = NULL;
    usize_res = dc_ht_find_by_key(table, "erisa", &found);
    dc_action_on(dc_res_is_err2(usize_res),
                 dc_return(dc_res_err_code2(usize_res)), "%s",
                 dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

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
    usize_res = dc_ht_keys(table, &all_keys);
    dc_action_on(dc_res_is_err2(usize_res),
                 dc_return(dc_res_err_code2(usize_res)), "%s",
                 dc_res_err_msg2(usize_res));

    dc_dbg_log("all keys address: %p", (voidptr)all_keys);
    dc_cleanups_push_free(all_keys);

    printf("=========\n got '%" PRIuMAX "' keys\n=========\n",
           dc_res_val2(usize_res));
    dc_foreach(all_keys, voidptr)
    {
        printf("- %s\n", (string)(*_it));
    }

    dc_def_exit_label();
}
