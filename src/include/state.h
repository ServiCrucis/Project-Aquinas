/*
 * # modulus.h
 * ## Created:
 * August 19th, A.D. 2019
 * ## Author:
 * Andrew Thomas Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2019 Christi Crucifixi, LLC. All rights reserved.
 */
#ifndef PROJECT_AQUINAS_DEBUG_H
#define PROJECT_AQUINAS_DEBUG_H

#include <stdlib.h>
#include <stdbool.h>
#include <platform.h>

// a macro to be used by programs to determine whether or not the build is debug (default: false
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

void info(char const *restrict fn_name, char const *information, ...);

void infof(char const *restrict fn_name, char const *restrict information, ...);

void warnf(char const *restrict fn_name, char const *restrict warning, ...);

__attribute__((noreturn))
void fatalf(char const *restrict fn_name, char const *restrict error_message, ...);

#endif /* PROJECT_AQUINAS_DEBUG_H */
