#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80177FE0.h"
#include <math.h>

/* 16-byte zone records at +24 of the block fn_8011F4EC returns. */
struct Zone_8011569C {
    float mUnknown0;
    float mUnknown4;
    float mLow;
    float mHigh;
};

struct Field_8011569C {
    char mUnknown0[24];
    Zone_8011569C mZones[1];
};

/* View of the block at player +336 used by fn_80117AA4. */
struct State_80117AA4 {
    char mUnknown0[17];
    unsigned char mUnknown17;
    char mUnknown18[2];
    Object_80039F5C *mpUnknown20;
};

extern "C" {
int fn_80178308(void);
float fn_80178A2C(void);
void *fn_8011F4EC(void);
void fn_8009E9EC(Object_80039F5C *p, int side, Point_8017886C *pOut);
int fn_8009EAB0(Object_80039F5C *p, int a);
Object_80039F5C *fn_8009EC60(unsigned int index, Point_8017886C *pOut);
Object_80039F5C *fn_8009EDD4(unsigned int index, int side, Point_8017886C *pOut);
int fn_8009EFDC(int side);
void fn_8009F928(Object_80039F5C *p, Point_8017886C *pSpot, int a, unsigned char flag);
int fn_8009FD7C(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_80168E00(int team, int index, unsigned char *pOut);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80227890(void *pA, void *pB);
int fn_80117494(Object_80039F5C *p, Point_8017886C *out);
Object_80039F5C *fn_80117794(int index);
Object_80039F5C *fn_80117934(void);
extern unsigned char lbl_803EB010;
extern float lbl_803EAFD0;
extern float lbl_803EAFD4;
extern float lbl_803EAFD8;
extern float lbl_803EAFDC;
extern unsigned short lbl_803EAFE0;
}

extern "C" void fn_80117AA4(Object_80039F5C *p, Point_8017886C *pOut, float *pSpeed)
{
    float speed = 0.6f;
    State_80117AA4 *pState = (State_80117AA4 *)&p->mUnknown336;
    Point_8017886C zone;
    unsigned char numPlayers = 0;
    unsigned char numBelow = 0;
    unsigned char numAbove = 0;
    Object_80039F5C *pOther = 0;
    Object_80039F5C *pMark;
    unsigned char side;
    int count;

    fn_80177FE0();
    side = p->mpState->mUnknown1 + 14;
    fn_8009E9EC(p, side, &zone);
    Zone_8011569C *pZone = &((Field_8011569C *)fn_8011F4EC())->mZones[side];
    float high = pZone->mHigh;
    float low = pZone->mLow;
    float top = pZone->mUnknown0;
    float bottom = pZone->mUnknown4;
    pOut->mX = p->mMotion.mPos.mX;
    pOut->mY = p->mMotion.mPos.mY;
    if (p == 0 || pOut == 0) return;

    count = fn_8009EAB0(p, side);
    if (count != 1) {
        pState->mUnknown17 = 0;
    }
    if (count == 0) {
        pState->mpUnknown20 = 0;
        if (!fn_80117494(p, pOut)) {
            if (fn_8009EFDC(side) || lbl_803EB010) {
                if (fn_8009EFDC(side)) {
                    pMark = fn_80117794(side);
                } else {
                    pMark = fn_80117934();
                }
                if (pMark) {
                    if (fn_8009EFDC(side)) {
                        pOut->mX = pMark->mMotion.mPos.mX;
                    } else {
                        pOut->mX = zone.mX;
                    }
                    pOut->mY = pMark->mMotion.mPos.mY >= zone.mY ? pMark->mMotion.mPos.mY : zone.mY;
                } else {
                    float minX = 100.0f;
                    float maxX = -100.0f;
                    unsigned char i;
                    for (i = 0; i <= 2; i++) {
                        int index = fn_80168E00(fn_80178308(), i, 0);
                        if (index != 0xFF) {
                            numPlayers++;
                            pMark = fn_80039F5C(fn_80178308(), index);
                            if (pMark->mMotion.mPos.mX > high) {
                                numAbove++;
                            } else if (pMark->mMotion.mPos.mX < low) {
                                numBelow++;
                            }
                            if (pMark->mMotion.mPos.mX < minX) {
                                minX = pMark->mMotion.mPos.mX;
                            }
                            if (pMark->mMotion.mPos.mX < maxX) {
                                maxX = pMark->mMotion.mPos.mX;
                            }
                        }
                    }
                    if (numPlayers == 0) {
                        minX = -7.0f;
                        maxX = 7.0f;
                    }
                    if (numPlayers != 0 && numBelow == numPlayers) {
                        pOut->mX = low + lbl_803EAFD8;
                    } else if (numPlayers != 0 && numAbove == numPlayers) {
                        pOut->mX = high - lbl_803EAFD8;
                    } else if (fn_8009EFDC(side)) {
                        if (zone.mX < fn_80177FE0().mX) {
                            pOut->mX = minX;
                        } else {
                            pOut->mX = maxX;
                        }
                    } else {
                        pOut->mX = zone.mX;
                    }
                    pOut->mY = zone.mY;
                }
            } else {
                pOut->mX = zone.mX;
                pOut->mY = zone.mY;
            }
            speed = 0.6f;
        }
        pOut->mX = pOut->mX < low + lbl_803EAFD8 ? low + lbl_803EAFD8
                 : (pOut->mX > high - lbl_803EAFD8 ? high - lbl_803EAFD8 : pOut->mX);
        pOut->mY = pOut->mY < bottom + lbl_803EAFD4 ? bottom + lbl_803EAFD4
                 : (pOut->mY > top - lbl_803EAFD4 ? top - lbl_803EAFD4 : pOut->mY);
    } else {
        if (!fn_8009EFDC(side)) {
            pOther = fn_8009EC60(0, pOut);
        } else {
            pOther = fn_8009EDD4(0, side, pOut);
        }
        if (pOther->mpState->mId != 20) {
            pState->mUnknown17 = 0;
        } else if (pState->mUnknown17 == 0) {
            pState->mUnknown17 = fn_8009FD7C(p, pOther);
        }
        fn_8009F928(pOther, pOut, 30, pState->mUnknown17);
        if (fn_8009EFDC(side)) {
            if (zone.mX < fn_80177FE0().mX) {
                pOut->mX += 1.0f;
            } else {
                pOut->mX -= 1.0f;
            }
        }
        Point_8017886C delta;
        fn_80227690(&delta, &p->mMotion.mPos, pOut);
        if (fn_801CFFD0(delta.Heading(), pOther->mMotion.mUnknown32) > (int)(lbl_803EAFE0 * 46603.38f)) {
            speed = 0.8f;
        } else if (delta.mY <= 0.0f) {
            pOut->mX = p->mMotion.mPos.mX;
            speed = 0.8f;
        } else {
            pOut->mY = p->mMotion.mPos.mY;
            if (fn_80227890(&p->mMotion.mPos, pOut) < lbl_803EAFDC) {
                pOut->mY += 2.0f;
            }
            speed = 0.8f;
        }
        pOut->mX = pOut->mX < low + lbl_803EAFD8 ? low + lbl_803EAFD8
                 : (pOut->mX > high - lbl_803EAFD8 ? high - lbl_803EAFD8 : pOut->mX);
        pOut->mY = pOut->mY < bottom + lbl_803EAFD4 ? bottom + lbl_803EAFD4
                 : (pOut->mY > top - lbl_803EAFD4 ? top - lbl_803EAFD4 : pOut->mY);
    }
    if (pOut->mY > fn_80178A2C() + lbl_803EAFD0) {
        pOut->mY = fn_80178A2C() + lbl_803EAFD0;
    }
    if (fabsf(p->mMotion.mPos.mX) < 4.0f) {
        pOut->mY = pOut->mY < zone.mY ? zone.mY : pOut->mY;
    }
    if (p->mMotion.mPos.mX <= low || p->mMotion.mPos.mX >= high
        || p->mMotion.mPos.mY <= bottom || p->mMotion.mPos.mY >= top) {
        speed = 1.0f;
    }
    if (pSpeed) {
        *pSpeed = speed;
    }
    pState->mpUnknown20 = pOther;
}
