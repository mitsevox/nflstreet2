/* Player state 21: a player without the ball looks for open space. He scores a grid of
   nearby defenders and team-mates around him, picks the least crowded cell between the line
   of the ball and the far end of the field, cuts toward it or runs there, and turns back to
   wave for the ball when the carrier is behind him. */

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

#ifdef DECOMP_COMPARE
struct State_8012A824 {
    char mUnknown0[20];
    float mUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown32;
    unsigned short mUnknown36;
    unsigned char mUnknown38;
    unsigned char mUnknown39;
    unsigned char mUnknown40;
};
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012A6B0(Object_80039F5C *p)
{
    float a, b;
    int facing = p->mMotion.mFacing;
    int result = 0;

    fn_8012BB6C(&a, &b);
    if ((MathAngleDiff(facing, 0x400000) <= 0x438E38 && p->mMotion.mPos.mY < b)
        || (!(p->mMotion.mPos.mY <= b) && !(p->mMotion.mPos.mY >= a))) {
        result = 1;
    }
    if (result) {
        if ((!(fn_80178A08() - p->mMotion.mPos.mX >= 4.0f)
             && MathAngleDiff(facing, 0) <= 0x1FFFFF)
            || (!(-fn_80178A08() - p->mMotion.mPos.mX <= -4.0f)
                && MathAngleDiff(facing, 0x800000) <= 0x1FFFFF)) {
            result = 0;
        }
    }
    if (p->mFlags & 0x4000) {
        result = 0;
    }
    if (!(p->mMotion.mUnknown28 >= PlyrMoveGetRatedSpeed(p, 0.14f, 1.0f))) {
        Object_80039F5C *pOther = BallGetCurrentHolder();

        if (pOther && pOther->mpState->mId == 15) {
            result = 0;
        }
    }
    return result;
}
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012A824(Object_80039F5C *p, float a, float b)
{
    Point_8017886C delta = {0.0f, 0.0f};
    State_8012A824 *state = (State_8012A824 *)&p->mUnknown336;
    Object_80039F5C *carrier = BallGetCurrentHolder();
    unsigned char count = 0;
    int tracking = 0;
    int angle = 0;
    if (!carrier) {
        return 0;
    }
    fn_80227690(&delta, &carrier->mMotion.mPos, &p->mMotion.mPos);
    if (p->mMotion.mPos.mY <= a || p->mMotion.mPos.mY >= b
        || (float)state->mUnknown36 >= state->mUnknown20
        || fabsf(delta.mX) >= fn_80178A08()
        || fabsf(p->mMotion.mPos.mX) >= fn_80178A08() - 1.0f) {
        return 0;
    }
    unsigned int total = fn_80178D18(fn_80178320());
    for (unsigned char i = 0; i < total; ++i) {
        Object_80039F5C *other = fn_80039F5C(fn_80178320(), i);
        Point_8017886C offset;
        fn_80227690(&offset, &other->mMotion.mPos, &p->mMotion.mPos);
        int otherAngle = fn_801CFE40(offset.mY, offset.mX);
        angle = fn_801CFE40(delta.mY, delta.mX);
        if (MathAngleDiff(otherAngle, angle) <= 0x555554 && fn_802270A4(&offset) < 5.0f) {
            count = 1;
            break;
        }
        if (other->mpState->mId == 22 && fn_8009BCE8((int *)&other->mUnknown336) == p) {
            tracking = 1;
            break;
        }
    }
    if (count || tracking) {
        return 0;
    }
    total = fn_80178D18(fn_80178308());
    for (unsigned char i = 0; i < total; ++i) {
        Object_80039F5C *other = fn_80039F5C(fn_80178308(), i);
        if (other != p) {
            Point_8017886C offset;
            fn_80227690(&offset, &other->mMotion.mPos, &p->mMotion.mPos);
            int otherAngle = fn_801CFE40(offset.mY, offset.mX);
            if (MathAngleDiff(otherAngle, angle) <= 0x555554 && fn_802270A4(&offset) < 5.0f) {
                ++count;
            }
        }
    }
    return count == 0;
}
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012AACC(Point_8017886C *out, Object_80039F5C *p, float lower, float upper)
{
    int grid[9][12];
    fn_801C1F94(grid, 0, sizeof(grid));
    out->mX = out->mY = 0.0f;
    float right = p->mMotion.mPos.mX + 27.0f;
    float left = p->mMotion.mPos.mX - 27.0f;
    float top = p->mMotion.mPos.mY + 42.0f;
    float bottom = p->mMotion.mPos.mY - 42.0f;
    if (!(top >= upper)) {
        upper = top;
        lower = top - 10.5f;
    }
    int team = fn_80178320();
    unsigned int total = fn_80178D70(team);
    for (unsigned char i = 0; i < total; ++i) {
        Object_80039F5C *other = fn_80039F5C(team, i);
        Point_8017886C point;
        if (other->mpState->mId == 22 && fn_8009BCE8((int *)&other->mUnknown336)
            && other->mpState->mId == 19) {
            point = *(Point_8017886C *)&other->mUnknown336;
        } else {
            point.mX = other->mMotion.mPos.mX;
            point.mY = other->mMotion.mPos.mY;
        }
        if (!(point.mX <= left) && !(point.mX >= right)
            && !(point.mY <= bottom) && !(point.mY >= top)) {
            int x = (int)((point.mX - p->mMotion.mPos.mX) * (1.0f / 6.0f)) + 4;
            int y = (int)((point.mY - p->mMotion.mPos.mY) * (1.0f / 7.0f)) + 6;
            if (x < 0) x = 0; else if (x > 8) x = 8;
            if (y < 0) y = 0; else if (y > 11) y = 11;
            grid[x][y] += 4;
        }
    }
    team = fn_80178308();
    for (unsigned char i = 0; i <= 2; ++i) {
        unsigned char valid;
        unsigned short index = PlayBookGetReceiver(team, i, &valid);
        if (valid) {
            Object_80039F5C *other = fn_80039F5C(team, index);
            if (other != p) {
                Point_8017886C point;
                if (other->mpState->mId == 19) {
                    point = *(Point_8017886C *)&other->mUnknown336;
                } else {
                    point.mX = other->mMotion.mPos.mX;
                    point.mY = other->mMotion.mPos.mY;
                }
                int x = (int)((point.mX - p->mMotion.mPos.mX) * (1.0f / 6.0f)) + 4;
                int y = (int)((point.mY - p->mMotion.mPos.mY) * (1.0f / 7.0f)) + 6;
                if (x < 0) x = 0; else if (x > 8) x = 8;
                if (y < 0) y = 0; else if (y > 11) y = 11;
                grid[x][y] += 8;
            }
        }
    }
    Object_80039F5C *carrier = BallGetCurrentHolder();
    if (carrier) {
        float width = fn_80178A08();
        width += width;
        float x = carrier->mMotion.mPos.mX;
        float minimum, maximum;
        if (!(x >= 0.0f)) {
            float candidate = x - width * (1.0f / 3.0f);
            if (!(-fn_80178A08() >= candidate)) minimum = candidate;
            else minimum = -fn_80178A08();
            maximum = width * (1.0f / 3.0f) + x;
            if (!(maximum <= 0.0f)) maximum = 0.0f;
        } else {
            float candidate = width * (1.0f / 3.0f) + x;
            if (!(fn_80178A08() <= candidate)) maximum = candidate;
            else maximum = fn_80178A08();
            minimum = x - width * (1.0f / 3.0f);
            if (!(minimum >= 0.0f)) minimum = 0.0f;
        }
        for (unsigned char i = 0; i <= 8; ++i) {
            float column = (float)i * 6.0f - 27.0f;
            if (!(column >= maximum) && !(column <= minimum)) {
                for (unsigned char j = 0; j <= 11; ++j) {
                    grid[i][j] -= 4;
                }
            }
        }
    }
    int best = 200;
    int bestX = 255, bestY = 255;
    for (unsigned char i = 0; i <= 8; ++i) {
        float x = (float)i * 6.0f - 27.0f + p->mMotion.mPos.mX;
        if (!(x <= 4.0f - fn_80178A08()) && !(x >= fn_80178A08() - 4.0f)) {
            for (unsigned char j = 0; j <= 11; ++j) {
                float y = (float)j * 7.0f - 42.0f + p->mMotion.mPos.mY;
                if (!(y <= lower) && !(y >= upper)) {
                    if (grid[i][j] < best) {
                        best = grid[i][j];
                        bestX = i;
                        bestY = j;
                    } else if (grid[i][j] == best && fn_802372EC(0, 100) <= 19) {
                        bestX = i;
                        bestY = j;
                    }
                }
            }
        }
    }
    if (bestX == 255) {
        return 0;
    }
    out->mX = (float)bestX * 6.0f - 27.0f + p->mMotion.mPos.mX;
    out->mY = (float)bestY * 7.0f - 42.0f + p->mMotion.mPos.mY;
    fn_8012BB6C(&upper, &lower);
    if (!(out->mX >= 4.0f - fn_80178A08())) {
        out->mX = 4.0f - fn_80178A08();
    } else if (out->mX > fn_80178A08() - 4.0f) {
        out->mX = fn_80178A08() - 4.0f;
    }
    if (out->mY < lower) out->mY = lower;
    else if (!(out->mY <= upper)) out->mY = upper;
    return 1;
}
#endif

