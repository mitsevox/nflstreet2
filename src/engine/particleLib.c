#include <string.h>
#include "engine/particleLib.h"
#include "engine/cu_801C06E8.h"
#include "game/cu_801CF5BC.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"

/* Pool of particle systems created from one template (0x6E4 bytes). */
typedef struct Pool_801DE1E0 {
    unsigned short mUnknown000;
    PartObj_801DE1E0 *mpObjs[32];
    unsigned short mFree;
    unsigned short mUsed;
    Template_801DE1E0 mTemplate;
} Pool_801DE1E0;

/* Descriptor passed to fn_801DE1E0 (lbl_802DCFF8 in the game). */
typedef struct Desc_801DE1E0 {
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
} Desc_801DE1E0;

/* Custom behaviour tables of the library state. */
typedef struct Custom_801DE1E0 {
    void **mppUnknown0;
    void **mppUnknown4;
    void **mppUnknown8;
    unsigned short mUnknownC;
    unsigned char mUnknownE;
} Custom_801DE1E0;

/* Library state at lbl_8039AD10. */
typedef struct State_801DE1E0 {
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
    Custom_801DE1E0 mUnknown8C;
} State_801DE1E0;

/* Template pool table at lbl_8039ADAC. */
typedef struct PoolTable_801DD498 {
    Pool_801DE1E0 *mpPools;
    unsigned char *mpUsed;
    int mUnknown8;
} PoolTable_801DD498;

/* Object-type record registered through fn_801D2130 ("PSYSLIB"). */
typedef struct ObjType_801DE1E0 {
    char mUnknown00[8];
    int mUnknown08;
    int mUnknown0C;
    int mUnknown10;
} ObjType_801DE1E0;

extern State_801DE1E0 lbl_8039AD10;
extern PoolTable_801DD498 lbl_8039ADAC;
extern ObjType_801DE1E0 lbl_802F94AC;
extern Vec3_801DE1E0 lbl_802F94C4;
extern unsigned char lbl_803EBD58;
extern float lbl_803ECF4C;

void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0558(void);
void fn_801D08FC(int a);
void fn_801D09EC(int a);
void fn_801D0ADC(int a);
void fn_801D0C58(Vec3_801DE1E0 *pPos);
void fn_801D0F80(float (*m)[4]);
void fn_801D2130(ObjType_801DE1E0 *pType);
int fn_801D2570(int a);
int fn_801D2730(void);
unsigned int fn_801D27F4(int heap);
int fn_801D34D0(void *p, unsigned int size, int value, int flags);
int fn_801DCF0C(unsigned char heap, int size, int count, void (*pAdd)(), void (*pDel)());
int fn_801DCF8C(unsigned char heap);
void *fn_801DCFF0(int a, int b, int c, int d, int e, int f, int g, int h);
void fn_801DD0C8(void *pList, unsigned char heap, int slot, void *pFunc);
void fn_801DD0E8(void *pList);
PartObj_801DE1E0 *fn_801DD168(unsigned char heap, int a, Template_801DE1E0 *pTemplate);
int fn_801DD200(void *pList, void *pObj);
void fn_801DF3E4(unsigned char *pSrc, unsigned char *pDst, unsigned int size, int noSwap);

void fn_801DD730(PartObj_801DE1E0 *pObj, unsigned short count, int step, int steps, float dt);
static void fn_801DDFB0(PartObj_801DE1E0 *pObj, Particle_801DE1E0 *pParticle, float dt);
static void fn_801DE04C(PartObj_801DE1E0 *pObj);
static void fn_801DE114(PartObj_801DE1E0 *pObj);
void fn_801DE564(PartObj_801DE1E0 *pDst, Template_801DE1E0 *pSrc);
void fn_801DE794(PartObj_801DE1E0 *pObj);
void fn_801DE968(PartObj_801DE1E0 *pObj, Texture_801C0928 *pTex);
void fn_801DE9A0(PartObj_801DE1E0 *pObj, Vec3_801DE1E0 *pPos, Vec3_801DE1E0 *pRot);
int fn_801DEA90(PartObj_801DE1E0 *pObj, int steps);
static void fn_801DE7F4(PartObj_801DE1E0 *pObj, Template_801DE1E0 *pTemplate);
static void fn_801DEA50(PartObj_801DE1E0 *pObj);
void fn_801DEF18(PartObj_801DE1E0 *pObj);
void fn_801DFD4C(void);

