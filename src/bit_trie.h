/*
 * Module: bit_trie
 * File: bit_trie.h
 * Created:
 * April 21, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef PROJECT_AQUINAS_BIT_TRIE_H
#define PROJECT_AQUINAS_BIT_TRIE_H

#include <stdint.h>

#include "platform.h"

#define BITS (sizeof(uqword) * sizeof(uintmin_t) * MIN_BITS)

typedef struct bit_trie {
	// the binary data
	uqword *binodes;
	// the size of the value
	uqword depth;
} bit_trie;

uqword btt_read(bit_trie *trie, uqword address);

void btt_write(bit_trie *trie, uqword address, uqword value);

bit_trie *btt_create(uqword_pair const *pairs, uqword depth, uqword length);

void btt_free(bit_trie *trie);

#endif //PROJECT_AQUINAS_BIT_TRIE_H
