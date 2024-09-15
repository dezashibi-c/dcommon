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

static void custom_free(DCDynValue* item)
{
    switch (item->type)
    {
        case dc_value_type(string):
            dc_dynval_set(*item, voidptr, NULL);
            break;

        default:
            break;
    }
}

void print_dynarr(DCDynArr* darr)
{
    dc_dynarr_for(*darr)
    {
        printf("[%zu] ", _idx);
        if (dc_dynarr_is(*darr, _idx, u8))
        {
            printf("u8: %u\n", dc_dynarr_get_as(darr, _idx, u8));
        }
        else if (dc_dynarr_is(*darr, _idx, i32))
        {
            printf("i32: %d\n", dc_dynarr_get_as(darr, _idx, i32));
        }
        else if (dc_dynarr_is(*darr, _idx, string))
        {
            printf("string: %s\n", dc_dynarr_get_as(darr, _idx, string));
        }
    }
}

void test1()
{
    DCDynArr darr;

    // Add elements
    dc_dynarr_init_with_values(&darr, custom_free,

                               dc_dynval_lit(u8, 42),
                               dc_dynval_lit(i32, -12345),
                               dc_dynval_lit(string, "Hello")

    );

    printf("========\nOriginal Array\n========\n");
    print_dynarr(&darr);

    // Delete the second element (index 1)
    dc_dynarr_delete(&darr, 1);

    // Print remaining elements
    printf("========\nElement 2 is removed\n========\n");
    print_dynarr(&darr);

    // inserting
    dc_dynarr_insert(&darr, 1, dc_dynval_lit(u8, 100));
    dc_dynarr_insert(&darr, 2, dc_dynval_lit(string, "New Item"));

    // Print remaining elements
    printf("========\nInserting 2 elements\n========\n");
    print_dynarr(&darr);

    // Free everything
    dc_dynarr_free(&darr);
}

void test2()
{
    DCDynArr darr;
    dc_dynarr_init(&darr, NULL);

    // Adding different types of values
    DCDynValue val;

    // Adding a u8 value
    dc_dynval_set(val, u8, 42);
    dc_dynarr_push(&darr, val);

    // Adding an i32 value
    dc_dynval_set(val, i32, -12345);
    dc_dynarr_push(&darr, val);

    // Adding a string
    dc_dynval_set(val, string, dc_strdup("Hello, Dynamic Array!"));
    dc_dynarr_push(&darr, val);

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

    dc_dynval_set(search_val, string, dc_strdup("Hello, Dynamic Array!"));

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
    /**
     * What happens here?
     *  dc_dynarr_free does nothing when the values are literal types on each
     *  type however, when it comes to strings it tries to free the memories if
     *  they are not null, what we generally in situations like this is to call
     *  a custom function that just mark the values as null so that
     *  dc_dynval_free won't fail
     */
    dc_dynarr_free(&darr);

    dc_dynval_free(&search_val, NULL);
}

void test3()
{
    DCDynArr darr;

    dc_dynarr_init_with_values(
        &darr, NULL,

        dc_dynval_lit(char, 'H'), dc_dynval_lit(char, 'e'),
        dc_dynval_lit(char, 'l'), dc_dynval_lit(char, 'l'),
        dc_dynval_lit(u8, 12), dc_dynval_lit(char, 'o'));

    string result_str = NULL;
    /**
     * Convert the `darr` to char flat array and don't fail (bypass the unwanted
     * value)
     */
    usize len = dc_char_dynarr_to_flat_arr(&darr, &result_str, false);

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

    dc_dynarr_init_with_values(&darr, NULL,

                               dc_dynval_lit(u8, 1), dc_dynval_lit(u8, 2),
                               dc_dynval_lit(u8, 3), dc_dynval_lit(u8, 4),
                               dc_dynval_lit(u8, 5)

    );

    u8* result = NULL;
    usize len = dc_u8_dynarr_to_flat_arr(&darr, &result, true);

    printf("========\n got %zu elements\n========\n", len);

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

    dc_dynarr_init_with_values(&darr, NULL,

                               dc_dynval_lit(usize, 6), dc_dynval_lit(usize, 7),
                               dc_dynval_lit(usize, 8), dc_dynval_lit(usize, 9),
                               dc_dynval_lit(usize, 10)

    );

    usize* result = NULL;
    usize len = dc_usize_dynarr_to_flat_arr(&darr, &result, true);

    printf("========\n got %zu elements\n========\n", len);

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

    dc_dynarr_init_with_values(&darr, NULL,

                               dc_dynval_lit(size, 11), dc_dynval_lit(size, 12),
                               dc_dynval_lit(size, 13), dc_dynval_lit(size, 14),
                               dc_dynval_lit(size, 15)

    );

    size* result = NULL;
    usize len = dc_size_dynarr_to_flat_arr(&darr, &result, true);

    printf("========\n got %zu elements\n========\n", len);

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

void test7()
{
    DCDynArr darr;

    dc_dynarr_init_with_values(&darr, custom_free,

                               dc_dynval_lit(voidptr, new_ms(42, 1.2)),
                               dc_dynval_lit(voidptr, new_ms(43, 3.14)),
                               dc_dynval_lit(voidptr, new_ms(44, 1.0)),
                               dc_dynval_lit(voidptr, new_ms(45, 0.5)),
                               dc_dynval_lit(voidptr, new_ms(46, 3.6))

    );

    dc_dynarr_for(darr)
    {
        print_struct((MyStruct*)dc_dynarr_get_as(&darr, _idx, voidptr));
    }

    voidptr* result = NULL;
    usize len = dc_voidptr_dynarr_to_flat_arr(&darr, &result, true);

    printf("========\n got %zu elements\n========\n", len);

    if (result)
    {
        for (usize i = 0; i < len; ++i) print_struct((MyStruct*)result[i]);

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

    test7();

    return 0;
}
