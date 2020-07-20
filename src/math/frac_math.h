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
#include "bit_math.h"

typedef union decimal {
	struct {
		word numerator: (bitwidth(word) / 2);
		word denominator: (bitwidth(word) / 2);
	};
	
	word value;
} fraction;

typedef union ieee_float32 {
	struct {
		uint32_t sign: 1;
		uint32_t exponent: 8;
		uint32_t fraction: 23;
	};
	float value;
} ieee_float32;

typedef union ieee_float64 {
	struct {
		uint64_t sign: 1;
		uint64_t exponent: 11;
		uint64_t fraction: 52;
	};
	double value;
} ieee_float64;

static inline fraction frc(register word numerator, register word denominator) {
	return (fraction) {{ numerator, denominator}};
}

static inline fraction flt_to_frc(ieee_float32 a) {
}

static inline fraction dbl_to_frc(ieee_float64 a) {
}

static inline ieee_float32 frc_to_flt(fraction a) {
}

static inline ieee_float64 frc_to_dbl(fraction a) {
}

static inline fraction frc_add(register fraction a, register fraction b) {
	b.denominator = a.denominator * b.denominator;
	b.numerator   = a.numerator + b.numerator;
	return b;
}

static inline fraction frc_sub(register fraction a, register fraction b) {
	b.denominator = a.denominator * b.denominator;
	b.numerator   = a.numerator - b.numerator;
	return b;
}

static inline fraction frc_mul(register fraction a, register fraction b) {
	b.numerator   = a.numerator * b.numerator;
	b.denominator = a.denominator * b.denominator;
	return b;
}

static inline fraction frc_div(register fraction a, register fraction b) {
	a.numerator   = a.numerator * b.denominator;
	a.denominator = a.denominator * b.numerator;
	return a;
}

static inline uword frc_absi(word a) {
	return a < 0 ? -a : a;
}

static inline fraction frc_abs(register fraction a) {
	a.numerator = frc_absi(a.numerator);
	a.denominator = frc_absi(a.denominator);
	return a;
}

// for values greater than 0
static inline uword frc_gcdi(register uword a, register uword b) {
	if (!b)
		return a;
	else
		return frc_gcdi(b, a % b);
}

static inline fraction frc_gcd(register fraction a, register fraction b) {
	a.numerator = frc_gcdi(frc_absi(a.numerator), frc_absi(b.numerator));
	a.denominator = frc_gcdi(frc_absi(a.denominator), frc_absi(b.denominator));
	return a;
}

/*
 * Simplifies the given value without loss of information.
 */
static inline fraction frc_simplify(register fraction a) {
	uword gcd = frc_gcdi(frc_absi(a.numerator), frc_absi(a.denominator));
	return (fraction) {{ a.numerator / gcd, a.denominator / gcd}};
}

#endif //CATHOLICUS_FRAC_MATH_H
