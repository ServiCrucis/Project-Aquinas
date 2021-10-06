/*
 * Module: universal_map
 * File: universal_map.c
 * Created:
 * October 28, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 *
 * License: See LICENSE.txt
 */

#include <stdlib.h>
#include "bit_math.h"
#include "universal_map.h"
#include "state.h"

umap *umap_create() {
    umap *map = malloc(sizeof(*map));
    map->levels = 0;
    map->nodes.map = calloc(256, sizeof(*map->nodes.map));
    return map;
}

void umap_free(umap *map) {
    if (map) {
        // we want ubyte to save space to minimize the chances of stack overflow
        // hence, we check if increment caused an overflow and check the overflow flag
        if (map->nodes.map) {
            ubyte i = 0;
            do {
                umap *node = map->nodes.map[i];
                if (node) {
                    if (node->nodes.map) {
                        umap_free(node);
                    } else {
                        free(node);
                    }
                }
                i++;
            } while(i > 0);
        }
        
        free(map);
    }
}

static inline uqword get_index(umap *map, umap_key key) {

}

uqword umap_get(umap *map, umap_key key) {
}

void umap_set(umap *map, umap_key key, umap_value value);

bool umap_exists(umap *map, umap_key key);
