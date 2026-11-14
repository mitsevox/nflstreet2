/* Debugger link over EXI channel 2: lets a development debugger on the host exchange data
   with the running game through the debug adapter's mailbox and its shared RAM, and raises a
   flag when the host sends something. No game code calls it. */

#include <dolphin/types.h>
#include <dolphin/os.h>
#include <dolphin/hw_regs.h>

typedef void (*MTRCallbackType)(int);
typedef void (*DBGCallbackType)(u32, OSContext *);

void DBClose(void);
void DBOpen(void);
BOOL DBWrite(const void *pData, u32 size);
BOOL DBRead(u32 *pData, s32 size);
u32 DBQueryData(void);
void DBInitInterrupts(void);
void DBInitComm(u8 **ppFlag, MTRCallbackType callback);
void DBGHandler(__OSInterrupt interrupt, OSContext *context);
void MWCallback(u32 value, OSContext *context);
BOOL DBGReadStatus(u32 *pValue);
BOOL DBGWrite(u32 address, const void *pData, s32 size);
BOOL DBGRead(u32 address, u32 *pData, s32 size);
BOOL DBGReadMailbox(u32 *pValue);
BOOL DBGEXIImm(void *pData, s32 size, u32 write);

static MTRCallbackType MTRCallback;
static DBGCallbackType DBGCallback;
static u32 RecvMailData;
static s32 RecvDataLeng;
static u8 *pEXIInputFlag;
static u8 EXIInputFlag;
#if defined(DECOMP_COMPARE)
static u8 SendCount = 0x80;
#endif

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

BOOL DBRead(u32 *pData, s32 size)
{
    BOOL enabled = OSDisableInterrupts();
    u32 bank = RecvMailData & 0x10000 ? 0x1000 : 0;

    DBGRead(bank + 0x1E000, pData, (size + 3) & ~3);
    RecvDataLeng = 0;
    EXIInputFlag = 0;
    OSRestoreInterrupts(enabled);
    return FALSE;
}

static inline void CheckMailbox(void)
{
    u32 value;

    DBGReadStatus(&value);
    if (value & 1) {
        DBGReadMailbox(&value);
        value &= 0x1FFFFFFF;
        if ((value & 0x1F000000) == 0x1F000000) {
            RecvMailData = value;
            RecvDataLeng = value & 0x7FFF;
            EXIInputFlag = 1;
        }
    }
}

u32 DBQueryData(void)
{
    BOOL enabled;

    EXIInputFlag = 0;
    if (!RecvDataLeng) {
        enabled = OSDisableInterrupts();
        CheckMailbox();
        OSRestoreInterrupts(enabled);
    }
    return RecvDataLeng;
}

void DBInitInterrupts(void)
{
    __OSMaskInterrupts(0x18000);
    __OSMaskInterrupts(0x40);
    DBGCallback = MWCallback;
    __OSSetInterruptHandler(25, DBGHandler);
    __OSUnmaskInterrupts(0x40);
}

void DBInitComm(u8 **ppFlag, MTRCallbackType callback)
{
    BOOL enabled = OSDisableInterrupts();

    pEXIInputFlag = &EXIInputFlag;
    *ppFlag = pEXIInputFlag;
    MTRCallback = callback;
    __OSMaskInterrupts(0x18000);
    __EXIRegs[10] = 0;
    OSRestoreInterrupts(enabled);
}

void DBGHandler(__OSInterrupt interrupt, OSContext *context)
{
    __PIRegs[0] = 0x1000;
    if (DBGCallback) {
        DBGCallback(interrupt, context);
    }
}

void MWCallback(u32 value, OSContext *context)
{
    EXIInputFlag = 1;
    if (MTRCallback) {
        MTRCallback(0);
    }
}

BOOL DBGReadStatus(u32 *pValue)
{
    BOOL error = FALSE;
    u32 command;

    Exi2Select(4);
    command = 0x40000000;
    error |= !DBGEXIImm(&command, 2, 1);
    error |= !Exi2Sync();
    error |= !DBGEXIImm(pValue, 4, 0);
    error |= !Exi2Sync();
    error |= !Exi2Deselect();
    return !error;
}

BOOL DBGWrite(u32 address, const void *pData, s32 size)
{
    BOOL error = FALSE;
    const u32 *p = pData;
    u32 command;
    u32 value;

    Exi2Select(4);
    command = (address & 0x1FFFC) << 8 | 0xA0000000;
    error |= !DBGEXIImm(&command, 4, 1);
    error |= !Exi2Sync();

    while (size) {
        value = *p++;
        error |= !DBGEXIImm(&value, 4, 1);
        error |= !Exi2Sync();
        size -= 4;
        if (size < 0) {
            size = 0;
        }
    }

    error |= !Exi2Deselect();
    return !error;
}

BOOL DBGRead(u32 address, u32 *pData, s32 size)
{
    BOOL error = FALSE;
    u32 *p = pData;
    u32 command;
    u32 value;

    Exi2Select(4);
    command = (address & 0x1FFFC) << 8 | 0x20000000;
    error |= !DBGEXIImm(&command, 4, 1);
    error |= !Exi2Sync();

    while (size) {
        error |= !DBGEXIImm(&value, 4, 0);
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

BOOL DBGReadMailbox(u32 *pValue)
{
    BOOL error = FALSE;
    u32 command;

    Exi2Select(4);
    command = 0x60000000;
    error |= !DBGEXIImm(&command, 2, 1);
    error |= !Exi2Sync();
    error |= !DBGEXIImm(pValue, 4, 0);
    error |= !Exi2Sync();
    error |= !Exi2Deselect();
    return !error;
}

BOOL DBGEXIImm(void *pData, s32 size, u32 write)
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

#if defined(DECOMP_COMPARE)
static inline BOOL WriteMailbox(u32 value)
{
    BOOL error = FALSE;
    u32 command;

    Exi2Select(4);
    command = (value & 0x1FFFFFFF) | 0xC0000000;
    error |= !DBGEXIImm(&command, 4, 1);
    error |= !Exi2Sync();
    error |= !Exi2Deselect();
    return !error;
}

BOOL DBWrite(const void *pData, u32 size)
{
    u32 value;
    u32 status;
    BOOL enabled = OSDisableInterrupts();

    do {
        DBGReadStatus(&status);
    } while (status & 2);

    SendCount++;
    value = (SendCount & 1) ? 0x1000 : 0;

    while (!DBGWrite(value | 0x1C000, pData, (size + 3) & ~3)) {
    }

    do {
        DBGReadStatus(&status);
    } while (status & 2);

    value = SendCount;
    while (!WriteMailbox(0x1F000000 | value << 16 | size)) {
    }

    do {
        while (!DBGReadStatus(&status)) {
        }
    } while (status & 2);

    OSRestoreInterrupts(enabled);
    return FALSE;
}

void DBOpen(void)
{
}

void DBClose(void)
{
}
#endif
