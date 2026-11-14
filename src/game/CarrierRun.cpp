/* Player state 1: the ball carrier runs with the ball. For a computer-controlled carrier it
   steers around defenders and the field edges, sets his speed and sprint, and picks evasive
   moves (jukes, spins and the like) from a table of move tests. */

#include "engine/animchan.h"
#include "game/StyleTracker.h"
#include "game/OptionRunControl.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/AnimMomentumActor.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Table_80089904.h"
#include "game/AudmonEvent.h"
#include "game/ReplayEvent.h"
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
void GetOpenGetRunOnPoint(Object_80039F5C *p, Point_8017886C *pOut);
void PlayerCutStartAnim(Object_80039F5C *p);
void PlayerCutGetAnimOffset(int a, unsigned char b, int angle, Point_8017886C *pOut);
void CarrierRunCountRetreat(Object_80039F5C *p, OptionRunControl_t *pControl);
void CarrierRunAddSideCosts(Object_80039F5C *p);
void CarrierRunSteerToSideline(Object_80039F5C *p);
void CarrierRunPickHeading(Object_80039F5C *p, int mode);
void CarrierRunAvoidPlayer(Object_80039F5C *p, OptionRunControl_t *pControl, int *pMode, Entry_801230B8 *pEntry);
int CarrierRunCheckRunOut(Object_80039F5C *p, OptionRunControl_t *pControl);
int CarrierRunCheckBlocked(Object_80039F5C *p, OptionRunControl_t *pControl);
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

}

extern "C" int PlayerCutGetAnimTime(Object_80039F5C *p);

