#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_800F06F4.h"
#include "game/Lookup_8012078C.h"

/* One of the 24 four-float boxes fn_8009E674 lays out at +0x18 of
   State_8011F4EC. */
struct Box_8009E674 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
};

/* Object whose address fn_8011F4EC returns. Only the accessed bytes are
   declared; the size is not established. */
struct State_8011F4EC {
    int mUnknown0;
    int mUnknown4[2];
    int mUnknownC;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned char mUnknown12[2];
    unsigned short mUnknown14;
    unsigned char mUnknown16[2];
    Box_8009E674 mUnknown18[24];
    unsigned char mUnknown198;
    unsigned char mUnknown199[3];
    unsigned char mUnknown19C[3];
    unsigned char mUnknown19F[3];
    unsigned char mUnknown1A2;
    unsigned char mUnknown1A3[5];
    unsigned char mUnknown1A8;
    unsigned char mUnknown1A9;
    unsigned char mUnknown1AA[2];
    float mUnknown1AC[3];
    unsigned char mUnknown1B8[3];
    unsigned char mUnknown1BB[3];
    unsigned char mUnknown1BE[3];
    unsigned char mUnknown1C1[3];
    unsigned char mUnknown1C4;
    unsigned char mUnknown1C5;
};

extern "C" float fn_80178A2C(void);

extern "C" {
float fn_80178A08(void);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801BE648(void *p);
int fn_801486A0(void);
int fn_8009F058(Object_80039F5C *p, Object_80039F5C *pOther, int angle);
int fn_801783AC(int bit);
int fn_8011F1CC(void);
unsigned int fn_8011E188(void);
State_8011F4EC *fn_8011F4EC(void);
Object_80039F5C *fn_8009BCE8(int *pRef);
int fn_800AC218(int team);
int fn_800AC268(int team);
void fn_8009E674(void);
float fn_80178A44(void);
int fn_8011F2C4(void);
int fn_8011F1A4(void);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
float fn_80237260(int stream);
extern float lbl_803EA9AC;
extern float lbl_803EA9B0;
extern float lbl_803EA9B4;
extern float lbl_803EA9B8;
extern Point_8017886C lbl_802DA728[10];
extern Point_8017886C lbl_802DA778[10];
Object_80039F5C *fn_80137B40(void);
 float fn_802270A4(void *);
}

