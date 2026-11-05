/* Football model rendering: loads the ball textures and the BALL model,
   attaches the model to a ball object and draws it with its lighting, fade
   and level of detail, toggling the ball's simple shadow. */
#include "game/fn_8017F584.h"
#include "game/fn_801EF390.h"
#include "game/Object_80233EAC.h"
#include "game/cu_801442FC.h"
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
    Object_80144310 *mpUnknown294;
    float mUnknown298;
    float mUnknown29C;
    float mUnknown2A0;
    char mUnknown2A4[8];
    Tracker_801442FC mUnknown2AC;
};

extern "C" {
int fn_80027DF0(void);
unsigned char fn_80054D24(int index);
int fn_801486A0(void);
void SimpShadowSetVisible(void *p, int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0664(Mtx44 m);
void fn_801D0CFC(float a);
void fn_8020FA38(int a, void *b);
void fn_802100C0(void *p, void *q);
void fn_80210114(void *p);
void fn_80210388(void);
void fn_80210654(Object_8023417C *pObject);
void fn_80210BA4(void *p);
void fn_80210BD8(int a);
void fn_80210CC4(float a, float b);
void fn_80210D10(int a, int b, int c);
void fn_80211350(void);
void fn_80211E08(BallTexLib *pElement, int a);
void fn_80211EFC(BallTexLib *pElement);
void fn_80211FF0(void);
void fn_80212018(const char *pName, BallTexLib *pElement);
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
static BallModelLod _BallRender_aModelLods = { 0.00390625f, 1500, 0, 13, { 0 }, 500, { 0 }, 14, { 0 }, 0xFFFF };
static BallTexLib _BallRender_aTexLibs[2];
static Object_80233EAC _BallRender_Model;
static unsigned char _BallRender_abTexLibLoaded[2] = { 0, 0 };

extern "C" {
void BallRenderInit(BallRenderObj *pObject)
{
    int value;

    fn_80211E08(&_BallRender_aTexLibs[0], fn_801EF390(pObject->mpUnknown18, 15, 1));
    _BallRender_abTexLibLoaded[0] = 1;
    value = fn_801486A0();
    if (value == 1) {
        fn_80211E08(&_BallRender_aTexLibs[1], fn_801EF390(pObject->mpUnknown18, 16, 1));
        _BallRender_abTexLibLoaded[1] = 1;
    }
    fn_80233D64(&_BallRender_Model, &_BallRender_aModelLods, "BALL", 0, pObject->mpUnknown18, 0);
}

void BallRenderShutdown(BallRenderObj *pObject)
{
    fn_80233FCC(&_BallRender_Model);
    fn_80211EFC(&_BallRender_aTexLibs[0]);
    _BallRender_abTexLibLoaded[0] = 0;
    if (_BallRender_abTexLibLoaded[1] != 0) {
        fn_80211EFC(&_BallRender_aTexLibs[1]);
        _BallRender_abTexLibLoaded[1] = 0;
    }
    fn_801F010C(pObject->mpUnknown18, 15);
}

void BallRenderAttach(BallRenderObj *pObject, int index)
{
    Object_8023417C *pResult;

    pObject->mUnknown28C = 1.0f;
    fn_80211FF0();
    fn_80212018("model", &_BallRender_aTexLibs[index]);
    pResult = fn_8023417C(&_BallRender_Model, 0);
    fn_802100C0(pObject->mUnknown284, pResult->mpUnknown18);
}

void BallRenderDetach(BallRenderObj *pObject)
{
    fn_80210114(pObject->mUnknown284);
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
    fn_80210388();
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
    if (fn_80144310(&pObject->mUnknown2AC, pObject->mpUnknown294, unknown28, unknown38)) {
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
    if (fn_80027DF0()) {
        pResult = fn_8023417C(&_BallRender_Model, 0);
    } else {
        pResult = fn_8023417C(&_BallRender_Model, fn_80234144(&_BallRender_Model, buffer));
    }
    fn_80210654(pResult);
    fn_80210BA4(pObject->mUnknown284);
    if (!(result & 63)) {
        fn_801D04C4();
        fn_801D0664(pObject->mUnknown20);
        if (fn_80054D24(33) || fn_80054D24(34)) {
            if (!fn_8017F584()) {
                fn_801D0CFC(1.5f);
            }
        }
        fn_8020FA38(0, 0);
        fn_80210BD8(2);
        fn_80211350();
        fn_80210BD8(1);
        fn_801D0544();
    }
    if (!(pObject->mUnknown14 & 2)) {
        SimpShadowSetVisible(pObject->mUnknown4, 1);
    } else {
        SimpShadowSetVisible(pObject->mUnknown4, 0);
    }
    fn_80210D10(1, 3, 1);
    fn_80210CC4(0.0f, 1.0f);
    fn_80210BD8(1);
}
}
