#include "game/cu_801A8620.h"
#include "engine/cu_80227F14.h"
#include "engine/vptmanager.h"
#include "game/GameVpt.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8020E52C.h"
#include "game/Object_80233EAC.h"
#include "game/cu_801442FC.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EF390.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"
#include <dolphin/gx/GXStruct.h>
typedef float Mtx44[4][4];
#include <dolphin/os/OSCache.h>
#include <string.h>

struct Texture_801A8D08 { unsigned char mUnknown0[16]; unsigned short mUnknown10; };
struct Mesh_801A93C0 {
    void *mpUnknown0; unsigned short mUnknown4; unsigned char mUnknown6;
    unsigned char mUnknown7; unsigned char mUnknown8; unsigned char mUnknown9;
};
struct MeshData_801A93C0 { unsigned char mUnknown0[0x18]; Mesh_801A93C0 mUnknown18; };
struct MeshRef_801A93C0 { unsigned char mUnknown0[8]; MeshData_801A93C0 *mpUnknown8; };
struct Offset_801A8620 { int mUnknown0; unsigned char *mpUnknown4; };
struct Asset_801A8620;
struct Geometry_801A8620 { Asset_801A8620 *mpUnknown0; unsigned char mUnknown4[0xC]; Offset_801A8620 *mpUnknown10; };
struct ModelData_801A8620 { Asset_801A8620 *mpUnknown0; unsigned char mUnknown4[0x6C]; MeshRef_801A93C0 *mpUnknown70; };
struct Model_801A8620 { unsigned char mUnknown0[8]; ModelData_801A8620 *mpUnknown8; unsigned char mUnknownC[0x10]; int mUnknown1C; };
struct Asset_801A8620 { unsigned char mUnknown0[0x11]; unsigned char mUnknown11; };
struct ModelRef_801A8620 { Geometry_801A8620 *mpUnknown0; };
struct Context_801A8620 { unsigned int mUnknown0; ModelRef_801A8620 *mpUnknown4; };

