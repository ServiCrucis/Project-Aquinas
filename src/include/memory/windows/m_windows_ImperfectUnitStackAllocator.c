/*
 * Module: m_windows_ImperfectUnitStackAllocator
 * File: m_windows_ImperfectUnitStackAllocator.c
 * Created:
 * October 19, 2023
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 * License: See LICENSE.txt
 *
 * Defines the ImperfectUnitStackAllocator implementation for Win32.
 */

#include <sysinfoapi.h>
#include <memoryapi.h>
#include <errhandlingapi.h>
#include <winerror.h>
#include "m_windows_ImperfectUnitStackAllocator.h"
#include "bit_math.h"

typedef struct {
    udqword allocatable_bits;
} m_windows_selflike_page_list_info;

typedef struct {
    udqword allocation_count_part0;
} m_windows_stack_info;

/*
 * The first part of a selflike continuous page allocation list. The other parts are not implemented,
 * but here we specify the design anyways with the intent to recognize it as such since we're choosing
 * not to implement it, but it could be implemented at some point in the future (not by me).
 */
static void *M_WINDOWS_PAGING_STATEHOLDS_STACK;

static inline udqword w32_get_page_size() {
    SYSTEM_INFO system_info;
    GetNativeSystemInfo(&system_info);
    return ((uqword)system_info.dwPageSize) << floor_log2i(bitwidth(ubyte));
}

static inline m_windows_selflike_page_list_info *m_windows_selflike_page_list_info_offset() {
    return (m_windows_selflike_page_list_info *) M_WINDOWS_PAGING_STATEHOLDS_STACK;
}

static inline m_windows_stack_info *m_windows_stack_info_offset() {
    const machine_operand computed_offset = sizeof(m_windows_selflike_page_list_info) + sizeof(m_windows_stack_info);
    return (m_windows_stack_info *) (((ubyte *) M_WINDOWS_PAGING_STATEHOLDS_STACK) + computed_offset);
}

static inline void *m_windows_stack_pointer_to_void_pointer(m_windows_stack_pointer absolute_bit_offset) {
    return (void *) (absolute_bit_offset >> bitwidth(ubyte));
}

static inline ubyte m_windows_get_bit_offset(m_windows_stack_pointer absolute_bit_offset) {
    return (ubyte) absolute_bit_offset;
}

static inline m_windows_stack_pointer m_windows_compute_pointer_from_offset(udqword bit_offset) {
    return (m_windows_stack_pointer) ((((udqword) m_windows_stack_info_offset()) << bitwidth(ubyte)) + bit_offset);
}

static inline uqword local_compute_required_bytes_for_stack(udqword program_lifetime_bit_quantity) {
    uqword const allocation_count_size = sizeof( ((m_windows_stack_info*) 0)->allocation_count_part0 );
    uqword const required_bytes_integer_part = (program_lifetime_bit_quantity >> floor_log2i(bitwidth(ubyte)));
    uqword const required_bytes_fraction_part = filter(program_lifetime_bit_quantity, floor_log2i(bitwidth(ubyte)), 0);
    return  allocation_count_size + required_bytes_integer_part + (0 != required_bytes_fraction_part);
}

