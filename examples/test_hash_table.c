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

DC_HT_HASH_FN_DECL(string_hash)
{
    DC_RES_u32();

    if (_key->type != dc_dvt(string)) dc_res_ret_e(dc_err(TYPE), dc_err_msg(TYPE));

    string str = dc_dv_as(*_key, string);
    u32 hash = 5381;
    i32 c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    dc_res_ret_ok(hash);
}

DC_HT_KEY_CMP_FN_DECL(string_key_cmp)
{
    return dc_dv_eq(_key1, _key2);
}

/**
 * This simple enums is to have constant for numbers 0 and 1 so that we can
 * write something meaningful when we're dealing with cleanup batches throughout
 * our program
 *
 * Although all the unversioned versions of cleanup functions are dealing with
 * index 0 automatically but I would prefer to use version 2 whenever I have
 * more than one batch
 */
enum
{
    MAIN_MEMORY_BATCH,
    TEMP_MEMORY_BATCH,
};

DCResVoid testing_hash_table_merge(DCHashTable* source)
{
    DC_RES_void();

    // First things first
    // source must not be NULL
    if (source == NULL)
    {
        dc_res_e(1, "source cannot be NULL");

        dc_return();
    }

    DCHashTable table2;
    DCResVoid void_res = dc_ht_init(&table2, 10, string_hash, string_key_cmp, NULL);

    // Pushing the result to the batch index TEMP_MEMORY_BATCH=1
    // We want to use it before taking any action on result as if it contains
    // any allocated strings they're going to be cleaned up
    dc_cleanup_pool_push(TEMP_MEMORY_BATCH, &void_res, dc_res_free);

    // Using combinations of dc_action_on and result macros (version 2s) can
    // make lots of code quite shorter but easy to follow, read and understand
    // and even debug
    dc_action_on(dc_res_is_err2(void_res), dc_return_with_val(void_res), "%s", dc_res_err_msg2(void_res));

    // We've passed the result test so we're sure table2 is initiated
    // Time to push it for cleanup in TEMP_MEMORY_BATCH
    dc_cleanup_push_ht2(TEMP_MEMORY_BATCH, &table2);

    // Initializing hash table with key/value pairs
    // Trying to do it in fact and save the result in void_res
    // It's really ok and even advised that we should reuse results as much as
    // we can
    dc_try_ht_set_multiple(void_res, &table2,

                           {dc_dv(string, "maria"), dc_dv(u8, 20)}, {dc_dv(string, "jesse"), dc_dv(u8, 6)},
                           {dc_dv(string, "sophia"), dc_dv(u8, 12)}, {dc_dv(string, "erisa"), dc_dv(u8, 20)});

    // Checking the result and take proper action
    dc_action_on(dc_res_is_err2(void_res), dc_return_with_val(void_res), "%s", dc_res_err_msg2(void_res));

    // Now trying to merge the table2 into given hash table
    void_res = dc_ht_merge(source, &table2);
    dc_action_on(dc_res_is_err2(void_res), dc_return_with_val(void_res), "%s", dc_res_err_msg2(void_res));

    // Initiating exit section that cleans up the memory batch index
    // TEMP_MEMORY_BATCH=1 only and returns current value of the __dc_res
    DC_EXIT_SECTION(TEMP_MEMORY_BATCH);
}

