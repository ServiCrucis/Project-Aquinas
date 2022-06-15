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
 * - polymorphic read/write via function-like macros where necessary
 *
*/

#ifndef PROJECT_AQUINAS_DATA_H
#define PROJECT_AQUINAS_DATA_H

#include <stdalign.h>
#include "platform.h"

// Method of mapping reads and writes regarding the order in which bytes are stored in memory.
//
// Do we really need such esoteric jargon for mere _byte order_?
// No, we don't; and if you say otherwise, you're part of the problem. :)
// Let's simplify that, shall we?
//
// LO TO HI: little endian
// HI TO LO: big endian
//
// HI and LO of course referring to HIgher order and LOwer order addresses
//
// LITERAL: the data is ordered respectively as such
// VIRTUAL: the data might be ordered differently, but will be accessed respectively as such
// If you want to access all data as though it were hi to lo or lo to hi, use virtual;
//
// If the hardware supports a change in data value mode, then the hardware state will be updated
// according to what is optimal for that hardware. For example, if a memory module supports
// hard-boot configuration data, this will not be updated; but if a processor supports changing
// byte processing order on the fly, this will be updated if possible, but may fail if, for example,
// there are insufficient permissions.
//
// Refer to your hardware OEM's manual for information on byte-order-invariant hardware,
// and available instructions, registers, or hardware functions in general for
// configuring data value mode ("endianness").
enum data_interpret_mode {
    // maps read/write from lo to hi to data value mode set with data_value_mode_set()
    BYTE_ORDER_VIRTUAL_LO_TO_HI = 0,
    // maps read/write from hi to lo to data value mode set with data_value_mode_set()
    BYTE_ORDER_VIRTUAL_HI_TO_LO,
    // maps read/write from current hardware-defined data value mode at the time of read/write call
    // (ignores data value mode set with data_value_mode_set())
    BYTE_ORDER_VIRTUAL_INVARIANT,
    // maps read/write from hi to lo to current hardware-defined data value mode at the time of read/write call
    // (respects data value mode set with data_value_mode_set()
    BYTE_ORDER_VIRTUAL_UNKNOWN
};

// If the hardware supports a change in data value mode, then the hardware state will be updated
// according to what is optimal for that hardware. For example, if a memory module supports
// boot configuration data, this will not be updated, but if a processor supports changing
// byte processing order on the fly, this will be updated if possible.
//
// Refer to your hardware OEM's manual for information on byte-order-invariant hardware,
// and available instructions, registers, or hardware functions in general for
// configuring data value mode ("endianness").
enum data_value_mode {
    BYTE_ORDER_LITERAL_LO_TO_HI = 0,
    BYTE_ORDER_LITERAL_HI_TO_LO,
    // For ARM et al.
    BYTE_ORDER_LITERAL_INVARIANT,
    BYTE_ORDER_LITERAL_UNKNOWN
};

typedef struct {
    uqword src_alignment;
    uqword dst_alignment;
    uqword src_length;
    uqword dst_length;
} __attribute__((aligned(32))) data_info;

#include "data_alignment_convenience_structs.h"

typedef struct {
    //
    udword src_offset;
    udword dst_offset;
    // number of elements (element size is data_info.alignment) to write
    uqword elements_write_quantity;
} __attribute__((packed)) __attribute__((aligned(16))) write_parameters;


void data_mode_set(enum data_interpret_mode);

#define data_read(object, offset, length) ({ \
})                                           \


/*
 * Writes data bytes from `source` to `destination` with the given `write_parameters`.
 * Both `source` and `destination` pointer variables are `restrict`. For writing
 * into shared memory from distinctly formed pointers, check output to ensure
 * correct operation.
 */
void data_write(void *restrict src, uqword src_alignment, void *restrict dst, uqword dst_alignment, data_info, write_parameters);

#endif //PROJECT_AQUINAS_DATA_H
