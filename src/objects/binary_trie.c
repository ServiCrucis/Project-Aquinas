/*
 * Module: binary_trie
 * File: binary_trie.c
 * Created:
 * May 20, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#include "platform.h"
#include "binary_trie.h"
#include "bit_math.h"


binary_trie *bintrie_create(uword nodes) {
	binary_trie *restrict trie = calloc(1, sizeof(binary_trie));
	trie->data = calloc(nodes, sizeof(uword));
	trie->nodes = nodes;
	return trie;
}

void bintrie_free(binary_trie *restrict trie) {
	if (trie) {
		if(trie->data) {
			free(trie->data);
		}
		free(trie);
	}
}

uword bintrie_get(binary_trie *restrict trie, uword address) {
	return trie->data[bin_index(address & bitmask(trie->nodes))];
}

void bintrie_set(binary_trie *restrict trie, uword address, uword value) {
	trie->data[bin_index(address & bitmask(trie->nodes))] = value;
}
