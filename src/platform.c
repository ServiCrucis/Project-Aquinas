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

	#include <libloaderapi.h>

#elif PLATFORM == LINUX || ENVIRONMENT == UNIX

	#include <unistd.h>

#endif

#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "macro.h"
#include "platform.h"

struct p_result p_get_platform() {
	struct p_result result = *((struct p_result *) m_get(sizeof(struct p_result)));
	result.content.value = PLATFORM_NAME;
	result.code = R_INITIALIZATION_SUCCESS;
	return result;
}

/*
 * Returns a copy of a system environment variable string value. There is no obligation to copy the returned string.
 * You must use m_free for the string.
 */
struct p_result p_get_env(char *var) {
#ifdef __STDC_HOSTED__ // check if standard C is defined on this platform
	char *env = getenv(var);
	size_t len = strlen(env);
	char *result = m_get(len);
	struct p_result ret = *((struct p_result *) m_get(sizeof(struct p_result)));
	strcpy(env, result);
	return ret;
#else
#error "[fatal][p_get_env] p_get_env is not defined on this platform."
#endif
}

struct p_result p_get_fn(char *module, char *function) {
	struct p_result result = *((struct p_result *) m_get(sizeof(struct p_result)));
#if PLATFORM == WINDOWS || ENVIRONMENT == WINDOWS
	result.content.function = (void (*)(void)) GetProcAddress(LoadLibrary(module), function);
#elif PLATFORM == LINUX || ENVIRONMENT == UNIX

#endif
}

struct p_result p_get_fna(char *module, uintptr_t function_offset) {

}
