#include "game/fn_801248D4.h"
#include "game/Directions_8012430C.h"
#include "game/Object_80039F5C.h"
#include "game/Plan_80121264.h"
#include "game/Class_80148A58.h"
#include "game/fn_800F06F4.h"
#include "game/cu_80136B1C.h"
#include "game/Lookup_8012078C.h"
#include "game/Input_800B6D34.h"
#include "game/Message_800F01CC.h"
#include "game/Object_8017886C.h"
#include "game/fn_801C1F94.h"
#include <math.h>

struct State_80125304 {
    Object_80039F5C *mpUnknown0;
    unsigned short mUnknown4;
};
struct State_80125594 {
    int mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
};
extern "C" {
unsigned int fn_80178D70(int team);
unsigned int fn_80178D18(int team);
int fn_80178320(void);
int fn_801486A0(void);
Object_80039F5C *fn_80137B40(void);
void fn_800F00D4(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800F053C(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);

void fn_800B6D34(Object_80039F5C *p, Input_800B6D34 *pInput);
void fn_800B6E68(Object_80039F5C *p, Input_800B6D34 *pInput);
void fn_80227690(Point_8017886C *pOut, Point_8017886C *pA, Point_8017886C *pB);
void fn_802276B4(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
float fn_802270A4(Point_8017886C *p);
float fn_8022781C(Point_8017886C *pA, Point_8017886C *pB);
float fn_80260B1C(float x);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
int fn_801CFFF0(int a, int b, float factor);
int fn_8011E9B4(Object_80039F5C *p);
int fn_8011EAC0(Object_80039F5C *p, Object_80039F5C *pOther);
float fn_80178A08(void);
float fn_80178A44(void);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_80121BE8(Point_8017886C *pA, Point_8017886C *pB, Point_8017886C *pTarget, int angle, int heading,
                float distB, float distA);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_80227970(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC, Vector_80039F5C *pOut, float *pValue, float *pOther);
extern float lbl_803ECB08;
extern float lbl_803EA2C4;
extern float lbl_803EC9E8;
typedef void (*Score_8012430C)(Directions_8012430C *, Object_80039F5C *, Object_80039F5C *);
extern Score_8012430C const lbl_8029F584[7];

int fn_80125DF0(Object_80039F5C *p);
int fn_800E1584(Object_80039F5C *p);
int fn_80125C28(Object_80039F5C *p, State_80125594 *pState);

void fn_80125594(Object_80039F5C *p, State_80125594 *pState);
void fn_80125708(Object_80039F5C *p, State_80125594 *pState);

Object_80039F5C *fn_80124CE4(Object_80039F5C *p, int team, float *pOut, int angle, float length, int facing, float width);

int fn_80178308(void);
int fn_80177C38(void);
Point_8017886C fn_80177FE0(void);
int fn_8011F1A4(void);
unsigned int fn_8011F4C8(void);
float fn_8011F4D4(void);
int fn_801783AC(int a);
void fn_8012327C(Directions_8012430C *pValues, Object_80039F5C *p);
extern float lbl_803EB0A0, lbl_803EB0A4, lbl_803EB0A8, lbl_803EB0AC;

int fn_801485D4(void);
extern const Directions_8012430C lbl_8029F5A0[6];

float fn_8016D9F4(Object_80039F5C *p, float a, float b);
int fn_801208C8(Point_8017886C *pPos, Vector_80039F5C *pTarget, Vector_80039F5C *pVelocity, float speed);
float fn_80237260(int a);
unsigned int fn_802372EC(int a, int b);
int fn_8012A3B0(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C target, unsigned int *pOut, float distance);
int fn_800E815C(Object_80039F5C *p, int a, int b);

void fn_80123E2C(Directions_8012430C *, Object_80039F5C *, Object_80039F5C *);
Entry_801230B8 *fn_801230B8(Plan_80121264 *pPlan);
Entry_801230B8 *fn_80123174(Plan_80121264 *pPlan);
int fn_80123254(void *pA, void *pB);
void fn_80123594(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *);
void fn_8012368C(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *);
void fn_8012430C(Directions_8012430C *pOut, int kind, Object_80039F5C *p);
void fn_80124374(Directions_8012430C *pOut, int kind, Object_80039F5C *p, Object_80039F5C *a);
unsigned char fn_801243E0(Directions_8012430C *pValues, int angle);
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, unsigned char a, unsigned char count, float *pOut, int b);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, unsigned char a, unsigned char count, int angle, float *pOut, int b);
int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, Object_80039F5C **pOut);
float fn_8012506C(Object_80039F5C *p, int kind);
float fn_801250B8(Object_80039F5C *p, Object_80039F5C *a, int kind);
int fn_8012510C(Directions_8012430C *pValues);
int fn_80125214(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_80125304(Object_80039F5C *p);
int fn_801253A8(Object_80039F5C *p);
int fn_80125494(Object_80039F5C *p);
int fn_801254C8(Object_80039F5C *p);
int fn_80125D98(Object_80039F5C *p, State_80125594 *pState);
void fn_80125B74(Object_80039F5C *p, State_80125594 *pState);
int fn_80125E20(Object_80039F5C *p);
void fn_80125EC8(int a, int b);
void fn_80125F10(void);
int fn_80124B1C(Object_80039F5C *p, Object_80039F5C *pOther, int angle, float length, float width);
Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float length, float width, int facing);
Object_80039F5C *fn_80124CE4(Object_80039F5C *p, int team, float *pOut, int angle, float length, int facing, float width);
Object_80039F5C *fn_80124E5C(Object_80039F5C *p, int team, float *pOut, int angle, float length, int facing, float width);
void fn_801237F4(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *);
void fn_80123C2C(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *pExclude);
void fn_80123E30(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *);
void fn_80123F48(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *);
void fn_8012327C(Directions_8012430C *pValues, Object_80039F5C *p);
void fn_80125594(Object_80039F5C *p, State_80125594 *pState);
void fn_80125708(Object_80039F5C *p, State_80125594 *pState);
int fn_80125C28(Object_80039F5C *p, State_80125594 *);

