/* Player state 1: the ball carrier runs with the ball. For a computer-controlled carrier it
   steers around defenders and the field edges, sets his speed and sprint, and picks evasive
   moves (jukes, spins and the like) from a table of move tests. */

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
typedef int (*Action_8012F5A0)(Object_80039F5C *, Object_80039F5C *, int, int, int, float);
extern const Action_8012F5A0 actions_8012F5A0[7];
#endif

extern "C" int fn_8012CE60(Object_80039F5C *p)
{
    int result = fn_800ABDA4(p->mIdBytes[2]) == 0;
    unsigned char i;
    unsigned int count;

    if (fn_800A8740()) {
        result = 1;
    }
    count = fn_80178D18(fn_80178320());
    for (i = 0; i < count; i++) {
        if (fn_80039F5C(fn_80178320(), i)->mMotion.mPos.mY > p->mMotion.mPos.mY) {
            result = 1;
            break;
        }
    }
    return result;
}

#ifdef DECOMP_COMPARE
extern "C" void fn_8012CEF4(Object_80039F5C *p, OptionRunControl_t *pControl)
{
    Vector_80039F5C position = p->mMotion.mPos;
    Vector_80039F5C previous = p->mMotion.mUnknown12;

    fn_80178A2C();
    fn_80178A2C();
    fn_80177FE0();
    if (!(previous.mY <= position.mY) && pControl->mUnknown50 <= 120) {
        pControl->mUnknown50++;
    } else {
        pControl->mUnknown50 = 0;
    }
}
#endif

#ifdef DECOMP_COMPARE
extern "C" void fn_8012CFA0(Object_80039F5C *p)
{
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
                    if (!(fabsf(fn_80039F5C(fn_80178308(), i)->mMotion.mPos.mX) <= 6.0f)) {
                        remaining--;
                    }
                }
                if (remaining < 0) {
                    if (!(p->mMotion.mPos.mX <= 12.0f - fn_80178A08())) {
                        values[2] += 3.0f;
                        values[1] += 2.0f;
                    }
                } else if (!(p->mMotion.mPos.mX >= -4.0f)) {
                    values[2] += 3.0f;
                    values[3] += 2.0f;
                } else if (!(p->mMotion.mPos.mX <= 4.0f)) {
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
#endif

extern "C" int fn_8012D1E4(Object_80039F5C *p)
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

#ifdef DECOMP_COMPARE
extern "C" void fn_8012D258(Object_80039F5C *p)
{
    OptionRunControl_t *control = (OptionRunControl_t *)&p->mUnknown336;
    float distance = 0.0f;

    if (fn_8012D1E4(p) && (!fn_80178BA4(p->mIdBytes[2]) || GameOptionsGet(14) == 1)
        && PlayerMoveGetKind(p)) {
        Point_8017886C delta;
        int team = fn_80178320();
        Object_80039F5C *other = fn_801244F0(p, team, 0, fn_80178D18(fn_80178320()), &distance, 0);

        fn_80227690(&delta, &other->mMotion.mPos, &p->mMotion.mPos);
        int side = MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), 0) <= 0x3FFFFF;

        if (!(p->mMotion.mPos.mY <= fn_80178A2C() - 10.0f)) {
            if (!control->mUnknown56.mUnknown4) {
                control->mUnknown56.mUnknown5 = !side;
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

            if (fn_8012CE60(p)) {
                near = 6.0f;
                far = 10.0f;
            } else {
                near = 3.0f;
                far = 8.0f;
            }
            int angle = control->mUnknown56.mUnknown5 ? 0 : 0x800000;
            int limit = (int)((unsigned int)((int)(fn_80178A2C() - p->mMotion.mPos.mY) - 4) << 22) / 6;

            if (limit < 0) limit = 0;
            else if (limit > 0x400000) limit = 0x400000;
            int extra = (int)((distance - near) * (0.0f - 4194304.0f) / (far - near) + 4194304.0f);

            if (extra < 0) extra = 0;
            else if (extra > 0x400000 - limit) extra = 0x400000 - limit;
            control->mUnknown44 = angle <= 0x400000 ? angle + limit + extra : angle - limit - extra;
        }
    }
}
#endif

