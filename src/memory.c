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
// number of sectors per cache
static size_t *cache_sectors;
// cpuid info for x86
static struct x86_cpuid_info *cpuid_info;

//static void *stack_heap;

//static void *heap_metadata;


static inline void m_init_page_size(size_t *_page_size) {
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

static inline void m_init_cpu_info(size_t *_caches, size_t **_cache_size, size_t *_behavior_cache_size, size_t **_sector_size, size_t *_word_size) {
    // initialize cpu info based on data model
    #if ARCH_VARIANT == ARCH_X86_32
    // execute CPUID; fatalf if CPUID is unsupported
    if (!__x86_cpuid_supported()) fatalf(__func__, "Unable to initialize CPU info: CPUID instruction not supported");
    cpuid_info = __x86_cpuid();

    *_caches = cpuid_info->cache_topologies;
    // initialize cache and sector size
    *_cache_size = malloc(7 * sizeof(size_t));
    *_sector_size = &(*_cache_size)[3];
    // 1KiB = 1024 bytes
    *_behavior_cache_size = (size_t) (cpuid_info->L1IcSize * 1024u);
    (*_cache_size)[L1] = (size_t) (cpuid_info->L1DcSize * 1024u);
    (*_cache_size)[L2] = (size_t) (cpuid_info->L2Size * 1024u);
    // 512KiB = 524,288 bytes
    if (cpuid_info->L3Size == 8192)
        (*_cache_size)[L3] = 0xFFFFFFFFu;
    else
        (*_cache_size)[L3] = (size_t) (cpuid_info->L3Size * 524288u);

    (*_sector_size)[L1_DATA] = (size_t) cpuid_info->cache_topology[L1_DATA].CacheLineSize + 1;
    (*_sector_size)[L1_INSTRUCTION] = (size_t) cpuid_info->cache_topology[L1_INSTRUCTION].CacheLineSize + 1;
    (*_sector_size)[L2_UNIFIED] = (size_t) cpuid_info->cache_topology[L2_UNIFIED].CacheLineSize + 1;
    (*_sector_size)[L3_UNIFIED] = (size_t) cpuid_info->cache_topology[L3_UNIFIED].CacheLineSize + 1;
    *_word_size = 32u;
    #elif ARCH_VARIANT == ARCH_X86_64
    // execute CPUID; fatalf if CPUID is unsupported
    if (!__x64_cpuid_supported()) fatalf(__func__, "Unable to initialize CPU info: CPUID instruction not supported");
    cpuid_info = __x64_cpuid();

    *_caches = cpuid_info->cache_topologies;
    // initialize cache and sector size
    *_cache_size = malloc(7 * sizeof(size_t));
    *_sector_size = &(*_cache_size)[3];
    // 1KiB = 1024 bytes
    *_behavior_cache_size = (size_t) (cpuid_info->L1IcSize * 1024u);
    (*_cache_size)[L1] = (size_t) (cpuid_info->L1DcSize * 1024u);
    (*_cache_size)[L2] = (size_t) (cpuid_info->L2Size * 1024u);
    // 512KiB = 524,288 bytes
    (*_cache_size)[L3] = (size_t) (cpuid_info->L3Size * 524288u);
    (*_sector_size)[L1_DATA] = (size_t) cpuid_info->cache_topology[L1_DATA].CacheLineSize + 1;
    (*_sector_size)[L1_INSTRUCTION] = (size_t) cpuid_info->cache_topology[L1_INSTRUCTION].CacheLineSize + 1;
    (*_sector_size)[L2_UNIFIED] = (size_t) cpuid_info->cache_topology[L2_UNIFIED].CacheLineSize + 1;
    (*_sector_size)[L3_UNIFIED] = (size_t) cpuid_info->cache_topology[L3_UNIFIED].CacheLineSize + 1;
    *_word_size = 64u;
    #elif ARCH == ARCH_ARM
    #error "ARM platform not yet supported by memory module"
    #else
    #error "This platform is not currently supported by the memory module"
    #endif


}

void m_initialize() {
    m_init_page_size(&page_size);
    m_init_cpu_info(&caches, &cache_size, &behavior_cache_size, &sector_size, &word_size);
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
