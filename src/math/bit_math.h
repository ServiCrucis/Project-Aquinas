/*
 * Module: bit_math
 * File: bit_math.h
 * Created:
 * April 28, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 *
 * License:
 * Codex Dominatio Publicus sub Leges
 * <https://github.com/ServiRegis/Licenses/blob/master/CODEX-DOMINATIO-PUBLICUS-SUB-LEGES.txt>
 */

#ifndef PROJECT_AQUINAS_BIT_MATH_H
#define PROJECT_AQUINAS_BIT_MATH_H

#include <stdbool.h>
#include <limits.h>
#include <platform.h>
#include "asm.h"
#include "state.h"

/* TYPES */

typedef struct pair {
    uqword x, y;
} point;

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
 * Returns 1 if the value is odd.
 */
#define is_odd(value) ( (value) & 1 )

/*
 * Returns 1 if the value is even.
 */
#define is_even(value) ( !is_odd(value) )

/*
 * Computes the absolute value of the given value
 */
#define abs(value) ( (value) > 0 ? (value) : -(value) )
//#define abs(value) ( ((value) ^ ((value) >> (bitwidth(typeof(value)) - 1u))) + (((value) >> (bitwidth(typeof(value)) - 1u)) & 1u) )

/*
 * Computes the sign of the given value (accepts signed or unsigned input)
 */
#define sign(value) ( (value) > 0 ? 1 : -1 )

/*
 * Performs left or right shift on value if a is positive or negative respectively.
 */
#define shift(value, a) ( (!a ? value : (a < 0 ? value >> a : value << a)) )

/*
 * Zeroes the value at the given location using bit math.
 */
__attribute__((hot, pure))
static inline void zero(uqword *restrict in) {
    *in ^= *in;
}

/*
 * Computes the absolute difference of the given values a and b
 */
#define abs_diff(a, b) ( abs((a) - (b)) )

//static inline uqword sqrti(register uqword a);
// TODO dst and sqrti
//static inline uqword dst(register point a, register point b) {
//    return sqrti(abs_diff(b.y, a.y) - abs_diff(b.x, a.x));
//}

/*
 * Generates a mersenne number and shifts by `offset` bits relative to the lsb using the `shift` macro function.
 */
__attribute__((hot, const))
static inline uqword mask(register uqword bits, register qword offset) {
    return shift(((1ull << bits) - 1), offset);
}

/*
 * Generates a bit filter from `value` by masking `bits` bits at `offset` offset relative to the lsb using the
 * `shift` macro function.
 */
__attribute__((hot, const))
static inline uqword filter(register uqword value, register uqword bits, register qword offset) {
    return value & mask(bits, offset);
}

// maintain grouping of functions
static inline uqword sigbits(uqword);

/*
 * Compute number of significant base 10 digits in a given base 2 qword
 */
__attribute__((hot, const))
static inline uqword digits(register uqword bit_string) {
    // ln(10) / ln(2) ~= 3.3219280948873623478703194294894
    const udqword numerator   = 10000ull;
    const udqword denominator = 33219ull;
    const udqword x           = bit_string;
    return (uqword) ((((udqword) sigbits(x)) * numerator) / denominator + 1);
}

/*
 * Zeroes all bits above the given bit index in src.
 */
__attribute__((hot, const))
static inline uqword zero_high_bits(register uqword src, register uqword index) {
    #if ARCH == ARCH_X86_64
    return __x64_bzhiq(src, src, index);
    #elif ARCH == ARCH_X86_32
    return __x86_bzhil(src, src, index);
    #else
    index = 64 - index;
    return (src << index) >> index;
    #endif
}

/*
 * Count the number of leading zeroes in bit_string.
 */
__attribute__((hot, const))
static inline uqword cntlz(register uqword bit_string) {
    #if ARCH == ARCH_X86_32
    return __x86_lzcnt(bit_string);
    #elif ARCH == ARCH_X86_64
    return __x64_lzcnt(bit_string);
    #else
    ubyte zeroes = 0;
    // zeroes to ones
    bit_string = ~bit_string;
    ubyte loop_condition;
    for (uqword i = bitwidth(bit_string) - 1u; i < bitwidth(bit_string) && (loop_condition = (bit_string >> i) & 1u); i++) {
        zeroes += loop_condition;
    }
    return zeroes;
    #endif
}

/*
 * Count the number of trailing zeroes in bit_string.
 */
