/* Hardware lights for the 3D scene: converts a scene's light list into GX
   light objects and colours, keeps the numbered light sets with their ambient
   colours, and loads a set into the GX hardware before models are drawn. */

#include "engine/Object_80237EE8.h"
#include "engine/Desc_80238424.h"
#include "engine/fn_80238680.h"
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/viewport.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80238174.h"
#include "game/Object_80235588.h"
#include "engine/list.h"
#include "engine/llmemory.h"
#include "engine/dslist.h"

typedef struct Light_802362C4 {
    unsigned int mUnknown0;
    float mUnknown4[3];
    float mUnknown16[4];
    void (*mpUnknown32)(struct Light_802362C4 *pLight);
    float mUnknown36[3];
} Light_802362C4;

/* 32-byte entry at +0x14 of Scene_8023609C, read by 0x80236164. */
typedef struct Projector_80236164 {
    unsigned int mUnknown0;
    float mUnknown4[4];
    int mUnknown20;
    float mUnknown24;
    float mUnknown28;
} Projector_80236164;

typedef struct Scene_8023609C {
    unsigned int mUnknown0;
    Light_802362C4 *mpUnknown4;
    unsigned int mUnknown8;
    char *mpUnknown12;
    unsigned int mUnknown16;
    Projector_80236164 mUnknown20[4];
    float mUnknown148[4];
} Scene_8023609C;

/* 20-byte record of the 100-byte block returned by 0x8023608C, read by 0x802368D0. */
typedef struct LightRef_802368D0 {
    int mUnknown0;
    float mUnknown4[4];
} LightRef_802368D0;

typedef struct LightSet_80236368 {
    unsigned int mUnknown0;
    GXColor mUnknown4;
    GXLightObj mUnknown8[4];
} LightSet_80236368;

typedef struct Lights_803A2868 {
    Scene_8023609C *mpUnknown0;
    GXLightObj mUnknown4[4];
    unsigned int mUnknown260[4];
    LightSet_80236368 mUnknown276[1];
} Lights_803A2868;

extern Lights_803A2868 lbl_803A2868;
extern LightSet_80236368 *lbl_803EC108;
extern int lbl_803ED028;
extern float lbl_803EC100;
extern float fn_802270A4(float *p);
extern void fn_8022728C(float *pOut, float *p, float length);
extern void fn_801CFC14(int angle, float *pFirst, float *pSecond);
Light_802362C4 *fn_802362C4(Scene_8023609C *pScene, int index);
void fn_80236164(Scene_8023609C *pScene, GXLightObj *pLights, unsigned int *pColors);
int fn_802365E8(LightSet_80236368 *pSet, float r, float g, float b);
void fn_802368D0(Scene_8023609C *pScene, LightRef_802368D0 *pRefs, LightSet_80236368 *pSet);
void fn_80236C04(void);

void fn_80235DD8(float m[4][4], float *pDir)
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
    if (!(fn_802270A4(shear) <= lbl_803EC100)) {
        fn_8022728C(shear, shear, lbl_803EC100);
        m[0][2] = shear[0];
        m[1][2] = shear[1];
    }
}

void fn_80235EB4(float m[4][4], int angle, float scale)
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

unsigned int fn_80235F58(float *pColor, float scale)
{
    unsigned int color;

    color = (unsigned int)(pColor[0] * scale);
    color |= (unsigned int)(pColor[1] * scale) << 8;
    color |= (unsigned int)(pColor[2] * scale) << 16;
    color |= (unsigned int)(pColor[3] * scale) << 24;
    return color;
}

void fn_80236164(Scene_8023609C *pScene, GXLightObj *pLights, unsigned int *pColors)
{
    unsigned int i;
    Projector_80236164 *pProjector;

    for (i = 0; i < pScene->mUnknown16; i++) {
        pProjector = &pScene->mUnknown20[i];
        switch (pProjector->mUnknown0) {
        case 0:
            break;
        case 1:
            fn_80235DD8((float (*)[4])&pLights[i], fn_802362C4(pScene, pProjector->mUnknown20)->mUnknown4);
            break;
        case 2:
            fn_80235EB4((float (*)[4])&pLights[i], (int)(pProjector->mUnknown24 * 46603.378f), pProjector->mUnknown28);
            break;
        }
        pColors[i] = fn_80235F58(pProjector->mUnknown4, 128.0f);
    }
}

void *fn_8023608C(Scene_8023609C *pScene, int index)
{
    return pScene->mpUnknown12 + index * 100;
}

void fn_8023609C(Scene_8023609C *pScene)
{
    unsigned int i;
    Light_802362C4 *pLight;

    for (i = 0; i < pScene->mUnknown0; i++) {
        pLight = fn_802362C4(pScene, i);
        if (pLight->mpUnknown32 != 0) {
            pLight->mpUnknown32(pLight);
        }
        fn_802271F0(pLight->mUnknown4, pLight->mUnknown4);
        switch (pLight->mUnknown0) {
        case 0:
        case 1:
            break;
        case 2:
        case 4:
            fn_80227C2C(pLight->mUnknown36, pLight->mUnknown4);
            break;
        case 3:
            pLight->mUnknown36[0] = pLight->mUnknown4[0];
            pLight->mUnknown36[1] = pLight->mUnknown4[1];
            pLight->mUnknown36[2] = pLight->mUnknown4[2];
            break;
        }
    }
}

void fn_80236258(Scene_8023609C *pScene, LightSet_80236368 *pSets)
{
    unsigned int i;

    for (i = 0; i < pScene->mUnknown8; i++) {
        fn_802368D0(pScene, fn_8023608C(pScene, i), &pSets[i]);
    }
}

