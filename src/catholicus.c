/*
 ============================================================================
 Name        : Modulus.c
 Author      : Andrew Thomas Porter (AMDG)
 Version     : 1.2.1
 Copyright   : See LICENSE.txt
 Description : Catholicus language compiler
 ============================================================================
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// make other libraries use our memory manager (overwrites free as well)
#define MEMORY_MALLOC_OVERWRITE true
// enable debug message printing
#define R_DEBUG true
// set memory unit to use dynamic allocations instead of a single static allocation
#define DYNAMIC_HEAP true
#include "memory.h"
#include "error.h"
#include "compiler.h"
#include "math.h"


static void printtrie(binary_trie trie) {

}

int main(int argc, char **argv) {
	r_info("Running.\n");
	r_info("Building binary_trie.\n");
	binary_trie trie;
	trie.binodes = NULL;
	printtrie(trie);
	return 0;
}
