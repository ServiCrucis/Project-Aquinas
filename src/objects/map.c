/*
 * Module: map
 * File: map.c
 * Created:
 * June 13, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#include <limits.h>

#include "map.h"
#include "bit_math.h"
#include "state.h"

map *map_create(register ubyte significant_bits) {
    map *map = calloc(1, sizeof(map));
    map->node = calloc(significant_bits, sizeof(typeof(*map->node)));
    map->node_index = calloc(significant_bits, sizeof(typeof(*map->node_index)));
    map->nodes = significant_bits;
}

void map_free(register map *restrict map) {
    if (map) {
        if (exists(map->node)) free(map->node);
        else warnf(R_FAILURE, "free",__func__, "map->node does not exist");
        if (exists(map->node_index)) free(map->node_index);
        set_state(R_SUCCESS);
    } else {
        set_state(R_FAILURE);
    }
}
