#include <math.h>
#include "game/Record_8011F4F8.h"
#include "game/fn_801248D4.h"
#include "game/Directions_8012430C.h"
#include "game/Object_80039F5C.h"
#include "game/Class_80297CE8.h"
#include "game/Object_8017886C.h"
#include "game/State_800FDA58.h"
#include "game/Command_800CEE74.h"
#include "game/Message_800F01CC.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Lookup_8012078C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800F06F4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"

extern "C" {
int fn_801CFE40(float,float);
int fn_801CFFD0(int,int);
float fn_801CFB94(int);
float fn_80260B1C(float);
void fn_80227538(Point_8017886C *,int,float);
void fn_80227690(void *,void *,void *);
void fn_802271A4(Point_8017886C *,Point_8017886C *);
void fn_80227248(Point_8017886C *,Point_8017886C *,float);
float fn_802276E8(Point_8017886C *,Point_8017886C *);
void fn_8022732C(void *,void *,float);
void fn_80227904(Point_8017886C *,void *,void *,float);
float fn_80237260(int);
Point_8017886C fn_80177FFC(int);
Point_8017886C fn_80177FE0(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_801783AC(int);
unsigned int fn_80178D18(int);
unsigned int fn_80178D70(int);
int fn_80177F70(void);
float fn_80178A08(void);
float fn_80178A2C(void);
float fn_80178A44(void);
float fn_80178A5C(void);
int fn_801486A0(void);
void fn_800FE41C(Object_80039F5C *,Object_80039F5C *,Point_8017886C *);
void fn_800FE430(Object_80039F5C *,Object_80039F5C *,Point_8017886C *);
void fn_800FF598(State_800FDA58 *,Object_80039F5C *,Point_8017886C *,int,float);

float fn_8016D9F4(Object_80039F5C *,float,float);
int fn_8012CAAC(Object_80039F5C *);
int fn_8012CAA4(Object_80039F5C *);
void fn_8012CD4C(Object_80039F5C *,Vector_80039F5C *);
float fn_8012CD60(Object_80039F5C *,float);
void fn_80103F80(Object_80137ABC *,Vector_80039F5C,Vector_80039F5C,int,Vector_80039F5C *,Object_80039F5C *,float,float);
void fn_80104328(Object_80039F5C *,unsigned int,int *,Vector_80039F5C *,int *);
float fn_80103DD8(Object_80039F5C *,Object_80039F5C *,short *,float);
int fn_8011E9B4(Object_80039F5C *);
int fn_800A7F1C(unsigned char);
unsigned int fn_80100B0C(void);
int fn_80168E00(int,int,unsigned char *);
void fn_8009BD2C(Object_80039F5C *,int *);
void fn_8012430C(Directions_8012430C *,int,Object_80039F5C *);
unsigned char fn_801243E0(Directions_8012430C *,int);
float fn_801242E0(Directions_8012430C *,unsigned int);
unsigned short fn_801BE648(void *p);
int fn_801BE068(void *,void *,void *,unsigned short,void *,float);
void fn_801BE67C(void *,void *,void *,void *);
int fn_8010A2DC(Object_80039F5C *, int, short);
void fn_8010CEB8(Object_80039F5C *,int);
void fn_800C89F0(Object_80039F5C *,int,int,int,float);
void fn_8009D284(Object_80039F5C *,Object_80039F5C *);
extern float lbl_803EA2C4;
extern float lbl_803ECB08,lbl_803EAE84;
extern float lbl_803EAEA4,lbl_803EAEA8,lbl_803EAEAC,lbl_803EAEB0;
extern float lbl_803EAEB4,lbl_803EAEB8,lbl_803EAEBC;
extern unsigned short lbl_803EAE76;
extern float lbl_803EAE78,lbl_803EAE7C;
extern unsigned int lbl_803EAE80;
extern unsigned char lbl_803EAEA0;

void fn_800FE444(Object_80039F5C *p, int angle, Point_8017886C *point, float length)
{
    Point_8017886C delta;
    int to;
    int difference;

    fn_80227690(&delta, point, &p->mMotion.mPos);
    fn_802270A4(&delta);
    to = fn_801CFE40(delta.mY, delta.mX);
    difference = fn_801CFFD0(to, angle);
    if (difference > 0x400000) {
        int limited = (angle - 0x400000) & 0xFFFFFF;

        if (fn_801CFFD0(to, limited) <= 0x3FFFFF) {
            limited = (angle + 0x400000) & 0xFFFFFF;
        }
        fn_80227538(&delta, limited, length);
        fn_80227638(point, point, &delta);
    } else {
        fn_80227538(&delta, (angle - 0x800000) & 0xFFFFFF,
                    ((float)difference + (float)difference) * length * 0.0000002384185791015625f);
        fn_80227638(point, point, &delta);
    }
}

void fn_800FE564(Object_80039F5C *p, Object_80039F5C *other, Object_80039F5C *target, float limit)
{
    Point_8017886C a;
    Point_8017886C b;
    Point_8017886C av;
    Point_8017886C bv;
    State_800FDA58 *state;
    float base;
    float radius;
    float dx;
    float dy;
    float px;
    float py;
    float aa;
    float bb;
    float disc;
    float first;
    float second;
    float t;
    float distance;

    fn_800FE41C(p, other, &a);
    fn_800FE41C(other, p, &b);
    state = (State_800FDA58 *)&p->mUnknown336;
    if (fn_8022781C(&a, &b) >= limit) {
        return;
    }
    fn_800FE430(p, target, &av);
    bv.mX = other->mMotion.mUnknown40;
    bv.mY = other->mMotion.mUnknown44;
    if (p->mpState->mId == 7) {
        base = 0.5f;
    } else {
        base = 2.0f;
    }
    if (base + fn_802270A4(&bv) / lbl_803ECB08 <= 5.5f) {
        radius = base + fn_802270A4(&bv) / lbl_803ECB08;
    } else {
        radius = 5.5f;
    }
    if (p->mMotion.mUnknown28 != 0.0f && other->mMotion.mUnknown28 != 0.0f) {
        radius -= lbl_803EAE78 * fn_801CFB94(fn_801CFFD0(p->mMotion.mUnknown32, other->mMotion.mUnknown32));
        if (radius < lbl_803EAE7C) {
            radius = lbl_803EAE7C;
        }
    }
    dx = bv.mX - av.mX;
    px = b.mX - a.mX;
    py = b.mY - a.mY;
    dy = bv.mY - av.mY;
    if (dx < 0.0000001f && dx > -0.0000001f) {
        dx = 0.0f;
    }
    if (dy < 0.0000001f && dy > -0.0000001f) {
        dy = 0.0f;
    }
    if (dx == 0.0f && dy == 0.0f) {
        return;
    }
    aa = dx * dx + dy * dy;
    bb = px * dx + py * dy;
    disc = bb * bb - 4.0f * aa * (px * px + py * py - radius * radius);
    if (disc < 0.0000001f) {
        return;
    }
    disc = fn_80260B1C(disc);
    if (aa < 0.0000001f) {
        aa = 0.0000001f;
    }
    first = (-bb - disc) / (aa + aa);
    second = (-bb + disc) / (aa + aa);
    if (first < 0.0f) {
        if (second >= 0.0f) {
            t = 0.0f;
        } else {
            t = first;
        }
    } else {
        t = first;
    }
    distance = fn_8022781C(&p->mMotion.mPos, &other->mMotion.mPos);
    if (t < 0.0f) {
        return;
    }
    if (t >= state->mUnknown40 && (t != state->mUnknown40 || distance >= state->mUnknown44)) {
        return;
    }
    fn_80227248(&av, &av, t);
    fn_80227638(&a, &a, &av);
    fn_80227248(&bv, &bv, t);
    fn_80227638(&b, &b, &bv);
    if (fn_8022781C(&a, &b) >= radius + 0.0000001f) {
        return;
    }
    fn_80227690(&av, &a, &b);
    state->mUnknown40 = t;
    state->mUnknown40 = state->mUnknown40 > 180.0f ? 180.0f : state->mUnknown40;
    state->mUnknown44 = distance;
    fn_802271A4(&state->mUnknown32, &av);
}

void fn_800FE910(Object_80039F5C *p, Point_8017886C *point, float *value, float *distance, float *time)
{
    *distance = fn_8022781C(point, &p->mMotion.mPos);
    *distance = *distance > 15.0f ? 15.0f : *distance;
    if (*value > 0.0000001f) {
        float t = *distance / (lbl_803ECB08 * *value);

        *time = t > 180.0f ? 180.0f : t;
    }
}

void fn_800FE9B4(Object_80039F5C *p, Point_8017886C *point, float *speed)
{
    State_800FDA58 *s = (State_800FDA58 *)&p->mUnknown336;
    float distance;
    float time;
    Point_8017886C goal;
    Point_8017886C *direction;
    int team;

    if (--s->mUnknown0 > 0) {
        return;
    }
    direction = &s->mUnknown32;
    fn_800FE910(p, point, speed, &distance, &time);
    s->mUnknown0 = lbl_803EAE76;
    s->mUnknown40 = 180.0f;
    s->mUnknown44 = 1000.0f;
    direction->mX = direction->mY = 0.0f;
    if (*speed == 0.0f) {
        return;
    }
    if (p->mpState->mId == 7) {
        goal = fn_80177FFC(p->mIdBytes[2]);
        if (fabsf(p->mMotion.mPos.mY - goal.mY) < 1.5f) {
            s->mUnknown40 = 0.0f;
            if (p->mIdBytes[2] == fn_80178308()) {
                fn_80227538(direction, 0xC00000, 1.0f);
            } else {
                fn_80227538(direction, 0x400000, 1.0f);
            }
        }
    }
    if (s->mUnknown40 == 180.0f) {
        for (team = 0; team <= 1; team++) {
            int count = fn_80178D18((unsigned char)team);
            int i;

            for (i = 0; i < count; i++) {
                Object_80039F5C *other = fn_80039F5C((unsigned char)team, (unsigned short)i);

                if (other != p) {
                    fn_800FE564(p, other, (Object_80039F5C *)point, distance);
                }
            }
        }
    }
}

void fn_800FEB60(Object_80039F5C *p, Point_8017886C *point, float *speed)
{
    float distance;
    float time;
    State_800FDA58 *s;
    Point_8017886C direction;
    Point_8017886C normal;
    Point_8017886C projected;
    Point_8017886C side;
    Point_8017886C delta;
    float parallel;
    float perpendicular;
    int target;
    int heading;
    int turn;
    float scale;

    fn_800FE910(p, point, speed, &distance, &time);
    s = (State_800FDA58 *)&p->mUnknown336;
    if (s->mUnknown40 >= time) {
        return;
    }
    fn_80227690(&direction, point, &p->mMotion.mPos);
    fn_802271A4(&direction, &direction);
    if (s->mUnknown40 < 4.5454545f) {
        parallel = 0.55f;
    } else {
        parallel = 2.5f / s->mUnknown40;
    }
    if (s->mUnknown40 < 6.1538463f) {
        perpendicular = 0.65f;
    } else {
        perpendicular = 4.0f / s->mUnknown40;
    }
    fn_802271A4(&normal, &s->mUnknown32);
    fn_80227248(&projected, &direction, fn_802276E8(&normal, &direction));
    fn_80227690(&side, &normal, &projected);
    fn_80227248(&projected, &projected, parallel);
    fn_802271A4(&side, &side);
    fn_80227248(&side, &side, perpendicular);
    fn_80227638(&direction, &direction, &projected);
    fn_80227638(&direction, &direction, &side);
    fn_80227690(&delta, point, &p->mMotion.mPos);
    target = fn_801CFE40(delta.mY, delta.mX);
    heading = fn_801CFE40(direction.mY, direction.mX);
    turn = fn_801CFFD0(target, heading);
    fn_801CFFD0(p->mMotion.mUnknown32, heading);
    scale = fn_802270A4(&direction) < 1.0f ? fn_802270A4(&direction) : 1.0f;
    if (s->mUnknown40 != 0.0f) {
        scale = fn_802270A4(&direction) < 1.0f ? fn_802270A4(&direction) : 1.0f;
    } else {
        if (turn != 0) {
            scale = fn_802270A4(&direction) < 1.0f ? fn_802270A4(&direction) : 1.0f;
        } else {
            scale = fn_802270A4(&direction) < 1.0f ? fn_802270A4(&direction) : 1.0f;
        }
    }
    *speed *= scale;
    fn_80227248(&direction, &direction, distance);
    fn_80227638(point, &p->mMotion.mPos, &direction);
}

float fn_800FEDBC(State_800FDA58 *s, Object_80039F5C *p, float distance)
{
    Point_8017886C goal;
    int mode;
    unsigned int minimum;
    float desired;
    float result;

    goal = fn_80177FFC(p->mIdBytes[2]);
    mode = fn_800AD9B4();
    minimum = p->mRatings[4];
    if (minimum < lbl_803EAE80) {
        minimum = lbl_803EAE80;
    }
    result = s->mUnknown24;
    if ((unsigned int)(s->mUnknown2 - 1) < 2) {
        return result;
    }
    desired = s->mUnknown20Float;
    if (mode != 1 && mode != 9 && distance > 20.0f) {
        desired = 0.72f;
    }
    if (lbl_803EABA4->fn_800C0414() == 3 && p->mIdBytes[2] == fn_80178308()) {
        desired = 1.0f;
    }
    if (distance > 4.0f && mode == 2 && fn_801783AC(21) != 0) {
        desired = 0.72f;
    }
    if (mode == 2 && fabsf(s->mUnknown8 - goal.mX) > 8.0f) {
        desired = 1.0f;
    }
    if (mode == 1) {
        desired = 0.5f;
    }
    result = desired - s->mUnknown24;
    result = result < -0.01f ? -0.01f : (result > 0.05f ? 0.05f : result);
    s->mUnknown24 += result;
    result = s->mUnknown24;
    if (distance < 3.0f) {
        result = result * (distance * 0.33333334f);
        if (result < minimum * 0.00054901966f) {
            result = minimum * 0.00054901966f;
        }
    }
    return result;
}

int fn_800FEFD4(Object_80039F5C *p)
{
    Point_8017886C point;
    point.mX=(float)(signed char)p->mpState->mUnknown1*0.25f;
    point.mY=(float)(signed char)p->mpState->mUnknown2*0.5f;
    fn_800FF598((State_800FDA58 *)&p->mUnknown336,p,&point,p->mpState->mUnknown3[0]<<16,-1.0f);
    return 0;
}

int fn_800FF094(Object_80039F5C *p)
{
    int mode = fn_800AD9B4();
    int special = mode == 4;
    State_800FDA58 *s = (State_800FDA58 *)&p->mUnknown336;
    Point_8017886C point;
    Point_8017886C delta;
    float distance;
    float speed;
    float limit;
    int angle;

    point.mX = s->mUnknown8;
    point.mY = s->mUnknown12;
    fn_800FE444(p, s->mUnknown16, &point, s->mUnknown28);
    distance = fn_8022781C(&s->mUnknown8, &p->mMotion.mPos);
    speed = fn_800FEDBC(s, p, distance);
    switch (s->mUnknown2) {
    case 0:
        if (--s->mUnknown0 <= 0) {
            s->mUnknown0 = 0;
            fn_800FE9B4(p, &point, &s->mUnknown24);
            fn_800FEB60(p, &point, &s->mUnknown24);
            fn_80227690(&delta, &point, &p->mMotion.mPos);
            fn_801CFE40(delta.mY, delta.mX);
            s->mUnknown2 = 3;
        }
        break;
    case 1:
    case 2:
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mMotion.mUnknown28 = 0.0f;
            s->mUnknown2 = s->mUnknown3Byte;
            s->mUnknown3Byte = 0;
        } else if (fn_801BE648(p->mpUnknown792) == 100) {
            if (s->mUnknown2 == 2) {
                p->mUnknown512.mUnknown14 = 7;
                p->mUnknown512.mUnknown0 = 1.5f;
                p->mUnknown512.mUnknown4 = s->mUnknown4;
                p->mUnknown512.mUnknown8 = s->mUnknown4;
            } else {
                p->mUnknown512.mUnknown14 = 6;
                p->mUnknown512.mUnknown0 = 1.0f;
                p->mUnknown512.mUnknown4 = s->mUnknown4;
                p->mUnknown512.mUnknown8 = s->mUnknown4;
            }
        } else {
            s->mUnknown2 = s->mUnknown3Byte;
            s->mUnknown3Byte = 0;
        }
        break;
    case 3:
        if (distance > 3.0f) {
            fn_800FE9B4(p, &point, &s->mUnknown24);
            fn_800FEB60(p, &point, &s->mUnknown24);
            speed = s->mUnknown24;
        } else if (special && p->mUnknown560.mFlags.mBytes[0] != 0) {
            s->mUnknown8 = p->mMotion.mPos.mX;
            s->mUnknown12 = p->mMotion.mPos.mY;
        }
        limit = special == 1 ? lbl_803EAE84 : 0.05f;
        if (distance < limit) {
            p->mMotion.mUnknown28 = 0.0f;
            s->mUnknown2 = 4;
        } else {
            fn_80227690(&delta, &point, &p->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX);
            if (speed == 1.0f) {
                p->mUnknown512.mUnknown15 = 1;
            }
            p->mUnknown512.mUnknown14 = fn_80137C48(p) ? 1 : 9;
            p->mUnknown512.mUnknown0 = speed;
            p->mUnknown512.mUnknown4 = angle;
            p->mUnknown512.mUnknown8 = angle;
        }
        break;
    case 4:
        if (special != 1 && fn_801CFFD0(s->mUnknown16, p->mMotion.mFacing) > 0xB60B) {
            if (fn_801CFFD0(p->mMotion.mFacing, s->mUnknown16) <= 0x155554) {
                if (p->mpState[1].mId != 87) {
                    p->mUnknown512.mUnknown14 = 3;
                    p->mUnknown512.mUnknown0 = 0.0f;
                    p->mUnknown512.mUnknown4 = s->mUnknown16;
                    p->mUnknown512.mUnknown8 = s->mUnknown16;
                    break;
                }
            } else {
                float limit = p->mIdBytes[2] == fn_80178308() ? 8.0f : 2.0f;

                s->mUnknown4 = s->mUnknown16;
                p->mFlags &= ~4;
                if (mode == 4 || !fn_80177F70()
                    || fabsf(fn_80177FFC(p->mIdBytes[2]).mY - p->mMotion.mPos.mY) > limit) {
                    s->mUnknown2 = 1;
                    p->mUnknown512.mUnknown14 = 6;
                    p->mUnknown512.mUnknown0 = 1.0f;
                } else {
                    s->mUnknown2 = 2;
                    p->mUnknown512.mUnknown14 = 7;
                    p->mUnknown512.mUnknown0 = 1.5f;
                }
                p->mUnknown512.mUnknown4 = s->mUnknown16;
                p->mUnknown512.mUnknown8 = s->mUnknown16;
                s->mUnknown3Byte = 6;
                break;
            }
        }
        s->mUnknown2 = 5;
        break;
    case 5:
        if (distance < 0.05f || special == 1) {
            p->mMotion.mUnknown28 = 0.0f;
            s->mUnknown2 = 6;
        } else {
            fn_80227690(&delta, &point, &p->mMotion.mPos);
            p->mUnknown512.mUnknown4 = fn_801CFE40(delta.mY, delta.mX);
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown8 = s->mUnknown16;
            p->mUnknown512.mUnknown0 = speed;
        }
        break;
    case 6:
        break;
    }
    return s->mUnknown2 == 6;
}

void fn_800FF598(State_800FDA58 *s, Object_80039F5C *p, Point_8017886C *point, int angle, float value)
{
    s->mUnknown0 = 0;
    s->mUnknown8 = point->mX;
    s->mUnknown12 = point->mY;
    s->mUnknown20Float = 0.56f;
    s->mUnknown16 = angle;
    s->mUnknown24 = p->mMotion.mUnknown28 / lbl_803ECB08;
    if (value == -1.0f) {
        Point_8017886C delta;

        if (fn_8022781C(&p->mMotion.mPos, point) < 3.0f) {
            s->mUnknown28 = 0.0f;
        } else {
            fn_80227690(&delta, point, &p->mMotion.mPos);
            if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), angle) >= 0x3C71C8) {
                s->mUnknown28 = 0.0f;
            } else {
                float random = fn_80237260(0);

                s->mUnknown28 = random + random + 2.0f;
            }
        }
    } else {
        s->mUnknown28 = value;
    }
    s->mUnknown4 = 0;
    s->mUnknown2 = 0;
    s->mUnknown32.mY = 0.0f;
    s->mUnknown32.mX = 0.0f;
    s->mUnknown40 = 0.0f;
    s->mUnknown3Byte = 0;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown0 = s->mUnknown24;
}


