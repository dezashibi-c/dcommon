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

// static dc_dv_free_func_decl(custom_free)
// {
//     switch (_value->type)
//     {
//         case dc_dvt(string):
//             dc_dv_set(*_value, voidptr, NULL);
//             break;

//         default:
//             break;
//     }
// }

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
        printf("[%zu] ", _idx);
        print_dv(dc_da_get(darr, _idx));
    }
}

void test1()
{
    DCDynArr darr;

    // Add elements
    dc_da_init_with_values(&darr, NULL,

                           dc_dv(u8, 42), dc_dv(i32, -12345),
                           dc_dv(string, "Hello")

    );

    printf("========\nOriginal Array\n========\n");
    printf("-- current capacity: %zu, current count: %zu\n", darr.cap,
           darr.count);
    print_da(&darr);


    // Print remaining elements
    printf("========\nElement 2 is removed\n========\n");
    // Delete the second element (index 1)
    dc_da_delete(&darr, 1);
    printf("-- current capacity: %zu, current count: %zu\n", darr.cap,
           darr.count);
    print_da(&darr);

    // inserting
    printf("========\nInserting 2 elements\n========\n");
    dc_da_insert(&darr, 1, dc_dv(u8, 100));
    printf("-- current capacity: %zu, current count: %zu\n", darr.cap,
           darr.count);

    dc_da_insert(&darr, 2, dc_dv(string, "New Item"));
    printf("-- current capacity: %zu, current count: %zu\n", darr.cap,
           darr.count);
    // Print elements
    print_da(&darr);


    printf("========\nAppending 5 more elements\n========\n");
    dc_da_append_values(&darr, dc_dv(string, "Using append_values started"),
                        dc_dv(u8, 11), dc_dv(u8, 12), dc_dv(u8, 13),
                        dc_dv(string, "Using append_values finished"));
    printf("-- current capacity: %zu, current count: %zu\n", darr.cap,
           darr.count);
    // Print elements
    print_da(&darr);

    DCDynArr darr2;

    // Add elements
    dc_da_init_with_values(&darr2, NULL,

                           dc_dv(string, "Using append started"), dc_dv(u8, 14),
                           dc_dv(u8, 15), dc_dv(u8, 16),
                           dc_dv(string, "Using append finished")

    );

    printf("========\nAppending 5 more elements from array\n========\n");
    dc_da_append(&darr, &darr2);
    printf("-- current capacity: %zu, current count: %zu\n", darr.cap,
           darr.count);
    // Print elements
    print_da(&darr);

    printf("========\nInserting 5 more elements in the middle\n========\n");
    dc_da_insert_values(&darr, 9, dc_dv(string, "Using insert_values started"),
                        dc_dv(u8, 11), dc_dv(u8, 12), dc_dv(u8, 13),
                        dc_dv(string, "Using insert_values finished"));
    printf("-- current capacity: %zu, current count: %zu\n", darr.cap,
           darr.count);
    // Print elements
    print_da(&darr);


    DCDynArr darr3;

    // Add elements
    dc_da_init_with_values(&darr3, NULL,

                           dc_dv(string, "Using insert_from started"),
                           dc_dv(u8, 14), dc_dv(u8, 15), dc_dv(u8, 16),
                           dc_dv(string, "Using insert_from finished")

    );
    printf("========\nInserting 5 more elements from another array in the "
           "middle\n========\n");
    dc_da_insert_from(&darr, 14, &darr3);
    printf("-- current capacity: %zu, current count: %zu\n", darr.cap,
           darr.count);
    // Print elements
    print_da(&darr);

    printf("========\nGrowing to current cap + 20\n========\n");
    dc_da_grow_by(&darr, 20);
    printf("-- current capacity: %zu, current count: %zu\n", darr.cap,
           darr.count);
    // Print elements
    print_da(&darr);

    printf("========\nTruncate\n========\n");
    dc_da_trunc(&darr);
    printf("-- current capacity: %zu, current count: %zu\n", darr.cap,
           darr.count);
    // Print elements
    print_da(&darr);

    printf("========\nPopping last 5 items\n========\n");
    DCDynValue* popped;
    dc_da_pop(&darr, 5, &popped, false);
    printf("-- current capacity: %zu, current count: %zu\n", darr.cap,
           darr.count);
    // Print elements
    print_da(&darr);

    printf("========\nPopped Items\n========\n");
    for (usize i = 0; i < 5; ++i) print_dv(&popped[i]);

    // Free everything
    dc_da_free(&darr);
    dc_da_free(&darr2);
    dc_da_free(&darr3);
    free(popped);
}

