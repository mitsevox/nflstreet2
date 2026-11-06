/* Football model rendering: loads the ball textures and the BALL model,
   attaches the model to a ball object and draws it with its lighting, fade
   and level of detail, toggling the ball's simple shadow. */
#include "game/fn_8017F584.h"
#include "game/fn_801EF390.h"
#include "game/Object_80233EAC.h"
#include "game/LightTracker.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>

struct BallTexLib {
    char mUnknown0[0x28];
};

struct BallModelLod {
    float mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    char mUnknown10[0x44];
    int mUnknown54;
    char mUnknown58[4];
    int mUnknown5C;
    char mUnknown60[0x4C];
    int mUnknownAC;
    char mUnknownB0[0x40];
};

struct BallRenderObj {
    char mUnknown0[4];
    char mUnknown4[0x10];
    int mUnknown14;
    void *mpUnknown18;
    char mUnknown1C[4];
    Mtx44 mUnknown20;
    char mUnknown60[0x224];
    char mUnknown284[8];
    float mUnknown28C;
    char mUnknown290[4];
    LightSource_t *mpUnknown294;
    float mUnknown298;
    float mUnknown29C;
    float mUnknown2A0;
    char mUnknown2A4[8];
    Tracker_801442FC mUnknown2AC;
};

extern "C" {
int FELoopIsMainFEActive(void);
unsigned char CheatFlagsIsSet(int index);
int fn_801486A0(void);
void SimpShadowSetVisible(void *p, int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0664(Mtx44 m);
void fn_801D0CFC(float a);
void TMXform(int a, void *b);
void TMMaterialListAllocDefs(void *p, void *q);
void TMMaterialListFree(void *p);
void TMRenderReset(void);
void TMRenderBindModel(Object_8023417C *pObject);
void TMRenderBindMaterialList(void *p);
void TMRenderSetBlendMode(int a);
void TMRenderSetZRange(float a, float b);
void TMRenderSetZMode(int a, int b, int c);
void fn_80211350(void);
void TMTexLibLoad(BallTexLib *pElement, int a);
void TMTexLibUnload(BallTexLib *pElement);
void TMTexLibRegistryReset(void);
void TMTexLibRegister(const char *pName, BallTexLib *pElement);
void fn_80233D64(Object_80233EAC *pObject, BallModelLod *pDesc, const char *pName, int a,
                 void *pData, void *p);
unsigned int fn_80234D4C(float *pBox, void *m, void *p, void *q);
void *fn_80236384(int a);
int fn_80236B98(int a, float x, float y, float z);
void fn_80236C10(int a, float *p, float *q);
void fn_8024FB58(int a, GXColor color);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
}

static float _BallRender_afCullBox[8] = { -0.5f, -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f };
static BallModelLod _BallRender_ModelLods = { 0.00390625f, 1500, 0, 13, { 0 }, 500, { 0 }, 14, { 0 }, 0xFFFF };
static BallTexLib _BallRender_aTexLibs[2];
static Object_80233EAC _BallRender_Model;
static unsigned char _BallRender_abTexLibLoaded[2] = { 0, 0 };

extern "C" {
void BallRenderInit(BallRenderObj *pObject)
{
    int value;

    TMTexLibLoad(&_BallRender_aTexLibs[0], fn_801EF390(pObject->mpUnknown18, 15, 1));
    _BallRender_abTexLibLoaded[0] = 1;
    value = fn_801486A0();
    if (value == 1) {
        TMTexLibLoad(&_BallRender_aTexLibs[1], fn_801EF390(pObject->mpUnknown18, 16, 1));
        _BallRender_abTexLibLoaded[1] = 1;
    }
    fn_80233D64(&_BallRender_Model, &_BallRender_ModelLods, "BALL", 0, pObject->mpUnknown18, 0);
}

void BallRenderShutdown(BallRenderObj *pObject)
{
    fn_80233FCC(&_BallRender_Model);
    TMTexLibUnload(&_BallRender_aTexLibs[0]);
    _BallRender_abTexLibLoaded[0] = 0;
    if (_BallRender_abTexLibLoaded[1] != 0) {
        TMTexLibUnload(&_BallRender_aTexLibs[1]);
        _BallRender_abTexLibLoaded[1] = 0;
    }
    fn_801F010C(pObject->mpUnknown18, 15);
}

void BallRenderAttach(BallRenderObj *pObject, int index)
{
    Object_8023417C *pResult;

    pObject->mUnknown28C = 1.0f;
    TMTexLibRegistryReset();
    TMTexLibRegister("model", &_BallRender_aTexLibs[index]);
    pResult = fn_8023417C(&_BallRender_Model, 0);
    TMMaterialListAllocDefs(pObject->mUnknown284, pResult->mpUnknown18);
}

void BallRenderDetach(BallRenderObj *pObject)
{
    TMMaterialListFree(pObject->mUnknown284);
}

void BallRenderDraw(BallRenderObj *pObject)
{
    char buffer[32];
    float unknown28[3];
    float unknown38[3];
    GXColor color = { 255, 255, 255, 255 };
    void *pUnknown;
    float x;
    float y;
    float z;
    int mask;
    int result;
    Object_8023417C *pResult;

    pUnknown = fn_80236384(0);
    TMRenderReset();
    x = y = z = 1.0f;
    if (pObject->mpUnknown294 != 0) {
        x = pObject->mpUnknown294->mUnknownC;
        y = pObject->mpUnknown294->mUnknown10;
        z = pObject->mpUnknown294->mUnknown14;
    }
    if (pObject->mUnknown14 & 0x20) {
        x *= pObject->mUnknown298;
        y *= pObject->mUnknown29C;
        z *= pObject->mUnknown2A0;
    }
    color.a = pObject->mUnknown28C * 128.0f;
    mask = fn_80236B98(4, x, y, z);
    if (LightTrackerUpdate(&pObject->mUnknown2AC, pObject->mpUnknown294, unknown28, unknown38)) {
        unknown38[0] *= x;
        unknown38[1] *= y;
        unknown38[2] *= z;
        fn_80236C10(0, unknown38, unknown28);
    }
    fn_8024FB58(4, color);
    fn_8024FC84(0, 1, 0, 0, mask, 2, 2);
    fn_8024FC84(2, 0, 0, 0, mask, 2, 2);
    if (!(pObject->mUnknown14 & 8)) {
        fn_80234D4C(_BallRender_afCullBox, pObject->mUnknown20, pUnknown, 0);
        result = fn_80234D4C(_BallRender_afCullBox, pObject->mUnknown20, 0, buffer);
    } else {
        pObject->mUnknown14 &= ~8;
        result = 63;
    }
    if (FELoopIsMainFEActive()) {
        pResult = fn_8023417C(&_BallRender_Model, 0);
    } else {
        pResult = fn_8023417C(&_BallRender_Model, fn_80234144(&_BallRender_Model, buffer));
    }
    TMRenderBindModel(pResult);
    TMRenderBindMaterialList(pObject->mUnknown284);
    if (!(result & 63)) {
        fn_801D04C4();
        fn_801D0664(pObject->mUnknown20);
        if (CheatFlagsIsSet(33) || CheatFlagsIsSet(34)) {
            if (!fn_8017F584()) {
                fn_801D0CFC(1.5f);
            }
        }
        TMXform(0, 0);
        TMRenderSetBlendMode(2);
        fn_80211350();
        TMRenderSetBlendMode(1);
        fn_801D0544();
    }
    if (!(pObject->mUnknown14 & 2)) {
        SimpShadowSetVisible(pObject->mUnknown4, 1);
    } else {
        SimpShadowSetVisible(pObject->mUnknown4, 0);
    }
    TMRenderSetZMode(1, 3, 1);
    TMRenderSetZRange(0.0f, 1.0f);
    TMRenderSetBlendMode(1);
}
}
