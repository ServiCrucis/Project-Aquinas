/*
 * # platform.c
 * ## Created:
 * November 8th, A.D. 2019
 * ## Author:
 * Andrew Thomas Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2019 Christi Crucifixi, LLC. All rights reserved.
 */
#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS

	#include <windows.h>

#elif PLATFORM == LINUX || ENVIRONMENT == UNIX

	#include <unistd.h>

#endif

#include <stdlib.h>
#include <string.h>
#include "memory/memory.h"
#include "platform.h"

char *p_get_platform() {
	return PLATFORM_NAME;
}

/*
 * Returns a copy of a system environment variable string value. There is no obligation to copy the returned string.
 * You must use m_free for the string.
 */
char *p_get_env(char *var) {
#ifdef __STDC_HOSTED__ // check if standard C is defined on this platform
	char   *env    = getenv(var);
	size_t len     = strlen(env);
	char   *result = malloc(len);
	strcpy(env, result);
	return result;
#else
	#error "[build][fatal][p_get_env] p_get_env is not defined on this platform."
#endif
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-m_context-types"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
void *(*p_get_fn(char *module, char *function))() {
#if PLATFORM == P_WINDOWS || ENVIRONMENT == P_WINDOWS
	return (void *(*)()) GetProcAddress(LoadLibrary(module), function);
#elif PLATFORM == LINUX || ENVIRONMENT == UNIX
	// TODO UNIX p_get_fn
#else
	#error "[build][fatal][p_get_fn] platform not yet supported"
#endif
}
#pragma clang diagnostic pop
#pragma GCC diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-m_context-types"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
void *(*p_get_fn_offset(char *module, uintptr_t function_offset))() {
#if PLATFORM == P_WINDOWS || ENVIRONMENT == P_WINDOWS
	return (void *(*)()) (LoadLibrary(module) + function_offset);
#elif PLATFORM == P_LINUX || ENVIRONMENT == P_UNIX
	// TODO UNIX p_get_fn_offset
#else
	#error "[build][fatal][p_get_fn_offset] platform not yet supported"
#endif
}
#pragma clang diagnostic pop
#pragma GCC diagnostic pop
