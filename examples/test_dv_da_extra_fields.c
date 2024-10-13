// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: test_dv_da_extra_fields.h
//    Date: 2024-10-13
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

/* First definition of the custom type, can be in another header file */
// You can use this header file to have access to basic types if you're willing
// to use them in your custom type (struct)
#include "../src/dcommon/dcommon_primitives.h"

typedef struct
{
    string name;
    u8 age;
} Person;

#define person_new(NAME, AGE) ((Person){(NAME), (AGE)})

/* Second definition of mandatory macros for dcommon lib to have the type included in dynamic value */
#define DC_DV_EXTRA_TYPES dc_dvt(Person),
#define DC_DV_EXTRA_FIELDS dc_dvf_decl(Person);

#define DC_STOPPER_Person ((Person){0})
#define DC_IS_ARR_TERMINATOR_Person(EL) ((EL).age == 0)

/* Third inclusion of the actual dcommon.h and possibly the DCOMMON_IMPL definition */
#define DCOMMON_IMPL
#include "../src/dcommon/dcommon.h"

/* Actual code starts from here */

void print_person(Person* p)
{
    printf("person: " dc_fmt(string) ", " dc_fmt(u8) "\n", p->name, p->age);
}

void print_dv(DCDynVal* dval)
{
    if (dval->type == dc_dvt(Person))
    {
        print_person(&dc_dv_as(*dval, Person));
        return;
    }

    printf("%s: ", dc_tostr_dvt(dval));

    dc_dv_println(dval);
}

void print_da(DCDynArr* darr)
{
    dc_da_for(*darr)
    {
        printf("['" dc_fmt(usize) "'] ", _idx);
        DCResDv res = dc_da_get(darr, _idx);
        if (dc_res_is_ok2(res)) print_dv(dc_res_val2(res));
    }
}

#define LOG_DYNAMIC_ARRAY_INFO(DARR)                                                                                           \
    printf("-- current capacity: '" dc_fmt(usize) "', current count: '" dc_fmt(usize) "'\n", DARR.cap, DARR.count);

DCResVoid test1()
{
    DC_RES_void();

    DC_ARRAY(people, Person, person_new("Navid", 30), person_new("James", 40), person_new("Bob", 50));

    dc_oneach(people, Person, print_person);

    dc_res_ret();
}

DCResVoid test2()
{
    DC_RES_void();

    DCDynArr darr;

    // Add elements
    dc_try_fail_da_init_with_values(&darr, NULL,

                                    dc_dv(u8, 42), dc_dv(i32, -12345), dc_dv(Person, person_new("Navid", 30)),

                                    // here it is a literal string so it doesn't need
                                    // to be mark as allocated (that's why dc_dv us used)
                                    dc_dv(string, "Hello")

    );

    printf("========\nOriginal Array\n========\n");
    LOG_DYNAMIC_ARRAY_INFO(darr);
    print_da(&darr);


    printf("========\nElement 2 is removed\n========\n");
    // Try to delete the second element (index 1) or fail
    dc_try_fail(dc_da_delete(&darr, 1));
    LOG_DYNAMIC_ARRAY_INFO(darr);
    print_da(&darr);

    printf("========\nInserting 2 elements\n========\n");
    // Try to insert or fail
    dc_try_fail(dc_da_insert(&darr, 1, dc_dv(u8, 100)));
    LOG_DYNAMIC_ARRAY_INFO(darr);

    // Try to insert or fail
    dc_try_fail(dc_da_insert(&darr, 2, dc_dv(string, "New Item")));
    LOG_DYNAMIC_ARRAY_INFO(darr);
    print_da(&darr);


    printf("========\nAppending 5 more elements\n========\n");
    // Try to append values or fail
    dc_try_fail_da_append_values(&darr, dc_dv(string, "Using append_values started"), dc_dv(u8, 11), dc_dv(u8, 12),
                                 dc_dv(u8, 13), dc_dv(string, "Using append_values finished"));

    LOG_DYNAMIC_ARRAY_INFO(darr);
    print_da(&darr);

    // Introducing the second dynamic array
    DCDynArr darr2;

    // Add elements the newly created array
    dc_try_fail_da_init_with_values(&darr2, NULL,

                                    dc_dv(string, "Using append started"), dc_dv(u8, 14), dc_dv(u8, 15), dc_dv(u8, 16),
                                    dc_dv(string, "Using append finished")

    );

    printf("========\nAppending 5 more elements from "
           "array\n========\n");
    // Try to append the second array to the first array or fail
    dc_try_fail(dc_da_append(&darr, &darr2));
    LOG_DYNAMIC_ARRAY_INFO(darr);
    print_da(&darr);

    printf("========\nInserting 5 more elements in the "
           "middle\n========\n");
    // Try to insert 5 elements to the first array or fail
    dc_try_fail_temp_da_insert_values(&darr, 9, dc_dv(string, "Using insert_values started"), dc_dv(u8, 11), dc_dv(u8, 12),
                                      dc_dv(u8, 13), dc_dv(string, "Using insert_values finished"));
    LOG_DYNAMIC_ARRAY_INFO(darr);
    print_da(&darr);

    // Introducing the third dynamic array
    DCDynArr darr3;

    // Add elements to the newly created array
    dc_try_fail_da_init_with_values(&darr3, NULL,

                                    dc_dv(string, "Using insert_from started"), dc_dv(u8, 14), dc_dv(u8, 15), dc_dv(u8, 16),
                                    dc_dv(string, "Using insert_from finished")

    );
    printf("========\nInserting 5 more elements from another array "
           "in the "
           "middle\n========\n");
    // Try inserting the third array at the index 14th of the first array or
    // fail
    dc_try_fail(dc_da_insert_from(&darr, 14, &darr3));
    LOG_DYNAMIC_ARRAY_INFO(darr);
    print_da(&darr);

    printf("========\nGrowing to current cap + 20\n========\n");
    // Try growing the first array's capacity by 20 or fail
    dc_try_fail(dc_da_grow_by(&darr, 20));
    LOG_DYNAMIC_ARRAY_INFO(darr);
    print_da(&darr);

    printf("========\nTruncate\n========\n");
    // Try truncating unused capacity of the first array or fail
    dc_try_fail(dc_da_trunc(&darr));
    LOG_DYNAMIC_ARRAY_INFO(darr);
    print_da(&darr);

    printf("========\nPopping last 5 items\n========\n");
    // Declaring a memory for holding popped items from the first array
    DCDynVal* popped;
    // Trying to pop out last 5 elements of the first array or fail
    dc_try_fail(dc_da_pop(&darr, 5, &popped, false));
    LOG_DYNAMIC_ARRAY_INFO(darr);
    print_da(&darr);

    printf("========\nPopped Items\n========\n");
    for (usize i = 0; i < 5; ++i) print_dv(&popped[i]);

    // Free everything
    dc_try_fail(dc_da_free(&darr));
    dc_try_fail(dc_da_free(&darr2));
    dc_try_fail(dc_da_free(&darr3));
    free(popped);

    // Returning the void result which is OK by default so if we're here we
    // haven't had any errors, yay!
    dc_res_ret();
}

int main()
{
    DC_RES_void();

    dc_try(test1());
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s", dc_res_err_msg());

    dc_try(test2());
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s", dc_res_err_msg());

    return 0;
}