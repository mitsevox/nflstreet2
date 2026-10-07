#include "game/fn_8022781C.h"
#include "game/fn_80177FE0.h"
#include "game/State_80167094.h"
#include "game/Object_8017886C.h"
#include "game/Object_80039F5C.h"
#include "game/fn_80178D18.h"
#include "game/fn_801EF390.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>

struct QuadPoint_801A0614 { float mX, mY; char mUnknown8[8]; };
struct Resource_801A1240 { char mUnknown0[40]; };
struct Palette_801A0088 { char mUnknown0[4]; GXTlutObj mUnknown4; };
struct Entry_801A0088 { GXTexObj *mpTexture; Palette_801A0088 *mpPalette; };
struct Descriptor_801A1240 { char mUnknown0[12]; short mUnknownC; };

static const char *lbl_802F2734[8] = {"PLYR", "PLTR", "TBAR", "ARRW", "ZONE", "TILE", "DASH", "FLD"};
static Resource_801A1240 lbl_8036550C;
static Entry_801A0088 lbl_80365534[8];

extern "C" {
extern Point_80167094 lbl_802F2754[4];
extern Point_80167094 lbl_802F2774[4][4];
extern Point_80167094 lbl_802F27F4[5][4];
extern QuadPoint_801A0614 lbl_802F2894[4];
extern Mtx44 lbl_802F28F4;
extern unsigned char lbl_803EB7DC[];
int fn_800BA6F8(void);
int fn_80027DF0(void);
int fn_80177F70(void);
float fn_80178298(void);
float fn_80178A2C(void);
int fn_80178308(void);
int fn_80178320(void);
void fn_801D0470(int);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0664(Mtx44);
void fn_801D0C58(float *);
void fn_801D0D94(float, float, float);
void fn_801D0F80(Mtx44);
void fn_80210388(void);
void fn_80211E08(Resource_801A1240 *, int);
void fn_80211EFC(Resource_801A1240 *);
Descriptor_801A1240 *fn_802120AC(Resource_801A1240 *, const char *);
Palette_801A0088 *fn_80212074(Descriptor_801A1240 *, int);
GXTexObj *fn_80212050(Descriptor_801A1240 *);
int fn_80228668(void);
void fn_8024D418(void);
void fn_8024CB90(int, int);
void fn_8024FC48(int);
void fn_8024FC84(int, int, int, int, int, int, int);
void fn_8024FA68(int, GXColor *);
void fn_80251CC4(int);
void fn_80251604(int, int);
void fn_8024DF64(int);
void fn_8024DCE4(int, int, int, int, int, int);
void fn_8024EB28(int);
void fn_8024D450(int, int, int, int, int);
void fn_80252114(int);
void fn_802520E0(int, int, int);
void fn_80251A58(int, int, int, int, int);
void fn_80251B28(int, int, int, int);
extern "C" void GXInitTexObjTlut(GXTexObj *, int);
extern "C" void GXLoadTlut(GXTlutObj *, int);
extern "C" void GXLoadTexObj(GXTexObj *, int);
void fn_8025251C(Mtx44, int);
void fn_80252034(int, int, int, int);
}