extern "C" {
int fn_80177F70(void);
float fn_80178298(void);
float fn_80178A08(void);
float fn_80178A2C(void);
float fn_80178A44(void);
float fn_80178A68(void *p);
float PlyrMoveGetRatedSpeed(Object_80039F5C *p, float a, float b);
void GetOpenGetDepthRange(float *pA, float *pB);
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
Object_80039F5C *fn_80105384(Object_80039F5C *p, int mode, Point_8017886C *pOut);
int OptionRunCanPitchTo(Object_80039F5C *p, Point_8017886C *pOut, Object_80039F5C *pOther);
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
int CarrierRunTryJuke(Object_80039F5C *, Object_80039F5C *, float, int, int, int);
int CarrierRunTrySpin(Object_80039F5C *, Object_80039F5C *, float, int, int, int);
static int _CarrierRun_iMoveSearchAngle = 0x38E38E;
static float _CarrierRun_fPitchRatingScale = 1.2f;
static float _CarrierRun_fPitchNearRange = 3.0f;
static float _CarrierRun_fPitchFarRange = 7.0f;
static unsigned char _CarrierRun_aucMoveOrder[3][7] = {
    {3, 4, 2, 0, 1, 6, 5}, {0, 1, 3, 4, 2, 6, 5}, {0, 1, 2, 3, 4, 6, 5}
};
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


extern "C" {
int GetOpenShouldRunOn(Object_80039F5C *p);
int GetOpenIsOpenToCarrier(Object_80039F5C *p, float a, float b);
int GetOpenFindOpenSpot(Point_8017886C *out, Object_80039F5C *p, float lower, float upper);
void GetOpenRunOn(Object_80039F5C *p);
void GetOpenGetRunOnPoint(Object_80039F5C *p, Point_8017886C *pOut);
int GetOpenEnter(Object_80039F5C *p);
int GetOpenUpdate(Object_80039F5C *p);
void GetOpenGetDepthRange(float *pA, float *pB);
int DirectedRunEnter(Object_80039F5C *p);
int DirectedRunUpdate(Object_80039F5C *p);
void PlayerCutStartAnim(Object_80039F5C *p);
Info_80089904 *PlayerCutFindAnimInfo(int a, int b);
void PlayerCutInitHeadings(Object_80039F5C *p);
void PlayerCutPostChainedCut(Object_80039F5C *p, int value);
void PlayerCutPostTurn(Object_80039F5C *p, int angle);
int PlayerCutEnter(Object_80039F5C *p);
int PlayerCutUpdate(Object_80039F5C *p);
int PlayerCutExit();
void PlayerCutMirrorMessage(unsigned char *p);
int PlayerCutGetTargetHeading(Object_80039F5C *p);
int PlayerCutGetStartHeading(Object_80039F5C *p);
int PlayerCutGetRunHeading(Object_80039F5C *p);
int PlayerCutGetMessageTurn(Message_800F01CC *pMessage);
void PlayerCutGetAnimOffset(int a, unsigned char b, int angle, Point_8017886C *pOut);
int PlayerCutGetAnimLength(unsigned char a);
int PlayerCutGetTimeLeft(Object_80039F5C *p);
int PlayerCutGetAnimTime(Object_80039F5C *p);
void PlayerCutGetEndPoint(Object_80039F5C *p, Point_8017886C *pOut);
float PlayerCutGetRunSpeed(Object_80039F5C *p, float value);
int CarrierRunHasDefenderAhead(Object_80039F5C *p);
void CarrierRunCountRetreat(Object_80039F5C *p, OptionRunControl_t *pControl);
void CarrierRunAddSideCosts(Object_80039F5C *p);
int CarrierRunCanUseSideline(Object_80039F5C *p);
void CarrierRunSteerToSideline(Object_80039F5C *p);
void CarrierRunPickHeading(Object_80039F5C *p, int mode);
void CarrierRunAvoidPlayer(Object_80039F5C *p, OptionRunControl_t *control, int *pMode, Entry_801230B8 *entry);
void CarrierRunKeepInBounds(Object_80039F5C *p, OptionRunControl_t *control, int);
int CarrierRunIsShielded(Object_80039F5C *p, Object_80039F5C *pOther);
int CarrierRunTryJuke(Object_80039F5C *p, Object_80039F5C *, float distance, int, int turn, int);
int CarrierRunTrySpinOffBlock(Object_80039F5C *p, Object_80039F5C *pOther);
int CarrierRunTrySpin(Object_80039F5C *p, Object_80039F5C *pOther, float distance, int angle, int turn, int);
int CarrierRunTryHurdle(Object_80039F5C *p, Object_80039F5C *pOther, float distance, int angle, int turn, int opposed);
int CarrierRunTryDive(Object_80039F5C *p, Object_80039F5C *pOther, float distance, int angle, int turn, int opposed);
int CarrierRunTryStiffArm(Object_80039F5C *p, Object_80039F5C *pOther, float distance, int angle, int turn, int opposed);
int CarrierRunTryNoMove(Object_80039F5C *p, Object_80039F5C *pOther, float distance, int angle, int turn, int opposed);
int CarrierRunTryPitch(Object_80039F5C *p, Object_80039F5C *pOther, float distance, int angle, int turn, int opposed);
int CarrierRunGetMoveRow(Object_80039F5C *p);
void CarrierRunTryMoves(Object_80039F5C *p, OptionRunControl_t *control, OptionRunMove_t *block);
void CarrierRunSetSpeed(Object_80039F5C *p, OptionRunControl_t *control, int mode);
int CarrierRunFindLeadBlocker(Object_80039F5C *p);
int CarrierRunCheckRunOut(Object_80039F5C *p, OptionRunControl_t *control);
int CarrierRunCheckBlocked(Object_80039F5C *p, OptionRunControl_t *pControl);
int CarrierRunEnter(Object_80039F5C *p);
int CarrierRunExit(Object_80039F5C *p);
int CarrierRunUpdate(Object_80039F5C *p);
int CarrierRunNotify(Object_80039F5C *p);
int CarrierRunInput(Object_80039F5C *p);
void CarrierRunResetControl(Object_80039F5C *p, OptionRunControl_t *pControl);
}

template <class T>
static inline T _CarrierRunMap(T value, T inLow, T inHigh, T outLow, T outHigh)
{
    return (value - inLow) * (outHigh - outLow) / (inHigh - inLow) + outLow;
}

template <class T>
static inline T _CarrierRunClamp(T value, T low, T high)
{
    return !(value < low) ? (value <= high ? value : high) : low;
}

typedef int (*CarrierRunMoveTest_t)(Object_80039F5C *, Object_80039F5C *, float, int, int, int);
extern const CarrierRunMoveTest_t _CarrierRun_apMoveTests[7];

#if defined(DECOMP_COMPARE)
extern "C" int CarrierRunHasDefenderAhead(Object_80039F5C *p)
{
    int result = fn_800ABDA4(p->mIdBytes[2]) == 0;
    unsigned char i;
    unsigned int count;

    if (fn_800A8740()) {
        result = 1;
    }
    count = fn_80178D18(fn_80178320());
    for (i = 0; i < count; i++) {
        if (PlyrGet(fn_80178320(), i)->mMotion.mPos.mY > p->mMotion.mPos.mY) {
            result = 1;
            break;
        }
    }
    return result;
}

extern "C" void CarrierRunCountRetreat(Object_80039F5C *p, OptionRunControl_t *pControl)
{
    Vector_80039F5C position = p->mMotion.mPos;
    Vector_80039F5C previous = p->mMotion.mUnknown12;

    fn_80178A2C();
    fn_80178A2C();
    fn_80177FE0();
    float y = position.mY;

    if (!(previous.mY <= y) && pControl->mUnknown50 <= 120) {
        pControl->mUnknown50++;
    } else {
        pControl->mUnknown50 = 0;
    }
}

extern "C" void CarrierRunAddSideCosts(Object_80039F5C *p)
{
    Object_800B26B0 *motion = &p->mMotion;
    float *values = ((OptionRunControl_t *)&p->mUnknown336)->mValues.mCost;

    if (fn_80177F70() == 0) {
        int team = fn_80178320();
        float distance;

        if (fn_801245DC(p, team, 0, fn_80178D18(fn_80178320()), 0x355555, &distance, 1)
            && !(distance >= 15.0f)) {
            if (fn_8011F32C()) {
                unsigned int count = fn_80178D18(fn_80178308());
                unsigned char i;
                signed char remaining = 6;

                for (i = 0; i < count; i++) {
                    if (!(fabsf(PlyrGet(fn_80178308(), i)->mMotion.mPos.mX) <= 6.0f)) {
                        remaining--;
                    }
                }
                if (remaining < 0) {
                    if (!(motion->mPos.mX <= 12.0f - fn_80178A08())) {
                        values[2] += 3.0f;
                        values[1] += 2.0f;
                    }
                } else if (!(motion->mPos.mX >= -4.0f)) {
                    values[2] += 3.0f;
                    values[3] += 2.0f;
                } else if (!(motion->mPos.mX <= 4.0f)) {
                    values[2] += 3.0f;
                    values[1] += 2.0f;
                }
            } else if (!(fabsf(p->mMotion.mPos.mX) <= 3.0f)) {
                if (!(p->mMotion.mPos.mX >= 0.0f)) {
                    values[2] += 3.0f;
                    values[3] += 2.0f;
                } else {
                    values[2] += 3.0f;
                    values[1] += 2.0f;
                }
            }
        }
    }
}

extern "C" int CarrierRunCanUseSideline(Object_80039F5C *p)
{
    int result = 1;

    if (fn_800A8444(p->mIdBytes[2])) {
        result = GameOptionsGet(14) == 1;
    }
    switch (fn_801486A0()) {
    case 0:
    case 2:
    case 3:
        result = 0;
        break;
    }
    return result;
}

extern "C" void CarrierRunSteerToSideline(Object_80039F5C *p)
{
    OptionRunControl_t *control = (OptionRunControl_t *)&p->mUnknown336;
    float distance = 0.0f;

    if (CarrierRunCanUseSideline(p) && (!fn_80178BA4(p->mIdBytes[2]) || GameOptionsGet(14) == 1)
        && PlayerMoveGetKind(p)) {
        Point_8017886C delta;
        int team = fn_80178320();
        Object_80039F5C *other = fn_801244F0(p, team, 0, fn_80178D18(fn_80178320()), &distance, 0);

        fn_80227690(&delta, &other->mMotion.mPos, &p->mMotion.mPos);
        int side = MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), 0) <= 0x3FFFFF;

        if (!(p->mMotion.mPos.mY <= fn_80178A2C() - 10.0f)) {
            if (!control->mUnknown56.mUnknown4) {
                if (side) {
                    control->mUnknown56.mUnknown5 = 0;
                } else {
                    control->mUnknown56.mUnknown5 = 1;
                }
                control->mUnknown56.mUnknown4 = 1;
            }
            if (!(p->mMotion.mPos.mX >= 4.0f - fn_80178A08())) {
                if (!control->mUnknown56.mUnknown5) {
                    control->mUnknown56.mUnknown5 = 1;
                }
            } else if (!(p->mMotion.mPos.mX <= fn_80178A08() - 4.0f)) {
                if (control->mUnknown56.mUnknown5 == 1) {
                    control->mUnknown56.mUnknown5 = 0;
                }
            }
            float near, far;

            if (CarrierRunHasDefenderAhead(p)) {
                near = 6.0f;
                far = 10.0f;
            } else {
                near = 3.0f;
                far = 8.0f;
            }
            int angle = control->mUnknown56.mUnknown5 ? 0 : 0x800000;
            int limit = _CarrierRunClamp(
                _CarrierRunMap((int)(fn_80178A2C() - p->mMotion.mPos.mY), 4, 10, 0, 0x400000), 0, 0x400000);
            int extra = (int)_CarrierRunMap(distance, near, far, 4194304.0f, 0.0f);

            extra = !(extra < 0) ? (extra <= 0x400000 - limit ? extra : 0x400000 - limit) : 0;

            control->mUnknown44 = angle <= 0x400000 ? angle + limit + extra : angle - limit - extra;
        }
    }
}