void fn_801227DC(Object_80039F5C *p, Plan_80121264 *pPlan, Entry_801230B8 *pEntry)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Entry_80120E98 *pA = pEntry->mpUnknown0;
    Entry_80120E98 *pB = pEntry->mpUnknown4;
    int flagsA;
    int flagsB;
    int blocked = 0;
    int open = 0;
    int wide = 0;
    int inside = pMotion->mPos.mX < pB->mUnknown8.mX + 0.25f && pMotion->mPos.mX > pA->mUnknown8.mX - 0.25f;
    Point_8017886C delta;
    int angle;
    float value;

    flagsA = pA->mUnknown36;
    flagsB = pB->mUnknown36;
    if ((flagsA & 1) && (flagsB & 1)) {
        if (inside) {
            open = 1;
        }
    } else if ((flagsA & 2) && (flagsB & 1) || (flagsA & 1) && (flagsB & 2)) {
        open = 1;
        if ((flagsA | flagsB) & 4) {
            wide = 1;
        }
    } else if ((flagsA & 8) && (flagsB & 1) || (flagsA & 1) && (flagsB & 8)) {
        if (inside) {
            if (flagsA & 8) {
                fn_80227690(&delta, (Point_8017886C *)&pMotion->mPos, &pA->mUnknown8);
                angle = pA->mUnknown16;
            } else {
                fn_80227690(&delta, (Point_8017886C *)&pMotion->mPos, &pB->mUnknown8);
                angle = pB->mUnknown16;
            }
            if (fn_801CFFD0(delta.Heading() & 0xFFFFFF, angle) > 0x400000) {
                open = 1;
            }
        }
    } else if ((flagsA & 0x40) && (flagsB & 1) || (flagsA & 1) && (flagsB & 0x40)) {
        if (inside || (!fn_8011F1A4() || fn_8011F4C8() > 3) && !fn_801783AC(0)) {
            open = 1;
        } else {
            blocked = 1;
        }
        if ((!fn_8011F1A4() || fn_8011F4C8() > 3) && !fn_801783AC(0) &&
            fn_801CFFD0(pMotion->mFacing, pEntry->mUnknown16) <= 0x1FFFFF) {
            pEntry->mUnknown28 += 1.0f;
        }
    } else if ((flagsA & 2) && (flagsB & 2)) {
        if (inside) {
            open = 1;
        } else {
            blocked = 1;
        }
        if ((flagsA | flagsB) & 4) {
            wide = 1;
        }
    } else if ((flagsA & 8) && (flagsB & 2) || (flagsA & 2) && (flagsB & 8)) {
        if (!inside) {
            open = 1;
        }
    } else if ((flagsA & 0x40) && (flagsB & 2) || (flagsA & 2) && (flagsB & 0x40)) {
        float distance;
        open = 1;
        if ((flagsA | flagsB) & 4) {
            wide = 1;
        }
        if (flagsA & 2) {
            value = pA->mUnknown28;
        } else {
            value = pB->mUnknown28;
        }
        if (value > 5.0f && (!fn_8011F1A4() || fn_8011F4C8() > 3) && !fn_801783AC(0) &&
            fn_801CFFD0(pMotion->mFacing, pEntry->mUnknown16) <= 0x1FFFFF) {
            pEntry->mUnknown28 += 1.0f;
        } else {
            blocked = 1;
        }
    } else if ((flagsA & 8) && (flagsB & 8)) {
    } else if ((flagsA & 0x40) && (flagsB & 8) || (flagsA & 8) && (flagsB & 0x40)) {
        if (inside && pPlan->mUnknown2372 <= 2) {
            fn_80227690(&delta, &pB->mUnknown8, (Point_8017886C *)&pMotion->mPos);
            angle = delta.Heading() & 0xFFFFFF;
            if ((pMotion->mFacing & 0xFFFFFF) > angle) {
                fn_80227690(&delta, &pA->mUnknown8, (Point_8017886C *)&pMotion->mPos);
                angle = delta.Heading() & 0xFFFFFF;
                if ((pMotion->mFacing & 0xFFFFFF) < angle) {
                    pEntry->mUnknown28 += 1.0f;
                }
            }
        }
    }

    if (((flagsA | flagsB) & 8) && pEntry->mUnknown24 < 5.0f) {
        value = 0.0f;

        if ((flagsA & 0x18) == 8 && pA->mUnknown8.mY - pMotion->mPos.mY > 1.0f) {
            value = fn_801CFB18(fn_801CFFD0(pA->mUnknown16, pEntry->mUnknown16) / 2) * 0.5f;
        }
        if ((flagsB & 0x18) == 8 && pB->mUnknown8.mY - pMotion->mPos.mY > 1.0f) {
            value += fn_801CFB18(fn_801CFFD0(pB->mUnknown16, pEntry->mUnknown16) / 2) * 0.5f;
            if (flagsA & 8) {
                value *= 0.5f;
            }
        }
        pEntry->mUnknown28 -= value;
    }
    if (open && pEntry->mUnknown24 > 3.0f && fn_801CFFD0(pMotion->mFacing, pEntry->mUnknown16) <= 0x1FFFFF) {
        value = fn_801CFB94(fn_801CFFD0(pEntry->mUnknown16, pMotion->mFacing));

        if (value < 0.0f) {
            value = 0.0f;
        }
        if (pA->mpUnknown0 && pA->mpUnknown4 &&
            (fn_80121BE8(pA->mpUnknown0, pA->mpUnknown4, 0, pA->mUnknown24, pA->mUnknown20, pA->mUnknown32, pA->mUnknown28) ||
             fn_80121BE8(pA->mpUnknown0, pA->mpUnknown4, &pEntry->mUnknown8, pA->mUnknown24, pA->mUnknown20,
                         pA->mUnknown32, pA->mUnknown28))) {
            pEntry->mUnknown28 += value;
        }
        if (pB->mpUnknown0 && pB->mpUnknown4 &&
            (fn_80121BE8(pB->mpUnknown0, pB->mpUnknown4, 0, pB->mUnknown24, pB->mUnknown20, pB->mUnknown32, pB->mUnknown28) ||
             fn_80121BE8(pB->mpUnknown0, pB->mpUnknown4, &pEntry->mUnknown8, pB->mUnknown24, pB->mUnknown20,
                         pB->mUnknown32, pB->mUnknown28))) {
            pEntry->mUnknown28 += value;
        }
    }
    if (wide) {
        if (fn_8011F1A4() && fn_8011F4C8() <= 3 ||
            fn_8011F1A4() && (fn_8011F4C8() & 1) == 0 && (flagsA & 4) ||
            fn_8011F1A4() && (fn_8011F4C8() & 1) && (flagsB & 4)) {
            pEntry->mUnknown28 += 1.0f;
        }
    }
    if (inside) {
        float width = pEntry->mUnknown24;
        unsigned int degrees;

        if (width > 12.0f) {
            width = 12.0f;
        }
        value = width / 12.0f;
        degrees = value * 90.0f;
        angle = degrees * 46603.38f;
        if (fn_801CFFD0(pEntry->mUnknown16, pMotion->mFacing) < angle) {
            pEntry->mUnknown28 += value;
        }
    }
    if (blocked && fn_801CFFD0(pMotion->mFacing, 0x400000) <= 0x1C71C6) {
        fn_80227690(&delta, &pB->mUnknown8, (Point_8017886C *)&pMotion->mPos);
        angle = delta.Heading() & 0xFFFFFF;
        if ((pMotion->mFacing & 0xFFFFFF) > angle) {
            fn_80227690(&delta, &pA->mUnknown8, (Point_8017886C *)&pMotion->mPos);
            angle = delta.Heading() & 0xFFFFFF;
            if ((pMotion->mFacing & 0xFFFFFF) < angle) {
                pEntry->mUnknown28 += 0.25f;
            }
        }
    }
}

