/* Sound module of the engine: starts and shuts down the sound driver with its heap and
   allocator, loads and unloads sample banks (synchronously or in the background), sequences and
   AEMS banks, plays and controls patches and streams, and services pending loads each frame. */

#include "engine/sound.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801C68FC.h"
#include "engine/IAllocator.h"

struct SndSeqInfo_t {
    ResFile_t *pRes;
    unsigned int mIndex;
    int mUnk8;
    void *pData;
    unsigned char mLoaded;
};

struct SndStream_t {
    int mHandle;
    void *pBuffer;
};

struct SndAemsBankInfo_t {
    int mHandle;
    int mSize;
    void *pData;
    int mBank;
    SndFileDesc_t mFile;
};

struct SndInitDesc_t {
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
    void (*mUnknown36)(int a, int b);
    int mUnknown40;
    int mUnknown44;
    int mUnknown48;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
};

struct SndPatchOpts_t {
    signed char mVolume;
    unsigned char mUnk1[7];
    unsigned short mPan;
    short mSpan;
    unsigned short mUnkC;
    char mUnkE[10];
};

union SndStatus_t {
    unsigned int mWord;
    struct {
        unsigned char mNoLock;
        unsigned char mActive;
        unsigned char mEnabled;
        unsigned char mUnk3B;
    } mFlags;
};

struct SndModuleInfo_t {
    int mUnk0;
    void *pHeap;
    int mHeapSize;
    void *pBankList;
    void *pAemsBankList;
    void *pSeqList;
    void *pStreamList;
    SndBankHeap_t *pBankTable;
    void *pAemsSystem;
    void *pAemsStreams;
    int mUnk28;
    void (*pServiceCallback)(int a, int b);
    int mUnk30;
    void (*pMemLabelCallback)(unsigned char label);
    SndStatus_t mStatus;
    unsigned char mUnk3C;
    SndFileDesc_t *apFileDesc[4];
    int mUnk50;
};

/* The active and enabled bytes tested together as one word. */
#define SND_READY() ((_Snd_ModuleInfo.mStatus.mWord & 0x00FFFF00) == 0x00010100)
#define SND_LOCK() if (_Snd_ModuleInfo.mStatus.mFlags.mNoLock == 0) fn_8026D0AC()
#define SND_UNLOCK() if (_Snd_ModuleInfo.mStatus.mFlags.mNoLock == 0) fn_8026D0EC()

typedef int (*SndTraverseFn_t)(void *pNode, void *pKey, void *pOut);

static IAllocator *pIAllocator;

static SndModuleInfo_t _Snd_ModuleInfo;

