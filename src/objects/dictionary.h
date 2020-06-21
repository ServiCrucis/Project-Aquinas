/*
 * Module: dictionary
 * File: dictionary.h
 * Created:
 * June 13, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef PROJECT_AQUINAS_DICTIONARY_H
#define PROJECT_AQUINAS_DICTIONARY_H

#include <platform.h>
#include "binary_trie.h"

typedef struct dictionary {
	binary_trie *trie;
} dictionary;

#endif //PROJECT_AQUINAS_DICTIONARY_H
