#include "engine/cu_801B9F00.h"
#include "game/Object_80039F5C.h"
#include "game/Table_80089904.h"
#include "game/fn_801BA2A8.h"
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
int fn_801CFFD0(int a, int b);
float fn_801BD690(void *p, int key);
}

extern "C" int fn_800E4264(Table_80089904 *pTable, unsigned short key, void *pRecord, Record_800D81C8 *pEntries,
                           Object_80039F5C *p, unsigned int phase)
{
    State_800E4264 *pState = (State_800E4264 *)&p->mUnknown336;

    switch (phase) {
    case 0: {
        int index = fn_8009C4B0(pTable, &p->mUnknown1008);
        if (index >= 0) {
            p->mFlags &= ~4;
            fn_801BA2A8(pRecord, pEntries, pTable->mEntries[index].mUnknown0,
                        pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        }
        int heading = pState->mUnknown56;
        if (fn_801CFFD0(heading, p->mMotion.mFacing) > 46603) {
            fn_801BE760(p->mpUnknown792, key, 1);
            if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 189)) {
                Record_800D81C8 *pChannels = p->mpUnknown800;
                int channel = fn_801BA5A8(p->mpUnknown796, pChannels, 189, 0);
                pState->mUnknown64 = pChannels[channel].mUnknown48;
                if (pState->mUnknown64 == 0.0f) {
                    pState->mUnknown64 = fn_801BD690(&pChannels[channel].mUnknown4C, 0xC004);
                    if (pState->mUnknown64 == 0.0f) {
                        break;
                    }
                }
                pState->mUnknown64 = pState->mUnknown64 > 50.0f ? 50.0f : pState->mUnknown64;
                pState->mUnknown60 = (int)(fn_801CFFD0(heading, p->mMotion.mFacing) / pState->mUnknown64);
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
