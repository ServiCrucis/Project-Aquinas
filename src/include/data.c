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

static volatile enum data_byte_order local_byte_order =
                                    #if ARCH_BYTE_ORDER == BYTE_ORDER_LO_TO_HI
                                    BYTE_ORDER_LITERAL_LO_AT_LO
#elif ARCH_BYTE_ORDER == BYTE_ORDER_HI_TO_LO
BYTE_ORDER_LITERAL_HI_AT_LO
#elif ARCH_BYTE_ORDER == BYTE_ORDER_INVARIANT
BYTE_ORDER_LITERAL_INVARIANT
#else
BYTE_ORDER_LITERAL_UNKNOWN
#endif
;

inline enum data_byte_order data_get_current_byte_order() {
    // TODO implement hardware-specific configuration reading
    return local_byte_order;
}

static inline udword compute_byte_index(udword current_byte, udword alignment, enum data_byte_order byte_order) {
    switch (byte_order) {
        case BYTE_ORDER_LITERAL_LO_AT_LO:
            return local_byte_order == BYTE_ORDER_LITERAL_LO_AT_LO ? current_byte : alignment - 1 - current_byte;
        case BYTE_ORDER_LITERAL_HI_AT_LO:
            return local_byte_order == BYTE_ORDER_LITERAL_HI_AT_LO ? current_byte : alignment - 1 - current_byte;
        default:
            fatalf(__func__, "system instability detected: byte order does not exist: %ull", (uqword) byte_order);
    }
}

// TODO optimize data_write_as(), etc.
void data_write_as(
        register uqword const elements,
        register uqword const alignment,
        void *restrict src,
        enum data_byte_order src_byte_order,
        void *restrict dst,
        enum data_byte_order dst_byte_order
                  ) {
    inline void write_element(
            udword src_element_byte_offset,
            udword dst_element_byte_offset,
            void *restrict src,
            enum data_byte_order src_byte_order,
            void *restrict dst,
            enum data_byte_order dst_byte_order
                             ) {
        ubyte *restrict dst_buffer = alloca(alignment);
        
        register udword offset = src_element_byte_offset;
        // write all bytes with current byte order for respective src and dst to buffer
        for (udword     i      = 0; i < alignment; ++i) {
            // read src as dst for faster writes
            dst_buffer[compute_byte_index(i, alignment, dst_byte_order)] =
                    ((ubyte *) src)[offset + compute_byte_index(i, alignment, src_byte_order)];
        }
        // copy from buffer to destination
        for (udword     i      = 0; i < alignment; ++i) {
            ((ubyte *) dst)[i] = dst_buffer[i];
        }
    };
    
    for (udword element_byte = 0; element_byte < (elements * alignment); element_byte += alignment) {
        write_element(element_byte, element_byte, src, src_byte_order, dst, dst_byte_order);
    }
}

void data_write(const uqword elements, const uqword alignment, enum data_interpret_mode interpret_mode, void *src, void *dst) {
    enum data_byte_order src_byte_order, dst_byte_order;
    switch (interpret_mode) {
        case BYTE_ORDER_VIRTUAL_LO_TO_HI:
            src_byte_order = BYTE_ORDER_LITERAL_LO_AT_LO;
            dst_byte_order = data_get_current_byte_order();
            break;
        case BYTE_ORDER_VIRTUAL_HI_TO_LO:
            src_byte_order = BYTE_ORDER_LITERAL_HI_AT_LO;
            dst_byte_order = data_get_current_byte_order();
            break;
        case BYTE_ORDER_VIRTUAL_INVARIANT:
            src_byte_order = data_get_current_byte_order();
            dst_byte_order = data_get_current_byte_order();
            break;
        case BYTE_ORDER_VIRTUAL_UNKNOWN:
            src_byte_order = BYTE_ORDER_LITERAL_HI_AT_LO;
            dst_byte_order = data_get_current_byte_order();
            break;
        default:
            fatalf(__func__, "system instability detected: unknown data_byte_order: %llu\n", interpret_mode);
    }
    
    data_write_as(elements, alignment, src, src_byte_order, dst, dst_byte_order);
}
