#include "engine/animchan.h"
#include "game/fn_801248D4.h"
#include "game/AnimChanStartAnim.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/PlayBookTeam.h"
#include "game/State_803EB098.h"
#include "game/AudmonEvent.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/Ball.h"
#include "game/PlayBookDb.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/PlaySet.h"
#include "game/PlayBookGetPlay.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"
#include "game/Block_801BE60C.h"

/* View of the block at player +336 as the animation callbacks use it. */
struct Block_8010BC90 {
    unsigned char mUnknown0;
    signed char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    char mUnknown4[16];
    int mUnknown20;
    unsigned short mUnknown24;
};

/* Record that fn_8010B738 and fn_8011067C read through each table entry.
   Partial layout. */
struct Record_8010B738 {
    char mUnknown0[4];
    Key_80110630 mUnknown4;
    unsigned char mUnknown7;
    char mUnknown8[4];
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
    float mUnknown24;
};

struct Entry_8010B738 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Record_8010B738 *mpRecord;
};

/* Counted table of 8-byte entries starting at +4. */
struct Table_8010B738 {
    unsigned short mCount;
    char mUnknown2[2];
    Entry_8010B738 mEntries[1];
};

extern "C" {
void fn_800A3B58(Object_80039F5C *p, int a, int b);
void fn_800F053C(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);
unsigned char fn_8010B738(Object_80039F5C *p, Table_8010B738 *pTable);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, unsigned char a, unsigned char count, int angle, float *pOut, int b);
int fn_801486A0(void);
void PossReleaseBall(Object_80039F5C *p);
float fn_80178A08(void);
float fn_80178A44(void);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
extern unsigned char lbl_802DABBC[];
}

extern "C" int fn_8010B224(Object_80039F5C *p) {
    int result = 1;

    if (fn_801486A0() == 0) {
        result = 0;
    }
    if (p->mFlags & 0x800) {
        result = 0;
    }
    if (p->mpState->mId == 10 || p->mpState->mId == 50) {
        result = 0;
    }
    switch (fn_801BE648(p->mpUnknown792)) {
    case 155:
    case 185:
    case 206:
        result = 0;
        break;
    }
    if (BallGetCurrentHolder() != p) {
        int facing = p->mMotion.mFacing;
        Point_8017886C ahead;

        ahead.mX = fn_801CFB94(facing) * 5.0f + p->mMotion.mPos.mX;
        ahead.mY = fn_801CFB18(facing) * 5.0f + p->mMotion.mPos.mY;
        if (fabsf(ahead.mX) > fn_80178A08() || fabsf(ahead.mY) > fn_80178A44()) {
            result = 0;
        }
        if (result) {
            unsigned char team;

            for (team = 0; team <= 1; team++) {
                float distance;

                fn_801245DC(p, team, 0, fn_80178D18(team), 0x400000, &distance, 0);
                if (distance < 2.0f) {
                    result = 0;
                }
            }
        }
    }
    return result;
}

extern "C" unsigned char fn_8010B87C(Object_80039F5C *p, Object_80039F5C *pOther) {
    unsigned char result = 0;

    if (pOther != 0 && p != 0 && pOther != p) {
        Point_8017886C delta;
        int angle;

        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        if (fn_802270A4(&delta) <= 5.0f) {
            result = MathAngleDiff(angle, p->mMotion.mFacing) <= 0xE38E2;
        }
    }
    return result;
}

