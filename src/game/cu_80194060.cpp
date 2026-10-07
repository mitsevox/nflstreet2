#include <dolphin/vi.h>
#include "game/fn_801EF390.h"
#include "game/fn_801EEB44.h"
#include "game/fn_8007F828.h"
#include "game/cu_801CF5BC.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXVert.h>
#include <string.h>

struct Texture_80194108 {
    unsigned char mUnknown0[0x54];
    GXTexRegion *mUnknown54;
};
struct Quad_8019424C {
    Texture_80194108 *mUnknown0;
    float mUnknown4[4][2];
    float mUnknown24[4][2];
};
struct Element_80194108 { unsigned char mUnknown0[0x28]; };
struct Palette_80194108 { unsigned char mUnknown0[4]; GXTlutObj mUnknown4; };
struct Point_803ECB9C { float mX, mY; };
static Texture_80194108 lbl_80364F58;
static Quad_8019424C lbl_80364FB0;
static Quad_8019424C lbl_80364FF4;
static GXTexRegion lbl_80365038[2];
static Mtx44 lbl_80365058;
static GXTexRegion lbl_80365098;
static void *lbl_803EB728 = 0;
static unsigned char lbl_803EB72C[4] = {0,0,0,0};
static Point_803ECB9C lbl_803ECB9C;
static float lbl_803ECBA4;
typedef GXTexRegion *(*RegionCallback_80194054)(GXTexObj *, GXTexMapID);
static RegionCallback_80194054 lbl_803ECBA8;
extern "C" const char lbl_802EBE14[];
extern "C" const signed char lbl_802AD828[40];

