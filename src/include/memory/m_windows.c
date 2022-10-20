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


#include "m_windows.h"
#include "m_object.h"
#include "memory.h"
#include "state.h"
#include "bit_math.h"

#include <memoryapi.h>

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
    const uqword bytes = ((bits >> 3) + ((bits & 0b111) > 0));
    object = VirtualAlloc(NULL, (DWORD) bytes, page_options, page_protections);
    return object;
}

__attribute__((always_inline))
void w32_m_transmute(m_object const object, enum m_object_type const object_type, enum m_state_type const state_type) {
    // TODO create robust global program status area to capture status codes such as error codes
    DWORD page_protections = 0;
    MEMORY_BASIC_INFORMATION auto*m_info = alloca(sizeof(*m_info));
    
    // used to get memory size (RegionSize) and to determine object type (
    VirtualQuery(object, (PMEMORY_BASIC_INFORMATION) m_info, sizeof(*m_info));
    
    if (!m_info->AllocationProtect)
        fatalf(__func__, "memory cannot be transmuted from this context (no access); "
                         "allocation base: %p\n", m_info->AllocationBase);
    
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
    
    DWORD currently_unused_old_page_protections = 0;
    VirtualProtect((LPVOID) object, m_info->RegionSize, page_protections, &currently_unused_old_page_protections);
}

__attribute__((always_inline))
void w32_m_relinquish(w32_m_object *const object) {
    VirtualFree(*object, 0, MEM_RELEASE);
    *object = NULL;
}

struct memory_interface const GLOBAL_WIN32_MEMORY_INTERFACE = {
        m_reserve: &w32_m_reserve,
        m_transmute: &w32_m_transmute,
        m_relinquish: &w32_m_relinquish
};

m_object m_reserve(udqword const bits, enum m_object_type const object_type, enum m_state_type const state_type) {
    return w32_m_reserve(bits, object_type, state_type);
}

void m_transmute(m_object const object, enum m_object_type const object_type, enum m_state_type const state_type) {
    w32_m_transmute(object, object_type, state_type);
}

void m_relinquish(m_object *const object) {
    w32_m_relinquish(object);
}
