#include "game/State_800D7A4C.h"
#include "game/Block_801BE60C.h"
#include "game/Object_80039F5C.h"
#include "game/Object_800D81C8.h"
#include "game/Object_801BC084.h"
#include "game/cu_80136B1C.h"
#include "game/bitstream.h"
#include "game/fn_801BE60C.h"
#include "game/fn_801BA2A8.h"
#include "game/Table_80089904.h"


extern "C" {
unsigned char fn_800D78C4(Object_80039F5C *p, unsigned short id);
void fn_800D7A4C(Object_80039F5C *p, Block_801BE60C *pBlock);
void fn_800E7E78(Object_80039F5C *p, State_800D7A4C *pState);
int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);
int fn_800CA5CC(Object_80039F5C *p, int kind, int apply);
float fn_800CA9B4(int kind, Object_80039F5C *p);
void fn_800D8140(State_800D8140 *p, Object_800D81C8 *pOther, int entry);
void fn_800D81C8(State_800D8140 *p, Object_800D81C8 *pOther);
void fn_800AE7F0(int index, int team, Object_80039F5C *p);
int fn_80178320(void);

extern unsigned short lbl_803192BC[2][7];
extern unsigned short lbl_803192D8[2][7];
extern signed char lbl_802DA87C[];
extern float lbl_803EAD00;
extern float lbl_803EAD04;
extern float lbl_803EAD08;
extern float lbl_803EAD0C;
extern float lbl_803EAD10;
}

extern "C" void fn_800D760C(BitStream_t *pStream)
{
    unsigned short anim = 0;

    for (unsigned char team = 0; team <= 1; team++) {
        for (unsigned char i = 0; i <= 6; i++) {
            Object_80039F5C *pPlayer = fn_80039F5C(team, i);
            unsigned int id = fn_801BE648(pPlayer->mpUnknown792);
            for (unsigned char k = 0; k < pPlayer->mpUnknown796->mUnknown4; k++) {
                if (pPlayer->mpUnknown800[k].mUnknown8 == id) {
                    Object_801BC084 *pInfo = fn_801BC084(pPlayer->mpUnknown800[k].mUnknown6);
                    anim = pPlayer->mpUnknown800[k].mUnknown2 + pInfo->mUnknown3 * 1000;
                    break;
                }
            }
            fn_80191068(pStream, id, 16);
            fn_80191068(pStream, anim, 16);
        }
    }
}

extern "C" void fn_800D7708(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2,
                            BitStream_t *pStream3, float t)
{
    for (unsigned char team = 0; team <= 1; team++) {
        for (unsigned char i = 0; i <= 6; i++) {
            unsigned short id = ReadBitStream(pStream1, 16);
            unsigned short anim = ReadBitStream(pStream1, 16);
            lbl_803192BC[team][i] = id;
            lbl_803192D8[team][i] = anim;
            if (pStream2) {
                ReadBitStream(pStream2, 32);
            }
            if (pStream3) {
                ReadBitStream(pStream3, 32);
            }
            if (pStream0) {
                ReadBitStream(pStream0, 32);
            }
        }
    }
}

extern "C" void fn_800D782C(Object_80039F5C *p)
{
    Object_80137ABC *pBall = fn_80137C48(p);
    unsigned short id = fn_801BE648(p->mpUnknown792);

    if (pBall) {
        if (p->mUnknown776) {
            if (id != p->mUnknown778Unsigned) {
                unsigned char value = fn_800D78C4(p, id);
                p->mUnknown777 = value;
                p->mUnknown776 = value;
            }
        } else {
            unsigned char value = fn_800D78C4(p, id);
            p->mUnknown776 = value;
            p->mUnknown777 = value;
        }
    } else {
        p->mUnknown776 = 0;
        p->mUnknown777 = 0;
    }
    p->mUnknown778Unsigned = id;
}

extern "C" void fn_800D7A0C(Object_80039F5C *p, int value)
{
    p->mUnknown776 = value;
    p->mUnknown777 = value;
}

extern "C" void fn_800D7A18(Object_80039F5C *p)
{
    p->mUnknown778Unsigned = fn_801BE648(p->mpUnknown792);
}

