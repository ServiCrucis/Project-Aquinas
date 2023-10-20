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
#include "state.h"
#include "bit_math.h"

#include <memoryapi.h>
#include <sysinfoapi.h>
#include <errhandlingapi.h>
#include <winerror.h>
#include <basetsd.h>

ImperfectUnitStackAllocator const M_WINDOWS_WIN32_GLOBAL_IMPERFECT_UNIT_STACK_ALLOCATOR = {
    allocate: &w32_stack_allocate,
    allocate_all: &w32_stack_allocate_all,
    deallocate: &w32_stack_deallocate,
    deallocate_all: &w32_stack_deallocate_all,
    start: &w32_stack_start,
    end: &w32_stack_end
};

ImperfectUnitAllocator const M_WINDOWS_WIN32_GLOBAL_PERFECT_UNIT_ALLOCATOR = {
};

ImperfectAllocator const M_WINDOWS_WIN32_GLOBAL_PERFECT_ALLOCATOR = {
};

PerfectAllocator const M_WINDOWS_WIN32_GLOBAL_IMPERFECT_ALLOCATOR = {
};

// OLD IMPLEMENTATION

//__attribute__((always_inline))
//w32_m_object w32_m_reserve(udqword const bits, enum w32_object_type object_type, enum w32_state_type state_type) {
//    m_context object;
//    DWORD page_options = 0, page_protections = 0;
//    page_options |= MEM_RESERVE | MEM_COMMIT;
//
//    switch (state_type) {
//        case READ:
//            switch (object_type) {
//                case STATE:
//                    page_protections |= PAGE_READONLY;
//                    break;
//                case CAUSING:
//                    page_protections |= PAGE_EXECUTE_READ;
//                    break;
//                default:
//                    fatalf(__func__, "impossible condition, SEU or "
//                                     "system instability detected: illegal value: object_type: %llu\n",
//                           (uqword) object_type);
//            }
//            break;
//        case WRITE:
//            switch (object_type) {
//                case STATE:
//                    // FIXME find and implement write-only access context for pages
//                    page_protections |= PAGE_READWRITE;
//                    break;
//                case CAUSING:
//                    page_protections |= PAGE_EXECUTE_READWRITE;
//                    break;
//                default:
//                    fatalf(__func__, "impossible condition, SEU or "
//                                     "system instability detected: illegal value: object_type: %llu\n",
//                           (uqword) object_type);
//            }
//            break;
//        case READ_WRITE:
//            switch (object_type) {
//                case STATE:
//                    page_protections |= PAGE_READWRITE;
//                    break;
//                case CAUSING:
//                    page_protections |= PAGE_EXECUTE_READWRITE;
//                    break;
//                default:
//                    fatalf(__func__, "impossible condition, SEU or "
//                                     "system instability detected: illegal value: object_type: %llu\n",
//                           (uqword) object_type);
//            }
//            break;
//        case NO_READ_NO_WRITE:
//            switch (object_type) {
//                case STATE:
//                case CAUSING:
//                    page_protections |= PAGE_NOACCESS;
//                    break;
//                default:
//                    fatalf(__func__, "impossible condition, SEU or "
//                                     "system instability detected: illegal value: object_type: %llu\n",
//                           (uqword) object_type);
//            }
//            break;
//        default:
//            fatalf(__func__, "impossible condition, SEU or "
//                             "system instability detected: illegal value: state_type: %llu\n", (uqword) state_type);
//    }
//
//    // init object pointer
//    const uqword bytes = ((bits >> 3) + ((bits & 0b111) > 0));
//    object = VirtualAlloc(NULL, (DWORD) bytes, page_options, page_protections);
//    return object;
//}
//
//__attribute__((always_inline))
//void
//w32_m_transmute(m_context const object, enum w32_object_type const object_type, enum w32_state_type const state_type) {
//    // TODO create robust global program status area to capture status codes such as error codes
//    DWORD page_protections = 0;
//    MEMORY_BASIC_INFORMATION *m_info = alloca(sizeof(*m_info));
//
//    // used to get memory size (RegionSize) and to determine object type (
//    VirtualQuery(object, (PMEMORY_BASIC_INFORMATION) m_info, sizeof(*m_info));
//
//    if (!m_info->AllocationProtect)
//        fatalf(__func__, "memory cannot be transmuted from this context (no access); "
//                         "allocation base: %p\n", m_info->AllocationBase);
//
//    switch (state_type) {
//        case READ:
//            switch (object_type) {
//                case STATE:
//                    page_protections |= PAGE_READONLY;
//                    break;
//                case CAUSING:
//                    page_protections |= PAGE_EXECUTE_READ;
//                    break;
//                default:
//                    fatalf(__func__, "impossible condition, SEU or "
//                                     "system instability detected: illegal value: object_type: %llu\n",
//                           (uqword) object_type);
//            }
//            break;
//        case WRITE:
//            switch (object_type) {
//                case STATE:
//                    // FIXME find and implement write-only access context for pages
//                    page_protections |= PAGE_READWRITE;
//                    break;
//                case CAUSING:
//                    page_protections |= PAGE_EXECUTE_READWRITE;
//                    break;
//                default:
//                    fatalf(__func__, "impossible condition, SEU or "
//                                     "system instability detected: illegal value: object_type: %llu\n",
//                           (uqword) object_type);
//            }
//            break;
//        case READ_WRITE:
//            switch (object_type) {
//                case STATE:
//                    page_protections |= PAGE_READWRITE;
//                    break;
//                case CAUSING:
//                    page_protections |= PAGE_EXECUTE_READWRITE;
//                    break;
//                default:
//                    fatalf(__func__, "impossible condition, SEU or "
//                                     "system instability detected: illegal value: object_type: %llu\n",
//                           (uqword) object_type);
//            }
//            break;
//        case NO_READ_NO_WRITE:
//            switch (object_type) {
//                case STATE:
//                case CAUSING:
//                    page_protections |= PAGE_NOACCESS;
//                    break;
//                default:
//                    fatalf(__func__, "impossible condition, SEU or "
//                                     "system instability detected: illegal value: object_type: %llu\n",
//                           (uqword) object_type);
//            }
//            break;
//        default:
//            fatalf(__func__, "impossible condition, SEU or "
//                             "system instability detected: illegal value: state_type: %llu\n", (uqword) state_type);
//    }
//
//    DWORD currently_unused_old_page_protections = 0;
//    VirtualProtect((LPVOID) object, m_info->RegionSize, page_protections, &currently_unused_old_page_protections);
//}
//
//__attribute__((always_inline))
//void w32_m_relinquish(w32_m_object *const object) {
//    VirtualFree(*object, 0, MEM_RELEASE);
//    *object = NULL;
//}