void fn_800FF6D8(Object_80039F5C *p)
{
    State_800FDA58 *s=(State_800FDA58 *)&p->mUnknown336;
    Object_800B26B0 *motion = &p->mMotion;

    motion->mPos.mX = s->mUnknown8;
    motion->mPos.mY = s->mUnknown12;
    motion->mFacing = s->mUnknown16;
    p->mpUnknown796->mUnknown8 = motion->mFacing;
    motion->mUnknown28 = 0.0f;
    s->mUnknown0 = 0;
    s->mUnknown4 = 0;
    s->mUnknown2 = 5;
    s->mUnknown3Byte = 0;
    s->mUnknown20Float = 0.0f;
    s->mUnknown24 = 0.0f;
    s->mUnknown28 = 0.0f;
    s->mUnknown32.mX = 0.0f;
    s->mUnknown32.mY = 0.0f;
    s->mUnknown40 = 0.0f;
    p->mUnknown512.mUnknown14=0;
    fn_801BE068(p->mpUnknown792,p->mpUnknown796,p->mpUnknown800,74,p,1.0f);
    fn_801BE67C(p->mpUnknown792,p->mpUnknown796,p->mpUnknown800,p);
    p->mUnknown9[0]=1;
}

int fn_800FF7F4(Object_80039F5C *p)
{
    fn_8010A2DC(p, 0, -1);
    if (p->mUnknown560.mUnknown53 != 0) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.0f;
        return 1;
    }
    return 0;
}

