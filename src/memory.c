/*
 * # memory.c
 * ## Created:
 * November 6th, A.D. 2019
 * ## Author:
 * Andrew Thomas Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2019 Christi Crucifixi, LLC. All rights reserved.
 */
#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	#include <windows.h>
#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	#include <unistd.h>
#endif

#ifndef DYNAMIC_HEAP
	#define DYNAMIC_HEAP true
#endif

#include <stdbool.h>

#include "error.h"
#include "memory.h"
#include "platform.h"
#include "math.h"

// page-aligned heap
static struct heap *heap;
// the size of a page in bytes
static size_t *cache_size; // in bytes
static size_t page_size; // in bytes
static size_t *sector_size; // a cache sector in bytes
static size_t word_size; // in bytes
// number of CPU caches available
static size_t caches = 0;
// size of the heap in pages
static size_t pages = 0;

struct block {
	// pointer to previous block
	uintptr_t prev;
	// number of bytes in this block
	size_t size;
	// the data of this block
	void *data;
};
// the offset of a block's metadata relative to the data pointer
#define METADATA sizeof(struct block) - sizeof(void *)

static inline void __m_init_page_size(size_t *_page_size) {
	//  set `page_size`
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	*_page_size = (size_t) info.dwPageSize;
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	*_page_size = (size_t) sysconf(_SC_PAGE_SIZE);
	#else
		#error "platform not yet supported"
	#endif
	if (!*_page_size) {
		r_debug_fatalf(R_INITIALIZATION_FAILURE, __func__, "failed to initialize page_size");
	}
}

static inline void __m_init_cpu_info(size_t *_caches, size_t **_cache_size, size_t **_sector_size, size_t *_word_size) {
	// initialize word size
	*_word_size = sizeof(uintptr_t);

	// !!!
	// (can use our memory functions from this point onwards)
	// !!!

	// initialize processor information
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	register WINBOOL (*GetLogicalProcessorInformationEx)(LOGICAL_PROCESSOR_RELATIONSHIP, PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX, PDWORD);
	GetLogicalProcessorInformationEx = (WINBOOL (*)(LOGICAL_PROCESSOR_RELATIONSHIP, PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX, PDWORD)) p_get_fn("kernel32", "GetLogicalProcessorInformationEx");

	if (!GetLogicalProcessorInformationEx) {
		r_debug_fatalf(R_INITIALIZATION_FAILURE, __func__, "failed to initialize function kernel32.GetLogicalProcessorInformation (error code: %X", GetLastError());
	}
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *pinfo = NULL;
	DWORD size = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
	// populate SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer
	register size_t len = 0;
	do {
		m_resize(pinfo, size);
		GetLogicalProcessorInformationEx(RelationCache, (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX) pinfo, &size);
		len++;
	} while (GetLastError() == ERROR_INSUFFICIENT_BUFFER);
	// initialize caches
	*_caches = len;
	// initialize cache_size array
	_cache_size = m_get(len * sizeof(size_t));
	// initialize sector_size
	_sector_size = m_get(len * sizeof(size_t));
	// read contents of SYSTEM_LOGICAL_PROCESSOR_INFORMATION array
	register size_t i = 0;
	for (register SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *current = pinfo; ((uintptr_t) current) < (len * sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)); current += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)) {
		switch (current->Relationship) {
			case RelationCache:
				*_cache_size[i] = current->Cache.CacheSize;
				*_sector_size[i] = current->Cache.LineSize;
				break;
			case RelationProcessorCore:
			case RelationNumaNode:
			case RelationProcessorPackage:
			case RelationGroup:
			case RelationAll:
			default:
				r_debug_infof(R_SUCCESS, __func__, "Ignoring unexpected Relationship: %X", current->Relationship);
				break;
		}
		// increment i
		i++;
	}

	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX __m_init_cpu_info
	#else
		#error "platform not yet supported"
	#endif
}