extern "C" void CarrierRunPickHeading(Object_80039F5C *p, int mode)
{
    OptionRunControl_t *control = (OptionRunControl_t *)&p->mUnknown336;
    Object_80039F5C *other = (Object_80039F5C *)mode;
    unsigned char index = control->mUnknown48;
    Object_800B26B0 *motion = &p->mMotion;
    int angle = control->mUnknown44;
    Directions_8012430C *values = &control->mValues;
    Point_8017886C ball;
    Point_8017886C point;
    int change = 0;

    ball = fn_80177FE0();
    point.mX = fn_8011F4D4();
    float offset = fabsf(motion->mPos.mX - point.mX);

    if (fn_8011F1A4() && fn_8011F1A4() && (unsigned int)fn_8011F4C8() > 3
        && !(motion->mPos.mY >= ball.mY - 1.0f)
        && !(fabsf(point.mX) <= fabsf(motion->mPos.mX)) && !(offset <= 3.0f)) {
        float distance = ball.mY - motion->mPos.mY;
        float projected = distance * (offset / fabsf(ball.mX - point.mX));

        point.mY = ball.mY - (projected <= distance ? projected : distance);
        fn_80227690(&point, &point, motion);
        angle = fn_801CFE40(point.mY, point.mX);
    } else {
        float threshold = fn_801783AC(0) ? -8.0f : 0.0f;

        if (!(values->mCost[index] < threshold)) {
            float right = values->mCost[(index + 1) & 7];
            float left = values->mCost[(index - 1) & 7];

            if (right == left) {
                float distance;
                int team = fn_80178320();
                Object_80039F5C *nearest = fn_801245DC(p, team, 0, fn_80178D18(fn_80178320()),
                                                     0x600000, &distance, 1);

                if (nearest && !(distance >= 4.0f)) {
                    fn_80227690(&point, &nearest->mMotion.mPos, motion);
                    if (((fn_801CFE40(point.mY, point.mX) - motion->mFacing) & 0xFFFFFF) > 0x800000) {
                        right -= 1.0f;
                    } else {
                        left -= 1.0f;
                    }
                }
            }
            float sine;

            if (!(right >= left)) {
                float degrees = right - values->mCost[index];

                degrees *= 5.0f;

                if (!(degrees >= 90.0f)) {
                    sine = fn_801CFB94((int)(degrees * 46603.37890625f)) * 0.5f;
                    change = (int)(sine * 2097152.0f);
                }
            } else if (!(left >= right)) {
                float degrees = left - values->mCost[index];

                degrees *= 5.0f;

                if (!(degrees >= 90.0f)) {
                    sine = fn_801CFB94((int)(degrees * 46603.37890625f)) * 0.5f;
                    change = (int)(sine * 2097152.0f);
                    change = -change;
                }
            }
        }
    }
    angle = (angle + change) & 0xFFFFFF;
    if (control->mUnknown44 != angle) {
        if (other) {
            fn_80227690(&point, &other->mMotion.mPos, &p->mMotion.mPos);
            int toward = fn_801CFE40(point.mY, point.mX);
            int candidate = MathAngleDiff(toward, angle);

            if (candidate > MathAngleDiff(toward, control->mUnknown44)) {
                control->mUnknown44 = angle;
            }
        } else {
            control->mUnknown44 = angle;
        }
        control->mUnknown48 = ((angle + 0x100000) >> 21) & 7;
    }
}

extern "C" void CarrierRunAvoidPlayer(Object_80039F5C *p, OptionRunControl_t *control, int *pMode, Entry_801230B8 *entry)
{
    Object_800B26B0 *motion = &p->mMotion;
    int secondAngle = 0;
    int firstAngle = 0;
    float limit;
    if (entry) {
        float value = entry->mUnknown20;
        if (value < 0.35f) {
            limit = 0.35f;
        } else {
            limit = value;
            if (!(limit <= 2.5f)) {
                limit = 2.5f;
            }
        }
    } else {
        limit = 2.5f;
    }
    float distance;
    Object_80039F5C *other = fn_80124C28(p, &distance, 0x355555, limit, 0.35f, control->mUnknown44);
    *pMode = (int)other;
    if (!other || distance >= limit) {
        return;
    }
    int blocked = 0;
    int linked = fn_8011E9B4(other);
    Vector_80039F5C point;
    Point_8017886C delta;
    int direction;
    if (linked) {
        Object_80039F5C *partner = fn_8009BCE8(&other->mUnknown1036);
        point.mX = (other->mMotion.mPos.mX + partner->mMotion.mPos.mX) * 0.5f;
        point.mY = (other->mMotion.mPos.mY + partner->mMotion.mPos.mY) * 0.5f;
        fn_80227690(&delta, &other->mMotion.mPos, motion);
        firstAngle = fn_801CFE40(delta.mY, delta.mX);
        fn_80227690(&delta, &partner->mMotion.mPos, motion);
        secondAngle = fn_801CFE40(delta.mY, delta.mX);
        int sector = (firstAngle - secondAngle) & 0xFFFFFF;
        if ((sector <= 0x7FFFFF && ((control->mUnknown44 - secondAngle) & 0xFFFFFF) <= 0x7FFFFF)
            || (sector > 0x800000 && ((control->mUnknown44 - secondAngle) & 0xFFFFFF) > 0x800000)) {
            if (MathAngleDiff(firstAngle - secondAngle, 0)
                > MathAngleDiff(control->mUnknown44 - secondAngle, 0)) {
                blocked = 1;
            }
        }
        fn_80227690(&delta, &point, motion);
        direction = fn_801CFE40(delta.mY, delta.mX);
        distance = fn_802270A4(&delta);
        if (!(fn_8022781C(&other->mMotion.mPos, motion) >= distance)) {
            distance = fn_8022781C(&other->mMotion.mPos, motion);
            direction = firstAngle;
        }
        if (!(fn_8022781C(&partner->mMotion.mPos, motion) >= distance)) {
            distance = fn_8022781C(&partner->mMotion.mPos, motion);
            direction = secondAngle;
        }
    } else {
        point = other->mMotion.mPos;
        point.mX += other->mMotion.mUnknown40 * 10.0f;
        point.mY += other->mMotion.mUnknown44 * 10.0f;
        fn_80227690(&delta, &point, motion);
        direction = fn_801CFE40(delta.mY, delta.mX);
        distance = fn_802270A4(&delta);
    }
    if (distance >= limit) {
        return;
    }
    float fraction = distance / limit;
    if (!(fraction <= 1.0f)) {
        fraction = 1.0f;
    }
    int angle;
    if (((direction - control->mUnknown44) & 0xFFFFFF) > 0x800000) {
        angle = (int)((1.0f - fraction) * 3495253.0f);
        if (linked && blocked) {
            if (((firstAngle - direction) & 0xFFFFFF) <= 0x7FFFFF) {
                angle += MathAngleDiff(firstAngle, control->mUnknown44);
            } else {
                angle += MathAngleDiff(secondAngle, control->mUnknown44);
            }
        }
    } else {
        angle = (int)(-((1.0f - fraction) * 3495253.0f));
        if (linked && blocked) {
            if (((firstAngle - direction) & 0xFFFFFF) > 0x800000) {
                angle -= MathAngleDiff(firstAngle, control->mUnknown44);
            } else {
                angle -= MathAngleDiff(secondAngle, control->mUnknown44);
            }
        }
    }
    angle = (control->mUnknown44 + angle) & 0xFFFFFF;
    int threshold = 0x3C71C7;
    if (((other->mId >> 8) & 0xFF) == p->mIdBytes[2]) {
        threshold = 0x18E38E;
    }
    if (MathAngleDiff(angle, 0xC00000) < threshold) {
        int difference = MathAngleDiff(direction, control->mUnknown44);
        if (difference <= 0x2E38E2) {
            angle = (int)((1.0f - fraction) * 3495253.0f);
            if (difference > angle) {
                angle = 0;
            } else {
                angle = MathAngleDiff(angle, difference);
            }
            if (((direction - control->mUnknown44) & 0xFFFFFF) <= 0x7FFFFF) {
                angle = -angle;
            }
            angle = (control->mUnknown44 + angle) & 0xFFFFFF;
        }
    }
    control->mUnknown44 = angle;
    angle = MathAngleDiff(motion->mUnknown32, direction);
    if (angle > 0x400000) {
        angle = 0x400000;
    }
    fn_801CFB18(angle);
    if (control->mUnknown40 < 0.72f
        || (MathAngleDiff(direction, motion->mFacing) <= 0xE38E2
            && ((other->mId >> 8) & 0xFF) == p->mIdBytes[2] && other->mId == p->mUnknown560.mUnknown44)) {
        control->mUnknown52 = 0;
    }
}