Entry_801230B8 *fn_801230B8(Plan_80121264 *pPlan)
{
    unsigned char best = 0;
    float value = 0.0f;
    for (unsigned char i = 0; i < pPlan->mUnknown2372; i++) {
        if (!(pPlan->mUnknown1444[i].mUnknown28 <= value)) {
            value = pPlan->mUnknown1444[i].mUnknown28;
            best = i;
        }
    }
    return &pPlan->mUnknown1444[best];
}

Entry_801230B8 *fn_80123174(Plan_80121264 *pPlan)
{
    Entry_801230B8 *pBest = 0;
    if (pPlan->mUnknown2372 != 0) {
        unsigned char best = 0;
        float value = 0.0f;
        for (unsigned char i = 0; i < pPlan->mUnknown2372; i++) {
            if (!(pPlan->mUnknown1444[i].mUnknown28 <= value)) {
                value = pPlan->mUnknown1444[i].mUnknown28;
                best = i;
            }
        }
        pBest = &pPlan->mUnknown1444[best];
    }
    return pBest;
}

int fn_80123254(void *pA, void *pB)
{
    if (*(float *)pA - *(float *)pB > 0.0f) return 1;
    return -1;
}

void fn_8012327C(Directions_8012430C *pValues, Object_80039F5C *p)
{
    Point_8017886C point;
    point.mY = fn_80177FE0().mY;
    Point_8017886C *pPos = (Point_8017886C *)&p->mMotion.mPos;
    unsigned char mode;
    if (pPos->mY > point.mY - 1.5f || fn_80177C38()) {
        if (!(pPos->mX >= 10.0f - fn_80178A08())) mode = 3;
        else if (!(pPos->mX <= fn_80178A08() - 10.0f)) mode = 4;
        else mode = 5;
    } else {
        mode = 0;
        if (fn_8011F1A4()) {
            point.mX = fn_8011F4D4();
            if (!(point.mY - pPos->mY <= 2.25f) && !fn_801783AC(0)) {
                Point_8017886C delta;
                fn_80227690(&delta, &point, pPos);
                unsigned int direction = (fn_801CFE40(delta.mY, delta.mX) + 0x100000) >> 21 & 7;
                switch ((int)fn_8011F4C8()) {
                case 6: case 8: case 10: case 12:
                    if (!(point.mX <= pPos->mX)) mode = 1;
                    else pValues->mCost[1] -= 5.0f;
                    break;
                case 7: case 9: case 11: case 13:
                    if (!(point.mX >= pPos->mX)) mode = 2;
                    else pValues->mCost[3] -= 5.0f;
                    break;
                default:
                    if (!(fabsf(point.mX - pPos->mX) <= 1.5f)) {
                        if (!(point.mX <= pPos->mX)) {pValues->mCost[2] -= 1.0f; pValues->mCost[1] -= 2.0f;}
                        else {pValues->mCost[2] -= 1.0f; pValues->mCost[3] -= 2.0f;}
                    } else pValues->mCost[direction] -= 10.0f;
                    break;
                }
            }
        }
    }
    const Directions_8012430C *pRow = &lbl_8029F5A0[mode];
    if (fn_801485D4() && fn_80148A58()->vfn_09(1)) pRow = (Directions_8012430C *)fn_80148A58()->vfn_09(1);
    for (unsigned char i = 0; i < 8; i++) pValues->mCost[i] += pRow->mCost[i];
}

void fn_80123594(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    for (unsigned char team = 0; team < 2; team++) {
        unsigned int count = fn_80178D70(team);
        for (unsigned char i = 0; i < count; i++) {
            Object_80039F5C *pOther = fn_80039F5C(team, i);
            Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
            float distance = fn_8022781C(&pos, pOtherPos);
            if (!(distance >= 15.0f)) {
                Point_8017886C delta;
                fn_80227690(&delta, pOtherPos, &pos);
                unsigned int direction = (fn_801CFE40(delta.mY, delta.mX) + 0x100000) >> 21 & 7;
                pValues->mCost[direction] += 15.0f - distance;
            }
        }
    }
}

void fn_8012368C(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    int team = p->mIdBytes[2] ^ 1;
    unsigned int count = fn_80178D70(team);
    for (unsigned char i = 0; i < count; i++) {
        int valid = 1;
        Object_80039F5C *pOther = fn_80039F5C(team, i);
        switch (pOther->mpState->mId) {
        case 10:
        case 11:
        case 17:
            valid = 0;
            break;
        }
        if (pOther->mFlags & 0x800) valid = 0;
        if (valid) {
            Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
            float distance = fn_8022781C(&pos, pOtherPos);
            if (pOther->mUnknown1032 != 8 && pOther->mUnknown1032 != 0) distance *= 4.0f;
            if (!(distance >= 8.0f)) {
                Point_8017886C delta;
                fn_80227690(&delta, pOtherPos, &pos);
                unsigned int direction = (fn_801CFE40(delta.mY, delta.mX) + 0x100000) >> 21 & 7;
                pValues->mCost[direction] += 15.0f - distance;
            }
        }
    }
}

