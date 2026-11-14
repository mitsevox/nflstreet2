/* Animation blending for players: interpolates bone angles and whole poses,
   decodes and mixes the weighted entries of a blend list into the player's
   pose, blends 64-value weight sets and builds the pose's bone matrices. */
#include "game/AnimRootItem.h"
#include "game/AnimFrameHeader.h"
#include "game/Object_8003DEC4.h"
#include "game/AnimQuantContext.h"
#include "game/Ball.h"
#include "game/fn_801D2B7C.h"
#include <string.h>

extern "C" {
void AnimLerpFixed(short *pOut, short *pA, short *pB, int weight, int count);
void AnimLerpFixedScaled(short *pOut, short *pA, short *pB, int weight, int count, short *pOffset, short *pScale);
void AnimScaleFixed(short *pOut, short *pA, int count, short *pOffset, short *pScale);
float fn_801BE5D0(void *p, unsigned short index);
void Orient3Lerp(int *pOut, int *pA, int *pB, float t);
void OrientLerpAngle(int *pOut, int a, int b, float t);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D09EC(int a);
void fn_801D0C58(float *p);
void QuatToEulerYZX(int *pAngles, Quat_801EB488 *pRot);
void QuatFromEulerYZX(Quat_801EB488 *pOut, int a, int b, int c);
void QuatSlerp(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB, float t);
void fn_80227930(float *pOut, float *pA, float *pB, float t);
void fn_802338D4(AnimPose_t *pPose, AnimSkeleton_t *pSkeleton, unsigned int flags);
}

static unsigned char _AnimBlend_bInterpBones = 1;
static unsigned char _AnimBlend_bWrapAngles = 1;

#define ABS(x) ((x) < 0 ? -(x) : (x))

