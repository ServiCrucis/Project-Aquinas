/*
* Module: m_windows
* File: m_windows.c
* Created:
* June 23, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
 *
 * Implements the memory model on the Windows platform (Microsoft Windows).
 * Where possible, the Win32 API is used directly.
 *
*/


#include <malloc.h>
#include "m_windows.h"
#include "m_object.h"
#include "platform.h"
#include "memory.h"
#include "state.h"
#include "bit_math.h"

#include <heapapi.h>

// Note to self:
// structs will be called named maps
typedef struct cache_block_metadata {
    // in bits
    ubyte free_offset;
}                              cache_block_metadata;

typedef struct cache_block {
    ubyte data[32];
} __attribute__((aligned(32))) cache_block;

struct m_object_metadata {
    // from this is determined the size
    // of offsets
    udword eleemnts;
    ubyte offsets[];
};

// bytes metadata:data = 1:256 = 1:8 metadata:cache_block_metadata



// memory hierarchy:
// object->element


// memory attributes:
// static/dynamic        - size
// contiguous/continuous - distribution in memory - let software implement



/*
 * Memory layout:
 * fetch_group: size is memory bus throughput
 *
 *
 */
/*
 */
static inline m_object w32_m_reserve_direct(uqword const context, uqword const identifier, udqword const bits) {
}

/*
 */
static inline m_object w32_m_resize_direct(uqword const context, uqword const identifier, udqword const bits) {
}

/*
 */
static inline void w32_m_relinquish_direct(uqword const context, uqword const identifier) {
}

m_object m_reserve(uqword const context, uqword const identifier, udqword const bits) {
}

m_object m_resize(uqword const context, uqword const identifier, udqword const bits) {
}

void m_relinquish(uqword const context, uqword const identifier) {
}

struct memory_interface const GLOBAL_WIN32_MEMORY_INTERFACE = {
        m_reserve: &w32_m_reserve,
        m_resize: &w32_m_resize,
        m_relinquish: &w32_m_relinquish
};

struct memory_interface const GLOBAL_MEMORY_INTERFACE = {
        m_reserve: &w32_m_reserve,
        m_resize: &w32_m_resize,
        m_relinquish: &w32_m_relinquish
};