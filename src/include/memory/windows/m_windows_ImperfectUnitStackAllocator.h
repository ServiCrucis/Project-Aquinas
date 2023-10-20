/*
 * Module: m_windows_ImperfectUnitStackAllocator
 * File: m_windows_ImperfectUnitStackAllocator.h
 * Created:
 * October 19, 2023
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 * License: See LICENSE.txt
 *
 * Defines the ImperfectUnitStackAllocator implementation for Win32.
 */

#ifndef PROJECT_AQUINAS_M_WINDOWS_IMPERFECTUNITSTACKALLOCATOR_H
#define PROJECT_AQUINAS_M_WINDOWS_IMPERFECTUNITSTACKALLOCATOR_H

#include "platform.h"

typedef udqword m_windows_stack_pointer;

typedef struct {
    m_windows_stack_pointer (*allocate)(void);
    m_windows_stack_pointer (*allocate_all)(udqword bits);
    void (*deallocate)();
    void (*deallocate_all)(m_windows_stack_pointer from, m_windows_stack_pointer to);
} ImperfectUnitStackAllocator;

void w32_stack_create(udqword program_lifetime_bit_quantity);
void w32_stack_destroy(void);

m_windows_stack_pointer w32_stack_allocate(void);
m_windows_stack_pointer w32_stack_allocate_all(udqword const bits);
void w32_stack_deallocate();
void w32_stack_deallocate_all(m_windows_stack_pointer from, m_windows_stack_pointer to);

#endif //PROJECT_AQUINAS_M_WINDOWS_IMPERFECTUNITSTACKALLOCATOR_H
