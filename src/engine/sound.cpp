#include "engine/sound.h"
#include "game/fn_801D2B7C.h"

struct SndSeqInfo_801F438C {
    Res_801EDC2C *pRes;
    unsigned int mIndex;
    int mUnk8;
    void *pData;
    unsigned char mLoaded;
};

struct SndStream_801F44B0 {
    int mHandle;
    void *pBuffer;
};

struct SndAemsBankInfo_801F4D00 {
    int mHandle;
    int mSize;
    void *pData;
    int mBank;
    StreamFile_801F6D54 mFile;
};

struct Desc_801F393C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    unsigned short mUnknown16;
    unsigned short mUnknown18;
    unsigned short mUnknown20;
    unsigned short mUnknown22;
    unsigned short mUnknown24;
    char mUnknown26[6];
    void *mUnknown32;
    int mUnknown36;
    int mUnknown40;
    int mUnknown44;
    int mUnknown48;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
};

struct SndPatchOpts_801F40F4 {
    signed char mVolume;
    unsigned char mUnk1[7];
    unsigned short mPan;
    short mSpan;
    unsigned short mUnkC;
    char mUnkE[10];
};

union SndStatus_8039AEC4 {
    unsigned int mWord;
    struct {
        unsigned char mNoLock;
        unsigned char mActive;
        unsigned char mEnabled;
        unsigned char mUnk3B;
    } mFlags;
};

struct SndState_8039AE8C {
    int mUnk0;
    void *pHeap;
    int mHeapSize;
    void *pBankList;
    void *pAemsBankList;
    void *pSeqList;
    void *pStreamList;
    SndBankEntry_801F50C8 *pBankTable;
    void *pAemsSystem;
    void *pAemsStreams;
    int mUnk28;
    void (*pServiceCallback)(int a, int b);
    int mUnk30;
    void (*pMemLabelCallback)(unsigned char label);
    SndStatus_8039AEC4 mStatus;
    unsigned char mUnk3C;
    StreamFile_801F6D54 *apFileDesc[4];
    int mUnk50;
};

/* The active and enabled bytes tested together as one word. */
#define SND_READY() ((lbl_8039AE8C.mStatus.mWord & 0x00FFFF00) == 0x00010100)
#define SND_LOCK() if (lbl_8039AE8C.mStatus.mFlags.mNoLock == 0) fn_8026D0AC()
#define SND_UNLOCK() if (lbl_8039AE8C.mStatus.mFlags.mNoLock == 0) fn_8026D0EC()

typedef int (*SndTraverse_801C6D34)(void *pNode, void *pKey, void *pOut);

