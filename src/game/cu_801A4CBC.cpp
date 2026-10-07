#include <dolphin/gx/GXPixel.h>
#include "engine/cu_80227F14.h"
#include "game/Object_80039F5C.h"
#include "game/fn_801D2B7C.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>

struct Entry_801A5050 {
    int mUnknown0;
    Vector_80039F5C *mpUnknown4;
    float mUnknown8;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mUnknownF;
    unsigned char mUnknown10;
};

struct Object_80193F84 {
    char mUnknown0[8];
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    char mUnknownC[4];
    int mUnknown10;
    void *mpUnknown14;
    char mUnknown18[16];
    unsigned char mUnknown28;
    char mUnknown29[23];
};

extern "C" {
int fn_800C47C4(void);
void fn_80193EF0(Object_80193F84 *p, int a, int b, int c, const char *pName);
void fn_80193F2C(Object_80193F84 *p);
void fn_80193F84(Object_80193F84 *p);
int fn_801CECCC(int index);
int fn_801CECDC(int a);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0664(Mtx44 m);
void fn_801D0D94(float x, float y, float z);
void fn_801D0F80(Mtx44 m);
int fn_801D34D0(void *pDest, int size, int value, int width);
void fn_80210388(void);
void fn_802271A4(Vector_80039F5C *pOut, Vector_80039F5C *p);
void fn_80227384(Vector_80039F5C *pOut, Vector_80039F5C *p, int a);
void *fn_80236384(int a);
void fn_80236408(int a, Vector_80039F5C *pOut);
void fn_8024CB90(int a, int b);
void fn_8024D418(void);
void fn_8024D450(int a, int b, int c, int d, int e);
void fn_8024DCE4(int a, int b, int c, int d, int e, int f);
void fn_8024DF64(int a);
void fn_8024FB58(int a, GXColor color);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void fn_8024FFC4(GXTexObj *pObj, void *p, int a, int b, int c, int d, int e, int f);
void fn_802505A8(GXTexObj *pObj, int a);
void fn_80251604(int a, int b);
void fn_80251B28(int a, int b, int c, int d);
void fn_80251CC4(int a);
void fn_8025251C(Mtx44 m, int a);
void fn_802525BC(int a);
}

extern int lbl_803EBC98;

static Entry_801A5050 *lbl_803664C0[96];
static Object_80193F84 lbl_80366640[1];
static GXTexObj lbl_80366680;
static int lbl_803EB830[1] = { 0 };
static unsigned short lbl_803EB834 = 0;
static Entry_801A5050 *lbl_803EB838 = 0;
static unsigned char lbl_803EB83C = 0;
static unsigned char lbl_803ECC18;

