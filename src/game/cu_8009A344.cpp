#include "game/Command_800CEE74.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8007F828.h"
#include "game/fn_80178D18.h"
#include "game/Block_801BE60C.h"
#include "game/fn_802372EC.h"
#include "game/fn_801BA2A8.h"
#include "game/fn_80238174.h"
#include "game/fn_801248D4.h"
#include "game/Item_80097440.h"

extern "C" {
void *fn_8023816C(void *pHandle);
unsigned short fn_801BE648(void *p);
int fn_800BA6F8(void);
void fn_8009A8F0(void);
extern Block_8009AB34 *lbl_803EA948;
extern float lbl_802D7BA8[];
extern float lbl_802D7BD0[];
extern Block_80099630 *lbl_803EC92C;
float fn_80178A68(Point_8017886C *pPos);
int fn_801787DC(int team);
int fn_800D41F8(int team);
float fn_80260E24(float a);
float fn_80260FE8(float a);
Block_801BE60C *fn_801BE60C(void *p, unsigned short key);
void fn_801BE760(void *p, unsigned short key, unsigned short flags);
void fn_800D8140(State_800D8140 *pState, Object_80039F5C *p, int value);
void fn_800D81C8(State_800D8140 *pState, Object_80039F5C *p);
void fn_8022765C(void *pOut, void *pA, void *pB);
int fn_800ACF40(Object_80039F5C *p, signed char value);
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, unsigned char a, unsigned char count, float *pOut, int b);
int fn_80177F70(void);
int fn_80178308(void);
int fn_800B65A0(int team);
}

extern "C" int fn_8009A344(Table_80089904 *pTable, unsigned short key, void *pRecord, Record_800D81C8 *pEntries,
                           Object_80039F5C *p, unsigned int phase)
{
    Block_8009A344 *pBlock = (Block_8009A344 *)fn_801BE60C(p->mpUnknown792, key);
    unsigned short animation;
    unsigned short value;

    switch (phase) {
    case 0:
    case 1:
        *pBlock = lbl_803EC92C->mUnknown4;
        animation = p->mUnknown1008.mUnknown0 | p->mUnknown1008.mUnknown1 << 8;
        value = p->mUnknown1008.mUnknown2 | p->mUnknown1011 << 8;
        pBlock->mUnknown20 = fn_801BA2A8(pRecord, pEntries, value, animation, key, p, 1.0f);
        fn_801BE760(p->mpUnknown792, key, 1);
        fn_800D8140(&pBlock->mUnknown24, p, lbl_803EC92C->mUnknown4.mUnknown20);
        break;
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            pBlock->mUnknown4 += 1.0f;
            pBlock->mUnknown10 += 1.0f;
            if (!(pBlock->mUnknown4 > pBlock->mUnknown8)) {
                p->mMotion.mFacing = (p->mMotion.mFacing + pBlock->mUnknown14) & 0xFFFFFF;
                p->mpUnknown796->mUnknown8 = p->mMotion.mFacing;
            } else {
                pEntries[pBlock->mUnknown20].mUnknown2C = 1.0f;
            }
            if (!(pBlock->mUnknown10 > pBlock->mUnknownC)) {
                Vector_80039F5C pos;
                Vector_80039F5C delta;

                delta.mX = pBlock->mUnknown18;
                delta.mY = pBlock->mUnknown1C;
                delta.mZ = 0.0f;
                fn_8022765C(&pos, &p->mMotion.mPos, &delta);
                if (fn_801248D4(p, 0, &pos, 0, 0.5f, 0.5f, 0, 0)) {
                    p->mMotion.mPos.mX += pBlock->mUnknown18;
                    p->mMotion.mPos.mY += pBlock->mUnknown1C;
                }
            }
            fn_800D81C8(&pBlock->mUnknown24, p);
        }
        break;
    }
    return 0;
}

extern "C" int fn_8009A6EC(Object_80039F5C *p)
{
    float distance;
    int result = fn_80178A68((Point_8017886C *)&p->mMotion.mPos) <= 5.0f;

    fn_801380AC(fn_801374BC(), &distance);
    if (distance < 40.0f) {
        result = 0;
    }
    if (p->mUnknown8 == 0xFF && p->mRatings[0] <= 59) {
        result = 0;
    }
    return result;
}

