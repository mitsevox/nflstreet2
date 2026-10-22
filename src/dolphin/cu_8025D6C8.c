/* Partial source for the SDK range 0x8025D6C8-0x8025E148 (neutral file name). */

#include <dolphin/types.h>
#include <dolphin/os.h>
#include <dolphin/hw_regs.h>

typedef void (*Callback_8025DAAC)(int);
typedef void (*Callback_8025DA58)(u32, OSContext *);

void fn_8025D6C8(void);
void fn_8025D6CC(void);
BOOL fn_8025D6D0(const void *pData, u32 size);
BOOL fn_8025D930(u32 *pData, s32 size);
u32 fn_8025D9BC(void);
void fn_8025DA58(void);
void fn_8025DAAC(u8 **ppFlag, Callback_8025DAAC callback);
void fn_8025DB24(__OSInterrupt interrupt, OSContext *context);
void fn_8025DB64(u32 value, OSContext *context);
BOOL fn_8025DBA0(u32 *pValue);
BOOL fn_8025DC4C(u32 address, const void *pData, s32 size);
BOOL fn_8025DD28(u32 address, u32 *pData, s32 size);
BOOL fn_8025DE04(u32 *pValue);
BOOL fn_8025DEB0(void *pData, s32 size, u32 write);

static Callback_8025DAAC lbl_803ED3F8;
static Callback_8025DA58 lbl_803ED3FC;
static u32 lbl_803ED400;
static s32 lbl_803ED404;
static u8 *lbl_803ED408;
static u8 lbl_803ED40C;
static u8 lbl_803EC320 = 0x80;

static inline void Exi2Select(u32 device)
{
    u32 value = __EXIRegs[10];

    value &= 0x405;
    value |= 0x80 | (device << 4);
    __EXIRegs[10] = value;
}

static inline BOOL Exi2Deselect(void)
{
    __EXIRegs[10] &= 0x405;
    return TRUE;
}

static inline BOOL Exi2Sync(void)
{
    while (__EXIRegs[13] & 1) {
    }
    return TRUE;
}

BOOL fn_8025DEB0(void *pData, s32 size, u32 write)
{
    u8 *p;
    u32 value;
    int i;

    if (write) {
        value = 0;
        for (i = 0; i < size; i++) {
            p = (u8 *)pData + i;
            value |= *p << ((3 - i) << 3);
        }
        __EXIRegs[14] = value;
    }

    __EXIRegs[13] = 1 | write << 2 | (size - 1) << 4;
    while (__EXIRegs[13] & 1) {
    }

    if (!write) {
        value = __EXIRegs[14];
        p = pData;
        for (i = 0; i < size; i++) {
            *p++ = value >> ((3 - i) << 3);
        }
    }

    return TRUE;
}

static inline void CheckMailbox(void)
{
    u32 value;

    fn_8025DBA0(&value);
    if (value & 1) {
        fn_8025DE04(&value);
        value &= 0x1FFFFFFF;
        if ((value & 0x1F000000) == 0x1F000000) {
            lbl_803ED400 = value;
            lbl_803ED404 = value & 0x7FFF;
            lbl_803ED40C = 1;
        }
    }
}

u32 fn_8025D9BC(void)
{
    BOOL enabled;

    lbl_803ED40C = 0;
    if (!lbl_803ED404) {
        enabled = OSDisableInterrupts();
        CheckMailbox();
        OSRestoreInterrupts(enabled);
    }
    return lbl_803ED404;
}

BOOL fn_8025DE04(u32 *pValue)
{
    BOOL error = FALSE;
    u32 command;

    Exi2Select(4);
    command = 0x60000000;
    error |= !fn_8025DEB0(&command, 2, 1);
    error |= !Exi2Sync();
    error |= !fn_8025DEB0(pValue, 4, 0);
    error |= !Exi2Sync();
    error |= !Exi2Deselect();
    return !error;
}

static inline BOOL WriteMailbox(u32 value)
{
    BOOL error = FALSE;
    u32 command;

    Exi2Select(4);
    command = (value & 0x1FFFFFFF) | 0xC0000000;
    error |= !fn_8025DEB0(&command, 4, 1);
    error |= !Exi2Sync();
    error |= !Exi2Deselect();
    return !error;
}

