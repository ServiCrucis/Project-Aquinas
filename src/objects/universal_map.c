/*
 * Module: map
 * File: map.c
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
}

void umap_free(umap *map) {
}

static inline uqword get_index(umap *map, umap_key key) {

}

uqword umap_get(umap *map, umap_key key) {
}

void umap_set(umap *map, umap_key key, umap_value value);

bool umap_exists(umap *map, umap_key key);
