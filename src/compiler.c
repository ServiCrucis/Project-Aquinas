/*
 * compiler.c
 *
 *  Created on: Jul 22, 2019
 *      Author: AMDG
 */

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "compiler.h"
#include "debug.h"

void mdu_compile__handler(struct symbol** symbols, size_t offset, size_t position, size_t length) {
	char* errpos = malloc(offset + position + 1);
	if (!errpos) {
		mdu_debug_fatal(MDU_ALLOCATION_FAILURE, "[%s] failed to allocate memory for error string (required memory: %d bytes)", __func__, offset + position + 1);
	}
	memset(errpos, ' ', offset + position);
	mdu_debug_fatal(MDU_INCOMPLETE_RESULT, "[%s] unexpected symbol:\n\n\toffset:%d\n\tposition:%d\n%s\n%s\n", __func__, offset, position, mdu_cat_symbols(symbols, length));
}

struct cpl_result* mdu_compile(struct pattern* const pattern, struct symbol** const input, const size_t length) {
	struct cpl_result* result = &((struct cpl_result){ input, MDU_COMPLETE_RESULT });

	for (uint32_t i = 0; i < pattern->magnitude; i++) {
		result->symbols = mdu_match_symbol_subset(pattern, i, result->symbols, length, &mdu_compile__handler);
	}

	return result;
}

struct symbol** mdu_match_symbol_subset(/* const enum cardinality cardinality, */ struct pattern* const pattern, const uint32_t subset, struct symbol** const input, const size_t length, void (*unexpected_handler)(struct symbol** symbols, size_t start_offset, size_t next, size_t length)) {
	struct symbol** stack = calloc(length, sizeof(struct symbol*));
	if (!stack) {
		mdu_debug_fatal(MDU_ALLOCATION_FAILURE, "[%s] failed to allocate memory for symbol stack (required memory: %d bytes)\n", __func__, length * sizeof(struct symbol*));
	}
	size_t offset = 0;
	size_t next = 0;
	struct symbol symbol = *input[0];
	struct node node = *pattern->subsets[subset]->children[symbol.symbol_info->id];

	size_t i = 1;
	while(i < length) {
		// continuity
		bool continuity = symbol.symbol_info == node.symbol_info;
		if (continuity) {
			stack[next + offset] = &symbol;
			next++;
		} else { // discontinuity
			// convert contents of stack to symbol and push back onto stack
			struct symbol** new_symbol = malloc(next * sizeof(struct symbol*));
			if(!new_symbol) {
				mdu_debug_fatal(MDU_ALLOCATION_FAILURE, "[%s] failed to allocate memory for symbols (required memory: %d bytes)\n", __func__, next * sizeof(struct symbol*));
			}
			size_t slength = next;
			for (size_t j = 0; j < slength; j++) {
				new_symbol[j] = stack[offset + j];
			}

			next = 0;
			offset++;

			stack[offset + next] = &((struct symbol) { node.composite->symbol_info, new_symbol });
			next++;
			if (!node.parent) { // if start symbol
				goto end;
			} else {
				(*unexpected_handler)(stack, offset, next, length);
			}
		}
		

		end:
			symbol = (*input)[i];
			node = *node.children[symbol.symbol_info->id];
	}

	return stack;
}

char* mdu_symbol_to_string(struct symbol* const symbol) {
	struct symbol_info info = *symbol->symbol_info;
	char* string = NULL;
	size_t length = (info.length + 1) * sizeof(uint32_t);
	string = calloc(info.length + 1, sizeof(uint32_t));

	if (!string) {
		mdu_debug_fatal(MDU_ALLOCATION_FAILURE, "[%s] failed to allocate memory for string (required memory: %d bytes)\n", __func__, length);
	}

	if (!symbol->symbol_info->subset) {
		// constituents in this subset are not symbol pointers, but concrete information
		memcpy(string, symbol->symbols, length);
		string[length-1] = (uint32_t) '\0';
	} else {
		for (size_t i = 0; i < length; i+=sizeof(sizeof(uint32_t))) {
			((uint32_t*) string)[i] = symbol->symbols[i]->symbol_info->id;
		}
	}

	return string;
}

char* mdu_cat_symbols(struct symbol** const symbols, size_t length) {
	char* string = mdu_symbol_to_string(symbols[0]);

	for (size_t i = 1; i < length; i++) {
		string = strcat(string, mdu_symbol_to_string(symbols[i]));
	}

	return string;
}
