/*
 ============================================================================
 Name        : Modulus.c
 Author      : Andrew Thomas Porter (AMDG)
 Version     : 0.0.1
 Copyright   : License
 Description : Modulus language compiler
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "debug.h"
#include "compiler.h"


// the ab language with productions S -> aSb and S -> ab
struct node* mdu_ab_lang(struct node* origin, struct symbol* input) {
	static struct node result;
	// principles:
	// a -> a : true;
	// b -> b : true;
	// a -> b : true;
	// b -> a : false
	char x = (char)(intptr_t) origin->x->y;
	char y = (char)(intptr_t) input->y;

	if ((x == 'a' && y == 'a') || (x == 'b' && y == 'b')) { // a -> a or b -> b
		result.origin = origin;
		result.x = input;
		return &result;
	} else {
		if ((x == 'a' && y == 'b')) { // a -> b
			result.origin = origin;
			result.x = input;
			return &result;
		} else { // b -> a or erroneous case
			return NULL;
		}
	}
}

int main(int argc, char* argv[]) {
	mdu_debug_info("Running...\n");
	//if (argc > 0) {
		//char* value = argv[0];
		char* value = "aaaaabbbbb";
		size_t length = strlen(value);

		struct symbol* input = mdu_str_input(value, length);
		struct symbol* result = mdu_match_symbol_subset(&mdu_ab_lang, input);
		mdu_debug_infof(MDU_SUCCESS, "[%s] number of symbols in input: %d\n", __func__, result->length);
	//} else {
	//	puts("No input given. Exiting...\n");
	//}
	return 0;
}
