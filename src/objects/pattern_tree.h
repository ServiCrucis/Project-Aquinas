/*
 * Module: pattern_tree
 * File: pattern_tree.h
 * Created:
 * February 25, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef PROJECT_AQUINAS_PATTERN_TREE_H
#define PROJECT_AQUINAS_PATTERN_TREE_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "binary_tree.h"

typedef struct tree_node {
	struct tree_node *children;
	uword order;
} tree_node;

typedef tree_node pattern_tree;



#endif //PROJECT_AQUINAS_PATTERN_TREE_H
