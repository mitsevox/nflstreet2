#include "game/Lookup_8012078C.h"
#include "game/Object_80039F5C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/cu_80136B1C.h"

extern "C" {
extern Lookup_8012078C *lbl_803EB09C;
extern int lbl_802DB03C[];
void fn_8011FCA4(void);
int fn_8011FD64(unsigned short index);
int fn_8011F1A4(void);
int fn_801486A0(void);
int fn_80178320(void);
int fn_801783AC(int bit);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);

void fn_8011FE0C(void)
{
    Point_8017886C origin;
    int low = 255;
    int high = 255;
    int team;
    unsigned int count;
    Object_80039F5C *pCarrier;
    short i;

    origin = fn_80177FE0();
    team = fn_80178320();
    fn_8011FCA4();
    count = fn_80178D70(team);
    if (count > 7) count = 7;
    for (i = 0; i < (int)count; i++) {
        lbl_803EB09C->mpUnknown12[i] = 0;
    }
    pCarrier = fn_80137B40();
    if (count <= 1) return;
    for (i = 0; i < (int)count; i++) {
        if (fn_8011FD64(lbl_803EB09C->mpUnknown0[i]) == 2 || fn_801486A0() == 2) {
            Object_80039F5C *p = fn_80039F5C(team, lbl_803EB09C->mpUnknown0[i]);
            if (!(p->mFlags & 0x800) &&
                (!pCarrier || !(p->mMotion.mPos.mY <= pCarrier->mMotion.mPos.mY)) &&
                (p->mUnknown1032 == 0 || p->mUnknown1032 == 8)) {
                low = lbl_803EB09C->mpUnknown0[i];
                break;
            }
        }
    }
    for (i = count - 1; i >= 0; i--) {
        if (fn_8011FD64(lbl_803EB09C->mpUnknown0[i]) == 2 || fn_801486A0() == 2) {
            Object_80039F5C *p = fn_80039F5C(team, lbl_803EB09C->mpUnknown0[i]);
            if (!(p->mFlags & 0x800) &&
                (!pCarrier || !(p->mMotion.mPos.mY <= pCarrier->mMotion.mPos.mY)) &&
                (p->mUnknown1032 == 0 || p->mUnknown1032 == 8)) {
                high = lbl_803EB09C->mpUnknown0[i];
                break;
            }
        }
    }
    if (pCarrier) {
        Vector_80039F5C *pPos = &pCarrier->mMotion.mPos;
        Object_80039F5C *pMiddle;
        int middle;

        if (pPos->mX - origin.mX > 0.0f) {
            lbl_803EB09C->mUnknown19 = 0;
        } else {
            lbl_803EB09C->mUnknown19 = 1;
        }
        middle = ((count + 1) >> 1) - 1;
        pMiddle = fn_80039F5C(team, lbl_803EB09C->mpUnknown4[middle]);
        if (!(pPos->mY >= pMiddle->mMotion.mPos.mY)) {
            if (lbl_803EB09C->mUnknown19 == 0) {
                if (low != 255) {
                    if (count > 2) {
                        lbl_803EB09C->mpUnknown12[low] = 3;
                    } else {
                        lbl_803EB09C->mpUnknown12[low] = 0;
                    }
                }
                if (high != 255) {
                    if (count > 2) {
                        lbl_803EB09C->mpUnknown12[high] = 4;
                    } else {
                        lbl_803EB09C->mpUnknown12[high] = 2;
                    }
                }
            } else {
                if (high != 255) {
                    if (count > 2) {
                        lbl_803EB09C->mpUnknown12[high] = 3;
                    } else {
                        lbl_803EB09C->mpUnknown12[high] = 0;
                    }
                }
                if (low != 255) {
                    if (count > 2) {
                        lbl_803EB09C->mpUnknown12[low] = 4;
                    } else {
                        lbl_803EB09C->mpUnknown12[low] = 2;
                    }
                }
            }
            if (fn_8011F1A4() || fn_801783AC(0)) {
                for (i = 0; i < (int)count; i++) {
                    if (lbl_803EB09C->mpUnknown12[i] == 0 && fn_8011FD64(i)) {
                        lbl_803EB09C->mpUnknown12[i] = 2;
                    }
                }
                for (i = count - 1; i >= 0; i--) {
                    unsigned char index = lbl_803EB09C->mpUnknown8[i].mUnknown4;
                    if (lbl_803EB09C->mpUnknown12[index] == 0 && fn_8011FD64(index) == 0) {
                        lbl_803EB09C->mpUnknown12[index] = 4;
                        break;
                    }
                }
            }
        } else {
            for (i = 0; i < (int)count; i++) {
                lbl_803EB09C->mpUnknown12[i] = 5;
            }
            if (lbl_803EB09C->mUnknown19 == 0) {
                if (low != 255 && !(fn_80039F5C(team, low)->mMotion.mPos.mY <= pCarrier->mMotion.mPos.mY)) {
                    lbl_803EB09C->mpUnknown12[low] = 3;
                }
            } else {
                if (high != 255 && !(fn_80039F5C(team, high)->mMotion.mPos.mY <= pCarrier->mMotion.mPos.mY)) {
                    lbl_803EB09C->mpUnknown12[high] = 3;
                }
            }
        }
    } else {
        if (lbl_803EB09C->mUnknown19 == 0) {
            if (low != 255) lbl_803EB09C->mpUnknown12[low] = 3;
            if (high != 255) lbl_803EB09C->mpUnknown12[high] = 4;
        } else {
            if (high != 255) lbl_803EB09C->mpUnknown12[high] = 3;
            if (low != 255) lbl_803EB09C->mpUnknown12[low] = 4;
        }
        for (i = 0; i < (int)count; i++) {
            if (fn_8011FD64(i) == 1) lbl_803EB09C->mpUnknown12[i] = 2;
        }
    }
}

