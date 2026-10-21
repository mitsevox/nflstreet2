#include "engine/cu_801BA03C.ba03c-1.h"

int fn_801B9F00(Object_801BA03C *pList, Record_800D81C8 *pChannels);
void fn_801BF46C(Block_801BF3C8 *pWeight, float time);

void fn_801BA03C(Object_801BA03C *pList, Record_800D81C8 *pChannels, float time, void *pUser)
{
    int i;
    int active;

    for (i = 0; i < pList->mCount; i++) {
        if (pChannels[i].mStatus == 1)
            pChannels[i].mStatus = 0;
        if (pChannels[i].mStatus != 0) {
            pChannels[i].mUnknown48 -= time;
            if (!(pChannels[i].mUnknown48 >= 0.0f)) {
                pChannels[i].mUnknown48 = 0.0f;
                active = pChannels[i].mUnknown30.mUnknown8;
                fn_801BF46C(&pChannels[i].mUnknown30, time);
                if (!(pChannels[i].mUnknown30.mWeight >= 1e-7f) && active != 0)
                    pChannels[i].mStatus = 1;
                if (pChannels[i].mStatus != 0 && fn_801BA650(&pChannels[i], time, pUser) == 1)
                    pChannels[i].mStatus = 1;
            }
        }
    }
}
