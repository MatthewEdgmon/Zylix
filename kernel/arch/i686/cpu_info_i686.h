/**
 * cpu_info_i686.h - CPU feature management for i686.
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

/**
 * Most information retrieved from:
 * http://en.wikipedia.org/wiki/CPUID
 * http://sandpile.org/x86/cpuid.htm
 */

#ifndef __CPU_INFO_I686_H__
#define __CPU_INFO_I686_H__

#include <stdbool.h>

/**
 * Types of CPUID requests, with explanations. Put this value into EAX.
 */
#define CPUID_REQUEST_STANDARD_VENDOR_MAX_LEVEL	    0x00000000  /* Returns max level in EAX, vendor string in EBX, EDX, ECX (in that order). */
#define CPUID_REQUEST_STANDARD_FEATURES	            0x00000001  /* Returns CPU signature in EAX, features flags in ECX & EDX, additional features in EBX. */
#define CPUID_REQUEST_STANDARD_CACHES               0x00000002  /* Processor configuration descriptors. */
#define CPUID_REQUEST_STANDARD_SERIAL_NUMBER		0x00000003  /* Returns processor serial number in EAX, EBX, ECX and EDX. */
#define CPUID_REQUEST_STANDARD_CACHES2              0x00000004
#define CPUID_REQUEST_STANDARD_POWER                0x00000006
#define CPUID_REQUEST_STANDARD_EXTENDED_FEATURES    0x00000007  /* Requests more feature information NOTE: ECX must equal 0x0 */
#define CPUID_REQUEST_STANDARD_FREQUENCY1           0x00000015  /* Requests information about the CPU frequency. */
#define CPUID_REQUEST_STANDARD_FREQUENCY2           0x00000016  /* Requests information about the CPU frequency. */
#define CPUID_REQUEST_STANDARD_TLB                  0x00000018
#define CPUID_REQUEST_XEON_PHI_MAX_LEVEL            0x20000000  /* Returns maximum supported level in EAX. */
#define CPUID_REQUEST_XEON_PHI                      0x20000001  /* Returns processor information in EDX. */
#define CPUID_REQUEST_HYPERVISOR_VENDOR             0x40000000  /* Requests vendor information, hypervisor only. */
#define CPUID_REQUEST_HYPERVISOR_INTERFACE          0x40000001  /* Requests interface information, hypervisor only. */
#define CPUID_REQUEST_HYPERVISOR_VERSION            0x40000002  /* Requests features information, hypervisor only. */
#define CPUID_REQUEST_HYPERVISOR_FEATURES           0x40000003  /* Requests limits information, hypervisor only. */
#define CPUID_REQUEST_HYPERVISOR_LIMITS             0x40000005  /* Requests limits information, hypervisor only. */
#define CPUID_REQUEST_HYPERVISOR_HARDWARE           0x40000006  /* Requests hardware features detected and in use, hypervisor only. */
#define CPUID_REQUEST_EXTENDED_HIGHEST_CALL_PARAM	0x80000000	/* Returns the highest supported calling parameter in EAX */
#define CPUID_REQUEST_EXTENDED_BRAND_STRING_ONE		0x80000002	/* Returns part 1 of the processor brand string in EAX, EBX, ECX and EDX */
#define CPUID_REQUEST_EXTENDED_BRAND_STRING_TWO		0x80000003	/* Returns part 2 of the processor brand string in EAX, EBX, ECX and EDX */
#define CPUID_REQUEST_EXTENDED_BRAND_STRING_THREE	0x80000004	/* Returns part 3 of the processor brand string in EAX, EBX, ECX and EDX */
#define CPUID_REQUEST_EXTENDED_CAPABILITIES         0x80000007
#define CPUID_REQUEST_EXTENDED_TOPOLGY              0x8000001E
#define CPUID_REQUEST_EXTENDED_SME_SEV              0x8000001F  /* Request SME/SEV information. */
#define CPUID_REQUEST_TRANSMETA_INFO                0x80860002  /* Requests processor information. TransMeta processors only. */
#define CPUID_REQUEST_TRANSMETA_INFO1               0x80860003  /* Requests information string part 1. TransMeta processors only. */
#define CPUID_REQUEST_TRANSMETA_INFO2               0x80860004  /* Requests information string part 2. TransMeta processors only. */
#define CPUID_REQUEST_TRANSMETA_INFO3               0x80860005  /* Requests information string part 3. TransMeta processors only. */
#define CPUID_REQUEST_TRANSMETA_INFO4               0x80860006  /* Requests information string part 4. TransMeta processors only. */
#define CPUID_REQUEST_MYSTERY_K6                    0x8FFFFFFE  /* Unkown. AMD K6 only. */
#define CPUID_REQUEST_AMD_EASTER_EGG                0x8FFFFFFF  /* AMD Easter egg. K6 = "NexGenerationAMD" K7/K8 = "IT'S HAMMER TIME" KB = "HELLO KITTY! ^-^" */
#define CPUID_REQUEST_SIMNOW                        0xBACCD00A  /* Uknown. AMD SimNow! only. */
#define CPUID_REQUEST_CENTAUR_MAX_LEVEL             0xC0000000  /* Returns maximum supported level in EAX, Centaur processors only. */
#define CPUID_REQUEST_CENTAUR_INFORMATION           0xC0000001  /* Requests processor information. Centaur processors only. */

