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

typedef struct m_object {
    void *pointer;
} __attribute__((aligned(8))) w32_m_object;

__attribute__((always_inline))
w32_m_object w32_m_reserve(udqword const bits, enum m_object_type object_type, enum m_state_type state_type) {
    m_object object;
    DWORD    page_options = 0, page_protections = 0;
    page_options |= MEM_RESERVE | MEM_COMMIT;
    
    switch (state_type) {
        case READ:
            switch (object_type) {
                case STATE:
                    page_protections |= PAGE_READONLY;
                    break;
                case BEHAVIOR:
                    page_protections |= PAGE_EXECUTE_READ;
                    break;
                default:
                    fatalf(__func__, "impossible condition, SEU or "
                                     "system instability detected: illegal value: object_type: %llu\n", (uqword) object_type);
            }
            break;
        case WRITE:
            switch (object_type) {
                case STATE:
                    // FIXME find and implement write-only access context for pages
                    page_protections |= PAGE_READWRITE;
                    break;
                case BEHAVIOR:
                    page_protections |= PAGE_EXECUTE_READWRITE;
                    break;
                default:
                    fatalf(__func__, "impossible condition, SEU or "
                                     "system instability detected: illegal value: object_type: %llu\n", (uqword) object_type);
            }
            break;
        case READ_WRITE:
            switch (object_type) {
                case STATE:
                    page_protections |= PAGE_READWRITE;
                    break;
                case BEHAVIOR:
                    page_protections |= PAGE_EXECUTE_READWRITE;
                    break;
                default:
                    fatalf(__func__, "impossible condition, SEU or "
                                     "system instability detected: illegal value: object_type: %llu\n", (uqword) object_type);
            }
            break;
        case NO_READ_NO_WRITE:
            switch (object_type) {
                case STATE:
                case BEHAVIOR:
                    page_protections |= PAGE_NOACCESS;
                    break;
                default:
                    fatalf(__func__, "impossible condition, SEU or "
                                     "system instability detected: illegal value: object_type: %llu\n", (uqword) object_type);
            }
            break;
        default:
            fatalf(__func__, "impossible condition, SEU or "
                             "system instability detected: illegal value: state_type: %llu\n", (uqword) state_type);
    }
    
    // init object pointer
    object.pointer = VirtualAlloc(NULL, (DWORD) (bits >> floor_log2i(8)), page_options, page_protections);
    return object;
}

__attribute__((always_inline))
void w32_m_relinquish(w32_m_object *const object) {
    VirtualFree(object->pointer, 0, MEM_RELEASE);
}

struct memory_interface const GLOBAL_WIN32_MEMORY_INTERFACE = {
        m_reserve: &w32_m_reserve,
        m_relinquish: &w32_m_relinquish
};

#ifndef BC_GLOBAL_MEMORY_INTERFACE
  #define BC_GLOBAL_MEMORY_INTERFACE GLOBAL_WIN32_MEMORY_INTERFACE

m_object m_reserve(udqword bits, enum m_object_type object_type, enum m_state_type state_type) {
    return w32_m_reserve(bits, object_type, state_type);
}

void m_relinquish(m_object *object) {
    w32_m_relinquish(object);
}

#endif
