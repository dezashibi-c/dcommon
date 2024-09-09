// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: test_lists.h
//    Date: 2024-09-08
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

#include "../src/dcommon/dcommon.h"

void print(u8* number)
{
    printf("%d\n", *number);
}

void print_str(string* text)
{
    printf("%s\n", *text);
}

typedef struct
{
    int a;
    int b;
} MyStruct;

void print_my_struct(MyStruct* m)
{
    printf("a=%d, b=%d\n", m->a, m->b++);
}

int main(void)
{
    dc_array(u8_list, u8, 10, 20, 30);
    dc_array(i32_list, i32, 1, 2, 3);
    dc_array(f32_list, f32, 1.1f, 2.2f);
    dc_array(byte_list, byte, 'a', 'b', 'c');

    printf("u8_list's count=%zu, u8_list's length=%zu, last element=%d\n",
           dc_count(u8_list), dc_len(u8_list), dc_last(u8_list));

    dc_halt_when(dc_len(u8_list) != 3, return 1, "length calculation error");

    dc_foreach(u8_list, u8, item)
    {
        printf("u8 item: %d\n", *item);
    }

    dc_foreach(i32_list, i32, item)
    {
        printf("i32 item: %d\n", *item);
    }

    dc_foreach(f32_list, f32, item)
    {
        printf("f32 item: %f\n", *item);
    }

    dc_foreach(byte_list, byte, item)
    {
        printf("byte item: %c\n", *item);
    }

    puts("\n==========================");
    dc_oneach(u8_list, u8, print);
    puts("==========================\n");

    dc_foreach_lit(u8, item, 40, 50, 60)
    {
        printf("Literal u8 item: %d\n", *item);
    }

    puts("\n==========================");
    dc_oneach_lit(u8, print, 23, 24, 25);
    puts("==========================\n");

    puts("\n==========================");
    dc_oneach_lit(string, print_str, "Hello", "There", "Byte");
    puts("==========================\n");

    puts("\n==========================");
    MyStruct m1 = {.a = 10, .b = 12};
    MyStruct m2 = {.a = 20, .b = 14};
    MyStruct m3 = {.a = 30, .b = 16};

    dc_poneach_lit(MyStruct, print_my_struct, &m1, &m2, &m3);
    puts("==========================\n");

    puts("\n==========================");
    dc_parray(my_struct_list, MyStruct, &m1, &m2, &m3);

    dc_pforeach(my_struct_list, MyStruct, item)
    {
        print_my_struct(*item);
    }
    puts("==========================\n");

    puts("\n==========================");
    string s1 = "Hello";
    string s2 = "There";
    string s3 = "Hey";
    dc_array(string_list, string, s1, s2, s3);

    dc_foreach(string_list, string, item)
    {
        print_str(item);
    }
    puts("==========================\n");

    return 0;
}
