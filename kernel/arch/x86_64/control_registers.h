/**
 * control_registers.h - Functions to load CR0 - CR15.
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

#ifndef __CONTROL_REGISTERS_H__
#define __CONTROL_REGISTERS_H__

#include <stdint.h>

/* NOTE: CR1, CR5 - CR7, and CR9 - CR15 will throw a #UD exception on access. */
/* NOTE: Reserved bits must be zero unless otherwise noted. */

#define CR0_BIT_PE           0    /* Protected mode enable. */
#define CR0_BIT_MP           1    /* Monitor co-processor, controls WAIT/FWAIT. */
#define CR0_BIT_EM           2    /* Emulation. */
#define CR0_BIT_TS           3    /* Task switched. */
#define CR0_BIT_ET           4    /* Extension type. */
#define CR0_BIT_NE           5    /* Numeric error. */
/*      CR0_BIT              6 - 15  Reserved. */
#define CR0_BIT_WP           16   /* Write protect. */
/*      CR0_BIT              17      Reserved */
#define CR0_BIT_AM           18   /* Alignment mask. */
/*      CR0_BIT              19 - 28 Reserved. */
#define CR0_BIT_NW           29   /* Globally enables/disables write through caching. */
#define CR0_BIT_CD           30   /* Globally enables/disables the memory cache. */
#define CR0_BIT_PG           31   /* Enables paging when set. */
/*      CR0_BIT              32 - 63 Reserved. */

#define CR4_BIT_VME          0    /* Virtual 8086 mode extensions */
#define CR4_BIT_PVI          1    /* Protected mode virtual interrupts. */
#define CR4_BIT_TSD          2    /* Time stamp allowed only in ring 0. */
#define CR4_BIT_DE           3    /* Debugging extensions. */
#define CR4_BIT_PSE          4    /* Page size extension. */
#define CR4_BIT_PAE          5    /* Physical address extension. */
#define CR4_BIT_MCE          6    /* Machine check exception. */
#define CR4_BIT_PGE          7    /* Page global enable. */
#define CR4_BIT_PCE          8    /* Performance monitoring counter enable. */
#define CR4_BIT_OSFXSR       9    /* Indicates OS support for FXSAVE and FXRSTOR instructions. */
#define CR4_BIT_OSXMMEXCPT   10   /* Indicates OS support for unmasked SIMD floating point exceptions. */
#define CR4_BIT_UMIP         11   /* User mode instruction prevention. SGDT, SIDT, SLDT, SMSW, and STR instruction need CPL > 0. */
/*      CR4_BIT              12      Reserved */
#define CR4_BIT_VMXE         13   /* VT-x */
#define CR4_BIT_SMXE         14   /* Trusted execution technology. */
/*      CR4_BIT              15      Reserved */
#define CR4_BIT_FSGSBASE     16   /* Enables the RDFSBASE, RDGSBASE, WRFSBASE, and WRGSBASE instructions. */
#define CR4_BIT_PCIDE        17
#define CR4_BIT_OSXSAVE      18
/*      CR4_BIT              19      Reserved */
#define CR4_BIT_SMEP         20   /* Supervisor mode executions protection enable. */
#define CR4_BIT_SMAP         21   /* Supervisor mode access protection enable. */
#define CR4_BIT_SMAP         21   /* Protection key enable. */
/*      CR4_BIT              23 - 63 Reserved. */

#define EFER_BIT_SCE         0    /* System call extensions. */
/*      EFER_BIT             1 - 7   Reserved. */
#define EFER_BIT_LME         8    /* Long mode enabled. */
/*      EFER_BIT             9       Reserved */
#define EFER_BIT_LMA         10   /* Long mode active. */
#define EFER_BIT_NXE         11   /* No execute enable. */
#define EFER_BIT_SVME        12   /* Secure virtual machine enable. */
#define EFER_BIT_LMSLE       13   /* Long mode segment limit enable. */
#define EFER_BIT_FFXSR       14   /* Fast FXSAVE and FXRSTOR. */
#define EFER_BIT_TCE         15   /* Translation cache extension. */
/*      EFER_BIT             16 - 63 Reserved. */

