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


typedef struct universal_map {
    uint32_t levels;
    union {
        struct universal_map **map;
        uqword               value;
    } nodes;
} umap;

typedef struct universal_map_key {
    uint32_t length;
    ubyte *value;
} umap_key;

typedef struct universal_map_value {
    uint32_t length;
    ubyte *bytes;
} umap_value;

umap *umap_create();

void umap_free(umap *map);

uqword umap_get(umap *map, umap_key key);

void umap_set(umap *map, umap_key key, umap_value value);

bool umap_exists(umap *map, umap_key key);

#endif //PROJECT_AQUINAS_UNIVERSAL_MAP_H
