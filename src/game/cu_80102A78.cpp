#include "game/fn_801248D4.h"
#include "game/fn_801BA2A8.h"
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

struct Entry_801018B4 {
    char mUnknown0[4];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    int mUnknown8;
    int mUnknown12;
    unsigned short mUnknown16;
    char mUnknown18[2];
    float mUnknown20;
    float mUnknown24;
};

/* 8-byte item of List_801018B4: two halfwords for fn_801BA2A8 and the
   entry pointer. */
struct Item_801018B4 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Entry_801018B4 *mpEntry;
};

struct List_801018B4 {
    unsigned short mCount;
    char mUnknown2[2];
    Item_801018B4 mItems[1];
};
extern "C" {
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
int fn_80178320(void);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_801486A0(void);
extern float lbl_803ECB08;
float fn_80237260(int stream);
void fn_800A5A8C(int a, Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
float fn_80178A08(void);
float fn_80178A44(void);
void fn_800A8954(int event, int team, Object_80039F5C *p);
void fn_801BD81C(void *p, float value);
float fn_801CFFA0(float value);
extern float lbl_803EA2C4;
void fn_8022732C(void *pPoint, void *pVelocity, float scale);
float fn_801CFB94(int angle);
}

struct State_80102664 {
    unsigned char mUnknown0;
    char mUnknown1[2];
    unsigned char mUnknown3;
};

extern "C" void fn_80156C78(int a, int b);
extern "C" {
void fn_80148154(void);
void fn_801483C8(void);
}

struct State_80102A78 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    float mUnknown20;
    float mUnknown24;
    float mUnknown28;
    float mUnknown32;
    unsigned char mUnknown36;
};
extern "C" {
void fn_800D4EC0(int value);
int fn_80100024(Object_80039F5C *p, int angle, int mode);
void fn_801016A4(Object_80039F5C *p, unsigned char *pKind, Point_8017886C *pPoint, unsigned int *pAngle);
void fn_8010176C(Object_80039F5C *p, int mode, Point_8017886C *pPoint);
float fn_801BD6D4(Block_801BD6D4 *p);
}

extern float lbl_803EAEC4;
extern "C" {
void fn_800B260C(short value);
void fn_800B1584(int a, const float *pPos);
void fn_800D7534(int team);
void fn_801783D0(int bit, int on);
void fn_80099568(int kind);
void fn_8013AD04(Object_80137ABC *pBall, Vector_80039F5C *pVelocity, int mode, float spin, float rate);
void fn_80101064(Object_80039F5C *p);
}

struct Type_803EA368;

extern Type_803EA368 *lbl_803EA368;

extern "C" void fn_800310C0(Type_803EA368 *p, int id, Object_80039F5C *pObject, Vector_80039F5C *pPos, int *pFacing);
extern "C" {
Object_80039F5C *fn_8003A130(Vector_80039F5C *pPos, int a, int team);
void fn_80076D5C(int id);
int fn_800A7F1C(int team);
void fn_8010016C(Object_80039F5C *pTarget, Vector_80039F5C *pPos, Object_80039F5C *p, float speed);
int fn_80100370(Object_80137ABC *pBall, Object_80039F5C *pTarget, float speed, Vector_80039F5C *pOut);
void fn_80100BF8(Object_80039F5C *p, Vector_80039F5C *pPos, int *pOut, float speed, float a, float b);
void fn_80101130(Object_80039F5C *pTarget, Object_80039F5C *p, short *pCount);
void fn_80103F80(Object_80137ABC *pBall, Vector_80039F5C pos, Vector_80039F5C velocity, float speed, int angle,
                 float ballSpeed, Vector_80039F5C *pOut, Object_80039F5C *p);
void fn_8013AC28(Object_80137ABC *pBall, Vector_80039F5C *pTarget, int mode, float speed, float spin, float side);
void fn_80152068(int index, Vector_80039F5C *pOut);
int fn_80156C8C(unsigned long long mask);
float fn_80103DD8(Object_80039F5C *p, Object_80039F5C *pOther, short *pCount, float scale);
float fn_8016D9F4(Object_80039F5C *p, float a, float b);
void fn_80176838(Object_80039F5C *p);
float fn_80178A2C(void);
void fn_80227248(void *pOut, void *p, float scale);
}

