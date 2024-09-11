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

void test1()
{
    DCDynArr darr;

    // Add elements
    dc_dynarr_init_with_values(&darr, 3,

                               dc_dynval_lit(u8, 42),
                               dc_dynval_lit(i32, -12345),
                               dc_dynval_lit(string, strdup("Hello"))

    );

    // Delete the second element (index 1)
    dc_dynarr_delete(&darr, 1, NULL);

    // Print remaining elements
    for (usize i = 0; i < darr.count; i++)
    {
        printf("[%zu] ", i);
        if (dc_dynval_is(darr.elements[i], u8))
        {
            printf("u8: %u\n", dc_dynval_get(darr.elements[i], u8));
        }
        else if (dc_dynval_is(darr.elements[i], i32))
        {
            printf("i32: %d\n", dc_dynval_get(darr.elements[i], i32));
        }
        else if (dc_dynval_is(darr.elements[i], string))
        {
            printf("string: %s\n", dc_dynval_get(darr.elements[i], string));
        }
    }

    // Free everything
    dc_dynarr_free(&darr);
}

void test2()
{
    DCDynArr darr;
    dc_dynarr_init(&darr);

    // Adding different types of values
    DCDynValue val;

    // Adding a u8 value
    dc_dynval_set(val, u8, 42);
    dc_dynarr_add(&darr, val);

    // Adding an i32 value
    dc_dynval_set(val, i32, -12345);
    dc_dynarr_add(&darr, val);

    // Adding a string
    dc_dynval_set(val, string, strdup("Hello, Dynamic Array!"));
    dc_dynarr_add(&darr, val);

    // Finding an element (search for u8 value 42)
    DCDynValue search_val;
    dc_dynval_set(search_val, u8, 42);

    DCDynValue* found = dc_dynarr_find(&darr, &search_val);
    if (found)
    {
        printf("Found u8: %d\n", dc_dynval_get((*found), u8));
    }
    else
    {
        printf("Element not found.\n");
    }

    dc_dynval_set(search_val, string, strdup("Hello, Dynamic Array!"));

    found = dc_dynarr_find(&darr, &search_val);
    if (found)
    {
        printf("Found string: %s\n", dc_dynval_get((*found), string));
    }
    else
    {
        printf("Element not found.\n");
    }

    // Free the dynamic array
    dc_dynarr_free(&darr);

    dc_dynarr_value_free(&search_val, NULL);
}

void test3()
{
    DCDynArr darr;

    dc_dynarr_init_with_values(
        &darr, 5,

        dc_dynval_lit(byte, 'H'), dc_dynval_lit(byte, 'e'),
        dc_dynval_lit(byte, 'l'), dc_dynval_lit(byte, 'l'),
        dc_dynval_lit(byte, 'o')

    );

    string result_str = NULL;
    usize len = dc_byte_dynarr_to_flat_arr(&darr, &result_str);

    if (result_str)
    {
        printf("Resulting string: %s\n", result_str);
        printf("String length: %zu\n", len);
        free(result_str);
    }
    else
    {
        printf("Conversion failed\n");
    }

    dc_dynarr_free(&darr);
}

void test4()
{
    DCDynArr darr;

    dc_dynarr_init_with_values(&darr, 5,

                               dc_dynval_lit(u8, 1), dc_dynval_lit(u8, 2),
                               dc_dynval_lit(u8, 3), dc_dynval_lit(u8, 4),
                               dc_dynval_lit(u8, 5)

    );

    u8* result = NULL;
    usize len = dc_u8_dynarr_to_flat_arr(&darr, &result);

    printf("========\n got %zu elements\n=======\n", len);

    if (result)
    {
        for (usize i = 0; i < len; ++i) printf("%d\n", result[i]);

        free(result);
    }
    else
    {
        printf("Conversion failed\n");
    }

    dc_dynarr_free(&darr);
}

void test5()
{
    DCDynArr darr;

    dc_dynarr_init_with_values(&darr, 5,

                               dc_dynval_lit(usize, 6), dc_dynval_lit(usize, 7),
                               dc_dynval_lit(usize, 8), dc_dynval_lit(usize, 9),
                               dc_dynval_lit(usize, 10)

    );

    usize* result = NULL;
    usize len = dc_usize_dynarr_to_flat_arr(&darr, &result);

    printf("========\n got %zu elements\n=======\n", len);

    if (result)
    {
        for (usize i = 0; i < len; ++i) printf("%zu\n", result[i]);

        free(result);
    }
    else
    {
        printf("Conversion failed\n");
    }

    dc_dynarr_free(&darr);
}

void test6()
{
    DCDynArr darr;

    dc_dynarr_init_with_values(&darr, 5,

                               dc_dynval_lit(size, 11), dc_dynval_lit(size, 12),
                               dc_dynval_lit(size, 13), dc_dynval_lit(size, 14),
                               dc_dynval_lit(size, 15)

    );

    size* result = NULL;
    usize len = dc_size_dynarr_to_flat_arr(&darr, &result);

    printf("========\n got %zu elements\n=======\n", len);

    if (result)
    {
        for (usize i = 0; i < len; ++i) printf("%zu\n", result[i]);

        free(result);
    }
    else
    {
        printf("Conversion failed\n");
    }

    dc_dynarr_free(&darr);
}


// Example usage of the dynamic array
int main()
{
    test1();

    test2();

    test3();

    test4();

    test5();

    test6();

    return 0;
}
