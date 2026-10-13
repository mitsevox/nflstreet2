#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/State_80134E24.h"
#include "game/Input_800B6D34.h"
#include "game/fn_80177FE0.h"
#include "game/fn_801C1F94.h"
#include "game/fn_800F06F4.h"
#include "game/fn_800B65A0.h"
#include "game/cu_80136B1C.h"

struct Aim_801327F4 {
    char mUnknown0[8];
    float mUnknown8;
    int mUnknownC, mUnknown10;
};

static float data_802DB0F4[7][8] = {
    {0, .75f, 1, .75f, 0, 2, 3, 2},
    {-1, 0, 0, 0, -1, 2, 3, 2},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 55, 60, 55},
    {1, 0, -1, 0, 1, 2, 3, 2},
    {7, 4, 0, -2, -1, 4, 12, 10},
    {-1, -2, 0, 4, 7, 10, 12, 4},
};

struct Mode_80133C50 {
    float mUnknown0, mUnknown4, mUnknown8;
    int mUnknownC, mUnknown10, mUnknown14;
    unsigned char mUnknown18, mUnknown19, mUnknown1A, mUnknown1B;
};

extern "C" {
void fn_801339E4(Object_80039F5C *, Object_80039F5C *, Aim_801327F4 *);
int fn_8011E3F4(Object_80039F5C *);
int fn_80124B1C(Object_80039F5C *, Object_80039F5C *, int, float, float);
Object_80039F5C *fn_80124C28(Object_80039F5C *, float *, int, int, float, float);

extern float lbl_803EB158, lbl_803EB15C, lbl_803ECB08;
unsigned int fn_8011E188(void);
void fn_8011E3EC(Object_80039F5C *, int);
void fn_8011E1BC(Object_80039F5C *, Object_80039F5C *, int, int);
int fn_801787A0(void);
int fn_8009FB60(Object_80039F5C *);
int fn_8011F524(void);
int fn_8011F2C4(void);
int fn_8010A2DC(Object_80039F5C *, int, int);
int fn_80178C9C(void);
int fn_800BA6F8(void);
int fn_800BAA24(void);
void fn_80133044(Object_80039F5C *, Object_80039F5C *, Mode_80133C50 *, float *);
int fn_8011E8A4(Object_80039F5C *);
int fn_800B7E60(Object_80039F5C *);
int fn_800B7F34(Object_80039F5C *);
void fn_800B6E68(Object_80039F5C *, Input_800B6D34 *);

extern float lbl_803EB144, lbl_803EB148, lbl_803EB14C, lbl_803EB150;
extern float lbl_803EB16C, lbl_803EB170, lbl_803EB174, lbl_803EB178, lbl_803EB17C, lbl_803EB180;
extern float lbl_803EB154;
extern unsigned char lbl_803EB160, lbl_803EB16B;
void fn_8011E240(Object_80039F5C *);
int fn_80177F70(void);
float fn_80178298(void);
float fn_80178A08(void);
float fn_80178A2C(void);
float fn_80178A44(void);
int fn_801CFE40(float, float);
int fn_801CFFD0(int, int);
float fn_8022781C(void *, void *);
void fn_80227690(void *, void *, void *);
float fn_802270A4(void *);
int fn_80120794(Object_800B26B0 *, Object_800B26B0 *, float *, float, float, int, float);
int fn_8011F32C(void);
Object_80039F5C *fn_80137BEC(void);
Object_80039F5C *fn_80137B40(void);
int fn_801783AC(int);
int fn_8011F2F8(void);
void fn_800C89F0(Object_80039F5C *, int, int, int, float);
int fn_80124714(Object_80039F5C *, Object_80039F5C *, Object_80039F5C **);
int fn_80178320(void);
unsigned int fn_80178D18(int);
Object_80039F5C *fn_801244F0(Object_80039F5C *, int, int, unsigned char, float *, int);
int fn_801486A0(void);
int fn_80156704(void);
float fn_80124FE0(Object_80039F5C *, int);
float fn_80125004(Object_80039F5C *, int, int);
void fn_8006F0B8(int);
int fn_800ABDA4(int);
float fn_80237260(int);
unsigned int fn_802372EC(unsigned int, unsigned int);
void fn_80168E54(int, unsigned char, unsigned char);
unsigned char fn_80168E00(int, unsigned char, unsigned char *);
int fn_801788D8(int *);
int fn_80178308(void);
unsigned int fn_801787DC(int);
Object_80039F5C *fn_80124E5C(Object_80039F5C *, int, float *, int, int, float, float);

int fn_80132630(Object_80039F5C *p, Vector_80039F5C *point, Object_80039F5C *other)
{
    signed char line = (signed char)(int)fn_80178A2C();
    signed char y = (signed char)(int)p->mMotion.mPos.mY;
    int allowed = (float)(line - y) >= 1.5f;
    if (point && other) {
        if (fn_80177F70() > 2 && !(p->mMotion.mPos.mY <= fn_80178298()) && !(point->mY >= fn_80178298()))
            allowed = 0;
        if (other->mpState->mId != 90 && !(point->mY >= lbl_803EB150 - fn_80178A2C()))
            allowed = 0;
        float x = fabsf(point->mX);
        if (!(x >= fabsf(fn_80178A08())) && !(x >= fabsf(other->mMotion.mPos.mX)) && !(x >= lbl_803EB148))
            allowed = 0;
        if (!(fn_8022781C(&p->mMotion.mPos, &other->mMotion.mPos) >= lbl_803EB144))
            allowed = 0;
        if (fn_801CFFD0(other->mMotion.mFacing, 0xC00000) < (int)(lbl_803EB14C * 46603.37890625f))
            allowed = 0;
    }
    return allowed;
}

void fn_801327F4(Object_80039F5C *p, Object_80039F5C *other, Aim_801327F4 *aim, float *values)
{
    float point[2] = {values[0], values[1]};
    float delta[2];
    aim->mUnknown8 = 0.4f;
    int fallback = 1;
    if (other) {
        fn_80227690(delta, &other->mMotion.mPos, &p->mMotion.mPos);
        float distance = fn_802270A4(delta);
        if (!(distance >= 3.25f)) {
            fallback = 0;
            aim->mUnknown10 = fn_801CFE40(delta[1], delta[0]);
            int angle = fn_80120794(&p->mMotion, &other->mMotion,
                &other->mMotion.mUnknown40, p->mMotion.mUnknown28,
                other->mMotion.mUnknown28, other->mMotion.mUnknown32, distance);
            if (((p->mMotion.mFacing - angle) & 0xFFFFFF) > 0x800000)
                aim->mUnknownC = (0xC00000 - (int)((float)lbl_803EB160 * 46603.37890625f)) & 0xFFFFFF;
            else
                aim->mUnknownC = (0xC00000 + (int)((float)lbl_803EB160 * 46603.37890625f)) & 0xFFFFFF;
            aim->mUnknown8 = other->mMotion.mUnknown28 != 0.0f ? 1.25f : 0.4f;
        }
    }
    if (fallback) {
        delta[0] = point[0];
        if (p->mUnknown2914 <= 2)
            delta[0] = !(p->mMotion.mPos.mX >= point[0]) ? point[0] - 2.0f : point[0] + 2.0f;
        delta[1] = point[1] - 9.0f;
        fn_80227690(delta, &p->mMotion.mPos, delta);
        aim->mUnknown10 = fn_801CFE40(delta[1], delta[0]);
        aim->mUnknownC = (aim->mUnknown10 - 0x800000) & 0xFFFFFF;
    }
}

int fn_80132A4C(Object_80039F5C *p, Object_80039F5C *ball, Object_80039F5C *other,
               float *point, Vector_80039F5C *location, int angle, int otherAngle, float distance)
{
    float reference[2] = {point[0], point[1]};
    float delta[2];
    int reverse = (angle + 0x800000) & 0xFFFFFF;
    fn_80227690(delta, &other->mMotion.mPos, &p->mMotion.mPos);
    if (fn_801CFFD0(reverse, fn_801CFE40(delta[1], delta[0])) <= 0x471C72)
        return 0;
    if (ball && !(ball->mFlags & 0x8000) && !(p->mMotion.mPos.mY + 1.0f >= location->mY) &&
        !(other->mMotion.mPos.mY + 1.0f >= location->mY)) {
        float a = fn_8022781C(location, &p->mMotion.mPos);
        float b = fn_8022781C(location, &other->mMotion.mPos);
        if (a < b) return 1;
    }
    if (p->mMotion.mPos.mY <= reference[1] - 9.0f || p->mMotion.mPos.mY >= other->mMotion.mPos.mY + 1.0f)
        return 0;
    if (!(other->mMotion.mPos.mY > reference[1]) && !(distance < 3.5f) && !fn_8011F32C())
        return 0;
    if (ball) {
        if (!(ball->mMotion.mPos.mY <= reference[1] - 3.5f) &&
            (ball->mMotion.mUnknown32 & 0xFFFFFF) > 0x800000)
            return 1;
    } else {
        Object_80039F5C *entry = fn_80137BEC();
        if (entry) {
            fn_80227690(delta, &other->mMotion.mPos, &entry->mMotion.mPos);
            otherAngle = fn_801CFE40(delta[1], delta[0]);
            fn_80227690(delta, &p->mMotion.mPos, &entry->mMotion.mPos);
            angle = fn_801CFE40(delta[1], delta[0]);
        }
    }
    return fn_801CFFD0(angle, otherAngle) < 0x11C71C;
}

void fn_80132C84(Object_80039F5C *p, Object_80039F5C *ball, Mode_80133C50 *s, float *location, float *values)
{
    float point[2] = {values[0], values[1]};
    if (fn_8011F32C()) {
        s->mUnknown10 = 0x400000;
        s->mUnknown8 = 0.0f;
        return;
    }
    float x;
    if (!(location[0] >= 6.0f - fn_80178A08()))
        x = 6.0f - fn_80178A08();
    else if (location[0] > fn_80178A08() - 6.0f)
        x = fn_80178A08() - 6.0f;
    else
        x = location[0];
    location[0] = x;
    float target[2];
    unsigned int kind = p->mUnknown2914;
    if (kind - 5 <= 4) {
        int n = kind - 7;
        target[0] = x + (float)n * 2.0f;
        int magnitude = n < 0 ? -n : n;
        target[1] = location[1] + (3.0f - (float)magnitude);
        if (!(target[1] <= point[1]) && (ball->mMotion.mUnknown32 & 0xFFFFFF) > 0x800000)
            target[1] = p->mMotion.mPos.mY;
    } else if (s->mUnknown1B & 1) {
        target[0] = x;
        target[1] = p->mMotion.mPos.mY;
    } else if (ball && (ball->mFlags & 0x8000)) {
        target[0] = !(p->mMotion.mPos.mX >= x) ? x - 2.0f : x + 2.0f;
        target[1] = location[1] + 2.0f;
    } else {
        target[0] = point[0];
        target[1] = point[1] - 4.5f;
        if (!(p->mMotion.mPos.mX >= point[0])) {
            if (!(p->mMotion.mPos.mY <= location[1] + 0.5f)) {
                target[0] -= 0.6666666865348816f;
                target[1] -= 0.5f;
            } else target[0] -= 2.0f;
        } else {
            if (!(p->mMotion.mPos.mY <= location[1] + 0.5f)) {
                target[0] += 0.6666666865348816f;
                target[1] -= 0.5f;
            } else target[0] += 2.0f;
        }
    }
    s->mUnknown10 = 0x400000;
    fn_80227690(target, target, &p->mMotion.mPos);
    s->mUnknownC = fn_801CFE40(target[1], target[0]) & 0xFFFFFF;
    float distance = fn_802270A4(target);
    if (!(distance <= 3.0f)) {
        if (!(distance >= 6.0f))
            s->mUnknown8 = distance * 0.10000000894069672f + 0.4f;
        else s->mUnknown8 = 0.7200000286102295f;
        if (fn_801CFFD0(s->mUnknownC, s->mUnknown10) <= 0x6E38E2)
            s->mUnknown10 = s->mUnknownC;
        else s->mUnknown8 = 0.4f;
    } else if (!(distance <= 0.5f)) s->mUnknown8 = 0.5f / distance;
    else s->mUnknown8 = 0.0f;
}

void fn_80133044(Object_80039F5C *p, Object_80039F5C *other, Mode_80133C50 *s, float *values)
{
    float point[2] = {values[0], values[1]};
    s->mUnknown4 = 99999.0f;
    --s->mUnknown19;
    if (!(s->mUnknown19 & 0x80)) return;
    int rating = p->mRatings[7] * 2;
    if (rating > 510) rating = 510;
    signed char scaled = (unsigned int)rating >> 1;
    s->mUnknown19 = (255 - scaled) >> 6;
    Object_80039F5C *ball = fn_80137B40();
    if (s->mUnknown1B & 1) {
        float nearest = 999.0f;
        for (unsigned char i = 0; i <= 2; ++i) {
            unsigned char active;
            unsigned char index = fn_80168E00(p->mIdBytes[2], i, &active);
            if (index != 255 && active) {
                Object_80039F5C *candidate = fn_80039F5C(p->mIdBytes[2], index);
                if (candidate->mMotion.mPos.mY < point[1] + 2.5f || candidate == ball) {
                    float distance = fn_8022781C(&p->mMotion.mPos, &candidate->mMotion.mPos);
                    if (!(distance >= nearest)) {
                        ball = candidate;
                        nearest = distance;
                    }
                }
            }
        }
    }
    Vector_80039F5C location;
    float reference[2];
    if (ball) {
        if (fn_801783AC(0) || !(ball->mFlags & 0x8000)) {
            location = ball->mMotion.mPos;
            reference[0] = location.mX;
            reference[1] = location.mY;
            if (fn_8011E188() <= 59) reference[1] = point[1] - 8.0f;
        } else {
            location.mX = !(ball->mMotion.mPos.mX >= 0.0f) ? point[0] - 3.0f : point[0] + 3.0f;
            location.mY = point[1];
            reference[0] = location.mX;
            reference[1] = location.mY;
        }
    } else {
        ball = fn_80137BEC();
        if (ball) location = ball->mMotion.mPos;
        else fn_80137D58(fn_801374BC(), &location);
        reference[0] = location.mX;
        reference[1] = location.mY;
    }
    if (other && p->mUnknown1032 == 3 &&
        (other->mMotion.mUnknown44 > lbl_803ECB08 * 0.5f || other->mMotion.mPos.mY - point[1] > 3.0f ||
         fabsf(s->mUnknown0 - p->mMotion.mPos.mX) > 1.5f || (short)p->mUnknown1134 > 60)) {
        if (!fn_8011E3F4(p)) {
            fn_8011E240(p);
            other = 0;
            fn_8011E1BC(p, 0, 0, 1);
        }
    }
    if (other) {
        float delta[2];
        fn_80227690(delta, &other->mMotion.mPos, &p->mMotion.mPos);
        int toward = fn_801CFE40(delta[1], delta[0]);
        float distance = fn_802270A4(delta);
        s->mUnknownC = fn_80120794(&p->mMotion, &other->mMotion,
            &other->mMotion.mUnknown40, p->mMotion.mUnknown28,
            other->mMotion.mUnknown28, other->mMotion.mUnknown32, distance);
        fn_80227690(delta, &other->mMotion.mPos, reference);
        int otherAngle = fn_801CFE40(delta[1], delta[0]);
        fn_80227690(delta, &p->mMotion.mPos, reference);
        int angle = fn_801CFE40(delta[1], delta[0]);
        if (!(s->mUnknown1B & 1) && fn_80132A4C(p, ball, other, point, &location, angle, otherAngle, distance)) {
            s->mUnknown10 = toward;
            if (other->mUnknown1032 == 4 && fn_801CFFD0(toward, p->mMotion.mFacing) <= 0x11C71C &&
                fn_801CFFD0(other->mMotion.mFacing, p->mMotion.mFacing) > 0x71C71B) goto finish;
            if (p->mMotion.mPos.mY > other->mMotion.mPos.mY ||
                fabsf(p->mMotion.mPos.mX - other->mMotion.mPos.mX) > 0.5f ||
                fn_801CFFD0(other->mMotion.mFacing, otherAngle) > 0x6E38E3) {
                int turn;
                if (fn_8011E188() <= 59 && fn_801CFFD0(otherAngle, toward) > 0xAAAAA) {
                    fn_80227690(delta, reference, &p->mMotion.mPos);
                    turn = fn_801CFE40(delta[1], delta[0]);
                } else turn = s->mUnknownC;
                s->mUnknownC = ((turn - toward) & 0xFFFFFF) <= 0x7FFFFF ? s->mUnknown10 + 0x400000 : s->mUnknown10 - 0x400000;
                if (!(distance >= 3.5f)) {
                    if (other->mMotion.mUnknown28 == 0.0f &&
                        fn_80124B1C(p, other, 0x200000, distance + 1.0f, 0.5f)) {
                        s->mUnknown8 = 0.0f;
                        goto finish;
                    }
                    if (!(other->mMotion.mPos.mY >= p->mMotion.mPos.mY) && ball && !(location.mY >= p->mMotion.mPos.mY)) {
                        s->mUnknown8 = 1.0f;
                        goto finish;
                    }
                    if (!(other->mMotion.mPos.mY >= point[1])) s->mUnknown8 = distance * 0.08f + 0.7200000286102295f;
                    else s->mUnknown8 = distance * 0.07428571581840515f + 0.14f;
                    goto finish;
                }
                if (!(other->mMotion.mUnknown28 < lbl_803ECB08 * 0.14f)) {
                    s->mUnknown8 = 0.4f;
                    goto finish;
                }
            }
            s->mUnknown8 = 0.0f;
            goto finish;
        }
        float interceptionDistance;
        Object_80039F5C *interceptor = fn_80124C28(p, &interceptionDistance, 0x2E38E3, s->mUnknownC, distance, 0.2f);
        if (!interceptor || interceptor == other) {
            fn_80227690(delta, &location, &p->mMotion.mPos);
            float ownDistance = fn_802270A4(delta);
            fn_80227690(delta, &other->mMotion.mPos, &location);
            s->mUnknown8 = 0.7200000286102295f;
            if (!(distance <= ownDistance) && !(distance >= fn_802270A4(delta)) &&
                fn_801CFFD0(otherAngle, angle) <= 0x5FFFFF) {
                int reverse = angle + 0x800000;
                int gap = fn_801CFFD0(reverse, toward);
                if (gap < fn_801CFFD0(s->mUnknownC, toward)) {
                    int base = toward - 0x800000;
                    if (((angle - base) & 0xFFFFFF) <= 0x7FFFFF && ((s->mUnknownC - toward) & 0xFFFFFF) <= 0x7FFFFF)
                        s->mUnknownC = toward + (fn_801CFFD0(reverse, toward) * 3) / 4;
                    else if (((angle - base) & 0xFFFFFF) > 0x800000 && ((s->mUnknownC - toward) & 0xFFFFFF) > 0x800000)
                        s->mUnknownC = toward - (fn_801CFFD0(reverse, toward) * 3) / 4;
                }
            }
        } else s->mUnknown8 = 0.4f;
        if (fn_801CFFD0(otherAngle, angle) > 0x4E38E3) s->mUnknownC = toward;
        s->mUnknown10 = s->mUnknownC;
        if (!(p->mMotion.mUnknown28 <= lbl_803ECB08 * 0.14f) &&
            fn_801CFFD0(p->mMotion.mUnknown32, p->mMotion.mFacing) > 0x400000 &&
            fn_801CFFD0(p->mMotion.mUnknown32, s->mUnknown10) > 0x400000) {
            s->mUnknown10 = toward;
            s->mUnknown8 = 0.0f;
            s->mUnknown19 = 2;
        }
    } else if (ball) {
        float location2[2] = {location.mX, location.mY};
        fn_80132C84(p, ball, s, location2, point);
    }
finish:
    fn_801339E4(p, ball, (Aim_801327F4 *)s);
}

void fn_80133920(Object_80039F5C *p, Object_80039F5C *other)
{
    if (other) {
        float delta[2];
        fn_80227690(delta, &other->mMotion.mPos, &p->mMotion.mPos);
        float distance = fn_802270A4(delta);
        if (!(distance >= 4.0f)) {
            distance -= 1.0f;
            if (!(distance >= 0.0f)) distance = 0.0f;
            float amount = 1.0f - distance * 0.25f;
            int angle = fn_801CFE40(delta[1], delta[0]);
            fn_800C89F0(p, angle & 0xFFFFFF, 2, 0, amount);
        }
    }
}

void fn_801339E4(Object_80039F5C *p, Object_80039F5C *, Aim_801327F4 *aim)
{
    Object_80039F5C *other = fn_8009BCE8(&p->mUnknown1036);
    if (other) {
        Object_80039F5C *target;
        if (!fn_80124714(p, other, &target)) {
            float delta[2];
            fn_80227690(delta, &target->mMotion.mPos, &p->mMotion.mPos);
            float distance = fn_802270A4(delta);
            if (!(distance >= 2.25f)) {
                Vector_80039F5C point;
                if (target->mUnknown1032 != 4) {
                    point = target->mMotion.mPos;
                    point.mX += target->mMotion.mUnknown40 * 5.0f;
                    point.mY += target->mMotion.mUnknown44 * 5.0f;
                } else {
                    Object_80039F5C *linked = fn_8009BCE8(&target->mUnknown1036);
                    point.mX = (target->mMotion.mPos.mX + linked->mMotion.mPos.mX) * 0.5f;
                    point.mY = (target->mMotion.mPos.mY + linked->mMotion.mPos.mY) * 0.5f;
                }
                fn_80227690(delta, &point, &p->mMotion.mPos);
                int angle = fn_801CFE40(delta[1], delta[0]);
                if (fn_801CFFD0(angle, aim->mUnknownC) <= 0x271C70) {
                    float amount = distance * 0.4444444477558136f;
                    float turn = (1.0f - amount) * 3495253.0f;
                    if (((angle - aim->mUnknownC) & 0xFFFFFF) <= 0x800000)
                        turn = -turn;
                    int next = (aim->mUnknownC + (int)turn) & 0xFFFFFF;
                    aim->mUnknown10 = next;
                    aim->mUnknownC = next;
                }
            }
        }
    }
}

void fn_80133BB4(Object_80039F5C *p, Object_80039F5C *other)
{
    if (other && fn_801783AC(13) && !fn_801783AC(0) && !fn_80137B40() && fn_8011F2F8()) {
        Point_8017886C point = fn_80177FE0();
        if (!(other->mMotion.mPos.mY - point.mY >= 2.5f))
            p->mUnknown1137 = 1;
    }
}

int fn_80133C50(Object_80039F5C *p)
{
    Mode_80133C50 *s = (Mode_80133C50 *)&p->mUnknown336;
    unsigned int count = p->mpState->mUnknown1;
    s->mUnknown14 = (count >> 5) * 60 + (int)((float)(count & 31) * 0.032258063554763794f * 60.0f);
    s->mUnknown18 = s->mUnknown14 != 0;
    Point_8017886C point = fn_80177FE0();
    float values[2] = {point.mX, point.mY};
    s->mUnknown0 = p->mMotion.mPos.mX;
    s->mUnknown4 = 99999.0f;
    s->mUnknown8 = p->mUnknown528.mUnknown0;
    s->mUnknownC = p->mMotion.mFacing;
    s->mUnknown10 = p->mMotion.mFacing;
    s->mUnknown1A = 0;
    s->mUnknown19 = 0;
    s->mUnknown1B = p->mpState->mUnknown2;
    if (fn_8011E188() <= 14) {
        s->mUnknown1A = 1;
        if (!(values[1] - p->mMotion.mPos.mY >= 2.0f)) {
            float limit = p->mMotion.mPos.mY - lbl_803EB158;
            Point_8017886C current = fn_80177FE0();
            limit -= fabsf(p->mMotion.mPos.mX - current.mX) * lbl_803EB15C;
            s->mUnknown4 = limit;
            s->mUnknown10 = p->mMotion.mFacing;
            s->mUnknownC = (p->mMotion.mFacing - 0x800000) & 0xFFFFFF;
        } else {
            s->mUnknown4 = fn_8011F32C() ? p->mMotion.mPos.mY : values[1] - 4.0f;
            s->mUnknown10 = p->mMotion.mFacing;
            s->mUnknownC = p->mMotion.mFacing;
        }
        s->mUnknown8 = 0.4f;
        if (!(p->mFlags & 0x4000)) {
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown4 = s->mUnknownC;
            p->mUnknown512.mUnknown8 = s->mUnknown10;
            p->mUnknown512.mUnknown0 = s->mUnknown8;
        }
    } else if (!(p->mFlags & 0x4000)) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
    }
    if (fn_801787A0()) {
        fn_8011E3EC(p, 0);
        fn_8011E240(p);
        return 1;
    }
    if (p->mUnknown1032 != 3) fn_8011E1BC(p, 0, 0, 1);
    fn_8011E3EC(p, 1);
    return 0;
}