void fn_800FF868(Object_80039F5C *p,State_800FFDFC *,Object_80039F5C *other)
{
    Point_8017886C delta;fn_80227690(&delta,&other->mMotion.mPos,&p->mMotion.mPos);
    fn_800C89F0(p,fn_801CFE40(delta.mY,delta.mX)&0xFFFFFF,1,0,0.5f);fn_8009D284(p,other);
}

void fn_800FF8FC(Object_80039F5C *p, float *out)
{
    State_80039F5C *state = p->mpState;

    out[0] = (float)(signed char)state->mUnknown1 * 0.0625f;
    out[1] = (float)(signed char)state->mUnknown2 * 0.0625f;
    if (fn_801486A0() == 2) {
        Vector_80039F5C ball;

        fn_80137D58(fn_801374BC(), &ball);
        if (p->mMotion.mPos.mX > ball.mX + 2.0f) {
            out[0] = fabsf(out[0]);
        } else if (p->mMotion.mPos.mX < ball.mX - 2.0f) {
            out[0] = -fabsf(out[0]);
        } else if (fn_802372EC(0, 100) < 50) {
            out[0] = fabsf(out[0]);
        } else {
            out[0] = -fabsf(out[0]);
        }
    }
}

int fn_800FFA10(Object_80039F5C *p, Object_80039F5C *other)
{
    State_80039F5C *state = other->mpState;
    int result = 1;

    switch (state->mId) {
    case 18:
        result = 0;
        break;
    case 1:
        if (fn_8022781C(&p->mMotion.mPos, &other->mMotion.mPos) > 9.0f
            || p->mMotion.mPos.mY > other->mMotion.mPos.mY) {
            if (fn_801486A0() != 2 || fn_801783AC(20) != 0) {
                Message_800F01CC message;

                result = 0;
                fn_801C1F94(&message, 0, 4);
                message.mId = 33;
                fn_800F053C(0, p->mpState, &message, p);
            }
        }
        break;
    case 25:
        if (state->mUnknown2 == 9) {
            Message_800F01CC message;

            fn_801C1F94(&message, 0, 4);
            if (state->mUnknown1 == p->mIdBytes[1]) {
                fn_8010CEB8(p, 9);
            } else {
                message.mId = 33;
                fn_800F053C(0, p->mpState, &message, p);
            }
            result = 0;
        }
        break;
    }
    return result;
}

