/*
 * file: platform.h
 * origin: platform.h
 * author: Andrew Thomas Porter <caritasdedeus@gmail.com>
 * description:
 */

#ifndef INCLUDE_PLATFORM_H_
#define INCLUDE_PLATFORM_H_

#include <stddef.h>

/*
 * VARIABLES:
 *
 * ENVIRONMENT: the value representing the current environment which is the name of a wrapper API such as Cygwin, MinGW,
 * ENVIRONMENT_NAME
 * ENVIRONMENT_NAME_LENGTH
 * ENVIRONMENT_VARIANT
 *
 * PLATFORM
 * PLATFORM_NAME
 * PLATFORM_NAME_LENGTH
 * PLATFORM_NAME_LENGTH_MAX
 * PLATFORM_VARIANT
 */
/* platforms */
#define WINDOWS         1
#define LINUX           2
#define UNIX            3
#define MACINTOSH       4
#define BSD_ENVIRONMENT 5
#define ANDROID         6
#define GNU             7
#define CYGWIN          8
#define MINGW           9
#define EMX            10
#define INTERIX        11
#define WINDU          12

/* platform variants */
/* WINDOWS */
#define WINDOWS_CE              13
#define WINDOWS_HPC2000         14
#define WINDOWS_HPCPRO          15
#define WINDOWS_POCKETPC        16
#define WINDOWS_MOBILE_2003     17
#define WINDOWS_SMARTPHONE_2002 18
/* LINUX */
#define SOLARIS  19
#define GNULINUX 20
#define MINIX    21
/* UNIX */
#define DRAGONFLY   22
#define HPUX        23
#define UNIXWARE    24
#define LYNX        25
#define DGUX_SYSTEM 26
#define SINUX       27
#define ULTRIX      28
#define DYNIX       29


/* other platforms */
#define AIX            30
#define OS400          31
#define FREEBSD        32
#define NETBSD         33
#define OPENBSD        34
#define BSDI           35
#define KFREEBSD       36
#define OS9            37
#define BEOS           38
#define AMIGAOS        39
#define MORPH          40
#define AEGIS          41
#define BLUE_GENE      42
#define AMDAHL_UTS     43
#define CONVEX         44
#define ECOS           45
#define HIUXMPP        46
#define INTEGRITY      47
#define MPE            48
#define MSDOS_SYSTEM   49
#define NONSTOP        50
#define NUCLEUS        51
#define OS2_SYSTEM     52
#define PALMOS         53
#define ZOS            54
#define PLAN9          55
#define PYRAMIDDC      56
#define QNX            57
#define SCO_OPENSERVER 58
#define STRATUS_VOS    59
#define SVR4           60
#define SYLLABLE       61
#define SYMBIAN        62
#define TRU64          63
#define UNICOS         64
#define VMS_SYSTEM     65
#define VXWORKS        66
#define UNKNOWN        67

// based on 0.1% percentile of word length distribution for English (16 * 4 = 64 characters)
// source: <http://www.ravi.io/language-word-lengths>
#define PLATFORM_NAME_LENGTH_MAX 64


/******************************************PLATFORMS******************************************/


/* Windows */

#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define PLATFORM WINDOWS
#define PLATFORM_VARIANT WINDOWS
#define PLATFORM_NAME "Windows"

#endif

#if defined(_WIN32_WCE)
	#define PLATFORM WINDOWS
	#define PLATFORM_VARIANT WINDOWS_CE
	#define PLATFORM_NAME "Windows CE"
	#define PLATFORM_NAME_LENGTH sizeof(PLATFORM_NAME)
#endif

#if defined(WIN32_PLATFORM_HPC2000)
	#define PLATFORM WINDOWS
	#define PLATFORM_VARIANT WINDOWS_HPC2000
	#define PLATFORM_NAME "Windows HPC 2000"
#endif

#if defined(WIN32_PLATFORM_HPCPRO)
	#define PLATFORM WINDOWS
	#define PLATFORM_VARIANT WINDOWS_HPCPRO
	#define PLATFORM_NAME "Windows HPC Pro"
#endif

