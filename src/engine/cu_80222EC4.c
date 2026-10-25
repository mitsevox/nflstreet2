/* Comparison fragment of src/engine/cu_80221198.c: fn_80222EC4 .. fn_80223224 and their literal pools. */
#include "engine/cu_8021A438.h"

extern float fn_80260B1C(float x);

extern Point_80222EC4 lbl_8039FDB8[];
extern Point_80222EC4 lbl_803A00D8[];

void fn_80222EC4(Point_80222EC4 *pPoints, int count, float t, Point_80222EC4 *pOut)
{
    int i;
    int j;

    for (j = 0; j < count; j++) {
        lbl_8039FDB8[j] = pPoints[j];
    }
    for (i = 1; i < count; i++) {
        for (j = 0; j < count - i; j++) {
            lbl_8039FDB8[j].mX = (1.0f - t) * lbl_8039FDB8[j].mX + t * lbl_8039FDB8[j + 1].mX;
            lbl_8039FDB8[j].mY = (1.0f - t) * lbl_8039FDB8[j].mY + t * lbl_8039FDB8[j + 1].mY;
        }
    }
    *pOut = lbl_8039FDB8[0];
}


void fn_80222F8C(Point_80222EC4 *pPoints, int count, Point_80222EC4 *pOut, int numOut)
{
    float step;
    float t;
    int i;

    step = 1.0f / (numOut - 1);
    t = step;
    pOut[0] = pPoints[0];
    for (i = 1; i < numOut - 1; i++, t += step) {
        fn_80222EC4(pPoints, count, t, &pOut[i]);
    }
    pOut[numOut - 1] = pPoints[count - 1];
}

void fn_8022306C(Point_80222EC4 *pA, Point_80222EC4 *pB, Point_80222EC4 *pLeft, Point_80222EC4 *pRight,
                 Point_80222EC4 *pDir, int useDir, float width)
{
    Point_80222EC4 normal;
    Point_80222EC4 offset;
    float len;
    float dx;
    float dy;

    dy = pA->mY - pB->mY;
    dx = pA->mX - pB->mX;
    normal.mX = dy;
    normal.mY = dx;
    len = fn_80260B1C(dy * dy + dx * dx);
    if (len != 0.0f) {
        normal.mX /= len;
        normal.mY /= len;
    }
    width *= 0.25f;
    if (pDir != 0 && useDir != 0) {
        offset.mX = (pDir->mX + normal.mX) * 0.5f;
        offset.mY = (pDir->mY + normal.mY) * 0.5f;
        len = fn_80260B1C(offset.mX * offset.mX + offset.mY * offset.mY);
        if (len != 0.0f) {
            offset.mX /= len;
            offset.mY /= len;
        }
    } else {
        offset.mX = normal.mX;
        offset.mY = normal.mY;
    }
    offset.mX *= width;
    offset.mY *= width;
    pLeft->mX = pA->mX - offset.mX;
    pLeft->mY = pA->mY + offset.mY;
    pRight->mX = pA->mX + offset.mX;
    pRight->mY = pA->mY - offset.mY;
    if (pDir != 0) {
        pDir->mX = normal.mX;
        pDir->mY = normal.mY;
    }
}


void fn_80223224(int numPoints, Point_80222EC4 *pPoints, float *pWidths, Point_80222EC4 *pOut, int numOut)
{
    Point_80222EC4 dir;
    float stepA;
    float stepB;
    float width;
    int half;
    int i;
    int j;

    half = numOut / 2;
    stepB = (pWidths[2] - pWidths[1]) / half;
    stepA = (pWidths[1] - pWidths[0]) / half;
    fn_80222F8C(pPoints, numPoints, lbl_803A00D8, numOut);
    lbl_803A00D8[numOut].mX = lbl_803A00D8[numOut - 2].mX;
    lbl_803A00D8[numOut].mY = lbl_803A00D8[numOut - 2].mY;
    fn_8022306C(&lbl_803A00D8[0], &lbl_803A00D8[1], &pOut[0], &pOut[1], &dir, 0, pWidths[0]);
    width = pWidths[0];
    j = 2;
    for (i = 1; i < numOut - 1; i++) {
        if (i <= half) {
            width += stepA;
        } else {
            width += stepB;
        }
        fn_8022306C(&lbl_803A00D8[i], &lbl_803A00D8[i + 1], &pOut[j], &pOut[j + 1], &dir, 1, width);
        j += 2;
    }
    fn_8022306C(&lbl_803A00D8[numOut - 1], &lbl_803A00D8[numOut], &pOut[j], &pOut[j + 1], 0, 0, pWidths[2]);
}

