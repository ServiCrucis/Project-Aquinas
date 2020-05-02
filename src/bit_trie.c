/*
 * Module: binary_trie
 * File: binary_trie.c
 * Created:
 * April 21, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#include <stdlib.h>

#include "bit_trie.h"
#include "bit_math.h"
#include "error.h"

static uword get_bit(uword *bitarray, uword words, uword bit_offset) {
	uword bits = sizeof(uword) * sizeof(uintmin_t) * MIN_BITS;
	uword index = bit_offset / bits;
	if (!in_buffer(0, words, index))
		r_fatalf(R_BUFFER_OVERFLOW, __func__, "index out of range: 0 <= index=%u < %u\n", index, words);
	uword word  = bitarray[index];
	uword bit   = (word >> (bit_offset % bits)) & ((uword) 1u);
	return bit;
}

static void set_bit(uword *bitarray, uword words, uword bit_offset, uword value) {
	uword bits = sizeof(uword) * sizeof(uintmin_t) * MIN_BITS;
	uword index = bit_offset / bits;
	// guard
	if (!in_buffer(0, words, index))
		r_fatalf(R_BUFFER_OVERFLOW, __func__, "index out of range: 0 <= index=%u < %u\n", index, words);
	uword word  = bitarray[index];
	word ^= (word ^ ((value & ((uword) 1u)) << (bit_offset % bits))) & (((uword) 1u) << (bit_offset % bits));
	bitarray[index] = word;
}

// {0,1}{2,3,4,5}{6,7,8,9,10,11,12,13}
// [0][1,2][3,4,5][6,7,8,9]

static uword bit_index(uword address /*, uword bits_per_node, uword nodes TODO: universal bit_index */) {
	uword address_bits = sigbits(address);
	uword rel_offset = 0;
	for (uword i = 0; i < address_bits; i++) {
		// length of the bitset
		uword length = dbl(pow2i(i));
		// address bit
		uword address_bit = (address >> i) & 1u;
		// relative offset
		rel_offset = rel_offset + address_bit * (length / 2u);
	}
	
	return dbl(pow2i(address_bits - 1u)) - 2u + rel_offset;
}

uword btt_read(bit_trie *trie, uword address) {
	return get_bit(trie->binodes, (2u << trie->depth) / BITS, bit_index(address));
}

void btt_write(bit_trie *trie, uword address, uword bit) {
	set_bit(trie->binodes, (2u << trie->depth) / BITS, bit_index(address), bit);
}

bit_trie *btt_create(pair const *pairs, uword depth, uword length) {
	bit_trie *result = malloc(sizeof(bit_trie));
	if (!result) {
		r_fatalf(R_ALLOCATION_FAILURE, __func__, "failed to allocate memory for binary_trie");
	}
	
	result->binodes = calloc((2u << depth) / BITS, sizeof(uword));
	result->depth   = depth;
	
	if (!result->binodes) {
		r_fatalf(R_ALLOCATION_FAILURE, __func__, "failed to allocate memory for binary_trie");
	}
	
	for (uword i = 0; i < length; i++) {
		pair pair = pairs[i];
		btt_write(result, pair.a, pair.b);
	}
	
	return result;
}
