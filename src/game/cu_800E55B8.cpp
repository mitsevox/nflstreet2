#include "game/State_800E4494.h"
#include "game/State_803EB098.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_802372EC.h"
#include "game/Object_8017886C.h"
#include "game/fn_80178D18.h"
#include <math.h>
#include "game/fn_800B65A0.h"

/* Records passed to fn_800E5EA4 as its third and fourth arguments; only the
   float +28 and byte +55 are read. */
struct Record_800E5EA4 {
    char mUnknown0[28];
    float mUnknown28;
    char mUnknown32[23];
    unsigned char mUnknown55;
};

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
int fn_80178320(void);
Point_8017886C fn_80177FE0(void);
float fn_80178A08(void);
int fn_800A7F58(int team);
int fn_800AC074(int team, int value);
float fn_8016B938(void);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(Point_8017886C *pOut, Point_8017886C *pA, Point_8017886C *pB);
int fn_800CA5CC(Object_80039F5C *p, int a, int b);
float fn_800CA9B4(int kind, Object_80039F5C *p);

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

void fn_800E586C(Object_80039F5C *p, float *pX)
{
    float best = 0.0f;
    int team = fn_80178320();
    signed char found = -1;
    unsigned char count = fn_80178D18(team);

    for (unsigned char i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(team, i);
        if (pOther->mMotion.mPos.mY < p->mMotion.mPos.mY) {
            if (*pX > 0.0f) {
                int inside = pOther->mMotion.mPos.mX > fn_80177FE0().mX &&
                             pOther->mMotion.mPos.mX < fn_80177FE0().mX + 4.0f;
                if (inside && pOther->mMotion.mPos.mX + fn_80177FE0().mX > best) {
                    found = i;
                    best = pOther->mMotion.mPos.mX + fn_80177FE0().mX;
                }
            } else {
                int inside = pOther->mMotion.mPos.mX < fn_80177FE0().mX &&
                             pOther->mMotion.mPos.mX > fn_80177FE0().mX + -4.0f;
                if (inside && fabsf(pOther->mMotion.mPos.mX - fn_80177FE0().mX) > best) {
                    found = i;
                    best = fabsf(pOther->mMotion.mPos.mX + fn_80177FE0().mX);
                }
            }
        }
    }
    if (found > -1 && best > 0.0f) {
        Object_80039F5C *pOther = fn_80039F5C(team, found);
        if (*pX > fn_80177FE0().mX) {
            if (*pX > pOther->mMotion.mPos.mX && *pX < pOther->mMotion.mPos.mX + 1.75f) {
                *pX = pOther->mMotion.mPos.mX + 1.75f;
            }
        } else {
            if (*pX < pOther->mMotion.mPos.mX && *pX > pOther->mMotion.mPos.mX - 1.75f) {
                *pX = pOther->mMotion.mPos.mX - 1.75f;
            }
        }
    }
}

int fn_800E5C00(Object_80039F5C *p, int value)
{
    Vector_80039F5C ball;
    int result = 1;

    if (fn_80137B40()) {
        ball.mX = fn_80137B40()->mMotion.mPos.mX;
        ball.mY = fn_80137B40()->mMotion.mPos.mY;
    } else {
        fn_80137D58(fn_801374BC(), &ball);
    }
    int heading = p->mUnknown512.mUnknown4;
    unsigned int turn = (p->mMotion.mFacing - heading) & 0xFFFFFF;
    if (turn <= 0x105B04) {
        result = 1;
    } else if (turn >= 0x105B05 && turn <= 0x305B04) {
        result = 4;
    } else if (turn >= 0x305B05 && turn <= 0x505B05) {
        result = 7;
    } else if (turn >= 0x505B06 && turn <= 0x705B05) {
        result = 10;
    } else if (turn >= 0x705B06 && turn <= 0x905B05) {
        result = 13;
    } else if (turn >= 0x905B06 && turn <= 0xB05B05) {
        result = 16;
    } else if (turn >= 0xB05B06 && turn <= 0xD05B05) {
        result = 14;
    } else if (turn >= 0xD05B06 && turn <= 0xF05B05) {
        result = 15;
    } else if (turn >= 0xF05B06 && turn <= 0x1000000) {
        result = 1;
    }
    if ((result == 1 || result == 4) && value != 242) {
        if (p->mMotion.mPos.mX >= 0.0f) {
            result = 15;
            if (fabsf(p->mMotion.mPos.mX) + fabsf(ball.mX) > 10.0f ||
                fn_80178A08() - fabsf(p->mMotion.mPos.mX) < 2.0f) {
                result = 7;
            }
        } else {
            result = 7;
            if (fabsf(p->mMotion.mPos.mX) + fabsf(ball.mX) > 10.0f ||
                fn_80178A08() - fabsf(p->mMotion.mPos.mX) < 2.0f) {
                result = 15;
            }
        }
    }
    if (value == 241) {
        switch (result) {
        case 15:
            switch (fn_802372EC(0, 4)) {
            case 0:
            case 1:
                break;
            case 2:
                result = 14;
                break;
            case 3:
                result = 16;
                break;
            }
            break;
        case 4:
            switch (fn_802372EC(0, 4)) {
            case 0:
            case 1:
                break;
            case 2:
                result = 7;
                break;
            case 3:
                result = 10;
                break;
            }
            break;
        }
    }
    return result;
}

int fn_800E5EA4(Object_80039F5C *p, Object_80039F5C *pOther, Record_800E5EA4 *pA, Record_800E5EA4 *pB,
                unsigned int kind)
{
    if (fn_800A7F58(p->mIdBytes[2]) == 2) {
        return 1;
    }
    if (fn_800A7F58(p->mIdBytes[2]) == 0) {
        return 0;
    }
    Object_80039F5C *pBall = fn_80137B40();
    int defense = (int)(float)pOther->mRatings[7];
    int offense = p->mRatings[9];
    int facing = 0;
    if (kind <= 5) {
        if (pA->mUnknown28 > pB->mUnknown28) {
            defense = (int)(defense * 0.75f);
        } else {
            offense = (int)(offense * 0.75f);
        }
        facing = 1;
    } else if (pA->mUnknown55) {
        defense = (int)(defense * 0.8f);
    } else {
        offense = (int)(offense * 0.8f);
    }
    if (facing && pBall) {
        Point_8017886C delta;
        fn_80227690(&delta, (Point_8017886C *)&pOther->mMotion.mPos, (Point_8017886C *)&p->mMotion.mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        fn_80227690(&delta, (Point_8017886C *)&pBall->mMotion.mPos, (Point_8017886C *)&p->mMotion.mPos);
        int turn = fn_801CFFD0(angle, fn_801CFE40(delta.mY, delta.mX));
        if (turn <= 0x3FFFFF) {
            defense -= (int)(defense * (fn_801CFB18(turn) * 0.5f));
        } else {
            defense = (int)(defense * 0.5f);
            defense += (int)(defense * (fn_801CFB94(turn) * 0.5f));
        }
    }
    offense = fn_800AC074(p->mIdBytes[2], offense);
    if (fn_800B65A0(p->mIdBytes[2]) == 255) {
        offense += (int)(offense * (fn_8016B938() * 0.5f));
    }
    if (offense < 0) {
        offense = 0;
    }
    if (defense < 0) {
        defense = 0;
    }
    if (fn_800CA5CC(p, 4, 1)) {
        offense = (int)(offense * fn_800CA9B4(6, p));
    }
    if (p->mFlags & 0x400) {
        offense = (int)(offense * 1.05f);
    }
    return fn_802372EC(0, offense) > fn_802372EC(0, defense);
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
