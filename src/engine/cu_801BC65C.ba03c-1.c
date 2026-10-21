#include "engine/cu_801BA03C.ba03c-1.h"

typedef struct Object_801BE594 {
    unsigned char mUnknown0[6];
    unsigned short mUnknown6;
    unsigned char mUnknown8[68];
    float mUnknown4C;
} Object_801BE594;

typedef struct Frame_801BC7C0 {
    float mWeight;
    float mBlend;
    unsigned char mFlags;
    unsigned char mChannel;
    unsigned char mUnknownA[22];
    unsigned short mSlot;
    unsigned short mFrame;
    void *mpCompress;
    void *mpMotion;
} Frame_801BC7C0;

/* Static frame list returned by fn_801BC7C0. */
typedef struct FrameList_801BC7C0 {
    unsigned short mCount;
    unsigned short mMax;
    Frame_801BC7C0 mFrames[24];
} FrameList_801BC7C0;

typedef struct Quat_801BC67C {
    float mValues[4];
} Quat_801BC67C;

extern FrameList_801BC7C0 lbl_8037E858;

int abs(int x);

Object_801BE594 *fn_801BE594(void *pObject, int state);
void fn_801EBFA0(Quat_801BC67C *pOut, int x, int y, int z);
void fn_801EC048(Quat_801BC67C *pOut, Quat_801BC67C *pA, Quat_801BC67C *pB, float t);
void fn_801EBD8C(int *pOut, Quat_801BC67C *pQuat);
void fn_801CF810(int *pOut, int *pA, int *pB, float t);

void *fn_801BC780(Object_801BC084 *pFile, int group);

unsigned short fn_801BC65C(int state, Object_801BC084 *pFile, Object_801BE594 *pInfo)
{
    if (pFile->mFlags & 4)
        return pInfo->mUnknown6;
    return 0xFFFF;
}

void fn_801BC67C(int *pOut, int *pA, int *pB, float t)
{
    Quat_801BC67C b;
    Quat_801BC67C a;
    int dx = (pA[0] - pB[0]) << 8 >> 8;
    int dy = (pA[1] - pB[1]) << 8 >> 8;
    int dz = (pA[2] - pB[2]) << 8 >> 8;

    if (abs(dx) + abs(dy) + abs(dz) > 0x400000) {
        fn_801EBFA0(&a, pA[1], pA[2], pA[0]);
        fn_801EBFA0(&b, pB[1], pB[2], pB[0]);
        fn_801EC048(&a, &a, &b, t);
        fn_801EBD8C(pOut, &a);
    } else {
        fn_801CF810(pOut, pA, pB, t);
    }
}

void *fn_801BC780(Object_801BC084 *pFile, int group)
{
    if ((pFile->mFlags & 1) && !(pFile->mFlags & 0x200)) {
        if (pFile->mFlags & 4)
            return pFile->mpGroupMotion[group].mpCompress;
        return pFile->mpCompress;
    }
    return 0;
}

FrameList_801BC7C0 *fn_801BC7C0(Object_801BA03C *pList, Record_800D81C8 *pChannels, void *pObject)
{
    unsigned short count = 0;
    int i;
    int k;
    Block_801BD6D4 *pSeq;
    Object_801BE594 *pInfo;
    Object_801BC084 *pFile;
    float weight;
    float total;
    int group;

    lbl_8037E858.mMax = 24;
    for (i = 0; i < pList->mCount && count < lbl_8037E858.mMax; i++) {
        if (pChannels[i].mStatus != 0 && pChannels[i].mUnknown48 == 0.0f) {
            pSeq = &pChannels[i].mUnknown4C;
            pInfo = fn_801BE594(pObject, pChannels[i].mUnknown8);
            weight = pInfo->mUnknown4C * pChannels[i].mUnknown30.mWeight;
            lbl_8037E858.mFrames[count].mWeight = weight;
            if ((lbl_8037E858.mFrames[count].mBlend = weight * pChannels[i].mUnknown4C.mUnknown14) != 0.0f) {
                pFile = fn_801BC084(pChannels[i].mUnknown6);
                if (pFile) {
                    group = pChannels[i].mUnknownA;
                    if (group == 0xFFFF)
                        group = fn_801BC65C(pChannels[i].mUnknown8, pFile, pInfo);
                    lbl_8037E858.mFrames[count].mpMotion =
                        fn_801BACD0(pFile, pChannels[i].mFlags, pChannels[i].mUnknown6, pSeq->mUnknown12,
                                    (unsigned short)group);
                    lbl_8037E858.mFrames[count].mpCompress = fn_801BC780(pFile, group);
                    lbl_8037E858.mFrames[count].mSlot = pChannels[i].mUnknown6;
                    lbl_8037E858.mFrames[count].mFrame = pSeq->mUnknown12;
                    lbl_8037E858.mFrames[count].mChannel = i;
                    lbl_8037E858.mFrames[count].mFlags = pChannels[i].mFlags;
                    count++;
                }
            }
            if (count < lbl_8037E858.mMax) {
                lbl_8037E858.mFrames[count].mWeight = weight;
                if ((lbl_8037E858.mFrames[count].mBlend = weight * (1.0f - pSeq->mUnknown14)) != 0.0f) {
                    pFile = fn_801BC084(pChannels[i].mUnknown6);
                    if (pFile) {
                        group = pChannels[i].mUnknownA;
                        if (group == 0xFFFF)
                            group = fn_801BC65C(pChannels[i].mUnknown8, pFile, pInfo);
                        lbl_8037E858.mFrames[count].mpMotion =
                            fn_801BACD0(pFile, pChannels[i].mFlags, pChannels[i].mUnknown6, pSeq->mUnknown10,
                                        (unsigned short)group);
                        lbl_8037E858.mFrames[count].mpCompress = fn_801BC780(pFile, group);
                        lbl_8037E858.mFrames[count].mSlot = pChannels[i].mUnknown6;
                        lbl_8037E858.mFrames[count].mFrame = pSeq->mUnknown10;
                        lbl_8037E858.mFrames[count].mChannel = i;
                        lbl_8037E858.mFrames[count].mFlags = pChannels[i].mFlags;
                        count++;
                    }
                }
            }
        }
    }
    total = lbl_8037E858.mFrames[0].mBlend;
    lbl_8037E858.mCount = count;
    lbl_8037E858.mFrames[0].mBlend = 1.0f;
    for (k = 1; k < count; k++) {
        total += lbl_8037E858.mFrames[k].mBlend;
        if (total != 0.0f)
            lbl_8037E858.mFrames[k].mBlend = lbl_8037E858.mFrames[k].mBlend / total;
        else
            lbl_8037E858.mFrames[k].mBlend = 0.0f;
    }
    return &lbl_8037E858;
}
