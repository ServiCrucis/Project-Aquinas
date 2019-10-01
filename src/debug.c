/*
 * debug.c
 *
 *  Created on: Sep 23, 2019
 *      Author: Andrew Porter (AMDG)
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

void mdu_debug_info(const enum mdu_result_code code, const char *information, ...) {
	char* print = "[info]";
	print = strcat(print, information);
	va_list objects;
	va_start(objects, information);
	printf(print, mdu_result_messages[code], objects);
	va_end(objects);
}

void mdu_debug_warn(const enum mdu_result_code code, const char *warning, ...) {
	char* print = "[warn]";
	print = strcat(print, warning);
	va_list objects;
	va_start(objects, warning);
	printf(print, mdu_result_messages[code], objects);
	va_end(objects);
}

void mdu_debug_fatal(const enum mdu_result_code code, const char *error_message, ...) {
	char* print = "[fatal]";
	print = strcat(print, error_message);
	va_list objects;
	va_start(objects, error_message);
	printf(print, mdu_result_messages[code], objects);
	va_end(objects);
	exit(code);
}

