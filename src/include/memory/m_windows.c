/*
* Module: m_windows
* File: m_windows.c
* Created:
* June 23, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
 *
 * Implements the memory model on the Windows platform (Microsoft Windows).
 * Where possible, the Win32 API is used directly.
 *
*/


#include <malloc.h>
#include "m_windows.h"
#include "m_object.h"
#include "platform.h"
#include "memory.h"
#include "state.h"
#include "bit_math.h"

#include <memoryapi.h>

struct m_object {
};




struct memory_interface const GLOBAL_WIN32_MEMORY_INTERFACE = {
        m_reserve: &w32_m_reserve,
        m_resize: &w32_m_resize,
        m_relinquish: &w32_m_relinquish
};

struct memory_interface const GLOBAL_MEMORY_INTERFACE = {
        m_reserve: &w32_m_reserve,
        m_resize: &w32_m_resize,
        m_relinquish: &w32_m_relinquish
};