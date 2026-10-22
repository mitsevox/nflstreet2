#include "game/State_800E4494.h"
#include "game/State_803EB098.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_802372EC.h"

extern "C" {
void fn_800E3C30(Object_80039F5C *p);
Record_8011F4E0 *fn_8011F4E0(void);
void fn_800FBB70(void);
Message_800F01CC *fn_800AEE20(Object_80039F5C *p);
int fn_8009FE24(Object_80039F5C *p);
int fn_8009F778(Object_80039F5C *p);
Object_80039F5C *fn_800FB844(Object_80039F5C *p);
void fn_800FB824(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800E1778(Object_80039F5C *p);
int fn_800B146C(void);
Object_800670B4 *fn_80168708(int team);
float fn_80237260(int stream);
extern float lbl_803EA2C4;

void fn_800E55B8(Object_80039F5C *p)
{
    Record_8011F4E0 *pInfo = fn_8011F4E0();
    State_800E4494 *state = (State_800E4494 *)&p->mUnknown336;
    fn_800E3C30(p);
    state->mUnknown1 = 1;
    state->mUnknown2 = fn_802372EC(0, 45);
    state->mUnknown0 = 0;
    state->mUnknown24 = 0;
    state->mUnknown26 = 15;
    state->mUnknown28 = (signed char)(int)(fn_80237260(0) * 240.0f + 150.0f);
    for (int i = 1; i >= 0; i--) {
        state->mUnknown22[i] = 0;
    }
    if (pInfo->mUnknown5 == 0) {
        fn_800FBB70();
    }
    Object_800670B4 *pTeam = fn_80168708(p->mIdBytes[2]);
    Message_800F01CC *pMessage = fn_800AEE20(p);
    if (pMessage == 0) {
        if (pTeam->mUnknown8.mUnknownF == 0) {
            pMessage = (Message_800F01CC *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]),
                (p->mId >> 8) & 255, (p->mId >> 16) & 255);
        } else {
            unsigned char index = fn_80163E94(pTeam, p->mIdBytes[1], 0)->mUnknownB;
            pMessage = (Message_800F01CC *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mIdBytes[2], index);
        }
    }
    switch (pMessage->mId & ~0x80) {
    case 48:
        if (pMessage->mUnknown1[0] >= fn_802372EC(0, 100)) {
            state->mUnknown30 = 0;
            state->mUnknown24 = 1;
        }
        break;
    case 22:
        if ((fn_8009FE24(p) && state->mpUnknown36 == 0) ||
            (fn_8009F778(p) && state->mpUnknown36 == 0)) {
            Object_80039F5C *pOther = fn_800FB844(p);
            if (pOther) {
                fn_800FB824(p, pOther);
                state->mpUnknown36 = pOther;
            }
        } else {
            fn_800E1778(p);
        }
        break;
    default:
        fn_800E1778(p);
        break;
    }
}

int fn_800E6984(Object_80039F5C *p)
{
    int angle = (int)(((0x1000000 - (p->mUnknown512.mUnknown4 - p->mMotion.mFacing)) & 0xFFFFFF)
                     * 0.000021457672119140625f);
    if (angle <= 179) {
        angle = angle < 0 ? 0 : angle > 135 ? 135 : angle;
    } else {
        angle = angle < 225 ? 225 : angle > 359 ? 359 : angle;
    }
    if (angle >= 225 && angle <= 247) return 16;
    if (angle >= 248 && angle <= 292) return 14;
    if (angle >= 293 && angle <= 337) return 15;
    if ((angle >= 338 && angle <= 358) || angle <= 22) return 1;
    if ((angle >= 23 && angle <= 67) || (angle >= 68 && angle <= 112) ||
        (angle >= 113 && angle <= 157)) return 4;
    return 1;
}

int fn_800E6F48(Object_80039F5C *p)
{
    unsigned char value = p->mpState->mUnknown1;
    unsigned int frames = (unsigned int)(60.0f / lbl_803EA2C4);
    p->mUnknown336 = (value >> 5) * frames + (int)((value & 31) * 0.032258063554763794f * 60.0f);
    if (!fn_800B146C()) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown0 = 0.0f;
        p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
    }
    return 0;
}
}
