/*
 ============================================================================
 Name        : aquinas.c
 Author      : Andrew Porter (AMDG)
 Version     : 1.0
 Copyright   : See LICENSE.txt
 Description : Project Aquinas Meta-compiler
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <platform.h>

// make other libraries use our memory manager (overwrites free as well)
#define MEMORY_MALLOC_OVERWRITE false
// enable debug message printing
#define R_DEBUG true

#include "state.h"
#include "tests.h"

void run_tests(void) {
//    test_expi();
//    test_lni();
//    test_log10i();
//    test_sigbits();
//    test_digits();
//    test_to_digits();
//    test_bittrie();
//    test_binary_trie();
//    test_map();
//    test_cpuid();
//    test_dynarray();
//    test_umap();
//    test_square_wave();
//    test_udiv();
//    test_umod();
//    test_fp_math();
//    test_data_byte_order();
//    test_w32_memory_allocator();
    test_m_pointer_offset();
}


int main(int argc, char **argv) {
    info(__func__, "Running\n");
    
    run_tests();
    
    return R_SUCCESS;
}

//// 0111 01
//// 0111 11 ->
////
//// if x == 0111: 1
//// else        : 0
//// then: (continue usual operation)
//
//// converts x into a standard binary path within a simpler tree structure
//// that compresses common data sequences into equivalence checks within a
//// difference tree.
//// tree_path_decode(x)
//
//
//[0110][1110]
//
//// binary transform (maps two arbitrary values to an order):
//0110 = floor(in * 2**(-N));
//1110 = floor(in * 2**(-N));
//
//// arbitrary order normalization: normalize x from order 2**(floor(lg(x))+1) to 2**m
//// bintree compression:
//// 1. determine order of values: lg of largest value in the set.
//// 2. determine order of number of values: lg of number of values in the set.
//// 3. create binary tree of binary transforms as described above.
//
//// binary_tree
//
//// 0: 2^0 nodes
//// 1: 2^1 nodes
//// 2: 2^2 nodes
//// N: 2^N nodes
