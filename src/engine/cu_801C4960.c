#include "engine/cu_801C4960.h"
#include "engine/cu_801C2EB4.h"
#include "engine/cu_801D03D0.h"
#include "game/fn_801EBC18.h"

void fn_801EB660(float *pDst, float *pA, float *pB);
void fn_801EB814(float *pMatrix, float *pQuat);
void fn_801EBA64(float *pQuat);
void fn_801EBAA0(float *pDst, float *pVec, float *pQuat);
void fn_801EBEF8(float *pQuat, int z, int y, int x);

int fn_801C4D3C(SkelNode_801C4960 *pNode, void (*callback)(SkelNode_801C4960 *, void *), void *pContext);

static void fn_801C4960(Skel_801C4960 *pSkel, SkelNode_801C4960 *pNode, SkelPose_801C4960 *pPose)
{
}

static void fn_801C4964(Skel_801C4960 *pSkel, SkelNode_801C4960 *pUnused, SkelPose_801C4960 *pPose)
{
    SkelEuler_801C4960 *pEulers = pPose->mpLocal;
    float (*pQuats)[4] = pPose->mpOutput;
    int i;

    for (i = 0; i < pSkel->mNumJoints; i++) {
        fn_801EBEF8(pQuats[i], pEulers[i].z, pEulers[i].y, pEulers[i].x);
    }
}

static int fn_801C49D8(Skel_801C4960 *pSkel, SkelNode_801C4960 *pNode, SkelEuler_801C4960 *pEulers,
                       float (*pMatrices)[16])
{
    int last;
    int joint;
    SkelEuler_801C4960 *pEuler;
    int i;

    fn_801D04C4();
    for (last = -1; last < pNode->mId; pNode = pNode->mpChildren[0]) {
        joint = pNode->mJoint;
        fn_801D0C58(pSkel->mPos[joint]);
        pEuler = &pEulers[joint];
        fn_801D0ADC(pEuler->z);
        fn_801D09EC(pEuler->y);
        fn_801D08FC(pEuler->x);
        fn_801D0F80(pMatrices[joint]);
        if (pNode->mNumChildren > 1) {
            for (i = 0; i < pNode->mNumChildren; i++) {
                last = fn_801C49D8(pSkel, pNode->mpChildren[i], pEulers, pMatrices);
            }
        } else {
            last = pNode->mId;
        }
    }
    fn_801D0544();
    return last;
}

static void fn_801C4AC0(Skel_801C4960 *pSkel, SkelNode_801C4960 *pNode, SkelPose_801C4960 *pPose)
{
    fn_801D04C4();
    fn_801D0C58(pPose->mPos);
    fn_801D09EC(pPose->mRotY);
    fn_801C49D8(pSkel, pNode, pPose->mpLocal, pPose->mpOutput);
    fn_801D0544();
}

static void fn_801C4B1C(Skel_801C4960 *pSkel, SkelNode_801C4960 *pUnused, SkelPose_801C4960 *pPose)
{
    SkelEuler_801C4960 *pEulers = pPose->mpLocal;
    float (*pQuats)[4] = pPose->mpOutput;
    Angles_801EBC18 angles;
    int i;

    for (i = 0; i < pSkel->mNumJoints; i++) {
        fn_801EBC18(&angles, pQuats[i]);
        pEulers[i].x = angles.mUnknown0;
        pEulers[i].y = angles.mUnknown4;
        pEulers[i].z = angles.mUnknown8;
    }
}

static int fn_801C4BA0(Skel_801C4960 *pSkel, SkelNode_801C4960 *pNode, SkelXform_801C4960 *pXform,
                       float (*pQuats)[4], float (*pMatrices)[16])
{
    int last = -1;
    int joint;
    int i;

    while (last < pNode->mId) {
        joint = pNode->mJoint;
        fn_801EBAA0(pXform->mPos, pSkel->mPos[joint], pXform->mQuat);
        fn_801EB660(pXform->mQuat, pXform->mQuat, pQuats[joint]);
        pMatrices[joint][3] = pXform->mPos[0];
        pMatrices[joint][7] = pXform->mPos[1];
        pMatrices[joint][11] = pXform->mPos[2];
        fn_801EB814(pMatrices[joint], pXform->mQuat);
        if (pNode->mNumChildren > 1) {
            for (i = 0; i < pNode->mNumChildren; i++) {
                last = fn_801C4BA0(pSkel, pNode, pXform, pQuats, pMatrices);
            }
        } else {
            last = pNode->mId;
        }
        pNode = pNode->mpChildren[0];
    }
    return last;
}

