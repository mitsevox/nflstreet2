#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Class_80297CE8.h"
#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Team_80167A8C.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"

extern "C" {
int fn_800D0B90(Object_80039F5C *p);
}

/* Bytes +0 and +1 of the player block at +336 as fn_80105898 and
   fn_80105AF4 access them. Partial layout. */
struct State_80105898 {
    signed char mUnknown0;
    unsigned char mUnknown1;
};

extern float lbl_803EAEF4;

struct Block_800F4A74 {
    char mUnknown0[20];
    int mUnknown20;
    int mUnknown24;
    float mUnknown28;
    float mUnknown32;
    int mUnknown36;
    int mUnknown40;
    float mUnknown44;
    unsigned char mUnknown48;
    unsigned char mUnknown49;
    unsigned char mUnknown50;
    unsigned char mUnknown51;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
    unsigned char mUnknown55;
    unsigned char mUnknown56;
    unsigned char mUnknown57;
    short mUnknown58;
    unsigned char mUnknown60;
    unsigned char mUnknown61;
    unsigned char mUnknown62;
    unsigned char mUnknown63;
    unsigned char mUnknown64;
    char mUnknown65[23];
};

/* View of another player's +336 block read by fn_800F3344 while that player
   is in state 28. Only the accessed prefix is declared; the size is unknown. */
struct Block_800F3344 {
    unsigned short mUnknown0;
    char mUnknown2[2];
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
};
extern "C" {
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_8011E3EC(Object_80039F5C *p, int a);
int fn_80178308(void);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
int fn_801486A0(void);
extern float lbl_803ECB08;
void fn_800D6914(int a, Object_80039F5C *p);
void fn_80104B3C(Object_80039F5C *p, Vector_80039F5C *pOut);
int fn_80105E90(Object_80039F5C *p, Object_80039F5C *pTarget, int kind);
int fn_80106618(Object_80039F5C *p);
void fn_80106678(Record_8011F518 *pRecord, Object_80039F5C *p, int a, int b);
void fn_8010CEB8(Object_80039F5C *p, int kind);
float fn_8012506C(Object_80039F5C *p, int kind);
void fn_8022765C(void *pOut, void *pA, void *pB);
extern const float lbl_803ED6CC;
void fn_800A5A8C(int a, Object_80039F5C *p, Object_80039F5C *pOther);
int fn_801787A0(void);
int fn_8011F1A4(void);
void fn_8013FA8C(int a);
void fn_800A2190(int bit);
void fn_800A60D8(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_801061E8(Object_80039F5C *p, Object_80137ABC *pBall);
void fn_8011F5AC(int index);
void fn_80148108(int mode);
int fn_801481B0(void);
Object_800670B4 *fn_80168708(int team);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
int fn_801BA5A8(void *pA, void *pB, unsigned short id, int index);
void fn_8009BD60(Object_80039F5C *p);
int fn_801BA568(void *pA, void *pB, int id);
extern float lbl_803EA2C4;
int fn_8011E9B4(Object_80039F5C *p);
int fn_801BA2A8(void *a, void *b, unsigned short c, unsigned short d, unsigned short e, void *p, float f);
float fn_801CFB94(int angle);
void fn_800D7534(int team);
void fn_801783D0(int bit, int on);
void fn_80099568(int kind);
void fn_8013AC28(Object_80137ABC *pBall, Vector_80039F5C *pTarget, int mode, float speed, float spin, float side);
}

extern "C" float fn_801CFB18(int angle);

extern "C" int fn_801CFDD0(float);

extern unsigned int lbl_803EAEE0;

extern unsigned int lbl_803EAEE4;

extern "C" void fn_80104B24(Vector_80039F5C *p);

extern "C" void fn_80105168(int mode, Object_80137ABC *pBall, Object_80039F5C *p, Object_80039F5C *pOther, float speed, Vector_80039F5C *pTarget, int unused);

extern "C" void fn_801BE67C(void *pA, void *pB, void *pC, void *p);

extern "C" int fn_801CFFF0(int a, int b, float factor);

extern "C" int fn_801C4E98(void *p, const char *pName);


extern "C" int fn_8011F524(void);

struct Reach_80105630 {
    unsigned int mEnd;
    unsigned char mHand;
    unsigned char mBall;
};

extern "C" int fn_8023790C(void);

extern "C" void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);


extern "C" int fn_8013BA70(Object_80137ABC *pBall, int *pOut);

extern "C" Reach_80105630 *fn_8009CD00(Object_80039F5C *p, void (*pCallback)(Object_80039F5C *, Vector_80039F5C *, Reach_80105630 *),
                                       int a, unsigned int delay, int b);

extern "C" void fn_8009CEE4(Object_80039F5C *p, int ref, int joint, int a, int b);


extern "C" float fn_801BD690(Block_801BD6D4 *p, int key);




extern "C" void fn_80104814(Object_80039F5C *p, Object_80039F5C *pOther, Object_80137ABC *pBall,
                            Vector_80039F5C *pTarget);

extern "C" void fn_80104944(Object_80039F5C *p, Vector_80039F5C *pOut);

extern "C" void fn_80104A08(Object_80039F5C *p, float scale, int angle, Point_8017886C *pPoint, float *pValue);





extern "C" void fn_8010D80C(Object_80039F5C *p, Vector_80039F5C *pOut);

extern "C" float fn_8010D82C(Object_80039F5C *p);

extern "C" int fn_8011F32C(void);

extern float lbl_803EAEEC;

extern float lbl_803EAEF0;

extern "C" void fn_80227350(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);

struct Turn_8010680C {
    int mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
};

