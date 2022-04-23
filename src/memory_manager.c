/*
 * Module: memory_manager
 * File: memory_manager.c
 * Created:
 * May 03, 2021
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2021 Christi Crucifixi, LLC. All rights reserved.
 *
 * License: See LICENSE.txt
 */

#include <malloc.h>
#include <state.h>
#include <bit_math.h>
#include "memory_manager.h"

mmu_heap *mmu_heap_create(enum mmu_heap_type type, enum mmu_heap_temporal_affinity heap_affinity, uint8_t alignment) {
    if (alignment > 0x7u) {
        fatalf(__func__, "alignment must be at most a value of 7 (2**8 bytes): alignment: %u", alignment);
    }
    
    mmu_heap *heap = calloc(1, sizeof(*heap));
    heap->table.type              = (uint8_t) type;
    heap->table.temporal_affinity = (uint8_t) heap_affinity;
    heap->table.alignment         = alignment;
    return heap;
}

void mmu_heap_destroy(register mmu_heap *restrict heap) {
    if (heap) {
        if (!heap->nodes) {
            free(heap);
            return;
        }
        
        mmu_heap       *node;
        uint32_t       i     = 0;
        const register uint32_t nodes = heap->table.block_count;
    loop_head:
        node = heap->nodes[i];
        if (node) {
            // frees the node pointer recursively
            mmu_heap_destroy(node);
        }
        
        i++;
        if (i < nodes)
            goto loop_head;
        else
            return;
    } else {
        return;
    }
}

void *mmu_to_abs_ptr(mmu_heap *restrict heap, mmu_rel_ptr ptr) {
}

mmu_rel_ptr mmu_to_rel_ptr(mmu_heap *restrict heap, void *restrict ptr) {
}

static inline void *mmu_scan_for_pointer(mmu_heap *heap) {
}

static inline void *mmu_heap_alloc_ptr(mmu_heap *heap, uint16_t values) {
}

static inline mmu_rel_ptr mmu_heap64_alloc(mmu_heap64 *heap, uint16_t values) {
}

static inline mmu_rel_ptr mmu_heap48_alloc(mmu_heap48 *heap, uint16_t values) {
}

static inline mmu_rel_ptr mmu_heap32_alloc(mmu_heap32 *heap, uint16_t values) {
}

static inline mmu_rel_ptr mmu_heap16_alloc(mmu_heap16 *heap, uint16_t values) {
    /*
     * Allocation algorithm:
     *
     * 1. Update offset table:
     *  i. If offset table is full, scan for free offsets; then goto iii.
     *  ii. If offset table not full, goto iv.
     *  iii. If no free offsets, set result pointer to NULL.
     *  iv. If free offsets, check continuity.
     *  v. If sufficient continuous blocks, mark offset table with offsets; allocate if necessary.
     *  vi. If insufficient continuous blocks, set result pointer to NULL.
     * 2. Update offset and index heads.
     * 3. Update node count.
     * 4. Return result pointer.
     */
    void *object;
    
}

mmu_rel_ptr mmu_reserve(mmu_heap *heap, uint64_t values) {
    mmu_rel_ptr result;
    switch (heap->table.type) {
        case MMU_HEAP_64:
            result = mmu_heap64_alloc((mmu_heap64 *) heap, values);
            break;
        case MMU_HEAP_48:
            result = mmu_heap48_alloc((mmu_heap48 *) heap, values);
            break;
        case MMU_HEAP_32:
            result = mmu_heap32_alloc((mmu_heap32 *) heap, values);
            break;
        case MMU_HEAP_16:
            result = mmu_heap16_alloc((mmu_heap16 *) heap, values);
            break;
        default:
            result.ptr_value = 0u;
            break;
    }
    
    return result;
}
