/*
 * Module: frac_math
 * File: frac_math.h
 * Created:
 * May 25, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef CATHOLICUS_FRAC_MATH_H
#define CATHOLICUS_FRAC_MATH_H

#include "platform.h"
#include "asm.h"

typedef union decimal {
    struct {
        // sign of the numerator
        uint_fast64_t sign: 1;
        // designates starting bit of denominator
        // as bit shift delta from right
        uint_fast64_t divider: 6;
        // numerator and denominator
        uint_fast64_t significand: 57;
    };

    uqword value;
} frac_t;

typedef union ieee_float32 {
    struct {
        uint32_t sign: 1;
        uint32_t exponent: 8;
        uint32_t significand: 23;
    };
    float value;
} ieee_float32;

typedef union ieee_float64 {
    struct {
        uint64_t sign: 1;
        uint64_t exponent: 11;
        uint64_t significand: 52;
    };
    double value;
} ieee_float64;


#define bitwidth(Type) (sizeof(Type) * MIN_BITS)
#define truncate(value, bits) ( (value << (sizeof(typeof(value)) * MIN_BITS - bits)) >> (sizeof(typeof(value)) * MIN_BITS - bits) )
static inline uqword frc_sigbits(register uqword bit_string) {
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
#elif ARCH == ARCH_X86_32
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
static inline uqword frc_bitmaskv(register uqword value, register uqword bit_count) {
    return truncate(~value, bit_count) ^ value;
}
static inline uqword frc_gcdi(register uqword a, register uqword b);
static inline frac_t frc(register int32_t numerator, register int32_t denominator) {
    #define max(a, b) ( (a) > (b) ? (a) : (b) )
    frac_t fraction;
    fraction.sign = numerator < 0;
    fraction.divider = frc_sigbits(denominator);
    register uqword r0 = frc_gcdi(numerator, denominator);
    register uqword r1;
    numerator = numerator / r0;
    denominator = denominator / r0;
    r0 = frc_sigbits(denominator);
    r1 = frc_sigbits(numerator);

    if ((r0 = (r0 + r1)) > 57) {
        r0 = (r0 - 57) >> 1;
        numerator >>= r0;
        denominator >>= r0;
    }

    fraction.significand = (numerator << fraction.divider) | denominator;
    return fraction;
    #undef max
}

//static inline frac_t flt_to_frc(ieee_float32 a) {
//}
//
//static inline frac_t dbl_to_frc(ieee_float64 a) {
//}
//
//static inline ieee_float32 frc_to_flt(frac_t a) {
//}
//
//static inline ieee_float64 frc_to_dbl(frac_t a) {
//}

static inline int32_t frc_rdnum(register frac_t a) {
    return (-1 * a.sign) * (a.significand >> a.divider);
}

static inline int32_t frc_rdden(register frac_t a) {
    return (-1 * a.sign) * (a.significand & frc_bitmaskv(a.significand, 63 - a.divider));
}

//static inline uqword frc_ctz10(register uqword a) {
//
//}

static inline frac_t frc_add(register frac_t a, register frac_t b) {
    register int32_t a_num = frc_rdnum(a);
    register int32_t a_den = frc_rdden(a);
    register int32_t b_num = frc_rdnum(b);
    register qword   b_den = frc_rdden(b);
    // normalize fractions
    if (b_den != a_den) {
        b_num = b_num * a_den;
        a_num = a_num * b_den;
    }

    // add numerators
    a_num = a_num + b_num;
    a.divider = frc_sigbits((uqword) a_den);
    a.significand = (a_num << a.divider) | a_den;
    return a;
}

static inline frac_t frc_sub(register frac_t a, register frac_t b) {
    register int32_t a_num = frc_rdnum(a);
    register int32_t a_den = frc_rdden(a);
    register int32_t b_num = frc_rdnum(b);
    register int32_t b_den = frc_rdden(b);
    // normalize fractions
    if (b_den != a_den) {
        b_num = b_num * a_den;
        a_num = a_num * b_den;
    }

    // subtract numerators
    a_num = a_num - b_num;
    a.divider = frc_sigbits((uqword) a_den);
    a.significand = (a_num << a.divider) | a_den;
    return a;
}

static inline frac_t frc_mul(register frac_t a, register frac_t b) {
    register int32_t a_num = frc_rdnum(a);
    register int32_t a_den = frc_rdden(a);
    register int32_t b_num = frc_rdnum(b);
    register int32_t b_den = frc_rdden(b);
    // multiply the fractions
    a_num = a_num * b_num;
    a_den = a_den * b_den;
    a.divider = frc_sigbits((uqword) a_den);
    a.significand = (a_num << a.divider) | a_den;
    return a;
}

static inline frac_t frc_div(register frac_t a, register frac_t b) {
    register int32_t a_num = frc_rdnum(a);
    register int32_t a_den = frc_rdden(a);
    register int32_t b_num = frc_rdnum(b);
    register int32_t b_den = frc_rdden(b);

    // divide the fractions (via multiply)
    a_num = a_num * b_den;
    a_den = a_den * b_num;
    a.divider = frc_sigbits((uqword) a_den);
    a.significand = (a_num << a.divider) | a_den;
    return a;
}

static inline int32_t frc_absi(int32_t a) {
    return a < 0 ? (~a) + 1 : a;
}

static inline frac_t frc_abs(register frac_t a) {
    a.sign = 0;
    return a;
}

#define max(a, b) ( (a) > (b) ? (a) : (b) )
#define min(a, b) ( (a) < (b) ? (a) : (b) )
#define abs(a) ( (a) > 0 ? (a) : -(a) )
#define abs_diff(a, b) ( abs((a) - (b)) )

static inline uqword frc_log2i(register uqword a) {
    return frc_sigbits(a) - 1u;
}

// 3c
static inline void frc_swap_max(register uqword *a, register uqword *b) {
    register uqword c = *a;
    *a = max(*a, *b);
    *b = min(c, *b);
}

static inline uqword frc_gcdi(uqword a, uqword b) {
    // 11c
    register uqword delta = min(frc_log2i(a), frc_log2i(b));
    a >>= delta;
    b >>= delta;
    a >>= __x64_tzcnt(a);
    b >>= __x64_tzcnt(b);
    // 32 * (8) = 256c
    while(b) {
        frc_swap_max(&a, &b);
        b = b - a;
        b >>= __x64_tzcnt(b);
    }
    // 2c
    return a << delta;
}

static inline uqword frc_gcd(register frac_t a) {
    return frc_gcdi(frc_rdnum(a), frc_rdden(a));

}

/*
 * Simplifies the given value without loss of information.
 */
//static inline frac_t frc_simplify(register frac_t a) {
//    register uqword gcd = frc_gcd(a);
//    register uint32_t numerator = frc_rdnum(a);
//    register uint32_t denominator = frc_rdden(a);
//
//}

#endif //CATHOLICUS_FRAC_MATH_H
