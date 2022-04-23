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
 * A robust and efficient memory manager.
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

/*
 * A pointer table that stores rewritten offsets and indices. Holds up to 2**16 (64KiB) bytes.
 */
// pointer = base + (256 * offset) + index * alignment;
typedef struct mmu_pointer_map {

} mmu_pointer_map;

#define MMU_HEAP_BLOCK_METADATA_BITS 2
typedef struct mmu_heap_metadata {
    uint8_t type:2;
    // Determines whether the heap does or does not grow in size.
    //
    // STATIC: does not allocate more memory after initialization.
    // Heap size remains constant throughout its lifetime.
    // If on a platform that uses paged memory,
    // all memory is allocated once to a single pointer.
    //
    // Space Complexity: Omega(1), Theta(1), O(1)
    // Time Complexity (alloc/free): Omega(1), Theta(1), O(log n)
    //
    // DYNAMIC: allocates memory as needed after initialization.
    // Heap size may vary throughout its lifetime.
    //
    // Space Complexity: Omega(1), Theta(n), O(n)
    // Time Complexity (alloc/free): Omega(1), Theta(1), O(log n)
    uint8_t temporal_affinity:2;
    // number of bytes in a value as 2**(alignment + 1)
    uint8_t alignment:4;
    // offset into block_table
    uint8_t offset_head;
    uint8_t index_head;
    // number of blocks allocated between 1 and 256 blocks (blocks = block_count + 1)
    uint8_t block_count;
    // a table that tracks the state of each block
    // block:
    //  block_table_offset + block_bit_index + 0 = enum block_sate
    //  0:
    //
    // block_table_offset = (offset * MMU_HEAP_BLOCK_METADATA_BITS) / sizeof(typeof(block_table));
    // block_bit_index = (offset * MMU_HEAP_BLOCK_METADATA_BITS) / sizeof(typeof(uint8_t));
    //
    uint8_t block_table[64];
    mmu_pointer_map pointers;
} mmu_heap_metadata;

typedef struct mmu_heap16 {
    mmu_heap_metadata table;
    void              *nodes;
} mmu_heap16;

typedef struct mmu_heap32 {
    mmu_heap_metadata table;
    mmu_heap16        **nodes;
} mmu_heap32;

typedef struct mmu_heap48 {
    mmu_heap_metadata table;
    mmu_heap32        **nodes;
} mmu_heap48;

typedef struct mmu_heap64 {
    mmu_heap_metadata table;
    mmu_heap48        **nodes;
} mmu_heap64;

typedef struct mmu_heap {
    mmu_heap_metadata table;
    struct mmu_heap   **nodes;
} mmu_heap;

typedef struct mmu_rel_ptr16 {
    __attribute__((unused)) uint8_t _pad0[6];
    uint8_t offset;
    uint8_t index;
} mmu_rel_ptr16;

typedef struct mmu_rel_ptr32 {
    __attribute__((unused)) uint8_t _pad0[4];
    uint8_t node16_offset;
    uint8_t node16_index;
    uint8_t offset;
    uint8_t index;
} mmu_rel_ptr32;

typedef struct mmu_rel_ptr48 {
    __attribute__((unused)) uint8_t _pad0[2];
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
 * Reserves sufficient space of at least the number of specified values on the given heap. The number of values is
 * values + 1.
 */
mmu_rel_ptr mmu_reserve(mmu_heap *, uint64_t values);

/*
 * Ensures that a particular pointer has sufficient subsequent available addresses on the given heap. Due to the
 * simplicity of this implementation, the heap may take up significant memory if a pointer is extended too often.
 * As such, it is best to avoid extension where possible except in the case of a series of sequential extensions.
 *
 * The number of values is values + 1.
 */
mmu_rel_ptr mmu_extend(mmu_heap *, mmu_rel_ptr, uint64_t values);

/*
 * Relinquishes the memory partition associated with the given pointer. The heap implementation is free to do what it
 * pleases with the partition itself.
 */
void mmu_relinquish(mmu_heap *, mmu_rel_ptr);

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
