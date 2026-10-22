#include <dolphin/os/OSCache.h>
#include <dolphin/mtx.h>
#include "engine/tmlib.h"
#include "game/fn_801D2B7C.h"

extern void fn_801CFC58(int angle, void *pTable, float *pSin, float *pCos);

extern unsigned char lbl_803E9288[];

typedef f32 Mtx34_80213444[3][4];

extern Mtx34_80213444 *lbl_803ECFD4[2];
extern int lbl_803ECFDC;
extern int lbl_803ECFE0;
extern int lbl_803ECFE4;

void fn_80213444(int maxMatrices, int numBuffers)
{
    Mtx34_80213444 *pBuffer = fn_801D2B7C(sizeof(Mtx34_80213444) * maxMatrices * numBuffers, 0, 0);

    lbl_803ECFD4[0] = pBuffer;
    lbl_803ECFD4[1] = pBuffer;
    if (numBuffers == 2) {
        lbl_803ECFD4[1] = pBuffer + maxMatrices;
    }
    lbl_803ECFE0 = maxMatrices;
    fn_802134E8();
}

void fn_802134AC(void)
{
    fn_801D2BD0(lbl_803ECFD4[0]);
}

void fn_802134D0(ClusterObj_80210724 *pObj)
{
    pObj->mpMatrices = 0;
    pObj->mNumMatrices = 0;
    pObj->mpCacheMatrices = (void *)0xE0000000;
}

void fn_802134E8(void)
{
    lbl_803ECFDC = !lbl_803ECFDC;
    lbl_803ECFE4 = 0;
}

void fn_80213504(ClusterObj_80210724 *pObj, int numMatrices)
{
    int used = lbl_803ECFE4;
    Mtx34_80213444 *pBuffer = lbl_803ECFD4[lbl_803ECFDC];

    numMatrices = (numMatrices + 1) & ~1;
    lbl_803ECFE4 = used + numMatrices;
    pObj->mNumMatrices = numMatrices;
    pObj->mpMatrices = pBuffer + used;
}

void fn_8021353C(ClusterObj_80210724 *pObj, Pose_8021353C *pPose, BoneList_8021353C *pBones, short (*pBlend)[3])
{
    Mtx34_80213444 *pMatrices = pObj->mpCacheMatrices;
    unsigned int i;

    if (pMatrices == 0) {
        pMatrices = pObj->mpMatrices;
    } else if (LCQueueLength() != 0) {
        LCQueueWait(0);
    }
    fn_801D0F80(pMatrices[0]);
    for (i = 1; i < pBones->mNumBones; i++) {
        BoneEntry_8021353C *pBone = &pBones->mpBones[i];
        int index = pBone->mIndex;
        Mtx34_80213444 *pParent = &pMatrices[pBone->mParent];
        float *pPos = pPose->mpPositions[index];
        int rx = pPose->mpRotations[index][0];
        int ry = pPose->mpRotations[index][1];
        int rz = pPose->mpRotations[index][2];
        float sx, cx, sy, cy, sz, cz;
        float sxsy, cxsy;
        f32 mtx[4][4];

        if (pBlend != 0 && index != -1) {
            rx += ((pBlend[index][0] - rx) * pBone->mWeight) >> 12;
            ry += ((pBlend[index][1] - ry) * pBone->mWeight) >> 12;
            rz += ((pBlend[index][2] - rz) * pBone->mWeight) >> 12;
        }
        fn_801CFC58(rx, lbl_803E9288, &sx, &cx);
        fn_801CFC58(ry, lbl_803E9288, &sy, &cy);
        fn_801CFC58(rz, lbl_803E9288, &sz, &cz);
        sxsy = sx * sy;
        cxsy = cx * sy;
        mtx[0][0] = cz * cy;
        mtx[0][1] = -sz * cx + cz * sxsy;
        mtx[0][2] = sz * sx + cz * cxsy;
        mtx[1][0] = sz * cy;
        mtx[1][1] = cz * cx + sz * sxsy;
        mtx[1][2] = -cz * sx + sz * cxsy;
        mtx[2][0] = -sy;
        mtx[2][1] = cy * sx;
        mtx[2][2] = cy * cx;
        mtx[0][3] = pPos[0];
        mtx[1][3] = pPos[1];
        mtx[2][3] = pPos[2];
        PSMTXConcat(*pParent, mtx, pMatrices[i]);
    }
    if (pObj->mpCacheMatrices != 0) {
        LCStoreData(pObj->mpMatrices, pObj->mpCacheMatrices, pBones->mNumBones * sizeof(Mtx34_80213444));
    } else {
        DCStoreRange(pMatrices, pBones->mNumBones * sizeof(Mtx34_80213444));
    }
}
