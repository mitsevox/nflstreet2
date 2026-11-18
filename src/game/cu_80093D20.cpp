#include "game/cu_8008E978.h"
#include "game/Frame_800DF7CC.h"
#include "game/Table_80089904.h"
#include "engine/AnimChannel.h"

extern "C" {
int AnimFileGetSlotFromFileNum(int objectType, int fileNum);
int AnimChanStartAnim(AnimHeader_t *pList, AnimChannel_t *pChannels, unsigned short slot, int anim, int state,
                void *pUser, float weight);
void AnimChanSetMirrored(AnimChannel_t *pChannel, int enable);
}

/* Per-state scratch at player +336 while handler 10 runs: +11 keeps the
   channel AnimChanStartAnim returned. */
struct State_80093D20 {
    unsigned char mUnknown0[11];
    unsigned char mChannel;
};

/* Handler 10 of the table fn_800B4D7C fills: on mode 0 starts the clip the
   player's frame names and flags its channel. */
extern "C" int fn_80093D20(Table_80089904 *pTable, unsigned short key, void *pA, void *pB, Object_80039F5C *pC,
                           unsigned int mode)
{
    if (mode == 0) {
        State_80093D20 *pState = (State_80093D20 *)&pC->mUnknown336Block;
        unsigned char index = pC->mUnknown1008.mUnknown2;
        unsigned char anim = pC->mUnknown1011;
        Frame_800DF7CC *pFrame = AnimSeqncrGetPlayerPtr(fn_80093BAC(pC->mUnknown1008.mUnknown0, pC->mUnknown1008.mUnknown1), index);
        AnimChannel_t *pChannels = (AnimChannel_t *)pB;

        pState->mChannel = AnimChanStartAnim((AnimHeader_t *)pA, pChannels,
                                       AnimFileGetSlotFromFileNum(pC->mpUnknown796->mUnknown2 | 0x4000, pFrame->mUnknown14), anim,
                                       key, pC, 1.0f);
        if (pFrame->mUnknown19 != 0) {
            pChannels[pState->mChannel].mUnknown7 |= 0x20;
        } else {
            pChannels[pState->mChannel].mUnknown7 |= 0x10;
        }
        if (pFrame->mUnknown16[2] != 0) {
            AnimChanSetMirrored(&pChannels[pState->mChannel], 1);
        } else {
            AnimChanSetMirrored(&pChannels[pState->mChannel], 0);
        }
    }
    return 0;
}
