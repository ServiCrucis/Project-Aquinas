/*
* Module: dynarray
* File: dynarray.h
* Created:
* November 03, 2020
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
*/

#ifndef PROJECT_AQUINAS_DYNARRAY_H
#define PROJECT_AQUINAS_DYNARRAY_H

#include <stdint.h>
#include <platform.h>

/*
 * A dynamic array. All lengths are lengths in bytes unless otherwise stated. The dynarray is aligned to the
 * native architecture's data model. For example, if DATA_MODEL == LP64, then the alignment is 64 bits.
 */
typedef struct dynamic_array {
    uint32_t data_length;
    ubyte data[];
} dynarray;

/*
 * Allocates space for a dynarray with at minimum data_length bytes. If the length is not aligned to the data model of
 * the native architecture, then the amount of allocated space is
 *      data_length - (data_length % sizeof(uqword)) + sizeof(uqword)
 */
dynarray *dynarray_create(uint32_t data_length);

/*
 * Frees the given dynarray pointer if it is not NULL. If NULL, this function only returns.
 */
void dynarray_free(dynarray *restrict array);

/*
 * Gets a specified number of bytes from the dynarray.
 */
void dynarray_get(dynarray *restrict src, uint32_t srcoff, uint32_t srclen, ubyte *restrict dst, uint32_t dstoff, uint32_t dstlen);

/*
 * Sets a specified number of bytes in the dynarray from a given array of bytes.
 */
void dynarray_set(dynarray *restrict dst, uint32_t dstoff, uint32_t dstlen, ubyte *restrict src, uint32_t srcoff, uint32_t srclen);

/*
 * Fills the dynarray with the value of src. src must have an alignment that equals or divides into the alignment of
 * dst's array.
 */
void dynarray_fill(dynarray *restrict dst, ubyte *restrict src, uint32_t srclen);

/*
 * Resizes the given dynarray using realloc to be at least size bytes. The function terminates the process if realloc
 * fails. As with dynarray_create, if the length is not aligned to the data model of the native architecture, then the
 * amount of allocated space is
 *      data_length - (data_length % sizeof(uqword)) + sizeof(uqword)
 *
 * The returned pointer is not guaranteed to be the original pointer.
 */
dynarray *dynarray_resize(dynarray *restrict array, uint32_t size);

#endif //PROJECT_AQUINAS_DYNARRAY_H
