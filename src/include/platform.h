/*
 * file: platform.h
 * origin: platform.h
 * author: Andrew Thomas Porter <caritasdedeus@gmail.com>
 * description:
 */

#ifndef PROJECT_AQUINAS_INCLUDE_P_H
#define PROJECT_AQUINAS_INCLUDE_P_H

#include <stddef.h>
#include <limits.h>
#include <stdint.h>

/*
 * VARIABLES:
 *
 * ENVIRONMENT: the value representing the current environment which is the name of a wrapper API such as Cygwin, MinGW,
 * ENVIRONMENT_NAME
 * ENVIRONMENT_NAME_LENGTH
 * ENVIRONMENT_NAME_LENGTH_MAX
 * ENVIRONMENT_VARIANT
 *
 * PLATFORM
 * PLATFORM_NAME
 * PLATFORM_NAME_LENGTH
 * PLATFORM_NAME_LENGTH_MAX
 * PLATFORM_VARIANT
 *
 * ARCH
 * ARCH_NAME
 * ARCH_NAME_LENGTH
 * ARCH_NAME_LENGTH_MAX
 * ARCH_VARIANT
 *
 * DATA_MODEL
 * DATA_MODEL_NAME
 * DATA_MODEL_NAME_LENGTH
 * DATA_MODEL_NAME_LENGTH_MAX
 * DATA_MODEL_VARIANT
 *
 */
/* platforms */
#define P_WINDOWS         1
#define P_LINUX           2
#define P_UNIX            3
#define P_MACINTOSH       4
#define P_BSD_ENVIRONMENT 5
#define P_ANDROID         6
#define P_GNU             7
#define P_CYGWIN          8
#define P_MINGW           9
#define P_EMX          10
#define P_INTERIX        11
#define P_WINDU          12

/* platform variants */
/* WINDOWS */
#define P_WINDOWS_CE              13
#define P_WINDOWS_HPC2000         14
#define P_WINDOWS_HPCPRO          15
#define P_WINDOWS_POCKETPC        16
#define P_WINDOWS_MOBILE_2003     17
#define P_WINDOWS_SMARTPHONE_2002 18
/* LINUX */
#define P_SOLARIS  19
#define P_GNULINUX 20
#define P_MINIX    21
/* UNIX */
#define P_DRAGONFLY   22
#define P_HPUX        23
#define P_UNIXWARE    24
#define P_LYNX        25
#define P_DGUX_SYSTEM 26
#define P_SINUX       27
#define P_ULTRIX      28
#define P_DYNIX       29


/* other platforms */
#define P_AIX            30
#define P_OS400          31
#define P_FREEBSD        32
#define P_NETBSD         33
#define P_OPENBSD        34
#define P_BSDI           35
#define P_KFREEBSD       36
#define P_OS9            37
#define P_BEOS           38
#define P_AMIGAOS        39
#define P_MORPH          40
#define P_AEGIS          41
#define P_BLUE_GENE      42
#define P_AMDAHL_UTS     43
#define P_CONVEX         44
#define P_ECOS           45
#define P_HIUXMPP        46
#define P_INTEGRITY      47
#define P_MPE            48
#define P_MSDOS_SYSTEM   49
#define P_NONSTOP        50
#define P_NUCLEUS        51
#define P_OS2_SYSTEM     52
#define P_PALMOS         53
#define P_ZOS            54
#define P_PLAN9          55
#define P_PYRAMIDDC      56
#define P_QNX            57
#define P_SCO_OPENSERVER 58
#define P_STRATUS_VOS    59
#define P_SVR4           60
#define P_SYLLABLE       61
#define P_SYMBIAN        62
#define P_TRU64          63
#define P_UNICOS         64
#define P_VMS_SYSTEM     65
#define P_VXWORKS        66
#define P_UNKNOWN        67

// based on 0.1% percentile of qword length distribution for English (16 * 4 = 64 characters)
// source: <http://www.ravi.io/language-word-lengths>
#define PLATFORM_NAME_LENGTH_MAX 64
#define ENVIRONMENT_NAME_LENGTH_MAX 64
#define ARCH_NAME_LENGTH_MAX 64


/******************************************PLATFORMS******************************************/


/* Windows */

#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define PLATFORM P_WINDOWS
#define PLATFORM_VARIANT P_WINDOWS
#define PLATFORM_NAME "Windows"

#endif

#if defined(_WIN32_WCE)
#define PLATFORM P_WINDOWS
#define PLATFORM_VARIANT P_WINDOWS_CE
#define PLATFORM_NAME "Windows CE"
#define PLATFORM_NAME_LENGTH sizeof(PLATFORM_NAME)
#endif

#if defined(WIN32_P_HPC2000)
#define PLATFORM P_WINDOWS
#define PLATFORM_VARIANT P_WINDOWS_HPC2000
#define PLATFORM_NAME "Windows HPC 2000"
#endif

#if defined(WIN32_P_HPCPRO)
#define PLATFORM P_WINDOWS
#define PLATFORM_VARIANT P_WINDOWS_HPCPRO
#define PLATFORM_NAME "Windows HPC Pro"
#endif

#if defined(WIN32_P_PSPC)
#define PLATFORM WINDOWS
#if WIN32_P_PSPC < 400
#define PLATFORM_VARIANT P_WINDOWS_POCKETPC
#define PLATFORM_NAME "Windows PocketPC"
#else
#define PLATFORM_VARIANT P_WINDOWS_MOBILE_2003
#define PLATFORM_NAME "Windows Mobile 2003"
#endif
#endif

#if defined(WIN32_P_WFSP)
#define PLATFORM P_WINDOWS
#define PLATFORM_VARIANT P_WINDOWS_SMARTPHONE_2002
#define PLATFORM_NAME "Windows Smartphone 2002"
#endif

/* LINUX */

#if defined(__linux__) || defined(linux) || defined(__linux)
#define ENVIRONMENT P_UNIX
#define PLATFORM P_LINUX
#define PLATFORM_VARIANT P_LINUX
#define PLATFORM_NAME "Linux"
#endif

#if defined(__gnu_linux__)
#define ENVIRONMENT P_UNIX
#define PLATFORM P_LINUX
#define PLATFORM_VARIANT P_GNULINUX
#define PLATFORM_NAME "GNU Linux"
#endif

#if defined(__minix)
#define ENVIRONMENT P_UNIX
#define PLATFORM P_LINUX
#define PLATFORM_VARIANT P_MINIX
#define PLATFORM_NAME "Minix"
#endif

/* UNIX */

#if defined(__unix__) || defined(__unix)
#if !(PLATFORM == P_CYGWIN) && !(PLATFORM == P_MINGW)
#define PLATFORM P_UNIX
#define PLATFORM_VARIANT P_UNIX
#ifndef PLATFORM_NAME
#define PLATFORM_NAME "Unix"
#endif
#endif
#endif

/* UNIX-derivative (newest to oldest release descending) */

/* DragonFly */
#if defined(__DragonFly__)
#define PLATFORM P_UNIX
#define PLATFORM_VARIANT P_DRAGONFLY
#define PLATFORM_NAME "DragonFly"
#endif

