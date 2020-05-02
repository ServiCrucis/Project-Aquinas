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


static char **cth_result_messages = (char *[])
		{
				"SUCCESS",
				"FAILURE",
				"ALLOCATION_SUCCESS",
				"ALLOCATION_FAILURE",
				"INITIALIZATION_SUCCESS",
				"INITIALIZATION_FAILURE",
				"STACK_OVERFLOW",
				"STACK_UNDERFLOW",
				"BUFFER_OVERFLOW",
				"BUFFER_UNDERFLOW",
				"COMPLETE_RESULT",
				"INCOMPLETE_RESULT",
				"INDETERMINATE_RESULT",
				"ASSERTION_SUCCESS",
				"ASSERTION_FAILURE",
				"NULL_POINTER",
				"ILLEGAL_VALUE",
				"STATUS"
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