/**
 * Vendor-strings returned by CPUID_REQUEST_VENDOR_STRING stored in EBX, EDX, ECX (in that order).
 */
#define CPUID_VENDOR_OLDAMD                 "AMDisbetter!"	 /* Early engineering samples of AMD K5 processor */
#define CPUID_VENDOR_AMD                    "AuthenticAMD"
#define CPUID_VENDOR_INTEL                  "GenuineIntel"
#define CPUID_VENDOR_OLDVIA                 "CentaurHauls"
#define CPUID_VENDOR_VIA                    "VIA VIA VIA "
#define CPUID_VENDOR_OLDTRANSMETA           "TransmetaCPU"
#define CPUID_VENDOR_TRANSMETA              "GenuineTMx86"
#define CPUID_VENDOR_CYRIX                  "CyrixInstead"
#define CPUID_VENDOR_CENTAUR                "CentaurHauls"
#define CPUID_VENDOR_NEXGEN                 "NexGenDriven"
#define CPUID_VENDOR_UMC                    "UMC UMC UMC "
#define CPUID_VENDOR_SIS                    "SiS SiS SiS "
#define CPUID_VENDOR_NSC                    "Geode by NSC"
#define CPUID_VENDOR_RISE                   "RiseRiseRise"
#define CPUID_VENDOR_VORTEX                 "Vortex86 SoC"

#define CPUID_VENDOR_KVM                    "KVMKVMKVMKVM"
#define CPUID_VENDOR_MICROSOFT_HYPERV       "Microsoft Hv"
#define CPUID_VENDOR_PARALLELS              " lrpepyh vr"
#define CPUID_VENDOR_VMWARE                 "VMwareVMware"
#define CPUID_VENDOR_XEN                    "XenVMMXenVMM"

/* CPUID reported CPU features, EAX = 0x1 returned in EDX. */
#define CPUID_FEAT_EDX_FPU                  0x1             /* Floating Point Unit. */
#define CPUID_FEAT_EDX_VME                  0x2             /* Virtual 8086 Mode Extensions. */
#define CPUID_FEAT_EDX_DE					0x4             /* Debugging Extensions. */
#define CPUID_FEAT_EDX_PSE					0x8             /* Page Size Extensions. */
#define CPUID_FEAT_EDX_TSC					0x10            /* Time Stamp Counter. */
#define CPUID_FEAT_EDX_MSR					0x20            /* Model-specific registers. */
#define CPUID_FEAT_EDX_PAE					0x40            /* Physical Address Extensions. */
#define CPUID_FEAT_EDX_MCE					0x80            /* Machine Check Exceptions. */
#define CPUID_FEAT_EDX_CX8					0x100           /* CMPXCHG8  Instruction (compare-and-swap). */
#define CPUID_FEAT_EDX_APIC					0x200           /* On-chip APIC. */
/*											0x400			   Reserved. */
#define CPUID_FEAT_EDX_SEP					0x800           /* SYSENTER and SYSEXIT support. */
#define CPUID_FEAT_EDX_MTRR					0x1000          /* Memory Type Range Registers. */
#define CPUID_FEAT_EDX_PGE					0x2000          /* Page Global Enable.  */
#define CPUID_FEAT_EDX_MCA          		0x4000          /* Machine Check Architecture. */
#define CPUID_FEAT_EDX_CMOV         		0x8000          /* Conditional move-instruction. */
#define CPUID_FEAT_EDX_PAT          		0x10000         /* Page Attribute Table. */
#define CPUID_FEAT_EDX_PSE36        		0x20000         /* 36-bit Page Size Extensions. */
#define CPUID_FEAT_EDX_PSN          		0x40000         /* Processor Serial Number. */
#define CPUID_FEAT_EDX_CLFSH         		0x80000         /* CLFLUSH instruction (SSE2). */
/*											0x100000		   Reserved. */
#define CPUID_FEAT_EDX_DS	         		0x200000        /* Debug Trace and EMON Store MSRs. */
#define CPUID_FEAT_EDX_ACPI         		0x400000        /* Thermal Cotrol MSR. */
#define CPUID_FEAT_EDX_MMX          		0x800000        /* MMX instruction set. */
#define CPUID_FEAT_EDX_FXSR         		0x1000000       /* Fast floating point save/restore. */
#define CPUID_FEAT_EDX_SSE          		0x2000000       /* SSE (Streaming SIMD Extensions) */
#define CPUID_FEAT_EDX_SSE2         		0x4000000       /* SSE2 (Streaming SIMD Extensions 2) */
#define CPUID_FEAT_EDX_SS           		0x8000000       /* Selfsnoop. */
#define CPUID_FEAT_EDX_HTT          		0x10000000      /* Hyper-Threading Technology. */
#define CPUID_FEAT_EDX_TM	          		0x20000000      /* Thermal Interrupts, Status MSRs. */
#define CPUID_FEAT_EDX_IA64         		0x40000000      /* IA-64 (64-bit Intel CPU) */
#define CPUID_FEAT_EDX_PBE					0x80000000      /* Pending Break Event. */

