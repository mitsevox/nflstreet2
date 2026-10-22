#include "engine/tmlib.h"

static void fn_80214F58(int *pAccum, short *pSrc, unsigned int count, int weight, int frac)
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

static void fn_80214FB8(int *pAccum, short *pSrc, unsigned int count, int weight, int frac)
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

static void fn_80215020(int *pAccum, short *pSrc, unsigned int count)
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

static void fn_802150AC(int *pDst, short *pSrc, unsigned int count, int frac)
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

static void fn_802150F0(int *pDst, float *pSrc, unsigned int count, int frac)
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

static void fn_80215190(float *pDst, int *pSrc, unsigned int count, int frac)
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

static void fn_80215258(short *pDst, int *pSrc, unsigned int count, int frac)
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

static void fn_802152F0(int *pAccum, signed char *pSrc, unsigned int count, int weight, int frac)
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

static void fn_8021535C(int *pAccum, signed char *pSrc, unsigned int count, int weight, int frac)
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

static void fn_802153D0(int *pAccum, signed char *pSrc, unsigned int count)
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

static void fn_8021546C(int *pDst, signed char *pSrc, unsigned int count, int frac)
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

static void fn_802154BC(signed char *pDst, int *pSrc, unsigned int count, int frac)
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

unsigned int fn_80215554(int dstId, int srcId, int weight)
{
    BlendChannel_80214D40 *pSrc = fn_80214DB8(srcId);
    BlendChannel_80214D40 *pDst = fn_80214DB8(dstId);
    SwapAttr_8020ED10 *pAttr = pSrc->mpAttr;

    if (pAttr->mbDelta) {
        switch (pAttr->mCompType) {
        case 3:
            fn_80215020((int *)pDst->mpCursor, (short *)pSrc->mpCursor, pAttr->mCount);
            break;
        case 1:
            fn_802153D0((int *)pDst->mpCursor, (signed char *)pSrc->mpCursor, pAttr->mCount);
            break;
        }
    } else {
        switch (pAttr->mCompType) {
        case 3:
            if (pAttr->mStride == 6) {
                fn_80214F58((int *)pDst->mpCursor, (short *)pSrc->mpCursor, pAttr->mCount, weight, pAttr->mFrac);
            } else if (pAttr->mStride == 8) {
                fn_80214FB8((int *)pDst->mpCursor, (short *)pSrc->mpCursor, pAttr->mCount, weight, pAttr->mFrac);
            }
            break;
        case 1:
            if (pAttr->mStride == 3) {
                fn_802152F0((int *)pDst->mpCursor, (signed char *)pSrc->mpCursor, pAttr->mCount, weight, pAttr->mFrac);
            } else if (pAttr->mStride == 6) {
                fn_8021535C((int *)pDst->mpCursor, (signed char *)pSrc->mpCursor, pAttr->mCount, weight, pAttr->mFrac);
            }
            break;
        case 4:
            break;
        }
    }
    return pAttr->mCount;
}

void fn_80215694(int dstId, int srcId)
{
    BlendChannel_80214D40 *pSrc = fn_80214DB8(srcId);
    BlendChannel_80214D40 *pDst = fn_80214DB8(dstId);
    SwapAttr_8020ED10 *pAttr = pSrc->mpAttr;

    switch (pAttr->mCompType) {
    case 4:
        fn_802150F0((int *)pDst->mpCursor, (float *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    case 3:
        fn_802150AC((int *)pDst->mpCursor, (short *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    case 1:
        fn_8021546C((int *)pDst->mpCursor, (signed char *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    }
    pDst->mSize = pAttr->mCount * 12;
}

void fn_8021574C(int dstId, int srcId)
{
    BlendChannel_80214D40 *pSrc = fn_80214DB8(srcId);
    BlendChannel_80214D40 *pDst = fn_80214DB8(dstId);
    SwapAttr_8020ED10 *pAttr = pDst->mpAttr;

    switch (pAttr->mCompType) {
    case 4:
        fn_80215190((float *)pDst->mpCursor, (int *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    case 3:
        fn_80215258((short *)pDst->mpCursor, (int *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    case 1:
        fn_802154BC((signed char *)pDst->mpCursor, (int *)pSrc->mpCursor, pAttr->mCount, pAttr->mFrac);
        break;
    }
    pDst->mSize = pAttr->mCount * 6;
}