extern "C" {
int fn_800A3444(void);
void fn_80211E08(Element_80194108 *, int);
void fn_80211EFC(Element_80194108 *);
Texture_80194108 *fn_802120E4(Element_80194108 *, int);
Palette_80194108 *fn_80212124(Element_80194108 *, int, int);
void fn_8025090C(Texture_80194108 *, GXTexRegion *);
void fn_8024E450(void);
void fn_80250654(GXTlutObj *, int);
void fn_802503D8(Texture_80194108 *, int);
void fn_8025042C(Texture_80194108 *, GXTexRegion *, int);
void fn_80251604(int, int);
void fn_8024E908(int, int, int);
void fn_8024FB58(int, GXColor);
void fn_8024FC48(int);
void fn_8024FC84(int,int,int,int,int,int,int);
void fn_80251CC4(int);
void fn_80251B28(int,int,int,int);
void fn_8024DF64(int);
void fn_8024DCE4(int,int,int,int,int,int);
void fn_8024D418(void);
void fn_8024CB90(int,int);
void fn_8024D450(int,int,int,int,int);
void fn_802520E0(int,int,int);
void fn_8024EB28(int);
void fn_802528B0(int);
void fn_80252034(int,int,int,int);
void fn_802524D4(float *);
void fn_8024AC28(Mtx44,float,float,float,float,float,float);
void fn_802523A4(Mtx44,int);
void fn_801D03D0(Mtx44);
void fn_8025251C(Mtx44,int);
void fn_802525BC(int);
void fn_801CE720(void);
void fn_801CE774(void);
void fn_802507E0(GXTexRegion *,int,int,int,int);
int fn_801CF6D4(void *,int);
void fn_8025089C(void);
void fn_8024E4F4(void);
void fn_801CEA7C(int);
int fn_801CEA08(void);
int fn_801CEA14(void);
void fn_801CEC48(int,int,int,int);
void fn_801CE22C(void (*)(void));
void fn_801CE23C(void);
void fn_802506EC(GXTexRegion *,int,unsigned int,int,unsigned int,int);
RegionCallback_80194054 fn_802508E4(RegionCallback_80194054);
int fn_801CE930(void);
int fn_801CE944(int);
void GXCopyDisp(int,int);
void fn_8024E4D0(void);
void fn_8024E034(void);

void fn_80194508(int);
void fn_8019471C(void);

int fn_80193FB0(void)
{
    int index = lbl_803EB72C[3];
    int value = fn_800A3444();
    while (lbl_802AD828[index - 4] != value && lbl_802AD828[index - 4] != -1) {
        if (++index > 43) index = 4;
    }
    lbl_803EB72C[3] = index + 1;
    if (lbl_803EB72C[3] > 43) lbl_803EB72C[3] = 4;
    return index;
}
GXTexRegion *fn_80194054(GXTexObj *, GXTexMapID)
{
    return &lbl_80365098;
}
void fn_80194060(void)
{
    if (lbl_803EB72C[1]) {
        lbl_803ECB9C.mX += lbl_803ECBA4;
        if (lbl_803ECB9C.mX < lbl_80364FF4.mUnknown4[0][0] || lbl_803ECB9C.mX + 32.0f > lbl_80364FF4.mUnknown4[1][0]) {
            lbl_803ECBA4 = -lbl_803ECBA4;
            lbl_803ECB9C.mX += 2.0f * lbl_803ECBA4;
        }
        fn_80194508(128);
        fn_8019471C();
        GXCopyDisp(fn_801CE944((unsigned char)fn_801CE930()), 1);
        fn_8024E4D0();
        fn_8024E034();
    }
}
void fn_80194108(int index, Texture_80194108 *out, int region)
{
    Element_80194108 element;
    fn_80211E08(&element, fn_801EF390(lbl_803EB728, index, 1));
    Texture_80194108 *texture = fn_802120E4(&element, 0xFF000000);
    Palette_80194108 *palette = fn_80212124(&element, 0xFF000000, 0);
    out->mUnknown54 = &lbl_80365038[region];
    fn_8025090C(texture, out->mUnknown54);
    fn_8024E450();
    if (palette) {
        fn_80250654(&palette->mUnknown4, region + 4);
        fn_802503D8(texture, region + 4);
    }
    memcpy(out, texture, 0x2C);
    fn_80211EFC(&element);
    fn_801F010C(lbl_803EB728, index);
}
void fn_80194248(Texture_80194108 *) {}
void fn_8019424C(Quad_8019424C *quad, float x, float y)
{
    quad->mUnknown24[3][0] = x;
    quad->mUnknown24[3][1] = y;
    quad->mUnknown24[2][0] = 0.0f;
    quad->mUnknown24[0][0] = 0.0f;
    quad->mUnknown24[0][1] = 0.0f;
    quad->mUnknown24[1][0] = x;
    quad->mUnknown24[1][1] = 0.0f;
    quad->mUnknown24[2][1] = y;
}
void fn_80194278(Quad_8019424C *quad, Texture_80194108 *texture) { quad->mUnknown0 = texture; }
void fn_80194280(Quad_8019424C *quad, int, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    quad->mUnknown4[2][0] = quad->mUnknown4[0][0] = (float)x;
    quad->mUnknown4[1][1] = quad->mUnknown4[0][1] = (float)y;
    quad->mUnknown4[3][0] = quad->mUnknown4[1][0] = (float)width;
    quad->mUnknown4[3][1] = quad->mUnknown4[2][1] = (float)height;
}
void fn_80194314(Quad_8019424C *quad)
{
    if (quad->mUnknown0) {
        fn_8025042C(quad->mUnknown0, quad->mUnknown0->mUnknown54, 0);
        fn_80251604(0, 0);
    } else {
        fn_80251604(0, 4);
    }
    fn_8024E908(0x98, 0, 4);
    for (int i = 0; i < 4; ++i) {
        GXPosition3f32(quad->mUnknown4[i][0], quad->mUnknown4[i][1], -1.5f);
        GXTexCoord2f32(quad->mUnknown24[i][0], quad->mUnknown24[i][1]);
    }
}
void fn_801943D4(void)
{
    GXColor color = {255, 0, 0, 255};
    fn_8024FB58(4, color);
    fn_8025042C(lbl_80364FB0.mUnknown0, lbl_80364FB0.mUnknown0->mUnknown54, 0);
    fn_80251604(0, 4);
    fn_8024E908(0x98, 0, 4);
    float x = lbl_803ECB9C.mX;
    float y = lbl_803ECB9C.mY;
    GXPosition3f32(x, y, -1.5f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(x + 32.0f, y, -1.5f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(x, y + 32.0f, -1.5f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(x + 32.0f, y + 32.0f, -1.5f);
    GXTexCoord2f32(1.0f, 1.0f);
    color.r = color.g = color.b = color.a = 255;
    fn_8024FB58(4, color);
}
void fn_80194508(int alpha)
{
    GXColor color = {255,255,255,(unsigned char)(alpha * 2 - 1)};
    fn_8024FC48(1);
    fn_8024FB58(4, color);
    fn_8024FC84(4,0,0,0,1,0,2);
    fn_80251CC4(1);
    fn_80251B28(0,0,0,4);
    fn_80251604(0,0);
    fn_8024DF64(1);
    fn_8024DCE4(0,0,4,60,0,125);
    fn_8024D418();
    fn_8024CB90(9,1);
    fn_8024CB90(13,1);
    fn_8024D450(0,9,1,4,0);
    fn_8024D450(0,13,1,4,0);
    fn_802520E0(0,7,0);
    fn_8024EB28(0);
    fn_802528B0(1);
    fn_80252034(1,4,5,5);
    fn_802524D4(lbl_80365058[0]);
    Mtx44 projection;
    fn_8024AC28(projection, 0.0f, 480.0f, 0.0f, 640.0f, 1.0f, 2.0f);
    fn_802523A4(projection,1);
    Mtx44 view;
    fn_801D03D0(view);
    fn_8025251C(view,0);
    fn_802525BC(0);
}
void fn_801946C4(void)
{
    fn_80252034(0,0,0,5);
    fn_802523A4(lbl_80365058,0);
    fn_802520E0(1,3,1);
    fn_802528B0(0);
}
void fn_8019471C(void)
{
    if (lbl_803EB72C[1]) fn_801943D4();
    fn_80194314(&lbl_80364FB0);
}
void fn_80194754(int, int alpha)
{
    fn_801CE720();
    fn_80194508(alpha);
    fn_8019471C();
    fn_801946C4();
    fn_801CE774();
}
void fn_80194794(void)
{
    fn_8019424C(&lbl_80364FB0,1.0f,1.0f);
    fn_8019424C(&lbl_80364FF4,1.0f,1.0f);
    fn_802507E0(&lbl_80365038[0],0,0x60000,0,0);
    fn_802507E0(&lbl_80365038[1],0x60000,0x20000,0,0);
    void *p = fn_801CF5BC(0,fn_801CF7AC());
    lbl_803EB72C[2] = fn_801CF6D4(p,2);
    lbl_803EB72C[3] = fn_801CF6D4(p,40) + 4;
    fn_801CF67C(p);
}
void fn_80194858(int mode)
{
    lbl_803EB728 = fn_801EEB44(lbl_802EBE14,44);
    fn_8025089C();
    fn_8024E4F4();
    fn_801CEA7C(0);
    lbl_803EB72C[1] = 0;
    switch (mode) {
    case 1:
        fn_80194108(0,&lbl_80364F58,0);
        fn_80194278(&lbl_80364FB0,&lbl_80364F58);
        fn_80194280(&lbl_80364FB0,0,0,0,640,480);
        fn_80194280(&lbl_80364FF4,0,17,432,273,464);
        break;
    case 4: {
        int index = lbl_803EB72C[2] + 1;
        lbl_803EB72C[2] = index;
        if (lbl_803EB72C[2] == 2) lbl_803EB72C[2] = 0;
        if (fn_8007F828(6) == 1) {
            int a = fn_801CEA08();
            int b = fn_801CEA14();
            fn_801CEC48(0,a,0,b);
        }
        fn_80194108(index,&lbl_80364F58,0);
        fn_80194278(&lbl_80364FB0,&lbl_80364F58);
        fn_80194280(&lbl_80364FB0,0,0,0,640,480);
        fn_80194280(&lbl_80364FF4,0,17,432,273,464);
        break;
    }
    case 2: case 3: {
        int a = fn_801CEA08();
        int b = fn_801CEA14();
        fn_801CEC48(0,a,0,b);
        fn_80194108(fn_80193FB0(),&lbl_80364F58,0);
        fn_80194278(&lbl_80364FB0,&lbl_80364F58);
        fn_80194280(&lbl_80364FB0,0,0,0,640,480);
        fn_80194280(&lbl_80364FF4,0,17,432,273,464);
        break;
    }
    case 5:
        fn_80194278(&lbl_80364FB0,&lbl_80364F58);
        fn_80194280(&lbl_80364FB0,0,0,0,640,480);
        break;
    }
    fn_801EEFAC(lbl_803EB728);
    lbl_803EB728 = 0;
    if (mode != 5) {
        lbl_803ECBA4 = 6.0f;
        lbl_803ECB9C.mX = lbl_80364FF4.mUnknown4[0][0];
        lbl_803ECB9C.mY = lbl_80364FF4.mUnknown4[0][1];
        lbl_803EB72C[1] = 1;
    }
    fn_80194754(mode,128);
    fn_80194508(128);
    fn_801CE22C(fn_80194060);
    fn_802506EC(&lbl_80365098,0,0x80000,1,0x80000,1);
    lbl_803ECBA8 = fn_802508E4(fn_80194054);
    lbl_803EB72C[0] = mode;
}
void fn_80194AEC(int a)
{
    VIWaitForRetrace();
    fn_801CE23C();
    fn_80194508(128);
    fn_8019471C();
    GXCopyDisp(fn_801CE944((unsigned char)fn_801CE930()),a);
    fn_8024E4D0();
    fn_8024E034();
    fn_801946C4();
    fn_801CEA7C(1);
    fn_80194248(&lbl_80364F58);
    fn_802508E4(lbl_803ECBA8);
    lbl_803EB72C[0] = 0;
}
const signed char lbl_802AD828[40] = {
-1,2,-1,-1,0,-1,-1,11,-1,-1,-1,-1,4,-1,-1,-1,
-1,9,-1,-1,-1,-1,1,-1,2,-1,-1,-1,-1,-1,4,-1,
9,9,-1,6,-1,-1,-1,8
};
}