extern "C" {
/* Replaces the three 16-bit angles of pTo with their value at t between
   pFrom (t = 0) and pTo (t = 1): linear when the two are within 0x71C,
   otherwise a cubic using pPrev and pNext, when given, for the tangents.
   On the cubic path, a pFrom or pNext angle shifted by 2*pi to follow the
   wrap at pi is written back. */
void AnimInterpAngles(short *pPrev, short *pFrom, short *pTo, short *pNext, float t)
{
    float tangent0[3];
    float tangent1[3];
    unsigned char wrapped[3];
    float prev[3];
    float from[3];
    float to[3];
    float next[3];
    float value[3];
    unsigned char spline[3];
    float duration = 1.0f;
    float t2 = t * t;
    float t3 = t2 * t;
    int noPrev = pPrev == 0;
    int noNext = pNext == 0;
    float diff;
    int i;

    spline[0] = spline[1] = spline[2] = 1;
    for (i = 0; i < 3; i++) {
        if (ABS(pFrom[i] - pTo[i]) <= 0x71C) {
            spline[i] = 0;
            AnimLerpFixed(&pTo[i], &pTo[i], &pFrom[i], (int)(t * 4095.0f), 1);
        }
        wrapped[0] = wrapped[1] = wrapped[2] = 0;
        from[i] = pFrom[i] * 9.5873802e-5f;
        to[i] = pTo[i] * 9.5873802e-5f;
        diff = 0.0f;
        if (!noPrev) {
            prev[i] = pPrev[i] * 9.5873802e-5f;
            diff = from[i] - prev[i];
        }
        if (!noNext) {
            next[i] = pNext[i] * 9.5873802e-5f;
        }
        if (_AnimBlend_bWrapAngles) {
            if (!noPrev) {
                if (diff > 3.1415927f) {
                    wrapped[0] = 1;
                    from[i] -= 6.2831855f;
                } else if (diff < -3.1415927f) {
                    wrapped[0] = 1;
                    from[i] += 6.2831855f;
                }
            }
            diff = to[i] - from[i];
            if (diff > 3.1415927f) {
                wrapped[1] = 1;
                to[i] -= 6.2831855f;
            } else if (diff < -3.1415927f) {
                wrapped[1] = 1;
                to[i] += 6.2831855f;
            }
            if (!noNext) {
                if (next[i] - to[i] > 3.1415927f) {
                    wrapped[2] = 1;
                    next[i] -= 6.2831855f;
                } else if (next[i] - to[i] < -3.1415927f) {
                    wrapped[2] = 1;
                    next[i] += 6.2831855f;
                }
            }
        }
        if (noPrev) {
            if (spline[i]) {
                tangent1[i] = (next[i] - from[i]) * 0.5f;
                tangent0[i] = ((to[i] - from[i]) * 3.0f / duration - tangent1[i]) * 0.5f;
            }
        } else if (noNext) {
            if (spline[i]) {
                tangent0[i] = (to[i] - prev[i]) * 0.5f;
                tangent1[i] = ((to[i] - from[i]) * 3.0f / duration - tangent0[i]) * 0.5f;
            }
        } else {
            if (spline[i]) {
                tangent0[i] = (to[i] - prev[i]) * 0.5f;
                tangent1[i] = (next[i] - from[i]) * 0.5f;
            }
        }
        if (spline[i]) {
            value[i] = from[i] * (2.0f * t3 - 3.0f * t2 + 1.0f) + to[i] * (-2.0f * t3 + 3.0f * t2) +
                       tangent0[i] * (t3 - 2.0f * t2 + t) + tangent1[i] * (t3 - t2);
            pTo[i] = (short)(value[i] * 10430.378f);
            if (wrapped[0]) {
                pFrom[i] = (short)(from[i] * 10430.378f);
            }
            if (wrapped[2]) {
                pNext[i] = (short)(next[i] * 10430.378f);
            }
        }
    }
}

void AnimBlendPoseAngles(AnimPose_t *pOut, AnimPose_t *pA, AnimPose_t *pPrev, AnimPose_t *pNext, float t,
                 unsigned char a)
{
    Quat_801EB488 rotA;
    Quat_801EB488 rot;
    int angles[3];
    unsigned int i;

    QuatFromEulerYZX(&rotA, pA->mUnknown32, pA->mUnknown48[2] << 8, pA->mUnknown48[0] << 8);
    QuatFromEulerYZX(&rot, pOut->mUnknown32, pOut->mUnknown48[2] << 8, pOut->mUnknown48[0] << 8);
    QuatSlerp(&rot, &rot, &rotA, t);
    QuatToEulerYZX(angles, &rot);
    if (_AnimBlend_bInterpBones) {
        for (i = 1; i < pOut->mUnknown4; i++) {
            if (pPrev != 0 && pNext != 0) {
                AnimInterpAngles(pPrev->mUnknown48 + i * 3, pA->mUnknown48 + i * 3, pOut->mUnknown48 + i * 3,
                            pNext->mUnknown48 + i * 3, t);
            } else if (pPrev == 0 && pNext != 0) {
                AnimInterpAngles(0, pA->mUnknown48 + i * 3, pOut->mUnknown48 + i * 3, pNext->mUnknown48 + i * 3, t);
            } else if (pPrev != 0 && pNext == 0) {
                AnimInterpAngles(pPrev->mUnknown48 + i * 3, pA->mUnknown48 + i * 3, pOut->mUnknown48 + i * 3, 0, t);
            } else {
                int weight = (int)(t * 4095.0f);

                AnimLerpFixed(pOut->mUnknown48 + i * 3, pOut->mUnknown48 + i * 3, pA->mUnknown48 + i * 3, weight, 1);
                AnimLerpFixed(pOut->mUnknown48 + i * 3 + 1, pOut->mUnknown48 + i * 3 + 1, pA->mUnknown48 + i * 3 + 1,
                            weight, 1);
                AnimLerpFixed(pOut->mUnknown48 + i * 3 + 2, pOut->mUnknown48 + i * 3 + 2, pA->mUnknown48 + i * 3 + 2,
                            weight, 1);
            }
        }
    } else {
        AnimLerpFixed(pOut->mUnknown48, pOut->mUnknown48, pA->mUnknown48, (int)(t * 4095.0f), pOut->mUnknown4 * 3);
    }
    pOut->mUnknown32 = angles[1];
    pOut->mUnknown48[0] = angles[0] >> 8;
    pOut->mUnknown48[2] = angles[2] >> 8;
}

void AnimBlendPose(AnimPose_t *pOut, AnimPose_t *pA, AnimPose_t *pPrev, AnimPose_t *pNext, float t,
                 unsigned char a)
{
    fn_80227930(pOut->mUnknown8, pOut->mUnknown8, pA->mUnknown8, t);
    fn_80227930(pOut->mUnknown20, pOut->mUnknown20, pA->mUnknown20, t);
    Orient3Lerp(pOut->mUnknown36, pOut->mUnknown36, pA->mUnknown36, t);
    AnimBlendPoseAngles(pOut, pA, pPrev, pNext, t, a);
}

short *AnimAllocPoseChannels(int count)
{
    return (short *)fn_801D2B7C(64 * 3 * sizeof(short), 0, 0);
}

void AnimDecompressFrame(unsigned char *pDestination, unsigned char *pSource, AnimQuantContext *pContext, int mirrored)
{
    AnimQuantTables *pPair;
    int size;

    if (mirrored) {
        pPair = &pContext->mUnknownC;
    } else {
        pPair = &pContext->mUnknown4;
    }
    size = AnimGetFrameHeaderSize(pSource);
    memcpy(pDestination, pSource, size);
    pDestination += size;
    AnimUnpackFrameBits((short *)pDestination, (short *)(pSource + size), pContext, mirrored);
    AnimScaleFixed((short *)pDestination, (short *)pDestination, pContext->mUnknown0, pPair->mUnknown0,
                pPair->mUnknown4);
}

void AnimBlendEntries(Object_8003DEC4 *pObject, AnimBlendList *pBlend, int count)
{
    AnimPose_t pose;
    short samples[64 * 3];
    AnimPose_t *pPose = &pObject->mUnknown44;
    unsigned int entries = pBlend->mUnknown0;
    AnimBlendEntry *pEntry;
    AnimQuantContext *pContext;
    AnimQuantTables *pPair;
    unsigned int values;
    float scale;
    float weight;
    unsigned int i;

    pose.mUnknown48 = samples;
    if (entries == 0) {
        return;
    }
    values = pPose->mUnknown4 * 3;
    pEntry = &pBlend->mUnknown4[0];
    scale = pObject->mUnknown28;
    pContext = pEntry->mpUnknown36;
    if (pEntry->mUnknown8 & 1) {
        AnimDecodePoseMirrored(pPose, pEntry, scale, pObject->mUnknown32, pContext, 0);
        pPair = &pContext->mUnknownC;
    } else {
        AnimDecodePose(pPose, pEntry, scale, pObject->mUnknown32, pContext, 0);
        pPair = &pContext->mUnknown4;
    }
    if (pContext != 0) {
        AnimScaleFixed(pPose->mUnknown48, pPose->mUnknown48, values, pPair->mUnknown0, pPair->mUnknown4);
    }
    for (i = 1; i < entries; i++) {
        pEntry = &pBlend->mUnknown4[i];
        weight = pBlend->mUnknown4[i].mUnknown4;
        pContext = pEntry->mpUnknown36;
        if (pEntry->mUnknown8 & 1) {
            AnimDecodePoseMirrored(&pose, pEntry, scale, pObject->mUnknown32, pContext, 0);
            pPair = &pContext->mUnknownC;
        } else {
            AnimDecodePose(&pose, pEntry, scale, pObject->mUnknown32, pContext, 0);
            pPair = &pContext->mUnknown4;
        }
        fn_80227930(pPose->mUnknown8, pose.mUnknown8, pPose->mUnknown8, weight);
        fn_80227930(pPose->mUnknown20, pose.mUnknown20, pPose->mUnknown20, weight);
        Orient3Lerp(pPose->mUnknown36, pose.mUnknown36, pPose->mUnknown36, weight);
        OrientLerpAngle(&pPose->mUnknown32, pose.mUnknown32, pPose->mUnknown32, weight);
        if (pContext != 0) {
            AnimLerpFixedScaled(pPose->mUnknown48, pose.mUnknown48, pPose->mUnknown48, (int)(weight * 4095.0f), values,
                        pPair->mUnknown0, pPair->mUnknown4);
        } else {
            AnimLerpFixed(pPose->mUnknown48, pose.mUnknown48, pPose->mUnknown48, (int)(weight * 4095.0f), values);
        }
    }
    pPose->mUnknown6 = -1;
    switch (pObject->mUnknown32) {
    case 1:
        pPose->mUnknown6 = 0x18;
        break;
    default:
        pPose->mUnknown6 = 0x12;
        break;
    case 0:
        if (pEntry->mUnknown8 & 0x10) {
            pPose->mUnknown6 = 0x18;
        } else {
            pPose->mUnknown6 = 0x12;
        }
        break;
    }
}

void AnimBlendRootAngles(Object_8003DEC4 *pObject, AnimRootItem *pItems, unsigned short count, void *p)
{
    int angles[3];
    float total = 0.0f;
    float weight;
    unsigned int i;
    unsigned int bone;

    angles[0] = angles[1] = angles[2] = 0;
    for (i = 0; i < count; i++) {
        if (pItems[i].mUnknown1 != 0 && pItems[i].mUnknown48 == 0.0f) {
            weight = fn_801BE5D0(p, pItems[i].mUnknown8) * pItems[i].mUnknown30;
            total += weight;
            Orient3Lerp(angles, pItems[i].mUnknown10, angles, weight / total);
        }
    }
    pObject->mUnknown44.mUnknown32 = angles[1];
    pObject->mUnknown44.mUnknown48[0] = angles[0] >> 8;
    pObject->mUnknown44.mUnknown48[1] = 0;
    pObject->mUnknown44.mUnknown48[2] = angles[2] >> 8;
    if (pObject->mUnknown20 & 0x80) {
        for (bone = 26; bone < 27 && bone < pObject->mUnknown100->mUnknown6; bone++) {
            pObject->mUnknown44.mUnknown48[bone * 3] = pObject->mUnknown44.mUnknown48[bone * 3 + 1] =
                pObject->mUnknown44.mUnknown48[bone * 3 + 2] = 0;
        }
    } else {
        for (bone = 26; bone < 30 && bone < pObject->mUnknown100->mUnknown6; bone++) {
            pObject->mUnknown44.mUnknown48[bone * 3] = pObject->mUnknown44.mUnknown48[bone * 3 + 1] =
                pObject->mUnknown44.mUnknown48[bone * 3 + 2] = 0;
        }
    }
}

void AnimBlendRawEntries(Object_8003DEC4 *pObject, AnimBlendList *pBlend, unsigned int index, int count)
{
    AnimPose_t pose;
    short samples[32 * 3];
    AnimPose_t *pPose = &pObject->mUnknown116[index].mUnknown12;
    unsigned int entries = pBlend->mUnknown0;
    AnimBlendEntry *pEntry;
    unsigned int values;
    int mirrored;
    float weight;
    unsigned int i;

    pose.mUnknown48 = samples;
    if (entries == 0) {
        return;
    }
    values = pPose->mUnknown4 * 3;
    pEntry = &pBlend->mUnknown4[0];
    mirrored = 0;
    if (pEntry->mUnknown8 & 1) {
        mirrored = 1;
    }
    AnimCopyRawFrame(pPose, pEntry, mirrored);
    for (i = 1; i < entries; i++) {
        weight = 1.0f - pBlend->mUnknown4[i].mUnknown4;
        AnimCopyRawFrame(&pose, &pBlend->mUnknown4[i], mirrored);
        AnimLerpFixed(pPose->mUnknown48, pPose->mUnknown48, pose.mUnknown48, (int)(weight * 4095.0f), values);
    }
}

void AnimClearWeights(float *pValues)
{
    int i;

    for (i = 63; i >= 0; i--) {
        pValues[i] = 0.0f;
    }
}

void AnimReadWeights(float *pValues, AnimBlendEntry *pEntry)
{
    unsigned short *pData = (unsigned short *)pEntry->mpUnknown40;
    unsigned int i;
    unsigned int index;
    unsigned int level;

    AnimClearWeights(pValues);
    for (i = 0; i < pData[0]; i++) {
        index = pData[i + 1] & 0x3F;
        level = pData[i + 1] >> 6;
        index++;
        if (index < 64) {
            pValues[index] = level * (1.0f / 1024.0f) * 2.0f - 0.5f;
        }
    }
}

void AnimLerpFloats(float *pOut, float *pIn, int count, float t)
{
    while (count--) {
        *pOut = (*pIn - *pOut) * t + *pOut;
        pOut++;
        pIn++;
    }
}

void AnimBlendWeights(float *pValues, AnimBlendList *pBlend)
{
    float values[64];
    unsigned int entries = pBlend->mUnknown0;
    unsigned int i;

    if (entries == 0) {
        return;
    }
    AnimReadWeights(pValues, &pBlend->mUnknown4[0]);
    for (i = 1; i < entries; i++) {
        AnimReadWeights(values, &pBlend->mUnknown4[i]);
        AnimLerpFloats(pValues, values, 64, pBlend->mUnknown4[i].mUnknown4);
    }
}

void AnimResetWeights(float *pValues)
{
    AnimClearWeights(pValues);
}

void AnimBuildPoseMatrices(Object_8003DEC4 *pObject)
{
    fn_801D0508();
    if (!(pObject->mUnknown20 & 0x2000)) {
        fn_801D0C58(pObject->mUnknown44.mUnknown8);
        fn_801D09EC(pObject->mUnknown44.mUnknown32);
    }
    fn_802338D4(&pObject->mUnknown44, pObject->mUnknown100, 0xE0000000);
    fn_801D0544();
}
}
