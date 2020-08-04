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

#include "state.h"
#include "pattern_tree.h"

typedef enum c_command {
	// Opens a pattern_tree and makes it the current context (isomorphic)
	BEGIN,
	// Closes the pattern_tree in the current context sets the current context to the parent context (isomorphic)
	END,
	// Links one pattern_tree to another creating a sequential continuity (new pattern_tree) at the point of bondage (isomorphic)
	LINK,
} behavior;

// a pattern_tree representing the current context
typedef struct context {
	// the super-context
	struct context *origin;
	// pattern_tree pointer array as a stack
	tree_node   **stack;
	// stack index
	size_t         si;
	// the length of the stack
	size_t         length;
	// the reference tree
	tree_node   *reference;
	// the current input
	tree_node   *current;
} context;

context c_begin(context local, tree_node in);

context c_end(context local, tree_node in);

context c_link(context local, tree_node in);

#endif /* COMPILER_H_ */