#define XCR0_BIT_X87         0    /* x87 FPU/MMX state (must always be 1?). */
#define XCR0_BIT_SSE         1    /* Enable XSAVE for MXCSR and XMM registers. */
#define XCR0_BIT_AVX         2    /* Enable AVX, and XSAVE for YMM registers. */
#define XCR0_BIT_BNDREF      3    /* Enable MPX, and XSAVE for BND registers. */
#define XCR0_BIT_BNDCSR      4    /* Enable MPX, and XSAVE for BNDCFGU and BNDSTATUS registers. */
#define XCR0_BIT_OPMASK      5    /* Enable AVX-512, and XSAVE for AVX opmask/kmask registers. */
#define XCR0_BIT_ZMM_HI256   6    /* Enable AVX-512, and XSAVE for upper half of lower ZMM registers. */
#define XCR0_BIT_HI16_ZMM    7    /* Enable AVX-512, and XSAVE for upper ZMM registers. */
/*      XCR0_BIT             8       Reserved */
#define XCR0_BIT_PKRU        9    /* XSAVE feature can be used for PKRU register (part of proection keys). */
/*      XCR0_BIT             10      Reserved */
#define XCR0_BIT_CET_USER    11   /* Control-flow Enforcement Technology user state. */
#define XCR0_BIT_CET_SUPER   12   /* Control-flow Enforcement Technology supervisor state. */
/*      XCR0_BIT             13 - 63 Reserved. */

/*      XSS_BIT              0 - 7   Reserved. */
#define XSS_BIT_PT           8    /* Enables the saving and loading of nine Processor Trace MSRs. */
/*      XSS_BIT              9 - 12  Reserved. */
#define XSS_BIT_HDC          13   /* Enables the saving and loading of the IA32_PM_CTL1 MSR. */
/*      XSS_BIT              14 - 63 Reserved. */

#define FLAG_BIT_CF          0    /* Carry flag. */
/*      FLAG_BIT             1       Reserved, must be 1. */
#define FLAG_BIT_PF          2    /* Parity flag. */
/*      FLAG_BIT             3       Reserved. */
#define FLAG_BIT_AF          4
/*      FLAG_BIT             5       Reserved. */
#define FLAG_BIT_ZF          6
#define FLAG_BIT_SF          7
#define FLAG_BIT_TF          8    /* Trap flag. */
#define FLAG_BIT_IF          9    /* Interrupt enable flag. */
#define FLAG_BIT_DF          10
#define FLAG_BIT_OF          11
#define FLAG_BIT_IOPL0       12
#define FLAG_BIT_IOPL1       13
#define FLAG_BIT_NT          14
/*      FLAG_BIT             15       Reserved. */
#define FLAG_BIT_RF          16
#define FLAG_BIT_VM          17
#define FLAG_BIT_AC          18
#define FLAG_BIT_VIF         19
#define FLAG_BIT_VIP         20
#define FLAG_BIT_ID          21
/*      FLAG_BIT             22 - 63 Reserved. */

void LoadCR0(uint64_t);
void LoadCR1(uint64_t);
void LoadCR2(uint64_t);
void LoadCR3(uint64_t);
void LoadCR4(uint64_t);
void LoadCR5(uint64_t);
void LoadCR6(uint64_t);
void LoadCR7(uint64_t);
void LoadCR8(uint64_t);
void LoadCR9(uint64_t);
void LoadCR10(uint64_t);
void LoadCR11(uint64_t);
void LoadCR12(uint64_t);
void LoadCR13(uint64_t);
void LoadCR14(uint64_t);
void LoadCR15(uint64_t);

uint64_t SaveCR0(void);
uint64_t SaveCR1(void);
uint64_t SaveCR2(void);
uint64_t SaveCR3(void);
uint64_t SaveCR4(void);
uint64_t SaveCR5(void);
uint64_t SaveCR6(void);
uint64_t SaveCR7(void);
uint64_t SaveCR8(void);
uint64_t SaveCR9(void);
uint64_t SaveCR10(void);
uint64_t SaveCR11(void);
uint64_t SaveCR12(void);
uint64_t SaveCR13(void);
uint64_t SaveCR14(void);
uint64_t SaveCR15(void);

uint64_t GetFlagRegister(void);
void SetFlagRegister(uint64_t);

#endif /* __CONTROL_REGISTERS_H__ */