#if defined(WIN32_PLATFORM_PSPC)
	#define PLATFORM WINDOWS
	#if WIN32_PLATFORM_PSPC < 400
		#define PLATFORM_VARIANT WINDOWS_POCKETPC
		#define PLATFORM_NAME "Windows PocketPC"
	#else
		#define PLATFORM_VARIANT WINDOWS_MOBILE_2003
		#define PLATFORM_NAME "Windows Mobile 2003"
	#endif
#endif

#if defined(WIN32_PLATFORM_WFSP)
	#define PLATFORM WINDOWS
	#define PLATFORM_VARIANT WINDOWS_SMARTPHONE_2002
	#define PLATFORM_NAME "Windows Smartphone 2002"
#endif

/* LINUX */

#if defined(__linux__) || defined(linux) || defined(__linux)
	#define ENVIRONMENT UNIX
	#define PLATFORM LINUX
	#define PLATFORM_VARIANT LINUX
	#define PLATFORM_NAME "Linux"
#endif

#if defined(__gnu_linux__)
	#define ENVIRONMENT UNIX
	#define PLATFORM LINUX
	#define PLATFORM_VARIANT GNULINUX
	#define PLATFORM_NAME "GNU Linux"
#endif

#if defined(__minix)
	#define ENVIRONMENT UNIX
	#define PLATFORM LINUX
	#define PLATFORM_VARIANT MINIX
	#define PLATFORM_NAME "Minix"
#endif

/* UNIX */

#if defined(__unix__) || defined(__unix)
	#if !(PLATFORM == CYGWIN) && !(PLATFORM == MINGW)
		#define PLATFORM UNIX
		#define PLATFORM_VARIANT UNIX
		#ifndef PLATFORM_NAME
			#define PLATFORM_NAME "Unix"
		#endif
	#endif
#endif

/* UNIX-derivative (newest to oldest release descending) */

/* DragonFly */
#if defined(__DragonFly__)
	#define PLATFORM UNIX
	#define PLATFORM_VARIANT DRAGONFLY
	#define PLATFORM_NAME "DragonFly"
#endif

/* HPUX */
#if defined(_hpux) || defined(hpux) || defined(__hpux)
	#define PLATFORM UNIX
	#define PLATFORM_VARIANT HPUX
	#define PLATFORM_NAME "HP-UX"
#endif

/* UnixWare */
#if defined(sco) || defined(_UNIXWARE7)
	#define PLATFORM UNIX
	#define PLATFORM_VARIANT UNIXWARE
	#define PLATFORM_NAME "UnixWare"
#endif

/* LynxOS */
#if defined(__Lynx__)
	#define PLATFORM UNIX
	#define PLATFORM_VARIANT LYNX
	#define PLATFORM_NAME "Lynx"
#endif

/* DG/UX */
#if defined(DGUX) || defined(__DGUX__) || defined(__dgux__)
	#define PLATFORM UNIX
	#define PLATFORM_VARIANT DGUX_SYSTEM
	#define PLATFORM_NAME "DG/UX"
#endif

/* Reliant UNIX */
#if defined(sinux)
	#define PLATFORM UNIX
	#define PLATFORM_VARIANT SINUX
	#define PLATFORM_NAME "Reliant UNIX"
#endif

/* Ultrix */
#if defined(ultrix) || defined(__ultrix) || defined(__ultrix__) || (defined(unix) && defined(vax))
	#define PLATFORM UNIX
	#define PLATFORM_VARIANT ULTRIX
	#define PLATFORM_NAME "Ultrix"
#endif

/* DYNIX */
#if defined(_SEQUENT_) || defined(sequent)
	#define PLATFORM UNIX
	#define PLATFORM_VARIANT DYNIX
	#define PLATFORM_NAME "DYNIX/ptx"
#endif

/* AIX */

#if defined(_AIX) || defined(__TOS_AIX__)
	#define PLATFORM AIX
	#define PLATFORM_VARIANT AIX
	#define PLATFORM_NAME "AIX"
#endif

/* APPLE MACINTOSH/MAC OS X */

#if defined(macintosh) || defined(Macintosh)
	#define PLATFORM MACINTOSH
	#define PLATFORM_VARIANT MACINTOSH
	#define PLATFORM_NAME "Macintosh"
#endif

