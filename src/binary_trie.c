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

#include "binary_trie.h"
#include "error.h"

static inline uword get_bit(binary_trie *trie, uword bit_offset) {
	uword bits = (2u << trie->bits) - 2u;
	uword words = bits / BITS;
	uword word = trie->binodes[bit_offset / words];
	uword bit = (word >> (bit_offset % words)) & 1u;
	return bit;
}

static inline void set_bit(binary_trie *trie, uword bit_offset, uword value) {
	uword bits = (2u << trie->bits) - 2u;
	uword words = bits / BITS;
	trie->binodes[bit_offset / words] &= ~(1u << (bit_offset % words));
	trie->binodes[bit_offset / words] |= (value & 1u) << (bit_offset % words);
}

uword b_read(binary_trie *trie, uword address) {
	uword value = 0;
	uword base;
	uword offset = 0;
	// i is the target bit index of the address bit for bits [0, trie->bits - 1]
	for (uword i = 0; i < trie->bits; i++) {
		// base of target node (2 * (2^N) - 2)
		// pow2(n) := (1u << n) where n >= 0
		// 2 * x = x << 1u
		// 2 * pow2(n) = (1u << n) << 1u = 2u << n
		base = (2u << i) - 2u;
		// offset of target node (previous_offset + address_bit * nodes)
		offset += (address >> (trie->bits - i - 1u)) * ((1u << (i + 1u)) >> 1u);
		// set the current bit of the result to the bit stored in the trie
		value |= get_bit(trie, base + offset) >> i;
	}
	
	return value;
}

void b_write(binary_trie *trie, register uword address, register uword value) {
	uword base;
	uword offset = 0;
	// i is the target bit index of the address bit for bits [0, trie->bits - 1]
	for (uword i = 0; i < trie->bits; i++) {
		// base of target node (2 * (2^N) - 2)
		// pow2(n) := (1u << n) where n >= 0
		// 2 * x = x << 1u
		// 2 * pow2(n) = (1u << n) << 1u = 2u << n
		base = (2u << i) - 2u;
		// offset of target node (previous_offset + address_bit * nodes)
		offset += (address >> (trie->bits - i - 1u)) * ((1u << (i + 1u)) >> 1u);
		// get the value of bit i in the given value parameter
		uword bit = (value >> i) & 1u;
		// set the value of the bit at (base + offset) to the corresponding bit in value
		set_bit(trie, base + offset, bit);
	}
}

binary_trie *b_create(pair *nodes, uword bits, uword length) {
	binary_trie *result = malloc(sizeof(binary_trie) + (2u << bits) - 2u);
	if (!result) {
		r_fatalf(R_ALLOCATION_FAILURE, __func__, "failed to allocate memory for binary_trie");
	}
	
	result->binodes = (uword *) (uintptr_t) result + sizeof(binary_trie);
	result->bits    = bits;
	
	
	for (uword i = 0; i < length; i++) {
		pair pair = nodes[i];
		b_write(result, pair.a, pair.b);
	}
	
	return result;
}
