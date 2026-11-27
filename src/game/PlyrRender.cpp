/* Player rendering: sets up each player's model parts, head and face morph, poses and draws
   the player every frame (with level of detail, eye movement, the big-head cheat and the
   style-meter glow and afterimages), and draws the players' shadows and trails. */

#include "engine/viewport.h"
#include "game/StyleTracker.h"
#include "game/PlayerObjInit.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/FEPlyrLoad.h"
#include "game/PlyrTex.h"
#include "game/GameModeType.h"
#include "game/GameObjList.h"

#include <dolphin/gx/GXVert.h>
#include <string.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>

struct PlyrRenderSlot_t {
    Object_8003DEC4 *mpUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    void *mpUnknown12;
    Block_8003DEC4 *mpUnknown16;
    void *mpUnknown20;
    void *mpUnknown24;
    void *mpUnknown28;
    void *mpUnknown32;
    void *mpUnknown36[2];
    unsigned char mUnknown44;
    char mUnknown45[3];
};

struct PlyrRenderColor_t {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct PlyrRenderVec3_t {
    float x;
    float y;
    float z;
};

struct PlyrModelData_t {
    char mUnknown0[24];
    void *mpUnknown24;
};

struct PlyrRenderPart_t {
    const char *mpName;
    const char *mpPass;
    short mUnknown8;
    short mUnknownA;
    const char *mpTexture;
    int mUnknownC[8];
};

struct PlyrRenderPartTable_t {
    int mUnknown0;
    PlyrRenderPart_t *mpUnknown4;
};

static int _PlyrRender_aPartParams[31] = {
    0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 255, 255, 255, 0, 255, 255, 255, 255, 255, 0, 0, 0, 0,
};

static float _PlyrRender_aGlowColorFrom[3] = {4.0f, 0.09f, 0.01f};
static float _PlyrRender_aGlowColorTo[3] = {0.7f, 0.02f, 0.12f};
static float _PlyrRender_aLodBounds[8] = {-0.7f, 0.0f, -0.7f, 0.0f, 0.7f, 2.0f, 0.7f, 0.0f};

#define PART_ENTRY(name, pass, texture) { name, pass, 1, 0, texture }

PlyrRenderPart_t _PlyrRender_aParts[56] = {
    PART_ENTRY("baseHead", "OnePass", "HEAD"),
    PART_ENTRY("facialHair", "OnePass", "FACIALHAIR"),
    PART_ENTRY("eyeL", "OnePassTX", "HEAD"),
    PART_ENTRY("eyeR", "OnePassTX", "HEAD"),
    PART_ENTRY("chain", "OnePass", "CHAIN"),
    PART_ENTRY("medallion", "OnePass", "MEDALLION"),
    PART_ENTRY("hairUpper", "OnePass", "HAIR"),
    PART_ENTRY("hairUpperAlpha", "OnePass", "HAIR"),
    PART_ENTRY("hairLower", "OnePass", "HAIR"),
    PART_ENTRY("hairLowerAlpha", "OnePass", "HAIR"),
    PART_ENTRY("torso", "OnePass", "TORSO"),
    PART_ENTRY("collarHood", "OnePass", "TORSO"),
    PART_ENTRY("shoulderPadL", "OnePass", "SHOULDERPAD"),
    PART_ENTRY("hat", "OnePass", "HAT"),
    PART_ENTRY("glasses", "OnePass", "GLASSES"),
    PART_ENTRY("shoulderPadUnderL", "OnePass", "SHOULDERPAD"),
    PART_ENTRY("shoulderPadUnderR", "OnePass", "SHOULDERPAD"),
    PART_ENTRY("bicepL", "OnePass", "BICEP"),
    PART_ENTRY("bicepSweatBandL", "OnePass", "BICEP"),
    PART_ENTRY("sweatBandBicepL", "OnePass", "BICEPSWEATBAND"),
    PART_ENTRY("elbowL", "OnePass", "ELBOW"),
    PART_ENTRY("forearmL", "OnePass", "FOREARM"),
    PART_ENTRY("wristL", "OnePass", "FOREARM"),
    PART_ENTRY("wristPartL", "OnePass", "WRIST"),
    PART_ENTRY("hand_Left", "OnePass", "LEFTHAND"),
    PART_ENTRY("shoulderPadR", "OnePass", "SHOULDERPAD"),
    PART_ENTRY("bicepR", "OnePass", "BICEP"),
    PART_ENTRY("bicepSweatBandR", "OnePass", "BICEP"),
    PART_ENTRY("sweatBandBicepR", "OnePass", "BICEPSWEATBAND"),
    PART_ENTRY("elbowR", "OnePass", "ELBOW"),
    PART_ENTRY("forearmR", "OnePass", "FOREARM"),
    PART_ENTRY("wristR", "OnePass", "FOREARM"),
    PART_ENTRY("wristPartR", "OnePass", "WRIST"),
    PART_ENTRY("hand_Rt", "OnePass", "RIGHTHAND"),
    PART_ENTRY("hipThigh", "OnePass", "THIGH"),
    PART_ENTRY("kneeL", "OnePass", "KNEE"),
    PART_ENTRY("shinUpperL", "OnePass", "UPPERSHIN"),
    PART_ENTRY("shinLowerL", "OnePass", "LOWERSHIN"),
    PART_ENTRY("shoeL", "OnePass", "SHOE"),
    PART_ENTRY("kneeR", "OnePass", "KNEE"),
    PART_ENTRY("shinUpperR", "OnePass", "UPPERSHIN"),
    PART_ENTRY("shinLowerR", "OnePass", "LOWERSHIN"),
    PART_ENTRY("shoeR", "OnePass", "SHOE"),
    PART_ENTRY("dclTorsoFront", "OnePass", "DECALFRONT"),
    PART_ENTRY("dclTorsoBack", "OnePass", "DECALBACK"),
    PART_ENTRY("hatDcl", "OnePass", "DECALHAT"),
    PART_ENTRY("hatLDcl", "OnePass", "HATLDCL"),
    PART_ENTRY("tatooBicepL", "OnePass", "TATOOBICEPL"),
    PART_ENTRY("tatooBicepR", "OnePass", "TATOOBICEPR"),
    PART_ENTRY("tatooForearmL", "OnePass", "TATOOFOREARML"),
    PART_ENTRY("tatooForearmR", "OnePass", "TATOOFOREARMR"),
    PART_ENTRY("tatooElbowL", "OnePass", "TATOOELBOWL"),
    PART_ENTRY("tatooElbowR", "OnePass", "TATOOELBOWR"),
    PART_ENTRY("dclLogo", "OnePass", "DECALFRONT"),
    PART_ENTRY("dclNumber", "OnePass", "DECALBACK"),
    PART_ENTRY("dclName", "OnePass", "NAMEPLATE"),
};

static unsigned char _PlyrRender_aJointFlags[30] = {0};

static PlyrRenderSlot_t _PlyrRender_aSlots[14];
static Record_8020F2C4 _PlyrRender_BlendModel;
static char _PlyrRender_aBlendBuffer[16];
static char _PlyrRender_aShadowTexLib[40];

static Viewport_t *_PlyrRender_pViewport;
static unsigned int _PlyrRender_uNumSlots;
static int _PlyrRender_iShadowTexture;
static int _PlyrRender_iShadowClut;
static int _PlyrRender_pShadowTexData;

static unsigned char _PlyrRender_bHideFlagged = 1;
static float _PlyrRender_fFarDistance = 2.0f;
static unsigned char _PlyrRender_bLodsUpdated = 0;
static unsigned int _PlyrRender_uHeadModelSize = 16000;
static int _PlyrRender_aiUnused[2] = {0, 0};
static float _PlyrRender_fFaceDepthBias = -0.0012f;
static float _PlyrRender_fHairDepthBias = -0.0024f;
static float _PlyrRender_fFaceDepthBiasNear = -0.0002f;
static float _PlyrRender_fHairDepthBiasNear = -0.0004f;
static void (*_PlyrRender_pHeadModelCallback)(Object_8003DEC4 *pPlayer) = 0;
static Object_8003DEC4 *_PlyrRender_pHeadModelPlayer = 0;
static unsigned char _PlyrRender_bHeadModelReady = 0;
static PlyrRenderPartTable_t _PlyrRender_aPartTables[1] = {{56, _PlyrRender_aParts}};
static unsigned char _PlyrRender_bPendingPlayerCall = 0;
static unsigned char _PlyrRender_ucPendingPlayerArg = 0;
static int _PlyrRender_iUnused = -1;

extern "C" {
extern float gFrameTimeScale;

int InGameIsPlaying(void);
int FELoopIsMainFEActive(void);
int PlyrObjsGetCount(void);
Object_80039F5C *PlyrObjsFindPlayer(Block_80170E64 *object);
float MathMapRangeClamped(float x, float hi, float vhi, float lo, float vlo);
int PlayerLookShowsHair(int index);
unsigned char PlayerLookHidesHead(int index);
unsigned char PlayerObjIsDrawReady(void);
unsigned char CheatFlagsIsSet(int index);
int fn_800A2624(void);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
int fn_800ADDD8(PlyrPosePart_t *pElements, int index);
unsigned int fn_800B823C(int team);
void fn_800C2150(Object_8003DEC4 *pPlayer, Block_800C2788 *pBlock, int a);
void fn_800C2884(Object_8003DEC4 *pPlayer, Block_800C2EC0 *pBlock, int a);
void ParticleTrailUpdateAfterimage(Object_8003DEC4 *pPlayer, float f);
void FEPlyrLoadMarkDrawn(Object_8003DEC4 *pPlayer);
void *fn_8015E2FC(int a, int b, int c);
int fn_8015E440(int a, int b);
void fn_8015E73C(int id);
void fn_8015E908(int a);
void fn_8015E9F4(int a, int *p);
void fn_8015EB4C(int a, int b);
void fn_8015EC74(int a, int b);
void fn_8015ED9C(int a, int b);
void fn_8015F3FC(int a);
void fn_8015F82C(int id, Object_8003DEC4 *pPlayer, void (*pCallback)(Object_8003DEC4 *));
void PlyrModelAttachLod(void *a, void *b);
void *PlaTexCacheGetArchive(void);
ModelTexSlot_t *PlaTexCacheGetDescs(int player);
void PlaTexCacheCloseArchive(void);
void ParticleTrailDraw(ParticleTrailSet_t *p);
void PlyrModelDrawNameplate(Object_8003DEC4 *pPlayer);
void ConGetCurrentContext(void);
void MatSetStack(void);
void MatPush(void);
void MatPop(void);
void MatCat(void *pMatrix);
void MatLoad(void *pMatrix);
void MatRotY(int a);
void MatTranslate(float *p);
void MatScale(float scale);
void MatScaleCol(float x, float y, float z);
void MatStore(float (*pMatrix)[4]);
int fn_801D2BB0(int a, void *p, int b, int c);
void fn_801D2BD0(int handle);
void ObjSetPriority(void *a, Object_8003DEC4 *pPlayer, int b);
void ResLoadToBuffer(void *a, int b, int c);
void ResUnLoad(void *a, int b);
void *ResGetSize(void *a, int b);
void TMModelReset(Record_8020F2C4 *p);
void TMModelClone(void *pDst, void *pSrc);
void TMModelRemapMaterials(Record_8020F2C4 *p, PlyrRenderPartTable_t *pRef);
void TMModelResetChannels(Record_8020F2C4 *p);
void TMModelAllocChannels(Record_8020F2C4 *p);
void TMModelFreeChannels(Record_8020F2C4 *p);
void TMMaterialListSetMatDefs(void *p, void *q);
void TMRenderReset(void);
void TMRenderBindModel(Record_8020F2C4 *p);
void TMRenderBindClusterObj(Joints_8003DEC4 *p);
void TMRenderBindTexture(int a, int b, int c);
void TMRenderBindMaterialList(void *p);
void TMRenderSetBlendMode(int a);
void TMRenderSetZRange(float a, float b);
void TMRenderGeomNode(int a, int b);
void TMTexLibLoad(void *p, int handle);
void TMTexLibUnload(void *p);
void TMTexLibRegistryReset(void);
void TMTexLibRegister(const char *pName, void *p);
int TMTexLibGetTexture(void *p, unsigned int color);
int TMTexLibGetClut(void *p, unsigned int color, int a);
void TMBufferNew(void *p, int a, int b);
void TMBufferDelete(void *p);
void TMBufferReset(void *p);
int TMBufferGetFreeSpace(void *p);
int TMBlendSetWeightsFloat(float *p, int a);
void TMBlendBegin(void *p);
void TMBlendFlushBuffer(void);
void TMBlendEnd(void);
void TMBlendBindModel2(Record_8020F2C4 *pDst, Record_8020F2C4 *pSrc);
int TMBlendGeomAll(void);
void Vec3Lerp(PlyrRenderVec3_t *pOut, float *pA, float *pB, float t);
void fn_802336C4(void *p, void *q, int a);
void fn_80233728(void *p);
void fn_80233760(void *p, short *pValues, int count);
void fn_802337D4(void *pModel, Joints_8003DEC4 *pJoints, void *pPose, unsigned int mask);
void fn_80233850(void *pModel, Joints_8003DEC4 *pJoints, void *pPose, unsigned int mask, unsigned char *pFlags);
void fn_80233BB8(Joints_8003DEC4 *p, int a, int b);
void fn_80233BD8(Joints_8003DEC4 *p);
void fn_80233BE0(void);
void fn_80233CBC(void *p, int index, int value);
void fn_802341AC(void);
void fn_802341B8(void);
void fn_802341C4(Lod_802341C4 *p);
void fn_802341E8(Lod_802341C4 *p);
void ModelLodBalance(int a);
void fn_802345BC(PlyrRenderPartTable_t *p);
void fn_8023465C(void *p, void *pModel, ModelTexSlot_t *pDescs);
void fn_8023472C(void *p, int a, int b, ModelTexSlot_t *pA, ModelTexSlot_t *pB, int c);
void fn_8023488C(void *p, int a);
void fn_802348AC(void *p);
void FloatArrayAlloc(void *p, int a);
void fn_80234994(void *p);
void fn_802349B8(void *p, int a);
void fn_80234A14(Part_8003DEC4 *p, int a);
void fn_80234A30(Part_8003DEC4 *p, int a);
void fn_80234A90(Part_8003DEC4 *p);
void fn_80234A94(Part_8003DEC4 *p, void *pModel);
void fn_80234AD8(Part_8003DEC4 *p, void *pModel);
void fn_80234BF4(int a, Part_8003DEC4 *p, int b);
void fn_80234CA4(Part_8003DEC4 *p, Joints_8003DEC4 *pJoints);
void fn_80234CAC(Part_8003DEC4 *p, void *q);
void fn_80234CF0(Part_8003DEC4 *p, int a, void *q);
void fn_80234DC0(Part_8003DEC4 *p, int a);
int LLLightLoadSetTinted(int a, float r, float g, float b);
void LLLightLoadDirectional(int a, PlyrRenderVec3_t *pScale, void *p);
int LLFogEnable(int a);
void GXSetCullMode(int a);
void GXSetChanMatColor(int chan, PlyrRenderColor_t color);
void GXSetNumChans(int n);
void GXSetChanCtrl(int chan, int enable, int amb, int mat, int lights, int diff, int attn);
void GXSetBlendMode(int type, int src, int dst, int op);
void GXSetZMode(int enable, int func, int update);
void GXSetZCompLoc(int a);
void GXLoadPosMtxImm(float (*pMatrix)[4], int id);
void GXSetCurrentMtx(int id);
void GXLoadTexMtxImm(float (*pMatrix)[4], int id, int type);

int PlyrHeadDrawFace(Object_8003DEC4 *pPlayer);
void PlyrHeadDrawFaceAlpha(Object_8003DEC4 *pPlayer, int flag);
int PlyrHeadBlendFace(Object_8003DEC4 *pPlayer);
struct PlyrRenderPoseJoint_t { short mX, mY, mZ; };
void PlyrRenderPoseModel(Object_8003DEC4 *pPlayer, float *pScale, float (*pMatrix)[4], ParticleTrailSet_t *pTrail,
                 int index, void *pModel, void **ppModels, unsigned int lod);
void PlyrRenderLoadTexMtx(int id, float sx, float sy, float tx, float ty);
void PlyrHeadGetEyeOffsets(Object_8003DEC4 *pPlayer, float *pA, float *pB);
void PlyrHeadOnModelLoaded(Object_8003DEC4 *pPlayer);
void PlyrRenderBindPartTable(int index);
void PlyrRenderUnbindPartTable(void);

void PlyrRenderLoadShadowTexture(void)
{
    void *p = ResGetSize(PlaTexCacheGetArchive(), 0);

    _PlyrRender_pShadowTexData = fn_801D2BB0(InGameIsPlaying() ? 0x40 : 1, p, 2, 0);
    ResLoadToBuffer(PlaTexCacheGetArchive(), 0, _PlyrRender_pShadowTexData);
    TMTexLibLoad(_PlyrRender_aShadowTexLib, _PlyrRender_pShadowTexData);
    _PlyrRender_iShadowTexture = TMTexLibGetTexture(_PlyrRender_aShadowTexLib, 0xFF000000);
    _PlyrRender_iShadowClut = TMTexLibGetClut(_PlyrRender_aShadowTexLib, 0xFF000000, 0);
}

void PlyrRenderUnloadShadowTexture(void)
{
    TMTexLibUnload(_PlyrRender_aShadowTexLib);
    fn_801D2BD0(_PlyrRender_pShadowTexData);
    if (FELoopIsMainFEActive()) {
        ResUnLoad(PlaTexCacheGetArchive(), 0);
        PlaTexCacheCloseArchive();
    }
}

void PlyrRenderVptCallback(Viewport_t *pObject)
{
    unsigned int i;

    TMBufferReset(_PlyrRender_aBlendBuffer);
    TMModelResetChannels(&_PlyrRender_BlendModel);
    for (i = 0; i < _PlyrRender_uNumSlots; i++) {
        Object_8003DEC4 *pPlayer = PlyrObjsGet(i);

        if (pPlayer->mUnknown20 & 8) {
            continue;
        }
        if (pPlayer->mUnknown20 & 0x20000) {
            ObjSetPriority((void *)GameObjList::GetListHandle(), pPlayer, 11);
        }
    }
}

int PlyrRenderCalcLight(Object_8003DEC4 *pPlayer)
{
    float r = 1.0f;
    float g = r;
    float b = r;
    int flash = 0;
    int light;
    float block[4];
    PlyrRenderVec3_t scale;
    PlyrRenderVec3_t color;

    if (pPlayer->mUnknown20 & 0x20000) {
        flash = pPlayer->mUnknown5188.mUnknown564 < 12.0f;
    }
    if (pPlayer->mUnknown972) {
        if (((LightSource_t *)pPlayer->mUnknown972)->mUnknownC != pPlayer->mUnknown5188.mUnknown580 ||
            ((LightSource_t *)pPlayer->mUnknown972)->mUnknown10 != pPlayer->mUnknown5188.mUnknown584 ||
            ((LightSource_t *)pPlayer->mUnknown972)->mUnknown14 != pPlayer->mUnknown5188.mUnknown588) {
            pPlayer->mUnknown5188.mUnknown590 =
                (pPlayer->mUnknown5188.mUnknown580 - pPlayer->mUnknown5188.mUnknown590) *
                    (pPlayer->mUnknown5188.mUnknown5A0 * (1.0f / 15.0f)) +
                pPlayer->mUnknown5188.mUnknown590;
            pPlayer->mUnknown5188.mUnknown594 =
                (pPlayer->mUnknown5188.mUnknown584 - pPlayer->mUnknown5188.mUnknown594) *
                    (pPlayer->mUnknown5188.mUnknown5A0 * (1.0f / 15.0f)) +
                pPlayer->mUnknown5188.mUnknown594;
            pPlayer->mUnknown5188.mUnknown598 =
                (pPlayer->mUnknown5188.mUnknown588 - pPlayer->mUnknown5188.mUnknown598) *
                    (pPlayer->mUnknown5188.mUnknown5A0 * (1.0f / 15.0f)) +
                pPlayer->mUnknown5188.mUnknown598;
            pPlayer->mUnknown5188.mUnknown580 = ((LightSource_t *)pPlayer->mUnknown972)->mUnknownC;
            pPlayer->mUnknown5188.mUnknown584 = ((LightSource_t *)pPlayer->mUnknown972)->mUnknown10;
            pPlayer->mUnknown5188.mUnknown588 = ((LightSource_t *)pPlayer->mUnknown972)->mUnknown14;
            pPlayer->mUnknown5188.mUnknown5A0 = 0;
        }
        if (pPlayer->mUnknown5188.mUnknown5A0 < 15) {
            float t = pPlayer->mUnknown5188.mUnknown5A0++;

            r = (pPlayer->mUnknown5188.mUnknown580 - pPlayer->mUnknown5188.mUnknown590) * (1.0f / 15.0f) * t +
                pPlayer->mUnknown5188.mUnknown590;
            g = (pPlayer->mUnknown5188.mUnknown584 - pPlayer->mUnknown5188.mUnknown594) * (1.0f / 15.0f) * t +
                pPlayer->mUnknown5188.mUnknown594;
            b = (pPlayer->mUnknown5188.mUnknown588 - pPlayer->mUnknown5188.mUnknown598) * (1.0f / 15.0f) * t +
                pPlayer->mUnknown5188.mUnknown598;
        } else {
            r = pPlayer->mUnknown5188.mUnknown580;
            g = pPlayer->mUnknown5188.mUnknown584;
            b = pPlayer->mUnknown5188.mUnknown588;
        }
    }
    if (pPlayer->mUnknown5188.mUnknown5A4) {
        if (pPlayer->mUnknown5188.mUnknown5A8 < 30) {
            float s = 2.0f - (float)pPlayer->mUnknown5188.mUnknown5A8++ * (1.0f / 30.0f);

            r *= pPlayer->mUnknown5188.mUnknown56C * s;
            g *= pPlayer->mUnknown5188.mUnknown570 * s;
            b *= pPlayer->mUnknown5188.mUnknown574 * s;
        } else {
            pPlayer->mUnknown5188.mUnknown5A4 = 0;
            pPlayer->mUnknown5188.mUnknown5A8 = 0;
        }
    } else if (pPlayer->mUnknown5188.mUnknown568 == 1) {
        r *= pPlayer->mUnknown5188.mUnknown56C;
        g *= pPlayer->mUnknown5188.mUnknown570;
        b *= pPlayer->mUnknown5188.mUnknown574;
    }
    if (flash) {
        Vec3Lerp(&color, _PlyrRender_aGlowColorFrom, _PlyrRender_aGlowColorTo, StyleTrackerGetMeterFraction(pPlayer->mUnknown4968));
        r = color.x;
        g = color.y;
        b = color.z;
    }
    light = LLLightLoadSetTinted(1, r, g, b);
    if (LightTrackerUpdate(&pPlayer->mUnknown4960, (LightSource_t *)pPlayer->mUnknown972, block, &scale.x)) {
        scale.x *= r;
        scale.y *= g;
        scale.z *= b;
        LLLightLoadDirectional(0, &scale, block);
    }
    return light;
}

void PlyrRenderDrawModel(Object_8003DEC4 *pPlayer, unsigned int flags)
{
    PlyrRenderColor_t color = {255};
    float depth;
    int light;

    color.g = 255;
    color.b = 255;
    color.a = 255;
    TMRenderReset();
    if (pPlayer->mUnknown20 & 8) {
        depth = 1.0f - pPlayer->mUnknown4216.mUnknown16 * _PlyrRender_fFaceDepthBiasNear;
    } else {
        depth = 1.0f - pPlayer->mUnknown4216.mUnknown16 * _PlyrRender_fFaceDepthBias;
    }
    light = PlyrRenderCalcLight(pPlayer);
    GXSetChanMatColor(0, color);
    GXSetChanMatColor(4, color);
    GXSetNumChans(1);
    GXSetChanCtrl(0, 1, 0, 0, light, 2, 2);
    GXSetChanCtrl(2, 0, 0, 0, light, 0, 2);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetCullMode(1);
    TMRenderSetBlendMode(1);
    fn_80234BF4(0, &pPlayer->mUnknown1164[0], 0);
    light = PlyrHeadDrawFace(pPlayer);
    fn_80234BF4(0, &pPlayer->mUnknown1164[2], 0);
    fn_80234BF4(0, &pPlayer->mUnknown1164[3], 0);
    TMRenderSetZRange(0.0f, depth);
    fn_80234BF4(0, &pPlayer->mUnknown1164[7], 0);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    TMRenderSetBlendMode(2);
    PlyrHeadDrawFaceAlpha(pPlayer, light);
    fn_80234BF4(0, &pPlayer->mUnknown1164[11], 0);
    fn_80234BF4(0, &pPlayer->mUnknown1164[9], 0);
    if (!PlayerLookShowsHair(pPlayer->mUnknown4971)) {
        TMRenderSetBlendMode(1);
    }
    if (pPlayer->mUnknown20 & 8) {
        depth = 1.0f - pPlayer->mUnknown4216.mUnknown16 * _PlyrRender_fHairDepthBiasNear;
    } else {
        depth = 1.0f - pPlayer->mUnknown4216.mUnknown16 * _PlyrRender_fHairDepthBias;
    }
    TMRenderSetZRange(0.0f, depth);
    fn_80234BF4(0, &pPlayer->mUnknown1164[6], 0);
    if (!PlayerLookShowsHair(pPlayer->mUnknown4971)) {
        TMRenderSetBlendMode(2);
    }
    fn_80234BF4(0, &pPlayer->mUnknown1164[1], 0);
    fn_80234BF4(0, &pPlayer->mUnknown1164[8], 0);
    TMRenderSetBlendMode(1);
    TMRenderSetZRange(0.0f, 1.0f);
    GXSetCullMode(0);
}

int PlyrHeadDrawFace(Object_8003DEC4 *pPlayer)
{
    int result = 0;
    PlyrRenderSlot_t *pSlot = pPlayer->mUnknown1160;

    if (pSlot->mUnknown8 == 0) {
        float a[2];
        float b[2];

        if (pSlot->mUnknown4 & 8) {
            result = PlyrHeadBlendFace(pPlayer);
        }
        if (result) {
            TMRenderBindModel(&_PlyrRender_BlendModel);
        } else {
            TMRenderBindModel(&pSlot->mpUnknown16->mUnknown16);
        }
        TMRenderBindMaterialList(pPlayer->mUnknown4044);
        TMRenderBindClusterObj(&pPlayer->mUnknown4064[1]);
        TMRenderSetBlendMode(1);
        GXSetCullMode(0);
        PlyrHeadGetEyeOffsets(pPlayer, a, b);
        PlyrRenderLoadTexMtx(30, 1.0f, 1.0f, b[0], b[1]);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        TMRenderGeomNode(2, 0);
        PlyrRenderLoadTexMtx(30, 1.0f, 1.0f, a[0], a[1]);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        TMRenderGeomNode(3, 0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        TMRenderGeomNode(1, 0);
    } else {
        fn_80234BF4(0, &pPlayer->mUnknown1164[4], 0);
    }
    return result;
}

void PlyrHeadDrawFaceAlpha(Object_8003DEC4 *pPlayer, int flag)
{
    if (flag) {
        TMRenderBindModel(&_PlyrRender_BlendModel);
        TMRenderBindMaterialList(pPlayer->mUnknown4044);
        TMRenderBindClusterObj(&pPlayer->mUnknown4064[1]);
        TMRenderGeomNode(4, 0);
    } else {
        fn_80234BF4(0, &pPlayer->mUnknown1164[5], 0);
    }
}

static inline void _FxAssert(int)
{
}
#define FX_ASSERT(e) _FxAssert(e)

void PlyrRenderDrawAfterimages(Object_8003DEC4 *pPlayer, PlyrRenderSlot_t *pSlot, unsigned int count)
{
    PlyrRenderColor_t color = {255};
    unsigned int i = 0;
    PlyrRenderVec3_t v;
    int light;
    int index;

    color.g = 255;
    color.b = 255;
    color.a = 255;
    float fraction = StyleTrackerGetMeterFraction(pPlayer->mUnknown4968);
    // FAKEMATCH: compiled-out range assert on the meter fraction; its 1.0f enters the pool before 0.0f
    FX_ASSERT(fraction <= 1.0f && fraction >= 0.0f);
    Vec3Lerp(&v, _PlyrRender_aGlowColorFrom, _PlyrRender_aGlowColorTo, fraction);
    light = LLLightLoadSetTinted(1, v.x, v.y, v.z);
    GXSetChanMatColor(0, color);
    GXSetNumChans(1);
    GXSetChanCtrl(0, 1, 0, 0, light, 2, 2);
    GXSetChanCtrl(2, 0, 0, 0, light, 0, 2);
    TMRenderSetBlendMode(2);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetCullMode(1);
    index = pPlayer->mUnknown5188.mUnknown554;
    for (i = 0; i < pPlayer->mUnknown5188.mUnknown558; i++) {
        color.a = (pPlayer->mUnknown5188.mUnknown558 - i) * 51 + 25;
        GXSetChanMatColor(4, color);
        if (i < count) {
            PlyrRenderPoseModel(pPlayer, 0, pPlayer->mUnknown5188.mUnknown260[index], &pPlayer->mUnknown5188, index,
                        pSlot->mpUnknown12, pSlot->mpUnknown36, pSlot->mUnknown8);
            fn_80234BF4(0, &pPlayer->mUnknown1164[0], 0);
            PlyrHeadDrawFace(pPlayer);
            fn_80234BF4(0, &pPlayer->mUnknown1164[7], 0);
            fn_80234BF4(0, &pPlayer->mUnknown1164[2], 0);
            fn_80234BF4(0, &pPlayer->mUnknown1164[3], 0);
            fn_80234BF4(0, &pPlayer->mUnknown1164[9], 0);
            fn_80234BF4(0, &pPlayer->mUnknown1164[6], 0);
        }
        index++;
        index &= 1;
    }
    ParticleTrailUpdateAfterimage(pPlayer, gFrameTimeScale);
    TMRenderSetBlendMode(1);
    TMRenderSetZRange(0.0f, 1.0f);
    GXSetCullMode(0);
}

int PlyrHeadBlendFace(Object_8003DEC4 *pPlayer)
{
    int result = 0;

    if (TMBufferGetFreeSpace(_PlyrRender_aBlendBuffer) > 0xCE3 && TMBlendSetWeightsFloat(pPlayer->mUnknown820, pPlayer->mUnknown816) > 0) {
        result = 1;
        TMBlendBegin(_PlyrRender_aBlendBuffer);
        TMBlendBindModel2(&pPlayer->mUnknown1024[0].mUnknown16, &_PlyrRender_BlendModel);
        TMBlendGeomAll();
        TMBlendEnd();
        TMBlendFlushBuffer();
    }
    return result;
}

void PlyrRenderPoseModel(Object_8003DEC4 *pPlayer, float *pScale, float (*pMatrix)[4], ParticleTrailSet_t *pTrail,
                 int index, void *pModel, void **ppModels, unsigned int lod)
{
    float scale = 1.5f;
    short *pPose;
    unsigned int i;
    unsigned int j;

    if (pTrail) {
        pPose = (short *)&pTrail->mUnknown2E0[index];
    } else {
        pPose = pPlayer->mUnknown44.mUnknown48;
    }
    MatPush();
    MatCat(pMatrix);
    MatScale(pPlayer->mUnknown24);
    if (pScale) {
        MatScaleCol(pScale[0], pScale[1], pScale[2]);
    }
    MatPush();
    fn_80233BE0();
    if (!(pPlayer->mUnknown20 & 0x2000)) {
        if (pTrail) {
            MatTranslate(&pTrail->mUnknown448[index].mX);
            MatRotY(pTrail->mUnknown460[index]);
        } else {
            MatTranslate(pPlayer->mUnknown44.mUnknown8);
            MatRotY(pPlayer->mUnknown44.mUnknown32);
        }
    }
    if (pPlayer->mUnknown20 & 0x4000) {
        fn_80233850(pPlayer->mUnknown1164[0].mpUnknown12, &pPlayer->mUnknown4064[0], pPose, 0xE0000000,
                    _PlyrRender_aJointFlags);
    } else {
        fn_802337D4(pPlayer->mUnknown1164[0].mpUnknown12, &pPlayer->mUnknown4064[0], pPose, 0xE0000000);
    }
    fn_802337D4(pPlayer->mUnknown1164[4].mpUnknown12, &pPlayer->mUnknown4064[1], pPose, 0xE0000000);
    if (CheatFlagsIsSet(0x20) && !GameModeTypeGet()) {
        for (i = 1; i < pPlayer->mUnknown1164[4].mpUnknown12->mpUnknown12->mUnknown4; i++) {
            if (pPlayer->mUnknown1164[4].mpUnknown12->mpUnknown12->mpUnknown0->mUnknown0[i][0] == 13) {
                for (j = 0; j < 12; j++) {
                    if (j != 3 && j != 7 && j != 11) {
                        pPlayer->mUnknown4064[1].mpUnknown0[i].mUnknown0[j] *= scale;
                    }
                }
            }
        }
    }
    if (pPlayer->mUnknown1164[7].mpUnknown12) {
        fn_802337D4(pPlayer->mUnknown1164[7].mpUnknown12, &pPlayer->mUnknown4064[3], pPose, 0xE0000000);
        if (CheatFlagsIsSet(0x20) && !GameModeTypeGet()) {
            if (pPlayer->mUnknown1164[7].mpUnknown12->mpUnknown12->mUnknown4 == 1) {
                for (j = 0; j < 12; j++) {
                    if (j != 3 && j != 7 && j != 11) {
                        pPlayer->mUnknown4064[3].mpUnknown0[0].mUnknown0[j] *= scale;
                    }
                }
            } else {
                for (i = 1; i < pPlayer->mUnknown1164[7].mpUnknown12->mpUnknown12->mUnknown4; i++) {
                    if (pPlayer->mUnknown1164[7].mpUnknown12->mpUnknown12->mpUnknown0->mUnknown0[i][0] == 13) {
                        for (j = 0; j < 12; j++) {
                            if (j != 3 && j != 7 && j != 11) {
                                pPlayer->mUnknown4064[3].mpUnknown0[i].mUnknown0[j] *= scale;
                            }
                        }
                    }
                }
            }
        }
    }
    if (pPlayer->mUnknown1164[9].mpUnknown12) {
        fn_802337D4(pPlayer->mUnknown1164[9].mpUnknown12, &pPlayer->mUnknown4064[4], pPose, 0xE0000000);
        if (CheatFlagsIsSet(0x20) && !GameModeTypeGet()) {
            if (pPlayer->mUnknown1164[9].mpUnknown12->mpUnknown12->mUnknown4 == 1) {
                for (j = 0; j < 12; j++) {
                    if (j != 3 && j != 7 && j != 11) {
                        pPlayer->mUnknown4064[4].mpUnknown0[0].mUnknown0[j] *= scale;
                    }
                }
            } else {
                for (i = 1; i < pPlayer->mUnknown1164[9].mpUnknown12->mpUnknown12->mUnknown4; i++) {
                    if (pPlayer->mUnknown1164[9].mpUnknown12->mpUnknown12->mpUnknown0->mUnknown0[i][0] == 13) {
                        for (j = 0; j < 12; j++) {
                            if (j != 3 && j != 7 && j != 11) {
                                pPlayer->mUnknown4064[4].mpUnknown0[i].mUnknown0[j] *= scale;
                            }
                        }
                    }
                }
            }
        }
    }
    MatPop();
    if (pPlayer->mUnknown1164[6].mpUnknown12) {
        float (*pBones)[4][4] = pPlayer->mUnknown44.mUnknown52;
        short *pHead;

        if (pTrail) {
            pHead = pTrail->mUnknown468[index].mUnknown;
            MatPush();
            MatCat(pTrail->mUnknown4D4[index]);
        } else {
            MatPush();
            MatLoad(pPlayer->mUnknown908);
            fn_800C2150(pPlayer, &pPlayer->mUnknown280, !(pPlayer->mUnknown20 & 8));
            MatPop();
            pHead = pPlayer->mUnknown280.mUnknown256.mUnknown48;
            MatPush();
            MatCat(pBones[13]);
        }
        pHead[0] = pPose[39];
        pHead[1] = pPose[40];
        pHead[2] = pPose[41];
        fn_802337D4(pPlayer->mUnknown1164[6].mpUnknown12, &pPlayer->mUnknown4064[2], pHead, 0xE0000000);
        MatPop();
    }
    if (pPlayer->mUnknown1164[11].mpUnknown12) {
        float (*pBones)[4][4] = pPlayer->mUnknown44.mUnknown52;
        short *pHat;

        MatPush();
        MatLoad(pPlayer->mUnknown908);
        fn_800C2884(pPlayer, &pPlayer->mUnknown596, !(pPlayer->mUnknown20 & 8));
        MatPop();
        pHat = pPlayer->mUnknown596.mUnknown160.mUnknown48;
        MatPush();
        MatCat(pBones[11]);
        pHat[0] = pPose[33];
        pHat[1] = pPose[34];
        pHat[2] = pPose[35];
        pHat[3] = pPose[42];
        pHat[4] = pPose[43];
        pHat[5] = pPose[44];
        pHat[6] = pPose[60];
        pHat[7] = pPose[61];
        pHat[8] = pPose[62];
        fn_802337D4(pPlayer->mUnknown1164[11].mpUnknown12, &pPlayer->mUnknown4064[5], pHat, 0xE0000000);
        if (CheatFlagsIsSet(0x20) && !GameModeTypeGet()) {
            if (pPlayer->mUnknown1164[6].mpUnknown12->mpUnknown12->mUnknown4 == 1) {
                for (j = 0; j < 12; j++) {
                    if (j != 3 && j != 7 && j != 11) {
                        pPlayer->mUnknown4064[2].mpUnknown0[0].mUnknown0[j] *= scale;
                    }
                }
            } else {
                for (i = 0; i < pPlayer->mUnknown1164[6].mpUnknown12->mpUnknown12->mUnknown4; i++) {
                    if (pPlayer->mUnknown1164[6].mpUnknown12->mpUnknown12->mpUnknown0->mUnknown0[i][0] == 0) {
                        for (j = 0; j < 12; j++) {
                            if (j != 3 && j != 7 && j != 11) {
                                pPlayer->mUnknown4064[2].mpUnknown0[i].mUnknown0[j] *= scale;
                            }
                        }
                    }
                }
            }
        }
        MatPop();
    }
    if (lod <= 1) {
        short *apHands[2];
        unsigned int k;

        for (k = 0; k <= 1; k++) {
            if (pPlayer->mUnknown116[k].mUnknown0 == 1 && lod == 0) {
                float (*pBones)[4][4] = pPlayer->mUnknown44.mUnknown52;
                int bone;

                if (k == 0) {
                    bone = 0x17;
                } else {
                    bone = 0x11;
                }
                apHands[k] = pPlayer->mUnknown116[k].mUnknown12.mUnknown48;
                MatPush();
                MatCat(pBones[bone]);
                apHands[k][0] = ((PlyrRenderPoseJoint_t *)pPose)[bone + 1].mX;
                apHands[k][1] = ((PlyrRenderPoseJoint_t *)pPose)[bone + 1].mY;
                apHands[k][2] = ((PlyrRenderPoseJoint_t *)pPose)[bone + 1].mZ;
                fn_802337D4(ppModels[k], &pPlayer->mUnknown4136[k], apHands[k], 0);
                if (CheatFlagsIsSet(0x20) && !GameModeTypeGet()) {
                    if (pPlayer->mUnknown1164[11].mpUnknown12->mpUnknown12->mUnknown4 == 1) {
                        for (j = 0; j < 12; j++) {
                            if (j != 3 && j != 7 && j != 11) {
                                pPlayer->mUnknown4064[5].mpUnknown0[0].mUnknown0[j] *= scale;
                            }
                        }
                    } else {
                        for (i = 1; i < pPlayer->mUnknown1164[11].mpUnknown12->mpUnknown12->mUnknown4; i++) {
                            if (pPlayer->mUnknown1164[11].mpUnknown12->mpUnknown12->mpUnknown0->mUnknown0[i][0] == 13) {
                                for (j = 0; j < 12; j++) {
                                    if (j != 3 && j != 7 && j != 11) {
                                        pPlayer->mUnknown4064[5].mpUnknown0[i].mUnknown0[j] *= scale;
                                    }
                                }
                            }
                        }
                    }
                }
                MatPop();
            }
        }
    }
    MatPop();
}

unsigned int PlyrRenderGetHideFlags(Object_8003DEC4 *pPlayer)
{
    unsigned int flags = 0;
    unsigned int state = pPlayer->mUnknown4216.mUnknown20;

    if ((state & 0x3F) || (_PlyrRender_bHideFlagged && (state & 0x2000))) {
        if (!(pPlayer->mUnknown20 & 8)) {
            flags = 1;
        }
    } else if (state & 0xF0000) {
        flags |= 2;
    }
    if (!(pPlayer->mUnknown20 & 1)) {
        flags |= 1;
    }
    if (!PlayerObjIsDrawReady()) {
        flags |= 1;
    }
    if (flags & 1) {
        pPlayer->mUnknown20 |= 0x200;
    } else {
        pPlayer->mUnknown20 &= ~0x200;
    }
    return flags;
}

void PlyrRenderInitPart(Part_8003DEC4 *pPart, int a, Joints_8003DEC4 *pJoints, void *pContext)
{
    fn_80234A30(pPart, a);
    fn_80234CA4(pPart, pJoints);
    fn_80234CF0(pPart, 0, pContext);
    fn_80234DC0(pPart, 10);
}

void PlyrHeadInitFacePart(Part_8003DEC4 *pPart, void *pContext, Object_8003DEC4 *pPlayer)
{
    fn_80234A30(pPart, 0);
    fn_80234CA4(pPart, &pPlayer->mUnknown4064[1]);
    fn_80234CF0(pPart, 0, pContext);
    fn_80234DC0(pPart, 10);
    FloatArrayAlloc(&pPlayer->mUnknown816, 0x40);
    fn_80234CAC(pPart, &pPlayer->mUnknown816);
    fn_802349B8(&pPlayer->mUnknown816, 12);
    pPlayer->mUnknown830 = 0x24;
}

void PlyrHeadBuildModel(Object_8003DEC4 *pPlayer, int unused)
{
    short values[53];
    int a;
    int b;
    int i;

    memset(values, 0, sizeof(values));
    if (pPlayer->mUnknown992 == 0xFFFF) {
        PlyrModelAttachLod(fn_8015E2FC(6, 0, 0), fn_8015E2FC(5, 0, 0));
        PlyrModelAttachLod(fn_8015E2FC(6, 0, 1), fn_8015E2FC(5, 0, 1));
        TMModelClone(fn_8015E2FC(4, 0, 0), fn_8015E2FC(6, 0, 0));
        TMModelClone(fn_8015E2FC(4, 0, 1), fn_8015E2FC(6, 0, 1));
        for (i = 0; i < 53; i++) {
            values[i] = pPlayer->mUnknown4976.mValues[i] * 4096.0f;
        }
        values[pPlayer->mUnknown4972 + 1] = 0x1000;
        if (PlayerLookHidesHead(pPlayer->mUnknown4971)) {
            values[6] = 0x1000;
        }
    } else {
        fn_8015E73C(pPlayer->mUnknown992);
        PlyrModelAttachLod(fn_8015E2FC(4, 0, 0), fn_8015E2FC(5, 0, 0));
        PlyrModelAttachLod(fn_8015E2FC(4, 0, 1), fn_8015E2FC(5, 0, 1));
        values[1] = 0x1000;
        values[pPlayer->mUnknown4972 + 2] = 0x1000;
        if (PlayerLookHidesHead(pPlayer->mUnknown4971)) {
            values[7] = 0x1000;
        }
    }
    fn_802336C4(&pPlayer->mUnknown1024[0], fn_8015E2FC(6, 0, 0), _PlyrRender_uHeadModelSize);
    fn_802336C4(&pPlayer->mUnknown1024[1], fn_8015E2FC(6, 0, 1), _PlyrRender_uHeadModelSize >> 1);
    if (pPlayer->mUnknown992 == 0xFFFF) {
        fn_80233760(&pPlayer->mUnknown1024[0], values, 53);
        fn_80233760(&pPlayer->mUnknown1024[1], values, 53);
    } else {
        a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
        b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
        TMModelClone(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(4, 0, 0));
        TMModelClone(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(4, 0, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        fn_80233760(&pPlayer->mUnknown1024[0], values, 37);
        fn_80233760(&pPlayer->mUnknown1024[1], values, 37);
    }
    a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
    b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
    if (pPlayer->mUnknown992 != 0xFFFF) {
        fn_8015E908(pPlayer->mUnknown4970);
    }
    TMModelClone(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(5, 0, 0));
    TMModelClone(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(5, 0, 1));
    pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
    pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
    TMModelRemapMaterials(&pPlayer->mUnknown1024[0].mUnknown16, _PlyrRender_aPartTables);
    TMModelRemapMaterials(&pPlayer->mUnknown1024[1].mUnknown16, _PlyrRender_aPartTables);
    PlyrRenderBindPartTable(0);
    fn_8015F3FC(0);
    if (_PlyrRender_BlendModel.mUnknown0 == 0) {
        TMModelClone(&_PlyrRender_BlendModel, &pPlayer->mUnknown1024[0].mUnknown16);
        TMModelAllocChannels(&_PlyrRender_BlendModel);
        TMBufferNew(_PlyrRender_aBlendBuffer, 0x7404, 0x20);
    }
    fn_8015E9F4(pPlayer->mUnknown4970, &pPlayer->mUnknown996);
    fn_8015EB4C(pPlayer->mUnknown4970, pPlayer->mUnknown1004);
    fn_8015EC74(pPlayer->mUnknown4970, pPlayer->mUnknown1008);
    PlyrRenderUnbindPartTable();
}

void PlyrHeadFreeModel(Object_8003DEC4 *pPlayer)
{
    fn_80233728(&pPlayer->mUnknown1024[0]);
    fn_80233728(&pPlayer->mUnknown1024[1]);
}

void PlyrRenderBindParts(Object_8003DEC4 *pPlayer, PlyrRenderSlot_t *pSlot)
{
    unsigned int i;

    fn_80234A94(&pPlayer->mUnknown1164[0], pSlot->mpUnknown12);
    fn_80234CA4(&pPlayer->mUnknown1164[0], &pPlayer->mUnknown4064[0]);
    fn_80234AD8(&pPlayer->mUnknown1164[4], pSlot->mpUnknown16);
    fn_80234CA4(&pPlayer->mUnknown1164[4], &pPlayer->mUnknown4064[1]);
    fn_80234AD8(&pPlayer->mUnknown1164[5], pSlot->mpUnknown16);
    fn_80234CA4(&pPlayer->mUnknown1164[5], &pPlayer->mUnknown4064[1]);
    if ((pPlayer->mUnknown20 & 0x10) && pSlot->mUnknown8 == 0) {
        if (!(pPlayer->mUnknown20 & 8) && pPlayer->mUnknown820) {
            if (PlyrObjsFindPlayer((Block_80170E64 *)pPlayer)->mpState->mId == 0x32) {
                pPlayer->mUnknown820[pPlayer->mUnknown4972 + 2] = -1.0f;
            } else if (pPlayer->mUnknown20 & 0x40000) {
                float f = pPlayer->mUnknown820[1];

                pPlayer->mUnknown820[1] = 0.0f;
                pPlayer->mUnknown820[pPlayer->mUnknown4972 + 2] = f + -1.0f;
            }
        }
        fn_80234CAC(&pPlayer->mUnknown1164[4], &pPlayer->mUnknown816);
        fn_80234A14(&pPlayer->mUnknown1164[4], 1);
        fn_80234CAC(&pPlayer->mUnknown1164[5], &pPlayer->mUnknown816);
        fn_80234A14(&pPlayer->mUnknown1164[5], 1);
    } else {
        fn_80234CAC(&pPlayer->mUnknown1164[4], 0);
        fn_80234CAC(&pPlayer->mUnknown1164[5], 0);
    }
    fn_80234A94(&pPlayer->mUnknown1164[6], pSlot->mpUnknown20);
    fn_80234CA4(&pPlayer->mUnknown1164[6], &pPlayer->mUnknown4064[2]);
    fn_80234A94(&pPlayer->mUnknown1164[7], pSlot->mpUnknown24);
    fn_80234A94(&pPlayer->mUnknown1164[8], pSlot->mpUnknown24);
    fn_80234CA4(&pPlayer->mUnknown1164[7], &pPlayer->mUnknown4064[3]);
    fn_80234CA4(&pPlayer->mUnknown1164[8], &pPlayer->mUnknown4064[3]);
    fn_80234A94(&pPlayer->mUnknown1164[9], pSlot->mpUnknown28);
    fn_80234CA4(&pPlayer->mUnknown1164[9], &pPlayer->mUnknown4064[4]);
    fn_80234A94(&pPlayer->mUnknown1164[11], pSlot->mpUnknown32);
    fn_80234CA4(&pPlayer->mUnknown1164[11], &pPlayer->mUnknown4064[5]);
    fn_80234A94(&pPlayer->mUnknown1164[1], pSlot->mpUnknown12);
    fn_80234CA4(&pPlayer->mUnknown1164[1], &pPlayer->mUnknown4064[0]);
    for (i = 0; i < 2; i++) {
        int part;
        int key;

        if (i == 0) {
            part = 2;
            key = 12;
        } else {
            part = 3;
            key = 13;
        }
        if (pPlayer->mUnknown116[i].mUnknown0 == 1 && pSlot->mUnknown8 == 0) {
            // FAKEMATCH: compiled-out assert on the hand model; its second use of i * 4 lets loop.c keep a separate index
            FX_ASSERT(pSlot->mpUnknown36[i] != 0);
            fn_80234A94(&pPlayer->mUnknown1164[part], pSlot->mpUnknown36[i]);
            fn_80234CA4(&pPlayer->mUnknown1164[part], &pPlayer->mUnknown4136[i]);
            fn_80233CBC(&pPlayer->mUnknown1164[part].mUnknown20, key, 0);
        } else {
            fn_80234A94(&pPlayer->mUnknown1164[part], pSlot->mpUnknown12);
            fn_80234CA4(&pPlayer->mUnknown1164[part], &pPlayer->mUnknown4064[0]);
            if (pSlot->mUnknown8 <= 1) {
                fn_80233CBC(&pPlayer->mUnknown1164[part].mUnknown20, key, fn_800ADDD8(pPlayer->mUnknown116, i));
            } else {
                fn_80233CBC(&pPlayer->mUnknown1164[part].mUnknown20, key, 0);
            }
        }
    }
}

void PlyrRenderInitLod(Object_8003DEC4 *pPlayer)
{
    pPlayer->mUnknown4216.mUnknown24 = pPlayer->mUnknown1020;
    pPlayer->mUnknown4216.mpUnknown32 = &pPlayer->mUnknown908;
    pPlayer->mUnknown4216.mpUnknown28 = _PlyrRender_aLodBounds;
    pPlayer->mUnknown4216.mUnknown36 = 0;
    fn_802341C4(&pPlayer->mUnknown4216);
}

void PlyrRenderUpdateLods(void)
{
    ModelLodBalance(0);
}

void PlyrRenderFreeLod(Object_8003DEC4 *pPlayer)
{
    fn_802341E8(&pPlayer->mUnknown4216);
}

void PlyrRenderAddSlot(Object_8003DEC4 *pPlayer)
{
    pPlayer->mUnknown1160 = &_PlyrRender_aSlots[_PlyrRender_uNumSlots];
    _PlyrRender_aSlots[_PlyrRender_uNumSlots].mpUnknown0 = pPlayer;
    _PlyrRender_uNumSlots++;
}

void PlyrRenderLoadTexMtx(int id, float sx, float sy, float tx, float ty)
{
    float m[4][4];

    m[0][0] = sx;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = tx;
    m[1][0] = 0.0f;
    m[1][1] = sy;
    m[1][2] = 0.0f;
    m[1][3] = ty;
    GXLoadTexMtxImm(m, id, 1);
}

void PlyrHeadGetEyeOffsets(Object_8003DEC4 *pPlayer, float *pA, float *pB)
{
    if (pPlayer->mUnknown20 & 0x80) {
        pB[0] = MathMapRangeClamped((pPlayer->mUnknown44.mUnknown48[87] << 8) * (360.0f / 16777216.0f), 45.619f, -0.03f,
                            -45.619f, 0.03f);
        pA[0] = MathMapRangeClamped((pPlayer->mUnknown44.mUnknown48[84] << 8) * (360.0f / 16777216.0f), 45.619f, -0.03f,
                            -45.619f, 0.03f);
        pB[1] = -MathMapRangeClamped((pPlayer->mUnknown44.mUnknown48[88] << 8) * (360.0f / 16777216.0f), 47.028f, -0.1f,
                             -47.028f, 0.1f);
        pA[1] = -MathMapRangeClamped((pPlayer->mUnknown44.mUnknown48[85] << 8) * (360.0f / 16777216.0f), 47.028f, -0.1f,
                             -47.028f, 0.1f);
    } else {
        pB[0] = 0.0f;
        pA[0] = 0.0f;
        pB[1] = 0.0f;
        pA[1] = 0.0f;
    }
}

void PlyrHeadOnModelLoaded(Object_8003DEC4 *pPlayer)
{
    _PlyrRender_bHeadModelReady = 1;
}

void PlyrRenderInit(int a, int b, int c, int d)
{
    fn_802341AC();
    _PlyrRender_uNumSlots = 0;
    TMModelReset(&_PlyrRender_BlendModel);
    PlyrRenderLoadShadowTexture();
    memset(_PlyrRender_aJointFlags, 0, sizeof(_PlyrRender_aJointFlags));
    _PlyrRender_aJointFlags[15] = 1;
    _PlyrRender_aJointFlags[21] = 1;
}

void PlyrRenderNewFrame(void)
{
    _PlyrRender_bLodsUpdated = 0;
}

void PlyrRenderShutdown(void)
{
    fn_802341B8();
    TMModelFreeChannels(&_PlyrRender_BlendModel);
    _PlyrRender_BlendModel.mUnknown0 = 0;
    TMBufferDelete(_PlyrRender_aBlendBuffer);
    PlyrRenderUnloadShadowTexture();
    if (_PlyrRender_pViewport) {
        VptRemoveCallback(_PlyrRender_pViewport, PlyrRenderVptCallback);
        _PlyrRender_pViewport = 0;
    }
}

void PlyrRenderInitPlayer(Object_8003DEC4 *pPlayer, Creation_8003D378 *pInit)
{
    PlyrModelData_t *pModel;
    unsigned int i;

    pPlayer->mUnknown984 = 0;
    pPlayer->mUnknown988 = 0;
    pPlayer->mUnknown4968 = pInit->mUnknown57;
    pPlayer->mUnknown4969 = pInit->mUnknown58;
    pPlayer->mUnknown1016 = pInit->mUnknown34;
    pPlayer->mUnknown992 = pInit->mUnknown1C;
    pPlayer->mUnknown996 = pInit->mUnknown20.mUnknown0;
    pPlayer->mUnknown1000 = pInit->mUnknown20.mUnknown4;
    pPlayer->mUnknown1008 = pInit->mUnknown2C;
    pPlayer->mUnknown1004 = pInit->mUnknown28;
    pPlayer->mUnknown1012 = pInit->mUnknown30;
    pPlayer->mUnknown4971 = pInit->mUnknown5A;
    pPlayer->mUnknown4970 = pInit->mUnknown59;
    pPlayer->mUnknown4972 = pInit->mUnknown5B;
    LightTrackerReset(&pPlayer->mUnknown4960);
    pPlayer->mUnknown4976 = pInit->mUnknown5C;
    strncpy(pPlayer->mUnknown4184, pInit->mUnknown38, 31);
    pPlayer->mUnknown1020 = fn_8015E440(0, pPlayer->mUnknown1016);
    pPlayer->mUnknown4060 = PlaTexCacheGetDescs(pInit->mUnknown5A);
    pModel = (PlyrModelData_t *)fn_8015E2FC(0, pPlayer->mUnknown1016, 0);
    PlyrHeadBuildModel(pPlayer, pInit->mInit.mUnknown04);
    PlyrRenderBindPartTable(0);
    fn_8015ED9C(pPlayer->mUnknown4970, pPlayer->mUnknown1012);
    PlyrRenderUnbindPartTable();
    pPlayer->mUnknown976 |= 0x10;
    PlyrRenderAddSlot(pPlayer);
    fn_80233BB8(&pPlayer->mUnknown4064[0], 0, 0);
    fn_80233BB8(&pPlayer->mUnknown4064[1], 0, 0);
    fn_80233BB8(&pPlayer->mUnknown4064[2], 0, 0);
    fn_80233BB8(&pPlayer->mUnknown4064[3], 0, 0);
    fn_80233BB8(&pPlayer->mUnknown4064[4], 0, 0);
    fn_80233BB8(&pPlayer->mUnknown4064[5], 0, 0);
    TMTexLibRegistryReset();
    TMTexLibRegister("platex", PlyrTexGetLib(pPlayer->mUnknown4971));
    fn_8023488C(pPlayer->mUnknown4044, 0x38);
    TMMaterialListSetMatDefs(pPlayer->mUnknown4044, pModel->mpUnknown24);
    fn_8023465C(pPlayer->mUnknown4044, pModel, PlaTexCacheGetDescs(pPlayer->mUnknown4971));
    fn_8023472C(pPlayer->mUnknown4044, 0x11, 1, &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[25],
                &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[25], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x12, 1, &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[25],
                &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[25], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x1A, 1, &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[26],
                &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[26], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x1B, 1, &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[26],
                &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[26], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x15, 1, &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[27],
                &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[27], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x16, 1, &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[27],
                &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[27], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x1E, 1, &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[28],
                &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[28], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x1F, 1, &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[28],
                &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[28], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x14, 1, &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[29],
                &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[29], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x1D, 1, &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[30],
                &PlaTexCacheGetDescs(pPlayer->mUnknown4971)[30], 0);
    PlyrTexApplyFilters(PlaTexCacheGetDescs(pPlayer->mUnknown4971), 0);
    TMTexLibRegistryReset();
    PlyrRenderInitPart(&pPlayer->mUnknown1164[0], 0, &pPlayer->mUnknown4064[0], pPlayer->mUnknown4044);
    PlyrHeadInitFacePart(&pPlayer->mUnknown1164[4], pPlayer->mUnknown4044, pPlayer);
    PlyrRenderInitPart(&pPlayer->mUnknown1164[5], 0, &pPlayer->mUnknown4064[1], pPlayer->mUnknown4044);
    PlyrRenderInitPart(&pPlayer->mUnknown1164[6], 0, &pPlayer->mUnknown4064[2], pPlayer->mUnknown4044);
    PlyrRenderInitPart(&pPlayer->mUnknown1164[7], 0, &pPlayer->mUnknown4064[3], pPlayer->mUnknown4044);
    PlyrRenderInitPart(&pPlayer->mUnknown1164[8], 0, &pPlayer->mUnknown4064[3], pPlayer->mUnknown4044);
    PlyrRenderInitPart(&pPlayer->mUnknown1164[9], 0, &pPlayer->mUnknown4064[4], pPlayer->mUnknown4044);
    PlyrRenderInitPart(&pPlayer->mUnknown1164[1], 0, &pPlayer->mUnknown4064[0], pPlayer->mUnknown4044);
    PlyrRenderInitPart(&pPlayer->mUnknown1164[11], 0, &pPlayer->mUnknown4064[5], pPlayer->mUnknown4044);
    for (i = 0; i < 2; i++) {
        fn_80233BB8(&pPlayer->mUnknown4136[i], 0, 0);
        PlyrRenderInitPart(&pPlayer->mUnknown1164[2 + i], 0, &pPlayer->mUnknown4136[i], pPlayer->mUnknown4044);
    }
    PlyrRenderInitLod(pPlayer);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 5, _PlyrRender_aPartParams[5]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 7, _PlyrRender_aPartParams[7]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 8, _PlyrRender_aPartParams[8]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 9, _PlyrRender_aPartParams[9]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 10, _PlyrRender_aPartParams[10]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 11, _PlyrRender_aPartParams[11]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 14, _PlyrRender_aPartParams[14]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 15, _PlyrRender_aPartParams[15]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 16, _PlyrRender_aPartParams[16]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 17, _PlyrRender_aPartParams[17]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 18, _PlyrRender_aPartParams[18]);
    fn_80233CBC(&pPlayer->mUnknown1164[4].mUnknown20, 1, _PlyrRender_aPartParams[1]);
    fn_80233CBC(&pPlayer->mUnknown1164[4].mUnknown20, 2, _PlyrRender_aPartParams[2]);
    fn_80233CBC(&pPlayer->mUnknown1164[4].mUnknown20, 3, _PlyrRender_aPartParams[3]);
    fn_80233CBC(&pPlayer->mUnknown1164[5].mUnknown20, 4, _PlyrRender_aPartParams[4]);
    fn_80233CBC(&pPlayer->mUnknown1164[6].mUnknown20, 0, _PlyrRender_aPartParams[0]);
    fn_80233CBC(&pPlayer->mUnknown1164[7].mUnknown20, 27, 0);
    fn_80233CBC(&pPlayer->mUnknown1164[9].mUnknown20, 28, 0);
    fn_80233CBC(&pPlayer->mUnknown1164[11].mUnknown20, 29, 0);
    fn_80233CBC(&pPlayer->mUnknown1164[11].mUnknown20, 30, 0);
}

void PlyrRenderDrawPlayer(Object_8003DEC4 *pPlayer)
{
    PlyrRenderSlot_t *pSlot = pPlayer->mUnknown1160;
    unsigned int flags;
    unsigned int lod;

    if (!_PlyrRender_bLodsUpdated) {
        PlyrRenderUpdateLods();
        _PlyrRender_bLodsUpdated = 1;
    }
    flags = PlyrRenderGetHideFlags(pPlayer);
    ConGetCurrentContext();
    VptGetMatrixStack();
    MatSetStack();
    lod = pPlayer->mUnknown4216.mUnknown0;
    if (pPlayer->mUnknown20 & 8) {
        lod = 0;
    } else if (pPlayer->mUnknown20 & 0x400) {
        lod = 0;
    }
    if (!(pPlayer->mUnknown20 & 8) && fn_800A2624()) {
        lod = 1;
    }
    if (pPlayer->mUnknown4216.mUnknown12 > _PlyrRender_fFarDistance) {
        flags |= 4;
    }
    if (lod <= 1) {
        pSlot->mpUnknown16 = &pPlayer->mUnknown1024[lod];
        if (lod == 0) {
            flags |= 8;
        }
    } else {
        pSlot->mpUnknown16 = 0;
    }
    if (pPlayer->mUnknown976 & 0x10) {
        PlyrModelDrawNameplate(pPlayer);
        pPlayer->mUnknown976 &= ~0x10;
    }
    pSlot->mpUnknown0 = pPlayer;
    pSlot->mpUnknown12 = fn_8015E2FC(0, pPlayer->mUnknown1016, lod);
    pSlot->mpUnknown20 = fn_8015E2FC(3, pPlayer->mUnknown4970, lod);
    pSlot->mpUnknown24 = fn_8015E2FC(7, pPlayer->mUnknown4970, lod);
    pSlot->mpUnknown28 = fn_8015E2FC(8, pPlayer->mUnknown4970, lod);
    pSlot->mpUnknown36[0] = fn_8015E2FC(1, pPlayer->mUnknown1016, 0);
    pSlot->mpUnknown36[1] = fn_8015E2FC(2, pPlayer->mUnknown1016, 0);
    pSlot->mpUnknown32 = fn_8015E2FC(9, pPlayer->mUnknown4970, 0);
    pSlot->mUnknown8 = lod;
    pSlot->mUnknown4 = flags;
    pSlot->mUnknown44 = (pPlayer->mUnknown20 >> 17) & 1;
    if (!(flags & 1)) {
        if ((pPlayer->mUnknown20 & 8) && !FEPlyrLoadIsShown(pPlayer)) {
            return;
        }
        if (_PlyrRender_bPendingPlayerCall == 1) {
            fn_800A3B58(PlyrObjsFindPlayer((Block_80170E64 *)pPlayer), 1, _PlyrRender_ucPendingPlayerArg);
            _PlyrRender_bPendingPlayerCall = 0;
        }
        PlyrRenderBindParts(pPlayer, pSlot);
        if (FEPlyrLoadIsActive()) {
            PlyrRenderVec3_t scale;

            FEPlyrLoadMarkDrawn(pPlayer);
            FEPlyrLoadGetScale(pPlayer, &scale.x);
            PlyrRenderPoseModel(pPlayer, &scale.x, pPlayer->mUnknown908, 0, 0, pSlot->mpUnknown12, pSlot->mpUnknown36,
                        pSlot->mUnknown8);
        } else {
            PlyrRenderPoseModel(pPlayer, 0, pPlayer->mUnknown908, 0, 0, pSlot->mpUnknown12, pSlot->mpUnknown36,
                        pSlot->mUnknown8);
        }
        PlyrRenderDrawModel(pPlayer, pSlot->mUnknown4);
        if (pPlayer->mUnknown20 & 0x20000) {
            int count = 2;

            if (fn_800B823C(0) > 1 || fn_800B823C(1) > 1) {
                count = 0;
            }
            pSlot->mUnknown8 = 1;
            pSlot->mpUnknown12 = fn_8015E2FC(0, pPlayer->mUnknown1016, 1);
            pSlot->mpUnknown20 = fn_8015E2FC(3, pPlayer->mUnknown4970, pSlot->mUnknown8);
            PlyrRenderBindParts(pPlayer, pSlot);
            PlyrRenderDrawAfterimages(pPlayer, pSlot, count);
        }
    } else {
        fn_800C2150(pPlayer, &pPlayer->mUnknown280, 0);
    }
}

void PlyrRenderFreePlayer(Object_8003DEC4 *pPlayer)
{
    unsigned int i;

    PlyrHeadFreeModel(pPlayer);
    fn_80234994(&pPlayer->mUnknown816);
    fn_802348AC(pPlayer->mUnknown4044);
    fn_80233BD8(&pPlayer->mUnknown4064[0]);
    fn_80233BD8(&pPlayer->mUnknown4064[1]);
    fn_80233BD8(&pPlayer->mUnknown4064[2]);
    fn_80233BD8(&pPlayer->mUnknown4064[3]);
    fn_80233BD8(&pPlayer->mUnknown4064[4]);
    fn_80233BD8(&pPlayer->mUnknown4064[5]);
    for (i = 0; i < 2; i++) {
        fn_80233BD8(&pPlayer->mUnknown4136[i]);
    }
    for (i = 0; i < 12; i++) {
        fn_80234A90(&pPlayer->mUnknown1164[i]);
    }
    PlyrRenderFreeLod(pPlayer);
}

void PlyrRenderDrawShadows(void)
{
    unsigned int i;
    int old;
    float m[4][4];

    TMRenderReset();
    i = 0;
    old = LLFogEnable(1);
    GXSetCullMode(0);
    GXSetBlendMode(1, 4, 5, 5);
    GXSetZCompLoc(0);
    GXSetZMode(1, 3, 0);
    TMRenderSetZRange(0.01f, 0.01f);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    TMRenderBindTexture(0, _PlyrRender_iShadowTexture, _PlyrRender_iShadowClut);
    MatStore(m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    for (; i < PlyrObjsGetCount(); i++) {
        Object_8003DEC4 *pPlayer = PlyrObjsGet(i);
        Projection_8003BA10 *pShadow = &pPlayer->mUnknown4256;

        if (pShadow->mUnknown673) {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
            int j;

            GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
            r = pShadow->mColor[0] * 255.0f;
            g = pShadow->mColor[1] * 255.0f;
            b = pShadow->mColor[2] * 255.0f;
            a = pShadow->mColor[3] * 255.0f;
            for (j = 0; j < 4; j++) {
                GXPosition3f32(pShadow->mPoints[j][0], pShadow->mPoints[j][1], pShadow->mPoints[j][2]);
                GXColor4u8(r, g, b, a);
                GXTexCoord2f32(pShadow->mPairs[j].mX, pShadow->mPairs[j].mY);
            }
        }
    }
    TMRenderSetZRange(0.0f, 1.0f);
    GXSetZMode(1, 3, 1);
    LLFogEnable(old);
}

void PlyrRenderDrawClippedShadows(void)
{
    unsigned int i;
    int old;
    float m[4][4];

    TMRenderReset();
    i = 0;
    old = LLFogEnable(1);
    GXSetCullMode(0);
    GXSetBlendMode(1, 4, 5, 5);
    GXSetZCompLoc(0);
    GXSetZMode(1, 3, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    TMRenderBindTexture(0, _PlyrRender_iShadowTexture, _PlyrRender_iShadowClut);
    MatStore(m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    for (; i < PlyrObjsGetCount(); i++) {
        Projection_8003BA10 *pShadow = &PlyrObjsGet(i)->mUnknown4256;
        unsigned char k;

        if (!pShadow->mUnknown673) {
            continue;
        }
        for (k = 0; k < pShadow->mUnknown672; k++) {
            Clip_8003BFCC *pClip = &pShadow->mRecords[k];
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
            int j;

            GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, pClip->mCount);
            r = pShadow->mColor[0] * 255.0f;
            g = pShadow->mColor[1] * 255.0f;
            b = pShadow->mColor[2] * 255.0f;
            a = pShadow->mColor[3] * 255.0f;
            for (j = 0; j < pClip->mCount; j++) {
                GXPosition3f32(pClip->mPoints[j][0], pClip->mPoints[j][1], pClip->mPoints[j][2]);
                GXColor4u8(r, g, b, a);
                GXTexCoord2f32(pClip->mPairs[j].mX, pClip->mPairs[j].mY);
            }
        }
    }
    TMRenderSetZRange(0.0f, 1.0f);
    GXSetZMode(1, 3, 1);
    LLFogEnable(old);
}

void PlyrRenderDrawTrails(void)
{
    unsigned int i;

    for (i = 0; i < PlyrObjsGetCount(); i++) {
        Object_8003DEC4 *pPlayer = PlyrObjsGet(i);

        if (pPlayer->mUnknown1160->mUnknown4 & 1) {
            continue;
        }
        if ((pPlayer->mUnknown20 & 8) && !FEPlyrLoadIsShown(pPlayer)) {
            continue;
        }
        if (pPlayer->mUnknown20 & 0x10000) {
            ParticleTrailDraw(&pPlayer->mUnknown5188);
        }
    }
}

void PlyrRenderSetViewport(Viewport_t *pObject)
{
    _PlyrRender_pViewport = pObject;
    VptSetCallback(pObject, 2, PlyrRenderVptCallback, 0);
}

void PlyrRenderSetHideFlagged(unsigned char enable)
{
    _PlyrRender_bHideFlagged = enable;
}

void PlyrRenderBindPartTable(int index)
{
    fn_802345BC(&_PlyrRender_aPartTables[index]);
}

void PlyrRenderUnbindPartTable(void)
{
    fn_802345BC(0);
}

void PlyrHeadSetModel(Object_8003DEC4 *pPlayer, int id, void (*pCallback)(Object_8003DEC4 *pPlayer))
{
    _PlyrRender_pHeadModelCallback = pCallback;
    _PlyrRender_bHeadModelReady = 0;
    _PlyrRender_pHeadModelPlayer = pPlayer;
    pPlayer->mUnknown992 = id;
    fn_8015F82C(id, pPlayer, PlyrHeadOnModelLoaded);
}

static void _PlyrHeadSetModelNow(Object_8003DEC4 *pPlayer, int id)
{
    short values[53];

    memset(values, 0, sizeof(values));
    pPlayer->mUnknown992 = id;
    if (id == 0xFFFF) {
        int a;
        int b;
        int i;

        PlyrModelAttachLod(fn_8015E2FC(6, 0, 0), fn_8015E2FC(5, 0, 0));
        PlyrModelAttachLod(fn_8015E2FC(6, 0, 1), fn_8015E2FC(5, 0, 1));
        for (i = 0; i < 53; i++) {
            values[i] = pPlayer->mUnknown4976.mValues[i] * 4096.0f;
        }
        values[pPlayer->mUnknown4972 + 1] = 0x1000;
        if (PlayerLookHidesHead(pPlayer->mUnknown4971)) {
            values[6] = 0x1000;
        }
        a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
        b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
        TMModelClone(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(6, pPlayer->mUnknown4970, 0));
        TMModelClone(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(6, pPlayer->mUnknown4970, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        fn_80233760(&pPlayer->mUnknown1024[0], values, 53);
        fn_80233760(&pPlayer->mUnknown1024[1], values, 53);
        a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
        b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
        TMModelClone(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(5, 0, 0));
        TMModelClone(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(5, 0, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        TMModelRemapMaterials(&pPlayer->mUnknown1024[0].mUnknown16, _PlyrRender_aPartTables);
        TMModelRemapMaterials(&pPlayer->mUnknown1024[1].mUnknown16, _PlyrRender_aPartTables);
        PlyrRenderBindPartTable(0);
        PlyrRenderUnbindPartTable();
    } else {
        PlyrModelAttachLod(fn_8015E2FC(4, 0, 0), fn_8015E2FC(5, 0, 0));
        PlyrModelAttachLod(fn_8015E2FC(4, 0, 1), fn_8015E2FC(5, 0, 1));
        int a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
        int b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
        TMModelClone(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(4, pPlayer->mUnknown4970, 0));
        TMModelClone(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(4, pPlayer->mUnknown4970, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        values[1] = 0x1000;
        values[pPlayer->mUnknown4972 + 2] = 0x1000;
        if (PlayerLookHidesHead(pPlayer->mUnknown4971)) {
            values[7] = 0x1000;
        }
        fn_80233760(&pPlayer->mUnknown1024[0], values, 37);
        fn_80233760(&pPlayer->mUnknown1024[1], values, 37);
        fn_8015E908(pPlayer->mUnknown1016);
        TMModelClone(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(5, 0, 0));
        TMModelClone(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(5, 0, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        TMModelRemapMaterials(&pPlayer->mUnknown1024[0].mUnknown16, _PlyrRender_aPartTables);
        TMModelRemapMaterials(&pPlayer->mUnknown1024[1].mUnknown16, _PlyrRender_aPartTables);
        PlyrRenderBindPartTable(0);
        fn_8015F3FC(0);
        PlyrRenderUnbindPartTable();
    }
}

void PlyrHeadProcessModel(void)
{
    Object_8003DEC4 *pPlayer;
    short values[53];

    if (!_PlyrRender_pHeadModelPlayer || !_PlyrRender_bHeadModelReady) {
        return;
    }
    memset(values, 0, sizeof(values));
    pPlayer = _PlyrRender_pHeadModelPlayer;
    if (pPlayer->mUnknown992 == 0xFFFF) {
        int a;
        int b;
        int i;

        PlyrModelAttachLod(fn_8015E2FC(6, 0, 0), fn_8015E2FC(5, 0, 0));
        PlyrModelAttachLod(fn_8015E2FC(6, 0, 1), fn_8015E2FC(5, 0, 1));
        for (i = 0; i < 53; i++) {
            values[i] = pPlayer->mUnknown4976.mValues[i] * 4096.0f;
        }
        values[pPlayer->mUnknown4972 + 1] = 0x1000;
        if (PlayerLookHidesHead(pPlayer->mUnknown4971)) {
            values[6] = 0x1000;
        }
        a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
        b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
        TMModelClone(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(6, pPlayer->mUnknown4970, 0));
        TMModelClone(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(6, pPlayer->mUnknown4970, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        fn_80233760(&pPlayer->mUnknown1024[0], values, 53);
        fn_80233760(&pPlayer->mUnknown1024[1], values, 53);
        a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
        b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
        TMModelClone(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(5, 0, 0));
        TMModelClone(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(5, 0, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        TMModelRemapMaterials(&pPlayer->mUnknown1024[0].mUnknown16, _PlyrRender_aPartTables);
        TMModelRemapMaterials(&pPlayer->mUnknown1024[1].mUnknown16, _PlyrRender_aPartTables);
        PlyrRenderBindPartTable(0);
        PlyrRenderUnbindPartTable();
    } else {
        PlyrModelAttachLod(fn_8015E2FC(4, 0, 0), fn_8015E2FC(5, 0, 0));
        PlyrModelAttachLod(fn_8015E2FC(4, 0, 1), fn_8015E2FC(5, 0, 1));
        int a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
        int b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
        TMModelClone(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(4, pPlayer->mUnknown4970, 0));
        TMModelClone(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(4, pPlayer->mUnknown4970, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        values[1] = 0x1000;
        values[pPlayer->mUnknown4972 + 2] = 0x1000;
        if (PlayerLookHidesHead(pPlayer->mUnknown4971)) {
            values[7] = 0x1000;
        }
        fn_80233760(&pPlayer->mUnknown1024[0], values, 37);
        fn_80233760(&pPlayer->mUnknown1024[1], values, 37);
        fn_8015E908(pPlayer->mUnknown1016);
        TMModelClone(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(5, 0, 0));
        TMModelClone(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(5, 0, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        TMModelRemapMaterials(&pPlayer->mUnknown1024[0].mUnknown16, _PlyrRender_aPartTables);
        TMModelRemapMaterials(&pPlayer->mUnknown1024[1].mUnknown16, _PlyrRender_aPartTables);
        PlyrRenderBindPartTable(0);
        fn_8015F3FC(0);
        PlyrRenderUnbindPartTable();
    }
    _PlyrRender_pHeadModelCallback(pPlayer);
    _PlyrRender_pHeadModelCallback = 0;
    _PlyrRender_pHeadModelPlayer = 0;
    _PlyrRender_bHeadModelReady = 0;
}
}
