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

__attribute__((always_inline)) static inline unsigned long long __x64_bsrl(register unsigned long long volatile value) {
    asm("bsrq %0, %0" : "=r" (value) : "r" (value));
    return value;
}

struct x86_cache_topology {
    alignas(__BIGGEST_ALIGNMENT__)
    unsigned char pad0;
    // 2 bytes
    unsigned short NumSharingCache:12;
    unsigned short FullyAssociative:1;
    unsigned short SelfInitialization:1;
    unsigned short CacheInclusive:1;
    unsigned short WBINVD:1;
    // 1 byte
    unsigned char CacheLevel:3;
    unsigned char CacheType:5;
    // 4 bytes
    unsigned int CacheNumWays:10;
    unsigned int CachePhysPartitions:10;
    unsigned int CacheLineSize:12;
    // 4 bytes
    unsigned int CacheNumSets;
};

struct x86_cpuid_info {
    alignas(__BIGGEST_ALIGNMENT__)
    unsigned int LFuncStd;
    char Vendor[13];

    unsigned int LFuncExt;
    unsigned short ExtFamily;
    unsigned short ExtModel:4;
    unsigned short BaseFamily:4;
    unsigned short BaseModel:4;
    unsigned short Stepping:4;

    unsigned char LocalApicId;
    unsigned char LogicalProcessorCount;
    unsigned char CLFlush;
    unsigned char _8BitBrandId;

    unsigned short RDRAND:1;
    unsigned short F16C:1;
    unsigned short AVX:1;
    unsigned short OSXSAVE:1;
    unsigned short XSAVE:1;
    unsigned short AES:1;
    unsigned short POPCNT:1;
    unsigned short MOVBE:1;
    unsigned short SSE42:1;
    unsigned short SSE41:1;
    unsigned short CMPXCHG16B:1;
    unsigned short FMA:1;
    unsigned short SSSE3:1;
    unsigned short MONITOR:1;
    unsigned short PCLMULQDQ:1;
    unsigned short SSE3:1;

    unsigned int HTT:1;
    unsigned int SSE2:1;
    unsigned int SSE:1;
    unsigned int FXSR:1;
    unsigned int MMX:1;
    unsigned int CLFSH:1;
    unsigned int PSE36:1;
    unsigned int PAT:1;
    unsigned int CMOV:1;
    unsigned int MCA:1;
    unsigned int PGE:1;
    unsigned int MTRR:1;
    unsigned int SysEnterSysExit:1;
    unsigned int APIC:1;
    unsigned int CMPXCHG8B:1;
    unsigned int MCE:1;
    unsigned int PAE:1;
    unsigned int MSR:1;
    unsigned int TSC:1;
    unsigned int PSE:1;
    unsigned int DE:1;
    unsigned int VME:1;
    unsigned int FPU:1;

    unsigned short MonLineSizeMin;
    unsigned short MonLineSizeMax;
    unsigned char IBE:1;
    unsigned char EMX:1;
    // Fn0000_0006
    unsigned char ARAT:1;
    unsigned char EffFreq:1;
    // Fn0000_0007
    unsigned int MaxSubFn;
    unsigned short SHA:1;
    unsigned short CLWB:1;
    unsigned short CLFLUSHOPT:1;
    unsigned short RDPID:1;
    unsigned short SMAP:1;
    unsigned short ADX:1;
    unsigned short RDSEED:1;
    unsigned short BMI2:1;
    unsigned short SMEP:1;
    unsigned short AVX2:1;
    unsigned short BMI1:1;
    unsigned short UMIP:1;
    unsigned short FSGSBASE:1;
    unsigned short VPCMULQDQ:1;
    unsigned short VAES:1;
    unsigned char OSPKE:1;
    unsigned char PKU:1;
    // Fn0000_000D_x0
    unsigned long long XFeatureSupportedMaskH:32;
    unsigned long long XFeatureSupportedMaskL:32;
    unsigned int XFeatureEnabledSizeMax;
    unsigned int XFeatureSupportedSizeMax;
    // Fn0000_000D_x1
    unsigned char XSAVEOPT:1;
    // Fn0000_000D_x2
    unsigned int YmmSaveStateSize;
    unsigned int YmmSaveStateOffset;
    // Fn0000_000D_x3E
    unsigned int LwpSaveStateSize;
    unsigned int LwpSaveStateOffset;

    // Fn8000_0001
    unsigned char PkgType;
    unsigned short BrandId;

    unsigned char PerfTsc:1;
    unsigned char DataBreakpointExtension:1;
    unsigned char PerfCtrExtNB:1;
    unsigned char PerfCtrExtCore:1;
    unsigned char TopologyExtensions:1;
    unsigned char TBM:1;
    unsigned char FMA4:1;
    unsigned char LWP:1;
    unsigned char WDT:1;
    unsigned char SKINIT:1;
    unsigned char XOP:1;
    unsigned char IBS:1;
    unsigned char OSVW:1;
    unsigned char _3DNowPrefetch:1;
    unsigned char MisAlignSse:1;
    unsigned char SSE4A:1;
    unsigned char ABM:1;
    unsigned char AltMovCr8:1;
    unsigned char ExtApicSpace:1;
    unsigned char SVM:1;
    unsigned char CmpLegacy:1;
    unsigned char LahfSahf:1;

    unsigned char _3DNow:1;
    unsigned char _3DNowExt:1;
    unsigned char LM:1;
    unsigned char RDTSCP:1;
    unsigned char Page1GB:1;
    unsigned char FFXSR:1;
    unsigned char MmxExt:1;
    unsigned char NX:1;
    unsigned char SysCallSysRet:1;

    unsigned char ProcName[48];

