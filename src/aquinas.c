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
// set memory unit to use dynamic allocations instead of a single static allocation
#define DYNAMIC_HEAP true

#include "state.h"
#include "tests.h"

void run_tests() {
    //test_expi();
    //test_lni();
    //test_log10i();
    //test_sigbits();
    //test_digits();
    //test_to_digits();
    //test_bittrie();
    //test_binary_trie();
    //test_map();
    //test_cpuid();
    test_dynarray();
}

int main(int argc, char **argv) {
    info(__func__, "Running.\n");
    
    run_tests();
    
    return R_SUCCESS;
}
