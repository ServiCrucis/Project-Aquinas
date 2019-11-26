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
	L1, L2, L3, L4
};

/*
 * # `void m_init(size_t);`
 * Initializes memory.c's internal components.
 *
 * ## `size_t bytes`
 * The size of the heap in bytes for the duration of the program.
 */
void m_init(size_t bytes);

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
 * ## `return void *`
 * A pointer to a block of allocated memory
 */
void *m_get(size_t minbytes);

/*
 * Frees the given block of memory.
 */
void m_free(void *ptr);

/*
 * Securely frees the given block of memory by zeroing the memory after freeing.
 */
void m_frees(void *ptr);

/*
 * Gets the next available memory block on the heap and clears the values to zero.
 */
void *m_getn(size_t minbytes);

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
