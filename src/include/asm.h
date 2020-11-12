/*
 * Module: asm
 * File: asm.h
 * Created:
 * May 21, 2020
 * Author: Andrew Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2020 Christi Crucifixi, LLC. All rights reserved.
 *
 * License:
 * Codex Dominatio Publicus sub Leges
 * <https://github.com/ServiRegis/Licenses/blob/master/CODEX-DOMINATIO-PUBLICUS-SUB-LEGES.txt>
 */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "UnreachableCode"
#pragma clang diagnostic ignored "-Wuninitialized"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough="

#ifndef PROJECT_AQUINAS_ASM_H
    #define PROJECT_AQUINAS_ASM_H
    
    #include <malloc.h>
    #include <stdalign.h>
    #include "state.h"

/**********************************************************************************************************************
 *                                           AMD64 (x86_64 LP64 thru SILP64)										  *
 **********************************************************************************************************************/

struct cpuid_function_values {
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
};

__attribute__((always_inline)) static inline unsigned long long __x64_bsrq(unsigned long long value) {
    asm("bsrq %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline unsigned long long __x64_bzhiq(unsigned long long dst, unsigned long long src, unsigned long long index) {
    asm("bzhiq %0, %1, %2" : "=r" (dst) : "rm" (src), "r" (index));
    return dst;
}

__attribute__((always_inline, cold)) static inline unsigned long long __x64_cpuid_supported() {
    register unsigned int eax asm("eax");
    register unsigned int ebx asm("ebx");
    // from AMD instruction manual
    asm volatile (
    // rax = RFLAGS
    "pushfq\n"
    "pop %%rax\n"
    // flip bit 21 of eax
    "xorl $00200000, %%eax\n"
    // ebx = eax
    "movl %%eax, %%ebx\n"
    // RFLAGS = (stack[top] = rax)
    "push %%rax\n"
    "popfq\n"
    "pushfq\n"
    // rax = RFLAGS
    "pop %%rax\n":: : "cc"
    );
    // cpuid supported if rax is not rbx
    return eax != ebx;
}

__attribute__((always_inline, cold)) static inline struct cpuid_function_values __x64_cpuid(unsigned int function) {
    register unsigned int eax asm("eax");
    register unsigned int ebx asm("ebx");
    register unsigned int ecx asm("ecx");
    register unsigned int edx asm("edx");
    
    struct cpuid_function_values values;
    eax = function;
    asm volatile (
    "cpuid"
    : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
    : "r" (eax));
    values.eax = eax;
    values.ebx = ebx;
    values.ecx = ecx;
    values.edx = edx;
    
    return values;
}

__attribute__((always_inline)) static inline unsigned long __x64_lzcnt(unsigned long long value) {
    asm("lzcntq %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline unsigned long __x64_popcnt(unsigned long long value) {
    asm("popcntq %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline unsigned long __x64_tzcnt(unsigned long long value) {
    asm("tzcntq %0, %0" : "+X" (value) : "X" (value));
    return value;
}

/**********************************************************************************************************************
 *                                         Intel x86 (32-bit LP32 and ILP32)   										  *
 **********************************************************************************************************************/

__attribute__((always_inline)) static inline unsigned long __x86_bsrl(unsigned long value) {
    asm("bsrl %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline unsigned long __x86_bzhil(unsigned long dst, unsigned long src, unsigned long index) {
    asm("bzhil %0, %1, %2" : "=r" (dst) : "rm" (src), "r" (index));
    return dst;
}

__attribute__((always_inline, cold)) static inline unsigned long long __x86_cpuid_supported() {
    register unsigned int eax asm("eax");
    register unsigned int ebx asm("ebx");
    // from AMD instruction manual
    asm volatile (
    // eax = EFLAGS
    "pushfd\n"
    "pop %%eax\n"
    // flip bit 21 of eax
    "xorl $00200000, %%eax\n"
    // ebx = eax
    "movl %%eax, %%ebx\n"
    // EFLAGS = (stack[top] = eax)
    "push %%eax\n"
    "popfq\n"
    "pushfd\n"
    // eax = EFLAGS
    "pop %%eax\n":: :"cc"
    );
    // cpuid supported if eax is not ebx
    return eax != ebx;
}

__attribute__((always_inline, cold)) static inline struct cpuid_function_values __x86_cpuid(unsigned int function) {
    register unsigned int eax asm("eax");
    register unsigned int ebx asm("ebx");
    register unsigned int ecx asm("ecx");
    register unsigned int edx asm("edx");
    
    struct cpuid_function_values values;
    eax = function;
    asm volatile (
    "cpuid"
    : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
    : "r" (eax));
    values.eax = eax;
    values.ebx = ebx;
    values.ecx = ecx;
    values.edx = edx;
    
    return values;
}

__attribute__((always_inline)) static inline unsigned long __x86_lzcnt(unsigned long value) {
    asm("lzcntl %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline unsigned long __x86_popcnt(unsigned long value) {
    asm("popcntl %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline unsigned long __x86_tzcnt(unsigned long value) {
    asm("tzcntl %0, %0" : "+X" (value) : "X" (value));
    return value;
}

#endif //PROJECT_AQUINAS_ASM_H

#pragma clang diagnostic pop
#pragma GCC diagnostic pop