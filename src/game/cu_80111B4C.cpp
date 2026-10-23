#include "engine/cu_801B9F00.h"
#include "game/fn_801248D4.h"
#include "game/State_800FDA58.h"
#include "game/fn_800B65A0.h"
#include "game/Input_800B6D34.h"
#include "game/Object_80039F5C.h"
#include "game/Record_800B15FC.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"

struct State_80111F80 {
    char mUnknown0[20];
    unsigned char mUnknown20;
};

struct State_8010CAE8 {
    char mUnknown0[12];
    float mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    char mUnknown21[3];
    int mUnknown24;
    char mUnknown28[16];
    float mUnknown44;
    float mUnknown48;
};

/* The 12 bytes at player +336 as the timer that fn_8010FD94 clears and
   fn_80113498 advances. */
struct Timer_8010FD94 {
    unsigned int mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
};

/* Bytes at player +336 as fn_80113680 sets them up. */
struct State_80113680 {
    int mRef;
    int mUnknown4;
    float mUnknown8;
    unsigned char mUnknown12;
    unsigned char mUnknown13;
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    char mUnknown16[2];
    short mUnknown18;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
};

/* Bytes at player +336 as fn_80113C20 sets them up. */
struct State_80113C20 {
    int mRef;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    int mUnknown20;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
    short mUnknown26;
    unsigned char mUnknown28;
    unsigned char mUnknown29;
    unsigned char mUnknown30;
    unsigned char mUnknown31;
    Record_800DB60C mUnknown32;
    unsigned char mUnknown56;
    unsigned char mUnknown57;
    unsigned char mUnknown58;
    unsigned char mUnknown59;
    int mUnknown60;
    short mUnknown64;
    unsigned char mUnknown66;
    unsigned char mUnknown67;
    unsigned char mUnknown68;
};

/* The bytes at player +336 as fn_80113E74 updates them; +32 is the block
   passed to fn_800DB7A4 and fn_800DB8B4. */
struct State_80113E74 {
    int mRef;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    char mUnknown16[4];
    unsigned int mUnknown20;
    char mUnknown24[1];
    unsigned char mUnknown25;
    short mUnknown26;
    unsigned char mUnknown28;
    unsigned char mUnknown29;
    unsigned char mUnknown30;
    unsigned char mUnknown31;
    char mUnknown32[24];
    unsigned char mUnknown56;
    char mUnknown57[2];
    unsigned char mUnknown59;
    int mUnknown60;
    unsigned short mUnknown64;
    char mUnknown66[2];
    unsigned char mUnknown68;
};

/* The bytes at +336 of the player that fn_80113E74's reference names. */
struct Other_80113E74 {
    char mUnknown0[4];
    unsigned int mUnknown4;
    float mUnknown8;
};

/* Payload of fn_801BE60C as fn_80114F64 reads it. */
struct Block_80114F64 {
    char mUnknown0[4];
    Point_8017886C mUnknown4;
    char mUnknown12[16];
    unsigned char mUnknown28;
};

/* Bytes at player +336 as fn_80115248 reads them for states 40 and 92. */
struct State_80115248 {
    char mUnknown0[12];
    float mUnknown12;
    char mUnknown16[4];
    Object_80039F5C *mpUnknown20;
};

/* The bytes at player +336 as fn_8011569C drives them. */
struct State_8011569C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned char mUnknown16;
    unsigned char mUnknown17;
    char mUnknown18[2];
    unsigned char mUnknown20;
};

/* 16-byte zone records at +24 of the block fn_8011F4EC returns. */
struct Zone_8011569C {
    float mUnknown0;
    float mUnknown4;
    float mLow;
    float mHigh;
};

struct Field_8011569C {
    char mUnknown0[24];
    Zone_8011569C mZones[1];
};