    unsigned char L1DTlb2and4MAssoc;
    unsigned char L1DTlb2and4MSize;
    unsigned char L1ITlb2and4MAssoc;
    unsigned char L1ITlb2and4MSize;

    unsigned char L1DTlb4KAssoc;
    unsigned char L1DTlb4KSize;
    unsigned char L1ITlb4KAssoc;
    unsigned char L1ITlb4KSize;

    unsigned char L1DcSize;
    unsigned char L1DcAssoc;
    unsigned char L1DcLinesPerTag;
    unsigned char L1DcLineSize;

    unsigned char L1IcSize;
    unsigned char L1IcAssoc;
    unsigned char L1IcLinesPerTag;
    unsigned char L1IcLineSize;

    unsigned char L2DTlb2and4MAssoc:4;
    unsigned char L2ITlb2and4MAssoc:4;
    unsigned char L2DTlb2and4MSize;
    unsigned char L2ITlb2and4MSize;

    unsigned char L2DTlb4KAssoc:4;
    unsigned char L2ITlb4KAssoc:4;
    unsigned char L2DTlb4KSize;
    unsigned char L2ITlb4KSize;

    unsigned short L2Size;
    unsigned char L2Assoc:4;
    unsigned char L2LinesPerTag:4;
    unsigned char L2LineSize;

    unsigned short L3Size;
    unsigned char L3Assoc:4;
    unsigned char L3LinesPerTag:4;
    unsigned char L3LineSize;

    unsigned short SUCCOR:1;
    unsigned short McaOverflowRecov:1;
    unsigned short CpuPwrSampleTimeRatio:1;
    unsigned short ProcPowerReporting:1;
    unsigned short ProcFeedbackInterface:1;
    unsigned short EffFreqRO:1;
    unsigned short CPB:1;
    unsigned short TscInvariant:1;
    unsigned short HwPstate:1;
    unsigned short _100MHzSteps:1;
    unsigned short TM:1;
    unsigned short TTP:1;
    unsigned short VID:1;
    unsigned short FID:1;
    unsigned short TS:1;

    unsigned char GuestPhysAddrSize;
    unsigned char LinAddrSize;
    unsigned char PhysAddrSize;

    unsigned char WBNOINVD:1;
    unsigned char MCOMMIT:1;
    unsigned char RDPRU:1;
    unsigned char RstrFpErrPtrs:1;
    unsigned char InstRetCntMsr:1;
    unsigned char CLZERO:1;

    unsigned char PerfTscSize:2;
    unsigned char ApicidSize:4;
    unsigned char NC;
    unsigned short MaxRdpruID;

    unsigned char SvmRev;
    unsigned int NASID;

    unsigned short TlbiCtl:1;
    unsigned short SpecCtrl:1;
    unsigned short GMET:1;
    unsigned short VGIF:1;
    unsigned short VMSAVEvirt:1;
    unsigned short AVIC:1;
    unsigned short PauseFilterThreshold:1;
    unsigned short PauseFilter:1;
    unsigned short DecodeAssists:1;
    unsigned short FlushByAsid:1;
    unsigned short VmcbClean:1;
    unsigned short TscRateMsr:1;
    unsigned short NRIPS:1;
    unsigned short SVML:1;
    unsigned short LbrVirt:1;
    unsigned short NP:1;

    unsigned short L1DTlb1GAssoc:4;
    unsigned short L1DTlb1GSize:12;
    unsigned short L1ITlb1GAssoc:4;
    unsigned short L1ITlb1GSize:12;

    unsigned short L2DTlb1GAssoc:4;
    unsigned short L2DTlb1GSize:12;
    unsigned short L2ITlb1GAssoc:4;
    unsigned short L2ITlb1GSize:12;

    unsigned char FP256:1;
    unsigned char MOVU:1;
    unsigned char FP128:1;

    unsigned char OpBrnFuse:1;
    unsigned char RipInvalidChk:1;
    unsigned char OpCntExt:1;
    unsigned char BrnTrgt:1;
    unsigned char OpCnt:1;
    unsigned char RdWrOpCnt:1;
    unsigned char OpSam:1;
    unsigned char FetchSam:1;
    unsigned char IBSFFV:1;

    unsigned char LwpInt:1;
    unsigned char LwpPTSC:1;
    unsigned char LwpCont:1;
    unsigned char LwpRNH:1;
    unsigned char LwpCNH:1;
    unsigned char LwpDME:1;
    unsigned char LwpBRE:1;
    unsigned char LwpIRE:1;
    unsigned char LwpVAL:1;
    unsigned char LwpAvail:1;

    unsigned char LwpEventOffset:1;
    unsigned char LwpMaxEvents:1;
    unsigned char LwpEventSize:1;
    unsigned char LwpCbSize:1;

    unsigned char LwpCacheLatency:1;
    unsigned char LwpCacheLevels:1;
    unsigned char LwpIpFiltering:1;
    unsigned char LwpBranchPrediction:1;
    unsigned char LwpMinBufferSize;
    unsigned char LwpVersion:7;
    unsigned char LwpLatencyRnd:3;
    unsigned char LwpDataAddress:1;
    unsigned char LwpLatencyMax:4;

    unsigned int cache_topologies;

    struct x86_cache_topology cache_topology[4];

    unsigned int ExtendedApicId;

    unsigned char ThreadsPerComputeUnit;
    unsigned char ComputeUnitId;

    unsigned char NodeId;
    unsigned short NodesPerProcessor:3;
    unsigned short PreventHostIbs:1;
    unsigned short DebugSwap:1;
    unsigned short AlternateInjection:1;
    unsigned short RestrictedInjection:1;
    unsigned short _64BitHost:1;
    unsigned short HwEnfCacheCoh:1;
    unsigned short VMPL:1;
    unsigned short SEV_SNP:1;
    unsigned short SEV_ES:1;
    unsigned short PageFlushMsr:1;
    unsigned short SEV:1;
    unsigned short SME:1;

