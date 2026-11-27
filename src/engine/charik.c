/* Skeleton joint chains: build a chain between two joints, pose it and clamp joint angles. */

#include "engine/skeleton.h"
#include "game/fn_801D2B7C.h"
#include "engine/llmatrix.h"
#include "engine/llquat.h"
#include "game/Vec3Magnitude.h"

typedef struct CharIKLimit_t {
    int mRange[3][2];
} CharIKLimit_t;

typedef struct CharIKLink_t {
    signed char mChild;
    unsigned char mBone;
    unsigned char mActive;
    unsigned char mUnk3;
} CharIKLink_t;

typedef struct CharIKChain_t {
    Skel_t *mpSkel;
    unsigned char mType;
    unsigned char mCount;
    unsigned char mStart;
    unsigned char mEnd;
    unsigned char mSolved;
    unsigned char mUnk9[3];
    CharIKLink_t *mpLinks;
} CharIKChain_t;

typedef struct CharIKResult_t {
    short x;
    short y;
    short z;
    short mBone;
} CharIKResult_t;

extern unsigned char lbl_803EBBD8;
extern unsigned char lbl_803EBBD9;
extern float lbl_803EBBDC;
extern float lbl_803EBBE0;
extern float lbl_803EBBE4;
extern float lbl_802F489C[3];
extern float lbl_802F48A8[3];

int MathArcCos(float x);
void QuatMultiply(float *pDst, float *pA, float *pB);
void QuatFromAxisAngle(float *pQuat, float *pAxis, int angle);
void QuatFromEuler(float *pQuat, int z, int y, int x);
void Vec3Normalize(float *pOut, float *p);
void Vec3RotateZYX(float *pOut, float *p, int x, int y, int z);
float Vec3DotProduct(float *pA, float *pB);
float Vec3CosAngle(float *pA, float *pB);
void Vec3CrossProduct(float *pOut, float *pA, float *pB);
void Vec3Mat33Mul(float *pOut, float *p);

int CharIKClampAngle(int *pLimits, int rest, int *pAngle)
{
    int clamped = 0;
    int angle = *pAngle - (rest << 12);

    if (angle > pLimits[1]) {
        angle = pLimits[1];
        clamped = 1;
    } else if (angle < pLimits[0]) {
        angle = pLimits[0];
        clamped = 1;
    }
    *pAngle = angle + (rest << 12);
    return clamped;
}

void CharIKBuildChainMatrices(CharIKChain_t *pChain, int first, int last, int (*pAngles)[3], float (*pOut)[16])
{
    Skel_t *pSkel = pChain->mpSkel;
    SkelNode_t *pNode = pSkel->mpJoints[pChain->mpLinks[first].mBone].mpNode;
    int bone;
    int i;

    for (i = first; i <= last; i++) {
        bone = pNode->mJoint;
        MatTranslate(pSkel->mPos[bone]);
        MatRotZYX(pAngles[bone][2], pAngles[bone][1], pAngles[bone][0]);
        MatStore(pOut[i]);
        pNode = pNode->mpChildren[pChain->mpLinks[i].mChild];
    }
}

static inline void _CharIKRotate(int x, int y, int z)
{
    MatRotZYX(z << 8, y << 8, x << 8);
}

static inline void _CharIKGetMatrixPos(float *pPos, float *pMatrix)
{
    pPos[0] = pMatrix[3];
    pPos[1] = pMatrix[7];
    pPos[2] = pMatrix[11];
}

static inline void _CharIKSetAngles(int *pDst, int *pSrc)
{
    pDst[0] = pSrc[0];
    pDst[1] = pSrc[1];
    pDst[2] = pSrc[2];
}

