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

typedef MyStruct* MyStructPtr;

/* if you want to use them in dc arrays that are meant to be terminated with a stopper value
    then both of these macros per type is mandatory

    Notes:
        1. as '*' cannot be used in macro name a simple typedef for pointer to your type
            can solve the problem
        2. The exact type name must be used in the macro name
*/
#define DC_STOPPER_MyStructPtr NULL
#define DC_IS_STOPPER_MyStructPtr(EL) ((EL) == NULL)

#define DC_STOPPER_MyStruct ((MyStruct){0})
#define DC_IS_STOPPER_MyStruct(EL) ((EL).a == 0)


void print_my_struct(MyStruct* m)
{
    printf("a=%d, b=%d\n", m->a, m->b++);
}

int main(void)
{
    // ***************************************************************************************
    // *  STRING CONVERSIONS
    // ***************************************************************************************
    const string i8Str = "127";
    DCResI8 i8_cnv_res = dc_str_to_i8(i8Str);

    if (dc_is_ok2(i8_cnv_res))
    {
        printf("Converted i8: %" PRId8 "\n", dc_unwrap2(i8_cnv_res));
    }
    else
    {
        printf("Failed to convert to i8.\n");
    }

    const string u32Str = "4294967295";
    DCResU32 u32_cnv_res = dc_str_to_u32(u32Str);

    if (dc_is_ok2(u32_cnv_res))
    {
        printf("Converted u32: %" PRIu32 "\n", dc_unwrap2(u32_cnv_res));
    }
    else
    {
        printf("Failed to convert to u32.\n");
    }

    const string f64Str = "3.14";
    DCResF64 f64_cnv_res = dc_str_to_f64(f64Str);

    if (dc_is_ok2(f64_cnv_res))
    {
        printf("Converted f64: %f\n", dc_unwrap2(f64_cnv_res));
    }
    else
    {
        printf("Failed to convert to f64.\n");
    }

    // ***************************************************************************************
    // *  LITERAL ARRAYS
    // ***************************************************************************************
    DC_DEF_ARRAY(bool_list, u8, 10, 0, false, true);
    DC_DEF_ARRAY(u8_list, u8, 10, 20, 30);
    DC_DEF_ARRAY(i16_list, i16, -10, 2, -30);
    DC_DEF_ARRAY(i32_list, i32, -1, -2, 3);
    DC_DEF_ARRAY(f32_list, f32, 1.1f, 2.2f);
    DC_DEF_ARRAY(char_list, char, 'a', 'b', 'c');

    printf("u8_list's count='" dc_fmt(usize) "', u8_list's length='" dc_fmt(usize) "', last element=%d\n", dc_count(u8_list),
           dc_len(u8_list), dc_last(u8_list));

    // Example usage of dc_action_on
    // As you can see this can be quite helpful, we've got our condition, action
    // and error log in a very readable and short way
    dc_action_on(dc_len(u8_list) != 3, return 1, "length calculation error");

    // Example usage of for each macros
    // 👉 Note: `_it` is in fact pointer to each element which makes sense why
    // copy?
    dc_foreach(loop1, bool_list, u8, printf("b1 item: %s\n", dc_tostr_bool(dc_u8_to_bool(*_it))));

    dc_foreach(loop2, u8_list, u8, printf("u8 item: %d\n", *_it));

    dc_foreach(loop3, i16_list, i16, printf("i16 item: %d\n", *_it));

    dc_foreach(loop4, i32_list, i32, printf("i32 item: %d\n", *_it));

    dc_foreach(loop5, f32_list, f32, printf("f32 item: %f\n", *_it));

    dc_foreach(loop6, char_list, char, printf("char item: %c\n", *_it));

    dc_foreach2(
        loop7, u8,
        {
            printf("Literal u8 item: %d\n", *_it); // <- Check here
        },
        40, 50, 60);

    puts("\n==========================");
    MyStruct m1 = {.a = 10, .b = 12};
    MyStruct m2 = {.a = 20, .b = 14};
    MyStruct m3 = {.a = 30, .b = 16};

    dc_foreach2(, MyStructPtr, print_my_struct(*_it), &m1, &m2, &m3);
    puts("==========================\n");

    puts("\n==========================");
    DC_DEF_ARRAY(my_struct_list, MyStructPtr, &m1, &m2, &m3);

    dc_foreach(loop9, my_struct_list, MyStructPtr, print_my_struct(*_it));

    puts("==========================\n");

    puts("\n==========================");
    dc_foreach2(loop10, MyStruct, print_my_struct(_it), {.a = 4, .b = 12}, {.a = 5, .b = 13}, {.a = 6, .b = 14});
    puts("==========================\n");

    puts("\n==========================");
    string s1 = "Hello";
    string s2 = "There";
    string s3 = "Hey";
    DC_DEF_ARRAY(string_list, string, s1, s2, s3);

    dc_foreach(loop11, string_list, string, print_str(_it));
    puts("==========================\n");

    return 0;
}
