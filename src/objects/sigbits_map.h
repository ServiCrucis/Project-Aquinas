/*
 * Module: map
 * File: map.h
 * Created:
 * June 13, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef PROJECT_AQUINAS_SIGBITS_MAP_H
#define PROJECT_AQUINAS_SIGBITS_MAP_H

#include <platform.h>


typedef struct map_node {
    struct map_node *children;
    uint_fast32_t values[2];
    sbyte *node_indices;
    ubyte bits;
    ubyte length;
} map_node;

/*
 * A significant bits map object.
 *
 * Significant bits map objects are pure as they only need to store the direct indices into an unordered list of values.
 * As such, a significant bits map object can be reused or recycled, but it is not strictly necessary to store values
 * indirectly unless using a value greater than the size of an unsigned qword for the target platform.
 *
 * Binary Key Format:
 *     sigbits:  __auto_type node_index;
 */
typedef struct map_node sigbits_map;

/*
 * Allocates and initializes a new map whose size is at minimum significant_bits in size, and at most two to the power
 * of significant_bits in size.
 */
sigbits_map *sbm_create(ubyte significant_bits);

/*
 * Frees the given map and all of its members.
 */
void sbm_free(sigbits_map *map);

/*
 * Gets the index associated with the given key in this map if it exists.
 */
uint_fast32_t sbm_get(sigbits_map *map, uqword key);

/*
 * Sets the associated key and value uqword_pair in the map whether or not the uqword_pair exists in the map. The allocated quantity
 * of memory associated with the map does not necessarily increase.
 */
void sbm_set(sigbits_map *map, uqword_pair key_and_value);

/*
 * Deletes the associated key and value uqword_pair in the map if the uqword_pair exists in the map. The allocated quantity of
 * memory associated with the map does not necessarily decrease. Be wary, therefore, of the possibility of memory leaks.
 */
uqword_pair sbm_delete(sigbits_map *map, uqword_pair pair);

// TODO map_optimize

#endif //PROJECT_AQUINAS_SIGBITS_MAP_H
