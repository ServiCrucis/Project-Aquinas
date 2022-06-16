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
// If the hardware supports a change in byte order, then the hardware state will be updated
// according to what is optimal for that hardware. For example, if a memory module supports
// hard-boot configuration data, this will not be updated; but if a processor supports changing
// byte processing order on the fly, this will be updated if possible, but may fail if, for example,
// there are insufficient permissions.
//
// Refer to your hardware OEM's manual for information on byte-order-invariant hardware,
// and available instructions, registers, or hardware functions in general for
// configuring data byte order ("endianness").
enum data_interpret_mode {
    // maps read/write from lo to hi to byte order set with data_byte_order_set()
    BYTE_ORDER_VIRTUAL_LO_TO_HI = 0,
    // maps read/write from hi to lo to byte order set with data_byte_order_set()
    BYTE_ORDER_VIRTUAL_HI_TO_LO = 1,
    // maps read/write from current hardware-defined byte order at the time of read/write call
    // (ignores byte order set with data_byte_order_set())
    BYTE_ORDER_VIRTUAL_INVARIANT = 2,
    // maps read/write from hi to lo to current hardware-defined byte order at the time of read/write call
    // (respects byte order set with data_byte_order_set()
    BYTE_ORDER_VIRTUAL_UNKNOWN = 3
};

// If the hardware supports a change in byte order, then the hardware state will be updated
// according to what is optimal for that hardware. For example, if a memory module supports
// boot configuration data, this will not be updated, but if a processor supports changing
// byte processing order on the fly, this will be updated if possible.
//
// Refer to your hardware OEM's manual for information on byte-order-invariant hardware,
// and available instructions, registers, or hardware functions in general for
// configuring data byte order ("endianness").
enum data_byte_order {
    BYTE_ORDER_LITERAL_LO_TO_HI = 0,
    BYTE_ORDER_LITERAL_HI_TO_LO = 1
};

void data_byte_order_set(enum data_byte_order);

/*
 * Writes `elements` elements from `src` start to `dst` start based on the given `alignment`.
 * The byte order of both arrays is determined by the `interpret_mode` (see enum data_interpret_mode).
 * Both `src` and `dst` pointer variables are `restrict`. For writing into shared memory
 * from distinctly formed pointers, check compiler and runtime output to ensure correct operation.
 */
void data_write(register uqword const elements, register uqword const alignment, enum data_interpret_mode, void *restrict src, void *restrict dst);

/*
 * Writes `elements` elements from `src` start as `src_byte_order` to `dst` start as
 * `dst_byte_order` based on the given `alignment`. Both `src` and `dst` pointer
 * variables are marked as `restrict`. For writing into shared memory from distinctly
 * formed pointers, check compiler and runtime output to ensure correct operation.
 */
void data_write_as(register uqword const elements, register uqword const alignment, void *restrict src, enum data_byte_order, void *restrict dst, enum data_byte_order);

#endif //PROJECT_AQUINAS_DATA_H
