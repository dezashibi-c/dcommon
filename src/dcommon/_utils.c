// ***************************************************************************************
//    Project: dcommon -> https://github.com/dezashibi-c/dcommon
//    File: _utils.c
//    Date: 2024-09-13
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more
//     information about the licensing of this work. If you have any questions
//     or concerns, please feel free to contact me at the email address provided
//     above.
//    ATTRIBUTIONS:
//     dc_sprintf and dc_strdup are based on source codes from the book
//     "21st-Century C" by Ben Klemens
// ***************************************************************************************
// *  Description: private implementation file for definition of common helper
// *               functions
// *               DO NOT LINK TO THIS DIRECTLY
// ***************************************************************************************

#ifndef __DC_BYPASS_PRIVATE_PROTECTION
#error                                                                         \
    "You cannot link to this source (_utils.c) directly, please consider including dcommon.h"
#endif

#include "dcommon.h"

#if defined(DC_WINDOWS)
#include <Lmcons.h>
#include <windows.h>
#else
#include <pwd.h>
#include <unistd.h>
#endif

// ***************************************************************************************
// * STRINGS AND PATHS
// ***************************************************************************************

DCResultUsize dc_sprintf(string* str, string fmt, ...)
{
    dc_res_usize();

    if (!str)
    {
        dc_dbg_log("got NULL str");

        dc_res_ret_e(1, "got NULL str");
    }

    va_list argp;
    va_start(argp, fmt);

    char one_char[1];
    int len = vsnprintf(one_char, 1, fmt, argp);
    if (len < 1)
    {
        dc_dbg_log(
            "An encoding error occurred. Setting the input pointer to NULL.");
        *str = NULL;
        va_end(argp);

        dc_res_ret_e(
            5,
            "An encoding error occurred. Setting the input pointer to NULL.");
    }
    va_end(argp);

    *str = malloc(len + 1);
    if (!str)
    {
        dc_dbg_log("Couldn't allocate %i chars.", len + 1);

        dc_res_ret_e(1, "Memory allocation failed");
    }

    va_start(argp, fmt);
    vsnprintf(*str, len + 1, fmt, argp);
    va_end(argp);

    dc_res_ret_ok((usize)len);
}

DCResultUsize dc_sappend(string* str, const string fmt, ...)
{
    dc_res_usize();

    if (!str)
    {
        dc_dbg_log("got NULL str");

        dc_res_ret_e(1, "got NULL str");
    }

    va_list argp;
    va_start(argp, fmt);

    // Calculate the length of the formatted string
    char one_char[1];
    int len = vsnprintf(one_char, 1, fmt, argp);
    if (len < 0)
    {
        dc_dbg_log(
            "An encoding error occurred. Setting the input pointer to NULL.");
        *str = NULL;
        va_end(argp);

        dc_res_ret_e(
            5,
            "An encoding error occurred. Setting the input pointer to NULL.");
    }
    va_end(argp);

    // Calculate the current length of the existing string
    size_t current_len = *str ? strlen(*str) : 0;

    // Allocate memory for the new string (old length + new formatted part)
    string new_str = realloc(*str, current_len + len + 1);
    if (!new_str)
    {
        dc_dbg_log("Couldn't allocate %i chars.", len + 1);

        dc_res_ret_e(1, "Memory allocation failed");
    }

    // Update the string pointer
    *str = new_str;

    // Append the new formatted string to the existing string
    va_start(argp, fmt);
    vsnprintf(*str + current_len, len + 1, fmt, argp);
    va_end(argp);

    dc_res_ret_ok(current_len + len);
}

DCResultString dc_strdup(const string in)
{
    dc_res_string();

    if (!in)
    {
        dc_dbg_log("got NULL input str");

        dc_res_ret_e(1, "got NULL input str");
    }

    string out;

    dc_try_fail_temp(DCResultUsize, dc_sprintf(&out, "%s", in));

    dc_res_ret_ok(out);
}

