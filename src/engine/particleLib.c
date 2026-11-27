/* Particle effects: pooled systems, particle generation and lifetime updates,
   effect parameter loading, and render colour evaluation. */

#include <string.h>
#include "engine/particleLib.h"
#include "engine/animTexLib.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/Vec3Magnitude.h"

/* Pool of particle systems created from one template (0x6E4 bytes). */
typedef struct ParticlePool_t {
    unsigned short mUnknown000;
    ParticleSysObj_t *mpObjs[32];
    unsigned short mFree;
    unsigned short mUsed;
    ParticleTemplate_t mTemplate;
} ParticlePool_t;

/* Descriptor passed to ParticleLibInit (_ParticleSys_EmitterDesc in the game). */
typedef struct ParticleLibParms_t {
    int mUnknown00;
    unsigned short mUnknown04;
    unsigned short mUnknown06;
    unsigned short mUnknown08;
    float mUnknown0C;
    unsigned char mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    void *mpUnknown20;
    unsigned char mUnknown24;
} ParticleLibParms_t;

/* Custom behaviour tables of the library state. */
typedef struct ParticleCustomBehavior_t {
    void **mppUnknown0;
    void **mppUnknown4;
    void **mppUnknown8;
    unsigned short mUnknownC;
    unsigned char mUnknownE;
} ParticleCustomBehavior_t;

/* Library state at partLibState. */
typedef struct ParticleLibState_t {
    int mUnknown00;
    void *mpUnknown04;
    void *mpUnknown08;
    void *mpUnknown0C;
    float mUnknown10;
    unsigned short mUnknown14;
    unsigned char mUnknown16;
    unsigned char mUnknown17;
    unsigned char mUnknown18;
    int mUnknown1C;
    float mUnknown20[4][4];
    unsigned short mUnknown60;
    unsigned short mUnknown62;
    unsigned char mUnknown64;
    int mUnknown68;
    int mHeap;
    int mPoolCount;
    float mUnknown74;
    Vec3_801DE1E0 mUnknown78;
    int mUnknown84;
    void *mpRandom;
    ParticleCustomBehavior_t mUnknown8C;
} ParticleLibState_t;

/* Template pool table at worldPoolMan. */
typedef struct ParticlePoolManager_t {
    ParticlePool_t *mpPools;
    unsigned char *mpUsed;
    int mUnknown8;
} ParticlePoolManager_t;

/* Heap descriptor for the library's optional particle-storage heap. */
typedef struct ParticleHeapDef_t {
    char mUnknown00[8];
    int mUnknown08;
    int mUnknown0C;
    int mUnknown10;
    unsigned short mAlign;
    unsigned short unk_0x16;
} ParticleHeapDef_t;

static ParticleLibState_t partLibState;
static ParticlePoolManager_t worldPoolMan;
ParticleHeapDef_t gPoolHeapDef = {"PSYSLIB", 0, 1, 0, 0x10, 0xA00};
Vec3_801DE1E0 gGravNorm = {0.0f, -1.0f, 0.0f};
unsigned char gPartLibIsInit = 0;
char *gPartLibVersion = "1.0b";
static float gSysSpeedCompVal;

void MatPush(void);
void MatPushUnit(void);
void MatPop(void);
void MatMakeUnit(void);
void MatRotX(int a);
void MatRotY(int a);
void MatRotZ(int a);
void MatTranslate(Vec3_801DE1E0 *pPos);
void MatStore(float (*m)[4]);
void fn_801D2130(ParticleHeapDef_t *pType);
int fn_801D2570(int a);
int fn_801D2730(void);
unsigned int fn_801D27F4(int heap);
int MemFill(void *p, unsigned int size, int value, int flags);
int ObjNewType_(unsigned char heap, int size, int count, void (*pAdd)(), void (*pDel)());
int ObjDelType(unsigned char heap);
void *ObjNewList(int a, int b, int c, int d, int e, int f, int g, int h);
void ObjSetListObjFunc(void *pList, unsigned char heap, int slot, void *pFunc);
void ObjDelList(void *pList);
ParticleSysObj_t *ObjNew(unsigned char heap, int a, ParticleTemplate_t *pTemplate);
int ObjAddToList(void *pList, void *pObj);
void _partReadWrite(unsigned char *pSrc, unsigned char *pDst, unsigned int size, int noSwap);
unsigned int ColorRampEval(ColorRamp_t *pRamp, float t, Vec3_801DE1E0 *pColor, unsigned int start);

static void _genNewParticles(ParticleSysObj_t *pObj, unsigned short count, int step, int steps, float dt);
static void _particleIntegrateTimestep(ParticleSysObj_t *pObj, PsysParticle_t *pParticle, float dt);
static void _sumGasMotionForces(ParticleSysObj_t *pObj);
static void _sumSolidMotionForces(ParticleSysObj_t *pObj);
void ParticleObjInitParms(ParticleSysObj_t *pDst, ParticleTemplate_t *pSrc);
void ParticleObjInitState(ParticleSysObj_t *pObj);
void ParticleObjAttachTex(ParticleSysObj_t *pObj, AnimTex_t *pTex);
void ParticleObjSetLocalMat(ParticleSysObj_t *pObj, Vec3_801DE1E0 *pPos, Vec3_801DE1E0 *pRot);
int ParticleObjUpdate(ParticleSysObj_t *pObj, int steps);
static void _particleObjAdd(ParticleSysObj_t *pObj, ParticleTemplate_t *pTemplate);
static void _particleObjDel(ParticleSysObj_t *pObj);
void ParticlePoolReturn(ParticleSysObj_t *pObj);
void ParticleLibShutdownCustomBehavior(void);
static float _partGetRandom(void);
static int _partGetRandomRange(int range);
void MatLoad(float *pMatrix);
void MatCat(float *pMatrix);
void EmitterPrecalcDependantVals(ParticleSysObj_t *pObj);
void EmitterGetNewPos(Vec3_801DE1E0 *pOut, ParticleSysObj_t *pObj);
void EmitterGetNewDir(Vec3_801DE1E0 *pOut, ParticleSysObj_t *pObj);
void ColorRampInitParms(ColorRamp_t *pRamp, ColorRampParms_t *pParms);

