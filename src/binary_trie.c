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
// as uint8_t array (two bytes, three bit addressing)
// {0,1}{0,1,0,1}{0,1 | ,0,1,0,1,0,1},0,1 (last two bits unused
// address: 011

// first bit: pow(2,1) * 2 - 2
static inline uword powi(uword base, uword exp) {
	uword result = 1u;
    for (;;)
    {
        if (exp & 1u)
            result *= base;
        exp >>= 1u;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

uword b_read(binary_trie trie, uword address) {
	uword value = (uword) 0;
	
	uword nodes = 0;
	uword address_bit = address >> BITS & 1u;
	uword current_bit = BITGET(trie.binodes, address_bit);
	uword previous_bit = current_bit;
	// prepare for loop
	value |= current_bit << BITS;
	nodes = 2;
	
	for (uword i = 1; i < BITS; i++) {
		uword a = 2 * nodes;
		a = 2 * a - 2 - a;
		// offset of next node
		uword offset = a + (previous_bit * nodes * 2) + previous_bit;
		// calculate offset of the current bit relative to current position
		current_bit = BITGET(trie.binodes, offset);
	}
	
	return value;
}

void b_write(binary_trie trie, register uword address, register uword value) {
	uword nodes = 0;
	uword address_bit = address >> BITS & 1u;
	uword value_bit = value >> BITS & 1u;
	uword previous_bit = value_bit;
	// prepare for loop
	if (value_bit)
		BITSET(trie.binodes, address_bit);
	else
		BITCLEAR(trie.binodes, address_bit);
	
	nodes = 2;
	
	for (uword i = 1; i < BITS; i++) {
		uword a = 2 * nodes;
		a = 2 * a - 2 - a;
		// offset of next node
		uword offset = a + (previous_bit * nodes * 2) + previous_bit;
		// calculate offset of the current bit relative to current position
		value_bit = BITGET(trie.binodes, offset);
	}
}

binary_trie b_create(pair *nodes, uword length) {
	binary_trie *result = malloc(BITNSLOTS(2 * powi(2, sizeof(uword)) - 2));
}
