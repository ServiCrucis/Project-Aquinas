/*
* Module: dynarray
* File: dynarray.c
* Created:
* November 03, 2020
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
*/

#include <stdlib.h>
#include <state.h>
#include "dynarray.h"

dynarray *dynarray_create(uint32_t data_length) {
    // ensure alignment of uword for array
    if (data_length % sizeof(uword))
        data_length = data_length - (data_length % sizeof(uword)) + sizeof(uword);
    dynarray *array = calloc(1, sizeof(*array) + data_length);
    array->data_length = data_length;
    return array;
}

void dynarray_free(dynarray *restrict array) {
    if (array) {
        free(array);
    }
}

void dynarray_get(dynarray *restrict src, uint32_t srcoff, uint32_t srclen, ubyte *restrict dst, uint32_t dstoff, uint32_t dstlen) {
    if (dstlen < srclen)
        fatalf(__func__, "destination is smaller than source\n");
    
    for (uint32_t i = 0; i < srclen; i++) {
        dst[dstoff + i] = src->data[srcoff + i];
    }
}

void dynarray_set(dynarray *restrict dst, uint32_t dstoff, uint32_t dstlen, ubyte *restrict src, uint32_t srcoff, uint32_t srclen) {
    if (dstlen < srclen)
        fatalf(__func__, "destination is smaller than source\n");
    
    for (uint32_t i = 0; i < srclen; i++) {
        dst->data[dstoff + i] = src[srcoff + i];
    }
}

void dynarray_fill(dynarray *restrict dst, ubyte *restrict src, uint32_t srclen) {
    if (dst->data_length % srclen)
        fatalf(__func__, "srclen is not aligned as a multiple of the native architecture's data model: %u\n", dst->data_length % srclen);
    
    for (uint32_t j = 0; j < dst->data_length; j += srclen) {
        for (uint32_t i = 0; i < srclen; i++) {
            dst->data[j + i] = src[i];
        }
    }
}

dynarray *dynarray_resize(dynarray *restrict array, uint32_t size) {
    if (!array)
        fatalf(__func__, "array is NULL\n");
    
    array = realloc(array, size);
    
    if (!array)
        fatalf(__func__, "failed to reallocate memory to resize array\n");
    
    array->data_length = size;
    return array;
}