extern "C" int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);

extern "C" Object_80039F5C *fn_800FB9D4(Object_80039F5C *p);
extern "C" {
}

extern "C" int fn_80104720(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_801047C8(void);
extern "C" void fn_801048B4(Object_80039F5C *p, Object_80137ABC *pBall, Vector_80039F5C *pTarget);
extern "C" void fn_80104C3C(Object_80039F5C *p, Vector_80039F5C *pOut, float scale);

extern "C" float fn_80104C9C(Object_80039F5C *p, Object_80039F5C *pOther)
{
    unsigned int frames;
    Vector_80039F5C *pPos;
    Vector_80039F5C *pOtherPos;
    float count;
    float time;
    float gain;
    Vector_80039F5C ahead;

    if (fn_8011F518()->mUnknown4 == 12) {
        frames = lbl_803EAEE4;
    } else {
        frames = lbl_803EAEE0;
    }
    pPos = &p->mMotion.mPos;
    pOtherPos = &pOther->mMotion.mPos;
    time = fn_8022781C(pOtherPos, pPos);
    count = frames;
    time /= count;
    if (time < 0.06f) {
        time = 0.06f;
    }
    fn_80104C3C(pOther, &ahead, count);
    gain = (fn_8022781C(&ahead, pPos) - fn_8022781C(pOtherPos, pPos)) / count;
    return time < time + gain ? time + gain : time;
}

extern "C" void fn_80104D98(Object_80039F5C *p)
{
    Point_8017886C goal;
    Record_8011F518 *pRecord;
    Object_80039F5C *pOther;
    unsigned short animation;

    fn_8009BD60(p);
    goal = fn_80177FE0();
    pRecord = fn_8011F518();
    pOther = fn_8009BCE8(&pRecord->mUnknown0);
    if (pRecord->mUnknown4 == 8) {
        animation = 34;
        p->mUnknown1008.mUnknown0 = 2;
    } else if (pRecord->mUnknown4 == 11 || pRecord->mUnknown4 == 9 || pRecord->mUnknown4 == 10 ||
               pRecord->mUnknown4 == 2 || pRecord->mUnknown4 == 3 || pRecord->mUnknown4 == 4 ||
               pRecord->mUnknown4 == 5) {
        Vector_80039F5C target;
        Point_8017886C dir;

        animation = pRecord->mUnknown4 != 10 ? 135 : 177;
        if (animation == 135 && fn_800D0B90(p) != 0) {
            animation = 191;
        }
        pRecord->mUnknown5 = 6;
        {
            Object_80137ABC *pBall = fn_801374BC();

            fn_80105168(6, pBall, p, pOther, fn_80104C9C(p, pOther), &target, 0);
        }
        if (p->mpState->mId == 91 && p->mMotion.mPos.mY < goal.mY) {
            fn_80104B24(&target);
        }
        fn_80104814(p, pOther, fn_801374BC(), &target);
        fn_80227690(&dir, &target, &p->mMotion.mPos);
        p->mUnknown1008.mUnknown1 = (int)(dir.mX * 10.0f);
        p->mUnknown1008.mUnknown2 = (int)(dir.mY * 10.0f);
    } else {
        Point_8017886C delta;
        int side;
        int angle;
        int facing;
        float rate;

        switch (pRecord->mUnknown4) {
        case 2:
        case 3:
            animation = 201;
            break;
        case 4:
        case 5:
            animation = 82;
            break;
        case 6:
        case 7:
            animation = 204;
            break;
        case 0:
        default:
            animation = 116;
            break;
        }
        switch (p->mpState->mUnknown3[0]) {
        case 2:
            side = 0;
            break;
        case 1:
            side = 1;
            break;
        case 0:
        default:
            side = fn_80104720(p, pOther);
            break;
        }
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        if (pRecord->mUnknown4 <= 1 || pRecord->mUnknown4 == 12 || pRecord->mUnknown4 == 13 ||
            pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7) {
            rate = 0.25f;
        } else {
            rate = 0.5f;
        }
        if (side) {
            pRecord->mUnknown5 = 6;
            facing = 0;
        } else {
            pRecord->mUnknown5 = 3;
            facing = 0x800000;
        }
        facing = fn_801CFFF0(facing, angle, rate);
        p->mUnknown512.mUnknown14 = 6;
        p->mUnknown512.mUnknown8 = facing;
        p->mUnknown512.mUnknown0 = 1.0f;
        p->mUnknown512.mUnknown4 = facing;
        p->mUnknown1008.mUnknown0 = pRecord->mUnknown5;
    }
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, animation, p, 1.0f);
    if (pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7) {
        fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
    }
    p->mUnknown512.mUnknown14 = 0;
    p->mUnknown778 = -1;
    p->mFlags &= ~0x1000;
    p->mFlags &= ~4;
}

extern "C" float fn_801050DC(Object_80137ABC *pBall, Vector_80039F5C *pTarget, float speed)
{
    Vector_80039F5C delta;
    float time;
    float clamped;

    fn_80137D58(pBall, &delta);
    fn_802276B4(&delta, &delta, pTarget);
    time = fn_802270A4(&delta) / speed;
    if (time < 0.04074074f) {
        clamped = 0.04074074f;
    } else {
        clamped = time;
        if (clamped > 0.4074074f) {
            clamped = 0.4074074f;
        }
    }
    return clamped * lbl_803EA2C4;
}