extern float lbl_803EAEC8;

extern float lbl_803EAECC;

extern float lbl_803EAED0;

extern float lbl_803EAED4;

static inline float AddRatingNoise_80102D78(float base, float random, int rating)
{
    return rating <= 255 ? random * (255 - rating) * (1.0f / 255.0f) + base : base;
}

extern "C" void fn_80101AE0(Object_80039F5C *p, float *pOut);

extern "C" unsigned int fn_8011E188(void);

extern float lbl_803EAE8C;

extern float lbl_803EAE90;

extern float lbl_803EAE94;

extern float lbl_803EAE98;

extern float lbl_803EAE9C;

extern float lbl_803EAEB8;


extern "C" float fn_800C49EC(float limit);

extern "C" float fn_800CAAFC(Object_80039F5C *p);

extern "C" float fn_801CFB18(int angle);

extern "C" int fn_801CFDD0(float);

extern "C" int fn_8012CAA4(Object_80039F5C *p);

extern "C" int fn_8012CAAC(Object_80039F5C *p);

extern "C" int fn_8012CB50(Message_800F01CC *pMessage);

extern "C" void fn_8012CB98(int a, int b, int angle, Point_8017886C *pOut);

extern "C" int fn_8012CC04(int a);

extern "C" int fn_8012CC50(Object_80039F5C *p);

extern "C" void fn_8012CD4C(Object_80039F5C *p, Point_8017886C *pOut);

struct State_80104328 {
    Point_8017886C mTarget;
};




extern "C" {
}

extern "C" int fn_801018B4(Object_80039F5C *p, List_801018B4 *pList, int a, int b, int *pOut);

extern "C" int fn_80102A78(List_801018B4 *pList, unsigned short animation, void *pData, Record_800D81C8 *pEntries,
                           Object_80039F5C *p, unsigned int mode)
{
    int delta = 0;
    unsigned int angle = 0;
    int failed = 0;
    State_80102A78 *pState = (State_80102A78 *)fn_801BE60C(p->mpUnknown792, animation);

    switch (mode) {
    case 0: {
        Record_8011F4F8 *pRecord = fn_8011F4F8(((State_80102664 *)&p->mUnknown336)->mUnknown3);
        unsigned char kind = pRecord->mUnknown1D;
        Point_8017886C point;
        int index;
        Entry_801018B4 *pEntry;

        fn_801016A4(p, &kind, &point, &angle);
        fn_8010176C(p, kind, &point);
        index = fn_801018B4(p, pList, 0, angle, &delta);
        if (index == -1) {
            index = 0;
        }
        pEntry = pList->mItems[index].mpEntry;
        if (animation == 178 && fn_80100024(p, angle, pEntry->mUnknown7) == 0) {
            failed = 1;
        }
        if (failed) {
            fn_800D0BF4(p, 0, 0);
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 69, p, 1.0f);
        } else if (index != -1) {
            fn_800D4EC0(pEntry->mUnknown7);
            pState->mUnknown20 = pEntry->mUnknown20;
            pState->mUnknown24 = pEntry->mUnknown24;
            pState->mUnknown28 = pState->mUnknown24 - pState->mUnknown20;
            pState->mUnknown32 = 0.0f;
            pState->mUnknown8 = pEntry->mUnknown12;
            pState->mUnknown16 = p->mMotion.mFacing;
            pState->mUnknown12 = failed;
            pState->mUnknown36 = pRecord->mUnknown1D;
            if (pState->mUnknown28 != 0.0f) {
                delta = (angle - pState->mUnknown8) & 0xFFFFFF;
                if (delta > ((0x1000000 - delta) & 0xFFFFFF)) {
                    delta = -((0x1000000 - delta) & 0xFFFFFF);
                }
                pState->mUnknown4 = (int)(delta / pState->mUnknown28);
                fn_801BE760(p->mpUnknown792, animation, 1);
            } else {
                pState->mUnknown4 = failed;
            }
            pState->mUnknown0 = fn_801BA2A8(pData, pEntries, pList->mItems[index].mUnknown0,
                                            pList->mItems[index].mUnknown2, animation, p, 1.0f);
            fn_801BD81C(&pEntries[pState->mUnknown0].mUnknown4C, fn_801CFFA0(lbl_803EAEC4));
        }
        break;
    }
    case 1:
        break;
    case 2:
        if (fn_801BE648(p->mpUnknown792) == animation) {
            float time = fn_801BD6D4(&p->mpUnknown800[pState->mUnknown0].mUnknown4C);
            float previous = pState->mUnknown32;

            pState->mUnknown32 = time;
            if (time > pState->mUnknown20 && previous < pState->mUnknown24) {
                int step = pState->mUnknown4;

                p->mMotion.mFacing = (p->mMotion.mFacing + step) & 0xFFFFFF;
                p->mpUnknown800[pState->mUnknown0].mUnknownC = (p->mpUnknown800[pState->mUnknown0].mUnknownC + step) & 0xFFFFFF;
            }
        }
        break;
    }
    return 0;
}