    unsigned short NumVMPL:4;
    unsigned short PhysAddrReduction:6;
    unsigned short CbitPosition:6;

    unsigned int NumEncryptedGuests;

    unsigned int MinSevNoEsAsid;
};

__attribute__((always_inline, cold)) static inline unsigned long long __x64_cpuid_supported() {
    register unsigned int eax asm("eax");
    register unsigned int ebx asm("ebx");
    // from AMD instruction manual
    asm volatile (
    // rax = RFLAGS
    "pushfq\n"
    "pop %rax\n"
    // flip bit 21 of eax
    "xorl $00200000, %eax\n"
    // ebx = eax
    "movl %eax, %ebx\n"
    // RFLAGS = (stack[top] = rax)
    "push %rax\n"
    "popfq\n"
    "pushfq\n"
    // eax = EFLAGS
    "pop %rax\n"
    );
    // cpuid supported if rax is not rbx
    return eax != ebx;
}

/*
 * Collates the output of every functional execution of CPUID on the native x86(_64) CPU.
 * If for some reason the rax register is corrupted during execution of this (inline) function
 * (e.g. due to CPU instability, or radiation), then the function returns the x86_cpuid_info
 * struct in whatever state it was left in before it encountered an invalid function.
 *
 * This manner of error handling is done to allow the user to decide what should be done, and
 * whether or not the currently executing system should terminate or attempt to recover.
 *
 * This function in particular returns a pointer to a heap-allocated struct x86_cpuid_info.
 */
