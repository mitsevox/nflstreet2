/* Player state 30: a player runs along the heading and for the distance given by the
   message that started the state, with rating-based chances to break off for the ball
   carrier or play a pass that is in the air. */

#include "engine/cu_801B9F00.h"
#include "game/StyleTracker.h"
#include "game/OptionRunControl.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/AnimMomentumActor.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Table_80089904.h"
#include "game/AudmonEvent.h"
#include "game/cu_8003108C.h"
#include "game/Ball.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_8007F828.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80227638.h"
#include "game/fn_802270D4.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_801BE60C.h"
#include "game/fn_800B65A0.h"
#include "game/fn_800F06F4.h"
#include <math.h>

extern "C" {
void fn_800A3B58(Object_80039F5C *p, int a, int b);
void fn_800A5A8C(int a, void *pA, void *pB);
int fn_800A8444(int team);
int fn_800A8740(void);
int fn_800ABDA4(int team);
short fn_800ACC80(Object_80039F5C *p, short value);
int fn_800B76E8(Object_80039F5C *p);
void fn_800B8344(Object_80039F5C *p);
void PlayerMoveUpdateRun(Object_80039F5C *p);
void PlayerMoveGetRunMode(Object_80039F5C *p, unsigned char *pOut);
int PlayerMoveTryStartRun(Object_80039F5C *p);
int fn_8009AD30(Object_80039F5C *p, int value);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800FD68C(Message_800F01CC *, void *, void *);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
void fn_8011168C(Object_80039F5C *p);
int fn_80110824(Object_80039F5C *p, int a, int b, int c);
int fn_8011E9B4(Object_80039F5C *p);
void fn_8012311C(Object_80039F5C *p, Plan_80121264 *pPlan, int angle);
Entry_801230B8 *fn_80123174(Plan_80121264 *pPlan);
void fn_8012430C(Directions_8012430C *pOut, int kind, Object_80039F5C *p);
unsigned char fn_801243E0(Directions_8012430C *pValues, int angle);
void fn_8012B2E0(Object_80039F5C *p, Point_8017886C *pOut);
void fn_8012C3A4(Object_80039F5C *p);
void fn_8012CB98(int a, unsigned char b, int angle, Point_8017886C *pOut);
void fn_8012CEF4(Object_80039F5C *p, OptionRunControl_t *pControl);
void fn_8012CFA0(Object_80039F5C *p);
void fn_8012D258(Object_80039F5C *p);
void fn_8012D4FC(Object_80039F5C *p, int mode);
void fn_8012D8A8(Object_80039F5C *p, OptionRunControl_t *pControl, int *pMode, Entry_801230B8 *pEntry);
int fn_8012FC08(Object_80039F5C *p, OptionRunControl_t *pControl);
int fn_8012FDDC(Object_80039F5C *p, OptionRunControl_t *pControl);
void CamGameSetModeAll(int a);
void PassIconsHide(void);
int PassIconsAreShown(void);
void PassIconsClearReplayFlag(void);
int fn_801486A0(void);
int fn_80178320(void);
float AnimSeqGetOpcodeTime(void *p, int key);
float AnimSeqGetTimeToOpcode(AnimSeq_t *p, int key);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80227890(void *pA, void *pB);
float fn_8022710C(void *pV);

extern Table_80089904 lbl_8031AABC;
}

extern "C" int fn_8012CCA0(Object_80039F5C *p);