#endif

extern "C" void CarrierRunKeepInBounds(Object_80039F5C *p, OptionRunControl_t *control, int)
{
    Object_800B26B0 *motion = &p->mMotion;
    int angle = control->mUnknown44;
    if (fn_801486A0()) {
        if (MathAngleDiff(motion->mFacing, 0x400000) <= 0x3FFFFF) {
            if (!(motion->mPos.mX >= 3.0f - fn_80178A08())) {
                if (MathAngleDiff(motion->mFacing, 0x800000) <= 0x438E38) angle = 0x400000;
            } else if (!(motion->mPos.mX <= fn_80178A08() - 3.0f)) {
                if (MathAngleDiff(motion->mFacing, 0) <= 0x438E38) angle = 0x400000;
            }
        }
        goto finish;
    }
    if (!(motion->mPos.mY <= fn_80178A44() - 5.0f)) {
        if ((MathAngleDiff(motion->mFacing, 0) <= 0x3FFFFF
             && motion->mPos.mX < fn_80178A08() - 3.5f)
            || motion->mPos.mX < 3.5f - fn_80178A08()) angle = 0;
        else angle = 0x800000;
    } else if (!(motion->mPos.mY >= 5.0f - fn_80178A44())) {
        if ((MathAngleDiff(motion->mFacing, 0) <= 0x3FFFFF
             && motion->mPos.mX < fn_80178A08() - 3.5f)
            || !(motion->mPos.mX >= 3.5f - fn_80178A08())) angle = 0;
        else angle = 0x800000;
    }
    if (!(motion->mPos.mX <= fn_80178A08() - 3.5f)) {
        if ((MathAngleDiff(motion->mFacing, 0x400000) <= 0x3FFFFF
             && motion->mPos.mY < fn_80178A44() - 5.0f)
            || motion->mPos.mY < 5.0f - fn_80178A44()) angle = 0x400000;
        else angle = 0xC00000;
    } else if (!(motion->mPos.mX >= 3.5f - fn_80178A08())) {
        if ((MathAngleDiff(motion->mFacing, 0x400000) <= 0x3FFFFF
             && motion->mPos.mY < fn_80178A44() - 5.0f)
            || !(motion->mPos.mY >= 5.0f - fn_80178A44())) angle = 0x400000;
        else angle = 0xC00000;
    }
    if (!(motion->mPos.mY <= fn_80178A44() * 0.5f)) {
        if (!(motion->mPos.mX <= fn_80178A08() * 0.2f)) {
            Point_8017886C corner, delta;
            corner.mX = fn_80178A08() * 0.2f;
            corner.mY = fn_80178A44() * 0.5f;
            fn_80227690(&delta, motion, &corner);
            Point_8017886C direction;
            direction.mX = -fabsf(delta.mY);
            direction.mY = fabsf(delta.mX);
            int first = direction.Heading();
            int back = (first + 0x800000) & 0xFFFFFF;
            if (MathAngleDiff(motion->mFacing, 0x600000) <= 0x3FFFFF) {
                if (((first - motion->mFacing) & 0xFFFFFF) <= 0x7FFFFF) angle = first;
            } else if (((motion->mFacing - back) & 0xFFFFFF) <= 0x7FFFFF) angle = back;
        } else if (!(motion->mPos.mX >= -(fn_80178A08() * 0.2f))) {
            Point_8017886C corner, delta;
            corner.mX = -(fn_80178A08() * 0.2f);
            corner.mY = fn_80178A44() * 0.5f;
            fn_80227690(&delta, motion, &corner);
            Point_8017886C direction;
            direction.mX = fabsf(delta.mY);
            direction.mY = fabsf(delta.mX);
            int first = direction.Heading();
            int back = (first + 0x800000) & 0xFFFFFF;
            if (MathAngleDiff(motion->mFacing, 0x200000) <= 0x3FFFFF) {
                if (((motion->mFacing - first) & 0xFFFFFF) <= 0x7FFFFF) angle = first;
            } else if (((back - motion->mFacing) & 0xFFFFFF) <= 0x7FFFFF) angle = back;
        }
    } else if (!(motion->mPos.mY >= -(fn_80178A44() * 0.5f))) {
        if (!(motion->mPos.mX <= fn_80178A08() * 0.2f)) {
            Point_8017886C corner, delta;
            corner.mX = fn_80178A08() * 0.2f;
            corner.mY = -(fn_80178A44() * 0.5f);
            fn_80227690(&delta, motion, &corner);
            Point_8017886C direction;
            direction.mX = fabsf(delta.mY);
            direction.mY = fabsf(delta.mX);
            int first = direction.Heading();
            int back = (first + 0x800000) & 0xFFFFFF;
            if (MathAngleDiff(motion->mFacing, 0x200000) <= 0x3FFFFF) {
                if (((first - motion->mFacing) & 0xFFFFFF) <= 0x7FFFFF) angle = first;
            } else if (((motion->mFacing - back) & 0xFFFFFF) <= 0x7FFFFF) angle = back;
        } else if (!(motion->mPos.mX >= -(fn_80178A08() * 0.2f))) {
            Point_8017886C corner, delta;
            corner.mX = -(fn_80178A08() * 0.2f);
            corner.mY = -(fn_80178A44() * 0.5f);
            fn_80227690(&delta, motion, &corner);
            Point_8017886C direction;
            direction.mX = -fabsf(delta.mY);
            direction.mY = fabsf(delta.mX);
            int first = direction.Heading();
            int back = (first + 0x800000) & 0xFFFFFF;
            if (MathAngleDiff(motion->mFacing, 0x600000) <= 0x3FFFFF) {
                if (((motion->mFacing - first) & 0xFFFFFF) <= 0x7FFFFF) angle = first;
            } else if (((back - motion->mFacing) & 0xFFFFFF) <= 0x7FFFFF) angle = back;
        }
    }
    if (!(motion->mPos.mY <= fn_80178A44() - 5.0f)) {
        if (!(motion->mPos.mY <= fn_80178A44() - 2.5f)) {
            angle = MathAngleDiff(motion->mFacing, 0) <= 0x3FFFFF ? 0xF77778 : 0x888889;
        }
    } else if (!(motion->mPos.mY >= 5.0f - fn_80178A44())) {
        if (!(motion->mPos.mY >= 2.5f - fn_80178A44())) {
            angle = MathAngleDiff(motion->mFacing, 0) <= 0x3FFFFF ? 0x88888 : 0x777777;
        }
    }
    if (!(motion->mPos.mX <= fn_80178A08() - 3.5f)) {
        if (!(motion->mPos.mX <= fn_80178A08() - 2.5f)) {
            angle = MathAngleDiff(motion->mFacing, 0x400000) <= 0x3FFFFF ? 0x488888 : 0xB77778;
        }
    } else if (!(motion->mPos.mX >= 3.5f - fn_80178A08())) {
        if (!(motion->mPos.mX >= 2.5f - fn_80178A08())) {
            angle = MathAngleDiff(motion->mFacing, 0x400000) <= 0x3FFFFF ? 0x377777 : 0xC88889;
        }
    }
finish:
    angle &= 0xFFFFFF;
    control->mUnknown44 = angle;
    control->mUnknown48 = ((angle + 0x100000) >> 21) & 7;
}

