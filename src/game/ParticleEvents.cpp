/* Keeps the lists of particle events and spawned effects, runs them every frame and frees
   the finished ones. */

#include <dolphin/mtx.h>
#include "game/ParticleSys.h"
#include "game/ParticleEvent.h"
#include "game/Ball.h"
#include "game/fn_801C68FC.h"
#include "game/ParticleTrail.h"
#include "engine/llquat.h"

/* One 0x44-byte entry of the pool at _Particles_pSpawnPool. */
struct ParticleSpawn_t {
    Mtx44 mMatrix;
    PsysEmitter_t *mUnknown40;
};

struct ParticleBallTrail_t {
    char mPad000[0x39C];
    float mUnknown39C;
    float mUnknown3A0;
    float mUnknown3A4;
};

extern "C" {
void GroundPulseUpdate(void);
void fn_80146FCC(void);
void fn_80146FD8(void);
void fn_80146FDC(ParticleTrailSet_t *pObject);
void fn_801475F4(void);
void fn_801478A8(void);
void *fn_801C6A20(void *pool);
void *fn_801C6B4C(void *pool, void *item);
void fn_801C6C0C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
int fn_801C6D34(void *pool, int b, void *ctx, int d, int (*fn)(void *, void *), int f);
void fn_801D03D0(Mtx44 m);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0BCC(int a, int b, int c);
void fn_801D0C58(void *a);
void fn_801D0F80(Mtx44 m);

extern unsigned char gParticles_bInit;
}

static void *_Particles_pEventPool = 0;
static int _Particles_iSpare = 0;
static void *_Particles_pSpawnPool = 0;
static ParticleBallTrail_t *_Particles_pBallTrails[2];

