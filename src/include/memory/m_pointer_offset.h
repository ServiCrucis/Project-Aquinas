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
#include "bit_math.h"

/*
 *  Computes the optimal size of a pointer_offset data type in bits for the given
 *  number of elements that one wishes to index.
 *
 *  Can be used as an input to the offset_bits parameter of m_compute_required_space.
 *
 *  See https://www.desmos.com/calculator/jjdq9w8ofs
 */
static inline uqword m_compute_optimal_offset_size(uqword const elements) {
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
static inline udqword m_compute_required_space(ubyte address_bits, ubyte offset_bits, uqword elements) {
    // filter to permit values in [0, 2**7)
    address_bits &= 0x7f;
    // filter to permit values in [0, 2**6)
    offset_bits &= 0x3f;
    
    register udqword a = 0;
    register udqword b = 0;
    
    // b_address - b_offset
    a = address_bits - offset_bits;
    // normalize to 64.64 fixed point
    a <<= 64;
    // multiply by 2**(-b_offset)
    a >>= offset_bits;
    // add b_offset
    a += (udqword) offset_bits << 64;
    
    // multiply integer part by elements
    b           = (a >> 64) * elements;
    
    // filter fraction part
    a &= 0xFFFFFFFFFFFFFFFF;
    // compute exponent of the fraction part
    offset_bits = 65 - sigbits((uqword) a);
    // reduce fraction part
    a >>= cnttz((uqword) a);
    
    // multiply fraction part by elements
    a *= ((udqword) elements);
    
    // combine integer and fraction parts and put in b
    b += a >> offset_bits;
    
    // compute ceiled integer result
    b += filter((uqword) a, offset_bits, 0) != 0;
    
    return b;
}

#endif //PROJECT_AQUINAS_M_POINTER_OFFSET_H
