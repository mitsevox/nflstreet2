/* Skeleton joint chains: build a chain between two joints, pose it and clamp joint angles. */

#include "engine/cu_801C4960.h"
#include "game/fn_801D2B7C.h"
#include "engine/cu_801D03D0.h"
#include "game/fn_801EBC18.h"
#include "game/fn_802270D4.h"

typedef struct Limit_801C3EFC {
    int mRange[3][2];
} Limit_801C3EFC;

typedef struct ChainLink_801C3EFC {
    signed char mChild;
    unsigned char mBone;
    unsigned char mActive;
    unsigned char mUnk3;
} ChainLink_801C3EFC;

typedef struct Chain_801C3EFC {
    Skel_801C4960 *mpSkel;
    unsigned char mType;
    unsigned char mCount;
    unsigned char mStart;
    unsigned char mEnd;
    unsigned char mSolved;
    unsigned char mUnk9[3];
    ChainLink_801C3EFC *mpLinks;
} Chain_801C3EFC;

typedef struct ChainResult_801C3EFC {
    short x;
    short y;
    short z;
    short mBone;
} ChainResult_801C3EFC;

extern unsigned char lbl_803EBBD8;
extern unsigned char lbl_803EBBD9;
extern float lbl_803EBBDC;
extern float lbl_803EBBE0;
extern float lbl_803EBBE4;
extern float lbl_802F489C[3];
extern float lbl_802F48A8[3];

int fn_801CFD78(float x);
void fn_801EB660(float *pDst, float *pA, float *pB);
void fn_801EBBA4(float *pQuat, float *pAxis, int angle);
void fn_801EBEF8(float *pQuat, int z, int y, int x);
void fn_802271F0(float *pOut, float *p);
void fn_80227490(float *pOut, float *p, int x, int y, int z);
float fn_80227704(float *pA, float *pB);
float fn_8022772C(float *pA, float *pB);
void fn_802277DC(float *pOut, float *pA, float *pB);
void fn_80227C2C(float *pOut, float *p);

int fn_801C3EFC(int *pLimits, int turns, int *pAngle)
{
    int clamped = 0;
    int angle = *pAngle - (turns << 12);

    if (angle > pLimits[1]) {
        angle = pLimits[1];
        clamped = 1;
    } else if (angle < pLimits[0]) {
        angle = pLimits[0];
        clamped = 1;
    }
    *pAngle = angle + (turns << 12);
    return clamped;
}

void fn_801C3F48(Chain_801C3EFC *pChain, int first, int last, int (*pAngles)[3], float (*pOut)[16])
{
    Skel_801C4960 *pSkel = pChain->mpSkel;
    SkelNode_801C4960 *pNode = pSkel->mpJoints[pChain->mpLinks[first].mBone].mpNode;
    int bone;
    int i;

    for (i = first; i <= last; i++) {
        bone = pNode->mJoint;
        fn_801D0C58(pSkel->mPos[bone]);
        fn_801D0BCC(pAngles[bone][2], pAngles[bone][1], pAngles[bone][0]);
        fn_801D0F80(pOut[i]);
        pNode = pNode->mpChildren[pChain->mpLinks[i].mChild];
    }
}

static inline void fn_801C3EFC_Rot(int x, int y, int z)
{
    fn_801D0BCC(z << 8, y << 8, x << 8);
}