extern "C" {
extern SndState_8039AE8C lbl_8039AE8C;
extern char lbl_803ECF80[8];
extern char lbl_802B1A28[];

int sprintf(char *s, const char *format, ...);
void DCFlushRange(void *addr, unsigned long nBytes);
void *fn_801C6A20(void *pList);
void *fn_801C6AA4(void *pPool, void *pItem, int c);
void *fn_801C6B4C(void *pList, int where);
void fn_801C6C0C(void *pList, void *pNode);
int fn_801C6D34(void *pPool, int start, void *pKey, void *pOut, SndTraverse_801C6D34 pFunc, int count);
int fn_801CB120(void);
void fn_801CAF24(void);
void *fn_801D310C(void *pAddr, int size, int ident, int flags);
int fn_801B91A0(void *p);
void fn_801B9328(void *p);
unsigned long fn_8023CEE0(void);
void fn_8027555C(void);
void fn_8026F5F8(int a);
void fn_8026F710(int mode);
void fn_8026F788(int a, int b);
void fn_8026F894(int a);
void fn_8026F908(void (*pAbort)(const char *pMessage));
void fn_8026FBFC(int a, int b, int c);
void fn_8026FCAC(int a, int b);
int fn_802692B8(int handle);
int fn_802697D8(void *pData, char *pName, int b, void *(*pAlloc)(void *, int, int));
void fn_8026A2DC(int handle, int a, int b);
void fn_8026A4D4(int *pHandle, void *pData);
void fn_8026A870(int *pHandle, void *pData);
int fn_8026A96C(void);
int fn_8026AAF0(int handle, int a, void *b);
void fn_8026AB88(int handle);
void fn_8026B124(void *p);
void fn_8026B250(void);
void fn_8026C280(void);
int fn_8026C3BC(int handle);
void fn_8026C9BC(int handle, int value);
void fn_8026CA50(SndPatchOpts_801F40F4 *pOpts);
void fn_8026D0AC(void);
void fn_8026D0EC(void);
int fn_8026E280(SndPatchOpts_801F40F4 *pOpts, int a, int b, void *pBuffer, int size);
void fn_8026E2A8(int handle);
int fn_8026E364(int handle, int a, void *b);
void fn_8026E388(int handle);
void fn_8026E8FC(int handle, int a, int b);
void fn_8026EAC0(int handle, int a, int b);
int fn_8026EBBC(int handle);
void fn_8026ED1C(int a, int b);
void fn_8026EDC4(int handle);
int fn_8026EE6C(int a, int b);
void fn_8026EEB0(int handle, int a);
void fn_8026EF38(int handle, int a);
int fn_8026EF88(int a, int b);
void fn_8026F1E8(int handle, int *pStatus);
void fn_802703A0(void);
void fn_802714A8(int handle, int value);

int fn_801F3B4C(Desc_801F393C *pDesc);
void fn_801F3C14(void);
unsigned char fn_801F3E28(void);
unsigned char fn_801F3E34(void);
SndBankInfo_801F3524 *fn_801F3E40(Res_801EDC2C *pRes, unsigned int index, unsigned int bank);
void fn_801F3ED8(Res_801EDC2C *pRes, SndBankInfo_801F3524 **ppBank, unsigned int index, unsigned int bank,
                 void (*pCallback)(SndBankInfo_801F3524 *pBank));
void fn_801F3F74(SndBankInfo_801F3524 *pBank);
unsigned char fn_801F4024(SndBankInfo_801F3524 *pBank);
int fn_801F4050(SndBankInfo_801F3524 *pBank, int patch, void *pOpts);
void fn_801F40F4(SndPatchOpts_801F40F4 *pOpts);
void fn_801F4130(int handle);
int fn_801F41A0(int handle);
void fn_801F421C(int handle, int value);
void fn_801F4294(int handle, int a, int value);
void fn_801F4314(int handle, int value);
SndSeqInfo_801F438C *fn_801F438C(Res_801EDC2C *pRes, unsigned int index);
void fn_801F4448(SndSeqInfo_801F438C *pSeq);
void *fn_801F44A4(void);
SndStream_801F44B0 *fn_801F44B0(int extra, int a, int b, int bank);
int fn_801F4580(SndStream_801F44B0 *pStream, void *pFile, int a, int b);
void fn_801F45D4(SndStream_801F44B0 *pStream);
void fn_801F4638(SndStream_801F44B0 *pStream);
void fn_801F4678(SndStream_801F44B0 *pStream, int a, int b);
void fn_801F46F8(SndStream_801F44B0 *pStream, int a);
void fn_801F4834(SndStream_801F44B0 *pStream, int *pStatus);
int fn_801F48B8(SndStream_801F44B0 *pStream);
int fn_801F4934(int a, int b);
void fn_801F49B8(SndStream_801F44B0 *pStream, int a, int b);
void fn_801F4A38(SndStream_801F44B0 *pStream, int a);
void fn_801F4AB0(int a, int b);
void fn_801F4AEC(int a, int b);
void fn_801F4AF8(void (*pCallback)(int a, int b));
void fn_801F4B20(void);
int fn_801F4B88(Res_801EDC2C *pRes, unsigned int index, int bank);
int fn_801F4C5C(void);
SndAemsBankInfo_801F4D00 *fn_801F4DAC(Res_801EDC2C *pRes, unsigned int index, int bank);
SndAemsBankInfo_801F4D00 *fn_801F4DD8(Res_801EDC2C *pRes, unsigned int index, Res_801EDC2C *pStreamRes,
                                      unsigned int streamIndex, int bank);
int fn_801F4F28(SndAemsBankInfo_801F4D00 *pBank);
char *fn_801F4F98(StreamFile_801F6D54 *pFile);
}