extern "C" void fn_80105168(int mode, Object_80137ABC *pBall, Object_80039F5C *p, Object_80039F5C *pOther, float speed, Vector_80039F5C *pTarget, int unused)
{
    Vector_80039F5C delta;
    Vector_80039F5C ball;
    Vector_80039F5C hand;
    Vector_80039F5C handDir;
    Vector_80039F5C velocity;
    float distance;
    float runSpeed;
    int angle;
    float time;

    fn_80137D58(pBall, &ball);
    if (mode == 6) {
        fn_8009BF5C(pOther, fn_801C4E98(pOther->mpUnknown4->mpUnknown100, "rwrist"), &hand, &handDir);
    } else {
        fn_8009BF5C(pOther, fn_801C4E98(pOther->mpUnknown4->mpUnknown100, "lwrist"), &hand, &handDir);
    }
    fn_802276B4(&delta, &ball, &hand);
    distance = fn_802270A4(&delta);
    fn_80104B3C(pOther, &velocity);
    runSpeed = fn_802270D4(&velocity);
    angle = fn_801CFE40(velocity.mY, velocity.mX);
    angle = (angle - fn_801CFE40(delta.mY, delta.mX)) & 0xFFFFFF;
    time = distance / (speed * fn_801CFB94(fn_801CFDD0(runSpeed * fn_801CFB18(angle) / speed)) + runSpeed * fn_801CFB94(angle));
    if (time <= 0.0f || time > 120.0f) {
        time = 2.0f;
    }
    fn_80104C3C(pOther, pTarget, time);
    pTarget->mZ = hand.mZ;
    fn_801048B4(p, pBall, pTarget);
    pTarget->mY = pTarget->mY >= pOther->mMotion.mPos.mY ? pTarget->mY : pOther->mMotion.mPos.mY;
}

extern "C" int fn_8010531C(Object_80039F5C *p) {
    switch (p->mpState->mId) {
    case 5:
    case 10:
    case 11:
    case 12:
    case 16:
    case 17:
    case 28:
    case 32:
    case 51:
        return 0;
    }
    return 1;
}

extern "C" Object_80039F5C *fn_80105384(Object_80039F5C *p, int aggressive, Point_8017886C *pOut)
{
    float bestScore = 0.0f;
    unsigned int count = fn_80178D18(p->mIdBytes[2]);
    Object_80039F5C *pBest = 0;
    int anyDepth = 0;
    unsigned char i;

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther;
        float distance;
        float score;
        float stamina;
        Vector_80039F5C target;
        Point_8017886C spot;
        Object_80137ABC *pBall;
        int side;

        if (((p->mId >> 16) & 0xFF) == i) {
            continue;
        }
        pOther = fn_80039F5C((p->mId >> 8) & 0xFF, i);
        if (!anyDepth && pOther->mMotion.mPos.mY >= p->mMotion.mPos.mY) {
            continue;
        }
        if (fn_8010531C(pOther) == 0 || fn_8011E9B4(pOther) != 0) {
            continue;
        }
        distance = fn_8022781C(&pOther->mMotion.mPos, &p->mMotion.mPos);
        if (distance >= 7.0f) {
            continue;
        }
        if (fn_801CFFD0(pOther->mMotion.mFacing, 0xC00000) <= 0x200000) {
            continue;
        }
        if ((p->mpState[0].mId == 91 || p->mpState[1].mId == 91 || (p->mUnknown2914 == 0 && fn_8011F524() != 0)) &&
            pOther->mpState->mId == 90) {
            score = !aggressive ? 70.0f : 14.0f;
        } else {
            score = 7.0f - distance;
        }
        stamina = fn_8012506C(p, 3);
        if (stamina < 42.0f) {
            score += (42.0f - stamina) * 0.16666667f;
        }
        pBall = fn_801374BC();
        fn_80105168(6, pBall, p, pOther, fn_80104C9C(p, pOther), &target, 0);
        spot.mX = target.mX;
        spot.mY = target.mY;
        fn_802276B4(&target, &target, &p->mMotion.mPos);
        side = ((fn_801CFE40(target.mY, target.mX) - p->mMotion.mFacing) & 0xFFFFFF) <= 0x7FFFFF ? 1 : 2;
        if (side != p->mUnknown776) {
            if (aggressive) {
                score *= 0.5f;
            } else {
                score = 0.0f;
            }
        }
        if (score > bestScore) {
            bestScore = score;
            pBest = pOther;
            if (pOut) {
                *pOut = spot;
            }
        }
    }
    return pBest;
}

extern "C" void fn_80105630(Object_80039F5C *p, Vector_80039F5C *pTarget, Reach_80105630 *pReach)
{
    int done = 0;
    Record_8011F518 *pRecord = fn_8011F518();
    Object_80039F5C *pOther = fn_8009BCE8(&pRecord->mUnknown0);

    if (pOther != 0) {
        Object_80137ABC *pBall = fn_80137ABC(pReach->mBall);
        char name[10];
        Vector_80039F5C shoulder;
        Vector_80039F5C dir;
        unsigned int now;
        float t;
        int turn;

        if (pReach->mHand == 1) {
            strcpy(name, "rshoulder");
        } else {
            strcpy(name, "lshoulder");
        }
        fn_8009BF5C(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, name), &shoulder, &dir);
        now = fn_8023790C() + 2;
        t = (pReach->mEnd - now) * 0.083333336f;
        t = t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t);
        fn_80105168(pRecord->mUnknown5, pBall, p, pOther, fn_80104C9C(p, pOther), pTarget, 0);
        fn_802276B4(pTarget, pTarget, &shoulder);
        turn = ((fn_801CFE40(pTarget->mY, pTarget->mX) - p->mMotion.mFacing) << 8) >> 8;
        fn_80227538((Point_8017886C *)pTarget, ((int)(turn * (1.0f - t)) + p->mMotion.mFacing) & 0xFFFFFF, 1.5f);
        pTarget->mZ = 0.4f;
        fn_8022765C(pTarget, pTarget, &shoulder);
    } else {
        done = 1;
    }
    if (pReach->mEnd <= fn_8023790C()) {
        done = 1;
    }
    if (done) {
        fn_8009CE88(p, pReach->mHand == 1 ? &p->mUnknown200 : &p->mUnknown108, 12);
        fn_8009CE88(p, &p->mUnknown16, 12);
    }
}