/* HPUX */
#if defined(_hpux) || defined(hpux) || defined(__hpux)
#define PLATFORM P_UNIX
#define PLATFORM_VARIANT P_HPUX
#define PLATFORM_NAME "HP-UX"
#endif

/* UnixWare */
#if defined(sco) || defined(_UNIXWARE7)
#define PLATFORM P_UNIX
#define PLATFORM_VARIANT P_UNIXWARE
#define PLATFORM_NAME "UnixWare"
#endif

/* LynxOS */
#if defined(__Lynx__)
#define PLATFORM P_UNIX
#define PLATFORM_VARIANT P_LYNX
#define PLATFORM_NAME "Lynx"
#endif

/* DG/UX */
#if defined(DGUX) || defined(__DGUX__) || defined(__dgux__)
#define PLATFORM P_UNIX
#define PLATFORM_VARIANT P_DGUX_SYSTEM
#define PLATFORM_NAME "DG/UX"
#endif

/* Reliant UNIX */
#if defined(sinux)
#define PLATFORM P_UNIX
#define PLATFORM_VARIANT P_SINUX
#define PLATFORM_NAME "Reliant UNIX"
#endif

/* Ultrix */
#if defined(ultrix) || defined(__ultrix) || defined(__ultrix__) || (defined(unix) && defined(vax))
#define PLATFORM P_UNIX
#define PLATFORM_VARIANT P_ULTRIX
#define PLATFORM_NAME "Ultrix"
#endif

/* DYNIX */
#if defined(_SEQUENT_) || defined(sequent)
#define PLATFORM P_UNIX
#define PLATFORM_VARIANT P_DYNIX
#define PLATFORM_NAME "DYNIX/ptx"
#endif

/* AIX */

#if defined(_AIX) || defined(__TOS_AIX__)
#define PLATFORM P_AIX
#define PLATFORM_VARIANT P_AIX
#define PLATFORM_NAME "AIX"
#endif

/* APPLE MACINTOSH/MAC OS X */

#if defined(macintosh) || defined(Macintosh)
#define PLATFORM P_MACINTOSH
#define PLATFORM_VARIANT P_MACINTOSH
#define PLATFORM_NAME "Macintosh"
#endif

#if defined(__APPLE__) && defined(__MACH__)
#define PLATFORM P_MACINTOSH
#define PLATFORM_VARIANT P_MACOSX
#define PLATFORM_NAME "Mac OS/X"
#endif

/* IBM OS/400 */

#if defined(__OS400__)
#define PLATFORM P_OS400
#define PLATFORM_VARIANT P_OS400
#define PLATFORM_NAME "IBM OS/400"
#endif

/* BSD */

#if defined(__FreeBSD__)
#define PLATFORM P_BSD_ENVRIONMENT
#define PLATFORM_VARIANT P_FREEBSD
#define PLATFORM_NAME "FreeBSD"
#endif

#if defined(__NetBSD__)
#define PLATFORM P_BSD_ENVIRONMENT
#define PLATFORM_VARIANT P_NETBSD
#define PLATFORM_NAME "NetBSD"
#endif

#if defined(__OpenBSD__)
#define PLATFORM P_BSD_ENVIRONMENT
#define PLATFORM_VARIANT P_OPENBSD
#define PLATFORM_NAME "OpenBSD"
#endif

#if defined(__bsdi__)
#define PLATFORM P_BSD_ENVIRONMENT
#define PLATFORM_VARIANT P_BSDI
#define PLATFORM_NAME "BSDi"
#endif

#if defined(BSD)
#define PLATFORM P_BSD_ENVIRONMENT
#define PLATFORM_NAME "BSD"
#endif

#if defined(_SYSTYPE_BSD)
#define PLATFORM P_BSD_ENVIRONMENT
#define PLATFORM_VARIANT P_BSD
#define PLATFORM_NAME "BSD"
#endif

#if defined(__FreeBSD_kernel__) && defined(__GLIBC__)
#define PLATFORM P_BSD_ENVIRONMENT
#define PLATFORM_VARIANT P_KFREEBSD
#define PLATFORM_NAME "KFreeBSD"
#endif

/* Android */

#if defined(__ANDROID__)
#define PLATFORM P_ANDROID
#define PLATFORM_VARIANT P_ANDROID
#define PLATFORM_NAME "Android"
#endif

/* Solaris */

#if defined(sun) || defined(__sun)
#define ENVIRONMENT P_UNIX
#define PLATFORM P_LINUX
#define PLATFORM_VARIANT P_SOLARIS
#define PLATFORM_NAME "Oracle Solaris"
#endif

/* GNU */

#if defined(__GNU__) || defined(__gnu_hurd__)
#define PLATFORM P_GNU
#define PLATFORM_VARIANT P_GNU
#define PLATFORM_NAME "GNU"
#endif

/* OS-9 */

#if defined(__OS9000) || defined(_OSK)
#define PLATFORM P_OS9
#define PLATFORM_VARIANT P_OS9
#define PLATFORM_NAME "Microware OS-9"
#endif

/* BeOS  */

#if defined(__BEOS__)
#define PLATFORM P_BEOS
#define PLATFORM_VARIANT P_BEOS
#define PLATFORM_NAME "BeOS"
#endif

/* AmigaOS */

#if defined(AMIGA) || defined(__amigaos__)
#define PLATFORM P_AMIGAOS
#define PLATFORM_VARIANT P_AMIGAOS
#define PLATFORM_NAME "AmigaOS"
#endif

/* MorphOS */

#if defined(__MORPHOS__)
#define PLATFORM P_MORPH
#define PLATFORM_VARIANT P_MORPH
#define PLATFORM_NAME "MorphOS"
#endif

/* Aegis */

#if defined(aegis)
#define PLATFORM P_AEGIS
#define PLATFORM_VARIANT P_AEGIS
#define PLATFORM_NAME "Apollo AEGIS"
#endif

/* Blue Gene */

#if defined(__bg__) || defined(__THW_BLUEGENE__)
#define PLATFORM P_BLUE_GENE
#define PLATFORM_VARIANT P_BLUE_GENE
#define PLATFORM_NAME "Blue Gene"
#endif

/* Amdahl UTS */

#if defined(UTS)
#define PLATFORM P_UTS
#define PLATFORM_VARIANT P_AMDAHL_UTS
#define PLATFORM_NAME "Amdahl UTS"
#endif

/* Convex */

#if defined(__convex__)
#define PLATFORM P_CONVEX
#define PLATFORM_VARIANT P_CONVEX
#define PLATFORM_NAME "ConvexOS"
#endif

/* eCos */

#if defined(__ECOS)
#define PLATFORM P_ECOS
#define PLATFORM_VARIANT P_ECOS
#define PLATFORM_NAME "eCos"
#endif

/* OSF/1 AD */

#if defined(__hiuxmpp)
#define PLATFORM P_HIUXMPP
#define PLATFORM_VARIANT P_HIUXMPP
#define PLATFORM_NAME "HI-UX MPP"
#endif

/* INTEGRITY */