static void _ParticlePoolInit(void)
{
    MemFill(&worldPoolMan, sizeof(worldPoolMan), 0, 1);
    worldPoolMan.mpUsed = fn_801D2B7C(partLibState.mPoolCount, 0, 0);
    MemFill(worldPoolMan.mpUsed, partLibState.mPoolCount, 0, 1);
    worldPoolMan.mpPools = fn_801D2B7C(partLibState.mPoolCount * sizeof(ParticlePool_t), 0, 0);
    MemFill(worldPoolMan.mpPools, partLibState.mPoolCount * sizeof(ParticlePool_t), 0, 1);
}

static void _ParticlePoolShutdown(void)
{
    fn_801D2BD0(worldPoolMan.mpUsed);
    worldPoolMan.mpUsed = 0;
    fn_801D2BD0(worldPoolMan.mpPools);
    worldPoolMan.mpPools = 0;
}

static ParticleSysObj_t *_ParticlePoolBorrow(unsigned short handle)
{
    ParticlePool_t *pPool = &worldPoolMan.mpPools[handle];
    ParticleSysObj_t *pObj;
    unsigned int size;
    unsigned short i;

    if (pPool->mFree == 0) {
        goto fail;
    }
    pObj = pPool->mpObjs[pPool->mUsed];
    if (partLibState.mUnknown64 != 0) {
        size = 0;
        if (pObj->mMax != 0) {
            size = pObj->mMax * sizeof(PsysParticle_t);
            size = (size + 15) & ~15;
        }
        if (fn_801D27F4(partLibState.mHeap) < size) {
            goto fail;
        }
        pObj->mpParticles = fn_801D2BB0(partLibState.mHeap, size, 0, 0);
        if (pObj->mpParticles == 0) {
            goto fail;
        }
        for (i = 0; i < pObj->mMax; i++) {
            pObj->mppParticles[i] = &pObj->mpParticles[i];
            pObj->mppParticles[i]->mActive = 0;
        }
    }
    ParticleObjInitParms(pObj, &pPool->mTemplate);
    ParticleObjInitState(pObj);
    pObj->mUnknown2B4 = 1;
    pPool->mUsed++;
    pPool->mFree--;
    return pObj;
fail:
    return 0;
}

static void _checkParticleLives(ParticleSysObj_t *pObj)
{
    int i;
    int last = pObj->mCount - 1;

    for (i = last; i >= 0; i--) {
        PsysParticle_t *pParticle = pObj->mppParticles[i];

        if (pParticle->mAge < pParticle->mLife) {
            continue;
        }
        pParticle->mActive = 0;
        if (i != last) {
            PsysParticle_t *pLast = pObj->mppParticles[last];
            pObj->mppParticles[last] = pParticle;
            pObj->mppParticles[i] = pLast;
        }
        pObj->mCount--;
        last = pObj->mCount - 1;
    }
}

static void _genNewParticles(ParticleSysObj_t *pObj, unsigned short count,
                             int step, int steps, float dt)
{
    Vec3_801DE1E0 randomVelocity;
    Vec3_801DE1E0 position;
    Vec3_801DE1E0 direction;
    Vec3_801DE1E0 offset;
    Vec3_801DE1E0 velocityRange;
    Vec3_801DE1E0 lastPosition;
    float fraction = 0.0f;
    float start = (float)step / (float)steps;
    float end = ((float)step + 1.0f) / (float)steps;
    float fractionStep;
    int transform = pObj->mUnknown2B6 | pObj->mUnknown03C | partLibState.mUnknown18;
    int lifeRange;
    unsigned short i;

    MatPushUnit();
    if (pObj->mUnknown2B6) {
        MatLoad((float *)pObj->mUnknown3B4);
    }
    if (partLibState.mUnknown18) {
        MatCat(&partLibState.mUnknown20[0][0]);
    }
    if (pObj->mUnknown03C) {
        MatCat(&pObj->mUnknown35C[0][0]);
    }
    lifeRange = pObj->mUnknown0E0 - pObj->mUnknown0DC;
    EmitterPrecalcDependantVals(pObj);
    if (pObj->mUnknown043 == 1) {
        if (transform) {
            Vec3Mat33Mul(&velocityRange, &pObj->mUnknown1F4);
        } else {
            velocityRange = *(Vec3_801DE1E0 *)&pObj->mUnknown1F4;
        }
    }
    if ((unsigned int)count > 1) {
        dt /= (unsigned int)count;
    } else {
        dt = 0.0f;
    }
    fractionStep = 1.0f / (int)count;
    for (i = 0; i < (unsigned int)count && pObj->mCount < pObj->mMax
         && (!pObj->mUnknown03F || pObj->mCount < (unsigned int)pObj->mUnknown0B4); i++) {
        PsysParticle_t *pParticle = pObj->mppParticles[pObj->mCount];

        EmitterGetNewPos(&position, pObj);
        EmitterGetNewDir(&direction, pObj);
        if (transform) {
            Vec3Mat34Mul(&position, &position);
            Vec3Mat33Mul(&direction, &direction);
        }
        if (pObj->mUnknown35A && pObj->mEmitterType != 3) {
            Vec3Sub(&offset, &position, &pObj->mUnknown3C8);
            Vec3Scale(&offset, &offset, fraction * (end - start) + start);
            fraction += fractionStep;
            Vec3Add(&offset, &offset, &pObj->mUnknown3C8);
            position = offset;
        }
        pParticle->mUnknown30 = (_partGetRandom() * 2.0f * pObj->mUnknown0AC - pObj->mUnknown0AC)
                             + pObj->mUnknown0A8;
        if (!(pParticle->mUnknown30 >= 0.0f)) {
            pParticle->mUnknown30 = 0.0f;
        }
        if (pObj->mUnknown05C == 1) {
            if (pObj->mUnknown03E) {
                pParticle->mUnknown34 = (_partGetRandom() * 2.0f * pObj->mUnknown0A4 - pObj->mUnknown0A4)
                                     + pObj->mUnknown0A0;
                pParticle->mUnknown50 = _partGetRandom() * 2.0f * pObj->mUnknown09C - pObj->mUnknown09C;
            } else {
                pParticle->mUnknown50 = pParticle->mUnknown34 = 0.0f;
            }
        }
        pParticle->mActive = 1;
        pParticle->mUnknown39 = 0;
        pParticle->mAge = 0.0f;
        pParticle->mAgeRatio = 0.0f;
        pParticle->mUnknown4C = 0.0f;
        if (pObj->mUnknown045) {
            pParticle->mUnknown3A = _partGetRandomRange(((AnimTex_t *)pObj->mpUnknown2AC)->mFrameCount);
        } else {
            pParticle->mUnknown3A = 0;
        }
        pParticle->mLife = (unsigned int)(_partGetRandomRange(lifeRange) + pObj->mUnknown0DC);
        if (pObj->mUnknown044) {
            pParticle->mLife /= gSysSpeedCompVal;
        }
        pParticle->mLife *= partLibState.mUnknown10;
        Vec3Scale(&pParticle->mVel, &direction,
                  (_partGetRandom() * 2.0f * pObj->mUnknown0BC - pObj->mUnknown0BC) + pObj->mUnknown0B8);
        Vec3Add(&pParticle->mVel, &pParticle->mVel, &pObj->mUnknown39C);
        if (pObj->mUnknown043 == 1) {
            randomVelocity.x = _partGetRandom() * 2.0f * velocityRange.x - velocityRange.x;
            randomVelocity.y = _partGetRandom() * 2.0f * velocityRange.y - velocityRange.y;
            randomVelocity.z = _partGetRandom() * 2.0f * velocityRange.z - velocityRange.z;
            Vec3Add(&pParticle->mVel, &pParticle->mVel, &randomVelocity);
        }
        pParticle->mPos.x = position.x;
        pParticle->mPos.y = position.y;
        pParticle->mPos.z = position.z;
        pParticle->mForce.x = pParticle->mForce.y = pParticle->mForce.z = 0.0f;
        pParticle->mPrevPos = pParticle->mPos;
        if (i) {
            _particleIntegrateTimestep(pObj, pParticle, dt * (int)(i - 1));
        }
        pObj->mCount++;
    }
    if (pObj->mUnknown35A && step + 1 == steps && pObj->mEmitterType != 3) {
        EmitterGetNewPos(&lastPosition, pObj);
        Vec3Mat34Mul(&lastPosition, &lastPosition);
        *(Vec3_801DE1E0 *)&pObj->mUnknown3C8 = lastPosition;
    }
    MatPop();
}

