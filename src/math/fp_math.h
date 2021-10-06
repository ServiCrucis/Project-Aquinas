/*
 * Module: fp_math
 * File: fp_math.h
 * Created:
 * August 15, 2021
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2021 Christi Crucifixi, LLC. All rights reserved.
 *
 * License: See LICENSE.txt
 */


#include <platform.h>
#ifndef PROJECT_AQUINAS_FP_MATH_H
  #define PROJECT_AQUINAS_FP_MATH_H

typedef float       machine_float;
typedef double      machine_double;
typedef long double machine_long_double;

  #ifndef FP_INTERNAL_FLOAT_DATATYPE
    #define FP_INTERNAL_FLOAT_DATATYPE uqword
  #endif

  #ifndef FP_MANTISSA_BITS
    #define FP_MANTISSA_BITS
  #endif

  #ifndef FP_USE_IEEE754
    #define FP_USE_IEEE754 24
  #endif

typedef union fp_float {
} fp_float;

typedef struct fp_double {
} fp_double;

typedef struct fp_long_double {
} fp_long_double;

typedef union fp_rational {
} fp_rational;

static fp_float fp_add(fp_float a, fp_float b) {
}

#endif //PROJECT_AQUINAS_FP_MATH_H
