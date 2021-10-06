/*
 * Module: map
 * File: map.h
 * Created:
 * May 02, 2021
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2021 Christi Crucifixi, LLC. All rights reserved.
 *
 * License: See LICENSE.txt
 */


#ifndef PROJECT_AQUINAS_MAP_H
#define PROJECT_AQUINAS_MAP_H

#include <platform.h>

#ifndef map_value
    #define map_value ubyte
#endif

typedef struct map8 {
    map_value values[256];
} map8;

typedef struct map {
    ubyte *offset_table;
    map8 *nodes;
    uint32_t nodes_allocated;
} map;

typedef struct map_result {

} map_result;

#endif //PROJECT_AQUINAS_MAP_H