#if defined(__INTEGRITY)
#define PLATFORM P_INTEGRITY
#define PLATFORM_VARIANT P_INTEGRITY
#define PLATFORM_NAME "INTEGRITY"
#endif

/* MPE */

#if defined(mpeix) || defined(__mpexl)
#define PLATFORM P_MPE
#define PLATFORM_VARIANT P_MPE
#define PLATFORM_NAME "MPE/iX"
#endif

/* MSDOS */

#if defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
#define PLATFORM P_MSDOS_SYSTEM
#define PLATFORM_VARIANT P_MSDOS_SYSTEM
#define PLATFORM_NAME "MSDOS"
#endif

/* NonStop */

#if defined(__TANDEM)
#define PLATFORM P_NONSTOP
#define PLATFORM_VARIANT P_NONSTOP
#define PLATFORM_NAME "NonStop"
#endif

/* Nucleus RTOS */

#if defined(__nucleus__)
#define PLATFORM P_NUCLEUS
#define PLATFORM_VARIANT P_NUCLEUS
#define PLATFORM_NAME "Nucleus RTOS"
#endif

/* OS/2 */

#if defined(OS2) || defined(_OS2) || defined(__OS2__) || defined(__TOS_OS2__)
#define PLATFORM P_OS2_SYSTEM
#define PLATFORM_VARIANT P_OS2_SYSTEM
#define PLATFORM_NAME "OS/2"
#endif

/* PalmOS */

#if defined(__palmos__)
#define PLATFORM P_PALMOS
#define PLATFORM_VARIANT P_PALMOS
#define PLATFORM_NAME "PalmOS"
#endif

/* z/OS */

#if defined(__MVS__) || defined(__HOS_MVS__) || defined(__TOS_MVS__)
#define PLATFORM P_ZOS
#define PLATFORM_VARIANT P_ZOS
#define PLATFORM_NAME "z/OS"
#endif

/* Plan 9 */

#if defined(EPLAN9)
#define PLATFORM P_PLAN9
#define PLATFORM_VARIANT P_PLAN9
#define PLATFORM_NAME "Plan 9"
#endif

/* Pyramid DC/OSx */

#if defined(pyr)
#define PLATFORM P_PYRAMIDDC
#define PLATFORM_VARIANT P_PYRAMIDDC
#define PLATFORM_NAME "Pyramid DC/OSx"
#endif

/* QNX */

#if defined(__QNX__) || defined(__QNXNTO__)
#define PLATFORM P_QNX
#define PLATFORM_VARIANT P_QNX
#define PLATFORM_NAME "QNX"
#endif
/* SCO OpenServer */

#if defined(M_I386) || defined(M_XENIX) || defined(_SCO_DS)
#define PLATFORM P_SCO_OPENSERVER
#define PLATFORM_VARIANT P_SCO_OPENSERVER
#define PLATFORM_NAME "SCO OpenServer"
#endif

/* Stratus VOS */

#if defined(__VOS__)
#define PLATFORM P_STRATUS_VOS
#define PLATFORM_VARIANT P_STRATUS_VOS
#define PLATFORM_NAME "Stratus VOS"
#endif

/* SVR4 */

#if defined(__sysv__) || defined(__SVR4) || defined(__svr4__) || defined(_SYSTYPE_SVR4)
#define PLATFORM P_SVR4
#define PLATFORM_VARIANT P_SVR4
#define PLATFORM_NAME "SVR4"
#endif

/* Syllable */

#if defined(__SYLLABLE__)
#define PLATFORM P_SYLLABLE
#define PLATFORM_VARIANT P_SYLLABLE
#define PLATFORM_NAME "Syllable"
#endif

/* Symbian OS */

#if defined(__SYMBIAN32__)
#define PLATFORM P_SYMBIAN
#define PLATFORM_VARIANT P_SYMBIAN
#define PLATFORM_NAME "Symbian OS"
#endif

/* Tru64 (OSF/1) */

#if defined(__osf__) || defined(__osf)
#define PLATFORM P_TRU64
#define PLATFORM_VARIANT P_TRU64
#define PLATFORM_NAME "Tru64 (OSF/1)"
#endif

/* UNICOS */

#if defined(_UNICOS)
#define PLATFORM P_UNICOS
#define PLATFORM_VARIANT P_UNICOS
#define PLATFORM_NAME "UNICOS"
#endif

/* VMS */

#if defined(VMS) || defined(__VMS)
#define PLATFORM P_VMS_SYSTEM
#define PLATFORM_VARIANT P_VMS_SYSTEM
#define PLATFORM_NAME "VMS"
#endif

/* VxWorks */

#if defined(__VXWORKS__) || defined(__vxworks)
#define PLATFORM P_VXWORKS
#define PLATFORM_VARIANT P_VXWORKS
#define PLATFORM_NAME "VxWorks"
#endif

/******************************************ENVIRONMENTS******************************************/


/* Cygwin */

#if defined(__CYGWIN__)
#define ENVIRONMENT P_CYGWIN
#define ENVIRONMENT_NAME "Cygwin"
#ifndef PLATFORM
#define PLATFORM P_WINDOWS
#define PLATFORM_NAME "Windows"
#endif
#endif

#if defined(__MINGW32__) && !defined(__MINGW64__)
#define ENVIRONMENT P_MINGW
#define ENVIRONMENT_NAME "MinGW"
#elif defined(__MINGW64__)
#define ENVIRONMENT P_MINGW
#define ENVIRONMENT_NAME "MinGW-w64"
#endif

#if defined(__MINGW32__) || defined(__MINGW64__) && !defined(PLATFORM_NAME)
#define PLATFORM_NAME "Windows"
#endif

/* EMX */

#if defined(__EMX__)
#define ENVIRONMENT P_EMX
#define ENVIRONMENT_NAME "EMX"
#endif

/* Interix */

#if defined(__INTERIX)
#define ENVIRONMENT P_INTERIX
#define ENVIRONMENT_NAME "Interix"
#endif

/* Wind/U */

#if defined(_WINDU_SOURCE)
#define ENVIRONMENT P_WINDU
#define PLATFORM P_WINDU
#define PLATFORM_VARIANT P_WINDU
#define PLATFORM_NAME "Wind/U"
#define ENVIRONMENT_NAME PLATFORM_NAME
#endif


// fail-safes
#ifndef PLATFORM
#ifdef PLATFORM_VARIANT
#define PLATFORM P_PLATFORM_VARIANT
#else
#define PLATFORM P_UKNOWN
#endif
#endif

#ifndef ENVIRONMENT
#define ENVIRONMENT PLATFORM
#endif

// set PLATFORM_NAME_LENGTH
#ifndef PLATFORM_NAME_LENGTH
#define PLATFORM_NAME_LENGTH sizeof(PLATFORM_NAME)
#endif

// set ENVIRONMENT_NAME_LENGTH
#ifndef ENVIRONMENT_NAME_LENGTH
#define ENVIRONMENT_NAME_LENGTH sizeof(ENVIRONMENT_NAME)
#endif

/**********************************************************************************************************************
 * 												    COMPILER VARIABLES
 **********************************************************************************************************************/

