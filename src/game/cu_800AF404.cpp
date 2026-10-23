#include "game/cu_8008E978.h"

extern "C" {
void fn_801C4010(Chain_800AF404 *pChain, void *pResult, Pose_80041930 *pPose, Item_800AF82C *pLimits,
                 float *pTarget, int count);
void fn_801C4550(Chain_800AF404 *pChain, void *pResult, Pose_80041930 *pPose, Item_800AF82C *pLimits,
                 float *pTarget, int *pValue);

extern int lbl_803EAB08;
}

extern "C" void fn_800AF404(Entry_800AF82C *p, void *pResult, float *pTarget)
{
    Chain_800AF404 *pChain = (Chain_800AF404 *)p->mpUnknown8;

    pChain->mUnknown8 = 0;
    switch (pChain->mType) {
    case 0:
        fn_801C4550(pChain, pResult, p->mpUnknown0, p->mpUnknown4, pTarget, p->mUnknown30);
        break;
    case 1:
        fn_801C4010(pChain, pResult, p->mpUnknown0, p->mpUnknown4, pTarget, (int)(float)lbl_803EAB08);
        break;
    }
}

extern "C" {
void fn_800AF2AC(Chain_800AF404 *pChain, Pose_80041930 *pPose, Source_800AF2AC *pSource);
void fn_800AF304(Chain_800AF404 *pChain, Pose_80041930 *pPose, Source_800AF2AC *pSource, float t);
int fn_801C384C(float *pValue, float *pSpeed, float dest, float maxSpeed, float accel);

extern Source_800AF2AC lbl_8030F9FC[];
extern Vector_80039F5C lbl_802D870C[];
extern Vector_80039F5C lbl_802D8730[];
}

extern "C" void fn_800AF4A8(Entry_800AF82C *p)
{
    Vector_80039F5C *pMax;
    Vector_80039F5C *pAccel;

    if (p->mpUnknown14 != 0) {
        fn_800AF404(p, lbl_8030F9FC, &p->mUnknown18.mX);
        if (p->mUnknownC == 1.0f) {
            fn_800AF2AC((Chain_800AF404 *)p->mpUnknown8, p->mpUnknown0, lbl_8030F9FC);
        } else {
            fn_800AF304((Chain_800AF404 *)p->mpUnknown8, p->mpUnknown0, lbl_8030F9FC, p->mUnknownC);
        }
        pMax = &lbl_802D8730[p->mUnknown3D];
        pAccel = &lbl_802D870C[p->mUnknown3D];
        fn_801C384C(&p->mUnknown18.mX, &p->mUnknown24.mX, p->mpUnknown14->mX, pMax->mX, pAccel->mX);
        fn_801C384C(&p->mUnknown18.mY, &p->mUnknown24.mY, p->mpUnknown14->mY, pMax->mY, pAccel->mY);
        fn_801C384C(&p->mUnknown18.mZ, &p->mUnknown24.mZ, p->mpUnknown14->mZ, pMax->mZ, pAccel->mZ);
    } else {
        fn_800AF404(p, lbl_8030F9FC, &p->mUnknown18.mX);
        fn_800AF304((Chain_800AF404 *)p->mpUnknown8, p->mpUnknown0, lbl_8030F9FC, 1.0f - p->mUnknownC);
    }
    if (p->mUnknown10 != 0.0f) {
        p->mUnknownC += p->mUnknown10;
        if (p->mUnknownC >= 1.0f) {
            p->mUnknownC = 1.0f;
            p->mUnknown10 = 0.0f;
        }
    }
    if (p->mpUnknown14 == 0 && p->mUnknownC == 1.0f) {
        p->mUnknown3C = 0;
    }
}

extern "C" void fn_800AF87C(Entry_800AF82C *pEntries, int index, Vector_80039F5C *pTarget, unsigned int count)
{
    Entry_800AF82C *p = &pEntries[index];

    if (p->mpUnknown14 == 0) {
        if (p->mUnknown3C == 0) {
            p->mUnknownC = 1.0f / count;
            p->mUnknown18.mX = pTarget->mX;
            p->mUnknown18.mY = pTarget->mY;
            p->mUnknown18.mZ = pTarget->mZ;
            Vector_80039F5C *pVector = &p->mUnknown24;

            pVector->mX = pVector->mY = pVector->mZ = 0.0f;
            p->mUnknown3C = 1;
        } else {
            p->mUnknownC = 1.0f - p->mUnknownC;
        }
        p->mUnknown10 = 1.0f / count;
    }
    p->mpUnknown14 = pTarget;
}