static void _deactivateAllParticles(ParticleSysObj_t *pObj)
{
    unsigned int i;

    for (i = 0; i < pObj->mCount; i++) {
        pObj->mppParticles[i]->mActive = 0;
    }
}

static void _updateSelfControlSys(ParticleSysObj_t *pObj, float dt)
{
    if (pObj->mUnknown0C8 != 0.0f) {
        float value = pObj->mUnknown0C8 * dt + pObj->mUnknown0B0;

        if (!(value >= pObj->mUnknown0CC)) {
            value = pObj->mUnknown0CC;
        } else if (!(value <= pObj->mUnknown0D0)) {
            value = pObj->mUnknown0D0;
        }
        pObj->mUnknown0B0 = value;
    }
    switch (pObj->mUnknown050) {
    case 0:
        break;
    case 1:
        if (!(pObj->mUnknown3B0 <= pObj->mUnknown054 * partLibState.mUnknown10)) {
            pObj->mUnknown0B0 = 0.0f;
            if (pObj->mCount == 0) {
                pObj->mUnknown2B4 = 0;
                if (pObj->mUnknown2B5 == 1) {
                    ParticlePoolReturn(pObj);
                }
            }
        }
        break;
    case 2:
        if (!(pObj->mUnknown0B0 > pObj->mUnknown054) && pObj->mCount == 0) {
            pObj->mUnknown2B4 = 0;
            if (pObj->mUnknown2B5 == 1) {
                ParticlePoolReturn(pObj);
            }
        }
        break;
    }
}

static void _updateParticles(ParticleSysObj_t *pObj, float dt)
{
    unsigned short i;

    PsysColPrecalcDependantVals(pObj);
    for (i = 0; i < pObj->mCount; i++) {
        PsysParticle_t *pParticle = pObj->mppParticles[i];

        if (pObj->mCollisionType != 0 || pObj->mColExtCount != 0) {
            PsysColCalcCollision(pObj, pParticle);
        }
        pParticle->mPrevPos = pParticle->mPos;
        _particleIntegrateTimestep(pObj, pParticle, dt);
        pParticle->mForce.x = pParticle->mForce.y = pParticle->mForce.z = 0.0f;
        if (pObj->mUnknown041 != 0) {
            pParticle->mUnknown4C = (pParticle->mAge * pObj->mUnknown0E4 + 1.0f) * pParticle->mUnknown30;
        }
        pParticle->mAgeRatio = pParticle->mAge / pParticle->mLife;
        pParticle->mAge += dt;
        pParticle->mUnknown50 += dt * pParticle->mUnknown34;
        pParticle->mUnknown40 = pParticle->mAge * partLibState.mUnknown14;
    }
}

static void _particleIntegrateTimestep(ParticleSysObj_t *pObj, PsysParticle_t *pParticle, float dt)
{
    float scale = pObj->mUnknown2B0 * dt;

    pParticle->mVel.x += pParticle->mForce.x * scale;
    pParticle->mVel.y += pParticle->mForce.y * scale;
    pParticle->mVel.z += pParticle->mForce.z * scale;
    pParticle->mPos.x = pParticle->mVel.x * dt + pParticle->mPrevPos.x;
    pParticle->mPos.y = pParticle->mVel.y * dt + pParticle->mPrevPos.y;
    pParticle->mPos.z = pParticle->mVel.z * dt + pParticle->mPrevPos.z;
}

static void _sumParticleForces(ParticleSysObj_t *pObj)
{
    switch (pObj->mForceType) {
    case 1:
        _sumGasMotionForces(pObj);
        break;
    case 0:
        _sumSolidMotionForces(pObj);
        break;
    }
}

static void _sumGasMotionForces(ParticleSysObj_t *pObj)
{
    Vec3_801DE1E0 force;
    unsigned int i;

    float x;
    float y;
    float z;

    Vec3Scale(&force, &partLibState.mUnknown78, -(pObj->mUnknown090 * pObj->mUnknown094));
    x = force.x;
    y = force.y;
    z = force.z;
    for (i = 0; i < pObj->mCount; i++) {
        PsysParticle_t *pParticle = pObj->mppParticles[i];

        pParticle->mForce.x += x;
        pParticle->mForce.y += y;
        pParticle->mForce.z += z;
        pParticle->mForce.x += pParticle->mVel.x * -0.45f;
        pParticle->mForce.y += pParticle->mVel.y * -0.45f;
        pParticle->mForce.z += pParticle->mVel.z * -0.45f;
    }
}