void m_heap_create(size_t minbytes, size_t maxbytes) {
	//  set `page_size`
	__m_init_page_size(&page_size);

	// initialize `heap`
	if (!heap) {
		pages = (size_t) (maxbytes / page_size);
		size_t size = pages * page_size;
		heap->memory = malloc(size);
		heap->size = size;

		if (!heap) {
			r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "failed to allocate heap (size: %d bytes)", minbytes);
		}
	}

	// initialize cache count, cache size, cache line size, and word size
	__m_init_cpu_info(&caches, &cache_size, &sector_size, &word_size);

	// set heap pointer variables
	heap->last_block = (uintptr_t) NULL;
	heap->next_block = (uintptr_t) heap->memory;
}

void m_heap_resize(size_t minbytes) {

}

/*
 * # `static inline void *__m_get(size_t minbytes, uintptr_t heap, size_t size, uintptr_t last_block, uintptr_t next_block);`
 *
 * Finds a pointer to an available block of memory that is at least minbytes bytes in size, but may be longer. The
 * calculation is based on the number of native words in order to prevent fragmentation. It is the responsibility of the
 * user of this memory interface to align data as needed, such as according to cache size, page size, sector size, or
 * only word size.
 *
 * ## `size_t minbytes`
 * The minimum size of the block in bytes
 *
 * ## `uintptr_t _heap`
 * A pointer to an allocated heap object
 *
 * ## `size_t _word_size`
 * The size of a native word in bytes (usually `sizeof(uintptr_t)`)
 *
 * ## `size_t size`
 * The size of the heap in bytes
 *
 * ## `uintptr_t last_block`
 * A pointer to the last block that was allocated on the heap
 *
 * ## `uintptr_t next_block`
 * A pointer to the next available position of a `struct block` on the heap
 *
 * ## `return;`
 * `void`
 */
static inline uintptr_t __m_get(size_t minbytes, struct heap *_heap, size_t _word_size) {
	struct block *block = (struct block *) _heap->next_block;
	block->prev = _heap->last_block;
	block->size = (size_t) (minbytes / _word_size) * _word_size;
	return (uintptr_t) block->data;
}

static inline void __m_free(void *ptr, struct heap *_heap) {
	struct block *block = ((struct block *) ptr - METADATA);
	// update heap pointers
	_heap->last_block = block->prev;
	_heap->next_block = (uintptr_t) block;
	block->prev = (uintptr_t) NULL;
	block->size = 0;
}

void *m_get(size_t minbytes) {
	uintptr_t memory = __m_get(minbytes, heap, word_size);
	struct block *block = (struct block *) (memory - METADATA);
	heap->last_block = (uintptr_t) memory;
	heap->next_block = (memory + block->size);
	return (void *) memory;
}

void *m_resize(void *ptr, size_t minbytes) {
	if (!ptr) {
		return m_get(minbytes);
	}
	// get the block that holds `ptr`
	struct block *block = (struct block *) ((uintptr_t) ptr - METADATA);
	// get the next block following this one
	struct block *next = (struct block *) ((uintptr_t) block + block->size);
	// check if the next block is empty and `minbytes` is greater than the size of the block
	if (minbytes > block->size && !next->size) {
		// increase block size to be at least `minbytes` in size
		block->size += (size_t) ((minbytes - block->size) / word_size) * word_size;
		// resize heap if necessary
		// compare last heap address with the address immediately following this block
		if (((uintptr_t) heap + heap->size - word_size) < ((uintptr_t) block->data + block->size - word_size)) {
			m_heap_resize(heap->size + minbytes);
		}

		return ptr;
	} else {
		ptr = NULL;
		return NULL;
	}
}

void m_free(void *ptr) {
	__m_free(ptr, heap);
}