struct Cache_801A8D9C {
    Asset_801A8620 *mpUnknown0; Context_801A8620 mUnknown4;
    unsigned char mUnknownC[0x2C]; char mUnknown38[0x100];
    int mUnknown138; void *mpUnknown13C; int mUnknown140;
    Texture_801A8D08 *mpUnknown144; void *mpUnknown148; Element_801A8620 mUnknown14C;
};
struct Packet_801A8620 {
    unsigned char mUnknown0[0xC]; Model_801A8620 *mpUnknownC;
    unsigned char mUnknown10[0x4C]; int mUnknown5C;
    unsigned char mUnknown60[4]; MeshRef_801A93C0 *mpUnknown64; unsigned char mUnknown68[0x78]; void *mpUnknownE0;
    unsigned char mUnknownE4[4]; void *mpUnknownE8;
};
struct Instance_801A8D9C {
    Cache_801A8D9C *mpUnknown0; Context_801A8620 mUnknown4;
    Packet_801A8620 mUnknownC; unsigned char mUnknownF8[4];
    unsigned char mUnknownFC[12]; Tracker_801442FC mUnknown108;
};
struct Pose_801A8B84 { unsigned char mUnknown0[8]; Vector_80039F5C mUnknown8; unsigned char mUnknown14[0x4C]; Vector_80039F5C mUnknown60; };
struct Env_801A8D9C { void *mpUnknown0; };
extern "C" {
extern void *lbl_803EA368;
int fn_8002D060(void *);
void fn_801C657C(void);
int fn_801A854C(void *, void *);
void fn_801A7C20(Mesh_801A93C0 *);
void fn_801A7F10(Mesh_801A93C0 *);
void fn_801D0470(int); void fn_801D04C4(void); void fn_801D0508(void);
void fn_801D0544(void); void fn_801D0558(void); void fn_801D06D4(Mtx44);
void fn_801D0C58(void *); void fn_801D0860(void *); void fn_801D08FC(int);
void fn_801D09EC(int); void fn_801D0F80(Mtx44);
void fn_8020FA38(int, void *); void fn_8020FA8C(int);
void fn_8020EBB0(void *); void fn_8020F4D0(void *, void *);
void *fn_8020EC50(void *, unsigned int, int);
void fn_8020F78C(void *, void *); void fn_8020F824(void *, void *);
void fn_8020F8E0(void *); void fn_8020F92C(void *);
void fn_802100C0(void *, void *); void fn_80210114(void *);
void fn_802101B0(void *, int); void fn_8020FDAC(unsigned int, int);
void fn_80210654(Object_8023417C *); void fn_80210724(void *);
void fn_80210814(int, int, unsigned char *);
void fn_80210BA4(void *); void fn_80210BD8(int);
void fn_8021126C(void); void fn_802112DC(void *, int); void fn_80211350(void);
void fn_80211E08(Element_801A8620 *, int); void fn_80211EFC(Element_801A8620 *);
void fn_80211FF0(void); void fn_80212018(const char *, Element_801A8620 *);
int fn_80212124(Element_801A8620 *, unsigned int, int);
void fn_80233BB8(void *, int, int); void fn_80233BDC(void *, void *); void fn_80233BD8(void *);
void fn_80233CBC(void *, int, int); void fn_802337D4(void *, void *, int, int);
void fn_80234A30(Packet_801A8620 *, int); void fn_80234A90(Packet_801A8620 *);
void fn_80234A94(Packet_801A8620 *, Context_801A8620 *);
void fn_80234AFC(void *); void fn_80234B1C(void *); void fn_80234B20(void *, void *, int);
void fn_80234B80(void *); void fn_80234DC4(void *, int); void fn_80234DC8(void *, unsigned int);
void fn_80234B88(Packet_801A8620 *); void fn_80234BF4(void *, Packet_801A8620 *, int);
void fn_80234CA4(Packet_801A8620 *, void *); void fn_80234CF0(Packet_801A8620 *, int, Context_801A8620 *);
void fn_80234DC0(Packet_801A8620 *, int); unsigned int fn_80234D4C(float *, void *, void *, void *);
void fn_80227C2C(void *, void *); void fn_802271F0(void *, void *); float fn_80227704(void *, void *);
int fn_8004D5B8(int, const char *, char *, int); void fn_8004D498(int);
int fn_8004D4B0(int, const char *); int fn_8004D508(int, const char *);
void fn_8004E090(Object_801A8620 *, int, int);
int fn_801F0A8C(void *, const char *); char *fn_801C310C(char *, const char *);
void fn_8024FB58(int, GXColor); void fn_8024FC48(int); void fn_8024FC84(int, int, int, int, int, int, int);
void fn_80251A58(int, int, int, int, int); void fn_80252114(int); void fn_802520E0(int, int, int);
void fn_8024EB28(int); void fn_8024DF64(int); void fn_80251CC4(int); void fn_80251B28(int, int, int, int);
void fn_802525BC(int); void fn_8025251C(Mtx44, int); void fn_8025256C(Mtx44, int);
int fn_801A8B84(Object_801A8620 *); int fn_801A8C48(Child_801A9430 *);
int fn_801A9430(Child_801A9430 *, int);
}

static float lbl_802F3B20[8] = {-3.1f,-1.5f,-2.0f,0.0f,3.9f,1.5f,5.0f,0.0f};
static Cache_801A8D9C *lbl_803673E0[104];
static unsigned int lbl_803EB870 = 0;

