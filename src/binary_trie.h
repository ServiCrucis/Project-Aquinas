/*
 * Module: binary_trie
 * File: binary_trie.h
 * Created:
 * May 03, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef CATHOLICUS_BINARY_TRIE_H
#define CATHOLICUS_BINARY_TRIE_H

#include "bit_math.h"

// discriminated union of node and binary_trie
typedef struct node {
	struct node **branches;
	uword order;
} node;

typedef struct binary_trie {
	node **root;
	uword order;
} binary_trie;

#endif //CATHOLICUS_BINARY_TRIE_H
