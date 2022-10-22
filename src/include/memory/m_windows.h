/*
 * Module: m_windows
 * File: m_windows.h
 * Created:
 * June 23, 2022
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 * License: See LICENSE.txt
 */

#ifndef PROJECT_AQUINAS_M_WINDOWS_H
#define PROJECT_AQUINAS_M_WINDOWS_H

#include "memory.h"

typedef void *w32_m_object;

extern struct memory_interface const GLOBAL_WIN32_MEMORY_INTERFACE;

struct memory_interface const GLOBAL_MEMORY_INTERFACE = GLOBAL_WIN32_MEMORY_INTERFACE;

#endif //PROJECT_AQUINAS_M_WINDOWS_H