DCResultVoid dc_normalize_path_to_posix(string path)
{
    dc_res_void();

    if (!path)
    {
        dc_dbg_log("got NULL path");

        dc_res_ret_e(1, "got NULL path");
    }

#if defined(DC_WINDOWS)
    for (string p = path; *p; ++p)
    {
        if (*p == '\\')
        {
            *p = '/';
        }
    }
#endif

    dc_res_ret();
}

DCResultString dc_replace_file_in_path(string path, const string file_name)
{
    dc_res_string();

    if (!path || !file_name)
    {
        dc_dbg_log("got NULL path or file_name");

        dc_res_ret_e(1, "got NULL path or file_name");
    }

    dc_try_fail_temp(DCResultVoid, dc_normalize_path_to_posix(path));
    const string last_sep = strrchr(path, '/');

    size_t dir_length = (last_sep != NULL) ? (last_sep - path + 1) : 0;

    size_t new_path_length = dir_length + strlen(file_name) + 1;
    string new_path = (string)malloc(new_path_length);

    if (new_path == NULL)
    {
        dc_dbg_log("Memory allocation failed");

        dc_res_ret_e(1, "Memory allocation failed");
    }

    if (dir_length > 0) strncpy(new_path, path, dir_length);

    strcpy(new_path + dir_length, file_name);

    dc_res_ret_ok(new_path);
}

string dc_get_home_dir_path()
{
#if defined(DC_WINDOWS)
    static char homeDir[MAX_PATH];
    if (GetEnvironmentVariable("USERPROFILE", homeDir, MAX_PATH))
    {
        return homeDir;
    }
    else
    {
        return NULL;
    }
#else
    return getenv("HOME");
#endif
}

string dc_get_username()
{
#if defined(DC_WINDOWS)
    static char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    if (GetUserName(username, &username_len))
    {
        return username;
    }
    else
    {
        return NULL;
    }
#else
    return getenv("USER");
#endif
}

string dc_get_os()
{
    string os = "unknown";

#ifdef DC_WINDOWS
    os = "windows";
#elif defined(DC_LINUX)
    os = "linux";
#elif defined(DC_ANDROID)
    os = "android";
#elif defined(DC_MACOS)
    os = "macos";
#elif defined(DC_UNIX)
    os = "unix";
#endif

    return os;
}

string dc_get_arch()
{
    string arch = "unknown";

#ifdef DC_WINDOWS_X64
    arch = "x64";
#elif defined(DC_WINDOWS_ARM64)
    arch = "arm64";
#elif defined(DC_WINDOWS_ARM)
    arch = "arm";
#elif defined(DC_WINDOWS_X86)
    arch = "x86";
#elif defined(DC_LINUX_X64)
    arch = "x64";
#elif defined(DC_LINUX_ARM64)
    arch = "arm64";
#elif defined(DC_LINUX_ARM)
    arch = "arm";
#elif defined(DC_LINUX_X86)
    arch = "x86";
#elif defined(DC_ANDROID_X64)
    arch = "x64";
#elif defined(DC_ANDROID_ARM64)
    arch = "arm64";
#elif defined(DC_ANDROID_ARM)
    arch = "arm";
#elif defined(DC_ANDROID_X86)
    arch = "x86";
#elif defined(DC_MACOS_X64)
    arch = "x64";
#elif defined(DC_MACOS_X86)
    arch = "x86";
#elif defined(DC_UNIX_X64)
    arch = "x64";
#elif defined(DC_UNIX_ARM64)
    arch = "arm64";
#elif defined(DC_UNIX_ARM)
    arch = "arm";
#elif defined(DC_UNIX_X86)
    arch = "x86";
#endif

    return arch;
}

// ***************************************************************************************
// * CLEANUP
// ***************************************************************************************

