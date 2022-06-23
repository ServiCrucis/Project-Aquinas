#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-no-int-to-ptr"
/*
* Module: tests
* File: tests.h
* Created:
* November 08, 2020
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
*/

#pragma clang diagnostic push
//#pragma ide diagnostic ignored "IncompatibleTypes"
#ifndef PROJECT_AQUINAS_TESTS_H
  #define PROJECT_AQUINAS_TESTS_H
  
  #include <dynarray.h>
  #include "state.h"
  #include "compiler.h"
  #include "bit_math.h"
  #include "memory/memory.h"
  #include "data.h"
  
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-function"

static void test_expi() {
    for (ubyte i = 0; i < 45; i++) {
        infof(__func__, "expi(%llu): %llu\n", i, expi(i));
    }
}

static void test_lni() {
    for (ubyte i = 0; i < 45; i++) {
        infof(__func__, "floor_lni(%llu): %llu\n", expi(i), floor_lni(expi(i)));
    }
}

static void test_log10i() {
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1ull, floor_log10i(1ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10ull, floor_log10i(10ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100ull, floor_log10i(100ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000ull, floor_log10i(1000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000ull, floor_log10i(10000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000ull, floor_log10i(100000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000ull, floor_log10i(1000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000ull, floor_log10i(10000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000ull, floor_log10i(100000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000ull, floor_log10i(1000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000ull, floor_log10i(10000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000ull, floor_log10i(100000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000ull, floor_log10i(1000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000ull, floor_log10i(10000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000ull, floor_log10i(100000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000ull, floor_log10i(1000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000ull, floor_log10i(10000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000000ull, floor_log10i(100000000000000000ul));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000000ull, floor_log10i(1000000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000000ull, floor_log10i(10000000000000000000ull));
}

static void test_sigbits() {
    for (uqword i = 0; i < 256; i++) {
        infof(__func__, "sigbits(%llu): %llu\n", i, sigbits(i));
    }
}

static void test_digits() {
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1ull, digits(1ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10ull, digits(10ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100ull, digits(100ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000ull, digits(1000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000ull, digits(10000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000ull, digits(100000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000ull, digits(1000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000ull, digits(10000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000ull, digits(100000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000ull, digits(1000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000ull, digits(10000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000ull, digits(100000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000ull, digits(1000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000ull, digits(10000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000ull, digits(100000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000ull, digits(1000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000ull, digits(10000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000000ull, digits(100000000000000000ul));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000000ull, digits(1000000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000000ull, digits(10000000000000000000ull));
}

static void test_to_digits() {
    uqword     value = UINT64_MAX;
    ubyte      digits[20];
    for (ubyte i     = 19; i < 20; i--) {
        digits[i] = (ubyte) get_digit10i(value, i);
        infof(__func__, "digit[%llu] = %llu\n", i, digits[i]);
    }
}

static void test_cpuid() {
    #if DATA_MODEL == LP64 || DATA_MODEL == ILP64 || DATA_MODEL == LLP64 || DATA_MODEL == SILP64
    if (!__x64_cpuid_supported())
            #elif DATA_MODEL == LP32 || DATA_MODEL == ILP32
        if (!__x86_cpuid_supported())
        #else
          #error "This (x86?) platform is not currently supported"
            #endif
        fatalf(__func__, "Unable to initialize CPU info: CPUID instruction not supported");
    
    info(__func__, "CPUID is supported on this platform\n");
}

static void test_dynarray() {
}

static void test_map() {
}

static void test_square_wave() {
    info(__func__, "beginning test of square_wave()\n");
    
    for (ubyte i = 0; i < 32; i++) {
        infof(__func__, "square_wave(period=3, time=loop_index) = %u\n", square_wave(3, i));
    }
    
    info(__func__, "-----------------------\n");
    
    for (ubyte i = 0; i < 32; i++) {
        infof(__func__, "square_wave_ext(period=2, time=loop_index) = %u\n", square_wave_ext(2, i));
    }
    
    info(__func__, "square_wave() test complete\n");
}

static void test_udiv() {
    info(__func__, "beginning unsigned integer division test\n");
    
    infof(__func__, "udiv(): %u / %u = %u\n", 0xFFFFFFFFFFFFFFFF, 3, udivq(0xFFFFFFFFFFFFFFFF, 3));
    //    for(ubyte i = 1; i < 65; i++) {
    //        for (ubyte j = 1; j < 64; j++) {
    //            infof(__func__, "udiv(): %u / %u = %u\n", j, i, udivq(j, i));
    //        }
    //    }
    //
    //    for(ubyte i = 1; i < 65; i++) {
    //        for (ubyte j = 1; j < 64; j++) {
    //            infof(__func__, "using divide C syntax: %u / %u = %u\n", j, i, j / i);
    //        }
    //    }
    
    info(__func__, "unsigned integer division test complete\n");
}

static void test_umod() {
    info(__func__, "beginning unsigned integer modulus test\n");
    
    for (uword i = 1; i < 257; i++) {
        for (uword j = 0; j < 256; j++) {
            infof(__func__, "umod(): %u %% %u = %u\n", j, i, umodq(j, i));
        }
    }
    
    for (uword i = 0; i < 256; i++) {
        for (uword j = 0; j < 256; j++) {
            infof(__func__, "using modulus C syntax: %u %% %u = %u\n", j, i, j % i);
        }
    }
    
    info(__func__, "unsigned integer modulus test complete\n");
}

static void test_fp_math() {
}

static void test_pointer() {
    auto volatile uintptr_t test_ptr_auto;
    volatile void           *test_ptr_heap;
    auto volatile void      *test_ptr_stack;
    // initialize pointers
    test_ptr_heap = malloc(sizeof(test_ptr_heap));
    if (!test_ptr_heap)
        fatalf(__func__, "insufficient memory for test; could not allocate %llu bytes", sizeof(test_ptr_heap));
    test_ptr_stack = alloca(sizeof(test_ptr_heap));
    // test pointers
    auto volatile relative_pointer test_relptr_auto  = pointer_deconstruct(&test_ptr_auto, 1);
    volatile relative_pointer      test_relptr_heap  = pointer_deconstruct(test_ptr_heap, 3);
    auto volatile relative_pointer test_relptr_stack = pointer_deconstruct(test_ptr_stack, 5);
    info(__func__, "beginning pointer deconstruction test\n");
    infof(__func__, "\t&test_ptr_auto: %p\n", &test_ptr_auto);
    infof(__func__, "\ttest_ptr_heap: %p\n", test_ptr_heap);
    infof(__func__, "\ttest_ptr_stack: %p\n", test_ptr_stack);
    infof(__func__, "\n");
    infof(__func__, "\ttest_relptr_auto offset: %p\n", test_relptr_auto.offset);
    infof(__func__, "\test_relptr_heap offset: %p\n", test_relptr_heap.offset);
    infof(__func__, "\ttest_relptr_stack offset: %p\n", test_relptr_stack.offset);
    infof(__func__, "\n");
    infof(__func__, "\ttest_relptr_auto base: %p\n", test_relptr_auto.base);
    infof(__func__, "\ttest_relptr_heap base: %p\n", test_relptr_heap.base);
    infof(__func__, "\ttest_relptr_stack base: %p\n", test_relptr_stack.base);
    infof(__func__, "\n");
    infof(__func__, "\ttest_relptr_auto reconstruction: %p\n", pointer_reconstruct(test_relptr_auto));
    infof(__func__, "\ttest_relptr_heap reconstruction: %p\n", pointer_reconstruct(test_relptr_heap));
    infof(__func__, "\ttest_relptr_stack reconstruction: %p\n", pointer_reconstruct(test_relptr_stack));
    info(__func__, "pointer deconstruction test complete");
    
    free(test_ptr_heap);
}

static void test_data_byte_order() {
    info(__func__, "beginning byte order write test\n");
    uqword test_lo_to_hi = 0x0000AABBCCDDEEFF;
    uqword test_hi_to_lo = 0xFFEEDDCCBBAA0000;
    
    info(__func__, "beginning lo to hi interpret test\n");
    infof(__func__, "\ttest_lo_to_hi before: %#16llx\n", test_lo_to_hi);
    data_write_as(1, sizeof(test_lo_to_hi),
                  &test_lo_to_hi, BYTE_ORDER_LITERAL_LO_AT_LO,
                  &test_lo_to_hi, BYTE_ORDER_LITERAL_HI_AT_LO);
    infof(__func__, "\ttest_lo_to_hi after: %#16llx\n", test_lo_to_hi);
    
    info(__func__, "beginning hi to lo interpret test\n");
    infof(__func__, "\ttest_hi_to_lo before: %#16llx\n", test_hi_to_lo);
    data_write_as(1, sizeof(test_hi_to_lo),
                  &test_hi_to_lo, BYTE_ORDER_LITERAL_HI_AT_LO,
                  &test_hi_to_lo, BYTE_ORDER_LITERAL_LO_AT_LO);
    infof(__func__, "\ttest_hi_to_lo after: %#16llx\n", test_hi_to_lo);
    
    // test unaligned
    
    ubyte test_unaligned[9] = {
            (ubyte) 0x00, (ubyte) 0xAA, (ubyte) 0xBB, (ubyte) 0xCC, (ubyte) 0xDD, (ubyte) 0xEE, (ubyte) 0xFF, (ubyte) 0x00, (ubyte) 0x00
    };
    
    info(__func__, "beginning unaligned hi to lo interpret test\n");
    infof(__func__, "\ttest_unaligned before: %#16llx\n", *(uqword *) &test_unaligned[0]);
    
    data_write_as(1, 9,
                  test_unaligned, BYTE_ORDER_LITERAL_LO_AT_LO,
                  test_unaligned, BYTE_ORDER_LITERAL_HI_AT_LO);
    infof(__func__, "\ttest_unaligned after: %#16llx\n", *(uqword *) &test_unaligned[0]);
}
  
  #pragma GCC diagnostic pop

#endif //PROJECT_AQUINAS_TESTS_H

//#pragma clang diagnostic pop
#pragma clang diagnostic pop