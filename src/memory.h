/*
 * # memory.h
 * ## Created:
 * November 6, A.D. 2019
 * ## Author:
 * Andrew Thomas Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2019 Christi Crucifixi, LLC. All rights reserved.
 */

#include <stdint.h>
#include "state.h"

#ifndef PROJECT_AQUINAS_MEMORY_H
#define PROJECT_AQUINAS_MEMORY_H

typedef enum cache {
    L1 = 0,
    L2 = 1,
    L3 = 2,
    L1_DATA = 0,
    L1_INSTRUCTION = 1,
    L2_UNIFIED = 2,
    L3_UNIFIED = 3
} cache;

void m_initialize();

void *m_create(uword bytes);

void m_delete(void *memory);

void *m_extend(void *memory, uword extra_bytes);

void *m_append(void *base, void *appendix);

void *m_reorder(void *memory, void *m_start, void *m_end);

size_t m_get_page_size();

size_t m_get_cache_size(enum cache);

// L1 instruction cache size
// for L1 data cache, use m_get_cache_size(L1)
size_t m_get_behavior_cache_size();

size_t m_get_sector_size(enum cache);

size_t m_get_word_size();

size_t m_get_caches();

size_t m_get_cache_sectors(enum cache);

#endif /* PROJECT_AQUINAS_MEMORY_H */
