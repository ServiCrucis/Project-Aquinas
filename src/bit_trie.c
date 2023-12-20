/*
 * Module: bit_trie
 * File: bit_trie.c
 * Created:
 * April 21, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#include <stdlib.h>

#include "bit_trie.h"
#include "bit_math.h"
#include "state.h"

uqword btt_read(bit_trie *trie, uqword address) {
    return get_bita(trie->binodes, (2u << trie->depth) / BITS, bin_index(address));
}

void btt_write(bit_trie *trie, uqword address, uqword bit) {
    set_bita(trie->binodes, (2u << trie->depth) / BITS, bin_index(address), bit);
}

bit_trie *btt_create(uqword_pair const *pairs, uqword depth, uqword length) {
    bit_trie *result = malloc(sizeof(bit_trie));
    
    if (!result) {
        fatalf(__func__, "failed to allocate state for binary_trie");
    }
    
    result->binodes = calloc((2u << depth) / BITS, sizeof(uqword));
    result->depth   = depth;
    
    if (!result->binodes) {
        fatalf(__func__, "failed to allocate state for binary_trie binodes");
    }
    
    for (uqword i = 0; i < length; i++) {
        uqword_pair pair = pairs[i];
        btt_write(result, pair.a, pair.b);
    }
    
    return result;
}

void btt_free(bit_trie *trie) {
    free(trie->binodes);
    free(trie);
}
