/* Curve lists: keyed Hermite and Bezier curves evaluated over a time range, with clamp or wrap past the end. */

#include "engine/fn_801F7BD4.h"

typedef struct CurveKey_801C4F64 {
    unsigned int mFlags;
    float mValue;
    float mTime;
} CurveKey_801C4F64;

typedef struct HermiteKey_801C4F64 {
    unsigned int mFlags;
    float mValue;
    float mTime;
    float mCoef[4];
} HermiteKey_801C4F64;

typedef struct BezierKey_801C4F64 {
    unsigned int mFlags;
    float mValue;
    float mTime;
    float mEndTime;
    float mX[4];
    float mY[4];
} BezierKey_801C4F64;

typedef struct CurveList_801C4F64 {
    unsigned short mType;
    unsigned short mCount;
    float mStart;
    float mEnd;
    void *mpKeys;
} CurveList_801C4F64;

extern unsigned char lbl_803EBBE8;

int fn_801C5740(float *pCoef, int degree, int includeLo, int includeHi, float *pRoots, float lo, float hi);

float fn_801C52CC(float t, float t0, float a, float b, float c, float d);
float fn_801C52E0(float t, float t0, float t1, float x0, float x1, float x2, float x3, float y0, float y1, float y2,
                  float y3);

int fn_801C4F64(void)
{
    int error = 0;

    if (lbl_803EBBE8) {
        error = 0x1E0001;
    } else {
        lbl_803EBBE8 = 1;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C4FB8(void)
{
    int error = 0;

    if (lbl_803EBBE8) {
        lbl_803EBBE8 = 0;
    } else {
        error = 0x1E0002;
    }
    fn_801F7BD4(error);
    return error;
}

static float fn_801C5008(CurveList_801C4F64 *pList, float t, int mode)
{
    HermiteKey_801C4F64 *pKeys = pList->mpKeys;
    HermiteKey_801C4F64 *pKey = pKeys;
    float start;
    float end;
    unsigned int i = 0;

    if (pList->mCount == 0) {
        return 0.0f;
    }
    start = pList->mStart;
    if (t < start) {
        return pKey->mValue;
    }
    end = pList->mEnd;
    if (!(t <= end) && mode == 0) {
        return pKeys[pList->mCount - 1].mValue;
    } else if (!(t <= end) && mode == 1) {
        end -= start;
        t -= (float)(int)(t / end) * end;
    }
    while (i < pList->mCount && !(t < pKeys[i].mTime)) {
        pKey = &pKeys[i];
        i++;
    }
    if (pKey->mFlags & 0xFFFF0000) {
        return pKey->mValue;
    }
    return fn_801C52CC(t, pKey->mTime, pKey->mCoef[0], pKey->mCoef[1], pKey->mCoef[2], pKey->mCoef[3]);
}

static float fn_801C5130(CurveList_801C4F64 *pList, float t, int mode)
{
    BezierKey_801C4F64 *pKeys = pList->mpKeys;
    BezierKey_801C4F64 *pKey = pKeys;
    float start;
    float end;
    unsigned int i = 0;

    if (pList->mCount == 0) {
        return 0.0f;
    }
    start = pList->mStart;
    if (t < start) {
        return pKey->mValue;
    }
    end = pList->mEnd;
    if (!(t <= end) && mode == 0) {
        return pKeys[pList->mCount - 1].mValue;
    } else if (!(t <= end) && mode == 1) {
        end -= start;
        t -= (float)(int)(t / end) * end;
    }
    while (i < pList->mCount && !(t < pKeys[i].mTime)) {
        pKey = &pKeys[i];
        i++;
    }
    if (pKey->mFlags & 0xFFFF0000) {
        return pKey->mValue;
    }
    return fn_801C52E0(t, pKey->mTime, pKey->mEndTime, pKey->mX[0], pKey->mX[1], pKey->mX[2], pKey->mX[3], pKey->mY[0],
                       pKey->mY[1], pKey->mY[2], pKey->mY[3]);
}

float fn_801C5278(CurveList_801C4F64 *pList, float t, int mode)
{
    float result = 0.0f;

    switch (pList->mType) {
    case 0:
        result = fn_801C5008(pList, t, mode);
        break;
    case 1:
        result = fn_801C5130(pList, t, mode);
        break;
    }
    return result;
}

float fn_801C52CC(float t, float t0, float a, float b, float c, float d)
{
    float dt = t - t0;

    return dt * (dt * (dt * a + b) + c) + d;
}

float fn_801C52E0(float t, float t0, float t1, float x0, float x1, float x2, float x3, float y0, float y1, float y2,
                  float y3)
{
    float coef[4];
    float roots[6];
    float u = 0.0f;
    float s;

    if (!(t <= t0)) {
        if (!(t < t1)) {
            u = 1.0f;
        } else {
            u = (t - t0) / (t1 - t0);
        }
    }
    coef[0] = x0 - u;
    coef[1] = x1;
    coef[2] = x2;
    coef[3] = x3;
    if (fn_801C5740(coef, 3, 1, 1, roots, 0.0f, 1.0f) == 1) {
        s = roots[0];
    } else {
        s = 0.0f;
    }
    return s * (s * (s * y3 + y2) + y1) + y0;
}