static inline float MapRange(float v, float inLo, float inHi, float outLo, float outHi)
{
    return (v - inLo) * (outHi - outLo) / (inHi - inLo) + outLo;
}

void fn_800FFB4C(Object_80039F5C *p, Object_80039F5C *other, float *value, Point_8017886C *out)
{
    float factor;

    if (*value > 0.0f) {
        factor = MapRange(fn_80178A08() - p->mMotion.mPos.mX, 1.0f, 4.5f, -1.0f, 1.0f);
        factor = factor < -1.0f ? -1.0f : (factor > 1.0f ? 1.0f : factor);
    } else {
        factor = MapRange(fn_80178A08() + p->mMotion.mPos.mX, 1.0f, 4.5f, -1.0f, 1.0f);
        factor = factor < -1.0f ? -1.0f : (factor > 1.0f ? 1.0f : factor);
    }
    Point_8017886C delta;

    delta.mX = value[0];
    delta.mY = value[1];
    delta.mX *= factor;
    if (fn_801CFFD0(other->mMotion.mUnknown32, 0x400000) > 0x200000) {
        if (delta.mY < 0.0f) {
            delta.mY *= 3.0f;
            delta.mY = delta.mY < -3.0f ? -3.0f : delta.mY;
        }
    } else {
        float d = 3.0f - fabsf(p->mMotion.mPos.mX - other->mMotion.mPos.mX);

        if (d < 0.0f) {
            d = 0.0f;
        }
        {
            float ratio = d / 3.0f;

            delta.mY *= ratio * 4.0f + 1.0f;
        }
    }
    fn_80227638(out, &other->mMotion.mPos, &delta);
}

