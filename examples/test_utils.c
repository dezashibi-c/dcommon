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

#define DCOMMON_IMPL
#include "../src/dcommon/dcommon.h"

int main(int argc, string argv[])
{
    (void)argc;

    string s;
    dc_sprintf(&s, "hello, %s.", "-Reader-");
    printf("%s\n", s);
    free(s);

    dc_sprintf(&s, "%c", '\0');
    printf("blank string: [%s]\n", s);
    free(s);

    int i = 0;
    dc_sprintf(&s, "%i", i++);
    printf("Zero: %s\n", s);
    free(s);

    printf("exec path: %s\n", argv[0]);

    s = dc_replace_file_in_path(argv[0], "my_config.ini");
    printf("config path close to exec: " DC_FG_LGREEN "%s" DC_COLOR_RESET "\n",
           s);
    free(s);

    puts("This " dc_colorize_fg(LRED, "color") " is red!");

    const char* homeDir = dc_get_home_dir_path();
    if (homeDir != NULL)
    {
        printf("Home directory: %s\n", homeDir);
    }
    else
    {
        printf("Failed to get home directory.\n");
    }

    const char* username = dc_get_username();
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
}
