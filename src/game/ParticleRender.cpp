/* Draws particle emitters: sets up the "ParticleOnePass" (textured) and "ParticleFlat" shaders and
   draws each particle as a coloured, rotated, camera-facing quad. */
#include <dolphin/gx/GXPixel.h>
#include "game/Object_80039F5C.h"
#include "game/ParticleRender.h"
#include "engine/animTexLib.h"
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXTev.h>

struct ShaderTable_t {
    int mCapacity;
    int mCount;
    void *mpEntries;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
};

struct ShaderPass_t {
    char mName[16];
    unsigned char mUnknown10;
    unsigned short mUnknown12;
};

struct ShaderDesc_t {
    char mName[16];
    int mUnknown10;
    int mUnknown14;
    int mCount;
};

struct ShaderDescPasses_t {
    ShaderDesc_t mShader;
    ShaderPass_t mPasses[1];
};

struct Particle_t {
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
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0ADC(int a);
void fn_801DF064(float *pColor, Object_80144CE0 *pEmitter, Particle_t *pParticle);
float fn_801DF184(Object_80144CE0 *pEmitter, Particle_t *pParticle);
void TMRenderBindShader(int a);
void TMRenderSetBlendMode(int a);
void TMShaderLibAlloc(ShaderTable_t *pTable, int count);
void TMShaderLibFree(ShaderTable_t *pTable);
int TMShaderLibAddShader(ShaderTable_t *pTable, ShaderDesc_t *pShader, void (*pSetup)(void));
void TMShaderLibRegister(const char *pName, ShaderTable_t *pTable);
void TMShaderLibUnregister(const char *pName);
int TMShaderLibGetShader(const char *pName);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8022765C(float *pOut, float *pA, float *pB);
void fn_80227C2C(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void fn_80227CC0(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);

static Vector_80039F5C _ParticleRender_aCorners[4] = {
    { -1.0f, -1.0f, 0.0f },
    { -1.0f, 1.0f, 0.0f },
    { 1.0f, 1.0f, 0.0f },
    { 1.0f, -1.0f, 0.0f },
};
static ShaderDesc_t _ParticleRender_OnePassShader = { "ParticleOnePass", 0, 0, 0 };
static ShaderDescPasses_t _ParticleRender_FlatShader = { { "ParticleFlat", 0, 0, 1 }, { { "base", 1, 0 } } };

static ShaderTable_t _ParticleRender_ShaderTable;

static unsigned char _ParticleRender_bInit = 0;
static int _ParticleRender_iOnePassShader = 0;
static int _ParticleRender_iFlatShader = 0;
unsigned char gParticleAnimTexFlag = 0;

#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))

void ParticleRenderSetBlend(int mode)
{
    switch (mode) {
    case 0:
        TMRenderSetBlendMode(2);
        break;
    case 1:
        TMRenderSetBlendMode(6);
        break;
    case 2:
        TMRenderSetBlendMode(0);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_INVSRCCLR, GX_LO_NOOP);
        break;
    default:
        TMRenderSetBlendMode(6);
        break;
    }
}

void ParticleRenderSetupTexturedPass(void)
{
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 0, 1, 0, 0, 2);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

void ParticleRenderSetupFlatPass(void)
{
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 0, 1, 0, 0, 2);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
}

void ParticleRenderInit(int a)
{
    _ParticleRender_bInit = 1;
    TMShaderLibAlloc(&_ParticleRender_ShaderTable, 2);
    TMShaderLibAddShader(&_ParticleRender_ShaderTable, &_ParticleRender_FlatShader.mShader, ParticleRenderSetupFlatPass);
    TMShaderLibAddShader(&_ParticleRender_ShaderTable, &_ParticleRender_OnePassShader, ParticleRenderSetupTexturedPass);
    TMShaderLibRegister("Particles", &_ParticleRender_ShaderTable);
    _ParticleRender_iOnePassShader = TMShaderLibGetShader("ParticleOnePass");
    _ParticleRender_iFlatShader = TMShaderLibGetShader("ParticleFlat");
}

void ParticleRenderShutdown(void)
{
    TMShaderLibUnregister("Particles");
    TMShaderLibFree(&_ParticleRender_ShaderTable);
    _ParticleRender_bInit = 0;
    _ParticleRender_iOnePassShader = 0;
    _ParticleRender_iFlatShader = 0;
}

int ParticleRenderEmitter(Object_80144CE0 *pEmitter, int mode)
{
    int count;
    AnimTex_t *pTexture;
    Particle_t *pParticle;
    int i;

    if (!pEmitter->mUnknown2B4) {
        return 1;
    }
    count = pEmitter->mUnknown3B8;
    pTexture = pEmitter->mpUnknown2AC;
    if (count) {
        fn_801D04C4();
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
        ParticleRenderSetBlend(pEmitter->mUnknown60);
        if (pEmitter->mUnknown45 && pTexture) {
            GXLoadTlut(&pTexture->mGX.mTlutObj, 0);
            GXLoadTexObj(&pTexture->mGX.mTexObj, GX_TEXMAP0);
            TMRenderBindShader(_ParticleRender_iOnePassShader);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
            GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
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
                AnimTexGetCoords(pTexture, pParticle->mUnknown40, pParticle->mUnknown3A, pEmitter->mUnknown48, coords[0]);
                size = fn_801DF184(pEmitter, pParticle);
                fn_801D0508();
                fn_801D0ADC((int)(pParticle->mUnknown50 * 46603.38f));
                for (j = 0; j < 4; j++) {
                    fn_80227264(&corner, &_ParticleRender_aCorners[j], size);
                    fn_80227C2C(&corner, &corner);
                    fn_8022765C(&vertex.mX, &position.mX, &corner.mX);
                    GXPosition3f32(vertex.mX, vertex.mY, vertex.mZ);
                    GXColor4u8(color[0] * 255.0f, color[1] * 255.0f, color[2] * 255.0f, color[3] * 255.0f);
                    GXTexCoord2f32(coords[j][0], coords[j][1]);
                }
                fn_801D0544();
            }
        } else {
            TMRenderBindShader(_ParticleRender_iFlatShader);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
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
                    fn_80227264(&corner, &_ParticleRender_aCorners[j], size);
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
