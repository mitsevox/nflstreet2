#include "game/cu_80136B1C.h"
#include "game/cu_80138CC0.h"
#include "game/fn_802270D4.h"

#include <string.h>

extern "C" {
float fn_80088FFC(Vector_80039F5C *pA0, Vector_80039F5C *pA1, Vector_80039F5C *pB0, Vector_80039F5C *pB1, Vector_80039F5C *pOut);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_80227350(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);

static int lbl_803EB1A8 = 4;
static unsigned char lbl_803EB1AC = 0;

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

float fn_80138F64(Record_8003EC04 *pA, Record_8003EC04 *pB, unsigned char sub, Object_80137ABC *pBall, Vector_80039F5C *pPos, unsigned char *pHit)
{
    Segment_80138CC0 seg;
    Segment_80138CC0 *pSeg;
    Vector_80039F5C step;
    Vector_80039F5C delta;
    float sum;
    float limit;

    memcpy(&seg, &pA->mpUnknown20->mUnknown10, sizeof(seg));
    pSeg = (Segment_80138CC0 *)&pB->mpUnknown20[sub].mUnknown10;
    fn_802276B4(&step, &pBall->mState.mPos, &pBall->mState.mUnknown28);
    sum = seg.mUnknownC + pSeg->mUnknownC;
    limit = sum * sum;
    pPos->mX = pBall->mState.mUnknown28.mX;
    pPos->mY = pBall->mState.mUnknown28.mY;
    pPos->mZ = pBall->mState.mUnknown28.mZ;
    fn_802276B4(&seg.mUnknown0, &seg.mUnknown0, &step);
    fn_802276B4(&seg.mUnknown10, &seg.mUnknown10, &step);
    if (lbl_803EB1AC) {
        *pHit = fn_80138D08(pPos, &seg, pSeg, &step, limit);
    } else {
        *pHit = fn_80138E20(pPos, &seg, pSeg, &step, limit);
    }
    fn_802276B4(&delta, pPos, &pBall->mState.mUnknown28);
    return fn_802270D4(&delta);
}

}
