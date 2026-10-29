#include "engine/particleLib.h"
#include "game/fn_802270D4.h"
#include "engine/cu_801D03D0.h"

float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFD78(float value);

void fn_801DFE0C(PartObj_801DE1E0 *pDst, PartObj_801DE1E0 *pSrc)
{
    switch (pDst->mEmitterType) {
    case 0:
        pDst->mEmitter.mPoint = pSrc->mEmitter.mPoint;
        break;
    case 1:
        pDst->mEmitter.mCase1 = pSrc->mEmitter.mCase1;
        break;
    case 2:
        pDst->mEmitter.mCase2 = pSrc->mEmitter.mCase2;
        break;
    case 3:
        pDst->mEmitter.mCase3 = pSrc->mEmitter.mCase3;
        break;
    }
}

void fn_801DFF10(PartObj_801DE1E0 *pObj)
{
    Vec3_801DE1E0 side;
    Vec3_801DE1E0 dir;
    Shape_801DF428 *pCase3;

    if (pObj->mEmitterType == 3) {
        pCase3 = &pObj->mEmitter.mCase3;
        fn_802276B4(&dir, &pCase3->mUnknown0C, &pCase3->mUnknown00);
        fn_802271F0(&pCase3->mUnknown2C, &dir);
        fn_802277DC(&side, &pCase3->mUnknown18, &pCase3->mUnknown2C);
        fn_802271F0(&side, &side);
        fn_802277DC(&pCase3->mUnknown38, &dir, &side);
        pCase3->mUnknown44 = pCase3->mUnknown28 - pCase3->mUnknown24;
    }
}

/* Fixed-origin modes use their first vector; mode 3 samples its two endpoints. */
void SampleEmitterPosition(Vec3_801DE1E0 *pOut, PartObj_801DE1E0 *pObj)
{
    switch (pObj->mEmitterType) {
    case 0: {
        Vec3_801DE1E0 *pPoint = &pObj->mEmitter.mPoint;
        pOut->x = pPoint->x;
        pOut->y = pPoint->y;
        pOut->z = pPoint->z;
        break;
    }
    case 1: {
        Vec3_801DE1E0 *pPoint = &pObj->mEmitter.mCase1.mUnknown00;
        pOut->x = pPoint->x;
        pOut->y = pPoint->y;
        pOut->z = pPoint->z;
        break;
    }
    case 2: {
        Vec3_801DE1E0 *pPoint = &pObj->mEmitter.mCase2.mUnknown00;
        pOut->x = pPoint->x;
        pOut->y = pPoint->y;
        pOut->z = pPoint->z;
        break;
    }
    case 3:
        fn_80227930(pOut, &pObj->mEmitter.mCase3.mUnknown0C, &pObj->mEmitter.mCase3.mUnknown00, fn_801DE1B8());
        break;
    }
}

/* Mode 2 scales the polar angle without scaling the azimuth draw. */
void SampleEmitterDirection(Vec3_801DE1E0 *pOut, PartObj_801DE1E0 *pObj)
{
    Payload1_801DFE0C *pCase1;
    Payload2_801DFE0C *pCase2;
    Shape_801DF428 *pCase3;

    switch (pObj->mEmitterType) {
    case 0: {
        int phi;
        int theta;
        Vec3_801DE1E0 dir;

        phi = fn_801CFD78(1.0f - 2.0f * fn_801DE1B8());
        theta = (int)(fn_801DE1B8() * 16777216.0f);
        dir.x = fn_801CFB94(theta) * fn_801CFB18(phi);
        dir.y = fn_801CFB18(theta) * fn_801CFB18(phi);
        dir.z = fn_801CFB94(phi);
        pOut->x = dir.x;
        pOut->y = dir.y;
        pOut->z = dir.z;
        break;
    }
    case 1:
        pCase1 = &pObj->mEmitter.mCase1;
        pOut->x = pCase1->mUnknown0C.x;
        pOut->y = pCase1->mUnknown0C.y;
        pOut->z = pCase1->mUnknown0C.z;
        break;
    case 2: {
        int phi;
        int theta;
        Vec3_801DE1E0 dir;

        pCase2 = &pObj->mEmitter.mCase2;
        phi = (int)(pCase2->mUnknown0C * 3.7450704e-07f * (float)fn_801CFD78(1.0f - fn_801DE1B8()) * 2670176.8f);
        theta = (int)(fn_801DE1B8() * 16777216.0f);
        dir.x = fn_801CFB94(theta) * fn_801CFB18(phi);
        dir.y = fn_801CFB18(theta) * fn_801CFB18(phi);
        dir.z = fn_801CFB94(phi);
        pOut->x = dir.x;
        pOut->y = dir.y;
        pOut->z = dir.z;
        break;
    }
    case 3:
        fn_801D0508();
        pCase3 = &pObj->mEmitter.mCase3;
        fn_801D0710(&pCase3->mUnknown2C.x, (int)((fn_801DE1B8() * pCase3->mUnknown44 + pCase3->mUnknown24) * 16777216.0f));
        fn_80227C2C(pOut, &pCase3->mUnknown38);
        fn_801D0544();
        break;
    }
}
