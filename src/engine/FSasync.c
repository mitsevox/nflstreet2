#include <dolphin/os.h>

#define EXI2_CPR (*(volatile u32 *)0xCC006828)
#define EXI2_CR (*(volatile u32 *)0xCC006834)
#define PI_INTSR (*(volatile u32 *)0xCC003000)

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

extern int fn_801ACB9C(void);
extern int fn_801ACC24(void *buf, int size);
extern int fn_801ACDE0(void *buf, int size);
extern void fn_801AD11C(void);
extern void fn_801AD16C(u8 *buf, u32 size);
extern void fn_801AD1DC(u8 *buf, u32 size);
extern void fn_801AD244(int size);
extern void fn_801AD380(void *data, int size);

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

void fn_801ADB94(u32 state)
{
    switch (state) {
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
