#include "game/State_801297F8.h"
#include "game/Object_80039F5C.h"
#include "game/Record_8011F4F8.h"
#include "game/Record_8011F518.h"
#include "game/cu_80125F3C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_801BE60C.h"
#include <math.h>

extern "C" {
int fn_8013BA58(Object_80137ABC *ball, int *pOut);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_802270A4(void *p);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
float fn_801CFB94(int angle);
int fn_801787A0(void);
int fn_800A7F30(int team);
int fn_800A851C(int team, Object_80039F5C *p);
int fn_801783AC(int bit);
float fn_80178A2C(void);
int fn_800ABDA4(int team);
int fn_8012A3B0(Object_80039F5C *p, Object_80039F5C *other, Vector_80039F5C pos, float distance, int *pOut);
int fn_800E815C(Object_80039F5C *p, int a, int b);
int fn_8011E88C(Object_80039F5C *p);
int fn_8011F1A4(void);
unsigned int fn_8011F4C8(void);
Object_80039F5C *fn_80128B60(void);
int fn_800E6AC8(Object_80039F5C *p, int mode);
int fn_800F2C1C(Object_80039F5C *p, int a);
Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float length, float width, int facing);
int fn_8011E9B4(Object_80039F5C *p);
void fn_8011E240(Object_80039F5C *p);
float fn_80237260(int stream);
extern float lbl_803EB0DC;

int fn_801260D4(Object_80039F5C *p)
{
    Object_80137ABC *ball = fn_801374BC();
    int info;
    if (fn_8013BA58(ball, &info) != 3) return 0;
    Record_8011F518 *record = fn_8011F518();
    if (record->mUnknown4 != 11 && record->mUnknown4 != 9) return 0;
    Object_80039F5C *other = fn_8009BCE8(&record->mUnknown0);
    Vector_80039F5C position;
    fn_80137D58(ball, &position);
    Vector_80039F5C ballDelta;
    Vector_80039F5C playerDelta;
    fn_80227690(&ballDelta, &position, &other->mMotion.mPos);
    fn_80227690(&playerDelta, &p->mMotion.mPos, &other->mMotion.mPos);
    int ballAngle = fn_801CFE40(ballDelta.mY, ballDelta.mX);
    float ballDistance = fn_802270A4(&ballDelta);
    int playerAngle = fn_801CFE40(playerDelta.mY, playerDelta.mX);
    float playerDistance = fn_8022781C(&p->mMotion.mPos, &position);
    short rating = p->mRatings[5];
    if (rating < p->mRatings[8]) rating = p->mRatings[8];
    if (fn_802372EC(0, 255) >= ((unsigned int)rating >> 2)) return 0;
    if (fn_801CFFD0(ballAngle, playerAngle) >= (int)(lbl_803EB0DC * 46603.37890625f)) return 0;
    return !(playerDistance >= ballDistance);
}

