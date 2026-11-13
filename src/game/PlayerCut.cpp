/* Player state 20: a player plants and cuts to a new direction with a table-driven
   animation, then hands over to the next state or keeps running on his facing. Also holds
   the lookups other code uses to read the cut table and the cut in progress. */

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
#include "game/GameOptions.h"
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
struct BigObj_t;
BigObj_t *BigObjFindNearestOfType(Vector_80039F5C *p, int a, float *pOut);
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
int DirectedRunEnter(Object_80039F5C *p);
int DirectedRunUpdate(Object_80039F5C *p);
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

/* Player block at +336 as used by fn_8012C548, fn_8012C7E0, fn_8012CAA4,
   fn_8012CAAC and fn_8012CD4C. Only the accessed fields are declared; the
   size is unknown. */
struct State_8012C7E0 {
    Point_8017886C mUnknown0;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
};

#ifdef DECOMP_COMPARE
extern "C" void fn_8012C3A4(Object_80039F5C *p)
{
    State_8012C7E0 *state = (State_8012C7E0 *)&p->mUnknown336;

    p->mUnknown512.mUnknown14 = 6;
    p->mUnknown512.mUnknown4 = state->mUnknown12;
    p->mUnknown512.mUnknown0 = 1.0f;
    p->mUnknown512.mUnknown8 = state->mUnknown12;
    fn_8009BD60(p);
    p->mUnknown1008.mUnknown0 = p->mpState->mUnknown1;
    p->mUnknown1008.mUnknown1 = p->mpState->mUnknown2;
    if (p->mpState->mUnknown3[0] == 1) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 198, 1.0f, p);
    } else if (p->mpState->mUnknown3[0] == 2) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 199, 1.0f, p);
    } else if (fn_800B83F4(p)) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 239, 1.0f, p);
    } else {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 153, 1.0f, p);
    }
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~1;
    p->mFlags &= ~4;
}
#endif

extern "C" Info_80089904 *fn_8012C4B4(int a, int b)
{
    unsigned int i;

    fn_801BBC3C(1, 153, &lbl_8031AABC);
    for (i = 0; i < lbl_8031AABC.mCount; i++) {
        Info_80089904 *pInfo = lbl_8031AABC.mEntries[i].mpInfo;

        if (pInfo->mType == a && pInfo->mValue == b) {
            return pInfo;
        }
    }
    return lbl_8031AABC.mEntries[0].mpInfo;
}

extern "C" void fn_8012C548(Object_80039F5C *p)
{
    State_8012C7E0 *state = (State_8012C7E0 *)&p->mUnknown336;
    Info_80089904 *pInfo = fn_8012C4B4(p->mpState->mUnknown2, p->mpState->mUnknown1);

    state->mUnknown8 = p->mMotion.mFacing & 0xFFFFFF;
    state->mUnknown12 = state->mUnknown8 + pInfo->mUnknown12 & 0xFFFFFF;
    state->mUnknown16 = 0;
}

extern "C" void fn_8012C5A8(Object_80039F5C *p, int value)
{
    Message_800F01CC message;
    int team;

    AudmonEventPostId(38, &p->mMotion.mPos, p->mId, 0, 0, 0);
    StyleTrackerOnCarrierActionTwo(p);
    fn_801C1F94(&message, 0, 4);
    message.mId = 20;
    team = p->mpState->mUnknown2;
    if (team == 4) {
        team = 1;
    }
    message.mUnknown1[1] = team;
    message.mUnknown1[0] = p->mpState->mUnknown1;
    message.mUnknown1[2] = value;
    fn_800F00D4(0, p->mpState, &message, p);
}

