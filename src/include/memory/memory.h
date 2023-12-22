/*
 * Module: memory
 * File: memory.h
 * Created:
 * May 03, 2021
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2021 Christi Crucifixi, LLC. All rights reserved.
 *
 * License: See LICENSE.txt
 *
 * A robust and efficient BC memory model implementation.
 */


#ifndef PROJECT_AQUINAS_MEMORY_H
#define PROJECT_AQUINAS_MEMORY_H

#include "platform.h"
#include <stdalign.h>

// utility functions useful for manipulating memory

/*
 * Computes the index of an element from the given bit_index into an array of length array_length and which array
 * stores values of size storage_width.
 */
static inline uqword m_compute_element_index(uqword bit_index, uqword array_length, uqword storage_width) {
    // TODO implement and use udiv64
    return (bit_index / storage_width) * array_length;
}

/*
 * Computes the relative bit index of the given absolute bit_index within an array. That is, the offset
 * in bits, given an array of elements of size storage_width, a value in [0, storage_width - 1].
 */
static inline uqword m_compute_relative_bit_index(uqword bit_index, uqword storage_width) {
    return bit_index % storage_width;
}


#if PLATFORM == P_WINDOWS

// TODO include windows header here for win32 implementation

#elif PLATFORM == P_LINUX
#include "m_linux.h"
#elif PLATFORM == P_UNIX
#include "m_unix.h"
#elif PLATFORM == P_MACINTOSH
#include "m_macintosh.h"
#elif PLATFORM == P_BSD_ENVIRONMENT
#include "m_bsd.h"
#elif PLATFORM == P_ANDROID
#include "m_android.h"
#elif PLATFORM == P_GNU
#include "m_gnu.h"
#elif PLATFORM == P_CYGWIN
#include "m_cygwin.h"
#elif PLATFORM == P_MINGW
#include "m_mingw.h"
#elif PLATFORM == P_EMX
#include "m_emx.h"
#elif PLATFORM == P_INTERIX
#include "m_interix.h"
#elif PLATFORM == P_WINDU
#include "m_windu.h"
#else
#error [memory.h] Unrecognized platform
#endif

#endif //PROJECT_AQUINAS_MEMORY_H