void fn_80120384(void)
{
    short i;
    int count;
    Vector_80039F5C pos;
    Vector_80039F5C velocity;
    Point_8017886C delta;
    Object_80039F5C *pCarrier;
    int angle;

    fn_8011FCA4();
    count = fn_80178D70(fn_80178320());
    for (i = 0; i < count; i++) {
        lbl_803EB09C->mpUnknown12[i] = 3;
    }
    fn_80137D58(fn_801374BC(), &pos);
    pCarrier = fn_80137B40();
    if (pCarrier) {
        velocity.mX = pCarrier->mMotion.mUnknown40;
        velocity.mY = pCarrier->mMotion.mUnknown44;
        velocity.mZ = pCarrier->mMotion.mUnknown48;
    } else {
        fn_80137EC4(fn_801374BC(), &velocity);
    }
    angle = fn_801CFE40(velocity.mY, velocity.mX);
    for (i = 0; i < count; i++) {
        fn_80227690(&delta, &fn_80039F5C(fn_80178320(), i)->mMotion.mPos, &pos);
        if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), angle) <= 0x238E38) {
            lbl_803EB09C->mpUnknown12[i] = 0;
        }
    }
    for (i = 0; i < count && i <= 1; i++) {
        lbl_803EB09C->mpUnknown12[lbl_803EB09C->mpUnknown8[i].mUnknown4] = 0;
    }
    for (i = 0; i < count; i++) {
        if (lbl_803EB09C->mpUnknown8[i].mUnknown0 < 2.5f) {
            lbl_803EB09C->mpUnknown12[lbl_803EB09C->mpUnknown8[i].mUnknown4] = 0;
        } else if (lbl_803EB09C->mpUnknown8[i].mUnknown0 > 100.0f) {
            lbl_803EB09C->mpUnknown12[lbl_803EB09C->mpUnknown8[i].mUnknown4] = 0;
        }
    }
}

void fn_80120D98(Object_80039F5C *p, Point_8017886C *pMin, Point_8017886C *pMax)
{
    float x = p->mMotion.mPos.mX;
    pMin->mX = x;
    pMin->mY = p->mMotion.mPos.mY;
    pMax->mX = x;
    pMax->mY = pMin->mY;
    for (unsigned char i = 0; lbl_802DB03C[i] != 30; i++) {
        Vector_80039F5C point;
        int angles[3];
        fn_8009BF5C(p, lbl_802DB03C[i], &point, angles);
        float x = point.mX;
        pMax->mX = pMax->mX >= x ? pMax->mX : x;
        pMin->mX = pMin->mX <= x ? pMin->mX : x;
        float y = point.mY;
        pMax->mY = pMax->mY >= y ? pMax->mY : y;
        pMin->mY = pMin->mY <= y ? pMin->mY : y;
    }
}
}
