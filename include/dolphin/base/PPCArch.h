#ifndef DOLPHIN_BASE_PPCARCH_H
#define DOLPHIN_BASE_PPCARCH_H

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

u32 PPCMfhid2(void);
void PPCMthid2(u32 val);
void PPCMtwpar(u32 val);


#define MSR_FP          0x00002000  // floating point available
#define MSR_FE0         0x00000800  // floating point exception enable
#define MSR_FE1         0x00000100  // floating point exception enable
#define MSR_RI          0x00000002  // Recoverable interrupt
#define FPSCR_FX            0x80000000  // Exception summary
#define FPSCR_OX            0x10000000  // Overflow exception
#define FPSCR_UX            0x08000000  // Underflow exception
#define FPSCR_ZX            0x04000000  // Zero divide exception
#define FPSCR_XX            0x02000000  // Inexact exception
#define FPSCR_VXSNAN        0x01000000  // SNaN
#define FPSCR_VXISI         0x00800000  // Infinity - Infinity
#define FPSCR_VXIDI         0x00400000  // Infinity / Infinity
#define FPSCR_VXZDZ         0x00200000  // 0 / 0
#define FPSCR_VXIMZ         0x00100000  // Infinity * 0
#define FPSCR_VXVC          0x00080000  // Invalid compare
#define FPSCR_FI            0x00020000  // Fraction inexact
#define FPSCR_VXSOFT        0x00000400  // Software request
#define FPSCR_VXSQRT        0x00000200  // Invalid square root
#define FPSCR_VXCVI         0x00000100  // Invalid integer convert
#define FPSCR_VE            0x00000080  // Invalid operation exception enable
#define FPSCR_OE            0x00000040  // Overflow exception enable
#define FPSCR_UE            0x00000020  // Underflow exception enable
#define FPSCR_ZE            0x00000010  // Zero divide exception enable
#define FPSCR_XE            0x00000008  // Inexact exception enable
#define FPSCR_NI            0x00000004  // Non-IEEE mode

u32 PPCMfmsr();
void PPCMtmsr(u32 newMSR);
void PPCSync(void);
void PPCHalt();
u32 PPCMffpscr();
void PPCMtfpscr(u32 newFPSCR);

void PPCMtmmcr0(u32 val);
void PPCMtmmcr1(u32 val);
void PPCMtpmc1(u32 val);
void PPCMtpmc2(u32 val);
void PPCMtpmc3(u32 val);
void PPCMtpmc4(u32 val);
void PPCDisableSpeculation(void);
void PPCSetFpNonIEEEMode(void);
u32 PPCMfhid0(void);
u32 PPCMfl2cr(void);
void PPCMtl2cr(u32 val);
void PPCMtdec(u32 val);
#define MSR_IR (1 << (31 - 26))
#define MSR_DR (1 << (31 - 27))
#define HID0_ICE (1 << (31 - 16))
#define HID0_DCE (1 << (31 - 17))
#define L2CR_L2E (1 << (31 - 0))
#define L2CR_L2I (1 << (31 - 10))
#define HID2_DCHERR (1 << (31 - 8))
#define HID2_DNCERR (1 << (31 - 9))
#define HID2_DCMERR (1 << (31 - 10))
#define HID2_DQOERR (1 << (31 - 11))
#define SRR1_DMA_BIT 0x00200000

#ifdef __cplusplus
}
#endif

#endif