static void _sumSolidMotionForces(ParticleSysObj_t *pObj)
{
    Vec3_801DE1E0 force;
    unsigned short i;

    float x;
    float y;
    float z;

    Vec3Scale(&force, &partLibState.mUnknown78, pObj->mUnknown098 * pObj->mUnknown090);
    x = force.x;
    y = force.y;
    z = force.z;
    for (i = 0; i < pObj->mCount; i++) {
        PsysParticle_t *pParticle = pObj->mppParticles[i];

        pParticle->mForce.x += x;
        pParticle->mForce.y += y;
        pParticle->mForce.z += z;
    }
}

float ParticleGetRandom(void)
{
    return MathGetRandom(partLibState.mpRandom);
}

void ParticleLibInit(ParticleLibParms_t *pDesc)
{

    partLibState.mUnknown00 = pDesc->mUnknown00;
    partLibState.mUnknown60 = pDesc->mUnknown04;
    partLibState.mUnknown62 = pDesc->mUnknown06;
    partLibState.mpUnknown0C = pDesc->mpUnknown20;
    partLibState.mUnknown16 = pDesc->mUnknown24;
    partLibState.mpUnknown08 = ParticleObjUpdate;
    partLibState.mUnknown17 = 0;
    partLibState.mUnknown14 = pDesc->mUnknown08;
    partLibState.mUnknown10 = 1.0f / (unsigned int)partLibState.mUnknown14;
    partLibState.mUnknown84 = MathGetRandomSeed();
    partLibState.mpRandom = MathNewRandomStream(0, partLibState.mUnknown84);
    partLibState.mPoolCount = pDesc->mUnknown18;
    ObjNewType_(partLibState.mUnknown00, sizeof(ParticleSysObj_t), pDesc->mUnknown04,
                (void (*)())_particleObjAdd, (void (*)())_particleObjDel);
    partLibState.mpUnknown04 = ObjNewList(1, partLibState.mUnknown60, 0, 0, 0, 2, 1, -1);
    ObjSetListObjFunc(partLibState.mpUnknown04, partLibState.mUnknown00, 0, partLibState.mpUnknown08);
    ObjSetListObjFunc(partLibState.mpUnknown04, partLibState.mUnknown00, 1, partLibState.mpUnknown0C);
    partLibState.mUnknown64 = pDesc->mUnknown10;
    if (partLibState.mUnknown64) {
        partLibState.mHeap = fn_801D2730();
        gPoolHeapDef.mUnknown08 = partLibState.mHeap;
        partLibState.mUnknown68 = (pDesc->mUnknown14 + 15) & ~15;
        gPoolHeapDef.mUnknown10 = partLibState.mUnknown68;
        fn_801D2130(&gPoolHeapDef);
    } else {
        partLibState.mUnknown68 = 0;
        partLibState.mHeap = 0;
    }
    _ParticlePoolInit();
    partLibState.mUnknown74 = pDesc->mUnknown0C;
    Vec3Scale(&partLibState.mUnknown78, &gGravNorm, pDesc->mUnknown0C);
    partLibState.mUnknown1C = pDesc->mUnknown1C;
    partLibState.mUnknown18 = 0;
    MatPush();
    MatMakeUnit();
    switch (partLibState.mUnknown1C) {
    case 0:
        break;
    case 1:
        partLibState.mUnknown18 = 1;
        MatRotX(0x400000);
        break;
    }
    Vec3Mat33Mul(&partLibState.mUnknown78, &partLibState.mUnknown78);
    MatStore(partLibState.mUnknown20);
    MatPop();
    partLibState.mUnknown8C.mppUnknown0 = 0;
    partLibState.mUnknown8C.mppUnknown4 = 0;
    partLibState.mUnknown8C.mppUnknown8 = 0;
    partLibState.mUnknown8C.mUnknownE = 0;
    gPartLibIsInit = 1;
}

void ParticleLibShutdown(void)
{
    ParticleLibState_t *pState = &partLibState;

    _ParticlePoolShutdown();
    ParticleLibShutdownCustomBehavior();
    ObjDelList(pState->mpUnknown04);
    ObjDelType(pState->mUnknown00);
    MathDelRandomStream(pState->mpRandom);
    if (pState->mUnknown64) {
        fn_801D2570(pState->mHeap);
    }
    pState->mUnknown64 = 0;
    pState->mUnknown00 = 0;
    pState->mUnknown74 = 0.0f;
    pState->mUnknown1C = 0;
    pState->mUnknown78.x = gGravNorm.x;
    pState->mUnknown78.y = gGravNorm.y;
    pState->mUnknown78.z = gGravNorm.z;
    pState->mHeap = 0;
    pState->mUnknown68 = 0;
    pState->mpUnknown04 = 0;
    pState->mpUnknown08 = 0;
    pState->mpUnknown0C = 0;
    pState->mUnknown60 = 0;
    pState->mUnknown62 = 0;
    pState->mpRandom = 0;
    pState->mUnknown84 = 0;
    pState->mUnknown18 = 0;
    MatPush();
    MatMakeUnit();
    MatStore(pState->mUnknown20);
    MatPop();
    gPartLibIsInit = 0;
}

void ParticleLibSetUpdatesPerSec(unsigned int rate)
{
    partLibState.mUnknown14 = rate;
    partLibState.mUnknown10 = 1.0f / rate;
}

static void _Vec4Copy(Vec4_801DE1E0 *pDst, Vec4_801DE1E0 *pSrc)
{
    pDst->x = pSrc->x;
    pDst->y = pSrc->y;
    pDst->z = pSrc->z;
    pDst->w = pSrc->w;
}

