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
#include "permutation.h"

typedef enum c_command {
	// Opens a permutation and makes it the current context (isomorphic)
	BEGIN,
	// Closes the permutation in the current context sets the current context to the parent context (isomorphic)
	END,
	// Links one permutation to another creating a sequential continuity (new permutation) at the point of bondage (isomorphic)
	LINK,
} behavior;

// a permutation representing the current context
typedef struct context {
	// the super-context
	struct context *origin;
	// permutation pointer array as a stack
	permutation    **stack;
	// stack index
	size_t         si;
	// the length of the stack
	size_t         length;
	// the reference tree
	permutation    *reference;
	// the current input
	permutation    *current;
} context;

context c_begin(context local, permutation in);

context c_end(context local, permutation in);

context c_link(context local, permutation in);

#endif /* COMPILER_H_ */


