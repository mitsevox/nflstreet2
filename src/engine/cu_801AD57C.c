#include <dolphin/os.h>

#define EXI2_CPR (*(volatile u32 *)0xCC006828)
#define EXI2_CR (*(volatile u32 *)0xCC006834)
#define PI_INTSR (*(volatile u32 *)0xCC003000)

#define DI_CMDBUF0 (*(volatile u32 *)0xCC006008)
#define DI_CMDBUF1 (*(volatile u32 *)0xCC00600C)
#define DI_CMDBUF2 (*(volatile u32 *)0xCC006010)
#define DI_MAR (*(volatile u32 *)0xCC006014)
#define DI_LENGTH (*(volatile u32 *)0xCC006018)
#define DI_CR (*(volatile u32 *)0xCC00601C)
#define DI_IMMBUF (*(volatile u32 *)0xCC006020)

typedef struct Packet_801AD584 {
    u8 mCommand;
    u8 mUnknown1;
    u16 mLength;
    u8 mUnknown4[4];
    u8 mMode;
    u8 mUnknown9[3];
    int mHandle;
    int mOffset;
    u32 mSize;
} Packet_801AD584;

typedef struct Reply_802CC5C0 {
    u8 mUnknown0[2];
    u16 mUnknown2;
    u8 mUnknown4[4];
    int mResult;
} Reply_802CC5C0;

typedef void (*Callback_802CC584)(int result);

extern volatile int lbl_802CC580;
extern Callback_802CC584 lbl_802CC584;
extern int lbl_802CC588;
extern int lbl_802CC58C;
extern int lbl_802CC5A0;
extern u8 *lbl_802CC5A4;
extern volatile int lbl_802CC5A8;
extern volatile u32 lbl_802CC5AC;
extern volatile u32 lbl_802CC5B0;
extern int lbl_802CC5B4;
extern int lbl_802CC5B8;
extern Reply_802CC5C0 lbl_802CC5C0;
extern int lbl_802CC5E0;
extern int lbl_802CC600;
extern u8 lbl_802CC620[32];
extern u32 lbl_802CC640;
extern int lbl_802CC644;
extern int lbl_802CC648;
extern int lbl_802CC64C;
extern u8 lbl_802CC650;
extern u8 lbl_802CC651;
extern int lbl_802C2A5C;

extern int fn_801ACB9C(void);
extern void fn_801ACC24(Reply_802CC5C0 *reply, int size);
extern void fn_801ACDE0(Reply_802CC5C0 *reply, int size);
extern void fn_801AD11C(void);
extern void fn_801AD16C(u8 *buf, u32 size);
extern void fn_801AD1DC(u8 *buf, u32 size);
extern void fn_801AD244(int size);
extern void fn_801AD380(void *data, int size);
extern void fn_801ADF64(__OSException exception, OSContext *context);

static inline u16 Swap16_801AD584(u16 value)
{
    return (value << 8) | (value >> 8);
}

int fn_801AD57C(void)
{
    return -1;
}

void fn_801AD584(int handle, u8 *buf, u32 size, int offset)
{
    Packet_801AD584 packet;
    u8 *p;
    int i;

    p = (u8 *)&packet;
    for (i = 0; i < sizeof(packet); i++)
        *p++ = 0;
    packet.mCommand = 9;
    packet.mLength = Swap16_801AD584(0x10);
    if (lbl_802CC5B4)
        packet.mMode = 9;
    else
        packet.mMode = 11;
    packet.mHandle = handle;
    packet.mOffset = offset;
    packet.mSize = size;
    fn_801AD244(sizeof(packet));
    fn_801AD380(&packet, sizeof(packet));
}

void fn_801AD610(void)
{
    u32 size;

    if (lbl_802CC5B0 > 0x1FC00)
        size = 0x1FC00;
    else
        size = lbl_802CC5B0;
    lbl_802CC5B0 -= size;
    lbl_802CC580 = 2;
    lbl_802CC5A8 = size >> 10;
    lbl_802CC5AC = size & 0x3FF;
}

void fn_801AD66C(void)
{
    u8 *buf;
    u32 size;

    buf = lbl_802CC5A4;
    PI_INTSR = 0x1000;
    fn_801AD610();
    if (lbl_802CC5A8) {
        size = 0x400;
        lbl_802CC5A4 += 0x400;
        lbl_802CC5A8--;
    } else {
        size = lbl_802CC5AC;
        lbl_802CC5AC = 0;
    }
    fn_801AD11C();
    fn_801AD16C(buf, size);
}

int fn_801ADB40(void);

int fn_801AD6F8(int handle, u8 *buf, u32 size, Callback_802CC584 callback, int offset, int mode)
{
    if (((u32)buf & 0x1F) == 0 && (size & 0x1F) == 0) {
        fn_801ADB40();
        lbl_802CC5B4 = mode;
        lbl_802CC584 = callback;
        fn_801AD584(handle, buf, size, offset);
        lbl_802CC5B0 = size;
        lbl_802CC5A0 = handle;
        lbl_802CC5A4 = buf;
        lbl_802CC580 = 1;
        return 0;
    }
    return -1;
}

