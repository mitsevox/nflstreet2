/* Bone matrices for skinned models: a double-buffered pool of matrices handed out each frame,
   and the code that builds a model's bone hierarchy from its animation pose. */

#include <dolphin/os/OSCache.h>
#include <dolphin/mtx.h>
#include "engine/tmlib.h"
#include "game/fn_801D2B7C.h"
#include "engine/llquat.h"

extern void fn_801CFC58(int angle, void *pTable, float *pSin, float *pCos);
void QuatFromEuler(float *pQuat, int z, int y, int x);
void QuatSlerp(float *pOut, float *pA, float *pB, float t);

extern unsigned char lbl_803E9288[];

extern Mtx *lbl_803ECFD4[2];
extern int lbl_803ECFDC;
extern int lbl_803ECFE0;
extern int lbl_803ECFE4;

void TMClusterObjInit(int maxMatrices, int numBuffers)
{
    Mtx *pBuffer = fn_801D2B7C(sizeof(Mtx) * maxMatrices * numBuffers, 0, 0);

    lbl_803ECFD4[0] = pBuffer;
    lbl_803ECFD4[1] = pBuffer;
    if (numBuffers == 2) {
        lbl_803ECFD4[1] = pBuffer + maxMatrices;
    }
    lbl_803ECFE0 = maxMatrices;
    TMClusterObjResetMatrices();
}

void TMClusterObjShutdown(void)
{
    fn_801D2BD0(lbl_803ECFD4[0]);
}

void TMClusterObjInitObj(ClusterObj_80210724 *pObj)
{
    pObj->mpMatrices = 0;
    pObj->mNumMatrices = 0;
    pObj->mpCacheMatrices = (void *)0xE0000000;
}

void TMClusterObjResetMatrices(void)
{
    lbl_803ECFDC = !lbl_803ECFDC;
    lbl_803ECFE4 = 0;
}

void TMClusterObjAllocMatrices(ClusterObj_80210724 *pObj, int numMatrices)
{
    int used = lbl_803ECFE4;
    Mtx *pBuffer = lbl_803ECFD4[lbl_803ECFDC];

    numMatrices = (numMatrices + 1) & ~1;
    lbl_803ECFE4 = used + numMatrices;
    pObj->mNumMatrices = numMatrices;
    pObj->mpMatrices = pBuffer + used;
}

/* Builds the local matrix of one bone from its three angles and position and
   concatenates it with the parent's matrix. */
static inline void _TMClusterObjBuildBoneMatrix(Mtx *pParent, Mtx *pOut, int rx, int ry, int rz,
                                      float *pPos)
{
    float sx, cx, sy, cy, sz, cz;
    float sxsy, cxsy;
    Mtx44 mtx;

    fn_801CFC58(rx, lbl_803E9288, &sx, &cx);
    fn_801CFC58(ry, lbl_803E9288, &sy, &cy);
    fn_801CFC58(rz, lbl_803E9288, &sz, &cz);
    cxsy = cx * sy;
    sxsy = sx * sy;
    mtx[0][0] = cz * cy;
    mtx[1][0] = sz * cy;
    mtx[2][0] = -sy;
    mtx[0][1] = -sz * cx + cz * sxsy;
    mtx[1][1] = cz * cx + sz * sxsy;
    mtx[2][1] = cy * sx;
    mtx[0][2] = sz * sx + cz * cxsy;
    mtx[1][2] = -cz * sx + sz * cxsy;
    mtx[2][2] = cy * cx;
    mtx[0][3] = pPos[0];
    mtx[1][3] = pPos[1];
    mtx[2][3] = pPos[2];
    PSMTXConcat(*pParent, mtx, *pOut);
}

/* Build the bone hierarchy from pose rotations and positions, optionally
   blending angles with 12-bit weights, then publish the matrix buffer. */