extern "C" {
int sprintf(char *s, const char *format, ...);
void DCFlushRange(void *addr, unsigned long nBytes);
void *fn_801C6A20(void *pList);
void *fn_801C6AA4(void *pPool, void *pItem, int c);
void *fn_801C6B4C(void *pList, int where);
void fn_801C6C0C(void *pList, void *pNode);
int fn_801C6D34(void *pPool, int start, void *pKey, void *pOut, SndTraverseFn_t pFunc, int count);
int FileHostCheckActive(void);
void FileDebugProcess(void);
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
int fn_8026A870(int *pHandle, void *pData);
int fn_8026A96C(void);
int fn_8026AAF0(int handle, int a, void *b);
int fn_8026AB88(int handle);
void fn_8026B124(void *p);
void fn_8026B250(void);
void fn_8026C280(void);
int fn_8026C3BC(int handle);
int fn_8026C9BC(int handle, int value);
void fn_8026CA50(SndPatchOpts_t *pOpts);
void fn_8026D0AC(void);
void fn_8026D0EC(void);
int fn_8026E280(SndPatchOpts_t *pOpts, int a, int b, void *pBuffer, int size);
void fn_8026E2A8(int handle);
int fn_8026E364(int handle, int a, void *b);
int fn_8026E388(int handle);
void fn_8026E8FC(int handle, int a, int b);
int fn_8026EAC0(int handle, int a, int b);
int fn_8026EBBC(int handle);
int fn_8026E4C0(int handle, float degrees, int a);
int fn_8026ED1C(int a, int b);
int fn_8026EDC4(int handle);
int fn_8026EE6C(int a, int b);
int fn_8026EEB0(int handle, int a);
int fn_8026EF38(int handle, int a);
int fn_8026EF88(int a, int b);
void fn_8026F1E8(int handle, int *pStatus);
void fn_802703A0(void);
int fn_802714A8(int handle, int value);

void _StreamMUTEX_init(void);
void fn_8026C39C(int a);
int fn_801B90BC(void *pAllocator);
int fn_801B90F0(void);
int fn_801B9134(void);
void fn_80270458(void);
void fn_8026F97C(int a);
void fn_8026C18C(void);
void fn_8026C23C(void);
void fn_8026FBCC(void);

int SndInit(SndInitDesc_t *pDesc);
int SndShutdown(void);
int SndInitParms(SndInitDesc_t *pDesc);
void SndUnloadAll(void);
unsigned char SndEnabled(void);
unsigned char SndIsActive(void);
SndBankInfo_t *SndLoadBank(ResFile_t *pRes, unsigned int index, unsigned int bank);
void SndALoadBank(ResFile_t *pRes, SndBankInfo_t **ppBank, unsigned int index, unsigned int bank,
                 void (*pCallback)(SndBankInfo_t *pBank));
void SndUnloadBank(SndBankInfo_t *pBank);
unsigned char SndIsBankLoaded(SndBankInfo_t *pBank);
int SndPlayPatch(SndBankInfo_t *pBank, int patch, void *pOpts);
void SndFillPatchOpts(SndPatchOpts_t *pOpts);
void SndStopPatch(int handle);
int SndPatchOver(int handle);
void SndSetPatchPitchMult(int handle, int value);
void SndSetPatchParam(int handle, int a, int value);
void SndSetPatchRate(int handle, int value);
SndSeqInfo_t *SndLoadSeq(ResFile_t *pRes, unsigned int index);
void SndUnloadSeq(SndSeqInfo_t *pSeq);
SndStream_t *SndCreateStream(int extra, int a, int b, int bank);
int SndStreamQueueFile(SndStream_t *pStream, void *pFile, int a, int b);
void SndDestroyStream(SndStream_t *pStream);
void SndPurgeStream(SndStream_t *pStream);
void SndStreamAutoVol(SndStream_t *pStream, int a, int b);
void SndStreamSetPitchMult(SndStream_t *pStream, int a);
int SndStreamSetPan(SndStream_t *pStream, unsigned int angle);
void SndStreamGetStatus(SndStream_t *pStream, int *pStatus);
int SndStreamGetVol(SndStream_t *pStream);
int SndStreamGetPosition(int a, int b);
void SndStreamSetParam(SndStream_t *pStream, int a, int b);
void SndStreamSetControl(SndStream_t *pStream, int a);
void SndSetMasterVol(int a, int b);
void SndSetOutputMode(int a, int b);
void SndSetServiceCallback(void (*pCallback)(int a, int b));
void SndService(void);
int SndAemsLoadSystem(ResFile_t *pRes, unsigned int index, int bank);
int SndAemsUnloadSystem(void);
SndAemsBankInfo_t *SndAemsLoadBank(ResFile_t *pRes, unsigned int index, int bank);
SndAemsBankInfo_t *SndAemsLoadBankWithStream(ResFile_t *pRes, unsigned int index, ResFile_t *pStreamRes,
                                      unsigned int streamIndex, int bank);
int SndAemsUnloadBank(SndAemsBankInfo_t *pBank);
char *SndAemsAllocFileDesc(SndFileDesc_t *pFile);
}

static int _SndBankTraverseFindState(void *pNode, void *pState, void *pOut)
{
    if (((SndBankInfo_t *)pNode)->mState == (int)pState) {
        *(SndBankInfo_t **)pOut = (SndBankInfo_t *)pNode;
        return 0;
    }
    return 1;
}

static void _SndBankFinishDMA(SndBankInfo_t *pBank)
{
    pBank->mState = 0;
    if (!(pBank->mFlags & 2)) {
        SndllResolveBank(pBank, 1);
    }
    pBank->mLoaded = 1;
    if (pBank->pCallback != 0) {
        pBank->pCallback(pBank);
    }
}

