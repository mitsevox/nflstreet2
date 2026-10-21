#include "engine/cu_801BDA30.h"

void fn_801BE910(Collection_801BE594 *p, unsigned short key, int frames);
Transition_801BEFA4 *fn_801BEFA4(List_801BAC1C *pTable, Object_801BA03C *pObject, Record_800D81C8 *pRecords,
                                 unsigned short fromType, unsigned short fromFrame, unsigned short fromKey,
                                 unsigned short toType, unsigned short toKey, unsigned short toFrame);

int fn_801BE82C(unsigned short type, unsigned short key)
{
    fn_801BBDCC(type, key, &lbl_803D4F50);
    return lbl_803D4F50.mCount;
}

unsigned int fn_801BE860(Collection_801BE594 *p, Object_801BA03C *pObject, Record_800D81C8 *pRecords, unsigned short key)
{
    float highest = 0.0f;
    unsigned int best = 0xFFFF;
    unsigned int count = fn_801BA568(pObject, pRecords, key);
    unsigned short i;

    for (i = 0; i < count; i++) {
        unsigned int index = fn_801BA5A8(pObject, pRecords, key, i);

        if (!(highest >= pRecords[index].mUnknown30.mUnknown0)) {
            highest = pRecords[index].mUnknown30.mUnknown0;
            best = index;
        }
    }
    return best;
}

void fn_801BE910(Collection_801BE594 *p, unsigned short key, int frames)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown0 == key
            || ((p->mUnknown4[i].mUnknown0 & 0x8000) && p->mUnknown4[i].mUnknown0 != 0xFFFF)) {
            fn_801BF4A8(&p->mUnknown4[i].mUnknown4C, frames, -1.0f, 0.0f);
        }
    }
}

