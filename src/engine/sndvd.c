/* Emulates DVD commands through the host file server and a DABR data-breakpoint handler. */
#include "engine/sndvd.h"
#include "engine/FSasync.h"

#define DI_CMDBUF0 (*(volatile u32 *)0xCC006008)
#define DI_CMDBUF1 (*(volatile u32 *)0xCC00600C)
#define DI_CMDBUF2 (*(volatile u32 *)0xCC006010)
#define DI_MAR (*(volatile u32 *)0xCC006014)
#define DI_LENGTH (*(volatile u32 *)0xCC006018)
#define DI_CR (*(volatile u32 *)0xCC00601C)
#define DI_IMMBUF (*(volatile u32 *)0xCC006020)

int g_hDVD = 0;

int g_nDvdAudioCfg = 0;
u8 g_aBuffer[32] ATTRIBUTE_ALIGN(32) = {0};
u32 g_nDvdError = 0;
int g_nDvdCurrOffset = 0;
int g_nDvdReadLength = 0;
int g_nBaseOffset = 0;
u8 g_nEmuState = 0;
u8 g_nLidState = 0;

extern int SN_DSI;

extern void DSIExcHandler(__OSException exception, OSContext *context);

void DisDvdBP(void)
{
    u32 value = 0;

    asm volatile("lwz 3,%0\n\tmtspr 1013,3\n\tisync" : : "m"(value) : "r3");
}

void EnaDvdBP(void)
{
    u32 value = 0xCC00601E;

    asm volatile("lwz 3,%0\n\tmtspr 1013,3\n\tisync" : : "m"(value) : "r3");
}

void ForceDvdTcIrq(void *dst)
{
    DisDvdBP();
    DI_CMDBUF0 = 0x12000000;
    DI_CMDBUF1 = 0;
    DI_CMDBUF2 = 0x20;
    DI_LENGTH = 0x20;
    DI_MAR = (u32)dst;
    DI_CR = 3;
    EnaDvdBP();
}

void ForceDvdDeIrq(void)
{
    DisDvdBP();
    DI_CMDBUF0 = 0;
    DI_CR = 1;
    EnaDvdBP();
}

void DvdCallback(int result)
{
    int size;

    size = (result + 31) & ~31;
    if (size == g_nDvdReadLength) {
        g_nDvdError = 0;
        g_nDvdCurrOffset += size;
        ForceDvdTcIrq(g_aBuffer);
    } else {
        g_nDvdCurrOffset = -1;
        g_nDvdError = 0x31100;
        ForceDvdDeIrq();
    }
}

u32 CheckSeekOffset(int offset)
{
    if (offset >= 0x57060000)
        return 0x52100;
    return 0;
}

// FAKEMATCH: Give the hand-written exception symbols separate input sections
// for whole-function retention; comparisons keep the contiguous exception block.
asm(
#ifndef DECOMP_COMPARE
    ".section .text.DSIExcHandler,\"ax\"\n"
#endif
    ".globl DSIExcHandler\n"
    ".type DSIExcHandler,@function\n"
    "DSIExcHandler:\n"
    "\tmfdsisr 5\n"
    "\trlwinm. 5,5,10,31,31\n"
    "\tbeq 1f\n"
    "\tstw 0,0(4)\n"
    "\tstw 1,4(4)\n"
    "\tstw 2,8(4)\n"
    "\tstmw 6,24(4)\n"
    "\tmfspr 0,913\n"
    "\tstw 0,424(4)\n"
    "\tmfspr 0,914\n"
    "\tstw 0,428(4)\n"
    "\tmfspr 0,915\n"
    "\tstw 0,432(4)\n"
    "\tmfspr 0,916\n"
    "\tstw 0,436(4)\n"
    "\tmfspr 0,917\n"
    "\tstw 0,440(4)\n"
    "\tmfspr 0,918\n"
    "\tstw 0,444(4)\n"
    "\tmfspr 0,919\n"
    "\tstw 0,448(4)\n"
    "\tmfdsisr 5\n"
    "\tmfdar 6\n"
    "\tb DSIHandler\n"
    "1:\n"
    "\tlwz 3,128(4)\n"
    "\tmtcrf 255,3\n"
    "\tlwz 3,132(4)\n"
    "\tmtlr 3\n"
    "\tlwz 3,136(4)\n"
    "\tmtctr 3\n"
    "\tlwz 3,140(4)\n"
    "\tmtxer 3\n"
    "\tlwz 3,408(4)\n"
    "\tmtsrr0 3\n"
    "\tlwz 3,412(4)\n"
    "\tmtsrr1 3\n"
    "\tlwz 3,12(4)\n"
    "\tlwz 5,20(4)\n"
    "\tlwz 4,16(4)\n"
    "\tb DSIentry\n"
    ".size DSIExcHandler,.-DSIExcHandler\n"
    "\n"
#ifndef DECOMP_COMPARE
    ".section .text.DSIHandlerZeroEntry,\"ax\"\n"
#endif
    ".globl DSIHandlerZeroEntry\n"
    ".type DSIHandlerZeroEntry,@function\n"
    "DSIHandlerZeroEntry:\n"
    "\tli 3,0\n"
    "\tli 4,0\n"
    "\tli 5,0\n"
    "\tli 6,0\n"
    "\tbl DSIHandler\n"
    ".size DSIHandlerZeroEntry,.-DSIHandlerZeroEntry\n");