void fn_801237F4(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    int facing = p->mMotion.mFacing;
    int ownTeam = fn_80178320();
    float range, factor;
    if (!fn_80177C38() && !(pos.mY >= fn_80177FE0().mY + 5.0f)) {
        if (fn_8011F1A4() && fn_8011F4C8() <= 3) range = 10.0f;
        else range = 12.0f;
        factor = 0.0f;
    } else {range = 14.0f; factor = 0.6f;}
    for (unsigned char team = 0; team < 2; team++) {
        unsigned int count = fn_80178D70(team);
        for (unsigned char i = 0; i < count; i++) {
            Object_80039F5C *pOther = fn_80039F5C(team, i);
            if (pOther == p) continue;
            Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
            float distance = fn_8022781C(&pos, pOtherPos);
            Point_8017886C delta;
            fn_80227690(&delta, pOtherPos, &pos);
            int angle = fn_801CFE40(delta.mY, delta.mX);
            float limit = (1.0f - fn_801CFB18(fn_801CFFD0(facing, angle) / 2) * factor) * range;
            if (!(distance >= limit)) {
                unsigned int direction = (angle + 0x100000) >> 21 & 7;
                float value = limit - distance;
                if (((unsigned int)pOther->mId >> 8 & 255) == ownTeam) {
                    if (!(pOther->mFlags & 0x800)) {
                        value *= 1.25f;
                        if (p->mUnknown560.mUnknown40 == pOther->mId) value += value;
                        if (pOther->mUnknown1032 == 5 || pOther->mUnknown1032 == 6) {
                            if (!(distance >= 1.5f)) value += value;
                        } else if (pOther->mUnknown1032 == 8 || pOther->mUnknown1032 == 0) {
                            if (!(distance >= 2.0f) && direction == ((p->mMotion.mFacing + 0x100000) >> 21 & 7)) value *= 5.0f;
                        }
                        if (!(pOtherPos->mY >= pos.mY)) value *= 0.5f;
                    }
                } else {
                    if (p->mUnknown560.mUnknown44 == pOther->mId) value += value;
                    if (pOther->mUnknown1032 == 4 || pOther->mUnknown1032 == 6 || pOther->mUnknown1032 == 5) {
                        if (!(distance >= 1.5f)) value += value;
                    } else {
                        if (!(pOther->mMotion.mUnknown28 <= lbl_803ECB08 * 0.4f)
                            && fn_801CFFD0(angle, pOther->mMotion.mUnknown32) <= 0x1FFFFF) value *= 0.25f;
                        if (pOther->mUnknown1052 == 3 && fn_8011F1A4() && fn_8011F4C8() <= 3
                            && fn_801CFFD0(angle, facing) <= 0x1FFFFF) {
                            if (!fn_801783AC(0)) value -= 4.0f;
                            else value -= 2.0f;
                        }
                    }
                }
                pValues->mCost[direction] += value;
            }
        }
    }
    if (fn_801486A0()) fn_8012327C(pValues, p);
    else if (fn_800F06F4(0, fn_80039F5C(fn_80178320(), 0)->mpState, 51, 65535) != 65535) {
        pValues->mCost[(p->mMotion.mFacing + 0x100000) >> 21 & 7] = 0.0f;
    }
}

void fn_80123C2C(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *pExclude)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    int facing = p->mMotion.mFacing;
    int team = fn_80178320();
    float range = lbl_803EB0A0;
    float factor = lbl_803EB0A4;
    unsigned int count = fn_80178D70(team);
    for (unsigned char i = 0; i < count; i++) {
        float value = 0.0f;
        Object_80039F5C *pOther = fn_80039F5C(team, i);
        if (pOther == pExclude) continue;
        Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
        float distance = fn_8022781C(&pos, pOtherPos);
        Point_8017886C delta;
        fn_80227690(&delta, pOtherPos, &pos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        int special = pOther->mpState->mId == 12 || pOther->mpState->mId == 94;
        float limit = (1.0f - fn_801CFB18(fn_801CFFD0(facing, angle) / 2) * factor) * range;
        if (!(distance >= limit)) {
            unsigned int direction = (angle + 0x100000) >> 21 & 7;
            if (!(pOther->mFlags & 0x800)) {
                value = limit - distance;
                if (pOther->mUnknown1032 == 8 || pOther->mUnknown1032 == 0) value += value;
                if (special) value *= 1.25f;
                value *= 1.0f + (1.0f - fn_801CFB18(fn_801CFFD0(pOther->mMotion.mFacing, (angle + 0x800000) & 0xFFFFFF))) * lbl_803EB0A8;
                if (!(pOtherPos->mY >= pos.mY)) value *= lbl_803EB0AC;
            }
            if (!(value <= pValues->mCost[direction])) pValues->mCost[direction] = value;
        }
    }
}

void fn_80123E30(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    int team = p->mIdBytes[2] ^ 1;
    for (unsigned char i = 0; i < 7; i++) {
        Object_80039F5C *pOther = fn_80039F5C(team, i);
        Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
        float distance = fn_8022781C(&pos, pOtherPos);
        if (!(distance >= 8.0f)) {
            Point_8017886C delta;
            fn_80227690(&delta, pOtherPos, &pos);
            unsigned int direction = (fn_801CFE40(delta.mY, delta.mX) + 0x100000) >> 21 & 7;
            float value = 8.0f - distance;
            pValues->mCost[direction] += value;
            pValues->mCost[(direction + 1) % 8] += value * 0.5f;
            pValues->mCost[(direction - 1) % 8] += value * 0.5f;
        }
    }
}

