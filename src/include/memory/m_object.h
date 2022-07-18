/*
* Module: m_object
* File: m_object.h
* Created:
* June 12, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
 *
 *
 * A stupidly simple m_object implementation that facilitates this incredibly revolutionary
 * new concept known as compressed pointers (m_object offsets) because this has
 * definitely never been thought of before and is of course used ubiquitously to save
 * every byte, hence why Steam games are now several hundred gigabytes instead of
 * several hundred megabytes.
*/

#ifndef PROJECT_AQUINAS_M_OBJECT_H
#define PROJECT_AQUINAS_M_OBJECT_H

#include "platform.h"

// x86 BC pointer composition:
// [    0,         2]: 3 bits: bit offset
// [    3,     2 + n]: n bits: byte offset
// [3 + n, 2 + n + m]: m bits: cache_block offset
// bits: block_group offset

// 3 bits for element size (2^k)
// 1 bit for cache_block existence
// 8 bits for elements used

typedef struct m_object_metadata m_object_metadata;
typedef struct m_object {
    m_object_metadata *metadata;
} m_object;

#endif //PROJECT_AQUINAS_M_OBJECT_H
