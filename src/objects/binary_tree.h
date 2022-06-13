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
#include "../pointer.h"

enum binary_tree_node_type {
    BRANCH = 0, LEAF = 1
};

typedef struct binary_tree_state_info {
    uword state;
} binary_tree_state_info;

alignas(ubyte)
typedef struct binary_tree_node {
    // branch (0) or leaf (1) node
    ubyte type;
    ubyte values_length;
    base_pointer values_target;
    pointer8 values[];
};

typedef struct binary_tree {
    // fixed (0) or arbitrary (1) storage class
    // fixed: values are stored on the node directly
    // arbitrary: the node contains a fixed-size pointer to the data
    ubyte storage_class:1;
    ubyte data_radix:7;
} binary_tree;

binary_tree binary_tree_create();

void binary_tree_destroy();

binary_tree_state_info binary_tree_linearize();

binary_tree_state_info binary_tree_read();

binary_tree_state_info binary_tree_write();

#endif //PROJECT_AQUINAS_BINARY_TREE_H
