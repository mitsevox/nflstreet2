#include <dolphin/gx/GXPixel.h>
#include "game/Object_80039F5C.h"
#include "game/cu_801962CC.h"
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>

struct Table_80212850 {
    int mCapacity;
    int mCount;
    void *mpEntries;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
};

struct Pass_80211638 {
    char mName[16];
    unsigned char mUnknown10;
    unsigned short mUnknown12;
};

struct Shader_80196480 {
    char mName[16];
    int mUnknown10;
    int mUnknown14;
    int mCount;
};

struct ShaderPasses_802EDDC0 {
    Shader_80196480 mShader;
    Pass_80211638 mPasses[1];
};

struct Texture_80196564 {
    char mUnknown0[124];
    GXTexObj mTexObj;
    GXTlutObj mTlutObj;
};

struct Particle_80196564 {
    char mUnknown0[12];
    Vector_80039F5C mPosition;
    char mUnknown18[34];
    unsigned short mUnknown3A;
    char mUnknown3C[4];
    int mUnknown40;
    char mUnknown44[12];
    float mUnknown50;
};

extern "C" {
void fn_801C0A38(Texture_80196564 *pTexture, int a, int b, int c, float *pCoords);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0ADC(int a);
void fn_801DF064(float *pColor, Object_80144CE0 *pEmitter, Particle_80196564 *pParticle);
float fn_801DF184(Object_80144CE0 *pEmitter, Particle_80196564 *pParticle);
void fn_8021077C(int a);
void fn_80210BD8(int a);
void fn_802117C8(Table_80212850 *pTable, int count);
void fn_802117F0(Table_80212850 *pTable);
int fn_80211860(Table_80212850 *pTable, Shader_80196480 *pShader, void (*pSetup)(void));
void fn_80211928(const char *pName, Table_80212850 *pTable);
void fn_80211958(const char *pName);
int fn_80211984(const char *pName);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8022765C(float *pOut, float *pA, float *pB);
void fn_80227C2C(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void fn_80227CC0(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void fn_8024CB90(int a, int b);
void fn_8024D418(void);
void fn_8024D450(int a, int b, int c, int d, int e);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
extern "C" void GXLoadTexObj(GXTexObj *pObj, int a);
extern "C" void GXLoadTlut(GXTlutObj *pObject, int a);
void fn_80251604(int a, int b);
void fn_80251690(int a, int b, int c, int d, int e);
void fn_802516D4(int a, int b, int c, int d, int e);
void fn_80251718(int a, int b, int c, int d, int e, int f);
void fn_80251780(int a, int b, int c, int d, int e, int f);
void fn_80251B28(int a, int b, int c, int d);
void fn_80251CC4(int a);

static Vector_80039F5C lbl_802EDD74[4] = {
    { -1.0f, -1.0f, 0.0f },
    { -1.0f, 1.0f, 0.0f },
    { 1.0f, 1.0f, 0.0f },
    { 1.0f, -1.0f, 0.0f },
};
static Shader_80196480 lbl_802EDDA4 = { "ParticleOnePass", 0, 0, 0 };
static ShaderPasses_802EDDC0 lbl_802EDDC0 = { { "ParticleFlat", 0, 0, 1 }, { { "base", 1, 0 } } };

static Table_80212850 lbl_80365188;

static unsigned char lbl_803EB740 = 0;
static int lbl_803EB744 = 0;
static int lbl_803EB748 = 0;
unsigned char lbl_803EB74C = 0;

#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))

void fn_801962CC(int mode)
{
    switch (mode) {
    case 0:
        fn_80210BD8(2);
        break;
    case 1:
        fn_80210BD8(6);
        break;
    case 2:
        fn_80210BD8(0);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_INVSRCCLR, GX_LO_NOOP);
        break;
    default:
        fn_80210BD8(6);
        break;
    }
}

void fn_8019634C(void)
{
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 0, 1, 0, 0, 2);
    fn_80251CC4(1);
    fn_80251B28(0, 0, 0, 4);
    fn_80251690(0, 15, 8, 10, 15);
    fn_80251718(0, 0, 0, 0, 1, 0);
    fn_802516D4(0, 7, 4, 5, 7);
    fn_80251780(0, 0, 0, 0, 1, 0);
}

void fn_80196414(void)
{
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 0, 1, 0, 0, 2);
    fn_80251CC4(1);
    fn_80251B28(0, 255, 255, 4);
    fn_80251604(0, 4);
}

void fn_80196480(int a)
{
    lbl_803EB740 = 1;
    fn_802117C8(&lbl_80365188, 2);
    fn_80211860(&lbl_80365188, &lbl_802EDDC0.mShader, fn_80196414);
    fn_80211860(&lbl_80365188, &lbl_802EDDA4, fn_8019634C);
    fn_80211928("Particles", &lbl_80365188);
    lbl_803EB744 = fn_80211984("ParticleOnePass");
    lbl_803EB748 = fn_80211984("ParticleFlat");
}

