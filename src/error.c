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
#include "error.h"


static char *cth_result_messages[] =
		{
				[R_SUCCESS] = "SUCCESS",
				[R_FAILURE] = "FAILURE",
				[R_ALLOCATION_SUCCESS] = "ALLOCATION_SUCCESS",
				[R_ALLOCATION_FAILURE] = "ALLOCATION_FAILURE",
				[R_INITIALIZATION_SUCCESS] = "INITIALIZATION_SUCCESS",
				[R_INITIALIZATION_FAILURE] = "INITIALIZATION_FAILURE",
				[R_STACK_OVERFLOW] = "STACK_OVERFLOW",
				[R_STACK_UNDERFLOW] = "STACK_UNDERFLOW",
				[R_BUFFER_OVERFLOW] = "BUFFER_OVERFLOW",
				[R_BUFFER_UNDERFLOW] = "BUFFER_UNDERFLOW",
				[R_COMPLETE_RESULT] = "COMPLETE_RESULT",
				[R_INCOMPLETE_RESULT] = "INCOMPLETE_RESULT",
				[R_INDETERMINATE_RESULT] = "INDETERMINATE_RESULT",
				[R_ASSERTION_SUCCESS] = "ASSERTION_SUCCESS",
				[R_ASSERTION_FAILURE] = "ASSERTION_FAILURE",
				[R_NULL_POINTER] = "NULL_POINTER",
				[R_ILLEGAL_VALUE] = "ILLEGAL_VALUE",
				[R_STATUS] = "STATUS"
		};

void r_info(char const *information, ...) {
	fputs("[info]", stdout);
	fputc(' ', stdout);
	va_list objects;
	va_start(objects, information);
	vprintf(information, objects);
	va_end(objects);
}

void r_infof(enum result_code const code, char const *fn_name, char const *information, ...) {
	fputs("[info][", stdout);
	fputs(cth_result_messages[code], stdout);
	fputs("][", stdout);
	fputs(fn_name, stdout);
	fputs("] ", stdout);
	va_list objects;
	va_start(objects, information);
	vprintf(information, objects);
	va_end(objects);
}

void r_warnf(enum result_code const code, char const *fn_name, char const *warning, ...) {
	fputs("[warning][", stdout);
	fputs(cth_result_messages[code], stdout);
	fputs("][", stdout);
	fputs(fn_name, stdout);
	fputs("] ", stdout);
	va_list objects;
	va_start(objects, warning);
	vprintf(warning, objects);
	va_end(objects);
}

void r_fatalf(enum result_code const code, char const *fn_name, char const *error_message, ...) {
	fputs("[fatal][", stderr);
	fputs(cth_result_messages[code], stderr);
	fputs("][", stderr);
	fputs(fn_name, stderr);
	fputs("] ", stderr);
	va_list objects;
	va_start(objects, error_message);
	vfprintf(stderr, error_message, objects);
	va_end(objects);
	exit(code);
}