/*
 * VARIABLES:
 *
 * COMPILER: A value representing the current compiler. May be one of the defined values below.
 * COMPILER_NAME: A string representing the name of the current compiler. It is recommended that COMPILER be used for
 * preprocessor comparisons instead of this string.
 * COMPILER_NAME_LENGTH: the length of the COMPILER_NAME string
 */

#define C_GCC                     1
#define C_CLANG                   2
#define C_MSVC                    3
#define C_ARM                     4
#define C_LLVM                    5
#define C_MINGW                   6
#define C_MIPSPRO                 7
#define C_ORACLE_PROC             8
#define C_ORACLE_SOLARIS_STUDIO   9
#define C_TEXAS_INSTRUMENTS      10
#define C_TURBO_C                11
#define C_TINY_C                 12
#define C_ACC                    13
#define C_ALTIUM_MICROBLAZE_C    14
#define C_ALTIUM_C2H             15
#define C_AMSTERDAM_COMPILER_KIT 16
#define C_AZTEC_C             17
#define C_BORLAND_CPP            18
#define C_CC65                   19
#define C_COMEAU_CPP             20
#define C_COMPAQ_C               21
#define C_CONVEX_C               22
#define C_COMPCERT_C             23
#define C_COVERITY_C             24
#define C_CRAY_C                 25
#define C_DIAB_C                 26
#define C_DICE_C                 27
#define C_DIGIAL_MARS_C          28
#define C_DIGNUS_SYSTEMS_CPP     29
#define C_DJGPP                  30
#define C_EDG_CPP                31
#define C_EKOPATH_C              32
#define C_GREEN_HILL_C           33
#define C_HP_ANSI_C              34
#define C_HP_ACPP                35
#define C_IAR_C                  36
#define C_IBMXL_C                37
#define C_IBMXL_C_LEGACY         38
#define C_IBM_ZOSXL_C            39
#define C_IMAGECRAFT_C           40
#define C_INTEL_C                41
#define C_KAI_CPP                42
#define C_KEIL_CARM              43
#define C_KEIL_C166              44
#define C_KEIL_C51               45
#define C_LCC                    46
#define C_METROWERKS_CODEWARRIOR 47
#define C_MICROTEC_C             48
#define C_MICROWAY_NDP_C         49
#define C_MIRACLE_C              50
#define C_MPW_CPP                51
#define C_NORCROFT_C             52
#define C_NWCC                   53
#define C_OPEN64_C               54
#define C_PACIFIC_C              55
#define C_PALM_C                 56
#define C_PELLES_C               57
#define C_PORTLAND_GROUP_C       58
#define C_RENESAS_C              59
#define C_SAS_C                  60
#define C_SCO_OPENSERVER_C       61
#define C_SMALL_DEVICE_C         62
#define C_SN_C                   63
#define C_STRATUS_VOS_C          64
#define C_SYMANTEC_CPP           65
#define C_TENDRA_C               66
#define C_THINK_C                67
#define C_ULTIMATE_C             68
#define C_USL_C                  69
#define C_VBCC                   70
#define C_WATCOM_CPP             71
#define C_ZORTECH_CPP            72


/***********************************************************************************************************************
 *                                                COMPILER DEFINITIONS
 **********************************************************************************************************************/

#if defined(_ACC_)
#define COMPILER C_ACC
#define COMPILER_NAME "ACC"
#endif

#if defined(_CMB__)
#define COMPILER C_ALTIUM_MICROBLAZE_C
#define COMPILER_NAME "Altium MicroBlaze C"
#endif

#if defined(__CHC__)
#define COMPILER C_ALTIUM_C2H
#define COMPILER_NAME "Altium C-to-Hardware"
#endif

#if defined(__ACK__)
#define COMPILER C_AMSTERDAM_COMPILER_KIT
#define COMPILER_NAME "Amsterdam Compiler Kit"
#endif

#if defined(__CC_ARM)
#define COMPILER C_ARM
#define COMPILER_NAME "ARM Compiler"
#endif

#if defined(AZTEC_C) || defined(__AZTEC_C__)
#define COMPILER C_AZTEC_C
#define COMPILER_NAME "Aztec C"
#endif

#if defined(__BORLANDC__) || defined(__CODEGEARC__)
#define COMPILER C_BORLAND_CPP
#define COMPILER_NAME "Borland C++"
#endif

#if defined(__CC65__)
#define COMPILER C_CC65
#define COMPILER_NAME "CC65"
#endif

#if defined(__clang__) && !defined(__ibmxl_vrm__) // IBM XL guard
#define COMPILER C_CLANG
#define COMPILER_NAME "Clang"
#endif

#if defined(__COMO__)
#define COMPILER C_COMEAU
#define COMPILER_NAME "Comeau C++"
#endif

#if defined(__DECC) || defined(VAXC) || defined(__VAXC)
#define COMPILER C_COMPAQ_C
#define COMPILER_NAME "Compaq C"
#elif defined(__DECCXX)
#define COMPILER C_COMPAQ_C
#define COMPILER_NAME "Compaq C++"
#endif

#if defined(__convexc__)
#define COMPILER C_CONVEX_C
#define COMPILER_NAME "Convex C"
#endif

#if defined(__COMPCERT__)
#define COMPILER C_COMPCERT_C
#define COMPILER "CompCert"
#endif

#if defined(__COVERITY__)
#define COMPILER C_COVERITY_C
#define COMPILER_NAME "Covertiy C/C++ Static Analyzer"
#endif

#if defined(_CRAYC)
#define COMPILER C_CRAY_C
#define COMPILER_NAME "Cray C"
#endif

#if defined(__DCC__)
#define COMPILER C_DIAB_C
#define COMPILER_NAME "Diab C/C++"
#endif

#if defined(_DICE)
#define COMPILER C_DICE_C
#define COMPILER_NAME "DICE C"
#endif

#if defined(__DMC__)
#define COMPILER C_DIGITAL_C_DIGIAL_MARS_C
#define COMPILER_NAME "Digital Mars"
#endif

#if defined(__SYSC__)
#define COMPILER C_DIGNUS_SYSTEMS_CPP
#define COMPILER_NAME "Dignus Systems C++"
#endif

#if defined(__DJGPP__) || defined(__GO32__)
#define COMPILER C_DJGPP
#define COMPILER_NAME "DJGPP"
#endif

#if defined(__EDG__)
#define COMPILER C_EDG_CPP
#define COMPILER_NAME "EDG C++ Frontend"
#endif

#if defined(__PATHCC__)
#define COMPILER C_EKOPATH_C
#define COMPILER_NAME "EKOPath"
#endif

#if defined(__GNUC__)
#define COMPILER C_GCC
#define COMPILER_NAME "GNU C/C++ Compiler"
#endif

#if defined(__ghs__)
#define COMPILER C_GREEN_HILL_C
#define COMPILER_NAME "Green Hill C/C++"
#endif

#if defined(__HP_aCC)
#define COMPILER C_HP_ACPP
#define COMPILER_NAME "HP aC++"
#endif

#if defined(__IAR_SYSTEMS_ICC__)
#define COMPILER C_IAR_C
#define COMPILER_NAME "IAR C/C++"
#endif

