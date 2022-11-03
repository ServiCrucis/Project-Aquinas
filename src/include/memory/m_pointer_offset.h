/*
 * Module: m_pointer_offset
 * File: m_pointer_offset.h
 * Created:
 * October 13, 2022
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 * License: See LICENSE.txt
 *
 * A stupidly simple pointer compression implementation that supports this incredibly
 * revolutionary new concept known as compressed pointers (pointer offsets) because
 * this has definitely never been thought of before and is of course used ubiquitously
 * to save every bit. /s
 */

#ifndef PROJECT_AQUINAS_M_POINTER_OFFSET_H
#define PROJECT_AQUINAS_M_POINTER_OFFSET_H

#include "platform.h"
#include "m_object.h"
#include "bit_math.h"

/*
 *  Computes the optimal size of a pointer_offset data type in bits for the given
 *  number of elements that one wishes to index.
 *
 *  Can be used as an input to the offset_bits parameter of m_compute_required_space.
 *
 *  See https://www.desmos.com/calculator/jjdq9w8ofs
 */
static inline uqword m_compute_optimal_offset_size(uqword elements) {
    register ubyte const order  = sigbits(elements);
    register ubyte const addend = (order >= 3) + (order >= 6) + (order >= 11) + (order >= 20);
    return floor_log2i(order - addend);
}

/*
 * Computes the minimum required amount of space in bits for the given number
 * of elements that one wishes to index.
 *
 * See https://www.desmos.com/calculator/jjdq9w8ofs
 */
static inline udqword m_compute_required_space(register ubyte address_bits, register ubyte offset_bits, register uqword elements) {
    offset_bits &= 0x3Full;
    address_bits -= offset_bits;
    
    // full 65.63 fixed point value
    register udqword a;
    // full 65.63 fixed point value
    register udqword b;
    // normalize to 65.63 fixed point and then multiply by 2**(-offset_bits)
    a            = ((udqword) address_bits << 63) >> offset_bits;
    // normalize to 65.63 fixed point
    a += (udqword) offset_bits << 63;
    // reduces the multiply to prevent overflow in a 128-bit multiply
    address_bits = cnttz((uqword) (a & (udqword)0xEFFFFFFFFFFFFFFF));
    // multiply by elements
    b            = (a >> 63) * elements + ((udqword) (((a & (udqword)0xEFFFFFFFFFFFFFFF) >> address_bits) * elements) << address_bits);
    // compute final ceiled integer result which is at most bitwidth(elements) + 6 = 70
    // ceil(x) = integer_part(x) + (fraction_part(x) > 0)
    b = (b >> 63) + ((a & (udqword)0xEFFFFFFFFFFFFFFF) > 0);
    
    return b;
}

#endif //PROJECT_AQUINAS_M_POINTER_OFFSET_H
