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
#include "state/allocating.h"

typedef uqword tree_node_value;
typedef void   *tree_node_pointer;

/*
 * A convenient data interface
 */
union tree_node_member {
    tree_node_value   value;
    tree_node_pointer pointer;
};

typedef struct tree_node {
    // pointer = base_pointer | pointer_offset;
    // sigbits(pointer) = base_pointer_size + pointer_offset_size;
    ubyte  base_pointer_size;
    ubyte  *base_pointers;
    // elements: either pointer_offset or data value
    // sizeof(*elements) is at most sizeof(void *)
    // number of elements in tree_node.elements
    // value = order + 1
    // order = value - 1
    uqword elements_size;
    ubyte  *elements;
}              tree_node;

typedef struct tree {
    // size in bits of a tree node element
    ubyte     element_size:6;
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
    uqword    address_transform;
    tree_node root;
}              tree;

enum tree_status {
    TREE_SUCCESS = 0,
    
};

tree tree_construct(ubyte element_size);

tree_node_value tree_get(uqword address, enum tree_status *);

void tree_set(uqword address, tree_node_value, enum tree_status *);

void tree_expand();

void tree_compress();

#endif //PROJECT_AQUINAS_TREE_H