extern "C" int fn_8009A77C(Object_80039F5C *p)
{
    float distance = 1000.0f;
    int result = 0;
    int team = p->mIdBytes[2] ^ 1;
    int base = fn_800ACF40(p, 70);
    signed char bonus;
    short chance;
    short rating;

    fn_801244F0(p, team, 0, fn_80178D18(team), &distance, 1);
    if (fn_80177F70() == 4) {
        bonus = (distance - 10.0f) * 20.0f;
    } else {
        bonus = (distance - 10.0f) * 10.0f;
    }
    chance = base + bonus;
    if (p->mIdBytes[2] == fn_80178308()) {
        rating = p->mRatings[3];
    } else {
        rating = p->mRatings[8];
    }
    chance = chance + (signed char)((rating - 128) * 0.25f);
    if (chance > (signed char)fn_802372EC(0, 100)) {
        result = 1;
    }
    return result;
}

extern "C" void fn_8009A8F0(void)
{
    float handicap = 0.0f;
    unsigned int high = 0;
    unsigned int low = 0;
    unsigned int score0;
    unsigned int score1;
    float scale;

    lbl_803EA948->mUnknown0[1] = lbl_803EA948->mUnknown0[0] = handicap;
    if (lbl_803EA948->mUnknown8 == 0) {
        return;
    }
    switch (fn_8007F828(14)) {
    case 0:
        score0 = fn_801787DC(0);
        score1 = fn_801787DC(1);
        scale = 8.0f;
        break;
    case 1:
        score0 = fn_800D41F8(0);
        score1 = fn_800D41F8(1);
        scale = 100000.0f;
        break;
    case 2:
    default:
        return;
    }
    if (score0 > score1) {
        high = score0;
        low = score1;
    } else if (score1 > score0) {
        high = score1;
        low = score0;
    }
    if (high != low) {
        float ratio = (high - low) / scale;
        unsigned int steps;

        if ((high == score0 && fn_800B65A0(1) != 0xFF) || (high == score1 && fn_800B65A0(0) != 0xFF)) {
            ratio = fn_80260E24(ratio);
        } else {
            ratio = fn_80260FE8(ratio);
        }
        steps = ratio > 4.0f ? 4.0f : ratio;
        if (steps > 1) {
            handicap = (steps - 1) * 0.33333334f;
        }
        if (high == score0) {
            if (fn_800B65A0(1) != 0xFF && fn_800B65A0(0) == 0xFF) {
                lbl_803EA948->mUnknown0[1] = handicap;
            }
        } else if (fn_800B65A0(0) != 0xFF && fn_800B65A0(1) == 0xFF) {
            lbl_803EA948->mUnknown0[0] = handicap;
        }
    }
}

extern "C" void fn_8009AB34(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EA948, sizeof(Block_8009AB34), 0, 0x63747570);
    Block_8009AB34 *p = (Block_8009AB34 *)fn_8023816C(pHandle);

    p->mUnknown0[1] = p->mUnknown0[0] = 0.0f;
    if (fn_800BA6F8() == 0 && fn_8007F828(8) != 0) {
        p->mUnknown8 = 1;
    } else {
        p->mUnknown8 = 0;
    }
    fn_802381E0(pHandle);
}

extern "C" short fn_8009AC18(int team, int index, short value)
{
    int other = 1;
    float result;

    if (team == 1) {
        other = 0;
    }
    if (lbl_803EA948->mUnknown0[team] != 0.0f) {
        result = value * (lbl_803EA948->mUnknown0[team] * lbl_802D7BA8[index] + 1.0f);
        if (result > 255.0f) {
            result = 255.0f;
        }
        value = result;
    } else if (lbl_803EA948->mUnknown0[other] != 0.0f) {
        result = value * (1.0f - lbl_803EA948->mUnknown0[other] * lbl_802D7BD0[index]);
        if (result < 1.0f) {
            result = 1.0f;
        }
        value = result;
    }
    return value;
}
