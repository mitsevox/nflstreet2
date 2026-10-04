#include "engine/cu_80227F14.h"
#include "game/cu_80064864.h"
#include "game/fn_8007F828.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801FCE10.h"

/* Four floats passed by value to fn_801CD308, which copies them into one of
   two slots selected by its first argument. */
struct Quad_801CD308 {
    float mValues[4];
};

/* 36-byte instance of object type 11 (registered by fn_80047578); the
   player object keeps one at +988 (include/game/Object_8003DEC4.h). */
struct Item_800476DC {
    char mUnknown0[4];
    float mUnknown4[3];
    char mUnknown16[4];
    int mUnknown20;
    const char *mpUnknown24;
    unsigned char mUnknown28;
    float mUnknown32;
};

extern "C" {
extern void *lbl_803EA368;

int fn_8002D060(void *p);
int fn_800A9680(void);
int fn_8018AD34(int a, int b);
int fn_801CD2A4(void);
int fn_801CD308(int index, Quad_801CD308 value);
void fn_801CD3B0(int a);
void fn_801CDB5C(int a, const char *b, int c, float d, float *pPosition);
void fn_801CDD18(void);
int fn_801CECCC(int index);
void fn_801CECDC(int a);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0C58(void *a);
void fn_801D1258(int which, float (*pMatrix)[4]);
void fn_801D1288(int which, float (*pMatrix)[4]);
void fn_801D12BC(int a);
int fn_801DCF0C(int a, int b, int c, void (*pA)(Item_800476DC *), void (*pB)(Item_800476DC *));
void fn_801DCF8C(int a);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(Item_800476DC *));
Item_800476DC *fn_801DD268(int handle, int a, int b, int *pInit);
void fn_801DD320(int handle, Item_800476DC *pInstance);
void fn_80227E40(float *pOut, float *pIn);
int fn_80236EC0(int a);

static int lbl_803EA4C0 = 0;
static float lbl_803EA4C4 = 1.3f;
static unsigned char lbl_803EA4C8 = 1;
static unsigned char lbl_803EA4C9 = 0;
static int lbl_803EC7CC;

void fn_8004732C(void)
{
    lbl_803EC7CC = fn_8018AD34(0, 1);
}

void fn_80047358(Item_800476DC *pInstance)
{
    pInstance->mUnknown4[0] = 0.0f;
    pInstance->mUnknown4[1] = 0.0f;
    pInstance->mUnknown4[2] = 0.02f;
    pInstance->mpUnknown24 = "DEFAULT";
    if (lbl_803EC7CC) {
        pInstance->mUnknown20 = lbl_803EC7CC;
    } else {
        pInstance->mUnknown20 = 0;
    }
    pInstance->mUnknown28 = 0;
}

void fn_80047398(Item_800476DC *pInstance)
{
    pInstance->mUnknown20 = 0;
    pInstance->mpUnknown24 = 0;
    pInstance->mUnknown28 = 0;
}

int fn_800473AC(Item_800476DC *pInstance)
{
    if (lbl_803EA4C8 && fn_8007F828(17)) {
        int mode = fn_800AD9B4();
        if (pInstance->mUnknown28 && pInstance->mUnknown20 && !fn_8002D060(lbl_803EA368) && mode != 4 &&
            mode != 7 && !fn_8006560C() && !fn_800A9680()) {
            float matrix[4][4];
            float saved[4][4];
            Quad_801CD308 value;
            float offset[3];
            int state;

            fn_801CECDC(fn_801CECCC(14));
            state = fn_80236EC0(0);
            fn_801CD2A4();
            if (lbl_803EA4C9) {
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
            fn_801D0470(fn_80228668());
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

void fn_80047578(void)
{
    fn_801DCF0C(11, 36, 27, fn_80047358, fn_80047398);
    fn_801DD0C8(lbl_803EA4C0, 11, 0, fn_800473AC);
    lbl_803EA4C8 = 1;
}

void fn_800475D4(void)
{
    fn_80228E18();
    fn_801DCF8C(11);
}

Item_800476DC *fn_800475FC(int value)
{
    return fn_801DD268(lbl_803EA4C0, 11, 0, &value);
}

void fn_80047630(Item_800476DC *pInstance)
{
    if (pInstance) {
        fn_801DD320(lbl_803EA4C0, pInstance);
        fn_80228D58((int)pInstance);
    }
}

void fn_80047670(int handle)
{
    lbl_803EA4C0 = handle;
    fn_80047578();
    fn_8004732C();
}

void fn_80047698(void)
{
    lbl_803EA4C0 = 0;
    fn_800475D4();
    lbl_803EA4C9 = 0;
}

void fn_800476CC(Item_800476DC *pInstance, const char *pName)
{
    if (pInstance) {
        pInstance->mpUnknown24 = pName;
    }
}

void fn_800476DC(Item_800476DC *pInstance, void *p)
{
    float *pPosition = (float *)p;
    float clip[4];
    float view[4];
    float position[3];
    float point[4];

    position[0] = pPosition[0];
    position[1] = pPosition[1];
    position[2] = pPosition[2];
    fn_801D0470(fn_80228668());
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
        float aspect = fn_80228644()->mUnknown208 * 0.75f;
        float width = aspect * 320.0f;
        pInstance->mUnknown4[0] = width * clip[0] + 320.0f;
        pInstance->mUnknown4[1] = 224.0f - clip[1] * 224.0f;
        pInstance->mUnknown4[1] += 25.0f;
        pInstance->mUnknown32 = view[2] * lbl_803EA4C4;
        pInstance->mUnknown28 = 1;
    } else {
        pInstance->mUnknown28 = 0;
    }
    fn_801D0544();
}

void fn_80047874(unsigned char enable)
{
    lbl_803EA4C8 = enable;
}

void fn_8004787C(void)
{
    int value = 0;

    fn_801FCE10(0, "select 'HTWG' into \x85 from 'FNIG'\n", &value);
    if (value == 3) {
        lbl_803EA4C9 = 1;
    } else {
        lbl_803EA4C9 = 0;
    }
}
}
