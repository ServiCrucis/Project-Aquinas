/*
 * compiler.c
 *
 *  Created on: Jul 22, 2019
 *      Author: Andrew Thomas Porter (AMDG)
 */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "compiler.h"
#include "error.h"
#include "memory.h"

// error handler
void c_compile__handler(struct symbol **symbols, size_t position, size_t length) {
	char *errpos = malloc(position + 1);
	if (!errpos) {
		r_debug_fatalf(R_ALLOCATION_FAILURE,
		               "[%s] failed to allocate memory for error string (required memory: %d bytes)",
		               __func__,
		               position + 1);
	}
	errpos[length - 1] = '\0';
	memset(errpos, ' ', position - 1);
	r_debug_fatalf(R_INCOMPLETE_RESULT, __func__, "[%s] unexpected symbol:\n\n\tposition:%d\n%s\n%s\n%s%s\n", position, mdu_cat_symbols(symbols, length), errpos, "|");
}

struct symbol *passthrough(struct symbol *const symbol) {
	return symbol;
}

struct symbol *c_match(struct node *(*pattern)(struct node *origin, struct symbol *input), struct symbol *input) {
	struct symbol **stack = malloc(input->length * sizeof(struct symbol *));
	if (!stack) {
		r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "[%s] failed to allocate memory for stack (required memory: %d bytes)", input->length * sizeof(struct symbol *));
	}
	// stack variables
	size_t offset = 0;
	size_t next = 0;

	struct symbol *symbol = input->y[0];
	struct node *node = &((struct node) { NULL, symbol });
	node->origin = node;

	for (size_t i = 1; i < input->length; i++) {
		if (node) { // continuity sustained
			stack[offset + next] = symbol;
			next++;
		} else { // continuity broken
			// create new symbol from contents of stack
			size_t len = (1 + next + offset);
			struct symbol **symbols = malloc(len * sizeof(struct symbol *));
			if (!symbols) {
				r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "[%s] failed to allocate memory for new_symbol (required memory: %d bytes)", len * sizeof(struct symbol *));
			}
			memcpy(symbols, stack, len);
			struct symbol *new_symbol = c_wrap(symbols, len, input->dimensions);
			// push new symbol onto stack
			stack[offset] = new_symbol;
			// increment stack offset
			offset++;
			// reset stack position
			next = 0;
		}

		symbol = input->y[i];
		node = (*pattern)(node, symbol);
	}

	stack = realloc(stack, offset * sizeof(struct symbol *));
	if (!stack) {
		r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "[%s] failed to shrink stack size to %d bytes from %d bytes", offset * sizeof(struct symbol *), input->length * sizeof(struct symbol *));
	}
	return c_wrap(stack, next + offset + 1, input->dimensions);
}

struct symbol *c_transform(struct symbol *(*transform)(struct symbol *), struct symbol *input) {

}

struct symbol *c_match_transform(struct node *(*pattern)(struct node *origin, struct symbol *input), struct symbol *(*transform)(struct symbol *), struct symbol *input) {

}

struct symbol *c_wrap(struct symbol **symbols, size_t length, size_t dimensions) {
	struct symbol *symbol = malloc(sizeof(struct symbol));
	if (!symbol) {
		r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "[%s] failed to allocate memory for symbol contents (required memory: %d bytes)", sizeof(struct symbol));
	}
	symbol->y = symbols;
	symbol->length = length;
	symbol->dimensions = dimensions + 1;
	return symbol;
}

struct symbol *mdu_input(void *y, size_t length) {
	struct symbol *symbol = malloc(sizeof(struct symbol));
	if (!symbol) {
		r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "[%s] failed to allocate memory for symbol contents (required memory: %d bytes)", sizeof(struct symbol));
	}
	symbol->y = (struct symbol **) y;
	symbol->length = length;
	symbol->dimensions = 0;
	return symbol;
}

struct symbol *mdu_str_input(char *y, size_t length) {
	struct symbol *symbol = malloc(sizeof(struct symbol));
	symbol->y = malloc(length * sizeof(struct symbol *));
	if (!symbol->y) {
		r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "[%s] failed to allocate memory for symbol contents (required memory: %d bytes)", length * sizeof(struct symbol *));
	}
	for (size_t i = 0; i < length; i++) {
		symbol->y[i] = mdu_input((void *) (intptr_t) y[i], 1);
	}
	symbol->length = length;
	symbol->dimensions = 1;
	return symbol;
}

char *mdu_symbol_to_string(struct symbol *const symbol) {
}

char *mdu_cat_symbols(struct symbol **const symbols, size_t length) {
}

