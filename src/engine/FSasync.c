/* Host file reads over the development kit's EXI channel 2: request packets, block-by-block
   transfers driven by the EXI transfer-complete interrupt, and the acknowledgement that ends a
   transfer. The SN runtime's host-file and DVD-emulation code uses it to read files from the
   host PC. */

#include <dolphin/os.h>

#define EXI2_CPR (*(volatile u32 *)0xCC006828)
#define EXI2_CR (*(volatile u32 *)0xCC006834)
#define PI_INTSR (*(volatile u32 *)0xCC003000)

typedef struct FSReadHeader_t {
    u8 mCommand;
    u8 mUnknown1;
    u16 mLength;
    u8 mUnknown4[4];
    u8 mMode;
    u8 mUnknown9[3];
    int mHandle;
    int mOffset;
    u32 mSize;
} FSReadHeader_t;

typedef struct FSResult_t {
    u8 mUnknown0[2];
    u16 mUnknown2;
    u8 mUnknown4[4];
    int mResult;
} FSResult_t;

typedef void (*FSCallback_t)(int result);

volatile int g_nRWasyncPhase = 0;
FSCallback_t g_FSCBFunc = 0;
int g_nEXI2TCCnt = 0;
int g_nDbgFsAsyncCnt = 0;

int g_hHandle;
u8 *g_pBuffer;
volatile int g_nBlockCnt;
volatile u32 g_nRemainderCnt;
volatile u32 g_nTotalBytesRemaining;
int g_bDoFSACK;
int g_nFSLastError;
FSResult_t g_FsResult;

extern int fn_801ACB9C(void);
extern int fn_801ACC24(void *buf, int size);
extern int fn_801ACDE0(void *buf, int size);
extern void fn_801AD11C(void);
extern void fn_801AD16C(u8 *buf, u32 size);
extern void fn_801AD1DC(u8 *buf, u32 size);
extern void fn_801AD244(int size);
extern void fn_801AD380(void *data, int size);

static inline u16 _FSSwap16(u16 value)
{
    return (value << 8) | (value >> 8);
}

int PCwriteAsyncInit(void)
{
    return -1;
}

void DoFSReadHeader(int handle, u8 *buf, u32 size, int offset)
{
    FSReadHeader_t packet;
    u8 *p;
    int i;
    u16 len;

    // FAKEMATCH: local set before the loop only so the swap is not constant-folded
    len = 0x10;
    p = (u8 *)&packet;
    for (i = 0; i < sizeof(packet); i++)
        *p++ = 0;
    packet.mCommand = 9;
    packet.mLength = _FSSwap16(len);
    if (g_bDoFSACK)
        packet.mMode = 9;
    else
        packet.mMode = 11;
    packet.mHandle = handle;
    packet.mOffset = offset;
    packet.mSize = size;
    fn_801AD244(sizeof(packet));
    fn_801AD380(&packet, sizeof(packet));
}

void InitReadCounts(void)
{
    u32 size;

    if (g_nTotalBytesRemaining > 0x1FC00)
        size = 0x1FC00;
    else
        size = g_nTotalBytesRemaining;
    g_nTotalBytesRemaining -= size;
    g_nRWasyncPhase = 2;
    g_nBlockCnt = size >> 10;
    g_nRemainderCnt = size & 0x3FF;
}

void PCreadAsyncNext(void)
{
    u8 *buf;
    u32 size;

    buf = g_pBuffer;
    PI_INTSR = 0x1000;
    InitReadCounts();
    if (g_nBlockCnt) {
        size = 0x400;
        g_pBuffer += 0x400;
        g_nBlockCnt--;
    } else {
        size = g_nRemainderCnt;
        g_nRemainderCnt = 0;
    }
    fn_801AD11C();
    fn_801AD16C(buf, size);
}

int CompleteAsync(void);

int PCreadAsyncInit(int handle, u8 *buf, u32 size, FSCallback_t callback, int offset, int mode)
{
    if (((u32)buf & 0x1F) == 0 && (size & 0x1F) == 0) {
        CompleteAsync();
        g_bDoFSACK = mode;
        g_FSCBFunc = callback;
        DoFSReadHeader(handle, buf, size, offset);
        g_nTotalBytesRemaining = size;
        g_hHandle = handle;
        g_pBuffer = buf;
        g_nRWasyncPhase = 1;
        return 0;
    }
    return -1;
}

