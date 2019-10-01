/*
 * compiler.h
 *
 *  Created on: Jul 22, 2019
 *      Author: Andrew Porter (AMDG)
 */

#ifndef COMPILER_H_
#define COMPILER_H_

#include <stdint.h>
#include <stdbool.h>

#include "debug.h"

struct symbol_info {
	// the node id of this symbol
	uint32_t id;
	// the subset of this symbol
	uint32_t subset;
	// the highest subset that this symbol belongs to
	//uint32_t max_subset;
	// the length of this symbol (for composites)
	size_t length;
};

struct symbol {
	struct symbol_info* symbol_info;
	struct symbol** symbols;
};

struct node {
	struct node* parent;
	struct node** children;
	struct node* composite;
	struct symbol_info* symbol_info;
};

struct pattern {
	struct node** subsets;
	// number of subsets
	uint32_t magnitude;
};

struct cpl_result {
	struct symbol** symbols;
	enum mdu_result_code code;
};

/*
enum cardinality {
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3,

	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};
*/

struct cpl_result* mdu_compile(struct pattern* const pattern, struct symbol** const input, const size_t length);

/*
 * function mdu_match_symbol_subset:
 *
 * A total Turing machine algorithm which matches a given input against a given pattern,
 * and accepts a symbol if it matches that pattern, or rejects the symbol if it does not
 * match the pattern.
 *
 */
struct symbol** mdu_match_symbol_subset(/* enum cardinality const cardinality, */ struct pattern* const pattern, const uint32_t subset, struct symbol** const input, const size_t length, void (*unexpected_handler)(struct symbol** symbols, size_t start_offset, size_t next, size_t length));

char* mdu_symbol_to_string(struct symbol* const symbol);

char* mdu_cat_symbols(struct symbol** const symbols, size_t length);

#endif /* COMPILER_H_ */