void fn_800FFD2C(Object_80039F5C *p, Point_8017886C *point)
{
    Point_8017886C delta;
    int angle;
    float speed;

    fn_80137B40();
    fn_80227690(&delta, point, &p->mMotion.mPos);
    angle = fn_801CFE40(delta.mY, delta.mX);
    speed = (fn_802270A4(&delta) - 0.3f) * 0.5f;
    speed = speed < 0.0f ? 0.0f : (speed > 1.0f ? 1.0f : speed);
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = angle;
    p->mUnknown512.mUnknown0 = speed;
    if (speed > 0.72f) {
        p->mUnknown512.mUnknown15 = 1;
    }
}



int fn_80100024(Object_80039F5C *p, int angle, int mode)
{
    Vector_80039F5C point;
    unsigned char filter[3] = {2, 10, 11};
    int result = 1;

    if (!(p->mFlags & 0x4000)) {
        point.mZ = 0.0f;
        if (mode == 2) {
            fn_80227538((Point_8017886C *)&point, angle, lbl_803EAEA4);
            fn_80227638(&point, &point, &p->mMotion.mPos);
            if (!fn_801248D4(p, &p->mMotion.mPos, &point, 0, 0.0f, 1.0f, (Filter_801248D4 *)filter, 0)) {
                result = 0;
            }
        }
    }
    return result;
}

void fn_8010016C(Object_80039F5C *p, Point_8017886C *point, Object_80039F5C *other, float speed)
{
    float chance = (float)other->mRatings[6] * 0.00392156886f;
    Point_8017886C middle;
    Point_8017886C delta;
    float time;
    float best;
    int replace;
    int team;
    unsigned int count;
    unsigned int i;

    if (lbl_803EAEA0 && fn_80237260(0) >= chance) {
        return;
    }
    fn_80227904(&middle, &p->mMotion.mPos, point, 0.5f);
    fn_80227690(&delta, point, &other->mMotion.mPos);
    time = fn_802270A4(&delta) / speed;
    best = 3.4028235e38f;
    replace = 0;
    team = fn_80178320();
    count = fn_80178D70(team);
    for (i = 0; i < count; i++) {
        Object_80039F5C *candidate = fn_80039F5C(team, (unsigned short)i);
        Point_8017886C pos;
        Point_8017886C offset;
        Point_8017886C future;
        float now;
        float later;

        if (fn_8011E9B4(candidate) || (candidate->mFlags & 0x800)) {
            continue;
        }
        pos.mX = candidate->mMotion.mPos.mX;
        pos.mY = candidate->mMotion.mPos.mY;
        fn_80227690(&offset, point, &pos);
        now = fn_802270A4(&offset);
        future.mX = candidate->mMotion.mPos.mX;
        future.mY = candidate->mMotion.mPos.mY;
        fn_8022732C(&future, &candidate->mMotion.mUnknown40, time);
        fn_80227690(&offset, point, &future);
        later = fn_802270A4(&offset);
        later = later > now ? now : later;
        if (later < best) {
            best = later;
            fn_80227690(&offset, &middle, &pos);
            replace = fn_802270A4(&offset) > now;
        }
    }
    if (replace) {
        point->mX = middle.mX;
        point->mY = middle.mY;
    }
}

