#include <stdint.h>
#include <types.h>

#include <arch/CPUInfo.h>

#include "i386.h"

/* Most information retrieved from http://en.wikipedia.org/wiki/CPUID */

/**
 * Vendor-strings returned by CPUID_REQUEST_VENDOR_STRING stored in EBX, EDX, ECX (in that order).
 */
#define CPUID_VENDOR_OLDAMD                 "AMDisbetter!"	/* Early engineering samples of AMD K5 processor */
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
#define CPUID_VENDOR_VMWARE                 "VMwareVMware"
#define CPUID_VENDOR_XEN                    "XenVMMXenVMM"

/* CPUID reported CPU features, EAX = 0x1 returned in EDX. */
#define CPUID_FEAT_EDX_FPU                  0x1                 /* Floating Point Unit. */
#define CPUID_FEAT_EDX_VME                  0x2                 /* Virtual 8086 Mode Extensions. */
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
#define CPUID_FEAT_ECX_ETPRD				0x4000			/* Can disable sending task priority messages *//
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

/**
 * Types of CPUID requests, with explanations.
 */
#define CPUID_REQUEST_VENDOR_STRING			0x0				/* Returns vendor string in EBX, EDX, ECX (in that order). */
#define CPUID_REQUEST_FEATURES				0x1				/* Returns CPU signature in EAX, features flags in ECX & EDX, additional features in EBX. */
#define CPUID_REQUEST_TLB					0x2
#define CPUID_REQUEST_SERIAL_NUMBER			0x3

#define CPUID_REQUEST_EXTENDED_FEATURES		0x7				/* Requests more feature information NOTE: ECX must equal 0x0 */

#define CPUID_REQUEST_HIGHEST_CALL_PARAM	0x80000000		/* Returns the highest supported calling parameter in EAX */

#define CPUID_REQUEST_BRAND_STRING_ONE		0x80000002		/* Returns part 1 of the processor brand string in EAX, EBX, ECX and EDX */
#define CPUID_REQUEST_BRAND_STRING_TWO		0x80000003		/* Returns part 2 of the processor brand string in EAX, EBX, ECX and EDX */
#define CPUID_REQUEST_BRAND_STRING_THREE	0x80000004		/* Returns part 3 of the processor brand string in EAX, EBX, ECX and EDX */

typedef struct {

	/* Information */
	char* vendor;
	char* brand;
	
	/* Features */
	bool features_FPU;
	bool features_APIC;
	bool features_MMX;
	bool features_SSE;
	bool features_SSE2;
	bool features_SSE3;
	bool features_IA64;
	bool features_HYPERTHREADING;

} cpu_info_t;

cpu_info_t* cpu_info;

/* C wrapper for CPUID */
static inline void cpuid(int request_code, unsigned long *eax, unsigned long *ebx, unsigned long *ecx, unsigned long *edx) {
	__asm__ __volatile__ (
		"cpuid"												/* Assembly code */
		:"=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx) /* Outputs */
		:"a"(request_code)									/* Put the request code into EAX */
															/* Clobbers: none. */
	);
}

/** 
 * Uses CPUID instruction to get info about CPU vendor, brand 
 * string. For more information about CPUID, check Intel IA-32
 * Architecture Software Developer Manual; Volume 2A Page 3-156 
 * We should call CPUID with EAX at 0 first, to get the highest
 * EAX parameter CPUID supports.
 */
void StoreCPUInformation(void) {

	char vendor_buffer[13];
	char brand_buffer[13];

	unsigned long eax, ebx, ecx, edx;
	
	/* Get the Vendor string then save the highest supported request level. */
	cpuid(CPUID_REQUEST_HIGHEST_CALL_PARAM, &eax, &ebx, &ecx, &edx);

	/**
	 * Vendor string.
	 */
	eax = ebx = ecx = edx = 0;

	cpuid(CPUID_REQUEST_VENDOR_STRING, &eax, &ebx, &ecx, &edx);

	*(uint32_t *)(&vendor_buffer[0]) = ebx;
	*(uint32_t *)(&vendor_buffer[4]) = edx;
	*(uint32_t *)(&vendor_buffer[8]) = ecx;
	vendor_buffer[12] = 0;

	cpu_info->vendor = *vendor_buffer;

	/**
	 * Features request.
	 */
	ClearRegisters(eax, ebx, ecx, edx);

	cpuid(CPUID_REQUEST_FEATURES, &eax, &ebx, &ecx, &edx);

	if(edx & CPUID_FEAT_EDX_FPU)
		cpu_info->features_FPU = true;

	if(edx & CPUID_FEAT_EDX_APIC)
		cpu_info->features_APIC = true;

	if(edx & CPUID_FEAT_EDX_MMX)
		cpu_info->features_MMX = true;

	if(edx & CPUID_FEAT_EDX_SSE)
		cpu_info->features_SSE = true;

	if(edx & CPUID_FEAT_EDX_SSE2)
		cpu_info->features_SSE2 = true;

	if(edx & CPUID_FEAT_EDX_IA64)
		cpu_info->features_IA64 = true;

	if(edx & CPUID_FEAT_EDX_HTT)
		cpu_info->features_HYPERTHREADING = true;

	/**
	 * Serial number.
	 */
	ClearRegisters(eax, ebx, ecx, edx);

	cpuid(CPUID_REQUEST_SERIAL_NUMBER, &eax, &ebx, &ecx, &edx);


	return;
 }

/**
 * Support functions.
 */
char* GetCPUVendor() {
	return cpu_info->vendor;
}

char* GetCPUBrand() {
	return cpu_info->brand;
}

bool CheckCPUFeature(int feature_code) {
	unsigned long eax, ebx, ecx, edx;
	cpuid(CPUID_REQUEST_FEATURES, &eax, &ebx, &ecx, &edx);

	if(edx & feature_code)
		return true;

	return false;
}

bool CheckCPUExtendedFeature(int feature_code) {
	unsigned long eax, ebx, ecx, edx;
	cpuid(CPUID_REQUEST_FEATURES, &eax, &ebx, &ecx, &edx);

	if(ecx & feature_code)
		return true;

	return false;
}

void ClearRegisters(unsigned long eax, unsigned long ebx , unsigned long ecx, unsigned long edx) {
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
}