void fn_801262B8(Object_80039F5C *p, Object_80039F5C *other, Vector_80039F5C position, float distance, int forced)
{
    int chance = 0;
    int attempt = 0;
    if (fn_801787A0()) return;
    Vector_80039F5C delta;
    fn_80227690(&delta, &position, &p->mMotion.mPos);
    int heading = fn_801CFE40(delta.mY, delta.mX);
    State_801297F8 *state = (State_801297F8 *)&p->mUnknown336;
    if (!fn_800A7F30((unsigned char)(1 - p->mIdBytes[2])) && fn_800A851C(p->mIdBytes[2], p))
        state->mUnknown13 = 0;
    else state->mUnknown13--;
    state->mUnknown14--;
    int done = 0;
    if (other && ((other->mFlags & 0x8000) || fn_801783AC(0)) &&
        !(fn_8022781C(&p->mMotion.mPos, &position) >= 5.0f) &&
        !(fn_80178A2C() - position.mY >= 7.0f)) {
        attempt = 1;
        chance = 100;
    }
    if (state->mUnknown14 <= 0) {
        done = 0;
        state->mUnknown14 = fn_80125FA0(p);
        if (other && !(fn_8022781C(&p->mMotion.mPos, &position) >= 5.0f) &&
            (unsigned int)(fn_801CFFD0(p->mMotion.mFacing, other->mMotion.mUnknown32) - 0x2AAAAB) <= 0x2AAAA9) {
            attempt = 1;
            chance = fn_800ABDA4(other->mIdBytes[2] == 0) ? 50 : 10;
        }
        if (!attempt) {
            if (fn_801CFFD0(heading, p->mMotion.mFacing) <= 0x18E38D)
                attempt = fn_8012A3B0(p, other, position, distance, &chance);
            else chance = 0;
        }
    }
    if (attempt && fn_802372EC(0, 100) < (unsigned int)chance && fn_800E815C(p, 0, 0)) done = 1;
    if (done) return;
    if (state->mUnknown13 <= 0) {
        state->mUnknown13 = fn_80125F3C(p->mRatings);
        if (p->mUnknown1032 == 4 && !fn_8011E88C(p)) {
            int odds = 35;
            if (fn_801783AC(0)) {
                if (!(distance >= 10.0f) && fn_80128B60() == fn_80137B40()) odds = 80;
            } else if (fn_8011F1A4()) {
                if (!forced) {
                    if (distance < 10.0f || (fn_8011F1A4() && fn_8011F4C8() > 3)) {
                        Object_80039F5C *selected = fn_80128B60();
                        odds = fn_80137B40() == selected ? 80 : 0;
                    } else odds = 0;
                }
            } else {
                odds = 70;
                if (other && (other->mFlags & 0x8000) &&
                    !(fabsf(other->mMotion.mPos.mX) <= fabsf(p->mMotion.mPos.mX))) odds = 80;
            }
            if (fn_802372EC(0, 100) < (unsigned int)odds ||
                (!fn_800A7F30((unsigned char)(1 - p->mIdBytes[2])) && fn_800A851C(p->mIdBytes[2], p))) {
                Object_80039F5C *reference = fn_8009BCE8(&p->mUnknown1036);
                int mode = 8;
                if (reference->mUnknown1052 != 1) {
                    Vector_80039F5C unusedDelta;
                    fn_80227690(&unusedDelta, &reference->mMotion.mPos, &p->mMotion.mPos);
                    if (!(fn_80237260(0) >= 0.8f)) mode = 4;
                }
                if (fn_800E6AC8(p, mode)) done = 1;
                else state->mUnknown13 += 10;
            }
        }
    }
    if (done) return;
    Object_80137ABC *ball = fn_801374BC();
    if (fn_8013BA58(ball, 0) == 4) {
        Record_8011F4F8 *record = fn_8011F4F8(fn_801374E0(ball));
        int ballAngle;
        if (other && (fn_801BE648(other->mpUnknown792) == 69 || fn_801BE648(other->mpUnknown792) == 178) &&
            (record->mUnknown1D <= 1 || record->mUnknown1D == 6 || record->mUnknown1D == 7)) {
            position = other->mMotion.mPos;
            position.mZ = 6.0f;
            Object_80039F5C *target = fn_80039F5C(other->mIdBytes[2], record->mUnknownAByte);
            Vector_80039F5C direction;
            fn_80227690(&direction, &target->mMotion.mPos, &other->mMotion.mPos);
            ballAngle = fn_801CFE40(direction.mY, direction.mX);
        } else {
            fn_80137D58(ball, &position);
            Vector_80039F5C velocity;
            fn_80137EC4(ball, &velocity);
            ballAngle = fn_801CFE40(velocity.mY, velocity.mX);
        }
        if (!(position.mZ >= 7.0f) && !(position.mZ <= 1.5f) &&
            !(position.mY >= fn_80177FE0().mY + 2.0f) &&
            (p->mUnknown1032 == 4 || !(p->mMotion.mPos.mY >= fn_80177FE0().mY))) {
            fn_80227690(&delta, &position, &p->mMotion.mPos);
            if (fn_801CFFD0(ballAngle, fn_801CFE40(delta.mY, delta.mX)) > 0x78E38E) {
                int facing = p->mMotion.mFacing;
                if (fn_801CFFD0(facing, fn_801CFE40(delta.mY, delta.mX)) <= 0x3FFFFF &&
                    !(fn_802270A4(&delta) >= 6.0f) && fn_802372EC(0, 100) <= 49) fn_800F2C1C(p, 0);
            }
        }
    } else if (p->mUnknown1032 == 4 && other) {
        Object_80039F5C *reference = fn_8009BCE8(&p->mUnknown1036);
        fn_80227690(&delta, &reference->mMotion.mPos, &p->mMotion.mPos);
        int angle = fn_801CFFD0(heading, fn_801CFE40(delta.mY, delta.mX));
        if (angle > 0x471C72) {
            int mode = ((state->mUnknown8 - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000;
            if (angle <= 0x5FFFFF) fn_800E6AC8(p, mode);
            else fn_8011E240(reference);
        }
    }
}

void fn_801269B8(Object_80039F5C *p, State_801297F8 *state, float unusedDistance)
{
    Vector_80039F5C target = {0.0f, 0.0f, 0.0f};
    if (p->mUnknown1032 == 4) return;
    float distance;
    Object_80039F5C *other = fn_80124C28(p, &distance, 0x38E38E, 3.0f, 0.5f, state->mUnknown8);
    if (!other || distance >= 3.0f) return;
    float limit = 3.0f;
    if (other == fn_80137B40() && !fn_801787A0()) return;
    int mode = fn_8011E9B4(other);
    if (other->mIdBytes[2] == p->mIdBytes[2] && !mode) limit *= 0.5f;
    if (distance >= limit) return;
    int inside = 0;
    int a = 0;
    int b = 0;
    if (mode) {
        Object_80039F5C *reference = fn_8009BCE8(&other->mUnknown1036);
        target.mX = (other->mMotion.mPos.mX + reference->mMotion.mPos.mX) * 0.5f;
        target.mY = (other->mMotion.mPos.mY + reference->mMotion.mPos.mY) * 0.5f;
        Vector_80039F5C delta;
        fn_80227690(&delta, &other->mMotion.mPos, &p->mMotion.mPos);
        a = fn_801CFE40(delta.mY, delta.mX);
        fn_80227690(&delta, &reference->mMotion.mPos, &p->mMotion.mPos);
        b = fn_801CFE40(delta.mY, delta.mX);
        int span = (a - b) & 0xFFFFFF;
        int offset = (state->mUnknown8 - b) & 0xFFFFFF;
        if ((span <= 0x7FFFFF && offset <= 0x7FFFFF) || (span > 0x800000 && offset > 0x800000)) {
            if (fn_801CFFD0(a - b, 0) > fn_801CFFD0(state->mUnknown8 - b, 0)) inside = 1;
        }
    } else {
        target = other->mMotion.mPos;
        target.mX += other->mMotion.mUnknown40 * 15.0f;
        target.mY += other->mMotion.mUnknown44 * 15.0f;
    }
    Vector_80039F5C delta;
    fn_80227690(&delta, &target, &p->mMotion.mPos);
    int heading = fn_801CFE40(delta.mY, delta.mX);
    float weight = distance * 0.4f;
    if (!(weight <= 1.0f)) weight = 1.0f;
    fn_80137B40();
    int step = 0;
    if (fn_801CFFD0(heading, state->mUnknown8) <= 0x271C70) {
        if (((heading - state->mUnknown8) & 0xFFFFFF) > 0x800000) {
            step = (int)((1.0f - weight) * 3728270.0f);
            if (mode && inside) {
                int chosen = ((a - heading) & 0xFFFFFF) <= 0x7FFFFF ? a : b;
                step += fn_801CFFD0(chosen, heading);
            }
        } else {
            step = (int)(-((1.0f - weight) * 3728270.0f));
            if (mode && inside) {
                int chosen = ((a - heading) & 0xFFFFFF) > 0x800000 ? a : b;
                step -= fn_801CFFD0(chosen, heading);
            }
        }
        int difference = fn_801CFFD0(state->mUnknown8 + step, p->mMotion.mFacing);
        if (difference > 0x11C71C) {
            float scale = fn_801CFB94(difference / 2);
            state->mUnknown16 = 0;
            state->mUnknown0 = scale * 0.72f;
        } else if (!(distance >= 2.1f) && fn_801CFFD0(heading, p->mMotion.mFacing) <= 0x1FFFFF) {
            state->mUnknown16 = 0;
        }
    }
    state->mUnknown8 = (state->mUnknown8 + step) & 0xFFFFFF;
}
}
