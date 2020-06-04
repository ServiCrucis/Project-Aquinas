/*
 * Module: permutation
 * File: permutation.h
 * Created:
 * February 25, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef CATHOLICUS_PERMUTATION_H
#define CATHOLICUS_PERMUTATION_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "binary_trie.h"

typedef struct permutation {
	struct permutation *nodes;
	binary_trie        *map;
} permutation;

permutation p_read(FILE *in);

void p_write(permutation in, FILE *out);

#endif //CATHOLICUS_PERMUTATION_H
