/*
* Module: data
* File: data.h
* Created:
* June 13, 2022
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
 *
 * Decouples information from its representation.
 * Module called data to prevent connotative ambiguity with "info".
 *
 * Zero-overhead abstractions:
 * - working byte order (endianness) to be RTL for ease of programming with Hindu-Arabic numeral system
 * - byte alignment:
 * - bits: first-class data objects; bit sequences (continuous array of bits): second-class data objects
 * - polymorphic read/write via macro-like functions where necessary
 *
 *
 *
*/

#ifndef PROJECT_AQUINAS_DATA_H
#define PROJECT_AQUINAS_DATA_H

#include <stdalign.h>
#include "platform.h"

enum data_interpret_mode {
    BYTE_ORDER_LITERAL_LO_TO_HI = 0,
    BYTE_ORDER_LITERAL_HI_TO_LO,
    BYTE_ORDER_LITERAL_INVARIANT,
    BYTE_ORDER_VIRTUAL_LO_TO_HI,
    BYTE_ORDER_VIRTUAL_HI_TO_LO,
    BYTE_ORDER_VIRTUAL_INVARIANT
};

typedef struct {
    uqword alignment;
    uqword src_offset;
    uqword rd_len_bytes;
    uqword dst_offset;
} __attribute__((aligned(32)))  write_params;

void data_mode_set(enum data_interpret_mode);

#define data_read(object, offset, length) ({ \
})                                           \


/*
 * Writes data bytes from `source` to `destination` with the given `write_params`.
 * Both `source` and `destination` pointer variables are `restrict`. For writing
 * into shared memory from distinctly formed pointers, check output to ensure
 * correct operation.
 */
void data_write(void *restrict source, void *restrict destination, write_params);

#endif //PROJECT_AQUINAS_DATA_H