void fn_801AD79C(void)
{
    u8 *buf;
    u32 size;

    buf = lbl_802CC5A4;
    while (fn_801ACB9C() == 0)
        ;
    PI_INTSR = 0x1000;
    fn_801AD610();
    if (lbl_802CC5A8) {
        size = 0x400;
        lbl_802CC5A8--;
        lbl_802CC5A4 += 0x400;
    } else {
        size = lbl_802CC5AC;
        lbl_802CC5AC = 0;
    }
    fn_801AD11C();
    fn_801AD1DC(buf, size);
}

void fn_801ADA68(void);

static inline void Drain_801AD83C(void)
{
    while (--lbl_802CC5A8 != -1) {
        fn_801AD1DC(lbl_802CC5A4, 0x400);
        lbl_802CC5A4 += 0x400;
    }
    if (lbl_802CC5AC) {
        fn_801AD1DC(lbl_802CC5A4, lbl_802CC5AC);
        lbl_802CC5AC = 0;
    }
    EXI2_CPR = 0;
}

void fn_801AD83C(void)
{
    if (lbl_802CC580 == 1)
        fn_801AD79C();
    while (EXI2_CR & 1)
        ;
    Drain_801AD83C();
    while (lbl_802CC5B0) {
        fn_801AD79C();
        Drain_801AD83C();
    }
    fn_801ADA68();
}

void fn_801AD9C0(void)
{
    Reply_802CC5C0 *reply;
    int size;

    reply = &lbl_802CC5C0;
    while ((size = fn_801ACB9C()) == 0)
        ;
    fn_801ACC24(reply, size);
    reply->mUnknown2 = 0;
    lbl_802CC5B8 = reply->mResult;
    fn_801ACDE0(reply, 8);
    lbl_802CC580 = 0;
    if (lbl_802CC584) {
        lbl_802CC584(lbl_802CC5B8);
        lbl_802CC584 = 0;
    }
    PI_INTSR = 0x1000;
}

void fn_801ADA68(void)
{
    Reply_802CC5C0 *reply;
    int size;

    reply = &lbl_802CC5C0;
    if (lbl_802CC5B4) {
        while ((size = fn_801ACB9C()) == 0)
            ;
        fn_801ACC24(reply, size);
        reply->mUnknown2 = 0;
        lbl_802CC5B8 = reply->mResult;
        fn_801ACDE0(reply, 8);
        lbl_802CC580 = 0;
        if (lbl_802CC584) {
            lbl_802CC584(lbl_802CC5B8);
            lbl_802CC584 = 0;
        }
    }
    lbl_802CC584 = 0;
    EXI2_CPR = 8;
    PI_INTSR = 0x1000;
    lbl_802CC580 = 0;
}

int fn_801ADB40(void)
{
    if (lbl_802CC580 == 0)
        return 0;
    if (lbl_802CC580 == 5)
        fn_801ADA68();
    else
        fn_801AD83C();
    return lbl_802CC5B8;
}

void fn_801ADB94(u32 event)
{
    switch (event) {
    case 1:
        fn_801AD66C();
        break;
    case 2:
    case 4:
        lbl_802CC58C++;
        break;
    case 3:
        break;
    case 5:
        fn_801AD9C0();
        break;
    }
}

void fn_801ADC08(__OSInterrupt interrupt, OSContext *context)
{
    u8 *buf;
    u32 size;

    buf = lbl_802CC5A4;
    lbl_802CC588++;
    EXI2_CPR = 0x88;
    if (lbl_802CC580 == 0)
        return;
    if (lbl_802CC5A8) {
        if (lbl_802CC580 == 4) {
            lbl_802CC5A4 = buf + 0x200;
            size = 0x200;
        } else {
            lbl_802CC5A4 = buf + 0x400;
            size = 0x400;
        }
        lbl_802CC5A8--;
    } else if (lbl_802CC5AC) {
        size = lbl_802CC5AC;
        lbl_802CC5AC = 0;
    } else {
        EXI2_CPR = 0;
        if (lbl_802CC5B0) {
            if (lbl_802CC580 != 4)
                lbl_802CC580 = 1;
        } else if (lbl_802CC5B4) {
            lbl_802CC580 = 5;
        } else {
            lbl_802CC580 = 0;
            lbl_802CC5B8 = 0;
            if (lbl_802CC584) {
                lbl_802CC584(0);
                lbl_802CC584 = 0;
            }
        }
        return;
    }
    fn_801AD16C(buf, size);
}

void fn_801ADD44(void)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_2_TC, fn_801ADC08);
    __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_2_TC);
    EXI2_CPR |= 8;
    EXI2_CPR &= ~4;
    OSRestoreInterrupts(enabled);
}

void fn_801ADDB4(void)
{
    u32 value = 0;

    asm volatile("lwz 3,%0\n\tmtspr 1013,3\n\tisync" : : "m"(value) : "r3");
}