#ifdef DECOMP_COMPARE
extern "C" void fn_8012D4FC(Object_80039F5C *p, int mode)
{
    OptionRunControl_t *control = (OptionRunControl_t *)&p->mUnknown336;
    Object_80039F5C *other = (Object_80039F5C *)mode;
    unsigned char index = control->mUnknown48;
    int angle = control->mUnknown44;
    Point_8017886C ball = fn_80177FE0();
    Point_8017886C point;
    point.mX = fn_8011F4D4();
    float offset = fabsf(p->mMotion.mPos.mX - point.mX);
    int change = 0;

    if (fn_8011F1A4() && fn_8011F1A4() && (unsigned int)fn_8011F4C8() > 3
        && !(p->mMotion.mPos.mY >= ball.mY - 1.0f)
        && !(fabsf(point.mX) <= fabsf(p->mMotion.mPos.mX)) && !(offset <= 3.0f)) {
        float distance = ball.mY - p->mMotion.mPos.mY;
        float projected = distance * (offset / fabsf(ball.mX - point.mX));

        point.mY = ball.mY - (projected <= distance ? projected : distance);
        fn_80227690(&point, &point, &p->mMotion.mPos);
        angle = fn_801CFE40(point.mY, point.mX);
    } else {
        float threshold = fn_801783AC(0) ? -8.0f : 0.0f;

        if (!(control->mValues.mCost[index] < threshold)) {
            float right = control->mValues.mCost[(index + 1) & 7];
            float left = control->mValues.mCost[(index - 1) & 7];

            if (right == left) {
                float distance;
                int team = fn_80178320();
                Object_80039F5C *nearest = fn_801245DC(p, team, 0, fn_80178D18(fn_80178320()),
                                                     0x600000, &distance, 1);

                if (nearest && !(distance >= 4.0f)) {
                    fn_80227690(&point, &nearest->mMotion.mPos, &p->mMotion.mPos);
                    if (((fn_801CFE40(point.mY, point.mX) - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                        right -= 1.0f;
                    } else {
                        left -= 1.0f;
                    }
                }
            }
            if (!(right >= left)) {
                float degrees = (right - control->mValues.mCost[index]) * 5.0f;

                if (!(degrees >= 90.0f)) {
                    change = (int)(fn_801CFB94((int)(degrees * 46603.37890625f)) * 0.5f * 2097152.0f);
                }
            } else if (!(left >= right)) {
                float degrees = (left - control->mValues.mCost[index]) * 5.0f;

                if (!(degrees >= 90.0f)) {
                    change = -(int)(fn_801CFB94((int)(degrees * 46603.37890625f)) * 0.5f * 2097152.0f);
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

            if (candidate <= MathAngleDiff(toward, control->mUnknown44)) {
                control->mUnknown44 = angle;
            }
        } else {
            control->mUnknown44 = angle;
        }
        control->mUnknown48 = ((angle + 0x100000) >> 21) & 7;
    }
}
#endif

#ifdef DECOMP_COMPARE
extern "C" void fn_8012D8A8(Object_80039F5C *p, OptionRunControl_t *control, int *pMode, Entry_801230B8 *entry)
{
    int firstAngle = 0, secondAngle = 0;
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
    Vector_80039F5C point, delta;
    int direction;
    if (linked) {
        Object_80039F5C *partner = fn_8009BCE8(&other->mUnknown1036);
        point.mX = (other->mMotion.mPos.mX + partner->mMotion.mPos.mX) * 0.5f;
        point.mY = (other->mMotion.mPos.mY + partner->mMotion.mPos.mY) * 0.5f;
        fn_80227690(&delta, &other->mMotion.mPos, &p->mMotion.mPos);
        firstAngle = fn_801CFE40(delta.mY, delta.mX);
        fn_80227690(&delta, &partner->mMotion.mPos, &p->mMotion.mPos);
        secondAngle = fn_801CFE40(delta.mY, delta.mX);
        int sector = (firstAngle - secondAngle) & 0xFFFFFF;
        int heading = (control->mUnknown44 - secondAngle) & 0xFFFFFF;
        if ((sector <= 0x7FFFFF && heading <= 0x7FFFFF)
            || (sector > 0x800000 && heading > 0x800000)) {
            if (MathAngleDiff(firstAngle - secondAngle, 0)
                > MathAngleDiff(control->mUnknown44 - secondAngle, 0)) {
                blocked = 1;
            }
        }
        fn_80227690(&delta, &point, &p->mMotion.mPos);
        direction = fn_801CFE40(delta.mY, delta.mX);
        distance = fn_802270A4(&delta);
        if (!(fn_8022781C(&other->mMotion.mPos, &p->mMotion.mPos) >= distance)) {
            distance = fn_8022781C(&other->mMotion.mPos, &p->mMotion.mPos);
            direction = firstAngle;
        }
        if (!(fn_8022781C(&partner->mMotion.mPos, &p->mMotion.mPos) >= distance)) {
            distance = fn_8022781C(&partner->mMotion.mPos, &p->mMotion.mPos);
            direction = secondAngle;
        }
    } else {
        point = other->mMotion.mPos;
        point.mX += other->mMotion.mUnknown40 * 10.0f;
        point.mY += other->mMotion.mUnknown44 * 10.0f;
        fn_80227690(&delta, &point, &p->mMotion.mPos);
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
    int change;
    if (((direction - control->mUnknown44) & 0xFFFFFF) > 0x800000) {
        change = (int)((1.0f - fraction) * 3495253.0f);
        if (linked && blocked) {
            int boundary = ((firstAngle - direction) & 0xFFFFFF) <= 0x7FFFFF ? firstAngle : secondAngle;
            change += MathAngleDiff(boundary, control->mUnknown44);
        }
    } else {
        change = (int)(-((1.0f - fraction) * 3495253.0f));
        if (linked && blocked) {
            int boundary = ((firstAngle - direction) & 0xFFFFFF) > 0x800000 ? firstAngle : secondAngle;
            change -= MathAngleDiff(boundary, control->mUnknown44);
        }
    }
    int candidate = (control->mUnknown44 + change) & 0xFFFFFF;
    int threshold = other->mIdBytes[2] == p->mIdBytes[2] ? 0x18E38E : 0x3C71C7;
    if (MathAngleDiff(candidate, 0xC00000) < threshold) {
        int difference = MathAngleDiff(direction, control->mUnknown44);
        if (difference <= 0x2E38E2) {
            change = (int)((1.0f - fraction) * 3495253.0f);
            if (difference > change) {
                change = 0;
            } else {
                change = MathAngleDiff(change, difference);
            }
            if (((direction - control->mUnknown44) & 0xFFFFFF) <= 0x7FFFFF) {
                change = -change;
            }
            candidate = (control->mUnknown44 + change) & 0xFFFFFF;
        }
    }
    control->mUnknown44 = candidate;
    int turn = MathAngleDiff(p->mMotion.mUnknown32, direction);
    if (turn > 0x400000) {
        turn = 0x400000;
    }
    fn_801CFB18(turn);
    if (control->mUnknown40 < 0.72f
        || (MathAngleDiff(direction, p->mMotion.mFacing) <= 0xE38E2
            && other->mIdBytes[2] == p->mIdBytes[2] && other->mId == p->mUnknown560.mUnknown44)) {
        control->mUnknown52 = 0;
    }
}
#endif

#ifdef DECOMP_COMPARE
extern "C" void fn_8012DDCC(Object_80039F5C *p, OptionRunControl_t *control, int)
{
    int angle = control->mUnknown44;
    if (fn_801486A0()) {
        if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x3FFFFF) {
            int direction;
            if (!(p->mMotion.mPos.mX >= 3.0f - fn_80178A08())) {
                direction = 0x800000;
            } else if (!(p->mMotion.mPos.mX <= fn_80178A08() - 3.0f)) {
                direction = 0;
            } else {
                goto finish;
            }
            if (MathAngleDiff(p->mMotion.mFacing, direction) <= 0x438E38) angle = 0x400000;
        }
        goto finish;
    }
    if (!(p->mMotion.mPos.mY <= fn_80178A44() - 5.0f)) {
        if ((MathAngleDiff(p->mMotion.mFacing, 0) <= 0x3FFFFF
             && p->mMotion.mPos.mX < fn_80178A08() - 3.5f)
            || p->mMotion.mPos.mX < 3.5f - fn_80178A08()) angle = 0;
        else angle = 0x800000;
    } else if (!(p->mMotion.mPos.mY >= 5.0f - fn_80178A44())) {
        if ((MathAngleDiff(p->mMotion.mFacing, 0) <= 0x3FFFFF
             && p->mMotion.mPos.mX < fn_80178A08() - 3.5f)
            || !(p->mMotion.mPos.mX >= 3.5f - fn_80178A08())) angle = 0;
        else angle = 0x800000;
    }
    if (!(p->mMotion.mPos.mX <= fn_80178A08() - 3.5f)) {
        if ((MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x3FFFFF
             && p->mMotion.mPos.mY < fn_80178A44() - 5.0f)
            || p->mMotion.mPos.mY < 5.0f - fn_80178A44()) angle = 0x400000;
        else angle = 0xC00000;
    } else if (!(p->mMotion.mPos.mX >= 3.5f - fn_80178A08())) {
        if ((MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x3FFFFF
             && p->mMotion.mPos.mY < fn_80178A44() - 5.0f)
            || !(p->mMotion.mPos.mY >= 5.0f - fn_80178A44())) angle = 0x400000;
        else angle = 0xC00000;
    }
    if (!(p->mMotion.mPos.mY <= fn_80178A44() * 0.5f)) {
        if (!(p->mMotion.mPos.mX <= fn_80178A08() * 0.2f)) {
            Point_8017886C corner, delta;
            corner.mX = fn_80178A08() * 0.2f;
            corner.mY = fn_80178A44() * 0.5f;
            fn_80227690(&delta, &p->mMotion.mPos, &corner);
            Point_8017886C direction = {-fabsf(delta.mY), fabsf(delta.mX)};
            int first = fn_801CFE40(direction.mY, direction.mX);
            int back = (first + 0x800000) & 0xFFFFFF;
            if (MathAngleDiff(p->mMotion.mFacing, 0x600000) <= 0x3FFFFF) {
                if (((first - p->mMotion.mFacing) & 0xFFFFFF) <= 0x7FFFFF) angle = first;
            } else if (((p->mMotion.mFacing - back) & 0xFFFFFF) <= 0x7FFFFF) angle = back;
        } else if (!(p->mMotion.mPos.mX >= -(fn_80178A08() * 0.2f))) {
            Point_8017886C corner, delta;
            corner.mX = -(fn_80178A08() * 0.2f);
            corner.mY = fn_80178A44() * 0.5f;
            fn_80227690(&delta, &p->mMotion.mPos, &corner);
            Point_8017886C direction = {fabsf(delta.mY), fabsf(delta.mX)};
            int first = fn_801CFE40(direction.mY, direction.mX);
            int back = (first + 0x800000) & 0xFFFFFF;
            if (MathAngleDiff(p->mMotion.mFacing, 0x200000) <= 0x3FFFFF) {
                if (((p->mMotion.mFacing - first) & 0xFFFFFF) <= 0x7FFFFF) angle = first;
            } else if (((back - p->mMotion.mFacing) & 0xFFFFFF) <= 0x7FFFFF) angle = back;
        }
    } else if (!(p->mMotion.mPos.mY >= -(fn_80178A44() * 0.5f))) {
        if (!(p->mMotion.mPos.mX <= fn_80178A08() * 0.2f)) {
            Point_8017886C corner, delta;
            corner.mX = fn_80178A08() * 0.2f;
            corner.mY = -(fn_80178A44() * 0.5f);
            fn_80227690(&delta, &p->mMotion.mPos, &corner);
            Point_8017886C direction = {fabsf(delta.mY), fabsf(delta.mX)};
            int first = fn_801CFE40(direction.mY, direction.mX);
            int back = (first + 0x800000) & 0xFFFFFF;
            if (MathAngleDiff(p->mMotion.mFacing, 0x200000) <= 0x3FFFFF) {
                if (((first - p->mMotion.mFacing) & 0xFFFFFF) <= 0x7FFFFF) angle = first;
            } else if (((p->mMotion.mFacing - back) & 0xFFFFFF) <= 0x7FFFFF) angle = back;
        } else if (!(p->mMotion.mPos.mX >= -(fn_80178A08() * 0.2f))) {
            Point_8017886C corner, delta;
            corner.mX = -(fn_80178A08() * 0.2f);
            corner.mY = -(fn_80178A44() * 0.5f);
            fn_80227690(&delta, &p->mMotion.mPos, &corner);
            Point_8017886C direction = {-fabsf(delta.mY), fabsf(delta.mX)};
            int first = fn_801CFE40(direction.mY, direction.mX);
            int back = (first + 0x800000) & 0xFFFFFF;
            if (MathAngleDiff(p->mMotion.mFacing, 0x600000) <= 0x3FFFFF) {
                if (((p->mMotion.mFacing - first) & 0xFFFFFF) <= 0x7FFFFF) angle = first;
            } else if (((back - p->mMotion.mFacing) & 0xFFFFFF) <= 0x7FFFFF) angle = back;
        }
    }
    if (!(p->mMotion.mPos.mY <= fn_80178A44() - 5.0f)) {
        if (!(p->mMotion.mPos.mY <= fn_80178A44() - 2.5f)) {
            angle = MathAngleDiff(p->mMotion.mFacing, 0) <= 0x3FFFFF ? 0xF77778 : 0x888889;
        }
    } else if (!(p->mMotion.mPos.mY >= 5.0f - fn_80178A44())) {
        if (!(p->mMotion.mPos.mY >= 2.5f - fn_80178A44())) {
            angle = MathAngleDiff(p->mMotion.mFacing, 0) <= 0x3FFFFF ? 0x88888 : 0x777777;
        }
    }
    if (!(p->mMotion.mPos.mX <= fn_80178A08() - 3.5f)) {
        if (!(p->mMotion.mPos.mX <= fn_80178A08() - 2.5f)) {
            angle = MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x3FFFFF ? 0x488888 : 0xB77778;
        }
    } else if (!(p->mMotion.mPos.mX >= 3.5f - fn_80178A08())) {
        if (!(p->mMotion.mPos.mX >= 2.5f - fn_80178A08())) {
            angle = MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x3FFFFF ? 0x377777 : 0xC88889;
        }
    }
finish:
    angle &= 0xFFFFFF;
    control->mUnknown44 = angle;
    control->mUnknown48 = ((angle + 0x100000) >> 21) & 7;
}
#endif

extern "C" int fn_8012E590(Object_80039F5C *p, Object_80039F5C *pOther)
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

#ifdef DECOMP_COMPARE
extern "C" int fn_8012E670(Object_80039F5C *p, Object_80039F5C *, int, int turn, int, float distance)
{
    int kind = 1;
    int side = 0;
    int facing = p->mMotion.mFacing;
    if ((float)p->mRatings[0] < 165.75f || distance > 10.0f || turn > 0x271C70) {
        return 0;
    }
    int facingDifference = MathAngleDiff(facing, 0x400000);
    if (facingDifference > 0x31C71B) {
        return 0;
    }
    unsigned char chance = ((p->mRatings[0] >> 2) + (p->mRatings[0] >> 3)) >> 1;
    chance = (unsigned char)(int)((float)chance
        - (float)facingDifference * 3.06538225913755e-7f * 0.8f * (float)chance);
    Object_80039F5C *pOther = fn_80124CE4(p, p->mIdBytes[2] ^ 1, &distance, 0x271C71, 10.0f, facing, 1.0f);
    if (pOther && pOther->mIdBytes[2] != p->mIdBytes[2] && !fn_8011E9B4(pOther)) {
        Vector_80039F5C delta;
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        turn = MathAngleDiff(angle, p->mMotion.mFacing);
        int right = ((p->mMotion.mFacing - angle) & 0xFFFFFF) > 0x800000;
        int difference = MathAngleDiff(p->mMotion.mFacing, pOther->mMotion.mFacing);
        angle = (angle + 0x800000) & 0xFFFFFF;
        int otherDifference = MathAngleDiff(pOther->mMotion.mFacing, angle);
        int ownDifference = MathAngleDiff(angle, p->mMotion.mFacing);
        if (difference + otherDifference > ownDifference) {
            chance = 0;
        } else {
            int threshold = (int)((float)otherDifference / (float)ownDifference * 2330169.0f + (float)0xAAAAA);
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
    if (!chance || fn_802372EC(0, 100) >= chance) {
        return 0;
    }
    if (!(fn_80178A68(&p->mMotion.mPos) >= 5.0f)) {
        return fn_800F22D8(p, kind, side, 4) != 0;
    }
    return fn_800F22D8(p, kind, side, fn_800F2828(p, pOther)) != 0;
}
#endif

extern "C" int fn_8012EA14(Object_80039F5C *p, Object_80039F5C *pOther)
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

#ifdef DECOMP_COMPARE
extern "C" int fn_8012EAF8(Object_80039F5C *p, Object_80039F5C *pOther, int angle, int turn, int, float distance)
{
    if ((float)p->mRatings[0] < 165.75f || p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
        return 0;
    }
    int kind = 1;
    int side = 0;
    if (pOther->mIdBytes[2] != p->mIdBytes[2] && !(pOther->mFlags & 0x800)
        && (MathAngleDiff(pOther->mMotion.mUnknown32, 0) <= 0x31C71B
            || MathAngleDiff(pOther->mMotion.mUnknown32, 0x800000) <= 0x31C71B)
        && !fn_8012E590(p, pOther) && fn_80124714(p, pOther, 0) == 1) {
        int threshold = 0x438E39;
        int difference = MathAngleDiff((angle + 0x800000) & 0xFFFFFF, pOther->mMotion.mFacing);
        if (difference > 0x200000) {
            difference = 0x200000;
        }
        if (MathAngleDiff(pOther->mMotion.mFacing, p->mMotion.mFacing) > 0x555555) {
            threshold = 0x21C71C;
        } else {
            threshold = (difference - 0x200000 + threshold) & 0xFFFFFF;
            int limit;
            if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x400000) {
                limit = MathAngleDiff(p->mMotion.mFacing, 0x400000);
            } else {
                limit = 0x400000;
            }
            threshold = (threshold - (int)((float)(0x400000 - limit)
                * 2.384185791015625e-7f * 0.5f * (float)threshold)) & 0xFFFFFF;
            if (threshold <= 0x11C71B) {
                threshold = 0x11C71C;
            } else if (threshold > 0x438E39) {
                threshold = 0x438E39;
            }
        }
        if (!(distance > 6.0f) && turn < threshold) {
            if (MathAngleDiff(p->mMotion.mFacing, 0x400000) > 0xE38E3) {
                kind = 2;
                side = 1;
                if (((p->mMotion.mFacing - 0x400000) & 0xFFFFFF) <= 0x7FFFFF) {
                    side = 2;
                }
            } else if (turn <= 0x11C71B) {
                kind = 2;
                side = 2;
                if (((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                    side = 1;
                }
            }
            if (kind != 1 && fn_802372EC(0, 100) < ((unsigned int)(p->mRatings[0] >> 3) & 0x7FFFFFFF)
                && fn_80110824(p, kind, side, fn_80110EB0(p, pOther))) {
                return 1;
            }
        }
    }
    if (p->mUnknown560.mFlags.mBytes[0]) {
        Object_80039F5C *pRef = fn_8009BCE8(&p->mUnknown560.mUnknown44);
        if (pRef && fn_8012EA14(p, pRef)) {
            return 1;
        }
        pRef = fn_8009BCE8(&p->mUnknown560.mUnknown40);
        if (pRef && fn_8012EA14(p, pRef)) {
            return 1;
        }
    }
    return 0;
}
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012EE90(Object_80039F5C *p, Object_80039F5C *pOther, int a, int angle, int b, float distance)
{
    if (!(fn_80178A68(&p->mMotion.mPos) >= 4.0f)) {
        if (!(distance > 5.0f) && angle <= 0x3FFFFF
            && MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x38E38D
            && CarrierMoveStart(p, 4)) {
            return 1;
        }
    } else if (!(distance > 2.5f) && angle <= 0x11C71B && (pOther->mFlags & 0x800)
               && CarrierMoveStart(p, CarrierMovePickKind(p, pOther))) {
        return 1;
    }
    return 0;
}
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012EF94(Object_80039F5C *p, Object_80039F5C *pOther, int a, int angle, int b, float distance)
{
    Object_800B26B0 *motion = &p->mMotion;
    unsigned int chance = (unsigned int)(((p->mRatings[0] >> 3) * 2) + (p->mRatings[2] >> 4)) >> 1;

    if (!(motion->mUnknown44 <= 0.0f) && !(distance > 4.0f) && angle <= 0x2AAAA9
        && !fn_8011E9B4(pOther) && p->mIdBytes[2] != pOther->mIdBytes[2]) {
        float remaining = fn_80178A2C() - motion->mPos.mY;
        float limit = fn_801CFB18(motion->mFacing) * 4.2f;

        if (!(remaining <= 0.0f) && !(remaining >= limit)) {
            if (MathAngleDiff(motion->mFacing, 0x400000) <= 0xAAAA9
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
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012F11C(Object_80039F5C *p, Object_80039F5C *pOther, int angle, int a, int b, float distance)
{
    if (!(pOther->mFlags & 0x800) && !fn_8011E9B4(pOther) && !(distance > 4.5f)
        && p->mIdBytes[2] != pOther->mIdBytes[2]) {
        int delta = (angle - p->mMotion.mFacing) & 0xFFFFFF;
        int side = delta > 0x800000 ? 1 : 2;

        if (MathAngleDiff(delta, side == 1 ? 0xC00000 : 0x400000) <= 0x3FFFFF
            && MathAngleDiff(pOther->mMotion.mUnknown32, angle) > 0x4E38E3) {
            int chance = (unsigned int)(((p->mRatings[2] >> 3) * 2) + (p->mRatings[2] >> 4)) >> 1;
            int facing = MathAngleDiff(p->mMotion.mFacing, 0x400000);

            if (facing > 0x31C71B) {
                if (facing <= 0x400000) {
                    chance = (int)(chance - chance * 0.0000010728831512096804f * (facing - 0x31C71C));
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
#endif

extern "C" int fn_8012F2E0(Object_80039F5C *p, Object_80039F5C *pOther, int a, int b, int c, float d)
{
    return 0;
}

#ifdef DECOMP_COMPARE
extern "C" int fn_8012F2E8(Object_80039F5C *p, Object_80039F5C *pUnused, int a, int b, int c, float d)
{
    Point_8017886C ball = fn_80177FE0();
    Vector_80039F5C aim;
    int result = 0;
    Object_80039F5C *other = fn_80105384(p, 1, &aim);
    int valid = OptionRunCanPitchTo(p, &aim, other);

    if (other && valid && fn_801066D0(p, other, 9) && !(p->mMotion.mPos.mY <= ball.mY)) {
        if (!(other->mRatings[4] <= p->mRatings[4] * lbl_803EB11C)) {
            float target = fn_8012506C(other, 6);
            float own = fn_8012506C(p, 6);

            if (!(own <= target) && !(own <= lbl_803EB124) && !(target >= lbl_803EB124)) {
                result = 1;
            }
        } else {
            if (!(fn_8012506C(p, 6) >= lbl_803EB120)
                && !(fn_8012506C(other, 6) >= lbl_803EB120)) {
                result = 1;
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
#endif

extern "C" int fn_8012F524(Object_80039F5C *p)
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

#ifdef DECOMP_COMPARE
extern "C" void fn_8012F5A0(Object_80039F5C *p, OptionRunControl_t *control, OptionRunMove_t *block)
{
    if (fn_801787A0()) return;
    block->mUnknown0 = (signed char)(((unsigned char *)&block->mUnknown0)[1] - 1);
    if (block->mUnknown0 > 0) return;
    block->mUnknown0 = (signed char)(16 - (p->mRatings[2] + p->mRatings[0]) / 32);
    block->mUnknown0 = fn_800ACC80(p, block->mUnknown0);
    block->mUnknown0 = fn_8009AD30(p, block->mUnknown0);
    if (control) control->mUnknown51[0] = 7;
    float distance;
    int team = fn_80178320();
    Object_80039F5C *other = fn_801245DC(p, team, 0, fn_80178D18(fn_80178320()), lbl_803EB118, &distance, 0);

    if (!other) {
        team = fn_80178308();
        other = fn_801245DC(p, team, 0, fn_80178D18(fn_80178308()), lbl_803EB118, &distance, 0);
    }
    if (other && !(distance > 10.0f)) {
        Point_8017886C delta;

        fn_80227690(&delta, &other->mMotion.mPos, &p->mMotion.mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        int turn = MathAngleDiff(angle, p->mMotion.mFacing);
        int opposed = MathAngleDiff((angle + 0x800000) & 0xFFFFFF, other->mMotion.mFacing) <= 0x1FFFFF;
        unsigned char *order = &lbl_802DB05C[fn_8012F524(p) * 7];
        unsigned char i;

        for (i = 0; i <= 6; i++) {
            if (actions_8012F5A0[order[i]](p, other, angle, turn, opposed, distance)) {
                if (control) control->mUnknown51[0] = order[i];
                return;
            }
        }
    }
    switch (fn_801486A0()) {
    case 0: case 1: case 2: case 3: return;
    }
    Vector_80039F5C position = p->mMotion.mPos;

    if (fn_801784C4()) {
        position.mX = -position.mX;
        position.mY = -position.mY;
    }
    float nearest;
    Object_80040818 *found = fn_80040FD4(&position, 7, &nearest);

    nearest = fn_800AD168(p->mIdBytes[2], nearest);
    if (found && !(nearest >= 3.0f)) {
        if (!(fn_80237260(0) >= 0.5f)) {
            fn_800F22D8(p, 4, 1, 4);
        } else {
            CarrierMoveStart(p, 4);
        }
    }
}
#endif

#ifdef DECOMP_COMPARE
extern "C" void fn_8012F89C(Object_80039F5C *p, OptionRunControl_t *control, int mode)
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
            int found = 0;

            if (turn <= 0x355555) {
                int team = p->mIdBytes[2];

                found = fn_801245DC(p, team, 0, fn_80178D18(team), turn, &distance, 0) != 0;
                if (!found) {
                    team = p->mIdBytes[2] ^ 1;
                    found = fn_801245DC(p, team, 0, fn_80178D18(team), turn, &distance, 0) != 0;
                }
            } else {
                found = 1;
            }
            if (found) {
                control->mUnknown52 = 0;
                if (!(distance >= 3.0f)) {
                    control->mUnknown40 = fn_801CFB94(turn / 2) * 0.72f;
                    control->mUnknown40 = control->mUnknown40 >= 0.5f ? control->mUnknown40 : 0.5f;
                }
            }
        }
    }
}
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012FA64(Object_80039F5C *p)
{
    int enabled = 0;

    if (!fn_80177C38() && !(fn_80177FE0().mY - p->mMotion.mPos.mY <= 4.0f)
        && !(fabsf(fn_80177FE0().mX - p->mMotion.mPos.mX) >= 8.0f) && fn_8011F1A4()) {
        enabled = (unsigned int)fn_8011F4C8() > 3;
    }
    if (enabled) {
        unsigned char team = p->mIdBytes[2];
        unsigned int count = fn_80178D18(team);
        unsigned short i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *other = fn_80039F5C(team, i);

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
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012FC08(Object_80039F5C *p, OptionRunControl_t *control)
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
                if (result) {
                    if (control->mUnknown55 > 20) {
                        result = 0;
                    }
                    if (result) {
                        control->mUnknown56.mUnknown3 = 1;
                        p->mUnknown512.mUnknown15 = 26;
                        return result;
                    }
                }
                control->mUnknown56.mUnknown3 = 0;
            }
        }
    }
    return result;
}
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012FDDC(Object_80039F5C *p, OptionRunControl_t *pControl)
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
#endif

extern "C" int fn_8012FEAC(Object_80039F5C *p)
{
    OptionRunControl_t *pControl = (OptionRunControl_t *)&p->mUnknown336;

    fn_80130338(p, pControl);
    fn_80031404(p);
    if (fn_800AD9B4() == 3) {
        pControl->mUnknown0 = fn_8012FA64(p);
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

extern "C" int fn_8012FF30(Object_80039F5C *p)
{
    fn_800A3B58(p, 2, 0);
    return 1;
}

extern "C" int fn_8012FF5C(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    OptionRunControl_t *pControl = (OptionRunControl_t *)&p->mUnknown336;
    Plan_80121264 plan;
    Message_800F01CC message;
    int mode = 0;

    fn_800B8344(p);
    if (p == BallGetCurrentHolder()) {
        fn_8012CEF4(p, pControl);
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
            fn_8012CFA0(p);
            pControl->mUnknown48 = fn_801243E0(pValues, pMotion->mFacing);
            pControl->mUnknown44 = pControl->mUnknown48 << 21;
            fn_8012D4FC(p, mode);
            fn_8012311C(p, &plan, pControl->mUnknown44);
            pEntry = fn_80123174(&plan);
            if (pEntry) {
                int angle = pEntry->mUnknown16;

                pControl->mUnknown44 = angle;
                pControl->mUnknown48 = ((angle + 0x100000) >> 21) & 7;
            }
            fn_8012D8A8(p, pControl, &mode, pEntry);
            fn_8012DDCC(p, pControl, mode);
            fn_8012D258(p);
            pControl->mUnknown0 = fn_8012FA64(p);
            fn_8012F89C(p, pControl, mode);
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
        fn_8012F5A0(p, pControl, &pControl->mUnknown56);
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
        fn_8012FDDC(p, pControl);
        fn_8012FC08(p, pControl);
        fn_8011168C(p);
    }
    return 0;
}

extern "C" int fn_8013028C(Object_80039F5C *p)
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

extern "C" int fn_80130318(Object_80039F5C *p)
{
    return fn_800B76E8(p);
}

extern "C" void fn_80130338(Object_80039F5C *p, OptionRunControl_t *pControl)
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
        pControl->mUnknown0 = fn_8012FA64(p);
    }
    pControl->mUnknown56.mUnknown2 = 0;
}

#ifdef DECOMP_COMPARE
const Action_8012F5A0 actions_8012F5A0[7] = {
    fn_8012E670, fn_8012EAF8, fn_8012EE90, fn_8012EF94,
    fn_8012F11C, fn_8012F2E0, fn_8012F2E8
};
#endif
