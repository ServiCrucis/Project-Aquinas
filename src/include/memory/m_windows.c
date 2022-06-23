/*
* Module: m_windows
* File: m_windows.c
* Created:
* June 23, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
*/


#include "m_windows.h"
#include "pointer.h"
#include "platform.h"
#include "memory.h"

static inline relative_pointer w32_m_reserve(uqword const context, uqword const identifier, udqword const bits) {
}

static inline relative_pointer w32_m_resize(uqword const context, uqword const identifier, udqword const bits) {
}

static inline void w32_m_relinquish(uqword const context, uqword const identifier) {
}

relative_pointer m_reserve(uqword const context, uqword const identifier, udqword const bits) {
    return w32_m_reserve(context, identifier, bits);
}

relative_pointer m_resize(uqword const context, uqword const identifier, udqword const bits) {
    return w32_m_resize(context, identifier, bits);
}

void m_relinquish(uqword const context, uqword const identifier) {
    w32_m_relinquish(context, identifier);
}

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