static void _SndALoadBankCallback(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser)
{
    ((SndBankInfo_t *)pUser)->mState = 2;
}

static void _SndProcessBanks(void)
{
    SndBankInfo_t *pBank;
    char *pData;
    int busy;

    busy = 0;
    pBank = 0;
    fn_801C6D34(_Snd_ModuleInfo.pBankList, 0, (void *)3, &pBank, _SndBankTraverseFindState, 1);
    if (pBank != 0 && pBank->mState == 3) {
        busy = 1;
        if (fn_8026A96C() != 0) {
            _SndBankFinishDMA(pBank);
        }
    }
    if (!busy) {
        pBank = 0;
        fn_801C6D34(_Snd_ModuleInfo.pBankList, 0, (void *)2, &pBank, _SndBankTraverseFindState, 1);
        if (pBank != 0 && pBank->mState == 2) {
            pBank->mState = 3;
            pData = (char *)pBank->pData;
            if (pData[0] != 'B' || pData[1] != 'N' || pData[2] != 'K' || pData[3] != 'b') {
                ResUnLoad(pBank->pRes, pBank->mIndex);
                pBank->mState = 1;
                ResLoadAsyncToBuffer(pBank->pRes, pBank->mIndex, 1, pData, 100, _SndALoadBankCallback, pBank);
            } else {
                SndSetHeap(_Snd_ModuleInfo.pBankTable, pBank->mBank);
                fn_8026A870(&pBank->mHandle, pBank->pData);
            }
        }
    }
}

static SndBankInfo_t *_SndLoadBank(void *pRes, unsigned int index, unsigned int bank, void *pData, unsigned int size,
                                          unsigned int flags)
{
    SndBankInfo_t *pBank;
    int length;

    if (!_Snd_ModuleInfo.mStatus.mFlags.mActive || !_Snd_ModuleInfo.mStatus.mFlags.mEnabled) {
        return 0;
    }
    pBank = (SndBankInfo_t *)fn_801C6A20(_Snd_ModuleInfo.pBankList);
    fn_801C6AA4(_Snd_ModuleInfo.pBankList, pBank, 0);
    pBank->mBank = bank;
    pBank->mFlags = flags;
    pBank->pRes = (ResFile_t *)pRes;
    pBank->mIndex = index;
    length = ResGetSize((ResFile_t *)pRes, index);
    pBank->pData = pData;
    DCFlushRange(pData, length);
    ResCopyToBuffer((ResFile_t *)pRes, index, pData);
    SndSetHeap(_Snd_ModuleInfo.pBankTable, pBank->mBank);
    DCFlushRange(pData, length);
    fn_8026A4D4(&pBank->mHandle, pData);
    pBank->mLoaded = 1;
    pBank->mState = 0;
    if (!(pBank->mFlags & 2)) {
        SndllResolveBank(pBank, 0);
    }
    return pBank;
}

static void _SndALoadBank(void *pRes, SndBankInfo_t **ppBank, unsigned int index, unsigned int bank, void *pData,
                        unsigned int size, unsigned int flags, void (*pCallback)(SndBankInfo_t *pBank))
{
    SndBankInfo_t *pBank;

    if (_Snd_ModuleInfo.mStatus.mFlags.mActive && _Snd_ModuleInfo.mStatus.mFlags.mEnabled) {
        pBank = (SndBankInfo_t *)fn_801C6A20(_Snd_ModuleInfo.pBankList);
        fn_801C6AA4(_Snd_ModuleInfo.pBankList, pBank, 0);
        // FAKEMATCH: store order found by trying the 120 orders of the first five stores
        pBank->mBank = bank;
        pBank->mLoaded = 0;
        pBank->pCallback = pCallback;
        pBank->mFlags = flags | 1;
        pBank->mState = 1;
        pBank->pRes = (ResFile_t *)pRes;
        pBank->mIndex = index;
        pBank->pData = pData;
        *ppBank = pBank;
        ResLoadAsyncToBuffer((ResFile_t *)pRes, index, 1, pData, 100, _SndALoadBankCallback, pBank);
    }
}

