/*
 * Module: universal_map
 * File: universal_map.h
 * Created:
 * October 28, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 *
 * License: See LICENSE.txt
 */

#ifndef PROJECT_AQUINAS_UNIVERSAL_MAP_H
#define PROJECT_AQUINAS_UNIVERSAL_MAP_H

#include <platform.h>
#include "dynarray.h"

typedef struct umap_node {
    
    struct umap_node *branches;
    
} umap_node;
typedef struct universal_map {
    dynarray *values;
} umap;



umap *umap_create();

void umap_free(umap *map);

uword umap_get(umap map, uint32_t key);

void umap_set(umap map, uint32_t key, uint32_t value);

bool umap_exists(umap map, uint32_t key);

#endif //PROJECT_AQUINAS_UNIVERSAL_MAP_H
