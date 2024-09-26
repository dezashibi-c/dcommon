// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: test_string_view.h
//    Date: 2024-09-12
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

void print_sv(DCStringView* sv)
{
    printf("I can see '" DCPRIsv "' in the text!\n", dc_sv_fmt(*sv));
}

int main()
{
    DC_RES_void();

    string my_string = "Hello, World!";

    DCStringView view = dc_res_val2(dc_sv_create(my_string, 7, 5));
    DCStringView view2 = dc_res_val2(dc_sv_create(my_string, 0, 5));

    print_sv(&view);
    print_sv(&view2);

    string world = dc_res_val2(dc_sv_as_cstr(&view));
    string hello = dc_res_val2(dc_sv_as_cstr(&view2));

    // do whatever I like with this, because it's now extracted and saved in
    // view.cstr
    printf("yes '%s' one more time!\n", world);
    printf("yes '%s' one more time!\n", hello);

    if (dc_sv_str_eq(view, "World")) printf("Yes they are the same!\n");

    if (dc_sv_str_eq(view2, "Hello")) printf("Yes they are the same!\n");

    if (dc_sv_str_eq(view, world))
        printf("Yes for heaven's sake, they are the same!\n");

    if (dc_sv_str_eq(view2, hello))
        printf("Yes for heaven's sake, they are the same!\n");

    if (dc_sv_sv_eq(view, view2)) printf("Do you really expect that!?");

    string some_text = NULL;
    dc_sprintf(&some_text, DCPRIsv " %s %s", dc_sv_fmt(view), "- whatever -",
               hello);
    dc_log("%s", some_text);
    free(some_text);

    // don't forget to free it!
    dc_try(dc_sv_free(&view));
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s",
                 dc_res_err_msg());
    // free(world); // or this (just one of them)

    dc_try(dc_sv_free(&view2));
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s",
                 dc_res_err_msg());
    // free(hello); // or this (just one of them)
}