static void fn_801DD498(void)
{
    fn_801D34D0(&lbl_8039ADAC, sizeof(lbl_8039ADAC), 0, 1);
    lbl_8039ADAC.mpUsed = fn_801D2B7C(lbl_8039AD10.mPoolCount, 0, 0);
    fn_801D34D0(lbl_8039ADAC.mpUsed, lbl_8039AD10.mPoolCount, 0, 1);
    lbl_8039ADAC.mpPools = fn_801D2B7C(lbl_8039AD10.mPoolCount * sizeof(Pool_801DE1E0), 0, 0);
    fn_801D34D0(lbl_8039ADAC.mpPools, lbl_8039AD10.mPoolCount * sizeof(Pool_801DE1E0), 0, 1);
}

static void fn_801DD534(void)
{
    fn_801D2BD0(lbl_8039ADAC.mpUsed);
    lbl_8039ADAC.mpUsed = 0;
    fn_801D2BD0(lbl_8039ADAC.mpPools);
    lbl_8039ADAC.mpPools = 0;
}

static PartObj_801DE1E0 *fn_801DD57C(unsigned short handle)
{
    Pool_801DE1E0 *pPool = &lbl_8039ADAC.mpPools[handle];
    PartObj_801DE1E0 *pObj;
    unsigned int size;
    unsigned short i;

    if (pPool->mFree == 0) {
        goto fail;
    }
    pObj = pPool->mpObjs[pPool->mUsed];
    if (lbl_8039AD10.mUnknown64 != 0) {
        size = 0;
        if (pObj->mMax != 0) {
            size = pObj->mMax * sizeof(Particle_801DE1E0);
            size = (size + 15) & ~15;
        }
        if (fn_801D27F4(lbl_8039AD10.mHeap) < size) {
            goto fail;
        }
        pObj->mpParticles = fn_801D2BB0(lbl_8039AD10.mHeap, size, 0, 0);
        if (pObj->mpParticles == 0) {
            goto fail;
        }
        for (i = 0; i < pObj->mMax; i++) {
            pObj->mppParticles[i] = &pObj->mpParticles[i];
            pObj->mppParticles[i]->mActive = 0;
        }
    }
    fn_801DE564(pObj, &pPool->mTemplate);
    fn_801DE794(pObj);
    pObj->mUnknown2B4 = 1;
    pPool->mUsed++;
    pPool->mFree--;
    return pObj;
fail:
    return 0;
}

static void fn_801DD6B8(PartObj_801DE1E0 *pObj)
{
    int i;
    int last = pObj->mCount - 1;

    for (i = last; i >= 0; i--) {
        Particle_801DE1E0 *pParticle = pObj->mppParticles[i];

        if (pParticle->mAge < pParticle->mLife) {
            continue;
        }
        pParticle->mActive = 0;
        if (i != last) {
            Particle_801DE1E0 *pLast = pObj->mppParticles[last];
            pObj->mppParticles[last] = pParticle;
            pObj->mppParticles[i] = pLast;
        }
        pObj->mCount--;
        last = pObj->mCount - 1;
    }
}

static void fn_801DDCC4(PartObj_801DE1E0 *pObj)
{
    unsigned int i;

    for (i = 0; i < pObj->mCount; i++) {
        pObj->mppParticles[i]->mActive = 0;
    }
}