extern "C" int fn_8010BA90(Object_80039F5C *p) {
    Block_8010BC90 *pBlock = (Block_8010BC90 *)&p->mUnknown336;
    Message_800F01CC message;

    if (pBlock->mUnknown0) {
        p->mFlags &= ~4;
        memset(&message, 0, 4);
        message.mId = 62;
        message.mUnknown1[0] = 0;
        message.mUnknown1[1] = 0;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (pBlock->mUnknown1 > 0) {
        pBlock->mUnknown1--;
    } else {
        if (fn_801BE648(p->mpUnknown792) != 206) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 206, 1.0f, p);
            if (fn_802372EC(0, 10) <= 4) {
                switch (pBlock->mUnknown2) {
                case 1:
                case 2:
                    fn_800A3B58(p, 9, 0);
                    break;
                case 3:
                case 4:
                    fn_800A3B58(p, 6, 0);
                    break;
                }
            }
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            memset(&message, 0, 4);
            message.mId = 62;
            message.mUnknown1[0] = 0;
            message.mUnknown1[1] = 0;
            fn_800F053C(0, p->mpState, &message, p);
            if (pBlock->mUnknown3 != 255) {
                lbl_802DABBC[pBlock->mUnknown3] = 0;
            }
            return 1;
        }
        if (p->mFlags & 0x1000) {
            if (BallGetCurrentHolder() == p) {
                PossReleaseBall(p);
            }
            p->mFlags &= ~0x1000;
        }
    }
    return 0;
}

extern "C" int fn_8010BC90(Table_8010B738 *pTable, unsigned short key, void *pData, AnimChannel_t *pEntries,
                           Object_80039F5C *p, unsigned int mode) {
    Block_801BE60C *pRecord = fn_801BE60C(p->mpUnknown792, key);
    Block_8010BC90 *pBlock = (Block_8010BC90 *)&p->mUnknown336;

    switch (mode) {
    case 0: {
        unsigned char index = fn_8010B738(p, pTable);

        if (index != 255) {
            pBlock->mUnknown3 = index;
            pRecord->mUnknown0Word = AnimChanStartAnim(pData, pEntries, pTable->mEntries[index].mUnknown0,
                                                 pTable->mEntries[index].mUnknown2, key, p, 1.0f);
            lbl_802DABBC[index] = 1;
        } else {
            pBlock->mUnknown0 = 1;
        }
        break;
    }
    case 1:
    case 3:
        break;
    }
    return 0;
}

extern "C" {
int fn_800A2178(void);
int fn_8010B224(Object_80039F5C *p);
int fn_801485D4(void);
int TutorialIsActive(void);
unsigned char TutorialIsStepDone(void);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80237260(int stream);
extern float lbl_802DAB74[];
}

extern "C" int fn_8010BD58(Object_80039F5C *p) {
    int result = 0;

    if (fn_8010B224(p)) {
        Vector_80039F5C toBall;
        float dist;
        float chance;
        float limit;
        int index;

        BallGetPosition(BallGetCurrent(), &toBall);
        fn_80227690(&toBall, &toBall, &p->mMotion.mPos);
        dist = fn_802270A4(&toBall);
        chance = 1.2f;
        chance -= dist * 0.15f;
        index = fn_800A2178();
        limit = lbl_802DAB74[index];
        if (TutorialIsActive() && !fn_801485D4()) {
            if (TutorialIsStepDone()) {
                limit = 1.0f;
            } else {
                limit = 0.75f;
            }
        }
        if (chance < limit) {
            chance = limit;
        }
        if (fn_80237260(0) < chance) {
            result = 1;
        }
    }
    return result;
}

/* View of the block at player +336 as fn_8010BED4 sets it up and fn_8010BF5C
   updates it. */
struct State_8010BF5C {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    int mUnknown12;
    float mUnknown16;
    float mUnknown20;
    float mUnknown24;
    float mUnknown28;
    float mUnknown32;
    int mUnknown36;
    Point_8017886C mUnknown40;
    short mUnknown48;
    char mUnknown50[2];
    unsigned int mUnknown52;
    unsigned short mUnknown56;
};

extern "C" {
float PlayTrackGetPlayIdRate(void);
float PlayTrackGetResult5Rate(void);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
int fn_80177C38(void);
int BallStateGet(Ball_t *pBall, int a);
int fn_8011F1CC(void);
int MathAngleDiff(int a, int b);
int fn_800DC21C(Object_80039F5C *p);
int fn_800A5C04(Object_80039F5C *p, int a, int b);
int fn_8009F7A4(Object_80039F5C *p, Object_80039F5C **ppOut);
int fn_8009E180(Object_80039F5C *p);
int fn_8009F0B8(Object_80039F5C *p, int angle);
float fn_80178A2C(void);
extern float lbl_803EAF24;
extern float lbl_803EAF28;
extern float lbl_803EAF2C;
extern float lbl_803EAF34;
extern unsigned int lbl_803EAF38;
extern float lbl_803EAF3C;
extern float lbl_803EAF40;
extern float lbl_803EAF44;
}