int fn_80100370(Object_80137ABC *ball, Object_80039F5C *p, Vector_80039F5C *out, float value)
{
    Vector_80039F5C pos;
    Vector_80039F5C velocity = *(Vector_80039F5C *)&p->mMotion.mUnknown40;
    Vector_80039F5C ballPos;
    State_80039F5C *queue = p->mpState;
    State_80039F5C *state;
    Object_800B26B0 *motion = &p->mMotion;
    int angle = motion->mUnknown32;
    float speed = motion->mUnknown28;

    pos = motion->mPos;
    int result = 0;

    fn_80137D58(ball, &ballPos);
    state = p->mpState;
    switch (state->mId) {
    case 19:
        speed = fn_8016D9F4(p, 1.0f, 1.0f);
        break;
    case 20:
        if ((unsigned int)(state->mUnknown2 - 8) < 2) {
            angle = fn_8012CAAC(p);
        } else {
            angle = fn_8012CAA4(p);
        }
        fn_8012CD4C(p, &pos);
        speed = fn_8012CD60(p, 0.5f);
        fn_80227538((Point_8017886C *)&velocity, angle, speed);
        break;
    case 52:
        if ((unsigned int)(state->mUnknown1 - 4) < 2) {
            pos.mY += 3.0f;
            speed = fn_8016D9F4(p, 1.0f, 0.72f);
            fn_80227538((Point_8017886C *)&velocity, angle, speed);
        }
        break;
    }
    fn_80103F80(ball, pos, velocity, angle, out, p, speed, value);
    switch (p->mpState->mId) {
    case 10:
    case 51:
    case 52:
    case 58:
        break;
    default:
        if (fn_800F06F4(0, queue, 19, 0xFFFF) != 0xFFFF || fn_800F06F4(0, queue, 20, 0xFFFF) != 0xFFFF) {
            unsigned int index = fn_800F06F4(0, queue, 21, 0xFFFF);

            if (index != 0xFFFF && index > 1) {
                while (queue[index].mId != 19 && queue[index].mId != 20 && queue[index].mId != 51) {
                    index--;
                }
                if (index != 0) {
                    float steps = fn_8022781C(out, &ballPos) / value;
                    int count;

                    steps = (float)(int)steps;
                    count = (int)steps;
                    float shortened;

                    fn_80104328(p, (unsigned char)(index - 1), &count, &pos, &angle);
                    shortened = (float)count;
                    if (shortened < steps) {
                        if (state->mId == 20) {
                            speed = fn_8012CD60(p, 1.0f - shortened / steps);
                        } else {
                            speed = fn_8016D9F4(p, 1.0f - shortened / steps, 1.0f);
                        }
                        fn_80227538((Point_8017886C *)&velocity, angle, speed);
                        result = 1;
                        fn_80103F80(ball, pos, velocity, angle, out, p, speed, value);
                    }
                }
            }
        }
        break;
    }
    return result;
}

void fn_801007A4(Object_80137ABC *ball, Object_80039F5C *p, Object_80039F5C *other, Vector_80039F5C *out,
                 unsigned char *kind, float value)
{
    Object_800B26B0 *motion = &other->mMotion;

    switch (*kind) {
    case 1:
    case 7:
        if (!fn_80100370(ball, other, out, value)) {
            if (*kind == 1) {
                *kind = 0;
            } else {
                *kind = 6;
            }
        }
        break;
    case 0:
    case 4:
    case 6: {
        Vector_80039F5C velocity = *(Vector_80039F5C *)&motion->mUnknown40;
        Vector_80039F5C pos = motion->mPos;
        float speed = motion->mUnknown28;
        State_80039F5C *state = other->mpState;

        switch (state->mId) {
        case 52:
            if ((unsigned int)(state->mUnknown1 - 4) < 2) {
                pos.mY += 3.0f;
                speed = fn_8016D9F4(other, 1.0f, 1.0f);
                fn_80227538((Point_8017886C *)&velocity, motion->mUnknown32, speed);
            }
            break;
        case 51:
            if (fn_800F06F4(0, state, 19, 0xFFFF) != 0xFFFF && other->mMotion.mPos.mY >= p->mMotion.mPos.mY) {
                pos.mY += 2.5f;
                speed = fn_8016D9F4(other, 1.0f, 1.0f);
                fn_80227538((Point_8017886C *)&velocity, motion->mUnknown32, speed);
            }
            break;
        case 19: {
            int towardNegative = fn_801CFFD0(motion->mUnknown32, 0x800000) <= 0x271C70;
            int towardPositive = fn_801CFFD0(motion->mUnknown32, 0) <= 0x271C70;

            if (motion->mPos.mY < p->mMotion.mPos.mY - 2.0f && (towardNegative || towardPositive)) {
                speed = fn_8016D9F4(other, 1.0f, 1.0f);
                fn_80227538((Point_8017886C *)&velocity, motion->mUnknown32, speed);
                if (towardNegative) {
                    pos.mX -= 3.0f;
                } else {
                    pos.mX += 3.0f;
                }
            }
            break;
        }
        }
        fn_80103F80(ball, pos, velocity, motion->mUnknown32, out, other, speed, value);
        break;
    }
    default:
        out->mX = out->mY = out->mZ = 0.0f;
        break;
    }
}

void fn_80100AA0(Object_80039F5C *p,int,float *a,float *b)
{
    float rating=1.0f-(float)p->mRatings[6]*0.00392156886f;
    *a=1.0f-lbl_803EAEA8*rating;*b=1.0f-lbl_803EAEAC*rating;
}