static void fn_801DDD00(PartObj_801DE1E0 *pObj, float dt)
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
        if (!(pObj->mUnknown3B0 <= pObj->mUnknown054 * lbl_8039AD10.mUnknown10)) {
            pObj->mUnknown0B0 = 0.0f;
            if (pObj->mCount == 0) {
                pObj->mUnknown2B4 = 0;
                if (pObj->mUnknown2B5 == 1) {
                    fn_801DEF18(pObj);
                }
            }
        }
        break;
    case 2:
        if (!(pObj->mUnknown0B0 > pObj->mUnknown054) && pObj->mCount == 0) {
            pObj->mUnknown2B4 = 0;
            if (pObj->mUnknown2B5 == 1) {
                fn_801DEF18(pObj);
            }
        }
        break;
    }
}

static void fn_801DDE08(PartObj_801DE1E0 *pObj, float dt)
{
    unsigned short i;

    fn_801E03F4(pObj);
    for (i = 0; i < pObj->mCount; i++) {
        Particle_801DE1E0 *pParticle = pObj->mppParticles[i];

        if (pObj->mCollisionType != 0 || pObj->mColExtCount != 0) {
            fn_801E043C(pObj, pParticle);
        }
        pParticle->mPrevPos = pParticle->mPos;
        fn_801DDFB0(pObj, pParticle, dt);
        pParticle->mForce.x = pParticle->mForce.y = pParticle->mForce.z = 0.0f;
        if (pObj->mUnknown041 != 0) {
            pParticle->mUnknown4C = (pParticle->mAge * pObj->mUnknown0E4 + 1.0f) * pParticle->mUnknown30;
        }
        pParticle->mAgeRatio = pParticle->mAge / pParticle->mLife;
        pParticle->mAge += dt;
        pParticle->mUnknown50 += dt * pParticle->mUnknown34;
        pParticle->mUnknown40 = pParticle->mAge * lbl_8039AD10.mUnknown14;
    }
}

static void fn_801DDFB0(PartObj_801DE1E0 *pObj, Particle_801DE1E0 *pParticle, float dt)
{
    float scale = pObj->mUnknown2B0 * dt;

    pParticle->mVel.x += pParticle->mForce.x * scale;
    pParticle->mVel.y += pParticle->mForce.y * scale;
    pParticle->mVel.z += pParticle->mForce.z * scale;
    pParticle->mPos.x = pParticle->mVel.x * dt + pParticle->mPrevPos.x;
    pParticle->mPos.y = pParticle->mVel.y * dt + pParticle->mPrevPos.y;
    pParticle->mPos.z = pParticle->mVel.z * dt + pParticle->mPrevPos.z;
}

static void fn_801DE010(PartObj_801DE1E0 *pObj)
{
    switch (pObj->mForceType) {
    case 1:
        fn_801DE04C(pObj);
        break;
    case 0:
        fn_801DE114(pObj);
        break;
    }
}

static void fn_801DE04C(PartObj_801DE1E0 *pObj)
{
    Vec3_801DE1E0 force;
    unsigned int i;

    float x;
    float y;
    float z;

    fn_80227264(&force, &lbl_8039AD10.mUnknown78, -(pObj->mUnknown090 * pObj->mUnknown094));
    x = force.x;
    y = force.y;
    z = force.z;
    for (i = 0; i < pObj->mCount; i++) {
        Particle_801DE1E0 *pParticle = pObj->mppParticles[i];

        pParticle->mForce.x = pParticle->mVel.x * -0.45f + (pParticle->mForce.x + x);
        pParticle->mForce.y = pParticle->mVel.y * -0.45f + (pParticle->mForce.y + y);
        pParticle->mForce.z = pParticle->mVel.z * -0.45f + (pParticle->mForce.z + z);
    }
}

static void fn_801DE114(PartObj_801DE1E0 *pObj)
{
    Vec3_801DE1E0 force;
    unsigned short i;

    float x;
    float y;
    float z;

    fn_80227264(&force, &lbl_8039AD10.mUnknown78, pObj->mUnknown098 * pObj->mUnknown090);
    x = force.x;
    y = force.y;
    z = force.z;
    for (i = 0; i < pObj->mCount; i++) {
        Particle_801DE1E0 *pParticle = pObj->mppParticles[i];

        pParticle->mForce.x += x;
        pParticle->mForce.y += y;
        pParticle->mForce.z += z;
    }
}