__attribute__((hot, const))
static inline uqword cnttz(register uqword bit_string) {
    #if ARCH == ARCH_X86_32
    return __x86_tzcnt(bit_string);
    #elif ARCH == ARCH_X86_64
    return __x64_tzcnt(bit_string);
    #else
    ubyte zeroes = 0;
    // zeroes to ones
    bit_string = ~bit_string;
    ubyte loop_condition;
    for (uqword i = 0; i < bitwidth(bit_string) && (loop_condition = (bit_string >> i) & 1u); i++) {
        zeroes += loop_condition;
    }
    return zeroes;
    #endif
}

/*
 * Count the number of ones in a bit_string
 */
__attribute__((hot, const))
static inline uqword ones(register uqword bit_string) {
    #if ARCH == ARCH_X86_32
    return __x86_popcnt(bit_string);
    #elif ARCH == ARCH_X86_64
    return __x64_popcnt(bit_string);
    #else
    ubyte zeroes = 0;
    // zeroes to ones
    bit_string = ~bit_string;
    ubyte loop_condition;
    for (uqword i = 0; i < bitwidth(bit_string) && (loop_condition = (bit_string >> i) & 1u); i++) {
        zeroes += loop_condition;
    }
    return zeroes;
    #endif
}

static inline uqword log2i(register uqword);

// computes 6-bit divide; returns ~0 for y=0 and 0 for y > 64
// intended to be used for computing how many times we must shift.
static inline uqword udiv6(register uqword x, register ubyte y) {
    switch (y) {
        case 0:
            return ~0;
        case 1:
            return x;
        case 2:
            return x >> 1;
        case 3:
            return x / 3;
        case 4:
            return x >> 2;
        case 5:
            return x / 5;
        case 6:
            return x / 6;
        case 7:
            return x / 7;
        case 8:
            return x >> 3;
        case 9:
            return x / 9;
        case 10:
            return x / 10;
        case 11:
            return x / 11;
        case 12:
            return x / 12;
        case 13:
            return x / 13;
        case 14:
            return x / 14;
        case 15:
            return x / 15;
        case 16:
            return x >> 4;
        case 17:
            return x / 17;
        case 18:
            return x / 18;
        case 19:
            return x / 19;
        case 20:
            return x / 20;
        case 21:
            return x / 21;
        case 22:
            return x / 22;
        case 23:
            return x / 23;
        case 24:
            return x / 24;
        case 25:
            return x / 25;
        case 26:
            return x / 26;
        case 27:
            return x / 27;
        case 28:
            return x / 28;
        case 29:
            return x / 29;
        case 30:
            return x / 30;
        case 31:
            return x / 31;
        case 32:
            return x >> 5;
        case 33:
            return x / 33;
        case 34:
            return x / 34;
        case 35:
            return x / 35;
        case 36:
            return x / 36;
        case 37:
            return x / 37;
        case 38:
            return x / 38;
        case 39:
            return x / 39;
        case 40:
            return x / 40;
        case 41:
            return x / 41;
        case 42:
            return x / 42;
        case 43:
            return x / 43;
        case 44:
            return x / 44;
        case 45:
            return x / 45;
        case 46:
            return x / 46;
        case 47:
            return x / 47;
        case 48:
            return x / 48;
        case 49:
            return x / 49;
        case 50:
            return x / 50;
        case 51:
            return x / 51;
        case 52:
            return x / 52;
        case 53:
            return x / 53;
        case 54:
            return x / 54;
        case 55:
            return x / 55;
        case 56:
            return x / 56;
        case 57:
            return x / 57;
        case 58:
            return x / 58;
        case 59:
            return x / 59;
        case 60:
            return x / 60;
        case 61:
            return x / 61;
        case 62:
            return x / 62;
        case 63:
            return x / 63;
        case 64:
            return x >> 6;
        default:
            return 0;
    }
}

/*
 * Compares a power of two encoded as exponent in `exp` to a value in `value` by computing their difference using
 * bit math.
 */
static inline ubyte cmp2pN8(register ubyte exp, register uqword value) {
    const register uqword a = (1 << (exp % bitwidth(a)));
    const register uqword b = value << ((exp - log2i(value)) % bitwidth(b));
    return (a < b) << 1 | (a == 0);
}

/*
 * Evaluates 2**(sign * exp) mod modulus in O(log n) time using bit math. (TODO) sign=0 is interpreted as the imaginary unit .
 */