void fn_80100B34(Object_80039F5C *p,float *out,float *maximum,float a,float b,float c)
{
    if(out && maximum) {
        a += (1.0f - (float)p->mRatings[6] * 0.00392156886f) * 0.3f + 0.05f;
        a += (1.0f - b) * 0.2f;
        *maximum = c * a * lbl_803EAEB0;
        *out = fn_80237260(0) * *maximum;
    }
}

void fn_80100BF8(Object_80039F5C *p, Vector_80039F5C *point, Point_8017886C *offset, float, float factor, float skill)
{
    float error = 0.0f;
    float amount = 0.0f;
    float maximum = 0.0f;
    Vector_80039F5C delta;
    Point_8017886C combined;
    Point_8017886C unused;
    Point_8017886C final;
    float distance;
    float length;
    float ratio;

    if (fn_800A7F1C(p->mIdBytes[2]) == 2) {
        return;
    }
    fn_802276B4(&delta, point, &p->mMotion.mPos);
    distance = fn_802270A4(&delta);
    length = factor * (lbl_803EAEB8 - lbl_803EAEB4) + lbl_803EAEB4;
    ratio = distance / length;
    length *= (float)fn_802372EC(0, 7) * 0.01f + 1.0f;
    if (ratio > 0.9f) {
        error = 0.05f;
        if (ratio > 1.0f) {
            error += 0.1f;
            length *= 1.0f - fn_80237260(0) * error * lbl_803EAEBC;
            distance = length;
            fn_80227538((Point_8017886C *)&delta, fn_801CFE40(delta.mY, delta.mX), length);
            fn_80227638(point, &delta, &p->mMotion.mPos);
        }
    }
    fn_80100B34(p, &amount, &maximum, error, skill, distance);
    fn_80227538((Point_8017886C *)&delta, fn_80100B0C(), amount);
    fn_80227638(&combined, &delta, offset);
    fn_80227690(&unused, point, offset);
    if (fn_802270A4(&combined) > maximum && amount > fn_802270A4(offset)) {
        fn_80227538((Point_8017886C *)&delta, fn_801CFE40(combined.mY, combined.mX), maximum);
        fn_80227690(&delta, &delta, offset);
    }
    fn_80227638(point, &delta, point);
    fn_80227690(&final, point, &p->mMotion.mPos);
    if (fn_802270A4(&final) > length || ratio > 1.0f) {
        fn_80227538((Point_8017886C *)point, fn_801CFE40(final.mY, final.mX), length);
        fn_80227638(point, point, &p->mMotion.mPos);
    }
}

Object_80039F5C *fn_80100EA0(Object_80039F5C *p, int angle)
{
    Object_80039F5C *players[3];
    unsigned char active;
    Point_8017886C center;
    Point_8017886C delta;
    Point_8017886C minimum;
    Point_8017886C maximum;
    unsigned char i;
    int best;
    Object_80039F5C *result;

    minimum.mX = 100.0f;
    minimum.mY = 100.0f;
    maximum.mX = -100.0f;
    maximum.mY = -100.0f;
    for (i = 0; i < 3; i++) {
        unsigned int index = fn_80168E00(p->mIdBytes[2], i, &active);

        if (index != 255 && active) {
            Object_80039F5C *other = fn_80039F5C(p->mIdBytes[2], (unsigned short)index);
            Vector_80039F5C *pos = &other->mMotion.mPos;

            players[i] = other;
            if (pos->mX < minimum.mX) {
                minimum.mX = pos->mX;
            }
            if (pos->mY < minimum.mY) {
                minimum.mY = pos->mY;
            }
            if (pos->mX > maximum.mX) {
                maximum.mX = pos->mX;
            }
            if (pos->mY > maximum.mY) {
                maximum.mY = pos->mY;
            }
        } else {
            players[i] = 0;
        }
    }
    center.mX = (maximum.mX - minimum.mX) * 0.5f + minimum.mX;
    center.mY = (maximum.mY - minimum.mY) * 0.5f + minimum.mY;
    best = 0x800000;
    result = 0;
    for (i = 0; i < 3; i++) {
        if (players[i]) {
            int difference;

            fn_80227690(&delta, &players[i]->mMotion.mPos, &center);
            difference = fn_801CFFD0(angle, fn_801CFE40(delta.mY, delta.mX));
            if (difference < best) {
                result = players[i];
                best = difference;
            }
        }
    }
    return result;
}

void fn_80101064(Object_80039F5C *p)
{
    int team=fn_80178320(),n=fn_80178D18(team);
    for(unsigned int i=0;(int)i<n;++i) {
        Object_80039F5C *other=fn_80039F5C(team,(unsigned char)i);
        Point_8017886C delta;fn_80227690(&delta,&other->mMotion.mPos,&p->mMotion.mPos);
        if(!(fn_802270A4(&delta)>=2.5f)) {
            Record_800B15FC *record=fn_800B15FC();fn_8009BD2C(other,&record->mUnknown0);
            record->mUnknownC=p->mMotion.mPos.mX;record->mUnknown10=p->mMotion.mPos.mY;record->mUnknown14=33;
            fn_800B1508();return;
        }
    }
}

