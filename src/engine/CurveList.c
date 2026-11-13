/* Curve lists: keyed Hermite and Bezier curves evaluated over a time range, with clamp or wrap past the end.
   Camera samples use them for animated camera moves. */

#include "engine/polynomial.h"
#include "engine/CurveList.h"

/* Mode 0 holds the last key's value past the end; mode 1 wraps the time into the range. */
static float _CurveListEvaluateHermiteCurve(float t, CurveList_t *pList, int mode)
{
    CurveHermiteKey_t *pKeys = pList->mpKeys;
    CurveHermiteKey_t *pKey = pKeys;
    float result = 0.0f;
    float start;
    float end;
    unsigned int i = 0;

    if (pList->mCount == 0) {
        return result;
    }
    start = pList->mStart;
    if (t < start) {
        return pKey->mValue;
    }
    end = pList->mEnd;
    if (!(t <= end) && mode == 0) {
        return pKeys[pList->mCount - 1].mValue;
    } else if (!(t <= end) && mode == 1) {
        float range = end - start;

        t -= (float)(int)(t / range) * range;
    }
    /* Find the last key at or before t. */
    for (;;) {
        if (i >= pList->mCount) {
            goto found;
        }
        if (t < pKeys[i].mTime) {
            goto found;
        }
        pKey = &pKeys[i];
        i++;
    }
found:
    if (pKey->mFlags & 0xFFFF0000) {
        return pKey->mValue;
    }
    return CurveListCalculateHermite(t, pKey->mTime, pKey->mCoef[0], pKey->mCoef[1], pKey->mCoef[2], pKey->mCoef[3]);
}

static float _CurveListEvaluateBezierCurve(float t, CurveList_t *pList, int mode)
{
    CurveBezierKey_t *pKeys = pList->mpKeys;
    CurveBezierKey_t *pKey = pKeys;
    float result = 0.0f;
    float start;
    float end;
    unsigned int i = 0;

    if (pList->mCount == 0) {
        return result;
    }
    start = pList->mStart;
    if (t < start) {
        return pKey->mValue;
    }
    end = pList->mEnd;
    if (!(t <= end) && mode == 0) {
        return pKeys[pList->mCount - 1].mValue;
    } else if (!(t <= end) && mode == 1) {
        float range = end - start;

        t -= (float)(int)(t / range) * range;
    }
    /* Find the last key at or before t. */
    for (;;) {
        if (i >= pList->mCount) {
            goto found;
        }
        if (t < pKeys[i].mTime) {
            goto found;
        }
        pKey = &pKeys[i];
        i++;
    }
found:
    if (pKey->mFlags & 0xFFFF0000) {
        return pKey->mValue;
    }
    return CurveListCalculateBezier(t, pKey->mTime, pKey->mEndTime, pKey->mX[0], pKey->mX[1], pKey->mX[2], pKey->mX[3],
                                    pKey->mY[0], pKey->mY[1], pKey->mY[2], pKey->mY[3]);
}

float CurveListEvaluate(float t, CurveList_t *pList, int mode)
{
    float result = 0.0f;

    switch (pList->mType) {
    case 0:
        result = _CurveListEvaluateHermiteCurve(t, pList, mode);
        break;
    case 1:
        result = _CurveListEvaluateBezierCurve(t, pList, mode);
        break;
    }
    return result;
}

/* The cubic with coefficients a..d in the time since t0. */
float CurveListCalculateHermite(float t, float t0, float a, float b, float c, float d)
{
    float dt = t - t0;

    return dt * (dt * (dt * a + b) + c) + d;
}

/* Solves x(s) = u for the segment parameter s, where u is t's position between t0 and t1, then returns y(s). */
float CurveListCalculateBezier(float t, float t0, float t1, float x0, float x1, float x2, float x3, float y0, float y1,
                               float y2, float y3)
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
    if (PolynomialCalculateRoots(coef, 3, 0.0f, 1, 1.0f, 1, roots) == 1) {
        s = roots[0];
    } else {
        s = 0.0f;
    }
    return s * (s * (s * y3 + y2) + y1) + y0;
}
