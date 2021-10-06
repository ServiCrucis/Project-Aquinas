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
        fatalf(__func__, "alignment must be at most 7: alignment: %u", alignment);
    }
    
    mmu_heap *heap = calloc(1, sizeof(*heap));
    heap->table.type              = (uint8_t) type;
    heap->table.temporal_affinity = (uint8_t) heap_affinity;
    heap->table.alignment         = alignment;
    return heap;
}

void mmu_heap_destroy(mmu_heap *heap) {
    if (heap) {
        if (!heap->nodes) {
            free(heap);
            return;
        }
        
        mmu_heap       *node;
        uint32_t       i     = 0;
        const uint32_t nodes = heap->table.node_count * 256u;
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

void *mmu_to_abs_ptr(mmu_heap *heap, mmu_rel_ptr ptr) {
}

mmu_rel_ptr mmu_to_rel_ptr(mmu_heap *heap, void *ptr) {
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

static inline ubyte n_consecutive_homo8(ubyte n, ubyte consecutive_ones, ubyte input_operand) {
}

/*
 * Finds n consecutive zeroes or ones patterns. For zeroes, consecutive_ones should be set to zero; for ones,
 * consecutive_ones should be set to one. input_operand is the value for which we want to find n consecutive zeroes or
 * ones. For finding n consecutive, arbitrary bit patterns, see n_consecutive_hetero.
 */
static inline uqword n_consecutive_homo(uqword n, uqword consecutive_ones, uqword input_operand) {
    input_operand                  = consecutive_ones ? input_operand : ~input_operand;
    uint8_t powers_of_two          = ~0;
    uint8_t power_of_two_remainder = 0;
    
    for (uint8_t i = 0; i < sizeof(n); i++) {
    }
}

/*
 * Find first offset. Finds the first bit offset (the number of times you must shift right to get the value of the bit)
 * of the given search_pattern within test_pattern. All other occurrences are ignored. Returns -1 if search_pattern is
 * not a valid subpattern of test_pattern as an index offset.
 */
static inline int8_t ffo8(uint8_t test_pattern, uint8_t search_pattern) {
    uint8_t a = test_pattern / search_pattern;
    a = sigbits(a);
    
}

static inline mmu_rel_ptr mmu_check_continuity(mmu_heap *heap, uint16_t values) {
    #define mmu_block_alignment uqword
    const ubyte blocks      = sizeof(heap->table.allocation_tree) >> sizeof(mmu_block_alignment);
    uqword      allocation_tree[blocks];
    uqword      regs[blocks];
    uqword      free_blocks = 0;
    
    // count number of free blocks
    for (ubyte i = 0; i < blocks; i++) {
        regs[i] = ones(allocation_tree[i]);
    }
    // determine which blocks meet the number of required sequential blocks
    
    
    #undef mmu_block_alignment
}

static inline mmu_rel_ptr mmu_heap16_alloc(mmu_heap16 *heap, uint16_t values) {
    /*
     * Allocation process:
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
    
    ubyte path = 0;
    
    // static or dynamic bit
    path |= (heap->table.temporal_affinity);
    // full/not full bit
    path |= (heap->table.node_count == 255u) << 1u;
    // free/not free bit
    path |= (heap->table.full_flag) << 2u;
    // continuous/not continuous bit
    bool continuity;
    
    
    
    // unconditional jump (near)
    switch (path) {
        // static, not full, offsets free
        case 0x0:
            break;
            // dynamic, not full, offsets free
        case 0x1:
            break;
            // static, full, offsets free
        case 0x2:
            break;
            // dynamic, full, offsets free
        case 0x3:
            break;
            // static, not full, no free offsets
        case 0x4:
            break;
            // dynamic, not full, no free offsets
        case 0x5:
            break;
            // static, full, no free offsets
        case 0x6:
            break;
            // dynamic, full, no free offsets
        case 0x7:
            break;
        default:
            break;
    }
    
    return mmu_to_rel_ptr((mmu_heap *) heap, object);
}

mmu_rel_ptr mmu_heap_alloc(mmu_heap *heap, uint16_t values) {
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
