/*
 * Module: binary_tree
 * File: binary_tree.h
 * Created:
 * May 20, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef PROJECT_AQUINAS_BINARY_TREE_H
#define PROJECT_AQUINAS_BINARY_TREE_H

#include "platform.h"
#include "bit_math.h"

typedef struct binode {
    struct binode *zero, *one;
    uword value;
} binode;


// A binary_tree implementation utilizing uword integer values aligned to data model
typedef struct binary_tree {
    binode *zero, *one;
    uword value;
	uword nodes;
} binary_tree;

binary_tree *binary_tree_create(uword nodes);

void binary_tree_free(binary_tree *tree);

/*
 * Gets the value at the given address in the tree.
 *
 * A bitmask is generated based on the number of nodes in the tree to handle buffer overflow.
 */
uword binary_tree_get(binary_tree *restrict tree, uword address);
/*
 * Sets the value at the given address in the tree to the given value.
 *
 * A bitmask is generated based on the number of nodes in the tree to handle buffer overflow.
 */
void binary_tree_set(binary_tree *restrict tree, uword address, uword value);

uword *b_get_all(binary_tree *restrict tree, uword *restrict addresses, uword length);

void b_set_all(binary_tree *restrict tree, pair *restrict values, uword length);

#endif //PROJECT_AQUINAS_BINARY_TREE_H
