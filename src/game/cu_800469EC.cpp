#include "game/fn_8022781C.h"
#include "game/fn_80177FE0.h"
#include "game/cu_8002B8F8.h"
#include "game/cu_80064864.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801EF390.h"
#include "engine/cu_80227F14.h"
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXVert.h>

/* The pool allocates 0x128 bytes. Only observed fields are exposed. */
struct Item_800469EC {
    char mUnknown0[4];
    Vector_80039F5C mUnknown4;
    char mUnknown10[0xC8];
    float mUnknownD8;
    float mUnknownDC;
    float mUnknownE0;
    float mUnknownE4;
    float mUnknownE8;
    float mUnknownEC;
    float mUnknownF0;
    int mUnknownF4;
    char mUnknownF8[0x28];
    int mUnknown120;
    int mUnknown124;
};

/* Projection writes two three-component bounds with 16-byte stride. */
struct Bounds_80234D00 {
    Vector_80039F5C mUnknown0;
    char mUnknownC[4];
    Vector_80039F5C mUnknown10;
    char mUnknown1C[4];
};

extern "C" {
unsigned char fn_8002D060(Type_803EA368 *p);
int fn_800BA6F8(void);
void *fn_800C47C4(void);
int fn_80177F70(void);
Point_8017886C fn_80177FFC(int team);
float fn_80178298(void);
int fn_80178320(void);
int fn_801784C4(void);
float fn_80178A08(void);
float fn_80178A2C(void);
int fn_801486A0(void);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0C58(void *p);
void fn_801D0F80(float (*pMatrix)[4]);
int fn_801DCF0C(int type, int size, int count, void (*a)(Item_800469EC *), void (*b)(Item_800469EC *));
void fn_801DCF8C(int type);
void fn_801DD0C8(int handle, int type, int a, int (*callback)(Item_800469EC *));
Item_800469EC *fn_801DD268(int handle, int type, int a, int *pInit);
void fn_801DD320(int handle, Item_800469EC *p);
void fn_801DD3AC(int handle, Item_800469EC *p, int a);
void fn_80210388(void);
void fn_80210814(int a, int b, int c);
void fn_80210CC4(float a, float b);
void fn_80211E08(void *p, int a);
void fn_80211EFC(void *p);
int fn_802120E4(void *p, unsigned int key);
int fn_80212124(void *p, unsigned int key, int a);
void fn_80234D00(Bounds_80234D00 *pIn, Bounds_80234D00 *pOut);
int fn_80236EC0(int a);
void fn_8024CB90(int a, int b);
void fn_8024D418(void);
void fn_8024D450(int a, int b, int c, int d, int e);
void fn_8024DCE4(int a, int b, int c, int d, int e, int f);
void fn_8024DF64(int a);
void fn_8024E908(int a, int b, int c);
void fn_8024EB28(int a);
void fn_8024FB58(int a, GXColor color);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void fn_80251604(int a, int b);
void fn_80251B28(int a, int b, int c, int d);
void fn_80251CC4(int a);
void fn_80252034(int a, int b, int c, int d);
void fn_802520E0(int a, int b, int c);
void fn_80252114(int a);
void fn_8025251C(float (*matrix)[4], int a);
void fn_802525BC(int a);
extern Bounds_80234D00 lbl_802CEFF0;
extern float lbl_803EA4B8;

static int lbl_803EC7B8;
static unsigned char lbl_803EC7BC[5];
static unsigned char lbl_803EC7C4[5];
static Item_800469EC *lbl_803078D4[5];

float fn_80046920(Item_800469EC *p)
{
    Bounds_80234D00 bounds;
    float extra = 0.0f;
    fn_801D04C4();
    fn_801D0C58(&p->mUnknown4);
    fn_80234D00(&lbl_802CEFF0, &bounds);
    float distance = fn_8022781C(&bounds.mUnknown10, &bounds.mUnknown0);
    fn_801D0544();
    if (distance < 0.08f) {
        float ratio = 0.08f / distance;
        if (!(ratio < 1.0f)) {
            if (ratio > 20.0f) {
                ratio = 20.0f;
            }
            extra = (ratio - 1.0f) * 0.5f;
        }
    }
    return extra + 1.0f;
}

int fn_800469EC(Item_800469EC *p)
{
    if (fn_80177F70() && !fn_800BA6F8() && !fn_8002D060(lbl_803EA368) &&
        lbl_803EC7C4[p->mUnknownF4] == 1 && !fn_8006560C() && fn_800AD9B4() != 7) {
        float zero = 0.0f;
        if (p->mUnknownE4 > zero) {
            float scale = fn_80046920(p);
            float matrix[4][4];
            fn_80210388();
            int state = fn_80236EC0(0);
            fn_8024EB28(0);
            fn_80252034(1, 4, 5, 5);
            fn_80252114(0);
            fn_802520E0(0, 3, 0);
            fn_80210CC4(zero, 1.0f);
            fn_8024D418();
            fn_8024CB90(9, 1);
            fn_8024D450(0, 9, 1, 4, 0);
            GXColor color;
            color.r = (unsigned char)(int)(p->mUnknownD8 * 255.0f);
            color.g = (unsigned char)(int)(p->mUnknownDC * 255.0f);
            color.b = (unsigned char)(int)(p->mUnknownE0 * 255.0f);
            color.a = (unsigned char)(int)(p->mUnknownE4 * 255.0f);
            fn_8024FB58(4, color);
            fn_8024FC48(1);
            fn_8024FC84(4, 0, 0, 0, 1, 2, 1);
            fn_8024CB90(13, 1);
            fn_8024D450(0, 13, 1, 4, 0);
            fn_80251604(0, 0);
            fn_8024DF64(1);
            fn_8024DCE4(0, 1, 4, 60, 0, 125);
            fn_80251CC4(1);
            fn_80251B28(0, 0, 0, 4);
            fn_80210814(0, p->mUnknown120, p->mUnknown124);
            fn_801D04C4();
            fn_801D0C58(&p->mUnknown4);
            fn_801D0F80(matrix);
            fn_8025251C(matrix, 0);
            fn_802525BC(0);
            fn_801D0544();
            fn_8024E908(0x98, 0, 4);
            GXPosition3f32(fn_80178A08(), scale * ((1.0f - lbl_803EA4B8) * 0.55556f), zero);
            GXTexCoord2f32(0.9f, 1.0f - lbl_803EA4B8 * 0.5f);
            GXPosition3f32(fn_80178A08(), scale * ((1.0f - lbl_803EA4B8) * -0.55556f), zero);
            GXTexCoord2f32(0.9f, lbl_803EA4B8 * 0.5f);
            GXPosition3f32(-fn_80178A08(), scale * ((1.0f - lbl_803EA4B8) * 0.55556f), zero);
            GXTexCoord2f32(0.1f, 1.0f - lbl_803EA4B8 * 0.5f);
            GXPosition3f32(-fn_80178A08(), scale * ((1.0f - lbl_803EA4B8) * -0.55556f), zero);
            GXTexCoord2f32(0.1f, lbl_803EA4B8 * 0.5f);
            fn_80236EC0(state);
        }
        p->mUnknownE4 += p->mUnknownE8;
        if ((p->mUnknownE8 > zero && p->mUnknownE4 > p->mUnknownF0) ||
            (p->mUnknownE8 < zero && p->mUnknownE4 < p->mUnknownEC)) {
            p->mUnknownE8 = -p->mUnknownE8;
        }
    }
    return 0;
}

void fn_80046DEC(Item_800469EC *p, int enabled)
{
    if (enabled) {
        p->mUnknownEC = 0.5f;
        p->mUnknownF0 = 0.8f;
    } else {
        p->mUnknownF0 = -0.1f;
        p->mUnknownE4 = 0.0f;
        p->mUnknownEC = -0.1f;
    }
}

void fn_80046E30(int handle)
{
    lbl_803EC7B8 = handle;
    fn_801DCF0C(17, 0x128, 5, 0, 0);
    fn_801DD0C8(lbl_803EC7B8, 17, 0, fn_800469EC);
    for (int i = 0; i <= 4; ++i) {
        lbl_803EC7C4[i] = 1;
        Item_800469EC *p = fn_801DD268(lbl_803EC7B8, 17, 0, 0);
        lbl_803078D4[i] = p;
        switch (i) {
        case 0:
            p->mUnknownD8 = 1.0f;
            p->mUnknownDC = 1.0f;
            p->mUnknownE0 = 0.0f;
            break;
        case 1:
        case 2:
            p->mUnknownD8 = 1.0f;
            p->mUnknownDC = 0.0f;
            p->mUnknownE0 = 0.0f;
            break;
        case 3:
        case 4:
            p->mUnknownD8 = 0.0f;
            p->mUnknownDC = 0.0f;
            p->mUnknownE0 = 1.0f;
            break;
        }
        p->mUnknownF4 = i;
        p->mUnknownE8 = 0.005f;
        p->mUnknownE4 = 0.0f;
        p->mUnknownEC = 0.0f;
        p->mUnknownF0 = 0.0f;
        lbl_803EC7BC[i] = 0;
        fn_80211E08(p->mUnknownF8, fn_801EF390(fn_800C47C4(), 17, 1));
        p->mUnknown120 = fn_802120E4(p->mUnknownF8, 0xFF000000);
        p->mUnknown124 = fn_80212124(p->mUnknownF8, 0xFF000000, 0);
        fn_801DD3AC(handle, p, 3);
    }
}

void fn_80046FD0(void)
{
    for (unsigned int i = 0; i <= 4; ++i) {
        fn_80211EFC(lbl_803078D4[i]->mUnknownF8);
        fn_801DD320(lbl_803EC7B8, lbl_803078D4[i]);
        fn_80228D58((int)lbl_803078D4[i]);
        lbl_803078D4[i] = 0;
    }
    fn_80228E18();
    fn_801DCF8C(17);
    lbl_803EC7B8 = 0;
}

void fn_80047050(void)
{
    for (unsigned int i = 0; i <= 4; ++i) {
        Item_800469EC *p = lbl_803078D4[i];
        int mode = fn_800AD9B4();
        int inRange = 0;
        if (mode <= 3) {
            inRange = mode >= 2;
        }
        int ready = 0;
        if (inRange && fn_80177F70() && !fn_800BA6F8()) {
            ready = !fn_8002D060(lbl_803EA368);
        }
        int enabled = ready;
        switch (p->mUnknownF4) {
        case 0: {
            lbl_803078D4[i]->mUnknown4.mX = 0.0f;
            Item_800469EC *q0 = lbl_803078D4[i];
            q0->mUnknown4.mY = fn_801784C4() ? -fn_80178298() : fn_80178298();
            lbl_803078D4[i]->mUnknown4.mZ = 0.0f;
            if (!(fn_80178298() < fn_80178A2C()) || !(fn_80178298() > -fn_80178A2C())) {
                enabled = 0;
            }
            break;
        }
        case 1: {
            lbl_803078D4[i]->mUnknown4.mX = 0.0f;
            Item_800469EC *q1 = lbl_803078D4[i];
            q1->mUnknown4.mY = fn_801784C4() ? -fn_80178A2C() : fn_80178A2C();
            lbl_803078D4[i]->mUnknown4.mZ = 0.0f;
            break;
        }
        case 2: {
            lbl_803078D4[i]->mUnknown4.mX = 0.0f;
            Item_800469EC *q2 = lbl_803078D4[i];
            q2->mUnknown4.mY = fn_801784C4() ? fn_80178A2C() : -fn_80178A2C();
            lbl_803078D4[i]->mUnknown4.mZ = 0.0f;
            break;
        }
        case 3: {
            lbl_803078D4[i]->mUnknown4.mX = 0.0f;
            Item_800469EC *q3 = lbl_803078D4[i];
            q3->mUnknown4.mY = fn_801784C4() ? -fn_80177FE0().mY : fn_80177FE0().mY;
            lbl_803078D4[i]->mUnknown4.mZ = 0.0f;
            break;
        }
        case 4: {
            lbl_803078D4[i]->mUnknown4.mX = 0.0f;
            Item_800469EC *q4 = lbl_803078D4[i];
            q4->mUnknown4.mY = fn_801784C4() ? -fn_80177FFC(fn_80178320()).mY : fn_80177FFC(fn_80178320()).mY;
            lbl_803078D4[i]->mUnknown4.mZ = 0.0f;
            if (fn_800AD9B4() != 2) {
                enabled = 0;
            }
            int state = fn_801486A0();
            if (state > 4 || state < 3) {
                enabled = 0;
            }
            break;
        }
        }
        if (lbl_803EC7BC[p->mUnknownF4]) {
            enabled = 1;
        }
        fn_80046DEC(p, enabled);
    }
}

void fn_8004730C(unsigned char enabled)
{
    for (unsigned char i = 0; i <= 4; ++i) {
        lbl_803EC7C4[i] = enabled;
    }
}
}