void TMClusterObjSynthesizeMatrices(ClusterObj_80210724 *pObj, TMClusterPose_t *pPose, TMClusterBoneList_t *pBones, short (*pBlend)[3])
{
    Mtx *pMatrices = pObj->mpCacheMatrices;
    unsigned int i;

    if (pMatrices == 0) {
        pMatrices = pObj->mpMatrices;
    } else if (LCQueueLength() != 0) {
        LCQueueWait(0);
    }
    fn_801D0F80(pMatrices[0]);
    for (i = 1; i < pBones->mNumBones; i++) {
        TMClusterBone_t *pBone = &pBones->mpBones[i];
        int index = pBone->mIndex;
        int parent = pBone->mParent;
        float *pPos = pPose->mpPositions[index];
        int rz = pPose->mpRotations[index][2];
        int ry = pPose->mpRotations[index][1];
        int rx = pPose->mpRotations[index][0];

        if (pBlend != 0 && index != -1) {
            short *pTarget = pBlend[index];

            rz += ((pTarget[2] - rz) * pBone->mWeight) >> 12;
            ry += ((pTarget[1] - ry) * pBone->mWeight) >> 12;
            rx += ((pTarget[0] - rx) * pBone->mWeight) >> 12;
        }
        _TMClusterObjBuildBoneMatrix(&pMatrices[parent], &pMatrices[i], rx, ry, rz, pPos);
    }
    if (pObj->mpCacheMatrices != 0) {
        LCStoreData(pObj->mpMatrices, pObj->mpCacheMatrices, pBones->mNumBones * sizeof(Mtx));
    } else {
        DCStoreRange(pMatrices, pBones->mNumBones * sizeof(Mtx));
    }
}

/* Start with angle-blended matrices, replace flagged bones with
   quaternion-interpolated rotations, and publish the updated buffer. */
void TMClusterObjSynthesizeMatricesSlerp(ClusterObj_80210724 *pObj, TMClusterPose_t *pPose, TMClusterBoneList_t *pBones, short (*pBlend)[3],
                 unsigned char *pFlags)
{
    Mtx *pMatrices;
    unsigned int i;

    TMClusterObjSynthesizeMatrices(pObj, pPose, pBones, pBlend);
    pMatrices = pObj->mpCacheMatrices;
    if (pMatrices == 0) {
        pMatrices = pObj->mpMatrices;
    } else if (LCQueueLength() != 0) {
        LCQueueWait(0);
    }
    for (i = 1; i < pBones->mNumBones; i++) {
        TMClusterBone_t *pBone = &pBones->mpBones[i];
        int index = pBone->mIndex;

        if (pBlend != 0 && index != -1) {
            short *pTarget = pBlend[index];

            if (pFlags[index] != 0) {
                float targetQuat[4];
                float poseQuat[4];
                float quat[4];
                QuatEulerAngles_t angles;
                int rz = pPose->mpRotations[index][2];
                int ry = pPose->mpRotations[index][1];
                int rx = pPose->mpRotations[index][0];
                float *pPos = pPose->mpPositions[index];
                int parent = pBone->mParent;
                unsigned int weight;

                QuatFromEuler(targetQuat, pTarget[2] << 8, pTarget[1] << 8, pTarget[0] << 8);
                QuatFromEuler(poseQuat, rz << 8, ry << 8, rx << 8);
                weight = pBone->mWeight;
                QuatSlerp(quat, targetQuat, poseQuat, weight / 4096.0f);
                QuatToEuler(&angles, quat);
                rx = angles.mUnknown0 >> 8;
                ry = angles.mUnknown4 >> 8;
                rz = angles.mUnknown8 >> 8;
                _TMClusterObjBuildBoneMatrix(&pMatrices[parent], &pMatrices[i], rx, ry, rz, pPos);
            }
        }
    }
    if (pObj->mpCacheMatrices != 0) {
        LCStoreData(pObj->mpMatrices, pObj->mpCacheMatrices, pBones->mNumBones * sizeof(Mtx));
    } else {
        DCStoreRange(pMatrices, pBones->mNumBones * sizeof(Mtx));
    }
}