int fn_80133EE8(Object_80039F5C *p)
{
    Object_80039F5C *ball = fn_80137B40();
    Mode_80133C50 *s = (Mode_80133C50 *)&p->mUnknown336;
    int post = 0;
    if (p == ball) {
        fn_8011E3EC(p, 0);
        fn_8011E240(p);
        post = 1;
    } else {
        if (fn_8009FB60(p)) return 1;
        if (p->mIdBytes[2] == fn_80178320()) {
            fn_8011E3EC(p, 0);
            fn_8011E240(p);
            post = 2;
        } else if ((fn_8011F524() && !fn_8011F2C4()) || fn_801783AC(0) || fn_801787A0()) {
            if (p->mUnknown1032 != 4 && p->mUnknown1032 != 7) {
                fn_8011E3EC(p, 0);
                fn_8011E240(p);
            }
            post = 33;
        }
    }
    if (post) {
        Message_800F01CC message;
        fn_801C1F94(&message, 0, 4);
        message.mId = post;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    int result = 0;
    if (fn_801787A0()) {
        if ((p->mUnknown1032 != 4 && p->mUnknown1032 != 7) || fn_802372EC(0, 100) <= 9) {
            fn_8011E3EC(p, 0);
            fn_8011E240(p);
        }
    } else if (!p->mUnknown1032) {
        fn_8011E240(p);
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 1);
    }
    fn_8010A2DC(p, 0, -1);
    if (!(p->mFlags & 0x4000)) {
        Point_8017886C point = fn_80177FE0();
        float values[2] = {point.mX, point.mY};
        Object_80039F5C *other = fn_8009BCE8(&p->mUnknown1036);
        if (p->mUnknown1032 != 4 && p->mUnknown1032 != 7) {
            if (ball && (ball->mFlags & 0x8000)) s->mUnknown1A = 0;
            if (s->mUnknown1A && !(p->mMotion.mPos.mY <= s->mUnknown4))
                fn_801327F4(p, other, (Aim_801327F4 *)s, values);
            else if (!fn_80178C9C() || (fn_800BA6F8() && fn_800BAA24() == 1)) {
                s->mUnknown8 = 0.0f;
                s->mUnknown10 = p->mMotion.mFacing;
                s->mUnknownC = p->mMotion.mFacing;
            } else
                fn_80133044(p, other, s, values);
            fn_80133920(p, other);
            fn_80133BB4(p, other);
        } else
            s->mUnknown4 = 99999.0f;
        int apply = 0;
        if ((unsigned int)(p->mUnknown2914 - 1) > 1 || p->mUnknown1032 != 2 ||
            !(fabsf(other->mMotion.mPos.mY - p->mMotion.mPos.mY) >= 5.0f)) apply = 1;
        if (apply) {
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown4 = s->mUnknownC & 0xFFFFFF;
            p->mUnknown512.mUnknown8 = s->mUnknown10;
            p->mUnknown512.mUnknown0 = s->mUnknown8;
        }
    } else if (p->mpState[1].mId == 19) {
        fn_8011E3EC(p, 0);
        result = 1;
        fn_8011E240(p);
    }
    if (s->mUnknown18) {
        --s->mUnknown14;
        p->mpState->mUnknown1 = (int)((float)s->mUnknown14 * 0.01666666753590107f * 32.0f);
        if (s->mUnknown14 > 0 && !p->mpState->mUnknown1) p->mpState->mUnknown1 = 1;
        int end = s->mUnknown14 <= 0;
        if (!end && (p->mFlags & 0x4000)) {
            Point_8017886C point = fn_80177FE0();
            if (!(p->mMotion.mPos.mY <= point.mY)) end = 1;
        }
        if (end) {
            fn_8011E3EC(p, 0);
            result = 1;
            fn_8011E240(p);
        }
    }
    return result;
}

