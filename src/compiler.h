/*
 * compiler.h
 *
 *  Created on: Jul 22, 2019
 *      Author: Andrew Thomas Porter (AMDG)
 */

#ifndef COMPILER_H_
#define COMPILER_H_

#include <stdint.h>
#include <stdbool.h>

#include "error.h"
#include "pattern.h"

typedef enum c_command {
	// Opens a pattern and makes it the current context (isomorphic)
	BEGIN,
	// Closes the pattern in the current context sets the current context to the parent context (isomorphic)
	END,
	// Links one pattern to another creating a sequential continuity (new pattern) at the point of bondage (isomorphic)
	LINK,
} behavior;

// a pattern representing the current context
typedef struct context {
	// the super-context
	struct context *origin;
	// pattern pointer array as a stack
	pattern **stack;
	// stack index
	size_t si;
	// the length of the stack
	size_t length;
	// the reference tree
	pattern *reference;
	// the current input
	pattern *current;
} context;

context c_begin(context local, pattern in);

context c_end(context local, pattern in);

context c_link(context local, pattern in);

#endif /* COMPILER_H_ */