static void _SndAbort(const char *pMessage)
{
}

static void _SndIAllocatorMemLabelCB(unsigned char label)
{
    if (_Snd_ModuleInfo.pMemLabelCallback != 0) {
        _Snd_ModuleInfo.pMemLabelCallback(label);
    }
}

int SndInit(SndInitDesc_t *pDesc)
{
    int result;
    int i;
    void *pHeap;

    _StreamMUTEX_init();
    if (pDesc == 0) {
        _Snd_ModuleInfo.mStatus.mFlags.mActive = 1;
        _Snd_ModuleInfo.mStatus.mFlags.mEnabled = 0;
        return 0;
    }
    result = 0;
    SndInitParms(pDesc);
    if (!_Snd_ModuleInfo.mStatus.mFlags.mActive) {
        _Snd_ModuleInfo.mStatus.mFlags.mActive = 1;
        _Snd_ModuleInfo.mStatus.mFlags.mEnabled = 1;
        _Snd_ModuleInfo.mStatus.mFlags.mNoLock = pDesc->mUnknown52;
        _Snd_ModuleInfo.mStatus.mFlags.mUnk3B = pDesc->mUnknown53;
        _Snd_ModuleInfo.mUnk3C = pDesc->mUnknown54;
        // FAKEMATCH: store order chosen to match (the label callback cleared after the heap id)
        _Snd_ModuleInfo.pServiceCallback = pDesc->mUnknown36;
        _Snd_ModuleInfo.mUnk30 = pDesc->mUnknown48;
        _Snd_ModuleInfo.pMemLabelCallback = 0;
        for (i = 3; i >= 0; i--) {
            _Snd_ModuleInfo.apFileDesc[i] = 0;
        }
        pHeap = fn_801D2BB0(1, pDesc->mUnknown4, 0, 0);
        _Snd_ModuleInfo.pHeap = pHeap;
        _Snd_ModuleInfo.mHeapSize = pDesc->mUnknown4;
        fn_8026C39C(4);
        pIAllocator = new TiburonIAllocator13Impl(_Snd_ModuleInfo.mUnk30, (void (*)(int))_SndIAllocatorMemLabelCB);
        fn_801B90BC(pIAllocator);
        fn_801B90F0();
        fn_80270458();
        fn_8026FBFC(0, (int)pHeap, pDesc->mUnknown4);
        fn_8026F97C(pDesc->mUnknown0);
        _Snd_ModuleInfo.mUnk0 = pDesc->mUnknown0;
        fn_8026C18C();
        _Snd_ModuleInfo.pBankList = fn_801C68FC(1, 0, pDesc->mUnknown16, sizeof(SndBankInfo_t), 0, 0);
        _Snd_ModuleInfo.pSeqList = fn_801C68FC(1, 0, pDesc->mUnknown20, sizeof(SndSeqInfo_t), 0, 0);
        _Snd_ModuleInfo.pStreamList = fn_801C68FC(1, 0, pDesc->mUnknown22, sizeof(SndStream_t), 0, 0);
        if (pDesc->mUnknown18 != 0) {
            _Snd_ModuleInfo.pAemsBankList =
                fn_801C68FC(1, 0, pDesc->mUnknown18, sizeof(SndAemsBankInfo_t), 0, 0);
        }
        _Snd_ModuleInfo.pBankTable = (SndBankHeap_t *)pDesc->mUnknown32;
        _Snd_ModuleInfo.pAemsSystem = 0;
        _Snd_ModuleInfo.pAemsStreams = 0;
    } else {
        result = 0x1C0001;
    }
    return result;
}

