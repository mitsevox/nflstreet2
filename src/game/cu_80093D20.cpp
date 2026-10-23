#include "game/cu_8008E978.h"
#include "game/Frame_800DF7CC.h"
#include "game/Table_80089904.h"
#include "engine/Record_800D81C8.h"

extern "C" {
int fn_801BBE5C(int objectType, int fileNum);
int fn_801BA2A8(Object_801BA03C *pList, Record_800D81C8 *pChannels, unsigned short slot, int anim, int state,
                void *pUser, float weight);
void fn_801BA6BC(Record_800D81C8 *pChannel, int enable);
}

/* Per-state scratch at player +336 while handler 10 runs: +11 keeps the
   channel fn_801BA2A8 returned. */
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
        Frame_800DF7CC *pFrame = fn_801C029C(fn_80093BAC(pC->mUnknown1008.mUnknown0, pC->mUnknown1008.mUnknown1), index);
        Record_800D81C8 *pChannels = (Record_800D81C8 *)pB;

        pState->mChannel = fn_801BA2A8((Object_801BA03C *)pA, pChannels,
                                       fn_801BBE5C(pC->mpUnknown796->mUnknown2 | 0x4000, pFrame->mUnknown14), anim,
                                       key, pC, 1.0f);
        if (pFrame->mUnknown19 != 0) {
            pChannels[pState->mChannel].mUnknown7 |= 0x20;
        } else {
            pChannels[pState->mChannel].mUnknown7 |= 0x10;
        }
        if (pFrame->mUnknown16[2] != 0) {
            fn_801BA6BC(&pChannels[pState->mChannel], 1);
        } else {
            fn_801BA6BC(&pChannels[pState->mChannel], 0);
        }
    }
    return 0;
}