static inline void __m_copy(void *src, size_t srclen, void *dst, size_t dstlen, size_t offset) {
	if (!dst) {
		r_debug_fatalf(R_NULL_POINTER, __func__, "dst (arg 3) is NULL");
	}

	size_t max = srclen < dstlen ? srclen : dstlen;
	if (offset >= max) {
		r_debug_fatalf(R_ILLEGAL_VALUE, __func__, "offset (arg 5) is greater than or equal to the length of the largest input for either src (arg 1) or dst (arg 3) (%d [arg 5] >= %d [arg 2 or arg 4])", offset, max);
	}
	// check if memory is aligned to native words or not
	if (((max / word_size) * word_size) < max) {

	}
	// copy the words from src to dst
	for (size_t i = offset; i < (max - word_size); i++) {
		((uintptr_t *) dst)[i] = ((uintptr_t *) src)[i];
	}

}

void m_copy(void *src, void *dst, size_t offset) {
	size_t srclen = ((struct block *) src - METADATA)->size;
	size_t dstlen = ((struct block *) dst - METADATA)->size;
	__m_copy(src, srclen, dst, dstlen, offset);
}

void m_copyd(void *src, size_t srclen, void *dst, size_t dstlen, size_t offset) {
	__m_copy(src, srclen, dst, dstlen, offset);
}

// sets all values to the given value, otherwise fills all possible words
static inline void __m_set(void *memory, uintptr_t value) {
	if (!memory) {
		r_debug_fatalf(R_NULL_POINTER, __func__, "memory (arg 1) is NULL");
	}

	struct block *block = (struct block *) ((uintptr_t) memory - METADATA);
	for (size_t i = 0; i < block->size; i++) {
		((uintptr_t *) block->data)[i] = value;
	}
}

static inline void __m_setd(void *memory, uintptr_t value, size_t len) {
	if (!memory) {
		r_debug_fatalf(R_NULL_POINTER, __func__, "memory (arg 1) is NULL");
	}

	struct block *block = (struct block *) ((uintptr_t) memory - METADATA);
	// compute the difference of len and word size
	size_t res = (len / word_size) * word_size;
	// set initial value of last
	size_t last;
	if (res != len) {
		last = len - (len - res);
	} else {
		last = len;
	}

	for (size_t i = 0; i < last; i++) {
		((uintptr_t *) block->data)[i] = value;
	}
}

/*
 * # `static inline void __m_setv(void *memory, uintptr_t value, size_t len);`
 * Sets the bytes in `memory` of size `len` bytes to a specific `value` of the given `stride`. If `stride` is not a power
 * of 2, and `len` is not a product of the multiplier `stride`, the behavior is undefined.
 *
 *
 */
static inline void __m_setv(void *memory, uint8_t const *value, uint8_t stride, size_t len) {
	if (!memory) {
		r_debug_fatalf(R_NULL_POINTER, __func__, "memory (arg 1) is NULL");
	}
	// set the values of memory
	for (size_t i = 0; i < len; i += stride) {
		for (size_t j = 0; j < stride; j++) {
			((uint8_t *) memory)[i + j] = value[j];
		}
	}
}

void m_set(void *memory, uintptr_t value) {
	__m_set(memory, value);
}

void m_setd(void *memory, uintptr_t value, size_t len) {
	__m_setd(memory, value, len);
}

void m_setv(void *memory, uint8_t *value, uint8_t stride) {
	__m_setv(memory, value, stride, ((struct block *) memory - METADATA)->size);
}

void m_setvd(void *memory, uint8_t *value, uint8_t stride, size_t len) {
	__m_setv(memory, value, stride, len);
}

size_t m_get_cache_size(enum cache cache) {
	return cache_size[cache];
}

size_t m_get_page_size() {
	return page_size;
}

size_t m_get_sector_size(enum cache cache) {
	return sector_size[cache];
}

size_t m_get_word_size() {
	return word_size;
}

size_t m_get_caches() {
	return caches;
}

size_t m_get_cache_sectors(enum cache cache) {
	return cache_size[cache] / sector_size[cache];
}
