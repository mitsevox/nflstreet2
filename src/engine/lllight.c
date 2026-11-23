/* Hardware lights for the 3D scene: converts a scene's light list into GX
   light objects and colours, keeps the numbered light sets with their ambient
   colours, and loads a set into the GX hardware before models are drawn. */

#include "engine/SyncStateGroup.h"
#include "engine/EvMonDesc.h"
#include "engine/EvMonAddListener.h"
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/viewport.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/SyncStateRegister.h"
#include "game/Object_80235588.h"
#include "engine/list.h"
#include "engine/llmemory.h"
#include "engine/dslist.h"
#include "engine/lllight.h"

typedef struct LLLightSet_t {
    unsigned int mUnknown0;
    GXColor mUnknown4;
    GXLightObj mUnknown8[4];
} LLLightSet_t;

typedef struct LLLightState_t {
    LLLightScene_t *mpUnknown0;
    GXLightObj mUnknown4[4];
    unsigned int mUnknown260[4];
    LLLightSet_t mUnknown276[16];
} LLLightState_t;

/* The longest shear a projector's direction matrix may have. */
static float _LLLight_fMaxShear = 1.5f;

static int _LLLight_iUnused0 = 0;

/* The light set loaded into the hardware last, or 0 once the sets are rebuilt. */
static LLLightSet_t *_LLLight_pCurrentSet = 0;

static int _LLLight_iUnused1 = 0;

/* The GX light mask of the current set. */
static int _LLLight_iCurrentMask;

/* The scene, its projector light objects and colours, and the sixteen light sets. */
static LLLightState_t _LLLight_State;
extern float Vec2Magnitude(float *p);
extern void Vec2ScaleLength(float *pOut, float *p, float length);
extern void fn_801CFC14(int angle, float *pFirst, float *pSecond);
LLLight_t *_LLLightGetSceneLight(LLLightScene_t *pScene, int index);
void _LLLightUpdateProjectors(LLLightScene_t *pScene, GXLightObj *pLights, unsigned int *pColors);
int _LLLightLoadSetScaled(LLLightSet_t *pSet, float r, float g, float b);
void _LLLightBuildSet(LLLightScene_t *pScene, LLLightSetRef_t *pRefs, LLLightSet_t *pSet);
void _LLLightClearCurrentSet(void);

void _LLLightProjectorDirMatrix(float m[4][4], float *pDir)
{
    float shear[2];

    m[0][0] = 1.0f;
    m[0][1] = 0.0f;
    m[0][2] = -pDir[0] / pDir[2];
    m[3][0] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 1.0f;
    m[1][2] = -pDir[1] / pDir[2];
    m[3][1] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 0.0f;
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    shear[0] = m[0][2];
    shear[1] = m[1][2];
    if (!(Vec2Magnitude(shear) <= _LLLight_fMaxShear)) {
        Vec2ScaleLength(shear, shear, _LLLight_fMaxShear);
        m[0][2] = shear[0];
        m[1][2] = shear[1];
    }
}