#if defined(__ibmxl__) || (!defined(COMPILER) && defined(__clang__) && defined(__ibmxl_vrm__))
#define COMPILER C_IBMXL_C
#define COMPILER_NAME "IBM XL C/C++"
#endif

#if defined(__xlC__)
#define COMPILER C_IBMXL_C_LEGACY
#define COMPILER_NAME "IBM XL C/C++ Legacy"
#endif

#if defined(__IBMC__) || defined(__IBMCPP__)
#define COMPILER C_IBM_ZOSXL_C
#define COMPILER_NAME "IBM z/OS XL C/C++"
#endif

#if defined(__IMAGECRAFT__)
#define COMPILER C_IMAGECRAFT_C
#define COMPILER_NAME "ImageCraft C"
#endif

#if defined(__INTEL_COMPILER) || defined(__ICC) || defined(_ECC) || defined(_ICL)
#define COMPILER C_INTEL_C
#define COMPILER_NAME "Intel C/C++"
#endif

#if defined(_KCC)
#define COMPILER C_KAI_CPP
#define COMPILER_NAME "KAI C++"
#endif

#if defined(__CA__) || defined(__KEIL__)
#define COMPILER C_KEIL_CARM
#define COMPILER_NAME "KEIL CARM"
#endif

#if defined(__C166__)
#define COMPILER C_KEIL_C166
#define COMPILER_NAME "KEIL C166"
#endif

#if defined(__C51__)
#define COMPILER C_KEIL_C51
#define COMPILER_NAME "KEIL C51"
#endif

#if defined(__LCC__)
#define COMPILER C_LCC
#define COMPILER_NAME "LCC"
#endif

#if defined(__llvm__)
#define COMPILER C_LLVM
#define COMPILER_NAME "LLVM"
#endif

#if defined(__MWERKS__) || defined(__CWCC__)
#define COMPILER C_METROWERKS_CODEWARRIOR
#define COMPILER "Metrowerks CodeWarrior"
#endif

#if defined(_MSC_VER)
#define C_MSVC
#define COMPILER_NAME "Microsoft Visual C++"
#endif

#if defined(_MRI)
#define COMPILER C_MICROTEC_C
#define COMPILER_NAME "Microtec C/C++"
#endif

#if defined(__NDPC__) || defined(__NDPX__)
#define COMPILER C_MICROWAY_NDP_C
#define COMPILER_NAME "Microway NDP C"
#endif

#if defined(__sgi) || defined(sgi)
#define COMPILER C_MIPSPRO
#define COMPILER_NAME "MIPSpro"
#endif

#if defined(MIRACLE)
#define COMPILER C_MIRACLE_C
#define COMPILER_NAME "Miracle C"
#endif

#if defined(__MRC__) || defined(MPW_C) || defined(MPW_CPLUS)
#define COMPILER C_MPW_CPP
#define COMPILER_NAME "MPW C++"
#endif

#if defined(__CC_NORCROFT)
#define COMPILER C_NORCROFT_C
#define COMPILER_NAME "Norcroft C"
#endif

#if defined(__NWCC__)
#define COMPILER C_NWCC
#define COMPILER_NAME "NWCC"
#endif

#if defined(__OPEN64__) || defined(__OPENCC__)
#define COMPILER C_OPEN64_C
#define COMPILER_NAME "Open64"
#endif

#if defined(ORA_PROC)
#define COMPILER C_ORACLE_PROC
#define COMPILER_NAME "Oracle Pro*C Precompiler"
#endif

#if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#define COMPILER C_ORACLE_SOLARIS_STUDIO
#define COMPILER_NAME "Oracle Solaris Studio"
#endif

#if defined(__PGI__)
#define COMPILER C_PORTLAND_GROUP_C
#define COMPILER_NAME "Portland Group C/C++"
#endif

#if defined(__RENESAS__) || defined(__HITACHI__)
#define COMPILER C_RENESAS_C
#define COMPILER_NAME "Renesas C/C++"
#endif

#if defined(SASC) || defined(__SASC) || defined(__SASC__)
#define COMPILER C_SAS_C
#define COMPILER_NAME "SAS/C"
#endif

#if defined(_SCO_DS)
#define COMPILER C_SCO_OPENSERVER_C
#define COMPILER_NAME "SCO OpenServer"
#endif

#if defined(SDCC)
#define COMPILER C_SMALL_DEVICE_C
#define COMPILER_NAME "Small Device C Compiler"
#endif

#if defined(__SNC__)
#define COMPILER C_SN_C
#define COMPILER_NAME "SN Compiler"
#endif

#if defined(__VOSC__)
#define COMPILER C_STRATUS_VOS_C
#define COMPILER_NAME "Stratus VOS C"
#endif

#if defined(__SC__)
#define COMPILER C_TENDRA_C
#define COMPILER_NAME "TenDRA C/C++"
#endif

#if defined(__TI_COMPILER_VERSION__) || defined(_TMS320C6X)
#define COMPILER C_TEXAS_INSTRUMENTS
#define COMPILER_NAME "Texas Instruments C/C++ Compiler"
#endif

#if defined(THINKC3) || defined(THINKC4)
#define COMPILER C_THINK_C
#define COMPILER_NAME "THINK C"
#endif

#if defined(__TINYC__)
#define COMPILER C_TINY_C
#define COMPILER_NAME "Tiny C"
#endif

#if defined(__TURBOC__)
#define COMPILER C_TURBO_C
#define COMPILER_NAME "Turbo C/C++"
#endif

#if defined(_UCC)
#define COMPILER C_ULTIMATE_C
#define COMPILER_NAME "Ultimate C/C++"
#endif

#if defined(__USLC__)
#define COMPILER C_USL_C
#define COMPILER_NAME "USL C"
#endif

#if defined(__VBCC__)
#define COMPILER C_VBCC
#define COMPILER_NAME "VBCC"
#endif

#if defined(__WATCOMC__)
#define COMPILER C_WATCOM_CPP
#define COMPILER_NAME "Watcom C++"
#endif

#if defined(__ZTC__)
#define COMPILER C_ZORTECH_CPP
#define COMPILER_NAME "Zortech C++"
#endif

#ifndef COMPILER_NAME_LENGTH
#define COMPILER_NAME_LENGTH sizeof(COMPILER_NAME)
#endif


/***********************************************************************************************************************
 * 													ARCHITECTURE VARIABLES
 **********************************************************************************************************************/