#if defined(__APPLE__) && defined(__MACH__)
	#define PLATFORM MACINTOSH
	#define PLATFORM_VARIANT MACOSX
	#define PLATFORM_NAME "Mac OS/X"
#endif

/* IBM OS/400 */

#if defined(__OS400__)
	#define PLATFORM OS400
	#define PLATFORM_VARIANT OS400
	#define PLATFORM_NAME "IBM OS/400"
#endif

/* BSD */

#if defined(__FreeBSD__)
	#define PLATFORM BSD_ENVRIONMENT
	#define PLATFORM_VARIANT FREEBSD
	#define PLATFORM_NAME "FreeBSD"
#endif

#if defined(__NetBSD__)
	#define PLATFORM BSD_ENVIRONMENT
	#define PLATFORM_VARIANT NETBSD
	#define PLATFORM_NAME "NetBSD"
#endif

#if defined(__OpenBSD__)
	#define PLATFORM BSD_ENVIRONMENT
	#define PLATFORM_VARIANT OPENBSD
	#define PLATFORM_NAME "OpenBSD"
#endif

#if defined(__bsdi__)
	#define PLATFORM BSD_ENVIRONMENT
	#define PLATFORM_VARIANT BSDI
	#define PLATFORM_NAME "BSDi"
#endif

#if defined(BSD)
	#define PLATFORM BSD_ENVIRONMENT
	#define PLATFORM_NAME "BSD"
#endif

#if defined(_SYSTYPE_BSD)
	#define PLATFORM BSD_ENVIRONMENT
	#define PLATFORM_VARIANT BSD
	#define PLATFORM_NAME "BSD"
#endif

#if defined(__FreeBSD_kernel__) && defined(__GLIBC__)
	#define PLATFORM BSD_ENVIRONMENT
	#define PLATFORM_VARIANT KFREEBSD
	#define PLATFORM_NAME "KFreeBSD"
#endif

/* Android */

#if defined(__ANDROID__)
	#define PLATFORM ANDROID
	#define PLATFORM_VARIANT ANDROID
	#define PLATFORM_NAME "Android"
#endif

/* Solaris */

#if defined(sun) || defined(__sun)
	#define ENVIRONMENT UNIX
	#define PLATFORM LINUX
	#define PLATFORM_VARIANT SOLARIS
	#define PLATFORM_NAME "Oracle Solaris"
#endif

/* GNU */

#if defined(__GNU__) || defined(__gnu_hurd__)
	#define PLATFORM GNU
	#define PLATFORM_VARIANT GNU
	#define PLATFORM_NAME "GNU"
#endif

/* OS-9 */

#if defined(__OS9000) || defined(_OSK)
	#define PLATFORM OS9
	#define PLATFORM_VARIANT OS9
	#define PLATFORM_NAME "Microware OS-9"
#endif

/* BeOS  */

#if defined(__BEOS__)
	#define PLATFORM BEOS
	#define PLATFORM_VARIANT BEOS
	#define PLATFORM_NAME "BeOS"
#endif

/* AmigaOS */

#if defined(AMIGA) || defined(__amigaos__)
	#define PLATFORM AMIGAOS
	#define PLATFORM_VARIANT AMIGAOS
	#define PLATFORM_NAME "AmigaOS"
#endif

/* MorphOS */

#if defined(__MORPHOS__)
	#define PLATFORM MORPH
	#define PLATFORM_VARIANT MORPH
	#define PLATFORM_NAME "MorphOS"
#endif

/* Aegis */

#if defined(aegis)
	#define PLATFORM AEGIS
	#define PLATFORM_VARIANT AEGIS
	#define PLATFORM_NAME "Apollo AEGIS"
#endif

/* Blue Gene */

#if defined(__bg__) || defined(__THW_BLUEGENE__)
	#define PLATFORM BLUE_GENE
	#define PLATFORM_VARIANT BLUE_GENE
	#define PLATFORM_NAME "Blue Gene"
#endif

/* Amdahl UTS */

#if defined(UTS)
	#define PLATFORM UTS
	#define PLATFORM_VARIANT AMDAHL_UTS
	#define PLATFORM_NAME "Amdahl UTS"
#endif

/* Convex */

