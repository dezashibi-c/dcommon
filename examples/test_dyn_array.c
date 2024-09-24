// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: test_dyn_array.h
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
// *  Description:
// ***************************************************************************************

#define DCOMMON_IMPL
#include "../src/dcommon/dcommon.h"

void print_dv(DCDynValue* dval)
{
    if (dc_dv_is(*dval, u8))
    {
        printf("u8: %u\n", dc_dv_as(*dval, u8));
    }
    else if (dc_dv_is(*dval, i32))
    {
        printf("i32: %d\n", dc_dv_as(*dval, i32));
    }
    else if (dc_dv_is(*dval, string))
    {
        printf("string: %s\n", dc_dv_as(*dval, string));
    }
}

void print_da(DCDynArr* darr)
{
    dc_da_for(*darr)
    {
        printf("['%" PRIuMAX "'] ", _idx);
        DCResultDv res = dc_da_get(darr, _idx);
        if (dc_res_is_ok2(res)) print_dv(dc_res_val2(res));
    }
}

DCResultVoid test1()
{
    dc_res_void();

    DCDynArr darr;

    // Add elements
    dc_try_fail_da_init_with_values(
        &darr, NULL,

        dc_dv(u8, 42), dc_dv(i32, -12345),
        dc_dv(string, "Hello") // here it is a literal string so it doesn't need
                               // to be mark as allocated

    );

    printf("========\nOriginal Array\n========\n");
    printf("-- current capacity: '%" PRIuMAX "', current count: '%" PRIuMAX
           "'\n",
           darr.cap, darr.count);
    print_da(&darr);


    // Print remaining elements
    printf("========\nElement 2 is removed\n========\n");
    // Delete the second element (index 1)
    dc_try_fail_temp(DCResultBool, dc_da_delete(&darr, 1));
    printf("-- current capacity: '%" PRIuMAX "', current count: '%" PRIuMAX
           "'\n",
           darr.cap, darr.count);
    print_da(&darr);

    // inserting
    printf("========\nInserting 2 elements\n========\n");
    dc_try_fail(dc_da_insert(&darr, 1, dc_dv(u8, 100)));
    printf("-- current capacity: '%" PRIuMAX "', current count: '%" PRIuMAX
           "'\n",
           darr.cap, darr.count);

    dc_try_fail(dc_da_insert(&darr, 2, dc_dv(string, "New Item")));
    printf("-- current capacity: '%" PRIuMAX "', current count: '%" PRIuMAX
           "'\n",
           darr.cap, darr.count);
    // Print elements
    print_da(&darr);


    printf("========\nAppending 5 more elements\n========\n");
    dc_try_fail_da_append_values(&darr,
                                 dc_dv(string, "Using append_values started"),
                                 dc_dv(u8, 11), dc_dv(u8, 12), dc_dv(u8, 13),
                                 dc_dv(string, "Using append_values finished"));

    printf("-- current capacity: '%" PRIuMAX "', current count: '%" PRIuMAX
           "'\n",
           darr.cap, darr.count);
    // Print elements
    print_da(&darr);

    DCDynArr darr2;

    // Add elements
    dc_try_fail_da_init_with_values(&darr2, NULL,

                                    dc_dv(string, "Using append started"),
                                    dc_dv(u8, 14), dc_dv(u8, 15), dc_dv(u8, 16),
                                    dc_dv(string, "Using append finished")

    );

    printf("========\nAppending 5 more elements from array\n========\n");
    dc_try_fail(dc_da_append(&darr, &darr2));
    printf("-- current capacity: '%" PRIuMAX "', current count: '%" PRIuMAX
           "'\n",
           darr.cap, darr.count);
    // Print elements
    print_da(&darr);

    printf("========\nInserting 5 more elements in the middle\n========\n");
    dc_try_fail_temp_da_insert_values(
        &darr, 9, dc_dv(string, "Using insert_values started"), dc_dv(u8, 11),
        dc_dv(u8, 12), dc_dv(u8, 13),
        dc_dv(string, "Using insert_values finished"));
    printf("-- current capacity: '%" PRIuMAX "', current count: '%" PRIuMAX
           "'\n",
           darr.cap, darr.count);
    // Print elements
    print_da(&darr);

    DCDynArr darr3;

    // Add elements
    dc_try_fail_da_init_with_values(&darr3, NULL,

                                    dc_dv(string, "Using insert_from started"),
                                    dc_dv(u8, 14), dc_dv(u8, 15), dc_dv(u8, 16),
                                    dc_dv(string, "Using insert_from finished")

    );
    printf("========\nInserting 5 more elements from another array in the "
           "middle\n========\n");
    dc_try_fail(dc_da_insert_from(&darr, 14, &darr3));
    printf("-- current capacity: '%" PRIuMAX "', current count: '%" PRIuMAX
           "'\n",
           darr.cap, darr.count);
    // Print elements
    print_da(&darr);

    printf("========\nGrowing to current cap + 20\n========\n");
    dc_try_fail(dc_da_grow_by(&darr, 20));
    printf("-- current capacity: '%" PRIuMAX "', current count: '%" PRIuMAX
           "'\n",
           darr.cap, darr.count);
    // Print elements
    print_da(&darr);

    printf("========\nTruncate\n========\n");
    dc_try_fail(dc_da_trunc(&darr));
    printf("-- current capacity: '%" PRIuMAX "', current count: '%" PRIuMAX
           "'\n",
           darr.cap, darr.count);
    // Print elements
    print_da(&darr);

    printf("========\nPopping last 5 items\n========\n");
    DCDynValue* popped;
    dc_try_fail(dc_da_pop(&darr, 5, &popped, false));
    printf("-- current capacity: '%" PRIuMAX "', current count: '%" PRIuMAX
           "'\n",
           darr.cap, darr.count);
    // Print elements
    print_da(&darr);

    printf("========\nPopped Items\n========\n");
    for (usize i = 0; i < 5; ++i) print_dv(&popped[i]);

    // Free everything
    dc_try_fail(dc_da_free(&darr));
    dc_try_fail(dc_da_free(&darr2));
    dc_try_fail(dc_da_free(&darr3));
    free(popped);

    dc_res_ret();
}

