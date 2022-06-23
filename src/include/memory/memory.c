/*
 * Module: memory
 * File: memory.c
 * Created:
 * May 03, 2021
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2021 Christi Crucifixi, LLC. All rights reserved.
 *
 * License: See LICENSE.txt
 */

#include <malloc.h>
#include "state.h"
#include "bit_math.h"
#include "memory.h"
#include "platform.h"

#if PLATFORM == P_WINDOWS
  #include "m_windows.h"
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
  #error [memory.c] Unrecognized platform
#endif