void _LLLightProjectorAngleMatrix(float m[4][4], int angle, float scale)
{
    float first;
    float second;

    fn_801CFC14(angle, &first, &second);
    m[0][0] = 1.0f;
    m[1][0] = 0.0f;
    m[2][0] = 0.0f;
    m[3][0] = 0.0f;
    m[0][1] = 0.0f;
    m[1][1] = 1.0f;
    m[2][1] = 0.0f;
    m[3][1] = 0.0f;
    m[0][2] = second * scale;
    m[1][2] = first * scale;
    m[2][2] = 0.0f;
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

unsigned int _LLLightPackColor(float *pColor, float scale)
{
    unsigned int color;

    color = (unsigned int)(pColor[0] * scale);
    color |= (unsigned int)(pColor[1] * scale) << 8;
    color |= (unsigned int)(pColor[2] * scale) << 16;
    color |= (unsigned int)(pColor[3] * scale) << 24;
    return color;
}

void *_LLLightGetSetRefs(LLLightScene_t *pScene, int index)
{
    return pScene->mpUnknown12 + index * 100;
}

void _LLLightUpdateLights(LLLightScene_t *pScene)
{
    unsigned int i;
    LLLight_t *pLight;

    for (i = 0; i < pScene->mUnknown0; i++) {
        pLight = _LLLightGetSceneLight(pScene, i);
        if (pLight->mpUnknown32 != 0) {
            pLight->mpUnknown32(pLight);
        }
        Vec3Normalize(pLight->mUnknown4, pLight->mUnknown4);
        switch (pLight->mUnknown0) {
        case 0:
        case 1:
            break;
        case 2:
        case 4:
            Vec3Mat33Mul(pLight->mUnknown36, pLight->mUnknown4);
            break;
        case 3:
            pLight->mUnknown36[0] = pLight->mUnknown4[0];
            pLight->mUnknown36[1] = pLight->mUnknown4[1];
            pLight->mUnknown36[2] = pLight->mUnknown4[2];
            break;
        }
    }
}

void _LLLightUpdateProjectors(LLLightScene_t *pScene, GXLightObj *pLights, unsigned int *pColors)
{
    unsigned int i;
    LLLightProjector_t *pProjector;

    for (i = 0; i < pScene->mUnknown16; i++) {
        pProjector = &pScene->mUnknown20[i];
        switch (pProjector->mUnknown0) {
        case 0:
            break;
        case 1:
            _LLLightProjectorDirMatrix((float (*)[4])&pLights[i], _LLLightGetSceneLight(pScene, pProjector->mUnknown20)->mUnknown4);
            break;
        case 2:
            _LLLightProjectorAngleMatrix((float (*)[4])&pLights[i], (int)(pProjector->mUnknown24 * 46603.378f), pProjector->mUnknown28);
            break;
        }
        pColors[i] = _LLLightPackColor(pProjector->mUnknown4, 128.0f);
    }
}

void _LLLightBuildSets(LLLightScene_t *pScene, LLLightSet_t *pSets)
{
    unsigned int i;

    for (i = 0; i < pScene->mUnknown8; i++) {
        _LLLightBuildSet(pScene, _LLLightGetSetRefs(pScene, i), &pSets[i]);
    }
}

LLLight_t *_LLLightGetSceneLight(LLLightScene_t *pScene, int index)
{
    return &pScene->mpUnknown4[index];
}

void LLLightUpdate(Viewport_t *pObject)
{
    if (_LLLight_State.mpUnknown0 != 0) {
        MatSetStack(VptGetMatrixStack());
        _LLLightUpdateLights(_LLLight_State.mpUnknown0);
        _LLLightBuildSets(_LLLight_State.mpUnknown0, _LLLight_State.mUnknown276);
        _LLLightUpdateProjectors(_LLLight_State.mpUnknown0, _LLLight_State.mUnknown4, _LLLight_State.mUnknown260);
        _LLLightClearCurrentSet();
    }
}

void LLLightSetScene(LLLightScene_t *pScene)
{
    _LLLight_State.mpUnknown0 = pScene;
    LLLightUpdate(0);
}

LLLightSet_t *LLLightGetSet(int index)
{
    return &_LLLight_State.mUnknown276[index];
}

GXLightObj *LLLightGetProjectorMatrix(int index)
{
    return &_LLLight_State.mUnknown4[index];
}

unsigned int LLLightGetProjectorColor(int index)
{
    return _LLLight_State.mUnknown260[index];
}

void LLLightAttachViewport(Viewport_t *pObject)
{
    VptSetCallback(pObject, 1, LLLightUpdate, 0);
}

void LLLightDetachViewport(Viewport_t *pObject)
{
    VptRemoveCallback(pObject, LLLightUpdate);
}

void LLLightGetProjectorDir(int index, float *pOut)
{
    GXLightObj *pLight = LLLightGetProjectorMatrix(index);
    float v[3];
    float w[3];

    MatSetStack(0);
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 1.0f;
    MatPush();
    MatLoad((float *)pLight);
    Vec3Mat33Mul(w, v);
    pOut[0] = v[0] - w[0];
    pOut[1] = v[1] - w[1];
    pOut[2] = v[2] - w[2];
    Vec3Normalize(pOut, pOut);
    MatPop();
}

GXColor _LLLightFloatToColor(float *pColor)
{
    unsigned char rgba[4];

    rgba[0] = (unsigned int)pColor[0];
    rgba[1] = (unsigned int)pColor[1];
    rgba[2] = (unsigned int)pColor[2];
    rgba[3] = (unsigned int)pColor[3];
    return *(GXColor *)rgba;
}

int _LLLightLoadSetScaled(LLLightSet_t *pSet, float r, float g, float b)
{
    int mask = 0;
    unsigned int i;
    GXLightObj light;
    GXColor color;
    unsigned int rValue;
    unsigned int gValue;
    unsigned int bValue;

    for (i = 0; i < pSet->mUnknown0; i++) {
        if (r != 1.0f || g != 1.0f || b != 1.0f) {
            /* FAKEMATCH: Keep the equivalent index-first address expression for the target add order. */
            light = *(i + pSet->mUnknown8);
            GXGetLightColor(&light, &color);
            rValue = color.r * r;
            if (rValue > 255) {
                rValue = 255;
            }
            color.r = rValue;
            gValue = color.g * g;
            if (gValue > 255) {
                gValue = 255;
            }
            color.g = gValue;
            bValue = color.b * b;
            if (bValue > 255) {
                bValue = 255;
            }
            color.b = bValue;
            GXInitLightColor(&light, color);
            GXLoadLightObjImm(&light, (GXLightID)(1 << i));
        } else {
            GXLoadLightObjImm(&pSet->mUnknown8[i], (GXLightID)(1 << i));
        }
        mask |= 1 << i;
    }
    GXSetChanAmbColor(GX_COLOR0A0, pSet->mUnknown4);
    return mask;
}

void _LLLightBuildSet(LLLightScene_t *pScene, LLLightSetRef_t *pRefs, LLLightSet_t *pSet)
{
    unsigned int i;
    LLLightSetRef_t *pRef;
    LLLight_t *pLight;
    float scaled[4];
    GXColor color;

    pSet->mUnknown0 = 0;
    pSet->mUnknown4.r = 0;
    pSet->mUnknown4.g = 0;
    pSet->mUnknown4.b = 0;
    pSet->mUnknown4.a = 0;
    for (i = 0; i < 5; i++) {
        pRef = &pRefs[i];
        pLight = _LLLightGetSceneLight(pScene, pRef->mUnknown0);
        scaled[0] = pLight->mUnknown16[0] * pRef->mUnknown4[0] * pScene->mUnknown148[0];
        scaled[1] = pLight->mUnknown16[1] * pRef->mUnknown4[1] * pScene->mUnknown148[1];
        scaled[2] = pLight->mUnknown16[2] * pRef->mUnknown4[2] * pScene->mUnknown148[2];
        scaled[3] = pLight->mUnknown16[3] * pRef->mUnknown4[3] * pScene->mUnknown148[3];
        color = _LLLightFloatToColor(scaled);
        switch (pLight->mUnknown0) {
        case 1:
            pSet->mUnknown4 = color;
            break;
        case 2:
        case 3:
            if (pSet->mUnknown0 < 4) {
                GXLightObj *pObj = &pSet->mUnknown8[pSet->mUnknown0++];
                Vec3_801DE1E0 pos;
                Vec3_801DE1E0 dir;

                pos.x = pLight->mUnknown36[0] * 10000.0f;
                pos.y = pLight->mUnknown36[1] * 10000.0f;
                pos.z = pLight->mUnknown36[2] * 10000.0f;
                dir.x = -pLight->mUnknown36[0];
                dir.y = -pLight->mUnknown36[1];
                dir.z = -pLight->mUnknown36[2];
                GXInitLightPos(pObj, pos.x, pos.y, pos.z);
                GXInitLightDir(pObj, dir.x, dir.y, dir.z);
                GXInitLightSpot(pObj, 0.0f, GX_SP_OFF);
                GXInitLightDistAttn(pObj, 0.0f, 0.0f, GX_DA_OFF);
                GXInitLightColor(pObj, color);
            }
            break;
        case 4:
            if (pSet->mUnknown0 < 4) {
                GXLightObj *pObj = &pSet->mUnknown8[pSet->mUnknown0++];
                Vec3_801DE1E0 dir;

                dir.x = -pLight->mUnknown36[0];
                dir.y = -pLight->mUnknown36[1];
                dir.z = -pLight->mUnknown36[2];
                GXInitLightColor(pObj, color);
                GXInitSpecularDir(pObj, dir.x, dir.y, dir.z);
                GXInitLightAttn(pObj, 0.0f, 0.0f, 1.0f, 25.0f, 0.0f, -24.0f);
            }
            break;
        }
    }
}

int LLLightLoadSet(int index)
{
    LLLightSet_t *pSet = LLLightGetSet(index);
    int mask = _LLLightLoadSetScaled(pSet, 1.0f, 1.0f, 1.0f);

    _LLLight_pCurrentSet = pSet;
    _LLLight_iCurrentMask = mask;
    return mask;
}

int LLLightLoadSetTinted(int index, float r, float g, float b)
{
    LLLightSet_t *pSet = LLLightGetSet(index);
    int mask = _LLLightLoadSetScaled(pSet, r, g, b);

    _LLLight_pCurrentSet = pSet;
    _LLLight_iCurrentMask = mask;
    return mask;
}

void _LLLightClearCurrentSet(void)
{
    _LLLight_pCurrentSet = 0;
}

void LLLightLoadDirectional(int index, float *pColor, float *pDir)
{
    GXLightObj light;
    Vec3_801DE1E0 pos;
    Vec3_801DE1E0 dir;
    unsigned char rgb[4];

    { float c; if (!(pColor[0] < 0.0f)) { c = pColor[0]; if (!(c <= 255.0f)) c = 255.0f; } else c = 0.0f; pColor[0] = c; }
    { float c; if (!(pColor[1] < 0.0f)) { c = pColor[1]; if (!(c <= 255.0f)) c = 255.0f; } else c = 0.0f; pColor[1] = c; }
    { float c; if (!(pColor[2] < 0.0f)) { c = pColor[2]; if (!(c <= 255.0f)) c = 255.0f; } else c = 0.0f; pColor[2] = c; }
    rgb[0] = (int)pColor[0];
    rgb[1] = (int)pColor[1];
    rgb[2] = (int)pColor[2];
    pos.x = pDir[0] * 10000.0f;
    pos.y = pDir[1] * 10000.0f;
    pos.z = pDir[2] * 10000.0f;
    dir.x = -pDir[0];
    dir.y = -pDir[1];
    dir.z = -pDir[2];
    GXInitLightPos(&light, pos.x, pos.y, pos.z);
    GXInitLightDir(&light, dir.x, dir.y, dir.z);
    GXInitLightSpot(&light, 0.0f, GX_SP_OFF);
    GXInitLightDistAttn(&light, 0.0f, 0.0f, GX_DA_OFF);
    GXInitLightColor(&light, *(GXColor *)rgb);
    GXLoadLightObjImm(&light, (GXLightID)(1 << index));
}
