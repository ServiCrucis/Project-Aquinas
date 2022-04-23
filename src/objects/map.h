/*
 * Module: map
 * File: map.h
 * Created:
 * May 02, 2021
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * This data structure is a minimal hash trie using (dynamic) perfect hashing.
 *
 * Copyright &copy; 2021 Christi Crucifixi, LLC. All rights reserved.
 *
 * License: See LICENSE.txt
 */


#ifndef PROJECT_AQUINAS_MAP_H
#define PROJECT_AQUINAS_MAP_H

#include <platform.h>

typedef struct map_proto_key {

} map_proto_key;

typedef struct map_key {
    uint64_t length;
    uint8_t *value;
} map_key;

typedef struct map_value {
} map_value;

enum map_state_code {
    SUCCESS = 0, FAIL
};

typedef struct map_result {
    enum map_state_code result_state;
    map_value value;
} map_result;

typedef struct map {
    map_key (*generate_hash)(uint8_t *key_data, size_t length);
    
} map;


map *map_create(map_key (*hash_generator)(uint8_t *key_data, size_t length));

void map_free(map *map);

map_result map_get(map *map, map_key key);

void map_set(map *map, map_key, map_value);


#endif //PROJECT_AQUINAS_MAP_H