extern "C" int fn_80105898(Object_80039F5C *p) {
    Message_800F01CC message;
    Vector_80039F5C ball;
    Point_8017886C delta;
    State_80105898 *pState = (State_80105898 *)&p->mUnknown336;
    Record_8011F518 *pRecord = fn_8011F518();
    Object_80039F5C *pTarget = fn_80039F5C(p->mIdBytes[2], p->mpState->mUnknown1);
    int kind = 3;

    fn_80137D58(fn_801374BC(), &ball);
    fn_80227690(&delta, &ball, &p->mMotion.mPos);
    if (((fn_801CFE40(delta.mY, delta.mX) - p->mMotion.mFacing) & 0xFFFFFF) <= 0x7FFFFF) {
        kind = 6;
    }
    if (p->mpState->mUnknown2 == 9 || p->mpState->mUnknown2 == 11) {
        fn_800D6914(fn_800D0B90(p) != 0, p);
    }
    fn_80106678(pRecord, pTarget, kind, p->mpState->mUnknown2);
    pState->mUnknown0 = 2;
    pState->mUnknown1 = 0;
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~0x1000;
    p->mFlags &= ~4;
    if (pRecord->mUnknown4 != 8) {
        if (p == fn_80137B40()) {
            if (!(pRecord->mUnknown4 == 10 || pRecord->mUnknown4 == 1 || pRecord->mUnknown4 == 13 ||
                  pRecord->mUnknown4 == 3 || pRecord->mUnknown4 == 5 || pRecord->mUnknown4 == 7) &&
                (pRecord->mUnknown4 <= 1 || pRecord->mUnknown4 == 12 || pRecord->mUnknown4 == 13 ||
                 pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7 ||
                 (pRecord->mUnknown4 >= 14 && pRecord->mUnknown4 <= 15))) {
                fn_80137C10(pTarget);
            }
            if (!fn_80105E90(p, pTarget, pRecord->mUnknown4)) {
                fn_801C1F94(&message, 0, 4);
                message.mId = 1;
                fn_800F053C(0, p->mpState, &message, p);
            }
        }
    } else if (p->mpState[1].mId == 31) {
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 1);
    } else if (p->mpState[1].mId == 33) {
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 2);
    }
    if (pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7) {
        fn_80104D98(p);
        pState->mUnknown0 = 0;
    }
    return 0;
}

extern "C" int fn_80105AF4(Object_80039F5C *p) {
    int result = 0;
    Record_8011F518 *pRecord = fn_8011F518();
    State_80105898 *pState = (State_80105898 *)&p->mUnknown336;

    if (fn_8009BCE8(&pRecord->mUnknown0)->mpState->mId == 93) {
        return 1;
    }
    if (p->mFlags & 1) {
        Object_80039F5C *pOther;

        p->mFlags &= ~1;
        pState->mUnknown1 = 1;
        pOther = fn_8009BCE8(&pRecord->mUnknown0);
        if (pRecord->mUnknown4 == 10 || pRecord->mUnknown4 == 1 || pRecord->mUnknown4 == 13 ||
            pRecord->mUnknown4 == 3 || pRecord->mUnknown4 == 5 || pRecord->mUnknown4 == 7) {
            if (pRecord->mUnknown4 <= 1 || pRecord->mUnknown4 == 12 ||
                pRecord->mUnknown4 == 13 || pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7) {
                fn_800A5A8C(0, p, pOther);
            } else {
                fn_800A5A8C(1, p, pOther);
            }
            fn_800A60D8(p, pOther);
        }
    }
    if (pRecord->mUnknown4 == 8 && fn_80137C48(p) == 0) {
        return 1;
    }
    if (pState->mUnknown0 != 0) {
        p->mFlags &= ~4;
        if (--pState->mUnknown0 == 0) {
            fn_80104D98(p);
        }
    }
    if (p->mFlags & 0x1000) {
        Object_80137ABC *pBall = fn_80137C48(p);

        if (pBall != 0 && fn_801787A0() == 0) {
            fn_801061E8(p, pBall);
            if (pRecord->mUnknown4 != 8) {
                fn_80067E3C(60, &p->mpUnknown4->mUnknown4, p->mId, 0, 0, 0);
                fn_800A2190(2);
            }
            fn_8011F5AC(0);
        }
        p->mFlags &= ~0x1000;
    }
    if (p->mFlags & 4) {
        p->mFlags &= ~4;
        result = 1;
    }
    if (result == 1) {
        if ((pRecord->mUnknown4 <= 1 || pRecord->mUnknown4 == 12 || pRecord->mUnknown4 == 13 ||
             pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7 ||
             (pRecord->mUnknown4 >= 14 && pRecord->mUnknown4 <= 15)) &&
            (pRecord->mUnknown4 == 10 || pRecord->mUnknown4 == 1 || pRecord->mUnknown4 == 13 ||
             pRecord->mUnknown4 == 3 || pRecord->mUnknown4 == 5 || pRecord->mUnknown4 == 7)) {
            if (fn_800B65A0(p->mIdBytes[2]) != 255 && fn_8011F1A4() == 0 && fn_801481B0() == 0) {
                fn_80148108(0);
                fn_8013FA8C(2);
            }
            if (fn_800B65A0(p->mIdBytes[2]) == 255 && fn_8011F1A4() == 0) {
                fn_8013FA8C(2);
            }
        }
        if (pRecord->mUnknown4 != 8) {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
        }
    }
    return result;
}

