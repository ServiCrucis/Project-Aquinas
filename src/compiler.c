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
#include "debug.h"
#include "memory.h"

void mdu_compile__handler(struct symbol **symbols, size_t position, size_t length) {
	char *errpos = m_get(position + 1);
	if (!errpos) {
		r_debug_fatalf(R_ALLOCATION_FAILURE,
		               "[%s] failed to allocate memory for error string (required memory: %d bytes)",
		               __func__,
		               position + 1);
	}
	errpos[length - 1] = '\0';
	memset(errpos, ' ', position - 1);
	r_debug_fatalf(R_INCOMPLETE_RESULT,
	               "[%s] unexpected symbol:\n\n\tposition:%d\n%s\n%s\n%s%s\n",
	               __func__,
	               position,
	               mdu_cat_symbols(symbols, length),
	               errpos,
	               "|");
}

struct symbol *mdu_match_symbol_subset(struct node *(*pattern)(struct node *origin, struct symbol *input), struct symbol *input) {
	struct symbol **stack = m_get(input->length * sizeof(struct symbol *));
	if (!stack) {
		r_debug_fatalf(R_ALLOCATION_FAILURE,
		               "[%s] failed to allocate memory for stack (required memory: %d bytes)",
		               __func__,
		               input->length * sizeof(struct symbol *));
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
			struct symbol **symbols = m_get(len * sizeof(struct symbol *));
			if (!symbols) {
				r_debug_fatalf(R_ALLOCATION_FAILURE,
				               "[%s] failed to allocate memory for new_symbol (required memory: %d bytes)",
				               __func__,
				               len * sizeof(struct symbol *));
			}
			memcpy(symbols, stack, len);
			struct symbol *new_symbol = mdu_wrap(symbols, len, input->dimensions);
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
		r_debug_fatalf(R_ALLOCATION_FAILURE,
		               "[%s] failed to shrink stack size to %d bytes from %d bytes",
		               __func__,
		               offset * sizeof(struct symbol *),
		               input->length * sizeof(struct symbol *));
	}
	return mdu_wrap(stack, next + offset + 1, input->dimensions);
}

struct symbol *mdu_wrap(struct symbol **symbols, size_t length, size_t dimensions) {
	struct symbol *symbol = m_get(sizeof(struct symbol));
	if (!symbol) {
		r_debug_fatalf(R_ALLOCATION_FAILURE,
		               "[%s] failed to allocate memory for symbol contents (required memory: %d bytes)",
		               __func__,
		               sizeof(struct symbol));
	}
	symbol->y = symbols;
	symbol->length = length;
	symbol->dimensions = dimensions + 1;
	return symbol;
}

struct symbol *mdu_input(void *y, size_t length) {
	struct symbol *symbol = m_get(sizeof(struct symbol));
	if (!symbol) {
		r_debug_fatalf(R_ALLOCATION_FAILURE,
		               "[%s] failed to allocate memory for symbol contents (required memory: %d bytes)",
		               __func__,
		               sizeof(struct symbol));
	}
	symbol->y = (struct symbol **) y;
	symbol->length = length;
	symbol->dimensions = 0;
	return symbol;
}

struct symbol *mdu_str_input(char *y, size_t length) {
	struct symbol *symbol = m_get(sizeof(struct symbol));
	symbol->y = m_get(length * sizeof(struct symbol *));
	if (!symbol->y) {
		r_debug_fatalf(R_ALLOCATION_FAILURE,
		               "[%s] failed to allocate memory for symbol contents (required memory: %d bytes)",
		               __func__,
		               length * sizeof(struct symbol *));
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

