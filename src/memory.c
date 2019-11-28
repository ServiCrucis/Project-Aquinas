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
#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	#include <unistd.h>
#endif
#if MEMORY_MALLOC_OVERWRITE
	#include <stdlib.h>
#endif

#ifndef DYNAMIC_HEAP
	#define DYNAMIC_HEAP true
#endif

#include <stdbool.h>

#include "debug.h"
#include "memory.h"
#include "platform.h"
#include "math.h"

// page-aligned heap
static struct heap *heap;
// heap stack
static struct heap **hstack;
// heap stack pointer offset
static size_t sp_offset;
// the size of a page in bytes
static size_t *cache_size; // in bytes
static size_t page_size; // in bytes
static size_t *sector_size; // a cache sector in bytes
static size_t word_size; // in bytes
// number of CPU caches available
static size_t caches = 0;
// size of the heap in pages
static size_t pages = 0;

// TODO convert Win32 error codes to POSIX-compatible enum codes.

struct block_metadata {
	// pointer to previous block_metadata
	uintptr_t prev;
	// number of words following this block of memory
	size_t words;
};

// uintptr_t win2posix_enum(uintptr_t word_Win32_err)

static inline void *__sysheap() {
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	return GetProcessHeap();
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX __sysheap
	#else
	r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "platform not yet supported (detected platform: %s)", PLATFORM_NAME);
	#endif
}

static inline void *__sys_create_heap(size_t minbytes, size_t maxbytes) {
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	return HeapCreate(0, minbytes, maxbytes);
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX __sysheap
	#else
	r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "platform not yet supported (detected platform: %s)", PLATFORM_NAME);
	#endif
}

static inline enum result_code __sys_free_heap(void *heap) {
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	return HeapDestroy(heap) ? R_SUCCESS : R_FAILURE;
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX __sys_resize_heap
	#else
	r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "platform not yet supported (detected platform: %s)", PLATFORM_NAME);
	#endif
}

