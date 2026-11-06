/* Per-format operations for geometry blending: widen vertex attributes (float, 16-bit,
   8-bit) to fixed point, accumulate weighted targets and narrow the result back. */

#include "engine/tmlib.h"

static void _TMBlendOpAccumulate_3s16(int *pAccum, short *pSrc, unsigned int count, int weight, int frac)
{
    weight <<= 15 - frac;
    for (; count != 0; count--) {
        int x = pSrc[0] * weight;
        int y = pSrc[1] * weight;
        int z = pSrc[2] * weight;

        pAccum[0] += x;
        pAccum[1] += y;
        pAccum[2] += z;
        pSrc += 3;
        pAccum += 3;
    }
}

static void _TMBlendOpAccumulate_3s16C(int *pAccum, short *pSrc, unsigned int count, int weight, int frac)
{
    weight <<= 15 - frac;
    for (; count != 0; count--) {
        int index = pSrc[3];
        int x = pSrc[0] * weight;
        int y = pSrc[1] * weight;
        int z = pSrc[2] * weight;

        pAccum[index * 3] += x;
        pAccum[index * 3 + 1] += y;
        pAccum[index * 3 + 2] += z;
        pSrc += 4;
    }
}

static void _TMBlendOpAccumulateInterp_4s16C(int *pAccum, short *pSrc, unsigned int count)
{
    for (; count != 0; count--) {
        int *pDst = &pAccum[pSrc[4] * 3];
        int x = pSrc[0] << 17;
        int y = pSrc[1] << 17;
        int z = pSrc[2] << 17;
        int w = pSrc[3];
        int dx = pDst[0];
        int dy = pDst[1];
        int dz = pDst[2];

        pDst[0] = w * ((dx - x) >> 8) + x;
        pDst[1] = w * ((dy - y) >> 8) + y;
        pDst[2] = w * ((dz - z) >> 8) + z;
        pSrc += 5;
    }
}

static void _TMBlendOpExtract_3s16(int *pDst, short *pSrc, unsigned int count, int frac)
{
    int shift = 27 - frac;

    for (; count != 0; count--) {
        int x = pSrc[0];
        int y = pSrc[1];
        int z = pSrc[2];

        pDst[0] = x << shift;
        pDst[1] = y << shift;
        pDst[2] = z << shift;
        pSrc += 3;
        pDst += 3;
    }
}

static void _TMBlendOpExtract_3f32(int *pDst, float *pSrc, unsigned int count, int frac)
{
    int shift = 27 - frac;

    for (; count != 0; count--) {
        float x = pSrc[0];
        float y = pSrc[1];
        float z = pSrc[2];

        pDst[0] = x * (float)(1 << shift);
        pDst[1] = y * (float)(1 << shift);
        pDst[2] = z * (float)(1 << shift);
        pSrc += 3;
        pDst += 3;
    }
}

static void _TMBlendOpIntract_3f32(float *pDst, int *pSrc, unsigned int count, int frac)
{
    int shift = 27 - frac;

    for (; count != 0; count--) {
        float x = pSrc[0];
        float y = pSrc[1];
        float z = pSrc[2];

        pDst[0] = x / (float)(1 << shift);
        pDst[1] = y / (float)(1 << shift);
        pDst[2] = z / (float)(1 << shift);
        pSrc += 3;
        pDst += 3;
    }
}

static void _TMBlendOpIntract_3s16(short *pDst, int *pSrc, unsigned int count, int frac)
{
    int shift = 27 - frac;

    for (; count != 0; count--) {
        int x = pSrc[0] >> shift;
        int y = pSrc[1] >> shift;
        int z = pSrc[2] >> shift;

        if (x < -0x8000) {
            x = -0x8000;
        } else if (x > 0x7FFF) {
            x = 0x7FFF;
        }
        if (y < -0x8000) {
            y = -0x8000;
        } else if (y > 0x7FFF) {
            y = 0x7FFF;
        }
        if (z < -0x8000) {
            z = -0x8000;
        } else if (z > 0x7FFF) {
            z = 0x7FFF;
        }
        pDst[0] = x;
        pDst[1] = y;
        pDst[2] = z;
        pSrc += 3;
        pDst += 3;
    }
}

static void _TMBlendOpAccumulate_3s8(int *pAccum, signed char *pSrc, unsigned int count, int weight, int frac)
{
    weight <<= 15 - frac;
    for (; count != 0; count--) {
        int x = pSrc[0] * weight;
        int y = pSrc[1] * weight;
        int z = pSrc[2] * weight;

        pAccum[0] += x;
        pAccum[1] += y;
        pAccum[2] += z;
        pSrc += 3;
        pAccum += 3;
    }
}

static void _TMBlendOpAccumulate_3s8C(int *pAccum, signed char *pSrc, unsigned int count, int weight, int frac)
{
    weight <<= 15 - frac;
    for (; count != 0; count--) {
        int index = *(short *)&pSrc[4];
        int x = pSrc[0] * weight;
        int y = pSrc[1] * weight;
        int z = pSrc[2] * weight;

        pAccum[index * 3] += x;
        pAccum[index * 3 + 1] += y;
        pAccum[index * 3 + 2] += z;
        pSrc += 6;
    }
}