#define ARCH_X86_32            1
#define ARCH_X86_64            2
#define ARCH_AMD64 ARCH_X86_64
#define ARCH_ARM64             3
#define ARCH_ARM32             4
#define ARCH_ARM               5
#define ARCH_INTEL_ITANIUM     6
#define ARCH_IA_64 ARCH_INTEL_ITANIUM
#define ARCH_POWERPC           7
#define ARCH_MIPS              8
#define ARCH_MIPS_R3000        9
#define ARCH_MIPS_R4000        10
#define ARCH_MIPS_R5900        11
#define ARCH_HPPA_RISC         12
#define ARCH_ALPHA             13
#define ARCH_CONVEX            14
#define ARCH_EPIPHANY          15
#define ARCH_BLACKFIN          16
#define ARCH_SPARC             17
#define ARCH_SYSTEMZ           18
#define ARCH_SUPERH            19
#define ARCH_SUPERH1           20
#define ARCH_SUPERH2           21
#define ARCH_SUPERH3           22
#define ARCH_SUPERH4           23
#define ARCH_SUPERH5           24
#define ARCH_RS6000            25
#define ARCH_RS6000_PWR        26
#define ARCH_RS6000_PWR2       27
#define ARCH_RS6000_PWR3       28
#define ARCH_RS6000_PWR4       29
#define ARCH_MOTOROLA_68000    30
#define ARCH_MOTOROLA_68010    31
#define ARCH_MOTOROLA_68020    32
#define ARCH_MOTOROLA_68030    33
#define ARCH_MOTOROLA_68040    34
#define ARCH_MOTOROLA_68060    35
#define ARCH_TMS320            36
#define ARCH_TMS320_C2800      37
#define ARCH_TMS320_C5400      38
#define ARCH_TMS320_C5500      39
#define ARCH_TMS320_C6200      40
#define ARCH_TMS320_C6400      41
#define ARCH_TMS320_C6400_PLUS 42
#define ARCH_TMS320_C6600      43
#define ARCH_TMS320_C6700      44
#define ARCH_TMS320_C6700_PLUS 45
#define ARCH_TMS320_C6740      46
#define ARCH_TMS470            47
#define ARCH_PYRAMID_9810      48
#define ARCH_RISCV             49
#define ARCH_OPTUMUS           50

#define BYTE_ORDER_ASCENDING 0
#define BYTE_ORDER_DESCENDING 1
#define BYTE_ORDER_HYBRID 2
#define BYTE_ORDER_UNDEFINED 3
#define BYTE_ORDER_BIG_ENDIAN 0
#define BYTE_ORDER_LITTLE_ENDIAN 1


/***********************************************************************************************************************
 * 													ARCHITECTURE DEFINITIONS
 **********************************************************************************************************************/


#if defined(i386) || defined(__i386) || defined(__i386__) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
#define ARCHITECTURE ARCH_X86_32
#define ARCHITECTURE_NAME "Intel x86"
  #define ARCH_BYTE_ORDER BYTE_ORDER_DESCENDING
#endif

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD64)
#define ARCH ARCH_AMD64
  #define ARCH_BYTE_ORDER BYTE_ORDER_DESCENDING
#endif

#if defined (__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB) || defined(_ARM) || defined(_M_ARM) || defined(_M_ARMT) || defined(__arm)
#define ARCHITECTURE ARCH_ARM
#define ARCHITECTURE_VARIANT ARCH_ARM32
#define ARCHITECTURE_NAME "ARM"
#define ARCH_POPULAR_BYTE_ORDER BYTE_ORDER_DESCENDING
#endif

#if defined(__aarch64__)
#define ARCHITECTURE ARCH_ARM
#define ARCHITECTURE_VARIANT ARCH_ARM64
#define ARCHITECTURE_NAME "ARM64"
#define ARCH_POPULAR_BYTE_ORDER BYTE_ORDER_DESCENDING
#endif

#if defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(_M_IA64) || defined (__itanium__)
#define ARCHITECTURE ARCH_IA_64
#define ARCHITECTURE_NAME "Intel Itanium"
#endif

#if defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__ppc64__) || defined(__PPC__) || defined(__PPC64__) || defined(_ARCH_PPC) || defined(_ARCH_PPC64) || defined(_M_PPC) || defined(__PCGECKO__) || defined(__PPCBROADWAY__) || defined(_XENON) || defined(__ppc)
#define ARCHITECTURE ARCH_POWERPC
#define ARCHITECTURE_NAME "PowerPC"
#endif

#if defined(__mips__) || defined(mips) || defined(_MIPS_ISA) || defined(__mips) || defined(__MIPS__)
#define ARCHITECTURE ARCH_MIPS
#if defined(_R3000)
#define ARCHITECTURE_VARIANT ARCH_MIPS_R3000
#define ARCHITECTURE_NAME "MIPS R3000"
#elif defined(_R4000)
#define ARCHITECTURE_VARIANT ARCH_MIPS_R4000
#define ARCHITECTURE_NAME "MIPS R4000"
#elif defined(_R5900)
#define ARCHITECTURE_VARIANT ARCH_MIPS_R5900
#define ARCHITECTURE_NAME "MIPS R5900"
#endif
#ifndef ARCHITECTURE_NAME
#define ARCHITECTURE_NAME "MIPS"
#endif
#endif

#if defined(__hppa__) || defined(__HPPA__) || defined(__hppa)
#define ARCHITECTURE ARCH_HPPA_RISC
#define ARCHITECTURE_NAME "HP/PA RISC"
#endif

#if defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
#define ARCHITECTURE ARCH_ALPHA
#define ARCHITECTURE_NAME "Alpha"
#endif

#if defined(__convex__)
#define ARCHITECTURE ARCH_CONVEX
#define ARCHITECTURE_NAME "Convex"
#endif

#if defined(__epiphany__)
#define ARCHITECTURE ARCH_EPIPHANY
#define ARCHITECTURE_NAME "Epiphany"
#endif

#if defined (__bfin) || defined(__BFIN__)
#define ARCHITECTURE ARCH_BLACKFIN
#define ARCHITECTURE_NAME "Blackfin"
#endif

#if defined(__sparc__) || defined(__sparc)
#define ARCHITECTURE ARCH_SPARC
#if defined(__sparc_v8__) || defined(__sparcv8)
#define ARCHITECTURE_VARIANT ARCH_SPARC_V8
#defien ARCHITECTURE_NAME "SPARC v8"
#elif defined(__sparc_v9__) || defined(__sparcv9)
#define ARCHITECTURE_VARIANT ARCH_SPARC_V9
#define ARCHITECTURE_NAME "SPARC v9"
#endif
#ifndef ARCHITECTURE_NAME
#define ARCHITECTURE_NAME "SPARC"
#endif
#endif

#if defined(__370__) || defined(__THW_370__) || defined(__s390__) || defined(__s390x__) || defined(__zarch__) || defined(__SYSC_ZARCH__)
#define ARCHITECTURE ARCH_SYSTEMZ
#define ARCHITECTURE_NAME "SystemZ"
#endif

#if defined(__sh__)
#define ARCHITECTURE ARCH_SUPERH
#if defined(__sh1__)
#define ARCHITECTURE_VARIANT ARCH_SUPERH1
#define ARCHITECTURE_NAME "SuperH v1"
#elif defined(__sh2__)
#define ARCHITECTURE_VARIANT ARCH_SUPERH2
#define ARCHITECTURE_NAME "SuperH v2"
#elif defined(__sh3__) || defined(__SH3__)
#define ARCHITECTURE_VARIANT ARCH_SUPERH3
#define ARCHITECTURE_NAME "SuperH v3"
#elif defined(__SH4__)
#define ARCHITECTURE_VARIANT ARCH_SUPERH4
#define ARCHITECTURE_NAME "SuperH v4"
#elif defined(__SH5__)
#define ARCHITECTURE_VARIANT ARCH_SUPERH5
#define ARCHITECTURE_NAME "SuperH v5"
#endif

