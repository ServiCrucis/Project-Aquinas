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
#include "pattern_trie.h"

typedef enum c_command {
	// Opens a pattern_trie and makes it the current context (isomorphic)
	BEGIN,
	// Closes the pattern_trie in the current context sets the current context to the parent context (isomorphic)
	END,
	// Links one pattern_trie to another creating a sequential continuity (new pattern_trie) at the point of bondage (isomorphic)
	LINK,
} behavior;

// a pattern_trie representing the current context
typedef struct context {
	// the super-context
	struct context *origin;
	// pattern_trie pointer array as a stack
	pattern_trie   **stack;
	// stack index
	size_t         si;
	// the length of the stack
	size_t         length;
	// the reference tree
	pattern_trie   *reference;
	// the current input
	pattern_trie   *current;
} context;

context c_begin(context local, pattern_trie in);

context c_end(context local, pattern_trie in);

context c_link(context local, pattern_trie in);

#endif /* COMPILER_H_ */


