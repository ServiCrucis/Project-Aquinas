/*
 * Module: memory_manager
 * File: memory_manager.h
 * Created:
 * May 03, 2021
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2021 Christi Crucifixi, LLC. All rights reserved.
 *
 * License: See LICENSE.txt
 *
 * A robust and efficient memory manager excelling at efficient memory management.
 */


#ifndef PROJECT_AQUINAS_MEMORY_MANAGER_H
#define PROJECT_AQUINAS_MEMORY_MANAGER_H

#include <platform.h>
#include <stdalign.h>
#include <dynarray.h>

// bytes
#define mmu_heap_node_allocation_unit 256u

enum mmu_heap_type {
    MMU_HEAP_16 = 0,
    MMU_HEAP_32 = 1,
    MMU_HEAP_48 = 2,
    MMU_HEAP_64 = 3,
};

enum mmu_heap_temporal_affinity {
    STATIC = 0, DYNAMIC = 1
};

typedef struct mmu_table {
    uint8_t type:2;
    uint8_t temporal_affinity:1;
    uint8_t full_flag:1;
    // number of bytes in a value
    uint8_t alignment:4;
    // allocation block queue heads
    uint8_t offset_head;
    uint8_t index_head;
    uint8_t node_count;
    // a bit tree denoting which blocks are free or allocated
    // 0 = free
    // 1 = allocated
    uint8_t allocation_tree[32];
    // pointer = base + (256 * offset) + index * alignment;
} mmu_table;

typedef struct mmu_heap16 {
    mmu_table table;
    void      *nodes;
} mmu_heap16;

typedef struct mmu_heap32 {
    mmu_table  table;
    mmu_heap16 **nodes;
} mmu_heap32;

typedef struct mmu_heap48 {
    mmu_table  table;
    mmu_heap32 **nodes;
} mmu_heap48;

typedef struct mmu_heap64 {
    mmu_table  table;
    mmu_heap48 **nodes;
} mmu_heap64;

typedef struct mmu_heap {
    mmu_table       table;
    struct mmu_heap **nodes;
} mmu_heap;

typedef struct mmu_rel_ptr16 {
    uint8_t _pad0[6];
    uint8_t offset;
    uint8_t index;
} mmu_rel_ptr16;

typedef struct mmu_rel_ptr32 {
    uint8_t _pad0[4];
    uint8_t node16_offset;
    uint8_t node16_index;
    uint8_t offset;
    uint8_t index;
} mmu_rel_ptr32;

typedef struct mmu_rel_ptr48 {
    uint8_t _pad0[2];
    uint8_t node32_offset;
    uint8_t node32_index;
    uint8_t node16_offset;
    uint8_t node16_index;
    uint8_t offset;
    uint8_t index;
} mmu_rel_ptr48;

typedef struct mmu_rel_ptr64 {
    uint8_t node48_offset;
    uint8_t node48_index;
    uint8_t node32_offset;
    uint8_t node32_index;
    uint8_t node16_offset;
    uint8_t node16_index;
    uint8_t offset;
    uint8_t index;
} mmu_rel_ptr64;

typedef union mmu_rel_ptr {
    uint8_t       bytes[8];
    uint64_t      ptr_value;
    mmu_rel_ptr16 ptr16;
    mmu_rel_ptr32 ptr32;
    mmu_rel_ptr48 ptr48;
    mmu_rel_ptr64 ptr64;
} mmu_rel_ptr;

/*
 * Creates an mmu_heap of the specified type
 */
mmu_heap *mmu_heap_create(enum mmu_heap_type, enum mmu_heap_temporal_affinity, uint8_t value_bytes);

/*
 * Frees an mmu_heap and all of its nodes
 */
void mmu_heap_destroy(mmu_heap *heap);

/*
 * Allocates sufficient space of at least the number of specified values on the given heap. The number of values is
 * values + 1.
 */
mmu_rel_ptr mmu_heap_alloc(mmu_heap *, uint16_t values);

/*
 * Requests that the specified offset be allocated with at least values values. The number of values is values + 1.
 */
mmu_rel_ptr mmu_heap_rqalloc(mmu_heap *, uint16_t values, mmu_rel_ptr);

/*
 * Ensures that a particular pointer has sufficient subsequent available addresses on the given heap. Due to the
 * simplicity of this implementation, the heap may take up significant memory if a pointer is reallocated too often.
 * As such, it is best to avoid reallocation where possible except in the case of a series of sequential reallocations.
 *
 * The number of values is values + 1.
 */
mmu_rel_ptr mmu_heap_realloc(mmu_heap *, mmu_rel_ptr, uint16_t values);

/*
 * Converts any relative pointer to an absolute pointer which can then be used by anything. Keep in mind that all
 * benefits of relative pointers are lost, and that it should be assumed that after an absolute pointer is used, any
 * subsequent uses of that pointer may be undefined behavior as the heap data pointer may change at any time.
 */
void *mmu_to_abs_ptr(mmu_heap *, mmu_rel_ptr);

/*
 * Converts a pointer to a relative pointer, even if the pointer is not within the range of addresses supported by the
 * given heap. Providing a pointer outside the range of addresses supported by the heap is undefined behavior.
 */
mmu_rel_ptr mmu_to_rel_ptr(mmu_heap *, void *);

#endif //PROJECT_AQUINAS_MEMORY_MANAGER_H
