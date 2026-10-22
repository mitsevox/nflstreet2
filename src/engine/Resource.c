#include "game/fn_801C68FC.h"

typedef struct ResBlock_801F10B0 {
    unsigned int mUnk0;
    unsigned int mUnk4;
} ResBlock_801F10B0;

typedef struct ResHash_801F0A8C {
    int mType;
    int mUnk4;
    unsigned int mWidth;
} ResHash_801F0A8C;

typedef struct Res_801EDC2C {
    int mFile;
    char *pName;
    int mUnk8;
    int mUnkC;
    unsigned short mUnk10;
    unsigned char mUnk12;
    unsigned char mUnk13;
    unsigned short mNumRes;
    unsigned short mAlignment;
    unsigned int mDirTag;
    int mHashCount;
    unsigned char mCompressed;
    unsigned char mUnk21;
    unsigned short mVersion;
    unsigned int mDirSize;
    unsigned int mCompSize;
    unsigned int mHashSize;
    unsigned int mDirOffset;
    unsigned int mCompOffset;
    unsigned int mHashOffset;
    unsigned int mBaseOffset;
    ResBlock_801F10B0 *pDir;
    ResHash_801F0A8C *pHash;
    unsigned int *pHashParams;
    void *pHashTable;
    void **pSlots;
    ResBlock_801F10B0 *pBlocks;
    unsigned short mState;
    unsigned short mNumLocked;
    unsigned int mDataSize;
    int mHeap;
    unsigned int mBaseAddr;
    void *pExtra;
    unsigned int mIndex;
    int mMode;
    unsigned int *pAddrs;
    volatile unsigned char *pFlags;
    char mUnk7C[8];
    int mCacheHandle;
    int mUnk88;
    unsigned int mFlags;
    int mOpenCount;
    char mUnk94[0x10];
} Res_801EDC2C;

typedef struct ResRequest_801F12B4 {
    void (*pCallback)(Res_801EDC2C *pRes, int index, int a, int b, int c);
    int mUnk4;
    Res_801EDC2C *pRes;
    int mIndex;
    int mUnk10;
    int mUnk14;
    int mUnk18;
    char mUnk1C[4];
    int mNoStore;
    unsigned short mRaw;
    char mUnk26[2];
    int mUnk28;
    unsigned char mCache;
    unsigned char mCancelled;
    char mUnk2E[2];
    int mUnk30;
    unsigned int mTime;
} ResRequest_801F12B4;

typedef struct ResEvent_801F12B4 {
    int mType;
    char *pName;
    unsigned int mFlags;
    int mUnkC;
    int mUnk10;
    int mUnk14;
    unsigned int mTime;
    unsigned int mNow;
} ResEvent_801F12B4;

typedef struct ResLock_803E931C {
    char mUnk0[0x20];
} ResLock_803E931C;

typedef struct ResBuf_801EC914 {
    void *pData;
    unsigned int mSize;
    char mUnk8[0x14];
} ResBuf_801EC914;

typedef void (*ResDone_801EFAD8)(Res_801EDC2C *pRes, unsigned int index, unsigned int buffer, int err, void *pUser);

extern ResLock_803E931C lbl_803E92FC;
extern ResLock_803E931C lbl_803E931C;
extern unsigned char lbl_803EBD80;
extern int lbl_803EBD84;
extern int lbl_803EBD88;
extern void (*lbl_803EBD8C)(Res_801EDC2C *pRes, int index, ResEvent_801F12B4 *pEvent, int a, int b);
extern int lbl_803EBD90;
extern void (*lbl_803EBD94)(int type);
extern void (*lbl_803EBD98)(char *pName, int err);
extern unsigned char lbl_803EBD9C;
extern unsigned char lbl_803EBDAC;
extern unsigned int lbl_803EBDA0;
extern int lbl_803EBDA4;
extern int lbl_803EBDA8;
extern int lbl_803EBDB0;
extern void *lbl_803ECF7C;
extern ResRequest_801F12B4 *lbl_8039AE4C[16];
extern void *lbl_803ED668;
extern char lbl_802B17F0[];

extern unsigned int strlen(const char *s);
extern char *strcpy(char *pDst, const char *pSrc);
extern int sprintf(char *s, const char *format, ...);

extern Res_801EDC2C *fn_801C6B4C(void *pPool, Res_801EDC2C *pStart);
extern Res_801EDC2C *fn_801C6C84(void *pPool, Res_801EDC2C *pCur);
extern Res_801EDC2C *fn_801C6A20(void *pPool);
extern void fn_801C6C0C(void *pPool, Res_801EDC2C *pRes);
extern int fn_801C6DCC(void *pPool, void *pStart, char *pName, Res_801EDC2C **ppFound, int (*pCompare)());
extern char *fn_801C3284(char *pDst, const char *pSrc, int n);
extern int fn_801CA648(int file, unsigned int offset, void *pBuffer);
extern void fn_801CA834(int file);
extern int fn_801CB120(void);
extern int fn_801C96E4(char *pName, int mode);
extern void fn_801C97F0(int file);
extern int fn_801C9960(int file, void *pBuffer, int size, int flags);
extern void *fn_801D2BB0(int heap, unsigned int size, int memFlags, int b);
extern int fn_801D2BD0(void *p);
extern int fn_801EC8AC(void *pA, void *pB);
extern int fn_801EC8D4();
extern int fn_801ECC70(Res_801EDC2C *pRes, unsigned int index, unsigned int *pBuffer);
extern int fn_801ED634(Res_801EDC2C *pRes, unsigned int index, unsigned int buffer, int heap, int a, ResDone_801EFAD8 pDone, void *pUser, int mode);
extern int fn_801EDDF8(Res_801EDC2C *pRes, char *pName);
extern void fn_801EC650(Res_801EDC2C *pRes, int index, unsigned int *pOffset, unsigned int *pPrevSize,
                        unsigned int *pSize);
