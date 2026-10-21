#include "engine/cu_801B9F00.h"

int fn_801B9F00(Object_801BA03C *pList, Record_800D81C8 *pChannels)
{
    unsigned short count = pList->mUnknown4;
    unsigned char pass;
    int i;
    float best;
    int selected;

    for (pass = 0; pass <= 1; pass++) {
        for (i = 0; i < count; i++) {
            if (pChannels[i].mUnknown1 == pass)
                return i;
        }
    }
    best = 1.0f;
    selected = -1;
    for (i = 0; i < count; i++) {
        if ((pChannels[i].mUnknown8 & 0x8000) && !(pChannels[i].mUnknown30.mUnknown0 > best)) {
            best = pChannels[i].mUnknown30.mUnknown0;
            selected = i;
        }
    }
    if (selected == -1)
        return -1;
    fn_801BA384(pList, pChannels, selected);
    return selected;
}

void fn_801B9FEC(Object_801BA03C *pList, Record_800D81C8 *pChannels)
{
    unsigned char state = 4;
    int i;

    if (pList->mUnknown0 == 0)
        state = 1;
    for (i = 0; i < pList->mUnknown4; i++) {
        pChannels[i].mUnknown0 = state;
        pChannels[i].mUnknown1 = 0;
        pChannels[i].mUnknown4C.mpUnknown0 = 0;
    }
}

void fn_801BA03C(Object_801BA03C *pList, Record_800D81C8 *pChannels, float time, void *pUser)
{
    int i;
    int active;

    for (i = 0; i < pList->mUnknown4; i++) {
        if (pChannels[i].mUnknown1 == 1)
            pChannels[i].mUnknown1 = 0;
        if (pChannels[i].mUnknown1 != 0) {
            pChannels[i].mUnknown48 -= time;
            if (!(pChannels[i].mUnknown48 >= 0.0f)) {
                pChannels[i].mUnknown48 = 0.0f;
                active = pChannels[i].mUnknown30.mUnknown8;
                fn_801BF46C(&pChannels[i].mUnknown30, time);
                if (!(pChannels[i].mUnknown30.mUnknown0 >= 1e-7f) && active != 0)
                    pChannels[i].mUnknown1 = 1;
                if (pChannels[i].mUnknown1 != 0 && fn_801BA650(&pChannels[i], time, pUser) == 1)
                    pChannels[i].mUnknown1 = 1;
            }
        }
    }
}