void fn_801C4010(Chain_801C3EFC *pChain, ChainResult_801C3EFC *pResult, SkelPose_801C4960 *pInst,
                 Limit_801C3EFC *pLimits, float *pTarget, int iterations)
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
    Angles_801EBC18 euler;
    Skel_801C4960 *pSkel;
    SkelEuler_801C4960 *pRest;
    Limit_801C3EFC *pLimit;
    float c;
    int bone;
    int count;
    int i;

    fn_801D04C4();
    pSkel = pChain->mpSkel;
    for (i = 0; i < 32; i++) {
        angles[i][0] = ((SkelEuler_801C4960 *)pInst->mpLocal)[i].x << 8;
        angles[i][1] = ((SkelEuler_801C4960 *)pInst->mpLocal)[i].y << 8;
        angles[i][2] = ((SkelEuler_801C4960 *)pInst->mpLocal)[i].z << 8;
    }
    fn_801D0558();
    fn_801D0C58(pInst->mPos);
    fn_801C3F48(pChain, 0, pChain->mStart - 1, angles, mats);
    while (iterations--) {
        fn_801D06D4(mats[pChain->mStart - 1]);
        fn_801C3F48(pChain, pChain->mStart, pChain->mEnd, angles, mats);
        endPos[0] = mats[pChain->mEnd][3];
        endPos[1] = mats[pChain->mEnd][7];
        endPos[2] = mats[pChain->mEnd][11];
        for (i = pChain->mEnd - 1; i >= pChain->mStart; i--) {
            bone = pChain->mpLinks[i].mBone;
            jointPos[0] = mats[i][3];
            jointPos[1] = mats[i][7];
            jointPos[2] = mats[i][11];
            fn_802276B4(toEnd, endPos, jointPos);
            fn_802276B4(toTarget, pTarget, jointPos);
            fn_801D06D4(mats[i]);
            fn_801D0E94();
            fn_80227C2C(toEnd, toEnd);
            fn_80227C2C(toTarget, toTarget);
            c = fn_8022772C(toEnd, toTarget);
            if (!(c >= 1.0f)) {
                fn_802277DC(axis, toTarget, toEnd);
                fn_802271F0(axis, axis);
                rot[0] = -fn_801CFD78(c);
                fn_801EBBA4(q, axis, rot[0]);
                fn_801EBEF8(cur, angles[bone][2], angles[bone][1], angles[bone][0]);
                fn_801EB660(q, cur, q);
                fn_801EBC18(&euler, q);
                rot[0] = (euler.mUnknown0 << 8) >> 8;
                rot[1] = (euler.mUnknown4 << 8) >> 8;
                rot[2] = (euler.mUnknown8 << 8) >> 8;
                pRest = &pSkel->mRest[bone];
                pLimit = &pLimits[bone];
                if (lbl_803EBBD9) {
                    fn_801C3EFC(pLimit->mRange[0], pRest->x, &rot[0]);
                    fn_801C3EFC(pLimit->mRange[1], pRest->y, &rot[1]);
                    fn_801C3EFC(pLimit->mRange[2], pRest->z, &rot[2]);
                }
                if (lbl_803EBBD8) {
                    angles[bone][0] = rot[0];
                    angles[bone][1] = rot[1];
                    angles[bone][2] = rot[2];
                }
                fn_801D06D4(mats[i - 1]);
                fn_801D0C58(pSkel->mPos[bone]);
                fn_801D0BCC(angles[bone][2], angles[bone][1], angles[bone][0]);
                fn_801D0C58(pSkel->mPos[bone + 1]);
                fn_801D0FB8(endPos);
            }
        }
    }
    fn_801D0544();
    count = 0;
    for (i = pChain->mStart; i <= pChain->mEnd; i++) {
        bone = pChain->mpLinks[i].mBone;
        pResult->mBone = bone;
        pResult->x = angles[bone][0] >> 8;
        pResult->y = angles[bone][1] >> 8;
        pResult->z = angles[bone][2] >> 8;
        pResult++;
        count++;
    }
    pChain->mSolved = count;
}

