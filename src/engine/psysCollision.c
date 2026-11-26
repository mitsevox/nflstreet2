/* Particle collisions: bounces particles off the ground or a plane, plus extra collision
   entries a particle system can carry. */

#include "engine/particleLib.h"


static void _calcGroundCollision(ParticleSysObj_t *pObj, PsysParticle_t *pParticle, float height)
{
    if (ParticleLibGetOrientation() == 0) {
        if (pParticle->mPos.y >= height) {
            return;
        }
        pParticle->mPos.y = height;
        Vec3Scale(&pParticle->mVel, &pParticle->mVel, pObj->mUnknown288);
        pParticle->mVel.y = -pParticle->mVel.y;
    } else {
        if (pParticle->mPos.z >= height) {
            return;
        }
        pParticle->mPos.z = height;
        Vec3Scale(&pParticle->mVel, &pParticle->mVel, pObj->mUnknown288);
        pParticle->mVel.z = -pParticle->mVel.z;
    }
}

static void _calcPlaneCollision(ParticleSysObj_t *pObj, PsysParticle_t *pParticle, Vec3_801DE1E0 *pNormal, float distance)
{
    Vec3_801DE1E0 push;
    Vec3_801DE1E0 bounce;
    float depth;
    float speed;

    depth = Vec3DotProduct(pNormal, &pParticle->mPos) + distance;
    if (depth >= 0.0f) {
        return;
    }
    Vec3Scale(&push, pNormal, depth * -1.0f);
    Vec3Add(&pParticle->mPos, &pParticle->mPos, &push);
    speed = Vec3DotProduct(pNormal, &pParticle->mVel);
    if (speed >= 0.0f) {
        return;
    }
    Vec3Scale(&bounce, pNormal, speed * (-1.0f - pObj->mUnknown288));
    Vec3Add(&pParticle->mVel, &pParticle->mVel, &bounce);
}

/* Copy only the payload selected by the destination collision type. */
void PsysColInitParms(ParticleSysObj_t *pDst, ParticleSysObj_t *pSrc)
{
    switch (pDst->mCollisionType) {
    case 0:
        break;
    case 1:
        pDst->mCollision.mWord = pSrc->mCollision.mWord;
        break;
    case 2:
        pDst->mCollision.mPlane = pSrc->mCollision.mPlane;
        break;
    }
}

void PsysColPrecalcDependantVals(ParticleSysObj_t *pObj)
{
    PsysColPlane_t *pPlane;

    if (pObj->mCollisionType == 2) {
        pPlane = &pObj->mCollision.mPlane;
        pPlane->mDistance = -Vec3DotProduct(&pPlane->mNormal, &pPlane->mPoint);
    }
}

void PsysColCalcCollision(ParticleSysObj_t *pObj, PsysParticle_t *pParticle)
{
    unsigned char i;
    PsysColPlane_t *pPlane;
    PsysColExt_t *pExt;

    switch (pObj->mCollisionType) {
    case 0:
        break;
    case 1:
        _calcGroundCollision(pObj, pParticle, pObj->mCollision.mGround.mHeight);
        break;
    case 2:
        pPlane = &pObj->mCollision.mPlane;
        _calcPlaneCollision(pObj, pParticle, &pPlane->mNormal, pPlane->mDistance);
        break;
    }
    for (i = 0; i < pObj->mColExtCount; i++) {
        pExt = &pObj->mColExt[i];
        switch (pExt->mType) {
        case 1:
            _calcGroundCollision(pObj, pParticle, pExt->mData.mHeight);
            break;
        case 2:
            _calcPlaneCollision(pObj, pParticle, &pExt->mData.mPlane.mNormal, pExt->mData.mPlane.mDistance);
            break;
        }
    }
}

void PsysColExtClearAll(ParticleSysObj_t *pObj)
{
    pObj->mColExtCount = 0;
}
