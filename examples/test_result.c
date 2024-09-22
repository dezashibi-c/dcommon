// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: test_result.h
//    Date: 2024-09-22
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

DCResult divide_i8(i8 a, i8 b)
{
    // DCResult result;
    dc_res_def(); // or this

    if (b == 0)
    {
        // dc_res_e(1, "Division by zero");
        dc_res_ea(1, "Division by zero, got='%d/%d'", a, b);
        return result;
    }

    dc_res_ok(i8, a / b);

    return result;
}

DCResult calculate_i8(i8 x, i8 y)
{
    // Trying the result
    dc_try(divide_i8(x, y));

    // result is ok
    dc_res_ok(i8, dc_res_as(i8) + 10);

    return result;
}

void handle_result(DCResult result)
{
    if (result.status == DC_RESULT_OK)
    {
        dc_log("Success: %d", dc_res_as(i8));
        return;
    }

    dc_log("Error: %s (code %d)", result.data.error.message,
           result.data.error.code);
}

int main()
{
    DCResult result1 = calculate_i8(10, 2);
    handle_result(result1);

    DCResult result2 = calculate_i8(10, 0);
    handle_result(result2);

    // Why freeing, messages of errors might be allocated
    // values also might be allocated, you can handle them all at once
    dc_result_free(&result1, NULL);
    dc_result_free(&result2, NULL);
}