int fn_80134370(Object_80039F5C *p)
{
    fn_8011E3EC(p, 0);
    fn_8011E240(p);
    return 1;
}

int fn_801343AC(Object_80039F5C *p)
{
    if (fn_8011E8A4(p)) return fn_800B7E60(p);
    if (p->mUnknown1032 == 4 || p->mUnknown1032 == 7) {
        Input_800B6D34 input;
        fn_800B6D34(p, &input);
        fn_800B6E68(p, &input);
        Object_80039F5C *other = fn_8009BCE8(&p->mUnknown1036);
        float delta[2];
        fn_80227690(delta, &other->mMotion.mPos, &p->mMotion.mPos);
        if (fn_801CFFD0(p->mUnknown512.mUnknown4, fn_801CFE40(delta[1], delta[0])) > 0x600000) {
            fn_8011E3EC(p, 0);
            fn_8011E240(p);
            return 0;
        }
        if (input.mUnknown92 & 1) p->mUnknown1137 = 1;
    }
    return fn_800B7F34(p);
}

int fn_801344A0(void)
{
    int mode = fn_801486A0();
    int result = mode <= 4 && mode >= 3;
    if (fn_80156704()) result = 1;
    return result;
}

void fn_801344F8(Object_80039F5C *p, float *values)
{
    int team = fn_80178320();
    unsigned char count = fn_80178D18(fn_80178320());
    float distance;
    fn_801244F0(p, team, 0, count, &distance, 0);
    State_80134E24 *s = (State_80134E24 *)&p->mUnknown336;
    s->mUnknown3 = 0;
    if (values[0] > 2.0f || values[1] > 2.0f || values[2] > 2.0f || values[3] > 2.0f ||
        values[4] > 2.0f || values[5] > 2.0f || values[6] > 2.0f || !(values[7] <= 2.0f)) {
        s->mUnknown6 = 10;
        s->mUnknown3 = 1;
        Point_8017886C point = fn_80177FE0();
        if (!(p->mMotion.mPos.mY >= point.mY - 13.0f)) {
            values[5] += 3.0f;
            values[7] += 3.0f;
            values[6] += 4.0f;
        } else if (!(fabsf(p->mMotion.mPos.mY) <= fn_80178A44() - 4.0f)) {
            values[5] += 3.0f;
            values[6] += 4.0f;
            values[7] += 3.0f;
        }
    } else {
        s->mUnknown6 = 10;
        unsigned int n = fn_80178D18(fn_80178320());
        for (unsigned short i = 0; i < n; ++i) {
            Object_80039F5C *other = fn_80039F5C(fn_80178320(), i);
            float delta[2];
            fn_80227690(delta, &other->mMotion.mPos, &p->mMotion.mPos);
            if (!(fn_802270A4(delta) >= 3.0f)) {
                int angle = fn_801CFE40(delta[1], delta[0]);
                values[((angle + 0x100000) >> 21) & 7] += 4.0f;
                s->mUnknown3 = 1;
            }
        }
    }
    if (s->mUnknown4 <= 0) s->mUnknown3 = 1;
}

