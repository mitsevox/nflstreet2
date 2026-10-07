#include "game/Object_80039F5C.h"

/* Two points 16 bytes apart; fn_80138CC0 passes both points of two of
   these to fn_80088FFC. */
struct Segment_80138CC0 {
    Vector_80039F5C mUnknown0;
    char mUnknownC[4];
    Vector_80039F5C mUnknown10;
};

extern "C" {
float fn_80088FFC(Vector_80039F5C *pA0, Vector_80039F5C *pA1, Vector_80039F5C *pB0, Vector_80039F5C *pB1, Vector_80039F5C *pOut);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_80227350(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_802276B4(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);

static int lbl_803EB1A8 = 4;

int fn_80138CC0(Segment_80138CC0 *pA, Segment_80138CC0 *pB, float limit)
{
    Vector_80039F5C point;

    return fn_80088FFC(&pA->mUnknown0, &pA->mUnknown10, &pB->mUnknown0, &pB->mUnknown10, &point) < limit;
}

int fn_80138D08(Vector_80039F5C *pOut, Segment_80138CC0 *pA, Segment_80138CC0 *pB, Vector_80039F5C *pStep, float limit)
{
    int result = 0;
    int i;

    fn_80227264(pStep, pStep, 1.0f / lbl_803EB1A8);
    for (i = 0; i < lbl_803EB1A8; i++) {
        fn_8022765C(&pA->mUnknown0, &pA->mUnknown0, pStep);
        fn_8022765C(&pA->mUnknown10, &pA->mUnknown10, pStep);
        if (fn_80138CC0(pA, pB, limit)) {
            if (i == 0) {
                result = 1;
            }
            break;
        }
    }
    fn_80227350(pOut, pStep, i - 1);
    return result;
}

int fn_80138E20(Vector_80039F5C *pPos, Segment_80138CC0 *pA, Segment_80138CC0 *pB, Vector_80039F5C *pStep, float limit)
{
    Vector_80039F5C pos;
    int first;
    int hit;
    int i;

    pos.mX = pPos->mX;
    pos.mY = pPos->mY;
    pos.mZ = pPos->mZ;
    first = fn_80138CC0(pA, pB, limit);
    hit = first;
    for (i = 0; i < lbl_803EB1A8; i++) {
        fn_80227264(pStep, pStep, 0.5f);
        if (hit == 0) {
            fn_8022765C(&pos, &pos, pStep);
            fn_8022765C(&pA->mUnknown0, &pA->mUnknown0, pStep);
            fn_8022765C(&pA->mUnknown10, &pA->mUnknown10, pStep);
        } else {
            fn_802276B4(&pos, &pos, pStep);
            fn_802276B4(&pA->mUnknown0, &pA->mUnknown0, pStep);
            fn_802276B4(&pA->mUnknown10, &pA->mUnknown10, pStep);
        }
        hit = fn_80138CC0(pA, pB, limit);
        if (hit == 0) {
            pPos->mX = pos.mX;
            pPos->mY = pos.mY;
            pPos->mZ = pos.mZ;
        }
    }
    return first;
}

}
