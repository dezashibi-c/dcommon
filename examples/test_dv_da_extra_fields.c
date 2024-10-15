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

/* First definition of the custom type, can be in another header file
    You can use this header file to have access to basic types if you're willing
    to use them in your custom type (struct) */
#include "../src/dcommon/dcommon_primitives.h"

typedef struct
{
    string name;
    u8 age;
} Person;

#define person_new(NAME, AGE) ((Person){(NAME), (AGE)})

/*
    Second definition of mandatory macros for dcommon lib to have the type included in dynamic value
    Important Notes:
        1. extra types and extra fields must be declared before including dcommon header file
        2. pay attention to ending ',' and ';' don't forget them
        3. most important: these two must be identically declared with same types

        so if let's say you've got 3 types called Shape, Person, Animal
            A. Extra types would be
                #define DC_DV_EXTRA_TYPES dc_dvt(Shape), dc_dvt(Person), dc_dvt(Animal),
            B. Extra fields would be
                #define DC_DV_EXTRA_FIELDS dc_dvf_decl(Shape); dc_dvf_decl(Person); dc_dvf_decl(Animal);
*/

#define DC_DV_EXTRA_TYPES dc_dvt(Person),
#define DC_DV_EXTRA_FIELDS dc_dvf_decl(Person);

/* Third inclusion of the actual dcommon.h and possibly the DCOMMON_IMPL definition */
#define DCOMMON_IMPL
#include "../src/dcommon/dcommon.h"

/* Forth these stopper and stopper checkers can be anywhere could be at step 2,
    if you want to use them in dc arrays that are meant to be terminated with a stopper value
    then both of these macros per type is mandatory */
#define DC_STOPPER_Person ((Person){0})
#define DC_IS_STOPPER_Person(EL) ((EL).age == 0)

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
    dc_da_for(*darr, {
        printf("['" dc_fmt(usize) "'] ", _idx);
        DCResDv res = dc_da_get(darr, _idx);
        if (dc_res_is_ok2(res)) print_dv(dc_res_val2(res));
    });
}

#define LOG_DYNAMIC_ARRAY_INFO(DARR)                                                                                           \
    printf("-- current capacity: '" dc_fmt(usize) "', current count: '" dc_fmt(usize) "'\n", DARR.cap, DARR.count);

DCResVoid test1()
{
    DC_RES_void();

    DC_DEF_ARRAY(people, Person, person_new("Navid", 30), person_new("James", 40), person_new("Bob", 50));

    dc_foreach(people, Person, print_person(_it));

    dc_res_ret();
}

DCResVoid test2()
{
    DC_RES_void();

    DCDynArr darr;

    string some_text = "This is Navid";

    // Add elements
    dc_try_fail_da_init_with_values(&darr, NULL,

                                    dc_dv(u8, 42), dc_dv(i32, -12345), dc_dv(Person, person_new("Navid", 30)),

                                    dc_dv(DCStringView, dc_sv(some_text, 8, 5)),

                                    // here it is a literal string so it doesn't need
                                    // to be mark as allocated (that's why dc_dv is used)
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

    printf("========\nInserting 1 element\n========\n");
    // Try to insert or fail
    dc_try_fail(dc_da_insert(&darr, 1, dc_dv(Person, person_new("James", 20))));
    LOG_DYNAMIC_ARRAY_INFO(darr);
    print_da(&darr);

    // Free everything
    dc_try_fail(dc_da_free(&darr));

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