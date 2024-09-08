// ***************************************************************************************
//    Project:
//    File: test_lists.c
//    Date: 2024-09-08
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website:
//    License:
//     Please refer to the LICENSE file, repository or website for more
//     information about the licensing of this work. If you have any questions
//     or concerns, please feel free to contact me at the email address provided
//     above.
// ***************************************************************************************
// *  Description:
// ***************************************************************************************

#include "../src/dcommon/dcommon.h"

void print(u8* number)
{
    printf("%d\n", *number);
}

int main(void)
{
    dc_list_make(u8_list, u8, 10, 20, 30);
    dc_list_make(i32_list, i32, 1, 2, 3);
    dc_list_make(f32_list, f32, 1.1f, 2.2f);
    dc_list_make(byte_list, byte, 'a', 'b', 'c');

    printf("u8_list's count=%zu, u8_list's length=%zu, last element=%d\n",
           dc_list_count(u8_list), dc_list_len(u8_list),
           dc_list_get_last(u8_list));

    dc_list_for_each(u8_list, u8, item)
    {
        printf("u8 item: %d\n", *item);
    }

    dc_list_for_each(i32_list, i32, item)
    {
        printf("i32 item: %d\n", *item);
    }

    dc_list_for_each(f32_list, f32, item)
    {
        printf("f32 item: %f\n", *item);
    }

    dc_list_for_each(byte_list, byte, item)
    {
        printf("byte item: %c\n", *item);
    }

    puts("\n==========================");
    dc_list_on_each(u8_list, u8, print);
    puts("==========================\n");

    dc_list_lit_for_each(u8, item, 40, 50, 60)
    {
        printf("Literal u8 item: %d\n", *item);
    }

    puts("\n==========================");
    dc_list_lit_on_each(u8, print, 23, 24, 25);
    puts("==========================\n");

    return 0;
}
