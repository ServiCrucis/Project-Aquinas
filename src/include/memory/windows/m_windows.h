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

#include "memory/memory.h"
#include "m_windows_ImperfectUnitStackAllocator.h"

extern ImperfectUnitStackAllocator const M_WINDOWS_WIN32_GLOBAL_IMPERFECT_UNIT_STACK_ALLOCATOR;

extern ImperfectUnitAllocator const M_WINDOWS_WIN32_GLOBAL_PERFECT_UNIT_ALLOCATOR;

extern ImperfectAllocator const M_WINDOWS_WIN32_GLOBAL_PERFECT_ALLOCATOR;

extern PerfectAllocator const M_WINDOWS_WIN32_GLOBAL_IMPERFECT_ALLOCATOR;

//typedef void *w32_m_object;
//
//enum w32_object_type {
//    STATE = 0,
//    CAUSING = 1
//};
//
//enum w32_state_type {
//    /*
//     * Defines the memory object to be read-only.
//     */
//    READ = 1,
//
//    /*
//     * Defines the memory object to be write-only.
//     */
//    WRITE = 2,
//
//    /*
//     * Defines the memory object to be readable and writable.
//     */
//    READ_WRITE = 0,
//
//    /*
//     * Defines the memory object to be unreadable and unwritable.
//     *
//     * Win32: defines one or more virtual memory pages to be marked as
//     * PAGE_NOACCESS. Attempting to read, write, or execute the committed page(s)
//     * results in EXCEPTION_ACCESS_VIOLATION.
//     * See https://learn.microsoft.com/en-us/windows/win32/memory/memory-protection-constants
//     */
//    NO_READ_NO_WRITE = 3
//};

#endif //PROJECT_AQUINAS_M_WINDOWS_H
