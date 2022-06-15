/*
* Module: data
* File: data.c
* Created:
* June 13, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
*/

#include "data.h"

static enum data_interpret_mode global_data_interpret_mode = BYTE_ORDER_VIRTUAL_INVARIANT;

static inline void *data_ptr_to_data_start(void *ptr, uqword offset, uqword alignment) {

}

void data_write(void *restrict src, void *restrict dst, write_params params) { // NOLINT
    // helper function definitions
    ubyte *next_element(uqword i, uqword alignment) {
    
    }
    // set pointer positions
    src = data_ptr_to_data_start(src, params.src_offset, params.alignment);
    dst = data_ptr_to_data_start(dst, params.dst_offset, params.alignment);
    
    ubyte current[params.alignment]
loop_start:

}
