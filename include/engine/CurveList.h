#ifndef ENGINE_CURVELIST_H
#define ENGINE_CURVELIST_H

/* Keyed curves evaluated by CurveList.c. A camera sample (engine/AnimSeqCamSample.h) holds fifteen. */

/* Curve: key type (0 Hermite, 1 Bezier), key count, time range and keys. */
typedef struct CurveList_t {
    unsigned short mType;
    unsigned short mCount;
    float mStart;
    float mEnd;
    void *mpKeys;
} CurveList_t;

/* Hermite key: with a nonzero high half of the flags the key holds its value; otherwise the cubic in the time
   since the key applies. */
typedef struct CurveHermiteKey_t {
    unsigned int mFlags;
    float mValue;
    float mTime;
    float mCoef[4];
} CurveHermiteKey_t;

/* Bezier key: the segment from mTime to mEndTime, with the cubic coefficients of x and y in the segment
   parameter. */
typedef struct CurveBezierKey_t {
    unsigned int mFlags;
    float mValue;
    float mTime;
    float mEndTime;
    float mX[4];
    float mY[4];
} CurveBezierKey_t;

#ifdef __cplusplus
extern "C" {
#endif

float CurveListEvaluate(float t, CurveList_t *pList, int mode);
float CurveListCalculateHermite(float t, float t0, float a, float b, float c, float d);
float CurveListCalculateBezier(float t, float t0, float t1, float x0, float x1, float x2, float x3, float y0, float y1,
                               float y2, float y3);

#ifdef __cplusplus
}
#endif

#endif
