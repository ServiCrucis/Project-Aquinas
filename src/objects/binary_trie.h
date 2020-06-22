/*
 * Module: binary_trie
 * File: binary_trie.h
 * Created:
 * May 20, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef PROJECT_AQUINAS_BINARY_TRIE_H
#define PROJECT_AQUINAS_BINARY_TRIE_H

#include "platform.h"
#include "bit_math.h"

// A binary_trie implementation utilizing uword integer values aligned to data model
typedef struct binary_trie {
	uword *restrict data;
	uword nodes;
} binary_trie;

binary_trie *bintrie_create(uword nodes);

void bintrie_free(binary_trie *trie);

/*
 * Gets the value at the given address in the trie.
 *
 * A bitmask is generated based on the number of nodes in the trie to handle buffer overflow.
 */
uword bintrie_get(binary_trie *restrict trie, uword address);
/*
 * Sets the value at the given address in the trie to the given value.
 *
 * A bitmask is generated based on the number of nodes in the trie to handle buffer overflow.
 */
void bintrie_set(binary_trie *restrict trie, uword address, uword value);

#endif //PROJECT_AQUINAS_BINARY_TRIE_H