BOOL fn_8025DD28(u32 address, u32 *pData, s32 size)
{
    BOOL error = FALSE;
    u32 *p = pData;
    u32 command;
    u32 value;

    Exi2Select(4);
    command = (address & 0x1FFFC) << 8 | 0x20000000;
    error |= !fn_8025DEB0(&command, 4, 1);
    error |= !Exi2Sync();

    while (size) {
        error |= !fn_8025DEB0(&value, 4, 0);
        error |= !Exi2Sync();
        *p++ = value;
        size -= 4;
        if (size < 0) {
            size = 0;
        }
    }

    error |= !Exi2Deselect();
    return !error;
}

BOOL fn_8025DC4C(u32 address, const void *pData, s32 size)
{
    BOOL error = FALSE;
    const u32 *p = pData;
    u32 command;
    u32 value;

    Exi2Select(4);
    command = (address & 0x1FFFC) << 8 | 0xA0000000;
    error |= !fn_8025DEB0(&command, 4, 1);
    error |= !Exi2Sync();

    while (size) {
        value = *p++;
        error |= !fn_8025DEB0(&value, 4, 1);
        error |= !Exi2Sync();
        size -= 4;
        if (size < 0) {
            size = 0;
        }
    }

    error |= !Exi2Deselect();
    return !error;
}

BOOL fn_8025DBA0(u32 *pValue)
{
    BOOL error = FALSE;
    u32 command;

    Exi2Select(4);
    command = 0x40000000;
    error |= !fn_8025DEB0(&command, 2, 1);
    error |= !Exi2Sync();
    error |= !fn_8025DEB0(pValue, 4, 0);
    error |= !Exi2Sync();
    error |= !Exi2Deselect();
    return !error;
}

void fn_8025DB64(u32 value, OSContext *context)
{
    lbl_803ED40C = 1;
    if (lbl_803ED3F8) {
        lbl_803ED3F8(0);
    }
}

void fn_8025DB24(__OSInterrupt interrupt, OSContext *context)
{
    __PIRegs[0] = 0x1000;
    if (lbl_803ED3FC) {
        lbl_803ED3FC(interrupt, context);
    }
}

void fn_8025DAAC(u8 **ppFlag, Callback_8025DAAC callback)
{
    BOOL enabled = OSDisableInterrupts();

    lbl_803ED408 = &lbl_803ED40C;
    *ppFlag = lbl_803ED408;
    lbl_803ED3F8 = callback;
    __OSMaskInterrupts(0x18000);
    __EXIRegs[10] = 0;
    OSRestoreInterrupts(enabled);
}

void fn_8025DA58(void)
{
    __OSMaskInterrupts(0x18000);
    __OSMaskInterrupts(0x40);
    lbl_803ED3FC = fn_8025DB64;
    __OSSetInterruptHandler(25, fn_8025DB24);
    __OSUnmaskInterrupts(0x40);
}

BOOL fn_8025D930(u32 *pData, s32 size)
{
    BOOL enabled = OSDisableInterrupts();
    u32 bank = lbl_803ED400 & 0x10000 ? 0x1000 : 0;

    fn_8025DD28(bank + 0x1E000, pData, (size + 3) & ~3);
    lbl_803ED404 = 0;
    lbl_803ED40C = 0;
    OSRestoreInterrupts(enabled);
    return FALSE;
}

BOOL fn_8025D6D0(const void *pData, u32 size)
{
    u32 value;
    u32 status;
    BOOL enabled = OSDisableInterrupts();

    do {
        fn_8025DBA0(&status);
    } while (status & 2);

    lbl_803EC320++;
    value = (lbl_803EC320 & 1) ? 0x1000 : 0;

    while (!fn_8025DC4C(value | 0x1C000, pData, (size + 3) & ~3)) {
    }

    do {
        fn_8025DBA0(&status);
    } while (status & 2);

    value = lbl_803EC320;
    while (!WriteMailbox(0x1F000000 | value << 16 | size)) {
    }

    do {
        while (!fn_8025DBA0(&status)) {
        }
    } while (status & 2);

    OSRestoreInterrupts(enabled);
    return FALSE;
}

void fn_8025D6CC(void)
{
}

void fn_8025D6C8(void)
{
}