m_windows_stack_pointer w32_stack_start(void);
m_windows_stack_pointer w32_stack_end(void);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshift-count-overflow"
void w32_stack_create(udqword program_lifetime_bit_quantity) {
    // add space to program_lifetime_bit_quantity for heap size and number of allocated bits
    program_lifetime_bit_quantity += bitwidth(m_windows_selflike_page_list_info) + bitwidth(m_windows_stack_info);
#define local_LARGEST_ALLOCATION_VALUE ((DWORD)-1ll)
    // ensure program_lifetime_bit_quantity size is supported by Windows
    if (
            (floor_log2i((uqword) (program_lifetime_bit_quantity >> 64)) >
             floor_log2i(local_LARGEST_ALLOCATION_VALUE >> 64))
            ||
            (floor_log2i((uqword) program_lifetime_bit_quantity) >
             floor_log2i((uqword) local_LARGEST_ALLOCATION_VALUE))
            ) {
        fatalf(__func__,
               "program_lifetime_bit_quantity is larger than %llX (largest allocation value)\nprogram_lifetime_bit_quantity=%llX%llX\n",
               (uqword) local_LARGEST_ALLOCATION_VALUE,
               (uqword) (program_lifetime_bit_quantity >> bitwidth(uqword)),
               (uqword) (program_lifetime_bit_quantity));
    }
#undef local_LARGEST_ALLOCATION_VALUE

    if (!M_WINDOWS_PAGING_STATEHOLDS_STACK) {
        // reserve all the pages we desire for making our own heap
        M_WINDOWS_PAGING_STATEHOLDS_STACK = (void *) VirtualAlloc(
                NULL,
                (DWORD) local_compute_required_bytes_for_stack(program_lifetime_bit_quantity),
                MEM_RESERVE, PAGE_EXECUTE_READWRITE
        );
        // check result of VirtualAlloc
        DWORD last_error = GetLastError();
        if (last_error != ERROR_SUCCESS) {
            fatalf(__func__, "Failed to reserve pages for stack: GetLastError()=%X\n", last_error);
        }
        // commit first page
        VirtualAlloc(M_WINDOWS_PAGING_STATEHOLDS_STACK, w32_get_page_size() >> floor_log2i(bitwidth(ubyte)), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        // check result of VirtualAlloc
        last_error = GetLastError();
        if (last_error != ERROR_SUCCESS) {
            fatalf(__func__, "Failed to commit first page for stack: GetLastError()=%X\n", last_error);
        }

        // restore logical heap size
        program_lifetime_bit_quantity -= bitwidth(m_windows_selflike_page_list_info) + bitwidth(m_windows_stack_info);
        // write program_lifetime_bit_quantity to first address
        m_windows_selflike_page_list_info_offset()->allocatable_bits = program_lifetime_bit_quantity;
        // initialize number of stack allocations to 0
        m_windows_stack_info_offset()->allocation_count_part0 = (udqword) 0;
        // initialization successful
    } else
        fatalf(__func__, "M_WINDOWS_PAGING_STATEHOLDS_STACK is non-NULL; unable to create stack representation of memory\n");
}
#pragma clang diagnostic pop

void w32_stack_destroy(void) {
    if (M_WINDOWS_PAGING_STATEHOLDS_STACK != NULL) {
        BOOL VirtualFree_succeeded = VirtualFree(M_WINDOWS_PAGING_STATEHOLDS_STACK, 0, MEM_RELEASE);
        if (VirtualFree_succeeded != TRUE) {
            fatalf(__func__, "VirtualFree failed: GetLastError(): %X", GetLastError());
        }
    } else
        fatalf(__func__, "M_WINDOWS_PAGING_STATEHOLDS_STACK is NULL");
}

static inline void w32_stack_ensure_sufficient_space(udqword bits_to_allocate) {
    if ((m_windows_stack_info_offset()->allocation_count_part0 + bits_to_allocate) >
        m_windows_selflike_page_list_info_offset()->allocatable_bits
            ) {
        fatalf(__func__, "insufficient space to allocate %llX%llX bits\n",
               (uqword)(bits_to_allocate >> 64),
               (uqword)(bits_to_allocate)
        );
    }
}

m_windows_stack_pointer w32_stack_allocate(void) {
    if (!M_WINDOWS_PAGING_STATEHOLDS_STACK)
        fatalf(__func__, "M_WINDOWS_PAGING_STATEHOLDS_STACK is NULL; unable to allocate\n");

    w32_stack_ensure_sufficient_space(1);
    // increment allocation count
    m_windows_stack_info_offset()->allocation_count_part0++;
    // compute stack pointer and return it
    return w32_stack_end();
}

m_windows_stack_pointer w32_stack_allocate_all(udqword const bits) {
    if (!M_WINDOWS_PAGING_STATEHOLDS_STACK)
        fatalf(__func__, "M_WINDOWS_PAGING_STATEHOLDS_STACK is NULL; unable to allocate\n");

    w32_stack_ensure_sufficient_space(bits);
    // compute stack pointer of first allocated unit
    register udqword const first_element = w32_stack_end();
    // add bits onto allocation count
    m_windows_stack_info_offset()->allocation_count_part0 += bits;

    return first_element;
}

void w32_stack_deallocate() {
    if (!M_WINDOWS_PAGING_STATEHOLDS_STACK)
        fatalf(__func__, "M_WINDOWS_PAGING_STATEHOLDS_STACK is NULL; unable to deallocate\n");
    // check that allocations exist first
    if (m_windows_stack_info_offset()->allocation_count_part0 == 0)
        fatalf(__func__, "nothing is allocated in the internal stack allocator; unable to deallocate\n");
    // deallocate the allocation
    m_windows_stack_info_offset()->allocation_count_part0 -= 1;
}

void w32_stack_deallocate_all(m_windows_stack_pointer from_allocation, m_windows_stack_pointer most_recent_allocation) {
    if (!M_WINDOWS_PAGING_STATEHOLDS_STACK)
        fatalf(__func__, "M_WINDOWS_PAGING_STATEHOLDS_STACK is NULL; unable to deallocate\n");
    // check that allocations exist first
    if (m_windows_stack_info_offset()->allocation_count_part0 == 0)
        fatalf(__func__, "nothing is allocated in the internal stack allocator; unable to deallocate\n");
    // verify that most_recent_allocation points to the last allocation on the stack
    m_windows_stack_pointer last_allocation = w32_stack_end();
    if (last_allocation != most_recent_allocation)
        fatalf(__func__, "most_recent_allocation is not the end of the stack; unable to deallocate\n");
    // verify that from_allocation is in the allocation bounds for the stack itself
    if ((from_allocation <= m_windows_compute_pointer_from_offset(0))
        ||
        (from_allocation > last_allocation))
        fatalf(__func__, "from_allocation was not allocated in the allocation boundary of the internal stack allocator\n");
    // deallocate the allocation
    m_windows_stack_info_offset()->allocation_count_part0 -= abs_diff(last_allocation, from_allocation) + 1;
}

m_windows_stack_pointer w32_stack_start(void) {
    return m_windows_compute_pointer_from_offset(1);
}

m_windows_stack_pointer w32_stack_end(void) {
    return m_windows_compute_pointer_from_offset(m_windows_stack_info_offset()->allocation_count_part0);
}