static void fn_801C4CA0(Skel_801C4960 *pSkel, SkelNode_801C4960 *pNode, SkelPose_801C4960 *pPose)
{
    SkelXform_801C4960 xform;

    fn_801EBA64(xform.mQuat);
    fn_801D0FB8(xform.mPos);
    fn_801C4BA0(pSkel, pNode, &xform, pPose->mpLocal, pPose->mpOutput);
}

static void fn_801C4CF8(SkelNode_801C4960 *pNode, void *pBase)
{
    int i;

    pNode->mpParent = (SkelNode_801C4960 *)((char *)pBase + (int)pNode->mpParent);
    for (i = 0; i < pNode->mNumChildren; i++) {
        pNode->mpChildren[i] = (SkelNode_801C4960 *)((char *)pBase + (int)pNode->mpChildren[i]);
    }
}

int fn_801C4D3C(SkelNode_801C4960 *pNode, void (*callback)(SkelNode_801C4960 *, void *), void *pContext)
{
    int last = -1;
    int i;

    while (last < pNode->mId) {
        callback(pNode, pContext);
        if (pNode->mNumChildren > 1) {
            for (i = 0; i < pNode->mNumChildren; i++) {
                last = fn_801C4D3C(pNode->mpChildren[i], callback, pContext);
            }
        } else {
            last = pNode->mId;
        }
        pNode = pNode->mpChildren[0];
    }
    return last;
}

void fn_801C4DEC(Skel_801C4960 *pSkel)
{
    unsigned int i;

    if (!(pSkel->mFlags & 0x8000)) {
        pSkel->mpJoints = (SkelJoint_801C4960 *)((char *)pSkel + (int)pSkel->mpJoints);
        pSkel->mpRoot = (SkelNode_801C4960 *)((char *)pSkel + (int)pSkel->mpRoot);
        fn_801C4D3C(pSkel->mpRoot, fn_801C4CF8, pSkel);
        pSkel->mpRoot->mpParent = pSkel->mpRoot;
        for (i = 0; i < pSkel->mNumJoints; i++) {
            pSkel->mpJoints[i].mpNode = (SkelNode_801C4960 *)((char *)pSkel + (int)pSkel->mpJoints[i].mpNode);
        }
        pSkel->mFlags |= 0x8000;
    }
}

int fn_801C4E98(Skel_801C4960 *pSkel, const char *pName)
{
    SkelJoint_801C4960 *pJoints = pSkel->mpJoints;
    int i;

    for (i = 0; i < pSkel->mNumJoints && fn_801C2FE4(pName, pJoints[i].mName) != 0; i++) {
    }
    if (i == pSkel->mNumJoints) {
        i = -1;
    }
    return i;
}

void fn_801C4F10(Skel_801C4960 *pDst, Skel_801C4960 *pSrc)
{
    int i;

    for (i = 0; i < pDst->mNumJoints; i++) {
        pDst->mRest[i].x = pSrc->mRest[i].x;
        pDst->mRest[i].y = -pSrc->mRest[i].y;
        pDst->mRest[i].z = -pSrc->mRest[i].z;
    }
}

void (*lbl_802F48C0[48])(Skel_801C4960 *, SkelNode_801C4960 *, SkelPose_801C4960 *) = {
    fn_801C4960, fn_801C4964, fn_801C4960, fn_801C4960,
    fn_801C4B1C, fn_801C4960, fn_801C4960, fn_801C4960,
    fn_801C4960, fn_801C4960, fn_801C4960, fn_801C4960,
    fn_801C4960, fn_801C4960, fn_801C4960, fn_801C4960,
    fn_801C4960, fn_801C4960, fn_801C4AC0, fn_801C4960,
    fn_801C4960, fn_801C4960, fn_801C4CA0, fn_801C4960,
    fn_801C4960, fn_801C4960, fn_801C4960, fn_801C4960,
    fn_801C4960, fn_801C4960, fn_801C4960, fn_801C4960,
    fn_801C4960, fn_801C4960, fn_801C4960, fn_801C4960,
    fn_801C4960, fn_801C4960, fn_801C4960, fn_801C4960,
    fn_801C4960, fn_801C4960, fn_801C4960, fn_801C4960,
    fn_801C4960, fn_801C4960, fn_801C4960, fn_801C4960,
};