static int fn_801F3524(void *pNode, void *pState, void *pOut)
{
    if (((SndBankInfo_801F3524 *)pNode)->mState == (int)pState) {
        *(SndBankInfo_801F3524 **)pOut = (SndBankInfo_801F3524 *)pNode;
        return 0;
    }
    return 1;
}

static void fn_801F3544(SndBankInfo_801F3524 *pBank)
{
    pBank->mState = 0;
    if (!(pBank->mFlags & 2)) {
        fn_801F5034(pBank, 1);
    }
    pBank->mLoaded = 1;
    if (pBank->pCallback != 0) {
        pBank->pCallback(pBank);
    }
}

static void fn_801F35A8(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser)
{
    ((SndBankInfo_801F3524 *)pUser)->mState = 2;
}

static void fn_801F35B4(void)
{
    SndBankInfo_801F3524 *pBank;
    char *pData;
    int busy;

    busy = 0;
    pBank = 0;
    fn_801C6D34(lbl_8039AE8C.pBankList, 0, (void *)3, &pBank, fn_801F3524, 1);
    if (pBank != 0 && pBank->mState == 3) {
        busy = 1;
        if (fn_8026A96C() != 0) {
            fn_801F3544(pBank);
        }
    }
    if (!busy) {
        pBank = 0;
        fn_801C6D34(lbl_8039AE8C.pBankList, 0, (void *)2, &pBank, fn_801F3524, 1);
        if (pBank != 0 && pBank->mState == 2) {
            pBank->mState = 3;
            pData = (char *)pBank->pData;
            if (pData[0] != 'B' || pData[1] != 'N' || pData[2] != 'K' || pData[3] != 'b') {
                fn_801F010C(pBank->pRes, pBank->mIndex);
                pBank->mState = 1;
                fn_801EFAD8(pBank->pRes, pBank->mIndex, 1, pData, 100, fn_801F35A8, pBank);
            } else {
                fn_801F50C8(lbl_8039AE8C.pBankTable, pBank->mBank);
                fn_8026A870(&pBank->mHandle, pBank->pData);
            }
        }
    }
}

static SndBankInfo_801F3524 *fn_801F3728(void *pRes, unsigned int index, unsigned int bank, void *pData, unsigned int size,
                                          unsigned int flags)
{
    SndBankInfo_801F3524 *pBank;
    int length;

    if (!lbl_8039AE8C.mStatus.mFlags.mActive || !lbl_8039AE8C.mStatus.mFlags.mEnabled) {
        return 0;
    }
    pBank = (SndBankInfo_801F3524 *)fn_801C6A20(lbl_8039AE8C.pBankList);
    fn_801C6AA4(lbl_8039AE8C.pBankList, pBank, 0);
    pBank->mBank = bank;
    pBank->mFlags = flags;
    pBank->pRes = (Res_801EDC2C *)pRes;
    pBank->mIndex = index;
    length = fn_801F0C50((Res_801EDC2C *)pRes, index);
    pBank->pData = pData;
    DCFlushRange(pData, length);
    fn_801EFF80((Res_801EDC2C *)pRes, index, pData);
    fn_801F50C8(lbl_8039AE8C.pBankTable, pBank->mBank);
    DCFlushRange(pData, length);
    fn_8026A4D4(&pBank->mHandle, pData);
    pBank->mLoaded = 1;
    pBank->mState = 0;
    if (!(pBank->mFlags & 2)) {
        fn_801F5034(pBank, 0);
    }
    return pBank;
}

static void fn_801F3834(void *pRes, SndBankInfo_801F3524 **ppBank, unsigned int index, unsigned int bank, void *pData,
                        unsigned int size, unsigned int flags, void (*pCallback)(SndBankInfo_801F3524 *pBank))
{
    SndBankInfo_801F3524 *pBank;

    if (lbl_8039AE8C.mStatus.mFlags.mActive && lbl_8039AE8C.mStatus.mFlags.mEnabled) {
        pBank = (SndBankInfo_801F3524 *)fn_801C6A20(lbl_8039AE8C.pBankList);
        fn_801C6AA4(lbl_8039AE8C.pBankList, pBank, 0);
        pBank->mFlags = flags | 1;
        pBank->mBank = bank;
        pBank->mLoaded = 0;
        pBank->pCallback = pCallback;
        pBank->mState = 1;
        pBank->pRes = (Res_801EDC2C *)pRes;
        pBank->mIndex = index;
        pBank->pData = pData;
        *ppBank = pBank;
        fn_801EFAD8((Res_801EDC2C *)pRes, index, 1, pData, 100, fn_801F35A8, pBank);
    }
}