extern "C" {
int fn_801A4CBC(int a, Entry_801A5050 *pEntry, Vector_80039F5C *pScale)
{
    Vector_80039F5C pts[4];
    Vector_80039F5C *pPos = pEntry->mpUnknown4;
    float dx = pEntry->mUnknown8 * pScale->mX;
    float dy = pEntry->mUnknown8 * pScale->mY;
    float z;

    pts[0].mX = pPos->mX + dx;
    pts[0].mY = pPos->mY + dy;
    pts[0].mZ = 0.0f;
    pts[1].mX = pPos->mX - dy;
    pts[1].mY = pPos->mY + dx;
    pts[1].mZ = 0.0f;
    pts[2].mX = pPos->mX - dx;
    pts[2].mY = pPos->mY - dy;
    pts[2].mZ = 0.0f;
    pts[3].mX = pPos->mX + dy;
    pts[3].mY = pPos->mY - dx;
    pts[3].mZ = 0.0f;
    z = pPos->mZ;
    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
    GXPosition3f32(pts[0].mX, pts[0].mY, z);
    GXColor4u8(pEntry->mUnknownC, pEntry->mUnknownE, pEntry->mUnknownD, pEntry->mUnknownF);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(pts[1].mX, pts[1].mY, z);
    GXColor4u8(pEntry->mUnknownC, pEntry->mUnknownE, pEntry->mUnknownD, pEntry->mUnknownF);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(pts[2].mX, pts[2].mY, z);
    GXColor4u8(pEntry->mUnknownC, pEntry->mUnknownE, pEntry->mUnknownD, pEntry->mUnknownF);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(pts[3].mX, pts[3].mY, z);
    GXColor4u8(pEntry->mUnknownC, pEntry->mUnknownE, pEntry->mUnknownD, pEntry->mUnknownF);
    GXTexCoord2f32(0.0f, 0.0f);
    return a;
}

void fn_801A4E9C(void)
{
    unsigned short i;

    lbl_803EB838 = (Entry_801A5050 *)fn_801D2B7C(96 * sizeof(Entry_801A5050), 0, 0);
    fn_801D34D0(lbl_803EB838, 96 * sizeof(Entry_801A5050), 0, 1);
    for (i = 0; i < 96; i++) {
        lbl_803664C0[i] = &lbl_803EB838[i];
    }
    for (i = 0; i < 1; i++) {
        fn_80193F84(&lbl_80366640[i]);
        fn_80193EF0(&lbl_80366640[i], 0, fn_800C47C4(), lbl_803EB830[i], "LLSimpShadow");
    }
    lbl_803EB834 = 0;
    lbl_803EB83C = 1;
    lbl_803ECC18 = 1;
    fn_8024FFC4(&lbl_80366680, lbl_80366640[0].mpUnknown14, lbl_80366640[0].mUnknown8,
                lbl_80366640[0].mUnknownA, lbl_80366640[0].mUnknown10, 0, 0, 0);
}

void fn_801A4FB0(void)
{
    unsigned short i;

    for (i = 0; i < 1; i++) {
        if (lbl_80366640[i].mUnknown28 != 0) {
            fn_80193F2C(&lbl_80366640[i]);
        }
    }
    for (i = 0; i < 96; i++) {
        lbl_803664C0[i] = 0;
    }
    fn_801D2BD0(lbl_803EB838);
    lbl_803EB838 = 0;
    lbl_803EB83C = 0;
    lbl_803EB834 = 0;
    lbl_803ECC18 = 0;
}

void fn_801A5050(int a, Vector_80039F5C *p, float b, float *pColor)
{
    Entry_801A5050 *pEntry = lbl_803664C0[lbl_803EB834];

    pEntry->mUnknown0 = a;
    pEntry->mpUnknown4 = p;
    pEntry->mUnknown8 = b;
    pEntry->mUnknownC = (unsigned char)(pColor[0] * 255.0f);
    pEntry->mUnknownE = (unsigned char)(pColor[1] * 255.0f);
    pEntry->mUnknownD = (unsigned char)(pColor[2] * 255.0f);
    pEntry->mUnknownF = (unsigned char)(pColor[3] * 255.0f);
    pEntry->mUnknown10 = 1;
    lbl_803EB834++;
}

void fn_801A5104(void)
{
    Mtx44 mtx;
    Vector_80039F5C scale;
    GXColor color = { 128, 128, 128, 255 };

    if (lbl_803ECC18 != 0) {
        unsigned short i;
        int cursor = fn_801CECDC(fn_801CECCC(2));

        fn_80210388();
        GXSetCullMode(GX_CULL_NONE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXSetZCompLoc(GX_DISABLE);
        GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
        fn_8024D418();
        fn_8024CB90(9, 1);
        fn_8024D450(0, 9, 1, 4, 0);
        fn_8024CB90(11, 1);
        fn_8024D450(0, 11, 1, 5, 0);
        fn_8024FC48(1);
        fn_8024FC84(4, 0, 1, 1, 0, 0, 2);
        fn_8024CB90(13, 1);
        fn_8024D450(0, 13, 1, 4, 0);
        fn_80251604(0, 0);
        fn_8024DF64(1);
        fn_8024DCE4(0, 1, 4, 60, 0, 125);
        fn_80251CC4(1);
        fn_80251B28(0, 0, 0, 4);
        fn_801D0470(fn_80228668());
        fn_802505A8(&lbl_80366680, 0);
        fn_801D04C4();
        fn_801D0664((float (*)[4])fn_80236384(0));
        fn_80236408(0, &scale);
        scale.mZ = 0.0f;
        fn_80227384(&scale, &scale, 0x200000);
        fn_802271A4(&scale, &scale);
        fn_801D0F80(mtx);
        fn_8025251C(mtx, 0);
        fn_802525BC(0);
        fn_801D0544();
        for (i = 0; i < lbl_803EB834; i++) {
            if (lbl_803664C0[i]->mUnknown10 != 0 && lbl_803664C0[i]->mUnknown0 == 0) {
                cursor = fn_801A4CBC(cursor, lbl_803664C0[i], &scale);
            }
        }
        fn_801D04C4();
        fn_801D0D94(1.0f, 1.0f, 0.0f);
        fn_801D0F80(mtx);
        fn_8025251C(mtx, 0);
        fn_802525BC(0);
        fn_801D0544();
        scale.mY = scale.mX = 0.5f;
        for (i = 0; i < lbl_803EB834; i++) {
            if (lbl_803664C0[i]->mUnknown10 != 0 && lbl_803664C0[i]->mUnknown0 == 1) {
                cursor = fn_801A4CBC(cursor, lbl_803664C0[i], &scale);
            }
        }
        lbl_803EBC98 = cursor;
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
        fn_8024FB58(4, color);
    }
}

void fn_801A5434(void *p, int value)
{
    unsigned int i;

    for (i = 0; i < lbl_803EB834; i++) {
        if (lbl_803664C0[i]->mpUnknown4 == p) {
            lbl_803664C0[i]->mUnknown10 = value;
        }
    }
}
}
