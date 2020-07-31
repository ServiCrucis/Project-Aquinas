/*
 * Module: bit_trie
 * File: bit_trie.c
 * Created:
 * April 21, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#include <stdlib.h>

#include "bit_trie.h"
#include "bit_math.h"
#include "state.h"

uword btt_read(bit_trie *trie, uword address) {
	return get_bit(trie->binodes, (2u << trie->depth) / BITS, bin_index(address));
}

void btt_write(bit_trie *trie, uword address, uword bit) {
	set_bit(trie->binodes, (2u << trie->depth) / BITS, bin_index(address), bit);
}

bit_trie *btt_create(pair const *pairs, uword depth, uword length) {
	bit_trie *result = malloc(sizeof(bit_trie));
	
	if (!result) {
		fatalf("allocating", __func__, "failed to allocate memory for binary_trie");
	}
	
	result->binodes = calloc((2u << depth) / BITS, sizeof(uword));
	result->depth   = depth;
	
	if (!result->binodes) {
		fatalf("allocating", __func__, "failed to allocate memory for binary_trie");
	}
	
	for (uword i = 0; i < length; i++) {
		pair pair = pairs[i];
		btt_write(result, pair.a, pair.b);
	}
	
	return result;
}

void btt_free(bit_trie *trie) {
	free(trie->binodes);
	free(trie);
}
