#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-no-int-to-ptr"
/*
* Module: m_object
* File: m_object.c
* Created:
* June 12, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
 *
 * A stupidly simple m_object implementation that supports this incredibly revolutionary
 * new concept known as compressed pointers (m_object offsets) because this has
 * definitely never been thought of before and is of course used ubiquitously to save
 * every byte, hence why Steam games are now several hundred gigabytes instead of
 * several hundred megabytes.
*/

#include "m_object.h"
#include "bit_math.h"
#include "data.h"

#pragma clang diagnostic pop