void ParticleObjInitParms(ParticleSysObj_t *pDst, ParticleTemplate_t *pSrc)
{
    strcpy(pDst->mUnknown014, pSrc->mObj.mUnknown014);
    strcpy(pDst->mUnknown01C, pSrc->mObj.mUnknown01C);
    pDst->mUnknown04C = pSrc->mObj.mUnknown04C;
    pDst->mUnknown050 = pSrc->mObj.mUnknown050;
    pDst->mUnknown054 = pSrc->mObj.mUnknown054;
    pDst->mForceType = pSrc->mObj.mForceType;
    pDst->mUnknown05C = pSrc->mObj.mUnknown05C;
    pDst->mUnknown060 = pSrc->mObj.mUnknown060;
    pDst->mUnknown03C = pSrc->mObj.mUnknown03C;
    pDst->mUnknown064.x = pSrc->mObj.mUnknown064.x;
    pDst->mUnknown064.y = pSrc->mObj.mUnknown064.y;
    pDst->mUnknown064.z = pSrc->mObj.mUnknown064.z;
    pDst->mUnknown070.x = pSrc->mObj.mUnknown070.x;
    pDst->mUnknown070.y = pSrc->mObj.mUnknown070.y;
    pDst->mUnknown070.z = pSrc->mObj.mUnknown070.z;
    ParticleObjSetLocalMat(pDst, &pSrc->mObj.mUnknown064, &pSrc->mObj.mUnknown070);
    _Vec4Copy(&pDst->mUnknown07C, &pSrc->mObj.mUnknown07C);
    pDst->mUnknown03D = pSrc->mObj.mUnknown03D;
    pDst->mpUnknown08C = &pSrc->mRamp;
    pDst->mUnknown090 = pSrc->mObj.mUnknown090;
    pDst->mUnknown094 = pSrc->mObj.mUnknown094;
    pDst->mUnknown098 = pSrc->mObj.mUnknown098;
    pDst->mUnknown03E = pSrc->mObj.mUnknown03E;
    pDst->mUnknown09C = pSrc->mObj.mUnknown09C;
    pDst->mUnknown0A0 = pSrc->mObj.mUnknown0A0;
    pDst->mUnknown0A4 = pSrc->mObj.mUnknown0A4;
    pDst->mUnknown0A8 = pSrc->mObj.mUnknown0A8;
    pDst->mUnknown0AC = pSrc->mObj.mUnknown0AC;
    pDst->mUnknown0B0 = pSrc->mObj.mUnknown0B0;
    pDst->mUnknown03F = pSrc->mObj.mUnknown03F;
    pDst->mUnknown0B4 = pSrc->mObj.mUnknown0B4;
    pDst->mUnknown0B8 = pSrc->mObj.mUnknown0B8;
    pDst->mUnknown0BC = pSrc->mObj.mUnknown0BC;
    pDst->mUnknown040 = pSrc->mObj.mUnknown040;
    pDst->mUnknown0C0 = pSrc->mObj.mUnknown0C0;
    pDst->mUnknown046 = pSrc->mObj.mUnknown046;
    pDst->mUnknown0C4 = pSrc->mObj.mUnknown0C4;
    pDst->mUnknown0C8 = pSrc->mObj.mUnknown0C8;
    pDst->mUnknown0CC = pSrc->mObj.mUnknown0CC;
    pDst->mUnknown0D0 = pSrc->mObj.mUnknown0D0;
    pDst->mUnknown0D4 = pSrc->mObj.mUnknown0D4;
    pDst->mUnknown0D8 = pSrc->mObj.mUnknown0D8;
    pDst->mUnknown0DC = pSrc->mObj.mUnknown0DC;
    pDst->mUnknown0E0 = pSrc->mObj.mUnknown0E0;
    pDst->mUnknown041 = pSrc->mObj.mUnknown041;
    pDst->mUnknown0E4 = pSrc->mObj.mUnknown0E4;
    pDst->mUnknown042 = pSrc->mObj.mUnknown042;
    pDst->mUnknown0E8 = pSrc->mObj.mUnknown0E8;
    pDst->mUnknown0EC = pSrc->mObj.mUnknown0EC;
    pDst->mEmitterType = pSrc->mObj.mEmitterType;
    EmitterInitParms(pDst, &pSrc->mObj);
    pDst->mUnknown043 = pSrc->mObj.mUnknown043;
    pDst->mUnknown1F4 = pSrc->mObj.mUnknown1F4;
    pDst->mUnknown1F8 = pSrc->mObj.mUnknown1F8;
    pDst->mUnknown1FC = pSrc->mObj.mUnknown1FC;
    pDst->mUnknown044 = pSrc->mObj.mUnknown044;
    pDst->mUnknown200 = pSrc->mObj.mUnknown200;
    pDst->mCollisionType = pSrc->mObj.mCollisionType;
    PsysColInitParms(pDst, &pSrc->mObj);
    pDst->mUnknown288 = pSrc->mObj.mUnknown288;
    pDst->mUnknown048 = pSrc->mObj.mUnknown048;
}

void ParticleObjInitState(ParticleSysObj_t *pObj)
{
    pObj->mUnknown35B = 0;
    pObj->mUnknown3D0 = 0.0f;
    pObj->mCount = 0;
    pObj->mUnknown3AC = 0.0f;
    pObj->mUnknown3B0 = 0.0f;
    pObj->mUnknown2B6 = 0;
    pObj->mUnknown3B4 = 0;
    pObj->mColExtCount = 0;
    pObj->mUnknown39C = 0.0f;
    pObj->mUnknown3A0 = 0.0f;
    pObj->mUnknown3A4 = 0.0f;
    pObj->mUnknown3A8 = 0.0f;
    pObj->mUnknown35A = 0;
    pObj->mUnknown3C8 = 0.0f;
    pObj->mUnknown3CC = 0.0f;
    pObj->mUnknown2B0 = 1.0f / pObj->mUnknown090;
}

static void _particleObjAdd(ParticleSysObj_t *pObj, ParticleTemplate_t *pTemplate)
{
    unsigned short i;
    AnimTex_t *pTex;

    if (pTemplate->mObj.mUnknown03F) {
        pObj->mMax = pTemplate->mObj.mUnknown0B4;
    } else {
        pObj->mMax = partLibState.mUnknown62;
    }
    pObj->mppParticles = fn_801D2B7C(pObj->mMax * sizeof(PsysParticle_t *), 0, 0);
    MemFill(pObj->mppParticles, pObj->mMax * sizeof(PsysParticle_t *), 0, 1);
    pObj->mpParticles = fn_801D2B7C(pObj->mMax * sizeof(PsysParticle_t), 0, 0);
    MemFill(pObj->mpParticles, pObj->mMax * sizeof(PsysParticle_t), 0, 1);
    for (i = 0; i < pObj->mMax; i++) {
        pObj->mppParticles[i] = &pObj->mpParticles[i];
    }
    ParticleObjInitParms(pObj, pTemplate);
    ParticleObjInitState(pObj);
    pTex = AnimTexFind(pTemplate->mObj.mUnknown28C);
    if (pTex) {
        ParticleObjAttachTex(pObj, pTex);
    }
    pObj->mUnknown2B4 = 1;
}

ParticleSysObj_t *ParticleObjAddSys(ParticleTemplate_t *pTemplate)
{
    ParticleLibState_t *pState = &partLibState;
    ParticleSysObj_t *pObj;

    pObj = ObjNew(pState->mUnknown00, 0, pTemplate);
    ObjAddToList(pState->mpUnknown04, pObj);
    return pObj;
}