#define MIN(a, b) ((a) > (b) ? (b) : (a))

/* Update handler of the state fn_8010BED4 enters (player state table at
   0x802DBA78): counts frames, rerolls the +48 timer from rating 8 and, when it
   expires, picks a spot beside the ball carrier (offset away from a team-mate
   in state 85, clamped to the field) and the heading and speed towards it.
   Sends message 2 (give up) or 24 and returns 1, else posts the move. */
extern "C" int fn_8010BF5C(Object_80039F5C *p)
{
    Message_800F01CC message;
    State_8010BF5C *pState = (State_8010BF5C *)&p->mUnknown336;
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_80039F5C *pCarrier;
    Point_8017886C ball;
    Point_8017886C target;
    Point_8017886C delta;
    Vector_80039F5C ballPos;
    float side = 0.0f;
    float reach = pState->mUnknown16;
    int expired = 0;
    int result = 0;
    int deep = 0;

    ball = fn_80177FE0();
    PlayTrackGetResult5Rate();
    fn_8010A2DC(p, 0, -1);
    pState->mUnknown52++;
    pCarrier = BallGetCurrentHolder();
    BallGetPosition(BallGetCurrent(), &ballPos);
    pState->mUnknown48 = (signed char)(pState->mUnknown48 - 1);
    if (pState->mUnknown48 < 0) {
        int rating = 255 - p->mRatings[8];

        if (rating < 0) {
            rating = 0;
        }
        pState->mUnknown48 = (signed char)(pState->mUnknown48 + 2 + fn_802372EC(0, (unsigned int)rating >> 5));
        if (pCarrier && fn_800B65A0(p->mIdBytes[2]) != 255
            && fn_800B65A0(pCarrier->mIdBytes[2]) == 255 && !fn_80177C38()) {
            pState->mUnknown48 -= (short)MIN((float)pState->mUnknown48,
                                             (float)pState->mUnknown48 * PlayTrackGetPlayIdRate());
            if (fn_8011F1CC() && (pCarrier->mFlags & 0x8000)) {
                pState->mUnknown48 -= (short)MIN((float)pState->mUnknown48,
                                                 (float)pState->mUnknown48 * PlayTrackGetResult5Rate());
            }
        }
        expired = 1;
    }
    if (!(p->mFlags & 0x4000) && expired) {
        if (pCarrier == 0 && BallStateGet(BallGetCurrent(), 0) == 4) {
            pCarrier = BallGetCurrentLastHolder();
        }
        if (pCarrier != 0) {
            unsigned int i;
            unsigned int count = fn_80178D18(p->mIdBytes[2]);
            const float margin = 2.0f;

            for (i = 0; i < count; i++) {
                if (i != (p->mId >> 16 & 0xFF)) {
                    Object_80039F5C *pOther = PlyrGet(p->mId >> 8 & 0xFF, i);

                    if (pOther->mpState->mId == 85) {
                        if (pOther->mMotion.mPos.mX > p->mMotion.mPos.mX) {
                            side = -lbl_803EAF44;
                        } else {
                            side = lbl_803EAF44;
                        }
                        if ((pCarrier->mMotion.mPos.mX > ball.mX && p->mMotion.mPos.mX > pOther->mMotion.mPos.mX)
                            || (pCarrier->mMotion.mPos.mX < ball.mX
                                && p->mMotion.mPos.mX < pOther->mMotion.mPos.mX)) {
                            if (pCarrier->mFlags & 0x8000) {
                                memset(&message, 0, 4);
                                message.mId = 2;
                                message.mUnknown1[0] = 1;
                                fn_800F053C(0, p->mpState, &message, p);
                                return 1;
                            }
                        }
                    }
                }
            }
            if (pState->mUnknown52 > pState->mUnknown56 && pState->mUnknown56 != 0) {
                memset(&message, 0, 4);
                message.mId = 2;
                message.mUnknown1[0] = 1;
                fn_800F053C(0, p->mpState, &message, p);
                return 1;
            }
            if (((pCarrier->mFlags & 0x8000) && pState->mUnknown52 > lbl_803EAF38
                 && ball.mY - pCarrier->mMotion.mPos.mY < reach * lbl_803EAF3C)
                || ((float)pState->mUnknown52 > lbl_803EAF34 && (pCarrier->mFlags & 0x8000)
                    && ball.mY - pCarrier->mMotion.mPos.mY < reach)) {
                memset(&message, 0, 4);
                message.mId = 2;
                message.mUnknown1[0] = 1;
                fn_800F053C(0, p->mpState, &message, p);
                return 1;
            }
            target.mX = pCarrier->mMotion.mPos.mX + side;
            target.mX = target.mX < margin - fn_80178A08() ? margin - fn_80178A08()
                : (target.mX > fn_80178A08() - margin ? fn_80178A08() - margin : target.mX);
            target.mY = ball.mY + lbl_803EAF2C;
            target.mY = MIN(target.mY, fn_80178A2C() + margin);
            fn_80227690(&delta, &target, &pMotion->mPos);
            {
                float dist = fn_802270A4(&delta);
                float dx = fabsf(pMotion->mPos.mX - target.mX);
                float near = lbl_803EAF24;
                float wide = lbl_803EAF28;
                int angle;

                if (pMotion->mUnknown28 != 0.0f) {
                    near *= 0.5f;
                    wide *= 0.5f;
                }
                pState->mUnknown28 = dx;
                pState->mUnknown40 = target;
                pState->mUnknown32 = wide;
                pState->mUnknown20 = dist;
                pState->mUnknown24 = near;
                pState->mUnknown36 = pCarrier->mMotion.mUnknown32;
                angle = MathAngleDiff(pCarrier->mMotion.mUnknown32, 0x400000);
                if ((dx > wide && (angle > 0x200000 && angle < 0x600000) && fn_800DC21C(pCarrier))
                    || dx > wide + wide || (dx > 0.5f && pState->mUnknown4 == 1.0f)) {
                    pState->mUnknown8 = delta.Heading() & 0xFFFFFF;
                    pState->mUnknown12 = delta.Heading();
                    pState->mUnknown4 = 1.0f;
                } else if (dist > near || dx > wide) {
                    pState->mUnknown8 = delta.Heading() & 0xFFFFFF;
                    pState->mUnknown12 = 0xC00000;
                    pState->mUnknown4 = 0.9f;
                } else {
                    pState->mUnknown8 = 0xC00000;
                    pState->mUnknown4 = 0.0f;
                    pState->mUnknown12 = 0xC00000;
                }
            }
        }
    }
    if (fn_800A5C04(p, pState->mUnknown8, pState->mUnknown12)) {
        return 0;
    }
    if (!(p->mFlags & 0x4000)) {
        if (expired) {
            int kind;

            result = fn_8009F7A4(p, 0) == 1;
            kind = fn_8009E180(p);
            if (kind > 2) {
                switch (kind) {
                default:
                    if (fn_802372EC(0, 255) < (unsigned short)(p->mRatings[8] / 2)) {
                        memset(&message, 0, 4);
                        message.mId = 2;
                        message.mUnknown1[0] = 1;
                        fn_800F053C(0, p->mpState, &message, p);
                        return 1;
                    }
                    break;
                case 4: {
                    int go = 0;
                    Object_80039F5C *pTarget = BallGetCurrentTarget();

                    if (pTarget != 0) {
                        if (fabsf(pTarget->mMotion.mPos.mX - p->mMotion.mPos.mX) < 12.0f) {
                            Ball_t *pBall = BallGetCurrent();
                            Vector_80039F5C landing;

                            if (BallGetLandingPoint(pBall, &landing)) {
                                if (fabsf(landing.mX - fn_80177FE0().mX) > 8.0f) {
                                    go = fn_802372EC(0, 32) < (unsigned int)((p->mRatings[8] >> 5) + 8);
                                } else {
                                    Vector_80039F5C velocity;

                                    BallGetVelocity(pBall, &velocity);
                                    if ((landing.mY < p->mMotion.mPos.mY + 12.0f
                                         && fn_802372EC(0, 100) < (unsigned int)((p->mRatings[8] >> 5) + 8))
                                        || velocity.mZ < 0.0f) {
                                        go = 1;
                                    }
                                }
                            }
                        }
                        if (ballPos.mY > p->mMotion.mPos.mY + lbl_803EAF40) {
                            go = 1;
                            deep = 1;
                        }
                    } else {
                        go = 1;
                    }
                    if (go == 1 && (fn_8009F0B8(p, 0x2AAAAA) || deep)) {
                        memset(&message, 0, 4);
                        message.mId = 24;
                        message.mUnknown1[0] = 2;
                        fn_800F053C(0, p->mpState, &message, p);
                        return 1;
                    }
                    break;
                }
                case 6:
                    memset(&message, 0, 4);
                    message.mId = 2;
                    message.mUnknown1[0] = 1;
                    fn_800F053C(0, p->mpState, &message, p);
                    return 1;
                }
            }
        }
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pState->mUnknown8;
        p->mUnknown512.mUnknown8 = pState->mUnknown12;
        p->mUnknown512.mUnknown0 = pState->mUnknown4;
        if (pState->mUnknown4 == 1.0f) {
            p->mUnknown512.mUnknown15 = 1;
        }
    }
    return result;
}