extern "C" void fn_80105DF0(Message_800F01CC *pMessage) {
    Object_800670B4 *pObject;
    unsigned int count;
    unsigned char i;

    if (pMessage->mUnknown1[2] == 1) {
        pMessage->mUnknown1[2] = 2;
    } else if (pMessage->mUnknown1[2] == 2) {
        pMessage->mUnknown1[2] = 1;
    }
    pObject = fn_80168708(fn_80178308());
    count = fn_80178D18(fn_80178308());
    for (i = 0; i < count; i++) {
        if (fn_80163E94(pObject, i, 0)->mUnknownB == pMessage->mUnknown1[0]) {
            pMessage->mUnknown1[0] = i;
            break;
        }
    }
}

extern "C" int fn_80105E90(Object_80039F5C *p, Object_80039F5C *pTarget, int kind) {
    int result = 1;
    Object_80137ABC *pBall = fn_801374BC();
    unsigned char count = fn_80137F88(pBall);
    int state = fn_8013BA70(pBall, 0);
    Vector_80039F5C target;

    if (count <= 21 && state == 4) {
        result = 0;
    } else if ((kind == 11 || kind == 9 || kind == 10 || kind == 2 || kind == 3 || kind == 4 || kind == 5) &&
               !(kind == 10 || kind == 1 || kind == 13 || kind == 3 || kind == 5 || kind == 7) &&
               !(kind >= 2 && kind <= 5)) {
        Object_80137ABC *pLive = fn_801374BC();

        fn_80105168(6, pLive, p, pTarget, fn_80104C9C(p, pTarget), &target, 0);
        if (fn_8022781C(&target, &p->mMotion.mPos) > 9.5f ||
            (!fn_801047C8() && pTarget->mMotion.mPos.mY > p->mMotion.mPos.mY)) {
            result = 0;
        }
    }
    if (fn_801BE648(p->mpUnknown792) == 234 || fn_801BE648(p->mpUnknown792) == 238) {
        result = 0;
    }
    return result;
}

extern "C" int fn_80105FF8(Object_80039F5C *p, Object_80137ABC *pBall, float time) {
    int ready = 0;
    Reach_80105630 *pReach = 0;
    Record_8011F518 *pRecord = fn_8011F518();
    int joint = fn_801C4E98(fn_8009BCE8(&pRecord->mUnknown0)->mpUnknown4->mpUnknown100, "rwrist");

    if (pRecord->mUnknown4 != 8) {
        int animation = fn_801BE648(p->mpUnknown792);
        unsigned char side = p->mUnknown776;

        if (p->mpState->mId == 10 || p->mpState->mId == 16) {
            int index = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, animation, 0);

            if (index != 0xFFFF && fn_801BD690(&p->mpUnknown800[index].mUnknown4C, 0xC001) > time) {
                ready = 1;
            }
        } else {
            ready = 1;
        }
        if (ready) {
            int left;

            if (animation == 135 || animation == 191) {
                fn_8009CEE4(p, pRecord->mUnknown0, joint, 6, 0);
            }
            left = side == 2;
            pReach = fn_8009CD00(p, fn_80105630, left, (unsigned int)time, 2);
            if (pReach != 0) {
                pReach->mHand = left;
                pReach->mBall = fn_801374E0(pBall);
                pReach->mEnd = fn_8023790C() + (unsigned int)time + 2;
            }
        }
    }
    return pReach != 0;
}

extern "C" void fn_801061E8(Object_80039F5C *p, Object_80137ABC *pBall) {
    Vector_80039F5C target;
    Vector_80039F5C velocity;
    float speed;
    Record_8011F518 *pRecord = fn_8011F518();
    Object_80039F5C *pTarget = fn_8009BCE8(&pRecord->mUnknown0);

    if (pRecord->mUnknown4 == 8) {
        fn_8013791C(pBall, 2, 0);
        fn_8010D80C(pTarget, &target);
        speed = fn_8010D82C(pTarget);
        speed = fn_801050DC(pBall, &target, speed);
        if (fn_8011F32C()) {
            fn_8013AC28(pBall, &target, 2, speed, 0.0f, 1.0f);
        } else {
            fn_8013AC28(pBall, &target, 2, speed, 0.0f, 1.0f);
        }
        fn_80137BC0(pBall, pTarget);
    } else if (!(pRecord->mUnknown4 == 10 || pRecord->mUnknown4 == 1 || pRecord->mUnknown4 == 13 ||
                 pRecord->mUnknown4 == 3 || pRecord->mUnknown4 == 5 || pRecord->mUnknown4 == 7)) {
        Record_800B15FC *pEvent;

        fn_80099568(2);
        fn_801379B4(pBall, 3, 0);
        speed = fn_80104C9C(p, pTarget);
        fn_80105168(pRecord->mUnknown5, pBall, p, pTarget, speed, &target, 0);
        if (pRecord->mUnknown4 == 9) {
            if (p->mUnknown2914 == 0) {
                fn_80104B24(&target);
            } else {
                fn_800A5A8C(6, p, p);
            }
        }
        if (pRecord->mUnknown4 == 9 || pRecord->mUnknown4 == 11) {
            fn_80104944(p, &target);
            fn_80104A08(p, pRecord->mUnknown8, pRecord->mUnknown12, (Point_8017886C *)&target, &speed);
        }
        fn_80104814(p, pTarget, pBall, &target);
        fn_8013AC28(pBall, &target, 3, speed, 1.0f, 4.0f);
        fn_80137BC0(pBall, pTarget);
        fn_80137EC4(pBall, &velocity);
        pEvent = fn_800B15FC();
        fn_8009BD2C(p, &pEvent->mUnknown0);
        pEvent->mUnknownC = p->mMotion.mPos.mX;
        pEvent->mUnknown10 = p->mMotion.mPos.mY;
        if (velocity.mY < 0.0f) {
            pEvent->mUnknown4 = pTarget->mId;
            pEvent->mUnknown8 = pRecord->mUnknown4;
            pEvent->mUnknown14 = 7;
            fn_801783D0(1, 1);
        } else {
            pEvent->mUnknown14 = 5;
            pEvent->mUnknown4 = 0;
            pEvent->mUnknown16 = 0;
            pEvent->mUnknown8 = (int)pTarget;
            fn_800D7534(p->mIdBytes[2]);
            fn_801783D0(13, 1);
            fn_801783D0(1, 0);
        }
        fn_800B1508();
    }
}

