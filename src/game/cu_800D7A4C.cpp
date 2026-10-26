#include "game/State_800D7A4C.h"
#include "game/Block_801BE60C.h"
#include "game/Object_80039F5C.h"

extern "C" {
int fn_801CFFD0(int a, int b);
float fn_801BD660(void *p, int key);
}

extern "C" void fn_800D7A4C(Object_80039F5C *p, Block_801BE60C *pBlock)
{
    pBlock->mUnknownCHalf = pBlock->mUnknown0Word = 0;
    Object_8016D8B0 *pMove = &p->mUnknown512;
    State_800D7A4C *pState = (State_800D7A4C *)&p->mUnknown336;
    if (pMove->mUnknown14 == 6 && pState->mUnknown11) {
        int facing = p->mMotion.mFacing;
        if (pBlock->mUnknown24Float > 0.0f) {
            facing += (int)(pBlock->mUnknown1CWord * (pBlock->mUnknown24Float / pBlock->mUnknown20Float));
        }
        int turn = fn_801CFFD0(facing, pMove->mUnknown8);
        if (((pMove->mUnknown8 - facing) & 0xFFFFFF) > 0x800000) {
            turn = -turn;
        }
        float frames = fn_801BD660(p->mpUnknown800[pBlock->mUnknown4Word].mUnknown4C.mpUnknown0, 0xC006);
        pBlock->mUnknown24Float -= 1.0f;
        turn = (int)(turn / frames);
        pBlock->mUnknown0Word = turn;
        pBlock->mUnknownCHalf = (int)frames;
    }
}
