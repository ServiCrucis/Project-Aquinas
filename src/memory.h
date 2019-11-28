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
	void *memory;
	uintptr_t last_block;
	uintptr_t next_block;
	size_t size;
};

/*
 * # `void m_init(size_t);`
 * Initializes memory.c's internal components.
 *
 * ## `size_t minbytes`
 * The minimum size of the heap in bytes for the duration of the program.
 *
 * ## `size_t maxbytes`
 * The maximum size of the heap in bytes for the duration of the program.
 */
void m_sysheap_create(size_t minbytes, size_t maxbytes);

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
 * Gets the next available memory block on the heap and clears the values to zero.
 */
void *m_getn(size_t minbytes);

/*
 * Resizes the given block of memory to minbytes.
 */
void *m_resize(void *ptr, size_t minbytes);

/*
 * Frees the given block of memory.
 */
enum result_code m_free(void *ptr);

/*
 * Securely frees the given block of memory by zeroing the memory after freeing.
 */
enum result_code m_frees(void *ptr);

/*
 *
 */
void m_copy(void *src, void *dst, size_t offset);

/*
 *
 */
void m_copyd(void *src, size_t srclen, void *dst, size_t dstlen, size_t offset);

/*
 *
 */
void m_set(void *memory, uint8_t *value, uint8_t stride);

void m_setd(void *memory, uint8_t *value, uint8_t stride, size_t len);

size_t m_get_cache_size(enum cache cache);

size_t m_get_page_size();

size_t m_get_cache_sector_size();

size_t m_get_word_size();

size_t m_get_caches();

size_t m_get_cache_sectors(enum cache cache);

#endif /* MEMORY_H_ */
