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
#include <limits.h>
#include "asm.h"
#include "platform.h"
#include "error.h"


/*
 * Gets the minimum number of bits required to represent the given type on the native architecture
 */
#define bitwidth(Type) (sizeof(Type) * MIN_BITS)

/*
 * Gets the number of bits for a given array
 */
#define bitlen(array, elements) (sizeof(typeof(array)) * elements * MIN_BITS)

/*
 * Truncates the given value by a specified number of bits and assumes the right-most bit is bit 0.
 */
#define truncate(value, bits) ( (value << (sizeof(typeof(value)) * MIN_BITS - bits)) >> (sizeof(typeof(value)) * MIN_BITS - bits) )

/*
 * Generates a bit mask from the given value that sets bit_count bits from the right to ones.
 */
static inline uword bitmaskv(register uword value, register uword bit_count) {
	return truncate(~value, bit_count) ^ value;
}

static inline uword sigbits(uword);
/*
 * Generates a bitmask from the given value that sets all significant bits to ones.
 *
 * Exactly equivalent to `bitmaskv(value, sigbits(value));`
 */
static inline uword bitmask(register uword value) {
	return bitmaskv(value, sigbits(value));
}

/*
 * Compute the number of significant bits in the given word
 */
static inline uword sigbits(register uword bit_string) {
#if defined(__GNUC__)
	#if DATA_MODEL == LLP64 || DATA_MODEL == ILP64 || DATA_MODEL == SILP64
	r_info("LLP64 or ILP64 or SILP64");
	return bitwidth(typeof(bit_string)) - __builtin_clzll((bit_string | 1ull));
	#elif DATA_MODEL == LP64
	return bitwidth(typeof(bit_string)) - __builtin_clzll((bit_string | 1ul));
	#elif DATA_MODEL == ILP32 || DATA_MODEL == LP32
	return bitwidth(typeof(bit_string)) - __builtin_clz((bit_string | 1u));
	#else
		#error "Unsupported data model"
	#endif
#elif ARCH == ARCH_INTEL_X86
	// must check CPU compatibility first
	return bitwidth(typeof(bit_string)) - __x86_lzcnt((((unsigned long) bit_string) | 1u));
#elif ARCH == ARCH_AMD64
	return __x64_bsrl((unsigned long long) bit_string);
#elif ARCH == ARCH_ARM
	#if ARCH_VARIANT == ARCH_ARM32
		return bitwidth(typeof(bit_string)) - __arm32_clz(~(((unsigned long) bit_string) | 1u));
	#elif ARCH_VARIANT == ARCH_ARM64
		return bitwidth(typeof(bit_string)) - __arm64_clz(~(((unsigned long) bit_string) | 1u));
	#else
		#error "ARM variant not supported"
	#endif
#else
	ubyte  k = 0;
	if (bit_string > 0xFFFFFFFFu) { bit_string >>= 32; k  = 32; }
	if (bit_string > 0x0000FFFFu) { bit_string >>= 16; k |= 16; }
	if (bit_string > 0x000000FFu) { bit_string >>= 8;  k |= 8;  }
	if (bit_string > 0x0000000Fu) { bit_string >>= 4;  k |= 4;  }
	if (bit_string > 0x00000003u) { bit_string >>= 2;  k |= 2;  }
	k |= (bit_string & 2u) >> 1u;
	return k;
#endif
}

/*
 * Compute number of significant base 10 digits in a given base 2 word
 */
static inline uword digits(register uword bit_string) {
	// can't include frac_math.h
	bit_string = sigbits(bit_string) * 1000000000000ull;
	bit_string = bit_string / 3321928094887ull;
	return bit_string + 1;
}

/*
 * Compute the number of significant bits in the given signed word.
 */
static inline uword sigbitss(word bit_string) {
	return sigbits((uword) bit_string);
}

/*
 * Compute the number of significant bits in the given bit string.
 */
static inline uword sigbitsn(uword *bit_string, size_t words) {
	uword     result = 0;
	for (word i      = (words - 1u); i >= 0u; i--) {
		result += sigbits(bit_string[i]);
	}
	return result;
}

/*
 * Compute 2 to the power of exponent using integer bit math.
 */