extern "C" int fn_801A0088(int)
{
    fn_80251CC4(1);
    Entry_801A0088 *p = lbl_80365534;
    for (unsigned int i = 0; i <= 7; ++i, ++p) {
        if (p->mpPalette) { GXInitTexObjTlut(p->mpTexture, i); GXLoadTlut(&p->mpPalette->mUnknown4, i); }
        GXLoadTexObj(p->mpTexture, i);
    }
    return 0;
}
extern "C" int fn_801A0108(int, Point_80167094 *p, QuadPoint_801A0614 *uv, GXColor *c)
{
    float z = 0.0f;
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    GXPosition3f32(p[0].mX, p[0].mY, z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[0].mX,uv[0].mY);
    GXPosition3f32(p[1].mX, p[1].mY, z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[1].mX,uv[1].mY);
    GXPosition3f32(p[2].mX, p[2].mY, z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[2].mX,uv[2].mY);
    GXPosition3f32(p[3].mX, p[3].mY, z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[3].mX,uv[3].mY);
    return 0;
}
extern "C" int fn_801A0270(int, Point_80167094 *p, QuadPoint_801A0614 *uv, GXColor *c)
{
    float z = 0.0f;
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    GXPosition3f32(p[0].mX,p[0].mY,z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[0].mX,z);
    GXPosition3f32(p[1].mX,p[1].mY,z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[1].mX,z);
    float length = fn_8022781C(&p[0],&p[2]) * 0.09f;
    GXPosition3f32(p[2].mX,p[2].mY,z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[2].mX,length);
    GXPosition3f32(p[3].mX,p[3].mY,z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[3].mX,length);
    return 0;
}
extern "C" int fn_801A03E4(int, Point_80167094 *p, QuadPoint_801A0614 *uv, unsigned int count, GXColor *c)
{
    unsigned int i = 0;
    while (i < count) {
        if (i > 1) i -= 2;
        int n = count - i; if (n > 16) n = 16;
        GXBegin(GX_TRIANGLESTRIP,GX_VTXFMT0,(unsigned short)n);
        Point_80167094 *current = p+i;
        while (n > 0) {
            unsigned int j = i & 3;
            GXPosition3f32(current->mX,current->mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[j].mX,uv[j].mY);
            ++i; ++current; --n;
        }
    }
    return 0;
}
extern "C" int fn_801A04D4(int, Point_80167094 *p, QuadPoint_801A0614 *uv, unsigned int count, GXColor *c)
{
    unsigned int i = 0; float length = 0.0f;
    while (i < count) {
        if (i > 1) i -= 2;
        int n = count - i; if (n > 16) n = 16;
        GXBegin(GX_TRIANGLESTRIP,GX_VTXFMT0,(unsigned short)n);
        Point_80167094 *current = p+i;
        while (n > 0) {
            unsigned int j = i & 3;
            if (j == 2) length += fn_8022781C(&p[i-2],&p[i]) * 0.09f;
            GXPosition3f32(current->mX,current->mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[j].mX,length);
            ++i; ++current; --n;
        }
    }
    return 0;
}
extern "C" int fn_801A0614(int, QuadPoint_801A0614 *p, Point_80167094 *uv, GXColor *c, int texture)
{
    fn_80251B28(0,0,texture,4);
    GXBegin(GX_TRIANGLESTRIP,GX_VTXFMT0,4);
    GXPosition3f32(p[0].mX,p[0].mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[0].mX,uv[0].mY);
    GXPosition3f32(p[1].mX,p[1].mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[1].mX,uv[1].mY);
    GXPosition3f32(p[2].mX,p[2].mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[2].mX,uv[2].mY);
    GXPosition3f32(p[3].mX,p[3].mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[3].mX,uv[3].mY);
    return 0;
}
extern "C" int fn_801A0788(int a,QuadPoint_801A0614 *p,Point_80167094 *uv,GXColor *c,int texture)
{
    return fn_801A0614(a,p,uv,c,texture);
}
extern "C" int fn_801A07A8(int a,Point_8017886C *)
{
    QuadPoint_801A0614 p[4];
    Point_80167094 uv[4];
    uv[0].mX=0.0f;uv[0].mY=0.0f;uv[1].mX=0.0f;uv[1].mY=1.0f;
    uv[2].mX=1.0f;uv[2].mY=0.0f;uv[3].mX=1.0f;uv[3].mY=1.0f;
    GXColor c; c.r=255;c.a=255;c.g=255;c.b=255;
    p[0].mX = 0.0f; p[0].mY = 0.0f;
    p[1].mX = 0.0f; p[1].mY = 100.0f;
    p[2].mX = 120.0f; p[2].mY = 0.0f;
    p[3].mX = 120.0f; p[3].mY = 100.0f;
    return fn_801A0788(a,p,uv,&c,7);
}
extern "C" int fn_801A085C(int a,State_80167094 *s,int)
{
    int team = s->mUnknown2083 ? fn_80178308() : fn_80178320();
    int count = fn_80178D70(team);
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j <= 11; ++j) {
            int kind = s->mUnknown19F0[i][j];
            if (kind) {
                int texture;
                switch (kind) {case 1:texture=2;break;case 3:case 4:case 5:texture=4;break;default:texture=3;break;}
                QuadPoint_801A0614 p[4];
                for (signed char k = 0; k <= 3; ++k) {p[k].mX = s->mUnknown970[i][j][k].mX;p[k].mY = s->mUnknown970[i][j][k].mY;}
                a = fn_801A0614(a,p,lbl_802F2754,&s->mUnknown2020[i],texture);
            }
        }
    }
    return a;
}
extern "C" int fn_801A09B0(int a,State_80167094 *s,int mirror)
{
    int count;
    if (s->mUnknown2083) count = fn_80178D70(fn_80178308()); else count = fn_80178D70(fn_80178320());
    for (int i = 0; i < count; ++i) {
        int kind = s->mUnknown2134[i];
        if (kind <= 5) {
            QuadPoint_801A0614 p[4];
            float x0, x1;
            if (mirror) {x0=120.0f-s->mUnknown2084[i][0];x1=120.0f-s->mUnknown2084[i][2];}
            else {x0=s->mUnknown2084[i][0];x1=s->mUnknown2084[i][2];}
            float y0=s->mUnknown2084[i][1],y1=s->mUnknown2084[i][3];
            p[0].mX=x0;p[0].mY=y0;p[1].mX=x0;p[1].mY=y1;p[2].mX=x1;p[2].mY=y0;p[3].mX=x1;p[3].mY=y1;
            a=fn_801A0614(a,p,lbl_802F2774[lbl_803EB7DC[kind]],&s->mUnknown204C[i],0);
        }
    }
    return a;
}
extern "C" void fn_801A0B1C(int a,State_80167094 *s,int mirror)
{
    for (int i=0;i<s->mUnknown2160;++i) {
        int flag=s->mUnknown21C8[i]; int kind=s->mUnknown2164[i];
        if (!(flag&0x80)) {
            QuadPoint_801A0614 p[4];float x0,x1;
            if (mirror) {x0=120.0f-s->mUnknown2178[i][2];x1=120.0f-s->mUnknown2178[i][0];}
            else {x0=s->mUnknown2178[i][0];x1=s->mUnknown2178[i][2];}
            float y0=s->mUnknown2178[i][1],y1=s->mUnknown2178[i][3];
            int texture;switch(kind){case 0:texture=0;break;case 1:texture=1;break;case 2:texture=2;break;case 3:texture=3;break;default:texture=4;break;}
            p[0].mX=x0;p[0].mY=y0;p[1].mX=x0;p[1].mY=y1;p[2].mX=x1;p[2].mY=y0;p[3].mX=x1;p[3].mY=y1;
            fn_801A0788(a,p,lbl_802F27F4[texture],&s->mUnknown204C[flag],1);
        }
    }
}
extern "C" int fn_801A0CA0(int a,State_80167094 *s,int)
{
    int mode=-1, tiled=0;
    int team=s->mUnknown2083?fn_80178308():fn_80178320();int count=fn_80178D70(team);
    for (int i=0;i<count;++i) {
        int start=s->mUnknown940[i];int n=s->mUnknown940[i+1]-start;
        if (n) {
            int next=s->mUnknown1E10[i][0];
            if(mode!=next){mode=next;if(!mode){tiled=0;fn_80251B28(0,0,5,4);}else{tiled=1;fn_80251B28(0,0,6,4);}}
            Point_80167094 *p=(Point_80167094 *)s+start;
            if(n==4){if(tiled)a=fn_801A0270(a,p,lbl_802F2894,&s->mUnknown2020[i]);else a=fn_801A0108(a,p,lbl_802F2894,&s->mUnknown2020[i]);}
            else {if(tiled)a=fn_801A04D4(a,p,lbl_802F2894,n,&s->mUnknown2020[i]);else a=fn_801A03E4(a,p,lbl_802F2894,n,&s->mUnknown2020[i]);}
        }
    }
    return a;
}
extern "C" void fn_801A0E2C(void)
{
    GXColor c={255,255,255,255},copy;
    fn_80210388();fn_8024D418();fn_8024CB90(9,1);fn_8024CB90(11,1);fn_8024CB90(13,1);fn_8024FC48(1);
    fn_8024FC84(0,1,0,1,0,0,2);fn_8024FC84(2,0,0,1,0,0,2);copy=c;fn_8024FA68(0,&copy);
    fn_80251CC4(1);fn_80251604(0,0);fn_8024DF64(1);fn_8024DCE4(0,0,4,60,0,125);fn_8024EB28(0);
    fn_8024D450(0,9,1,4,0);fn_8024D450(0,11,1,5,0);fn_8024D450(0,13,1,4,0);fn_80252114(1);fn_802520E0(0,7,0);fn_80251A58(4,0,0,4,0);fn_801A0088(0);
}
extern "C" void fn_801A0FAC(int a,State_80167094 *s,unsigned char mirror)
{
    Mtx44 m;fn_801D04C4();if(mirror)fn_801D0664(lbl_802F28F4);fn_801D0F80(m);fn_8025251C(m,0);
    a=fn_801A09B0(a,s,0);a=fn_801A0CA0(a,s,0);a=fn_801A085C(a,s,0);
    fn_801D0544();fn_801D0F80(m);fn_8025251C(m,0);fn_801A0B1C(a,s,mirror);
}
extern "C" void fn_801A105C(float x,float y,void *input,unsigned char mirror)
{
    State_80167094 *s=(State_80167094 *)input;GXColor c={255,255,255,255},copy;float pos[3]={x,y,0.0f};Mtx44 m;
    fn_801A0E2C();Point_8017886C point=fn_80177FE0();
    if(fn_80177F70()!=0&&fn_80177F70()!=6){float v=fn_80178298();if(v<fn_80178A2C()&&!fn_800BA6F8()&&!fn_80027DF0())fn_80178298();}
    copy=c;fn_8024FA68(4,&copy);fn_801D0470(fn_80228668());fn_801D04C4();fn_801D0D94(1.0f,1.0f,0.0f);fn_801D0C58(pos);fn_801D0F80(m);fn_8025251C(m,0);
    fn_80251604(0,3);fn_80252034(0,0,0,5);int a=fn_801A07A8(0,&point);fn_80251604(0,0);fn_80252034(1,4,5,5);
    fn_801D0F80(m);fn_8025251C(m,0);copy=c;fn_8024FA68(4,&copy);fn_801A0FAC(a,s,mirror);fn_80252034(0,0,0,5);fn_801D0544();fn_801D0F80(m);fn_8025251C(m,0);
}
extern "C" void fn_801A1240(int resource)
{
    fn_80211E08(&lbl_8036550C,fn_801EF390((void *)resource,0,1));
    Entry_801A0088 *p=lbl_80365534;
    for(unsigned int i=0;i<=7;++i,++p){Descriptor_801A1240 *d=fn_802120AC(&lbl_8036550C,lbl_802F2734[i]);if(d->mUnknownC)p->mpPalette=fn_80212074(d,0);else p->mpPalette=0;p->mpTexture=fn_80212050(d);}
}
extern "C" void fn_801A12E8(void)
{
    fn_80211EFC(&lbl_8036550C);
    for(int i=7;i>=0;--i){lbl_80365534[i].mpTexture=0;lbl_80365534[i].mpPalette=0;}
}