void fn_80123F48(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    int team = fn_80178320();
    unsigned int count = fn_80178D70(team);
    for (unsigned char i = 0; i < count; i++) {
        float value = 0.0f;
        Object_80039F5C *pOther = fn_80039F5C(team, i);
        if (pOther == p) continue;
        Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
        float distance = fn_8022781C(&pos, pOtherPos);
        if (!(distance >= 8.5f)) {
            Point_8017886C delta;
            fn_80227690(&delta, pOtherPos, &pos);
            int angle = fn_801CFE40(delta.mY, delta.mX);
            unsigned int direction = (angle + 0x100000) >> 21 & 7;
            if (pOther->mIdBytes[2] == team) {
                Object_80039F5C *pBlocker = 0;
                value = 8.5f - distance;
                if (!(value <= 7.0f)) value = 7.0f;
                if (pOther->mFlags & 0x800) value -= 3.0f;
                int facing = p->mMotion.mFacing;
                if (!(p->mFlags & 0x200000)) {
                    if (!p->mUnknown2913) facing += 0x400000;
                    else facing -= 0x400000;
                    facing &= 0xFFFFFF;
                }
                if (fn_801CFFD0(facing, angle) > 0x400000) {
                    float divisor = 0.25f + (1.0f - p->mRatings[6] * 0.003921568859368563f);
                    if (!(divisor >= 0.25f)) divisor = 0.25f;
                    value /= divisor * 4.0f;
                }
                if (!(distance >= 4.0f)) {
                    if ((pOther->mUnknown1032 >= 4 && pOther->mUnknown1032 <= 6)
                        || pOther->mpState->mId == 32 || pOther->mpState->mId == 11 || pOther->mpState->mId == 17) value -= 4.0f;
                    fn_80124714(p, pOther, &pBlocker);
                    if (pBlocker && pBlocker->mIdBytes[2] == fn_80178308()) value -= 4.0f;
                } else {
                    if ((pOther->mUnknown1032 >= 4 && pOther->mUnknown1032 <= 6)
                        || pOther->mpState->mId == 32 || pOther->mpState->mId == 11 || pOther->mpState->mId == 17) value -= 9.0f;
                    fn_80124714(p, pOther, &pBlocker);
                    if (pBlocker && pBlocker->mIdBytes[2] == fn_80178308()) value -= 9.0f;
                }
            }
            if (!(value >= 0.0f)) value = 0.0f;
            float side = value * 0.5f;
            pValues->mCost[direction] += value;
            pValues->mCost[(direction + 1) % 8] += side;
            pValues->mCost[(direction - 1) % 8] += side;
            pValues->mCost[(direction + 3) % 8] -= side;
            pValues->mCost[(direction - 3) % 8] -= side;
            pValues->mCost[(direction + 4) % 8] -= value;
        }
    }
}

void fn_8012430C(Directions_8012430C *pOut, int kind, Object_80039F5C *p)
{
    fn_801C1F94(pOut, 0, 32);
    if (lbl_8029F584[kind]) lbl_8029F584[kind](pOut, p, 0);
}

void fn_80124374(Directions_8012430C *pOut, int kind, Object_80039F5C *p, Object_80039F5C *a)
{
    fn_801C1F94(pOut, 0, 32);
    if (lbl_8029F584[kind]) lbl_8029F584[kind](pOut, p, a);
}

unsigned char fn_801243E0(Directions_8012430C *pValues, int angle)
{
    float minimum = 32767.0f;
    unsigned char best = 0;
    for (unsigned char i = 0; i < 8; i++) {
        float value = pValues->mCost[i];
        if (!(value >= minimum)) {
            best = i;
            minimum = value;
        } else if (value == minimum) {
            float side = pValues->mCost[(i - 1) & 7] + pValues->mCost[(i + 1) & 7];
            float bestSide = pValues->mCost[(best - 1) & 7] + pValues->mCost[(best + 1) & 7];
            if (!(side >= bestSide)) {
                minimum = value;
                best = i;
            } else if (side == bestSide && angle != -1
                && fn_801CFFD0(angle, i << 21) < fn_801CFFD0(angle, best << 21)) {
                minimum = pValues->mCost[i];
                best = i;
            }
        }
    }
    return best;
}

Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, unsigned char a, unsigned char count, float *pOut, int b)
{
    Point_8017886C *pPos = (Point_8017886C *)&p->mMotion.mPos;
    float minimum = 3.4028234663852886e38f;
    Object_80039F5C *pBest = 0;
    for (unsigned char i = a; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(team, i);
        if (pOther != p && (!b || !fn_8011E9B4(pOther))) {
            Point_8017886C delta;
            fn_80227690(&delta, (Point_8017886C *)&pOther->mMotion.mPos, pPos);
            float distance = delta.mX * delta.mX + delta.mY * delta.mY;
            if (!(distance >= minimum)) { minimum = distance; pBest = pOther; }
        }
    }
    *pOut = fn_80260B1C(minimum);
    return pBest;
}

Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, unsigned char a, unsigned char count, int angle, float *pOut, int b)
{
    Point_8017886C *pPos = (Point_8017886C *)&p->mMotion.mPos;
    int facing = p->mMotion.mUnknown28 != 0.0f ? p->mMotion.mUnknown32 : p->mMotion.mFacing;
    float minimum = 32767.0f;
    Object_80039F5C *pBest = 0;
    for (unsigned char i = a; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(team, i);
        if (pOther == p || (b && (pOther->mUnknown1032 >= 4 && pOther->mUnknown1032 <= 6))) continue;
        Point_8017886C delta;
        fn_80227690(&delta, (Point_8017886C *)&pOther->mMotion.mPos, pPos);
        if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), facing) < angle) {
            float distance = delta.mX * delta.mX + delta.mY * delta.mY;
            if (!(distance >= minimum)) { minimum = distance; pBest = pOther; }
        }
    }
    *pOut = fn_80260B1C(minimum);
    return pBest;
}

int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, Object_80039F5C **pOut)
{
    Point_8017886C delta;
    Object_800B26B0 *pMotion = &p->mMotion;
    fn_80227690(&delta, (Point_8017886C *)&pOther->mMotion.mPos, (Point_8017886C *)&pMotion->mPos);
    int angle = fn_801CFE40(delta.mY, delta.mX);
    float length = fn_802270A4(&delta);
    float minimum = 1000.0f;
    int result = 1;
    if (pOut) *pOut = 0;
    for (unsigned char team = 0; team < 2; team++) {
        unsigned int count = fn_80178D70(team);
        for (unsigned char i = 0; i < count; i++) {
            Object_80039F5C *pCandidate = fn_80039F5C(team, i);
            if (pCandidate == p || pCandidate == pOther) continue;
            Point_8017886C *pCandidatePos = (Point_8017886C *)&pCandidate->mMotion.mPos;
            fn_80227690(&delta, pCandidatePos, (Point_8017886C *)&pMotion->mPos);
            if (fn_801CFFD0(angle, fn_801CFE40(delta.mY, delta.mX)) <= 0x355554) {
                float distance = fn_802270A4(&delta);
                if (!(distance >= length) && !(distance >= minimum)) {
                    Vector_80039F5C nearest;
                    float offset, unused;
                    fn_80227970(&pMotion->mPos, &pOther->mMotion.mPos, &pCandidate->mMotion.mPos, &nearest, &offset, &unused);
                    if (!(offset >= 0.5f)) {
                        minimum = distance;
                        result = 0;
                        if (pOut) *pOut = pCandidate;
                    }
                }
            }
        }
    }
    return result;
}

