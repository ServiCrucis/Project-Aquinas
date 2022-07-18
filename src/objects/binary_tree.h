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

#include "memory/m_object.h"

typedef struct binary_tree_data_header {
    // identifier of first element that differs
    uword difference_element_offset;
    //
    uword element_type_table;
}                                          binary_tree_data_header;

typedef struct binary_tree_node {
    // |elements| = 2**elements_length
    ubyte    elements_length;
    m_object elements;
} __attribute__((aligned (sizeof(uword)))) binary_tree_node;

/*
 * Current design notes:
 * 1. each node is an array of elements
 * 2. each element can be a value or node m_object
 * 3. each node m_object is compressed via m_object
 * 4. each m_object is associated with a pointer_group
 * 5. each pointer_group is per 256 elements to maximize m_object compression
 * 6. pointer_group table tracks allocated pointers relative to elements via:
 *      i. node radix
 *      ii. elements allocated in entire tree
 *
 */
typedef struct binary_tree {
    // number of bits a single pair takes up
    udword           pair_radix;
    udword           pairs_length;
    ubyte            *radix_offset_pairs;
    binary_tree_node *root;
    ubyte            *data;
} __attribute__((aligned(32)))             binary_tree;

/*
 * Collection of states for operating on a binary tree's nodes individually
 */
typedef struct binary_tree_node_generator {
} binary_tree_node_generator;

/*
 * Collection of behaviors for operating on a binary tree's nodes individually
 */
typedef struct binary_tree_node_interface {
} binary_tree_node_interface;

void binary_tree_construct(void *memory);

void binary_tree_get();

void binary_tree_set();

binary_tree_node_generator binary_tree_goto();

#endif //PROJECT_AQUINAS_BINARY_TREE_H
