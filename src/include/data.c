/*
* Module: data
* File: data.c
* Created:
* June 13, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
*/

#include "data.h"
#include "bit_math.h"

static enum data_interpret_mode local_data_interpret_mode = BYTE_ORDER_VIRTUAL_INVARIANT;
static enum data_value_mode     local_data_value_mode     =
                                        #if ARCH_BYTE_ORDER == BYTE_ORDER_LO_TO_HI
                                        BYTE_ORDER_LITERAL_LO_TO_HI
                                        #elif ARCH_BYTE_ORDER == BYTE_ORDER_HI_TO_LO
                                        BYTE_ORDER_LITERAL_HI_TO_LO
#elif ARCH_BYTE_ORDER == BYTE_ORDER_INVARIANT
BYTE_ORDER_LITERAL_INVARIANT
#else
BYTE_ORDER_LITERAL_UNKNOWN
#endif
;

static inline void *local_data_ptr_to_data_start(void *ptr, uqword offset, uqword alignment) {
}

void data_write(void *restrict src, void *restrict dst, write_parameters params) { // NOLINT
    // helper function definitions
    ubyte *next_element(uqword i, uqword alignment) {
    }
    // set pointer positions
    src = local_data_ptr_to_data_start(src, params.src_offset, params.alignment);
    dst = local_data_ptr_to_data_start(dst, params.dst_offset, params.alignment);
    
    // Write Algorithm:
    //
    //  0 set current element
    //  1 copy current to destination element
    //  2 if:
    //      0 end of elements:
    // size is aligned to nearest multiple of native alignment
    ubyte current[];
data_copy_loop_start:
}
