#include "game/Object_80039F5C.h"
#include "game/fn_801C1F94.h"

extern "C" {
extern float lbl_803EA2C4;

int fn_800AD9B4(void);
void fn_800B26B0(Object_800B26B0 *pObject);
void fn_800B26E0(Object_800B26B0 *pObject);
void fn_800B2A14(Object_800B26B0 *pObject, unsigned char *a);
void fn_800B2D9C(Object_800B26B0 *pObject);
float fn_800C4914(Object_80039F5C *p, float value);
float fn_800C495C(Object_80039F5C *p, float value);
void fn_800CA8F4(Object_80039F5C *p);
int fn_800DC080(Object_80039F5C *p);
int fn_8011E9B4(Object_80039F5C *p);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, int a, unsigned char b, int angle, float *pOut, int c);
int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, int a);
Object_80039F5C *fn_80137B40(void);
void fn_8016BDCC(Object_80039F5C *p);
void fn_8016BE10(Object_80039F5C *p);
void fn_8016C3FC(Object_80039F5C *p);
void fn_8016C434(Object_80039F5C *p);
void fn_8016C550(Object_80039F5C *p);
void fn_8016C70C(Object_80039F5C *p);
void fn_8016CA50(Object_80039F5C *p);
int fn_8016CDD4(Object_80039F5C *p);
void fn_8016CEEC(Object_80039F5C *p);
void fn_8016CF00(Object_80039F5C *p);
int fn_80178308(void);
unsigned int fn_80178D18(int a);
float fn_801CFB18(int angle);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
}

static unsigned short lbl_803EB428 = 30;

float lbl_803ECB04 = 40.0f / (210.0f / lbl_803EA2C4);
float lbl_803ECB08 = lbl_803ECB04;
float lbl_803ECB0C = lbl_803ECB04;
float lbl_803ECB10 = lbl_803ECB04;
static float lbl_803ECB14 = lbl_803ECB04 * 0.15f;
static float lbl_803ECB18 = lbl_803EA2C4 * 0.0125f;
static float lbl_803ECB1C = lbl_803EA2C4 * 0.009f;
static float lbl_803ECB20 = lbl_803EA2C4 * 0.0036f;

static void (*const lbl_802A4E08[])(Object_80039F5C *) = {
    fn_8016CEEC, fn_8016C3FC, fn_8016C434, fn_8016C70C, fn_8016CA50, fn_8016BE10,
    fn_8016CF00, fn_8016CF00, fn_8016C70C, fn_8016C550, fn_8016C3FC,
};