void fn_8013474C(Object_80039F5C *p)
{
    float a = fn_80124FE0(p, 3);
    float b = fn_80125004(p, 3, 1);
    if (a > 7.0f || (!(a <= 5.0f) && !(b <= 5.0f)))
        fn_8006F0B8(16);
}

int fn_801347D4(Object_80039F5C *p, State_80134E24 *s,
               Object_80039F5C **out, unsigned char *choice, unsigned char *indexes)
{
    if (lbl_803EB16B) {
        float threshold = (float)p->mRatings[6] * 0.003921568859368563f;
        if (!fn_800ABDA4(p->mIdBytes[2])) threshold *= 0.5f;
        if (!(fn_80237260(0) <= threshold)) {
            *out = 0;
            for (;;) {
                unsigned int n = fn_802372EC(0, 3);
                if (indexes[n] != 255 && s->mUnknown30[n]) {
                    *out = fn_80039F5C(p->mIdBytes[2], indexes[n]);
                    *choice = s->mUnknown23[n];
                    return 1;
                }
                if (*out) return 1;
            }
        }
    }
    return 0;
}

int fn_801348F0(Object_80039F5C *p)
{
    State_80134E24 *s = (State_80134E24 *)&p->mUnknown336;
    if (fn_801783AC(0)) return 1;
    unsigned int kind = p->mUnknown2914;
    if (fn_801344A0() || !(kind <= 1 || kind == 3)) return 0;
    float threshold = ((float)p->mRatings[4] * lbl_803EB16C + (float)p->mRatings[0] * lbl_803EB170) * 0.003921568859368563f;
    if (fn_80237260(0) > threshold) return 0;
    int mode = fn_80177F70();
    Point_8017886C point = fn_80177FE0();
    float remaining = 2.0f - threshold;
    float limit = (lbl_803EB174 + point.mY - p->mMotion.mPos.mY) * remaining;
    if (mode == 4 || mode == 6) {
        limit = (fn_80178298() - p->mMotion.mPos.mY) * remaining;
        if (mode == 6) {
            int time;
            if (!fn_801788D8(&time)) {
                time -= fn_801787DC(fn_80178308());
                if ((unsigned int)time <= 24 && !((time - 2) & 7)) return 0;
            }
        }
    }
    float distance;
    fn_80124E5C(p, fn_80178320(), &distance, (int)(lbl_803EB178 * 46603.37890625f), 0x400000, lbl_803EB17C, lbl_803EB180);
    if (!(distance <= limit)) {s->mUnknown18 = 1; return 1;}
    return 0;
}