#ifdef DECOMP_COMPARE
extern "C" {
int fn_80177F70(void);
float fn_80178298(void);
float fn_80178A08(void);
float fn_80178A2C(void);
float fn_80178A44(void);
float fn_80178A68(void *p);
float PlyrMoveGetRatedSpeed(Object_80039F5C *p, float a, float b);
void fn_8012BB6C(float *pA, float *pB);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
void fn_8009BD60(Object_80039F5C *p);
int fn_800B83F4(Object_80039F5C *p);
int CarrierMoveStart(Object_80039F5C *p, int a);
int CarrierMovePickKind(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_800C4D54(Object_80039F5C *p);
int fn_80112928(Object_80039F5C *p);
int fn_8011F1CC(void);
int fn_8011F1A4(void);
int fn_8011F4C8(void);
int fn_80177C38(void);
float fn_801CFB18(int angle);
int fn_800E885C(Object_80039F5C *p);
int fn_800E815C(Object_80039F5C *p, int a, int b);
int fn_80111090(Object_80039F5C *p, int a);
int BallStateGetPrev(Ball_t *p, int *pOut);
int BallStateGet(Ball_t *p, int *pOut);
float fn_80260FE8(float a);
float fn_80260E24(float a);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, unsigned char a, unsigned char count, int angle, float *pOut, int b);
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, unsigned char a, unsigned char count, float *pOut, int b);
int fn_8011F32C(void);
int fn_80178308(void);
int fn_80178BA4(int team);
int PlayerMoveGetKind(Object_80039F5C *p);
float fn_801CFB94(int angle);
Object_80039F5C *fn_80105384(Object_80039F5C *p, int mode, Vector_80039F5C *pOut);
int OptionRunCanPitchTo(Object_80039F5C *p, Vector_80039F5C *pOut, Object_80039F5C *pOther);
int fn_801066D0(Object_80039F5C *p, Object_80039F5C *pOther, int a);
float fn_8012506C(Object_80039F5C *p, int kind);
int fn_8011F59C(int a);
int fn_80105E90(Object_80039F5C *p, Object_80039F5C *pOther, int kind);
int fn_801067D8(Object_80039F5C *p);
int fn_801064A4(Object_80039F5C *p, int a);
int fn_801787A0(void);
int fn_801784C4(void);
struct Object_80040818;
Object_80040818 *fn_80040FD4(Vector_80039F5C *p, int a, float *pOut);
float fn_800AD168(int team, float value);
float fn_80237260(int a);
int fn_800F22D8(Object_80039F5C *p, int a, int b, int c);
float fn_8011F4D4(void);
int fn_801783AC(int a);
int fn_8012E670(Object_80039F5C *, Object_80039F5C *, int, int, int, float);
int fn_8012EAF8(Object_80039F5C *, Object_80039F5C *, int, int, int, float);
extern int lbl_803EB118;
extern float lbl_803EB11C, lbl_803EB120, lbl_803EB124;
extern unsigned char lbl_802DB05C[21];
Object_80039F5C *fn_80124CE4(Object_80039F5C *p, int team, float *pOut, int angle, float a, int facing, float b);
extern float gPlyrMoveFwdSpeed;
}

extern "C" int fn_800F2828(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, Object_80039F5C **pOut);
extern "C" int fn_80110EB0(Object_80039F5C *p, Object_80039F5C *pOther);

extern "C" void fn_8009A8D4(void *p);
extern "C" int fn_80103D6C(Object_80039F5C *p);
extern "C" unsigned char fn_800C13A0(Object_80039F5C *p, unsigned char *pA, unsigned char *pB);

extern "C" int fn_8009FB60(Object_80039F5C *p);
extern "C" int fn_800A5C04(Object_80039F5C *p, int a, int b);
extern "C" float fn_8016B938(void);
extern "C" float fn_8016B974(void);
extern "C" int fn_800E1584(Object_80039F5C *p);
extern "C" int fn_8009E180(Object_80039F5C *p);
extern "C" int fn_800F2C1C(Object_80039F5C *p, int a);
extern "C" int fn_800E6AC8(Object_80039F5C *p, int a);

extern "C" Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float a, float b, int facing);

extern "C" int PlayBookGetReceiver(int team, int a, unsigned char *pOut);

#endif

