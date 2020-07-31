/*
 * Module: map
 * File: map.h
 * Created:
 * June 13, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef PROJECT_AQUINAS_MAP_H
#define PROJECT_AQUINAS_MAP_H

#include <platform.h>

// forward declarations
union map_node;
typedef struct node {
    union {
        union map_node *node;
        uword value;
    };
    ubyte *node_index;
    uword nodes;
} node;

/*
 * A map object.
 *
 * Map objects are pure as they only need to store the direct indices into an unordered list of values. As such, a map
 * object can be reused or recycled.
 *
 * Binary Key Format:
 *     sigbits:  __auto_type node_index;
 */
typedef struct map {
    union {
        union map_node *node;
        uword value;
    };
    ubyte *node_index;
    uword nodes;
} map;

typedef union map_node {
    struct node node;
    struct map map;
} map_node;

/*
 * Allocates and initializes a new map whose size is at minimum significant_bits in size, and at most two to the power
 * of significant_bits in size.
 */
map *map_create(ubyte significant_bits);

/*
 * Frees the given map and all of its members.
 */
void map_free(map *restrict map);

/*
 * Gets the index associated with the given key in this map if it exists.
 */
uword map_get(map *restrict map, uword key);

/*
 * Sets the associated key and value pair in the map whether or not the pair exists in the map. The allocated quantity
 * of memory associated with the map does not necessarily increase.
 */
void map_set(map *restrict map, pair pair);

/*
 * Deletes the associated key and value pair in the map if the pair exists in the map. The allocated quantity of
 * memory associated with the map does not necessarily decrease.
 */
pair map_delete(map *restrict map, pair pair);

#endif //PROJECT_AQUINAS_MAP_H
