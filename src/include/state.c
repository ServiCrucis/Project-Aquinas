/*
 * # debug.c
 * ## Created:
 * September 23rd, A.D. 2019
 * ## Author:
 * Andrew Thomas Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2019 Christi Crucifixi, LLC. All rights reserved.
 */
#include <stdio.h>
#include <stdarg.h>
#include "state.h"


static char *aqu_result_messages[] =
        {
                [R_SUCCESS] = "SUCCESS",
                [R_FAILURE] = "FAILURE",
        };

void info(char const *information, ...) {
    fputs("[info]", stdout);
    fputc('[', stdout);
    fputs(_global_context, stdout);
    fputs("] ", stdout);
    va_list objects;
    va_start(objects, information);
    vprintf(information, objects);
    va_end(objects);
}

void infof(enum result_code const code, char const *fn_name, char const *information, ...) {
    fputs("[info][", stdout);
    fputs(aqu_result_messages[code], stdout);
    fputs("][", stdout);
    fputs(_global_context, stdout);
    fputs("][", stdout);
    fputs(fn_name, stdout);
    fputs("] ", stdout);
    va_list objects;
    va_start(objects, information);
    vprintf(information, objects);
    va_end(objects);
}

void warnf(enum result_code const code, char const *fn_name, char const *warning, ...) {
    fputs("[warning][", stdout);
    fputs(aqu_result_messages[code], stdout);
    fputs("][", stdout);
    fputs(_global_context, stdout);
    fputs("][", stdout);
    fputs(fn_name, stdout);
    fputs("] ", stdout);
    va_list objects;
    va_start(objects, warning);
    vprintf(warning, objects);
    va_end(objects);
}

void fatalf(char const *fn_name, char const *error_message, ...) {
    fputs("[fatal][", stderr);
    fputs(_global_context, stderr);
    fputs("][", stderr);
    fputs(fn_name, stderr);
    fputs("] ", stderr);
    va_list objects;
    va_start(objects, error_message);
    vfprintf(stderr, error_message, objects);
    va_end(objects);
    exit(R_FAILURE);
}