extern "C" {
int fn_80099734(Object_80039F5C *p, Object_80137ABC *pBall, int a, int mode, void *pBlock, int b, int c, int d, int e,
                float range);
int fn_800997F4(Object_80039F5C *p, Object_80137ABC *pBall, float range, void *pBlock, int a, int b, int c, int *pOutA,
                int *pOutB);
int fn_80099F04(Object_80039F5C *p, int a, unsigned char index);
int fn_8009A1A8(Object_80039F5C *p, int a, int b, int c, int index);
int fn_8009A6EC(Object_80039F5C *p);
int fn_8009A77C(Object_80039F5C *p);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_8009E9A4(void);
void fn_8009E9EC(Object_80039F5C *p, int side, Point_8017886C *pOut);
int fn_8009EAB0(Object_80039F5C *p, int a);
Object_80039F5C *fn_8009EC60(unsigned int index, Point_8017886C *pOut);
int fn_8009EF6C(void *p);
int fn_8009EFDC(int side);
int fn_8009F0B8(Object_80039F5C *p, int angle);
void fn_8009F928(Object_80039F5C *p, Point_8017886C *pSpot, int a, unsigned char flag);
unsigned char fn_8009FD7C(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
int fn_800A7F1C(unsigned char);
void fn_800A8954(int event, int team, Object_80039F5C *p);
void fn_800B2370(Object_80039F5C *, int, Object_80039F5C *, float);
Object_80039F5C *fn_800B6544(int index);
int fn_800B7FE8(Object_80039F5C *p);
int fn_800C1180(Object_80039F5C *p);
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
int fn_800CD35C(int mode, Object_80039F5C *p);
void fn_800CE674(Object_800CE674 *p);
void fn_800CE684(Object_800CE674 *p);
int fn_800CE690(Object_800CE674 *p);
float fn_800CE73C(Object_800CE674 *p);
int fn_800D0B90(Object_80039F5C *p);
void fn_800D640C(Object_80039F5C *p);
void fn_800D6E98(int team);
void fn_800D7A18(Object_80039F5C *p);
void fn_800DB520(void *pBlock, Object_80039F5C *p, Object_80039F5C *pOther, float value);
void fn_800DB7A4(void *pBlock, Object_80039F5C *p);
void fn_800DB8B4(void *pBlock, Object_80039F5C *p);
int fn_800DC080(Object_80039F5C *p);
int fn_800DC21C(Object_80039F5C *p);
void fn_800DF134(Object_80039F5C *p, Point_8017886C offset, int angle, int key);
int fn_800E1554(Object_80039F5C *p);
void fn_800F05E4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
Object_80039F5C *fn_800FB9D4(Object_80039F5C *p);
void fn_80102D78(Object_80039F5C *p);
void fn_801039D8(Object_80039F5C *p);
void fn_80111A28(Object_80039F5C *p, int angle, float length, Vector_80039F5C *pOut);
int fn_80113C18(Object_80039F5C *p, void *pState);
Object_80039F5C *fn_80114E7C(Object_80039F5C *p);
void fn_80114F64(Object_80039F5C *p, int angle);
int fn_80116410(Object_80039F5C *p, Object_80039F5C *pOther, State_8011569C *pState, Point_8017886C *pTarget);
int fn_801167C4(void *pTarget, Object_80039F5C *p);
void fn_80116880(Object_80039F5C *p, Object_80039F5C *pOther, float *pValue, float *pOut, float range);
int fn_80116984(Object_80039F5C *p, Object_80039F5C *pOther, float *pOut);
int fn_80116AB8(Object_80039F5C *p);
void fn_8011E8D8(Object_80039F5C *p);
Record_8011F4E0 *fn_8011F4E0(void);
void *fn_8011F4EC(void);
void fn_8013AA00(Object_80137ABC *pBall, float height, float *pTime, Vector_80039F5C *pLanding);
float fn_8013AB64(Object_80137ABC *pBall, float t);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
void fn_801410F4(int a);
void fn_80143E14(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80143EBC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_801486A0(void);
void fn_80156C78(int a, int b);
int fn_80168E00(int team, int index, unsigned char *pOut);
float fn_8016D9F4(Object_80039F5C *p, float a, float b);
void fn_8016F6F4(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80171824(Object_80039F5C *p);
void fn_801718E8(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80171E30(void);
void fn_801720B4(Object_80039F5C *p);
int fn_8017319C(Object_80039F5C *p);
int fn_80176B04(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_801783AC(int bit);
int fn_801784C4(void);
int fn_801787A0(void);
float fn_80178A08(void);
float fn_80178A2C(void);
float fn_80178A44(void);
void fn_80194C5C(int a, int b, int c);
float fn_801CFB18(int angle);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227248(void *pOut, void *pIn, float scale);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80227890(void *pA, void *pB);
void fn_80227970(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC, Vector_80039F5C *pOut, float *pValue,
                 float *pOther);
float fn_80237260(int stream);
extern float lbl_803EA2C4;
extern float lbl_803EAF60;
extern float lbl_803EAF64;
extern float lbl_803EAF68;
extern float lbl_803EAF6C;
extern float lbl_803EAF70;
extern float lbl_803EAF74;
extern float lbl_803EAF78;
extern unsigned char lbl_803EAF7C;
extern unsigned char lbl_803EAF7D;
extern float lbl_803EAF80;
extern float lbl_803EAF84;
extern float lbl_803EAF88;
extern float lbl_803EAF8C;
extern unsigned char lbl_803EAF90;
extern unsigned char lbl_803EAF91;
extern int lbl_803EAF94;
extern unsigned char lbl_803EAF98;
extern float lbl_803EAF9C;
extern float lbl_803EAFA0;
extern float lbl_803EAFA4;
extern float lbl_803EAFA8;
extern float lbl_803EAFAC;
extern float lbl_803EAFB0;
extern float lbl_803EAFB4;
extern float lbl_803EAFB8;
extern float lbl_803EAFBC;
extern float lbl_803EAFCC;
extern float lbl_803ECB04;
extern float lbl_803ECB08;
extern const float lbl_803ED6CC;
int fn_8010FD94(Object_80039F5C *p);
}

extern "C" int fn_80111B4C(Object_80039F5C *p)
{
    State_8010CAE8 *pState = (State_8010CAE8 *)&p->mUnknown336;
    Vector_80039F5C travel;
    Vector_80039F5C ahead;
    Vector_80039F5C fromTarget;
    Vector_80039F5C toBall;
    Vector_80039F5C closest;
    Vector_80039F5C velocity;
    Vector_80039F5C ball;
    Vector_80039F5C target;
    Vector_80039F5C offset;
    float distance;
    float along;
    float maxDistance;
    float maxHeight;
    float minHeight;
    float height;
    Object_80137ABC *pBall;
    int travelAngle;
    int targetAngle;
    int result;

    travel.mZ = 0.0f;
    fromTarget.mZ = 0.0f;
    toBall.mZ = 0.0f;
    ahead.mZ = 0.0f;
    maxDistance = lbl_803EAF6C;
    result = 1;
    maxHeight = lbl_803EAF70;
    minHeight = lbl_803EAF74;
    pBall = fn_80137ABC(p->mpState->mUnknown1);
    fn_80138064(pBall, &ball);
    fn_80137D58(pBall, &target);
    fn_80227690(&travel, &ball, &target);
    fn_80227690(&fromTarget, &p->mMotion.mPos, &target);
    fn_80227690(&toBall, &ball, &p->mMotion.mPos);
    travelAngle = fn_801CFE40(travel.mY, travel.mX);
    targetAngle = fn_801CFE40(fromTarget.mY, fromTarget.mX);
    if (lbl_803EAF7C) {
        if (p->mUnknown528.mUnknown0 <= lbl_803EAF68 ||
            fn_801CFFD0(p->mMotion.mFacing, (targetAngle + 0x800000) & 0xFFFFFF) < (int)(lbl_803EAF64 * 46603.379f)) {
            fn_80227248(&ahead, &travel, 4.0f);
            fn_80227638(&ahead, &ahead, &target);
            target.mZ = 0.0f;
            fn_80227970(&target, &ahead, &p->mMotion.mPos, &closest, &distance, &along);
            if (pState->mUnknown20) {
                maxDistance *= lbl_803EAF78 + 1.0f;
                maxHeight *= lbl_803EAF78 + 1.0f;
                minHeight *= 1.0f - lbl_803EAF78;
            }
            if (distance < maxDistance) {
                distance = fn_8022781C(&target, &closest);
                fn_80137EC4(pBall, &velocity);
                height = fn_8013AB64(pBall, distance / fn_802270A4(&velocity));
                if (height < maxHeight * p->mUnknown768 && height > minHeight * p->mUnknown768) {
                    result = 0;
                    pState->mUnknown20 = 1;
                }
            }
        }
    } else {
        if (fn_801CFFD0(travelAngle, targetAngle) < (int)(lbl_803EAF60 * 46603.379f) &&
            fn_801CFFD0(p->mMotion.mFacing, (targetAngle + 0x800000) & 0xFFFFFF) < (int)(lbl_803EAF64 * 46603.379f) &&
            fn_802270A4(&fromTarget) < fn_802270A4(&travel) && fn_802270A4(&toBall) < 0.5f) {
            result = 0;
        }
        if (result) {
            fn_802276B4(&offset, &ball, &p->mMotion.mPos);
            if (fn_802270A4(&offset) < 0.5f) {
                result = 0;
            }
        }
    }
    if (result) {
        pState->mUnknown20 = 0;
    }
    return result;
}

extern "C" void fn_80111E80(Object_80039F5C *p)
{
    Vector_80039F5C ball;
    Point_8017886C delta;
    Object_80137ABC *pBall = fn_801374BC();
    int angle;
    float distance;

    fn_80138064(pBall, &ball);
    fn_80227690(&delta, &ball, &p->mMotion.mPos);
    if (fn_802270A4(&delta) < 10.0f) {
        fn_80137D58(pBall, &ball);
        fn_80227690(&delta, &ball, &p->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        if (fn_801CFFD0(angle, p->mMotion.mFacing) <= 0x71C71B) {
            distance = fn_802270A4(&delta);
            if (distance < 35.0f) {
                fn_800C89F0(p, angle, 2, 0, 1.0f - distance / 35.0f);
            }
        }
    }
}

extern "C" int fn_80111FBC(Object_80039F5C *p)
{
    State_80111F80 *state = (State_80111F80 *)&p->mUnknown336;
    Vector_80039F5C delta;
    Vector_80039F5C ball;
    Vector_80039F5C from;
    Vector_80039F5C velocity;
    Vector_80039F5C pos;
    Vector_80039F5C offset;
    Message_800F01CC message;
    Point_8017886C toBall;
    float height;
    int value;
    int extra;
    Object_80137ABC *pBall;
    int target = 0x1FFFFFFF;
    int flag;
    int found;
    int a;
    int mode;
    float range;
    float t;
    float speed;

    pBall = fn_80137ABC(p->mpState->mUnknown1);
    fn_80138064(pBall, &ball);
    fn_80137D58(pBall, &from);
    fn_80137EC4(pBall, &velocity);
    fn_802276B4(&offset, &from, &p->mMotion.mPos);
    if (!(p->mFlags & 0x4000)) {
        if (ball.mX > fn_80178A08()) {
            ball.mX -= 2.0f * (ball.mX - fn_80178A08());
        } else if (ball.mX < -fn_80178A08()) {
            ball.mX -= 2.0f * (ball.mX + fn_80178A08());
        }
        if (lbl_803EAF7D != 0) {
            if (ball.mX > fn_80178A08() - 3.0f && p->mMotion.mPos.mX < ball.mX) {
                if (ball.mX > fn_80178A08() + 0.5f) {
                    if (fabsf(ball.mX - from.mX) < 1e-7f) {
                        t = 0.0f;
                    } else {
                        t = (fn_80178A08() + 0.5f - from.mX) / (ball.mX - from.mX);
                    }
                    ball.mX = fn_80178A08() + 0.5f;
                    ball.mY = (ball.mY - from.mY) * t + from.mY;
                }
                fn_80227690(&delta, &p->mMotion.mPos, &ball);
                fn_80227538((Point_8017886C *)&delta, fn_801CFE40(delta.mY, delta.mX), 1.25f);
                fn_80227638(&ball, &ball, &delta);
            }
            if (ball.mX < -(fn_80178A08() - 3.0f) && p->mMotion.mPos.mX > ball.mX) {
                if (ball.mX < -(fn_80178A08() + 0.5f)) {
                    if (ball.mX - from.mX != 0.0f) {
                        t = (-(fn_80178A08() + 0.5f) - from.mX) / (ball.mX - from.mX);
                    } else {
                        t = 0.0f;
                    }
                    ball.mX = -(fn_80178A08() + 0.5f);
                    ball.mY = (ball.mY - from.mY) * t + from.mY;
                }
                fn_80227690(&delta, &p->mMotion.mPos, &ball);
                fn_80227538((Point_8017886C *)&delta, fn_801CFE40(delta.mY, delta.mX), 1.25f);
                fn_80227638(&ball, &ball, &delta);
            }
        }
        ball.mY = ball.mY > fn_80178A44() - 0.75f ? fn_80178A44() - 0.75f : ball.mY;
    } else {
        fn_80138064(fn_801374BC(), &pos);
        fn_80227690(&toBall, &pos, &p->mMotion.mPos);
        if (fn_801CFFD0(p->mUnknown512.mUnknown4, fn_801CFE40(toBall.mY, toBall.mX)) > 0x200000) {
            Object_80039F5C *pOther = fn_800FB9D4(p);

            if (pOther != 0) {
                fn_801C1F94(&message, 0, 4);
                message.mId = 24;
                message.mUnknown1[0] = 2;
                fn_800F053C(0, pOther->mpState, &message, pOther);
            }
        }
    }
    flag = ball.mY >= fn_80177FE0().mY + 2.0f;
    if (fn_801CFFD0(p->mMotion.mFacing, 0xC00000) < 0x2AAAAA) {
        flag = 0;
    }
    if (fn_8013BA58(pBall, 0) != 4) {
        fn_801C1F94(&message, 0, 4);
        if (fn_80137AD0(pBall) == p) {
            message.mId = 1;
            fn_800F053C(0, p->mpState, &message, p);
        }
        return 1;
    }
    if (!(p->mFlags & 0x4000)) {
        if (flag == 1) {
            a = 0;
            mode = 3;
        } else {
            a = 0;
            mode = 2;
        }
    } else {
        a = 0;
        mode = 1;
    }
    if (p->mUnknown8 == 0xFF) {
        range = 120.0f;
    } else {
        range = 17.0f;
    }
    fn_801380AC(pBall, &height);
    value = -1;
    extra = 0;
    if (fn_8009A6EC(p)) {
        target = fn_800997F4(p, pBall, range, state, 3, 0, 0, &value, &extra);
    }
    if (target == 0x1FFFFFFF) {
        target = fn_80099734(p, pBall, 0, mode, state, 1, 0, 0, fn_8009A77C(p), range);
    }
    if (target != 0x1FFFFFFF) {
        int result;

        if (((target >> 29) & 3) == 1) {
            result = fn_8009A1A8(p, target, value, extra, p->mpState->mUnknown1);
        } else {
            result = fn_80099F04(p, target, p->mpState->mUnknown1);
        }
        if (result != 0) {
            return 0;
        }
    } else if (height <= lbl_803EAF80) {
        fn_80138064(pBall, &pos);
        flag = 0;
        if (fn_8022781C(&p->mMotion.mPos, &pos) < lbl_803EAF84) {
            if (fn_80137B88(pBall) == p && fn_801783AC(11) == 0) {
                if (fn_801CFFD0(fn_801CFE40(offset.mY, offset.mX), p->mMotion.mFacing) >
                    (int)(lbl_803EAF88 * 46603.378f)) {
                    mode = 2;
                }
                flag = 1;
            } else if (fn_801783AC(11) == 1 && fn_8022781C(&p->mMotion.mPos, &pos) > lbl_803EAF8C) {
                a = 3;
                mode = 3;
                flag = 1;
            }
            if (flag) {
                found = 1;
                target = fn_80099734(p, pBall, a, mode, state, 1, 0, 1, fn_8009A77C(p), range);
                if (target == 0x1FFFFFFF) {
                    found = 0;
                }
            } else {
                found = 0;
            }
            if (found && fn_80099F04(p, target, p->mpState->mUnknown1) == 1) {
                return 0;
            }
        }
    }
    if (!(p->mFlags & 0x4000)) {
        fn_802276B4(&delta, &ball, &p->mMotion.mPos);
        if (fn_80111B4C(p)) {
            float ratio;
            float distance;

            speed = lbl_803ECB08 * (lbl_803ED6CC + (1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f));
            fn_802276B4(&ball, &ball, &from);
            if (fn_802270A4(&velocity) != 0.0f) {
                ratio = fn_802270A4(&ball) / fn_802270A4(&velocity);
            } else {
                ratio = 0.0f;
            }
            distance = fn_802270A4(&delta);
            if (distance > 0.5f) {
                distance -= 0.5f;
            }
            if (ratio == 0.0f) {
                distance = 0.0f;
            } else {
                distance /= ratio;
            }
            if (distance > speed) {
                t = 1.0f;
            } else if (speed != 0.0f) {
                t = distance / speed;
            } else {
                t = 0.0f;
            }
            if (t < 0.4f) {
                t = 0.4f;
            }
            if (t != 0.0f) {
                int angle = fn_801CFE40(delta.mY, delta.mX);

                if (fn_801CFFD0(angle, p->mMotion.mFacing) < 0xAAAAA) {
                    p->mUnknown512.mUnknown15 = 1;
                }
                if (fn_801CFFD0(p->mMotion.mFacing, angle) > 0x600000) {
                    int turn = (p->mMotion.mFacing + 0x5F49F5) & 0xFFFFFF;

                    if (fn_801CFFD0(turn, angle) > 0x400000) {
                        turn = (turn + 0x800000) & 0xFFFFFF;
                    }
                    angle = turn;
                }
                p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = angle;
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown0 = t;
            }
        } else {
            fn_80227690(&offset, &from, &p->mMotion.mPos);
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = fn_801CFE40(offset.mY, offset.mX) & 0xFFFFFF;
            p->mUnknown512.mUnknown4 = fn_801CFE40(offset.mY, offset.mX) & 0xFFFFFF;
            p->mUnknown512.mUnknown0 = 0.0f;
        }
        fn_80111E80(p);
    }
    return 0;
}

extern "C" int fn_80112928(Object_80039F5C *p)
{
    int attempt = 0;
    Object_80137ABC *pBall = fn_801374BC();
    Object_80039F5C *pTarget;
    Message_800F01CC message;
    Vector_80039F5C ballPos;
    Vector_80039F5C pos;
    float time;
    Point_8017886C landing;
    Point_8017886C delta;

    if (fn_801783AC(11) == 1 || fn_801783AC(12) == 1) {
        attempt = 1;
    }
    pTarget = fn_80137B88(pBall);
    if (p == pTarget && fn_8013BA58(pBall, 0) == 4) {
        attempt = 1;
    } else if (fn_80138064(pBall, &ballPos) != 0 && pTarget != 0 && fn_801380AC(pBall, &time) != 0) {
        float targetDistance;
        float otherDistance;
        float distance;
        float targetSpeed;
        float speed;

        fn_8013AA00(pBall, 2.0f, 0, (Vector_80039F5C *)&landing);
        fn_80227690(&delta, &pTarget->mMotion.mPos, &landing);
        targetDistance = fn_802270A4(&delta) - 2.0f;
        fn_80227690(&delta, &pTarget->mMotion.mPos, &ballPos);
        otherDistance = fn_802270A4(&delta) - 2.0f;
        if (otherDistance < targetDistance) {
            targetDistance = otherDistance;
        }
        fn_80227690(&delta, &p->mMotion.mPos, &ballPos);
        distance = fn_802270A4(&delta) + 0.5f;
        targetSpeed = fn_8016D9F4(pTarget, 1.0f, 1.0f);
        speed = fn_8016D9F4(p, 1.0f, 1.0f);
        if (targetDistance / targetSpeed > time && distance / speed < time) {
            attempt = 1;
        }
    }
    if (attempt != 0) {
        float chance;

        fn_80137EC4(pBall, &pos);
        if (pos.mZ < 0.0f && fn_801783AC(11) == 0 && fn_801783AC(12) == 0) {
            chance = 1.0f;
        } else {
            chance = p->mRatings[3] * 0.00078431377f;
            if (fn_8009F0B8(p, 0x400000) != 0) {
                chance += 0.15f;
            }
            if (p == pTarget) {
                chance = 1.0f;
            }
            if (fn_800A7F1C(p->mIdBytes[2]) == 0) {
                chance = 0.0f;
            }
        }
        if (fn_80237260(0) <= chance) {
            fn_801C1F94(&message, 0, sizeof(message));
            message.mId = 23;
            message.mUnknown1[0] = fn_801374E0(pBall);
            fn_800F053C(0, p->mpState, &message, p);
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_80112C04(Object_80039F5C *p, Object_80137ABC *pBall, int *pAngle, float *pValue)
{
    Vector_80039F5C velocity;
    Vector_80039F5C playerVelocity;
    float lowTime;
    Point_8017886C lowLanding;
    float highTime;
    Point_8017886C highLanding;
    Point_8017886C lowReach;
    Point_8017886C highReach;
    Point_8017886C middle;
    int lowAngle;
    int highAngle;
    float value;

    fn_80137EC4(pBall, &velocity);
    playerVelocity.mX = p->mMotion.mUnknown40;
    playerVelocity.mY = p->mMotion.mUnknown44;
    playerVelocity.mZ = p->mMotion.mUnknown48;
    fn_8013AA00(pBall, 0.8f, &lowTime, (Vector_80039F5C *)&lowLanding);
    fn_8013AA00(pBall, 2.1f, &highTime, (Vector_80039F5C *)&highLanding);
    fn_80227690(&lowLanding, &lowLanding, &p->mMotion.mPos);
    lowAngle = fn_801CFE40(lowLanding.mY, lowLanding.mX);
    fn_80111A28(p, lowAngle, lowTime, (Vector_80039F5C *)&lowReach);
    fn_80227690(&lowReach, &lowReach, &p->mMotion.mPos);
    fn_80227690(&highLanding, &highLanding, &p->mMotion.mPos);
    highAngle = fn_801CFE40(highLanding.mY, highLanding.mX);
    fn_80111A28(p, highAngle, highTime, (Vector_80039F5C *)&highReach);
    fn_80227690(&highReach, &highReach, &p->mMotion.mPos);
    value = *pValue;
    if (fn_802270A4(&highLanding) > fn_802270A4(&highReach)) {
        if (value < 0.9f) {
            value += 0.1f;
        } else {
            value = 1.0f;
        }
        *pAngle = lowAngle;
    } else if (fn_802270A4(&lowLanding) < fn_802270A4(&lowReach)) {
        if (value > 0.24000001f) {
            value -= 0.1f;
        } else {
            value = 0.14f;
        }
        *pAngle = highAngle;
    } else {
        fn_80227638(&middle, &lowLanding, &highLanding);
        *pAngle = fn_801CFE40(middle.mY, middle.mX);
    }
    *pValue = value;
    return 0;
}

extern "C" int fn_80113498(Object_80039F5C *p)
{
    int result = 0;
    Timer_8010FD94 *pTimer = (Timer_8010FD94 *)&p->mUnknown336;

    if (p->mFlags & 0x4000) {
        pTimer->mUnknown0 += (unsigned int)lbl_803EA2C4;
    } else {
        result = 1;
    }
    return result;
}

extern "C" int fn_80113680(Object_80039F5C *p)
{
    State_80113680 *state = (State_80113680 *)&p->mUnknown336;
    Object_80039F5C *pOther;
    State_80039F5C *pState;

    if (p->mpState->mUnknown3[0] == 255) {
        return 1;
    }
    p->mUnknown9[0] = 1;
    state->mUnknown21 = 0;
    pOther = fn_80039F5C(p->mIdBytes[2] ^ 1, p->mpState->mUnknown3[0]);
    fn_8009BD2C(pOther, &state->mRef);
    p->mFlags |= 8;
    fn_80143E14(p, pOther);
    state->mUnknown4 = 255;
    state->mUnknown8 = 0.0f;
    state->mUnknown12 = 0;
    state->mUnknown14 = 0;
    state->mUnknown15 = 0;
    state->mUnknown18 = 0;
    state->mUnknown20 = fn_800E1554(p);
    state->mUnknown13 = 0;
    p->mUnknown1218 = fn_800CD35C(1, p);
    if (fn_800B65A0(p->mIdBytes[2]) == 255 && fn_802372EC(0, 100) > 80.0f) {
        state->mUnknown13 = 1;
    }
    fn_800CE674(&p->mUnknown1240);
    fn_800CE684(&p->mUnknown1240);
    fn_8011E8D8(p);
    pState = p->mpState;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, (pState->mUnknown1 << 8) | pState->mUnknown2, p, 1.0f);
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~4;
    return 0;
}

extern "C" int fn_8011380C(Object_80039F5C *p)
{
    State_80113680 *state = (State_80113680 *)&p->mUnknown336;
    int result = 0;
    Object_800CE674 *pAnim = &p->mUnknown1240;
    Object_80039F5C *pOther = fn_8009BCE8(&state->mRef);

    if (state->mUnknown14 == 1) {
        if (!(p->mFlags & 0x4000)) {
            state->mUnknown18++;
        }
        if (state->mUnknown14 == 1 && p->mUnknown8 != 255) {
            fn_80194C5C(p->mUnknown8, lbl_803EAF90, 10);
        }
    }
    if (pAnim->mUnknown0 != -1) {
        state->mUnknown4 = fn_800CE690(pAnim);
        state->mUnknown8 = fn_800CE73C(pAnim);
        fn_800CE674(pAnim);
    }
    if (pAnim->mUnknown3 != -1) {
        if (pOther == fn_80137B40()) {
            switch (pAnim->mUnknown3) {
            case 2:
                fn_800B2370(p, 4, pOther, 1.0f);
                break;
            case 3:
                fn_800B2370(p, 5, pOther, 1.0f);
                break;
            case 1:
                if (fn_80176B04() != 0) {
                    if (fn_802372EC(0, 100) < 75) {
                        fn_800B2370(p, 4, pOther, 1.0f);
                    } else {
                        fn_800B2370(p, 5, pOther, 1.0f);
                    }
                } else if (fn_802372EC(0, 100) < 20) {
                    fn_800B2370(p, 5, pOther, 0.0f);
                }
                break;
            }
        }
        fn_800CE684(&p->mUnknown1240);
    }
    if (p->mUnknown9[0] != 1) {
        Message_800F01CC message;

        p->mFlags &= ~8;
        fn_80143EBC(p, fn_8009BCE8(&state->mRef));
        state->mUnknown21 = 1;
        if ((unsigned int)state->mUnknown4 <= 10) {
            fn_801C1F94(&message, 0, sizeof(message));
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F05E4(0, p->mpState, &message, p);
        } else {
            fn_801C1F94(&message, 0, sizeof(message));
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F05E4(0, p->mpState, &message, p);
        }
    }
    if ((p->mFlags & 4) && state->mUnknown14 != 1 && state->mUnknown14 != 4) {
        p->mFlags &= ~0xC;
        p->mFlags &= ~0x800;
        fn_80143EBC(p, fn_8009BCE8(&state->mRef));
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
        result = 1;
    }
    return result;
}

extern "C" int fn_80113C20(Object_80039F5C *p)
{
    State_80113C20 *state = (State_80113C20 *)&p->mUnknown336;
    unsigned short key;
    Object_80039F5C *pOther;
    Object_80137ABC *pBall;
    State_80039F5C *pState;

    p->mUnknown9[0] = 1;
    if (fn_800D0B90(p) != 0 && fn_800D0B90(p) != 4 && fn_801BE648(p->mpUnknown792) != 227) {
        state->mUnknown24 = 1;
    } else {
        state->mUnknown24 = 0;
    }
    pOther = fn_80039F5C(p->mIdBytes[2] ^ 1, p->mpState->mUnknown3[0]);
    fn_8009BD2C(pOther, &state->mRef);
    p->mFlags |= 8;
    fn_80143E14(p, pOther);
    state->mUnknown4 = 0.0f;
    state->mUnknown20 = 255;
    state->mUnknown25 = 1;
    state->mUnknown56 = 0;
    state->mUnknown58 = 0;
    state->mUnknown60 = 0;
    state->mUnknown64 = 0;
    state->mUnknown57 = 0;
    state->mUnknown67 = 0;
    state->mUnknown68 = 0;
    state->mUnknown66 = p->mUnknown776;
    fn_800CE674(&p->mUnknown1240);
    fn_800CE684(&p->mUnknown1240);
    fn_800DB520(&state->mUnknown32, p, pOther, state->mUnknown4);
    state->mUnknown8 = 0.0f;
    state->mUnknown16 = 0.0f;
    state->mUnknown26 = -1;
    state->mUnknown59 = 0;
    state->mUnknown31 = 0;
    state->mUnknown30 = 0;
    state->mUnknown28 = 0;
    state->mUnknown29 = 0;
    if (p->mFlags & 0x1000) {
        state->mUnknown29 = 1;
    }
    pState = p->mpState;
    key = (pState->mUnknown1 << 8) | pState->mUnknown2;
    pBall = fn_80137C48(p);
    if (pBall != 0) {
        Record_8011F4F8 *pRecord = fn_8011F4F8(fn_801374E0(pBall));

        if ((fn_801BE648(p->mpUnknown792) == 69 || fn_801BE648(p->mpUnknown792) == 178) &&
            pRecord->mUnknownB == 1 && key != 234 &&
            (pRecord->mUnknown1D <= 1 || pRecord->mUnknown1D == 3 || pRecord->mUnknown1D == 6 ||
             pRecord->mUnknown1D == 7)) {
            Vector_80039F5C pos;

            state->mUnknown30 = 1;
            fn_80137D58(pBall, &pos);
            state->mUnknown12 = state->mUnknown8 = pos.mZ;
        }
    }
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, p, 1.0f);
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~0x1005;
    if (state->mUnknown30 == 1) {
        fn_800D7A18(p);
    }
    return 0;
}

extern "C" int fn_80113E74(Object_80039F5C *p)
{
    int result = 0;
    State_80113E74 *state = (State_80113E74 *)&p->mUnknown336;
    Object_800CE674 *pAnim = &p->mUnknown1240;
    Other_80113E74 *pOtherState = 0;
    Object_80039F5C *pOther = fn_8009BCE8(&state->mRef);
    Message_800F01CC message;
    Vector_80039F5C ball;
    Vector_80039F5C hand;
    Point_8017886C aim;
    Object_80137ABC *pBall;
    int allowed;
    float speed;

    if (pOther != 0) {
        pOtherState = (Other_80113E74 *)&pOther->mUnknown336;
    }
    if (state->mUnknown68 == 0) {
        fn_8017319C(p);
        state->mUnknown68 = 1;
    }
    fn_800DB7A4(state->mUnknown32, p);
    if (state->mUnknown56 == 1) {
        state->mUnknown60++;
        if (!(p->mFlags & 0x4000)) {
            state->mUnknown64++;
            if (!(p->mFlags & 0x4000)) {
                if (fn_801486A0() == 0) {
                    fn_80114F64(p, (fn_801CFE40(p->mMotion.mPos.mY, p->mMotion.mPos.mX) + 0x800000) & 0xFFFFFF);
                } else {
                    fn_80114F64(p, 0x400000);
                }
            }
        }
    }
    if (p == fn_80137B40() && fn_801787A0() == 0 && (p->mFlags & 1)) {
        p->mFlags &= ~1;
        if (fn_801787A0() == 0) {
            if (state->mUnknown56 == 5) {
                fn_80067E3C(61, &p->mpUnknown4->mUnknown4, p->mId, 0, 0, 0);
                fn_800D6E98(fn_80178320());
                fn_80171E30();
                fn_801720B4(pOther);
                fn_800A8954(26, p->mIdBytes[2], p);
            } else if (fn_801BE648(p->mpUnknown792) == 234 && fn_801BE648(pOther->mpUnknown792) == 234) {
                fn_80171E30();
                fn_801720B4(pOther);
                if (fn_801787A0() == 0) {
                    fn_800D6E98(fn_80178308());
                    fn_800A8954(26, p->mIdBytes[2], p);
                    fn_80156C78(40, 1);
                }
            } else {
                fn_80171824(p);
            }
        }
    }
    if (state->mUnknown25 != 0) {
        if (fn_80137C48(p) == 0) {
            p->mFlags |= 0x4000000;
            state->mUnknown25 = 0;
        } else {
            if (((p->mFlags & 0x10000) && state->mUnknown56 != 4 && state->mUnknown56 != 2) ||
                state->mUnknown56 == 3) {
                allowed = 1;
                if (state->mUnknown56 == 1) {
                    allowed = p->mRatings[2] - pOther->mRatings[5] <= lbl_803EAF94;
                }
                if (allowed) {
                    fn_800DB8B4(state->mUnknown32, p);
                }
            }
        }
    }
    if (state->mUnknown30 == 1) {
        if ((p->mFlags & 0x1000) || state->mUnknown29 != 0) {
            pBall = fn_80137C48(p);
            if (pBall != 0) {
                fn_80137D58(pBall, &ball);
                fn_8009BF5C(p, 12, &hand, 0);
                if (fn_800A7F1C(p->mIdBytes[2]) == 2 ||
                    (ball.mZ >= state->mUnknown8 - 0.3f && ball.mZ > hand.mZ - 0.15f)) {
                    Record_8011F4F8 *pRecord = fn_8011F4F8(fn_801374E0(pBall));

                    if (pRecord->mUnknownB == 1) {
                        int angle;
                        float scale;
                        Object_80039F5C *pTarget;

                        aim.mX = 0.2f;
                        aim.mY = state->mUnknown12 - ball.mZ;
                        if (aim.mY < 0.0f) {
                            aim.mY = 0.0f;
                        }
                        angle = fn_801CFE40(aim.mY, aim.mX);
                        pRecord->mUnknown10 = angle + fn_802372EC(0, 0xE38E3);
                        pRecord->mUnknown8 = (pRecord->mUnknown8 - 5) / 3 + 5;
                        pRecord->mUnknownC = state->mUnknown4 / (lbl_803ECB08 * 100621.12f);
                        if (pRecord->mUnknownC == 0.0f) {
                            float spread = pRecord->mUnknown10 / 4194304.0f;

                            pRecord->mUnknownC = spread * 0.5f + 0.5f;
                        }
                        scale = pRecord->mUnknownC / 3.0f;
                        pRecord->mUnknown0 -= pRecord->mUnknown0 * scale;
                        pRecord->mUnknown4 -= pRecord->mUnknown4 * scale;
                        fn_80102D78(p);
                        pTarget = fn_8009BCE8(&state->mRef);
                        if (pTarget != 0) {
                            Record_800B15FC *pEvent = fn_800B15FC();

                            fn_8009BD2C(pTarget, &pEvent->mUnknown0);
                            pEvent->mUnknownC = p->mMotion.mPos.mX;
                            pEvent->mUnknown10 = p->mMotion.mPos.mY;
                            pEvent->mUnknown14 = 34;
                            fn_800B1508();
                        }
                    }
                } else {
                    fn_801039D8(p);
                }
            }
            p->mUnknown778 = -1;
            p->mFlags &= ~0x1000;
            state->mUnknown30 = 0;
        } else if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 69) == 0 &&
                   fn_801BA568(p->mpUnknown796, p->mpUnknown800, 178) == 0) {
            p->mUnknown778 = -1;
            state->mUnknown30 = 0;
        } else {
            pBall = fn_80137C48(p);
            if (pBall != 0) {
                fn_80137D58(pBall, &ball);
                if (state->mUnknown12 < ball.mZ) {
                    state->mUnknown12 = ball.mZ;
                }
            }
        }
    }
    if (pAnim->mUnknown0 != -1) {
        if (state->mUnknown26 < 0) {
            state->mUnknown26 = fn_80113C18(p, state);
            state->mUnknown28 = 1;
        }
        if (pAnim->mUnknown2 != 7) {
            state->mUnknown20 = fn_800CE690(pAnim);
            state->mUnknown4 = fn_800CE73C(pAnim);
            if (state->mUnknown28 == 1) {
                if (fn_80137B40() == p) {
                    if (state->mUnknown4 >= lbl_803ECB08 * 80496.9f || lbl_803EAF91 != 0) {
                        fn_801410F4(2);
                    } else if (state->mUnknown4 >= lbl_803ECB08 * 70434.78f) {
                        fn_801410F4(1);
                    } else if (state->mUnknown4 >= lbl_803ECB08 * 60372.67f) {
                        fn_801410F4(0);
                    }
                }
                if (fn_80137B40() == p) {
                    fn_8016F6F4(p, fn_8009BCE8(&state->mRef));
                }
                state->mUnknown28 = 0;
            }
        } else {
            fn_80067E3C(45, &pOther->mMotion.mPos, pOther->mId, 0, 0, 0);
        }
        if (state->mUnknown26 == 0) {
            Object_80137ABC *pHeld = fn_80137C48(p);

            if (pHeld != 0 && pHeld == fn_801374BC() && fn_801BE648(p->mpUnknown792) != 234 &&
                fn_801BE648(p->mpUnknown792) != 238) {
                fn_801718E8(p, pOther);
            }
        }
        state->mUnknown26--;
        if (state->mUnknown26 < 0) {
            fn_800CE674(pAnim);
        }
    }
    if (state->mUnknown59 == 0 && pOtherState != 0 && state->mUnknown20 != 0xFF && pOtherState->mUnknown4 != 0xFF) {
        speed = pOtherState->mUnknown8 < state->mUnknown4 ? state->mUnknown4 : pOtherState->mUnknown8;
        fn_80067E3C(37, &p->mMotion.mPos, p->mId, (unsigned int)speed, state->mUnknown20, pOtherState->mUnknown4);
        state->mUnknown59 = 1;
        fn_800A3B58(p, 1, 1);
        speed = pOtherState->mUnknown8 < state->mUnknown4 ? state->mUnknown4 : pOtherState->mUnknown8;
        if (speed > lbl_803ECB08 * 100621.12f * 0.75 && fn_80137B40() == p) {
            fn_80067D4C(100, 0);
        }
    }
    if (fn_801787A0() != 0 && p->mIdBytes[3] == 1 && (p->mFlags & 0x1000)) {
        p->mFlags &= ~0x1000;
        pBall = fn_80137C48(p);
        if (pBall != 0) {
            fn_8013791C(pBall, 5, 0);
        }
    }
    if (p->mUnknown9[0] != 1) {
        p->mFlags &= ~0x82008;
        fn_80143EBC(p, fn_8009BCE8(&state->mRef));
        state->mUnknown31 = 1;
        if (state->mUnknown20 <= 10) {
            fn_801C1F94(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F05E4(0, p->mpState, &message, p);
        } else {
            fn_801C1F94(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F05E4(0, p->mpState, &message, p);
        }
    }
    if ((p->mFlags & 4) && state->mUnknown56 != 1 && state->mUnknown56 != 4) {
        result = 1;
        p->mFlags &= ~0x0409280C;
        fn_80143EBC(p, fn_8009BCE8(&state->mRef));
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
        fn_800D640C(p);
    }
    return result;
}

extern "C" int fn_80114838(Object_80039F5C *p)
{
    State_80113C20 *state = (State_80113C20 *)&p->mUnknown336;
    Input_800B6D34 input;
    Vector_80039F5C dir;
    int done = 0;
    int port = fn_800B65A0(p->mIdBytes[2]);

    fn_800B6D34(p, &input);
    if (fn_80137B40() == p && (input.mUnknown95 & 0x40)) {
        fn_800DB60C(&state->mUnknown32, p);
    } else {
        if (state->mUnknown56 == 1) {
            if (input.mUnknown95 & 0x10) {
                done = 1;
                state->mUnknown58++;
            } else {
                dir.mX = dir.mY = 0.0f;
                if (input.mUnknown4 != 0.0f || input.mUnknown8 != 0.0f) {
                    dir.mX = input.mUnknown4;
                    dir.mY = input.mUnknown8;
                } else {
                    if (input.mUnknown0 & 1) {
                        dir.mY = 1.0f;
                    }
                    if (input.mUnknown0 & 2) {
                        dir.mY = -1.0f;
                    }
                    if (input.mUnknown0 & 4) {
                        dir.mX = -1.0f;
                    }
                    if (input.mUnknown0 & 8) {
                        dir.mX = 1.0f;
                    }
                }
                if (fabsf(dir.mY) > 1e-7f || fabsf(dir.mX) > 1e-7f) {
                    int angle = fn_801CFE40(dir.mY, dir.mX) - input.mUnknown20;
                    if (fn_801784C4() != 0) {
                        angle -= 0x800000;
                    }
                    fn_80114F64(p, angle & 0xFFFFFF);
                }
            }
            if (p->mUnknown8 != 255) {
                fn_80194C5C(p->mUnknown8, lbl_803EAF98, 10);
            }
        }
        if (done == 0) {
            int mode = fn_800AD9B4();
            if (p->mIdBytes[2] == fn_80178320() || mode == 3 ||
                (mode == 2 && port != 255 && fn_800B6544(port) != p)) {
                return fn_800B7FE8(p);
            }
        }
    }
    return 0;
}

extern "C" float fn_80114EE4(Object_80039F5C *pA, Object_80039F5C *pB)
{
    float a = pA->mUnknown2904Float * lbl_803EAFA4 + pA->mRatings[2];
    float b = pB->mUnknown2904Float * lbl_803EAFA4 + pB->mRatings[5];
    float ratio = a / (a + b);

    return ratio * (lbl_803EAF9C - lbl_803EAFA0) + lbl_803EAFA0;
}

extern "C" void fn_80114F64(Object_80039F5C *p, int angle)
{
    State_80113C20 *state = (State_80113C20 *)&p->mUnknown336;
    float scale = lbl_803EAFA8;
    unsigned short key = fn_801BE648(p->mpUnknown792);
    Object_80039F5C *pOpponent = fn_80114E7C(p);
    float diff = p->mRatings[2] - pOpponent->mRatings[5];
    int delta;
    Object_80039F5C *pOther;
    int index;
    int otherIndex;

    float clamped = diff < -lbl_803EAFB0 ? -lbl_803EAFB0 : (diff > lbl_803EAFB0 ? lbl_803EAFB0 : diff);
    diff = (clamped + lbl_803EAFB0) / (lbl_803EAFB0 + lbl_803EAFB0);
    scale *= diff;
    if (scale < lbl_803EAFAC) {
        scale = lbl_803EAFAC;
    }
    switch (state->mUnknown67) {
    case 4:
    case 5:
    case 6:
        scale *= lbl_803EAFB4;
        if (scale > lbl_803EAFB8) {
            scale = lbl_803EAFB8;
        }
        break;
    }
    delta = fn_801CFFD0(angle, p->mMotion.mFacing);
    if (((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
        int limit = -(int)(scale * 46603.38f);

        delta = -delta;
        if (delta < limit) {
            delta = limit;
        }
    } else {
        int limit = (int)(scale * 46603.38f);

        if (delta > limit) {
            delta = limit;
        }
    }
    pOther = fn_8009BCE8(&state->mRef);
    index = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, key, 0);
    otherIndex = fn_801BA5A8(pOther->mpUnknown796, pOther->mpUnknown800, key, 0);
    if (otherIndex != 0xFFFF && index != 0xFFFF) {
        Record_800D81C8 *pOtherRecord;
        Block_80114F64 *pBlock;
        Point_8017886C offset;
        Point_8017886C rotated;
        Point_8017886C target;
        Point_8017886C shift;

        p->mMotion.mFacing = (p->mMotion.mFacing + delta) & 0xFFFFFF;
        p->mpUnknown796->mUnknown8 = p->mMotion.mFacing;
        p->mpUnknown800[index].mUnknownC = (p->mpUnknown800[index].mUnknownC + delta) & 0xFFFFFF;
        pOtherRecord = &pOther->mpUnknown800[otherIndex];
        pBlock = (Block_80114F64 *)fn_801BE60C(pOther->mpUnknown792, key);
        if (pBlock->mUnknown28 == 0) {
            fn_80227690(&offset, &pOther->mMotion.mPos, &p->mMotion.mPos);
            fn_80227384(&rotated, &offset, delta);
            fn_80227638(&pOther->mMotion.mPos, &rotated, &p->mMotion.mPos);
            pOther->mMotion.mFacing = (pOther->mMotion.mFacing + delta) & 0xFFFFFF;
            pOtherRecord->mUnknownC = (pOtherRecord->mUnknownC + delta) & 0xFFFFFF;
        } else {
            fn_80227690(&target, &pBlock->mUnknown4, &p->mMotion.mPos);
            fn_80227384(&rotated, &target, delta);
            fn_80227690(&shift, &rotated, &target);
            fn_800DF134(pOther, shift, delta, key);
        }
    }
}

extern "C" float fn_80115248(Object_80039F5C *p, Object_80039F5C *pTarget, unsigned char kind)
{
    float score = 1.0f;
    float part = 0.0f;
    int found = 0;
    Object_80039F5C *pDefender = fn_800FB9D4(pTarget);
    Point_8017886C delta;
    Point_8017886C offset;
    unsigned char i;
    unsigned int count;
    int angle;

    if (pDefender != 0) {
        fn_80227690(&delta, &pDefender->mMotion.mPos, &pTarget->mMotion.mPos);
        if (fn_802270A4(&delta) < 5.0f && !(pDefender->mFlags & 0x20000)) {
            fn_80227690(&delta, &p->mMotion.mPos, &pTarget->mMotion.mPos);
            part = fn_802270A4(&delta) * 0.5f;
            if (part > 1.0f) {
                part = 1.0f;
            }
            found = 1;
            switch (pDefender->mUnknown2914) {
            case 13:
            case 14:
            case 15:
                part += part;
                break;
            }
        }
    }
    score += part;
    part = 0.0f;
    count = fn_80178D18(p->mIdBytes[2]);
    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);
        float distance;

        fn_80227690(&delta, &pOther->mMotion.mPos, &pTarget->mMotion.mPos);
        distance = fn_802270A4(&delta);
        if (pOther != p) {
            fn_80227690(&delta, &pOther->mMotion.mPos, &pTarget->mMotion.mPos);
            switch (pOther->mpState->mId) {
            case 92:
                if (((State_80115248 *)&pOther->mUnknown336)->mpUnknown20 == pTarget &&
                    fn_80227890(&pOther->mMotion.mPos, &pTarget->mMotion.mPos) < 25.0f) {
                    found = 1;
                }
                break;
            case 40: {
                State_80115248 *pState = (State_80115248 *)&pOther->mUnknown336;

                fn_8009EAB0(pOther, fn_800C1180(pOther));
                if (fn_8009EF6C(pTarget) != 0) {
                    int side = pTarget->mMotion.mPos.mX - pOther->mMotion.mPos.mX >= 0.0f ? 0x800000 : 0;

                    if ((fn_801CFFD0(pTarget->mMotion.mUnknown32, side) < 0x355555 &&
                         (fn_801CFFD0(pOther->mMotion.mUnknown32, side) > 0x355555 ||
                          pState->mUnknown12 < 1.0f)) ||
                        distance < 7.0f) {
                        found = 1;
                    }
                }
                break;
            }
            case 85:
                if (distance < 2.5f) {
                    found = 1;
                }
                break;
            }
        } else if (fn_8009EF6C(pTarget) != 0) {
            int side = pTarget->mMotion.mPos.mX - p->mMotion.mPos.mX >= 0.0f ? 0x800000 : 0;

            if (fn_801CFFD0(pTarget->mMotion.mUnknown32, side) < 0x355555) {
                found = 1;
            }
        }
    }
    if (found == 0) {
        part = 500.0f;
    }
    score += part;
    part = 0.0f;
    fn_8009EAB0(p, p->mpState->mUnknown1);
    if (fn_8009EC60(0, 0) == pTarget) {
        float dy = pTarget->mMotion.mPos.mY - fn_8009EC60(1, 0)->mMotion.mPos.mY;

        dy = dy < 4.0f ? 4.0f : (dy > part ? part : dy);
        part = dy;
    }
    score += part;
    part = 0.0f;
    angle = fn_801CFFD0(pTarget->mMotion.mUnknown32, 0x400000);
    if (angle <= 0x1C71C6) {
        part = 40.0f - angle * 2.1457672e-05f;
        if (part > 4.0f) {
            part = 4.0f;
        }
    }
    if (part > 30.0f) {
        part = 30.0f;
    }
    score += part;
    if (pTarget->mMotion.mPos.mY > fn_80178A2C()) {
        fn_80227690(&offset, &pTarget->mMotion.mPos, &p->mMotion.mPos);
        score += fn_802270A4(&offset) * 4.0f;
    }
    return score;
}

extern "C" void fn_8011569C(Object_80039F5C *p)
{
    float bonus;
    Point_8017886C zone;
    Point_8017886C target;
    Point_8017886C ball;
    Point_8017886C spot;
    Vector_80039F5C ballPos;
    float xs[4];
    float weights[4];
    float total = 0.0f;
    float minX = 1000.0f;
    float maxX = -1000.0f;
    const float kAdvance = 4.0f;
    const float kCruise = 0.8f;
    const float kDepth = 10.0f;
    const float kSlow = 0.6f;
    const float kMargin = 2.0f;
    unsigned char numPlayers = 0;
    unsigned char numBelow = 0;
    unsigned char numAbove = 0;
    State_8011569C *pState = (State_8011569C *)&p->mUnknown336;
    signed char side;
    int count;

    bonus = 0.0f;
    zone.mX = 0.0f;
    zone.mY = 0.0f;
    target.mX = 0.0f;
    target.mY = 0.0f;
    ball.mX = 0.0f;
    ball.mY = 0.0f;
    spot.mX = 0.0f;
    spot.mY = 0.0f;
    ballPos.mX = 0.0f;
    ballPos.mY = 0.0f;
    ballPos.mZ = 0.0f;
    target.mX = 0.0f;
    target.mY = 0.0f;
    side = p->mpState->mUnknown1;
    count = fn_8009EAB0(p, side);
    fn_8009E9EC(p, side, &zone);
    Zone_8011569C *pZone = &((Field_8011569C *)fn_8011F4EC())->mZones[side];
    float low = pZone->mLow;
    float high = pZone->mHigh;
    ball = fn_80177FE0();
    fn_80137D58(fn_801374BC(), &ballPos);
    if (count != 1) {
        pState->mUnknown17 = 0;
    }
    fn_80116AB8(p);

    if (count == 0) {
        unsigned char i;
        for (i = 0; i < 3; i++) {
            int index = fn_80168E00(fn_80178308(), i, 0);
            if (index != 0xFF) {
                numPlayers++;
                Object_80039F5C *pOther = fn_80039F5C(fn_80178308(), index);
                if (pOther->mMotion.mPos.mX > high) {
                    numAbove++;
                } else if (pOther->mMotion.mPos.mX < low) {
                    numBelow++;
                }
                if (pOther->mMotion.mPos.mX < minX) {
                    minX = pOther->mMotion.mPos.mX;
                }
                if (pOther->mMotion.mPos.mX > maxX) {
                    maxX = pOther->mMotion.mPos.mX;
                }
            }
        }
        if (numPlayers == 0) {
            minX = -7.0f;
            maxX = 7.0f;
        }
        if (numPlayers != 0 && numBelow == numPlayers) {
            target.mX = low;
        } else if (numPlayers != 0 && numAbove == numPlayers) {
            target.mX = high;
        } else {
            float x;
            if (fn_8009EFDC(side) != 0) {
                if (zone.mX < fn_80177FE0().mX) {
                    x = minX < zone.mX ? zone.mX : minX;
                } else {
                    x = maxX > zone.mX ? zone.mX : maxX;
                }
            } else {
                x = zone.mX;
            }
            target.mX = x;
        }
        target.mY = ball.mY + kDepth;
        pState->mUnknown12 = kSlow;
        fn_80116410(p, 0, pState, &target);
        if (ball.mY > fn_80178A2C() - 5.0f) {
            Object_80039F5C *pCarrier = fn_80137B40();
            if (pCarrier != 0 && (pCarrier->mFlags & 0x8000)
                && ((pCarrier->mMotion.mPos.mX < ball.mX && p->mMotion.mPos.mX < ball.mX)
                    || (pCarrier->mMotion.mPos.mX > ball.mX && p->mMotion.mPos.mX > ball.mX))) {
                float gap = ball.mY - pCarrier->mMotion.mPos.mY;
                int a = fn_800DC21C(pCarrier);
                int b = fn_800DC080(pCarrier);
                if ((a != 0 || b != 0 || fn_801783AC(0) != 0) && gap < 8.0f) {
                    pState->mUnknown20 = 1;
                }
            }
        }
    } else {
        if (count == 1) {
            Object_80039F5C *pOther = fn_8009EC60(0, &spot);
            int covered = 0;
            int handled = 0;

            if (pOther->mpState->mId != 20) {
                pState->mUnknown17 = 0;
            } else if (pState->mUnknown17 == 0) {
                pState->mUnknown17 = fn_8009FD7C(p, pOther);
            }
            fn_8009F928(pOther, &spot, 12, pState->mUnknown17);
            float range;
            if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0x400000) <= 0x155554
                || fn_801CFFD0(pOther->mMotion.mUnknown32, 0xC00000) <= 0x155554) {
                range = 1.5f;
            } else {
                range = 6.0f;
            }
            fn_80116880(p, pOther, &spot.mX, &target.mX, range);
            Object_80039F5C *pMark = fn_800FB9D4(pOther);
            if (pMark != 0) {
                Point_8017886C delta;
                fn_80227690(&delta, &pMark->mMotion.mPos, &pOther->mMotion.mPos);
                if (fn_802270A4(&delta) < 5.0f && !(pMark->mFlags & 0x20000)) {
                    covered = 1;
                }
            }
            if (covered == 0 && fn_801167C4(pOther, p) != 0) {
                covered = 1;
            }
            if (covered != 0) {
                handled = fn_80116410(p, pOther, pState, &target);
                if (target.mY < pOther->mMotion.mPos.mY) {
                    handled = 0;
                }
            }
            if (handled == 0) {
                Point_8017886C delta;
                float dy = pOther->mMotion.mPos.mY - p->mMotion.mPos.mY;
                fn_80227690(&delta, &spot, &p->mMotion.mPos);
                float dist = fn_802270A4(&delta);
                float dx = fabsf(spot.mX - p->mMotion.mPos.mX);
                dx *= fn_801CFB18(pOther->mMotion.mUnknown32);
                if (dx < 0.0f) {
                    dx = 0.0f;
                }
                dx *= 0.75f;
                int ahead = fn_80116984(p, pOther, &bonus);
                dx += bonus;
                target.mY = pOther->mMotion.mUnknown44 * 60.0f * lbl_803EAFCC + spot.mY + kMargin + dx;
                if (target.mY < p->mMotion.mPos.mY
                    && fn_801CFFD0(pOther->mMotion.mUnknown32, 0x400000) <= 0x155554
                    && spot.mY > p->mMotion.mPos.mY - lbl_803EAFBC) {
                    target.mY = p->mMotion.mPos.mY + kMargin;
                }
                if (ahead != 0) {
                    pState->mUnknown12 = 1.0f;
                } else if (dy > -2.0f) {
                    pState->mUnknown12 = p->mMotion.mPos.mY < spot.mY + 5.0f ? 1.0f : kCruise;
                } else if (dy > -5.0f && dist > 8.0f) {
                    pState->mUnknown12 = 1.0f;
                } else if (dy > -7.0f) {
                    pState->mUnknown12 = dist > 12.0f ? 1.0f : kSlow;
                } else {
                    int moving = 1;
                    if ((short)fn_8011F4E0()->mUnknown2 < 0
                        && (pOther->mMotion.mUnknown44 <= fabsf(pOther->mMotion.mUnknown40) * 2.0f / 3.0f
                            || pOther->mMotion.mUnknown44 <= lbl_803ECB04 * 0.25f)) {
                        moving = 0;
                    }
                    if (moving == 1) {
                        target.mY = p->mMotion.mPos.mY;
                        pState->mUnknown12 = 0.4f;
                    } else {
                        pState->mUnknown12 = kSlow;
                    }
                }
            }
            if (p->mMotion.mPos.mY > fn_80178A2C()) {
                if (fabsf(target.mX - p->mMotion.mPos.mX) > 1.0f) {
                    pState->mUnknown12 = 1.0f;
                } else if (pState->mUnknown12 != 1.0f) {
                    pState->mUnknown12 = kCruise;
                }
            } else if (pState->mUnknown12 < kCruise && fabsf(target.mX - p->mMotion.mPos.mX) > kMargin) {
                pState->mUnknown12 = kCruise;
            }
        } else {
            Object_80039F5C *pOther = 0;
            unsigned int i;

            for (i = 0; i < count; i++) {
                Point_8017886C pos;
                weights[i] = fn_80115248(p, fn_8009EC60(i, &pos), count);
                xs[i] = pos.mX;
                if (xs[i] > maxX) {
                    maxX = xs[i];
                }
                if (xs[i] < minX) {
                    minX = xs[i];
                }
            }
            for (i = 0; i < count; i++) {
                total += weights[i];
            }
            for (i = 0; i < count; i++) {
                pOther = fn_8009EC60(i, &spot);
                if (weights[i] / total < kCruise || weights[i] < 500.0f) {
                    pOther = 0;
                } else {
                    break;
                }
            }
            Object_80039F5C *pLeader = pOther;
            if (pOther == 0) {
                pOther = fn_8009EC60(0, &spot);
            }
            if (pLeader == 0) {
                float halfSpread = (maxX - minX) * 0.5f;
                target.mX = halfSpread;
                for (i = 0; i < count; i++) {
                    target.mX += (xs[i] - halfSpread) * (weights[i] / total);
                }
            } else {
                fn_80116880(p, pOther, &spot.mX, &target.mX, 1.5f);
            }
            float dx = fabsf(spot.mX - p->mMotion.mPos.mX);
            dx *= fn_801CFB18(pOther->mMotion.mUnknown32);
            if (dx < 0.0f) {
                dx = 0.0f;
            }
            dx *= 0.75f;
            int ahead = fn_80116984(p, pOther, &bonus);
            dx += bonus;
            target.mY = pOther->mMotion.mUnknown44 * 60.0f * lbl_803EAFCC + spot.mY + kMargin + dx;
            int angle = fn_801CFFD0(pOther->mMotion.mUnknown32, 0x400000);
            if (target.mY < p->mMotion.mPos.mY && angle <= 0x155554
                && spot.mY > p->mMotion.mPos.mY - lbl_803EAFBC) {
                target.mY = p->mMotion.mPos.mY + kMargin;
            }
            float dy = target.mY - p->mMotion.mPos.mY;
            if (ahead != 0) {
                pState->mUnknown12 = 1.0f;
            } else if (angle <= 0x2E38E2) {
                if (dy > kMargin) {
                    if (p->mMotion.mPos.mY < pOther->mMotion.mPos.mY + kMargin
                        && p->mMotion.mPos.mY < fn_80178A2C()) {
                        pState->mUnknown12 = 1.0f;
                    } else {
                        pState->mUnknown12 = kCruise;
                    }
                } else if (dy > -2.0f) {
                    if (pOther->mMotion.mUnknown44 > fabsf(pOther->mMotion.mUnknown40) * 2.0f / 3.0f
                        && pOther->mMotion.mUnknown44 > lbl_803ECB04 * 0.25f) {
                        pState->mUnknown12 = kSlow;
                    } else {
                        pState->mUnknown12 = 0.4f;
                    }
                } else {
                    pState->mUnknown12 = 0.4f;
                }
            } else if (dy <= 0.0f && dy > -2.0f) {
                pState->mUnknown12 = 1.0f;
            } else {
                pState->mUnknown12 = kCruise;
            }
            if (p->mMotion.mPos.mY > fn_80178A2C()) {
                if (fabsf(target.mX - p->mMotion.mPos.mX) > 1.0f) {
                    pState->mUnknown12 = 1.0f;
                } else if (pState->mUnknown12 != 1.0f) {
                    pState->mUnknown12 = kCruise;
                }
            } else if (pState->mUnknown12 < kCruise && fabsf(target.mX - p->mMotion.mPos.mX) > kMargin) {
                pState->mUnknown12 = kCruise;
            }
        }
    }

    target.mX = target.mX < low + kMargin ? low + kMargin : (target.mX > high - kMargin ? high - kMargin : target.mX);
    if (p->mMotion.mPos.mY > fn_80178A44() - 6.0f - 1.0f) {
        pState->mUnknown12 = kCruise;
    }
    target.mY = target.mY > fn_80178A44() - 6.0f ? fn_80178A44() - 6.0f : target.mY;
    switch (fn_8009E9A4()) {
    case 1:
        target.mY += kAdvance;
        break;
    case 2:
        target.mY -= 1.0f;
        break;
    }
    fn_80227690(&target, &target, &p->mMotion.mPos);
    pState->mUnknown8 = fn_801CFE40(target.mY, target.mX);
    if (fn_802270A4(&target) < 1.0f) {
        pState->mUnknown4 = 0xC00000;
        pState->mUnknown12 = 0.0f;
    }
}