extern unsigned int fn_801EC6C4(Res_801EDC2C *pRes, int index);
extern int fn_801EE38C(Res_801EDC2C *pRes, char *pName, unsigned int size);
int fn_801EEFAC(Res_801EDC2C *pRes);
extern void fn_801F3104(Res_801EDC2C *pRes);
extern void fn_801F30CC(Res_801EDC2C *pRes);
extern int fn_801F1B6C(Res_801EDC2C *pRes);
int fn_801F08FC(Res_801EDC2C *pRes);
void fn_801EE91C(Res_801EDC2C *pRes);
extern int fn_801F1538(char *pString, unsigned int length, unsigned int *pParams);
extern int fn_801F155C(unsigned char *pData, unsigned int length, unsigned int *pParams);
extern int fn_801F33F0(Res_801EDC2C *pRes, unsigned int index, unsigned int *pSize);
extern void fn_801F2ED8(int mode);
extern void fn_801F2EE0(Res_801EDC2C *pRes, char *pName);
extern void *memset();
extern void *memcpy();
extern unsigned int fn_801F7B14(void);
extern void fn_801F7BD4(int err);
extern int fn_801F7C88(void);
extern void fn_801F7FA8(ResLock_803E931C *pLock);
extern void fn_801F8014(ResLock_803E931C *pLock);
extern void fn_801F809C(ResLock_803E931C *pLock);
extern void fn_801F80D0(ResLock_803E931C *pLock);
extern void fn_801F81AC(void);
extern int fn_8027F0DC(int a);
extern int fn_8027F77C(unsigned int codec);
extern void fn_8027FAB8(char *pName);
extern void fn_8027F3A4(unsigned int codec, ResBuf_801EC914 *pSrc, ResBuf_801EC914 *pDst);
extern void fn_80239CEC(void *p, unsigned int size);
extern void fn_801F318C(Res_801EDC2C *pRes, int index, int offset, int data, int size);
extern void fn_801F23DC(unsigned int type, void *pData);
extern char lbl_802F9508[];
extern int fn_8027F21C(void);
extern int fn_8027F2C0(void);

void fn_801F1230(Res_801EDC2C *pRes, unsigned int flags);
void fn_801F12B4(unsigned int time);
int fn_801F0D34(Res_801EDC2C *pRes);
int fn_801F010C(Res_801EDC2C *pRes, unsigned int index);
void fn_801F1488(Res_801EDC2C *pRes, int index);
unsigned int fn_801EF390(Res_801EDC2C *pRes, unsigned int index, int heap);
unsigned int fn_801F0C50(Res_801EDC2C *pRes, unsigned int index);

void fn_801EC914(int result, int arg, ResRequest_801F12B4 *pReq)
{
    Res_801EDC2C *pRes;
    int index;
    int err;
    unsigned int codec;
    ResBuf_801EC914 src;
    ResBuf_801EC914 dst;
    ResEvent_801F12B4 event;
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;
    void *track[2];

    pRes = pReq->pRes;
    index = pReq->mIndex;
    err = 0;
    if (lbl_803EBD8C != 0) {
        event.mType = 2;
        event.pName = pRes->pName;
        event.mFlags = pRes->mFlags;
        event.mUnkC = pReq->mUnk18;
        event.mUnk14 = result;
        event.mTime = pReq->mTime;
        event.mNow = lbl_803EBDA0;
        lbl_803EBD8C(pRes, index, &event, arg, lbl_803EBD90);
    }
    if (result < pReq->mUnk10) {
        err = fn_801F7C88();
        fn_801D2BD0((void *)pReq->mUnk18);
        pRes->pFlags[index] &= ~0x10;
    } else {
        if (pRes->pBlocks != 0 && pReq->mRaw == 0) {
            codec = pRes->pBlocks[index].mUnk0;
        } else {
            codec = 0;
        }
        if (lbl_803EBD9C != 0 && pReq->pRes->mCacheHandle >= 0 && pReq->mCache != 0) {
            fn_801F318C(pReq->pRes, pReq->mIndex, pReq->mUnk28, pReq->mUnk18, pReq->mUnk10);
        }
        if (codec != 0 && fn_8027F77C(codec) == 0) {
            memset((void *)&src, 0, 0x1C);
            memset((void *)&dst, 0, 0x1C);
            src.mSize = pReq->mUnk10;
            src.pData = fn_801D2BB0(1, src.mSize, 0, 0);
            memcpy(src.pData, (void *)pReq->mUnk18, src.mSize);
            dst.mSize = pReq->mUnk14;
            dst.pData = (void *)pReq->mUnk18;
            fn_8027FAB8(lbl_802F9508);
            fn_8027F3A4(codec, &src, &dst);
            fn_8027FAB8(0);
            fn_801D2BD0(src.pData);
        }
        if (pReq->mNoStore == 0) {
            pRes->pAddrs[index] = pReq->mUnk18;
            pRes->pFlags[index] |= 6;
        }
        pRes->pFlags[index] &= ~0x10;
        fn_801EC650(pRes, index, &offset, &prevSize, &size);
        fn_80239CEC((void *)pReq->mUnk18, size);
        if (pReq->pCallback != 0 && pReq->mTime == 0) {
            pReq->pCallback(pRes, index, pReq->mUnk18, 0, pReq->mUnk4);
        }
    }
    if (pReq->mTime != 0) {
        pReq->mUnk30 = err;
        pReq->mCancelled = 1;
    } else {
        fn_801D2BD0(pReq);
    }
    track[0] = pRes;
    track[1] = (void *)index;
    fn_801F23DC(3, track);
    fn_801F8014(&lbl_803E92FC);
    lbl_803EBD84--;
    fn_801F809C(&lbl_803E92FC);
}