DCResultVoid test2()
{
    dc_res_void();

    DCDynArr darr;
    dc_try_fail(dc_da_init(&darr, NULL));

    // Adding different types of values
    DCDynValue val;

    // Adding a u8 value
    dc_dv_set(val, u8, 42);
    dc_try_fail(dc_da_push(&darr, val));

    // Adding an i32 value
    dc_dv_set(val, i32, -12345);
    dc_try_fail(dc_da_push(&darr, val));

    // Adding a string
    // in this line something risky is happening as we assumed dc_strdup is
    // successful
    dc_dv_seta(val, string, dc_res_val2(dc_strdup("Hello, Dynamic Array!")));
    dc_try_fail(dc_da_push(&darr, val));

    // Finding an element (search for u8 value 42)
    DCDynValue search_val;
    dc_dv_set(search_val, u8, 42);

    DCResultDv found = dc_da_find(&darr, &search_val);
    dc_fail_if_res(found);

    if (dc_res_val2(found))
    {
        printf("Found u8: %d\n", dc_dv_as((*dc_res_val2(found)), u8));
    }
    else
    {
        dc_log("Element not found.\n");
    }

    // dc_strdup allocates memory so we use the allocated version of dc_dv_set
    // (with an 'a' at the end) and in this line something risky is happening
    // too as we assumed dc_strdup is successful
    dc_dv_seta(search_val, string,
               dc_res_val2(dc_strdup("Hello, Dynamic Array!")));

    found = dc_da_find(&darr, &search_val);
    dc_fail_if_res(found);

    if (dc_res_val2(found))
    {
        printf("Found u8: %d\n", dc_dv_as((*dc_res_val2(found)), u8));
    }
    else
    {
        dc_log("Element not found.\n");
    }

    dc_try_fail(dc_da_free(&darr));

    return dc_dv_free(&search_val, NULL);
}

DCResultVoid test3()
{
    dc_res_void();

    DCDynArr darr;

    dc_try_fail_da_init_with_values(&darr, NULL,

                                    dc_dv(char, 'H'), dc_dv(char, 'e'),
                                    dc_dv(char, 'l'), dc_dv(char, 'l'),
                                    dc_dv(u8, 12), dc_dv(char, 'o'));

    string result_str = NULL;
    /**
     * Convert the `darr` to char flat array and don't fail (bypass the unwanted
     * value)
     */
    DCResultUsize len_res = dc_char_da_to_flat_arr(&darr, &result_str, false);
    dc_fail_if_res(len_res);

    if (dc_res_is_ok2(len_res))
    {
        printf("Resulting string: %s\n", result_str);
        printf("String length: '%" PRIuMAX "'\n", dc_res_val2(len_res));
        free(result_str);
    }
    else
    {
        dc_log("Conversion failed\n");
    }

    return dc_da_free(&darr);
}

