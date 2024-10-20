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

DCResI8 divide_i8(i8 a, i8 b)
{
    // Initializes a result for i8 type value and sets its status to OK by
    // default (creates __dc_res variable)
    DC_RES_i8();

    // Test for possible error (division by zero)
    if (b == 0)
    {
        // This version doesn't have
        // allocated string
        // dc_ret_e(1, "Division by zero");

        // This version does have allocated string
        dc_ret_ea(1, "Division by zero, got='%d/%d'", a, b);
    }

    // Sets ok status, sets value to the a/b and return the __dc_res
    dc_ret_ok(a / b);
}

DCResI8 calculate_i8(i8 x, i8 y)
{
    DC_RES_i8();

    // Trying the result
    dc_try_fail(divide_i8(x, y));

    // result is ok
    dc_ret_ok(dc_val() + 10);
}

void handle_result(DCResI8 result)
{
    if (dc_is_ok2(result))
    {
        dc_log("Success: %d", dc_val2(result));
        return;
    }

    dc_log("Error: %s (code %d)", dc_err_msg2(result), dc_err_code2(result));
}

int main()
{
    DC_RES_void();

    DCResI8 result1 = calculate_i8(10, 2);
    handle_result(result1);

    DCResI8 result2 = calculate_i8(10, 0);
    handle_result(result2);

    DCResI8 res2_cpy;

    dc_err_cpy2(res2_cpy, result2);
    handle_result(res2_cpy);

    // Why freeing, messages of errors might be allocated
    // values also might be allocated, you can handle them all at once
    dc_try(dc_result_free(&result1));
    dc_action_on(dc_is_err(), return dc_err_code(), "%s", dc_err_msg());

    dc_try(dc_result_free(&result2));
    dc_action_on(dc_is_err(), return dc_err_code(), "%s", dc_err_msg());

    return 0;
}