extern "C" void fn_80102D78(Object_80039F5C *p)
{
    int result[2] = {0, 0};
    Object_80039F5C *pTarget = 0;
    Object_80137ABC *pBall = fn_80137C48(p);
    Record_8011F4F8 *pRecord = fn_8011F4F8(fn_801374E0(pBall));
    Record_800B15FC *pEvent;
    Vector_80039F5C ball;
    Vector_80039F5C delta;
    Vector_80039F5C velocity;
    Vector_80039F5C target;
    float speed;
    float spin;
    float random;
    int side;

    fn_800A8954(5, p->mIdBytes[2], p);
    fn_80148154();
    fn_801483C8();
    fn_800B260C(0);
    fn_8013791C(pBall, 4, 0);
    pEvent = fn_800B15FC();
    if (fn_80156C8C(0x20000000) == 0) {
        fn_80156C78(42, 1);
    }
    fn_8009BD2C(p, &pEvent->mUnknown0);
    pEvent->mUnknownC = p->mMotion.mPos.mX;
    pEvent->mUnknown10 = p->mMotion.mPos.mY;
    pEvent->mUnknown4 = pRecord->mUnknown1D;
    switch (pRecord->mUnknown1D) {
    case 0:
    case 1:
    case 6:
    case 7:
        pTarget = fn_80039F5C(p->mIdBytes[2], pRecord->mUnknownAByte);
        if (!(p->mFlags & 0x4000)) {
            fn_80101130(pTarget, p, &pRecord->mUnknown8);
        }
        speed = fn_80103DD8(p, pTarget, &pRecord->mUnknown8, pRecord->mUnknown0);
        pEvent->mUnknown8 = (int)pTarget;
        if (fn_800D0B90(p) != 0) {
            fn_80067E3C(40, &p->mMotion.mPos, p->mId, 0, 0, 0);
        }
        break;
    case 8:
        speed = lbl_803EA2C4 * 0.27f;
        pEvent->mUnknown8 = (int)pTarget;
        break;
    default:
        speed = lbl_803EA2C4 * 0.37f;
        pEvent->mUnknown8 = 0;
        break;
    }
    pEvent->mUnknown14 = 5;
    pEvent->mUnknown16 = (int)(speed * 256.0f);
    fn_800B1508();
    spin = fn_80237260(0) * 0.2f;
    spin += p->mMotion.mUnknown28 * 0.1f / lbl_803ECB08;
    spin += p->mUnknown560.mUnknown32 * 0.15f / (lbl_803ECB08 * 100621.1171875f);
    spin += (1.0f - pRecord->mUnknown4) * 0.2f * 2.0f;
    spin += pRecord->mUnknownC;
    random = fn_80237260(0);
    spin = AddRatingNoise_80102D78(spin, random, p->mRatings[6]);
    if (fn_800A7F1C(p->mIdBytes[2]) == 0) {
        spin = lbl_803EAEC8;
    }
    side = -4;
    if (p->mUnknown2913 == 1) {
        side = 4;
    }
    if (fn_800A7F1C(p->mIdBytes[2]) == 2) {
        spin = 0.0f;
        side = (int)(side * 3.0f);
    }
    if (pRecord->mUnknownC > 0.0f) {
        fn_800B1584(56, 0);
        fn_801783D0(23, 1);
    }
    switch (pRecord->mUnknown1D) {
    case 0:
    case 6:
        if (pTarget->mpState->mId == 20) {
            if (pRecord->mUnknown1D == 0) {
                pRecord->mUnknown1D = 1;
            } else {
                pRecord->mUnknown1D = 7;
            }
        }
        /* fall through */
    case 1:
    case 7: {
        Object_800B26B0 *pMotion = &pTarget->mMotion;
        Vector_80039F5C *pPos;
        float limit;
        float distance;
        float ratio;
        float maximum;

        if (pRecord->mUnknown1D == 1 || pRecord->mUnknown1D == 7) {
            fn_80100370(pBall, pTarget, speed, &target);
        } else {
            Vector_80039F5C offset;
            int angle;
            float length;

            if ((int)pTarget->mFlags >= 0) {
                if (pTarget->mpState->mId == 19) {
                    angle = (pTarget->mpState->mUnknown2 << 17) & 0xFE0000;
                } else {
                    angle = pMotion->mUnknown32;
                }
                if (pTarget->mpState->mId == 20) {
                    length = pTarget->mMotion.mUnknown28 >= fn_8016D9F4(pTarget, 0.72f, 1.0f)
                        ? pTarget->mMotion.mUnknown28 : fn_8016D9F4(pTarget, 0.72f, 1.0f);
                } else {
                    length = pTarget->mMotion.mUnknown28;
                }
            } else {
                angle = fn_801CFE40(pRecord->mUnknown18, pRecord->mUnknown14);
                length = fn_802270A4(&pRecord->mUnknown14);
            }
            fn_80227538((Point_8017886C *)&offset, angle, length);
            offset.mZ = 0.0f;
            fn_80103F80(pBall, pMotion->mPos, offset, length, angle, speed, &target, pTarget);
        }
        fn_8010016C(pTarget, &target, p, speed);
        limit = 1.0f - fn_80237260(0) * 2.5f;
        target.mX = target.mX > fn_80178A08() + limit ? fn_80178A08() + limit : target.mX;
        target.mX = target.mX < -(fn_80178A08() + limit) ? -(fn_80178A08() + limit) : target.mX;
        target.mY = target.mY > fn_80178A44() + limit ? fn_80178A44() + limit : target.mY;
        fn_80100BF8(p, &target, result, speed, pRecord->mUnknown0, pRecord->mUnknown4);
        target.mX = target.mX > fn_80178A08() + 3.0f ? fn_80178A08() + 3.0f : target.mX;
        target.mX = target.mX < -(fn_80178A08() + 3.0f) ? -(fn_80178A08() + 3.0f) : target.mX;
        target.mY = target.mY > fn_80178A44() + 2.5f ? fn_80178A44() + 2.5f : target.mY;
        pPos = &p->mMotion.mPos;
        fn_80137D58(pBall, &ball);
        if (fn_800A7F1C(p->mIdBytes[2]) != 2) {
            if (pRecord->mUnknown10 != 0) {
                Point_8017886C offset;

                fn_80227690(&offset, &target, &ball);
                fn_80227248(&offset, &offset, fn_801CFB94(pRecord->mUnknown10));
                fn_80227638(&target, &offset, &ball);
            }
            fn_80227690(&delta, &target, &ball);
            if (fn_802270A4(&delta) < 3.0f) {
                fn_80227690(&delta, &pTarget->mMotion.mPos, pPos);
                fn_80227538((Point_8017886C *)&target, fn_801CFE40(delta.mY, delta.mX), 4.0f);
                fn_80227638(&target, &target, pPos);
            }
        }
        {
            Object_80039F5C *pNearest = fn_8003A130(&pTarget->mMotion.mPos, 0, fn_80178320());

            fn_800310C0(lbl_803EA368, 5, pNearest, &pNearest->mMotion.mPos, &pNearest->mMotion.mFacing);
        }
        fn_800310C0(lbl_803EA368, 18, p, pPos, &p->mMotion.mFacing);
        fn_800310C0(lbl_803EA368, 17, pTarget, &pTarget->mMotion.mPos, &pTarget->mMotion.mFacing);
        fn_80099568(1);
        if (fn_800A7F1C(p->mIdBytes[2]) == 0) {
            speed *= lbl_803EAECC;
        }
        if (p->mRatings[6] <= lbl_803EAED0) {
            speed *= 1.0f - lbl_803EAED4 * ((lbl_803EAED0 - p->mRatings[6]) / lbl_803EAED0);
        }
        distance = fn_8022781C(&target, pPos);
        ratio = distance / speed;
        maximum = (pTarget->mFlags & 0x4000) ? 40.0f : 30.0f;
        if (ratio < maximum) {
            speed = distance / maximum;
            if (speed < 0.18f) {
                speed = 0.18f;
            }
        }
        target.mX = target.mX < 1.0f - fn_80178A08() ? 1.0f - fn_80178A08()
            : (target.mX > fn_80178A08() - 1.0f ? fn_80178A08() - 1.0f : target.mX);
        fn_8013AC28(pBall, &target, 1, speed, spin, side);
        fn_80137BC0(pBall, pTarget);
        fn_80076D5C(pTarget->mId);
        fn_80137EC4(pBall, &velocity);
        if (velocity.mY < 0.0f) {
            fn_801783D0(1, 1);
        } else {
            fn_801783D0(13, 1);
            fn_801783D0(1, 0);
            fn_800D7534(p->mIdBytes[2]);
        }
        fn_80101064(p);
        break;
    }
    case 3:
        speed = lbl_803EA2C4 * 0.37f;
        if (pRecord->mUnknownAByte != 15) {
            Object_80039F5C *pReceiver = fn_80039F5C(p->mIdBytes[2], pRecord->mUnknownAByte);

            if (pReceiver->mMotion.mPos.mX > fn_80178A08() - 8.0f) {
                target.mX = pReceiver->mMotion.mPos.mX + 14.0f;
                target.mY = pReceiver->mMotion.mPos.mY;
            } else if (pReceiver->mMotion.mPos.mX < 8.0f - fn_80178A08()) {
                target.mX = pReceiver->mMotion.mPos.mX - 14.0f;
                target.mY = pReceiver->mMotion.mPos.mY;
            } else if (pReceiver->mMotion.mPos.mY > fn_80178A2C()) {
                target.mX = pReceiver->mMotion.mPos.mX;
                target.mY = pReceiver->mMotion.mPos.mY + 10.0f;
            } else {
                target.mX = fn_80178A08() + 14.0f;
                target.mY = fn_80177FE0().mY + 10.0f;
            }
        } else {
            target.mX = fn_80178A08() + 14.0f;
            target.mY = fn_80177FE0().mY + 10.0f;
            if (fn_801CFFD0(p->mMotion.mFacing, 0) > 0x400000) {
                target.mX = -target.mX;
            }
        }
        target.mZ = 0.0f;
        fn_80099568(1);
        fn_8013AC28(pBall, &target, 1, speed, spin, side);
        fn_80137BC0(pBall, 0);
        fn_80101064(p);
        fn_80176838(p);
        fn_801783D0(13, 1);
        break;
    case 2:
        target.mX = 0.0f;
        target.mY = 0.02f;
        target.mZ = -0.2f;
        fn_8013AD04(pBall, &target, 1, spin, side);
        break;
    case 8:
        speed = lbl_803EA2C4 * 0.27f;
        if (fn_801486A0() == 1) {
            fn_80152068(fn_801374E0(pBall), &target);
        }
        fn_8013AC28(pBall, &target, 1, speed, spin, side);
        fn_80137BC0(pBall, 0);
        fn_80101064(p);
        fn_801783D0(13, 1);
        break;
    }
    p->mFlags &= ~0x2000;
    pRecord->mUnknownB = 0;
}