extern "C" int fn_801064A4(Object_80039F5C *p, int a) {
    int result = 0;
    Object_80039F5C *pTarget = fn_80105384(p, 1, 0);

    if (pTarget == 0) {
        if (fn_801486A0() == 0) {
            fn_8013791C(fn_801374BC(), 3, 1);
        }
    } else if (fn_80105E90(p, pTarget, 11)) {
        Message_800F01CC message;

        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 25;
        fn_800D0BF4(p, a, 25);
        message.mUnknown1[0] = pTarget->mIdBytes[1];
        message.mUnknown1[1] = 11;
        fn_800F00D4(0, p->mpState, &message, p);
        fn_8010CEB8(pTarget, 11);
    }
    return result;
}

extern "C" int fn_80106580(Object_80039F5C *p, int a) {
    int result = 0;
    Object_80039F5C *pTarget = fn_80105384(p, a, 0);

    if (pTarget != 0 && fn_80105E90(p, pTarget, 11) && fn_80106618(p)) {
        result = 1;
        fn_80106678(fn_8011F518(), pTarget, 6, 11);
        fn_8010CEB8(pTarget, 11);
        fn_800D6914(0, p);
    }
    return result;
}

extern "C" int fn_80106618(Object_80039F5C *p) {
    int *pValue;

    switch (p->mUnknown776) {
    case 1:
        pValue = &p->mUnknown108;
        break;
    case 2:
        pValue = &p->mUnknown200;
        break;
    default:
        pValue = 0;
        break;
    }
    if (pValue != 0) {
        return *pValue != 0 && *pValue != 4;
    }
    return 0;
}

extern "C" void fn_80106678(Record_8011F518 *pRecord, Object_80039F5C *p, int a, int b) {
    fn_8009BD2C(p, &pRecord->mUnknown0);
    pRecord->mUnknown4 = b;
    pRecord->mUnknown5 = a;
    pRecord->mUnknown8 = 0.0f;
    pRecord->mUnknown12 = 0;
}

extern "C" int fn_801066D0(Object_80039F5C *p, Object_80039F5C *pTarget, int kind) {
    unsigned char filter[2] = {1, 0x11};
    int result = 1;

    if (kind == 9) {
        Object_80137ABC *pBall = fn_801374BC();
        Vector_80039F5C pos;
        Vector_80039F5C target;

        fn_80105168(6, pBall, p, pTarget, fn_80104C9C(p, pTarget), &target, 0);
        pos.mX = p->mMotion.mPos.mX;
        pos.mY = p->mMotion.mPos.mY;
        pos.mZ = p->mMotion.mPos.mZ;
        fn_80227350(&pos, (Vector_80039F5C *)&p->mMotion.mUnknown40, 40.0f);
        result = fn_801248D4(p, &pos, &target, 0, lbl_803EAEF0, lbl_803EAEEC, (Filter_801248D4 *)filter, pTarget);
    }
    return result;
}

extern "C" int fn_80106794(Object_80039F5C *p) {
    if (fn_80137C48(p) == fn_801374BC()) {
        fn_80137C10(0);
    }
    return 1;
}

extern "C" int fn_801067D8(Object_80039F5C *p) {
    return fn_8012506C(p, 6) < lbl_803EAEF4;
}