static inline void *__sysmalloc(size_t _Size, void *heap) {
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

static inline void *__syscalloc(size_t _NumOfElements, size_t _SizeOfElements, void *heap) {
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

static inline void *__sysrealloc(void *_Memory, size_t _NewSize, void *heap) {
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

static inline void __m_init_page_size(size_t *page_size) {
	//  set `page_size`
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	*page_size = (size_t) info.dwPageSize;
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	*page_size = (size_t) sysconf(_SC_PAGE_SIZE);
	#else
		#error "platform not yet supported"
	#endif
	if (!*page_size) {
		r_debug_fatalf(R_INITIALIZATION_FAILURE, __func__, "failed to initialize page_size");
	}
}

static inline void __m_init_cpu_info(size_t **cache_size, size_t **sector_size, size_t *word_size) {
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	// heap is already initialized before this function is called, so we use m_getn
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION pinfo = m_getn(sizeof(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION));
	DWORD size = sizeof(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION);
	if (!GetLogicalProcessorInformation(pinfo, &size)) {
		r_debug_fatalf(R_INITIALIZATION_FAILURE, __func__, "failed to initialize PSYSTEM_LOGICAL_PROCESSOR_INFORMATION (error code: %d", GetLastError());
	}

	// TODO Win32 __m_init_cpu_info

	*word_size = sizeof(uintptr_t);
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX __m_init_cpu_info
	#else
	r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "platform not yet supported (detected platform: %s)", PLATFORM_NAME);
	#endif
}

void m_sysheap_create(size_t minbytes, size_t maxbytes) {
	//  set `page_size`
	__m_init_page_size(&page_size);

	// initialize `heap`
	if (!heap) {
		pages = (size_t) (maxbytes / page_size);
		size_t size = pages * page_size;
		heap->memory = __sys_create_heap((size_t) (minbytes / page_size) * page_size, size);
		heap->size = size;

		if (!heap) {
			r_debug_fatalf(R_ALLOCATION_FAILURE, __func__, "failed to allocate heap (size: %d bytes)", minbytes);
		}
	}

	// initialize cache size, cache line size, and word size
	__m_init_cpu_info(&cache_size, &sector_size, &word_size);

	// set heap pointer variables
	heap->last_block = (uintptr_t) NULL;
	heap->next_block = (uintptr_t) heap->memory;
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
 * ## `uintptr_t heap`
 * A pointer to an allocated heap object
 *
 * ## `size_t word_size`
 * The size of a native word in bytes (usually `sizeof(uintptr_t)`)
 *
 * ## `size_t size`
 * The size of the heap in bytes
 *
 * ## `uintptr_t last_block`
 * A pointer to the last block that was allocated on the heap
 *
 * ## `uintptr_t next_block`
 * A pointer to the next available position of a `struct block_metadata` on the heap
 *
 * ## `return;`
 * `void`. If needed, may TODO return a status code in a struct m_result
 */
static inline uintptr_t __m_get(size_t minbytes, struct heap *heap, size_t word_size) {
	struct block_metadata *block = ((struct block_metadata *) heap->next_block);
	block->prev = ((struct heap *) heap)->last_block;
	block->words = (size_t) (minbytes / word_size);
	return heap->last_block + sizeof(struct block_metadata);
}

static inline enum result_code __m_free(void *ptr, struct heap *heap) {
	struct block_metadata *block = ((struct block_metadata *) ptr - sizeof(struct block_metadata));
	// update heap pointers
	heap->last_block = block->prev;
	heap->next_block = (uintptr_t) block;
	block->prev = (uintptr_t) NULL;
	block->words = 0;
	return R_SUCCESS;
}

void *m_get(size_t minbytes) {
	uintptr_t memory = __m_get(minbytes, heap, word_size);
	struct block_metadata *meta = (struct block_metadata *) (memory - sizeof(struct block_metadata));
	heap->last_block = (uintptr_t) memory;
	heap->next_block = (memory + meta->words * word_size);
	return (void *) memory;
}

#if MEMORY_MALLOC_OVERWRITE
void *malloc(size_t _Size) {
	return m_get(_Size);
}
#endif

void *m_getn(size_t minbytes) {
	void *result = m_get(minbytes);
	uint8_t *value = { 0 };
	m_set(result, value, 1);
	return result;
}

#if MEMORY_MALLOC_OVERWRITE
void *calloc(size_t _NumOfElements, size_t _ElementSize) {
	return m_getn(_NumOfElements * _ElementSize);
}
#endif

void *m_resize(void *ptr, size_t minbytes) {
	// TODO m_resize
}

enum result_code m_free(void *ptr) {
	return __m_free(ptr, heap);
}

enum result_code m_frees(void *ptr) {
	uint8_t *value = { 0 };
	m_set(ptr, value, 1);
	return __m_free(ptr, heap);
}

#if MEMORY_MALLOC_OVERWRITE
void free(void *_Memory) {
	__m_free(_Memory, heap);
}
#endif

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
	size_t srclen = ((struct block_metadata *) src - sizeof(struct block_metadata))->words * word_size;
	size_t dstlen = ((struct block_metadata *) dst - sizeof(struct block_metadata))->words * word_size;
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
	__m_set(memory, value, stride, ((struct block_metadata *) memory - sizeof(struct block_metadata))->words * word_size);
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

// manual mm functions

struct heap *mm_create_heap(size_t minbytes, size_t maxbytes) {
	struct heap *heap = (struct heap *) m_get(sizeof(struct heap));
	heap->memory = __sys_create_heap(minbytes, maxbytes);
	heap->last_block = (uintptr_t) heap->memory;
	*(struct block_metadata *) heap->last_block = (struct block_metadata) {
			heap->last_block,
			0
	};

	return heap;
}

enum result_code mm_free_heap(struct heap *heap) {
	return __sys_free_heap(heap->memory);
}

enum result_code mm_heap_stack_init(size_t heaps) {
	hstack = m_get(heaps * sizeof(struct heap *));
	if (!hstack) {
		return R_ALLOCATION_FAILURE;
	}
	sp_offset = 0;
	return R_INITIALIZATION_SUCCESS;
}

enum result_code mm_push(struct heap *heap) {
	hstack[sp_offset] = heap;
	sp_offset++;
	return R_SUCCESS;
}

struct heap *mm_pop() {
	sp_offset--;
	struct heap *heap = hstack[sp_offset];
	hstack[sp_offset] = NULL;
	return heap;
}

void *mm_get(size_t minbytes) {
	return (void *) __m_get(minbytes, hstack[sp_offset], word_size);
}

void *mm_getn(size_t minbytes) {
	void *result = (void *) __m_get(minbytes, hstack[sp_offset], word_size);
	m_set(result, (uint8_t *) { 0 }, 1);
	return result;
}

void *mm_resize(size_t minbytes) {

}

void *mm_free(void *ptr) {

}

#pragma clang diagnostic pop
