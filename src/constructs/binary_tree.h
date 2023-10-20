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

#include "memory/m_pointer_offset.h"

typedef struct binary_tree_member {
} binary_tree_member;

typedef struct binary_tree {
//    metadata;
    binary_tree_member *data;
} binary_tree;

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
