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

struct symbol {
	// either struct symbol ** or void **
	union {
		struct symbol **y;
		void **value;
	};
	// number of pointers
	size_t length;
	// how deep the nesting is, or how many times I need to dereference y to get a real value.
	size_t dimensions;
};

struct node {
	// the origin of x
	struct node *origin;
	// the expected x
	struct symbol *x;
};

struct symbol_context {
	struct symbol **bottom;
	struct symbol **top;
};

struct symbol *c_match(struct node *(*pattern)(struct node *origin, struct symbol *input), struct symbol *input);

struct symbol *c_wrap(struct symbol **symbols, size_t length, size_t dimensions);

struct symbol *mdu_input(void *y, size_t length);

struct symbol *mdu_str_input(char *y, size_t length);

char *mdu_symbol_to_string(struct symbol *const symbol);

char *mdu_cat_symbols(struct symbol **const symbols, size_t length);

#endif /* COMPILER_H_ */


