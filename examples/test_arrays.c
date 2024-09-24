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

#define DCOMMON_IMPL
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
    const string i8Str = "127";
    DCResultI8 i8_cnv_res = dc_str_to_i8(i8Str);

    if (dc_res_is_ok2(i8_cnv_res))
    {
        printf("Converted i8: %" PRId8 "\n", dc_res_val2(i8_cnv_res));
    }
    else
    {
        printf("Failed to convert to i8.\n");
    }

    // Repeat for other types as needed...
    const string u32Str = "4294967295";
    DCResultU32 u32_cnv_res = dc_str_to_u32(u32Str);

    if (dc_res_is_ok2(u32_cnv_res))
    {
        printf("Converted u32: %" PRIu32 "\n", dc_res_val2(u32_cnv_res));
    }
    else
    {
        printf("Failed to convert to u32.\n");
    }

    const string f64Str = "3.14";
    DCResultF64 f64_cnv_res = dc_str_to_f64(f64Str);

    if (dc_res_is_ok2(f64_cnv_res))
    {
        printf("Converted f64: %f\n", dc_res_val2(f64_cnv_res));
    }
    else
    {
        printf("Failed to convert to f64.\n");
    }

    dc_array(bool_list, u8, 10, 0, false, true);
    dc_array(u8_list, u8, 10, 20, 30);
    dc_array(i16_list, i16, -10, 2, -30);
    dc_array(i32_list, i32, -1, -2, 3);
    dc_array(f32_list, f32, 1.1f, 2.2f);
    dc_array(char_list, char, 'a', 'b', 'c');

    printf("u8_list's count='%" PRIuMAX "', u8_list's length='%" PRIuMAX
           "', last element=%d\n",
           dc_count(u8_list), dc_len(u8_list), dc_last(u8_list));

    dc_action_on(dc_len(u8_list) != 3, return 1, "length calculation error");

    dc_foreach(bool_list, u8)
    {
        printf("bool item: %s\n", dc_tostr_bool(dc_u8_as_bool(*_it)));
    }

    dc_foreach(u8_list, u8)
    {
        printf("u8 item: %d\n", *_it);
    }

    dc_foreach(i16_list, i16)
    {
        printf("i16 item: %d\n", *_it);
    }

    dc_foreach(i32_list, i32)
    {
        printf("i32 item: %d\n", *_it);
    }

    dc_foreach(f32_list, f32)
    {
        printf("f32 item: %f\n", *_it);
    }

    dc_foreach(char_list, char)
    {
        printf("char item: %c\n", *_it);
    }

    puts("\n==========================");
    dc_oneach(u8_list, u8, print);
    puts("==========================\n");

    dc_foreach_lit(u8, 40, 50, 60)
    {
        printf("Literal u8 item: %d\n", *_it);
    }

    puts("\n==========================");
    dc_oneach_lit(u8, print, 23, 24, 25);
    puts("==========================\n");

    puts("\n==========================");
    dc_oneach_lit(string, print_str, "Hello", "There", "char");
    puts("==========================\n");

    puts("\n==========================");
    MyStruct m1 = {.a = 10, .b = 12};
    MyStruct m2 = {.a = 20, .b = 14};
    MyStruct m3 = {.a = 30, .b = 16};

    dc_poneach_lit(MyStruct, print_my_struct, &m1, &m2, &m3);
    puts("==========================\n");

    puts("\n==========================");
    dc_parray(my_struct_list, MyStruct, &m1, &m2, &m3);

    dc_pforeach(my_struct_list, MyStruct)
    {
        print_my_struct(*_it);
    }
    puts("==========================\n");

    puts("\n==========================");
    dc_soneach_lit(MyStruct, _it->a != 0, print_my_struct, {.a = 4, .b = 12},
                   {.a = 5, .b = 13}, {.a = 6, .b = 14}, {.a = 0});
    puts("==========================\n");

    puts("\n==========================");
    dc_sforeach_lit(MyStruct, _it->a != 0, {.a = 4, .b = 12}, {.a = 5, .b = 13},
                    {.a = 6, .b = 14}, {.a = 0})
    {
        print_my_struct(_it);
    }
    puts("==========================\n");

    puts("\n==========================");
    string s1 = "Hello";
    string s2 = "There";
    string s3 = "Hey";
    dc_array(string_list, string, s1, s2, s3);

    dc_foreach(string_list, string)
    {
        print_str(_it);
    }
    puts("==========================\n");

    return 0;
}