extern "C" int CarrierRunIsShielded(Object_80039F5C *p, Object_80039F5C *pOther)
{
    OptionRunControl_t *state = (OptionRunControl_t *)&p->mUnknown336;
    int result = 0;

    if (fn_8011E9B4(pOther)) {
        result = 1;
    } else {
        Object_80039F5C *pRef = fn_8009BCE8(&pOther->mUnknown1036);

        if (pRef) {
            Point_8017886C delta;

            fn_80227690(&delta, &pRef->mMotion.mPos, &p->mMotion.mPos);
            if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), state->mUnknown44) <= 0x355554
                && MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing) <= 0x355554) {
                float distance = fn_8022710C(&delta);

                if (distance < fn_80227890(&p->mMotion.mPos, &pOther->mMotion.mPos)) {
                    result = 1;
                }
            }
        }
    }
    return result;
}

extern "C" int CarrierRunTryJuke(Object_80039F5C *p, Object_80039F5C *, float distance, int, int turn, int)
{
    Object_800B26B0 *motion = &p->mMotion;
    int kind = 1;
    int side = 0;
    if ((float)p->mRatings[0] < 165.75f || distance > 10.0f || turn > 0x271C70) {
        return 0;
    }
    int facingDifference = MathAngleDiff(motion->mFacing, 0x400000);
    if (facingDifference > 0x31C71B) {
        return 0;
    }
    int chance = (unsigned char)(((p->mRatings[0] >> 2) + (p->mRatings[0] >> 3)) >> 1);
    float scale = (float)facingDifference / (float)0x31C71C;
    float reduction = scale * 0.8f;

    chance = (unsigned char)(int)((float)chance - reduction * (float)chance);
    Object_80039F5C *pOther = fn_80124CE4(p, p->mIdBytes[2] ^ 1, &distance, 0x271C71, 10.0f, motion->mFacing, 1.0f);
    if (pOther && p->mIdBytes[2] != pOther->mIdBytes[2] && !fn_8011E9B4(pOther)) {
        Point_8017886C delta;
        fn_80227690(&delta, &pOther->mMotion.mPos, motion);
        int threshold = 0xAAAAA;
        int angle = delta.Heading();
        turn = MathAngleDiff(angle, motion->mFacing);
        int right = 0;
        if (((p->mMotion.mFacing - angle) & 0xFFFFFF) > 0x800000) {
            right = 1;
        }
        int difference = MathAngleDiff(p->mMotion.mFacing, pOther->mMotion.mFacing);
        angle = (angle + 0x800000) & 0xFFFFFF;
        int otherDifference = MathAngleDiff(pOther->mMotion.mFacing, angle);
        int ownDifference = MathAngleDiff(angle, p->mMotion.mFacing);
        if (difference + otherDifference > ownDifference) {
            chance = 0;
        } else {
            threshold = (int)((float)otherDifference / (float)ownDifference * 2330169.0f + (float)threshold);
            if (turn < threshold) {
                side = right ? 2 : 1;
            } else {
                side = right ? 1 : 2;
            }
        }
        kind = 4;
        if (!(distance <= 8.5f)) {
            kind = 3;
        }
    } else if (MathAngleDiff(turn, 0x400000) <= 0x138E37) {
        kind = 4;
    } else {
        chance = 0;
    }
    if (chance && fn_802372EC(0, 100) < chance) {
        if (!(fn_80178A68(&p->mMotion.mPos) >= 5.0f)) {
            if (fn_800F22D8(p, kind, side, 4)) {
                return 1;
            }
        } else if (fn_800F22D8(p, kind, side, fn_800F2828(p, pOther))) {
            return 1;
        }
    }
    return 0;
}

extern "C" int CarrierRunTrySpinOffBlock(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Object_800B26B0 *pMotion = &p->mMotion;

    if (fn_8011E9B4(pOther) && fn_802372EC(0, 100) < (unsigned int)(p->mRatings[0] >> 3 & 0x7FFFFFFF)) {
        Point_8017886C delta;
        int direction;

        fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
        direction = fn_801CFE40(delta.mY, delta.mX);
        if (MathAngleDiff(pMotion->mFacing, direction) <= 0x11C71B) {
            int side = 1;

            if ((direction - pMotion->mFacing & 0xFFFFFF) <= 0x7FFFFF) {
                side = 2;
            }
            if (fn_80110824(p, 2, side, 0)) {
                return 1;
            }
        }
    }
    return 0;
}

extern "C" int CarrierRunTrySpin(Object_80039F5C *p, Object_80039F5C *pOther, float distance, int angle, int turn, int)
{
    Object_800B26B0 *motion = &p->mMotion;
    short *pRatings = p->mRatings;
    int kind = 1;
    int side = 0;

    if ((float)pRatings[0] < 165.75f || p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
        return 0;
    }
    if (p->mIdBytes[2] != pOther->mIdBytes[2] && !(pOther->mFlags & 0x800)
        && (MathAngleDiff(pOther->mMotion.mUnknown32, 0) <= 0x31C71B
            || MathAngleDiff(pOther->mMotion.mUnknown32, 0x800000) <= 0x31C71B)
        && !CarrierRunIsShielded(p, pOther) && fn_80124714(p, pOther, 0) == 1) {
        int threshold = 0x438E39;
        int difference = MathAngleDiff((angle + 0x800000) & 0xFFFFFF, pOther->mMotion.mFacing);
        if (difference > 0x200000) {
            difference = 0x200000;
        }
        if (MathAngleDiff(pOther->mMotion.mFacing, p->mMotion.mFacing) > 0x555555) {
            threshold = 0x21C71C;
        } else {
            int offset = difference - 0x200000;

            threshold = (offset + threshold) & 0xFFFFFF;
            int limit;
            if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x400000) {
                limit = MathAngleDiff(p->mMotion.mFacing, 0x400000);
            } else {
                limit = 0x400000;
            }
            float scale = (float)(0x400000 - limit) / (float)0x400000;
            float reduction = scale * 0.5f;

            threshold = (threshold - (int)(reduction * (float)threshold)) & 0xFFFFFF;
            threshold = threshold > 0x11C71B ? (threshold <= 0x438E39 ? threshold : 0x438E39) : 0x11C71C;
        }
        if (!(distance > 6.0f) && turn < threshold) {
            if (MathAngleDiff(motion->mFacing, 0x400000) > 0xE38E3) {
                kind = 2;
                side = 1;
                if (((motion->mFacing - 0x400000) & 0xFFFFFF) <= 0x7FFFFF) {
                    side = 2;
                }
            } else if (turn <= 0x11C71B) {
                kind = 2;
                side = 2;
                if (((angle - motion->mFacing) & 0xFFFFFF) > 0x800000) {
                    side = 1;
                }
            }
            if (kind != 1 && fn_802372EC(0, 100) < ((unsigned int)(pRatings[0] >> 3) & 0x7FFFFFFF)
                && fn_80110824(p, kind, side, fn_80110EB0(p, pOther))) {
                return 1;
            }
        }
    }
    if (p->mUnknown560.mFlags.mBytes[0]) {
        Object_80039F5C *pRef = fn_8009BCE8(&p->mUnknown560.mUnknown44);
        if (pRef && CarrierRunTrySpinOffBlock(p, pRef)) {
            return 1;
        }
        pRef = fn_8009BCE8(&p->mUnknown560.mUnknown40);
        if (pRef && CarrierRunTrySpinOffBlock(p, pRef)) {
            return 1;
        }
    }
    return 0;
}