static void fn_801F3904(const char *pMessage)
{
}

static void fn_801F3908(unsigned char label)
{
    if (lbl_8039AE8C.pMemLabelCallback != 0) {
        lbl_8039AE8C.pMemLabelCallback(label);
    }
}

int fn_801F3B4C(Desc_801F393C *pDesc)
{
    fn_8027555C();
    if (fn_8023CEE0() == 0) {
        fn_8026F710(0);
    } else {
        switch (lbl_8039AE8C.mUnk50) {
        case 1:
        case 2:
        default:
            fn_8026F710(1);
            break;
        case 3:
            fn_8026F710(8);
            break;
        }
    }
    fn_8026FBFC(2, pDesc->mUnknown8, pDesc->mUnknown12);
    fn_8026F894(0);
    fn_8026F788(0, pDesc->mUnknown24);
    fn_8026F5F8(pDesc->mUnknown16);
    fn_8026F908(fn_801F3904);
    if (pDesc->mUnknown40 != 0) {
        fn_8026FCAC(pDesc->mUnknown40, pDesc->mUnknown44);
    }
    return 0;
}

void fn_801F3C14(void)
{
    void *pNode;
    int i;

    if (lbl_8039AE8C.mStatus.mFlags.mEnabled) {
        SND_LOCK();
        fn_8026C280();
        SND_UNLOCK();
        for (;;) {
            pNode = fn_801C6B4C(lbl_8039AE8C.pSeqList, 0);
            if (pNode == 0) {
                break;
            }
            fn_801F4448((SndSeqInfo_801F438C *)pNode);
        }
        for (;;) {
            pNode = fn_801C6B4C(lbl_8039AE8C.pBankList, 0);
            if (pNode == 0) {
                break;
            }
            fn_801F3F74((SndBankInfo_801F3524 *)pNode);
        }
        if (lbl_8039AE8C.pAemsBankList != 0) {
            for (;;) {
                pNode = fn_801C6B4C(lbl_8039AE8C.pAemsBankList, 0);
                if (pNode == 0) {
                    break;
                }
                fn_801F4F28((SndAemsBankInfo_801F4D00 *)pNode);
            }
        }
        if (lbl_8039AE8C.pAemsSystem != 0 || lbl_8039AE8C.pAemsStreams != 0) {
            fn_801F4C5C();
        }
        for (i = 3; i >= 0; i--) {
            lbl_8039AE8C.apFileDesc[i] = 0;
        }
    }
}

unsigned char fn_801F3E28(void)
{
    return lbl_8039AE8C.mStatus.mFlags.mEnabled;
}

unsigned char fn_801F3E34(void)
{
    return lbl_8039AE8C.mStatus.mFlags.mActive;
}

SndBankInfo_801F3524 *fn_801F3E40(Res_801EDC2C *pRes, unsigned int index, unsigned int bank)
{
    unsigned int size;

    if (!lbl_8039AE8C.mStatus.mFlags.mActive || !lbl_8039AE8C.mStatus.mFlags.mEnabled) {
        return 0;
    }
    size = fn_801F0C50(pRes, index);
    return fn_801F3728(pRes, index, bank, fn_801D2BB0(1, size, 0, 0), size, 0);
}

void fn_801F3ED8(Res_801EDC2C *pRes, SndBankInfo_801F3524 **ppBank, unsigned int index, unsigned int bank,
                 void (*pCallback)(SndBankInfo_801F3524 *pBank))
{
    unsigned int size;

    if (lbl_8039AE8C.mStatus.mFlags.mActive && lbl_8039AE8C.mStatus.mFlags.mEnabled) {
        size = fn_801F0C50(pRes, index);
        fn_801F3834(pRes, ppBank, index, bank, fn_801D2BB0(1, size, 0, 0), size, 0, pCallback);
    }
}