#ifndef ARCHITECTURE_NAME
#define ARCHITECTURE_NAME "SuperH"
#endif
#endif

#if defined(__THW_RS6000) || defined(_IBMR2) || defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || defined(_ARCH_PWR4)
#define ARCHITECTURE ARCH_RS6000
#if defined(_ARCH_PWR)
#define ARCHITECTURE_VARIANT ARCH_RS6000_PWR
#define ARCHITECTURE_NAME "RS/6000 Power 1"
#elif defined(_ARCH_PWR2)
#define ARCHITECTURE_VARIANT ARCH_RS6000_PWR2
#define ARCHITECTURE_NAME "RS/6000 Power 2"
#elif defined(_ARCH_PWR3)
#define ARCHITECTURE_VARIANT ARCH_RS6000_PWR3
#define ARCHITECTURE_NAME "RS/6000 Power 3"
#elif defined(_ARCH_PWR4)
#define ARCHITECTURE_VARIANT ARCH_RS6000_PWR4
#define ARCHITECTURE_NAME "RS/6000 Power 4"
#endif
#ifndef ARCHITECTURE_NAME
#define ARCHITECTURE_NAME "RS/6000"
#endif
#endif

#if defined(__m68k__) || defined(M68000)
#define ARCHITECTURE ARCH_MOTOROLA_68000
#if defined(__mc68010__)
#define ARCHITECTURE_VARIANT ARCH_MOTOROLA_68010
#define ARCHITECTURE_NAME "Motorola 68010"
#elif defined(__mc68020__) || defined(__MC68020__)
#define ARCHITECTURE_VARIANT ARCH_MOTOROLA_68020
#define ARCHITECTURE_NAME "Motorola 68020"
#elif defined(__mc68030__) || defined(__MC68030__)
#define ARCHITECTURE_VARIANT ARCH_MOTOROLA_68030
#define ARCHITECTURE_NAME "Motorola 68030"
#elif defined(__mc68040__)
#define ARCHITECTURE_VARIANT ARCH_MOTOROLA_68040
#define ARCHITECTURE_NAME "Motorola 68040"
#elif defined(__mc68050__)
#define ARCHITECTURE_VARIANT ARCH_MOTOROLA_68060
#define ARCHITECTURE_NAME "Motorola 68060"
#endif
#ifndef ARCHITECTURE_NAME
#define ARCHITECTURE_NAME "Motorola 68000"
#endif
#endif

#if defined(_TMS320C2XX) || defined(__TMS320C2000__) || defined(_TMS320C5X) || defined(__TMS320C55X__) || defined(_TMS320C6X) || defined(__TMS320C6X__)
#define ARCHITECTURE ARCH_TMS320
#if defined(_TMS320C28X)
#define ARCHITECTURE_VARIANT ARCH_TMS320_C2800
#define ARCHITECTURE_NAME "TMS320 C2800"
#elif defined(_TMS320C5XX)
#define ARCHITECTURE_VARIANT ARCH_TMS320_C5400
#define ARCHITECTURE_NAME "TMS320 C5400"
#elif defined(__TMS320C55X__)
#define ARCHITECTURE_VARIANT ARCH_TMS320_C5500
#define ARCHITECTURE_NAME "TMS320 C5500"
#elif defined(_TMS320C6200)
#define ARCHITECTURE_VARIANT ARCH_TMS320_C6200
#define ARCHITECTURE_NAME "TMS320 C6200"
#elif defined(_TMS320C6400)
#define ARCHITECTURE_VARIANT ARCH_TMS320_C6400
#define ARCHITECTURE_NAME "TMS320 C6400"
#elif defined(_TMS320C6400_PLUS)
#define ARCHITECTURE_VARIANT ARCH_TMS320_C6400_PLUS
#define ARCHITECTURE_NAME "TMS320 C6400+"
#elif defined(_TMS320C6600)
#define ARCHITECTURE_VARIANT ARCH_TMS320_C6600
#define ARCHITECTURE_NAME "TMS320 C6600"
#elif defined(_TMS320C6700)
#define ARCHITECTURE_VARIANT ARCH_TMS320_C6700
#define ARCHITECTURE_NAME "TMS320 C6700"
#elif defined(_TMS320C6700_PLUS)
#define ARCHITECTURE_VARIANT ARCH_TMS320_C6700_PLUS
#define ARCHITECTURE_NAME "TMS320 C6700+"
#elif defined(_TMS320C6740)
#define ARCHITECTURE_VARIANT ARCH_TMS320_C6740
#define ARCHITECTURE_NAME "TMS320 C6740"
#endif
#ifndef ARCHITECTURE_NAME
#define ARCHITECTURE_NAME "TMS320 C????"
#endif
#endif

#if defined(__TMS470__)
#define ARCHITECTURE ARCH_TMS470
#define ARCHITECTURE_NAME "TMS470"
#endif

#if defined(pyr) || defined(__pyr) || defined(__pyr__)
#define ARCHITECTURE ARCH_PYRAMID_9810
#define ARCHITECTURE_NAME "Pyramid 9810"
#endif

// RISC-V detection
#if defined(riscv) || defined(__riscv) || defined(__riscv__)
#define ARCHITECTURE ARCH_RISCV
#define ARCHITECTURE_NAME "RISC-V"
#endif

// our abstract universal ISA
#if defined(__optumus) || defined(__optumus__) || defined(__OPTUMUS) || defined(__OPTUMUS__)
#define ARCHITECTURE ARCH_OPTUMUS
#define ARCHITECTURE_NAME "Optumus"
#endif

#ifndef ARCH_VARIANT
#define ARCH_VARIANT ARCH
#endif

#define ARCH_NAME_LENGTH sizeof(ARCHITECTURE_NAME)

/***********************************************************************************************************************
 * 													DATA MODEL VARIABLES
 **********************************************************************************************************************/

#define LP32 1
#define ILP32 2
#define LP64 3
#define LLP64 4
#define ILP64 5
#define SILP64 6
#define M_AQUINAS 7


/***********************************************************************************************************************
 * 													DATA MODEL DEFINITIONS
 **********************************************************************************************************************/

#if defined(_ILP32) || defined(__ILP32__)
#define DATA_MODEL ILP32
#define DATA_MODEL_NAME "ILP32"
#endif

#if defined(_LP64) || defined(__LP64__)
#define DATA_MODEL LP64
#define DATA_MODEL_NAME "LP64"
#endif

#if defined(_LP32) || defined(__LP32__)
#define DATA_MODEL LP32
#define DATA_MODEL_NAME "LP32"
#endif

#if defined(_LLP64) || defined(__LLP64__)
#define DATA_MODEL LLP64
#define DATA_MODEL_NAME "LLP64"
#endif

#if defined(_ILP64) || defined(__ILP64__)
#define DATA_MODEL ILP64
#define DATA_MODEL_NAME "ILP64"
#endif

#if defined(_SILP64) || defined (__SILP64__)
#define DATA_MODEL SILP64
#define DATA_MODEL_NAME "SILP64"
#endif