__attribute__((hot, const))
static inline udqword umod2pN8(register sbyte sign, register ubyte exp, register uqword modulus) {
    uqword a
}

/*
 * Evaluates fast modulus as a mod b to machine precision using bit math.
 */
__attribute__((const))
static inline uqword umodq(register uqword x, register uqword modulus) {
}

/*
 * Evaluates a square wave function of the given periodicity at the given time. Valid periodicity range is equivalent to
 * the number of values supported by uqword.
 *
 * The input is two integers. The returned value is a fixed-point u32.32 value.
 */
__attribute__((hot, const))
static inline uqword square_wave(register uqword period, register uqword time) {
    // implements sgn( (time mod period) - (period - 1)/2 )
    // a = (time mod period)
    register qword a = (qword) (umodq(time, period));
    // --- begin signed arithmetic
    // a - (period - 1)/2
    a -= ((qword) (period - 1ull) >> 1ull);
    return ((uqword) (sign(a) >= 0)) << 31ull;
    // --- end signed arithmetic
}

/*
 * TODO implement square_wave_ext
 *
 * Evaluates a square wave function of the given periodicity at the given time. Valid periodicity range is equivalent to
 * the number of values supported by udqword. Provides no semantic difference over square_wave, but allows a greater
 * periodicity range.
 *
 * The input is two integers. The returned value is a fixed-point u64.64 value.
 */
__attribute__((const))
static inline udqword square_wave_ext(register udqword period, register udqword time) {
}

/*
 *
 * TODO implement square wave function valid for all rationals
 *
 * Evaluates a square wave function of the given periodicity at the given time. Valid periodicity range is equivalent to
 * the number of values supported by the current platform. Provides no semantic difference over square_wave
 * nor square_wave_ext, but allows a virtually infinite range of periodicities by providing an exponent denoting
 * a value for which two is raised to the power of.
 *
 * The time parameter should be aligned to ubyte.
 *
 */
__attribute__((pure))
static inline ubyte square_wave_ext_infty(register udqword period, register udqword time, register udqword exponent) {
}

/*
 * Computes fixed point reciprocal with arbitrary base arithmetic via base two bit math. Supports values in [0, 2^64 - 1].
 */
__attribute__((noinline))
static inline uqword urcpq(register uqword divisor) {
    // used with the digit_bitwidth parameter of functions defined here
    const static ubyte    digit_width_quotient_table = {
            0
    };
    const register uqword base                       = divisor;
    const register bool   divisor_is_power_of_two    = ones(divisor) == 1;
    
    if (divisor_is_power_of_two) {
        return (1ull << (bitwidth(uqword) - 1)) >> log2i(divisor);
    } else {
        // initialize base `divisor` registers
        register udqword erax, erbx, ercx, erdx;
        // define base `divisor` operations necessary for computing reciprocals.
        // apparently inner functions are a security hazard, but whatever--C is a means to an end
        
        // digit shift in native base
        __attribute__((hot, const, always_inline))
        udqword base_div_shift(udqword reg, sbyte digits, ubyte digit_bitwidth) {
            return shift(reg, digits / digit_bitwidth);
        }
        // 2**n in native base
        __attribute__((hot, const, always_inline))
        udqword base_div_pow2(udqword reg, ubyte exponent, ubyte digit_bitwidth) {
        }
    }
    
    // fixed point constant coefficients
    // (-) 0.6296735
    const uqword A = 0xA1325 << (31 - sigbits(0xA1325));
    // (+) 2.726314
    const uqword B = 0x2B9EFB << (31 - sigbits(0x2B9EFB));
    // (-) 2.096641
    const uqword C = 0x218BD7 << (31 - sigbits(0x218BD7));
}

#ifndef BIT_MATH_USE_HW_MUL
  #define BIT_MATH_USE_HW_MUL 1
#endif

/*
 * Uses the fastest multiplier available, either hardware if BIT_MATH_USE_HW_MUL macro is set to a value of 1 and is the
 * default option, or software implementation using bit math.
 */
__attribute__((const))
static inline udqword umulq(register uqword multiplicand, register uqword multiplier) {
    #if BIT_MATH_USE_HW_MUL == 1
    // optimizes to mul which is sufficiently fast
    return multiplicand * multiplier;
    #else
    // TODO create faster SW mul (difficult, considering mul is already 3c, 1t on Ryzen Family 17h)
    return multiplicand * multiplier;
    #endif
}

