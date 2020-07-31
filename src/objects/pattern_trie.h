/*
 * Module: pattern_trie
 * File: pattern_trie.h
 * Created:
 * February 25, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef PROJECT_AQUINAS_PATTERN_TRIE_H
#define PROJECT_AQUINAS_PATTERN_TRIE_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "binary_tree.h"

typedef struct pattern_trie {
	struct pattern_trie *children;
	uword order;
} pattern_trie;

pattern_trie p_read(FILE *in);

void p_write(pattern_trie in, FILE *out);

#endif //PROJECT_AQUINAS_PATTERN_TRIE_H