void fn_801BE99C(Collection_801BE594 *p, Object_801BA03C *pObject, Record_800D81C8 *pRecords, unsigned short key,
                 unsigned short previous, int state, void *pOwner)
{
    List_801BAC1C *pTable = &lbl_803D4F50;
    int fallback = 1;
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown0 == 0xFFFF) {
            p->mUnknown4[i].mUnknown6 = fn_801BBF44(pObject->mUnknown2);
            continue;
        }
        if (p->mUnknown4[i].mUnknown2 != state) {
            continue;
        }
        p->mUnknown4[i].mUnknown2 = 1;
        if (pTable->mState != previous) {
            fn_801BE82C(pObject->mUnknown2, previous);
        }
        if (pTable->mCount != 0) {
            unsigned short slotKey = p->mUnknown4[i].mUnknown0;
            unsigned int from = fn_801BE860(p, pObject, pRecords, slotKey);
            unsigned int to = fn_801BE860(p, pObject, pRecords, key);

            if (from != 0xFFFF && to != 0xFFFF) {
                Transition_801BEFA4 *pTransition;

                pTransition = fn_801BEFA4(pTable, pObject, pRecords, pRecords[from].mUnknown2, pRecords[from].mUnknown4,
                                          pRecords[from].mUnknown4C.mUnknown18, key, pRecords[to].mUnknown2,
                                          pRecords[to].mUnknown4);
                if (pTransition == 0) {
                    pTransition = fn_801BEFA4(pTable, pObject, pRecords, pRecords[from].mUnknown2,
                                              pRecords[from].mUnknown4, pRecords[from].mUnknown4C.mUnknown18, key,
                                              0xFFFF, 0);
                }
                if (pTransition == 0) {
                    pTransition = fn_801BEFA4(pTable, pObject, pRecords, 0xFFFF, 0, 0, key, pRecords[to].mUnknown2,
                                              pRecords[to].mUnknown4);
                }
                if (pTransition == 0) {
                    pTransition = fn_801BEFA4(pTable, pObject, pRecords, 0xFFFF, 0, 0, key, 0xFFFF, 0);
                }
                if (pTransition != 0) {
                    switch (pTransition->mUnknown4) {
                    case 0:
                        fn_801BF3C8(&p->mUnknown4[i].mUnknown4C, 0, 0.0f, 0, 0.0f);
                        fallback = 0;
                        break;
                    case 1: {
                        float frames = pTransition->mUnknown6 * pRecords[from].mUnknown4C.mUnknown4 *
                                           (1.0f - pTransition->mUnknown8) +
                                       pTransition->mUnknown6 * pRecords[to].mUnknown4C.mUnknown4 * pTransition->mUnknown8;

                        fn_801BE910(p, slotKey, (unsigned int)frames);
                        fn_801BF4A8(&p->mUnknown4[i + 2].mUnknown4C, (unsigned int)frames, 0.0f,
                                    p->mUnknown4[i + 2].mUnknown4C.mUnknown4);
                        fallback = 0;
                        break;
                    }
                    case 2:
                        fn_801BF3C8(&p->mUnknown4[i].mUnknown4C, 0, 0.0f, 0, 0.0f);
                        fallback = 0;
                        break;
                    case 3: {
                        int file;
                        int index;

                        p->mUnknown4[i].mUnknown6 = fn_801BBF44(pObject->mUnknown2);
                        file = fn_801BBE5C(pObject->mUnknown2, pTransition->mUnknownC);
                        if (file != 0xFFFFFF &&
                            (index = fn_801BA154(pObject, pRecords, (unsigned short)file, pTransition->mUnknownE, 1.0f,
                                                 0xFFFF, pOwner, p->mUnknown4[i].mUnknown6)) != -1) {
                            float duration = fn_801BD60C(pRecords[index].mUnknown4C.mpUnknown0);
                            unsigned int fade = duration * (1.0f - pTransition->mUnknown8) * 0.5f;
                            unsigned int hold = (unsigned int)duration - fade * 2;
                            float delay;

                            fn_801BF4A8(&p->mUnknown4[i].mUnknown4C, fade, -1.0f, 0.0f);
                            fn_801BF530(&p->mUnknown4[i + 1].mUnknown4C, fade, hold, -1.0f, 1.0f);
                            fn_801BF4A8(&p->mUnknown4[i + 2].mUnknown4C, fade, 0.0f,
                                        p->mUnknown4[i + 2].mUnknown4C.mUnknown4);
                            delay = (float)hold + (float)fade;
                            fn_801BE798(p, key, delay);
                            fn_801BA60C(pObject, pRecords, key, delay);
                            fallback = 0;
                        } else {
                            fallback = 1;
                        }
                        break;
                    }
                    }
                }
            }
        }
        if (fallback == 1) {
            fn_801BF4A8(&p->mUnknown4[i].mUnknown4C, 10, -1.0f, 0.0f);
        }
    }
}

Transition_801BEFA4 *fn_801BEFA4(List_801BAC1C *pTable, Object_801BA03C *pObject, Record_800D81C8 *pRecords,
                                 unsigned short fromType, unsigned short fromFrame, unsigned short fromKey,
                                 unsigned short toType, unsigned short toKey, unsigned short toFrame)
{
    Transition_801BEFA4 *pResult = 0;
    unsigned short key;
    int i;

    if (toKey != 0xFFFF) {
        key = toFrame | 0x8000;
    } else {
        key = 0xFFFF;
        toKey = toType;
    }
    for (i = 0; i < pTable->mCount; i++) {
        StateTrans_801BAC1C *pGroup = pTable->mEntries[i].mpUnknown4;
        int j;

        for (j = 0; j < pGroup->mCount; j++) {
            if ((pGroup->mEntries[j].mUnknown0 == key || (key == 0xFFFF && !(pGroup->mEntries[j].mUnknown0 & 0x8000))) &&
                pGroup->mEntries[j].mUnknown2 == toKey && pGroup->mEntries[j].mUnknown4 == fromType &&
                (fromType == 0xFFFF ||
                 (fromKey >= pGroup->mEntries[j].mUnknown6 && fromKey <= pGroup->mEntries[j].mUnknown8))) {
                pResult = pGroup->mEntries[j].mpUnknownC;
            }
        }
    }
    return pResult;
}
