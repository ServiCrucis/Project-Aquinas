/*
* Module: pointer
* File: pointer.h
* Created:
* June 12, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
 *
 *
 * A stupidly simple pointer implementation that supports this incredibly revolutionary
 * new concept known as compressed pointers (pointer offsets) because this has
 * definitely never been thought of before and is of course used ubiquitously to save
 * every byte, hence why Steam games are now several hundred gigabytes instead of
 * several hundred megabytes.
*/

#ifndef PROJECT_AQUINAS_POINTER_H
#define PROJECT_AQUINAS_POINTER_H

#include "platform.h"

typedef uintptr_t pointer;
// planned
typedef union long_pointer {
}               long_pointer;

typedef struct relative_pointer {
    pointer base;
    pointer offset;
} __attribute__((aligned(16))) relative_pointer;

typedef struct pointer_group {
    uqword identifier;
} pointer_group;

relative_pointer pointer_form(register uintptr_t const base, register uintptr_t const offset);

/*
 * A revolutionary function that splits an address into base and offset, deterministically even.
 */
relative_pointer pointer_deconstruct(void *restrict const address, uqword const pointer_size);

/*
 * A revolutionary function that sums a base and an offset into a single void pointer. Imagine that.
 */
void *pointer_reconstruct(relative_pointer const ptr);

pointer_group pointer_group_create();

#endif //PROJECT_AQUINAS_POINTER_H
