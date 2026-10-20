#include "game/Block_8030E6E8.h"
#include "game/fn_801FCE10.h"
#include "game/Item_80097440.h"

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
