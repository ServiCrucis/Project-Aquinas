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
		r_debug_fatalf(R_INITIALIZATION_FAILURE, __func__, "failed to initialize page_size");
	}
}

static inline void __m_init_cpu_info(size_t *_caches, size_t *_cache_size, size_t *_sector_size, size_t *_word_size) {
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
	register WINBOOL (*GetLogicalProcessorInformationEx)(LOGICAL_PROCESSOR_RELATIONSHIP, PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX, PDWORD);
	GetLogicalProcessorInformationEx = (WINBOOL (*)(LOGICAL_PROCESSOR_RELATIONSHIP, PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX, PDWORD)) p_get_fn("kernel32", "GetLogicalProcessorInformationEx");

	if (!GetLogicalProcessorInformationEx) {
		r_debug_fatalf(R_INITIALIZATION_FAILURE, __func__, "failed to initialize function kernel32.GetLogicalProcessorInformation (error code: %X", GetLastError());
	}
	DWORD size = sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
	auto SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *pinfo = malloc(size);
	// populate SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer
	do {
		m_resize(pinfo, size);
	} while (!GetLogicalProcessorInformationEx(RelationCache, (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX) pinfo, &size));
	// read contents of SYSTEM_LOGICAL_PROCESSOR_INFORMATION array
	register size_t i = 0;
	for (register SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *current = pinfo; ((uintptr_t) current) < ((uintptr_t) pinfo + size) && i < 3; current = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *) ((uintptr_t) current + current->Size)) {
		switch (current->Relationship) {
			case RelationCache:
				i = current->Cache.Level - 1;
				switch (current->Cache.Type) {
					case CacheUnified:
					case CacheInstruction:
						break;
					case CacheData:
						_cache_size[i] = current->Cache.CacheSize;
						_sector_size[i] = current->Cache.LineSize;
						break;
					case CacheTrace:
					default:
						r_debug_infof(R_SUCCESS, __func__, "Ignoring irrelevant cache type: 0x%X\n", current->Cache.Type);
						break;
				}
				break;
			case RelationProcessorCore:
			case RelationNumaNode:
			case RelationProcessorPackage:
			case RelationGroup:
			case RelationAll:
			default:
				r_debug_infof(R_SUCCESS, __func__, "Ignoring irrelevant relationship: 0x%X\n", current->Relationship);
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
}

void m_heap_create(size_t minbytes) {
	heap = malloc(sizeof(struct heap));
	__m_init_page_size(&page_size);
	__m_init_cpu_info(&caches, cache_size, sector_size, &word_size);
	heap->memory = malloc((minbytes / page_size) * page_size + 1);

}

void m_heap_destroy() {
	if (heap) {
		if (heap->memory) {
			free(heap->memory);
		}
		if (heap->ptable) {
			free(heap->ptable);
		}
	}
}

void m_heap_resize(size_t minbytes) {
}

void *m_block(size_t minbytes) {
}

void *m_resize(void *ptr, size_t minbytes) {
}

void m_free(void *ptr) {
}

void *m_copy(void *src, void *dst, size_t offset) {
}

void *m_set(void *memory, uintptr_t value) {
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
