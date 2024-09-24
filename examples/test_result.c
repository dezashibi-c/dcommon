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

DCResultI8 divide_i8(i8 a, i8 b)
{
    // DCResult result;
    dc_res_i8(); // or this

    if (b == 0)
    {
        // dc_res_ret_e(1, "Division by zero");
        dc_res_ret_ea(1, "Division by zero, got='%d/%d'", a, b);
    }

    dc_res_ret_ok(a / b);
}

DCResultI8 calculate_i8(i8 x, i8 y)
{
    dc_res_i8();

    // Trying the result
    dc_try_fail(divide_i8(x, y));

    // result is ok
    dc_res_ret_ok(dc_res_val() + 10);
}

void handle_result(DCResultI8 result)
{
    if (result.status == DC_RESULT_OK)
    {
        dc_log("Success: %d", dc_res_val2(result));
        return;
    }

    dc_log("Error: %s (code %d)", dc_res_err_msg2(result),
           dc_res_err_code2(result));
}

int main()
{
    dc_res_void();

    DCResultI8 result1 = calculate_i8(10, 2);
    handle_result(result1);

    DCResultI8 result2 = calculate_i8(10, 0);
    handle_result(result2);

    // Why freeing, messages of errors might be allocated
    // values also might be allocated, you can handle them all at once
    dc_try(dc_result_free(&result1));
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s",
                 dc_res_err_msg());

    dc_try(dc_result_free(&result2));
    dc_action_on(dc_res_is_err(), return dc_res_err_code(), "%s",
                 dc_res_err_msg());

    return 0;
}