/* View of the block at player +336 as fn_8010CB58 runs its states. */
struct Block_8010CB58 {
    char mUnknown0[12];
    float mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    char mUnknown21[3];
    int mUnknown24;
};

extern "C" {
void fn_800B8344(Object_80039F5C *p);
int fn_800FD580(Object_80039F5C *p);
void fn_800F053C(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_8009BD60(Object_80039F5C *p);
int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float e, void *pRecord);
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);
}

extern "C" int fn_8010C8F8(Object_80039F5C *p) {
    int result = 0;
    float range = 1.0f;
    Ball_t *pBall;
    Vector_80039F5C pos;
    Point_8017886C delta;

    BallGetCurrentHolder();
    pBall = BallFindTargeting(p);
    if (pBall == 0) {
        pBall = BallGetCurrent();
        range = 1.5f;
    }
    BallGetPosition(pBall, &pos);
    fn_80227690(&delta, &pos, &p->mMotion.mPos);
    if (fn_802270A4(&delta) < range) {
        result = 1;
    }
    return result;
}

extern "C" void fn_8010C98C(Object_80039F5C *p) {
    int pick = 1;
    Ball_t *pBall;
    Vector_80039F5C pos;
    int index;

    pBall = BallFindTargeting(p);
    if (pBall == 0) {
        pBall = BallGetCurrent();
    }
    BallGetPosition(pBall, &pos);
    fn_8009BD60(p);
    index = fn_800F06F4(0, p->mpState, 26, 0xFFFF);
    if (index != 0xFFFF) {
        switch (p->mpState[index].mUnknown2) {
        case 2:
        case 3:
            p->mUnknown1008.mUnknown0 = 1;
            pick = 0;
            break;
        case 4:
        case 5:
            p->mUnknown1008.mUnknown0 = 2;
            pick = 0;
            break;
        default:
            pick = 1;
            break;
        }
    }
    if (pick) {
        if (fn_8011F1A4()) {
            if (fn_8011F1A4() && (fn_8011F4C8() & 1)) {
                p->mUnknown1008.mUnknown0 = 1;
            } else {
                p->mUnknown1008.mUnknown0 = 2;
            }
        } else {
            Point_8017886C delta;

            fn_80227690(&delta, &pos, &p->mMotion.mPos);
            if (((fn_801CFE40(delta.mY, delta.mX) - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                p->mUnknown1008.mUnknown0 = 1;
            } else {
                p->mUnknown1008.mUnknown0 = 2;
            }
        }
    }
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 78, 1.0f, p);
    p->mUnknown512.mUnknown14 = 0;
}

extern "C" int fn_8010CB58(Object_80039F5C *p) {
    int result = 0;
    Block_8010CB58 *pBlock = (Block_8010CB58 *)&p->mUnknown336;
    int animation;

    fn_800B8344(p);
    animation = fn_801BE648(p->mpUnknown792);
    switch (pBlock->mUnknown20) {
    case 0:
        if ((unsigned int)(animation - 30) <= 1 || animation == 202 || animation == 200) {
            p->mUnknown512.mUnknown14 = 0;
            pBlock->mUnknown20 = 1;
        } else {
            Object_80039F5C *pCarrier;

            result = fn_800FD580(p);
            pCarrier = BallGetCurrentHolder();
            if (pCarrier != 0 && pCarrier->mpState->mId == 18 && (p->mFlags & 0x4000)) {
                result = 1;
            }
            if (fn_8010C8F8(p)) {
                fn_8010C98C(p);
                pBlock->mUnknown20 = 1;
            }
        }
        break;
    case 1:
        if (BallGetCurrentHolder() == p && animation == 74) {
            pBlock->mUnknown20 = 2;
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            pBlock->mUnknown24 = 20;
            pBlock->mUnknown20 = 2;
        } else if (!((unsigned int)(animation - 30) <= 1 || animation == 202 || animation == 200)) {
            if (animation == 78) {
                p->mUnknown512.mUnknown14 = 0;
            } else {
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
            }
        }
        break;
    case 2: {
        int has18 = fn_800F06F4(0, p->mpState, 18, 0xFFFF) != 0xFFFF;
        int has26 = fn_800F06F4(0, p->mpState, 26, 0xFFFF) != 0xFFFF;
        int has25 = fn_800F06F4(0, p->mpState, 25, 0xFFFF) != 0xFFFF;

        if (p == BallGetCurrentHolder() && !has18 && !has26 && !has25) {
            Message_800F01CC message;

            memset(&message, 0, 4);
            message.mId = 1;
            fn_800F053C(0, p->mpState, &message, p);
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown0 = 0.72f;
        } else if (!has18) {
            if (--pBlock->mUnknown24 < 0) {
                result = 1;
            } else {
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
            }
        } else {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
            p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
            p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
            result = 1;
        }
        break;
    }
    }
    return result;
}

extern "C" {
extern float lbl_803EAF48;
extern float lbl_803EAF4C;
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void StyleTrackerFinishRun(void);
}

/* Posts message 68 to the player's queue with the facing and a 0-255
   effort level taken from the move speed (scaled by rating 4 for a player
   whose id byte 3 is 1); kind 11 also finishes the running-style run. */
extern "C" void fn_8010CEB8(Object_80039F5C *p, int kind)
{
    Message_800F01CC message;
    float speed = p->mUnknown528.mUnknown0;
    float level;

    if (p->mIdBytes[3] == 1) {
        float scale = speed * 0.0052287583f;
        speed = scale * p->mRatings[4];
    }
    level = speed < lbl_803EAF48 ? lbl_803EAF48 : (speed > lbl_803EAF4C ? lbl_803EAF4C : speed);
    level *= 255.0f;
    message.mId = 68;
    message.mUnknown1[0] = 160;
    message.mUnknown1[1] = p->mMotion.mFacing >> 17;
    message.mUnknown1[2] = level < 0.0f ? 0 : (unsigned char)(level > 255.0f ? 255.0f : level);
    fn_800F00D4(0, p->mpState, &message, p);
    if (kind == 11) {
        StyleTrackerFinishRun();
    }
}
