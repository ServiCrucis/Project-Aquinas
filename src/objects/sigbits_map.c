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
#include <string.h>

#include "sigbits_map.h"
#include "bit_math.h"
#include "state.h"

static inline void map_allocate_node_data(map_node *restrict node, register ubyte significant_bits, register ubyte nodes) {
    node->children = calloc(nodes, sizeof(*node->children));
    node->node_indices = calloc(significant_bits, sizeof(typeof(*node->node_indices)));

    if (!node->node_indices) fatalf(__func__, "Failed to allocate new memory for node_indices\n");
    for (ubyte i = 0; i < significant_bits; i++) {
        node->node_indices[i] = -1;
    }

    node->bits = significant_bits;
    node->length = nodes;
}

static inline map_node *map_create_node(register ubyte significant_bits, register ubyte nodes) {
    map_node *restrict node = calloc(1, sizeof(*node));
    map_allocate_node_data(node, significant_bits, nodes);
    return node;
}

static inline void map_resize_nodes(register map_node *restrict node, register ubyte new_length) {
    if (new_length == node->length) return;

    map_node *old_children = node->children;
    map_node *new_children = realloc(old_children, new_length * sizeof(*new_children));

    if (!new_children) {
        warnf(R_FAILURE, __func__, "Failed to reallocate memory for node resizing.\n");
        warnf(R_FAILURE, __func__, "Attempting to allocate new memory\n");
        new_children = calloc(new_length, sizeof(*new_children));

        if (!new_children) {
            fatalf(__func__, "Failed to allocate new memory for node resizing.\n");
        }

    copy_to_new:
        {
            ubyte i = 0;
            new_children[i] = old_children[i];
            i++;
            if (i < new_length) goto copy_to_new;
        }

    }

    node->children = new_children;
}

sigbits_map *sbm_create(register ubyte significant_bits) {
    return map_create_node(significant_bits, 0);
}

void sbm_free(register sigbits_map *restrict map) {

}

uint_fast32_t sbm_get(register sigbits_map *restrict map, register uword key) {
    #define end_of_key() ( !bit_index )
    #define next_node_is_NULL() ( node_index < 0 )
    register uword bit_index = sigbits(key) - 1;
    register typeof(*map->node_indices) node_index;
    register map_node *current = map;

next_node:
    if (end_of_key()) {
        goto get_node_value;
    }

    node_index = current->node_indices[bit_index];
    if (next_node_is_NULL()) {
        return 0;
    }
    current = &current->children[node_index];
    key = clear_bit(key, bit_index);
    bit_index = sigbits(key) - 1;
    goto next_node;

get_node_value:
    return current->values[key & 1];

    #undef next_node_is_NULL
    #undef end_of_key
}

void sbm_set(register sigbits_map *restrict map, register pair key_and_value) {
    #define end_of_key() ( !bit_index )
    #define next_node_is_NULL() ( node_index < 0 )
    register uword key = key_and_value.a;
    register const typeof(*map->values) value = (typeof(*map->values)) key_and_value.b;
    register uword bit_index = sigbits(key) - 1;
    register typeof(*map->node_indices) node_index;
    register map_node *current = map;

next_node:
    if (end_of_key()) {
        goto set_node_value;
    }

    node_index = current->node_indices[bit_index];
    if (next_node_is_NULL()) {
        if (current->length > current->bits)
            fatalf(__func__, "Key/Value pair out of range: supported bits: %llu; required bits: %llu\n", current->bits, current->length);
        // update the node index
        node_index = current->length;
        current->node_indices[bit_index] = node_index;

        map_resize_nodes(current, current->length + 1);
        map_allocate_node_data(&current->children[node_index], sigbits(key), 0);
    }
    current = &current->children[node_index];
    key = clear_bit(key, bit_index);
    bit_index = sigbits(key) - 1;
    goto next_node;

set_node_value:
    current->values[key & 1] = value;
    return;

    #undef next_node_is_NULL
    #undef end_of_key
}

/*
 * This implementation has a fail-fast behavior: if the node is not initialized, we return.
 */
pair sbm_delete(sigbits_map *restrict map, pair pair) {
    #define end_of_key() ( !bit_index )
    #define next_node_is_NULL() ( node_index < 0 )
    register typeof(*map->values) key = (typeof(*map->values)) pair.a;
    register const uword value = pair.b;
    register uword bit_index = sigbits(key) - 1;
    register typeof(*map->node_indices) node_index;
    register map_node *current = map;

next_node:
    if (end_of_key()) {
        goto delete_node_value;
    }

    node_index = current->node_indices[bit_index];
    if (next_node_is_NULL()) {
        pair.b = 0;
        return pair;
    }
    current = &current->children[(ubyte) node_index];
    key = clear_bit(key, bit_index);
    bit_index = sigbits(key) - 1;
    goto next_node;

delete_node_value:
    pair.b = current->values[key & 1ull];
    current->values[key & 1ull] = 0;
    return pair;

    #undef next_node_is_NULL
    #undef end_of_key
}