float fn_801DE1B8(void)
{
    return fn_801CF69C(lbl_8039AD10.mpRandom);
}

void fn_801DE1E0(Desc_801DE1E0 *pDesc)
{

    lbl_8039AD10.mUnknown00 = pDesc->mUnknown00;
    lbl_8039AD10.mUnknown60 = pDesc->mUnknown04;
    lbl_8039AD10.mUnknown62 = pDesc->mUnknown06;
    lbl_8039AD10.mpUnknown0C = pDesc->mpUnknown20;
    lbl_8039AD10.mpUnknown08 = fn_801DEA90;
    lbl_8039AD10.mUnknown17 = 0;
    lbl_8039AD10.mUnknown16 = pDesc->mUnknown24;
    lbl_8039AD10.mUnknown14 = pDesc->mUnknown08;
    lbl_8039AD10.mUnknown10 = 1.0f / (unsigned int)lbl_8039AD10.mUnknown14;
    lbl_8039AD10.mUnknown84 = fn_801CF7AC();
    lbl_8039AD10.mpRandom = fn_801CF5BC(0, lbl_8039AD10.mUnknown84);
    lbl_8039AD10.mPoolCount = pDesc->mUnknown18;
    fn_801DCF0C(lbl_8039AD10.mUnknown00, sizeof(PartObj_801DE1E0), pDesc->mUnknown04,
                (void (*)())fn_801DE7F4, (void (*)())fn_801DEA50);
    lbl_8039AD10.mpUnknown04 = fn_801DCFF0(1, lbl_8039AD10.mUnknown60, 0, 0, 0, 2, 1, -1);
    fn_801DD0C8(lbl_8039AD10.mpUnknown04, lbl_8039AD10.mUnknown00, 0, lbl_8039AD10.mpUnknown08);
    fn_801DD0C8(lbl_8039AD10.mpUnknown04, lbl_8039AD10.mUnknown00, 1, lbl_8039AD10.mpUnknown0C);
    lbl_8039AD10.mUnknown64 = pDesc->mUnknown10;
    if (lbl_8039AD10.mUnknown64) {
        lbl_8039AD10.mHeap = fn_801D2730();
        lbl_802F94AC.mUnknown08 = lbl_8039AD10.mHeap;
        lbl_8039AD10.mUnknown68 = (pDesc->mUnknown14 + 15) & ~15;
        lbl_802F94AC.mUnknown10 = lbl_8039AD10.mUnknown68;
        fn_801D2130(&lbl_802F94AC);
    } else {
        lbl_8039AD10.mUnknown68 = 0;
        lbl_8039AD10.mHeap = 0;
    }
    fn_801DD498();
    lbl_8039AD10.mUnknown74 = pDesc->mUnknown0C;
    fn_80227264(&lbl_8039AD10.mUnknown78, &lbl_802F94C4, pDesc->mUnknown0C);
    lbl_8039AD10.mUnknown1C = pDesc->mUnknown1C;
    lbl_8039AD10.mUnknown18 = 0;
    fn_801D04C4();
    fn_801D0558();
    switch (lbl_8039AD10.mUnknown1C) {
    case 0:
        break;
    case 1:
        lbl_8039AD10.mUnknown18 = 1;
        fn_801D08FC(0x400000);
        break;
    }
    fn_80227C2C(&lbl_8039AD10.mUnknown78, &lbl_8039AD10.mUnknown78);
    fn_801D0F80(lbl_8039AD10.mUnknown20);
    fn_801D0544();
    lbl_8039AD10.mUnknown8C.mppUnknown0 = 0;
    lbl_8039AD10.mUnknown8C.mppUnknown4 = 0;
    lbl_8039AD10.mUnknown8C.mppUnknown8 = 0;
    lbl_8039AD10.mUnknown8C.mUnknownE = 0;
    lbl_803EBD58 = 1;
}

