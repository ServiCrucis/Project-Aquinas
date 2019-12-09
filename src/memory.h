/*
 * # memory.h
 * ## Created:
 * November 6th, A.D. 2019
 * ## Author:
 * Andrew Thomas Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2019 Christi Crucifixi, LLC. All rights reserved.
 */

#include <stdint.h>
#include "error.h"

#ifndef MEMORY_H_
#define MEMORY_H_

enum cache {
	L1 = 0,
	L2 = 1,
	L3 = 3,
	L4 = 4,
	L_EXT = 0
	// `L_EXT` is the start of cache level extensions for CPUs or platforms offering more than four cache levels
	// and begins at zero for compatibility purposes. Access of `L_EXT + (level - 1)` greater than or equal to `caches`
	// is undefined behavior.
};

struct heap {
	uintptr_t last_block;
	uintptr_t next_block;
	size_t size;
	void *memory;
};

/*
 * # `void m_heap_create(size_t minbytes, size_t maxbytes);`
 * Initializes memory.c's internal heap (the process heap).
 *
 * ## `size_t minbytes`
 * The minimum size of the heap in bytes for the duration of the program.
 *
 * ## `size_t maxbytes`
 * The maximum size of the heap in bytes for the duration of the program.
 */
void m_heap_create(size_t minbytes, size_t maxbytes);

/*
 * # `void m_heap_resize(size_t minbytes);`
 * Resizes the heap with as many pages as are necessary to meet the minimum bytes requirement.
 * If the heap is greater than `minbytes` bytes, an attempt will be made to shrink the heap. Any memory outside this range
 * that is accessed after a call to this function is undefined behavior.
 *
 * If the heap is less than `minbytes` bytes, an attempt will be made to expand the heap.
 *
 *
 */
void m_heap_resize(size_t minbytes);

/*
 * # `size_t m_get_heap_size();`
 * Gets the actual size of the heap in bytes.
 *
 * ## `return size_t`
 * A value representing the size of the heap in bytes
 */
size_t m_get_heap_size();

/*
 * # `void *m_get(size_t minbytes);`
 * Gets the next available memory block on the heap.
 *
 * ## `return void *`
 * A pointer to a block of allocated memory, or NULL if we failed to find available memory
 */
void *m_get(size_t minbytes);

/*
 * Resizes the given block of memory to minbytes. If `ptr` is `NULL`, `ptr` will be initialized with `m_get(size_t)`.
 * If there is a block following this block, the function fails: `ptr` is set to `NULL`, and the function returns `NULL`.
 * The global error variable is set to `R_ILLEGAL_ACCESS` since in all single-threaded cases, the heap is a FIFO stack of
 * contiguous memory blocks, and position on the heap is temporally linear deterministic such that heap location is
 * dependent on what is currently executing, whereas a multi-threaded heap is temporally non-linear non-deterministic
 * such that heap location is dependent on thread competition. The latter is not the case with deterministic multi-
 * threaded environments, in which case position on the heap is contingent on execution order and temporal placement. For
 * all other cases, a different heap than this one is needed to make efficient use of m_resize as there is no guarantee
 * that the usage will be optimally linear.
 */
void *m_resize(void *ptr, size_t minbytes);

/*
 * Frees the given block of memory.
 */
void m_free(void *ptr);

void m_copy(void *src, void *dst, size_t offset);

void m_copyd(void *src, size_t srclen, void *dst, size_t dstlen, size_t offset);

void m_set(void *memory, uintptr_t value);

void m_setd(void *memory, uintptr_t value, size_t len);

void m_setv(void *memory, uint8_t *value, uint8_t stride);

void m_setvd(void *memory, uint8_t *value, uint8_t stride, size_t len);

size_t m_get_cache_size(enum cache cache);

size_t m_get_page_size();

size_t m_get_cache_sector_size();

size_t m_get_word_size();

size_t m_get_caches();

size_t m_get_cache_sectors(enum cache cache);

#endif /* MEMORY_H_ */
