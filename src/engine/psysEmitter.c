#include "engine/particleLib.h"
#include "game/fn_802270D4.h"

float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFD78(float value);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0710(Vec3_801DE1E0 *pAxis, int angle);

void fn_801DFE0C(PartObj_801DE1E0 *pDst, PartObj_801DE1E0 *pSrc)
{
    switch (pDst->mEmitterType) {
    case 0:
        pDst->mEmitter.mPoint = pSrc->mEmitter.mPoint;
        break;
    case 1:
        pDst->mEmitter.mLine = pSrc->mEmitter.mLine;
        break;
    case 2:
        pDst->mEmitter.mSphere = pSrc->mEmitter.mSphere;
        break;
    case 3:
        pDst->mEmitter.mBox = pSrc->mEmitter.mBox;
        break;
    }
}

void fn_801DFF10(PartObj_801DE1E0 *pObj)
{
    Vec3_801DE1E0 side;
    Vec3_801DE1E0 dir;
    Shape_801DF428 *pBox;

    if (pObj->mEmitterType == 3) {
        pBox = &pObj->mEmitter.mBox;
        fn_802276B4(&dir, &pBox->mUnknown0C, &pBox->mUnknown00);
        fn_802271F0(&pBox->mUnknown2C, &dir);
        fn_802277DC(&side, &pBox->mUnknown18, &pBox->mUnknown2C);
        fn_802271F0(&side, &side);
        fn_802277DC(&pBox->mUnknown38, &dir, &side);
        pBox->mUnknown44 = pBox->mUnknown28 - pBox->mUnknown24;
    }
}

void fn_801DFFA8(Vec3_801DE1E0 *pOut, PartObj_801DE1E0 *pObj)
{
    Vec3_801DE1E0 *pPoint;

    switch (pObj->mEmitterType) {
    case 0:
        pPoint = &pObj->mEmitter.mPoint;
        pOut->x = pPoint->x;
        pOut->y = pPoint->y;
        pOut->z = pPoint->z;
        break;
    case 1:
        pPoint = &pObj->mEmitter.mLine.mUnknown00;
        pOut->x = pPoint->x;
        pOut->y = pPoint->y;
        pOut->z = pPoint->z;
        break;
    case 2:
        pPoint = &pObj->mEmitter.mSphere.mUnknown00;
        pOut->x = pPoint->x;
        pOut->y = pPoint->y;
        pOut->z = pPoint->z;
        break;
    case 3:
        fn_80227930(pOut, &pObj->mEmitter.mBox.mUnknown0C, &pObj->mEmitter.mBox.mUnknown00, fn_801DE1B8());
        break;
    }
}

void fn_801E0034(Vec3_801DE1E0 *pOut, PartObj_801DE1E0 *pObj)
{
    int phi;
    int theta;
    Vec3_801DE1E0 dir;
    ShapeLine_801DFE0C *pLine;
    ShapeSphere_801DFE0C *pSphere;
    Shape_801DF428 *pBox;

    switch (pObj->mEmitterType) {
    case 0:
        phi = fn_801CFD78(1.0f - 2.0f * fn_801DE1B8());
        theta = (int)(fn_801DE1B8() * 16777216.0f);
        dir.x = fn_801CFB94(theta) * fn_801CFB18(phi);
        dir.y = fn_801CFB18(theta) * fn_801CFB18(phi);
        dir.z = fn_801CFB94(phi);
        pOut->x = dir.x;
        pOut->y = dir.y;
        pOut->z = dir.z;
        break;
    case 1:
        pLine = &pObj->mEmitter.mLine;
        pOut->x = pLine->mUnknown0C.x;
        pOut->y = pLine->mUnknown0C.y;
        pOut->z = pLine->mUnknown0C.z;
        break;
    case 2:
        pSphere = &pObj->mEmitter.mSphere;
        phi = (int)(pSphere->mUnknown0C * 3.7450704e-07f * (float)fn_801CFD78(1.0f - fn_801DE1B8()) * 2670176.8f);
        theta = (int)(fn_801DE1B8() * 16777216.0f);
        dir.x = fn_801CFB94(theta) * fn_801CFB18(phi);
        dir.y = fn_801CFB18(theta) * fn_801CFB18(phi);
        dir.z = fn_801CFB94(phi);
        pOut->x = dir.x;
        pOut->y = dir.y;
        pOut->z = dir.z;
        break;
    case 3:
        fn_801D0508();
        pBox = &pObj->mEmitter.mBox;
        fn_801D0710(&pBox->mUnknown2C, (int)((fn_801DE1B8() * pBox->mUnknown44 + pBox->mUnknown24) * 16777216.0f));
        fn_80227C2C(pOut, &pBox->mUnknown38);
        fn_801D0544();
        break;
    }
}