extern "C" {

static int _ParticleEventUpdate(void *pItem, void *pContext)
{
    ParticleEvent_t *pEvent = (ParticleEvent_t *)pItem;

    if (pEvent->mType != 7) {
        switch (pEvent->mType) {
        case 0:
            ParticleEventFootstep(pEvent);
            break;
        case 1:
            ParticleEventBodyTrail(pEvent);
            break;
        case 4:
            ParticleEventAttached(pEvent);
            break;
        case 2:
            ParticleEventBodyImpact(pEvent);
            break;
        case 5:
            ParticleEventBallBounce(pEvent);
            break;
        }
        PsysEmitter_t *pObject = pEvent->mUnknown18;
        if (pObject != 0 && pObject->mUnknown2B4 == 0 && pObject->mUnknown3B8 == 0) {
            ParticleSysReleaseEmitter(pObject);
            pEvent->mUnknown18 = 0;
        }
    }
    return 1;
}

static int _ParticleEventStop(void *pItem, void *pContext)
{
    ParticleEvent_t *pEvent = (ParticleEvent_t *)pItem;

    if (pEvent->mType != 7) {
        pEvent->mUnknown04 = 0;
        switch (pEvent->mType) {
        case 0:
        case 2:
        case 4:
        case 5:
            if (pEvent->mUnknown18 != 0) {
                ParticleSysReleaseEmitter(pEvent->mUnknown18);
                pEvent->mUnknown18 = 0;
            }
            break;
        }
    }
    return 1;
}

static int _ParticleEventReset(void *pItem, void *pContext)
{
    ParticleEvent_t *pEvent = (ParticleEvent_t *)pItem;

    if (pEvent->mType != 7) {
        pEvent->mUnknown04 = 0;
    }
    return 1;
}

static void _ParticlesFollowBall(void)
{
    Ball_t *pBall = BallGetCurrent();
    unsigned int i;

    for (i = 0; i < 2; i++) {
        if (_Particles_pBallTrails[i] != 0) {
            _Particles_pBallTrails[i]->mUnknown39C = pBall->mState.mUnknown54.mX;
            _Particles_pBallTrails[i]->mUnknown3A0 = pBall->mState.mUnknown54.mY;
            _Particles_pBallTrails[i]->mUnknown3A4 = pBall->mState.mUnknown54.mZ;
        }
    }
}

static void _ParticlesFreeFinished(void)
{
    ParticleSpawn_t *pDone[64];
    unsigned int count = 0;
    unsigned int i;
    ParticleSpawn_t *pEntry;

    for (pEntry = (ParticleSpawn_t *)fn_801C6B4C(_Particles_pSpawnPool, 0); pEntry != 0;
         pEntry = (ParticleSpawn_t *)fn_801C6C84(_Particles_pSpawnPool, pEntry)) {
        PsysEmitter_t *pObject = pEntry->mUnknown40;
        if (pObject == 0) {
            pDone[count++] = pEntry;
        } else if (pObject->mUnknown2B4 == 0 && pObject->mUnknown3B8 <= 1) {
            ParticleSysReleaseEmitter(pObject);
            pDone[count++] = pEntry;
        }
    }
    for (i = 0; i < count; i++) {
        fn_801C6C0C(_Particles_pSpawnPool, pDone[i]);
    }
}

void ParticlesInit(void)
{
    unsigned int i;

    for (i = 0; i < 2; i++) {
        _Particles_pBallTrails[i] = 0;
    }
    _Particles_pEventPool = fn_801C68FC(1, 0, 75, sizeof(ParticleEvent_t), 0, 0);
    _Particles_pSpawnPool = fn_801C68FC(1, 0, 64, sizeof(ParticleSpawn_t), 0, 0);
    fn_80146FCC();
    gParticles_bInit = 1;
}

void ParticlesShutdown(void)
{
    if (_Particles_pEventPool != 0) {
        fn_801C69E4(_Particles_pEventPool);
        _Particles_pEventPool = 0;
    }
    if (_Particles_pSpawnPool != 0) {
        fn_801C69E4(_Particles_pSpawnPool);
        _Particles_pSpawnPool = 0;
    }
    fn_80146FD8();
    gParticles_bInit = 0;
}

void ParticlesAddPlayerEvent(int type, float (*pMatrix)[4][4], Object_80039F5C *pPlayer, int c)
{
    ParticleEvent_t *pEvent = (ParticleEvent_t *)fn_801C6A20(_Particles_pEventPool);

    if (pEvent != 0) {
        pEvent->mType = type;
        pEvent->mUnknown04 = 0;
        pEvent->mUnknown08 = pMatrix;
        pEvent->mUnknown18 = 0;
        pEvent->mUnknown0C = pPlayer;
        pEvent->mUnknown10 = 0;
        pEvent->mUnknown14 = c;
        pEvent->mUnknown1C = 21;
        fn_801C6AA4(_Particles_pEventPool, pEvent, 0);
    }
}

void ParticlesAddBallEvent(int type, Ball_t *pBall)
{
    ParticleEvent_t *pEvent = (ParticleEvent_t *)fn_801C6A20(_Particles_pEventPool);

    if (pEvent != 0) {
        pEvent->mType = type;
        pEvent->mUnknown04 = 0;
        pEvent->mUnknown08 = (float (*)[4][4])((char *)pBall->mpUnknown00 + 0x20);
        pEvent->mUnknown18 = 0;
        pEvent->mUnknown0C = 0;
        pEvent->mUnknown10 = pBall;
        pEvent->mUnknown14 = 0;
        pEvent->mUnknown1C = 21;
        fn_801C6AA4(_Particles_pEventPool, pEvent, 0);
    }
}

void ParticlesProcess(void)
{
    if (_Particles_pEventPool != 0) {
        fn_801C6D34(_Particles_pEventPool, 0, 0, 0, _ParticleEventUpdate, 1);
    }
    _ParticlesFreeFinished();
    _ParticlesFollowBall();
    fn_801478A8();
    GroundPulseUpdate();
}

void ParticlesResetEvents(void)
{
    if (_Particles_pEventPool != 0) {
        fn_801C6D34(_Particles_pEventPool, 0, 0, 0, _ParticleEventReset, 1);
    }
}

void ParticlesSpawnAt(int a, float *pPos, float *pRot, ParticleSource_t *pSource)
{
    ParticleSpawnArgs_t args;
    Mtx44 m;
    ParticleSpawn_t *pEntry;

    if (_Particles_pSpawnPool == 0) {
        return;
    }
    pEntry = (ParticleSpawn_t *)fn_801C6A20(_Particles_pSpawnPool);
    if (pEntry == 0) {
        return;
    }
    fn_801D03D0(m);
    m[2][3] = m[1][3] = m[0][3] = 0.0f;
    fn_801D0508();
    fn_801D0C58(pPos);
    if (pRot != 0) {
        QuatEulerAngles_t v;
        QuatToEuler(&v, pRot);

        fn_801D0BCC(v.mUnknown8, v.mUnknown4, v.mUnknown0);
    }
    fn_801D0F80(pEntry->mMatrix);
    fn_801D0544();
    args.mUnknown0C = 0;
    args.mUnknown10 = 0;
    args.mUnknown04 = &pEntry->mMatrix;
    args.mUnknown08 = &m;
    args.mUnknown00 = a;
    pEntry->mUnknown40 = ParticleSysSpawnEmitter(&args, 0, pSource);
    fn_801C6AA4(_Particles_pSpawnPool, pEntry, 0);
}

void ParticlesStopOnEnter(void)
{
    if (_Particles_pEventPool != 0) {
        fn_801C6D34(_Particles_pEventPool, 0, 0, 0, _ParticleEventStop, 1);
    }
    fn_801475F4();
}

void ParticlesFlush(void)
{
    _ParticlesFreeFinished();
}

void ParticlesStopOnLeave(void)
{
    if (_Particles_pEventPool != 0) {
        fn_801C6D34(_Particles_pEventPool, 0, 0, 0, _ParticleEventStop, 1);
    }
    fn_801475F4();
}

void ParticleTrailReset(ParticleTrailSet_t *pObject)
{
    pObject->mUnknown568 = 0;
    pObject->mUnknown57C = 0;
    pObject->mUnknown5A4 = 0;
    pObject->mUnknown5A8 = 0;
    fn_80146FDC(pObject);
    pObject->mUnknown5A0 = 0;
    pObject->mUnknown580 = 1.0f;
    pObject->mUnknown588 = 1.0f;
    pObject->mUnknown584 = 1.0f;
    pObject->mUnknown590 = 1.0f;
    pObject->mUnknown598 = 1.0f;
    pObject->mUnknown594 = 1.0f;
}

void ParticleTrailSetTint(ParticleTrailSet_t *pObject, float a, float b, float c)
{
    pObject->mUnknown568 = 1;
    pObject->mUnknown56C = a;
    pObject->mUnknown570 = b;
    pObject->mUnknown574 = c;
}

void ParticleTrailClearTint(ParticleTrailSet_t *pObject)
{
    pObject->mUnknown568 = 0;
    pObject->mUnknown56C = 1.0f;
    pObject->mUnknown570 = 1.0f;
    pObject->mUnknown574 = 1.0f;
}
}
