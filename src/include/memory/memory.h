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
#include "m_object.h"

enum m_object_type {
    STATE = 0,
    BEHAVIOR = 1
};

enum m_state_type {
    /*
     * Defines the memory object to be read-only.
     */
    READ=1,
    
    /*
     * Defines the memory object to be write-only.
     */
    WRITE=2,
    
    /*
     * Defines the memory object to be readable and writable.
     */
    READ_WRITE=0,
    
    /*
     * Defines the memory object to be unreadable and unwritable.
     *
     * Win32: defines one or more virtual memory pages to be marked as
     * PAGE_NOACCESS. Attempting to read, write, or execute the committed page(s)
     * results in EXCEPTION_ACCESS_VIOLATION.
     * See https://learn.microsoft.com/en-us/windows/win32/memory/memory-protection-constants
     */
    NO_READ_NO_WRITE=3
};

/*
 * A memory interface for partitioning an infinite address space in $[0, +\infty)$.
 */
typedef struct memory_interface {
    /*
     * Reserves a partition to be associated with an integer representing this memory partition.
     * The m_object_type parameter indicates whether the memory is for state or behavior.
     * The m_state_type parameter indicates whether the memory can be read and/or written.
     *
     * It is maintained that the value returned by this procedure is implementation-defined, but has
     * a standard interface in BC and AD, therefore its use within a C runtime or similar environment
     * can be taken as implementation defined.
     *
     * In BC, as memory is implicit so as to decouple software from the constraints of finite
     * memory, these procedures are provided optionally by an allocator language module which
     * the programmer is free to use or not use for organizing data within a memory context.
     * Each unique memory context is infinitely addressable from [0, +\infty). Note that
     * although memory is implicit, the use of such allocators is subject to the same
     * constraints as that of C's memory model. Furthermore, in such model, one is free
     * to choose any positive integer address, whereas this restriction present in the C
     * allocator is only due to C's own memory model.
     *
     * In C, this value has a void pointer that may be directly accessed according to the usual pointer
     * semantics without any special arithmetic.
     *
     * As there is no memory resizing in this model, the pointer is guaranteed to not change
     * throughout its lifetime.
     */
    m_object *(*m_reserve)(uqword const bits, enum m_object_type, enum m_state_type);
    
    /*
     * Relinquishes the partition associated with the given m_object. If the m_object
     * given has no associated memory partition, the procedure will terminate the
     * program. In C, if the object's pointer is NULL, the procedure returns immediately.
     *
     * In BC, as memory is implicit so as to decouple software from the constraints of finite
     * memory, these procedures are provided optionally by an allocator language module which
     * the programmer is free to use or not use for organizing data within a memory context.
     * Each unique memory context is infinitely addressable from [0, +\infty). Note that
     * although memory is implicit, the use of such allocators is subject to the same
     * constraints as that of C's memory model. Furthermore, in such model, one is free
     * to choose any positive integer address, whereas this restriction present in the C
     * allocator is only due to C's own memory model.
     *
     * In C, the m_object's pointer is set to NULL.
     */
    m_object *(*m_relinquish)(m_object *);
} memory_interface;

/*
 * Reserves a partition to be associated with an integer representing this memory partition.
 * The m_object_type parameter indicates whether the memory is for state or behavior.
 * The m_state_type parameter indicates whether the memory can be read and/or written.
 *
 * It is maintained that the value returned by this procedure is implementation-defined, but has
 * a standard interface in BC and AD, therefore its use within a C runtime or similar environment
 * can be taken as implementation defined.
 *
 * In BC, as memory is implicit so as to decouple software from the constraints of finite
 * memory, these procedures are provided optionally by an allocator language module which
 * the programmer is free to use or not use for organizing data within a memory context.
 * Each unique memory context is infinitely addressable from [0, +\infty). Note that
 * although memory is implicit, the use of such allocators is subject to the same
 * constraints as that of C's memory model. Furthermore, in such model, one is free
 * to choose any positive integer address, whereas this restriction present in the C
 * allocator is only due to C's own memory model.
 *
 * In C, this value has a void pointer that may be directly accessed according to the usual pointer
 * semantics without any special arithmetic.
 *
 * As there is no memory resizing in this model, the pointer is guaranteed to not change
 * throughout its lifetime.
 */
m_object m_reserve(udqword const bits, enum m_object_type, enum m_state_type);

/*
 * Relinquishes the partition associated with the given m_object. If the m_object
 * given has no associated memory partition, the procedure will terminate the
 * program. In C, if the object's pointer is NULL, the procedure returns immediately.
 *
 * In BC, as memory is implicit so as to decouple software from the constraints of finite
 * memory, these procedures are provided optionally by an allocator language module which
 * the programmer is free to use or not use for organizing data within a memory context.
 * Each unique memory context is infinitely addressable from [0, +\infty). Note that
 * although memory is implicit, the use of such allocators is subject to the same
 * constraints as that of C's memory model. Furthermore, in such model, one is free
 * to choose any positive integer address, whereas this restriction present in the C
 * allocator is only due to C's own memory model.
 *
 * In C, the m_object's pointer is set to NULL.
 */
void m_relinquish(m_object *);

#endif //PROJECT_AQUINAS_MEMORY_H