extern "C" void fn_8012B268(Object_80039F5C *p)
{
    Message_800F01CC message;
    Point_8017886C point;

    fn_8012B2E0(p, &point);
    fn_801C1F94(&message, 0, 4);
    message.mId = 19;
    fn_800FD68C(&message, &p->mMotion, &point);
    message.mUnknown1[2] = 255;
    fn_800F00D4(0, p->mpState, &message, p);
}

#ifdef DECOMP_COMPARE
extern "C" void fn_8012B2E0(Object_80039F5C *p, Point_8017886C *pOut)
{
    float a, b;

    fn_8012BB6C(&a, &b);
    fn_80227538(pOut, p->mMotion.mUnknown32, 5.0f);
    pOut->mX += p->mMotion.mPos.mX;
    pOut->mY += p->mMotion.mPos.mY;
    fn_80177FE0();
    pOut->mX = pOut->mX > fn_80178A08() - 4.0f ? fn_80178A08() - 4.0f : pOut->mX;
    pOut->mX = pOut->mX < 4.0f - fn_80178A08() ? 4.0f - fn_80178A08() : pOut->mX;
    pOut->mY = pOut->mY < b ? b : (pOut->mY <= a ? pOut->mY : a);
}
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012B3EC(Object_80039F5C *p)
{
    State_8012A824 *state = (State_8012A824 *)&p->mUnknown336;
    state->mUnknown38 = 0;
    state->mUnknown24 = 0;
    state->mUnknown28 = (int)((float)(int)((1.0f - (float)p->mRatings[3] * (1.0f / 255.0f)) * 5.0f) + 2.0f);
    state->mUnknown40 = 0;
    state->mUnknown39 = 0;
    state->mUnknown36 = 0;
    state->mUnknown20 = 250.0f;
    state->mUnknown32 = 700;
    fn_8009A8D4(state);
    if (p->mIdBytes[3] == 1) {
        float fraction = (float)p->mRatings[3] * (1.0f / 255.0f);
        state->mUnknown32 -= (int)(fraction * 400.0f);
        state->mUnknown20 += fraction * 150.0f;
    }
    int result = fn_8012A6B0(p);
    if (result) {
        Point_8017886C ball = fn_80177FE0();
        int near = 0;
        result = 0;
        if (!(p->mMotion.mPos.mY >= ball.mY + 5.0f)) {
            result = MathAngleDiff(p->mMotion.mUnknown32, 0x400000) <= 0x3FFFFF;
        }
        if (result) {
            near = 1;
        }
        if (!near) {
            result = fn_80103D6C(p);
            if (!result) {
                unsigned char a, b;
                if (fn_800C13A0(p, &a, &b) > 1 && BallGetCurrentHolder()) {
                    if (!(fabsf(fn_80178A08() - p->mMotion.mPos.mX) >= 9.0f)) {
                        state->mUnknown28 = result;
                    }
                    return 0;
                }
            }
        }
        fn_8012B268(p);
    } else if (!(fabsf(fn_80178A08() - p->mMotion.mPos.mX) >= 9.0f)) {
        state->mUnknown28 = result;
    }
    return 0;
}
#endif