__attribute__((always_inline, cold)) static inline struct x86_cpuid_info *__x86_x64_cpuid() {
    register unsigned int eax asm("eax");
    register unsigned int ebx asm("ebx");
    register unsigned int ecx asm("ecx");
    register unsigned int edx asm("edx");
    // initialize cpuid_info on heap
    struct x86_cpuid_info *cpuid_info = calloc(1u, sizeof(*cpuid_info));
    
    eax = 0x00000000u;
    asm volatile (
    "cpuid"
    : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
    : "r" (eax)
    );
    cpuid_info->LFuncStd = eax;
    // write vendor string
    cpuid_info->Vendor[0] = ebx & 0xFFu;
    cpuid_info->Vendor[1] = (ebx >> 8) & 0xFFu;
    cpuid_info->Vendor[2] = (ebx >> 16) & 0xFFu;
    cpuid_info->Vendor[3] = (ebx >> 24) & 0xFFu;
    cpuid_info->Vendor[4] = edx & 0xFFu;
    cpuid_info->Vendor[5] = (edx >> 8) & 0xFFu;
    cpuid_info->Vendor[6] = (edx >> 16) & 0xFFu;
    cpuid_info->Vendor[7] = (edx >> 24) & 0xFFu;
    cpuid_info->Vendor[8] = ecx & 0xFFu;
    cpuid_info->Vendor[9] = (ecx >> 8) & 0xFFu;
    cpuid_info->Vendor[10] = (ecx >> 16) & 0xFFu;
    cpuid_info->Vendor[11] = (ecx >> 24) & 0xFFu;
    cpuid_info->Vendor[12] = '\0';

    // compute nearest CPUID function available
    if (eax >= 0x0Du)
        eax = 0x0Du;
    else if (eax >= 0x07u)
        eax = 0x07u;
    else if (eax >= 0x06u)
        eax = 0x06u;
    else if (eax >= 0x05u)
        eax = 0x05u;
    else if (eax >= 0x01u)
        eax = 0x01u;
    else if (!eax)
        return cpuid_info;

    switch (eax) {
        case 0x0000000D:
            eax = 0x0D;
            // 3E
            ecx = 0x3Eu;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax), "r"(ecx)
            );
            cpuid_info->LwpSaveStateSize = eax;
            cpuid_info->LwpSaveStateOffset = ebx;
            // 02
            ecx = 0x02u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax), "r"(ecx)
            );
            cpuid_info->YmmSaveStateSize = eax;
            cpuid_info->YmmSaveStateOffset = ebx;
            // 01
            ecx = 0x01u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax), "r"(ecx)
            );
            cpuid_info->XSAVEOPT = (eax & 1u);
            // 00
            ecx = 0x00u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax), "r"(ecx)
            );
            cpuid_info->XFeatureSupportedMaskH = edx;
            cpuid_info->XFeatureSupportedMaskL = eax;
            cpuid_info->XFeatureEnabledSizeMax = ebx;
            cpuid_info->XFeatureSupportedSizeMax = ecx;
        case 0x00000007:
            eax = 0x07u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->MaxSubFn = eax;

            cpuid_info->SHA = (ebx >> 29u) & 1u;
            cpuid_info->CLWB = (ebx >> 24u) & 1u;
            cpuid_info->CLFLUSHOPT = (ebx >> 23u) & 1u;
            cpuid_info->RDPID = (ebx >> 22u) & 1u;
            cpuid_info->SMAP = (ebx >> 20u) & 1u;
            cpuid_info->ADX = (ebx >> 19u) & 1u;
            cpuid_info->RDSEED = (ebx >> 18u) & 1u;
            cpuid_info->BMI2 = (ebx >> 8u) & 1u;
            cpuid_info->SMEP = (ebx >> 7u) & 1u;
            cpuid_info->AVX2 = (ebx >> 5u) & 1u;
            cpuid_info->BMI1 = (ebx >> 3u) & 1u;
            cpuid_info->UMIP = (ebx >> 2u) & 1u;
            cpuid_info->FSGSBASE = ebx & 1u;

            cpuid_info->VPCMULQDQ = (ecx >> 10u) & 1u;
            cpuid_info->VAES = (ecx >> 9u) & 1u;
            cpuid_info->OSPKE = (ecx >> 4u) & 1u;
            cpuid_info->PKU = (ecx >> 3u) & 1u;
        case 0x00000006:
            eax = 0x06u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->ARAT = (eax >> 2u) & 1u;
            cpuid_info->EffFreq = ecx & 1u;
        case 0x00000005:
            eax = 0x05u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->MonLineSizeMin = eax & 0xFFFFu;
            cpuid_info->MonLineSizeMax = ebx & 0xFFFFu;
            cpuid_info->IBE = (ecx >> 1u) & 1u;
            cpuid_info->EMX = ecx & 1u;
        case 0x00000001:
            eax = 0x01u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->ExtFamily = (eax >> 20u) & 0xFFu;
            cpuid_info->ExtModel = (eax >> 16u) & 0xFu;
            cpuid_info->BaseFamily = (eax >> 8u) & 0xFu;
            cpuid_info->BaseModel = (eax >> 4u) & 0xFu;
            cpuid_info->Stepping = eax & 0xFu;

            cpuid_info->LocalApicId = (ebx >> 24u) & 0xFFu;
            cpuid_info->LogicalProcessorCount = (ebx >> 16u) & 0xFFu;
            cpuid_info->CLFlush = (ebx >> 8u) & 0xFFu;
            cpuid_info->_8BitBrandId = ebx & 0xFFu;

            cpuid_info->RDRAND = (ecx >> 30u) & 1u;
            cpuid_info->F16C = (ecx >> 29u) & 1u;
            cpuid_info->AVX = (ecx >> 28u) & 1u;
            cpuid_info->OSXSAVE = (ecx >> 27u) & 1u;
            cpuid_info->XSAVE = (ecx >> 26u) & 1u;
            cpuid_info->AES = (ecx >> 25u) & 1u;
            cpuid_info->POPCNT = (ecx >> 23u) & 1u;
            cpuid_info->MOVBE = (ecx >> 22u) & 1u;
            cpuid_info->SSE42 = (ecx >> 20u) & 1u;
            cpuid_info->SSE41 = (ecx >> 19u) & 1u;
            cpuid_info->CMPXCHG16B = (ecx >> 13u) & 1u;
            cpuid_info->FMA = (ecx >> 12u) & 1u;
            cpuid_info->SSSE3 = (ecx >> 9u) & 1u;
            cpuid_info->MONITOR = (ecx >> 3u) & 1u;
            cpuid_info->PCLMULQDQ = (ecx >> 1u) & 1u;
            cpuid_info->SSE3 = ecx & 1u;

            cpuid_info->HTT = (edx >> 28u) & 1u;
            cpuid_info->SSE2 = (edx >> 26u) & 1u;
            cpuid_info->SSE = (edx >> 25u) & 1u;
            cpuid_info->FXSR = (edx >> 24u) & 1u;
            cpuid_info->MMX = (edx >> 23u) & 1u;
            cpuid_info->CLFSH = (edx >> 19u) & 1u;
            cpuid_info->PSE36 = (edx >> 17u) & 1u;
            cpuid_info->PAT = (edx >> 16u) & 1u;
            cpuid_info->CMOV = (edx >> 15u) & 1u;
            cpuid_info->MCA = (edx >> 14u) & 1u;
            cpuid_info->PGE = (edx >> 13u) & 1u;
            cpuid_info->MTRR = (edx >> 12u) & 1u;
            cpuid_info->SysEnterSysExit = (edx >> 11u) & 1u;
            cpuid_info->APIC = (edx >> 9u) & 1u;
            cpuid_info->CMPXCHG8B = (edx >> 8u) & 1u;
            cpuid_info->MCE = (edx >> 7u) & 1u;
            cpuid_info->PAE = (edx >> 6u) & 1u;
            cpuid_info->MSR = (edx >> 5u) & 1u;
            cpuid_info->TSC = (edx >> 4u) & 1u;
            cpuid_info->PSE = (edx >> 3u) & 1u;
            cpuid_info->DE = (edx >> 2u) & 1u;
            cpuid_info->VME = (edx >> 1u) & 1u;
            cpuid_info->FPU = edx & 1u;
        case 0x00000000:
            break;

        default:
            return cpuid_info;
    }

    // get largest extended function
    eax = 0x80000000u;
    asm volatile(
    "cpuid"
    : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
    : "r" (eax)
    );
    cpuid_info->LFuncExt = eax;

    // compute nearest CPUID function available
    if (eax >= 0x8000001Fu)
        eax = 0x8000001Fu;
    else if (eax >= 0x8000001Eu)
        eax = 0x8000001Eu;
    else if (eax >= 0x8000001Du)
        eax = 0x8000001Du;
    else if (eax >= 0x8000001Cu)
        eax = 0x8000001Cu;
    else if (eax >= 0x8000001Bu)
        eax = 0x8000001Bu;
    else if (eax >= 0x8000001Au)
        eax = 0x8000001Au;
    else if (eax >= 0x80000019u)
        eax = 0x80000019u;
    else if (eax >= 0x8000000Au)
        eax = 0x8000000Au;
    else if (eax >= 0x80000008u)
        eax = 0x80000008u;
    else if (eax >= 0x80000007u)
        eax = 0x80000007u;
    else if (eax >= 0x80000006u)
        eax = 0x80000006u;
    else if (eax >= 0x80000005u)
        eax = 0x80000005u;
    else if (eax >= 0x80000004u)
        eax = 0x80000004u;
    else if (eax >= 0x80000003u)
        eax = 0x80000003u;
    else if (eax >= 0x80000002u)
        eax = 0x80000002u;
    else if (eax >= 0x80000001u)
        eax = 0x80000001u;
    else if (eax == 0x80000000u)
        return cpuid_info;

    switch (eax) {
        case 0x8000001F:
            eax = 0x8000001Fu;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->PreventHostIbs = (eax >> 15u) & 1u;
            cpuid_info->DebugSwap = (eax >> 14u) & 1u;
            cpuid_info->AlternateInjection = (eax >> 13u) & 1u;
            cpuid_info->RestrictedInjection = (eax >> 12u) & 1u;
            cpuid_info->_64BitHost = (eax >> 11u) & 1u;
            cpuid_info->HwEnfCacheCoh = (eax >> 10u) & 1u;
            cpuid_info->VMPL = (eax >> 5u) & 1u;
            cpuid_info->SEV_SNP = (eax >> 4u) & 1u;
            cpuid_info->SEV_ES = (eax >> 3u) & 1u;
            cpuid_info->PageFlushMsr = (eax >> 2u) & 1u;
            cpuid_info->SEV = (eax >> 1u) & 1u;
            cpuid_info->SME = eax & 1u;

            cpuid_info->NumVMPL = (ebx >> 12u) & 0xFu;
            cpuid_info->PhysAddrReduction = (ebx >> 6u) & 0x3Fu;
            cpuid_info->CbitPosition = ebx & 0x3Fu;

            cpuid_info->NumEncryptedGuests = ecx;

            cpuid_info->MinSevNoEsAsid = edx;

        case 0x8000001E:
            // first check if 0x8000001E is reserved before continuing
            eax = 0x80000001;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            // if TopologyExtensions is zero, skip this function of CPUID
            if (!((ecx >> 22u) & 1u)) goto end_0x8000001E;
            eax = 0x8000001Eu;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->ExtendedApicId = eax;

            cpuid_info->ThreadsPerComputeUnit = (ebx >> 8u) & 0xFFu;
            cpuid_info->ComputeUnitId = ebx & 0xFFu;

            cpuid_info->NodesPerProcessor = (ecx >> 8u) & 0x7f;
            cpuid_info->NodeId = ecx & 0xFFu;
        end_0x8000001E:
        case 0x8000001D:
            // first check if 0x8000001D is reserved before continuing
            eax = 0x80000001;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            // if TopologyExtensions is zero, skip this function of CPUID
            if (!((ecx >> 22u) & 1u)) goto end_0x8000001D;

            volatile unsigned int cache_counter = 0u;
        get_cache_topology:
        {
            // put the value of cache_counter int ecx
            // get topology data
            eax = 0x8000001Du;
            ecx = cache_counter;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );

            // if CacheType is not zero, write cache data and loop
            if (eax & 0x1Fu) {
                cpuid_info->cache_topology[cache_counter].NumSharingCache = (eax >> 14u) & 0xFFFu;
                cpuid_info->cache_topology[cache_counter].FullyAssociative = (eax >> 9u) & 1u;
                cpuid_info->cache_topology[cache_counter].SelfInitialization = (eax >> 8u) & 1u;
                cpuid_info->cache_topology[cache_counter].CacheLevel = (eax >> 5u) & 0x7u;
                cpuid_info->cache_topology[cache_counter].CacheType = eax & 0x1Fu;

                cpuid_info->cache_topology[cache_counter].CacheNumWays = (ebx >> 22u) & 0x3FFu;
                cpuid_info->cache_topology[cache_counter].CachePhysPartitions = (ebx >> 12u) & 0x3FFu;
                cpuid_info->cache_topology[cache_counter].CacheLineSize = ebx & 0xFFFu;

                cpuid_info->cache_topology[cache_counter].CacheNumSets = ecx;

                cpuid_info->cache_topology[cache_counter].CacheInclusive = (edx >> 1u) & 1u;
                cpuid_info->cache_topology[cache_counter].WBINVD = edx & 1u;

                // increment cache_counter
                cache_counter++;
                goto get_cache_topology;
            }
        }
        // set cache_topologies to the number of cache_counter values
        cpuid_info->cache_topologies = cache_counter;
        end_0x8000001D:
        case 0x8000001C:
            eax = 0x8000001Cu;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->LwpInt = (eax >> 31u) & 1u;
            cpuid_info->LwpPTSC = (eax >> 30u) & 1u;
            cpuid_info->LwpCont = (eax >> 29u) & 1u;
            cpuid_info->LwpRNH = (eax >> 6u) & 1u;
            cpuid_info->LwpCNH = (eax >> 5u) & 1u;
            cpuid_info->LwpDME = (eax >> 4u) & 1u;
            cpuid_info->LwpBRE = (eax >> 3u) & 1u;
            cpuid_info->LwpIRE = (eax >> 2u) & 1u;
            cpuid_info->LwpVAL = (eax >> 1u) & 1u;
            cpuid_info->LwpAvail = eax & 1u;

            cpuid_info->LwpEventOffset = (ebx >> 24u) & 0xFFu;
            cpuid_info->LwpMaxEvents = (eax >> 16u) & 0xFFu;
            cpuid_info->LwpEventSize = (eax >> 8u) & 0xFFu;
            cpuid_info->LwpCbSize = eax & 0xFFu;

            cpuid_info->LwpCacheLatency = (ecx >> 31u) & 1u;
            cpuid_info->LwpCacheLevels = (ecx >> 30u) & 1u;
            cpuid_info->LwpIpFiltering = (ecx >> 29u) & 1u;
            cpuid_info->LwpBranchPrediction = (ecx >> 28u) & 1u;
            cpuid_info->LwpMinBufferSize = (ecx >> 16u) & 0xFFu;
            cpuid_info->LwpVersion = (ecx >> 9u) & 0x7F;
            cpuid_info->LwpLatencyRnd = (ecx >> 6u) & 0x7F;
            cpuid_info->LwpDataAddress = (ecx >> 4u) & 1u;
            cpuid_info->LwpLatencyMax = ecx & 0xFu;
        case 0x8000001B:
            eax = 0x8000001Bu;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->OpBrnFuse = (eax >> 8u) & 1u;
            cpuid_info->RipInvalidChk = (eax >> 7u) & 1u;
            cpuid_info->OpCntExt = (eax >> 6u) & 1u;
            cpuid_info->BrnTrgt = (eax >> 5u) & 1u;
            cpuid_info->OpCnt = (eax >> 4u) & 1u;
            cpuid_info->RdWrOpCnt = (eax >> 3u) & 1u;
            cpuid_info->OpSam = (eax >> 2u) & 1u;
            cpuid_info->FetchSam = (eax >> 1u) & 1u;
            cpuid_info->IBSFFV = eax & 1u;
        case 0x8000001A:
            eax = 0x8000001Au;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->FP256 = (eax >> 2u) & 1u;
            cpuid_info->MOVU = (eax >> 1u) & 1u;
            cpuid_info->FP128 = eax & 1u;
        case 0x80000019:
            eax = 0x80000019u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->L1DTlb1GAssoc = (eax >> 28u) & 0xFFu;
            cpuid_info->L1DTlb1GSize = (eax >> 16u) & 0xFFFu;
            cpuid_info->L1ITlb1GAssoc = (eax >> 12u) & 0xFFu;
            cpuid_info->L1ITlb1GSize = eax & 0xFFFu;

            cpuid_info->L2DTlb1GAssoc = (ebx >> 28u) & 0xFFu;
            cpuid_info->L2DTlb1GSize = (ebx >> 16u) & 0xFFFu;
            cpuid_info->L2ITlb1GAssoc = (ebx >> 12u) & 0xFFu;
            cpuid_info->L2ITlb1GSize = ebx & 0xFFFu;
        case 0x8000000A:
            eax = 0x8000000Au;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->SvmRev = eax & 0xFFu;

            cpuid_info->NASID = ebx;

            cpuid_info->TlbiCtl = (edx >> 24u) & 1u;
            cpuid_info->SpecCtrl = (edx >> 20u) & 1u;
            cpuid_info->GMET = (edx >> 17u) & 1u;
            cpuid_info->VGIF = (edx >> 16u) & 1u;
            cpuid_info->VMSAVEvirt = (edx >> 15u) & 1u;
            cpuid_info->AVIC = (edx >> 13u) & 1u;
            cpuid_info->PauseFilterThreshold = (edx >> 12u) & 1u;
            cpuid_info->PauseFilter = (edx >> 10u) & 1u;
            cpuid_info->DecodeAssists = (edx >> 7u) & 1u;
            cpuid_info->FlushByAsid = (edx >> 6u) & 1u;
            cpuid_info->VmcbClean = (edx >> 5u) & 1u;
            cpuid_info->TscRateMsr = (edx >> 4u) & 1u;
            cpuid_info->NRIPS = (edx >> 3u) & 1u;
            cpuid_info->SVML = (edx >> 2u) & 1u;
            cpuid_info->LbrVirt = (edx >> 1u) & 1u;
            cpuid_info->NP = edx & 1u;
        case 0x80000008:
            eax = 0x80000008u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->GuestPhysAddrSize = (eax >> 16u) & 0xFFu;
            cpuid_info->LinAddrSize = (eax >> 8u) & 0xFFu;
            cpuid_info->PhysAddrSize = eax & 0xFFu;

            cpuid_info->WBNOINVD = (ebx >> 9u) & 1u;
            cpuid_info->MCOMMIT = (ebx >> 8u) & 1u;
            cpuid_info->RDPRU = (ebx >> 4u) & 1u;
            cpuid_info->RstrFpErrPtrs = (ebx >> 2u) & 1u;
            cpuid_info->InstRetCntMsr = (ebx >> 1u) & 1u;
            cpuid_info->CLZERO = ebx & 1u;

            cpuid_info->PerfTscSize = (ecx >> 16u) & 0x3u;
            cpuid_info->ApicidSize = (ecx >> 12u) & 0xFu;
            cpuid_info->NC = ecx & 0xFFu;

            cpuid_info->MaxRdpruID = (edx >> 16u) & 0xFFFFu;
        case 0x80000007:
            eax = 0x80000007u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->SUCCOR = (ebx >> 1u) & 1u;
            cpuid_info->McaOverflowRecov = ebx & 1u;

            cpuid_info->CpuPwrSampleTimeRatio = ecx & 1u;

            cpuid_info->ProcPowerReporting = (edx >> 12u) & 1u;
            cpuid_info->ProcFeedbackInterface = (edx >> 11u) & 1u;
            cpuid_info->EffFreqRO = (edx >> 10u) & 1u;
            cpuid_info->CPB = (edx >> 9u) & 1u;
            cpuid_info->TscInvariant = (edx >> 8u) & 1u;
            cpuid_info->HwPstate = (edx >> 7u) & 1u;
            cpuid_info->_100MHzSteps = (edx >> 6u) & 1u;
            cpuid_info->TM = (edx >> 4u) & 1u;
            cpuid_info->TTP = (edx >> 3u) & 1u;
            cpuid_info->VID = (edx >> 2u) & 1u;
            cpuid_info->FID = (edx >> 1u) & 1u;
            cpuid_info->TS = edx & 1u;
        case 0x80000006:
            eax = 0x80000006u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->L2DTlb2and4MAssoc = (eax >> 28u) & 0xFu;
            cpuid_info->L2DTlb2and4MSize = (eax >> 16u) & 0xFFFu;
            cpuid_info->L2ITlb2and4MAssoc = (eax >> 12u) & 0xFu;
            cpuid_info->L2ITlb2and4MSize = eax & 0xFFFu;

            cpuid_info->L2DTlb4KAssoc = (ebx >> 28u) & 0xFu;
            cpuid_info->L2DTlb4KSize = (ebx >> 16u) & 0xFFFu;
            cpuid_info->L2ITlb4KAssoc = (ebx >> 12u) & 0xFu;
            cpuid_info->L2ITlb4KSize = ebx & 0xFFFu;

            cpuid_info->L2Size = (ecx >> 16u) & 0xFFFFu;
            cpuid_info->L2Assoc = (ecx >> 12u) & 0xFu;
            cpuid_info->L2LinesPerTag = (ecx >> 8u) & 0xFu;
            cpuid_info->L2LineSize = ecx & 0xFFu;

            cpuid_info->L3Size = (edx >> 18u) & 0x3FFFu;
            cpuid_info->L3Assoc = (edx >> 12u) & 0xFu;
            cpuid_info->L3LinesPerTag = (edx >> 8u) & 0xFu;
            cpuid_info->L3LineSize = edx & 0xFFu;
        case 0x80000005:
            eax = 0x80000005u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->L1DTlb2and4MAssoc = (eax >> 24u) & 0xFFu;
            cpuid_info->L1DTlb2and4MSize = (eax >> 16u) & 0xFFu;
            cpuid_info->L1ITlb2and4MAssoc = (eax >> 8u) & 0xFFu;
            cpuid_info->L1ITlb2and4MSize = eax & 0xFFu;

            cpuid_info->L1DTlb4KAssoc = (ebx >> 24u) & 0xFFu;
            cpuid_info->L1DTlb4KSize = (ebx >> 16u) & 0xFFu;
            cpuid_info->L1ITlb4KAssoc = (ebx >> 8u) & 0xFFu;
            cpuid_info->L1ITlb4KSize = ebx & 0xFFu;

            cpuid_info->L1DcSize = (ecx >> 24u) & 0xFFu;
            cpuid_info->L1DcAssoc = (ecx >> 16u) & 0xFFu;
            cpuid_info->L1DcLinesPerTag = (ecx >> 8u) & 0xFFu;
            cpuid_info->L1DcLineSize = ecx & 0xFFu;

            cpuid_info->L1IcSize = (edx >> 24u) & 0xFFu;
            cpuid_info->L1IcAssoc = (edx >> 16u) & 0xFFu;
            cpuid_info->L1IcLinesPerTag = (edx >> 8u) & 0xFFu;
            cpuid_info->L1IcLineSize = edx & 0xFFu;
        case 0x80000004:
            eax = 0x80000004u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->ProcName[32] = eax & 0xFFu;
            cpuid_info->ProcName[33] = (eax >> 8u) & 0xFFu;
            cpuid_info->ProcName[34] = (eax >> 16u) & 0xFFu;
            cpuid_info->ProcName[35] = (eax >> 24u) & 0xFFu;

            cpuid_info->ProcName[36] = ebx & 0xFFu;
            cpuid_info->ProcName[37] = (ebx >> 8u) & 0xFFu;
            cpuid_info->ProcName[38] = (ebx >> 16u) & 0xFFu;
            cpuid_info->ProcName[39] = (ebx >> 24u) & 0xFFu;

            cpuid_info->ProcName[40] = ecx & 0xFFu;
            cpuid_info->ProcName[41] = (ecx >> 8u) & 0xFFu;
            cpuid_info->ProcName[42] = (ecx >> 16u) & 0xFFu;
            cpuid_info->ProcName[43] = (ecx >> 24u) & 0xFFu;

            cpuid_info->ProcName[44] = edx & 0xFFu;
            cpuid_info->ProcName[45] = (edx >> 8u) & 0xFFu;
            cpuid_info->ProcName[46] = (edx >> 16u) & 0xFFu;
            cpuid_info->ProcName[47] = (edx >> 24u) & 0xFFu;
        case 0x80000003:
            eax = 0x80000003u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->ProcName[16] = eax & 0xFFu;
            cpuid_info->ProcName[17] = (eax >> 8u) & 0xFFu;
            cpuid_info->ProcName[18] = (eax >> 16u) & 0xFFu;
            cpuid_info->ProcName[19] = (eax >> 24u) & 0xFFu;

            cpuid_info->ProcName[20] = ebx & 0xFFu;
            cpuid_info->ProcName[21] = (ebx >> 8u) & 0xFFu;
            cpuid_info->ProcName[22] = (ebx >> 16u) & 0xFFu;
            cpuid_info->ProcName[23] = (ebx >> 24u) & 0xFFu;

            cpuid_info->ProcName[24] = ecx & 0xFFu;
            cpuid_info->ProcName[25] = (ecx >> 8u) & 0xFFu;
            cpuid_info->ProcName[26] = (ecx >> 16u) & 0xFFu;
            cpuid_info->ProcName[27] = (ecx >> 24u) & 0xFFu;

            cpuid_info->ProcName[28] = edx & 0xFFu;
            cpuid_info->ProcName[29] = (edx >> 8u) & 0xFFu;
            cpuid_info->ProcName[30] = (edx >> 16u) & 0xFFu;
            cpuid_info->ProcName[31] = (edx >> 24u) & 0xFFu;
        case 0x80000002:
            eax = 0x80000002u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->ProcName[0] = eax & 0xFFu;
            cpuid_info->ProcName[1] = (eax >> 8u) & 0xFFu;
            cpuid_info->ProcName[2] = (eax >> 16u) & 0xFFu;
            cpuid_info->ProcName[3] = (eax >> 24u) & 0xFFu;

            cpuid_info->ProcName[4] = ebx & 0xFFu;
            cpuid_info->ProcName[5] = (ebx >> 8u) & 0xFFu;
            cpuid_info->ProcName[6] = (ebx >> 16u) & 0xFFu;
            cpuid_info->ProcName[7] = (ebx >> 24u) & 0xFFu;

            cpuid_info->ProcName[8] = ecx & 0xFFu;
            cpuid_info->ProcName[9] = (ecx >> 8u) & 0xFFu;
            cpuid_info->ProcName[10] = (ecx >> 16u) & 0xFFu;
            cpuid_info->ProcName[11] = (ecx >> 24u) & 0xFFu;

            cpuid_info->ProcName[12] = edx & 0xFFu;
            cpuid_info->ProcName[13] = (edx >> 8u) & 0xFFu;
            cpuid_info->ProcName[14] = (edx >> 16u) & 0xFFu;
            cpuid_info->ProcName[15] = (edx >> 24u) & 0xFFu;
        case 0x80000001:
            eax = 0x80000001u;
            asm volatile (
            "cpuid"
            : "+r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
            : "r" (eax)
            );
            cpuid_info->PkgType = (ebx >> 28u) & 0xFFu;
            cpuid_info->BrandId = ebx & 0xFFFFu;

            cpuid_info->PerfTsc = (ecx >> 27u) & 1u;
            cpuid_info->DataBreakpointExtension = (ecx >> 26u) & 1u;
            cpuid_info->PerfCtrExtNB = (ecx >> 24u) & 1u;
            cpuid_info->PerfCtrExtCore = (ecx >> 23u) & 1u;
            cpuid_info->TopologyExtensions = (ecx >> 22u) & 1u;
            cpuid_info->TBM = (ecx >> 21u) & 1u;
            cpuid_info->FMA4 = (ecx >> 16u) & 1u;
            cpuid_info->LWP = (ecx >> 15u) & 1u;
            cpuid_info->WDT = (ecx >> 13u) & 1u;
            cpuid_info->SKINIT = (ecx >> 12u) & 1u;
            cpuid_info->XOP = (ecx >> 11u) & 1u;
            cpuid_info->IBS = (ecx >> 10u) & 1u;
            cpuid_info->OSVW = (ecx >> 9u) & 1u;
            cpuid_info->_3DNowPrefetch = (ecx >> 8u) & 1u;
            cpuid_info->MisAlignSse = (ecx >> 7u) & 1u;
            cpuid_info->SSE4A = (ecx >> 6u) & 1u;
            cpuid_info->ABM = (ecx >> 5u) & 1u;
            cpuid_info->AltMovCr8 = (ecx >> 4u) & 1u;
            cpuid_info->ExtApicSpace = (ecx >> 3u) & 1u;
            cpuid_info->SVM = (ecx >> 2u) & 1u;
            cpuid_info->CmpLegacy = (ecx >> 1u) & 1u;
            cpuid_info->LahfSahf = ecx & 1u;

            cpuid_info->_3DNow = (edx >> 31u) & 1u;
            cpuid_info->_3DNowExt = (edx >> 30u) & 1u;
            cpuid_info->LM = (edx >> 29u) & 1u;
            cpuid_info->RDTSCP = (edx >> 27u) & 1u;
            cpuid_info->Page1GB = (edx >> 26u) & 1u;
            cpuid_info->FFXSR = (edx >> 25u) & 1u;
            cpuid_info->MmxExt = (edx >> 22u) & 1u;
            cpuid_info->NX = (edx >> 20u) & 1u;
            cpuid_info->SysCallSysRet = (edx >> 11u) & 1u;

            break;
        case 0x80000000:
        default:
            return cpuid_info;
    }

    return cpuid_info;
}