/*
 * Uses a fast division algorithm to compute divides to machine precision using bit math.
 */
//__attribute__((noinline))
//static inline uqword udivq(register uqword dividend, register uqword divisor) {
//    register uqword a, coefficient_accumulator = 0;
//    if (dividend == divisor) return 1;
//    if (dividend < divisor) return 0;
//
//    // compute largest power of two greater than divisor and less than or equal to dividend
//    const uqword divisor_log = log2i(divisor) + 1;
//    const uqword divisor_pow = 1 << divisor_log;
//algorithm_start:
//    a = dividend >> divisor_log;
//    coefficient_accumulator += a;
//    a *= divisor_pow - divisor;
//
//    if (divisor > a) {
//        return coefficient_accumulator;
//    } else {
//        dividend = a;
//        goto algorithm_start;
//    }
//}

/*
 * Uses a fast division algorithm to compute divides to machine precision using bit math.
 */
__attribute__((noinline))
static inline uqword udivq(register uqword dividend, register uqword divisor) {
    return (uqword)
            ((((udqword) urcpq(divisor)) << bitwidth(urcpq(divisor))) *
             ((udqword) dividend << (bitwidth(urcpq(divisor)))) >>
                                                                bitwidth(urcpq(divisor)));
}

/*
 * Compute the number of significant bits in the given uqword
 */
