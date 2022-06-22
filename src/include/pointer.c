#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-no-int-to-ptr"
/*
* Module: pointer
* File: pointer.c
* Created:
* June 12, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
 *
 * A stupidly simple pointer implementation that supports this incredibly revolutionary
 * new concept known as compressed pointers (pointer offsets) because this has
 * definitely never been thought of before and is of course used ubiquitously to save
 * every byte, hence why Steam games are now several hundred gigabytes instead of
 * several hundred megabytes.
*/

#include "pointer.h"
#include "bit_math.h"
#include "data.h"

relative_pointer pointer_form(register uintptr_t const base, register uintptr_t const offset) {
    relative_pointer result = {
            base: base,
            offset: offset
    };
    
    return result;
}

relative_pointer pointer_deconstruct(void *const address, uqword const pointer_size) {
    if (pointer_size > sizeof(address))
        fatalf(__func__,
               "cannot deconstruct: pointer_size is larger than sizeof(address) (%llu bytes)\n",
               sizeof(address));
    uqword offset = filter((uqword) address, pointer_size * 8, 0);
    uqword base = ((uqword)address) - offset;
    return pointer_form(base, offset);
}

void *pointer_reconstruct(relative_pointer const ptr) {
    return (void *) (ptr.base + ptr.offset);
}

#pragma clang diagnostic pop
