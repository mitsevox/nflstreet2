/* Player name tags: one small object per player that projects the player's
   position to the screen each frame and draws the player's name above it. */
#include "engine/viewport.h"
#include "game/PauseMenu.h"
#include "game/GameOptions.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801FCE10.h"
#include "game/PlyrNameTag.h"

/* Four floats passed by value to fn_801CD308, which copies them into one of
   two slots selected by its first argument. */
struct NameTagColor_t {
    float mValues[4];
};

extern "C" {
extern void *lbl_803EA368;

int fn_8002D060(void *p);
int fn_800A9680(void);
int UISGetFont(int a, int b);
void fn_801CD2A4(void);
int fn_801CD308(int index, NameTagColor_t value);
void fn_801CD3B0(int a);
int fn_801CDB5C(int a, const char *b, int c, float d, float *pPosition);
void fn_801CDD18(void);
int GlibRenderGetBin(int index);
void GlibRenderSelectBin(int a);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0C58(void *a);
void fn_801D1258(int which, float (*pMatrix)[4]);
void fn_801D1288(int which, float (*pMatrix)[4]);
void fn_801D12BC(int a);
int ObjNewType_(int a, int b, int c, void (*pA)(PlyrNameTag_t *), void (*pB)(PlyrNameTag_t *));
int ObjDelType(int a);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)(PlyrNameTag_t *));
int ObjNewInList(int handle, int a, int b, int *pInit);
void ObjRemoveFromList(int handle, PlyrNameTag_t *pInstance);
void fn_80227E40(float *pOut, float *pIn);
int fn_80236EC0(int a);

static int _PlyrNameTag_iObjList = 0;
static float _PlyrNameTag_fDepthScale = 1.3f;
static unsigned char _PlyrNameTag_bEnabled = 1;
static unsigned char _PlyrNameTag_bBlackText = 0;
unsigned char gPlayerObjDrawReady = 0;
static int _PlyrNameTag_iFont;

void PlyrNameTagLoadFont(void)
{
    _PlyrNameTag_iFont = UISGetFont(0, 1);
}

void PlyrNameTagCreate(PlyrNameTag_t *pInstance)
{
    pInstance->mUnknown4[0] = 0.0f;
    pInstance->mUnknown4[1] = 0.0f;
    pInstance->mUnknown4[2] = 0.02f;
    pInstance->mpUnknown24 = "DEFAULT";
    if (_PlyrNameTag_iFont) {
        pInstance->mUnknown20 = _PlyrNameTag_iFont;
    } else {
        pInstance->mUnknown20 = 0;
    }
    pInstance->mUnknown28 = 0;
}

void PlyrNameTagDestroy(PlyrNameTag_t *pInstance)
{
    pInstance->mUnknown20 = 0;
    pInstance->mpUnknown24 = 0;
    pInstance->mUnknown28 = 0;
}

int PlyrNameTagDraw(PlyrNameTag_t *pInstance)
{
    if (_PlyrNameTag_bEnabled && GameOptionsGet(17)) {
        int mode = fn_800AD9B4();
        if (pInstance->mUnknown28 && pInstance->mUnknown20 && !fn_8002D060(lbl_803EA368) && mode != 4 &&
            mode != 7 && !PauseIsOpen() && !fn_800A9680()) {
            float matrix[4][4];
            float saved[4][4];
            NameTagColor_t value;
            float offset[3];
            int state;

            GlibRenderSelectBin(GlibRenderGetBin(14));
            state = fn_80236EC0(0);
            fn_801CD2A4();
            if (_PlyrNameTag_bBlackText) {
                value.mValues[0] = 0.0f;
                value.mValues[1] = 0.0f;
                value.mValues[2] = 0.0f;
                value.mValues[3] = 1.0f;
                fn_801CD308(0, value);
            }
            fn_801CD3B0(32);
            fn_801CDD18();
            fn_801D1288(1, saved);
            fn_801D1288(1, matrix);
            matrix[2][0] = 0.0f;
            matrix[2][1] = 0.0f;
            matrix[2][2] = 0.0f;
            matrix[2][3] = pInstance->mUnknown32;
            fn_801D1258(1, matrix);
            fn_801D0470(VptGetMatrixStack());
            fn_801D04C4();
            offset[0] = 106.666679f;
            offset[1] = 0.0f;
            offset[2] = 0.0f;
            fn_801D0C58(offset);
            fn_801CDB5C(pInstance->mUnknown20, pInstance->mpUnknown24, 1, 0.0f, pInstance->mUnknown4);
            fn_801D0544();
            fn_801D1258(1, saved);
            fn_80236EC0(state);
        }
    }
    return 0;
}