extern "C" void fn_801039D8(Object_80039F5C *p)
{
    Object_80039F5C *pTarget = 0;
    Object_80137ABC *pBall = fn_80137C48(p);
    Record_8011F4F8 *pRecord = fn_8011F4F8(fn_801374E0(pBall));
    Record_800B15FC *pEvent;
    Vector_80039F5C velocity;

    fn_80148154();
    fn_801483C8();
    fn_800B260C(0);
    pEvent = fn_800B15FC();
    fn_8009BD2C(p, &pEvent->mUnknown0);
    pEvent->mUnknownC = p->mMotion.mPos.mX;
    pEvent->mUnknown10 = p->mMotion.mPos.mY;
    pEvent->mUnknown4 = pRecord->mUnknown1D;
    switch (pRecord->mUnknown1D) {
    case 0:
    case 1:
    case 6:
    case 7:
        pTarget = fn_80039F5C(p->mIdBytes[2], pRecord->mUnknownAByte);
        pEvent->mUnknown8 = (int)pTarget;
        if (fn_800D0B90(p) != 0) {
            fn_80067E3C(40, &p->mMotion.mPos, p->mId, 0, 0, 0);
        }
        break;
    case 8:
        if (fn_800D0B90(p) != 0) {
            fn_80067E3C(40, &p->mMotion.mPos, p->mId, 0, 0, 0);
        }
        pEvent->mUnknown8 = (int)pTarget;
        break;
    default:
        pEvent->mUnknown8 = 0;
        break;
    }
    pEvent->mUnknown16 = 0;
    pEvent->mUnknown14 = 5;
    fn_800B1508();
    fn_800D7534(p->mIdBytes[2]);
    fn_800B1584(56, 0);
    fn_801783D0(23, 1);
    fn_800310C0(lbl_803EA368, 18, p, &p->mMotion.mPos, &p->mMotion.mFacing);
    fn_80137EC4(pBall, &velocity);
    velocity.mX = velocity.mX < -0.2f ? -0.2f : (velocity.mX > 0.2f ? 0.2f : velocity.mX);
    velocity.mY = velocity.mY < -0.1f ? -0.1f : (velocity.mY > 0.15f ? 0.15f : velocity.mY);
    velocity.mZ = velocity.mZ < -0.1f ? -0.1f : (velocity.mZ > 0.15f ? 0.15f : velocity.mZ);
    fn_80137EE0(pBall, &velocity);
    fn_80099568(1);
    fn_801379B4(pBall, 4, 0);
    fn_8013AD04(pBall, &velocity, 1, 2.0f, 1.0f);
    fn_80137BC0(pBall, pTarget);
    if (velocity.mY < 0.0f) {
        fn_801783D0(1, 1);
    } else {
        fn_801783D0(13, 1);
    }
    fn_80101064(p);
    p->mFlags &= ~0x2000;
    pRecord->mUnknownB = 0;
}

