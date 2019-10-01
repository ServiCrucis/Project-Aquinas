/*
 * modulus.h
 *
 *  Created on: Aug 19, 2019
 *      Author: Andrew Porter (AMDG)
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdlib.h>

#ifndef MDU_DEBUG
#define MDU_DEBUG
#endif

enum mdu_result_code {
	MDU_SUCCESS = EXIT_SUCCESS,
	MDU_FAILURE = EXIT_FAILURE,
	MDU_ALLOCATION_SUCCESS,
	MDU_ALLOCATION_FAILURE,
	MDU_INITIALIZATION_SUCCESS,
	MDU_INITIALIZATION_FAILURE,
	MDU_STACK_OVERFLOW,
	MDU_STACK_UNDERFLOW,
	MDU_BUFFER_OVERFLOW,
	MDU_BUFFER_UNDERFLOW,
	MDU_COMPLETE_RESULT,
	MDU_INCOMPLETE_RESULT
};

void mdu_debug_info(const enum mdu_result_code code, const char* information, ...);

void mdu_debug_warn(const enum mdu_result_code code, const char* warning, ...);

void mdu_debug_fatal(const enum mdu_result_code code, const char* error_message, ...);

#endif /* DEBUG_H_ */
