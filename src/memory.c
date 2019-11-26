/*
 * # memory.c
 * ## Created:
 * November 6th, A.D. 2019
 * ## Author:
 * Andrew Thomas Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2019 Christi Crucifixi, LLC. All rights reserved.
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	#include <windows.h>
#include <stdbool.h>
#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	#include <unistd.h>
#endif
#if MEMORY_MALLOC_OVERWRITE
	#include <stdlib.h>
#endif

#ifndef DYNAMIC_HEAP
	#define DYNAMIC_HEAP true
#endif

#include "debug.h"
#include "memory.h"
#include "platform.h"
#include "libcpuid.h"
#include "math.h"

// page-aligned heap
static void *heap;
// heap info
static size_t heap_size; // in bytes
static uintptr_t last_block;
static uintptr_t next_block;
// the size of a page in bytes
static size_t *cache_size; // in bytes
static size_t page_size; // in bytes
static size_t *sector_size; // a cache sector in bytes
static size_t word_size; // in bytes
// number of CPU caches available
static size_t caches = 0;
// size of the heap in pages
static size_t pages = 0;
// the cpuid info
static struct cpu_id_t cpuid;

// TODO convert Win32 error codes to POSIX-compatible enum codes.

struct m_block {
	// pointer to previous m_block
	uintptr_t prev;
	// number of words following this block of memory
	size_t words;
};

static inline void *__sysheap() {
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	return GetProcessHeap();
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX __sysheap
	#else
	r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "platform not yet supported (detected platform: %s)", PLATFORM_NAME);
	#endif
}

static inline void *__sys_create_heap(size_t heap_size) {
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	return HeapCreate(0, heap_size, (size_t) ((1 + (double) 1 / 3) * heap_size));
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX __sysheap
	#else
	r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "platform not yet supported (detected platform: %s)", PLATFORM_NAME);
	#endif
}

static inline void __sys_free_heap(void *heap) {
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	HeapDestroy(heap);
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX __sys_resize_heap
	#else
	r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "platform not yet supported (detected platform: %s)", PLATFORM_NAME);
	#endif
}

static inline void *__sys_resize_heap(void *heap, size_t new_size) {
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	// TODO Win32 __sys_resize_heap
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX __sys_resize_heap
	#else
	r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "platform not yet supported (detected platform: %s)", PLATFORM_NAME);
	#endif
}

static inline void *__sysmalloc(size_t _Size) {
	void *memory = NULL;
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	if (!HeapAlloc(heap, 0, _Size)) {
		_set_errno(GetLastError());
	}
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX malloc
	#else
	r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "platform not yet supported (detected platform: %s)", PLATFORM_NAME);
	#endif
	return memory;
}

static inline void *__syscalloc(size_t _NumOfElements, size_t _SizeOfElements) {
	void *memory = NULL;
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	if (!HeapAlloc(heap, HEAP_ZERO_MEMORY, _NumOfElements * _SizeOfElements)) {
		_set_errno(GetLastError());
	}
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX calloc
	#else
	r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "platform not yet supported (detected platform: %s)", PLATFORM_NAME);
	#endif

	return memory;
}

static inline void *__sysrealloc(void *_Memory, size_t _NewSize) {
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	if (!HeapReAlloc(heap, 0, _Memory, _NewSize)) {
		_set_errno(GetLastError());
	}
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX realloc
	#else
r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "platform not yet supported (detected platform: %s)", PLATFORM_NAME);
	#endif
}

void m_init(size_t bytes) {
	// initialize local scope `struct cpu_raw_data_t`
	struct cpu_raw_data_t *raw = NULL;
	if (!cpuid_get_raw_data(raw)) {
		r_debug_fatalf(R_INITIALIZATION_FAILURE, __func__, "failed to initialize cpu_raw_data_t");
	}
	// ---
	// initialize `static struct cpu_id_t cpuid`
	if (!cpu_identify(raw, &cpuid)) {
		r_debug_fatalf(R_INITIALIZATION_FAILURE, __func__, "failed to initialize cpuid");
	}
	// ---
	//  set `page_size`
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	page_size = (size_t) info.dwPageSize;
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	page_size = (size_t) sysconf(_SC_PAGE_SIZE);
	#endif

	if (!page_size) {
		r_debug_fatalf(R_INITIALIZATION_FAILURE, __func__, "failed to initialize page_size");
	}
	// ---
	// initialize `heap`
	if (!heap) {
		pages = (size_t) (bytes / page_size);
		heap_size = pages * page_size;
		heap = __sys_create_heap(heap_size);
	} else {
		#if DYNAMIC_HEAP == false
		r_debug_fatalf(R_ALLOCATION_FAILURE,
					   __func__,
					   "you must compile with DYNAMIC_HEAP set to 1 in order to resize the heap.");
		#else
		if (bytes != heap_size) {
			// expand the heap
			if (bytes > heap_size) {
				#if R_DEBUG
				r_debug_info(__func__, "expanding heap from %d bytes to %d bytes", heap_size, bytes);
				#endif
				pages = (size_t) (bytes / page_size);
				heap_size = pages * page_size;
				__sys_resize_heap(heap, heap_size);
			} else if (bytes < heap_size) { // attempt to shrink the heap
				#if R_DEBUG
				r_debug_info(__func__, "expanding heap from %d bytes to %d bytes", heap_size, bytes);
				#endif
				pages = (size_t) (bytes / page_size);
				heap_size = pages * page_size;
				__sys_resize_heap(heap, heap_size);
			} else {
				r_debug_fatalf(R_FAILURE,
				               __func__,
				               "unexpected condition: heap_size was not >, <, ==, or !=; system has non-binary condition principle(s)");
			}
		}
		#endif
	}

	if (!heap) {
		r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "failed to allocate heap (size: %d bytes)", bytes);
	}

	// ---
	// determine cache quantity and size
	caches = 0;
	cache_size[L1] = cpuid.l1_data_cache;
	caches++;
	cache_size[L2] = cpuid.l2_cache;
	if (cache_size[L2]) caches++;
	cache_size[L3] = cpuid.l3_cache;
	if (cache_size[L3]) caches++;
	cache_size[L4] = cpuid.l4_cache;
	if (cache_size[L4]) caches++;
	// determine sector size (cache line size)
	sector_size[L1] = cpuid.l1_cacheline;
	sector_size[L2] = cpuid.l2_cacheline;
	sector_size[L3] = cpuid.l3_cacheline;
	sector_size[L4] = cpuid.l4_cacheline;
	// ---
	// initialize `word_size`
	word_size = sizeof(uintptr_t);

	// set heap pointer variables
	last_block = (uintptr_t) NULL;
	next_block = (uintptr_t) heap;
}

/*
 * # `static inline void *__m_find(size_t minbytes, uintptr_t heap, size_t heap_size, uintptr_t last_block, uintptr_t next_block);`
 *
 * Finds a pointer to an available block of memory that is at least minbytes bytes in size, but may be longer. The
 * calculation is based on the number of native words in order to prevent fragmentation. It is the responsibility of the
 * user of this memory interface to align data as needed, such as according to cache size, page size, sector size, or
 * only word size.
 *
 * ## `size_t minbytes`
 * The minimum size of the block in bytes
 *
 * ## `uintptr_t heap`
 * A pointer to an allocated heap object
 *
 * ## `size_t word_size`
 * The size of a native word in bytes (usually `sizeof(uintptr_t)`)
 *
 * ## `size_t heap_size`
 * The size of the heap in bytes
 *
 * ## `uintptr_t last_block`
 * A pointer to the last block that was allocated on the heap
 *
 * ## `uintptr_t next_block`
 * A pointer to the next available position of a `struct m_block` on the heap
 *
 * ## `return;`
 * `void`. If needed, may TODO return a status code in a struct m_result
 */
