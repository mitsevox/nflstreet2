#include "engine/tmlib.h"

static inline void fn_80213DB0_Project(f32 *pClip, f32 (*pMtx)[4], f32 *pPos)
{
    pClip[0] = pMtx[0][0] * pPos[0] + pMtx[0][2] * pPos[2];
    pClip[1] = pMtx[1][1] * pPos[1] + pMtx[1][2] * pPos[2];
    pClip[2] = pMtx[2][2] * pPos[2] + pMtx[2][3];
    pClip[3] = pMtx[3][2] * pPos[2];
}

static inline unsigned int fn_80213DB0_Code(f32 *pClip)
{
    unsigned int code;

    code = 0;
    if (!(pClip[0] >= -pClip[3])) {
        code = 2;
    } else if (!(pClip[0] <= pClip[3])) {
        code = 1;
    }
    if (!(pClip[1] >= -pClip[3])) {
        code |= 8;
    } else if (!(pClip[1] <= pClip[3])) {
        code |= 4;
    }
    if (!(pClip[2] >= -pClip[3])) {
        code |= 0x20;
    } else if (!(pClip[2] <= pClip[3])) {
        code |= 0x10;
    }
    return code;
}

static inline void fn_80213F18_Extent(Extent_802144AC *pExtent, f32 *pPos)
{
    if (!(pPos[0] >= pExtent->mMin[0])) {
        pExtent->mMin[0] = pPos[0];
    }
    if (!(pPos[0] <= pExtent->mMax[0])) {
        pExtent->mMax[0] = pPos[0];
    }
    if (!(pPos[1] >= pExtent->mMin[1])) {
        pExtent->mMin[1] = pPos[1];
    }
    if (!(pPos[1] <= pExtent->mMax[1])) {
        pExtent->mMax[1] = pPos[1];
    }
    if (!(pPos[2] >= pExtent->mMin[2])) {
        pExtent->mMin[2] = pPos[2];
    }
    if (!(pPos[2] <= pExtent->mMax[2])) {
        pExtent->mMax[2] = pPos[2];
    }
}

unsigned int fn_80213DB0(f32 *pPoints, int numPoints, f32 (*pMtx)[4], f32 *pDepth)
{
    f32 aClip[4];
    f32 depth;
    unsigned int andCode;
    unsigned int orCode;
    unsigned int code;
    int count;

    depth = 0.0f;
    andCode = 0x3F;
    orCode = 0;
    count = numPoints;
    for (; numPoints > 0; numPoints--) {
        fn_80213DB0_Project(aClip, pMtx, pPoints);
        code = fn_80213DB0_Code(aClip);
        orCode |= code;
        andCode &= code;
        if (pDepth != 0) {
            depth -= aClip[3];
        }
        pPoints += 3;
    }
    if (pDepth != 0) {
        *pDepth = depth / count;
    }
    return (orCode << 8) | andCode;
}

unsigned int fn_80213F18(f32 *pPoints, int numPoints, f32 (*pMtx)[4], Extent_802144AC *pExtent, f32 *pDepth)
{
    f32 aClip[4];
    f32 aNdc[3];
    f32 depth;
    f32 inv;
    unsigned int andCode;
    unsigned int orCode;
    unsigned int code;
    int count;

    depth = 0.0f;
    andCode = 0x3F;
    orCode = 0;
    count = numPoints;
    for (; numPoints > 0; numPoints--) {
        fn_80213DB0_Project(aClip, pMtx, pPoints);
        inv = 1.0f / aClip[3];
        code = fn_80213DB0_Code(aClip);
        orCode |= code;
        andCode &= code;
        aNdc[0] = aClip[0] * inv;
        aNdc[1] = aClip[1] * inv;
        aNdc[2] = aClip[2] * inv;
        fn_80213F18_Extent(pExtent, aNdc);
        if (pDepth != 0) {
            depth -= aClip[3];
        }
        pPoints += 3;
    }
    if (pDepth != 0) {
        *pDepth = depth / count;
    }
    return (orCode << 8) | andCode;
}