#if defined(__convex__)
	#define PLATFORM CONVEX
	#define PLATFORM_VARIANT CONVEX
	#define PLATFORM_NAME "ConvexOS"
#endif

/* eCos */

#if defined(__ECOS)
	#define PLATFORM ECOS
	#define PLATFORM_VARIANT ECOS
	#define PLATFORM_NAME "eCos"
#endif

/* OSF/1 AD */

#if defined(__hiuxmpp)
	#define PLATFORM HIUXMPP
	#define PLATFORM_VARIANT HIUXMPP
	#define PLATFORM_NAME "HI-UX MPP"
#endif

/* INTEGRITY */

#if defined(__INTEGRITY)
	#define PLATFORM INTEGRITY
	#define PLATFORM_VARIANT INTEGRITY
	#define PLATFORM_NAME "INTEGRITY"
#endif

/* MPE */

#if defined(mpeix) || defined(__mpexl)
	#define PLATFORM MPE
	#define PLATFORM_VARIANT MPE
	#define PLATFORM_NAME "MPE/iX"
#endif

/* MSDOS */

#if defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
	#define PLATFORM MSDOS_SYSTEM
	#define PLATFORM_VARIANT MSDOS_SYSTEM
	#define PLATFORM_NAME "MSDOS"
#endif

/* NonStop */

#if defined(__TANDEM)
	#define PLATFORM NONSTOP
	#define PLATFORM_VARIANT NONSTOP
	#define PLATFORM_NAME "NonStop"
#endif

/* Nucleus RTOS */

#if defined(__nucleus__)
	#define PLATFORM NUCLEUS
	#define PLATFORM_VARIANT NUCLEUS
	#define PLATFORM_NAME "Nucleus RTOS"
#endif

/* OS/2 */

#if defined(OS2) || defined(_OS2) || defined(__OS2__) || defined(__TOS_OS2__)
	#define PLATFORM OS2_SYSTEM
	#define PLATFORM_VARIANT OS2_SYSTEM
	#define PLATFORM_NAME "OS/2"
#endif

/* PalmOS */

#if defined(__palmos__)
	#define PLATFORM PALMOS
	#define PLATFORM_VARIANT PALMOS
	#define PLATFORM_NAME "PalmOS"
#endif

/* z/OS */

#if defined(__MVS__) || defined(__HOS_MVS__) || defined(__TOS_MVS__)
	#define PLATFORM ZOS
	#define PLATFORM_VARIANT ZOS
	#define PLATFORM_NAME "z/OS"
#endif

/* Plan 9 */

#if defined(EPLAN9)
	#define PLATFORM PLAN9
	#define PLATFORM_VARIANT PLAN9
	#define PLATFORM_NAME "Plan 9"
#endif

/* Pyramid DC/OSx */

#if defined(pyr)
	#define PLATFORM PYRAMIDDC
	#define PLATFORM_VARIANT PYRAMIDDC
	#define PLATFORM_NAME "Pyramid DC/OSx"
#endif

/* QNX */

#if defined(__QNX__) || defined(__QNXNTO__)
	#define PLATFORM QNX
	#define PLATFORM_VARIANT QNX
	#define PLATFORM_NAME "QNX"
#endif
/* SCO OpenServer */

#if defined(M_I386) || defined(M_XENIX) || defined(_SCO_DS)
	#define PLATFORM SCO_OPENSERVER
	#define PLATFORM_VARIANT SCO_OPENSERVER
	#define PLATFORM_NAME "SCO OpenServer"
#endif

/* Stratus VOS */

#if defined(__VOS__)
	#define PLATFORM STRATUS_VOS
	#define PLATFORM_VARIANT STRATUS_VOS
	#define PLATFORM_NAME "Stratus VOS"
#endif

/* SVR4 */

#if defined(__sysv__) || defined(__SVR4) || defined(__svr4__) || defined(_SYSTYPE_SVR4)
	#define PLATFORM SVR4
	#define PLATFORM_VARIANT SVR4
	#define PLATFORM_NAME "SVR4"
#endif

/* Syllable */

#if defined(__SYLLABLE__)
	#define PLATFORM SYLLABLE
	#define PLATFORM_VARIANT SYLLABLE
	#define PLATFORM_NAME "Syllable"
#endif

