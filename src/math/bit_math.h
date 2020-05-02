/*
 * Module: bit_math
 * File: bit_math.h
 * Created:
 * April 28, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef CATHOLICUS_BIT_MATH_H
#define CATHOLICUS_BIT_MATH_H

#include <stdbool.h>

#include "platform.h"


static inline uword log2i(uword bit_string);
/*
 * Compute number of significant bits in the given word
 */
static inline uword sigbits(uword bit_string) {
	// TODO use assembly instructions to implement sigbits with log2i for unsupported architectures
	return log2i(bit_string) + 1u;
}

/*
 * Compute number of significant bits in the given signed word.
 */
static inline uword sigbitss(word bit_string) {
	return sigbits((uword) bit_string);
}

/*
 * Compute the number of significant bits in the given bit string.
 */
static inline uword sigbitsn(uword *bit_string, size_t words) {
	uword result = 0;
	for(word i = (words - 1u); i >= 0u; i--) {
		result += sigbits(bit_string[i]);
	}
	return result;
}

/*
 * Compute 2 to the power of exponent using integer bit math.
 */
static inline uword pow2i(uword exponent) {
	return 1u << exponent;
}

static inline uword powni(uword base, uword exponent) {
	uword result = 1;
	
	while (exponent) {
		if (exponent & 1u)
			result *= base;
		exponent >>= 1u;
		base *= base;
	}
	
	return result;
}

/*
 * Compute log base 2 of the given bit string using integer bit math.
 */
static inline uword log2i(uword bit_string) {
	uword result = 0;
	
	while (bit_string >>= (uword) 1ull) {
		result++;
	}
	
	return result;
}

/*
 * Doubles the given value using bit math.
 */
static inline uword dbl(uword value) {
	return value << 1u;
}

/*
 * Halves the given value using bit math.
 */
static inline uword hlv(uword value) {
	return value >> 1u;
}

// data structures

/*
 * Compute if given value is within the range [min, max].
 */
static inline bool in_range(uword min, uword max, uword value) {
	return (min <= value) & (value <= max);
}

/*
 * Compute if given value is within the range [min, max).
 */
static inline bool in_buffer(uword min, uword max, uword value) {
	return (min <= value) & (value < max);
}

#endif //CATHOLICUS_BIT_MATH_H