int fn_801248D4(Object_80039F5C *p, Vector_80039F5C *pPos, Vector_80039F5C *pTarget, Object_80039F5C **pOut, float margin, float width, Filter_801248D4 *pFilter, Object_80039F5C *pExclude)
{
    int result = 1;
    if (!pPos) pPos = &p->mMotion.mPos;
    pTarget->mZ = 0.0f;
    Vector_80039F5C nearest;
    Vector_80039F5C delta;
    fn_802276B4(&delta, pTarget, pPos);
    int angle = fn_801CFE40(delta.mY, delta.mX);
    float length = fn_802270A4((Point_8017886C *)&delta);
    float minimum = 1000.0f;
    if (pOut) *pOut = 0;
    for (unsigned char team = 0; team < 2; team++) {
        unsigned int count = fn_80178D70(team);
        for (unsigned char i = 0; i < count; i++) {
            int valid = 1;
            Object_80039F5C *pOther = fn_80039F5C(team, i);
            if (pFilter) {
                for (unsigned char j = 0; j < pFilter->mCount; j++) {
                    if (pOther->mpState->mId == *(pFilter->mValues + j)) {valid = 0; break;}
                }
            }
            if (pOther == p || !valid || pExclude == pOther) continue;
            fn_802276B4(&delta, &pOther->mMotion.mPos, pPos);
            if (fn_801CFFD0(angle, fn_801CFE40(delta.mY, delta.mX)) <= 0x355554) {
                float distance = fn_802270A4((Point_8017886C *)&delta);
                if (!(distance >= length + margin) && !(distance >= minimum)) {
                    float offset, unused;
                    fn_80227970(pPos, pTarget, &pOther->mMotion.mPos, &nearest, &offset, &unused);
                    if (!(offset >= width)) {
                        minimum = distance; result = 0;
                        if (pOut) *pOut = pOther;
                    }
                }
            }
        }
    }
    return result;
}

int fn_80124B1C(Object_80039F5C *p, Object_80039F5C *pOther, int angle, float length, float width)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
    int facing = pMotion->mFacing;
    if (pOther != p) {
        Point_8017886C delta;
        fn_80227690(&delta, pOtherPos, (Point_8017886C *)&pMotion->mPos);
        if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), facing) < angle) {
            float distance = fn_802270A4(&delta);
            if (!(distance >= length)) {
                Vector_80039F5C target;
                fn_80227538((Point_8017886C *)&target, facing, length);
                target.mX += pMotion->mPos.mX;
                target.mY += pMotion->mPos.mY;
                target.mZ = pMotion->mPos.mZ;
                Vector_80039F5C nearest;
                float unused;
                fn_80227970(&pMotion->mPos, &target, &pOther->mMotion.mPos, &nearest, &distance, &unused);
                if (width + width > distance) return 1;
            }
        }
    }
    return 0;
}

Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float length, float width, int facing)
{
    *pOut = 32767.0f;
    Object_80039F5C *pBest = 0;
    for (unsigned char team = 0; team < 2; team++) {
        float distance;
        Object_80039F5C *pOther = fn_80124CE4(p, team, &distance, angle, length, facing, width);
        if (pOther && !(distance >= *pOut)) { *pOut = distance; pBest = pOther; }
    }
    return pBest;
}

Object_80039F5C *fn_80124CE4(Object_80039F5C *p, int team, float *pOut, int angle, float length, int facing, float width)
{
    *pOut = 32767.0f;
    float limit = width + width;
    Object_80039F5C *pBest = 0;
    unsigned int count = fn_80178D70(team);
    Vector_80039F5C *pPos = &p->mMotion.mPos;
    for (unsigned char i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(team, i);
        if (pOther == p) continue;
        Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
        Point_8017886C delta;
        fn_80227690(&delta, pOtherPos, (Point_8017886C *)pPos);
        if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), facing) < angle) {
            float distance = fn_802270A4(&delta);
            if (!(distance >= length)) {
                Vector_80039F5C target;
                fn_80227538((Point_8017886C *)&target, facing, length);
                target.mX += pPos->mX;
                target.mY += pPos->mY;
                target.mZ = pPos->mZ;
                Vector_80039F5C nearest;
                float offset, unused;
                fn_80227970(pPos, &target, &pOther->mMotion.mPos, &nearest, &offset, &unused);
                if (!(limit <= offset) && !(distance >= *pOut)) { *pOut = distance; pBest = pOther; }
            }
        }
    }
    return pBest;
}

Object_80039F5C *fn_80124E5C(Object_80039F5C *p, int team, float *pOut, int angle, float length, int facing, float width)
{
    *pOut = 32767.0f;
    float limit = width + width;
    Object_80039F5C *pBest = 0;
    unsigned int count = fn_80178D70(team);
    Vector_80039F5C *pPos = &p->mMotion.mPos;
    for (unsigned char i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(team, i);
        if (pOther == p || pOther->mUnknown1032 == 4) continue;
        Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
        Point_8017886C delta;
        fn_80227690(&delta, pOtherPos, (Point_8017886C *)pPos);
        if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), facing) < angle) {
            float distance = fn_802270A4(&delta);
            if (!(distance >= length)) {
                Vector_80039F5C target;
                fn_80227538((Point_8017886C *)&target, facing, length);
                target.mX += pPos->mX;
                target.mY += pPos->mY;
                target.mZ = pPos->mZ;
                Vector_80039F5C nearest;
                float offset, unused;
                fn_80227970(pPos, &target, &pOther->mMotion.mPos, &nearest, &offset, &unused);
                if (!(limit <= offset) && !(distance >= *pOut)) { *pOut = distance; pBest = pOther; }
            }
        }
    }
    return pBest;
}

float fn_8012506C(Object_80039F5C *p, int kind)
{
    Directions_8012430C values;
    fn_8012430C(&values, kind, p);
    float sum = 0.0f;
    for (int i = 0; i < 8; i++) sum += values.mCost[i];
    return sum;
}

