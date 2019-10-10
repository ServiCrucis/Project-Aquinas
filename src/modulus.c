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
	static struct node result = { NULL, NULL};
	// principles:
	// a -> a : true;
	// b -> b : true;
	// a -> b : true;
	// b -> a : false
	char x = *((char**) origin->x->y)[0];
	char y = *((char**) input->y)[0];

	if (x == y) { // a -> a or b -> b
		result.origin = origin;
		result.x = input;
		return &result;
	} else {
		if ((x == 'a' && y == 'b')) { // a -> b

			return &result;
		} else { // b -> c or erroneous case
			return NULL;
		}
	}
}

int main(int argc, char* argv[]) {
	printf("Running...");
	//if (argc > 0) {
		//char* value = argv[0];
		char* value = "ab";
		size_t length = strlen(value);

		struct node* origin = calloc(1, sizeof(struct node));
		if (!origin) {
			mdu_debug_fatal(MDU_ALLOCATION_FAILURE, "[%s] failed to allocate memory for origin (required memory: %d bytes)", __func__, sizeof(struct node));
		}
		struct symbol* input = mdu_str_input(value, length);
		origin->origin = origin;
		origin->x = input;
		struct symbol* result = mdu_match_symbol_subset(origin, &mdu_ab_lang, input);
		mdu_debug_info(MDU_SUCCESS, "[%s] number of symbols in input: %d\n", __func__, result->length);
	//} else {
	//	puts("No input given. Exiting...\n");
	//}
	return 0;
}
