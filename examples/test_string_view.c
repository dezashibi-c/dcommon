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
    printf("I can see '" DC_SV_FMT "' in the text!\n", dc_sv_fmt_val(*sv));
}

int main()
{
    string my_string = "Hello, World!";

    DCStringView view = dc_sv_create(my_string, 7, 5);
    DCStringView view2 = dc_sv_create(my_string, 0, 5);

    print_sv(&view);
    print_sv(&view2);

    string world = dc_sv_as_cstr(&view);
    string hello = dc_sv_as_cstr(&view2);

    // do whatever I like with this, because it's now extracted and saved in
    // view.cstr
    printf("yes '%s' one more time!\n", world);
    printf("yes '%s' one more time!\n", hello);

    if (dc_sv_cmp(view, "World") == 0)
        printf("Yes for heaven sake, they are the same!\n");

    if (dc_sv_cmp(view2, "Hello") == 0)
        printf("Yes for heaven sake, they are the same!\n");

    // don't forget to free it!
    dc_sv_free(&view);
    // free(world); // or this (just one of them of course)

    dc_sv_free(&view2);
    // free(hello); // or this (just one of them of course)
}