float fn_801250B8(Object_80039F5C *p, Object_80039F5C *a, int kind)
{
    Directions_8012430C values;
    fn_80124374(&values, kind, p, a);
    float sum = 0.0f;
    for (int i = 0; i < 8; i++) sum += values.mCost[i];
    return sum;
}

int fn_8012510C(Directions_8012430C *pValues)
{
    unsigned int best = fn_801243E0(pValues, -1);
    float next = pValues->mCost[(best + 1) % 8];
    float previous = pValues->mCost[(best - 1) % 8];
    float scale = pValues->mCost[best];
    float lower = next;
    int offset = 0x100000;
    if (!(next < previous)) {
        lower = previous;
        offset = -0x100000;
    }
    if (!(scale <= 0.0f)) scale /= lower;
    else if (!(scale >= 0.0f) && !(lower >= 0.0f)) scale = lower / scale;
    else scale = 0.0f;
    return ((best << 21) + (int)(offset * scale)) & 0xFFFFFF;
}

int fn_80125214(Object_80039F5C *p, Object_80039F5C *pTarget)
{
    int result = 0;
    Object_80039F5C *pOther;
    float distance;
    if (!pTarget) {
        int team;
        if (fn_801486A0() == 0 || fn_801486A0() == 1) team = p->mIdBytes[2];
        else {
            team = p->mIdBytes[2];
            team ^= 1;
        }
        pOther = fn_801245DC(p, team, 0, fn_80178D18(team), 0x400000, &distance, 1);
    } else {
        pOther = pTarget;
        Point_8017886C delta;
        fn_80227690(&delta, (Point_8017886C *)&p->mMotion.mPos, (Point_8017886C *)&pOther->mMotion.mPos);
        distance = fn_802270A4(&delta);
    }
    if (pOther && pOther != fn_80137B40() && !(distance >= 3.0f)) result = fn_8011EAC0(p, pOther);
    return result;
}

int fn_80125304(Object_80039F5C *p)
{
    State_80125304 *pState = (State_80125304 *)&p->mUnknown336;
    if (p->mpState->mUnknown1 != 255) {
        int key = 1 | ((p->mIdBytes[2] ^ 1) << 8) | (p->mpState->mUnknown1 << 16);
        pState->mpUnknown0 = fn_8009BCE8(&key);
    } else pState->mpUnknown0 = 0;
    pState->mUnknown4 = 30;
    p->mUnknown512.mUnknown15 = 30;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
    p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
    p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
    return 0;
}

int fn_801253A8(Object_80039F5C *p)
{
    State_80125304 *pState = (State_80125304 *)&p->mUnknown336;
    pState->mUnknown4--;
    if (pState->mUnknown4 & 0x8000) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.72f;
        p->mUnknown512.mUnknown15 = 0;
        return 1;
    }
    p->mUnknown512.mUnknown15 = 30;
    if (!fn_80125214(p, pState->mpUnknown0) && p->mUnknown8 == 255) {
        if (!pState->mpUnknown0) return 1;
        Point_8017886C delta;
        fn_80227690(&delta, (Point_8017886C *)&pState->mpUnknown0->mMotion.mPos, (Point_8017886C *)&p->mMotion.mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = angle;
        p->mUnknown512.mUnknown4 = angle;
        p->mUnknown512.mUnknown0 = 1.0f;
    }
    return 0;
}

int fn_80125494(Object_80039F5C *p)
{
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown0 = 0.72f;
    p->mUnknown512.mUnknown15 = 0;
    return 1;
}

int fn_801254C8(Object_80039F5C *p)
{
    Input_800B6D34 input;
    fn_800B6D34(p, &input);
    fn_800B6E68(p, &input);
    return 0;
}

void fn_80125594(Object_80039F5C *p, State_80125594 *pState)
{
    Vector_80039F5C target, velocity;
    fn_80137D58(fn_801374BC(), &target);
    Object_80039F5C *pOther = fn_80137B40();
    if (!pOther) fn_80137EC4(fn_801374BC(), &velocity);
    else { velocity.mX = pOther->mMotion.mUnknown40; velocity.mY = pOther->mMotion.mUnknown44; velocity.mZ = pOther->mMotion.mUnknown48; }
    float speed;
    if (!(p->mMotion.mUnknown28 < fn_8016D9F4(p, 0.14f, 1.0f))) speed = p->mMotion.mUnknown28;
    else speed = fn_8016D9F4(p, 0.14f, 1.0f);
    Point_8017886C *pPos = (Point_8017886C *)&p->mMotion.mPos;
    int predicted = fn_801208C8(pPos, &target, &velocity, speed);
    Point_8017886C delta;
    fn_80227690(&delta, (Point_8017886C *)&target, pPos);
    int toward = fn_801CFE40(delta.mY, delta.mX);
    if (fn_801486A0() == 0) {
        predicted = fn_801CFFF0(predicted, toward, fn_80237260(0));
    }
    pState->mUnknown8 = 1;
    pState->mUnknown4 = 1.0f;
    pState->mUnknown4 -= fn_801CFFD0(p->mMotion.mFacing, predicted) * 7.152557657263969e-8f;
    pState->mUnknown0 = predicted;
}