extern "C" int CarrierRunTryHurdle(Object_80039F5C *p, Object_80039F5C *pOther, float distance, int, int turn, int)
{
    if (!(fn_80178A68(&p->mMotion.mPos) >= 4.0f)) {
        if (!(distance > 5.0f) && turn <= 0x3FFFFF
            && MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x38E38D
            && CarrierMoveStart(p, 4)) {
            return 1;
        }
    } else if (!(distance > 2.5f) && turn <= 0x11C71B && (pOther->mFlags & 0x800)
               && CarrierMoveStart(p, CarrierMovePickKind(p, pOther))) {
        return 1;
    }
    return 0;
}

extern "C" int CarrierRunTryDive(Object_80039F5C *p, Object_80039F5C *pOther, float distance, int, int turn, int)
{
    Object_800B26B0 *motion = &p->mMotion;
    short *pRatings = p->mRatings;

    if (motion->mUnknown44 <= 0.0f) {
        return 0;
    }
    unsigned int chance = (unsigned int)(((pRatings[0] >> 3) * 2) + (pRatings[2] >> 4)) >> 1;

    if (!(distance > 4.0f) && turn <= 0x2AAAA9
        && !fn_8011E9B4(pOther) && p->mIdBytes[2] != pOther->mIdBytes[2]) {
        float remaining = fn_80178A2C() - motion->mPos.mY;
        float limit = 4.2f;

        limit = fn_801CFB18(p->mMotion.mFacing) * limit;

        if (!(remaining <= 0.0f) && !(remaining >= limit)) {
            if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0xAAAA9
                && !(fn_80178A08() - fabsf(p->mMotion.mPos.mX) >= 4.0f)) {
                chance = chance * 3 >> 1;
            }
            if (fn_802372EC(0, 100) < chance && fn_800E815C(p, 2, fn_800E885C(p))) {
                StyleTrackerOnStyleFirstDown();
                return 1;
            }
        }
    }
    return 0;
}

extern "C" int CarrierRunTryStiffArm(Object_80039F5C *p, Object_80039F5C *pOther, float distance, int angle, int, int)
{
    Object_800B26B0 *motion = &p->mMotion;
    short *pRatings = p->mRatings;

    if (!(pOther->mFlags & 0x800) && !fn_8011E9B4(pOther) && !(distance > 4.5f)
        && p->mIdBytes[2] != pOther->mIdBytes[2]) {
        int delta = (angle - motion->mFacing) & 0xFFFFFF;
        int side;
        int toward;

        if (delta > 0x800000) {
            toward = 0xC00000;
            side = 1;
        } else {
            toward = 0x400000;
            side = 2;
        }
        if (MathAngleDiff(delta, toward) <= 0x3FFFFF
            && MathAngleDiff(pOther->mMotion.mUnknown32, angle) > 0x4E38E3) {
            int chance = (unsigned int)(((pRatings[2] >> 3) * 2) + (pRatings[2] >> 4)) >> 1;
            int facing = MathAngleDiff(motion->mFacing, 0x400000);

            if (facing > 0x31C71B) {
                if (facing <= 0x400000) {
                    float scaled = chance;

                    chance = (int)(scaled - scaled * ((facing - 0x31C71C) / (float)(0x400000 - 0x31C71C)));
                } else {
                    chance = 0;
                }
            }
            if (fn_802372EC(0, 100) < (unsigned int)chance && fn_80111090(p, side)) {
                return 1;
            }
        }
    }
    return 0;
}

extern "C" int CarrierRunTryNoMove(Object_80039F5C *, Object_80039F5C *, float, int, int, int)
{
    return 0;
}

extern "C" int CarrierRunTryPitch(Object_80039F5C *p, Object_80039F5C *, float, int, int, int)
{
    Point_8017886C ball;
    Point_8017886C aim;
    int result = 0;

    ball = fn_80177FE0();
    Object_80039F5C *other = fn_80105384(p, 1, &aim);
    int valid = OptionRunCanPitchTo(p, &aim, other);

    if (other) {
        int open = valid && fn_801066D0(p, other, 9);

        if (open && !(p->mMotion.mPos.mY <= ball.mY)) {
            if (!(other->mRatings[4] <= p->mRatings[4] * _CarrierRun_fPitchRatingScale)) {
                float target = fn_8012506C(other, 6);
                float own = fn_8012506C(p, 6);

                if (!(own <= target) && !(own <= _CarrierRun_fPitchFarRange) && !(target >= _CarrierRun_fPitchFarRange)) {
                    result = 1;
                }
            } else {
                if (!(fn_8012506C(p, 6) >= _CarrierRun_fPitchNearRange)
                    && !(fn_8012506C(other, 6) >= _CarrierRun_fPitchNearRange)) {
                    result = 1;
                }
            }
        }
    }
    if (fn_800ABDA4(fn_80178308()) == 0) {
        int count = fn_8011F59C(0);

        if (count + fn_8011F59C(1) > 0) result = 0;
    } else if (fn_800ABDA4(fn_80178308()) == 1) {
        int count = fn_8011F59C(0);

        if (count + fn_8011F59C(1) > 1) result = 0;
    }
    if (result && fn_80105E90(p, other, 11)) {
        result = fn_801064A4(p, fn_801067D8(p));
    }
    return result;
}

extern "C" int CarrierRunGetMoveRow(Object_80039F5C *p)
{
    unsigned int value = p->mUnknown2914;

    if (value == 1 || value == 2) {
        return 1;
    }
    switch (value) {
    case 3:
    case 16:
    case 17:
    case 18:
    case 21:
    case 22:
        return 2;
    case 0:
    case 13:
    case 14:
    case 15:
    case 25:
        return 1;
    }
    return 0;
}

