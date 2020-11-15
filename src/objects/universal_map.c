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

// allocation unit in bytes
#ifndef UMAP_ALLOCATION_UNIT
    #define UMAP_ALLOCATION_UNIT 16
#endif

umap *umap_create() {
    umap *map = malloc(sizeof(*map));
    map->offsets = calloc(4 * 4, sizeof(ubyte));
    map->values  = dynarray_create(UMAP_ALLOCATION_UNIT);
    return map;
}

void umap_free(umap *map) {
    if (map) {
        if (map->offsets) {
            dynarray_free(map->offsets);
        }
        if (map->values) {
            dynarray_free(map->values);
        }
        free(map);
    }
}

static inline uint32_t get_offset(umap map, uint32_t index_value, uint32_t offset_depth) {
    const uint32_t offset_index = offset_depth * (index_value >> 1ull);
    if (offset_index > map.offsets->data_length)
        map.offsets = dynarray_resize(map.offsets, map.offsets->data_length + UMAP_ALLOCATION_UNIT);
    // the modulus of the index value since each ubyte has two nybbles
    index_value = index_value & 1ull;
    // extract and return
    return (map.offsets->data[offset_index] >> (index_value * 4ull)) & 0xFull;
}

static inline uint32_t get_index(umap map, uint32_t key) {
    uint32_t key0, key1, key2, key3;
    uint32_t key4, key5, key6, key7;
    // mov rah, ... (1c) move high 16 bits into rah, rbh, rch, rdh
    key0 = key >> 15;
    key1 = key >> 15;
    key2 = key >> 15;
    key3 = key >> 15;
    // mov ral, ... (1c) move low 16 bits into ral, rbl, rcl, rdl
    key4 = key & 0xFFFFu;
    key5 = key & 0xFFFFu;
    key6 = key & 0xFFFFu;
    key7 = key & 0xFFFFu;
    // shr/sar rah, ... (1c) get nybbles in upper 16 bits
    key0 >>= 16 - 4 * 1;
    key1 >>= 16 - 4 * 2;
    key2 >>= 16 - 4 * 3;
    key3 >>= 16 - 4 * 4;
    // shr/sar ral, ... (1c) get nybbles in lower 16 bits
    key4 >>= 16 - 4 * 1;
    key5 >>= 16 - 4 * 2;
    key6 >>= 16 - 4 * 3;
    key7 >>= 16 - 4 * 4;
    // and rah, ... (1c) mask high 16 bits to zero upper bits
    key0 &= 0xFu;
    key1 &= 0xFu;
    key2 &= 0xFu;
    key3 &= 0xFu;
    // and ral, ... (1c) mask low 16 bits to zero upper bits
    key4 &= 0xFu;
    key5 &= 0xFu;
    key6 &= 0xFu;
    key7 &= 0xFu;
}

uword umap_get(umap map, uint32_t key) {
    return map.values->data[get_index(map, key)];
}

void umap_set(umap map, uint32_t key, uint32_t value);

bool umap_exists(umap map, uint32_t key);

#ifdef UMAP_ALLOCATION_UNIT
    #undef UMAP_ALLOCATION_UNIT
#endif
