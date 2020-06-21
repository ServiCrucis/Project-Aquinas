/*
 * # modulus.h
 * ## Created:
 * August 19th, A.D. 2019
 * ## Author:
 * Andrew Thomas Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2019 Christi Crucifixi, LLC. All rights reserved.
 */
#ifndef PROJECT_AQUINAS_DEBUG_H
#define PROJECT_AQUINAS_DEBUG_H

#include <stdlib.h>
#include <stdbool.h>

// a macro to be used by programs to determine whether or not the build is debug (default: false
#ifndef R_DEBUG
	#define R_DEBUG false
#endif
#ifndef R_DEBUG_LOGGING
	#define R_DEBUG_LOGGING false
#endif

enum result_code {
	// R for Result
	R_SUCCESS = EXIT_SUCCESS,
	R_FAILURE = EXIT_FAILURE,
	R_ALLOCATION_SUCCESS,
	R_ALLOCATION_FAILURE,
	R_INITIALIZATION_SUCCESS,
	R_INITIALIZATION_FAILURE,
	R_STACK_OVERFLOW,
	R_STACK_UNDERFLOW,
	R_BUFFER_OVERFLOW,
	R_BUFFER_UNDERFLOW,
	R_COMPLETE_RESULT,
	R_INCOMPLETE_RESULT,
	R_INDETERMINATE_RESULT,
	R_ASSERTION_SUCCESS,
	R_ASSERTION_FAILURE,
	R_NULL_POINTER,
	R_ILLEGAL_VALUE,
	R_STATUS,
};

void r_info(char const *information, ...);

void r_infof(enum result_code const code, char const *fn_name, char const *information, ...);

void r_warnf(enum result_code const code, char const *fn_name, char const *warning, ...);

void r_fatalf(enum result_code const code, char const *fn_name, char const *error_message, ...);

#endif /* PROJECT_AQUINAS_DEBUG_H */