Light_802362C4 *fn_802362C4(Scene_8023609C *pScene, int index)
{
    return &pScene->mpUnknown4[index];
}

void fn_802362D4(Viewport_t *pObject)
{
    if (lbl_803A2868.mpUnknown0 != 0) {
        MatSetStack(VptGetMatrixStack());
        fn_8023609C(lbl_803A2868.mpUnknown0);
        fn_80236258(lbl_803A2868.mpUnknown0, lbl_803A2868.mUnknown276);
        fn_80236164(lbl_803A2868.mpUnknown0, lbl_803A2868.mUnknown4, lbl_803A2868.mUnknown260);
        fn_80236C04();
    }
}

void fn_8023633C(Scene_8023609C *pScene)
{
    lbl_803A2868.mpUnknown0 = pScene;
    fn_802362D4(0);
}

LightSet_80236368 *fn_80236368(int index)
{
    return &lbl_803A2868.mUnknown276[index];
}

GXLightObj *fn_80236384(int index)
{
    return &lbl_803A2868.mUnknown4[index];
}

unsigned int fn_80236398(int index)
{
    return lbl_803A2868.mUnknown260[index];
}

void fn_802363B0(Viewport_t *pObject)
{
    VptSetCallback(pObject, 1, fn_802362D4, 0);
}

void fn_802363E0(Viewport_t *pObject)
{
    VptRemoveCallback(pObject, fn_802362D4);
}

void fn_80236408(int index, float *pOut)
{
    GXLightObj *pLight = fn_80236384(index);
    float v[3];
    float w[3];

    MatSetStack(0);
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 1.0f;
    MatPush();
    MatLoad((float *)pLight);
    fn_80227C2C(w, v);
    pOut[0] = v[0] - w[0];
    pOut[1] = v[1] - w[1];
    pOut[2] = v[2] - w[2];
    fn_802271F0(pOut, pOut);
    MatPop();
}

GXColor fn_802364B4(float *pColor)
{
    unsigned char rgba[4];

    rgba[0] = (unsigned int)pColor[0];
    rgba[1] = (unsigned int)pColor[1];
    rgba[2] = (unsigned int)pColor[2];
    rgba[3] = (unsigned int)pColor[3];
    return *(GXColor *)rgba;
}

int fn_802365E8(LightSet_80236368 *pSet, float r, float g, float b)
{
    int mask = 0;
    unsigned int i;
    GXLightObj light;
    GXColor color;
    unsigned int value;

    for (i = 0; i < pSet->mUnknown0; i++) {
        if (r != 1.0f || g != 1.0f || b != 1.0f) {
            light = pSet->mUnknown8[i];
            GXGetLightColor(&light, &color);
            value = color.r * r;
            color.r = value > 255 ? 255 : value;
            value = color.g * g;
            color.g = value > 255 ? 255 : value;
            value = color.b * b;
            color.b = value > 255 ? 255 : value;
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

void fn_802368D0(Scene_8023609C *pScene, LightRef_802368D0 *pRefs, LightSet_80236368 *pSet)
{
    unsigned int i;
    LightRef_802368D0 *pRef;
    Light_802362C4 *pLight;
    float scaled[4];
    GXColor color;

    pSet->mUnknown0 = 0;
    pSet->mUnknown4.r = 0;
    pSet->mUnknown4.g = 0;
    pSet->mUnknown4.b = 0;
    pSet->mUnknown4.a = 0;
    for (i = 0; i < 5; i++) {
        pRef = &pRefs[i];
        pLight = fn_802362C4(pScene, pRef->mUnknown0);
        scaled[0] = pLight->mUnknown16[0] * pRef->mUnknown4[0] * pScene->mUnknown148[0];
        scaled[1] = pLight->mUnknown16[1] * pRef->mUnknown4[1] * pScene->mUnknown148[1];
        scaled[2] = pLight->mUnknown16[2] * pRef->mUnknown4[2] * pScene->mUnknown148[2];
        scaled[3] = pLight->mUnknown16[3] * pRef->mUnknown4[3] * pScene->mUnknown148[3];
        color = fn_802364B4(scaled);
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

int fn_80236B4C(int index)
{
    LightSet_80236368 *pSet = fn_80236368(index);
    int mask = fn_802365E8(pSet, 1.0f, 1.0f, 1.0f);

    lbl_803EC108 = pSet;
    lbl_803ED028 = mask;
    return mask;
}

int fn_80236B98(int index, float r, float g, float b)
{
    LightSet_80236368 *pSet = fn_80236368(index);
    int mask = fn_802365E8(pSet, r, g, b);

    lbl_803EC108 = pSet;
    lbl_803ED028 = mask;
    return mask;
}

void fn_80236C04(void)
{
    lbl_803EC108 = 0;
}

void fn_80236C10(int index, float *pColor, float *pDir)
{
    GXLightObj light;
    Vec3_801DE1E0 pos;
    Vec3_801DE1E0 dir;
    unsigned char rgb[4];

    if (pColor[0] < 0.0f) {
        pColor[0] = 0.0f;
    } else if (!(pColor[0] <= 255.0f)) {
        pColor[0] = 255.0f;
    }
    if (pColor[1] < 0.0f) {
        pColor[1] = 0.0f;
    } else if (!(pColor[1] <= 255.0f)) {
        pColor[1] = 255.0f;
    }
    if (pColor[2] < 0.0f) {
        pColor[2] = 0.0f;
    } else if (!(pColor[2] <= 255.0f)) {
        pColor[2] = 255.0f;
    }
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