/* Intel-defined CPU features, EAX = 0x1 returned in ECX. */
#define CPUID_FEAT_ECX_SSE3					0x1             /* SSE3 (Streaming SIMD Extensions 3) */
#define CPUID_FEAT_ECX_PCLMULQDQ			0x2				/* PCLMULQDQ Instruction (Carry-Less Multiplication) support */
#define CPUID_FEAT_ECX_DTES64				0x4				/* 64-bit Debug Store */
#define CPUID_FEAT_ECX_MONITOR				0x8				/* Monitor/Mwait support */
#define CPUID_FEAT_ECX_DS_CPL				0x10			/* CPL Qual. Debug Store */
#define CPUID_FEAT_ECX_VMX					0x20			/* Hardware virtualization support. */
#define CPUID_FEAT_ECX_SMX					0x40			/* Safer mode: Trusted Execution Technology */
#define CPUID_FEAT_ECX_EST					0x80			/* Enhanced SpeedStep */
#define CPUID_FEAT_ECX_TM2					0x100			/* Thermal Monitor 2 */
#define CPUID_FEAT_ECX_SSSE3				0x200			/* Supplemental Streaming SIMD Extensions 3 */
#define CPUID_FEAT_ECX_CNXTID				0x400			/* Context ID */
/*											0x800			   Reserved. */
#define CPUID_FEAT_ECX_FMA					0x1000			/* Fused Multiply-Add */
#define CPUID_FEAT_ECX_CX16					0x2000			/* Compare-And-Swap CMPXCHG16B */
#define CPUID_FEAT_ECX_ETPRD				0x4000			/* Can disable sending task priority messages */
#define CPUID_FEAT_ECX_PDCM					0x8000			/* Perfmon & debug capability */
/*											0x10000			   Reserved. */
#define CPUID_FEAT_ECX_PCID					0x20000			/* Process Context Identifiers. */
#define CPUID_FEAT_ECX_DCA					0x40000			/* Direct Cache Access */
#define CPUID_FEAT_ECX_SSE4_1				0x80000			/* Streaming SIMD Extensions 4.1 */
#define CPUID_FEAT_ECX_SSE4_2				0x100000		/* Streaming SIMD Extensions 4.2 */
#define CPUID_FEAT_ECX_X2APIC				0x200000		/* New intel x2APIC extensions. */
#define CPUID_FEAT_ECX_MOVBE				0x400000		/* MOVBE Instruction */
#define CPUID_FEAT_ECX_POPCNT				0x800000		/* POPCNT instruction */
#define CPUID_FEAT_ECX_TSC_DEADLINE			0x1000000		/* APIC supports one-shot operation using a TSC deadline value. */
#define CPUID_FEAT_ECX_AES					0x2000000		/* AES instructions. */
#define CPUID_FEAT_ECX_XSAVE				0x4000000		/* XSAVE/XRSTOR/XSETBV/XGETBV */
#define CPUID_FEAT_ECX_OSXSAVE				0x8000000		/* XSAVE enabled by OS */
#define CPUID_FEAT_ECX_AVX					0x10000000		/* Advanced Vector Extensions. */
#define CPUID_FEAT_ECX_F16C					0x20000000		/* F16C (half-precision) FP support. */
#define CPUID_FEAT_ECX_RDRAND				0x40000000		/* RDRAND Instruction (on-chip random number generator) support */
#define CPUID_FEAT_ECX_HYPERVISOR			0x80000000		/* Running on a hyervisor. Not reliable. */