extern "C" int fn_8010680C(Table_80089904 *pTable, unsigned short key, void *pRecord, Record_800D81C8 *pEntries,
                           Object_80039F5C *p, unsigned int phase) {
    Turn_8010680C *pTurn = (Turn_8010680C *)fn_801BE60C(p->mpUnknown792, key);

    switch (phase) {
    case 0: {
        int index = fn_8009C4B0(pTable, &p->mUnknown1008);
        int facing;

        if (index >= 0) {
            p->mFlags &= ~4;
            pTurn->mUnknown8 = fn_801BA2A8(pRecord, pEntries, pTable->mEntries[index].mUnknown0,
                                           pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        }
        facing = p->mUnknown512.mUnknown8;
        if (fn_801CFFD0(facing, p->mMotion.mFacing) > 0xB60B) {
            fn_801BE760(p->mpUnknown792, key, 1);
            if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 204)) {
                int entry;

                pEntries = p->mpUnknown800;
                entry = fn_801BA5A8(p->mpUnknown796, pEntries, 204, 0);

                pTurn->mUnknown4 = pEntries[entry].mUnknown48;
                if (pTurn->mUnknown4 != 0.0f ||
                    (pTurn->mUnknown4 = fn_801BD690(&pEntries[entry].mUnknown4C, 0xC003)) != 0.0f) {
                    pTurn->mUnknown4 = pTurn->mUnknown4 > 50.0f ? 50.0f : pTurn->mUnknown4;
                    pTurn->mUnknown0 = (int)(fn_801CFFD0(facing, p->mMotion.mFacing) / pTurn->mUnknown4);
                    if (((p->mMotion.mFacing - facing) & 0xFFFFFF) <= 0x7FFFFF) {
                        pTurn->mUnknown0 = -pTurn->mUnknown0;
                    }
                    /* The shipped code discards the rate it just computed. */
                    pTurn->mUnknown0 = 0;
                }
            }
        }
        break;
    }
    case 1:
        break;
    case 2:
        if (pTurn->mUnknown4 > 0.0f) {
            pTurn->mUnknown4 -= 1.0f;
            p->mMotion.mFacing += pTurn->mUnknown0;
            p->mpUnknown800[pTurn->mUnknown8].mUnknownC += pTurn->mUnknown0;
        }
        break;
    }
    return 0;
}

extern "C" void fn_80106A60(Object_80039F5C *p) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
    Object_80137ABC *pBall = fn_80137ABC(pBlock->mUnknown64);
    Object_80039F5C *pCarrier;
    Vector_80039F5C pos;
    Vector_80039F5C landing;
    Point_8017886C delta;
    int heading;
    int angle;
    int diff;

    fn_80137D58(pBall, &pos);
    fn_80138064(pBall, &landing);
    fn_80227690(&delta, &landing, &pos);
    heading = fn_801CFE40(delta.mY, delta.mX);
    pCarrier = fn_80137B88(pBall);
    if (pCarrier != 0) {
        fn_80227690(&delta, &landing, &pCarrier->mMotion.mPos);
        if (fn_802270A4(&delta) > 2.0f) {
            angle = fn_801CFE40(delta.mY, delta.mX);
            diff = fn_801CFFD0(heading, angle);
            if (diff <= 0x1FFFFF) {
                pBlock->mUnknown24 = 0;
            } else if (diff > 0x600000) {
                pBlock->mUnknown24 = 1;
            } else if (((heading - angle) & 0xFFFFFF) <= 0x7FFFFF) {
                pBlock->mUnknown24 = 2;
            } else {
                pBlock->mUnknown24 = 3;
            }
        } else {
            pBlock->mUnknown24 = 4;
        }
    } else {
        pBlock->mUnknown24 = 1;
    }
    fn_80227690(&delta, &landing, &p->mMotion.mPos);
    if (fn_802270A4(&delta) > 2.0f) {
        angle = fn_801CFE40(delta.mY, delta.mX);
        diff = fn_801CFFD0(heading, angle);
        if (diff <= 0x1FFFFF) {
            pBlock->mUnknown20 = 0;
        } else if (diff > 0x600000) {
            pBlock->mUnknown20 = 1;
        } else if (((heading - angle) & 0xFFFFFF) <= 0x7FFFFF) {
            pBlock->mUnknown20 = 2;
        } else {
            pBlock->mUnknown20 = 3;
        }
    } else {
        pBlock->mUnknown20 = 4;
    }
}

