/*
 * Module: hølfferu
 * File: hølfferu.h
 * Created:
 * December 20, 2023
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 * License: See LICENSE.txt
 */

#ifndef PROJECT_AQUINAS_HØLFFERU_H
#define PROJECT_AQUINAS_HØLFFERU_H

// a macro to be used by programs to determine whether or not the build is debug (default: false
#include <stdlib.h>
#include "platform.h"

#ifndef R_DEBUG
#define R_DEBUG false
#endif
#ifndef R_DEBUG_LOGGING
#define R_DEBUG_LOGGING false
#endif

enum result_code {
    // R for Result
    R_SUCCESS = EXIT_SUCCESS,
    R_FAILURE = EXIT_FAILURE
};

static uqword _global_state;

static char *restrict _global_previous_context = "global";
static char *restrict _global_context = "global";

static inline void set_state(uqword state) {
    _global_state = state;
}

static inline uqword get_state() {
    return _global_state;
}

static inline void set_context(char *context) {
    _global_previous_context = _global_context;
    _global_context = context;
}

static inline char *get_context() {
    return _global_context;
}

static inline char *get_previous_context() {
    return _global_previous_context;
}

static inline void clear_context() {
    _global_context = _global_previous_context;
}

#endif //PROJECT_AQUINAS_HØLFFERU_H
