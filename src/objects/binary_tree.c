/*
 * Module: binary_tree
 * File: binary_tree.c
 * Created:
 * May 20, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#include "platform.h"
#include "binary_tree.h"
#include "bit_math.h"


binary_tree *binary_tree_create(uqword nodes) {
    binary_tree *tree = calloc((2u << sigbits(nodes)), sizeof(uqword));
    tree->nodes = nodes;
    return tree;
}

void binary_tree_free(binary_tree *restrict tree) {

}

static inline binode *b_traverse(binode *restrict node, uqword address) {
traverse:
    node = (address & 1) ? node->one : node->zero;
    address >>= 1;

    if (address > 0)
        return node;
    else
        goto traverse;
}

uqword binary_tree_get(binary_tree *restrict tree, uqword address) {
    return b_traverse((binode *) tree, address)->value;
}

void binary_tree_set(binary_tree *restrict tree, uqword address, uqword value) {
    b_traverse((binode *) tree, address)->value = value;
}

uqword *b_get_all(binary_tree *restrict tree, uqword *restrict addresses, uqword length) {
    uqword *values = malloc(sizeof(uqword) * length);
    binode *node;

    for (uqword i = 0; i < length; i++) {
        node = b_traverse((binode *) tree, addresses[i]);
        values[i] = node->value;
    }

    return values;
}

//void b_set_all(binary_tree *restrict tree, uqword_pair *values, uqword length) {
//    binode *node;
//    uqword_pair *uqword_pair;
//
//}
