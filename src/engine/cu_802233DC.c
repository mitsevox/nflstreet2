/* Comparison fragment of src/engine/cu_80221198.c: fn_802233DC and its literal pool. */
#include "engine/cu_8021A438.h"

Point_80222EC4 fn_802233DC(Point_80222EC4 *pPoints, int unused, int index)
{
    Point_80222EC4 result;

    if (index == 1) {
        result.mX = ((pPoints[0].mX + pPoints[2].mX) * 0.5f + pPoints[1].mX) * 0.5f;
        result.mY = ((pPoints[0].mY + pPoints[2].mY) * 0.5f + pPoints[1].mY) * 0.5f;
        return result;
    }
    return pPoints[index];
}