void ParticleObjAttachTex(ParticleSysObj_t *pObj, AnimTex_t *pTex)
{
    pObj->mUnknown045 = 1;
    pObj->mpUnknown2AC = pTex;
    strcpy(pObj->mUnknown28C, pTex->mName);
}

void ParticleObjSetLocalMat(ParticleSysObj_t *pObj, Vec3_801DE1E0 *pPos, Vec3_801DE1E0 *pRot)
{
    MatPushUnit();
    if (pPos) {
        MatTranslate(pPos);
    }
    if (pRot) {
        MatRotZ((int)(pRot->z * 46603.38f));
        MatRotY((int)(pRot->y * 46603.38f));
        MatRotX((int)(pRot->x * 46603.38f));
    }
    MatStore(pObj->mUnknown35C);
    MatPop();
}

static void _particleObjDel(ParticleSysObj_t *pObj)
{
    fn_801D2BD0(pObj->mppParticles);
    if (pObj->mpParticles) {
        fn_801D2BD0(pObj->mpParticles);
    }
}

int ParticleObjUpdate(ParticleSysObj_t *pObj, int steps)
{
    void (*pfnEmit)(ParticleSysObj_t *, float);
    void (*pfnUpdate)(ParticleSysObj_t *, float);
    void (*pfnPre)(ParticleSysObj_t *);
    float dt;
    float rate;
    unsigned short count;
    ParticleCustomBehavior_t *pCustom;
    int i;

    if (!pObj->mUnknown2B4) {
        return 0;
    }
    pfnEmit = 0;
    pfnUpdate = 0;
    pfnPre = 0;
    pCustom = &partLibState.mUnknown8C;
    if (pCustom->mUnknownE) {
        pfnEmit = (void (*)(ParticleSysObj_t *, float))pCustom->mppUnknown0[pObj->mUnknown358];
        pfnUpdate = (void (*)(ParticleSysObj_t *, float))pCustom->mppUnknown4[pObj->mUnknown358];
        pfnPre = (void (*)(ParticleSysObj_t *))pCustom->mppUnknown8[pObj->mUnknown358];
    }
    dt = partLibState.mUnknown10;
    if (!partLibState.mUnknown17) {
        dt *= (float)steps;
        steps = 1;
    }
    if (pObj->mUnknown044) {
        pObj->mUnknown3A8 = Vec3Magnitude(&pObj->mUnknown39C);
        gSysSpeedCompVal = pObj->mUnknown3A8 * pObj->mUnknown200 + 1.0f;
    }
    for (i = 0; i < steps; i++) {
        if (!pObj->mUnknown04C) {
            _updateSelfControlSys(pObj, dt);
        }
        if (!pObj->mUnknown2B4) {
            break;
        }
        if (pObj->mCount) {
            if (pfnPre) {
                pfnPre(pObj);
            } else {
                _checkParticleLives(pObj);
            }
        }
        _sumParticleForces(pObj);
        if (pfnUpdate) {
            pfnUpdate(pObj, dt);
        } else {
            _updateParticles(pObj, dt);
        }
        if (!(pObj->mUnknown0B0 <= 0.0f) && pObj->mCount < pObj->mMax) {
            if (pfnEmit) {
                pfnEmit(pObj, dt);
            } else {
                if (pObj->mUnknown044) {
                    rate = pObj->mUnknown0B0 * gSysSpeedCompVal;
                } else {
                    rate = pObj->mUnknown0B0;
                }
                rate = rate * dt + pObj->mUnknown3AC;
                count = rate;
                if (count) {
                    _genNewParticles(pObj, count, i, steps, dt);
                }
                pObj->mUnknown3AC = rate - (unsigned int)count;
            }
        }
        pObj->mUnknown3B0 += dt;
    }
    return 0;
}

unsigned short ParticlePoolCreate(unsigned short count, ParticleTemplate_t *pTemplate)
{
    unsigned short index;
    unsigned short i;
    unsigned short j;
    ParticleSysObj_t *pObj;

    index = 0;
    for (i = 0; i < partLibState.mPoolCount; i++) {
        if (worldPoolMan.mpUsed[i] == 0) {
            index = i;
            break;
        }
    }
    for (i = 0; i < count; i++) {
        pObj = ParticleObjAddSys(pTemplate);
        if (partLibState.mUnknown64) {
            fn_801D2BD0(pObj->mpParticles);
            for (j = 0; j < pObj->mMax; j++) {
                pObj->mppParticles[j] = 0;
            }
            pObj->mpParticles = 0;
        }
        pObj->mUnknown2B4 = 0;
        pObj->mUnknown2B5 = 1;
        pObj->mUnknown358 = index;
        worldPoolMan.mpPools[index].mpObjs[i] = pObj;
    }
    worldPoolMan.mpPools[index].mUnknown000 = count;
    worldPoolMan.mpPools[index].mFree = count;
    worldPoolMan.mpPools[index].mUsed = 0;
    worldPoolMan.mpUsed[index] = 1;
    worldPoolMan.mpPools[index].mTemplate = *pTemplate;
    ColorRampCopy(&pTemplate->mRamp, &worldPoolMan.mpPools[index].mTemplate.mRamp);
    return index;
}

ParticleSysObj_t *ParticlePoolBorrow(unsigned short handle)
{
    return _ParticlePoolBorrow(handle);
}

void ParticlePoolReturn(ParticleSysObj_t *pObj)
{
    unsigned short index = pObj->mUnknown358;
    ParticlePool_t *pPool = &worldPoolMan.mpPools[index];
    unsigned short i;
    unsigned short last;
    unsigned short j;
    ParticleSysObj_t *pSwap;

    last = pPool->mUsed - 1;
    for (i = 0; i < pPool->mUsed; i++) {
        if (pPool->mpObjs[i] == pObj) {
            break;
        }
    }
    pObj->mUnknown2B4 = 0;
    _deactivateAllParticles(pObj);
    if (partLibState.mUnknown64) {
        fn_801D2BD0(pObj->mpParticles);
        pObj->mpParticles = 0;
        for (j = 0; j < pObj->mMax; j++) {
            pObj->mppParticles[j] = 0;
        }
    }
    if (i != last) {
        pSwap = pPool->mpObjs[last];
        pPool->mpObjs[last] = pObj;
        pPool->mpObjs[i] = pSwap;
    }
    worldPoolMan.mpPools[index].mUsed--;
    worldPoolMan.mpPools[index].mFree++;
}