int main()
{
    // Initializing error logs to default file name _error_logs.log
    // Also errors won't be appended and the log file will be reset
    // at each run
    dc_error_logs_init(NULL, false);

    // Initialize the global pool with 2 batches and each batches 10 spot for
    // holding allocated memory addresses
    dc_cleanup_pool_init2(2, 10);

    // This is the main function so __dc_res must be a number, u8 can do the job
    // and 0 as we assume proccess is going ok until it won't
    DC_RET_VAL_INIT(u8, 0);

    // Trying to initiate and then checking for the result and jumping to exit
    // with error value if that's the case
    DCResHt table_res = dc_ht_new(10, string_hash, string_key_cmp, NULL);
    dc_action_on(dc_res_is_err2(table_res), dc_return_with_val(dc_res_err_code2(table_res)), "%s", dc_res_err_msg2(table_res));

    // We could use dc_cleanup_push_res to push automatically to the default
    // batch which is index 0
    // I've used this only for demonstration purposes which by the way is
    // totally fine and even more readable in this context to be honest
    dc_cleanup_push_res2(MAIN_MEMORY_BATCH, &table_res);


    DCHashTable* table = dc_res_val2(table_res);

    dc_dbg_log("hash table address: %p", (voidptr)table);

    // we don't this as we have a shortcut for it
    // dc_cleanup_default_pool_push(table, __dc_ht_free);
    // dc_cleanup_push_ht pushes to index 0 which is the default batch
    // dc_cleanup_push_ht2 can be used to push into any batches including
    // index 0
    dc_cleanup_push_ht(table);


    // we also need this as after we cleaned the hash table we need to free
    // local allocated hash table
    dc_cleanup_push_free(table);


    DCDynVal key1 = dc_dv(string, "navid");
    dc_ht_set(table, key1, dc_dv(u8, 30));

    DCDynVal key2 = dc_dv(string, "james");
    dc_ht_set(table, key2, dc_dv(u8, 40));

    DCDynVal key3 = dc_dv(string, "bob");
    dc_ht_set(table, key3, dc_dv(u8, 50));

    DCDynVal* found = NULL;
    DCResUsize usize_res = dc_ht_find_by_key(table, key1, &found);

    dc_action_on(dc_res_is_err2(usize_res), dc_return_with_val(dc_res_err_code2(usize_res)), "%s", dc_res_err_msg2(usize_res));

    dc_cleanup_push_res(&usize_res);


    dc_action_on(table->key_count != 3, dc_return_with_val(1), "key_count must be 3");

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", dc_dv_as(key1, string), dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", dc_dv_as(key1, string));
    }

    found = NULL;
    usize_res = dc_ht_find_by_key(table, key2, &found);

    dc_action_on(dc_res_is_err2(usize_res), dc_return_with_val(dc_res_err_code2(usize_res)), "%s", dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", dc_dv_as(key2, string), dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", dc_dv_as(key2, string));
    }

    DCResBool del_res = dc_ht_delete(table, key2);
    dc_action_on(dc_res_is_err2(del_res), dc_return_with_val(dc_res_err_code2(del_res)), "%s", dc_res_err_msg2(del_res));

    dc_cleanup_push_res(&del_res);


    dc_action_on(table->key_count != 2, dc_return_with_val(1), "key_count must be 2");

    found = NULL;
    usize_res = dc_ht_find_by_key(table, key2, &found);

    dc_action_on(dc_res_is_err2(usize_res), dc_return_with_val(dc_res_err_code2(usize_res)), "%s", dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", dc_dv_as(key2, string), dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", dc_dv_as(key2, string));
    }

    DCResVoid void_res = dc_ht_set(table, key1, dc_dv(u8, 36));
    dc_action_on(dc_res_is_err2(void_res), dc_return_with_val(dc_res_err_code2(void_res)), "%s", dc_res_err_msg2(void_res));

    void_res = dc_ht_set(table, key2, dc_dv(u8, 100));
    dc_action_on(dc_res_is_err2(void_res), dc_return_with_val(dc_res_err_code2(void_res)), "%s", dc_res_err_msg2(void_res));

    dc_action_on(table->key_count != 3, dc_return_with_val(1), "key_count must be 3");

    found = NULL;
    usize_res = dc_ht_find_by_key(table, key1, &found);
    dc_action_on(dc_res_is_err2(usize_res), dc_return_with_val(dc_res_err_code2(usize_res)), "%s", dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", dc_dv_as(key1, string), dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", dc_dv_as(key1, string));
    }

    found = NULL;
    usize_res = dc_ht_find_by_key(table, key2, &found);
    dc_action_on(dc_res_is_err2(usize_res), dc_return_with_val(dc_res_err_code2(usize_res)), "%s", dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", dc_dv_as(key2, string), dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", dc_dv_as(key2, string));
    }

    dc_try_ht_set_multiple(void_res, table,

                           dc_ht_entry(string, "robert", u8, 20), dc_ht_entry(string, "albert", u8, 6),
                           dc_ht_entry(string, "boris", u8, 12), dc_ht_entry(string, "navid", u8, 29)

    );
    dc_action_on(dc_res_is_err2(void_res), dc_return_with_val(dc_res_err_code2(void_res)), "%s", dc_res_err_msg2(void_res));

    found = NULL;
    usize_res = dc_ht_find_by_key(table, key1, &found);
    dc_action_on(dc_res_is_err2(usize_res), dc_return_with_val(dc_res_err_code2(usize_res)), "%s", dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", dc_dv_as(key1, string), dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", dc_dv_as(key1, string));
    }

    found = NULL;
    usize_res = dc_ht_find_by_key(table, dc_dv(string, "boris"), &found);
    dc_action_on(dc_res_is_err2(usize_res), dc_return_with_val(dc_res_err_code2(usize_res)), "%s", dc_res_err_msg2(usize_res));

    printf("Found index: '%" PRIuMAX "'\n", dc_res_val2(usize_res));

    if (found != NULL)
    {
        printf("Found value for key '%s': %d\n", "boris", dc_dv_as(*found, u8));
    }
    else
    {
        printf("Key '%s' not found\n", "boris");
    }

    // **************************************************************
    // Calling another function that uses another cleanup batch
    // **************************************************************
    dc_log("Calling another function that uses another cleanup batch");
    void_res = testing_hash_table_merge(table);
    dc_action_on(dc_res_is_err2(void_res), dc_return_with_val(dc_res_err_code2(void_res)), "%s", dc_res_err_msg2(void_res));

    dc_log("Returned another function that uses another cleanup batch");
    // **************************************************************
    // Returning back to the main function
    // **************************************************************

    found = NULL;
    usize_res = dc_ht_find_by_key(table, dc_dv(string, "erisa"), &found);
    dc_action_on(dc_res_is_err2(usize_res), dc_return_with_val(dc_res_err_code2(usize_res)), "%s", dc_res_err_msg2(usize_res));

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
    DCDynVal* all_keys = NULL;
    usize_res = dc_ht_keys(table, &all_keys);
    dc_action_on(dc_res_is_err2(usize_res), dc_return_with_val(dc_res_err_code2(usize_res)), "%s", dc_res_err_msg2(usize_res));

    dc_dbg_log("all keys address: %p", (voidptr)all_keys);
    // Registering the all_keys to the batch index 0 with the general free
    // function
    dc_cleanup_push_free(all_keys);

    printf("=========\n got '%" PRIuMAX "' keys\n=========\n", dc_res_val2(usize_res));
    dc_foreach(all_keys, DCDynVal, printf("- %s\n", dc_dv_as((*_it), string)));

    // Create an exit section label with final cleanup trigger
    // We could set the cleanup to MAIN_MEMORY_BATCH and that was totally fine
    // as we've already cleaned that up but using -1 meaning to cleanup all the
    // batches is fine too if a batch is cleaned up it won't be tried again
    DC_EXIT_SECTION(DC_CLEANUP_POOL);
}