void fn_801C447C(Chain_801C3EFC *pChain, SkelPose_801C4960 *pInst, SkelEuler_801C4960 *pAngles, int stop)
{
    Skel_801C4960 *pSkel = pChain->mpSkel;
    SkelNode_801C4960 *pNode;
    int bone;
    int i;

    fn_801D0C58(pInst->mPos);
    fn_801D09EC(pInst->mRotY);
    pNode = pSkel->mpJoints[pChain->mpLinks[0].mBone].mpNode;
    for (i = 0; i < pChain->mCount; i++) {
        bone = pNode->mJoint;
        fn_801D0C58(pSkel->mPos[bone]);
        if (bone == stop) {
            break;
        }
        fn_801C3EFC_Rot(pAngles[bone].x, pAngles[bone].y, pAngles[bone].z);
        pNode = pNode->mpChildren[pChain->mpLinks[i].mChild];
    }
}

void fn_801C4550(Chain_801C3EFC *pChain, ChainResult_801C3EFC *pResult, SkelPose_801C4960 *pInst, int unused,
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
    SkelEuler_801C4960 *pAngles = pInst->mpLocal;
    int bone = pChain->mpLinks[pChain->mCount - 1].mBone;
    float d;

    fn_801D0508();
    fn_801C447C(pChain, pInst, pAngles, bone);
    fn_801D0F80(base);
    pos[0] = base[3];
    pos[1] = base[7];
    pos[2] = base[11];
    fn_802276B4(dir, pTarget, pos);
    fn_801D04C4();
    fn_801C3EFC_Rot(pAngles[bone].x, pAngles[bone].y, pAngles[bone].z);
    fn_801D0F80(joint);
    fn_80227C2C(up, lbl_802F48A8);
    fn_801D0544();
    up[0] = 0.0f;
    fn_802271F0(up, up);
    fn_801D04C4();
    fn_801D0E94();
    fn_80227C2C(fwd, up);
    fn_80227C2C(dir, dir);
    fn_801D0544();
    fn_80227490(dir, dir, 0, 0, *pYaw);
    if (!(dir[2] >= lbl_803EBBE0)) {
        d = __builtin_fabs(dir[0]);
        dir[2] = !(d >= lbl_803EBBDC) ? 1.0f - d : lbl_803EBBE0;
    }
    if (!(dir[1] <= lbl_803EBBE4)) {
        dir[1] = lbl_803EBBE4;
    }
    fn_80227490(dir, dir, 0, 0, -*pYaw);
    fn_802271F0(dir, dir);
    if (!(fn_80227704(lbl_802F489C, dir) >= 0.9999f)) {
        fn_802277DC(side, fwd, dir);
        fn_802277DC(up, dir, side);
        fn_801D03D0(rot);
        fn_801D0C0C(rot, side, up, dir);
        fn_801D0FFC(angles, rot);
        fn_801D06D4(base);
        fn_801D0664(rot);
        fn_801D0F80(((float (*)[16])pInst->mpOutput)[bone]);
        pChain->mSolved = 1;
        pResult->mBone = bone;
        pResult->x = angles[0] >> 8;
        pResult->y = angles[1] >> 8;
        pResult->z = angles[2] >> 8;
    }
    fn_801D0544();
}

Chain_801C3EFC *fn_801C47EC(Skel_801C4960 *pSkel, int start, int end, int type)
{
    SkelNode_801C4960 *pRoot = pSkel->mpJoints[0].mpNode;
    SkelNode_801C4960 *pLast = pSkel->mpJoints[end].mpNode;
    SkelNode_801C4960 *pNode;
    SkelNode_801C4960 *pParent;
    Chain_801C3EFC *pChain;
    unsigned int child;
    int count = 0;
    int i;

    for (pNode = pLast; pNode != pRoot && pNode->mJoint != 0; pNode = pNode->mpParent) {
        count++;
    }
    pChain = fn_801D2BB0(1, sizeof(Chain_801C3EFC) + ++count * sizeof(ChainLink_801C3EFC) + pSkel->mNumJoints * 8,
                         0, 0);
    pChain->mpLinks = (ChainLink_801C3EFC *)(pChain + 1);
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

void fn_801C4958(unsigned char enable)
{
    lbl_803EBBD9 = enable;
}