void test2()
{
    DCDynArr darr;
    dc_da_init(&darr, NULL);

    // Adding different types of values
    DCDynValue val;

    // Adding a u8 value
    dc_dv_set(val, u8, 42);
    dc_da_push(&darr, val);

    // Adding an i32 value
    dc_dv_set(val, i32, -12345);
    dc_da_push(&darr, val);

    // Adding a string
    dc_dv_seta(val, string, dc_strdup("Hello, Dynamic Array!"));
    dc_da_push(&darr, val);

    // Finding an element (search for u8 value 42)
    DCDynValue search_val;
    dc_dv_set(search_val, u8, 42);

    DCDynValue* found = dc_da_find(&darr, &search_val);
    if (found)
    {
        printf("Found u8: %d\n", dc_dv_as((*found), u8));
    }
    else
    {
        printf("Element not found.\n");
    }

    dc_dv_seta(search_val, string, dc_strdup("Hello, Dynamic Array!"));

    found = dc_da_find(&darr, &search_val);
    if (found)
    {
        printf("Found string: %s\n", dc_dv_as((*found), string));
    }
    else
    {
        printf("Element not found.\n");
    }

    // Free the dynamic array
    /**
     * What happens here?
     *  dc_da_free does nothing when the values are literal types on each
     *  type however, when it comes to strings it tries to free the memories if
     *  they are not null, what we generally in situations like this is to call
     *  a custom function that just mark the values as null so that
     *  dc_dv_free won't fail
     */
    dc_da_free(&darr);

    dc_dv_free(&search_val, NULL);
}

void test3()
{
    DCDynArr darr;

    dc_da_init_with_values(&darr, NULL,

                           dc_dv(char, 'H'), dc_dv(char, 'e'), dc_dv(char, 'l'),
                           dc_dv(char, 'l'), dc_dv(u8, 12), dc_dv(char, 'o'));

    string result_str = NULL;
    /**
     * Convert the `darr` to char flat array and don't fail (bypass the unwanted
     * value)
     */
    usize len = dc_char_da_to_flat_arr(&darr, &result_str, false);

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

    dc_da_free(&darr);
}

void test4()
{
    DCDynArr darr;

    dc_da_init_with_values(&darr, NULL,

                           dc_dv(u8, 1), dc_dv(u8, 2), dc_dv(u8, 3),
                           dc_dv(u8, 4), dc_dv(u8, 5)

    );

    u8* result = NULL;
    usize len = dc_u8_da_to_flat_arr(&darr, &result, true);

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

    dc_da_free(&darr);
}

void test5()
{
    DCDynArr darr;

    dc_da_init_with_values(&darr, NULL,

                           dc_dv(usize, 6), dc_dv(usize, 7), dc_dv(usize, 8),
                           dc_dv(usize, 9), dc_dv(usize, 10)

    );

    usize* result = NULL;
    usize len = dc_usize_da_to_flat_arr(&darr, &result, true);

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

    dc_da_free(&darr);
}

void test6()
{
    DCDynArr darr;

    dc_da_init_with_values(&darr, NULL,

                           dc_dv(size, 11), dc_dv(size, 12), dc_dv(size, 13),
                           dc_dv(size, 14), dc_dv(size, 15)

    );

    size* result = NULL;
    usize len = dc_size_da_to_flat_arr(&darr, &result, true);

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

    dc_da_free(&darr);
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

    dc_da_init_with_values(
        &darr, NULL,

        dc_dva(voidptr, new_ms(42, 1.2)), dc_dva(voidptr, new_ms(43, 3.14)),
        dc_dva(voidptr, new_ms(44, 1.0)), dc_dva(voidptr, new_ms(45, 0.5)),
        dc_dva(voidptr, new_ms(46, 3.6))

    );

    dc_da_for(darr)
    {
        print_struct((MyStruct*)dc_da_get_as(&darr, _idx, voidptr));
    }

    voidptr* result = NULL;
    usize len = dc_voidptr_da_to_flat_arr(&darr, &result, true);

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

    dc_da_free(&darr);
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