__attribute__((always_inline)) static inline struct x86_cpuid_info *__x64_cpuid() {
    return __x86_x64_cpuid();
}

__attribute__((always_inline)) static inline unsigned long __x64_lzcnt(register unsigned long volatile value) {
    asm("lzcntq %0, %0" : "=r" (value) : "r" (value));
    return value;
}

__attribute__((always_inline)) static inline unsigned long __x64_tzcnt(register unsigned long volatile value) {
    asm("tzcntq %0, %0" : "=r" (value) : "r" (value));
    return value;
}

/**********************************************************************************************************************
 *                                         Intel x86 (32-bit LP32 and ILP32)   										  *
 **********************************************************************************************************************/

__attribute__((always_inline)) static inline unsigned long __x86_bsrl(register unsigned long volatile value) {
    asm("bsrl %0, %0" : "=r" (value) : "r" (value));
    return value;
}

__attribute__((always_inline, cold)) static inline unsigned long long __x86_cpuid_supported() {
    register unsigned int eax asm("eax");
    register unsigned int ebx asm("ebx");
    // from AMD instruction manual
    asm volatile (
    // eax = EFLAGS
    "pushfd\n"
    "pop %eax\n"
    // flip bit 21 of eax
    "xorl $00200000, %eax\n"
    // ebx = eax
    "movl %eax, %ebx\n"
    // EFLAGS = (stack[top] = eax)
    "push %eax\n"
    "popfq\n"
    "pushfd\n"
    // eax = EFLAGS
    "pop %eax\n"
    );
    // cpuid supported if eax is not ebx
    return eax != ebx;
}

__attribute__((always_inline)) static inline struct x86_cpuid_info *__x86_cpuid() {
    return __x86_x64_cpuid();
}

__attribute__((always_inline)) static inline unsigned long __x86_lzcnt(register unsigned long volatile value) {
    asm("lzcntl %0, %0" : "=r" (value) : "r" (value));
    return value;
}

__attribute__((always_inline)) static inline unsigned long __x86_tzcnt(register unsigned long volatile value) {
    asm("tzcntl %0, %0" : "=r" (value) : "r" (value));
    return value;
}

#endif //PROJECT_AQUINAS_ASM_H

#pragma clang diagnostic pop
#pragma GCC diagnostic pop