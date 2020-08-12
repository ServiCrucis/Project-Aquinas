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

#include "state.h"
#include "memory.h"
#include "platform.h"
#include "asm.h"

// the size of a page in bytes
static size_t page_size; // in bytes
static size_t *cache_size; // in bytes
static size_t behavior_cache_size;
static size_t *sector_size; // a cache sector in bytes
static size_t word_size; // in bytes
// number of CPU caches available
static size_t caches = 0;
// size of the heap in pages
static size_t pages = 0;
// number of sectors per cache
static size_t *cache_sectors;

static inline void __m_init_page_size(size_t *_page_size) {
    //  set `page_size`
    #if PLATFORM == P_WINDOWS || ENVIRONMENT == P_WINDOWS
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    *_page_size = (size_t) info.dwPageSize;
    #elif PLATFORM == P_LINUX || ENVIRONMENT == P_UNIX
    *_page_size = (size_t) sysconf(_SC_PAGE_SIZE);
    #else
    #error "platform not yet supported"
    #endif
    if (!*_page_size) {
        fatalf(__func__, "failed to initialize page_size");
    }
}

static inline void __m_init_cpu_info(size_t *_caches, size_t *_cache_size, size_t *_behavior_cache_size, size_t *_sector_size, size_t *_word_size) {
    // execute CPUID; fatalf if CPUID is unsupported
    if (!__x64_cpuid_supported()) fatalf(__func__, "Unable to initialize CPU info: CPUID instruction not supported");
    struct x86_cpuid_info *cpu_info = __x64_cpuid();


}

void m_init() {
    __m_init_page_size(&page_size);
    __m_init_cpu_info(&caches, cache_size, &behavior_cache_size, sector_size, &word_size);
}

size_t m_get_page_size() {
    return page_size;
}

size_t m_get_cache_size(enum cache cache) {
    return cache_size[cache];
}

size_t m_get_behavior_cache_size() {
    return behavior_cache_size;
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
    return cache_sectors[cache];
}