extern "C" void fn_80106C24(Object_80039F5C *p, Block_800F4A74 *pBlock) {
    Object_80137ABC *pBall = fn_80137ABC(pBlock->mUnknown64);
    Object_80039F5C *pOther = fn_80137B88(pBall);
    int result = pBlock->mUnknown49;
    Vector_80039F5C start;
    Vector_80039F5C target;
    Vector_80039F5C velocity;
    Point_8017886C delta;
    Point_8017886C apart;
    Point_8017886C ahead;
    float ballTime;
    float otherTime;
    float time;
    float distance = 0.0f;

    fn_80138064(pBall, &start);
    fn_80137D58(pBall, &target);
    fn_80137EC4(pBall, &velocity);
    fn_80227690(&delta, &start, &target);
    ballTime = fn_802270A4(&delta) / fn_802270A4(&velocity);
    if (pOther != 0) {
        fn_80227690(&delta, &start, &pOther->mMotion.mPos);
        otherTime = fn_802270A4(&delta)
            / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (pOther->mRatings[4] / 255.0f) + lbl_803ED6CC));
        fn_80227690(&delta, &start, &p->mMotion.mPos);
        time = fn_802270A4(&delta) / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        distance = fn_802270A4(&delta);
        fn_80227690(&apart, &p->mMotion.mPos, &pOther->mMotion.mPos);
        fn_80227690(&ahead, &target, &pOther->mMotion.mPos);
        if (pOther->mpState->mId == 28 && fn_80137B40() != pOther) {
            Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

            if (pPass->mUnknown0 < pPass->mUnknown16) {
                otherTime = pPass->mUnknown16 - pPass->mUnknown0;
                fn_80227690(&delta, &pPass->mUnknown4, &target);
                ballTime = fn_802270A4(&delta) / fn_802270A4(&velocity);
                fn_80227690(&delta, &pPass->mUnknown4, &p->mMotion.mPos);
                time = fn_802270A4(&delta)
                    / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
            }
        }
        switch (pBlock->mUnknown20) {
        case 0:
            if (ballTime > time - 5.0f) {
                switch (pBlock->mUnknown24) {
                case 0:
                    if (time < otherTime) {
                        if ((time > 20.0f
                             && fn_801CFFD0(fn_801CFE40(ahead.mY, ahead.mX), fn_801CFE40(apart.mY, apart.mX)) <= 0x71C71B)
                            || (fn_801CFFD0(pOther->mMotion.mUnknown32, 0) <= 0x11C71B
                                && p->mMotion.mPos.mX > pOther->mMotion.mPos.mX)
                            || (fn_801CFFD0(pOther->mMotion.mUnknown32, 0x800000) <= 0x11C71B
                                && p->mMotion.mPos.mX < pOther->mMotion.mPos.mX)
                            || p->mMotion.mPos.mY < pOther->mMotion.mPos.mY) {
                            result = 2;
                        } else {
                            result = 3;
                        }
                    } else if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.5f || pBlock->mUnknown49 == 3) {
                        result = 3;
                    } else {
                        result = 2;
                    }
                    break;
                case 2:
                case 3:
                    result = 0;
                    if (pBlock->mUnknown54 == 1) {
                        result = 3;
                    }
                    break;
                case 1:
                case 4:
                    result = 3;
                    if (pBlock->mUnknown56 <= 79) {
                        result = 0;
                    }
                    break;
                }
            } else {
                if (time < otherTime && pBlock->mUnknown51 != 1 && pOther->mpState->mId != 28) {
                    result = 0;
                } else if (pOther->mpState->mId == 28 && (pBlock->mUnknown50 == 3 || pBlock->mUnknown49 == 3)) {
                    result = 3;
                } else if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.5f || pBlock->mUnknown49 == 3) {
                    result = 3;
                } else {
                    result = 2;
                }
            }
            break;
        case 1:
            switch (pBlock->mUnknown24) {
            case 0:
            case 4:
                result = 3;
                break;
            case 2:
            case 3:
                result = 3;
                if (time < otherTime && pBlock->mUnknown54 == 0) {
                    result = 0;
                }
                break;
            case 1:
                result = 3;
                if (time < otherTime && pBlock->mUnknown54 == 0) {
                    result = 0;
                }
                break;
            }
            break;
        case 4:
            switch (pBlock->mUnknown24) {
            case 0:
                result = 3;
                break;
            case 1:
                result = 0;
                break;
            case 2:
            case 3:
                result = 0;
                if (pBlock->mUnknown54 != 0) {
                    result = 3;
                }
                break;
            case 4:
                result = 2;
                break;
            }
            break;
        case 2:
        case 3:
            switch (pBlock->mUnknown24) {
            case 0:
                {
                    int angle = fn_801CFE40(velocity.mY, velocity.mX);

                    if ((fn_801CFFD0(angle, pOther->mMotion.mUnknown32) <= 0x3FFFFF
                         && fn_801CFFD0(angle, p->mMotion.mUnknown32) > 0x400000 && distance > 2.0f)
                        || (pBlock->mUnknown49 == 0 && velocity.mZ < 0.0f)) {
                        result = pOther->mMotion.mPos.mY >= p->mMotion.mPos.mY ? 2 : 0;
                    } else {
                        result = 3;
                        if (time < ballTime && pBlock->mUnknown56 <= 49) {
                            result = 2;
                        }
                    }
                }
                break;
            case 2:
            case 3:
                if (ballTime > time - 5.0f || distance < 5.0f) {
                    if (pBlock->mUnknown24 == pBlock->mUnknown20) {
                        if (pBlock->mUnknown54 == 0) {
                            result = 2;
                        } else {
                            result = 3;
                        }
                    } else {
                        result = 3;
                        if (time < otherTime) {
                            result = 2;
                        }
                    }
                } else {
                    result = 1;
                }
                break;
            case 4:
                result = 3;
                break;
            case 1:
                result = 3;
                if (time < otherTime) {
                    result = 0;
                }
                break;
            }
            break;
        }
    }
    if (pOther != 0 && result == 3) {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *pMate = fn_80039F5C(p->mIdBytes[2], i);

            if (pMate != p) {
                Point_8017886C gap;
                Block_800F4A74 *pMateBlock;

                fn_80227690(&gap, &pOther->mMotion.mPos, &pMate->mMotion.mPos);
                pMateBlock = (Block_800F4A74 *)&pMate->mUnknown336;
                if (pMateBlock->mUnknown49 == 3
                    && pMate->mMotion.mPos.mY > p->mMotion.mPos.mY && fn_802270A4(&gap) < 4.5f) {
                    result = 2;
                    break;
                }
            }
        }
    }
    if (pOther != 0 && result == 2 && p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *pMate = fn_80039F5C(p->mIdBytes[2], i);
            Object_80039F5C *pMark = fn_800FB9D4(pOther);

            if (pMate != p) {
                Point_8017886C gap;
                Block_800F4A74 *pMateBlock;

                fn_80227690(&gap, &pOther->mMotion.mPos, &pMate->mMotion.mPos);
                pMateBlock = (Block_800F4A74 *)&pMate->mUnknown336;
                if (pMateBlock->mUnknown49 == 2 && pMate->mMotion.mPos.mY < p->mMotion.mPos.mY
                    && fn_802270A4(&gap) < 3.5f) {
                    result = 3;
                    break;
                }
                if (pMark == pMate && pMate->mMotion.mPos.mY < p->mMotion.mPos.mY && fn_802270A4(&gap) < 3.5f) {
                    result = 3;
                    break;
                }
            }
        }
    }
    if (pOther != 0 && otherTime > ballTime + 5.0f) {
        result = 0;
    }
    if (result != pBlock->mUnknown49) {
        pBlock->mUnknown50 = pBlock->mUnknown49;
        pBlock->mUnknown49 = result;
    }
}