float *fn_80134AD0(Object_80039F5C *p, int *count)
{
    State_80134E24 *s = (State_80134E24 *)&p->mUnknown336;
    float *values = (s->mUnknown1 & 0x80) ? (s->mUnknown1C == 29 ? data_802DB0F4[1] : data_802DB0F4[0]) : data_802DB0F4[2];
    if (!(p->mMotion.mPos.mY >= -(fn_80178A2C() + 6.5f))) {
        values = data_802DB0F4[3];
        *count = -20;
        if (!(p->mMotion.mPos.mY >= -(fn_80178A2C() + 8.0f))) *count = -10;
    }
    if (!(p->mMotion.mPos.mX <= fn_80178A08() - 5.0f) && !(p->mMotion.mUnknown40 <= 0.0f))
        values = data_802DB0F4[5];
    else if (!(p->mMotion.mPos.mX >= 5.0f - fn_80178A08()) && !(p->mMotion.mUnknown40 >= 0.0f))
        values = data_802DB0F4[6];
    return values;
}

void fn_80134C20(Object_80039F5C *p, State_80134E24 *s)
{
    if (!p || !s) return;
    unsigned char indexes[3];
    for (unsigned char i = 0; i <= 2; ++i) indexes[i] = fn_80168E00(p->mIdBytes[2], i, 0);
    for (unsigned char i = 0; i <= 2; ++i) {
        if (!s->mUnknown30[i] || indexes[i] == 255) continue;
        Object_80039F5C *other = fn_80039F5C(p->mIdBytes[2], indexes[i]);
        int disabled = 0;
        switch (other->mpState->mId) {
        case 3: case 51:
            if (fn_800F06F4(0, other->mpState, 31, 0xFFFF) != 0xFFFF) disabled = 1;
            break;
        case 10: case 11: case 16: case 31: case 32: disabled = 1; break;
        }
        if (other->mFlags & 0x800) disabled = 1;
        if (!(p->mMotion.mPos.mY <= other->mMotion.mPos.mY) &&
            !(fabsf(p->mMotion.mPos.mX - other->mMotion.mPos.mX) >= 3.0f) && fn_800B65A0(p->mIdBytes[2]) == 255)
            disabled = 1;
        if (s->mUnknown2D[i] && disabled) {
            s->mUnknown2D[i] = 0;
            fn_80168E54(p->mIdBytes[2], indexes[i], 0);
        } else if (s->mUnknown30[i] && !s->mUnknown2D[i] &&
                   (other->mpState->mId == 19 || other->mpState->mId == 21)) {
            s->mUnknown2D[i] = s->mUnknown30[i];
            fn_80168E54(p->mIdBytes[2], indexes[i], s->mUnknown30[i]);
        }
    }
}
}
