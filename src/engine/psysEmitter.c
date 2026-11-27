/* Particle emitters: copies an emitter's settings and picks the start position and direction
   of each new particle (point, directed, cone or line emitters). */

#include "engine/particleLib.h"
#include "game/Vec3Magnitude.h"
#include "engine/llmatrix.h"

float MathSin(int angle);
float MathCos(int angle);
int MathArcCos(float value);

void EmitterInitParms(ParticleSysObj_t *pDst, ParticleSysObj_t *pSrc)
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

void EmitterPrecalcDependantVals(ParticleSysObj_t *pObj)
{
    Vec3_801DE1E0 side;
    Vec3_801DE1E0 dir;
    EmitterLine_t *pCase3;

    if (pObj->mEmitterType == 3) {
        pCase3 = &pObj->mEmitter.mCase3;
        Vec3Sub(&dir, &pCase3->mUnknown0C, &pCase3->mUnknown00);
        Vec3Normalize(&pCase3->mUnknown2C, &dir);
        Vec3CrossProduct(&side, &pCase3->mUnknown18, &pCase3->mUnknown2C);
        Vec3Normalize(&side, &side);
        Vec3CrossProduct(&pCase3->mUnknown38, &dir, &side);
        pCase3->mUnknown44 = pCase3->mUnknown28 - pCase3->mUnknown24;
    }
}

/* Fixed-origin modes use their first vector; mode 3 samples its two endpoints. */
void EmitterGetNewPos(Vec3_801DE1E0 *pOut, ParticleSysObj_t *pObj)
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
        Vec3Lerp(pOut, &pObj->mEmitter.mCase3.mUnknown0C, &pObj->mEmitter.mCase3.mUnknown00, ParticleGetRandom());
        break;
    }
}

/* Mode 2 scales the polar angle without scaling the azimuth draw. */
void EmitterGetNewDir(Vec3_801DE1E0 *pOut, ParticleSysObj_t *pObj)
{
    EmitterDirected_t *pCase1;
    EmitterCone_t *pCase2;
    EmitterLine_t *pCase3;

    switch (pObj->mEmitterType) {
    case 0: {
        int phi;
        int theta;
        Vec3_801DE1E0 dir;

        phi = MathArcCos(1.0f - 2.0f * ParticleGetRandom());
        theta = (int)(ParticleGetRandom() * 16777216.0f);
        dir.x = MathCos(theta) * MathSin(phi);
        dir.y = MathSin(theta) * MathSin(phi);
        dir.z = MathCos(phi);
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
        phi = (int)(pCase2->mUnknown0C * 3.7450704e-07f * (float)MathArcCos(1.0f - ParticleGetRandom()) * 2670176.8f);
        theta = (int)(ParticleGetRandom() * 16777216.0f);
        dir.x = MathCos(theta) * MathSin(phi);
        dir.y = MathSin(theta) * MathSin(phi);
        dir.z = MathCos(phi);
        pOut->x = dir.x;
        pOut->y = dir.y;
        pOut->z = dir.z;
        break;
    }
    case 3:
        MatPushUnit();
        pCase3 = &pObj->mEmitter.mCase3;
        MatRotAxis(&pCase3->mUnknown2C.x, (int)((ParticleGetRandom() * pCase3->mUnknown44 + pCase3->mUnknown24) * 16777216.0f));
        Vec3Mat33Mul(pOut, &pCase3->mUnknown38);
        MatPop();
        break;
    }
}