static inline void *__m_find(size_t minbytes, uintptr_t heap, size_t word_size, size_t heap_size, uintptr_t next_block) {
	struct m_block *block = ((struct m_block *) next_block);
	block->prev = last_block;
	block->words = (size_t) (minbytes / word_size);
	#if DYNAMIC_HEAP // resizes the heap if necessary
		#if R_DEBUG
	r_debug_info(__func__, "expanding heap from %d pages to %d pages", pages, pages + 1);
		#endif
	size_t bytes = block->words * word_size;
	size_t remaining = (size_t) ((heap + heap_size) - (next_block + sizeof(struct m_block)));
	if (bytes > remaining) {
		// allocate more memory to the heap
		if (!realloc((void *) heap, (heap_size) + (page_size))) {
			r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "failed to expand heap size from %d pages (%d bytes) to %d pages (%d bytes)", pages, heap_size, pages + 1, heap_size + page_size);
		}
		pages++;
	}
	#endif
	return ((void *) (last_block + sizeof(struct m_block)));
}

/*
 * # `static inline void __m_cleanup(void *ptr, size_t len);`
 *
 * Sets the block of memory at `ptr` of length `len` words to zero, and any other necessary cleanup.
 *
 * ## `void *ptr`
 * The block of memory immediately succeeding a `struct m_block`
 *
 * ## `size_t len`
 * The number of native words in the block of memory
 */