void fn_801F3F74(SndBankInfo_801F3524 *pBank)
{
    if (lbl_8039AE8C.mStatus.mFlags.mActive && lbl_8039AE8C.mStatus.mFlags.mEnabled) {
        while (!pBank->mLoaded) {
            if (fn_801CB120() != 0) {
                fn_801CAF24();
            }
            fn_801F4B20();
        }
        fn_8026AB88(pBank->mHandle);
        if (pBank->mFlags & 1) {
            fn_801F010C(pBank->pRes, pBank->mIndex);
        }
        if (!(pBank->mFlags & 2)) {
            fn_801D2BD0(pBank->pData);
        }
        fn_801C6C0C(lbl_8039AE8C.pBankList, pBank);
    }
}

unsigned char fn_801F4024(SndBankInfo_801F3524 *pBank)
{
    if (SND_READY()) {
        return pBank->mLoaded;
    }
    return 1;
}

int fn_801F4050(SndBankInfo_801F3524 *pBank, int patch, void *pOpts)
{
    int handle;

    if (!lbl_8039AE8C.mStatus.mFlags.mActive || !lbl_8039AE8C.mStatus.mFlags.mEnabled) {
        return 0;
    }
    if (pBank->mLoaded) {
        SND_LOCK();
        handle = fn_8026AAF0(pBank->mHandle, patch, pOpts);
        SND_UNLOCK();
    } else {
        handle = -1;
    }
    return handle;
}

void fn_801F40F4(SndPatchOpts_801F40F4 *pOpts)
{
    if (SND_READY()) {
        fn_8026CA50(pOpts);
    }
}

void fn_801F4130(int handle)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026EDC4(handle);
        SND_UNLOCK();
    }
}

int fn_801F41A0(int handle)
{
    int result;

    result = 0;
    if (SND_READY()) {
        SND_LOCK();
        result = fn_8026C3BC(handle);
        SND_UNLOCK();
    }
    return result;
}

void fn_801F421C(int handle, int value)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_802714A8(handle, value);
        SND_UNLOCK();
    }
}

void fn_801F4294(int handle, int a, int value)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026A2DC(handle, a, value);
        SND_UNLOCK();
    }
}

void fn_801F4314(int handle, int value)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026C9BC(handle, value);
        SND_UNLOCK();
    }
}

SndSeqInfo_801F438C *fn_801F438C(Res_801EDC2C *pRes, unsigned int index)
{
    SndSeqInfo_801F438C *pSeq;
    void *pData;

    if (!lbl_8039AE8C.mStatus.mFlags.mActive || !lbl_8039AE8C.mStatus.mFlags.mEnabled) {
        return 0;
    }
    pSeq = (SndSeqInfo_801F438C *)fn_801C6A20(lbl_8039AE8C.pSeqList);
    fn_801C6AA4(lbl_8039AE8C.pSeqList, pSeq, 0);
    pSeq->pRes = pRes;
    pSeq->mIndex = index;
    pData = fn_801D2B7C(fn_801F0C50(pRes, index), 0, 0);
    fn_801EFF80(pRes, index, pData);
    pSeq->mLoaded = 1;
    pSeq->pData = pData;
    pSeq->mUnk8 = -1;
    return pSeq;
}

void fn_801F4448(SndSeqInfo_801F438C *pSeq)
{
    if (SND_READY()) {
        fn_801D2BD0(pSeq->pData);
        fn_801C6C0C(lbl_8039AE8C.pSeqList, pSeq);
    }
}

void *fn_801F44A4(void)
{
    return lbl_8039AE8C.pBankTable;
}

SndStream_801F44B0 *fn_801F44B0(int extra, int a, int b, int bank)
{
    SndStream_801F44B0 *pStream;
    SndPatchOpts_801F40F4 opts;
    int size;

    if (!lbl_8039AE8C.mStatus.mFlags.mActive || !lbl_8039AE8C.mStatus.mFlags.mEnabled) {
        return 0;
    }
    fn_801F50C8(lbl_8039AE8C.pBankTable, bank);
    pStream = (SndStream_801F44B0 *)fn_801C6A20(lbl_8039AE8C.pStreamList);
    fn_801C6AA4(lbl_8039AE8C.pStreamList, pStream, 0);
    fn_8026CA50(&opts);
    size = fn_8026EE6C(a, b) + extra;
    pStream->pBuffer = fn_801D2BB0(1, size, 0, 0);
    pStream->mHandle = fn_8026E280(&opts, a, b, pStream->pBuffer, size);
    return pStream;
}

