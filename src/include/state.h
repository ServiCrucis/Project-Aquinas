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

static uword _global_state;

static inline void set_state(uword state) {
    _global_state = state;
}

static inline uword get_state() {
    return _global_state;
}

void info(char const *information, ...);

void infof(enum result_code const code, char const *restrict state, char const *restrict fn_name, char const *restrict information, ...);

void warnf(enum result_code const code, char const *restrict state, char const *restrict fn_name, char const *restrict warning, ...);

void fatalf(char const *restrict state, char const *restrict fn_name, char const *restrict error_message, ...);

#endif /* PROJECT_AQUINAS_DEBUG_H */