int SndInitParms(SndInitDesc_t *pDesc)
{
    fn_8027555C();
    if (fn_8023CEE0() == 0) {
        fn_8026F710(0);
    } else {
        switch (_Snd_ModuleInfo.mUnk50) {
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
    fn_8026F908(_SndAbort);
    if (pDesc->mUnknown40 != 0) {
        fn_8026FCAC(pDesc->mUnknown40, pDesc->mUnknown44);
    }
    return 0;
}

void SndUnloadAll(void)
{
    void *pNode;
    int i;

    if (_Snd_ModuleInfo.mStatus.mFlags.mEnabled) {
        SND_LOCK();
        fn_8026C280();
        SND_UNLOCK();
        // FAKEMATCH: node tested twice per pass (target keeps the loop test at the top)
        do {
            pNode = fn_801C6B4C(_Snd_ModuleInfo.pSeqList, 0);
            if (pNode != 0) {
                SndUnloadSeq((SndSeqInfo_t *)pNode);
            }
        } while (pNode != 0);
        // FAKEMATCH: node tested twice per pass (target keeps the loop test at the top)
        do {
            pNode = fn_801C6B4C(_Snd_ModuleInfo.pBankList, 0);
            if (pNode != 0) {
                SndUnloadBank((SndBankInfo_t *)pNode);
            }
        } while (pNode != 0);
        if (_Snd_ModuleInfo.pAemsBankList != 0) {
            // FAKEMATCH: node tested twice per pass (target keeps the loop test at the top)
            do {
                pNode = fn_801C6B4C(_Snd_ModuleInfo.pAemsBankList, 0);
                if (pNode != 0) {
                    SndAemsUnloadBank((SndAemsBankInfo_t *)pNode);
                }
            } while (pNode != 0);
        }
        if (_Snd_ModuleInfo.pAemsSystem != 0 || _Snd_ModuleInfo.pAemsStreams != 0) {
            SndAemsUnloadSystem();
        }
        for (i = 3; i >= 0; i--) {
            _Snd_ModuleInfo.apFileDesc[i] = 0;
        }
    }
}

int SndShutdown(void)
{
    int result;

    result = 0;
    if (_Snd_ModuleInfo.mStatus.mFlags.mActive) {
        if (_Snd_ModuleInfo.mStatus.mFlags.mEnabled) {
            SND_LOCK();
            fn_8026C280();
            SND_UNLOCK();
            SndUnloadAll();
            fn_801C69E4(_Snd_ModuleInfo.pSeqList);
            fn_801C69E4(_Snd_ModuleInfo.pBankList);
            if (_Snd_ModuleInfo.pAemsBankList != 0) {
                fn_801C69E4(_Snd_ModuleInfo.pAemsBankList);
                _Snd_ModuleInfo.pAemsBankList = 0;
            }
            fn_8026C23C();
            fn_8026FBCC();
            fn_801B9134();
            delete pIAllocator;
            fn_801C69E4(_Snd_ModuleInfo.pStreamList);
            fn_801D2BD0(_Snd_ModuleInfo.pHeap);
        }
    } else {
        result = 0x1C0002;
    }
    _Snd_ModuleInfo.mStatus.mFlags.mActive = 0;
    _Snd_ModuleInfo.mStatus.mFlags.mEnabled = 0;
    return result;
}

unsigned char SndEnabled(void)
{
    return _Snd_ModuleInfo.mStatus.mFlags.mEnabled;
}

unsigned char SndIsActive(void)
{
    return _Snd_ModuleInfo.mStatus.mFlags.mActive;
}

SndBankInfo_t *SndLoadBank(ResFile_t *pRes, unsigned int index, unsigned int bank)
{
    unsigned int size;

    if (!_Snd_ModuleInfo.mStatus.mFlags.mActive || !_Snd_ModuleInfo.mStatus.mFlags.mEnabled) {
        return 0;
    }
    size = ResGetSize(pRes, index);
    return _SndLoadBank(pRes, index, bank, fn_801D2BB0(1, size, 0, 0), size, 0);
}

void SndALoadBank(ResFile_t *pRes, SndBankInfo_t **ppBank, unsigned int index, unsigned int bank,
                 void (*pCallback)(SndBankInfo_t *pBank))
{
    unsigned int size;

    if (_Snd_ModuleInfo.mStatus.mFlags.mActive && _Snd_ModuleInfo.mStatus.mFlags.mEnabled) {
        size = ResGetSize(pRes, index);
        _SndALoadBank(pRes, ppBank, index, bank, fn_801D2BB0(1, size, 0, 0), size, 0, pCallback);
    }
}

void SndUnloadBank(SndBankInfo_t *pBank)
{
    if (_Snd_ModuleInfo.mStatus.mFlags.mActive && _Snd_ModuleInfo.mStatus.mFlags.mEnabled) {
        while (!pBank->mLoaded) {
            if (FileHostCheckActive() != 0) {
                FileDebugProcess();
            }
            SndService();
        }
        fn_8026AB88(pBank->mHandle);
        if (pBank->mFlags & 1) {
            ResUnLoad(pBank->pRes, pBank->mIndex);
        }
        if (!(pBank->mFlags & 2)) {
            fn_801D2BD0(pBank->pData);
        }
        fn_801C6C0C(_Snd_ModuleInfo.pBankList, pBank);
    }
}

unsigned char SndIsBankLoaded(SndBankInfo_t *pBank)
{
    if (SND_READY()) {
        return pBank->mLoaded;
    }
    return 1;
}

int SndPlayPatch(SndBankInfo_t *pBank, int patch, void *pOpts)
{
    int handle;

    if (!_Snd_ModuleInfo.mStatus.mFlags.mActive || !_Snd_ModuleInfo.mStatus.mFlags.mEnabled) {
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

void SndFillPatchOpts(SndPatchOpts_t *pOpts)
{
    if (SND_READY()) {
        fn_8026CA50(pOpts);
    }
}

void SndStopPatch(int handle)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026EDC4(handle);
        SND_UNLOCK();
    }
}

int SndPatchOver(int handle)
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

void SndSetPatchPitchMult(int handle, int value)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_802714A8(handle, value);
        SND_UNLOCK();
    }
}