#ifdef DECOMP_COMPARE
extern "C" void fn_8012C648(Object_80039F5C *p, int angle)
{
    Message_800F01CC message;

    fn_801C1F94(&message, 0, 4);
    message.mUnknown1[0] = ((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000 ? 1 : 2;
    message.mUnknown1[2] = 0;
    unsigned short value = (unsigned short)fn_80260E24(fn_80260FE8((float)((float)MathAngleDiff(angle, p->mMotion.mFacing)
                                                   * 0.000021457672119140625f * (16.0 / 180.0))) * 0.5f);

    switch (value) {
    case 1: case 15: message.mUnknown1[1] = 3; break;
    case 2: case 14: message.mUnknown1[1] = 1; break;
    case 3: case 13: message.mUnknown1[1] = 4; break;
    case 4: case 12: message.mUnknown1[1] = 2; break;
    case 5: case 11: message.mUnknown1[1] = 7; break;
    case 6: case 10: message.mUnknown1[1] = 5; break;
    case 7: case 8: case 9: message.mUnknown1[1] = 11; break;
    default: return;
    }
    message.mId = 20;
    fn_800F053C(0, p->mpState, &message, p);
}
#endif

extern "C" int fn_8012C7E0(Object_80039F5C *p)
{
    State_8012C7E0 *state = (State_8012C7E0 *)&p->mUnknown336;

    state->mUnknown20 = 0;
    fn_8012C548(p);
    fn_8012C3A4(p);
    fn_8012CB98(p->mpState->mUnknown2, p->mpState->mUnknown1, state->mUnknown8 + state->mUnknown16,
                &state->mUnknown0);
    fn_80227638(&state->mUnknown0, &state->mUnknown0, &p->mMotion.mPos);
    if (fn_801BE648(p->mpUnknown792) == 153) {
        fn_800A5A8C(10, p, p);
    }
    return 0;
}

#ifdef DECOMP_COMPARE
extern "C" int fn_8012C874(Object_80039F5C *p)
{
    State_8012C7E0 *state = (State_8012C7E0 *)&p->mUnknown336;
    int animation = fn_801BE648(p->mpUnknown792);

    if (p->mFlags & 0x4000) {
        if (!p->mUnknown512.mUnknown14) {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown0 = 1.0f;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        }
        return 1;
    }
    if (p->mFlags & 1) {
        p->mFlags &= ~1;
        int value = fn_800C4D54(p);

        if (value) {
            fn_8012C5A8(p, value);
            return 1;
        }
    }
    if (p->mFlags & 4) {
        p->mFlags &= ~4;
        int angle = p->mpState[1].mId == 51 ? p->mMotion.mFacing : p->mMotion.mUnknown32;

        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = angle;
        p->mUnknown512.mUnknown0 = 1.0f;
        p->mUnknown512.mUnknown8 = angle;
        if (!p->mpState[1].mId) {
            Message_800F01CC message;

            fn_801C1F94(&message, 0, 4);
            message.mId = 21;
            fn_800F00D4(0, p->mpState, &message, p);
        }
        return 1;
    }
    if ((animation == 153 || animation == 239) && --state->mUnknown20 < 0) {
        state->mUnknown20 = (int)((int)((1.0f - p->mRatings[3] * (1.0f / 255.0f)) * 5.0f) + 2.0f);
        if (fn_80112928(p)) {
            return 0;
        }
    }
    return 0;
}
#endif

extern "C" int fn_8012CA78()
{
    return 1;
}

extern "C" void fn_8012CA80(unsigned char *p)
{
    if (p[1] == 1) {
        p[1] = 2;
    } else {
        p[1] = 1;
    }
}

extern "C" int fn_8012CAA4(Object_80039F5C *p)
{
    return ((State_8012C7E0 *)&p->mUnknown336)->mUnknown12;
}

extern "C" int fn_8012CAAC(Object_80039F5C *p)
{
    return ((State_8012C7E0 *)&p->mUnknown336)->mUnknown8;
}

extern "C" int fn_8012CAB4(Object_80039F5C *p)
{
    int angle = 0;
    int other = 0;
    State_80039F5C *pState = p->mpState;

    switch (pState->mUnknown2) {
    case 8:
    case 9: {
        int count = fn_8012CCA0(p);

        if (pState->mUnknown2 == 8 ? count <= 55 : count <= 51) {
            angle = fn_8012CAA4(p) + 0x800000 & 0xFFFFFF;
        } else {
            other = 1;
        }
        break;
    }
    default:
        other = 1;
        break;
    }
    if (other) {
        angle = fn_8012CAA4(p);
    }
    return angle;
}

extern "C" int fn_8012CB50(Message_800F01CC *pMessage)
{
    int angle = 0;
    Info_80089904 *pInfo = fn_8012C4B4(pMessage->mUnknown1[1], pMessage->mUnknown1[0]);

    if (pInfo) {
        angle = pInfo->mUnknown12 & 0xFFFFFF;
    }
    return angle;
}

#ifdef DECOMP_COMPARE
extern "C" void fn_8012CB98(int a, unsigned char b, int angle, Point_8017886C *pOut)
{
    Point_8017886C point = {0.0f, 0.0f};
    Info_80089904 *pInfo = fn_8012C4B4(a, b);

    if (pInfo) {
        point.mX = pInfo->mUnknown28;
        point.mY = pInfo->mUnknown32;
    }
    fn_80227384(pOut, &point, angle);
}
#endif

extern "C" int fn_8012CC04(unsigned char a)
{
    int result = 0;
    Info_80089904 *pInfo = fn_8012C4B4(a, 1);

    if (pInfo) {
        result = (int)pInfo->mUnknown24;
    }
    return result;
}

extern "C" int fn_8012CC50(Object_80039F5C *p)
{
    int result = 0;
    int count = fn_8012CCA0(p);
    int limit = fn_8012CC04(p->mpState->mUnknown2);

    if (limit > count) {
        result = limit - count;
    }
    return result;
}

extern "C" int fn_8012CCA0(Object_80039F5C *p)
{
    int result = 0;

    if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 153)) {
        int index = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 153, 0);
        float start = AnimSeqGetTimeToOpcode(&p->mpUnknown800[index].mUnknown4C, 0xC004);

        result = (int)(AnimSeqGetOpcodeTime(p->mpUnknown800[index].mUnknown4C.mpUnknown0, 0xC004) - start);
    }
    return result;
}

extern "C" void fn_8012CD4C(Object_80039F5C *p, Point_8017886C *pOut)
{
    State_8012C7E0 *state = (State_8012C7E0 *)&p->mUnknown336;

    pOut->mX = state->mUnknown0.mX;
    pOut->mY = state->mUnknown0.mY;
}

#ifdef DECOMP_COMPARE
extern "C" float fn_8012CD60(Object_80039F5C *p, float value)
{
    State_80039F5C *state = p->mpState;
    int limit = fn_8012CC04(state->mUnknown2);
    float fraction = 1.0f - (unsigned int)fn_8012CC50(p) / (float)(unsigned int)limit;

    switch (state->mUnknown2) {
    case 5:
        if (!(fraction < 0.8f)) {
            value = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        }
        break;
    case 11:
        if (fraction >= 0.64f) {
            value = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        }
        break;
    }
    return PlyrMoveGetRatedSpeed(p, value, 0.72f);
}
#endif
