/*
 * Module: asm
 * File: asm.h
 * Created:
 * May 21, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 */

#ifndef PROJECT_AQUINAS_ASM_H
#define PROJECT_AQUINAS_ASM_H

/**********************************************************************************************************************
 *                                           AMD64 (x86_64 LP64 thru SILP64)										  *
 **********************************************************************************************************************/

static inline unsigned long long __x64_bsrl(register unsigned long long volatile value) {
	asm("bsrl %0, %0" : "=r" (value) : "r" (value));
	return value;
}

static inline unsigned long __x64_lzcnt(register unsigned long volatile value) {
	asm("lzcnt %0, %0" : "=r" (value) : "r" (value));
	return value;
}

/**********************************************************************************************************************
 *                                         Intel x86 (32-bit LP32 and ILP32)   										  *
 **********************************************************************************************************************/

static inline unsigned long __x86_bsrl(register unsigned long volatile value) {
	asm("bsrl %0, %0" : "=r" (value) : "r" (value));
	return value;
}

static inline unsigned long __x86_lzcnt(register unsigned long volatile value) {
	asm("lzcnt %0, %0" : "=r" (value) : "r" (value));
	return value;
}

#endif //PROJECT_AQUINAS_ASM_H
