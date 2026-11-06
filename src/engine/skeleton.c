/* Character skeletons: relocates a loaded skeleton file, walks its joint hierarchy, finds joints by
   name and converts joint rotations between Euler angles, quaternions and global matrices. */

#include "engine/skeleton.h"
#include "engine/cu_801C2EB4.h"
#include "engine/llmatrix.h"
#include "engine/llquat.h"

void QuatMultiply(float *pDst, float *pA, float *pB);
void QuatToMatrix(float *pMatrix, float *pQuat);
void QuatFromMat(float *pQuat);
void QuatTranslate(float *pDst, float *pVec, float *pQuat);
void QuatFromEuler(float *pQuat, int z, int y, int x);

int CharTraverseSkeleton(SkelNode_t *pNode, void (*callback)(SkelNode_t *, void *), void *pContext);

static void _SkelNullFunc(Skel_t *pSkel, SkelNode_t *pNode, SkelPose_t *pPose)
{
}

static void _SkelEulerLToQuatL(Skel_t *pSkel, SkelNode_t *pUnused, SkelPose_t *pPose)
{
    SkelEuler_t *pEulers = pPose->mpLocal;
    float (*pQuats)[4] = pPose->mpOutput;
    int i;

    for (i = 0; i < pSkel->mNumJoints; i++) {
        QuatFromEuler(pQuats[i], pEulers[i].z, pEulers[i].y, pEulers[i].x);
    }
}

static int _SkelEulerLToMatrixGHierarchy(Skel_t *pSkel, SkelNode_t *pNode, SkelEuler_t *pEulers,
                       float (*pMatrices)[16])
{
    int last;
    int joint;
    SkelEuler_t *pEuler;
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
                last = _SkelEulerLToMatrixGHierarchy(pSkel, pNode->mpChildren[i], pEulers, pMatrices);
            }
        } else {
            last = pNode->mId;
        }
    }
    fn_801D0544();
    return last;
}

static void _SkelEulerLToMatrixG(Skel_t *pSkel, SkelNode_t *pNode, SkelPose_t *pPose)
{
    fn_801D04C4();
    fn_801D0C58(pPose->mPos);
    fn_801D09EC(pPose->mRotY);
    _SkelEulerLToMatrixGHierarchy(pSkel, pNode, pPose->mpLocal, pPose->mpOutput);
    fn_801D0544();
}

static void _SkelQuatLToEulerL(Skel_t *pSkel, SkelNode_t *pUnused, SkelPose_t *pPose)
{
    SkelEuler_t *pEulers = pPose->mpLocal;
    float (*pQuats)[4] = pPose->mpOutput;
    QuatEulerAngles_t angles;
    int i;

    for (i = 0; i < pSkel->mNumJoints; i++) {
        QuatToEuler(&angles, pQuats[i]);
        pEulers[i].x = angles.mUnknown0;
        pEulers[i].y = angles.mUnknown4;
        pEulers[i].z = angles.mUnknown8;
    }
}

static int _SkelQuatLToMatrixGHierarchy(Skel_t *pSkel, SkelNode_t *pNode, SkelXform_t *pXform,
                       float (*pQuats)[4], float (*pMatrices)[16])
{
    int last = -1;
    int joint;
    int i;

    while (last < pNode->mId) {
        joint = pNode->mJoint;
        QuatTranslate(pXform->mPos, pSkel->mPos[joint], pXform->mQuat);
        QuatMultiply(pXform->mQuat, pXform->mQuat, pQuats[joint]);
        pMatrices[joint][3] = pXform->mPos[0];
        pMatrices[joint][7] = pXform->mPos[1];
        pMatrices[joint][11] = pXform->mPos[2];
        QuatToMatrix(pMatrices[joint], pXform->mQuat);
        if (pNode->mNumChildren > 1) {
            for (i = 0; i < pNode->mNumChildren; i++) {
                last = _SkelQuatLToMatrixGHierarchy(pSkel, pNode, pXform, pQuats, pMatrices);
            }
        } else {
            last = pNode->mId;
        }
        pNode = pNode->mpChildren[0];
    }
    return last;
}

