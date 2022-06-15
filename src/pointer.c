/*
* Module: pointer
* File: pointer.c
* Created:
* June 12, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
 * A stupidly simple pointer implementation that supports this incredibly revolutionary
 * new concept known as compressed pointers (pointer offsets) because this has
 * definitely never been thought of before and is of course used ubiquitously to save
 * every byte, hence why Steam games are now several hundred gigabytes instead of
 * several hundred megabytes.
*/

#include "pointer.h"
#include "bit_math.h"

pointer ptr_compress(register void *restrict const address, register uqword const ptr_size) {
    // the purpose is defeated if the pointer is greater than the size of a native address
    if (ptr_size > sizeof(void *))
        fatalf(__func__, "pointer is greater than sizeof(void *): %u\n", ptr_size);
    
    // Bruh, if you can just alloca FAMs... why not just standardize it?
    pointer *result = alloca(sizeof(pointer) + ptr_size);
    result->base          = (uintptr_t) filter((uqword) address, abs_diff(sizeof(address), ptr_size) * 8, ptr_size * 8);
    result->offset_bytes  = ptr_size;
    
    // Ugly FAM noise because associating intuitive semantics to syntax is too much for a committee
    // to accomplish in twenty-three years. L+ratio, ISO.
    union {
        void  *ptr;
        ubyte data[sizeof(address)];
    }       address_bytes = { ptr:address };
    
    // Ugly FAM noise because associating intuitive semantics to syntax is too much for a committee
    // to accomplish in twenty-three years. L+ratio, ISO.
    for (udword i = 0; i < ptr_size; ++i) {
        result->offset[i] = address_bytes.data[i];
    }
    
    return *result;
}

void *ptr_decompress(pointer const address) {
    if (address.offset_bytes > sizeof(void *))
        fatalf(__func__, "pointer is greater than sizeof(void *): %u\n", address.offset_bytes);
    
    // read address offset
    ubyte data[address.offset_bytes];
    for (udword i = 0; i < address.offset_bytes; ++i) {
        data[i] = address.offset[i];
    }
    
    
}