void fn_801DE410(void)
{
    State_801DE1E0 *pState = &lbl_8039AD10;

    fn_801DD534();
    fn_801DFD4C();
    fn_801DD0E8(pState->mpUnknown04);
    fn_801DCF8C(pState->mUnknown00);
    fn_801CF67C(pState->mpRandom);
    if (pState->mUnknown64) {
        fn_801D2570(pState->mHeap);
    }
    pState->mUnknown64 = 0;
    pState->mUnknown00 = 0;
    pState->mUnknown74 = 0.0f;
    pState->mUnknown1C = 0;
    pState->mUnknown78.x = lbl_802F94C4.x;
    pState->mUnknown78.y = lbl_802F94C4.y;
    pState->mUnknown78.z = lbl_802F94C4.z;
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
    fn_801D04C4();
    fn_801D0558();
    fn_801D0F80(pState->mUnknown20);
    fn_801D0544();
    lbl_803EBD58 = 0;
}

void fn_801DE4F8(unsigned int rate)
{
    lbl_8039AD10.mUnknown14 = rate;
    lbl_8039AD10.mUnknown10 = 1.0f / rate;
}

static void fn_801DE540(Vec4_801DE1E0 *pDst, Vec4_801DE1E0 *pSrc)
{
    pDst->x = pSrc->x;
    pDst->y = pSrc->y;
    pDst->z = pSrc->z;
    pDst->w = pSrc->w;
}

void fn_801DE564(PartObj_801DE1E0 *pDst, Template_801DE1E0 *pSrc)
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
    fn_801DE9A0(pDst, &pSrc->mObj.mUnknown064, &pSrc->mObj.mUnknown070);
    fn_801DE540(&pDst->mUnknown07C, &pSrc->mObj.mUnknown07C);
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
    fn_801DFE0C(pDst, &pSrc->mObj);
    pDst->mUnknown043 = pSrc->mObj.mUnknown043;
    pDst->mUnknown1F4 = pSrc->mObj.mUnknown1F4;
    pDst->mUnknown1F8 = pSrc->mObj.mUnknown1F8;
    pDst->mUnknown1FC = pSrc->mObj.mUnknown1FC;
    pDst->mUnknown044 = pSrc->mObj.mUnknown044;
    pDst->mUnknown200 = pSrc->mObj.mUnknown200;
    pDst->mCollisionType = pSrc->mObj.mCollisionType;
    CopyParticleCollisionPayload(pDst, &pSrc->mObj);
    pDst->mUnknown288 = pSrc->mObj.mUnknown288;
    pDst->mUnknown048 = pSrc->mObj.mUnknown048;
}

void fn_801DE794(PartObj_801DE1E0 *pObj)
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

static void fn_801DE7F4(PartObj_801DE1E0 *pObj, Template_801DE1E0 *pTemplate)
{
    unsigned short i;
    Texture_801C0928 *pTex;

    if (pTemplate->mObj.mUnknown03F) {
        pObj->mMax = pTemplate->mObj.mUnknown0B4;
    } else {
        pObj->mMax = lbl_8039AD10.mUnknown62;
    }
    pObj->mppParticles = fn_801D2B7C(pObj->mMax * sizeof(Particle_801DE1E0 *), 0, 0);
    fn_801D34D0(pObj->mppParticles, pObj->mMax * sizeof(Particle_801DE1E0 *), 0, 1);
    pObj->mpParticles = fn_801D2B7C(pObj->mMax * sizeof(Particle_801DE1E0), 0, 0);
    fn_801D34D0(pObj->mpParticles, pObj->mMax * sizeof(Particle_801DE1E0), 0, 1);
    for (i = 0; i < pObj->mMax; i++) {
        pObj->mppParticles[i] = &pObj->mpParticles[i];
    }
    fn_801DE564(pObj, pTemplate);
    fn_801DE794(pObj);
    pTex = fn_801C0D8C(pTemplate->mObj.mUnknown28C);
    if (pTex) {
        fn_801DE968(pObj, pTex);
    }
    pObj->mUnknown2B4 = 1;
}

