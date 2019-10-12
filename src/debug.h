/*
 * modulus.h
 *
 *  Created on: Aug 19, 2019
 *      Author: Andrew Thomas Porter (AMDG)
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdlib.h>

#ifndef MDU_DEBUG
#define MDU_DEBUG
#endif

enum mdu_result_code {
	MDU_SUCCESS,
	MDU_FAILURE,
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

void mdu_debug_info(char const *information, ...);

void mdu_debug_infof(enum mdu_result_code const code, char const *information, ...);

void mdu_debug_warnf(enum mdu_result_code const code, char const *warning, ...);

void mdu_debug_fatalf(enum mdu_result_code const code, char const *error_message, ...);

#endif /* DEBUG_H_ */
