/*
 ============================================================================
 Name        : catholicus.c
 Author      : Andrew Thomas Porter (AMDG)
 Version     : 1.0
 Copyright   : See LICENSE.txt
 Description : Catholicus language compiler
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>

// make other libraries use our memory manager (overwrites free as well)
#define MEMORY_MALLOC_OVERWRITE true
// enable debug message printing
#define R_DEBUG true
// set memory unit to use dynamic allocations instead of a single static allocation
#define DYNAMIC_HEAP true

#include "platform.h"
#include "compiler.h"
#include "bit_math.h"

static void test_bittrie() {
	r_info("Building bit_trie.\n");
//	pair    test[] = {
//			{ 23,1 },
//			{ 237,1 }
//	};
//	bit_trie *trie   = btt_create(test, 8, 2);
//	uword bits = 256;
	for(uword address = 0; address < (1ull << 8ull); address++) {
//		uword bit = btt_read(trie, address);
		r_infof(R_STATUS, __func__, "[%u]\n", bit_index((address << 1u) | 1ull));
	}
	
//	btt_free(trie);
	r_info("Done.\n");
}



int main(int argc, char **argv) {
	r_info("Running.\n");
	test_bittrie();
	return R_SUCCESS;
}
