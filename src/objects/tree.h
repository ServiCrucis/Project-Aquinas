/*
 * Module: tree
 * File: tree.h
 * Created:
 * October 28, 2022
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
  * License: See LICENSE.txt
 */

#ifndef PROJECT_AQUINAS_TREE_H
#define PROJECT_AQUINAS_TREE_H

#include "platform.h"
#include "bit_math.h"

typedef struct tree_node_member {
} tree_node_member;

typedef struct tree_node {
    // to what base does this belong? (number of elements)
    // value = order + 1
    // order = value - 1
    uqword order;
    // elements: either pointer_offset or data value
    // sizeof(*elements) is at most sizeof(void *)
    void   *elements;
} __attribute__((aligned(16))) tree_node;

typedef struct tree {
    // in bits
    uqword  element_size:6;
    // unary coding designating separations between each level of the tree
    //
    // For each occurrence of zero or more zeroes followed by a one, the
    // position of the one represents the size of a level in the tree relative
    // to the previous level.
    //
    // For example, if a sequence 011 is given, then there are two levels in the
    // tree; the first level's index is formed from the bits marked as zero
    // including the one itself. Any consecutive sequence of ones means that the
    // succeeding ones are distinct levels of one bit indices.
    //
    uqword  address_transform;
    tree_node root;
} __attribute__((aligned(32))) tree;

typedef struct tree_result {

} tree_result;

void tree_get(uqword address, tree_result *);

void tree_set(uqword address, uword value_length, void *value);

#endif //PROJECT_AQUINAS_TREE_H
