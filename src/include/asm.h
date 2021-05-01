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
#pragma ide diagnostic ignored "UnusedValue"
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
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
};

__attribute__((always_inline)) static inline uint64_t __x64_bsrq(uint64_t value) {
    asm("bsrq %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline uint64_t __x64_bzhiq(uint64_t dst, uint64_t src, uint64_t index) {
    asm("bzhiq %0, %1, %2" : "=X" (dst) : "X" (src), "X" (index));
    return dst;
}

__attribute__((always_inline, cold)) static inline uint64_t __x64_cpuid_supported() {
    register uint32_t eax asm("eax");
    register uint32_t ebx asm("ebx");
    // from AMD instruction manual
    asm volatile (
    // rax = RFLAGS
    "pushfq\n"
    "popq %%rax\n"
    // flip bit 21 of eax
    "xorl $00200000, %%eax\n"
    // ebx = eax
    "movl %%eax, %%ebx\n"
    // RFLAGS = (stack[top] = rax)
    "pushq %%rax\n"
    "popfq\n"
    "pushfq\n"
    // rax = RFLAGS
    "popq %%rax\n":: : "cc"
    );
    // cpuid supported if rax is not rbx
    return eax != ebx;
}

__attribute__((always_inline, cold)) static inline struct cpuid_function_values __x64_cpuid(uint32_t function) {
    register uint32_t eax asm("eax");
    register uint32_t ebx asm("ebx");
    register uint32_t ecx asm("ecx");
    register uint32_t edx asm("edx");
    
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

__attribute__((always_inline)) static inline uint64_t __x64_lzcnt(uint64_t value) {
    asm("lzcntq %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline uint64_t __x64_popcnt(uint64_t value) {
    asm("popcntq %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline uint64_t __x64_tzcnt(uint64_t value) {
    asm("tzcntq %0, %0" : "+X" (value) : "X" (value));
    return value;
}

// FLAGS register info

// Convenience function to read rflags register
__attribute__((always_inline)) static inline uint64_t __x64_read_rflags() {
    register uint64_t rax asm("rax");
    asm volatile (
            "pushfq\n"
            "popq %%rax\n" ::: "cc"
            );
    return rax;
}

// Convenience function to write rflags register
__attribute__((always_inline)) static inline void __x64_write_rflags(uint64_t value) {
    asm volatile (
            "push %0\n"
            "popfq\n"
            :
            : "X" (value)
            : "cc"
            );
}

/**********************************************************************************************************************
 *                                         Intel x86 (32-bit LP32 and ILP32)   										  *
 **********************************************************************************************************************/

__attribute__((always_inline)) static inline uint32_t __x86_bsrl(uint32_t value) {
    asm("bsrl %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline uint32_t __x86_bzhil(uint32_t dst, uint32_t src, uint32_t index) {
    asm("bzhil %0, %1, %2" : "=X" (dst) : "X" (src), "X" (index));
    return dst;
}

__attribute__((always_inline, cold)) static inline uint32_t __x86_cpuid_supported() {
    register uint32_t eax asm("eax");
    register uint32_t ebx asm("ebx");
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
    "pop %%eax\n" ::: "cc"
    );
    // cpuid supported if eax is not ebx
    return eax != ebx;
}

__attribute__((always_inline, cold)) static inline struct cpuid_function_values __x86_cpuid(uint32_t function) {
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

__attribute__((always_inline)) static inline uint32_t __x86_lzcnt(uint32_t value) {
    asm("lzcntl %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline uint32_t __x86_popcnt(uint32_t value) {
    asm("popcntl %0, %0" : "+X" (value) : "X" (value));
    return value;
}

__attribute__((always_inline)) static inline uint32_t __x86_tzcnt(uint32_t value) {
    asm("tzcntl %0, %0" : "+X" (value) : "X" (value));
    return value;
}

// FLAGS register info

// Convenience function to read rflags register
__attribute__((always_inline)) static inline uint32_t __x86_read_eflags() {
    register uint32_t eax asm("eax");
    asm volatile (
    "pushfd\n"
    "pop %%eax\n" ::: "cc"
    );
    return eax;
}

// Convenience function to write rflags register
__attribute__((always_inline)) static inline void __x86_write_eflags(uint32_t value) {
    asm volatile (
    "push %0\n"
    "popfd\n"
    :
    : "X" (value)
    : "cc"
    );
}

#endif //PROJECT_AQUINAS_ASM_H

#pragma clang diagnostic pop
#pragma GCC diagnostic pop