static void _TMBlendOpAccumulateInterp_4s8C(int *pAccum, signed char *pSrc, unsigned int count)
{
    for (; count != 0; count--) {
        int *pDst = &pAccum[*(short *)&pSrc[4] * 3];
        int x = pSrc[0] << 20;
        int y = pSrc[1] << 20;
        int z = pSrc[2] << 20;
        int w = pSrc[3];
        int dx = pDst[0];
        int dy = pDst[1];
        int dz = pDst[2];

        pDst[0] = w * ((dx - x) >> 8) + x;
        pDst[1] = w * ((dy - y) >> 8) + y;
        pDst[2] = w * ((dz - z) >> 8) + z;
        pSrc += 6;
    }
}

static void _TMBlendOpExtract_3s8(int *pDst, signed char *pSrc, unsigned int count, int frac)
{
    int shift = 27 - frac;

    for (; count != 0; count--) {
        int x = pSrc[0];
        int y = pSrc[1];
        int z = pSrc[2];

        pDst[0] = x << shift;
        pDst[1] = y << shift;
        pDst[2] = z << shift;
        pSrc += 3;
        pDst += 3;
    }
}

static void _TMBlendOpIntract_3s8(signed char *pDst, int *pSrc, unsigned int count, int frac)
{
    int shift = 27 - frac;

    for (; count != 0; count--) {
        int x = pSrc[0] >> shift;
        int y = pSrc[1] >> shift;
        int z = pSrc[2] >> shift;

        if (x < -0x80) {
            x = -0x80;
        } else if (x > 0x7F) {
            x = 0x7F;
        }
        if (y < -0x80) {
            y = -0x80;
        } else if (y > 0x7F) {
            y = 0x7F;
        }
        if (z < -0x80) {
            z = -0x80;
        } else if (z > 0x7F) {
            z = 0x7F;
        }
        pDst[0] = x;
        pDst[1] = y;
        pDst[2] = z;
        pSrc += 3;
        pDst += 3;
    }
}

unsigned int TMBlendOpAccumulate(int dstId, int srcId, int weight)
{
    TMBlendChannel_t *pSrc = TMBlendChannelGetBuffer(srcId);
    TMBlendChannel_t *pDst = TMBlendChannelGetBuffer(dstId);
    TMGeomAttr_t *pAttr = pSrc->mpAttr;

    if (pAttr->mbDelta) {
        switch (pAttr->mCompType) {
        case 3:
            _TMBlendOpAccumulateInterp_4s16C((int *)pDst->mpCursor, (short *)pSrc->mpCursor, pAttr->mCount);
            break;
        case 1:
            _TMBlendOpAccumulateInterp_4s8C((int *)pDst->mpCursor, (signed char *)pSrc->mpCursor, pAttr->mCount);
            break;
        }
    } else {
        switch (pAttr->mCompType) {
        case 3:
            if (pAttr->mStride == 6) {
                _TMBlendOpAccumulate_3s16((int *)pDst->mpCursor, (short *)pSrc->mpCursor, pAttr->mCount, weight, pAttr->mFrac);
            } else if (pAttr->mStride == 8) {
                _TMBlendOpAccumulate_3s16C((int *)pDst->mpCursor, (short *)pSrc->mpCursor, pAttr->mCount, weight, pAttr->mFrac);
            }
            break;
        case 1:
            if (pAttr->mStride == 3) {
                _TMBlendOpAccumulate_3s8((int *)pDst->mpCursor, (signed char *)pSrc->mpCursor, pAttr->mCount, weight, pAttr->mFrac);
            } else if (pAttr->mStride == 6) {
                _TMBlendOpAccumulate_3s8C((int *)pDst->mpCursor, (signed char *)pSrc->mpCursor, pAttr->mCount, weight, pAttr->mFrac);
            }
            break;
        case 4:
            break;
        }
    }
    return pAttr->mCount;
}

void TMBlendOpExtract(int dstId, int srcId)
{
    TMBlendChannel_t *pSrc = TMBlendChannelGetBuffer(srcId);
    TMBlendChannel_t *pDst = TMBlendChannelGetBuffer(dstId);
    TMGeomAttr_t *pAttr = pSrc->mpAttr;

    switch (pAttr->mCompType) {
    case 4:
        _TMBlendOpExtract_3f32((int *)pDst->mpCursor, (float *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    case 3:
        _TMBlendOpExtract_3s16((int *)pDst->mpCursor, (short *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    case 1:
        _TMBlendOpExtract_3s8((int *)pDst->mpCursor, (signed char *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    }
    pDst->mSize = pAttr->mCount * 12;
}

void TMBlendOpIntract(int dstId, int srcId)
{
    TMBlendChannel_t *pSrc = TMBlendChannelGetBuffer(srcId);
    TMBlendChannel_t *pDst = TMBlendChannelGetBuffer(dstId);
    TMGeomAttr_t *pAttr = pDst->mpAttr;

    switch (pAttr->mCompType) {
    case 4:
        _TMBlendOpIntract_3f32((float *)pDst->mpCursor, (int *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    case 3:
        _TMBlendOpIntract_3s16((short *)pDst->mpCursor, (int *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    case 1:
        _TMBlendOpIntract_3s8((signed char *)pDst->mpCursor, (int *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    }
    pDst->mSize = pAttr->mCount * 6;
}