void fn_8019651C(void)
{
    fn_80211958("Particles");
    fn_802117F0(&lbl_80365188);
    lbl_803EB740 = 0;
    lbl_803EB744 = 0;
    lbl_803EB748 = 0;
}

int fn_80196564(Object_80144CE0 *pEmitter, int mode)
{
    int count;
    Texture_80196564 *pTexture;
    Particle_80196564 *pParticle;
    int i;

    if (!pEmitter->mUnknown2B4) {
        return 1;
    }
    count = pEmitter->mUnknown3B8;
    pTexture = pEmitter->mpUnknown2AC;
    if (count) {
        fn_801D04C4();
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
        fn_801962CC(pEmitter->mUnknown60);
        if (pEmitter->mUnknown45 && pTexture) {
            GXLoadTlut(&pTexture->mTlutObj, 0);
            GXLoadTexObj(&pTexture->mTexObj, 0);
            fn_8021077C(lbl_803EB744);
            fn_8024D418();
            fn_8024CB90(9, 1);
            fn_8024CB90(11, 1);
            fn_8024CB90(13, 1);
            fn_8024D450(0, 9, 1, 4, 0);
            fn_8024D450(0, 11, 1, 5, 0);
            fn_8024D450(0, 13, 1, 4, 0);
            GXBegin(GX_QUADS, GX_VTXFMT0, count * 4);
            for (i = 0; i < count; i++) {
                pParticle = pEmitter->mppUnknown3C0[i];
                float color[4];
                Vector_80039F5C position;
                Vector_80039F5C vertex;
                Vector_80039F5C corner;
                float coords[4][2];
                float scale;
                float size;
                int j;

                fn_80227CC0(&position, &pParticle->mPosition);
                fn_801DF064(color, pEmitter, pParticle);
                scale = (unsigned int)pEmitter->mUnknown35B * 0.01f;
                color[0] = CLAMP(color[0] * scale, 0.0f, 1.0f);
                color[1] = CLAMP(color[1] * scale, 0.0f, 1.0f);
                color[2] = CLAMP(color[2] * scale, 0.0f, 1.0f);
                fn_801C0A38(pTexture, pParticle->mUnknown40, pParticle->mUnknown3A, pEmitter->mUnknown48, coords[0]);
                size = fn_801DF184(pEmitter, pParticle);
                fn_801D0508();
                fn_801D0ADC((int)(pParticle->mUnknown50 * 46603.38f));
                for (j = 0; j < 4; j++) {
                    fn_80227264(&corner, &lbl_802EDD74[j], size);
                    fn_80227C2C(&corner, &corner);
                    fn_8022765C(&vertex.mX, &position.mX, &corner.mX);
                    GXPosition3f32(vertex.mX, vertex.mY, vertex.mZ);
                    GXColor4u8(color[0] * 255.0f, color[1] * 255.0f, color[2] * 255.0f, color[3] * 255.0f);
                    GXTexCoord2f32(coords[j][0], coords[j][1]);
                }
                fn_801D0544();
            }
        } else {
            fn_8021077C(lbl_803EB748);
            fn_8024D418();
            fn_8024CB90(9, 1);
            fn_8024CB90(11, 1);
            fn_8024D450(0, 9, 1, 4, 0);
            fn_8024D450(0, 11, 1, 5, 0);
            GXBegin(GX_QUADS, GX_VTXFMT0, count * 4);
            for (i = 0; i < count; i++) {
                pParticle = pEmitter->mppUnknown3C0[i];
                float color[4];
                Vector_80039F5C position;
                Vector_80039F5C vertex;
                Vector_80039F5C corner;
                float size;
                int j;

                fn_801DF064(color, pEmitter, pParticle);
                size = fn_801DF184(pEmitter, pParticle);
                fn_80227CC0(&position, &pParticle->mPosition);
                fn_801D0508();
                fn_801D0ADC((int)(pParticle->mUnknown50 * 46603.38f));
                for (j = 0; j < 4; j++) {
                    fn_80227264(&corner, &lbl_802EDD74[j], size);
                    fn_80227C2C(&corner, &corner);
                    fn_8022765C(&vertex.mX, &position.mX, &corner.mX);
                    GXPosition3f32(vertex.mX, vertex.mY, vertex.mZ);
                    GXColor4u8(color[0] * 255.0f, color[1] * 255.0f, color[2] * 255.0f, color[3] * 255.0f);
                }
                fn_801D0544();
            }
        }
        fn_801D0544();
    }
    return 1;
}
}