int fn_801F4580(SndStream_801F44B0 *pStream, void *pFile, int a, int b)
{
    int result;

    result = -1;
    if (SND_READY()) {
        result = fn_8026E364(pStream->mHandle, a, pFile);
    }
    return result;
}

void fn_801F45D4(SndStream_801F44B0 *pStream)
{
    if (SND_READY()) {
        fn_8026E2A8(pStream->mHandle);
        fn_801D2BD0(pStream->pBuffer);
        fn_801C6C0C(lbl_8039AE8C.pStreamList, pStream);
    }
}

void fn_801F4638(SndStream_801F44B0 *pStream)
{
    if (SND_READY()) {
        fn_8026E388(pStream->mHandle);
    }
}

void fn_801F4678(SndStream_801F44B0 *pStream, int a, int b)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026E8FC(pStream->mHandle, a, b);
        SND_UNLOCK();
    }
}

void fn_801F46F8(SndStream_801F44B0 *pStream, int a)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026EEB0(pStream->mHandle, a);
        SND_UNLOCK();
    }
}

void fn_801F4834(SndStream_801F44B0 *pStream, int *pStatus)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026F1E8(pStream->mHandle, pStatus);
        SND_UNLOCK();
    } else {
        pStatus[0] = 0;
    }
}

int fn_801F48B8(SndStream_801F44B0 *pStream)
{
    int result;

    result = 0;
    if (SND_READY()) {
        SND_LOCK();
        result = fn_8026EBBC(pStream->mHandle);
        SND_UNLOCK();
    }
    return result;
}

int fn_801F4934(int a, int b)
{
    int result;

    result = -1;
    if (SND_READY()) {
        SND_LOCK();
        result = fn_8026EF88(a, b);
        SND_UNLOCK();
    }
    return result;
}

void fn_801F49B8(SndStream_801F44B0 *pStream, int a, int b)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026EAC0(pStream->mHandle, a, b);
        SND_UNLOCK();
    }
}

void fn_801F4A38(SndStream_801F44B0 *pStream, int a)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026EF38(pStream->mHandle, a);
        SND_UNLOCK();
    }
}

void fn_801F4AB0(int a, int b)
{
    if (SND_READY()) {
        fn_8026ED1C(a, b);
    }
}

void fn_801F4AEC(int a, int b)
{
    lbl_8039AE8C.mUnk50 = a;
}

void fn_801F4AF8(void (*pCallback)(int a, int b))
{
    if (SND_READY()) {
        lbl_8039AE8C.pServiceCallback = pCallback;
    }
}

void fn_801F4B20(void)
{
    if (SND_READY()) {
        fn_802703A0();
        fn_801F35B4();
        if (lbl_8039AE8C.pServiceCallback != 0) {
            lbl_8039AE8C.pServiceCallback(0, 0);
        }
    }
}

int fn_801F4B88(Res_801EDC2C *pRes, unsigned int index, int bank)
{
    int result;

    result = 0;
    if (SND_READY()) {
        fn_801F50C8(lbl_8039AE8C.pBankTable, bank);
        lbl_8039AE8C.pAemsSystem = fn_801D2B7C(fn_801F0C50(pRes, index), 0, 0);
        fn_801EF7BC(pRes, index, lbl_8039AE8C.pAemsSystem);
        result = fn_801B91A0(lbl_8039AE8C.pAemsSystem);
        lbl_8039AE8C.pAemsStreams = fn_801D2B7C(fn_801F0C50(pRes, index + 1), 0, 0);
        fn_801EF7BC(pRes, index + 1, lbl_8039AE8C.pAemsStreams);
        fn_8026B124(lbl_8039AE8C.pAemsStreams);
    }
    return result;
}

