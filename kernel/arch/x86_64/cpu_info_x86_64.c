/**
 * cpu_info.c - CPU feature management for x86_64.
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cpu_info_x86_64.h"

cpu_info_t* cpu_info;

#define cpuid(in, a, b, c, d) __asm__ __volatile__ ("cpuid" : "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

void DumpCPUInformation() {
    printf("CPU Information:\n");
    printf("    Vendor: %s\n", cpu_info->vendor);
    printf("    Processor Name: %s%s%s\n", cpu_info->processor_name1, cpu_info->processor_name2, cpu_info->processor_name3);
    printf("    Max CPUID: 0x%X\n", cpu_info->max_request);
    printf("    Features: %s\n\n\n", cpu_info->features);
}

void StoreCPUInformation() {

    uint32_t eax, ebx, ecx, edx;

    /**
     * Vendor string and max request level.
     */
    cpuid(CPUID_REQUEST_STANDARD_VENDOR_MAX_LEVEL, eax, ebx, ecx, edx);
    cpu_info->max_request = eax;

    for(size_t i = 0; i < 4; i++) {
        cpu_info->vendor[i]      = ebx >> (8 * i);
        cpu_info->vendor[i + 4]  = edx >> (8 * i);
        cpu_info->vendor[i + 8]  = ecx >> (8 * i);
    }

    cpu_info->vendor[12] = '\0';

    cpuid(CPUID_REQUEST_STANDARD_FEATURES, eax, ebx, ecx, edx);

    if(ecx & CPUID_FEAT_ECX_SSE3)         { sprintf(cpu_info->features, "SSE3");                                      cpu_info->features_SSE3 = true; }
    if(ecx & CPUID_FEAT_ECX_PCLMULQDQ)    { sprintf(cpu_info->features, "%s PCLMULQDQ",          cpu_info->features); cpu_info->features_PCLMULQDQ = true; }
    if(ecx & CPUID_FEAT_ECX_DTES64)       { sprintf(cpu_info->features, "%s DTES64",             cpu_info->features); cpu_info->features_DTES64 = true; }
    if(ecx & CPUID_FEAT_ECX_MONITOR)      { sprintf(cpu_info->features, "%s Monitor",            cpu_info->features); cpu_info->features_MONITOR = true; }
    if(ecx & CPUID_FEAT_ECX_DS_CPL)       { sprintf(cpu_info->features, "%s CPL Qual",           cpu_info->features); cpu_info->features_DS_CPL = true; }
    if(ecx & CPUID_FEAT_ECX_VMX)          { sprintf(cpu_info->features, "%s VMX",                cpu_info->features); cpu_info->features_VMX = true; }
    if(ecx & CPUID_FEAT_ECX_SMX)          { sprintf(cpu_info->features, "%s SMX",                cpu_info->features); cpu_info->features_SMX = true; }
    if(ecx & CPUID_FEAT_ECX_EST)          { sprintf(cpu_info->features, "%s EST",                cpu_info->features); cpu_info->features_EST = true; }
    if(ecx & CPUID_FEAT_ECX_TM2)          { sprintf(cpu_info->features, "%s TM2",                cpu_info->features); cpu_info->features_TM2 = true; }
    if(ecx & CPUID_FEAT_ECX_SSSE3)        { sprintf(cpu_info->features, "%s SSSE3",              cpu_info->features); cpu_info->features_SSSE3 = true; }
    if(ecx & CPUID_FEAT_ECX_CNXTID)       { sprintf(cpu_info->features, "%s CNXTID",             cpu_info->features); cpu_info->features_CNXTID = true; }
    if(ecx & CPUID_FEAT_ECX_FMA)          { sprintf(cpu_info->features, "%s FMA",                cpu_info->features); cpu_info->features_FMA = true; }
    if(ecx & CPUID_FEAT_ECX_CX16)         { sprintf(cpu_info->features, "%s CMPXCHG16B",         cpu_info->features); cpu_info->features_CMPXCHG16B = true; }
    if(ecx & CPUID_FEAT_ECX_ETPRD)        { sprintf(cpu_info->features, "%s ETPRD",              cpu_info->features); cpu_info->features_ETPRD = true; }
    if(ecx & CPUID_FEAT_ECX_PDCM)         { sprintf(cpu_info->features, "%s PDCM",               cpu_info->features); cpu_info->features_PDCM = true; }
    if(ecx & CPUID_FEAT_ECX_PCID)         { sprintf(cpu_info->features, "%s PCID",               cpu_info->features); cpu_info->features_PCID = true; }
    if(ecx & CPUID_FEAT_ECX_DCA)          { sprintf(cpu_info->features, "%s DCA",                cpu_info->features); cpu_info->features_DCA = true; }
    if(ecx & CPUID_FEAT_ECX_SSE4_1)       { sprintf(cpu_info->features, "%s SSE4.1",             cpu_info->features); cpu_info->features_SSE4_1 = true; }
    if(ecx & CPUID_FEAT_ECX_SSE4_2)       { sprintf(cpu_info->features, "%s SSE4.2",             cpu_info->features); cpu_info->features_SSE4_2 = true; }
    if(ecx & CPUID_FEAT_ECX_X2APIC)       { sprintf(cpu_info->features, "%s x2APIC",             cpu_info->features); cpu_info->features_X2APIC = true; }
    if(ecx & CPUID_FEAT_ECX_MOVBE)        { sprintf(cpu_info->features, "%s MOVBE",              cpu_info->features); cpu_info->features_MOVBE = true; }
    if(ecx & CPUID_FEAT_ECX_POPCNT)       { sprintf(cpu_info->features, "%s POPCNT",             cpu_info->features); cpu_info->features_POPCNT = true; }
    if(ecx & CPUID_FEAT_ECX_TSC_DEADLINE) { sprintf(cpu_info->features, "%s APIC One-Shot",      cpu_info->features); cpu_info->features_TSC_DEADLINE = true; }
    if(ecx & CPUID_FEAT_ECX_AES)          { sprintf(cpu_info->features, "%s AES",                cpu_info->features); cpu_info->features_AES = true; }
    if(ecx & CPUID_FEAT_ECX_XSAVE)        { sprintf(cpu_info->features, "%s XSAVE",              cpu_info->features); cpu_info->features_XSAVE = true; }
    if(ecx & CPUID_FEAT_ECX_OSXSAVE)      { sprintf(cpu_info->features, "%s OSXSAVE",            cpu_info->features); cpu_info->features_OSXSAVE = true; }
    if(ecx & CPUID_FEAT_ECX_AVX)          { sprintf(cpu_info->features, "%s AVX",                cpu_info->features); cpu_info->features_AVX = true; }
    if(ecx & CPUID_FEAT_ECX_F16C)         { sprintf(cpu_info->features, "%s F16C",               cpu_info->features); cpu_info->features_F16C = true; }
    if(ecx & CPUID_FEAT_ECX_RDRAND)       { sprintf(cpu_info->features, "%s RDRAND",             cpu_info->features); cpu_info->features_RDRAND = true; }
    if(ecx & CPUID_FEAT_ECX_HYPERVISOR)   { sprintf(cpu_info->features, "%s HyperVisor",         cpu_info->features); cpu_info->features_HYPERVISOR = true; }

    if(edx & CPUID_FEAT_EDX_FPU)          { sprintf(cpu_info->features, "%s FPU",                cpu_info->features); cpu_info->features_FPU = true; }
    if(edx & CPUID_FEAT_EDX_VME)          { sprintf(cpu_info->features, "%s VME",                cpu_info->features); cpu_info->features_VME = true; }
    if(edx & CPUID_FEAT_EDX_DE)           { sprintf(cpu_info->features, "%s DE",                 cpu_info->features); cpu_info->features_DE = true; }
    if(edx & CPUID_FEAT_EDX_PSE)          { sprintf(cpu_info->features, "%s PSE",                cpu_info->features); cpu_info->features_PSE = true; }
    if(edx & CPUID_FEAT_EDX_TSC)          { sprintf(cpu_info->features, "%s TSC",                cpu_info->features); cpu_info->features_TSC = true; }
    if(edx & CPUID_FEAT_EDX_MSR)          { sprintf(cpu_info->features, "%s MSR",                cpu_info->features); cpu_info->features_MSR = true; }
    if(edx & CPUID_FEAT_EDX_PAE)          { sprintf(cpu_info->features, "%s PAE",                cpu_info->features); cpu_info->features_PAE = true; }
    if(edx & CPUID_FEAT_EDX_MCE)          { sprintf(cpu_info->features, "%s MCE",                cpu_info->features); cpu_info->features_MCE = true; }
    if(edx & CPUID_FEAT_EDX_CX8)          { sprintf(cpu_info->features, "%s CX8",                cpu_info->features); cpu_info->features_CX8 = true; }
    if(edx & CPUID_FEAT_EDX_APIC)         { sprintf(cpu_info->features, "%s APIC",               cpu_info->features); cpu_info->features_APIC = true; }
    if(edx & CPUID_FEAT_EDX_SEP)          { sprintf(cpu_info->features, "%s SEP",                cpu_info->features); cpu_info->features_SEP = true; }
    if(edx & CPUID_FEAT_EDX_MTRR)         { sprintf(cpu_info->features, "%s MTRR",               cpu_info->features); cpu_info->features_MTRR = true; }
    if(edx & CPUID_FEAT_EDX_PGE)          { sprintf(cpu_info->features, "%s PGE",                cpu_info->features); cpu_info->features_PGE = true; }
    if(ecx & CPUID_FEAT_EDX_MCA)          { sprintf(cpu_info->features, "%s MCA",                cpu_info->features); cpu_info->features_MCA = true; }
    if(edx & CPUID_FEAT_EDX_CMOV)         { sprintf(cpu_info->features, "%s CMOV",               cpu_info->features); cpu_info->features_CMOV = true; }
    if(edx & CPUID_FEAT_EDX_PAT)          { sprintf(cpu_info->features, "%s PAT",                cpu_info->features); cpu_info->features_PAT = true; }
    if(edx & CPUID_FEAT_EDX_PSE36)        { sprintf(cpu_info->features, "%s PSE36",              cpu_info->features); cpu_info->features_PSE36 = true; }
    if(edx & CPUID_FEAT_EDX_PSN)          { sprintf(cpu_info->features, "%s PSN",                cpu_info->features); cpu_info->features_PSN = true; }
    if(edx & CPUID_FEAT_EDX_CLFSH)        { sprintf(cpu_info->features, "%s CLFLUSH",            cpu_info->features); cpu_info->features_CLFLUSH = true; }
    if(edx & CPUID_FEAT_EDX_DS)           { sprintf(cpu_info->features, "%s DS",                 cpu_info->features); cpu_info->features_DS = true; }
    if(edx & CPUID_FEAT_EDX_ACPI)         { sprintf(cpu_info->features, "%s ACPI",               cpu_info->features); cpu_info->features_ACPI = true; }
    if(edx & CPUID_FEAT_EDX_MMX)          { sprintf(cpu_info->features, "%s MMX",                cpu_info->features); cpu_info->features_MMX = true; }
    if(ecx & CPUID_FEAT_EDX_FXSR)         { sprintf(cpu_info->features, "%s FXSR",               cpu_info->features); cpu_info->features_FXSR = true; }
    if(edx & CPUID_FEAT_EDX_SSE)          { sprintf(cpu_info->features, "%s SSE",                cpu_info->features); cpu_info->features_SSE = true; }
    if(edx & CPUID_FEAT_EDX_SSE2)         { sprintf(cpu_info->features, "%s SSE2",               cpu_info->features); cpu_info->features_SSE2 = true; }
    if(edx & CPUID_FEAT_EDX_SS)           { sprintf(cpu_info->features, "%s SS",                 cpu_info->features); cpu_info->features_SS = true; }
    if(edx & CPUID_FEAT_EDX_HTT)          { sprintf(cpu_info->features, "%s Hyper-Threading",    cpu_info->features); cpu_info->features_HYPERTHREADING = true; }
    if(edx & CPUID_FEAT_EDX_TM)           { sprintf(cpu_info->features, "%s Thermal Interrupts", cpu_info->features); cpu_info->features_TM = true; }
    if(edx & CPUID_FEAT_EDX_IA64)         { sprintf(cpu_info->features, "%s IA64",               cpu_info->features); cpu_info->features_IA64 = true; }
    if(edx & CPUID_FEAT_EDX_PBE)          { sprintf(cpu_info->features, "%s PBE",                cpu_info->features); cpu_info->features_PBE = true; }

    sprintf(cpu_info->features, "%s\0", cpu_info->features);

    cpuid(CPUID_REQUEST_STANDARD_SERIAL_NUMBER, eax, ebx, ecx, edx);

    for(size_t i = 0; i < 4; i++) {
        cpu_info->serial[i]      = eax >> (8 * i);
        cpu_info->serial[i + 4]  = ebx >> (8 * i);
        cpu_info->serial[i + 8]  = ecx >> (8 * i);
        cpu_info->serial[i + 12] = edx >> (8 * i);
    }

    cpuid(CPUID_REQUEST_STANDARD_FREQUENCY1, eax, ebx, ecx, edx);

    cpu_info->freq_denominator = eax;
    cpu_info->freq_numerator = ebx;
    cpu_info->freq_hz = ecx;

    cpuid(CPUID_REQUEST_EXTENDED_BRAND_STRING_ONE, eax, ebx, ecx, edx);
    for(size_t i = 0; i < 4; i++) {
        cpu_info->processor_name1[i]      = eax >> (8 * i);
        cpu_info->processor_name1[i + 4]  = ebx >> (8 * i);
        cpu_info->processor_name1[i + 8]  = ecx >> (8 * i);
        cpu_info->processor_name1[i + 12] = edx >> (8 * i);
    }

    cpu_info->processor_name1[16] = '\0';

    cpuid(CPUID_REQUEST_EXTENDED_BRAND_STRING_TWO, eax, ebx, ecx, edx);
    for(size_t i = 0; i < 4; i++) {
        cpu_info->processor_name2[i]      = eax >> (8 * i);
        cpu_info->processor_name2[i + 4]  = ebx >> (8 * i);
        cpu_info->processor_name2[i + 8]  = ecx >> (8 * i);
        cpu_info->processor_name2[i + 12] = edx >> (8 * i);
    }

    cpu_info->processor_name2[16] = '\0';

    cpuid(CPUID_REQUEST_EXTENDED_BRAND_STRING_THREE, eax, ebx, ecx, edx);
    for(size_t i = 0; i < 4; i++) {
        cpu_info->processor_name3[i]      = eax >> (8 * i);
        cpu_info->processor_name3[i + 4]  = ebx >> (8 * i);
        cpu_info->processor_name3[i + 8]  = ecx >> (8 * i);
        cpu_info->processor_name3[i + 12] = edx >> (8 * i);
    }

    cpu_info->processor_name3[16] = '\0';

    return;
 }