#ifdef DECOMP_COMPARE
extern "C" int fn_8012B654(Object_80039F5C *p)
{
    State_8012A824 *state = (State_8012A824 *)&p->mUnknown336;
    p->mFlags |= 0x80000000;
    BallGetCurrent();
    fn_8010A2DC(p, 0, -1);
    if (p->mFlags & 0x4000) {
        return fn_80112928(p) != 0;
    }
    if (--state->mUnknown28 < 0) {
        state->mUnknown28 = (int)((float)(int)((1.0f - (float)p->mRatings[3] * (1.0f / 255.0f)) * 5.0f) + 2.0f);
        if (fn_80112928(p)) {
            return 1;
        }
    }
    Message_800F01CC message;
    if (BallGetCurrentHolder() && fn_801783AC(0)) {
        fn_801C1F94(&message, 0, 4);
        message.mId = 33;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    float a, b;
    state->mUnknown24 -= 2;
    if (state->mUnknown24 < 0 || !(fabsf(p->mMotion.mPos.mX) <= fn_80178A08() - 4.0f)) {
        int available = 0;
        if (BallGetCurrentHolder() && fn_80103D6C(p)) {
            unsigned char first, second;
            available = fn_800C13A0(p, &first, &second) <= 1;
        }
        if (!state->mUnknown39 && available && fn_8012A6B0(p)) {
            fn_8012B268(p);
            goto fallback;
        }
        fn_8012BB6C(&a, &b);
        if (state->mUnknown39) {
            if (p->mFlags & 4) {
                p->mFlags &= ~4;
                state->mUnknown39 = 0;
                state->mUnknown40 = 1;
            }
        } else if (fn_8012A824(p, b, a)) {
            if (MathAngleDiff(p->mMotion.mFacing, 0xC00000) > 0x71C70) {
                p->mUnknown512.mUnknown14 = 6;
                p->mUnknown512.mUnknown8 = 0xC00000;
                p->mUnknown512.mUnknown0 = 4.0f;
                p->mUnknown512.mUnknown4 = 0xC00000;
            } else {
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown4 = 0xC00000;
                p->mUnknown512.mUnknown0 = 0.0f;
                p->mUnknown512.mUnknown8 = 0xC00000;
            }
            ++state->mUnknown36;
            if (!fn_80103D6C(p) && MathAngleDiff(p->mMotion.mFacing, 0xC00000) <= 0x71C70
                && !state->mUnknown40 && fn_802372EC(0, state->mUnknown32) < state->mUnknown36) {
                p->mUnknown512.mUnknown14 = 0;
                fn_8009BD60(p);
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 152, 1.0f, p);
                state->mUnknown39 = 1;
            }
        } else {
            state->mUnknown36 = 0;
        }
        if (state->mUnknown36) {
            return 0;
        }
        Point_8017886C point, delta;
        if (fn_8012AACC(&point, p, b, a)) {
            fn_80227690(&delta, &point, &p->mMotion.mPos);
            fn_8012C648(p, fn_801CFE40(delta.mY, delta.mX));
            fn_801C1F94(&message, 0, 4);
            message.mId = 19;
            fn_800FD68C(&message, &p->mMotion, &point);
            message.mUnknown1[2] = 255;
            if (fn_800F06F4(0, p->mpState, 20, 65535) == 65535) {
                fn_800F053C(0, p->mpState, &message, p);
            } else {
                fn_800F03D8(0, p->mpState, &message, p);
            }
            fn_801C1F94(&message, 0, 4);
            message.mId = 21;
            fn_800F03D8(0, p->mpState, &message, p);
            return 0;
        }
    }
fallback:
    if (!state->mUnknown36) {
        if (state->mUnknown38) {
            p->mUnknown512.mUnknown14 = 10;
            p->mUnknown512.mUnknown0 = 0.5f;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        } else {
            float speed = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
            if (!(speed >= 0.14f)) speed = 0.14f;
            p->mUnknown512.mUnknown0 = speed;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        }
    }
    return 0;
}
#endif

#ifdef DECOMP_COMPARE
extern "C" void fn_8012BB6C(float *pA, float *pB)
{
    switch (fn_80177F70()) {
    case 3:
    case 4:
    case 5:
        *pB = fn_80178298() + 1.0f;
        break;
    case 6:
        *pB = fn_80178A2C();
        break;
    default:
        if (!(fn_80177FE0().mY <= fn_80178A2C() - 12.0f)) {
            *pB = fn_80178A2C() + 1.0f;
        } else {
            *pB = fn_80177FE0().mY + 3.0f;
        }
        break;
    }
    Object_80039F5C *pOther = BallGetCurrentHolder();

    if (pOther) {
        *pA = pOther->mMotion.mPos.mY + 30.0f;
    } else {
        *pA = fn_80177FE0().mY + 30.0f;
    }
    if (!(*pA >= *pB + 10.5f)) {
        *pA = *pB + 10.5f;
    }
    if (!(*pA <= fn_80178A44() - 2.0f)) {
        *pA = fn_80178A44() - 2.0f;
    }
}
#endif
