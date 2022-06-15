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

typedef ubyte pointer8;

typedef uword pointer16;

typedef ubyte pointer24[3];

typedef udword pointer32;

typedef ubyte pointer40[5];

typedef ubyte pointer48[6];

typedef ubyte pointer56[7];

typedef uqword pointer64;

typedef struct pointer {
    uintptr_t base;
    ubyte        offset_bytes;
    ubyte        offset[];
}            pointer;

/*
 * A revolutionary function that splits an address into base and offset, deterministically even.
 */
pointer ptr_compress(register void *restrict const address, uqword const ptr_size);

/*
 * A revolutionary function that sums a base and an offset into a single void pointer. Imagine that.
 */
void *ptr_decompress(pointer const ptr);



#endif //PROJECT_AQUINAS_POINTER_H
