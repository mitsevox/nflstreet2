#include "game/cu_801442FC.h"
#include "game/cu_801A8620.h"

#include <math.h>

extern "C" {
extern void *lbl_803EA368;
extern unsigned char lbl_803EB874;
int fn_8002D058(void *p);
int fn_8002D060(void *p);
int fn_8002D150(void *p);
}

struct UV_801A7C20 {
    float u;
    float v;
};

struct Mesh_801A7C20 {
    UV_801A7C20 *mpUVs;
    unsigned short mCount;
};

struct FixedUV_801A7F10 {
    short u;
    short v;
};

struct FixedMesh_801A7F10 {
    FixedUV_801A7F10 *mpUVs;
    unsigned short mCount;
};

/* Texture-scroll settings: frame lengths in seconds, then per-axis scroll
   values whose meaning depends on the scroll type. */
struct Scroll_801A7C20 {
    int mUnknown0;
    float mDurations[11];
    unsigned int mPeriodV;
    unsigned int mPeriodU;
    unsigned char mUnknown38[8];
    unsigned int mFrame;
    unsigned int mFrameCount;
    float mTimer;
    int mAxis;
    int mType;
};

extern "C" {
void fn_801A7C20(Mesh_801A7C20 *pMesh, Scroll_801A7C20 *pScroll)
{
    UV_801A7C20 *uv = pMesh->mpUVs;
    float step = 0.0f;
    if (pScroll->mAxis == 1) {
        if (pScroll->mType == 0) {
            pScroll->mTimer += 1.0f;
            if (pScroll->mTimer >= pScroll->mDurations[pScroll->mFrame] * 60.0f) {
                pScroll->mTimer = 0.0f;
                step = 1.0f / pScroll->mPeriodV;
                pScroll->mFrame = (pScroll->mFrame + 1) % pScroll->mFrameCount;
            }
        } else if (pScroll->mType == 1) {
            step = pScroll->mPeriodV / (pScroll->mDurations[0] * 60.0f);
        }
        for (unsigned int i = 0; i < pMesh->mCount; i += 4) {
            uv[i].v += step;
            if (uv[i].v > 1.0f) {
                uv[i].v = step;
                uv[i + 1].v = 0.0f;
                uv[i + 2].v = step;
                uv[i + 3].v = 0.0f;
            } else {
                uv[i + 1].v += step;
                uv[i + 2].v += step;
                uv[i + 3].v += step;
            }
            uv[i].u = 1.0f;
            uv[i + 1].u = 1.0f;
            uv[i + 2].u = 0.0f;
            uv[i + 3].u = 0.0f;
        }
    } else {
        if (pScroll->mType == 0) {
            pScroll->mTimer += 1.0f;
            if (pScroll->mTimer >= pScroll->mDurations[pScroll->mFrame] * 60.0f) {
                pScroll->mTimer = 0.0f;
                step = 1.0f / pScroll->mPeriodU;
                pScroll->mFrame = (pScroll->mFrame + 1) % pScroll->mFrameCount;
            }
        } else if (pScroll->mType == 1) {
            step = pScroll->mPeriodU / (pScroll->mDurations[0] * 60.0f);
        }
        for (unsigned int i = 0; i < pMesh->mCount; i += 4) {
            uv[i].u += step;
            if (uv[i].u > 1.0f) {
                uv[i].u = step;
                uv[i + 1].u = step;
                uv[i + 2].u = 0.0f;
                uv[i + 3].u = 0.0f;
            } else {
                uv[i + 1].u += step;
                uv[i + 2].u += step;
                uv[i + 3].u += step;
            }
            uv[i].v = 1.0f;
            uv[i + 1].v = 0.0f;
            uv[i + 2].v = 1.0f;
            uv[i + 3].v = 0.0f;
        }
    }
}

void fn_801A7F10(FixedMesh_801A7F10 *pMesh, Scroll_801A7C20 *pScroll)
{
    float step = 0.0f;
    int one = 0x1000;
    float minV = one * 2;
    FixedUV_801A7F10 *uv = pMesh->mpUVs;
    signed char corner = 0;
    float minU = minV;
    signed char corners[4];

    if (pScroll->mAxis == 1) {
        if (lbl_803EB874) return;
        if (pScroll->mType == 0) {
            float speed = 1.0f;
            if (fn_8002D060(lbl_803EA368)) {
                int rate = fn_8002D150(lbl_803EA368);
                if (fn_8002D058(lbl_803EA368)) speed = fabs(rate * (1.0f / 60.0f));
                else speed = 0.0f;
            }
            pScroll->mTimer += speed;
            if (pScroll->mTimer >= pScroll->mDurations[pScroll->mFrame] * 60.0f) {
                pScroll->mTimer = 0.0f;
                step = 1.0f / pScroll->mPeriodV;
                pScroll->mFrame = (pScroll->mFrame + 1) % pScroll->mFrameCount;
            }
        } else if (pScroll->mType == 1) {
            step = pScroll->mPeriodV / (pScroll->mDurations[0] * 60.0f);
        }
        short delta = (short)(step * one);
        for (unsigned int i = 0; i < pMesh->mCount; i += 4) {
            int k;
            for (k = 0; k < 4; k++) {
                if (uv[k].u < minU) minU = uv[k].u;
                if (uv[k].v < minV) minV = uv[k].v;
            }
            for (k = 0; k < 4; k++) {
                if (uv[k].u <= minU - 5.0f || uv[k].u >= minU + 5.0f) corner = 1;
                if (uv[k].v <= minV - 5.0f || uv[k].v >= minV + 5.0f) corner += 2;
                corners[corner] = k;
                corner = 0;
            }
            uv[corners[3]].v += delta;
            if (uv[corners[3]].v > one) {
                uv[corners[2]].v = delta;
                uv[corners[3]].v = delta;
                uv[corners[0]].v = 0;
                uv[corners[1]].v = 0;
            } else {
                uv[corners[2]].v += delta;
                uv[corners[0]].v += delta;
                uv[corners[1]].v += delta;
            }
            uv[corners[2]].u = 0;
            uv[corners[3]].u = one;
            uv[corners[1]].u = one;
            uv[corners[0]].u = 0;
        }
    } else {
        if (pScroll->mType == 0) {
            pScroll->mTimer += 1.0f;
            if (pScroll->mTimer >= pScroll->mDurations[pScroll->mFrame] * 60.0f) {
                pScroll->mTimer = 0.0f;
                step = 1.0f / pScroll->mPeriodU;
                pScroll->mFrame = (pScroll->mFrame + 1) % pScroll->mFrameCount;
            }
        } else if (pScroll->mType == 1) {
            step = pScroll->mPeriodV / (pScroll->mDurations[0] * 60.0f);
        }
        short delta = (short)(step * one);
        for (unsigned int i = 0; i < pMesh->mCount; i += 4) {
            uv[i].u += delta;
            if (uv[i].u > one) {
                uv[i].u = delta;
                uv[i + 1].u = delta;
                uv[i + 2].u = 0;
                uv[i + 3].u = 0;
            } else {
                uv[i + 1].u += delta;
                uv[i + 2].u += delta;
                uv[i + 3].u += delta;
            }
            uv[i].v = one;
            uv[i + 1].v = 0;
            uv[i + 2].v = one;
            uv[i + 3].v = 0;
        }
    }
}

int fn_80236B98(int a, float x, float y, float z);
void fn_80236C10(int a, float *pScale, float *pDirection);

void fn_801A8548(Object_801A8620 *, int)
{
}

int fn_801A854C(Tracker_801442FC *pTracker, Object_80144310 *pSource)
{
    float direction[4];
    float scale[3];
    float x = 1.0f, y = 1.0f, z = 1.0f;
    if (pSource) {
        x = pSource->mUnknownC;
        y = pSource->mUnknown10;
        z = pSource->mUnknown14;
    }
    int light = fn_80236B98(0, x, y, z);
    if (fn_80144310(pTracker, pSource, direction, scale)) {
        scale[0] *= x;
        scale[1] *= y;
        scale[2] *= z;
        fn_80236C10(0, scale, direction);
    }
    return light;
}
}