void CharIKSolveCCD(CharIKChain_t *pChain, CharIKResult_t *pResult, SkelPose_t *pInst,
                 CharIKLimit_t *pLimits, float *pTarget, unsigned int iterations)
{
    float toEnd[3];
    float toTarget[3];
    float jointPos[3];
    float mats[16][16];
    int rot[3];
    float axis[3];
    float endPos[3];
    float q[4];
    float cur[4];
    int angles[32][3];
    QuatEulerAngles_t euler;
    Skel_t *pSkel;
    SkelEuler_t *pRest;
    CharIKLimit_t *pLimit;
    float c;
    int bone;
    int count;
    int i;

    MatPush();
    pSkel = pChain->mpSkel;
    for (i = 0; i < 32; i++) {
        angles[i][0] = ((SkelEuler_t *)pInst->mpLocal)[i].x << 8;
        angles[i][1] = ((SkelEuler_t *)pInst->mpLocal)[i].y << 8;
        angles[i][2] = ((SkelEuler_t *)pInst->mpLocal)[i].z << 8;
    }
    MatMakeUnit();
    MatTranslate(pInst->mPos);
    CharIKBuildChainMatrices(pChain, 0, pChain->mStart - 1, angles, mats);
    while (iterations-- > 0) {
        i = pChain->mEnd - 1;
        MatLoad(mats[pChain->mStart - 1]);
        CharIKBuildChainMatrices(pChain, pChain->mStart, pChain->mEnd, angles, mats);
        _CharIKGetMatrixPos(endPos, mats[pChain->mEnd]);
        for (; i >= pChain->mStart; i--) {
            bone = pChain->mpLinks[i].mBone;
            _CharIKGetMatrixPos(jointPos, mats[i]);
            Vec3Sub(toEnd, endPos, jointPos);
            Vec3Sub(toTarget, pTarget, jointPos);
            MatLoad(mats[i]);
            MatTranspose();
            Vec3Mat33Mul(toEnd, toEnd);
            Vec3Mat33Mul(toTarget, toTarget);
            c = Vec3CosAngle(toEnd, toTarget);
            if (!(c >= 1.0f)) {
                Vec3CrossProduct(axis, toTarget, toEnd);
                Vec3Normalize(axis, axis);
                rot[0] = -MathArcCos(c);
                QuatFromAxisAngle(q, axis, rot[0]);
                QuatFromEuler(cur, angles[bone][2], angles[bone][1], angles[bone][0]);
                QuatMultiply(q, cur, q);
                QuatToEuler(&euler, q);
                rot[0] = (euler.mUnknown0 << 8) >> 8;
                rot[1] = (euler.mUnknown4 << 8) >> 8;
                rot[2] = (euler.mUnknown8 << 8) >> 8;
                pRest = &pSkel->mRest[bone];
                pLimit = &pLimits[bone];
                if (lbl_803EBBD9) {
                    CharIKClampAngle(pLimit->mRange[0], pRest->x, &rot[0]);
                    CharIKClampAngle(pLimit->mRange[1], pRest->y, &rot[1]);
                    CharIKClampAngle(pLimit->mRange[2], pRest->z, &rot[2]);
                }
                if (lbl_803EBBD8) {
                    _CharIKSetAngles(angles[bone], rot);
                }
                MatLoad(mats[i - 1]);
                MatTranslate(pSkel->mPos[bone]);
                MatRotZYX(angles[bone][2], angles[bone][1], angles[bone][0]);
                MatTranslate(pSkel->mPos[bone + 1]);
                MatGetPos(endPos);
            }
        }
    }
    MatPop();
    count = 0;
    for (i = pChain->mStart; i <= pChain->mEnd; i++) {
        bone = pChain->mpLinks[i].mBone;
        pResult[count].mBone = bone;
        pResult[count].x = angles[bone][0] >> 8;
        pResult[count].y = angles[bone][1] >> 8;
        pResult[count].z = angles[bone][2] >> 8;
        count++;
    }
    pChain->mSolved = count;
}

void CharIKTransformToJoint(CharIKChain_t *pChain, SkelPose_t *pInst, SkelEuler_t *pAngles, int stop)
{
    Skel_t *pSkel = pChain->mpSkel;
    SkelNode_t *pNode;
    int bone;
    int i;

    MatTranslate(pInst->mPos);
    MatRotY(pInst->mRotY);
    pNode = pSkel->mpJoints[pChain->mpLinks[0].mBone].mpNode;
    for (i = 0; i < pChain->mCount; i++) {
        bone = pNode->mJoint;
        MatTranslate(pSkel->mPos[bone]);
        if (bone == stop) {
            break;
        }
        _CharIKRotate(pAngles[bone].x, pAngles[bone].y, pAngles[bone].z);
        pNode = pNode->mpChildren[pChain->mpLinks[i].mChild];
    }
}

