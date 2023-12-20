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
#include <errhandlingapi.h>
#include "state.h"
#include "compiler.h"
#include "bit_math.h"
#include "state/allocating.h"
#include "data.h"
#include "state/windows/m_windows_ImperfectUnitStackAllocator.h"
#include "state/m_pointer_offset.h"
#include "state/windows/m_windows.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

static void test_expi(void) {
    for (ubyte i = 0; i < 45; i++) {
        infof(__func__, "expi(%llu): %llu\n", i, expi(i));
    }
}

static void test_lni(void) {
    for (ubyte i = 0; i < 45; i++) {
        infof(__func__, "floor_lni(%llu): %llu\n", expi(i), floor_lni(expi(i)));
    }
}

static void test_log10i(void) {
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
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000000ull,
          floor_log10i(1000000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000000ull,
          floor_log10i(10000000000000000000ull));
}

static void test_sigbits(void) {
    for (uqword i = 0; i < 256; i++) {
        infof(__func__, "sigbits(%llu): %llu\n", i, sigbits(i));
    }
}

static void test_digits(void) {
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

static void test_to_digits(void) {
    uqword value = UINT64_MAX;
    ubyte digits[20];
    for (ubyte i = 19; i < 20; i--) {
        digits[i] = (ubyte) get_digit10i(value, i);
        infof(__func__, "digit[%llu] = %llu\n", i, digits[i]);
    }
}

static void test_cpuid(void) {
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

static void test_dynarray(void) {
}

static void test_map(void) {
}

static void test_square_wave(void) {
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

static void test_udiv(void) {
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

static void test_umod(void) {
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

static void test_fp_math(void) {
}

static void test_m_pointer_offset(void) {
    info(__func__, "beginning pointer offset test\n");
    info(__func__, "m_compute_required_space(address_bits=64, offset_bits=63, elements=0xFFFFFFFFFFFFFFFF): \n");

    udqword result = m_compute_required_space(64, 63, 0xFFFFFFFFFFFFFFFF);
    infof(__func__, "\thi 64: %llX\n", (uqword) (result >> 64));
    infof(__func__, "\tlo 64: %llX\n", (uqword) (result & 0xFFFFFFFFFFFFFFFF));

    udqword expected = ((udqword) 0x3E << 64) | 0xFFFFFFFFFFFFFFC3;
    if (abs_diff(expected, result) != 0) {
        warnf(__func__, "pointer offset test failed: expected does not match result:\n");
        warnf(__func__, "difference: %llX\n", (uqword) abs_diff(expected, result));
    }

}

static void test_data_byte_order(void) {
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
            (ubyte) 0x00, (ubyte) 0xAA, (ubyte) 0xBB, (ubyte) 0xCC, (ubyte) 0xDD, (ubyte) 0xEE, (ubyte) 0xFF,
            (ubyte) 0x00, (ubyte) 0x00
    };

    info(__func__, "beginning unaligned hi to lo interpret test\n");
    infof(__func__, "\ttest_unaligned before: %#16llx\n", *(uqword *) &test_unaligned[0]);

    data_write_as(1, 9,
                  test_unaligned, BYTE_ORDER_LITERAL_LO_AT_LO,
                  test_unaligned, BYTE_ORDER_LITERAL_HI_AT_LO);
    infof(__func__, "\ttest_unaligned after: %#16llx\n", *(uqword *) &test_unaligned[0]);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"

static void test_w32_memory_allocator(void) {
#if PROJECT_AQUINAS_TEST_WIN32_MEMORY_ALLOCATOR == 1
    // defined in m_windows.c
    extern w32_m_object w32_m_reserve(udqword const bits, enum w32_object_type const, enum w32_state_type const);
    extern void w32_m_transmute(m_context const object, enum w32_object_type const object_type,
                                enum w32_state_type const state_type);
    extern void w32_m_relinquish(w32_m_object *const);

    volatile w32_m_object test_state_read = NULL;
    volatile w32_m_object test_state_write = NULL;
    volatile w32_m_object test_state_read_write = NULL;
    volatile w32_m_object test_state_noread_nowrite = NULL;

    info(__func__, "beginning Win32 memory allocator test\n");
    info(__func__, "pre-init state:\n");
    infof(__func__, "test_state_read = %p\n", test_state_read);
    infof(__func__, "test_state_write = %p (FIXME)\n", test_state_write);
    infof(__func__, "test_state_read_write = %p\n", test_state_read_write);
    infof(__func__, "test_state_noread_nowrite = %p\n", test_state_noread_nowrite);

    info(__func__, "\n");
    info(__func__, "post-init state:\n");

    // initialize as write-only first
    test_state_read = w32_m_reserve(255, STATE, WRITE);
    DWORD ERROR_CODE = GetLastError();
    infof(__func__, "test_state_read = %p\n", test_state_read);
    infof(__func__, "last error code: %i\n", ERROR_CODE);

    test_state_write = w32_m_reserve(256, STATE, WRITE);
    ERROR_CODE = GetLastError();
    infof(__func__, "test_state_write = %p (FIXME)\n", test_state_write);
    infof(__func__, "last error code: %i\n", ERROR_CODE);

    test_state_read_write = w32_m_reserve(257, STATE, READ_WRITE);
    ERROR_CODE = GetLastError();
    infof(__func__, "test_state_read_write = %p\n", test_state_read_write);
    infof(__func__, "last error code: %i\n", ERROR_CODE);

    test_state_noread_nowrite = w32_m_reserve(258, STATE, NO_READ_NO_WRITE);
    ERROR_CODE = GetLastError();
    infof(__func__, "test_state_noread_nowrite = %p\n", test_state_noread_nowrite);
    infof(__func__, "last error code: %i\n", ERROR_CODE);

    info(__func__, "\n");
    info(__func__, "beginning write test\n");

    // set as read-only before writing
    ((word *) test_state_read)[0] = 0x0123;
    DWORD read_error_code = GetLastError();
    info(__func__, "test_state_read[?] = 0x0123;\n");
    infof(__func__, "last error code: %i\n", read_error_code);

    ((word *) test_state_write)[0] = 0x4567;
    DWORD write_error_code = GetLastError();
    info(__func__, "test_state_write[?] = 0x4567; (FIXME) \n");
    infof(__func__, "last error code: %i\n", write_error_code);

    ((word *) test_state_read_write)[0] = 0x89AB;
    DWORD read_write_error_code = GetLastError();
    info(__func__, "test_state_read_write[?] = 0x89AB;\n");
    infof(__func__, "last error code: %i\n", read_write_error_code);

//    w32_m_transmute(test_state_noread_nowrite, STATE, READ);
//    ((word *) test_state_noread_nowrite)[0] = 0xCDEF;
//    DWORD noread_nowrite_error_code = GetLastError();
//    info(__func__, "test_state_noread_nowrite[?] = 0xCDEF;\n");
//    infof(__func__, "last error code: %i\n", noread_nowrite_error_code);

    info(__func__, "\n");
    info(__func__, "beginning read test\n");

    infof(__func__, "test_state_read value: %u\n", ((word *) test_state_read)[0]);
    read_error_code = GetLastError();
    infof(__func__, "last error code: %i\n", read_error_code);

    infof(__func__, "test_state_write value: %u\n", ((word *) test_state_write)[0]);
    write_error_code = GetLastError();
    infof(__func__, "last error code: %i\n", write_error_code);

    infof(__func__, "test_state_read_write value: %u\n", ((word *) test_state_read_write)[0]);
    read_write_error_code = GetLastError();
    infof(__func__, "last error code: %i\n", read_write_error_code);

//    infof(__func__, "test_state_noread_nowrite value: %u\n", ((word *) test_state_noread_nowrite)[0]);
//    noread_nowrite_error_code = GetLastError();
//    infof(__func__, "last error code: %i\n", noread_nowrite_error_code);

    info(__func__, "\n");
    info(__func__, "freeing pointers\n");

    w32_m_relinquish(&test_state_read);
    read_error_code = GetLastError();

    w32_m_relinquish(&test_state_write);
    write_error_code = GetLastError();

    w32_m_relinquish(&test_state_read_write);
    read_write_error_code = GetLastError();

//    w32_m_relinquish(&test_state_noread_nowrite);
//    noread_nowrite_error_code = GetLastError();

    info(__func__, "pointers freed\n");
    infof(__func__, "test_state_read = %p\n", test_state_read);
    infof(__func__, "last error code: %i", read_error_code);

    infof(__func__, "test_state_write = %p (FIXME)\n", test_state_write);
    infof(__func__, "last error code: %i", write_error_code);

    infof(__func__, "test_state_read_write = %p\n", test_state_read_write);
    infof(__func__, "last error code: %i", read_write_error_code);

//    infof(__func__, "test_state_noread_nowrite = %p\n", test_state_noread_nowrite);
//    infof(__func__, "last error code: %i\n", noread_nowrite_error_code);
#endif
}

static void test_w32_stack_allocator(void) {
    info(__func__, "Beginning Win32 ImperfectUnitStackAllocator test\n");

    register machine_workeld const heap_size = 4096 * bitwidth(ubyte) + 255;
    ImperfectUnitStackAllocator unit_stack = M_WINDOWS_WIN32_GLOBAL_IMPERFECT_UNIT_STACK_ALLOCATOR;
    w32_stack_create(heap_size);

    infof(__func__, "\tinitial stack end=%llX%llX\n",
            (uqword) (unit_stack.end() >> 64),
            (uqword) (unit_stack.end()));

    // test allocate()
    m_windows_stack_pointer allocate_allocation = unit_stack.allocate();
    infof(__func__, "allocate() succeeded; allocate_allocation=%llX%llX\n",
          (uqword) (allocate_allocation >> 64),
          (uqword) (allocate_allocation));
    infof(__func__, "\tstack end=%llX%llX\n",
          (uqword) (unit_stack.end() >> 64),
          (uqword) (unit_stack.end()));
    info(__func__, "\n");

    // test allocate_all()
    register machine_workeld const allocate_all_allocation_size = 4096 * bitwidth(ubyte);
    m_windows_stack_pointer allocate_all_allocation = unit_stack.allocate_all(allocate_all_allocation_size);
    infof(__func__, "allocate_all() succeeded; allocate_all_allocation=%llX%llX\n",
          (uqword) (allocate_all_allocation >> 64),
          (uqword) (allocate_all_allocation));
    infof(__func__, "\tstack end=%llX%llX\n",
          (uqword) (unit_stack.end() >> 64),
          (uqword) (unit_stack.end()));
    info(__func__, "\n");

    // test deallocate()
    unit_stack.allocate();
    info(__func__, "\tallocate()\n");
    infof(__func__, "\tstack end=%llX%llX\n",
          (uqword) (unit_stack.end() >> 64),
          (uqword) (unit_stack.end()));
    info(__func__, "\tdeallocate()\n");
    unit_stack.deallocate();
    infof(__func__, "\tstack end=%llX%llX\n",
          (uqword) (unit_stack.end() >> 64),
          (uqword) (unit_stack.end()));
    info(__func__, "deallocate() succeeded\n");
    infof(__func__, "\tstack end=%llX%llX\n",
          (uqword) (unit_stack.end() >> 64),
          (uqword) (unit_stack.end()));
    info(__func__, "\n");

    // test deallocate_all()
    info(__func__, "\tdeallocate_all()\n");
    unit_stack.deallocate_all(allocate_all_allocation, allocate_all_allocation + allocate_all_allocation_size);
    infof(__func__, "\tstack end=%llX%llX\n",
          (uqword) (unit_stack.end() >> 64),
          (uqword) (unit_stack.end()));
    info(__func__, "deallocate_all() succeeded\n");
    info(__func__, "\n");

    info(__func__, "Attempting controlled failure condition:\n");
    // this should fail by allocating just 1 greater than the size of the heap
    register machine_workeld const should_fail_allocation_size = heap_size + 1;
    m_windows_stack_pointer should_fail_allocation = unit_stack.allocate_all(should_fail_allocation_size);
    // if the above doesn't fail, then something should happen here:
    unit_stack.deallocate_all(should_fail_allocation, should_fail_allocation + should_fail_allocation_size);

    info(__func__, "ImperfectUnitStackAllocator test complete\n");

    // final cleanup
    w32_stack_destroy();
}

#define kin enum
#define manyfold_fare struct
#define nameas typedef

kin FareKin {
    FIRST,
    OTHER,
    THIRD,
    FOURTH
};

typedef machine_workeld Fare;

static void test_faring(void) {
    // a way of being
    Fare fare;
    // a thing that holds one or more fares
    manyfold_fare Farer farer;
    // producer of farers
    Ferera farera;
    // supplier of fareras (and farers by extension)
    FareraFruma fareraFruma;
    // supplier of giving meanings, aka context object or qualifier
    Beyameanelda beyameanelda;

}

#pragma clang diagnostic pop

#pragma GCC diagnostic pop

#endif //PROJECT_AQUINAS_TESTS_H

#pragma clang diagnostic pop