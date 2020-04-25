/*
 ============================================================================
 Name        : Modulus.c
 Author      : Andrew Thomas Porter (AMDG)
 Version     : 1.2.1
 Copyright   : See LICENSE.txt
 Description : Catholicus language compiler
 ============================================================================
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// make other libraries use our memory manager (overwrites free as well)
#define MEMORY_MALLOC_OVERWRITE true
// enable debug message printing
#define R_DEBUG true
// set memory unit to use dynamic allocations instead of a single static allocation
#define DYNAMIC_HEAP true
#include "memory.h"
#include "error.h"
#include "compiler.h"
#include "math.h"


static void printtrie(binary_trie *trie) {
	uword values = 1u << trie->bits;
	for(uword address = 0; address < values; address++) {
		r_infof(R_SUCCESS, __func__, "[%u] = %u\n", address, b_read(trie, address));
	}
}

int main(int argc, char **argv) {
	r_info("Running.\n");
	r_info("Building binary_trie.\n");
	pair test[3] = {
			{0, 1},
			{1, 2},
			{2, 3}
	};
	binary_trie *trie = b_create(test, 8, 3);
	printtrie(trie);
	free(trie);
	return 0;
}
