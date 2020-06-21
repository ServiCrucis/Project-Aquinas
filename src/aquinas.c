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

// make other libraries use our memory manager (overwrites free as well)
#define MEMORY_MALLOC_OVERWRITE false
// enable debug message printing
#define R_DEBUG true
// set memory unit to use dynamic allocations instead of a single static allocation
#define DYNAMIC_HEAP true

#include "platform.h"
#include "compiler.h"
#include "bit_math.h"
#include "bit_trie.h"

static void test_bittrie() {
	r_info("Building bit_trie.\n");
	pair    test[] = {
			{ 23,1 },
			{ 237,1 }
	};
	bit_trie *trie   = btt_create(test, 8, 2);
	uword values = 256;
	// 0: left; 1: right
	uword side = 0ull;
	r_info("bit_trie side:left.\n");
	for(uword address = 0; address < values; address++) {
		
		uword bit = btt_read(trie, (address << 1u) | side);
		r_infof(R_STATUS, __func__, "[%u] = %u\n", bin_index((address << 1u) | side), bit);
	}
	
	r_info("bit_trie side:right.\n");
	side = 1ull;
	for(uword address = 0; address < values; address++) {
		uword bit = btt_read(trie, (address << 1u) | side);
		r_infof(R_STATUS, __func__, "[%u]\n", bin_index((address << 1u) | side), bit);
	}
	
	btt_free(trie);
	r_info("Done.\n");
}

static void test_digits() {
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 1ull, digits(1ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 10ull, digits(10ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 100ull, digits(100ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 1000ull, digits(1000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 10000ull, digits(10000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 100000ull, digits(100000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 1000000ull, digits(1000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 10000000ull, digits(10000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 100000000ull, digits(100000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 1000000000ull, digits(1000000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 10000000000ull, digits(10000000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 100000000000ull, digits(100000000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000ull, digits(1000000000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000ull, digits(10000000000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000ull, digits(100000000000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000ull, digits(1000000000000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000ull, digits(10000000000000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000000ull, digits(100000000000000000ul));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000000ull, digits(1000000000000000000ull));
	r_infof(R_STATUS, __func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000000ull, digits(10000000000000000000ull));
}

static void test_binary_trie() {
	binary_trie *btrie;
}

static void test_sort() {

}

//static inline void swap(uword indexA, uword indexB, uword *set) {
//	uword b = set[indexB];
//	set[indexB] = set[indexA];
//	set[indexA] = b;
//}

static void test_binsearch() {
	// generate set
	uword size = 1000;
	uword *set = malloc(sizeof(uword) * size);
	
	for (uword i = 0; i < 1000; i++) {
		uword v = (((uword) rand()) << 31) | (uword) rand();
		set[i] = v;
		r_infof(R_STATUS, __func__, "set[%u] = %llu\n", i, v);
	}
	
//	// sort the values
//	// heap sort
//	// heapify
//	// pair: a=index; b=value;
//	pair smallest = {0, bitmask(0)};
//	pair largest = { 0, 0 };
//	for (uword i = 0; i < size; i++) {
//		uword value = set[i];
//		smallest = smallest.b <= value ? smallest : (pair){i, value};
//		largest = largest.b >= value ? largest : (pair){i, value};
//	}
//	// set 0 and size - 1 to smallest and largest respectively
//	swap(0, smallest.a, set);
//	swap(size - 1, largest.a, set);

	
	uword index = rand();
	index = (index * 1000) / (bitmaskv(index, sigbits(index) + 1));
	uword value = set[index];
	uword result = binsearch(value, set, 1000);
	r_infof(R_STATUS, __func__, "Search result: set[%u]=%llu; actual value: set[%u]=%llu", result, set[result], index, value);
}

int main(int argc, char **argv) {
	r_info("Running.\n");
	//test_bittrie();
	//test_digits();
	//test_sort();
	//test_binsearch();
	//test_dynhashtrie();
	return R_SUCCESS;
}