static inline uword pow2i(uword exponent) {
	return 1ull << exponent;
}

/*
 * Compute base to the power of exponent using integer bit math.
 */
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
static inline uword log2i(register uword bit_string) {
	return sigbits(bit_string) - 1ull;
}

/*
 * Computes log base 10 the given bit string using integer bit math.
 */
static inline uword log10i(register uword bit_string) {
	return digits(bit_string) - 1ull;
}

/*
 * Computes log_<base>(bit_string) with base as the base, and the given bit string using integer bit math.
 */
static inline uword logni(register uword base, register uword bit_string) {
	return log10i(bit_string) / log10i(base);
}

/*
 * Doubles the given value using bit math.
 */
static inline uword dbl(register uword const value) {
	return value << 1u;
}

/*
 * Halves the given value using bit math.
 */
static inline uword hlv(register uword const value) {
	return value >> 1u;
}

// data structures

/*
 * Compute if given value is within the range [min, max].
 */
static inline bool in_range(register uword const min, register uword const max, register uword const value) {
	return (min <= value) & (value <= max);
}

/*
 * Compute if given value is within the range [min, max).
 */
static inline bool in_buffer(register uword const min, register uword const max, register uword const value) {
	return (min <= value) & (value < max);
}

/*
 * Gets the binary index of a given address in a binary binary_trie.
 * For a given bit binary_trie of N bits, there are 2*(2^N) - 2 bits in the binary_trie, and 2^N - 1 indices for either the left or
 * right side, so the index may be calculated as 2 * (2^log_2(address)) - 2 + address - side_bit * pow2(log_2(address)). The
 * right-most bit determines which side of the binary_trie will be accessed, either 0 for left, or 1 for right.
 * (See <https://www.desmos.com/calculator/z8l7kyskro>)
 */
static inline uword bin_index(register uword address) {
	uword side = address & 1u;
	address >>= 1u;
	if (!address)
		return side;
	uword address_bits = log2i(address);
	// 2 * pow2i(address_bits) - 2u + address - side * pow2i(address_bits)
	return address == 1 ? side : (2ull << address_bits) - 2u + address - side * (1ull << address_bits);
}

static inline uword get_bit(uword const *bitarray, uword const words, uword const bit_index) {
	uword bits = sizeof(uword) * sizeof(uintmin_t) * MIN_BITS;
	
	uword index = bit_index / bits;
	if (!in_buffer(0, words, index))
		r_fatalf(R_BUFFER_OVERFLOW, __func__, "index out of range: 0 <= index=%u < %u\n", index, words);
	
	uword word = bitarray[index];
	uword bit  = (word >> (bit_index % bits)) & ((uword) 1u);
	return bit;
}

static inline uword *get_bits(uword const *bitarray, uword const words, uword const bit_index, uword const value_bits) {
	uword bits = sizeof(uword) * sizeof(uintmin_t) * MIN_BITS;
	
	uword start = bit_index / bits;
	if (!in_buffer(0, words, start))
		r_fatalf(R_BUFFER_OVERFLOW, __func__, "start out of range: 0 <= start=%u < %u\n", start, words);
	
	uword end = (bit_index + value_bits - 1u) / bits;
	if (!in_buffer(0, words, end))
		r_fatalf(R_BUFFER_OVERFLOW, __func__, "end out of range: 0 <= end=%u < %u\n", end, words);
	
	for (uword i = start; i < end; i++) {
	}
}

static inline void set_bit(uword *bitarray, uword const words, uword const bit_offset, uword const value) {
	uword bits  = sizeof(uword) * sizeof(uintmin_t) * MIN_BITS;
	uword index = bit_offset / bits;
	// guard
	if (!in_buffer(0, words, index))
		r_fatalf(R_BUFFER_OVERFLOW, __func__, "index out of range: 0 <= index=%u < %u\n", index, words);
	uword word = bitarray[index];
	word ^= (word ^ ((value & ((uword) 1u)) << (bit_offset % bits))) & (((uword) 1u) << (bit_offset % bits));
	bitarray[index] = word;
}

#endif //CATHOLICUS_BIT_MATH_H