void SndSetPatchParam(int handle, int a, int value)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026A2DC(handle, a, value);
        SND_UNLOCK();
    }
}

void SndSetPatchRate(int handle, int value)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026C9BC(handle, value);
        SND_UNLOCK();
    }
}

SndSeqInfo_t *SndLoadSeq(ResFile_t *pRes, unsigned int index)
{
    SndSeqInfo_t *pSeq;
    void *pData;

    if (!_Snd_ModuleInfo.mStatus.mFlags.mActive || !_Snd_ModuleInfo.mStatus.mFlags.mEnabled) {
        return 0;
    }
    pSeq = (SndSeqInfo_t *)fn_801C6A20(_Snd_ModuleInfo.pSeqList);
    fn_801C6AA4(_Snd_ModuleInfo.pSeqList, pSeq, 0);
    pSeq->pRes = pRes;
    pSeq->mIndex = index;
    pData = fn_801D2B7C(ResGetSize(pRes, index), 0, 0);
    ResCopyToBuffer(pRes, index, pData);
    pSeq->mLoaded = 1;
    pSeq->pData = pData;
    pSeq->mUnk8 = -1;
    return pSeq;
}

void SndUnloadSeq(SndSeqInfo_t *pSeq)
{
    if (SND_READY()) {
        fn_801D2BD0(pSeq->pData);
        fn_801C6C0C(_Snd_ModuleInfo.pSeqList, pSeq);
    }
}

void *SndGetBankTable(void)
{
    return _Snd_ModuleInfo.pBankTable;
}

SndStream_t *SndCreateStream(int extra, int a, int b, int bank)
{
    SndStream_t *pStream;
    SndPatchOpts_t opts;
    int size;

    if (!_Snd_ModuleInfo.mStatus.mFlags.mActive || !_Snd_ModuleInfo.mStatus.mFlags.mEnabled) {
        return 0;
    }
    SndSetHeap(_Snd_ModuleInfo.pBankTable, bank);
    pStream = (SndStream_t *)fn_801C6A20(_Snd_ModuleInfo.pStreamList);
    fn_801C6AA4(_Snd_ModuleInfo.pStreamList, pStream, 0);
    fn_8026CA50(&opts);
    size = fn_8026EE6C(a, b) + extra;
    pStream->pBuffer = fn_801D2BB0(1, size, 0, 0);
    pStream->mHandle = fn_8026E280(&opts, a, b, pStream->pBuffer, size);
    return pStream;
}

int SndStreamQueueFile(SndStream_t *pStream, void *pFile, int a, int b)
{
    int result;

    result = -1;
    if (SND_READY()) {
        result = fn_8026E364(pStream->mHandle, a, pFile);
    }
    return result;
}