extern "C" void CarrierRunTryMoves(Object_80039F5C *p, OptionRunControl_t *control, OptionRunMove_t *block)
{
    if (fn_801787A0()) return;
    Object_800B26B0 *motion = &p->mMotion;

    block->mUnknown0 = (signed char)(((unsigned char *)&block->mUnknown0)[1] - 1);
    if (block->mUnknown0 > 0) return;
    block->mUnknown0 = (signed char)(16 - (p->mRatings[2] + p->mRatings[0]) / 32);
    block->mUnknown0 = fn_800ACC80(p, block->mUnknown0);
    block->mUnknown0 = fn_8009AD30(p, block->mUnknown0);
    if (control) control->mUnknown51[0] = 7;
    float distance;
    int team = fn_80178320();
    Object_80039F5C *other = fn_801245DC(p, team, 0, fn_80178D18(fn_80178320()), _CarrierRun_iMoveSearchAngle, &distance, 0);

    if (!other) {
        team = fn_80178308();
        other = fn_801245DC(p, team, 0, fn_80178D18(fn_80178308()), _CarrierRun_iMoveSearchAngle, &distance, 0);
    }
    if (other && !(distance > 10.0f)) {
        Point_8017886C delta;

        fn_80227690(&delta, &other->mMotion.mPos, motion);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        int turn = MathAngleDiff(angle, motion->mFacing);
        int opposed = MathAngleDiff((angle + 0x800000) & 0xFFFFFF, other->mMotion.mFacing) <= 0x1FFFFF;
        unsigned char *order = _CarrierRun_aucMoveOrder[CarrierRunGetMoveRow(p)];
        unsigned char i;

        for (i = 0; i <= 6; i++) {
            if (_CarrierRun_apMoveTests[order[i]](p, other, distance, angle, turn, opposed)) {
                if (control) control->mUnknown51[0] = order[i];
                return;
            }
        }
    }
    int mode = fn_801486A0();

    if (mode == 0 || mode == 2 || mode == 3 || mode == 1) return;
    Vector_80039F5C position;

    position.mX = motion->mPos.mX;
    position.mY = motion->mPos.mY;
    position.mZ = motion->mPos.mZ;

    if (fn_801784C4()) {
        position.mX = -position.mX;
        position.mY = -position.mY;
    }
    float nearest;
    BigObj_t *found = BigObjFindNearestOfType(&position, 7, &nearest);

    nearest = fn_800AD168(p->mIdBytes[2], nearest);
    if (found && !(nearest >= 3.0f)) {
        if (!(fn_80237260(0) >= 0.5f)) {
            fn_800F22D8(p, 4, 1, 4);
        } else {
            CarrierMoveStart(p, 4);
        }
    }
}

extern "C" void CarrierRunSetSpeed(Object_80039F5C *p, OptionRunControl_t *control, int mode)
{
    float distance = 0.0f;
    Object_80039F5C *other = (Object_80039F5C *)control->mUnknown0;

    if (other && mode == 0) {
        control->mUnknown52 = 0;
        if (!(fabsf(other->mMotion.mPos.mX) - 0.5f >= fabsf(p->mMotion.mPos.mX))
            && !(other->mMotion.mUnknown28 >= p->mMotion.mUnknown28)) {
            control->mUnknown40 = other->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
            control->mUnknown40 = control->mUnknown40 >= 0.75f ? control->mUnknown40 : 0.75f;
        }
    } else if (control->mUnknown52 == 1) {
        int turn = MathAngleDiff(control->mUnknown44, p->mMotion.mFacing);

        if (turn > 0x177777) {
            if (turn > 0x355555
                || fn_801245DC(p, p->mIdBytes[2], 0, fn_80178D18(p->mIdBytes[2]), turn, &distance, 0)
                || fn_801245DC(p, p->mIdBytes[2] ^ 1, 0, fn_80178D18(p->mIdBytes[2] ^ 1), turn, &distance, 0)) {
                control->mUnknown52 = 0;
                if (!(distance >= 3.0f)) {
                    control->mUnknown40 = fn_801CFB94(turn / 2) * 0.72f;
                    control->mUnknown40 = control->mUnknown40 >= 0.5f ? control->mUnknown40 : 0.5f;
                }
            }
        }
    }
}

extern "C" int CarrierRunFindLeadBlocker(Object_80039F5C *p)
{
    int enabled = 0;

    if (!fn_80177C38()) {
        if (!(fn_80177FE0().mY - p->mMotion.mPos.mY <= 4.0f)) {
            if (!(fabsf(fn_80177FE0().mX - p->mMotion.mPos.mX) >= 8.0f)) {
                if (fn_8011F1A4()) {
                    enabled = (unsigned int)fn_8011F4C8() > 3;
                }
            }
        }
    }
    if (enabled) {
        unsigned char team = p->mIdBytes[2];
        unsigned int count = fn_80178D18(team);
        unsigned short i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *other = PlyrGet(team, i);

            if ((unsigned int)(other->mUnknown1032 - 1) <= 1 || other->mQueue[0].mId == 47) {
                if (!(fn_80177FE0().mY - other->mMotion.mPos.mY <= 2.25f)
                    && !(other->mMotion.mPos.mY - p->mMotion.mPos.mY <= 1.0f)
                    && MathAngleDiff(other->mMotion.mFacing, p->mMotion.mFacing) <= 0x2AAAA9) {
                    return (int)other;
                }
            }
        }
    }
    return 0;
}

extern "C" int CarrierRunCheckRunOut(Object_80039F5C *p, OptionRunControl_t *control)
{
    int result = 0;

    if (p && control && control->mUnknown56.mUnknown2) {
        if (!control->mUnknown54 && BallStateGetPrev(BallGetCurrent(), 0) == 4) {
            control->mUnknown54 = BallGetStateFrames(BallGetCurrent());
        }
        unsigned char previous = control->mUnknown54;

        if (BallStateGet(BallGetCurrent(), 0) == 1
            && (fabsf(p->mMotion.mPos.mX) > fn_80178A08() - 1.5f
                || !(p->mMotion.mPos.mY <= fn_80178A44() - 1.5f))) {
            int facing = p->mMotion.mFacing;
            int signedAngle = facing > 0x800000 ? facing - 0x1000000 : facing;

            if (((unsigned int)(signedAngle + 0x1FFFFF) <= 0x3FFFFE && p->mMotion.mPos.mX > 0.0f)
                || ((unsigned int)(facing - 0x600001) <= 0x3FFFFE && p->mMotion.mPos.mX < 0.0f)
                || ((unsigned int)(facing - 0x200001) <= 0x3FFFFE
                    && !(p->mMotion.mPos.mY <= fn_80178A44() - 1.5f))) {
                if ((unsigned int)BallGetStateFrames(BallGetCurrent()) < (unsigned int)(previous + 25)
                    || control->mUnknown56.mUnknown3) {
                    result = 1;
                    control->mUnknown55++;
                }
                if (result && control->mUnknown55 > 20) {
                    result = 0;
                }
                if (result) {
                    control->mUnknown56.mUnknown3 = 1;
                    p->mUnknown512.mUnknown15 = 26;
                } else {
                    control->mUnknown56.mUnknown3 = 0;
                }
            }
        }
    }
    return result;
}

extern "C" int CarrierRunCheckBlocked(Object_80039F5C *p, OptionRunControl_t *pControl)
{
    int result = 0;

    if (p && pControl && BallGetCurrentHolder() == p) {
        float distance;
        Object_80039F5C *pOther = fn_80124CE4(p, p->mIdBytes[2], &distance, 0x200000,
                                           1.5f, p->mMotion.mFacing, 1.0f);

        if (pOther && fn_8011E9B4(pOther)
            && MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x200000) {
            result = p->mMotion.mUnknown28 <= gPlyrMoveFwdSpeed * 0.4f;
        }
        if (result) {
            p->mUnknown512.mUnknown15 = 27;
        }
    }
    return result;
}

extern "C" int CarrierRunEnter(Object_80039F5C *p)
{
    OptionRunControl_t *pControl = (OptionRunControl_t *)&p->mUnknown336;

    CarrierRunResetControl(p, pControl);
    ReplayEventAddPlayer(p);
    if (fn_800AD9B4() == 3) {
        pControl->mUnknown0 = CarrierRunFindLeadBlocker(p);
        if (BallGetCurrentHolder() == p) {
            if (PassIconsAreShown()) {
                CamGameSetModeAll(1);
            }
            PassIconsHide();
            PassIconsClearReplayFlag();
        }
        return 0;
    }
    return 1;
}