void CharIKSolveLookAt(CharIKChain_t *pChain, CharIKResult_t *pResult, SkelPose_t *pInst, int unused,
                 float *pTarget, int *pYaw)
{
    int angles[3];
    float dir[3];
    float side[3];
    float fwd[3];
    float up[3];
    float pos[3];
    float base[16];
    float rot[16];
    float joint[16];
    SkelEuler_t *pAngles = pInst->mpLocal;
    int bone = pChain->mpLinks[pChain->mCount - 1].mBone;
    float d;

    MatPushUnit();
    CharIKTransformToJoint(pChain, pInst, pAngles, bone);
    MatStore(base);
    pos[0] = base[3];
    pos[1] = base[7];
    pos[2] = base[11];
    Vec3Sub(dir, pTarget, pos);
    MatPush();
    _CharIKRotate(pAngles[bone].x, pAngles[bone].y, pAngles[bone].z);
    MatStore(joint);
    Vec3Mat33Mul(up, lbl_802F48A8);
    MatPop();
    up[0] = 0.0f;
    Vec3Normalize(up, up);
    MatPush();
    MatTranspose();
    Vec3Mat33Mul(fwd, up);
    Vec3Mat33Mul(dir, dir);
    MatPop();
    Vec3RotateZYX(dir, dir, 0, 0, *pYaw);
    if (!(dir[2] >= lbl_803EBBE0)) {
        d = __builtin_fabs(dir[0]);
        dir[2] = !(d >= lbl_803EBBDC) ? 1.0f - d : lbl_803EBBE0;
    }
    if (!(dir[1] <= lbl_803EBBE4)) {
        dir[1] = lbl_803EBBE4;
    }
    Vec3RotateZYX(dir, dir, 0, 0, -*pYaw);
    Vec3Normalize(dir, dir);
    if (!(Vec3DotProduct(lbl_802F489C, dir) >= 0.9999f)) {
        Vec3CrossProduct(side, fwd, dir);
        Vec3CrossProduct(up, dir, side);
        MatMakeUnitMatrix(rot);
        MatSetAxes(rot, side, up, dir);
        MatGetRotFromMatrixZYX(angles, rot);
        MatLoad(base);
        MatCat(rot);
        MatStore(((float (*)[16])pInst->mpOutput)[bone]);
        pChain->mSolved = 1;
        pResult->mBone = bone;
        pResult->x = angles[0] >> 8;
        pResult->y = angles[1] >> 8;
        pResult->z = angles[2] >> 8;
    }
    MatPop();
}

CharIKChain_t *CharIKCreateChain(Skel_t *pSkel, int start, int end, int type)
{
    SkelNode_t *pRoot = pSkel->mpJoints[0].mpNode;
    SkelNode_t *pLast = pSkel->mpJoints[end].mpNode;
    SkelNode_t *pNode;
    SkelNode_t *pParent;
    CharIKChain_t *pChain;
    unsigned int child;
    int count = 0;
    int i;

    for (pNode = pLast; pNode != pRoot && pNode->mJoint != 0; pNode = pNode->mpParent) {
        count++;
    }
    pChain = fn_801D2BB0(1, sizeof(CharIKChain_t) + ++count * sizeof(CharIKLink_t) + pSkel->mNumJoints * 8,
                         0, 0);
    pChain->mpLinks = (CharIKLink_t *)(pChain + 1);
    pNode = pLast;
    i = count - 1;
    child = 0;
    for (;;) {
        pChain->mpLinks[i].mChild = child;
        pChain->mpLinks[i].mBone = pNode->mJoint;
        pChain->mpLinks[i].mActive = 1;
        pChain->mpLinks[i].mUnk3 = 0;
        if (pNode->mJoint == start) {
            pChain->mStart = i;
        }
        if (pNode->mJoint == end) {
            pChain->mEnd = i;
        }
        if (i <= 0) {
            break;
        }
        pParent = pNode->mpParent;
        for (child = 0; child < pParent->mNumChildren && pParent->mpChildren[child] != pNode; child++) {
        }
        pNode = pParent;
        i--;
    }
    pChain->mpSkel = pSkel;
    pChain->mCount = count;
    pChain->mType = type;
    return pChain;
}

void CharIKEnableLimits(unsigned char enable)
{
    lbl_803EBBD9 = enable;
}