extern "C" {
int fn_8012A6B0(Object_80039F5C *p);
int fn_8012A824(Object_80039F5C *p, float a, float b);
int fn_8012AACC(Point_8017886C *out, Object_80039F5C *p, float lower, float upper);
void fn_8012B268(Object_80039F5C *p);
void fn_8012B2E0(Object_80039F5C *p, Point_8017886C *pOut);
int fn_8012B3EC(Object_80039F5C *p);
int fn_8012B654(Object_80039F5C *p);
void fn_8012BB6C(float *pA, float *pB);
int fn_8012BCC8(Object_80039F5C *p);
int fn_8012BE28(Object_80039F5C *p);
void fn_8012C3A4(Object_80039F5C *p);
Info_80089904 *fn_8012C4B4(int a, int b);
void fn_8012C548(Object_80039F5C *p);
void fn_8012C5A8(Object_80039F5C *p, int value);
void fn_8012C648(Object_80039F5C *p, int angle);
int fn_8012C7E0(Object_80039F5C *p);
int fn_8012C874(Object_80039F5C *p);
int fn_8012CA78();
void fn_8012CA80(unsigned char *p);
int fn_8012CAA4(Object_80039F5C *p);
int fn_8012CAAC(Object_80039F5C *p);
int fn_8012CAB4(Object_80039F5C *p);
int fn_8012CB50(Message_800F01CC *pMessage);
void fn_8012CB98(int a, unsigned char b, int angle, Point_8017886C *pOut);
int fn_8012CC04(unsigned char a);
int fn_8012CC50(Object_80039F5C *p);
int fn_8012CCA0(Object_80039F5C *p);
void fn_8012CD4C(Object_80039F5C *p, Point_8017886C *pOut);
float fn_8012CD60(Object_80039F5C *p, float value);
int fn_8012CE60(Object_80039F5C *p);
void fn_8012CEF4(Object_80039F5C *p, OptionRunControl_t *pControl);
void fn_8012CFA0(Object_80039F5C *p);
int fn_8012D1E4(Object_80039F5C *p);
void fn_8012D258(Object_80039F5C *p);
void fn_8012D4FC(Object_80039F5C *p, int mode);
void fn_8012D8A8(Object_80039F5C *p, OptionRunControl_t *control, int *pMode, Entry_801230B8 *entry);
void fn_8012DDCC(Object_80039F5C *p, OptionRunControl_t *control, int);
int fn_8012E590(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8012E670(Object_80039F5C *p, Object_80039F5C *, int, int turn, int, float distance);
int fn_8012EA14(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8012EAF8(Object_80039F5C *p, Object_80039F5C *pOther, int angle, int turn, int, float distance);
int fn_8012EE90(Object_80039F5C *p, Object_80039F5C *pOther, int a, int angle, int b, float distance);
int fn_8012EF94(Object_80039F5C *p, Object_80039F5C *pOther, int a, int angle, int b, float distance);
int fn_8012F11C(Object_80039F5C *p, Object_80039F5C *pOther, int angle, int a, int b, float distance);
int fn_8012F2E0(Object_80039F5C *p, Object_80039F5C *pOther, int a, int b, int c, float d);
int fn_8012F2E8(Object_80039F5C *p, Object_80039F5C *pUnused, int a, int b, int c, float d);
int fn_8012F524(Object_80039F5C *p);
void fn_8012F5A0(Object_80039F5C *p, OptionRunControl_t *control, OptionRunMove_t *block);
void fn_8012F89C(Object_80039F5C *p, OptionRunControl_t *control, int mode);
int fn_8012FA64(Object_80039F5C *p);
int fn_8012FC08(Object_80039F5C *p, OptionRunControl_t *control);
int fn_8012FDDC(Object_80039F5C *p, OptionRunControl_t *pControl);
int fn_8012FEAC(Object_80039F5C *p);
int fn_8012FF30(Object_80039F5C *p);
int fn_8012FF5C(Object_80039F5C *p);
int fn_8013028C(Object_80039F5C *p);
int fn_80130318(Object_80039F5C *p);
void fn_80130338(Object_80039F5C *p, OptionRunControl_t *pControl);
}

#ifdef DECOMP_COMPARE
struct State_8012BCC8 {
    Point_8017886C mUnknown0;
    float mUnknown8;
    int mUnknown12;
    int mUnknown16;
    union {
        int mUnknown20Word;
        struct { unsigned short mUnknown20; unsigned short mUnknown22; };
    };
};
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012BCC8(Object_80039F5C *p)
{
    State_8012BCC8 *state = (State_8012BCC8 *)&p->mUnknown336;

    if (fn_800B65A0(p->mIdBytes[2]) == 255 && fn_8011F1CC()
        && fn_800ABDA4(p->mIdBytes[2]) == 0
        && (p->mUnknown2914 > 12 || p->mUnknown2914 < 10)) {
        Message_800F01CC message;

        fn_801C1F94(&message, 0, 4);
        message.mId = 85;
        message.mUnknown1[0] = 96;
        message.mUnknown1[1] = 180;
        fn_800F00D4(0, p->mpState, &message, p);
        return 1;
    }
    state->mUnknown0.mX = p->mMotion.mPos.mX;
    state->mUnknown0.mY = p->mMotion.mPos.mY;
    state->mUnknown8 = (p->mpState->mUnknown1 & 7) * (1.0f / 7.0f)
                      + (p->mpState->mUnknown1 >> 3);
    state->mUnknown12 = (p->mpState->mUnknown2 << 17) & 0xFFFFFF;
    state->mUnknown16 = 0;
    state->mUnknown20Word = 0;
    p->mUnknown512.mUnknown0 = 0.0f;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
    return 0;
}
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012BE28(Object_80039F5C *p)
{
    State_8012BCC8 *state = (State_8012BCC8 *)&p->mUnknown336;
    Point_8017886C ball = fn_80177FE0();
    Object_80039F5C *carrier = BallGetCurrentHolder();
    if (fn_8009FB60(p)) {
        return 1;
    }
    fn_8010A2DC(p, 0, -1);
    if (fn_800A5C04(p, state->mUnknown12, state->mUnknown12) || (p->mFlags & 0x4000)) {
        return 0;
    }
    if (--state->mUnknown16 < 0) {
        int rating = 255 - p->mRatings[5];
        if (rating < 0) {
            rating = 0;
        }
        state->mUnknown16 += fn_802372EC(0, rating >> 4) + (rating >> 5);
        if (carrier && fn_800B65A0(p->mIdBytes[2]) != 255
            && fn_800B65A0(carrier->mIdBytes[2]) == 255 && !fn_80177C38()) {
            int previous = state->mUnknown16;
            float first = (float)previous;
            float factor = fn_8016B938();
            float current = (float)state->mUnknown16;
            if (!(first > current * factor)) {
                state->mUnknown16 = previous - (int)current;
            } else {
                state->mUnknown16 = previous - (int)((float)state->mUnknown16 * fn_8016B938());
            }
            if (fn_8011F1CC() && (carrier->mFlags & 0x8000)) {
                previous = state->mUnknown16;
                first = (float)previous;
                factor = fn_8016B974();
                current = (float)state->mUnknown16;
                if (!(first > current * factor)) {
                    state->mUnknown16 = previous - (int)current;
                } else {
                    state->mUnknown16 = previous - (int)((float)state->mUnknown16 * fn_8016B974());
                }
            }
        }
        if (fn_800E1584(p)) {
            return 0;
        }
        int kind = fn_8009E180(p);
        int chance;
        int attempt = 0;
        if (kind > 1) {
            chance = p->mRatings[5] >> 3;
            if (p->mUnknown1032 == 4) {
                chance += chance;
            }
            if (!(p->mMotion.mPos.mY >= ball.mY - 1.0f)) {
                chance <<= 2;
            }
            attempt = 1;
        } else if (p->mUnknown1032 == 4
            && fn_8009BCE8(&p->mUnknown1036)->mUnknown1052 == 1) {
            chance = p->mRatings[5] >> 2;
            attempt = 1;
        }
        if (attempt && fn_802372EC(0, 100) < (unsigned int)chance) {
            Message_800F01CC message;
            fn_801C1F94(&message, 0, 4);
            message.mId = 2;
            fn_800F053C(0, p->mpState, &message, p);
            return 1;
        }
    }
    Vector_80039F5C delta;
    fn_80227690(&delta, &p->mMotion.mPos, &state->mUnknown0);
    if (fn_802270A4(&delta) > state->mUnknown8) {
        return 1;
    }
    p->mUnknown512.mUnknown15 = MathAngleDiff(p->mMotion.mFacing, state->mUnknown12) <= 0x11C71B;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = state->mUnknown12;
    p->mUnknown512.mUnknown0 = 1.0f;
    p->mUnknown512.mUnknown4 = state->mUnknown12;
    Ball_t *pBall = BallGetCurrent();
    if (BallStateGet(pBall, 0) == 4) {
        BallGetPosition(pBall, &delta);
        if (!(delta.mZ >= 3.3f)) {
            Vector_80039F5C direction;
            BallGetVelocity(pBall, &direction);
            fn_80227690(&delta, &p->mMotion.mPos, &delta);
            int directionAngle = fn_801CFE40(direction.mY, direction.mX);
            int deltaAngle = fn_801CFE40(delta.mY, delta.mX);
            if (MathAngleDiff(directionAngle, deltaAngle) <= 0x155554
                && fn_802372EC(0, 100) <= 4 && fn_800F2C1C(p, 0)) {
                return 0;
            }
        }
    }
    if (--state->mUnknown20Word <= 0) {
        int ratings = p->mRatings[5] + p->mRatings[9];
        if (ratings > 510) {
            ratings = 510;
        }
        state->mUnknown20Word = 31 - ratings / 32;
        if (fn_802372EC(0, 100) <= 24 && p->mUnknown1032 == 4) {
            fn_8009BCE8(&p->mUnknown1036);
            if (fn_800E6AC8(p, 8)) {
                return 0;
            }
        }
    }
    return 0;
}
#endif