static inline void __m_cleanup(void *ptr) {
	struct m_block *block = ((struct m_block *) ptr - sizeof(struct m_block));
	block->prev = (uintptr_t) NULL;
	block->words = 0;
}

void *m_get(size_t minbytes) {
	void *m = __m_find(minbytes, (uintptr_t) heap, word_size, heap_size, next_block);
	last_block = (uintptr_t) m;
	next_block = last_block + (((struct m_block *) m - sizeof(struct m_block))->words * word_size);
	return m;
}

#if MEMORY_MALLOC_OVERWRITE
void *malloc(size_t _Size) {
	return __m_find(_Size, heap, word_size, heap_size, last_block, next_block);
}
#endif

void m_free(void *ptr) {
	struct m_block *block = ((struct m_block *) ptr - sizeof(struct m_block));
	// update heap pointers
	last_block = block->prev;
	next_block = (uintptr_t) block;
	// performs any necessary cleanup operations
	__m_cleanup(ptr);
}

void m_frees(void *ptr) {
	m_free(ptr);
	uint8_t value = { 0 };
	m_set(ptr, &value, 1);
}

#if MEMORY_MALLOC_OVERWRITE
void free(void *_Memory) {
	__m_cleanup(_Memory);
}
#endif

void *m_getn(size_t minbytes) {
	void *m = __m_find(minbytes, (uintptr_t) heap, word_size, heap_size, next_block);
	struct m_block *block = ((struct m_block *) m - sizeof(struct m_block));
	memset(m, 0, block->words * word_size);
	return m;
}

static inline void __m_copy(void *src, size_t srclen, void *dst, size_t dstlen, size_t offset) {
	// if dst is NULL, create dst
	if (!dst) {
		r_debug_fatalf(R_NULL_POINTER, __func__, "dst (arg 3) is NULL");
	}

	size_t max = srclen < dstlen ? srclen : dstlen;
	// return NULL if the offset is not within bounds
	if (offset >= max) {
		r_debug_fatalf(R_ILLEGAL_VALUE, __func__, "offset (arg 5) is greater than or equal to the length of the largest input for either src (arg 1) or dst (arg 3) (%d [arg 5] >= %d [arg 2 or arg 4])", offset, max);
	}
	// copy the words from src to dst
	for (size_t i = offset; i < max; i++) {
		((char *) dst)[i] = ((char *) src)[i];
	}
}

void m_copy(void *src, void *dst, size_t offset) {
	size_t srclen = ((struct m_block *) src - sizeof(struct m_block))->words * word_size;
	size_t dstlen = ((struct m_block *) dst - sizeof(struct m_block))->words * word_size;
	__m_copy(src, srclen, dst, dstlen, offset);
}

void m_copyd(void *src, size_t srclen, void *dst, size_t dstlen, size_t offset) {
	__m_copy(src, srclen, dst, dstlen, offset);
}

/*
 * # `static inline void __m_set(void *memory, uintptr_t value, size_t len);`
 * Sets the bytes in `memory` of size `len` bytes to a specific `value` of the given `stride`. If `stride` is not a power
 * of 2, and `len` is not a product of the multiplier `stride`, the behavior is undefined.
 *
 *
 */
static inline void __m_set(void *memory, uint8_t const *value, uint8_t stride, size_t len) {
	if (!memory) {
		r_debug_fatalf(R_NULL_POINTER, __func__, "memory (arg 1) is NULL");
	}
	// set the values of memory
	for (size_t i = 0; i < len; i += stride) {
		for (uint8_t j = 0; j < stride; j++) {
			((uint8_t *) memory)[i + j] = value[j];
		}
	}
}

void m_set(void *memory, uint8_t *value, uint8_t stride) {
	__m_set(memory, value, stride, ((struct m_block *) memory - sizeof(struct m_block))->words * word_size);
}

void m_setd(void *memory, uint8_t *value, uint8_t stride, size_t len) {
	__m_set(memory, value, stride, len);
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

#pragma clang diagnostic pop
