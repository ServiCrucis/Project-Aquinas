/*
* Module: tests
* File: tests.h
* Created:
* November 08, 2020
* Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
* License: See LICENSE.txt
*/

#ifndef PROJECT_AQUINAS_TESTS_H
#define PROJECT_AQUINAS_TESTS_H

#include <dynarray.h>
#include "state.h"
#include "compiler.h"
#include "bit_math.h"
#include "sigbits_map.h"
#include "memory.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

static void test_expi() {
    for (ubyte i = 0; i < 45; i++) {
        infof(__func__, "expi(%llu): %llu\n", i, expi(i));
    }
}

static void test_lni() {
    for (ubyte i = 0; i < 45; i++) {
        infof(__func__, "lni(%llu): %llu\n", expi(i), lni(expi(i)));
    }
}

static void test_log10i() {
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1ull, log10i(1ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10ull, log10i(10ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100ull, log10i(100ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000ull, log10i(1000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000ull, log10i(10000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000ull, log10i(100000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000ull, log10i(1000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000ull, log10i(10000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000ull, log10i(100000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000ull, log10i(1000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000ull, log10i(10000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000ull, log10i(100000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000ull, log10i(1000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000ull, log10i(10000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000ull, log10i(100000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000ull, log10i(1000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000ull, log10i(10000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000000ull, log10i(100000000000000000ul));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000000ull, log10i(1000000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000000ull, log10i(10000000000000000000ull));
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

//static void test_bittrie() {
//    info(__func__, "Building bit_trie.\n");
//    uqword_pair test[] = {
//            { 23,  1 },
//            { 237, 1 }
//    };
//    bit_trie    *trie  = btt_create(test, 8, 2);
//    uqword   values = 256;
//    // 0: left; 1: right
//    uqword   side   = 0ull;
//    info(__func__, "bit_trie side:left.\n");
//    for (uqword address = 0; address < values; address++) {
//
//        uqword bit = btt_read(trie, (address << 1u) | side);
//        infof(__func__, "[%u] = %u\n", bin_index((address << 1u) | side), bit);
//    }
//
//    info(__func__, "bit_trie side:right.\n");
//    side = 1ull;
//    for (uqword address = 0; address < values; address++) {
//        uqword bit = btt_read(trie, (address << 1u) | side);
//        infof(__func__, "[%u]\n", bin_index((address << 1u) | side), bit);
//    }
//
//    btt_free(trie);
//    info(__func__, "Done.\n");
//}

//static void test_binary_trie() {
//    binary_tree *btrie = binary_tree_create(31);
//
//    for (uqword i = 0; i < btrie->nodes; i++) {
//        binary_tree_set(btrie, i, powni(i, i));
//        infof(__func__, "binary_tree+%llu = %llu\n", i, binary_tree_get(btrie, i));
//    }
//}

static void test_map() {
    sigbits_map *map = sbm_create(bitwidth(ubyte));
    for (uqword i    = 0; i < 256; i++) {
        sbm_set(map, (uqword_pair) { i, rand() });
        infof(__func__, "map[%llu] = %llu\n", i, sbm_get(map, i) & 255);
    }
    // undefined behavior
    infof(__func__, "(undefined behavior test) map[257]: %llu\n", sbm_get(map, 257));
    
    //    for (ubyte i = 0; i < bitwidth(uqword); i++) {
    //        uqword value = map_get(map, i);
    //        infof(__func__, "map[%llu] : %u\n", i, value);
    //    }
    
    
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
    dynarray *array       = dynarray_create(32u);
    ubyte    test_data[4] = { 0x12, 0x34, 0xAB, 0xCD };
    // print dynarray
    info(__func__, "dynarray before filling:\n");
    for (uqword i = 0; i < 32u; i++) {
        infof(__func__, "dynarray[%u]: %#x\n", i, array->data[i]);
    }
    
    // fill dynarray
    dynarray_fill(array, (ubyte *) test_data, sizeof(test_data));
    
    // print dynarray
    info(__func__, "dynarray after filling:\n");
    for (uqword i = 0; i < 32u; i++) {
        infof(__func__, "dynarray[%u]: %#x\n", i, array->data[i]);
    }
    
    // test dynarray_get
    info(__func__, "test_get before dynarray_get(): \n");
    ubyte *test_get = calloc(32u, sizeof(*test_get));
    if (!test_get)
        fatalf(__func__, "failed to allocate memory for test_get\n");
    for (uqword i = 0; i < 32u; i++) {
        infof(__func__, "test_get[%u]: %#x\n", i, test_get[i]);
    }
    
    info(__func__, "dynarray_get():\n");
    dynarray_get(array, 0, 32u, test_get, 0, 32u);
    for (uqword i = 0; i < 32u; i++) {
        infof(__func__, "test_get[%u]: %#x\n", i, test_get[i]);
    }
    free(test_get);
    
    // test dynarray_set
    ubyte *test_set = calloc(32u, sizeof(*test_set));
    if (!test_set)
        fatalf(__func__, "failed to allocate memory for test_set\n");
    memset(test_set, 0x11, 32u);
    dynarray_set(array, 0, 32u, test_set, 0, 32u);
    for (uqword i = 0; i < 32u; i++) {
        infof(__func__, "dynarray[%u]: %#x\n", i, array->data[i]);
    }
    free(test_set);
    
    // test dynarray_resize
    // should resize to 16 bytes from 32 bytes
    array = dynarray_resize(array, 16u);
    info(__func__, "after dynarray_resize() from 32 to 16 bytes:\n");
    // undefined behavior; test results may vary
    for (uqword i = 0; i < 32u; i++) {
        infof(__func__, "dynarray[%u]: %#x\n", i, array->data[i]);
    }
    
    array = dynarray_resize(array, 64u);
    info(__func__, "after dynarray_resize() from 16 to 64 bytes:\n");
    // undefined behavior; test results may vary
    for (uqword i = 0; i < 64u; i++) {
        infof(__func__, "dynarray[%u]: %#x\n", i, array->data[i]);
    }
    
    free(array);
    
    info(__func__, "dynarray test completed\n");
}

static void test_umap() {
}

static void test_memory_allocator() {
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

static void test_data_order() {
    info(__func__, "Beginning data order (endianness) test");
}

static void test_pointer() {
    infof(__func__, "pointer size: %u\n", sizeof(pointer24));
    void   *test_ptr;
    test_ptr = (void *) 0xffffabcddcbaffff;
    
    if (!test_ptr)
        fatalf(__func__, "What is this, a microcontroller? Unable to allocate %u bytes.\n", sizeof(void *));
    
    infof(__func__, "test_ptr value: %p\n", test_ptr);
    volatile pointer test_ptr8  = ptr_compress(test_ptr, sizeof(pointer8));
    volatile pointer test_ptr16 = ptr_compress(test_ptr, sizeof(pointer16));
    volatile pointer test_ptr24 = ptr_compress(test_ptr, sizeof(pointer24));
    volatile pointer test_ptr32 = ptr_compress(test_ptr, sizeof(pointer32));
    volatile pointer test_ptr40 = ptr_compress(test_ptr, sizeof(pointer40));
    volatile pointer test_ptr48 = ptr_compress(test_ptr, sizeof(pointer48));
    volatile pointer test_ptr56 = ptr_compress(test_ptr, sizeof(pointer56));
    volatile pointer test_ptr64 = ptr_compress(test_ptr, sizeof(pointer64));
    
    info(__func__, "as pointer8: %p\n", (void *)(ubyte) test_ptr8.offset);
    info(__func__, "as pointer16: %p\n", (void *)(uword) test_ptr16.offset);
    info(__func__, "as pointer24: %p\n", (void *)(udword) test_ptr24.offset);
    info(__func__, "as pointer32: %p\n", (void *)(udword) test_ptr32.offset);
    info(__func__, "as pointer40: %p\n", (void *)(uqword) test_ptr40.offset);
    info(__func__, "as pointer48: %p\n", (void *)(uqword) test_ptr48.offset);
    info(__func__, "as pointer56: %p\n", (void *)(uqword) test_ptr56.offset);
    info(__func__, "as pointer64: %p\n", (void *)(uqword) test_ptr64.offset);
    
    info(__func__, "pointer back to void *: %p\n", ptr_decompress(test_ptr8));
    info(__func__, "pointer back to void *: %p\n", ptr_decompress(test_ptr16));
    info(__func__, "pointer back to void *: %p\n", ptr_decompress(test_ptr24));
    info(__func__, "pointer back to void *: %p\n", ptr_decompress(test_ptr32));
    info(__func__, "pointer back to void *: %p\n", ptr_decompress(test_ptr40));
    info(__func__, "pointer back to void *: %p\n", ptr_decompress(test_ptr48));
    info(__func__, "pointer back to void *: %p\n", ptr_decompress(test_ptr56));
    info(__func__, "pointer back to void *: %p\n", ptr_decompress(test_ptr64));
    
}

#pragma GCC diagnostic pop

#endif //PROJECT_AQUINAS_TESTS_H