void __dc_handle_signal(int sig)
{
    switch (sig)
    {
        case SIGINT:
            dc_log("Caught SIGINT (Ctrl+C)");
            break;

        case SIGTERM:
            dc_log("Caught SIGTERM");
            break;

        case SIGSEGV:
            dc_log("Caught SIGSEGV (Segmentation Fault)");
            break;

        default:
            dc_log("Caught other signals: %d", sig);
            break;
    };

    if (sig != SIGSEGV)
    {
        DCResultVoid res = dc_perform_cleanup();
        dc_action_on(dc_res_is_err2(res), exit(dc_res_err_code2(res)), "%s",
                     dc_res_err_msg2(res));
    }

    exit(sig);
}

DCResultVoid __dc_perform_cleanup(DCCleanups* cleanups_arr)
{
    dc_res_void();

    dc_dbg_log_if(cleanups_arr->cap == 0 || cleanups_arr->count == 0,
                  "cleanups_arr is not initialized or has no "
                  "elements registered, exiting now...");

    if (cleanups_arr->cap == 0 || cleanups_arr->count == 0) dc_res_ret();

    dc_dbg_log("cleaning up '%" PRIuMAX "' elements", cleanups_arr->count);

    // run cleanup of each item
    dc_da_for(*cleanups_arr)
    {
        DCCleanupEntry* entry = dc_da_get_as(cleanups_arr, _idx, voidptr);

        dc_dbg_log("cleaning index: '%" PRIuMAX "', cleanup perform: %p", _idx,
                   (*entry).element);

        dc_try_fail(dc_cleanup_do(*entry));
    }

    // clean up the dc_cleanup itself
    dc_dbg_log("freeing cleanups dynamic array, current capacity: '%" PRIuMAX
               "', current "
               "count: '%" PRIuMAX "'",
               cleanups_arr->cap, cleanups_arr->count);

    dc_try_fail(dc_da_free(cleanups_arr));

    dc_dbg_log(
        "cleanups dynamic array has been freed, current capacity: '%" PRIuMAX
        "', current "
        "count: '%" PRIuMAX "'",
        cleanups_arr->cap, cleanups_arr->count);

    dc_result_free(&dc_cleanups_res);

    dc_dbg_log("cleanups result has been freed");

    dc_res_ret();
}

DCResultVoid dc_perform_cleanup()
{
    dc_dbg_log("performing global cleanups");

    return __dc_perform_cleanup(&dc_cleanups);
}

DCResultVoid __dc_cleanups_custom_push(DCCleanups* cleanup_arr, voidptr element,
                                       DCCleanupFn cleanup_fn)
{
    dc_res_void();

    if (!element || !cleanup_fn)
    {
        dc_dbg_log("got null element or cleanup_fn");

        dc_res_ret_e(1, "got null element or cleanup_fn");
    }

    __dc_cleanups_arr_init(*cleanup_arr, 10);

    DCCleanupEntry* item = malloc(sizeof(DCCleanupEntry));
    if (!item)
    {
        dc_dbg_log("Memory allocation failed");

        dc_res_ret_e(2, "Memory allocation failed");
    }

    dc_dbg_log("cleanup push: %p", element);

    item->element = element;
    item->cleanup_fn = cleanup_fn;

    return dc_da_push(cleanup_arr, dc_dva(voidptr, item));
}

DCResultVoid dc_free(voidptr variable)
{
    dc_res_void();

    if (!variable) dc_res_ret_e(1, "try to free NULL");

    free(variable);

    dc_res_ret();
}

// ***************************************************************************************
// * RESULT
// ***************************************************************************************

DCResultVoid dc_result_free(voidptr res_ptr)
{
    dc_res_void();

    if (!res_ptr) dc_res_ret_e(1, "got NULL result");

    DCResultVoid* result = (DCResultVoid*)res_ptr;


    if (dc_res_is_err2(*result) && result->data.e.allocated)
    {
        free(result->data.e.message);
    }

    result->data.e.message = "";

    dc_res_ret();
}