#if defined(_AQUINAS) || defined (__AQUINAS__) || defined(_aquinas) || defined(__aquinas__)
#define DATA_MODEL M_AQUINAS
#define DATA_MODEL_NAME "Aquinas"
#endif

#ifndef DATA_MODEL
// make default data model LP64
#define DATA_MODEL LP64
#endif

#ifndef DATA_MODEL_VARIANT
#define DATA_MODEL_VARIANT DATA_MODEL
#endif

#ifndef DATA_MODEL_NAME_LENGTH
#define DATA_MODEL_NAME_LENGTH sizeof(DATA_MODEL_NAME)
#endif

/* general word information */
// udqword: unsigned 128-bit value
// dqword: signed 128-bit value
// uqword: unsigned 64-bit value
// qword: signed 64-bit value
// udword: unsigned 32-bit value
// dword: signed 32-bit value
// uword: unsigned 16-bit value
// word: signed 16-bit value
// ubyte: unsigned 8-bit value
// sbyte: signed 8-bit value
// uintmin_t: smallest supported unsigned integer type (may be ubyte or smaller)
// intmin_t: smallest supported signed integer type (may be sbyte or smaller)
// udevptr_t: a udqword containing a hardware address to a hardware device (implementation dependent), for example: to PCI,
// SATA, SCSI, network, virtual (software) device, etc.

// independent types
//typedef uintmax_t     udqword;
//typedef intmax_t      dqword;
typedef uint64_t uqword;
typedef int64_t  qword;
typedef uint32_t udword;
typedef int32_t dword;
typedef uint16_t uword;
typedef int16_t word;
typedef uint8_t  ubyte;
typedef int8_t sbyte;
#define p_unybble 4
#define p_nybble 4
typedef uint8_t uintmin_t;
typedef int8_t intmin_t;

// data-model-specific types
#if DATA_MODEL == ILP32
typedef uint64_t udqword;
typedef int64_t dqword;
#elif DATA_MODEL == LP64
typedef unsigned __int128 udqword;
typedef signed __int128   dqword;
#elif DATA_MODEL == LP32
typedef uint64_t udqword;
typedef int64_t  dqword;
#elif DATA_MODEL == LLP64
typedef unsigned __int128 udqword;
typedef signed __int128   dqword;
#elif DATA_MODEL == ILP64
typedef unsigned __int128 udqword;
typedef signed __int128   dqword;
#elif DATA_MODEL == SILP64
typedef unsigned __int128 udqword;
typedef signed __int128   dqword;
#elif DATA_MODEL == M_OPTUMUS
typedef unsigned bool udqword[2];
typedef signed bool   dqword[2];
#else
#endif

// device pointer types should be twice the native qword size in bits
typedef udqword udevptr_t;

// common uqword_pair struct
typedef struct uqword_pair {
    uqword a;
    uqword b;
} uqword_pair;

#define MIN_BITS CHAR_BIT

/* generic platform functions */

// currently unused
typedef enum device_type {
    PHYSICAL, LOGICAL
} device_type;

// currently unused
typedef struct p_device {
    // the unique identifier for this device
    uintmax_t uid;
    // the device name string
    char *name;
    // the platform-dependent interface module name of this device, commonly called the device driver
    // may otherwise be a logical interface, a.k.a. virtual device driver.
    // To be used with p_get_fn's module parameter
    char *interface_module;
    device_type type;
} p_device;

typedef enum p_time_resolution {
    CYCLES, NANOSECONDS, MICROSECONDS, MILLISECONDS, SECONDS,
} p_time_resolution;

/*
 * # `char *p_get_platform();`
 * Gets the platform (friendly) name string. Use the macro expansion `PLATFORM_NAME_LENGTH` for string length (with null terminator).
 *
 * You may alternatively use the `PLATFORM_NAME` macro when you do not need to retrieve the friendly platform name strictly
 * at runtime.
 *
 * ## `return struct p_result`
 * A `struct p_result` containing a pointer of type `char *`, a null-terminated string containing the platform name.
 */
char *p_get_platform();

/*
 * # `char *p_get_env(char *var);`
 * Gets an environment variable associated with the given string. The platform-dependent behavior is conveniently
 * abstracted away in favor of a common behavior.
 *
 */
char *p_get_env(char *var);

/* platform functional programming */

/*
 * # `void *p_get_fn(char *module, char *function);` ("get function")
 * Gets a function from the specified implementation-specific module. The module is explicitly the name of the module
*  without any sort of file extension, and will first check the program's environment for an existing module before
*  searching the system's environment for the given module. If the function succeeds in finding the module, the function
*  will attempt to retrieve the address of the specified function, or return `NULL` with result code `R_INITIALIZATION_FAILURE`.
*
*  If the function is unable to find the module name, the result will contain a `NULL` result with result code `R_FAILURE`.
 *
 *  The return type and arguments of this function pointer are non-sensical; you must cast the returned function pointer
 *  to the correct function pointer.
 *
 *  ## `char *module`
 *  a string containing the module name
 *
 *  ## `char *function`
 *  a string containing the function name
 *
 *  ## `return uintptr_t`
 *  A `void *` containing the start of the function as `(void *(module_base_address + function_offset)`
*/
void *(*p_get_fn(char *module, char *function))();

/*
 * # `uintptr_t p_get_fn_offset(char *module, uintptr_t function_offset);` ("get function absolute")
 * Gets a function from the specified implementation-specific module. The module is explicitly the name of the module
*  without any sort of file extension, and will first check the program's environment for an existing module before
*  searching the system's environment for the given module. If the function succeeds in finding the module, the function
*  will attempt to retrieve the address of the specified function, or return `NULL` with result code `R_INITIALIZATION_FAILURE`.
 *
 * The return type and arguments of this function pointer are non-sensical; you must cast the returned function pointer
 *  to the correct function pointer.
 *
 * ## `char *module`
 * a string containing the module name
 *
 * ## `uintptr_t function_offset`
 * a pointer value representing the offset of the function relative to the start of the module
 *
 * ## `return uintptr_t`
 * A `uintptr_t` containing the start of the function as `(uintptr_t) (module_base_address + function_offset)`
 */
void *(*p_get_fn_offset(char *module, uintptr_t function_offset))();

// currently unused (no implementation)
int p_get_errno();

// currently unused (no implementation)
void p_set_errno(int state);

/*
 * # `uintmax_t p_get_time(enum p_unit unit);`
 * Real-time hardware clock interrupt query.
 *
 * Returns the current real-time clock value stored in a `uintmax_t`.
 */
uintmax_t p_get_time(enum p_time_resolution unit);

/*
 * # `uintmax_t p_get_timestamp();`
 * Gets the current timestamp in the following encoding:
 *
 *      :year:month:day:hour:minute:second:
 *      : 12 :  4  : 5 : 5  :  6   :   6  :
 *
 * Each value is stored as a big endian value. The returned value is a single 64-bit big endian value whose most
 * significant bits are zero.
 */
uint64_t p_get_timestamp();

/* platform hardware enumeration */

// struct p_device p_get_device();

#endif /* PROJECT_AQUINAS_INCLUDE_P_H */
