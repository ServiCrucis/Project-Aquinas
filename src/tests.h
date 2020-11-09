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

#include "state.h"
#include "compiler.h"
#include "bit_math.h"
#include "bit_trie.h"
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
    for (uword i = 0; i < 256; i++) {
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
    uword      value = UINT64_MAX;
    ubyte      digits[20];
    for (ubyte i     = 19; i < 20; i--) {
        digits[i] = (ubyte) get_digit10i(value, i);
        infof(__func__, "digit[%llu] = %llu\n", i, digits[i]);
    }
}

static void test_bittrie() {
    info(__func__, "Building bit_trie.\n");
    pair     test[] = {
            { 23,  1 },
            { 237, 1 }
    };
    bit_trie *trie  = btt_create(test, 8, 2);
    uword    values = 256;
    // 0: left; 1: right
    uword    side   = 0ull;
    info(__func__, "bit_trie side:left.\n");
    for (uword address = 0; address < values; address++) {
        
        uword bit = btt_read(trie, (address << 1u) | side);
        infof(__func__, "[%u] = %u\n", bin_index((address << 1u) | side), bit);
    }
    
    info(__func__, "bit_trie side:right.\n");
    side = 1ull;
    for (uword address = 0; address < values; address++) {
        uword bit = btt_read(trie, (address << 1u) | side);
        infof(__func__, "[%u]\n", bin_index((address << 1u) | side), bit);
    }
    
    btt_free(trie);
    info(__func__, "Done.\n");
}

static void test_binary_trie() {
    binary_tree *btrie = binary_tree_create(31);
    
    for (uword i = 0; i < btrie->nodes; i++) {
        binary_tree_set(btrie, i, powni(i, i));
        infof(__func__, "binary_tree+%llu = %llu\n", i, binary_tree_get(btrie, i));
    }
}

static void test_map() {
    sigbits_map *map = sbm_create(bitwidth(ubyte));
    for (uword  i    = 0; i < 256; i++) {
        sbm_set(map, (pair) { i, rand() });
        infof(__func__, "map[%llu] = %llu\n", i, sbm_get(map, i) & 255);
    }
    // undefined behavior
    infof(__func__, "(undefined behavior test) map[257]: %llu\n", sbm_get(map, 257));
    
    //    for (ubyte i = 0; i < bitwidth(uword); i++) {
    //        uword value = map_get(map, i);
    //        infof(__func__, "map[%llu] : %u\n", i, value);
    //    }
    
    
}

static void test_cpuid() {
    if (!__x86_cpuid_supported())
        fatalf(__func__, "Unable to initialize CPU info: CPUID instruction not supported");
    info(__func__, "CPUID is supported on this platform\n");
}

#pragma GCC diagnostic pop

#endif //PROJECT_AQUINAS_TESTS_H