PartObj_801DE1E0 *fn_801DE918(Template_801DE1E0 *pTemplate)
{
    State_801DE1E0 *pState = &lbl_8039AD10;
    PartObj_801DE1E0 *pObj;

    pObj = fn_801DD168(pState->mUnknown00, 0, pTemplate);
    fn_801DD200(pState->mpUnknown04, pObj);
    return pObj;
}

void fn_801DE968(PartObj_801DE1E0 *pObj, Texture_801C0928 *pTex)
{
    pObj->mUnknown045 = 1;
    pObj->mpUnknown2AC = pTex;
    strcpy(pObj->mUnknown28C, pTex->mName);
}

void fn_801DE9A0(PartObj_801DE1E0 *pObj, Vec3_801DE1E0 *pPos, Vec3_801DE1E0 *pRot)
{
    fn_801D0508();
    if (pPos) {
        fn_801D0C58(pPos);
    }
    if (pRot) {
        fn_801D0ADC((int)(pRot->z * 46603.38f));
        fn_801D09EC((int)(pRot->y * 46603.38f));
        fn_801D08FC((int)(pRot->x * 46603.38f));
    }
    fn_801D0F80(pObj->mUnknown35C);
    fn_801D0544();
}

static void fn_801DEA50(PartObj_801DE1E0 *pObj)
{
    fn_801D2BD0(pObj->mppParticles);
    if (pObj->mpParticles) {
        fn_801D2BD0(pObj->mpParticles);
    }
}

int fn_801DEA90(PartObj_801DE1E0 *pObj, int steps)
{
    void (*pfnEmit)(PartObj_801DE1E0 *, float);
    void (*pfnUpdate)(PartObj_801DE1E0 *, float);
    void (*pfnPre)(PartObj_801DE1E0 *);
    float dt;
    float rate;
    unsigned short count;
    Custom_801DE1E0 *pCustom;
    int i;

    if (!pObj->mUnknown2B4) {
        return 0;
    }
    pfnEmit = 0;
    pfnUpdate = 0;
    pfnPre = 0;
    pCustom = &lbl_8039AD10.mUnknown8C;
    if (pCustom->mUnknownE) {
        pfnEmit = (void (*)(PartObj_801DE1E0 *, float))pCustom->mppUnknown0[pObj->mUnknown358];
        pfnUpdate = (void (*)(PartObj_801DE1E0 *, float))pCustom->mppUnknown4[pObj->mUnknown358];
        pfnPre = (void (*)(PartObj_801DE1E0 *))pCustom->mppUnknown8[pObj->mUnknown358];
    }
    dt = lbl_8039AD10.mUnknown10;
    if (!lbl_8039AD10.mUnknown17) {
        dt *= (float)steps;
        steps = 1;
    }
    if (pObj->mUnknown044) {
        pObj->mUnknown3A8 = fn_802270D4(&pObj->mUnknown39C);
        lbl_803ECF4C = pObj->mUnknown3A8 * pObj->mUnknown200 + 1.0f;
    }
    for (i = 0; i < steps; i++) {
        if (!pObj->mUnknown04C) {
            fn_801DDD00(pObj, dt);
        }
        if (!pObj->mUnknown2B4) {
            break;
        }
        if (pObj->mCount) {
            if (pfnPre) {
                pfnPre(pObj);
            } else {
                fn_801DD6B8(pObj);
            }
        }
        fn_801DE010(pObj);
        if (pfnUpdate) {
            pfnUpdate(pObj, dt);
        } else {
            fn_801DDE08(pObj, dt);
        }
        if (!(pObj->mUnknown0B0 <= 0.0f) && pObj->mCount < pObj->mMax) {
            if (pfnEmit) {
                pfnEmit(pObj, dt);
            } else {
                if (pObj->mUnknown044) {
                    rate = pObj->mUnknown0B0 * lbl_803ECF4C;
                } else {
                    rate = pObj->mUnknown0B0;
                }
                rate = rate * dt + pObj->mUnknown3AC;
                count = rate;
                if (count) {
                    fn_801DD730(pObj, count, i, steps, dt);
                }
                pObj->mUnknown3AC = rate - (unsigned int)count;
            }
        }
        pObj->mUnknown3B0 += dt;
    }
    return 0;
}