void ReadSyncNext(void)
{
    u8 *buf;
    u32 size;

    buf = g_pBuffer;
    while (fn_801ACB9C() == 0)
        ;
    PI_INTSR = 0x1000;
    InitReadCounts();
    if (g_nBlockCnt) {
        size = 0x400;
        g_nBlockCnt--;
        g_pBuffer += 0x400;
    } else {
        size = g_nRemainderCnt;
        g_nRemainderCnt = 0;
    }
    fn_801AD11C();
    fn_801AD1DC(buf, size);
}

void PCrwSyncFSACK(void);

static inline void _FSDrainReadBlocks(void)
{
    while (--g_nBlockCnt != -1) {
        fn_801AD1DC(g_pBuffer, 0x400);
        g_pBuffer += 0x400;
    }
    if (g_nRemainderCnt) {
        fn_801AD1DC(g_pBuffer, g_nRemainderCnt);
        g_nRemainderCnt = 0;
    }
    EXI2_CPR = 0;
}

void CompletePCreadAsync(void)
{
    if (g_nRWasyncPhase == 1)
        ReadSyncNext();
    while (EXI2_CR & 1)
        ;
    _FSDrainReadBlocks();
    while (g_nTotalBytesRemaining) {
        ReadSyncNext();
        _FSDrainReadBlocks();
    }
    PCrwSyncFSACK();
}

void PCrwAsyncFSACK(void)
{
    FSResult_t *reply;
    int size;

    reply = &g_FsResult;
    while ((size = fn_801ACB9C()) == 0)
        ;
    fn_801ACC24(reply, size);
    reply->mUnknown2 = 0;
    g_nFSLastError = reply->mResult;
    fn_801ACDE0(reply, 8);
    g_nRWasyncPhase = 0;
    if (g_FSCBFunc) {
        g_FSCBFunc(g_nFSLastError);
        g_FSCBFunc = 0;
    }
    PI_INTSR = 0x1000;
}

void PCrwSyncFSACK(void)
{
    FSResult_t *reply;
    int size;

    reply = &g_FsResult;
    if (g_bDoFSACK) {
        while ((size = fn_801ACB9C()) == 0)
            ;
        fn_801ACC24(reply, size);
        reply->mUnknown2 = 0;
        g_nFSLastError = reply->mResult;
        fn_801ACDE0(reply, 8);
        g_nRWasyncPhase = 0;
        if (g_FSCBFunc) {
            g_FSCBFunc(g_nFSLastError);
            g_FSCBFunc = 0;
        }
    }
    g_FSCBFunc = 0;
    EXI2_CPR = 8;
    PI_INTSR = 0x1000;
    g_nRWasyncPhase = 0;
}

int CompleteAsync(void)
{
    if (g_nRWasyncPhase == 0)
        return 0;
    if (g_nRWasyncPhase == 5)
        PCrwSyncFSACK();
    else
        CompletePCreadAsync();
    return g_nFSLastError;
}

void PCrwAsyncNextPh(u32 state)
{
    switch (state) {
    case 1:
        PCreadAsyncNext();
        break;
    case 2:
    case 4:
        g_nDbgFsAsyncCnt++;
        break;
    case 3:
        break;
    case 5:
        PCrwAsyncFSACK();
        break;
    }
}

void EXI2TCHandler(__OSInterrupt interrupt, OSContext *context)
{
    u8 *buf;
    u32 size;

    buf = g_pBuffer;
    g_nEXI2TCCnt++;
    EXI2_CPR = 0x88;
    if (g_nRWasyncPhase == 0)
        return;
    if (g_nBlockCnt) {
        if (g_nRWasyncPhase == 4) {
            g_pBuffer = buf + 0x200;
            size = 0x200;
        } else {
            g_pBuffer = buf + 0x400;
            size = 0x400;
        }
        g_nBlockCnt--;
    } else if (g_nRemainderCnt) {
        size = g_nRemainderCnt;
        g_nRemainderCnt = 0;
    } else {
        EXI2_CPR = 0;
        if (g_nTotalBytesRemaining) {
            if (g_nRWasyncPhase != 4)
                g_nRWasyncPhase = 1;
        } else if (g_bDoFSACK) {
            g_nRWasyncPhase = 5;
        } else {
            g_nRWasyncPhase = 0;
            g_nFSLastError = 0;
            if (g_FSCBFunc) {
                g_FSCBFunc(0);
                g_FSCBFunc = 0;
            }
        }
        return;
    }
    fn_801AD16C(buf, size);
}

void SNInitEXI2TCHandler(void)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_2_TC, EXI2TCHandler);
    __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_2_TC);
    EXI2_CPR |= 8;
    EXI2_CPR &= ~4;
    OSRestoreInterrupts(enabled);
}