void fn_80125708(Object_80039F5C *p, State_80125594 *pState)
{
    Vector_80039F5C target;
    fn_80137D58(fn_801374BC(), &target);
    Object_80039F5C *pOther = fn_80137B40();
    int velocityAngle;
    if (!pOther) {
        Vector_80039F5C velocity;
        fn_80137EC4(fn_801374BC(), &velocity);
        velocityAngle = fn_801CFE40(velocity.mY, velocity.mX);
    } else velocityAngle = pOther->mMotion.mUnknown32;
    Point_8017886C delta;
    fn_80227690(&delta, (Point_8017886C *)&target, (Point_8017886C *)&p->mMotion.mPos);
    float distance = fn_802270A4(&delta);
    int toward = fn_801CFE40(delta.mY, delta.mX);
    int opposite = (toward + 0x800000) & 0xFFFFFF;
    int blockedA = 0, blockedB = 0;
    if ((fn_801CFFD0(velocityAngle, 0x400000) <= 0xFA4F9 && target.mX > fn_80178A08() - 4.0f)
        || (fn_801CFFD0(velocityAngle, 0x800000) <= 0xFA4F9 && target.mY > fn_80178A44() - 4.0f)
        || (fn_801CFFD0(velocityAngle, 0xC00000) <= 0xFA4F9 && target.mX < 4.0f - fn_80178A08())
        || (fn_801CFFD0(velocityAngle, 0) <= 0xFA4F9 && !(target.mY >= 4.0f - fn_80178A44()))) blockedA = 1;
    else if ((fn_801CFFD0(velocityAngle, 0xC00000) <= 0xFA4F9 && target.mX > fn_80178A08() - 4.0f)
        || (fn_801CFFD0(velocityAngle, 0) <= 0xFA4F9 && target.mY > fn_80178A44() - 4.0f)
        || (fn_801CFFD0(velocityAngle, 0x400000) <= 0xFA4F9 && target.mX < 4.0f - fn_80178A08())
        || (fn_801CFFD0(velocityAngle, 0x800000) <= 0xFA4F9 && !(target.mY >= 4.0f - fn_80178A44()))) blockedB = 1;
    int difference = (opposite - velocityAngle) & 0xFFFFFF;
    float offset = 0.0f;
    int side = 0;
    if (difference <= 0x7FFFFF) {
        if (!blockedB) {
            side = 1;
            offset = distance * fn_801CFB18(0x800000 - difference);
            offset += (fn_80237260(0) - 0.5f) * 3.0f;
        }
    } else if (!blockedA) {
        offset = distance * fn_801CFB18(difference - 0x800000);
        offset += (fn_80237260(0) - 0.5f) * 3.0f;
    } else side = 1;
    int angle;
    if (!(offset >= distance * 0.25f)) {
        if (side) angle = (velocityAngle + 0x200000) & 0xFFFFFF;
        else angle = (velocityAngle - 0x200000) & 0xFFFFFF;
    } else angle = fn_801CFFF0(velocityAngle, toward, 0.05f);
    if (fn_801CFFD0(angle, 0) <= 0x3FFFFF && p->mMotion.mPos.mX > fn_80178A08() - 5.0f) angle = toward;
    else if (fn_801CFFD0(angle, 0x400000) <= 0x3FFFFF && p->mMotion.mPos.mY > fn_80178A44() - 5.0f) angle = toward;
    else if (fn_801CFFD0(angle, 0x800000) <= 0x3FFFFF && p->mMotion.mPos.mX < 5.0f - fn_80178A08()) angle = toward;
    else if (fn_801CFFD0(angle, 0xC00000) <= 0x3FFFFF && !(p->mMotion.mPos.mY >= 5.0f - fn_80178A44())) angle = toward;
    pState->mUnknown8 = 1;
    pState->mUnknown4 = 1.0f;
    pState->mUnknown4 -= fn_801CFFD0(p->mMotion.mFacing, angle) * 7.152557657263969e-8f;
    pState->mUnknown0 = angle;
}

void fn_80125B74(Object_80039F5C *p, State_80125594 *pState)
{
    Lookup_8012078C *pLookup = fn_8012078C();
    if (!(p->mFlags & 0x400)) {
        switch (pLookup->mpUnknown12[p->mIdBytes[1]]) {
        case 0: fn_80125594(p, pState); break;
        case 3: fn_80125708(p, pState); break;
        default: fn_80125594(p, pState); break;
        }
        p->mUnknown512.mUnknown15 = pState->mUnknown8;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pState->mUnknown0;
        p->mUnknown512.mUnknown4 = pState->mUnknown0;
        p->mUnknown512.mUnknown0 = pState->mUnknown4;
    }
}

int fn_80125C28(Object_80039F5C *p, State_80125594 *)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Vector_80039F5C target;
    fn_80137D58(fn_801374BC(), &target);
    Point_8017886C delta;
    fn_80227690(&delta, (Point_8017886C *)&target, (Point_8017886C *)&pMotion->mPos);
    int angle = fn_801CFE40(delta.mY, delta.mX);
    int result = 0;
    unsigned int value = 0;
    if (fn_801CFFD0(angle, pMotion->mFacing) <= 0x18E38D) {
        Object_80039F5C *pOther = fn_80137B40();
        float distance = fn_802270A4(&delta);
        result = fn_8012A3B0(p, pOther, target, &value, distance);
    }
    if (result) {
        value = (unsigned int)(value * 0.1f);
        if (fn_802372EC(0, 100) < value && fn_800E815C(p, 0, 0)) return 1;
    }
    return 0;
}

int fn_80125D98(Object_80039F5C *p, State_80125594 *pState)
{
    if (fn_800E1584(p)) return 1;
    if (fn_80125C28(p, pState)) return 1;
    return 0;
}

int fn_80125E20(Object_80039F5C *p)
{
    State_80125594 *pState = (State_80125594 *)&p->mUnknown336;
    if (!fn_80137B40()) {
        Message_800F01CC message;
        fn_801C1F94(&message, 0, sizeof(message));
        message.mId = 57;
        message.mUnknown1[0] = fn_801374D4();
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (!(p->mFlags & 0x400)) {
        fn_80125B74(p, pState);
        if (fn_80125D98(p, pState)) return 0;
    }
    return 0;
}

void fn_80125EC8(int a, int b)
{
    if (b == 65535 && a != 0) {
        float value = 210.0f / lbl_803EA2C4;
        lbl_803EC9E8 = (40.0f / value) * 0.25f;
    }
}

void fn_80125F10(void)
{
    fn_80125EC8(1, 65535);
}

Score_8012430C const lbl_8029F584[7] = {fn_80123594, fn_801237F4, fn_80123E2C, fn_80123E30, fn_80123F48, fn_8012368C, fn_80123C2C};
extern const Directions_8012430C lbl_8029F5A0[6] = {
    {24.0f, -2.0f, -3.0f, -2.0f, 24.0f, 30.0f, 40.0f, 30.0f},
    {0.0f, 0.0f, 4.0f, 15.0f, 45.0f, 30.0f, 40.0f, 30.0f},
    {45.0f, 15.0f, 4.0f, 0.0f, 0.0f, 45.0f, 60.0f, 45.0f},
    {20.0f, 15.0f, -4.0f, -8.0f, -4.0f, 45.0f, 60.0f, 45.0f},
    {-4.0f, -8.0f, -4.0f, 15.0f, 20.0f, 45.0f, 60.0f, 45.0f},
    {0.0f, -5.0f, -6.0f, -5.0f, 0.0f, 85.0f, 200.0f, 85.0f}
};
}
