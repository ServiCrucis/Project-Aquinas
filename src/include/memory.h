/*
 * Module: memory
 * File: memory.h
 * Created:
 * May 03, 2021
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2021 Christi Crucifixi, LLC. All rights reserved.
 *
 * License: See LICENSE.txt
 *
 * A robust and efficient BC memory model implementation.
 */


#ifndef PROJECT_AQUINAS_MEMORY_H
#define PROJECT_AQUINAS_MEMORY_H

#include "platform.h"
#include <stdalign.h>
#include "dynarray.h"
#include "pointer.h"

typedef struct memory_interface {
    /*
     * Reserves a memory partition if applicable.
     * Calling this function tells the memory interface:
     * "I need this much memory right now."
     */
    relative_pointer (*m_reserve);
    
    /*
     * Resizes a memory partition if applicable.
     * Calling this function tells the memory interface:
     * "I need a different amount of memory right now."
     */
    relative_pointer (*m_resize);
    
    /*
     * Relinquishes a memory partition if applicable.
     * Calling this function tells the memory interface:
     * "I don't need this memory anymore."
     */
    relative_pointer (*m_relinquish);
} memory_interface;

/*
 * Reserves sufficient space of at least the number of specified bits.
 */
relative_pointer m_reserve(uqword const context, uqword const identifier, udqword const bits);

/*
 *
 */
relative_pointer m_resize(uqword const context, uqword const identifier, udqword const bits);

/*
 *
 */
void m_relinquish(uqword const context, uqword const identifier);

#endif //PROJECT_AQUINAS_MEMORY_H