void PlyrNameTagAddObjType(void)
{
    ObjNewType_(11, 36, 27, PlyrNameTagCreate, PlyrNameTagDestroy);
    ObjSetListObjFunc(_PlyrNameTag_iObjList, 11, 0, PlyrNameTagDraw);
    _PlyrNameTag_bEnabled = 1;
}

void PlyrNameTagRemoveObjType(void)
{
    VptFlushObjectTrashSync();
    ObjDelType(11);
}

PlyrNameTag_t *PlyrNameTagNew(int value)
{
    return (PlyrNameTag_t *)ObjNewInList(_PlyrNameTag_iObjList, 11, 0, &value);
}

void PlyrNameTagDelete(PlyrNameTag_t *pInstance)
{
    if (pInstance) {
        ObjRemoveFromList(_PlyrNameTag_iObjList, pInstance);
        VptTrashObject((int)pInstance);
    }
}

void PlyrNameTagInit(int handle)
{
    _PlyrNameTag_iObjList = handle;
    PlyrNameTagAddObjType();
    PlyrNameTagLoadFont();
}

void PlyrNameTagShutdown(void)
{
    _PlyrNameTag_iObjList = 0;
    PlyrNameTagRemoveObjType();
    _PlyrNameTag_bBlackText = 0;
}

void PlyrNameTagSetText(PlyrNameTag_t *pInstance, const char *pName)
{
    if (pInstance) {
        pInstance->mpUnknown24 = pName;
    }
}

void PlyrNameTagUpdatePosition(PlyrNameTag_t *pInstance, void *p)
{
    float *pPosition = (float *)p;
    float clip[4];
    float view[4];
    float position[3];
    float point[4];

    position[0] = pPosition[0];
    position[1] = pPosition[1];
    position[2] = pPosition[2];
    fn_801D0470(VptGetMatrixStack());
    fn_801D04C4();
    fn_801D12BC(4);
    point[0] = position[0];
    point[1] = position[1];
    point[2] = position[2];
    point[3] = 1.0f;
    fn_80227E40(clip, point);
    if (clip[0] > -clip[3] && clip[0] < clip[3] && clip[1] > -clip[3] && clip[1] < clip[3] &&
        clip[2] > -clip[3] && clip[2] < clip[3]) {
        float scale = 1.0f / clip[3];
        clip[0] *= scale;
        clip[1] *= scale;
        clip[2] *= scale;
        clip[3] *= scale;
        fn_801D12BC(1);
        fn_80227E40(view, clip);
        float aspect = VptGetCurrentViewport()->mUnknown208 * 0.75f;
        float width = aspect * 320.0f;
        pInstance->mUnknown4[0] = width * clip[0] + 320.0f;
        pInstance->mUnknown4[1] = 224.0f - clip[1] * 224.0f;
        pInstance->mUnknown4[1] += 25.0f;
        pInstance->mUnknown32 = view[2] * _PlyrNameTag_fDepthScale;
        pInstance->mUnknown28 = 1;
    } else {
        pInstance->mUnknown28 = 0;
    }
    fn_801D0544();
}

void PlyrNameTagEnable(unsigned char enable)
{
    _PlyrNameTag_bEnabled = enable;
}

void PlyrNameTagReadTextColor(void)
{
    int value = 0;

    fn_801FCE10(0, "select 'HTWG' into \x85 from 'FNIG'\n", &value);
    if (value == 3) {
        _PlyrNameTag_bBlackText = 1;
    } else {
        _PlyrNameTag_bBlackText = 0;
    }
}
}
