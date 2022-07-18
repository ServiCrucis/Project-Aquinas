/*
* Module: array
* File: array.h
* Created:
* June 29, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
*/

#ifndef PROJECT_AQUINAS_ARRAY_H
#define PROJECT_AQUINAS_ARRAY_H

#include "platform.h"

typedef struct array {
    udword type;
    udword size;
    ubyte data[];
} array;

typedef struct contiguous_array {
    udword type;
    udword size;
    void *data;
} contiguous_array;

#endif //PROJECT_AQUINAS_ARRAY_H
