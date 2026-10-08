#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80227638.h"

extern "C" {
extern unsigned char lbl_803EAEE8;
extern float lbl_803ECB08;
extern float lbl_803ED6CC;
float fn_80237260(int stream);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_8022765C(void *pOut, void *pA, void *pB);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
}

extern "C" void fn_80104944(Object_80039F5C *p, Vector_80039F5C *pOut) {
    float rating = p->mRatings[6] / 255.0f;
    float range = (1.0f - rating * 0.5f) * 2.0f;

    if (lbl_803EAEE8 == 0) {
        pOut->mX += fn_80237260(0) * 2.0f * range - range;
        pOut->mY += fn_80237260(0) * 2.0f * range - range;
    }
}

extern "C" void fn_80104A08(Object_80039F5C *p, int angle, Point_8017886C *pPoint, float *pValue, float scale) {
    if (scale == 0.0f) {
        scale = p->mUnknown560.mUnknown28 / (lbl_803ECB08 * 100621.117f);
    }
    if (scale > 0.0f) {
        Point_8017886C offset;
        float t;

        fn_80227538(&offset, angle, scale * 2.0f * fn_80237260(0));
        offset.mX += fn_80237260(0) + -0.5f;
        offset.mY += fn_80237260(0) + -0.5f;
        fn_80227638(pPoint, pPoint, &offset);
        t = scale * 0.13000001f + 0.02f;
        t = t * 2.0f * fn_80237260(0) - t;
        *pValue *= t + 1.0f;
    }
}

extern "C" void fn_80104B24(Vector_80039F5C *p) {
    p->mY += 1.0f;
}

extern "C" void fn_80104B3C(Object_80039F5C *p, Vector_80039F5C *pOut) {
    State_80039F5C *pState = p->mpState;

    switch (pState->mId) {
    case 68:
    case 90:
        fn_80227538((Point_8017886C *)pOut, (pState->mUnknown2 << 17) & 0xFFFFFF,
                    pState->mUnknown3[0] / 255.0f * lbl_803ECB08 *
                        ((1.0f - lbl_803ED6CC) * 0.75000006f + lbl_803ED6CC));
        fn_8022765C(pOut, pOut, &p->mMotion.mUnknown40);
        fn_80227264(pOut, pOut, 0.5f);
        break;
    default:
        pOut->mX = p->mMotion.mUnknown40;
        pOut->mY = p->mMotion.mUnknown44;
        pOut->mZ = p->mMotion.mUnknown48;
        break;
    }
    pOut->mZ = 0.0f;
}
