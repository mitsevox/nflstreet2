#include "game/Block_8030E6E8.h"
#include "game/fn_801FCE10.h"

/* 24-byte entries at +44 of Block_8009C6F4. */
struct Entry_8009C684 {
    void (*mpCallback0)(Object_80039F5C *p, Vector_80039F5C *pVec, void *pData);
    Vector_80039F5C mUnknown4;
    unsigned char mUnknown10[8];
};

/* Record passed to fn_8009C6F4, fn_8009C814 and fn_8009C88C. Only the
   accessed fields are declared; the size is unknown. */
struct Block_8009C6F4 {
    int mUnknown0;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    int mUnknown8;
    short mUnknownC;
    short mUnknownE;
    Vector_80039F5C mUnknown10;
    int mUnknown1C[3];
    Pose_80041930 *mpPose;
    Entry_8009C684 mEntries[2];
};

struct Entry_8009D964 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
};

/* Allocated through fn_80238174 under the id 'clck' (fn_8009D474). */
struct Block_8009D474 {
    int mUnknown0;
    Entry_8009D964 mEntries[6];
    int mUnknown94;
    int mUnknown98;
};

extern "C" {
void fn_8009CF30(Block_8009C6F4 *pBlock, Pose_80041930 *pPose);
extern Block_8009D474 *lbl_803EA9A8;
}

extern "C" void fn_8009CF30(Block_8009C6F4 *pBlock, Pose_80041930 *pPose)
{
    int *pInts = pBlock->mUnknown1C;
    Vector_80039F5C *pVec = &pBlock->mUnknown10;

    pBlock->mUnknown6 = pBlock->mUnknown4 = 0;
    pBlock->mUnknown0 = 1;
    pBlock->mpPose = pPose;
    pInts[0] = pInts[1] = pInts[2] = 0;
    pVec->mX = pVec->mY = pVec->mZ = 0.0f;
}

extern "C" void fn_8009D818(int state)
{
    int previous = lbl_803EA9A8->mUnknown0;

    lbl_803EA9A8->mUnknown0 = state;
    lbl_803EA9A8->mUnknown98 = previous;
    fn_801FCE10(0, "update 'FNIG' set 'RTQG' = \x85\n", state);
    lbl_803EA9A8->mUnknown94 &= ~1;
}