void DSIHandler(int unused, OSContext *context, u32 dsisr, u32 dar)
{
    u32 regs[10];
    u32 insn;
    u32 addr;
    u32 offset;
    int command;
    int i;

    insn = *(u32 *)context->srr0;
    addr = insn & 0xFFFF;
    if (insn & 0x8000)
        addr |= 0xFFFF0000;
    addr += context->gpr[(insn >> 16) & 0x1F];
    if (dar == 0xCC00601C) {
        for (i = 0; i < 10; i++)
            regs[i] = *(u32 *)((0x0C006000 + i * 4) | 0xC0000000);
        command = regs[2] >> 16;
        offset = g_nBaseOffset + (regs[3] << 2);
        switch (command) {
        case 0x1200:
            ForceDvdTcIrq((void *)regs[5]);
            break;
        case 0xA800:
            if (regs[6] == 0) {
                ForceDvdTcIrq(g_aBuffer);
            } else {
                g_nDvdError = CheckSeekOffset(offset);
                if (g_nDvdError == 0) {
                    g_nDvdReadLength = regs[6];
                    if (PCreadAsyncInit(g_hDVD, (u8 *)regs[5], regs[6], DvdCallback, offset, 1) == -1)
                        g_nDvdError = 0x31100;
                }
            }
            if (g_nDvdError)
                ForceDvdDeIrq();
            break;
        case 0xE000:
            DI_IMMBUF = g_nDvdError;
            g_nDvdError &= 0xFF000000;
            ForceDvdTcIrq(g_aBuffer);
            break;
        case 0xE100:
        case 0xE200:
        case 0xE401:
            if (g_nDvdAudioCfg)
                goto passthrough;
        case 0xAB00:
        case 0xE300:
            ForceDvdTcIrq(g_aBuffer);
            break;
        default:
            OSReport("Unknown DVD cmd (%08X)\n", regs[2]);
            asm volatile(".long 1");
            g_nDvdError = 0x52000;
            ForceDvdDeIrq();
            break;
        }
    } else {
    passthrough:
        DisDvdBP();
        *(u32 *)addr = context->gpr[(insn >> 21) & 0x1F];
        EnaDvdBP();
    }
    context->srr0 += 4;
    OSLoadContext(context);
}

void SNDVDEmuInit(int id)
{
    if (id == -0x8000) {
        g_hDVD = id;
        SN_DSI = 0;
    }
}

void SNDVDEmuInitDSIHandler(void)
{
    if (g_hDVD == -0x8000) {
        g_nDvdAudioCfg = 0;
        g_nDvdError = 0;
        g_nDvdCurrOffset = -1;
        g_nBaseOffset = 0;
        g_nLidState = 1;
        g_nEmuState = 1;
        EnaDvdBP();
        __OSSetExceptionHandler(__OS_EXCEPTION_DSI, DSIExcHandler);
    }
}

u32 SNDVDEmuControl(int request)
{
    u32 result = 0;

    if (g_hDVD != -0x8000)
        return 0;
    switch (request) {
    case 0:
        g_nLidState = 0;
        break;
    case 1:
        g_nLidState = 1;
        break;
    case 2:
        g_nEmuState = 0;
        DisDvdBP();
        result = 0x80000000;
        break;
    case 3:
        g_nEmuState = 1;
        EnaDvdBP();
        result = 0x80000000;
        break;
    }
    return result | (g_nEmuState << 8) | g_nLidState;
}