int fn_801F4C5C(void)
{
    int result;

    result = 0;
    if (SND_READY()) {
        if (lbl_8039AE8C.pAemsStreams != 0) {
            fn_8026B250();
            fn_801D2BD0(lbl_8039AE8C.pAemsStreams);
            lbl_8039AE8C.pAemsStreams = 0;
        }
        if (lbl_8039AE8C.pAemsSystem != 0) {
            fn_801B9328(lbl_8039AE8C.pAemsSystem);
            fn_801D2BD0(lbl_8039AE8C.pAemsSystem);
            lbl_8039AE8C.pAemsSystem = 0;
        }
    }
    return result;
}

static int fn_801F4CE0(void *pNode, void *pData, void *pOut)
{
    if (((SndAemsBankInfo_801F4D00 *)pNode)->pData == pData) {
        *(SndAemsBankInfo_801F4D00 **)pOut = (SndAemsBankInfo_801F4D00 *)pNode;
        return 0;
    }
    return 1;
}

static void *fn_801F4D00(void *pData, int size, int c)
{
    SndAemsBankInfo_801F4D00 *pBank;

    pBank = 0;
    fn_801C6D34(lbl_8039AE8C.pAemsBankList, 0, pData, &pBank, fn_801F4CE0, 1);
    if (pBank != 0) {
        pBank->mSize = size;
    }
    return pData;
}

static void fn_801F4D6C(SndAemsBankInfo_801F4D00 *pBank)
{
    pBank->pData = fn_801D310C(pBank->pData, pBank->mSize, 0, 0);
}

SndAemsBankInfo_801F4D00 *fn_801F4DAC(Res_801EDC2C *pRes, unsigned int index, int bank)
{
    return fn_801F4DD8(pRes, index, (Res_801EDC2C *)-1, (unsigned int)-1, bank);
}

SndAemsBankInfo_801F4D00 *fn_801F4DD8(Res_801EDC2C *pRes, unsigned int index, Res_801EDC2C *pStreamRes,
                                      unsigned int streamIndex, int bank)
{
    SndAemsBankInfo_801F4D00 *pBank;
    unsigned int size;
    char *pName;

    pBank = 0;
    if (SND_READY() && lbl_8039AE8C.pAemsBankList != 0) {
        pBank = (SndAemsBankInfo_801F4D00 *)fn_801C6A20(lbl_8039AE8C.pAemsBankList);
        fn_801C6AA4(lbl_8039AE8C.pAemsBankList, pBank, 0);
        pBank->mBank = bank;
        fn_801F50C8(lbl_8039AE8C.pBankTable, bank);
        size = fn_801F0C50(pRes, index);
        pBank->pData = fn_801D2BB0(1, size, 0, 0);
        DCFlushRange(pBank->pData, size);
        fn_801EF7BC(pRes, index, pBank->pData);
        DCFlushRange(pBank->pData, size);
        if (pStreamRes != (Res_801EDC2C *)-1 && streamIndex != (unsigned int)-1) {
            pBank->mFile.pRes = pStreamRes;
            pBank->mFile.mIndex = streamIndex;
            pName = fn_801F4F98(&pBank->mFile);
            pBank->mHandle = fn_802697D8(pBank->pData, pName, 0, fn_801F4D00);
            fn_801F4D6C(pBank);
        } else {
            pBank->mHandle = fn_802697D8(pBank->pData, 0, 0, fn_801F4D00);
            fn_801F4D6C(pBank);
        }
    }
    return pBank;
}

int fn_801F4F28(SndAemsBankInfo_801F4D00 *pBank)
{
    int result;

    result = 0;
    if (SND_READY()) {
        result = fn_802692B8(pBank->mHandle);
        fn_801D2BD0(pBank->pData);
        fn_801C6C0C(lbl_8039AE8C.pAemsBankList, pBank);
    }
    return result;
}

char *fn_801F4F98(StreamFile_801F6D54 *pFile)
{
    int i;

    for (i = 0; i <= 3; i++) {
        if (lbl_8039AE8C.apFileDesc[i] == 0) {
            lbl_8039AE8C.apFileDesc[i] = pFile;
            sprintf(lbl_803ECF80, lbl_802B1A28, i);
            return lbl_803ECF80;
        }
    }
    return lbl_803ECF80;
}

StreamFile_801F6D54 *fn_801F5000(const char *pName)
{
    return lbl_8039AE8C.apFileDesc[(pName[4] - '0') * 10 + (pName[5] - '0')];
}
