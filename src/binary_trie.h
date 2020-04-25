/*
 * Module: binary_trie
 * File: binary_trie.h
 * Created:
 * April 21, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef CATHOLICUS_BINARY_TRIE_H
#define CATHOLICUS_BINARY_TRIE_H

#include <stdint.h>
#include <stdbool.h>

#include "platform.h"

#define BITS sizeof(uword)

typedef struct binary_trie {
	// the binary nodes
	uword *binodes;
	// the size of the value
	uword bits;
} binary_trie;

typedef struct uword_pair {
	uword a;
	uword b;
} pair;

uword b_read(binary_trie *trie, uword address);

void b_write(binary_trie *trie, uword address, uword value);

binary_trie *b_create(pair *nodes, uword bits, uword length);

#endif //CATHOLICUS_BINARY_TRIE_H