/* Frame of a particle's texture: 0 for a single frame, else the particle's start frame plus (for
   an animated texture) its age in 60ths of a second divided by the object's frame divisor,
   modulo the frame count. */
static unsigned int PSysRenderCalcParticleFrame(AnimTex_t *pTex, ParticleSysObj_t *pObj,
                                                PsysParticle_t *pParticle)
{
    unsigned int frame = 0;

    if (pTex->mFrameCount > 1) {
        frame = pParticle->mUnknown3A;
        if (pTex->mAnimated && pObj->mUnknown048) {
            frame += (int)(pParticle->mAge * 60.0f) / pObj->mUnknown048;
        }
        frame %= pTex->mFrameCount;
    }
    return frame;
}

void PSysRenderCalcParticleColor(Vec4_801DE1E0 *pColor, ParticleSysObj_t *pObj, PsysParticle_t *pParticle)
{
    float fadeOut;

    if (pObj->mUnknown03D && pObj->mpUnknown08C) {
        pParticle->mUnknown39 = ColorRampEval(pObj->mpUnknown08C, pParticle->mAgeRatio, (Vec3_801DE1E0 *)pColor,
                                            pParticle->mUnknown39);
    } else {
        pColor->x = pObj->mUnknown07C.x;
        pColor->y = pObj->mUnknown07C.y;
        pColor->z = pObj->mUnknown07C.z;
    }
    pColor->w = pObj->mUnknown07C.w;
    fadeOut = 1.0f - pObj->mUnknown0EC;
    if (pObj->mUnknown042) {
        if (!(pParticle->mAgeRatio < pObj->mUnknown0EC)) {
            if (pObj->mUnknown060 == 2) {
                Vec3Scale(pColor, pColor, (1.0f - pParticle->mAgeRatio) / fadeOut);
            } else {
                pColor->w *= (1.0f - pParticle->mAgeRatio) / fadeOut;
            }
        }
        if (!(pParticle->mAgeRatio >= pObj->mUnknown0E8)) {
            if (pObj->mUnknown060 == 2) {
                Vec3Scale(pColor, pColor, pParticle->mAgeRatio / pObj->mUnknown0E8);
            } else {
                pColor->w *= pParticle->mAgeRatio / pObj->mUnknown0E8;
            }
        }
    }
}

float PSysRenderCalcParticleScale(ParticleSysObj_t *pObj, PsysParticle_t *pParticle)
{
    if (pObj->mUnknown041) {
        return pParticle->mUnknown4C;
    }
    return pParticle->mUnknown30;
}

void PartRead8(unsigned char **ppData, void *pDst, int noSwap)
{
    _partReadWrite(*ppData, pDst, 1, noSwap);
    *ppData += 1;
}

void PartRead16(unsigned char **ppData, void *pDst, int noSwap)
{
    _partReadWrite(*ppData, pDst, 2, noSwap);
    *ppData += 2;
}

void PartRead32(unsigned char **ppData, void *pDst, int noSwap)
{
    _partReadWrite(*ppData, pDst, 4, noSwap);
    *ppData += 4;
}

void PartRead(unsigned char **ppData, void *pDst, unsigned int size, int noSwap)
{
    _partReadWrite(*ppData, pDst, size, noSwap);
    *ppData += size;
}

void PartReadVec3(unsigned char **ppData, Vec3_801DE1E0 *pDst, int noSwap)
{
    _partReadWrite(*ppData, (unsigned char *)&pDst->x, 4, noSwap);
    *ppData += 4;
    _partReadWrite(*ppData, (unsigned char *)&pDst->y, 4, noSwap);
    *ppData += 4;
    _partReadWrite(*ppData, (unsigned char *)&pDst->z, 4, noSwap);
    *ppData += 4;
}

static void PartReadVec4(unsigned char **ppData, Vec4_801DE1E0 *pDst, int noSwap)
{
    _partReadWrite(*ppData, (unsigned char *)&pDst->x, 4, noSwap);
    *ppData += 4;
    _partReadWrite(*ppData, (unsigned char *)&pDst->y, 4, noSwap);
    *ppData += 4;
    _partReadWrite(*ppData, (unsigned char *)&pDst->z, 4, noSwap);
    *ppData += 4;
    _partReadWrite(*ppData, (unsigned char *)&pDst->w, 4, noSwap);
    *ppData += 4;
}

void _partReadWrite(unsigned char *pSrc, unsigned char *pDst, unsigned int size, int noSwap)
{
    unsigned int i = 0;
    unsigned int j;
    unsigned int next;

    while (i < size) {
        if (noSwap) {
            j = i;
            next = i + 1;
        } else {
            unsigned int distance = i + 1;
            j = size - distance;
            next = distance;
        }
        pDst[j] = pSrc[i];
        i = next;
    }
}

static void PartReadEmitter(unsigned char **ppData, EmitterParms_t *pDst, unsigned int type, int noSwap)
{
    unsigned char *pData = *ppData;

    switch (type) {
    case 0:
        PartReadVec3(&pData, &pDst->mPoint, noSwap);
        break;
    case 1:
        PartReadVec3(&pData, &pDst->mCase1.mUnknown00, noSwap);
        PartReadVec3(&pData, &pDst->mCase1.mUnknown0C, noSwap);
        break;
    case 2:
        PartReadVec3(&pData, &pDst->mCase2.mUnknown00, noSwap);
        PartRead32(&pData, &pDst->mCase2.mUnknown0C, noSwap);
        break;
    case 3:
        PartReadVec3(&pData, &pDst->mCase3.mUnknown00, noSwap);
        PartReadVec3(&pData, &pDst->mCase3.mUnknown0C, noSwap);
        PartReadVec3(&pData, &pDst->mCase3.mUnknown18, noSwap);
        PartRead32(&pData, &pDst->mCase3.mUnknown24, noSwap);
        PartRead32(&pData, &pDst->mCase3.mUnknown28, noSwap);
        PartReadVec3(&pData, &pDst->mCase3.mUnknown2C, noSwap);
        PartReadVec3(&pData, &pDst->mCase3.mUnknown38, noSwap);
        PartRead32(&pData, &pDst->mCase3.mUnknown44, noSwap);
        break;
    }
    *ppData += 0x100;
}

static void PartReadCollision(unsigned char **ppData, PsysColParms_t *pDst, unsigned int type, int noSwap)
{
    unsigned char *pData = *ppData;

    switch (type) {
    case 0:
        break;
    case 1:
        PartRead32(&pData, &pDst->mGround.mHeight, noSwap);
        break;
    case 2:
        PartReadVec3(&pData, &pDst->mParm[0], noSwap);
        PartReadVec3(&pData, &pDst->mParm[1], noSwap);
        PartReadVec3(&pData, &pDst->mParm[2], noSwap);
        break;
    }
    *ppData += 0x80;
}

