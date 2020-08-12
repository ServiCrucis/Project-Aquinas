/*
 ============================================================================
 Name        : aquinas.c
 Author      : Andrew Porter (AMDG)
 Version     : 1.0
 Copyright   : See LICENSE.txt
 Description : Project Aquinas Meta-compiler
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <platform.h>

// make other libraries use our memory manager (overwrites free as well)
#define MEMORY_MALLOC_OVERWRITE false
// enable debug message printing
#define R_DEBUG true
// set memory unit to use dynamic allocations instead of a single static allocation
#define DYNAMIC_HEAP true

#include "state.h"
#include "compiler.h"
#include "bit_math.h"
#include "bit_trie.h"
#include "sigbits_map.h"
#include "memory.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

static void test_expi() {
    for (ubyte i = 0; i < 45; i++) {
        infof(__func__, "expi(%llu): %llu\n", i, expi(i));
    }
}

static void test_lni() {
    for (ubyte i = 0; i < 45; i++) {
        infof(__func__, "lni(%llu): %llu\n", expi(i), lni(expi(i)));
    }
}

static void test_log10i() {
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1ull, log10i(1ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10ull, log10i(10ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100ull, log10i(100ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000ull, log10i(1000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000ull, log10i(10000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000ull, log10i(100000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000ull, log10i(1000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000ull, log10i(10000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000ull, log10i(100000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000ull, log10i(1000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000ull, log10i(10000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000ull, log10i(100000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000ull, log10i(1000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000ull, log10i(10000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000ull, log10i(100000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000ull, log10i(1000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000ull, log10i(10000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000000ull, log10i(100000000000000000ul));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000000ull, log10i(1000000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000000ull, log10i(10000000000000000000ull));
}

static void test_sigbits() {
    for (uword i = 0; i < 256; i++) {
        infof(__func__, "sigbits(%llu): %llu\n", i, sigbits(i));
    }
}

static void test_digits() {
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1ull, digits(1ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10ull, digits(10ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100ull, digits(100ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000ull, digits(1000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000ull, digits(10000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000ull, digits(100000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000ull, digits(1000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000ull, digits(10000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000ull, digits(100000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000ull, digits(1000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000ull, digits(10000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000ull, digits(100000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000ull, digits(1000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000ull, digits(10000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000ull, digits(100000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000ull, digits(1000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000ull, digits(10000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 100000000000000000ull, digits(100000000000000000ul));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 1000000000000000000ull, digits(1000000000000000000ull));
    infof(__func__, "Digits: value=%llu, digits()=%llu\n", 10000000000000000000ull, digits(10000000000000000000ull));
}

static void test_to_digits() {
    uword value = UINT64_MAX;
    ubyte digits[20];
    for (ubyte i = 19; i < 20; i--) {
        digits[i] = get_digit10i(value, i);
        infof(__func__, "digit[%llu] = %llu\n", i, digits[i]);
    }
}

static void test_bittrie() {
    info(__func__, "Building bit_trie.\n");
    pair test[] = {
            {23,  1},
            {237, 1}
    };
    bit_trie *trie = btt_create(test, 8, 2);
    uword values = 256;
    // 0: left; 1: right
    uword side = 0ull;
    info(__func__, "bit_trie side:left.\n");
    for (uword address = 0; address < values; address++) {

        uword bit = btt_read(trie, (address << 1u) | side);
        infof(__func__, "[%u] = %u\n", bin_index((address << 1u) | side), bit);
    }

    info(__func__, "bit_trie side:right.\n");
    side = 1ull;
    for (uword address = 0; address < values; address++) {
        uword bit = btt_read(trie, (address << 1u) | side);
        infof(__func__, "[%u]\n", bin_index((address << 1u) | side), bit);
    }

    btt_free(trie);
    info(__func__, "Done.\n");
}

static void test_binary_trie() {
    binary_tree *btrie = binary_tree_create(31);

    for (uword i = 0; i < btrie->nodes; i++) {
        binary_tree_set(btrie, i, powni(i, i));
        infof(__func__, "binary_tree+%llu = %llu\n", i, binary_tree_get(btrie, i));
    }
}

static void test_map() {
    sigbits_map *map = sbm_create(bitwidth(ubyte));
    for (uword i = 0; i < 256; i++) {
        sbm_set(map, (pair) {i, rand()});
        infof(__func__, "map[%llu] = %llu\n", i, sbm_get(map, i) & 255);
    }
    // undefined behavior
    infof(__func__, "(undefined behavior test) map[257]: %llu\n", sbm_get(map, 257));

//    for (ubyte i = 0; i < bitwidth(uword); i++) {
//        uword value = map_get(map, i);
//        infof(__func__, "map[%llu] : %u\n", i, value);
//    }


}

static void test_cpuid() {
    if (!__x64_cpuid_supported()) fatalf(__func__, "Unable to initialize CPU info: CPUID instruction not supported");
    info(__func__, "CPUID is supported on this platform\n");
    struct x86_cpuid_info *cpu_info_ptr = __x64_cpuid();
    struct x86_cpuid_info cpu_info = *cpu_info_ptr;
    // 261 values + cache_topology=sizeof(struct x86_cache_topology) * LogicalProcessorCount
    infof(__func__, "Printing CPU info:\n");
    info(__func__, "\n");
    infof(__func__, "LFuncStd: %#x\n", cpu_info.LFuncStd);
    infof(__func__, "Vendor: %s\n", cpu_info.Vendor);
    infof(__func__, "LFuncExt: %#x\n", cpu_info.LFuncExt);
    infof(__func__, "ExtFamily: %u\n", cpu_info.ExtFamily);
    infof(__func__, "ExtModel: %u\n", cpu_info.ExtModel);
    infof(__func__, "BaseFamily: %u\n", cpu_info.BaseFamily);
    infof(__func__, "BaseModel: %u\n", cpu_info.BaseModel);
    infof(__func__, "Stepping: %u\n", cpu_info.Stepping);
    infof(__func__, "LocalApicId: %u\n", cpu_info.LocalApicId);
    infof(__func__, "LogicalProcessorCount: %u\n", cpu_info.LogicalProcessorCount);
    infof(__func__, "CLFlush: %u\n", cpu_info.CLFlush);
    infof(__func__, "_8BitBrandId: %u\n", cpu_info._8BitBrandId);
    infof(__func__, "RDRAND: %u\n", cpu_info.RDRAND);
    infof(__func__, "F16C: %u\n", cpu_info.F16C);
    infof(__func__, "AVX: %u\n", cpu_info.AVX);
    infof(__func__, "OSXSAVE: %u\n", cpu_info.OSXSAVE);
    infof(__func__, "XSAVE: %u\n", cpu_info.XSAVE);
    infof(__func__, "AES: %u\n", cpu_info.AES);
    infof(__func__, "POPCNT: %u\n", cpu_info.POPCNT);
    infof(__func__, "MOVBE: %u\n", cpu_info.MOVBE);
    infof(__func__, "SSE42: %u\n", cpu_info.SSE42);
    infof(__func__, "SSE41: %u\n", cpu_info.SSE41);
    infof(__func__, "CMPXCHG16B: %u\n", cpu_info.CMPXCHG16B);
    infof(__func__, "FMA: %u\n", cpu_info.FMA);
    infof(__func__, "SSSE3: %u\n", cpu_info.SSSE3);
    infof(__func__, "MONITOR: %u\n", cpu_info.MONITOR);
    infof(__func__, "PCLMULQDQ: %u\n", cpu_info.PCLMULQDQ);
    infof(__func__, "SSE3: %u\n", cpu_info.SSE3);
    infof(__func__, "HTT: %u\n", cpu_info.HTT);
    infof(__func__, "SSE2: %u\n", cpu_info.SSE2);
    infof(__func__, "SSE: %u\n", cpu_info.SSE);
    infof(__func__, "FXSR: %u\n", cpu_info.FXSR);
    infof(__func__, "MMX: %u\n", cpu_info.MMX);
    infof(__func__, "CLFSH: %u\n", cpu_info.CLFSH);
    infof(__func__, "PSE36: %u\n", cpu_info.PSE36);
    infof(__func__, "PAT: %u\n", cpu_info.PAT);
    infof(__func__, "CMOV: %u\n", cpu_info.CMOV);
    infof(__func__, "MCA: %u\n", cpu_info.MCA);
    infof(__func__, "PGE: %u\n", cpu_info.PGE);
    infof(__func__, "MTRR: %u\n", cpu_info.MTRR);
    infof(__func__, "SysEnterSysExit: %u\n", cpu_info.SysEnterSysExit);
    infof(__func__, "APIC: %u\n", cpu_info.APIC);
    infof(__func__, "CMPXCHG8B: %u\n", cpu_info.CMPXCHG8B);
    infof(__func__, "MCE: %u\n", cpu_info.MCE);
    infof(__func__, "PAE: %u\n", cpu_info.PAE);
    infof(__func__, "MSR: %u\n", cpu_info.MSR);
    infof(__func__, "TSC: %u\n", cpu_info.TSC);
    infof(__func__, "PSE: %u\n", cpu_info.PSE);
    infof(__func__, "DE: %u\n", cpu_info.DE);
    infof(__func__, "VME: %u\n", cpu_info.VME);
    infof(__func__, "FPU: %u\n", cpu_info.FPU);
    infof(__func__, "MonLineSizeMin: %u\n", cpu_info.MonLineSizeMin);
    infof(__func__, "MonLineSizeMax: %u\n", cpu_info.MonLineSizeMax);
    infof(__func__, "IBE: %u\n", cpu_info.IBE);
    infof(__func__, "EMX: %u\n", cpu_info.EMX);
    infof(__func__, "ARAT: %u\n", cpu_info.ARAT);
    infof(__func__, "EffFreq: %u\n", cpu_info.EffFreq);
    infof(__func__, "MaxSubFn: %u\n", cpu_info.MaxSubFn);
    infof(__func__, "SHA: %u\n", cpu_info.SHA);
    infof(__func__, "CLWB: %u\n", cpu_info.CLWB);
    infof(__func__, "CLFLUSHOPT: %u\n", cpu_info.CLFLUSHOPT);
    infof(__func__, "RDPID: %u\n", cpu_info.RDPID);
    infof(__func__, "SMAP: %u\n", cpu_info.SMAP);
    infof(__func__, "ADX: %u\n", cpu_info.ADX);
    infof(__func__, "RDSEED: %u\n", cpu_info.RDSEED);
    infof(__func__, "BMI2: %u\n", cpu_info.BMI2);
    infof(__func__, "SMEP: %u\n", cpu_info.SMEP);
    infof(__func__, "AVX2: %u\n", cpu_info.AVX2);
    infof(__func__, "BMI1: %u\n", cpu_info.BMI1);
    infof(__func__, "UMIP: %u\n", cpu_info.UMIP);
    infof(__func__, "FSGSBASE: %u\n", cpu_info.FSGSBASE);
    infof(__func__, "VPCMULQDQ: %u\n", cpu_info.VPCMULQDQ);
    infof(__func__, "VAES: %u\n", cpu_info.VAES);
    infof(__func__, "OSPKE: %u\n", cpu_info.OSPKE);
    infof(__func__, "PKU: %u\n", cpu_info.PKU);
    infof(__func__, "XFeatureSupportedMask (high bits): %u\n", cpu_info.XFeatureSupportedMaskH);
    infof(__func__, "XFeatureSupportedL (low bits): %u\n", cpu_info.XFeatureSupportedMaskL);
    infof(__func__, "XFeatureEnabledSizeMax: %u\n", cpu_info.XFeatureEnabledSizeMax);
    infof(__func__, "XFeatureSupportedSizeMax: %u\n", cpu_info.XFeatureSupportedSizeMax);
    infof(__func__, "XSAVEOPT: %u\n", cpu_info.XSAVEOPT);
    infof(__func__, "YmmSaveStateSize: %u\n", cpu_info.YmmSaveStateSize);
    infof(__func__, "YmmSaveStateOffset: %u\n", cpu_info.YmmSaveStateOffset);
    infof(__func__, "LwpSaveStateSize: %u\n", cpu_info.LwpSaveStateSize);
    infof(__func__, "LwpSaveStateOffset: %u\n", cpu_info.LwpSaveStateOffset);
    infof(__func__, "PkgType: %u\n", cpu_info.PkgType);
    infof(__func__, "BrandId: %u\n", cpu_info.BrandId);
    infof(__func__, "PerfTsc: %u\n", cpu_info.PerfTsc);
    infof(__func__, "DataBreakpointExtension: %u\n", cpu_info.DataBreakpointExtension);
    infof(__func__, "PerfCtrExtNB: %u\n", cpu_info.PerfCtrExtNB);
    infof(__func__, "PerfCtrExtCore: %u\n", cpu_info.PerfCtrExtCore);
    infof(__func__, "TopologyExtensions: %u\n", cpu_info.TopologyExtensions);
    infof(__func__, "TBM: %u\n", cpu_info.TBM);
    infof(__func__, "FMA4: %u\n", cpu_info.FMA4);
    infof(__func__, "LWP: %u\n", cpu_info.LWP);
    infof(__func__, "WDT: %u\n", cpu_info.WDT);
    infof(__func__, "SKINIT: %u\n", cpu_info.SKINIT);
    infof(__func__, "XOP: %u\n", cpu_info.XOP);
    infof(__func__, "IBS: %u\n", cpu_info.IBS);
    infof(__func__, "OSVW: %u\n", cpu_info.OSVW);
    infof(__func__, "_3DNowPrefetch: %u\n", cpu_info._3DNowPrefetch);
    infof(__func__, "MisAlignSse: %u\n", cpu_info.MisAlignSse);
    infof(__func__, "SSE4A: %u\n", cpu_info.SSE4A);
    infof(__func__, "ABM: %u\n", cpu_info.ABM);
    infof(__func__, "AltMovCr8: %u\n", cpu_info.AltMovCr8);
    infof(__func__, "ExtApicSpace: %u\n", cpu_info.ExtApicSpace);
    infof(__func__, "SVM: %u\n", cpu_info.SVM);
    infof(__func__, "CmpLegacy: %u\n", cpu_info.CmpLegacy);
    infof(__func__, "LahfSahf: %u\n", cpu_info.LahfSahf);
    infof(__func__, "_3DNow: %u\n", cpu_info._3DNow);
    infof(__func__, "_3DNowExt: %u\n", cpu_info._3DNowExt);
    infof(__func__, "LM: %u\n", cpu_info.LM);
    infof(__func__, "RDTSCP: %u\n", cpu_info.RDTSCP);
    infof(__func__, "Page1GB: %u\n", cpu_info.Page1GB);
    infof(__func__, "FFXSR: %u\n", cpu_info.FFXSR);
    infof(__func__, "MmxExt: %u\n", cpu_info.MmxExt);
    infof(__func__, "NX: %u\n", cpu_info.NX);
    infof(__func__, "SysCallSysRet: %u\n", cpu_info.SysCallSysRet);
    infof(__func__, "ProcName: %s\n", cpu_info.ProcName);
    infof(__func__, "L1DTlb2and4MAssoc: %u\n", cpu_info.L1DTlb2and4MAssoc);
    infof(__func__, "L1DTlb2and4MSize: %u\n", cpu_info.L1DTlb2and4MSize);
    infof(__func__, "L1ITlb2and4MAssoc: %u\n", cpu_info.L1ITlb2and4MAssoc);
    infof(__func__, "L1ITlb2and4MSize: %u\n", cpu_info.L1ITlb2and4MSize);
    infof(__func__, "L1DTlb4KAssoc: %u\n", cpu_info.L1DTlb4KAssoc);
    infof(__func__, "L1DTlb4KSize: %u\n", cpu_info.L1DTlb4KSize);
    infof(__func__, "L1ITlb4KAssoc: %u\n", cpu_info.L1ITlb4KAssoc);
    infof(__func__, "L1ITlb4KSize: %u\n", cpu_info.L1ITlb4KSize);
    infof(__func__, "L1DcSize: %u\n", cpu_info.L1DcSize);
    infof(__func__, "L1DcAssoc: %u\n", cpu_info.L1DcAssoc);
    infof(__func__, "L1DcLinesPerTag: %u\n", cpu_info.L1DcLinesPerTag);
    infof(__func__, "L1DcLineSize: %u\n", cpu_info.L1DcLineSize);
    infof(__func__, "L1IcSize: %u\n", cpu_info.L1IcSize);
    infof(__func__, "L1IcAssoc: %u\n", cpu_info.L1IcAssoc);
    infof(__func__, "L1IcLinesPerTag: %u\n", cpu_info.L1IcLinesPerTag);
    infof(__func__, "L1IcLineSize: %u\n", cpu_info.L1IcLineSize);
    infof(__func__, "L2DTlb2and4MAssoc: %u\n", cpu_info.L2DTlb2and4MAssoc);
    infof(__func__, "L2ITlb2and4MAssoc: %u\n", cpu_info.L2ITlb2and4MAssoc);
    infof(__func__, "L2DTlb2and4MSize: %u\n", cpu_info.L2DTlb2and4MSize);
    infof(__func__, "L2ITlb2and4MSize: %u\n", cpu_info.L2ITlb2and4MSize);
    infof(__func__, "L2DTlb4KAssoc: %u\n", cpu_info.L2DTlb4KAssoc);
    infof(__func__, "L2ITlb4KAssoc: %u\n", cpu_info.L2ITlb4KAssoc);
    infof(__func__, "L2DTlb4KSize: %u\n", cpu_info.L2DTlb4KSize);
    infof(__func__, "L2ITlb4KSize: %u\n", cpu_info.L2ITlb4KSize);
    infof(__func__, "L2Size: %u\n", cpu_info.L2Size);
    infof(__func__, "L2Assoc: %u\n", cpu_info.L2Assoc);
    infof(__func__, "L2LinesPerTag: %u\n", cpu_info.L2LinesPerTag);
    infof(__func__, "L2LineSize: %u\n", cpu_info.L2LineSize);
    infof(__func__, "L3Size: %u\n", cpu_info.L3Size);
    infof(__func__, "L3Assoc: %u\n", cpu_info.L3Assoc);
    infof(__func__, "L3LinesPerTag: %u\n", cpu_info.L3LinesPerTag);
    infof(__func__, "L3LineSize: %u\n", cpu_info.L3LineSize);
    infof(__func__, "SUCCOR: %u\n", cpu_info.SUCCOR);
    infof(__func__, "McaOverflowRecov: %u\n", cpu_info.McaOverflowRecov);
    infof(__func__, "CpuPwrSampleTimeRatio: %u\n", cpu_info.CpuPwrSampleTimeRatio);
    infof(__func__, "ProcPowerReporting: %u\n", cpu_info.ProcPowerReporting);
    infof(__func__, "ProcFeedbackInterface: %u\n", cpu_info.ProcFeedbackInterface);
    infof(__func__, "EffFreqRO: %u\n", cpu_info.EffFreqRO);
    infof(__func__, "CPB: %u\n", cpu_info.CPB);
    infof(__func__, "TscInvariant: %u\n", cpu_info.TscInvariant);
    infof(__func__, "HwPstate: %u\n", cpu_info.HwPstate);
    infof(__func__, "_100MHzSteps: %u\n", cpu_info._100MHzSteps);
    infof(__func__, "TM: %u\n", cpu_info.TM);
    infof(__func__, "TTP: %u\n", cpu_info.TTP);
    infof(__func__, "VID: %u\n", cpu_info.VID);
    infof(__func__, "FID: %u\n", cpu_info.FID);
    infof(__func__, "TS: %u\n", cpu_info.TS);
    infof(__func__, "GuestPhysAddrSize: %u\n", cpu_info.GuestPhysAddrSize);
    infof(__func__, "LinAddrSize: %u\n", cpu_info.LinAddrSize);
    infof(__func__, "PhysAddrSize: %u\n", cpu_info.PhysAddrSize);
    infof(__func__, "WBNOINVD: %u\n", cpu_info.WBNOINVD);
    infof(__func__, "MCOMMIT: %u\n", cpu_info.MCOMMIT);
    infof(__func__, "RDPRU: %u\n", cpu_info.RDPRU);
    infof(__func__, "RstrFpErrPtrs: %u\n", cpu_info.RstrFpErrPtrs);
    infof(__func__, "InstRetCntMsr: %u\n", cpu_info.InstRetCntMsr);
    infof(__func__, "CLZERO: %u\n", cpu_info.CLZERO);
    infof(__func__, "PerfTscSize: %u\n", cpu_info.PerfTscSize);
    infof(__func__, "ApicidSize: %u\n", cpu_info.ApicidSize);
    infof(__func__, "NC: %u\n", cpu_info.NC);
    infof(__func__, "MaxRdpruID: %u\n", cpu_info.MaxRdpruID);
    infof(__func__, "SvmRev: %u\n", cpu_info.SvmRev);
    infof(__func__, "NASID: %u\n", cpu_info.NASID);
    infof(__func__, "TlbiCtl: %u\n", cpu_info.TlbiCtl);
    infof(__func__, "SpecCtrl: %u\n", cpu_info.SpecCtrl);
    infof(__func__, "GMET: %u\n", cpu_info.GMET);
    infof(__func__, "VGIF: %u\n", cpu_info.VGIF);
    infof(__func__, "VMSAVEvirt: %u\n", cpu_info.VMSAVEvirt);
    infof(__func__, "AVIC: %u\n", cpu_info.AVIC);
    infof(__func__, "PauseFilterThreshold: %u\n", cpu_info.PauseFilterThreshold);
    infof(__func__, "PauseFilter: %u\n", cpu_info.PauseFilter);
    infof(__func__, "DecodeAssists: %u\n", cpu_info.DecodeAssists);
    infof(__func__, "FlushByAsid: %u\n", cpu_info.FlushByAsid);
    infof(__func__, "VmcbClean: %u\n", cpu_info.VmcbClean);
    infof(__func__, "TscRateMsr: %u\n", cpu_info.TscRateMsr);
    infof(__func__, "NRIPS: %u\n", cpu_info.NRIPS);
    infof(__func__, "SVML: %u\n", cpu_info.SVML);
    infof(__func__, "LbrVirt: %u\n", cpu_info.LbrVirt);
    infof(__func__, "NP: %u\n", cpu_info.NP);
    infof(__func__, "L1DTlb1GAssoc: %u\n", cpu_info.L1DTlb1GAssoc);
    infof(__func__, "L1DTlb1GSize: %u\n", cpu_info.L1DTlb1GSize);
    infof(__func__, "L1ITlb1GAssoc: %u\n", cpu_info.L1ITlb1GAssoc);
    infof(__func__, "L1ITlb1GSize: %u\n", cpu_info.L1ITlb1GSize);
    infof(__func__, "L2DTlb1GAssoc: %u\n", cpu_info.L2DTlb1GAssoc);
    infof(__func__, "L2DTlb1GSize: %u\n", cpu_info.L2DTlb1GSize);
    infof(__func__, "L2ITlb1GAssoc: %u\n", cpu_info.L2ITlb1GAssoc);
    infof(__func__, "L2ITlb1GSize: %u\n", cpu_info.L2ITlb1GSize);
    infof(__func__, "FP256: %u\n", cpu_info.FP256);
    infof(__func__, "MOVU: %u\n", cpu_info.MOVU);
    infof(__func__, "FP128: %u\n", cpu_info.FP128);
    infof(__func__, "OpBrnFuse: %u\n", cpu_info.OpBrnFuse);
    infof(__func__, "RipInvalidChk: %u\n", cpu_info.RipInvalidChk);
    infof(__func__, "OpCntExt: %u\n", cpu_info.OpCntExt);
    infof(__func__, "BrnTrgt: %u\n", cpu_info.BrnTrgt);
    infof(__func__, "OpCnt: %u\n", cpu_info.OpCnt);
    infof(__func__, "RdWrOpCnt: %u\n", cpu_info.RdWrOpCnt);
    infof(__func__, "OpSam: %u\n", cpu_info.OpSam);
    infof(__func__, "FetchSam: %u\n", cpu_info.FetchSam);
    infof(__func__, "IBSFFV: %u\n", cpu_info.IBSFFV);
    infof(__func__, "LwpInt: %u\n", cpu_info.LwpInt);
    infof(__func__, "LwpPTSC: %u\n", cpu_info.LwpPTSC);
    infof(__func__, "LwpCont: %u\n", cpu_info.LwpCont);
    infof(__func__, "LwpRNH: %u\n", cpu_info.LwpRNH);
    infof(__func__, "LwpCNH: %u\n", cpu_info.LwpCNH);
    infof(__func__, "LwpDME: %u\n", cpu_info.LwpDME);
    infof(__func__, "LwpBRE: %u\n", cpu_info.LwpBRE);
    infof(__func__, "LwpIRE: %u\n", cpu_info.LwpIRE);
    infof(__func__, "LwpVAL: %u\n", cpu_info.LwpVAL);
    infof(__func__, "LwpAvail: %u\n", cpu_info.LwpAvail);
    infof(__func__, "LwpEventOffset: %u\n", cpu_info.LwpEventOffset);
    infof(__func__, "LwpMaxEvents: %u\n", cpu_info.LwpMaxEvents);
    infof(__func__, "LwpEventSize: %u\n", cpu_info.LwpEventSize);
    infof(__func__, "LwpCbSize: %u\n", cpu_info.LwpCbSize);
    infof(__func__, "LwpCacheLatency: %u\n", cpu_info.LwpCacheLatency);
    infof(__func__, "LwpCacheLevels: %u\n", cpu_info.LwpCacheLevels);
    infof(__func__, "LwpIpFiltering: %u\n", cpu_info.LwpIpFiltering);
    infof(__func__, "LwpMinBufferSize: %u\n", cpu_info.LwpMinBufferSize);
    infof(__func__, "LwpVersion: %u\n", cpu_info.LwpVersion);
    infof(__func__, "LwpLatencyRnd: %u\n", cpu_info.LwpLatencyRnd);
    infof(__func__, "LwpDataAddress: %u\n", cpu_info.LwpDataAddress);
    infof(__func__, "LwpLatencyMax: %u\n", cpu_info.LwpLatencyMax);
    for (uword i = 0; i < cpu_info.cache_topologies; i++) {
        infof(__func__, "\n");
        infof(__func__, "cache_topology[%u]:\n", i);
        infof(__func__, "\tNumSharingCache: %u\n", cpu_info.cache_topology[i].NumSharingCache);
        infof(__func__, "\tFullyAssociative: %u\n", cpu_info.cache_topology[i].FullyAssociative);
        infof(__func__, "\tSelfInitialization: %u\n", cpu_info.cache_topology[i].SelfInitialization);
        infof(__func__, "\tCacheInclusive: %u\n", cpu_info.cache_topology[i].CacheInclusive);
        infof(__func__, "\tWBINVD: %u\n", cpu_info.cache_topology[i].WBINVD);
        infof(__func__, "\tCacheLevel: %u\n", cpu_info.cache_topology[i].CacheLevel);
        infof(__func__, "\tCacheType: %u\n", cpu_info.cache_topology[i].CacheType);
        infof(__func__, "\tCacheNumWays: %u\n", cpu_info.cache_topology[i].CacheNumWays);
        infof(__func__, "\tCachePhysPartitions: %u\n", cpu_info.cache_topology[i].CachePhysPartitions);
        infof(__func__, "\tCacheLineSize: %u\n", cpu_info.cache_topology[i].CacheLineSize);
        infof(__func__, "\tCacheNumSets: %u\n", cpu_info.cache_topology[i].CacheNumSets);
    }
    infof(__func__, "ExtendedApicId: %u\n", cpu_info.ExtendedApicId);
    infof(__func__, "ThreadsPerComputeUnit: %u\n", cpu_info.ThreadsPerComputeUnit);
    infof(__func__, "ComputeUnitId: %u\n", cpu_info.ComputeUnitId);
    infof(__func__, "NodeId: %u\n", cpu_info.NodeId);
    infof(__func__, "NodesPerProcessor: %u\n", cpu_info.NodesPerProcessor);
    infof(__func__, "PreventHostIbs: %u\n", cpu_info.PreventHostIbs);
    infof(__func__, "DebugSwap: %u\n", cpu_info.DebugSwap);
    infof(__func__, "AlternateInjection: %u\n", cpu_info.AlternateInjection);
    infof(__func__, "RestrictedInjection: %u\n", cpu_info.RestrictedInjection);
    infof(__func__, "_64BitHost: %u\n", cpu_info._64BitHost);
    infof(__func__, "HwEnfCacheCoh: %u\n", cpu_info.HwEnfCacheCoh);
    infof(__func__, "VMPL: %u\n", cpu_info.VMPL);
    infof(__func__, "SEV_SNP: %u\n", cpu_info.SEV_SNP);
    infof(__func__, "SEV_ES: %u\n", cpu_info.SEV_ES);
    infof(__func__, "PageFlushMsr: %u\n", cpu_info.PageFlushMsr);
    infof(__func__, "SEV: %u\n", cpu_info.SEV);
    infof(__func__, "SME: %u\n", cpu_info.SME);
    infof(__func__, "NumVMPL: %u\n", cpu_info.NumVMPL);
    infof(__func__, "PhysAddrReduction: %u\n", cpu_info.PhysAddrReduction);
    infof(__func__, "CbitPosition: %u\n", cpu_info.CbitPosition);
    infof(__func__, "NumEncryptedGuests: %u\n", cpu_info.NumEncryptedGuests);
    infof(__func__, "MinSevNoEsAsid: %u\n", cpu_info.MinSevNoEsAsid);

}

static void test_memory() {
    m_initialize();
    info(__func__, "Memory module successfully initialized\n");
    info(__func__, "\n");
    infof(__func__, "cache_size[L1]: %llu\n", m_get_cache_size(L1));
    infof(__func__, "cache_size[L2]: %llu\n", m_get_cache_size(L2));
    infof(__func__, "cache_size[L3]: %llu\n", m_get_cache_size(L3));
    infof(__func__, "behavior_cache_size: %llu\n", m_get_behavior_cache_size());
    infof(__func__, "page_size: %llu\n", m_get_page_size());
    infof(__func__, "sector_size[L1_DATA]: %llu\n", m_get_sector_size(L1_DATA));
    infof(__func__, "sector_size[L1_INSTRUCTION]: %llu\n", m_get_sector_size(L1_INSTRUCTION));
    infof(__func__, "sector_size[L2_UNIFIED]: %llu\n", m_get_sector_size(L2_UNIFIED));
    infof(__func__, "sector_size[L3_UNIFIED]: %llu\n", m_get_sector_size(L3_UNIFIED));
    infof(__func__, "word_size: %llu\n", m_get_word_size());
}

#pragma GCC diagnostic pop

int main(int argc, char **argv) {
    info(__func__, "Running.\n");
    //test_expi();
    //test_lni();
    //test_log10i();
    //test_sigbits();
    //test_digits();
    //test_to_digits();
    //test_bittrie();
    //test_binary_trie();
    //test_map();
    //test_cpuid();
    test_memory();

    return R_SUCCESS;
}