int fn_801ECBE4(unsigned int tag, int count)
{
    int size;

    switch (tag) {
    case 0x54455246:
        size = 8;
        break;
    case 0x434F4D50:
    case 0x44495231:
        size = count * 8;
        break;
    case 0x48534831:
        size = count * 4 + 0x10;
        break;
    case 0x48534832:
        size = count * 2 + 0xC;
        break;
    default:
        size = 0;
        break;
    }
    return size;
}

static inline void WaitLoad_801EF390(Res_801EDC2C *pRes, unsigned int index, int type)
{
    unsigned int start;
    unsigned int elapsed;

    if (pRes != 0) {
        start = fn_801F7B14();
        while (pRes->pFlags[index] & 0x10) {
            elapsed = fn_801F7B14() - start;
            if (lbl_803EBD94 != 0 && elapsed > 0x4650) {
                lbl_803EBD94(type);
            }
            if (fn_801CB120() != 0) {
                fn_801CA834(pRes->mFile);
            } else {
                fn_801F81AC();
            }
        }
    }
}

static inline void Find_801EEB44(char *pName, Res_801EDC2C **ppRes)
{
    *ppRes = 0;
    fn_801C6DCC(lbl_803ED668, 0, pName, ppRes, fn_801EC8D4);
}

unsigned int fn_801EDC2C(Res_801EDC2C *pRes, int index)
{
    if (!(pRes->pFlags[index] & 4)) {
        if (!(pRes->pFlags[index] & 8)) {
            pRes->pFlags[index] |= 4;
        } else {
            pRes->mNumLocked++;
            pRes->pAddrs[index] = pRes->mBaseAddr + fn_801EC6C4(pRes, index);
            pRes->pFlags[index] |= 4;
        }
    }
    return pRes->pAddrs[index];
}

unsigned int fn_801EDCD0(Res_801EDC2C *pRes, int index)
{
    if (pRes->pFlags[index] & 4) {
        if (pRes->pFlags[index] & 1) {
            if (!(pRes->pFlags[index] & 8)) {
                pRes->pFlags[index] &= ~4;
            } else {
                pRes->mNumLocked--;
                pRes->pAddrs[index] = 0;
                pRes->pFlags[index] &= ~4;
            }
            return pRes->pAddrs[index];
        }
        return 0;
    }
    return pRes->pAddrs[index];
}

int fn_801EDD68(int file, void *pBuffer)
{
    int err;

    err = 0;
    if (fn_801C9960(file, pBuffer, 8, 0) < 8) {
        err = fn_801F7C88();
    }
    return err;
}

int fn_801EDDB0(int file, void *pBuffer, int size)
{
    int err;

    err = 0;
    if (fn_801C9960(file, pBuffer, size, 0) < size) {
        err = fn_801F7C88();
    }
    return err;
}

void *fn_801EE700(Res_801EDC2C *pRes, unsigned int index, int heap, unsigned int *pBuffer, int noFlags)
{
    char name[0x10];
    unsigned int size;
    unsigned int offset;
    unsigned int prevSize;
    void *p;

    *pBuffer = 0;
    if (lbl_803EBDAC != 0 && fn_801F33F0(pRes, index, &size) != 0) {
        if (pRes->pDir[index].mUnk4 < size) {
            fn_801C3284(name, pRes->pName, 0xB);
            sprintf(name + strlen(name), lbl_802B17F0, index);
            if (noFlags != 0) {
                p = fn_801D2BB0(heap, size, 0, 0);
            } else {
                p = fn_801D2BB0(heap, size, lbl_803EBDB0, 0);
            }
            if (p != 0) {
                pRes->mFlags |= 0x40;
                *pBuffer = (unsigned int)p;
            }
            return p;
        }
        if (pRes->mState == 2) {
            pRes->pFlags[index] = 0x20;
        }
    }
    if (pRes->mState == 1 && pRes->mBaseAddr != 0 && heap == pRes->mHeap) {
        pRes->pFlags[index] = 8;
        *pBuffer = fn_801EDC2C(pRes, index);
    } else if (pRes->mState == 2 || pRes->mState == 3) {
        *pBuffer = pRes->mBaseAddr + pRes->mBaseOffset + fn_801EC6C4(pRes, index);
    } else {
        fn_801EC650(pRes, index, &offset, &prevSize, &size);
        fn_801C3284(name, pRes->pName, 0xB);
        sprintf(name + strlen(name), lbl_802B17F0, index);
        if (noFlags != 0) {
            p = fn_801D2BB0(heap, size, 0, 0);
        } else {
            p = fn_801D2BB0(heap, size, lbl_803EBDB0, 0);
        }
        if (p != 0) {
            *pBuffer = (unsigned int)p;
        }
    }
    return pBuffer;
}