extern "C" int fn_80103CB0(Object_80039F5C *p)
{
    Record_8011F4F8 *pRecord = fn_8011F4F8(fn_801374E0(fn_80137C48(p)));

    switch (pRecord->mUnknown1D) {
    case 4:
        fn_800A5A8C(2, p, fn_80039F5C(p->mIdBytes[2], pRecord->mUnknownAByte));
        if (fn_801BE648(p->mpUnknown792) == 69 || fn_801BE648(p->mpUnknown792) == 178) {
            p->mFlags |= 4;
        }
        break;
    case 5:
        fn_800A5A8C(3, p, p);
        break;
    case 3:
    default:
        fn_80102D78(p);
        break;
    }
    return 1;
}

extern "C" int fn_80103D6C(Object_80039F5C *p)
{
    int result = 0;
    Object_80039F5C *pOther = fn_80137B40();

    if (pOther != 0) {
        State_80039F5C *pState = pOther->mpState;

        if (pState->mId == 15 && pState->mUnknown1 != 4) {
            result = pState->mUnknown2 == p->mIdBytes[1];
        }
    }
    return result;
}

extern "C" float fn_80103DD8(Object_80039F5C *p, Object_80039F5C *pOther, short *pCount, float scale)
{
    Vector_80039F5C delta;
    float factor = 0.0f;
    float distance;
    float spread;
    float base;
    float result;

    fn_8011F4F8(fn_801374E0(fn_801374BC()));
    fn_802276B4(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
    distance = fn_802270A4(&delta);
    fn_801CFE40(delta.mY, delta.mX);
    *pCount = *pCount < 5 ? 5 : (*pCount > 20 ? 20 : *pCount);
    spread = (*pCount - 5.0f) * scale * (1.0f / 15.0f);
    fn_80101AE0(p, &factor);
    base = (lbl_803EAEB8 - distance) * (lbl_803EAEB8 - distance) / (lbl_803EAEB8 * lbl_803EAEB8)
        * (lbl_803EAE94 - lbl_803EAE98) + lbl_803EAE98;
    result = spread * (factor * (lbl_803EAE8C - base)) + base;
    result *= 1.1f;
    result *= lbl_803EA2C4;
    if ((p->mFlags & 0x4000) && fn_8011E188() < lbl_803EAE9C && result > lbl_803EAE90) {
        result = lbl_803EAE90;
    }
    return result;
}

extern "C" void fn_80103F80(Object_80137ABC *pBall, Vector_80039F5C pos, Vector_80039F5C velocity, float speed,
                            int angle, float ballSpeed, Vector_80039F5C *pOut, Object_80039F5C *p)
{
    Vector_80039F5C ball;
    Point_8017886C delta;
    int behind;
    int running;
    float runSpeed;
    float distance;
    float closing;
    float time;
    float reach;
    float slack;
    float burst;
    int turn;

    pOut->mX = pOut->mY = pOut->mZ = 0.0f;
    behind = pos.mY < fn_80177FE0().mY + 13.0f && fn_801CFFD0(angle, 0xC00000) <= 0x271C70;
    if (behind) {
        pOut->mX = pos.mX;
        pOut->mY = pos.mY;
        pOut->mZ = 1.3f;
        return;
    }
    running = speed > fn_8016D9F4(p, 0.14f, 1.0f) && angle <= 0x7FFFFF;
    if (speed > fn_800C49EC(lbl_803ECB08)) {
        speed = fn_800C49EC(lbl_803ECB08);
    }
    fn_80137D58(pBall, &ball);
    runSpeed = speed;
    fn_802276B4(&ball, &ball, &pos);
    distance = fn_802270A4(&ball);
    if (running) {
        runSpeed += (fn_8016D9F4(p, 1.0f, 1.0f) - runSpeed) * fn_801CFB18(angle);
    }
    runSpeed /= lbl_803EA2C4;
    if (runSpeed >= ballSpeed) {
        pOut->mX = pos.mX;
        pOut->mY = pos.mY;
        pOut->mZ = 1.3f;
        return;
    }
    turn = fn_801CFFD0(angle, fn_801CFE40(ball.mY, ball.mX));
    if (turn > 0x400000) {
        turn = fn_801CFFD0(0x800000, turn);
        closing = ballSpeed * fn_801CFB94(fn_801CFDD0(runSpeed * fn_801CFB18(turn) / ballSpeed)) - runSpeed * fn_801CFB94(turn);
    } else {
        closing = ballSpeed * fn_801CFB94(fn_801CFDD0(runSpeed * fn_801CFB18(turn) / ballSpeed)) + runSpeed * fn_801CFB94(turn);
    }
    time = distance / closing / lbl_803EA2C4;
    pOut->mX = pos.mX;
    pOut->mY = pos.mY;
    fn_8022732C(pOut, &velocity, time);
    pOut->mZ = 1.3f;
    fn_80227690(&delta, pOut, &p->mMotion.mPos);
    distance = fn_802270A4(&delta);
    burst = fn_800CAAFC(p);
    slack = runSpeed - fn_8016D9F4(p, 0.72f, 1.0f);
    if (slack < 0.0f) {
        slack = 0.0f;
    }
    reach = (slack * burst + fn_8016D9F4(p, 0.72f, 1.0f) * time) * 0.75f;
    if (reach < distance) {
        float short_ = distance - reach;

        pOut->mX -= short_ * fn_801CFB94(angle);
        pOut->mY -= short_ * fn_801CFB18(angle);
    }
    pOut->mX = pOut->mX < 1.0f - fn_80178A08()
                   ? 1.0f - fn_80178A08()
                   : (pOut->mX > fn_80178A08() - 1.0f ? fn_80178A08() - 1.0f : pOut->mX);
}

extern "C" void fn_80104328(Object_80039F5C *p, unsigned int count, int *pTime, Vector_80039F5C *pPos, int *pAngle)
{
    State_80039F5C *pQueue = p->mpState;
    float speed = fn_8016D9F4(p, 1.0f, 1.0f);
    State_80039F5C *pEntry;
    Point_8017886C offset;
    unsigned char i;

    pPos->mX = pPos->mY = pPos->mZ = 0.0f;
    pEntry = pQueue;
    switch (pEntry->mId) {
    case 19: {
        State_80104328 *pState = (State_80104328 *)&p->mUnknown336;

        offset.mX = pState->mTarget.mX;
        offset.mY = pState->mTarget.mY;
        *pTime = (int)(fn_8022781C(&offset, &p->mMotion.mPos) / speed);
        pPos->mX = pState->mTarget.mX;
        pPos->mY = pState->mTarget.mY;
        *pAngle = pEntry->mUnknown2 << 17 & 0xFE0000;
        break;
    }
    case 20:
        fn_8012CD4C(p, &offset);
        pPos->mX = offset.mX;
        pPos->mY = offset.mY;
        if ((unsigned int)(pEntry->mUnknown2 - 8) <= 1) {
            *pAngle = fn_8012CAAC(p);
        } else {
            *pAngle = fn_8012CAA4(p);
        }
        *pTime = fn_8012CC50(p);
        break;
    default:
        *pTime = 0;
        break;
    }
    for (i = 1; i <= count; i++) {
        pEntry = &pQueue[i];
        if (pEntry->mId == 20) {
            State_80039F5C *pPrev = &pQueue[i - 1];
            int kind = pEntry->mUnknown2;
            unsigned char type = pEntry->mUnknown1;

            if (pPrev->mId == 19) {
                fn_8012CB98(kind, type, pPrev->mUnknown2 << 17 & 0xFE0000, &offset);
                *pTime += fn_8012CC04(type);
                pPos->mX += offset.mX;
                pPos->mY += offset.mY;
                *pAngle += fn_8012CB50((Message_800F01CC *)pEntry);
            }
        } else if (pEntry->mId == 19) {
            float distance = (unsigned int)pEntry->mUnknown1 * 0.125f;

            *pTime += (int)(distance / speed);
            *pAngle = pEntry->mUnknown2 << 17 & 0xFE0000;
            fn_80227538(&offset, *pAngle, distance);
            pPos->mX += offset.mX;
            pPos->mY += offset.mY;
        }
    }
}