void fn_801ADDD4(void)
{
    u32 value = 0xCC00601E;

    asm volatile("lwz 3,%0\n\tmtspr 1013,3\n\tisync" : : "m"(value) : "r3");
}

void fn_801ADDF8(void *dst)
{
    fn_801ADDB4();
    DI_CMDBUF0 = 0x12000000;
    DI_CMDBUF1 = 0;
    DI_CMDBUF2 = 0x20;
    DI_LENGTH = 0x20;
    DI_MAR = (u32)dst;
    DI_CR = 3;
    fn_801ADDD4();
}

void fn_801ADE80(void)
{
    fn_801ADDB4();
    DI_CMDBUF0 = 0;
    DI_CR = 1;
    fn_801ADDD4();
}

void fn_801ADEC4(int result)
{
    int size;

    size = (result + 31) & ~31;
    if (size == lbl_802CC648) {
        lbl_802CC640 = 0;
        lbl_802CC644 += size;
        fn_801ADDF8(lbl_802CC620);
    } else {
        lbl_802CC644 = -1;
        lbl_802CC640 = 0x31100;
        fn_801ADE80();
    }
}

u32 fn_801ADF44(int offset)
{
    if (offset >= 0x57060000)
        return 0x52100;
    return 0;
}

void fn_801AE018(int unused, OSContext *context, u32 dsisr, u32 dar);

asm(".globl fn_801ADF64\n"
    ".type fn_801ADF64,@function\n"
    "fn_801ADF64:\n"
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
    "\tb fn_801AE018\n"
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
    "\tb fn_801ABF48\n"
    ".size fn_801ADF64,.-fn_801ADF64\n"
    "\n"
    ".globl fn_801AE004\n"
    ".type fn_801AE004,@function\n"
    "fn_801AE004:\n"
    "\tli 3,0\n"
    "\tli 4,0\n"
    "\tli 5,0\n"
    "\tli 6,0\n"
    "\tbl fn_801AE018\n"
    ".size fn_801AE004,.-fn_801AE004\n");

void fn_801AE018(int unused, OSContext *context, u32 dsisr, u32 dar)
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
        offset = lbl_802CC64C + (regs[3] << 2);
        switch (command) {
        case 0x1200:
            fn_801ADDF8((void *)regs[5]);
            break;
        case 0xA800:
            if (regs[6] == 0) {
                fn_801ADDF8(lbl_802CC620);
            } else {
                lbl_802CC640 = fn_801ADF44(offset);
                if (lbl_802CC640 == 0) {
                    lbl_802CC648 = regs[6];
                    if (fn_801AD6F8(lbl_802CC5E0, (u8 *)regs[5], regs[6], fn_801ADEC4, offset, 1) == -1)
                        lbl_802CC640 = 0x31100;
                }
            }
            if (lbl_802CC640)
                fn_801ADE80();
            break;
        case 0xE000:
            DI_IMMBUF = lbl_802CC640;
            lbl_802CC640 &= 0xFF000000;
            fn_801ADDF8(lbl_802CC620);
            break;
        case 0xE100:
        case 0xE200:
        case 0xE401:
            if (lbl_802CC600)
                goto passthrough;
        case 0xAB00:
        case 0xE300:
            fn_801ADDF8(lbl_802CC620);
            break;
        default:
            OSReport("Unknown DVD cmd (%08X)\n", regs[2]);
            asm volatile(".long 1");
            lbl_802CC640 = 0x52000;
            fn_801ADE80();
            break;
        }
    } else {
    passthrough:
        fn_801ADDB4();
        *(u32 *)addr = context->gpr[(insn >> 21) & 0x1F];
        fn_801ADDD4();
    }
    context->srr0 += 4;
    OSLoadContext(context);
}

void fn_801AE28C(int id)
{
    if (id == -0x8000) {
        lbl_802CC5E0 = id;
        lbl_802C2A5C = 0;
    }
}

void fn_801AE2AC(void)
{
    if (lbl_802CC5E0 == -0x8000) {
        lbl_802CC600 = 0;
        lbl_802CC640 = 0;
        lbl_802CC644 = -1;
        lbl_802CC64C = 0;
        lbl_802CC651 = 1;
        lbl_802CC650 = 1;
        fn_801ADDD4();
        __OSSetExceptionHandler(__OS_EXCEPTION_DSI, fn_801ADF64);
    }
}

u32 fn_801AE328(int request)
{
    u32 result = 0;

    if (lbl_802CC5E0 != -0x8000)
        return 0;
    switch (request) {
    case 0:
        lbl_802CC651 = 0;
        break;
    case 1:
        lbl_802CC651 = 1;
        break;
    case 2:
        lbl_802CC650 = 0;
        fn_801ADDB4();
        result = 0x80000000;
        break;
    case 3:
        lbl_802CC650 = 1;
        fn_801ADDD4();
        result = 0x80000000;
        break;
    }
    return result | (lbl_802CC650 << 8) | lbl_802CC651;
}
