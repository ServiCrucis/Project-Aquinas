/*
 ============================================================================
 Name        : Modulus.c
 Author      : Andrew Thomas Porter (AMDG)
 Version     : 1.2.1
 Copyright   : See LICENSE.txt
 Description : Modulus language compiler
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

int main(int argc, char **argv) {
	r_debug_info("Running...\n");
	// 128KiB heap
	m_heap_create(128 * 1024, 128 * 1024);
	return 0;
}
