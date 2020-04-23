/*
 * File: symbol
 * Created:
 * February 25, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef CATHOLICUS_PATTERN_H
#define CATHOLICUS_PATTERN_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "binary_trie.h"

// Genus Primus (principia) de computator
// mov x to y
// unity
// uniqueness
// unity + uniqueness = continuity

typedef struct pattern {
	struct pattern *nodes;
	binary_trie *map;
} pattern;

pattern p_read(FILE *in);

void p_write(pattern in, FILE *out);

#endif //CATHOLICUS_PATTERN_H