void fn_801EE91C(Res_801EDC2C *pRes)
{
    int i;
    int count;

    count = fn_801F0D34(pRes);
    for (i = 0; i < count; i++) {
        fn_801F1488(pRes, i);
    }
}

int fn_801EE970(int heap)
{
    int err;

    err = 0;
    if (fn_8027F2C0() == 0) {
        fn_8027F0DC(0);
    }
    if (lbl_803EBD80 == 0) {
        fn_801F7FA8(&lbl_803E931C);
        fn_801F7FA8(&lbl_803E92FC);
        fn_801F8014(&lbl_803E931C);
        lbl_803ED668 = fn_801C68FC(1, 1, heap, 0xA4, fn_801EC8AC, 0);
        lbl_803ECF7C = fn_801D2BB0(1, 0x8000, lbl_803EBDB0, 0);
        lbl_803EBD80 = 1;
        lbl_803EBD9C = 0;
        fn_801F2ED8(0);
        fn_801F809C(&lbl_803E931C);
    } else {
        err = 0xF0001;
    }
    lbl_803EBDA4 = 0;
    lbl_803EBDA8 = 0;
    lbl_803EBDA0 = 0;
    fn_801F7BD4(err);
    return err;
}

int fn_801EEA60(void)
{
    Res_801EDC2C *pRes;
    Res_801EDC2C *pNext;
    int err;

    err = 0;
    if (lbl_803EBD80 != 0) {
        fn_801F8014(&lbl_803E931C);
        pNext = fn_801C6B4C(lbl_803ED668, 0);
        while (pNext != 0) {
            pRes = pNext;
            fn_801F1230(pRes, 1);
            pNext = fn_801C6C84(lbl_803ED668, pRes);
            fn_801EEFAC(pRes);
        }
        fn_801C69E4(lbl_803ED668);
        fn_801D2BD0(lbl_803ECF7C);
        fn_801F809C(&lbl_803E931C);
        fn_801F80D0(&lbl_803E931C);
        fn_801F80D0(&lbl_803E92FC);
        lbl_803EBD80 = 0;
    } else {
        err = 0xF0002;
    }
    if (fn_8027F2C0() != 0) {
        fn_8027F21C();
    }
    fn_801F7BD4(err);
    return err;
}