unsigned short fn_801DECFC(unsigned short count, Template_801DE1E0 *pTemplate)
{
    unsigned short index;
    unsigned short i;
    unsigned short j;
    PartObj_801DE1E0 *pObj;

    index = 0;
    for (i = 0; i < lbl_8039AD10.mPoolCount; i++) {
        if (lbl_8039ADAC.mpUsed[i] == 0) {
            index = i;
            break;
        }
    }
    for (i = 0; i < count; i++) {
        pObj = fn_801DE918(pTemplate);
        if (lbl_8039AD10.mUnknown64) {
            fn_801D2BD0(pObj->mpParticles);
            for (j = 0; j < pObj->mMax; j++) {
                pObj->mppParticles[j] = 0;
            }
            pObj->mpParticles = 0;
        }
        pObj->mUnknown2B4 = 0;
        pObj->mUnknown2B5 = 1;
        pObj->mUnknown358 = index;
        lbl_8039ADAC.mpPools[index].mpObjs[i] = pObj;
    }
    lbl_8039ADAC.mpPools[index].mUnknown000 = count;
    lbl_8039ADAC.mpPools[index].mFree = count;
    lbl_8039ADAC.mpPools[index].mUsed = 0;
    lbl_8039ADAC.mpUsed[index] = 1;
    lbl_8039ADAC.mpPools[index].mTemplate = *pTemplate;
    fn_801E098C(&pTemplate->mRamp, &lbl_8039ADAC.mpPools[index].mTemplate.mRamp);
    return index;
}

PartObj_801DE1E0 *fn_801DEEF8(unsigned short handle)
{
    return fn_801DD57C(handle);
}