void ParticleParmLoad(ParticleTemplate_t *pTemplate, unsigned char *data, int noSwap)
{
    ColorRampParms_t ramp;
    unsigned char oldPointers[128];
    unsigned short i;
    ParticleSysObj_t *pObj = &pTemplate->mObj;

    MemFill(pTemplate, sizeof(*pTemplate), 0, 1);
    PartRead(&data, pObj->mUnknown014, 8, 1);
    PartRead(&data, pObj->mUnknown01C, 32, 1);
    PartRead32(&data, &pObj->mUnknown04C, noSwap);
    PartRead32(&data, &pObj->mUnknown050, noSwap);
    PartRead32(&data, &pObj->mUnknown054, noSwap);
    PartRead32(&data, &pObj->mForceType, noSwap);
    PartRead32(&data, &pObj->mUnknown05C, noSwap);
    PartRead32(&data, &pObj->mUnknown060, noSwap);
    PartRead8(&data, &pObj->mUnknown03C, 1);
    PartReadVec3(&data, &pObj->mUnknown064, noSwap);
    PartReadVec3(&data, &pObj->mUnknown070, noSwap);
    PartReadVec4(&data, &pObj->mUnknown07C, noSwap);
    PartRead8(&data, &pObj->mUnknown03D, 1);
    PartRead32(&data, &ramp.mInterp, noSwap);
    PartRead16(&data, &ramp.mCount, noSwap);
    if (strcmp(pObj->mUnknown014, "1.0b") < 0) {
        PartRead16(&data, (unsigned char *)&ramp + 2, noSwap);
        PartRead(&data, oldPointers, sizeof(oldPointers), noSwap);
        for (i = 0; i < 32; i++) {
            PartRead32(&data, &ramp.mNodes[i].mT, noSwap);
            PartReadVec3(&data, &ramp.mNodes[i].mColor, noSwap);
        }
    } else {
        for (i = 0; i < ramp.mCount; i++) {
            PartRead32(&data, &ramp.mNodes[i].mT, noSwap);
            PartReadVec3(&data, &ramp.mNodes[i].mColor, noSwap);
        }
    }
    ColorRampInitParms(&pTemplate->mRamp, &ramp);
    PartRead32(&data, &pObj->mUnknown090, noSwap);
    PartRead32(&data, &pObj->mUnknown094, noSwap);
    PartRead32(&data, &pObj->mUnknown098, noSwap);
    PartRead8(&data, &pObj->mUnknown03E, 1);
    PartRead32(&data, &pObj->mUnknown09C, noSwap);
    PartRead32(&data, &pObj->mUnknown0A0, noSwap);
    PartRead32(&data, &pObj->mUnknown0A4, noSwap);
    PartRead32(&data, &pObj->mUnknown0A8, noSwap);
    PartRead32(&data, &pObj->mUnknown0AC, noSwap);
    PartRead32(&data, &pObj->mUnknown0B0, noSwap);
    PartRead8(&data, &pObj->mUnknown03F, 1);
    PartRead32(&data, &pObj->mUnknown0B4, noSwap);
    PartRead32(&data, &pObj->mUnknown0B8, noSwap);
    PartRead32(&data, &pObj->mUnknown0BC, noSwap);
    PartRead8(&data, &pObj->mUnknown040, 1);
    PartRead32(&data, &pObj->mUnknown0C0, noSwap);
    PartRead16(&data, &pObj->mUnknown046, noSwap);
    PartRead32(&data, &pObj->mUnknown0C4, noSwap);
    PartRead32(&data, &pObj->mUnknown0C8, noSwap);
    PartRead32(&data, &pObj->mUnknown0CC, noSwap);
    PartRead32(&data, &pObj->mUnknown0D0, noSwap);
    PartRead32(&data, &pObj->mUnknown0D4, noSwap);
    PartRead32(&data, &pObj->mUnknown0D8, noSwap);
    PartRead32(&data, &pObj->mUnknown0DC, noSwap);
    PartRead32(&data, &pObj->mUnknown0E0, noSwap);
    PartRead8(&data, &pObj->mUnknown041, 1);
    PartRead32(&data, &pObj->mUnknown0E4, noSwap);
    PartRead8(&data, &pObj->mUnknown042, 1);
    PartRead32(&data, &pObj->mUnknown0E8, noSwap);
    PartRead32(&data, &pObj->mUnknown0EC, noSwap);
    PartRead32(&data, &pObj->mEmitterType, noSwap);
    PartReadEmitter(&data, &pObj->mEmitter, pObj->mEmitterType, noSwap);
    PartRead8(&data, &pObj->mUnknown043, 1);
    PartReadVec3(&data, (Vec3_801DE1E0 *)&pObj->mUnknown1F4, noSwap);
    PartRead8(&data, &pObj->mUnknown044, 1);
    PartRead32(&data, &pObj->mUnknown200, noSwap);
    PartRead32(&data, &pObj->mCollisionType, noSwap);
    PartReadCollision(&data, &pObj->mCollision, pObj->mCollisionType, noSwap);
    PartRead32(&data, &pObj->mUnknown288, noSwap);
    PartRead(&data, pObj->mUnknown28C, 32, 1);
    PartRead16(&data, &pObj->mUnknown048, noSwap);
}

void *ParticleLibGetSysList(void)
{
    return partLibState.mpUnknown04;
}

int ParticleLibGetOrientation(void)
{
    return partLibState.mUnknown1C;
}

void ParticleLibShutdownCustomBehavior(void)
{
    ParticleCustomBehavior_t *pCustom = &partLibState.mUnknown8C;

    if (pCustom->mUnknownE) {
        fn_801D2BD0(pCustom->mppUnknown0);
        fn_801D2BD0(pCustom->mppUnknown4);
        fn_801D2BD0(pCustom->mppUnknown8);
        pCustom->mppUnknown0 = 0;
        pCustom->mppUnknown4 = 0;
        pCustom->mppUnknown8 = 0;
        pCustom->mUnknownC = 0;
        pCustom->mUnknownE = 0;
    }
}

static float _partGetRandom(void)
{
    return MathGetRandom(partLibState.mpRandom);
}

static int _partGetRandomRange(int range)
{
    return MathGetRandomRange(partLibState.mpRandom, range);
}