__attribute__((hot, const))
static inline uqword sigbits(register uqword bit_string) {
    #if defined(__GNUC__)
      #if DATA_MODEL == LLP64 || DATA_MODEL == ILP64 || DATA_MODEL == SILP64
    return bitwidth(typeof(bit_string)) - __builtin_clzll((bit_string | 1ull));
      #elif DATA_MODEL == LP64
    return bitwidth(typeof(bit_string)) - __builtin_clzll((bit_string | 1ul));
      #elif DATA_MODEL == ILP32 || DATA_MODEL == LP32
    return bitwidth(typeof(bit_string)) - __builtin_clz((bit_string | 1u));
      #else
        #error "Unsupported data model"
      #endif
    #elif ARCH == ARCH_X86_32
    return bitwidth(typeof(bit_string)) - __x86_lzcnt((((unsigned long) bit_string) | 1u));
    #elif ARCH == ARCH_AMD64
    return __x64_bsrq((unsigned long long) bit_string);
    #elif ARCH == ARCH_ARM
      #if ARCH_VARIANT == ARCH_ARM32
        return bitwidth(typeof(bit_string)) - __arm32_clz((((unsigned long) bit_string) | 1u));
          #elif ARCH_VARIANT == ARCH_ARM64
        return bitwidth(typeof(bit_string)) - __arm64_clz((((unsigned long) bit_string) | 1u));
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

__attribute__((const))
static inline uqword lerp(register uqword lower_bound, register uqword upper_bound, register uqword x) {
    return lower_bound + x * (upper_bound - lower_bound);
}

/*
 * Compute the distance, i.e. absolute difference, between two values
 */
#define dst(a, b) ( (a) > (b) ? (a) - (b) : (b) - (a) )

/*
 * Compute the number of significant bits in the given signed qword.
 */
__attribute__((const))
static inline uqword sigbitss(register qword bit_string) {
    return sigbits((uqword) bit_string);
}

/*
 * Compute the number of significant bits in the given bit string.
 */
__attribute__((const))
static inline uqword sigbitsn(register uqword *bit_string, register size_t words) {
    uqword     result = 0;
    for (qword i      = (qword) (words - 1u); i >= 0u; i--) {
        result += sigbits(bit_string[i]);
    }
    return result;
}

/*
 * Compute 2 to the power of exponent using integer bit math with truncated results for overflow.
 */
__attribute__((hot, const))
static inline uqword pow2i(register uqword exponent) {
    return 1ull << exponent;
}

/*
 * Compute 2 to the power of exponent for all integers using bit math with truncated results for overflow.
 */
__attribute__((const))
static inline uqword pow2si(register qword exponent) {
    return pow2i(abs(exponent));
}

/*
 * Compute 10 to the power of exponent using integer bit math with truncated results for overflow.
 */
__attribute__((const))
static inline uqword pow10i(register uqword exponent) {
    static const uqword pow10[20] = {
            1ull,
            10ull,
            100ull,
            1000ull,
            10000ull,
            100000ull,
            1000000ull,
            10000000ull,
            100000000ull,
            1000000000ull,
            10000000000ull,
            100000000000ull,
            1000000000000ull,
            10000000000000ull,
            100000000000000ull,
            1000000000000000ull,
            10000000000000000ull,
            100000000000000000ull,
            1000000000000000000ull,
            10000000000000000000ull
    };
    
    return pow10[exponent];
}

#include <math.h>

__attribute__((const))
static inline float fexp(float x) {
    return exp2f(x * 1.4426950408889634073599246810019f);
}

/*
 * Compute e to the power of exponent using integer bit math with truncated results for overflow.
 */
__attribute__((const))
static inline uqword expi(register uqword exponent) {
    //    static const uqword expi[45] = {
    //            1ull,
    //            2ull,
    //            7ull,
    //            20ull,
    //            54ull,
    //            148ull,
    //            403ull,
    //            1096ull,
    //            2980ull,
    //            8103ull,
    //            22026ull,
    //            59874ull,
    //            162754ull,
    //            442413ull,
    //            1202604ull,
    //            3269017ull,
    //            8886110ull,
    //            24154952ull,
    //            65659969ull,
    //            178482300ull,
    //            485165195ull,
    //            1318815734ull,
    //            3584912846ull,
    //            9744803446ull,
    //            26489122129ull,
    //            72004899337ull,
    //            195729609428ull,
    //            532048240601ull,
    //            1446257064291ull,
    //            3931334297144ull,
    //            10686474581524ull,
    //            29048849665247ull,
    //            78962960182680ull,
    //            214643579785916ull,
    //            583461742527454ull,
    //            1586013452313430ull,
    //            4311231547115195ull,
    //            11719142372802611ull,
    //            31855931757113756ull,
    //            86593400423993746ull,
    //            235385266837019985ull,
    //            639843493530054949ull,
    //            1739274941520501047ull,
    //            4727839468229346561ull,
    //            12851600114359308275ull
    //    };
    //
    //    return expi[exponent];
    
    
    //    // log2(e) = 1.4426950408889634073599246810019
    //    const udqword numerator   = 10000000000000000000ull;
    //    const udqword denominator = 14426950408889634073ull;
    //    const udqword x           = exponent;
    //    return pow2i(((uqword) ((x * numerator) / denominator)));
    return (uqword) fexp((float) exponent);
}

/*
 * Compute base to the power of exponent using integer bit math.
 */
__attribute__((const))
static inline uqword powni(register uqword base, register uqword exponent) {
    uqword result = 1;
    
    while (exponent) {
        if (exponent & 1u)
            result *= base;
        exponent >>= 1u;
        base *= base;
    }
    
    return result;
    // TODO implement powni using exp()
    //    return expi(exponent * lni(base));
}

/*
 * Compute log base 2 of the given bit string using integer bit math.
 */
__attribute__((hot, const))
static inline uqword log2i(register uqword bit_string) {
    return sigbits(bit_string) - 1ull;
}

/*
 * Compute log base 10 of the given bit string using integer bit math.
 */
__attribute__((const))
static inline uqword log10i(register uqword bit_string) {
    // ln(10) / ln(2) ~= 3.3219280948873623478703194294894
    const udqword numerator   = 10000ull;
    const udqword denominator = 33219ull;
    const udqword x           = bit_string;
    return (uqword) ((((udqword) sigbits(x)) * numerator) / denominator);
}

/*
 * Computes log_<base>(bit_string) with base as the base, and the given bit string using integer bit math.
 */
__attribute__((const))
static inline uqword logni(register uqword base, register uqword bit_string) {
    return log10i(bit_string) / log10i(base);
}

/*
 * Computes log base e of the given bit string using integer bit math.
 */
__attribute__((const))
static inline uqword lni(register uqword bit_string) {
    // ln(10) / ln(2) * log(e) ~= 1.4426950408889634073599246810019
    const udqword numerator   = 10000000000000000ull;
    const udqword denominator = 14426950408889634ull;
    const udqword x           = bit_string;
    // log(bit_string) / log(e)
    return (uqword) (((sigbits(x)) * numerator) / denominator);
}

/*
 * Computes the value of a single bit at a given digit offset from the right.
 */
__attribute__((hot, const))
static inline uqword get_digit2i(uqword value, uqword digit) {
    return (value >> digit) & 1;
}

/*
 * Computes the value of a single base 10 digit at the given digit offset.
 */
__attribute__((const))
static inline uqword get_digit10i(uqword value, uqword digit) {
    value /= pow10i(digit);
    return value % 10ull;
}

/*
 * Doubles the given value using bit math.
 */
__attribute__((hot, const))
static inline uqword dbl(register uqword const value) {
    return value << 1u;
}

/*
 * Halves the given value using bit math.
 */
__attribute__((hot, const))
static inline uqword hlv(register uqword const value) {
    return value >> 1u;
}

// data structures

/*
 * Compute if given value is within the range [min, max].
 */
__attribute__((hot, const))
static inline bool in_range(register uqword const min, register uqword const max, register uqword const value) {
    return (min <= value) & (value <= max);
}

/*
 * Compute if given value is within the range [min, max).
 */
__attribute__((hot, const))
static inline bool in_buffer(register uqword const min, register uqword const max, register uqword const value) {
    return (min <= value) & (value < max);
}

/*
 * Gets the binary index of a given address in a binary binary_tree.
 * For a given bit binary_tree of N bits, there are 2*(2^N) - 2 bits in the binary_tree, and 2^N - 1 indices for either the left or
 * right side, so the index may be calculated as 2 * (2^log_2(address)) - 2 + address - side_bit * pow2(log_2(address)). The
 * right-most bit determines which side of the binary_tree will be accessed, either 0 for left, or 1 for right.
 * (See <https://www.desmos.com/calculator/z8l7kyskro>)
 */
__attribute__((const))
static inline uqword bin_index(register uqword address) {
    uqword side = address & 1u;
    address >>= 1u;
    if (!address)
        return side;
    uqword address_bits = log2i(address);
    // 2 * pow2i(address_bits) - 2u + address - side * pow2i(address_bits)
    return address == 1 ? side : (2ull << address_bits) - 2u + address - side * (1ull << address_bits);
}

__attribute__((pure))
static inline uqword get_bita(uqword const *restrict bitarray, uqword const words, uqword const bit_index) {
    uqword bits = sizeof(uqword) * sizeof(uintmin_t) * MIN_BITS;
    
    uqword index = bit_index / bits;
    if (!in_buffer(0, words, index))
        fatalf(__func__, "index out of range: 0 <= index=%u < %u\n", index, words);
    
    uqword word = bitarray[index];
    uqword bit  = (word >> (bit_index % bits)) & ((uqword) 1u);
    return bit;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

__attribute__((hot, const))
static inline uqword get_bit(uqword bit_string, ubyte bit) {
    return (bit_string >> bit) & 1ull;
}

__attribute__((hot, const))
static inline uqword set_bit(uqword bit_string, ubyte bit, ubyte value) {
    bit_string ^= (-value ^ bit_string) & (1ull << bit);
    return bit_string;
}

__attribute__((pure))
static inline uqword *get_bitsa(uqword const *restrict bitarray, uqword const words, uqword const bit_index, uqword const value_bits) {
    // TODO implement get_bits
    uqword bits = sizeof(uqword) * sizeof(uintmin_t) * MIN_BITS;
    
    uqword start = bit_index / bits;
    if (!in_buffer(0, words, start))
        fatalf(__func__, "start out of range: 0 <= start=%u < %u\n", start, words);
    
    uqword end = (bit_index + value_bits - 1u) / bits;
    if (!in_buffer(0, words, end))
        fatalf(__func__, "end out of range: 0 <= end=%u < %u\n", end, words);
    
    for (uqword i = start; i < end; i++) {
    }
}

static inline void set_bita(uqword *restrict bitarray, uqword const words, uqword const bit_offset, uqword const value) {
    uqword bits  = sizeof(uqword) * sizeof(uintmin_t) * MIN_BITS;
    uqword index = bit_offset / bits;
    // guard
    if (!in_buffer(0, words, index))
        fatalf(__func__, "index out of range: 0 <= index=%u < %u\n", index, words);
    uqword word = bitarray[index];
    word ^= (word ^ ((value & ((uqword) 1u)) << (bit_offset % bits))) & (((uqword) 1u) << (bit_offset % bits));
    bitarray[index] = word;
}

static inline void set_bitsa() {
    // TODO implement set_bits
}

static inline uqword clear_bit(uqword bit_string, ubyte bit) {
    bit_string &= ~(1ull << bit);
    return bit_string;
}

static inline uqword toggle_bit(uqword bit_string, ubyte bit) {
    bit_string ^= (1ull << bit);
    return bit_string;
}

#endif //PROJECT_AQUINAS_BIT_MATH_H