extern "C" {
int fn_801A8620(Object_801A8620 *p, int arg)
{
    GXColor color = {255,255,255,255}; GXColor copy;
    Mtx44 m1, m2; unsigned char work[0x90]; Vector_80039F5C delta;
    Instance_801A8D9C *s = p->mpUnknown12C;
    Model_801A8620 *model = s->mUnknownC.mpUnknownC;
    fn_801C657C();
    int value = fn_801A854C(&s->mUnknown108,p->mpUnknown14C);
    copy=color; fn_8024FB58(0,copy); fn_8024FC48(1);
    fn_8024FC84(0,1,0,0,value,2,2); fn_8024FC84(2,0,0,0,value,0,2);
    fn_80251A58(6,16,0,7,0); fn_80252114(0); fn_802520E0(1,3,1); fn_8024EB28(1);
    fn_80210BD8(2); fn_801D0470(fn_80228668()); fn_801D04C4(); fn_801D0508();
    fn_801D0C58(&p->mUnknown4); fn_801D0860(&p->mUnknown18); fn_801D08FC(0x400000);
    fn_801D0C58(&p->mUnknownB4); fn_801D09EC(p->mUnknownCC); fn_801D0F80(m1);
    fn_801D0544(); fn_801D0C58(&p->mUnknown4); fn_801D0860(&p->mUnknown18);
    fn_801D08FC(0x400000); fn_801D0C58(&p->mUnknownB4); fn_801D09EC(p->mUnknownCC);
    fn_801D0F80(m2); fn_8020FA38(0,m2); fn_8020FA8C(0);
    unsigned int flags=fn_80234D4C(lbl_802F3B20,m1,0,0);
    if(fn_801A8B84(p)) flags|=0x3F;
    p->mUnknown138=0;
    if(!(flags&0x3F)) {
        fn_80234AFC(work); fn_80234DC8(work,flags&0xF2000); fn_80234B1C(work);
        fn_80234B20(work,m1,0); fn_80234B80(work); fn_80234DC4(work,0);
        if(!fn_8002D060(lbl_803EA368)) fn_80233CBC(&s->mUnknownC.mUnknown10[4],0,p->mUnknown13C);
        if(p->mUnknown140) {
            void *viewport=fn_8002B550(GameVpt::fn_800293A8());
            fn_802276B4(&delta,&p->mUnknown4,static_cast<unsigned char *>(viewport)+4);
            float distance=fn_802270D4(&delta);
            if(distance>10.0f) {
                if(distance>25.0f) color.a=0;
                else color.a=(unsigned char)((float)(unsigned int)color.a*(1.0f-(distance-10.0f)*0.06666667f));
            } else color.a=255;
            copy=color; fn_8024FB58(4,copy);
        }
        s->mUnknownC.mUnknown5C=1;
        unsigned int enabled=fn_8002D060(lbl_803EA368)?(p->mUnknownE8.mBytes[3]&4):(p->mUnknownE8.mBytes[3]&1);
        if(enabled) {
            if(p->mpUnknown130) {
                if(model->mpUnknown8->mpUnknown0->mUnknown11&8) {
                    fn_80210BA4(s->mUnknownC.mpUnknownE8); fn_80234B88(&s->mUnknownC);
                    if(!p->mUnknown138) {
                        p->mUnknown138=1;
                        if(!model->mUnknown1C) fn_8020F8E0(model);
                        fn_80210654(reinterpret_cast<Object_8023417C *>(model));
                        fn_80210724(s->mUnknownC.mpUnknownE0); fn_801D04C4(); fn_801D0558();
                        fn_802337D4(model,s->mUnknownFC,p->mUnknownDC,0);
                        fn_801D0544(); fn_8021126C();
                    }
                    fn_802525BC(0);fn_8025251C(m2,0);fn_8025256C(m2,0);
                    fn_8024DF64(1);fn_80251CC4(1);fn_80251B28(0,0,0,4);
                    if(p->mUnknownE8.mWord&16) {
                        ModelRef_801A8620 *r=s->mUnknown4.mpUnknown4;
                        r->mpUnknown0->mpUnknown10->mpUnknown4+=p->mUnknownFC*40;
                        fn_80211350();
                        r=s->mUnknown4.mpUnknown4;
                        r->mpUnknown0->mpUnknown10->mpUnknown4-=p->mUnknownFC*40;
                    } else fn_802112DC(s->mUnknownC.mUnknown60,s->mUnknownC.mUnknown5C);
                } else {
                    p->mUnknown138=1;fn_802337D4(model,s->mUnknownFC,p->mUnknownDC,0);
                    fn_80234BF4(work,&s->mUnknownC,0);
                }
            } else fn_80234BF4(work,&s->mUnknownC,0);
        }
    }
    fn_801D0544(); if(p->mpUnknown1E0)fn_801A9430(p->mpUnknown1E0,arg);
    fn_8024EB28(0); return 0;
}
int fn_801A8B0C(const char *name)
{
    for(int i=0;i<(int)lbl_803EB870;i++) if(!strcmp(name,lbl_803673E0[i]->mUnknown38))return i;
    return -1;
}
static const Vector_80039F5C lbl_802AE8F8={0.0f,1.0f,0.0f};
int fn_801A8B84(Object_801A8620 *p)
{
    int result=0;
    if(p->mUnknownE8.mWord&16) {
        Vector_80039F5C delta,axis=lbl_802AE8F8;
        void *viewport=fn_8002B550(0);fn_801D0508();fn_801D0860(&p->mpUnknown1D8->mUnknown60);
        fn_80227C2C(&axis,&axis);fn_801D0544();
        fn_802276B4(&delta,&p->mpUnknown1D8->mUnknown8,static_cast<unsigned char *>(viewport)+4);
        fn_802271F0(&delta,&delta);result=fn_80227704(&delta,&axis)<-0.2f;
    }
    return result;
}
int fn_801A8C48(Child_801A9430 *p)
{
    int result=0;
    if(p->mpUnknown50->mUnknownE8.mWord&16) {
        Vector_80039F5C delta,axis=lbl_802AE8F8;
        void *viewport=fn_8002B550(0);fn_801D0508();fn_801D0860(&p->mUnknown3C);
        fn_80227C2C(&axis,&axis);fn_801D0544();
        fn_802276B4(&delta,&p->mUnknown30,static_cast<unsigned char *>(viewport)+4);
        fn_802271F0(&delta,&delta);result=fn_80227704(&delta,&axis)<-0.2f;
    }
    return result;
}
void fn_801A8D08(Child_801A9430 *p,Object_801A8620 *owner)
{
    Cache_801A8D9C *resource=owner->mpUnknown12C->mpUnknown0;
    unsigned int index=fn_802372EC(1,resource->mpUnknown144->mUnknown10);
    p->mUnknown6C=index;
    if((unsigned char)index==owner->mUnknownFC && resource->mpUnknown144->mUnknown10>1) {
        p->mUnknown6C=index+1;
        if(p->mUnknown6C>=resource->mpUnknown144->mUnknown10) p->mUnknown6C=index-1;
    }
}
void fn_801A8D9C(void *data,int handle,Object_801A8620 *p)
{
    char name[256],behavior[128];
    fn_8004D5B8(handle,"tideRef",name,256);
    int index=fn_801A8B0C(name),hasBehavior=0;
    p->mpUnknown12C=static_cast<Instance_801A8D9C *>(fn_801D2B7C(0x110,0,0));
    fn_801C1F94(p->mpUnknown12C,0,0x110);
    Instance_801A8D9C *s=p->mpUnknown12C;Env_801A8D9C *env=p->mpUnknown130;
    fn_8004D498(handle);fn_8004D4B0(handle,"render");
    if(fn_8004D508(handle,"clut"))hasBehavior=fn_8004D5B8(handle,"tideRef",behavior,128);
    if(index!=-1) {s->mpUnknown0=lbl_803673E0[index];s->mpUnknown0->mUnknown138++;}
    else {
        lbl_803673E0[lbl_803EB870]=static_cast<Cache_801A8D9C *>(fn_801D2B7C(0x174,0,0));
        fn_801C1F94(lbl_803673E0[lbl_803EB870],0,0x174);
        s->mpUnknown0=lbl_803673E0[lbl_803EB870++];s->mpUnknown0->mUnknown138=1;
        strcpy(s->mpUnknown0->mUnknown38,name);s->mpUnknown0->mpUnknown13C=data;
        s->mpUnknown0->mUnknown140=fn_801F0A8C(data,name);
        s->mpUnknown0->mpUnknown0=reinterpret_cast<Asset_801A8620 *>(fn_801EF390(data,s->mpUnknown0->mUnknown140,1));
        if(s->mpUnknown0->mpUnknown0) {
            fn_8020EBB0(s->mpUnknown0->mpUnknown0);
            fn_8020F4D0(&s->mpUnknown0->mUnknown4,s->mpUnknown0->mpUnknown0);
            if(!hasBehavior || !strcmp(behavior,"CUSTOM_BEHAVIOR")) {
                s->mpUnknown0->mpUnknown144=static_cast<Texture_801A8D08 *>(fn_8020EC50(s->mpUnknown0->mpUnknown0,0x54657874,0));
                p->mUnknownFC=0;
            } else {
                p->mUnknownF4=fn_801F0A8C(data,behavior);
                s->mpUnknown0->mpUnknown144=reinterpret_cast<Texture_801A8D08 *>(fn_801EF390(data,p->mUnknownF4,1));
                p->mUnknownFC=fn_802372EC(1,s->mpUnknown0->mpUnknown144->mUnknown10);
            }
            if(s->mpUnknown0->mpUnknown144)fn_80211E08(&s->mpUnknown0->mUnknown14C,reinterpret_cast<int>(s->mpUnknown0->mpUnknown144));
            s->mpUnknown0->mpUnknown148=fn_8020EC50(s->mpUnknown0->mpUnknown0,0x4D61746C,0);
            fn_8020F78C(&s->mpUnknown0->mUnknown4,s->mpUnknown0->mpUnknown148);
        }
    }
    fn_80211FF0();fn_80212018("model",&s->mpUnknown0->mUnknown14C);
    fn_802100C0(&s->mUnknown4,s->mpUnknown0->mpUnknown148);fn_80211FF0();
    fn_80234A30(&s->mUnknownC,fn_801C310C(p->mUnknown158,"CROWDGROUP")?0x80:0x40);
    fn_80234CF0(&s->mUnknownC,0,&s->mUnknown4);fn_80234DC0(&s->mUnknownC,8);
    fn_80234A94(&s->mUnknownC,&s->mpUnknown0->mUnknown4);
    if(env) {
        fn_8020F824(&s->mpUnknown0->mUnknown4,env->mpUnknown0);
        fn_80233BB8(s->mUnknownFC,0x100,1);fn_80233BDC(s->mUnknownFC,env->mpUnknown0);
        fn_80234CA4(&s->mUnknownC,s->mUnknownFC);
    } else fn_80233BB8(s->mUnknownFC,0,1);
    fn_8004E090(p,0,0);p->mUnknownE8.mWord=1;
    if(fn_8004D5B8(handle,"tideEnvMapRef",name,256))p->mUnknownE8.mWord=2;
    p->mUnknown14=fn_801A8620;fn_801442FC(&s->mUnknown108);
}
void fn_801A9184(Object_801A8620 *p)
{
    Instance_801A8D9C *s=p->mpUnknown12C;
    fn_80210114(&s->mUnknown4);fn_80233BD8(s->mUnknownFC);fn_80234A90(&s->mUnknownC);
    if(s->mUnknownC.mpUnknownC->mUnknown1C)fn_8020F92C(s->mUnknownC.mpUnknownC);
    s->mpUnknown0->mUnknown138--;
    if(s->mpUnknown0->mUnknown138<=0) {
        fn_80211EFC(&s->mpUnknown0->mUnknown14C);
        fn_801F010C(s->mpUnknown0->mpUnknown13C,s->mpUnknown0->mUnknown140);
    }
    fn_801D2BD0(s);p->mpUnknown12C=0;
}
void fn_801A9224(void) {lbl_803EB870=0;fn_801C1F94(lbl_803673E0,0,sizeof(lbl_803673E0));}
void fn_801A925C(void)
{
    for(unsigned int i=0;i<lbl_803EB870;i++)fn_801D2BD0(lbl_803673E0[i]);
    fn_801C1F94(lbl_803673E0,0,sizeof(lbl_803673E0));lbl_803EB870=0;
}
void fn_801A92D0(void *data,Object_801A8620 *p)
{
    p->mpUnknown100=reinterpret_cast<Texture_801A8D08 *>(fn_801EF390(data,p->mUnknownF4,1));
    fn_8020E2B0(p->mpUnknown100);fn_80211FF0();
    fn_80211E08(&p->mUnknown104,reinterpret_cast<int>(p->mpUnknown100));
    p->mUnknownF8=p->mpUnknown100->mUnknown10;
}
void fn_801A932C(Object_801A8620 *p)
{
    fn_80211EFC(&p->mUnknown104);
    fn_801F010C(p->mpUnknownA8,p->mUnknownF4);
}
void fn_801A9368(Object_801A8620 *p,int index)
{
    Instance_801A8D9C *s=p->mpUnknown12C;
    int palette=fn_80212124(&p->mUnknown104,0xFF000000,index);
    fn_802101B0(&s->mUnknownC.mUnknown10[0x44],0);fn_8020FDAC(0xFF000000,palette);
}
void fn_801A93C0(Object_801A8620 *p)
{
    Mesh_801A93C0 *mesh=&p->mpUnknown12C->mUnknownC.mpUnknown64->mpUnknown8->mUnknown18;
    if(mesh->mUnknown9==4)fn_801A7C20(mesh);else if(mesh->mUnknown9==3)fn_801A7F10(mesh);
    DCFlushRange(mesh->mpUnknown0,mesh->mUnknown4*mesh->mUnknown7);
}
int fn_801A9430(Child_801A9430 *p,int arg)
{
    GXColor color={255,255,255,255},copy;Mtx44 m1,m2;unsigned char work[0x90];
    Instance_801A8D9C *s=p->mpUnknown50->mpUnknown12C;Model_801A8620 *model=s->mUnknownC.mpUnknownC;
    fn_801C657C();int value=fn_801A854C(&p->mUnknown60,p->mpUnknown58);
    copy=color;fn_8024FB58(0,copy);fn_8024FC48(1);
    fn_8024FC84(0,1,0,0,value,2,2);fn_8024FC84(2,0,0,0,value,0,2);
    fn_801D0470(fn_80228668());fn_801D0508();
    fn_801D0C58(&p->mUnknown30);fn_801D0860(&p->mUnknown3C);fn_801D08FC(0x400000);
    fn_801D0C58(&p->mpUnknown50->mUnknownB4);fn_801D09EC(p->mpUnknown50->mUnknownCC);fn_801D0F80(m1);
    fn_801D0544();fn_801D04C4();fn_801D0C58(&p->mUnknown30);fn_801D0860(&p->mUnknown3C);
    fn_801D08FC(0x400000);fn_801D0C58(&p->mpUnknown50->mUnknownB4);fn_801D09EC(p->mpUnknown50->mUnknownCC);fn_801D0F80(m2);
    unsigned int flags=fn_80234D4C(lbl_802F3B20,m1,0,0);if(fn_801A8C48(p))flags|=0x3F;
    if(!(flags&0x3F)) {
        fn_80234AFC(work);fn_80234DC8(work,flags&0xF2000);fn_80234B1C(work);fn_80234B20(work,m1,0);
        fn_80234B80(work);fn_80234DC4(work,0);s->mUnknownC.mUnknown5C=1;
        unsigned int enabled=fn_8002D060(lbl_803EA368)?(p->mpUnknown50->mUnknownE8.mBytes[3]&4):(p->mpUnknown50->mUnknownE8.mBytes[3]&1);
        if(enabled) {
            if(model->mpUnknown8->mpUnknown0->mUnknown11&8) {
                fn_80234B88(&s->mUnknownC);fn_80210BA4(s->mUnknownC.mpUnknownE8);
                if(!p->mpUnknown50->mUnknown138) {
                    p->mpUnknown50->mUnknown138=1;
                    if(!model->mUnknown1C)fn_8020F8E0(model);
                    fn_80210654(reinterpret_cast<Object_8023417C *>(model));fn_80210724(s->mUnknownC.mpUnknownE0);
                    fn_801D04C4();fn_801D0558();fn_802337D4(model,s->mUnknownFC,p->mpUnknown50->mUnknownDC,0);
                    fn_801D0544();fn_8021126C();fn_8024DF64(1);fn_80251CC4(1);fn_80251B28(0,0,0,4);
                }
                fn_802525BC(0);fn_8025251C(m2,0);fn_8025256C(m2,0);
                if(p->mpUnknown50->mUnknownE8.mWord&16) {
                    ModelRef_801A8620 *r=s->mUnknown4.mpUnknown4;
                    r->mpUnknown0->mpUnknown10->mpUnknown4+=p->mUnknown6C*40;
                    r=s->mUnknown4.mpUnknown4;
                    fn_80210814(0,r->mpUnknown0->mpUnknown10->mUnknown0,r->mpUnknown0->mpUnknown10->mpUnknown4);
                    fn_80211350();r=s->mUnknown4.mpUnknown4;
                    r->mpUnknown0->mpUnknown10->mpUnknown4-=p->mUnknown6C*40;
                } else fn_802112DC(s->mUnknownC.mUnknown60,s->mUnknownC.mUnknown5C);
            } else {
                if(!p->mpUnknown50->mUnknown138) {
                    fn_801D06D4(m2);p->mpUnknown50->mUnknown138=1;
                    fn_802337D4(model,s->mUnknownFC,p->mpUnknown50->mUnknownDC,0);
                }
                fn_80234BF4(work,&s->mUnknownC,0);
            }
        }
    }
    fn_801D0544();if(p->mpUnknown5C)fn_801A9430(p->mpUnknown5C,arg);
    fn_8024EB28(0);return 0;
}
}