void fn_80101130(Object_80039F5C *p, Object_80039F5C *other, unsigned short *out)
{
    Directions_8012430C values;
    unsigned char best;
    unsigned int facing;
    Lookup_8012078C *lookup;
    Object_80039F5C *receiver;
    Point_8017886C delta;
    unsigned int octant;
    int difference;
    float left = 0.0f;
    float right = 0.0f;
    int chosen = 0;
    int forward = 0;

    fn_8012430C(&values, 3, p);
    best = fn_801243E0(&values, -1);
    facing = ((unsigned int)p->mMotion.mUnknown32 + 0x100000) >> 21 & 7;
    lookup = fn_8012078C();
    receiver = fn_80039F5C(fn_80178320(), lookup->mpUnknown4[1]);
    fn_80227690(&delta, &other->mMotion.mPos, &p->mMotion.mPos);
    octant = ((unsigned int)fn_801CFE40(delta.mY, delta.mX) + 0x100000) >> 21 & 7;
    difference = fn_801CFFD0(p->mMotion.mUnknown32, 0x400000);
    if ((values.mCost[best] == 0.0f || values.mCost[(best + 1) & 7] == 0.0f || values.mCost[(best + 7) & 7] == 0.0f)
        && (values.mCost[octant] >= 3.0f || values.mCost[(octant + 1) & 7] >= 4.0f || values.mCost[(octant + 7) & 7] >= 4.0f)
        && difference < 0x4AAAAB) {
        chosen = 1;
    }
    if (!chosen) {
        int pastRight = p->mMotion.mPos.mX > fn_80178A5C() + (fn_80178A08() - fn_80178A5C()) * 0.25f;
        int pastLeft = p->mMotion.mPos.mX < -(fn_80178A5C() + (fn_80178A08() - fn_80178A5C()) * 0.25f);
        left = fn_801242E0(&values, 0);
        right = fn_801242E0(&values, 4);

        if (((pastLeft && left > right * 1.45f) || (pastRight && right > left * 1.45f)) && difference < 0xE38E3) {
            chosen = 1;
        }
    }
    if (!chosen) {
        if (p->mMotion.mPos.mY < fn_80177FE0().mY) {
            forward = 1;
        }
    }
    if (chosen) {
        if (facing == 2 && p->mMotion.mPos.mY > receiver->mMotion.mPos.mY
            && p->mMotion.mPos.mY < fn_80178A2C() - 15.0f) {
            *out = 5;
        }
    } else if (forward) {
        *out = 12;
    }
}

void fn_80101408(Object_80039F5C *p,Point_8017886C *point,int *angle)
{
    if(point && angle) {
        point->mX=fn_80178A08()+14.0f;
        point->mY=fn_80177FE0().mY+10.0f;
        if(!(p->mMotion.mPos.mX>=0.0f))point->mX=-point->mX;
        fn_80227690(point,point,&p->mMotion.mPos);
        *angle=(fn_801CFE40(point->mY,point->mX)-p->mMotion.mFacing)&0xFFFFFF;
    }
}

void fn_801014C8(Object_80039F5C *p,Point_8017886C *point,int *angle)
{
    if(point && angle) {
        Point_8017886C target;target.mX=0.0f;
        target.mY=(fn_80178A2C()+fn_80178A44())*0.5f;
        fn_80227690(point,&target,&p->mMotion.mPos);
        *angle=(fn_801CFE40(point->mY,point->mX)-p->mMotion.mFacing)&0xFFFFFF;
    }
}

void fn_80101568(Object_80039F5C *p, unsigned char *kind, Point_8017886C *point, int *angle)
{
    Vector_80039F5C target;

    target.mX = target.mY = target.mZ = 0.0f;
    if (point && angle && kind) {
        State_800FDA58 *state = (State_800FDA58 *)&p->mUnknown336;
        Object_80137ABC *ball = fn_80137C48(p);
        Record_8011F4F8 *record = fn_8011F4F8(state->mUnknown3Byte);
        Object_80039F5C *other = fn_80039F5C(p->mIdBytes[2], (unsigned char)record->mUnknownA[0]);
        float speed;

        if (state->mUnknown0Bytes[0]) {
            speed = lbl_803EA2C4 * 0.3f;
        } else {
            speed = fn_80103DD8(p, other, &record->mUnknown8, 0.9f);
        }
        if (ball) {
            fn_801007A4(ball, p, other, &target, kind, speed);
        } else {
            target.mX = other->mMotion.mPos.mX;
            target.mY = other->mMotion.mPos.mY;
        }
        fn_80227690(point, &target, &p->mMotion.mPos);
        fn_801CFE40(point->mY, point->mX);
        *angle = (fn_801CFE40(point->mY, point->mX) - p->mMotion.mFacing) & 0xFFFFFF;
        if (*angle > 0x1000000) {
            *angle -= 0x1000000;
        }
    }
}

void fn_801016A4(Object_80039F5C *p, unsigned char *kind, Point_8017886C *point, int *angle)
{
    if (!p || !kind || !point || !angle) {
        return;
    }
    *angle = 0;
    point->mY = point->mX = 0.0f;
    switch (*kind) {
    case 2:
    case 5:
        *angle = 0;
        break;
    case 3:
        fn_80101408(p, point, angle);
        break;
    case 8:
        fn_801014C8(p, point, angle);
        break;
    case 0:
    case 1:
    case 4:
    case 6:
    case 7:
        fn_80101568(p, kind, point, angle);
        break;
    }
}

void fn_8010176C(Object_80039F5C *p, int mode, Point_8017886C *point)
{
    if (!p) {
        return;
    }
    switch (mode) {
    case 4:
        if (fn_801BE648(p->mpUnknown792) == 69) {
            p->mUnknown1008.mUnknown1 = 10;
        } else {
            p->mUnknown1008.mUnknown1 = 1;
        }
        break;
    case 2:
        p->mUnknown1008.mUnknown1 = 3;
        break;
    case 5:
        p->mUnknown1008.mUnknown1 = 4;
        break;
    default: {
        State_800FDA58 *state = (State_800FDA58 *)&p->mUnknown336;
        Record_8011F4F8 *record = fn_8011F4F8(state->mUnknown3Byte);
        Object_80039F5C *other = 0;
        float distance;

        if (record && (unsigned char)record->mUnknownA[0] != 15) {
            other = fn_80039F5C(p->mIdBytes[2], (unsigned char)record->mUnknownA[0]);
        }
        if (other) {
            int near = other->mMotion.mPos.mY < fn_80177FE0().mY + 24.0f && fn_802270A4(point) < 32.0f;

            if (near) {
                distance = 24.0f;
            } else {
                distance = fn_802270A4(point);
            }
        } else {
            distance = fn_802270A4(point);
        }
        p->mUnknown1008.mUnknown1 = distance <= 24.0f ? 5 : 1;
        break;
    }
    }
}

}