void SndDestroyStream(SndStream_t *pStream)
{
    if (SND_READY()) {
        fn_8026E2A8(pStream->mHandle);
        fn_801D2BD0(pStream->pBuffer);
        fn_801C6C0C(_Snd_ModuleInfo.pStreamList, pStream);
    }
}

void SndPurgeStream(SndStream_t *pStream)
{
    if (SND_READY()) {
        fn_8026E388(pStream->mHandle);
    }
}

void SndStreamAutoVol(SndStream_t *pStream, int a, int b)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026E8FC(pStream->mHandle, a, b);
        SND_UNLOCK();
    }
}

void SndStreamSetPitchMult(SndStream_t *pStream, int a)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026EEB0(pStream->mHandle, a);
        SND_UNLOCK();
    }
}

int SndStreamSetPan(SndStream_t *pStream, unsigned int angle)
{
    int result;
    float degrees;

    degrees = angle / 65536.0f;
    degrees *= 360.0f;
    result = 0;
    if (_Snd_ModuleInfo.mStatus.mFlags.mActive && _Snd_ModuleInfo.mStatus.mFlags.mEnabled) {
        SND_LOCK();
        result = fn_8026E4C0(pStream->mHandle, degrees, -1);
        SND_UNLOCK();
    }
    return result;
}

void SndStreamGetStatus(SndStream_t *pStream, int *pStatus)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026F1E8(pStream->mHandle, pStatus);
        SND_UNLOCK();
    } else {
        pStatus[0] = 0;
    }
}

int SndStreamGetVol(SndStream_t *pStream)
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

int SndStreamGetPosition(int a, int b)
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

void SndStreamSetParam(SndStream_t *pStream, int a, int b)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026EAC0(pStream->mHandle, a, b);
        SND_UNLOCK();
    }
}

void SndStreamSetControl(SndStream_t *pStream, int a)
{
    if (SND_READY()) {
        SND_LOCK();
        fn_8026EF38(pStream->mHandle, a);
        SND_UNLOCK();
    }
}

void SndSetMasterVol(int a, int b)
{
    if (SND_READY()) {
        fn_8026ED1C(a, b);
    }
}

void SndSetOutputMode(int a, int b)
{
    _Snd_ModuleInfo.mUnk50 = a;
}

void SndSetServiceCallback(void (*pCallback)(int a, int b))
{
    if (SND_READY()) {
        _Snd_ModuleInfo.pServiceCallback = pCallback;
    }
}

void SndService(void)
{
    if (SND_READY()) {
        fn_802703A0();
        _SndProcessBanks();
        if (_Snd_ModuleInfo.pServiceCallback != 0) {
            _Snd_ModuleInfo.pServiceCallback(0, 0);
        }
    }
}

int SndAemsLoadSystem(ResFile_t *pRes, unsigned int index, int bank)
{
    int result;

    result = 0;
    if (SND_READY()) {
        SndSetHeap(_Snd_ModuleInfo.pBankTable, bank);
        _Snd_ModuleInfo.pAemsSystem = fn_801D2B7C(ResGetSize(pRes, index), 0, 0);
        ResLoadToBuffer(pRes, index, _Snd_ModuleInfo.pAemsSystem);
        result = fn_801B91A0(_Snd_ModuleInfo.pAemsSystem);
        _Snd_ModuleInfo.pAemsStreams = fn_801D2B7C(ResGetSize(pRes, index + 1), 0, 0);
        ResLoadToBuffer(pRes, index + 1, _Snd_ModuleInfo.pAemsStreams);
        fn_8026B124(_Snd_ModuleInfo.pAemsStreams);
    }
    return result;
}

int SndAemsUnloadSystem(void)
{
    int result;

    result = 0;
    if (SND_READY()) {
        if (_Snd_ModuleInfo.pAemsStreams != 0) {
            fn_8026B250();
            fn_801D2BD0(_Snd_ModuleInfo.pAemsStreams);
            _Snd_ModuleInfo.pAemsStreams = 0;
        }
        if (_Snd_ModuleInfo.pAemsSystem != 0) {
            fn_801B9328(_Snd_ModuleInfo.pAemsSystem);
            fn_801D2BD0(_Snd_ModuleInfo.pAemsSystem);
            _Snd_ModuleInfo.pAemsSystem = 0;
        }
    }
    return result;
}

