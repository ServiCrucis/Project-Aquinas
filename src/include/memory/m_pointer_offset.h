/*
 * Module: m_pointer_offset
 * File: m_pointer_offset.h
 * Created:
 * October 13, 2022
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 * License: See LICENSE.txt
 *
 * A stupidly simple pointer compression implementation that supports this incredibly
 * revolutionary new concept known as compressed pointers (pointer offsets) because
 * this has definitely never been thought of before and is of course used ubiquitously
 * to save every bit. /s
 */

#ifndef PROJECT_AQUINAS_M_POINTER_OFFSET_H
#define PROJECT_AQUINAS_M_POINTER_OFFSET_H

#include "platform.h"
typedef struct m_pointer_offset {

} pointer_offset;

typedef struct m_pointer_offset_tree {

} m_pointer_offset_tree;

pointer_offset m_pointer_cast(void *pointer);

pointer_offset m_pointer_split(ubyte bit_index, void *pointer);


/*
 *  Computes the optimal size of a pointer_offset data type in bits for the given
 *  number of elements that one wishes to index.
 */
uqword m_compute_optimal_offset_size(udqword elements);

/*
 * Computes the optimal required amount of space in bits for the given number
 * of elements that one wishes to index.
 */
uqword m_compute_optimal_required_space(udqword elements);

#endif //PROJECT_AQUINAS_M_POINTER_OFFSET_H
