// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: test_utils.h
//    Date: 2024-09-13
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

#define DC_DEBUG
#define DCOMMON_IMPL
#include "../src/dcommon/dcommon.h"

int main(int argc, string argv[])
{
    (void)argc;

    string s;
    DCResUsize res = dc_sprintf(&s, "hello, %s.", "-Reader-");
    dc_action_on(dc_res_is_err2(res), return dc_res_err_code2(res), "%s", dc_res_err_msg2(res));

    printf("%s\n", s);
    free(s);

    res = dc_sprintf(&s, "%c", '\0');
    dc_action_on(dc_res_is_err2(res), return dc_res_err_code2(res), "%s", dc_res_err_msg2(res));

    printf("blank string: [%s]\n", s);
    free(s);

    int i = 0;
    res = dc_sprintf(&s, "%i", i++);
    dc_action_on(dc_res_is_err2(res), return dc_res_err_code2(res), "%s", dc_res_err_msg2(res));

    printf("Zero: %s\n", s);
    free(s);

    string my_str = NULL;

    res = dc_sappend(&my_str, "Hello");
    dc_action_on(dc_res_is_err2(res), return dc_res_err_code2(res), "%s", dc_res_err_msg2(res));

    res = dc_sappend(&my_str, ", World!");
    dc_action_on(dc_res_is_err2(res), return dc_res_err_code2(res), "%s", dc_res_err_msg2(res));

    printf("%s\n", my_str);
    free(my_str);

    printf("exec path: %s\n", argv[0]);

    DCResString s_res = dc_replace_file_in_path(argv[0], "my_config.ini");
    dc_action_on(dc_res_is_err2(s_res), return dc_res_err_code2(s_res), "%s", dc_res_err_msg2(s_res));

    s = dc_res_val2(s_res);

    printf("config path close to exec: " DC_FG_LGREEN "%s" DC_COLOR_RESET "\n", s);
    free(s);

    puts("This " dc_colorize_fg(LRED, "color") " is red!");

    const string homeDir = dc_get_home_dir_path();
    if (homeDir != NULL)
    {
        printf("Home directory: %s\n", homeDir);
    }
    else
    {
        printf("Failed to get home directory.\n");
    }

    const string username = dc_get_username();
    if (username != NULL)
    {
        printf("Username: %s\n", username);
    }
    else
    {
        printf("Failed to retrieve username.\n");
    }

    dc_log("Some logging information: running 'ls %s'", argv[0]);
    int out;
    dc_system(out, "ls %s", argv[0]);
    dc_log("running command returned: %d", out);

    dc_dbg_log_if(out == 0, "Operation was successful: %d", out);
    dc_dbg_log_if(out != 0, "Operation was not successful: %d", out);

    dc_log("running on: %s, %s", dc_get_os(), dc_get_arch());
}
