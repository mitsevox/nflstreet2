#include "engine/particleLib.h"

int fn_801DFD40(void);
void fn_80227264(Vec3_801DE1E0 *pDst, Vec3_801DE1E0 *pSrc, float scale);
void fn_8022765C(Vec3_801DE1E0 *pDst, Vec3_801DE1E0 *pA, Vec3_801DE1E0 *pB);
float fn_80227704(Vec3_801DE1E0 *pA, Vec3_801DE1E0 *pB);

static void fn_801E01FC(PartObj_801DE1E0 *pObj, Particle_801DE1E0 *pParticle, float height)
{
    if (fn_801DFD40() == 0) {
        if (pParticle->mPos.y >= height) {
            return;
        }
        pParticle->mPos.y = height;
        fn_80227264(&pParticle->mVel, &pParticle->mVel, pObj->mUnknown288);
        pParticle->mVel.y = -pParticle->mVel.y;
    } else {
        if (pParticle->mPos.z >= height) {
            return;
        }
        pParticle->mPos.z = height;
        fn_80227264(&pParticle->mVel, &pParticle->mVel, pObj->mUnknown288);
        pParticle->mVel.z = -pParticle->mVel.z;
    }
}

static void fn_801E02A4(PartObj_801DE1E0 *pObj, Particle_801DE1E0 *pParticle, Vec3_801DE1E0 *pNormal, float distance)
{
    Vec3_801DE1E0 push;
    Vec3_801DE1E0 bounce;
    float depth;
    float speed;

    depth = fn_80227704(pNormal, &pParticle->mPos) + distance;
    if (depth >= 0.0f) {
        return;
    }
    fn_80227264(&push, pNormal, depth * -1.0f);
    fn_8022765C(&pParticle->mPos, &pParticle->mPos, &push);
    speed = fn_80227704(pNormal, &pParticle->mVel);
    if (speed >= 0.0f) {
        return;
    }
    fn_80227264(&bounce, pNormal, speed * (-1.0f - pObj->mUnknown288));
    fn_8022765C(&pParticle->mVel, &pParticle->mVel, &bounce);
}

void fn_801E0384(PartObj_801DE1E0 *pDst, PartObj_801DE1E0 *pSrc)
{
    switch (pDst->mCollisionType) {
    case 0:
        break;
    case 1:
        pDst->mCollision.mGround = pSrc->mCollision.mGround;
        break;
    case 2:
        pDst->mCollision.mPlane = pSrc->mCollision.mPlane;
        break;
    }
}

void fn_801E03F4(PartObj_801DE1E0 *pObj)
{
    Plane_801E0384 *pPlane;

    if (pObj->mCollisionType == 2) {
        pPlane = &pObj->mCollision.mPlane;
        pPlane->mDistance = -fn_80227704(&pPlane->mNormal, &pPlane->mPoint);
    }
}

void fn_801E043C(PartObj_801DE1E0 *pObj, Particle_801DE1E0 *pParticle)
{
    unsigned char i;
    Plane_801E0384 *pPlane;
    ColExt_801E043C *pExt;

    switch (pObj->mCollisionType) {
    case 0:
        break;
    case 1:
        fn_801E01FC(pObj, pParticle, pObj->mCollision.mGround.mHeight);
        break;
    case 2:
        pPlane = &pObj->mCollision.mPlane;
        fn_801E02A4(pObj, pParticle, &pPlane->mNormal, pPlane->mDistance);
        break;
    }
    for (i = 0; i < pObj->mColExtCount; i++) {
        pExt = &pObj->mColExt[i];
        switch (pExt->mType) {
        case 1:
            fn_801E01FC(pObj, pParticle, pExt->mData.mHeight);
            break;
        case 2:
            fn_801E02A4(pObj, pParticle, &pExt->mData.mPlane.mNormal, pExt->mData.mPlane.mDistance);
            break;
        }
    }
}

void fn_801E0520(PartObj_801DE1E0 *pObj)
{
    pObj->mColExtCount = 0;
}
