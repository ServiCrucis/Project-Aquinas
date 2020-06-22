/*
 * Module: binary_trie
 * File: binary_trie.h
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

#define BITS (sizeof(uword) * sizeof(uintmin_t) * MIN_BITS)

typedef struct bit_trie {
	// the binary data
	uword *binodes;
	// the size of the value
	uword depth;
} bit_trie;

uword btt_read(bit_trie *trie, uword address);

void btt_write(bit_trie *trie, uword address, uword value);

bit_trie *btt_create(pair const *pairs, uword depth, uword length);

void btt_free(bit_trie *trie);

#endif //PROJECT_AQUINAS_BIT_TRIE_H
