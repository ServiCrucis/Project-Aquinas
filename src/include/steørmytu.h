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

void info(char const *restrict fn_name, char const *information, ...);

void infof(char const *restrict fn_name, char const *restrict information, ...);

void warnf(char const *restrict fn_name, char const *restrict warning, ...);

__attribute__((noreturn))
void fatalf(char const *restrict fn_name, char const *restrict error_message, ...);

#endif /* PROJECT_AQUINAS_DEBUG_H */