DCResultVoid test4()
{
    dc_res_void();

    DCDynArr darr;

    dc_try_fail_da_init_with_values(&darr, NULL,

                                    dc_dv(u8, 1), dc_dv(u8, 2), dc_dv(u8, 3),
                                    dc_dv(u8, 4), dc_dv(u8, 5)

    );

    u8* result = NULL;
    DCResultUsize len_res = dc_u8_da_to_flat_arr(&darr, &result, true);
    dc_fail_if_res(len_res);

    if (dc_res_is_ok2(len_res))
    {
        printf("========\n got '%" PRIuMAX "' elements\n========\n",
               dc_res_val2(len_res));

        for (usize i = 0; i < dc_res_val2(len_res); ++i)
            printf("%d\n", result[i]);

        free(result);
    }
    else
    {
        dc_log("Conversion failed\n");
    }

    return dc_da_free(&darr);
}

DCResultVoid test5()
{
    dc_res_void();

    DCDynArr darr;

    dc_try_fail_da_init_with_values(&darr, NULL,

                                    dc_dv(usize, 6), dc_dv(usize, 7),
                                    dc_dv(usize, 8), dc_dv(usize, 9),
                                    dc_dv(usize, 10)

    );

    usize* result = NULL;
    DCResultUsize len_res = dc_usize_da_to_flat_arr(&darr, &result, true);
    dc_fail_if_res(len_res);

    if (dc_res_is_ok2(len_res))
    {
        printf("========\n got '%" PRIuMAX "' elements\n========\n",
               dc_res_val2(len_res));

        for (usize i = 0; i < dc_res_val2(len_res); ++i)
            printf("'%" PRIuMAX "'\n", result[i]);

        free(result);
    }
    else
    {
        dc_log("Conversion failed\n");
    }

    return dc_da_free(&darr);
}

DCResultVoid test6()
{
    dc_res_void();

    DCDynArr darr;

    dc_try_fail_da_init_with_values(&darr, NULL,

                                    dc_dv(size, 11), dc_dv(size, 12),
                                    dc_dv(size, 13), dc_dv(size, 14),
                                    dc_dv(size, 15)

    );

    size* result = NULL;
    DCResultUsize len_res = dc_size_da_to_flat_arr(&darr, &result, true);
    dc_fail_if_res(len_res);

    if (dc_res_is_ok2(len_res))
    {
        printf("========\n got '%" PRIuMAX "' elements\n========\n",
               dc_res_val2(len_res));

        for (usize i = 0; i < dc_res_val2(len_res); ++i)
            printf("'%" PRIuMAX "'\n", result[i]);

        free(result);
    }
    else
    {
        dc_log("Conversion failed\n");
    }

    return dc_da_free(&darr);
}

typedef struct
{
    int a;
    float b;
} MyStruct;

void print_struct(MyStruct* s)
{
    printf("a: %d, b: %g\n", s->a, s->b);
}

MyStruct* new_ms(int a, float b)
{
    MyStruct* ms = malloc(sizeof(MyStruct));
    ms->a = a;
    ms->b = b;

    return ms;
}

DCResultVoid test7()
{
    dc_res_void();

    DCDynArr darr;

    dc_try_fail_da_init_with_values(
        &darr, NULL,

        // These are allocated instances of MyStruct
        // So We must use dc_dva (Allocated Dynamic Value)
        dc_dva(voidptr, new_ms(42, 1.2)), dc_dva(voidptr, new_ms(43, 3.14)),
        dc_dva(voidptr, new_ms(44, 1.0)), dc_dva(voidptr, new_ms(45, 0.5)),
        dc_dva(voidptr, new_ms(46, 3.6))

    );

    dc_da_for(darr)
    {
        print_struct((MyStruct*)dc_da_get_as(&darr, _idx, voidptr));
    }

    voidptr* result = NULL;
    DCResultUsize len_res = dc_voidptr_da_to_flat_arr(&darr, &result, true);
    dc_fail_if_res(len_res);

    if (dc_res_is_ok2(len_res))
    {
        printf("========\n got '%" PRIuMAX "' elements\n========\n",
               dc_res_val2(len_res));

        for (usize i = 0; i < dc_res_val2(len_res); ++i)
            print_struct((MyStruct*)result[i]);

        free(result);
    }
    else
    {
        dc_log("Conversion failed\n");
    }

    return dc_da_free(&darr);
}


// Example usage of the dynamic array
int main()
{
    dc_res_void();

    dc_try(test1());
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s",
                 dc_res_err_msg());

    dc_try(test2());
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s",
                 dc_res_err_msg());

    dc_try(test3());
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s",
                 dc_res_err_msg());

    dc_try(test4());
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s",
                 dc_res_err_msg());

    dc_try(test5());
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s",
                 dc_res_err_msg());

    dc_try(test6());
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s",
                 dc_res_err_msg());

    dc_try(test7());
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s",
                 dc_res_err_msg());

    return 0;
}
