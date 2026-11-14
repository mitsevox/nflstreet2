#include "engine/animchan.h"
#include "game/Object_80039F5C.h"
#include "game/Table_80089904.h"
#include "game/AnimChanStartAnim.h"
#include "game/fn_801BE60C.h"

/* Player block at +336 as fn_800E4264 uses it. */
struct State_800E4264 {
    char mUnknown0[56];
    int mUnknown56;
    int mUnknown60;
    float mUnknown64;
};

extern "C" {
int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);
int MathAngleDiff(int a, int b);
float AnimSeqGetTimeToOpcode(void *p, int key);
}

extern "C" int fn_800E4264(Table_80089904 *pTable, unsigned short key, void *pRecord, AnimChannel_t *pEntries,
                           Object_80039F5C *p, unsigned int phase)
{
    State_800E4264 *pState = (State_800E4264 *)&p->mUnknown336;

    switch (phase) {
    case 0: {
        int index = fn_8009C4B0(pTable, &p->mUnknown1008);
        if (index >= 0) {
            p->mFlags &= ~4;
            AnimChanStartAnim(pRecord, pEntries, pTable->mEntries[index].mUnknown0,
                        pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        }
        int heading = pState->mUnknown56;
        if (MathAngleDiff(heading, p->mMotion.mFacing) > 46603) {
            fn_801BE760(p->mpUnknown792, key, 1);
            if (AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 189)) {
                AnimChannel_t *pChannels = p->mpUnknown800;
                int channel = AnimChanGetStateChannelByIndex(p->mpUnknown796, pChannels, 189, 0);
                pState->mUnknown64 = pChannels[channel].mUnknown48;
                if (pState->mUnknown64 == 0.0f) {
                    pState->mUnknown64 = AnimSeqGetTimeToOpcode(&pChannels[channel].mUnknown4C, 0xC004);
                    if (pState->mUnknown64 == 0.0f) {
                        break;
                    }
                }
                pState->mUnknown64 = pState->mUnknown64 > 50.0f ? 50.0f : pState->mUnknown64;
                pState->mUnknown60 = (int)(MathAngleDiff(heading, p->mMotion.mFacing) / pState->mUnknown64);
                if (((p->mMotion.mFacing - heading) & 0xFFFFFF) <= 0x7FFFFF) {
                    pState->mUnknown60 = -pState->mUnknown60;
                }
            }
        }
        break;
    }
    case 1:
        break;
    case 2:
        if (pState->mUnknown64 > 0.0f) {
            pState->mUnknown64 -= 1.0f;
            p->mMotion.mFacing += pState->mUnknown60;
            p->mpUnknown796->mUnknown8 += pState->mUnknown60;
        }
        break;
    }
    return 0;
}