extern "C" int CarrierRunExit(Object_80039F5C *p)
{
    fn_800A3B58(p, 2, 0);
    return 1;
}

extern "C" int CarrierRunUpdate(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    OptionRunControl_t *pControl = (OptionRunControl_t *)&p->mUnknown336;
    Plan_80121264 plan;
    Message_800F01CC message;
    int mode = 0;

    fn_800B8344(p);
    if (p == BallGetCurrentHolder()) {
        CarrierRunCountRetreat(p, pControl);
        StyleTrackerUpdateRun(0, 0, 0);
        fn_800A3B58(p, 2, 0);
    } else {
        fn_801C1F94(&message, 0, 4);
        if (fn_801486A0() == 0) {
            message.mId = 57;
            message.mUnknown1[0] = BallGetCurrentIndex();
        } else {
            message.mId = 33;
        }
        fn_800F053C(0, p->mpState, &message, p);
        return 0;
    }
    if (fn_8010A2DC(p, 0, -1)) {
        p->mUnknown512.mUnknown15 = pControl->mUnknown52;
        return 0;
    }
    if (!(p->mFlags & 0x4000)) {
        if (--pControl->mUnknown49 <= 0) {
            Directions_8012430C *pValues = &pControl->mValues;
            Entry_801230B8 *pEntry;

            pControl->mUnknown49 = (255 - ((p->mRatings[0] >> 1) + (p->mRatings[2] >> 1))) >> 4;
            pControl->mUnknown40 = 1.0f;
            pControl->mUnknown52 = 1;
            fn_8012430C(pValues, 1, p);
            CarrierRunAddSideCosts(p);
            pControl->mUnknown48 = fn_801243E0(pValues, pMotion->mFacing);
            pControl->mUnknown44 = pControl->mUnknown48 << 21;
            CarrierRunPickHeading(p, mode);
            fn_8012311C(p, &plan, pControl->mUnknown44);
            pEntry = fn_80123174(&plan);
            if (pEntry) {
                int angle = pEntry->mUnknown16;

                pControl->mUnknown44 = angle;
                pControl->mUnknown48 = ((angle + 0x100000) >> 21) & 7;
            }
            CarrierRunAvoidPlayer(p, pControl, &mode, pEntry);
            CarrierRunKeepInBounds(p, pControl, mode);
            CarrierRunSteerToSideline(p);
            pControl->mUnknown0 = CarrierRunFindLeadBlocker(p);
            CarrierRunSetSpeed(p, pControl, mode);
            if (pControl->mUnknown56.mUnknown6) {
                PlayerMoveTryStartRun(p);
            }
        }
        PlayerMoveUpdateRun(p);
        PlayerMoveGetRunMode(p, &pControl->mUnknown52);
        p->mUnknown512.mUnknown15 = pControl->mUnknown52;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pControl->mUnknown44;
        p->mUnknown512.mUnknown4 = pControl->mUnknown44;
        p->mUnknown512.mUnknown0 = pControl->mUnknown40;
        if (p->mFlags & 0x400000) {
            p->mUnknown512.mUnknown14 = 10;
            p->mUnknown512.mUnknown8 = pMotion->mFacing;
            p->mUnknown512.mUnknown4 = pMotion->mFacing;
            p->mUnknown512.mUnknown0 = 0.5f;
        }
        CarrierRunTryMoves(p, pControl, &pControl->mUnknown56);
    } else {
        if (PlayerMoveTryStartRun(p)) {
            PlayerMoveUpdateRun(p);
            PlayerMoveGetRunMode(p, &pControl->mUnknown52);
            p->mUnknown512.mUnknown15 = pControl->mUnknown52;
        }
        if (p->mFlags & 0x400000) {
            p->mUnknown512.mUnknown14 = 10;
            p->mUnknown512.mUnknown8 = pMotion->mFacing;
            p->mUnknown512.mUnknown4 = pMotion->mFacing;
            p->mUnknown512.mUnknown0 = 0.5f;
        }
    }
    if (p->mpState->mId == 1) {
        CarrierRunCheckBlocked(p, pControl);
        CarrierRunCheckRunOut(p, pControl);
        fn_8011168C(p);
    }
    return 0;
}

extern "C" int CarrierRunNotify(Object_80039F5C *p)
{
    OptionRunControl_t *pControl = (OptionRunControl_t *)&p->mUnknown336;

    pControl->mUnknown44 = 0x400000;
    pControl->mUnknown52 = 0;
    pControl->mUnknown49 = 0;
    pControl->mUnknown56.mUnknown0 = (signed char)(16 - (p->mRatings[2] + p->mRatings[0]) / 32);
    pControl->mUnknown56.mUnknown0 = fn_800ACC80(p, pControl->mUnknown56.mUnknown0);
    pControl->mUnknown56.mUnknown0 = fn_8009AD30(p, pControl->mUnknown56.mUnknown0);
    return 0;
}

extern "C" int CarrierRunInput(Object_80039F5C *p)
{
    return fn_800B76E8(p);
}

extern "C" void CarrierRunResetControl(Object_80039F5C *p, OptionRunControl_t *pControl)
{
    pControl->mUnknown36 = fn_80177FE0().mY;
    pControl->mUnknown44 = 0;
    pControl->mUnknown49 = 0;
    pControl->mUnknown56.mUnknown0 = (signed char)(16 - (p->mRatings[2] + p->mRatings[0]) / 32);
    pControl->mUnknown56.mUnknown0 = fn_800ACC80(p, pControl->mUnknown56.mUnknown0);
    pControl->mUnknown56.mUnknown0 = fn_8009AD30(p, pControl->mUnknown56.mUnknown0);
    pControl->mUnknown52 = 1;
    pControl->mUnknown40 = 1.0f;
    pControl->mUnknown0 = 0;
    pControl->mUnknown56.mUnknown4 = 0;
    pControl->mUnknown56.mUnknown5 = 0;
    if (fn_801486A0() == 0) {
        if (!(p->mFlags & 0x400)) {
            unsigned char roll = fn_802372EC(0, 100);

            if ((fn_800ABDA4(1) == 0 && roll > 80) || (fn_800ABDA4(1) == 1 && roll > 40)
                || (fn_800ABDA4(1) == 2 && roll != 0)) {
                pControl->mUnknown56.mUnknown6 = 1;
            } else {
                pControl->mUnknown56.mUnknown6 = 0;
            }
        } else {
            pControl->mUnknown56.mUnknown6 = 1;
        }
    } else {
        pControl->mUnknown56.mUnknown6 = 1;
    }
    if (fn_800AD9B4() == 3) {
        pControl->mUnknown0 = CarrierRunFindLeadBlocker(p);
    }
    pControl->mUnknown56.mUnknown2 = 0;
}

const CarrierRunMoveTest_t _CarrierRun_apMoveTests[7] = {
    CarrierRunTryJuke, CarrierRunTrySpin, CarrierRunTryHurdle, CarrierRunTryDive,
    CarrierRunTryStiffArm, CarrierRunTryNoMove, CarrierRunTryPitch
};
