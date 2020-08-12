//
// Created by ServiRegis on 2020-08-06.
//

#ifndef PROJECT_AQUINAS_TREE3D_H
#define PROJECT_AQUINAS_TREE3D_H

#include <platform.h>

#ifndef Tree3D_value
#define Tree3D_value uint64_t
#endif

#ifndef Tree3D_address
#define Tree3D_address uint64_t
#endif

typedef struct Tree3D_node {
    struct Tree3D_node *nodes;
    Tree3D_value *values;
    ubyte *indices;
    ubyte address_bits;
} Tree3D_node;

typedef struct Tree3D_node Tree3D;

Tree3D *tree3D_create(ubyte bits);

void tree3D_free(Tree3D *restrict tree);

Tree3D_value tree3D_get(Tree3D *restrict, Tree3D_address);

Tree3D_value tree3D_set(Tree3D *restrict, Tree3D_address, Tree3D_value);

#endif //PROJECT_AQUINAS_TREE3D_H