/*
char* cpuid_intel_brand[] = {
	"Brand ID Not Supported.",
	"Intel(R) Celeron(R) Processor",
	"Intel(R) Pentium(R) III Processor",
	"Intel(R) Pentium(R) III Xeon(R) Processor",
	"Intel(R) Pentium(R) III Processor",
	"Reserved",
	"Mobile Intel(R) Pentium(R) III Processor-M",
	"Mobile Intel(R) Celeron(R) Processor",
	"Intel(R) Pentium(R) 4 Processor",
	"Intel(R) Pentium(R) 4 Processor",
	"Intel(R) Celeron(R) Processor",
	"Intel(R) Xeon(R) Processor",
	"Intel(R) Xeon(R) Processor MP",
	"Reserved",
	"Mobile Intel(R) Pentium(R) 4 Processor-M",
	"Mobile Intel(R) Pentium(R) Celeron(R) Processor",
	"Reserved",
	"Mobile Genuine Intel(R) Processor",
	"Intel(R) Celeron(R) M Processor",
	"Mobile Intel(R) Celeron(R) Processor",
	"Intel(R) Celeron(R) Processor",
	"Mobile Geniune Intel(R) Processor",
	"Intel(R) Pentium(R) M Processor",
	"Mobile Intel(R) Celeron(R) Processor"
};

char* cpuid_intel_brand_other[] = {
	"Reserved",
	"Reserved",
	"Reserved",
	"Intel(R) Celeron(R) Processor",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Intel(R) Xeon(R) Processor MP",
	"Reserved",
	"Reserved",
	"Intel(R) Xeon(R) Processor",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};
*/

typedef struct {

	/* What's the max value CPUID supports? */
	uint32_t max_request;

	/* Information, all strings are null terminated. */
	char vendor[13];
	char processor_name1[17];
	char processor_name2[17];
	char processor_name3[17];
	char serial[64];
	char features[8192];

	/* Frequency */
	uint32_t freq_denominator;
	uint32_t freq_numerator;
	uint32_t freq_hz;

	/* EDX Features */
	bool features_FPU;
	bool features_VME;
	bool features_DE;
	bool features_PSE;
	bool features_TSC;
	bool features_MSR;
	bool features_PAE;
	bool features_MCE;
	bool features_CX8;
	bool features_APIC;
	bool features_SEP;
	bool features_MTRR;
	bool features_PGE;
	bool features_MCA;
	bool features_CMOV;
	bool features_PAT;
	bool features_PSE36;
	bool features_PSN;
	bool features_CLFLUSH;
	bool features_DS;
	bool features_ACPI;
	bool features_MMX;
	bool features_FXSR;
	bool features_SSE;
	bool features_SSE2;
	bool features_SS;
	bool features_HYPERTHREADING;
	bool features_TM;
	bool features_IA64;
	bool features_PBE;

	/* ECX Features */
	bool features_SSE3;
	bool features_PCLMULQDQ;
	bool features_DTES64;
	bool features_MONITOR;
	bool features_DS_CPL;
	bool features_VMX;
	bool features_SMX;
	bool features_EST;
	bool features_TM2;
	bool features_SSSE3;
	bool features_CNXTID;
	bool features_FMA;
	bool features_CMPXCHG16B;
	bool features_ETPRD;
	bool features_PDCM;
	bool features_PCID;
	bool features_DCA;
	bool features_SSE4_1;
	bool features_SSE4_2;
	bool features_X2APIC;
	bool features_MOVBE;
	bool features_POPCNT;
	bool features_TSC_DEADLINE;
	bool features_AES;
	bool features_XSAVE;
	bool features_OSXSAVE;
	bool features_AVX;
	bool features_F16C;
	bool features_RDRAND;
	bool features_HYPERVISOR;

} cpu_info_t;

extern cpu_info_t* cpu_info;

void DumpCPUInformation();

void StoreCPUInformation();

#endif /* __CPU_INFO_I686_H__ */