Res_801EDC2C *fn_801EEB44(char *pName, int mode)
{
    Res_801EDC2C *pRes;
    int err;

    pRes = 0;
    fn_801F8014(&lbl_803E931C);
    err = 0;
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else {
        Find_801EEB44(pName, &pRes);
        if (pRes == 0) {
            pRes = fn_801C6A20(lbl_803ED668);
            if (pRes == 0) {
                err = fn_801F7C88();
                goto done;
            }
            memset(pRes, 0, sizeof(Res_801EDC2C));
            pRes->mFile = fn_801C96E4(pName, mode);
            if (pRes->mFile < 0) {
                err = fn_801F7C88();
                goto done;
            }
            err = fn_801EDDF8(pRes, pName);
            if (err != 0) {
                fn_801C97F0(pRes->mFile);
                goto done;
            }
            if (lbl_803EBD9C != 0) {
                fn_801F2EE0(pRes, pName);
            }
            fn_801C6AA4(lbl_803ED668, pRes, 0);
        }
        pRes->mOpenCount++;
    }
done:
    if (err != 0) {
        if (pRes != 0) {
            fn_801C6C0C(lbl_803ED668, pRes);
            pRes = 0;
        }
        if (lbl_803EBD98 != 0) {
            lbl_803EBD98(pName, err);
        }
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return pRes;
}

Res_801EDC2C *fn_801EECD0(Res_801EDC2C *pParent, unsigned int index, int heap, int mode)
{
    Res_801EDC2C *pRes;
    char *pName;
    int err;
    unsigned int digits;
    unsigned int j;
    int len;
    unsigned int offset;
    unsigned int value;

    pRes = 0;
    fn_801F8014(&lbl_803E931C);
    err = 0;
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else {
        digits = 0;
        pRes = 0;
        for (j = pParent->mNumRes; j != 0; j /= 10) {
            digits++;
        }
        pName = fn_801D2BB0(1, strlen(pParent->pName) + 1 + digits, lbl_803EBDB0, 0);
        if (pName == 0) {
            err = fn_801F7C88();
            goto done;
        }
        strcpy(pName, pParent->pName);
        pName[0xC] = 0;
        len = strlen(pName);
        value = index;
        for (j = 0; j < digits; j++) {
            pName[len + digits - 1 - j] = value % 10 + '0';
            value /= 10;
        }
        pName[len + digits] = 0;
        fn_801C6DCC(lbl_803ED668, 0, pName, &pRes, fn_801EC8D4);
        if (pRes == 0) {
            pRes = fn_801C6A20(lbl_803ED668);
            if (pRes == 0) {
                err = fn_801F7C88();
                goto done;
            }
            memset(pRes, 0, sizeof(Res_801EDC2C));
            pRes->mFile = -1;
            if (mode != 1) {
                pRes->mState = 3;
            } else {
                pRes->mState = 2;
            }
            pRes->mMode = mode;
            pRes->mBaseAddr = fn_801EF390(pParent, index, heap);
            pRes->pExtra = pParent;
            pRes->mIndex = index;
            err = fn_801EE38C(pRes, pName, fn_801F0C50(pRes->pExtra, pRes->mIndex));
            if (err != 0) {
                goto done;
            }
            for (index = 0; index < pRes->mNumRes; index++) {
                pRes->pAddrs[index] = 0;
                fn_801EC650(pRes, index, &offset, &value, &value);
            }
            fn_801C6AA4(lbl_803ED668, pRes, 0);
        } else {
            fn_801D2BD0(pName);
        }
        pRes->mOpenCount++;
    }
done:
    if (err != 0 && pRes != 0) {
        fn_801C6C0C(lbl_803ED668, pRes);
        pRes = 0;
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return pRes;
}

int fn_801EEFAC(Res_801EDC2C *pRes)
{
    Res_801EDC2C *pFound;
    unsigned int i;
    int err;
    int close;
    int flush;

    err = 0;
    close = 1;
    flush = 1;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes->pName == 0) {
        err = 0xF0006;
    } else {
        Find_801EEB44(pRes->pName, &pFound);
        if (pFound != 0 && pFound == pRes) {
            if (pRes->mOpenCount != 0 && --pRes->mOpenCount != 0 && (pRes->mFlags & 1)) {
                close = 0;
                if (pRes->mFlags & 2) {
                    flush = 1;
                } else {
                    flush = 0;
                }
            }
            if (pRes->mState == 2) {
                if ((pRes->mFlags & 0x40) && pRes->mUnk21 == 0) {
                    fn_801EE91C(pRes);
                    err = fn_801F08FC(pRes);
                }
                if (pRes->pExtra == 0) {
                    err = fn_801F08FC(pRes);
                }
                if (pRes->pName != 0) {
                    fn_801D2BD0(pRes->pName);
                }
                if (pRes->pAddrs != 0) {
                    fn_801D2BD0(pRes->pAddrs);
                    pRes->pAddrs = 0;
                }
                if (pRes->pFlags != 0) {
                    fn_801D2BD0((void *)pRes->pFlags);
                    pRes->pFlags = 0;
                }
                if (pRes->pExtra != 0) {
                    fn_801F1488(pRes->pExtra, pRes->mIndex);
                    fn_801F010C(pRes->pExtra, pRes->mIndex);
                }
            } else if (pRes->mState == 3) {
                if ((pRes->mFlags & 0x40) && pRes->mUnk21 == 0) {
                    fn_801EE91C(pRes);
                    err = fn_801F08FC(pRes);
                }
                if (pRes->pExtra == 0) {
                    err = fn_801F08FC(pRes);
                }
                if (pRes->pName != 0) {
                    fn_801D2BD0(pRes->pName);
                }
                if (pRes->pAddrs != 0) {
                    fn_801D2BD0(pRes->pAddrs);
                    pRes->pAddrs = 0;
                }
                if (pRes->pFlags != 0) {
                    fn_801D2BD0((void *)pRes->pFlags);
                    pRes->pFlags = 0;
                }
                if (pRes->pExtra != 0) {
                    fn_801F1488(pRes->pExtra, pRes->mIndex);
                    fn_801F010C(pRes->pExtra, pRes->mIndex);
                }
                if (pRes->mBaseOffset != 0) {
                    fn_801D2BD0((void *)pRes->mBaseOffset);
                }
            } else {
                if (lbl_803EBD9C != 0 && pRes->mCacheHandle >= 0) {
                    fn_801F3104(pRes);
                    if (close) {
                        fn_801F30CC(pRes);
                    }
                }
                if (flush == 1 && pRes->mUnk21 == 0) {
                    if (close) {
                        fn_801EE91C(pRes);
                    }
                    err = fn_801F08FC(pRes);
                }
                if (pRes->mUnk21 != 0) {
                    err = fn_801F1B6C(pRes);
                }
                if (close == 1) {
                    if (pRes->pSlots != 0) {
                        for (i = 0; i < pRes->mNumRes; i++) {
                            if (pRes->pSlots[i] != 0) {
                                fn_801D2BD0(pRes->pSlots[i]);
                            }
                        }
                        fn_801D2BD0(pRes->pSlots);
                    }
                    if (pRes->pName != 0) {
                        fn_801D2BD0(pRes->pName);
                    }
                    if (pRes->pDir != 0) {
                        fn_801D2BD0(pRes->pDir);
                    }
                    if (pRes->pHash != 0) {
                        fn_801D2BD0(pRes->pHash);
                    }
                    if (pRes->pBlocks != 0) {
                        fn_801D2BD0(pRes->pBlocks);
                    }
                    if (pRes->pAddrs != 0) {
                        fn_801D2BD0(pRes->pAddrs);
                        pRes->pAddrs = 0;
                    }
                    if (pRes->pFlags != 0) {
                        fn_801D2BD0((void *)pRes->pFlags);
                        pRes->pFlags = 0;
                    }
                    fn_801C97F0(pRes->mFile);
                }
            }
            if (close) {
                fn_801C6C0C(lbl_803ED668, pRes);
            }
        } else {
            err = 0xF0005;
        }
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return err;
}

unsigned int fn_801EF390(Res_801EDC2C *pRes, unsigned int index, int heap)
{
    unsigned int buffer;
    void *p;
    int err;

    buffer = 0;
    err = 0;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else {
        WaitLoad_801EF390(pRes, index, 1);
        if (!(pRes->pFlags[index] & 2)) {
            p = fn_801EE700(pRes, index, heap, &buffer, 0);
            if (buffer != 0) {
                err = fn_801ECC70(pRes, index, &buffer);
            } else {
                err = fn_801F7C88();
            }
            if (err == 0) {
                pRes->pAddrs[index] = buffer;
                pRes->pFlags[index] |= 7;
            } else {
                if (p != 0) {
                    fn_801D2BD0(p);
                }
                buffer = 0;
            }
        } else {
            buffer = fn_801EDC2C(pRes, index);
        }
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return buffer;
}

unsigned int fn_801EF548(Res_801EDC2C *pRes, unsigned int index, int heap, int a, ResDone_801EFAD8 pDone,
                         void *pUser)
{
    unsigned int buffer;
    void *p;
    int err;

    buffer = 0;
    fn_801F8014(&lbl_803E931C);
    err = 0;
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else {
        WaitLoad_801EF390(pRes, index, 1);
        if (!(pRes->pFlags[index] & 2)) {
            p = fn_801EE700(pRes, index, heap, &buffer, 1);
            if (buffer != 0) {
                pRes->pFlags[index] |= 0x11;
                err = fn_801ED634(pRes, index, buffer, heap, a, pDone, pUser, 0);
            } else {
                err = fn_801F7C88();
            }
            if (err != 0) {
                if (p != 0) {
                    fn_801D2BD0(p);
                }
                buffer = 0;
            }
        } else {
            buffer = fn_801EDC2C(pRes, index);
            if (pDone != 0) {
                pDone(pRes, index, buffer, 0, pUser);
            }
        }
        if (lbl_803EBD88 > 0 && !(pRes->mFlags & 4)) {
            WaitLoad_801EF390(pRes, index, 1);
        }
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return buffer;
}

unsigned int fn_801EF7BC(Res_801EDC2C *pRes, unsigned int index, unsigned int buffer)
{
    int err;

    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
        buffer = 0;
    } else if (index > pRes->mNumRes) {
        err = 0xF0006;
        buffer = 0;
    } else {
        WaitLoad_801EF390(pRes, index, 1);
        if (!(pRes->pFlags[index] & 2)) {
            err = fn_801ECC70(pRes, index, &buffer);
            if (err == 0) {
                pRes->pAddrs[index] = buffer;
                pRes->pFlags[index] = 6;
            } else {
                buffer = 0;
            }
        } else {
            buffer = fn_801EDC2C(pRes, index);
            err = 0xF0007;
        }
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return buffer;
}

int fn_801EF92C(Res_801EDC2C *pRes, unsigned int index, void *pBuffer)
{
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;
    int err;

    err = 0;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index > pRes->mNumRes) {
        err = 0xF0006;
    } else {
        WaitLoad_801EF390(pRes, index, 1);
        if (pRes->pFlags[index] & 2) {
            err = 0xF000B;
        } else {
            fn_801EC650(pRes, index, &offset, &prevSize, &size);
            if (size != prevSize) {
                err = 0xF000C;
            } else if (pRes->mState != 2 && pRes->mState != 3) {
                err = fn_801CA648(pRes->mFile, offset + pRes->mBaseOffset, pBuffer);
            } else {
                memcpy((void *)(pRes->mBaseAddr + pRes->mBaseOffset + fn_801EC6C4(pRes, index)), pBuffer, size);
            }
        }
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return err;
}

unsigned int fn_801EFAD8(Res_801EDC2C *pRes, unsigned int index, int heap, unsigned int buffer, int a,
                         ResDone_801EFAD8 pDone, void *pUser)
{
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;
    int err;

    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else {
        WaitLoad_801EF390(pRes, index, 1);
        if (!(pRes->pFlags[index] & 2)) {
            fn_801EC650(pRes, index, &offset, &prevSize, &size);
            if (buffer != 0) {
                pRes->pFlags[index] |= 0x10;
                err = fn_801ED634(pRes, index, buffer, heap, a, pDone, pUser, 0);
            } else {
                err = fn_801F7C88();
            }
            if (err != 0) {
                buffer = 0;
            }
        } else {
            buffer = fn_801EDC2C(pRes, index);
            err = 0xF0007;
            pDone(pRes, index, buffer, 0xF0007, pUser);
        }
        if (lbl_803EBD88 > 0 && !(pRes->mFlags & 4)) {
            WaitLoad_801EF390(pRes, index, 1);
        }
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return buffer;
}

unsigned int fn_801EFD2C(Res_801EDC2C *pRes, unsigned int index, int heap, unsigned int buffer, int a,
                         ResDone_801EFAD8 pDone, void *pUser)
{
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;
    int err;

    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else {
        WaitLoad_801EF390(pRes, index, 1);
        if (!(pRes->pFlags[index] & 2)) {
            fn_801EC650(pRes, index, &offset, &prevSize, &size);
            if (buffer != 0) {
                pRes->pFlags[index] |= 0x10;
                err = fn_801ED634(pRes, index, buffer, heap, a, pDone, pUser, 1);
            } else {
                err = fn_801F7C88();
            }
            if (err != 0) {
                buffer = 0;
            }
        } else {
            buffer = fn_801EDC2C(pRes, index);
            err = 0xF0007;
            pDone(pRes, index, buffer, 0xF0007, pUser);
        }
        if (lbl_803EBD88 > 0 && !(pRes->mFlags & 4)) {
            WaitLoad_801EF390(pRes, index, 1);
        }
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return buffer;
}

int fn_801EFF80(Res_801EDC2C *pRes, unsigned int index, unsigned int buffer)
{
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;
    unsigned int src;
    int err;

    err = 0;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
        buffer = 0;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
        buffer = 0;
    } else {
        WaitLoad_801EF390(pRes, index, 1);
        if (pRes->pFlags[index] & 2) {
            fn_801EC650(pRes, index, &offset, &prevSize, &size);
            if (pRes->pFlags[index] & 4) {
                src = pRes->pAddrs[index];
            } else {
                src = *(unsigned int *)pRes->pAddrs[index];
            }
            memcpy((void *)buffer, (void *)src, size);
        } else {
            err = fn_801ECC70(pRes, index, &buffer);
        }
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return err;
}

int fn_801F010C(Res_801EDC2C *pRes, unsigned int index)
{
    int err;

    err = 0;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else {
        WaitLoad_801EF390(pRes, index, 1);
        if ((pRes->pFlags[index] & 2) && !(pRes->pFlags[index] & 0x40)) {
            if ((pRes->pFlags[index] & 1) && !(pRes->pFlags[index] & 0x20)) {
                if (!(pRes->pFlags[index] & 8)) {
                    err = fn_801D2BD0((void *)pRes->pAddrs[index]);
                } else {
                    fn_801EDCD0(pRes, index);
                }
            }
            if (pRes->mState != 2 && pRes->mState != 3) {
                pRes->pAddrs[index] = 0;
                pRes->pFlags[index] = 0;
            } else {
                pRes->pFlags[index] = 0;
                pRes->pAddrs[index] = 0;
            }
        }
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return err;
}

int fn_801F08FC(Res_801EDC2C *pRes)
{
    unsigned int index;
    int result;
    int err;

    err = 0;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else {
        for (index = 0; index < pRes->mNumRes; index++) {
            WaitLoad_801EF390(pRes, index, 1);
            if (pRes->pFlags[index] & 2) {
                result = fn_801F010C(pRes, index);
                if (result != 0) {
                    err = result;
                }
            }
        }
        if (pRes->mState == 1 && pRes->mBaseAddr != 0) {
            result = fn_801D2BD0((void *)pRes->mBaseAddr);
            if (result != 0) {
                err = result;
            }
            result = fn_801D2BD0(pRes->pExtra);
            if (result != 0) {
                err = result;
            }
            pRes->mBaseAddr = 0;
            pRes->pExtra = 0;
            pRes->mHeap = 0;
            pRes->mNumLocked = 0;
        }
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return err;
}

int fn_801F0A8C(Res_801EDC2C *pRes, char *pName)
{
    ResHash_801F0A8C *pHash;
    int err;
    int index;
    int hash;
    int value;

    pHash = pRes->pHash;
    index = -1;
    fn_801F8014(&lbl_803E931C);
    err = 0;
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else if (pHash == 0 || pRes->pHashTable == 0 || pRes->mHashCount == 0) {
        err = 0xF000A;
    } else {
        switch (pHash->mType) {
        case 1:
            hash = fn_801F1538(pName, strlen(pName), pRes->pHashParams);
            break;
        case 2:
            hash = fn_801F155C((unsigned char *)pName, strlen(pName), pRes->pHashParams);
            break;
        default:
            index = -1;
            err = 0xF000A;
            goto done;
        }
        for (index = 0; index < pRes->mNumRes; index++) {
            switch (pHash->mWidth) {
            case 1:
                value = ((unsigned char *)pRes->pHashTable)[index];
                break;
            case 2:
                value = ((unsigned short *)pRes->pHashTable)[index];
                break;
            case 4:
                value = ((int *)pRes->pHashTable)[index];
                break;
            default:
                index = -1;
                err = 0xF000A;
                goto done;
            }
            if (value == hash) {
                break;
            }
        }
        if (index >= pRes->mNumRes) {
            index = -1;
        }
    }
done:
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return index;
}

unsigned int fn_801F0C50(Res_801EDC2C *pRes, unsigned int index)
{
    unsigned int size;
    unsigned int offset;
    unsigned int prevSize;
    int err;

    prevSize = 0;
    size = 0;
    err = 0;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else if (lbl_803EBDAC == 0 || fn_801F33F0(pRes, index, &size) == 0) {
        fn_801EC650(pRes, index, &offset, &prevSize, &size);
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return size;
}

int fn_801F0D34(Res_801EDC2C *pRes)
{
    int count;
    int err;

    count = 0;
    err = 0;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else {
        count = pRes->mNumRes;
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return count;
}

int fn_801F0DB8(Res_801EDC2C *pRes, unsigned int index)
{
    int err;
    int loaded;

    err = 0;
    loaded = 0;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else if (pRes->pFlags[index] & 2) {
        loaded = 1;
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return loaded;
}

int fn_801F0E68(Res_801EDC2C *pRes, unsigned int index)
{
    int err;
    int loading;

    err = 0;
    loading = 0;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else if (pRes->pFlags[index] & 0x10) {
        loading = 1;
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return loading;
}

int fn_801F0F18(int noWait)
{
    unsigned int start;
    unsigned int elapsed;

    if (noWait == 0) {
        start = fn_801F7B14();
        while (lbl_803EBD84 != 0) {
            elapsed = fn_801F7B14() - start;
            if (lbl_803EBD94 != 0 && elapsed > 0x4650) {
                lbl_803EBD94(2);
            }
            fn_801F81AC();
        }
        fn_801F12B4(-1);
    }
    return lbl_803EBD84;
}

int fn_801F0F9C(char *pName)
{
    Res_801EDC2C *pFound;
    int open;

    pFound = 0;
    open = 0;
    if (lbl_803EBD80 != 0) {
        fn_801C6DCC(lbl_803ED668, 0, pName, &pFound, fn_801EC8D4);
        if (pFound != 0) {
            open = 1;
        }
    }
    return open;
}

int fn_801F1008(Res_801EDC2C *pRes)
{
    Res_801EDC2C *pFound;
    int err;
    int result;

    err = 0;
    result = 0;
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else {
        Find_801EEB44(pRes->pName, &pFound);
        if (pFound != 0 && pFound == pRes) {
            result = pFound->mState == 2 || pFound->mState == 3;
        } else {
            err = 0xF0005;
        }
    }
    fn_801F7BD4(err);
    return result;
}

int fn_801F10B0(Res_801EDC2C *pRes, unsigned int index, unsigned int *pSize, unsigned int *pOffset, int *pFile)
{
    unsigned int offset;
    unsigned int prevSize;
    int err;

    err = 0;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else if (pRes->pBlocks != 0 && pRes->pBlocks[index].mUnk0 != 0) {
        err = 0xF000E;
    } else {
        fn_801EC650(pRes, index, &offset, &prevSize, pSize);
        *pOffset = offset + pRes->mBaseOffset;
        *pFile = pRes->mFile;
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return err;
}

void fn_801F11AC(Res_801EDC2C *pRes, unsigned int flags)
{
    int err;

    err = 0;
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else {
        fn_801F8014(&lbl_803E931C);
        pRes->mFlags |= flags;
        fn_801F809C(&lbl_803E931C);
    }
    fn_801F7BD4(err);
}

void fn_801F1230(Res_801EDC2C *pRes, unsigned int flags)
{
    int err;

    err = 0;
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else {
        fn_801F8014(&lbl_803E931C);
        pRes->mFlags &= ~flags;
        fn_801F809C(&lbl_803E931C);
    }
    fn_801F7BD4(err);
}

void fn_801F12B4(unsigned int time)
{
    ResRequest_801F12B4 *pReq;
    Res_801EDC2C *pRes;
    ResEvent_801F12B4 event;
    int index;

    fn_801F8014(&lbl_803E931C);
    if (time != -1) {
        lbl_803EBDA0 = time;
    }
    if (time == 0) {
        time = -1;
    }
    while (lbl_803EBDA8 != lbl_803EBDA4 && time >= lbl_8039AE4C[lbl_803EBDA8]->mTime) {
        pReq = lbl_8039AE4C[lbl_803EBDA8];
        if (pReq->mCancelled == 0) {
            pRes = pReq->pRes;
            index = pReq->mIndex;
            WaitLoad_801EF390(pRes, index, 1);
        }
        lbl_803EBDA8 = (lbl_803EBDA8 + 1) & 0xF;
        if (lbl_803EBD8C != 0) {
            event.mType = 3;
            event.pName = pReq->pRes->pName;
            event.mFlags = pReq->pRes->mFlags;
            event.mUnk14 = pReq->mUnk14;
            event.mUnkC = pReq->mUnk18;
            event.mTime = pReq->mTime;
            event.mNow = lbl_803EBDA0;
            lbl_803EBD8C(pReq->pRes, pReq->mIndex, &event, 0, lbl_803EBD90);
        }
        pReq->pCallback(pReq->pRes, pReq->mIndex, pReq->mUnk18, pReq->mUnk30, pReq->mUnk4);
        fn_801D2BD0(pReq);
    }
    fn_801F809C(&lbl_803E931C);
}

void fn_801F1488(Res_801EDC2C *pRes, int index)
{
    pRes->pFlags[index] &= ~0x40;
}

int fn_801F149C(Res_801EDC2C *pRes)
{
    int alignment;
    int err;

    alignment = 0;
    err = 0;
    fn_801F8014(&lbl_803E931C);
    if (lbl_803EBD80 == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else {
        alignment = pRes->mAlignment;
    }
    fn_801F809C(&lbl_803E931C);
    fn_801F7BD4(err);
    return alignment;
}

int fn_801F1520(int flags)
{
    int old;

    old = lbl_803EBDB0;
    lbl_803EBDB0 = flags;
    return old;
}

int fn_801F1530(void)
{
    return lbl_803EBDB0;
}