extern "C" {
void fn_8016CEEC(Object_80039F5C *p)
{
    p->mMotion.mUnknown52 = 0.0f;
    p->mUnknown512.mUnknown0 = 0.0f;
}

void fn_8016CF00(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion = &p->mMotion;

    pMotion->mUnknown52 = 0.0f;
    if (p->mUnknown544 != 0 && p->mUnknown545 == 0) {
        pMotion->mFacing = (pMotion->mFacing + p->mUnknown548) & 0xFFFFFF;
    }
}

void fn_8016CF40(Object_80039F5C *p)
{
    int reverse = 0;
    Object_8016D8B0 *pInput = &p->mUnknown528;
    Object_800B26B0 *pMotion = &p->mMotion;
    int turn = fn_801CFFD0(pInput->mUnknown4, pInput->mUnknown8);
    float sign = 1.0f;
    float speed;
    float limit;

    if (p->mUnknown1032 == 4) {
        speed = lbl_803ECB14 * p->mUnknown528.mUnknown0;
        limit = lbl_803ECB14;
    } else if (turn <= 0x2E38E2) {
        speed = lbl_803ECB08 * p->mUnknown528.mUnknown0;
        limit = lbl_803ECB08 - fn_801CFB18(turn) * (lbl_803ECB08 / 2.0f);
        if (pInput->mUnknown4 != p->mUnknown512.mUnknown4) {
            reverse = 1;
        }
        if (fn_800AD9B4() == 3 && p->mUnknown528.mUnknown0 == 0.0f) {
            reverse = 1;
        }
    } else if (fn_800DC080(p) == 0) {
        if (turn <= 0x56C16B) {
            speed = lbl_803ECB0C * p->mUnknown528.mUnknown0;
            limit = lbl_803ECB0C - fn_801CFB18(0x56C16C - turn) * (lbl_803ECB0C / 2.0f);
        } else {
            speed = lbl_803ECB10 * p->mUnknown528.mUnknown0;
            limit = lbl_803ECB10 - fn_801CFB18(0x80B60C - turn) * (lbl_803ECB10 / 2.0f);
        }
    } else {
        limit = speed = lbl_803ECB10 * p->mUnknown528.mUnknown0;
    }
    if (reverse) {
        sign = -sign;
    }
    limit *= 5.0f;
    if (pInput->mUnknown14 == 2 || p->mUnknown1032 == 4) {
        pMotion->mUnknown36 = speed * (191.25f / 255.0f * 0.38f + 0.62f);
        pMotion->mUnknown36 = pMotion->mUnknown36 <= limit ? pMotion->mUnknown36 : limit;
        pMotion->mUnknown52 = lbl_803ECB20 * (191.25f / 510.0f + 0.5f) * sign;
    } else {
        pMotion->mUnknown36 = speed * (((p->mId & 0xFF) == 1 ? p->mRatings[4] : 191.25f) / 255.0f * 0.38f + 0.62f);
        pMotion->mUnknown36 = pMotion->mUnknown36 <= limit ? pMotion->mUnknown36 : limit;
        switch (pInput->mUnknown14) {
        case 9:
            pMotion->mUnknown52 = lbl_803ECB18 * (((p->mId & 0xFF) == 1 ? p->mRatings[4] : 191.25f) / 510.0f + 0.5f) * sign;
            break;
        case 10:
            pMotion->mUnknown36 = lbl_803ECB08;
            pMotion->mUnknown52 = 0.0f;
            pMotion->mUnknown60 = pInput->mUnknown0 * 0.0036f;
            break;
        default:
            pMotion->mUnknown52 = lbl_803ECB1C + (lbl_803ECB18 - lbl_803ECB1C) * pInput->mUnknown0;
            pMotion->mUnknown52 = pMotion->mUnknown52 * (((p->mId & 0xFF) == 1 ? p->mRatings[4] : 191.25f) / 510.0f + 0.5f) * sign;
            break;
        }
    }
    pMotion->mUnknown36 = fn_800C495C(p, pMotion->mUnknown36);
    pMotion->mUnknown52 = fn_800C4914(p, pMotion->mUnknown52);
    if (fn_8016CDD4(p)) {
        float cap = lbl_803ECB08 * pInput->mUnknown0;

        pMotion->mUnknown36 = pMotion->mUnknown36 <= cap ? pMotion->mUnknown36 : cap;
        pMotion->mUnknown52 = lbl_803ECB18;
    }
}

void fn_8016D344(Object_80039F5C *p)
{
    float delta[2];
    float distance;

    if (fn_801CFFD0(0x400000, p->mMotion.mFacing) < 0x355555 && p == fn_80137B40()) {
        int team = fn_80178308();
        Object_80039F5C *pOther = fn_801245DC(p, team, 0, fn_80178D18(fn_80178308()), 0x355555, &distance, 0);

        if (pOther && distance < 2.0f && !(pOther->mFlags & 0x800) && fn_8011E9B4(pOther)) {
            int angle;

            fn_80227690(delta, &pOther->mMotion, &p->mMotion);
            angle = fn_801CFE40(delta[1], delta[0]);
            if (distance < 2.0f - fn_801CFFD0(angle, p->mMotion.mFacing) / 3495253.0f &&
                fn_80124714(p, pOther, 0)) {
                if (((angle - p->mUnknown512.mUnknown4) & 0xFFFFFF) <= 0x7FFFFF) {
                    if (p->mUnknown776 == 2) {
                        p->mUnknown528.mUnknown15 = 3;
                    } else {
                        p->mUnknown528.mUnknown15 = 2;
                    }
                } else {
                    if (p->mUnknown776 == 2) {
                        p->mUnknown528.mUnknown15 = 2;
                    } else {
                        p->mUnknown528.mUnknown15 = 3;
                    }
                }
            }
        }
    }
}

void fn_8016D4D8(Object_80039F5C *p)
{
    Object_8016D8B0 *pRequest = &p->mUnknown512;
    Object_8016D8B0 *pInput = &p->mUnknown528;
    Object_800B26B0 *pMotion = &p->mMotion;
    float limit;

    p->mUnknown512.mUnknown0 = p->mUnknown512.mUnknown0 >= 0.0f ? p->mUnknown512.mUnknown0 : 0.0f;
    pInput->mUnknown15 = 0;
    fn_800CA8F4(p);
    if (pRequest->mUnknown15 == 0 || pInput->mUnknown12 == lbl_803EB428) {
        if (p->mFlags & 0x4000) {
            if (pInput->mUnknown12 != 0) {
                if (fn_801CFFD0(pMotion->mUnknown32, pRequest->mUnknown4) <= 0x11C71B) {
                    pInput->mUnknown12--;
                    pRequest->mUnknown15 = 1;
                } else {
                    pInput->mUnknown12 = 0;
                }
            }
        } else {
            pInput->mUnknown12 = 0;
        }
    } else {
        pInput->mUnknown12 = 0;
    }
    switch (pRequest->mUnknown15) {
    case 28:
        pInput->mUnknown15 = 28;
        pInput->mUnknown0 = pRequest->mUnknown0 <= 0.25f ? pRequest->mUnknown0 : 0.25f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 29:
        pInput->mUnknown15 = 29;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 23:
        pInput->mUnknown15 = 23;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.98f ? pInput->mUnknown0 : 0.98f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 1:
    case 5:
    case 11:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 1.0f ? pInput->mUnknown0 : 1.0f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        if (p == fn_80137B40()) {
            pInput->mUnknown0 = pInput->mUnknown0 <= 0.98f ? pInput->mUnknown0 : 0.98f;
            pRequest->mUnknown0 = pInput->mUnknown0;
            if (pInput->mUnknown15 == 1) {
                fn_8016D344(p);
            }
        }
        break;
    case 8:
    case 9:
        limit = pRequest->mUnknown15 == 8 ? 0.65f : 0.92f;
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= limit ? pInput->mUnknown0 : limit;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 6:
    case 7:
        limit = pRequest->mUnknown15 == 6 ? 0.65f : 0.92f;
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= limit ? pInput->mUnknown0 : limit;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 13:
    case 14:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.7f ? pInput->mUnknown0 : 0.7f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 24:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.8f ? pInput->mUnknown0 : 0.8f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 25:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 1.0f ? pInput->mUnknown0 : 1.0f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 12:
        pInput->mUnknown15 = 12;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.7f ? pInput->mUnknown0 : 0.7f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 15:
    case 16:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.72f ? pInput->mUnknown0 : 0.72f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 20:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.65f ? pInput->mUnknown0 : 0.65f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 21:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.92f ? pInput->mUnknown0 : 0.92f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 26:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.55f ? pInput->mUnknown0 : 0.55f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 27:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 1.0f ? pInput->mUnknown0 : 1.0f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 0:
    case 10:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.72f ? pInput->mUnknown0 : 0.72f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        if (pRequest->mUnknown15 == 0) {
            fn_8016D344(p);
        }
        break;
    case 30:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 1.0f ? pInput->mUnknown0 : 1.0f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 2:
    case 3:
    case 4:
    case 18:
    case 19:
    case 22:
        pInput->mUnknown15 = pRequest->mUnknown15;
    default:
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.72f ? pInput->mUnknown0 : 0.72f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    }
    pRequest->mUnknown15 = 0;
}

void fn_8016D8B0(Object_8016D8B0 *pObject)
{
    fn_801C1F94(pObject, 0, sizeof(*pObject));
    pObject->mUnknown14 = 0;
    pObject->mUnknown15 = 0;
}

void fn_8016D8F0(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion = &p->mMotion;

    fn_800B26B0(pMotion);
    fn_8016D4D8(p);
    if (lbl_802A4E08[p->mUnknown528.mUnknown14] != fn_8016CEEC) {
        fn_8016CF40(p);
    }
    lbl_802A4E08[p->mUnknown528.mUnknown14](p);
    if (p->mUnknown545 == 0) {
        fn_8016BDCC(p);
        fn_800B26E0(pMotion);
    } else {
        fn_800B2A14(pMotion, &p->mUnknown544);
    }
    if (p->mFlags & 0x100) {
        p->mFlags &= ~0x100;
        fn_800B2D9C(&p->mMotion);
    }
    p->mUnknown528.mUnknown14 = 0;
    p->mUnknown512.mUnknown14 = 0;
    p->mpUnknown796->mUnknown8 = p->mMotion.mFacing;
}

void fn_8016D9D0(Object_8016D8B0 *pObject)
{
    pObject->mUnknown4 = (pObject->mUnknown4 + 0x800000) & 0xFFFFFF;
    pObject->mUnknown8 = (pObject->mUnknown8 + 0x800000) & 0xFFFFFF;
}

float fn_8016D9F4(Object_80039F5C *p, float a, float b)
{
    float speed = a <= b ? a : b;

    speed *= lbl_803ECB08;
    return speed * (p->mRatings[4] / 255.0f * 0.38f + 0.62f);
}

void fn_8016DA5C(Object_80039F5C *p)
{
    if (!(p->mFlags & 0x4000) && (p->mUnknown528.mUnknown15 == 1 || p->mUnknown512.mUnknown15 == 1) &&
        p->mUnknown528.mUnknown12 == 0) {
        p->mUnknown528.mUnknown12 = lbl_803EB428;
    }
}

void fn_8016DA98(Object_80039F5C *p)
{
    p->mUnknown528.mUnknown12 = 0;
}

int fn_8016DAA4(Object_80039F5C *p)
{
    return fn_801CFFD0(p->mMotion.mFacing, p->mMotion.mUnknown32) <= 0x200000;
}
}
