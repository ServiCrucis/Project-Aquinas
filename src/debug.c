/*
 * debug.c
 *
 *  Created on: Sep 23, 2019
 *      Author: Andrew Thomas Porter (AMDG)
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "debug.h"


static char** mdu_result_messages = (char *[])
{
		"MDU_SUCCESS",
		"MDU_FAILURE",
		"MDU_ALLOCATION_SUCCESS",
		"MDU_ALLOCATION_FAILURE",
		"MDU_INITIALIZATION_SUCCESS",
		"MDU_INITIALIZATION_FAILURE",
		"MDU_STACK_OVERFLOW",
		"MDU_STACK_UNDERFLOW",
		"MDU_BUFFER_OVERFLOW",
		"MDU_BUFFER_UNDERFLOW",
		"MDU_COMPLETE_RESULT",
		"MDU_INCOMPLETE_RESULT"
};

void mdu_debug_info(char const *information, ...) {
	fputs("[info][", stdout);
	fputs(mdu_result_messages[MDU_SUCCESS], stdout);
	fputc(']', stdout);
	fputc(' ', stdout);
	va_list objects;
	va_start(objects, information);
	vprintf(information, objects);
	va_end(objects);
}

void mdu_debug_infof(enum mdu_result_code const code, char const *information, ...) {
	fputs("[info][", stdout);
	fputs(mdu_result_messages[code], stdout);
	fputc(']', stdout);
	va_list objects;
	va_start(objects, information);
	vprintf(information, objects);
	va_end(objects);
}

void mdu_debug_warnf(enum mdu_result_code const code, char const *warning, ...) {
	fputs("[warning][", stdout);
	fputs(mdu_result_messages[code], stdout);
	fputc(']', stdout);
	va_list objects;
	va_start(objects, warning);
	vprintf(warning, objects);
	va_end(objects);
}

void mdu_debug_fatalf(enum mdu_result_code const code, char const *error_message, ...) {
	fputs("[fatal][", stdout);
	fputs(mdu_result_messages[code], stdout);
	fputc(']', stdout);
	va_list objects;
	va_start(objects, error_message);
	vprintf(error_message, objects);
	va_end(objects);
	exit(code);
}

