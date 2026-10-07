#include "game/Object_80039F5C.h"
#include "game/Object_800D81C8.h"
#include "game/bitstream.h"

/* View of the player object's state block at +336 used by these functions. */
struct State_800D7A4C {
    char mUnknown0[5];
    unsigned char mUnknown5;
    char mUnknown6[5];
    unsigned char mUnknown11;
};

struct Block_800D7A4C {
    int mUnknown0;
    int mUnknown4;
    float mUnknown8;
    short mUnknown12;
    signed char mUnknown14[11];
    char mUnknown25[3];
    int mUnknown28;
    float mUnknown32;
    float mUnknown36;
};

struct Object_801BC084 {
    char mUnknown0[3];
    unsigned char mUnknown3;
};

extern "C" {
unsigned char fn_800D78C4(Object_80039F5C *p, int id);
void fn_800D7A4C(Object_80039F5C *p, Block_800D7A4C *pBlock);
void fn_800E7E78(Object_80039F5C *p, State_800D7A4C *pState);
Object_80039F5C *fn_80137B40(void);
int fn_80137C48(Object_80039F5C *p);
Object_801BC084 *fn_801BC084(int handle);
int fn_801BE648(void *p);

extern unsigned short lbl_803192BC[2][7];
extern unsigned short lbl_803192D8[2][7];
extern signed char lbl_802DA87C[];
extern float lbl_803EAD00;
extern float lbl_803EAD04;
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
                            BitStream_t *pStream3)
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
    int active = fn_80137C48(p);
    int id = fn_801BE648(p->mpUnknown792);

    if (active) {
        if (p->mUnknown776) {
            if (id != p->mUnknown778) {
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
        p->mUnknown776 = active;
        p->mUnknown777 = active;
    }
    p->mUnknown778 = id;
}

extern "C" void fn_800D7A0C(Object_80039F5C *p, int value)
{
    p->mUnknown776 = value;
    p->mUnknown777 = value;
}

extern "C" void fn_800D7A18(Object_80039F5C *p)
{
    p->mUnknown778 = fn_801BE648(p->mpUnknown792);
}

extern "C" void fn_800D7BC4(Object_80039F5C *p, Block_800D7A4C *pBlock)
{
    State_800D7A4C *pState = (State_800D7A4C *)&p->mUnknown336;

    if (pState->mUnknown5 == 3 && fn_80137B40() && pState->mUnknown11) {
        float count = pBlock->mUnknown12;
        unsigned char saved = p->mUnknown512.mUnknown14;
        p->mUnknown512.mUnknown14 = 6;
        fn_800E7E78(p, pState);
        fn_800D7A4C(p, pBlock);
        int n = (int)count;
        int value = pBlock->mUnknown0 * pBlock->mUnknown12 / n;
        pBlock->mUnknown12 = n;
        pBlock->mUnknown0 = value;
        if (value < 0) {
            if (pBlock->mUnknown12 <= 5) {
                int limit = (int)(-lbl_803EAD00 * 46603.38f);
                pBlock->mUnknown0 = value < limit ? limit : value;
            } else {
                int limit = (int)(-lbl_803EAD04 * 46603.38f);
                pBlock->mUnknown0 = value < limit ? limit : value;
            }
        } else {
            if (pBlock->mUnknown12 <= 5) {
                int limit = (int)(lbl_803EAD00 * 46603.38f);
                pBlock->mUnknown0 = value < limit ? limit : value;
            } else {
                int limit = (int)(lbl_803EAD04 * 46603.38f);
                pBlock->mUnknown0 = value > limit ? limit : value;
            }
        }
        p->mUnknown512.mUnknown14 = saved;
    }
}

extern "C" void fn_800D7D78(Object_80039F5C *p, Block_800D7A4C *pBlock)
{
    if (p->mUnknown560.mFlags.mBytes[0] != 0) {
        unsigned char k = p->mUnknown560.mUnknown54;
        if (k <= 10 && pBlock->mUnknown8 > 0.0f) {
            signed char *pLevels = pBlock->mUnknown14;
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
                p->mpUnknown800[pBlock->mUnknown4].mUnknown2C = rest;
            }
        }
    }
}