extern "C" void fn_800D7BC4(Object_80039F5C *p, Block_801BE60C *pBlock)
{
    State_800D7A4C *pState = (State_800D7A4C *)&p->mUnknown336;

    if (pState->mUnknown5 == 3 && fn_80137B40() && pState->mUnknown11) {
        float count = pBlock->mUnknownCHalf;
        unsigned char saved = p->mUnknown512.mUnknown14;
        p->mUnknown512.mUnknown14 = 6;
        fn_800E7E78(p, pState);
        fn_800D7A4C(p, pBlock);
        int n = (int)count;
        int value = pBlock->mUnknown0Word * pBlock->mUnknownCHalf / n;
        pBlock->mUnknownCHalf = n;
        pBlock->mUnknown0Word = value;
        if (value < 0) {
            if (pBlock->mUnknownCHalf <= 5) {
                int limit = (int)(-lbl_803EAD00 * 46603.38f);
                pBlock->mUnknown0Word = value < limit ? limit : value;
            } else {
                int limit = (int)(-lbl_803EAD04 * 46603.38f);
                pBlock->mUnknown0Word = value < limit ? limit : value;
            }
        } else {
            if (pBlock->mUnknownCHalf <= 5) {
                int limit = (int)(lbl_803EAD00 * 46603.38f);
                pBlock->mUnknown0Word = value < limit ? limit : value;
            } else {
                int limit = (int)(lbl_803EAD04 * 46603.38f);
                pBlock->mUnknown0Word = value > limit ? limit : value;
            }
        }
        p->mUnknown512.mUnknown14 = saved;
    }
}

extern "C" void fn_800D7D78(Object_80039F5C *p, Block_801BE60C *pBlock)
{
    if (p->mUnknown560.mFlags.mBytes[0] != 0) {
        unsigned char k = p->mUnknown560.mUnknown54;
        if (k <= 10 && pBlock->mUnknown8 > 0.0f) {
            signed char *pLevels = pBlock->mUnknownE;
            if (pLevels[k] < lbl_802DA87C[k]) {
                float step = lbl_802DA87C[k] * 0.2f;
                signed char level = (int)(pLevels[k] + step);
                pLevels[k] = level > lbl_802DA87C[k] ? lbl_802DA87C[k] : level;
                pBlock->mUnknown8 -= step * 0.01f;
                float rest = pBlock->mUnknown8;
                if (!(rest >= 0.0f)) {
                    rest = 0.0f;
                }
                pBlock->mUnknown8 = rest;
                p->mpUnknown800[pBlock->mUnknown4Word].mUnknown2C = rest;
            }
        }
    }
}

extern "C" int fn_800D7E9C(Table_80089904 *pTable, unsigned short key, void *pRecord, Record_800D81C8 *pEntries,
                           Object_80039F5C *p, unsigned int phase)
{
    Block_801BE60C *pBlock = fn_801BE60C(p->mpUnknown792, key);
    State_800D7A4C *pState = (State_800D7A4C *)&p->mUnknown336;

    switch (phase) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        int index = fn_8009C4B0(pTable, &p->mUnknown1008);
        float scale;
        pBlock->mUnknown4Word = fn_801BA2A8(pRecord, pEntries, pTable->mEntries[index].mUnknown0,
                                       pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        pBlock->mUnknown24Float = 0.0f;
        if (pState->mUnknown5 == 3) {
            Info_80089904 *pInfo = pTable->mEntries[index].mpInfo;
            pBlock->mUnknown1CWord = pInfo->mUnknown12;
            pBlock->mUnknown24Float = pInfo->mUnknown24;
            pBlock->mUnknown20Float = pInfo->mUnknown24;
            if (pState->mUnknown9 == 1) {
                scale = lbl_803EAD0C;
            } else {
                scale = lbl_803EAD10;
            }
        } else {
            scale = lbl_803EAD08;
        }
        if (fn_800CA5CC(p, 3, 1)) {
            scale *= fn_800CA9B4(pState->mUnknown5 == 3 ? 11 : 10, p);
        }
        pBlock->mUnknown8 = scale;
        for (int i = 0; i != 11; i++) {
            pBlock->mUnknownE[i] = 0;
        }
        p->mpUnknown800[pBlock->mUnknown4Word].mUnknown2C = scale;
        fn_800D8140(&pBlock->mUnknown28, (Object_800D81C8 *)p, pBlock->mUnknown4Word);
        fn_800D7A4C(p, pBlock);
        if (pState->mUnknown5 == 3) {
            fn_800AE7F0(6, fn_80178320(), p);
            if (pState->mUnknown5 == 3 && pBlock->mUnknownCHalf != 0) {
                pBlock->mUnknownCHalf += 6;
            }
        }
        pBlock->mUnknown19 = 0;
        break;
    }
    case 1:
        break;
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            fn_800D7D78(p, pBlock);
            if (pBlock->mUnknown0Word != 0) {
                if (--pBlock->mUnknownCHalf > 0) {
                    fn_800D7BC4(p, pBlock);
                    p->mMotion.mFacing = (p->mMotion.mFacing + pBlock->mUnknown0Word) & 0xFFFFFF;
                    p->mpUnknown800[pBlock->mUnknown4Word].mUnknownC =
                        (p->mpUnknown800[pBlock->mUnknown4Word].mUnknownC + pBlock->mUnknown0Word) & 0xFFFFFF;
                } else {
                    pBlock->mUnknown0Word = 0;
                    pBlock->mUnknownCHalf = 0;
                }
            }
            fn_800D81C8(&pBlock->mUnknown28, (Object_800D81C8 *)p);
            if (p->mFlags & 1) {
                p->mFlags &= ~1;
            }
        }
        break;
    }
    return 0;
}