void fn_801DEF18(PartObj_801DE1E0 *pObj)
{
    unsigned short index = pObj->mUnknown358;
    Pool_801DE1E0 *pPool = &lbl_8039ADAC.mpPools[index];
    unsigned short i;
    unsigned short last;
    unsigned short j;
    PartObj_801DE1E0 *pSwap;

    last = pPool->mUsed - 1;
    for (i = 0; i < pPool->mUsed; i++) {
        if (pPool->mpObjs[i] == pObj) {
            break;
        }
    }
    pObj->mUnknown2B4 = 0;
    fn_801DDCC4(pObj);
    if (lbl_8039AD10.mUnknown64) {
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
    lbl_8039ADAC.mpPools[index].mUsed--;
    lbl_8039ADAC.mpPools[index].mFree++;
}

float fn_801DF184(PartObj_801DE1E0 *pObj, Particle_801DE1E0 *pParticle)
{
    if (pObj->mUnknown041) {
        return pParticle->mUnknown4C;
    }
    return pParticle->mUnknown30;
}

void fn_801DF1A0(unsigned char **ppData, void *pDst, int noSwap)
{
    fn_801DF3E4(*ppData, pDst, 1, noSwap);
    *ppData += 1;
}

void fn_801DF1E4(unsigned char **ppData, void *pDst, int noSwap)
{
    fn_801DF3E4(*ppData, pDst, 2, noSwap);
    *ppData += 2;
}

void fn_801DF228(unsigned char **ppData, void *pDst, int noSwap)
{
    fn_801DF3E4(*ppData, pDst, 4, noSwap);
    *ppData += 4;
}

void fn_801DF26C(unsigned char **ppData, void *pDst, unsigned int size, int noSwap)
{
    fn_801DF3E4(*ppData, pDst, size, noSwap);
    *ppData += size;
}

void fn_801DF2AC(unsigned char **ppData, Vec3_801DE1E0 *pDst, int noSwap)
{
    fn_801DF3E4(*ppData, (unsigned char *)&pDst->x, 4, noSwap);
    *ppData += 4;
    fn_801DF3E4(*ppData, (unsigned char *)&pDst->y, 4, noSwap);
    *ppData += 4;
    fn_801DF3E4(*ppData, (unsigned char *)&pDst->z, 4, noSwap);
    *ppData += 4;
}

static void fn_801DF338(unsigned char **ppData, Vec4_801DE1E0 *pDst, int noSwap)
{
    fn_801DF3E4(*ppData, (unsigned char *)&pDst->x, 4, noSwap);
    *ppData += 4;
    fn_801DF3E4(*ppData, (unsigned char *)&pDst->y, 4, noSwap);
    *ppData += 4;
    fn_801DF3E4(*ppData, (unsigned char *)&pDst->z, 4, noSwap);
    *ppData += 4;
    fn_801DF3E4(*ppData, (unsigned char *)&pDst->w, 4, noSwap);
    *ppData += 4;
}

static void fn_801DF428(unsigned char **ppData, Emitter_801DFE0C *pDst, unsigned int type, int noSwap)
{
    unsigned char *pData = *ppData;

    switch (type) {
    case 0:
        fn_801DF2AC(&pData, &pDst->mPoint, noSwap);
        break;
    case 1:
        fn_801DF2AC(&pData, &pDst->mCase1.mUnknown00, noSwap);
        fn_801DF2AC(&pData, &pDst->mCase1.mUnknown0C, noSwap);
        break;
    case 2:
        fn_801DF2AC(&pData, &pDst->mCase2.mUnknown00, noSwap);
        fn_801DF228(&pData, &pDst->mCase2.mUnknown0C, noSwap);
        break;
    case 3:
        fn_801DF2AC(&pData, &pDst->mCase3.mUnknown00, noSwap);
        fn_801DF2AC(&pData, &pDst->mCase3.mUnknown0C, noSwap);
        fn_801DF2AC(&pData, &pDst->mCase3.mUnknown18, noSwap);
        fn_801DF228(&pData, &pDst->mCase3.mUnknown24, noSwap);
        fn_801DF228(&pData, &pDst->mCase3.mUnknown28, noSwap);
        fn_801DF2AC(&pData, &pDst->mCase3.mUnknown2C, noSwap);
        fn_801DF2AC(&pData, &pDst->mCase3.mUnknown38, noSwap);
        fn_801DF228(&pData, &pDst->mCase3.mUnknown44, noSwap);
        break;
    }
    *ppData += 0x100;
}

static void fn_801DF578(unsigned char **ppData, Collision_801E0384 *pDst, unsigned int type, int noSwap)
{
    unsigned char *pData = *ppData;

    switch (type) {
    case 0:
        break;
    case 1:
        fn_801DF228(&pData, &pDst->mGround.mHeight, noSwap);
        break;
    case 2:
        fn_801DF2AC(&pData, &pDst->mParm[0], noSwap);
        fn_801DF2AC(&pData, &pDst->mParm[1], noSwap);
        fn_801DF2AC(&pData, &pDst->mParm[2], noSwap);
        break;
    }
    *ppData += 0x80;
}

void *fn_801DFD34(void)
{
    return lbl_8039AD10.mpUnknown04;
}

int fn_801DFD40(void)
{
    return lbl_8039AD10.mUnknown1C;
}

void fn_801DFD4C(void)
{
    Custom_801DE1E0 *pCustom = &lbl_8039AD10.mUnknown8C;

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

static float fn_801DFDB8(void)
{
    return fn_801CF69C(lbl_8039AD10.mpRandom);
}

static int fn_801DFDE0(int range)
{
    return fn_801CF6D4(lbl_8039AD10.mpRandom, range);
}