static void _SkelQuatLToMatrixG(Skel_t *pSkel, SkelNode_t *pNode, SkelPose_t *pPose)
{
    SkelXform_t xform;

    QuatFromMat(xform.mQuat);
    fn_801D0FB8(xform.mPos);
    _SkelQuatLToMatrixGHierarchy(pSkel, pNode, &xform, pPose->mpLocal, pPose->mpOutput);
}

static void _SkelRelocateHierarchyNode(SkelNode_t *pNode, void *pBase)
{
    int i;

    pNode->mpParent = (SkelNode_t *)((char *)pBase + (int)pNode->mpParent);
    for (i = 0; i < pNode->mNumChildren; i++) {
        pNode->mpChildren[i] = (SkelNode_t *)((char *)pBase + (int)pNode->mpChildren[i]);
    }
}

int CharTraverseSkeleton(SkelNode_t *pNode, void (*callback)(SkelNode_t *, void *), void *pContext)
{
    int last = -1;
    int i;

    while (last < pNode->mId) {
        callback(pNode, pContext);
        if (pNode->mNumChildren > 1) {
            for (i = 0; i < pNode->mNumChildren; i++) {
                last = CharTraverseSkeleton(pNode->mpChildren[i], callback, pContext);
            }
        } else {
            last = pNode->mId;
        }
        pNode = pNode->mpChildren[0];
    }
    return last;
}

void CharRelocateSkeleton(Skel_t *pSkel)
{
    unsigned int i;

    if (!(pSkel->mFlags & 0x8000)) {
        pSkel->mpJoints = (SkelJoint_t *)((char *)pSkel + (int)pSkel->mpJoints);
        pSkel->mpRoot = (SkelNode_t *)((char *)pSkel + (int)pSkel->mpRoot);
        CharTraverseSkeleton(pSkel->mpRoot, _SkelRelocateHierarchyNode, pSkel);
        pSkel->mpRoot->mpParent = pSkel->mpRoot;
        for (i = 0; i < pSkel->mNumJoints; i++) {
            pSkel->mpJoints[i].mpNode = (SkelNode_t *)((char *)pSkel + (int)pSkel->mpJoints[i].mpNode);
        }
        pSkel->mFlags |= 0x8000;
    }
}

int CharSkelGetJointByName(Skel_t *pSkel, const char *pName)
{
    SkelJoint_t *pJoints = pSkel->mpJoints;
    int i;

    for (i = 0; i < pSkel->mNumJoints && fn_801C2FE4(pName, pJoints[i].mName) != 0; i++) {
    }
    if (i == pSkel->mNumJoints) {
        i = -1;
    }
    return i;
}

void CharSkelMirrorRest(Skel_t *pDst, Skel_t *pSrc)
{
    int i;

    for (i = 0; i < pDst->mNumJoints; i++) {
        pDst->mRest[i].x = pSrc->mRest[i].x;
        pDst->mRest[i].y = -pSrc->mRest[i].y;
        pDst->mRest[i].z = -pSrc->mRest[i].z;
    }
}

void (*_Skel_aConvertFuncs[48])(Skel_t *, SkelNode_t *, SkelPose_t *) = {
    _SkelNullFunc, _SkelEulerLToQuatL, _SkelNullFunc, _SkelNullFunc,
    _SkelQuatLToEulerL, _SkelNullFunc, _SkelNullFunc, _SkelNullFunc,
    _SkelNullFunc, _SkelNullFunc, _SkelNullFunc, _SkelNullFunc,
    _SkelNullFunc, _SkelNullFunc, _SkelNullFunc, _SkelNullFunc,
    _SkelNullFunc, _SkelNullFunc, _SkelEulerLToMatrixG, _SkelNullFunc,
    _SkelNullFunc, _SkelNullFunc, _SkelQuatLToMatrixG, _SkelNullFunc,
    _SkelNullFunc, _SkelNullFunc, _SkelNullFunc, _SkelNullFunc,
    _SkelNullFunc, _SkelNullFunc, _SkelNullFunc, _SkelNullFunc,
    _SkelNullFunc, _SkelNullFunc, _SkelNullFunc, _SkelNullFunc,
    _SkelNullFunc, _SkelNullFunc, _SkelNullFunc, _SkelNullFunc,
    _SkelNullFunc, _SkelNullFunc, _SkelNullFunc, _SkelNullFunc,
    _SkelNullFunc, _SkelNullFunc, _SkelNullFunc, _SkelNullFunc,
};