static int _SndAemsBankTraverseFindPointer(void *pNode, void *pData, void *pOut)
{
    if (((SndAemsBankInfo_t *)pNode)->pData == pData) {
        *(SndAemsBankInfo_t **)pOut = (SndAemsBankInfo_t *)pNode;
        return 0;
    }
    return 1;
}

static void *_SndAemsBankAlloc(void *pData, int size, int c)
{
    SndAemsBankInfo_t *pBank;

    pBank = 0;
    fn_801C6D34(_Snd_ModuleInfo.pAemsBankList, 0, pData, &pBank, _SndAemsBankTraverseFindPointer, 1);
    if (pBank != 0) {
        pBank->mSize = size;
    }
    return pData;
}

static void _SndAemsBankRealloc(SndAemsBankInfo_t *pBank)
{
    pBank->pData = fn_801D310C(pBank->pData, pBank->mSize, 0, 0);
}

SndAemsBankInfo_t *SndAemsLoadBank(ResFile_t *pRes, unsigned int index, int bank)
{
    return SndAemsLoadBankWithStream(pRes, index, (ResFile_t *)-1, (unsigned int)-1, bank);
}

SndAemsBankInfo_t *SndAemsLoadBankWithStream(ResFile_t *pRes, unsigned int index, ResFile_t *pStreamRes,
                                      unsigned int streamIndex, int bank)
{
    SndAemsBankInfo_t *pBank;
    unsigned int size;
    char *pName;

    pBank = 0;
    if (SND_READY() && _Snd_ModuleInfo.pAemsBankList != 0) {
        pBank = (SndAemsBankInfo_t *)fn_801C6A20(_Snd_ModuleInfo.pAemsBankList);
        fn_801C6AA4(_Snd_ModuleInfo.pAemsBankList, pBank, 0);
        pBank->mBank = bank;
        SndSetHeap(_Snd_ModuleInfo.pBankTable, bank);
        size = ResGetSize(pRes, index);
        pBank->pData = fn_801D2BB0(1, size, 0, 0);
        DCFlushRange(pBank->pData, size);
        ResLoadToBuffer(pRes, index, pBank->pData);
        DCFlushRange(pBank->pData, size);
        if (pStreamRes != (ResFile_t *)-1 && streamIndex != (unsigned int)-1) {
            pBank->mFile.pRes = pStreamRes;
            pBank->mFile.mIndex = streamIndex;
            pName = SndAemsAllocFileDesc(&pBank->mFile);
            pBank->mHandle = fn_802697D8(pBank->pData, pName, 0, _SndAemsBankAlloc);
            _SndAemsBankRealloc(pBank);
        } else {
            pBank->mHandle = fn_802697D8(pBank->pData, 0, 0, _SndAemsBankAlloc);
            _SndAemsBankRealloc(pBank);
        }
    }
    return pBank;
}

int SndAemsUnloadBank(SndAemsBankInfo_t *pBank)
{
    int result;

    result = 0;
    if (SND_READY()) {
        result = fn_802692B8(pBank->mHandle);
        fn_801D2BD0(pBank->pData);
        fn_801C6C0C(_Snd_ModuleInfo.pAemsBankList, pBank);
    }
    return result;
}

char *SndAemsAllocFileDesc(SndFileDesc_t *pFile)
{
    static char outStr[8];
    int i;

    for (i = 0; i <= 3; i++) {
        if (_Snd_ModuleInfo.apFileDesc[i] == 0) {
            _Snd_ModuleInfo.apFileDesc[i] = pFile;
            sprintf(outStr, "AEMS%02d", i);
            return outStr;
        }
    }
    return outStr;
}

SndFileDesc_t *SndAemsDerefrenceFileDesc(const char *pName)
{
    int i;

    i = (pName[4] - '0') * 10;
    i += pName[5] - '0';
    return _Snd_ModuleInfo.apFileDesc[i];
}