extern "C" int fn_8009DD88(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;

    if (p != 0 && pOther != 0 && fn_80237260(0) < p->mRatings[8] / 255.0f
        && fn_8009F058(p, pOther, 0x400000) != 0) {
        Object_80039F5C *pCarrier = fn_80137B40();

        if (pCarrier != 0) {
            Point_8017886C carrierDelta;
            Point_8017886C otherDelta;
            float carrierDistance;
            float otherDistance;

            fn_80227690(&carrierDelta, &pCarrier->mMotion.mPos, &p->mMotion.mPos);
            fn_80227690(&otherDelta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            carrierDistance = fn_802270A4(&carrierDelta);
            otherDistance = fn_802270A4(&otherDelta);
            if (carrierDistance > 3.0f) {
                result = carrierDistance > otherDistance;
            }
        }
    }
    return result;
}

extern "C" int fn_8009E180(Object_80039F5C *p)
{
    int check = 0;
    Object_80137ABC *pBall = fn_801374BC();
    Object_80039F5C *pCarrier = fn_80137B40();

    if (pCarrier != 0) {
        if (pCarrier->mIdBytes[3] == 1) {
            int pending;

            if (fn_801783AC(0) == 1) {
                return 6;
            }
            pending = fn_800F06F4(0, pCarrier->mpState, 18, 0xFFFF);
            if (pending != 0xFFFF || fn_800F06F4(0, pCarrier->mpState, 15, 0xFFFF) != pending
                || fn_8011F2C4() != 0) {
                Object_80039F5C *pTarget;
                Point_8017886C ball;

                if (pCarrier->mFlags & 0x8000) {
                    return 2;
                }
                pTarget = fn_8009BCE8(&p->mUnknown1036);
                if (pTarget != 0 && (pTarget->mUnknown1052 == 2 || pTarget->mUnknown1052 == 3)) {
                    unsigned int limit = fn_800AC268(p->mIdBytes[2]);
                    Lookup_8012078C *pLookup = fn_8012078C();

                    if (pLookup->mpUnknown4[0] != p->mIdBytes[1] && pLookup->mpUnknown4[1] != p->mIdBytes[1]) {
                        int kind = pLookup->mpUnknown12[p->mIdBytes[1]];

                        if ((kind == 2 || kind == 0) && fn_8011E188() > limit) {
                            check = 1;
                        }
                    }
                }
                ball = fn_80177FE0();
                if (p->mpState->mId == 30 && p->mMotion.mPos.mY < ball.mY - 1.0f) {
                    if (fn_8011F1CC() != 0) {
                        return 4;
                    }
                    if (fn_8011F1A4() != 0) {
                        return 5;
                    }
                }
            } else if (fn_801BE648(pCarrier->mpUnknown792) != 34) {
                check = 1;
            }
            if (check != 0) {
                unsigned int limit = fn_800AC218(p->mIdBytes[2]);
                int kind = fn_8012078C()->mpUnknown12[p->mIdBytes[1]];
                Object_80039F5C *pHolder;

                if (kind == 4) {
                    limit += 15;
                } else if (kind == 3) {
                    limit += 6;
                }
                pHolder = fn_80137AD0(pBall);
                if (fn_8011F1A4() != 0 && (pHolder->mUnknown2914 != 0 || pHolder->mpState->mId == 91)) {
                    limit /= 2;
                }
                if (fn_80137F88(pBall) > limit) {
                    return 5;
                }
            }
        }
    } else {
        switch (fn_8013BA58(pBall, 0)) {
        case 4:
            if (fn_80137B88(fn_801374BC()) != 0 || fn_801486A0() == 1) {
                return 4;
            }
            break;
        case 2:
            break;
        case 3:
            if (fn_801783AC(0) == 1) {
                return 6;
            }
            if (fn_8011F2C4() != 0) {
                return 1;
            }
            return 3;
        default:
            return 6;
        }
    }
    return 0;
}

extern "C" void fn_8009E674(void)
{
    State_8011F4EC *p = fn_8011F4EC();
    Box_8009E674 *pBoxes;
    Vector_80039F5C pos;
    Point_8017886C ball;
    float offset;
    int i;

    fn_80137D58(fn_801374BC(), &pos);
    pBoxes = p->mUnknown18;
    ball = fn_80177FE0();
    p->mUnknown14 = 12;
    if (pos.mX > fn_80178A08() * 0.5f) {
        pos.mX = fn_80178A08() * 0.5f;
    } else if (pos.mX < -fn_80178A08() * 0.5f) {
        pos.mX = -fn_80178A08() * 0.5f;
    }
    offset = pos.mX * 0.25f;
    for (i = 0; i < 10; i++) {
        pBoxes[i].mUnknown0 = fn_80178A44();
        pBoxes[i].mUnknown4 = ball.mY + lbl_803EA9AC;
        pBoxes[i].mUnknown8 = lbl_802DA778[i].mX * fn_80178A08();
        pBoxes[i].mUnknownC = lbl_802DA778[i].mY * fn_80178A08();
    }
    if (ball.mY < fn_80178A2C() - 5.0f) {
        pBoxes[10].mUnknown0 = pBoxes[11].mUnknown0 = ball.mY + 10.5f;
    } else {
        pBoxes[10].mUnknown0 = pBoxes[11].mUnknown0 = fn_80178A2C() + 7.0f;
    }
    pBoxes[10].mUnknown4 = pBoxes[11].mUnknown4 = ball.mY - 5.5f;
    pBoxes[10].mUnknown8 = -fn_80178A08();
    pBoxes[10].mUnknownC = offset - 8.0f;
    pBoxes[11].mUnknown8 = offset + 8.0f;
    pBoxes[11].mUnknownC = fn_80178A08();
    if (ball.mY < fn_80178A2C() - 8.0f) {
        pBoxes[12].mUnknown0 = pBoxes[13].mUnknown0 = ball.mY + 10.0f;
    } else {
        pBoxes[12].mUnknown0 = pBoxes[13].mUnknown0 = fn_80178A2C() + 7.0f;
    }
    pBoxes[12].mUnknown4 = pBoxes[13].mUnknown4 = ball.mY - 7.0f;
    pBoxes[12].mUnknown8 = -fn_80178A08();
    pBoxes[12].mUnknownC = offset - 8.0f;
    pBoxes[13].mUnknown8 = offset + 8.0f;
    pBoxes[13].mUnknownC = fn_80178A08();
    for (i = 14; i < 24; i++) {
        pBoxes[i].mUnknown4 = ball.mY + lbl_803EA9B8;
        pBoxes[i].mUnknown0 = ball.mY + lbl_803EA9B4 > fn_80178A2C() + lbl_803EA9B0
                                  ? fn_80178A2C() + lbl_803EA9B0
                                  : ball.mY + lbl_803EA9B4;
        pBoxes[i].mUnknown8 = lbl_802DA728[i - 14].mX;
        pBoxes[i].mUnknownC = lbl_802DA728[i - 14].mY;
        pBoxes[i].mUnknown8 = pBoxes[i].mUnknown8 < -fn_80178A08() ? -fn_80178A08() : pBoxes[i].mUnknown8;
        pBoxes[i].mUnknownC = pBoxes[i].mUnknownC > fn_80178A08() ? fn_80178A08() : pBoxes[i].mUnknownC;
    }
}