/* Symbian OS */

#if defined(__SYMBIAN32__)
	#define PLATFORM SYMBIAN
	#define PLATFORM_VARIANT SYMBIAN
	#define PLATFORM_NAME "Symbian OS"
#endif

/* Tru64 (OSF/1) */

#if defined(__osf__) || defined(__osf)
	#define PLATFORM TRU64
	#define PLATFORM_VARIANT TRU64
	#define PLATFORM_NAME "Tru64 (OSF/1)"
#endif

/* UNICOS */

#if defined(_UNICOS)
	#define PLATFORM UNICOS
	#define PLATFORM_VARIANT UNICOS
	#define PLATFORM_NAME "UNICOS"
#endif

/* VMS */

#if defined(VMS) || defined(__VMS)
	#define PLATFORM VMS_SYSTEM
	#define PLATFORM_VARIANT VMS_SYSTEM
	#define PLATFORM_NAME "VMS"
#endif

/* VxWorks */

#if defined(__VXWORKS__) || defined(__vxworks)
	#define PLATFORM VXWORKS
	#define PLATFORM_VARIANT VXWORKS
	#define PLATFORM_NAME "VxWorks"
#endif

/******************************************ENVIRONMENTS******************************************/


/* Cygwin */

#if defined(__CYGWIN__)
	#define ENVIRONMENT CYGWIN
	#define ENVIRONMENT_NAME "Cygwin"
	#ifndef PLATFORM
		#define PLATFORM WINDOWS
		#define PLATFORM_NAME "Windows"
	#endif
#endif

#if defined(__MINGW32__) && !defined(__MINGW64__)
	#define ENVIRONMENT MINGW
	#define ENVIRONMENT_NAME "MinGW"
#elif defined(__MINGW64__)
	#define ENVIRONMENT MINGW
	#define ENVIRONMENT_NAME "MinGW-w64"
#endif

#if defined(__MINGW32__) || defined(__MINGW64__) && !defined(PLATFORM_NAME)
	#define PLATFORM_NAME "Windows"
#endif

/* EMX */

#if defined(__EMX__)
	#define ENVIRONMENT EMX
	#define ENVIRONMENT_NAME "EMX"
#endif

/* Interix */

#if defined(__INTERIX)
	#define ENVIRONMENT INTERIX
	#define ENVIRONMENT_NAME "Interix"
#endif

/* Wind/U */

#if defined(_WINDU_SOURCE)
	#define ENVIRONMENT WINDU
	#define PLATFORM WINDU
	#define PLATFORM_VARIANT WINDU
	#define PLATFORM_NAME "Wind/U"
	#define ENVIRONMENT_NAME PLATFORM_NAME
#endif


// fail-safes
#ifndef PLATFORM
	#ifdef PLATFORM_VARIANT
		#define PLATFORM PLATFORM_VARIANT
	#else
		#define PLATFORM UKNOWN
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
 ***********************************************************************************************************************/

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

/* generic word information */
// uword: an unsigned word; has the same number of bits as the native architecture's word
typedef uintptr_t uword;
// word: a signed word; has the same number of bits as the native architecture's word
typedef intptr_t word;

/* generic platform functions */

#include "../error.h"
#include <stdint.h>

struct p_result {
	union {
		void *value;

		void (*function)();
	} content;

	enum result_code code;
};

// currently unused
enum device_type {
	PHYSICAL, LOGICAL
};

typedef uintmax_t udevptr_t;

// currently unused
struct p_device {
	// the unique identifier for this device
	uintmax_t        uid;
	// the device name string
	char             *name;
	// the platform-dependent interface module name of this device, commonly called the device driver
	// may otherwise be a logical interface, a.k.a. virtual device driver.
	// To be used with p_get_fn's module parameter
	char             *interface_module;
	enum device_type type;
};

enum p_time_resolution {
	CYCLES, NANOSECONDS, MICROSECONDS, MILLISECONDS, SECONDS,
};

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
 * # `uintptr_t p_get_fna(char *module, uintptr_t function_offset);` ("get function absolute")
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
void *(*p_get_fna(char *module, uintptr_t function_offset))();

int p_get_errno();

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

#endif /* INCLUDE_PLATFORM_H_ */
