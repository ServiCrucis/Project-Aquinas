/*
 * # memory.c
 * ## Created:
 * November 6, A.D. 2019
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

#include "state.h"
#include "memory.h"
#include "platform.h"
#include "math.h"

static heap current;
// the size of a page in bytes
static size_t *cache_size; // in bytes
static size_t page_size; // in bytes
static size_t *sector_size; // a cache sector in bytes
static size_t word_size; // in bytes
// number of CPU caches available
static size_t caches = 0;
// size of the heap in pages
static size_t pages = 0;

#define METADATA sizeof(struct block) - sizeof(uintptr_t)

// approximates the given size to a particular minimum size which will either be the size of a word, sector, cache,
// or page. If `minbytes` is greater than the size of a page, the returned value is guaranteed to be a multiple of
// `page_size`.
static inline size_t __m_approximate(size_t minbytes) {
	size_t page = page_size;
	size_t cache = cache_size[L1];
	size_t sector = sector_size[L1];
	size_t word = word_size;

	if (minbytes <= word) {
		return word;
	} else if (minbytes <= sector) {
		return sector;
	} else if (minbytes > page) {
		if (minbytes <= cache) {
			return cache;
		} else {
			return ((minbytes / page) * page) + (minbytes % page);
		}
	} else {
		return (minbytes / word_size) * word_size;
	}
}

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
		fatalf("initialization", __func__, "failed to initialize page_size");
	}
}

static inline void __m_init_cpu_info(size_t *_caches, size_t *_cache_size, size_t *_sector_size, size_t *_word_size) {
    set_context("memory");
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!! USE STANDARD MALLOC HERE ONLY !!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// initialize word size
	*_word_size = sizeof(uintptr_t);
	// initialize caches
	*_caches = 3;
	// initialize cache_size array
	_cache_size = malloc(3 * sizeof(size_t));
	// initialize sector_size
	_sector_size = malloc(3 * sizeof(size_t));

	// initialize processor information
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	DWORD size = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *pinfo = malloc(size);
	// populate SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer
	do {
		m_resize(pinfo, size);
	} while (!GetLogicalProcessorInformationEx(RelationCache, (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX) pinfo, &size));
	// read contents of SYSTEM_LOGICAL_PROCESSOR_INFORMATION array
	register size_t i = 0;
	for (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *current = pinfo; ((uintptr_t) current) < ((uintptr_t) pinfo + size) && i < 3; current = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *) ((uintptr_t) current + current->Size)) {
		switch (current->Relationship) {
			case RelationCache:
				i = current->Cache.Level - 1;
				switch (current->Cache.Type) {
					case CacheUnified:
					case CacheInstruction:
						break;
					case CacheData:
						_cache_size[i] = current->Cache.CacheSize;
						infof(R_SUCCESS, __func__, "_cache_size[i]: %u", _cache_size[i]);
						_sector_size[i] = current->Cache.LineSize;
						infof(R_SUCCESS, __func__, "_sector_size[i]: %u", _sector_size[i]);
						break;
					case CacheTrace:
					default:
						infof(R_SUCCESS, __func__, "Ignoring irrelevant cache type: 0x%X\n", current->Cache.Type);
						break;
				}
				break;
			case RelationProcessorCore:
			case RelationNumaNode:
			case RelationProcessorPackage:
			case RelationGroup:
			case RelationAll:
			default:
				infof(R_SUCCESS, __func__, "Ignoring irrelevant relationship: 0x%X\n", current->Relationship);
				break;
		}
	}
	// free the memory used for our SYSTEM_LOGICAL_PROCESSOR_INFORMATION array
	free(pinfo);
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX __m_init_cpu_info
	#else
		#error "platform not yet supported"
    #endif

    clear_context();
}

static inline heap __m_get_process_heap() {
	#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	HANDLE procheap = GetProcessHeap();
	size_t size = HeapSize(procheap, 0, &size);
		heap result = {size, procheap};
		
	#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	#endif
}

void m_init() {
	__m_init_page_size(&page_size);
	__m_init_cpu_info(&caches, cache_size, sector_size, &word_size);
	current = __m_get_process_heap();
}

void m_heap_resize(size_t minbytes) {
}

void *m_request(size_t minbytes) {
}

void *m_resize(void *ptr, size_t minbytes) {
}

void m_free(void *ptr) {
}

// chooses whether to use greater than or less than depending on cardinality
// used by m_copy and m_set
static inline bool __cmp(size_t a, size_t b, cardinality cardinality) {
	switch (cardinality) {
		case UP:
		case LEFT:
			return a > b;
		case DOWN:
		case RIGHT:
			return a < b;
		default:
			fatalf("illegal value", __func__, "unknown cardinality: %d", cardinality);
			return false;
	}
}

void *m_copy(void *src, size_t srcoff, size_t srclen, cardinality srcdir, void *dst, size_t dstoff, size_t dstlen, cardinality dstdir) {
    set_context("memory");
	if (!src) {
		fatalf("null pointer", __func__, "src (arg 1) is NULL");
	}

	if (!dst) {
		fatalf("null pointer", __func__, "dst (arg 5) is NULL");
	}
	// array indices (with segfault init guard [UB])
	register size_t srci = -1, dsti = -1;
	// array index deltas (with 0 delta init guard [endless loop])
	register int8_t srcd = 0, dstd = 0;
	// array boundaries (with segfault init guard [UB])
	register size_t srcend = UINTPTR_MAX, dstend = UINTPTR_MAX;
	// initialize the source offset
	switch (srclen) {
		case UP:
		case LEFT:
			srci = srclen - 1;
			srcd = -1;
			srcend = -1;
			break;
		case DOWN:
		case RIGHT:
			srci = 0;
			srcd = 1;
			srcend = srclen;
			break;
		default:
			fatalf("illegal value", __func__, "unknown srcdir cardinality: %d", srcdir);
	}
	// initialize the destination offset
	switch (dstdir) {
		case UP:
		case LEFT:
			dsti = dstlen - 1;
			dstd = -1;
			dstend = -1;
			break;
		case DOWN:
		case RIGHT:
			dsti = 0;
			dstd = 1;
			dstend = dstlen;
			break;
		default:
			fatalf("illegal value", __func__, "unknown dstdir cardinality: %d", srcdir);
	}

	srci += srcd * srcoff;
	dsti += dstd * dstoff;

	for (; __cmp(srci, srcend, srcdir); srci += srcd) {
		for (; __cmp(dsti, dstend, dstdir); dsti += dstd) {
			((char *) dst)[dsti] = ((char *) src)[srci];
		}
	}

	return dst;
}

void *m_set(void *memory, size_t offset, size_t length, uintptr_t value, cardinality dir) {
	if (!memory) {
		fatalf("null pointer", __func__, "memory (arg 1) is NULL");
	}
	// memory offset (with segfault init guard [UB])
	register size_t i = -1;
	// memory offset delta, -1 or 1 (with infinite loop guard)
	register uint8_t delta = 0;
	// memory end position (with segfault init guard [UB])
	register size_t end = UINTPTR_MAX;
	// initialize memory index, delta, and end
	switch (dir) {
		case UP:
		case LEFT:
			i = length - 1;
			delta = -1;
			end = -1;
			break;
		case DOWN:
		case RIGHT:
			i = 0;
			delta = 1;
			end = length;
			break;
		default:
			fatalf("illegal value", __func__, "unknown cardinality: %d", dir);
	}
	// increment the memory index by offset (cardinality adjusted by delta)
	i += offset * delta;

	register size_t j = 0;
	for (; __cmp(i, end, dir); i += delta * sizeof(value)) {
		for (; __cmp(j, sizeof(value), dir); j++) {
			((char *) memory)[i + j * delta] = ((char *) value)[j];
		}
		j = 0;
	}

	return memory;
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
