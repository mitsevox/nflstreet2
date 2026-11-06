/* Dynamic world objects (DYNAMIC_RENDER): shared model caches by tideRef
   name, drawing with facing cull and distance fade, child objects,
   animated palettes and scrolling UVs; crowd groups use it too. */
#include "game/DynObjRender.h"
#include "engine/viewport.h"
#include "engine/vptmanager.h"
#include "game/GameVpt.h"
#include "game/Object_80039F5C.h"
#include "engine/texfile.h"
#include "game/Object_80233EAC.h"
#include "game/LightTracker.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EF390.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"
#include <dolphin/gx/GXStruct.h>
typedef float Mtx44[4][4];
#include <dolphin/os/OSCache.h>
#include <string.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXTransform.h>

struct DynObjTexHeader { unsigned char mUnknown0[16]; unsigned short mUnknown10; };
struct DynObjUVMesh {
    void *mpUnknown0; unsigned short mUnknown4; unsigned char mUnknown6;
    unsigned char mUnknown7; unsigned char mUnknown8; unsigned char mUnknown9;
};
struct DynObjMeshData { unsigned char mUnknown0[0x18]; DynObjUVMesh mUnknown18; };
struct DynObjMeshRef { unsigned char mUnknown0[8]; DynObjMeshData *mpUnknown8; };
struct DynObjTexCursor { int mUnknown0; unsigned char *mpUnknown4; };
struct DynObjAsset;
struct DynObjGeometry { DynObjAsset *mpUnknown0; unsigned char mUnknown4[0xC]; DynObjTexCursor *mpUnknown10; };
struct DynObjModelData { DynObjAsset *mpUnknown0; unsigned char mUnknown4[0x6C]; DynObjMeshRef *mpUnknown70; };
struct DynObjModel { unsigned char mUnknown0[8]; DynObjModelData *mpUnknown8; unsigned char mUnknownC[0x10]; int mUnknown1C; };
struct DynObjAsset { unsigned char mUnknown0[0x11]; unsigned char mUnknown11; };
struct DynObjModelRef { DynObjGeometry *mpUnknown0; };
struct DynObjContext { unsigned int mUnknown0; DynObjModelRef *mpUnknown4; };

struct DynObjCache {
    DynObjAsset *mpUnknown0; DynObjContext mUnknown4;
    unsigned char mUnknownC[0x2C]; char mUnknown38[0x100];
    int mUnknown138; void *mpUnknown13C; int mUnknown140;
    DynObjTexHeader *mpUnknown144; void *mpUnknown148; DynObjTexLib mUnknown14C;
};
struct DynObjPacket {
    unsigned char mUnknown0[0xC]; DynObjModel *mpUnknownC;
    unsigned char mUnknown10[0x4C]; int mUnknown5C;
    unsigned char mUnknown60[4]; DynObjMeshRef *mpUnknown64; unsigned char mUnknown68[0x78]; void *mpUnknownE0;
    unsigned char mUnknownE4[4]; void *mpUnknownE8;
};
struct DynObjInstance {
    DynObjCache *mpUnknown0; DynObjContext mUnknown4;
    DynObjPacket mUnknownC; unsigned char mUnknownF8[4];
    unsigned char mUnknownFC[12]; Tracker_801442FC mUnknown108;
};
struct DynObjPose { unsigned char mUnknown0[8]; Vector_80039F5C mUnknown8; unsigned char mUnknown14[0x4C]; Vector_80039F5C mUnknown60; };
struct DynObjSkeletonRef { void *mpUnknown0; };
extern "C" {
extern void *lbl_803EA368;
int fn_8002D060(void *);
void ConGetCurrentContext(void);
int DynObjSetupLight(void *, void *);
void UVScrollFloat(DynObjUVMesh *);
void UVScrollFixed(DynObjUVMesh *);
void fn_801D0470(int); void fn_801D04C4(void); void fn_801D0508(void);
void fn_801D0544(void); void fn_801D0558(void); void fn_801D06D4(Mtx44);
void fn_801D0C58(void *); void fn_801D0860(void *); void fn_801D08FC(int);
void fn_801D09EC(int); void fn_801D0F80(Mtx44);
void TMXform(int, void *); void TMXformSelect(int);
void TMModelResRelocate(void *); void TMModelBindModelRes(void *, void *);
void *TMModelResGetChunk(void *, unsigned int, void *);
void TMModelRemapMaterials(void *, void *); void TMModelRemapClusters(void *, void *);
void TMModelAllocChannels(void *); void TMModelFreeChannels(void *);
void TMMaterialListAllocDefs(void *, void *); void TMMaterialListFree(void *);
void TMMaterialListSelect(void *, int); void TMMaterialBindClut(unsigned int, int);
void TMRenderBindModel(Object_8023417C *); void TMRenderBindClusterObj(void *);
void TMRenderBindTexture(int, int, unsigned char *);
void TMRenderBindMaterialList(void *); void TMRenderSetBlendMode(int);
void fn_8021126C(void); void fn_802112DC(void *, int); void fn_80211350(void);
void TMTexLibLoad(DynObjTexLib *, int); void TMTexLibUnload(DynObjTexLib *);
void TMTexLibRegistryReset(void); void TMTexLibRegister(const char *, DynObjTexLib *);
int TMTexLibGetClut(DynObjTexLib *, unsigned int, int);
void fn_80233BB8(void *, int, int); void fn_80233BDC(void *, void *); void fn_80233BD8(void *);
void fn_80233CBC(void *, int, int); void fn_802337D4(void *, void *, void *, unsigned int);
void fn_80234A30(DynObjPacket *, int); void fn_80234A90(DynObjPacket *);
void fn_80234A94(DynObjPacket *, DynObjContext *);
void fn_80234AFC(void *); void fn_80234B1C(void *); void fn_80234B20(void *, Mtx44, Mtx44);
int fn_80234B80(void *); void fn_80234DC4(void *, int); void fn_80234DC8(void *, unsigned int);
void fn_80234B88(DynObjPacket *); void fn_80234BF4(void *, DynObjPacket *, int);
void fn_80234CA4(DynObjPacket *, void *); void fn_80234CF0(DynObjPacket *, int, DynObjContext *);
void fn_80234DC0(DynObjPacket *, int); unsigned int fn_80234D4C(float *, void *, void *, void *);
void fn_80227C2C(void *, void *); void fn_802271F0(void *, void *); float fn_80227704(void *, void *);
int fn_8004D5B8(int, const char *, char *, int); void fn_8004D498(int);
int fn_8004D4B0(int, const char *); int fn_8004D508(int, const char *);
void fn_8004E090(DynObj *, int, int);
int fn_801F0A8C(void *, const char *); char *fn_801C310C(char *, const char *);
int DynObjIsFacingAway(DynObj *); int DynObjChildIsFacingAway(DynObjChild *);
int DynObjDrawChild(DynObjChild *, int);
}

static float _DynObj_afCullBox[8] = {-3.1f,-1.5f,-2.0f,0.0f,3.9f,1.5f,5.0f,0.0f};
static DynObjCache *_DynObj_apCaches[104];
static unsigned int _DynObj_uNumCaches = 0;

extern "C" {
/* Render the object and its child chain, sharing prepared model state
   within this draw and applying the optional distance fade. */
int DynObjDraw(DynObj *p, int arg)
{
    GXColor color = {255,255,255,255}; GXColor copy;
    unsigned char work[0x90]; Mtx44 m1, m2;
    DynObjInstance *s = p->mpUnknown12C;
    ConGetCurrentContext();
    DynObjModel *model = s->mUnknownC.mpUnknownC;
    int value = DynObjSetupLight(&s->mUnknown108,p->mpUnknown14C);
    copy=color; GXSetChanMatColor(GX_COLOR0,copy); GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0,GX_ENABLE,GX_SRC_REG,GX_SRC_REG,value,GX_DF_CLAMP,GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0,GX_DISABLE,GX_SRC_REG,GX_SRC_REG,value,GX_DF_NONE,GX_AF_NONE);
    GXSetAlphaCompare(GX_GEQUAL, 16, GX_AOP_AND, GX_ALWAYS, 0); GXSetZCompLoc(GX_FALSE); GXSetZMode(GX_TRUE,GX_LEQUAL,GX_TRUE); GXSetCullMode(GX_CULL_FRONT);
    TMRenderSetBlendMode(2); fn_801D0470(VptGetMatrixStack()); fn_801D04C4(); fn_801D0508();
    fn_801D0C58(&p->mUnknown4); fn_801D0860(&p->mUnknown18); fn_801D08FC(0x400000);
    fn_801D0C58(&p->mUnknownB4); fn_801D09EC(p->mUnknownCC); fn_801D0F80(m1);
    fn_801D0544(); fn_801D0C58(&p->mUnknown4); fn_801D0860(&p->mUnknown18);
    fn_801D08FC(0x400000); fn_801D0C58(&p->mUnknownB4); fn_801D09EC(p->mUnknownCC);
    fn_801D0F80(m2); TMXform(0,m2); TMXformSelect(0);
    unsigned int flags=fn_80234D4C(_DynObj_afCullBox,m1,0,0);
    if(DynObjIsFacingAway(p)) flags|=0x3F;
    p->mUnknown138=0;
    if(!(flags&0x3F)) {
        fn_80234AFC(work); fn_80234DC8(work,flags&0xF2000); fn_80234B1C(work);
        fn_80234B20(work,m1,0); fn_80234B80(work); fn_80234DC4(work,0);
        if(!fn_8002D060(lbl_803EA368)) fn_80233CBC(&s->mUnknownC.mUnknown10[4],0,p->mUnknown13C);
        if(p->mUnknown140) {
            Vector_80039F5C delta;
            void *viewport=VptManagerGetCurrentCamera(GameVpt::GetViewport());
            fn_802276B4(&delta,&p->mUnknown4,static_cast<unsigned char *>(viewport)+4);
            float distance=fn_802270D4(&delta);
            if(distance<=10.0f) color.a=255;
            else if(distance<=25.0f) color.a=(unsigned char)((float)(unsigned int)color.a*(1.0f-(distance-10.0f)*0.06666667f));
            else color.a=0;
            copy=color; GXSetChanMatColor(GX_COLOR0A0,copy);
        }
        s->mUnknownC.mUnknown5C=1;
        unsigned int enabled=fn_8002D060(lbl_803EA368)?(p->mUnknownE8.mBytes[3]&4):(p->mUnknownE8.mBytes[3]&1);
        if(enabled) {
            if(p->mpUnknown130) {
                if(model->mpUnknown8->mpUnknown0->mUnknown11&8) {
                    TMRenderBindMaterialList(s->mUnknownC.mpUnknownE8); fn_80234B88(&s->mUnknownC);
                    if(!p->mUnknown138) {
                        p->mUnknown138=1;
                        if(!s->mUnknownC.mpUnknownC->mUnknown1C) TMModelAllocChannels(s->mUnknownC.mpUnknownC);
                        TMRenderBindModel(reinterpret_cast<Object_8023417C *>(model));
                        TMRenderBindClusterObj(s->mUnknownC.mpUnknownE0); fn_801D04C4(); fn_801D0558();
                        fn_802337D4(model,s->mUnknownFC,p->mpUnknownDC,0);
                        fn_801D0544(); fn_8021126C();
                    }
                    GXSetCurrentMtx(GX_PNMTX0);GXLoadPosMtxImm(m2,GX_PNMTX0);GXLoadNrmMtxImm(m2,GX_PNMTX0);
                    GXSetNumTexGens(1);GXSetNumTevStages(1);GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                    if(p->mUnknownE8.mWord&16) {
                        s->mUnknown4.mpUnknown4->mpUnknown0->mpUnknown10->mpUnknown4+=p->mUnknownFC*40;
                        fn_80211350();
                        s->mUnknown4.mpUnknown4->mpUnknown0->mpUnknown10->mpUnknown4-=p->mUnknownFC*40;
                    } else fn_802112DC(s->mUnknownC.mUnknown60,s->mUnknownC.mUnknown5C);
                } else {
                    p->mUnknown138=1;fn_802337D4(s->mUnknownC.mpUnknownC,s->mUnknownFC,p->mpUnknownDC,0);
                    fn_80234BF4(work,&s->mUnknownC,0);
                }
            } else fn_80234BF4(work,&s->mUnknownC,0);
        }
    }
    fn_801D0544(); if(p->mpUnknown1E0)DynObjDrawChild(p->mpUnknown1E0,arg);
    GXSetCullMode(GX_CULL_NONE); return 0;
}
int DynObjFindCache(const char *name)
{
    for(int i=0;i<(int)_DynObj_uNumCaches;i++) if(!strcmp(name,_DynObj_apCaches[i]->mUnknown38))return i;
    return -1;
}
extern const Vector_80039F5C _DynObj_vUpAxis={0.0f,1.0f,0.0f};
/* Cull frame-based geometry when its transformed axis dotted with the
   viewport-to-pose direction falls below -0.2. */
int DynObjIsFacingAway(DynObj *p)
{
    int result=0;
    if(p->mUnknownE8.mWord&16) {
        Vector_80039F5C delta,axis=_DynObj_vUpAxis;
        void *viewport=VptManagerGetCurrentCamera(0);fn_801D0508();fn_801D0860(&p->mpUnknown1D8->mUnknown60);
        fn_80227C2C(&axis,&axis);fn_801D0544();
        fn_802276B4(&delta,&p->mpUnknown1D8->mUnknown8,static_cast<unsigned char *>(viewport)+4);
        fn_802271F0(&delta,&delta);result=fn_80227704(&delta,&axis)<-0.2f;
    }
    return result;
}
/* Apply the frame-geometry facing test using the child transform and
   its owner's enable flag. */
int DynObjChildIsFacingAway(DynObjChild *p)
{
    int result=0;
    if(p->mpUnknown50->mUnknownE8.mWord&16) {
        Vector_80039F5C delta,axis=_DynObj_vUpAxis;
        void *viewport=VptManagerGetCurrentCamera(0);fn_801D0508();fn_801D0860(&p->mUnknown3C);
        fn_80227C2C(&axis,&axis);fn_801D0544();
        fn_802276B4(&delta,&p->mUnknown30,static_cast<unsigned char *>(viewport)+4);
        fn_802271F0(&delta,&delta);result=fn_80227704(&delta,&axis)<-0.2f;
    }
    return result;
}
/* Avoid reusing the owner's frame by choosing an adjacent index when
   the texture offers more than one frame. */
void DynObjChildPickFrame(DynObjChild *p,DynObj *owner)
{
    DynObjInstance *s=owner->mpUnknown12C;
    unsigned int index=fn_802372EC(1,s->mpUnknown0->mpUnknown144->mUnknown10);
    p->mUnknown6C=index;
    if((unsigned char)index==owner->mUnknownFC && s->mpUnknown0->mpUnknown144->mUnknown10>1) {
        p->mUnknown6C=index+1;
        if(p->mUnknown6C>=s->mpUnknown0->mpUnknown144->mUnknown10) p->mUnknown6C=index-1;
    }
}
/* Acquire the shared tideRef model cache and initialize this object's
   render packet, texture binding, and draw callback. */
void DynObjRenderInit(void *data,int handle,DynObj *p)
{
    char name[256],behavior[128];
    fn_8004D5B8(handle,"tideRef",name,256);
    int index=DynObjFindCache(name),hasBehavior=0;
    p->mpUnknown12C=static_cast<DynObjInstance *>(fn_801D2B7C(0x110,0,0));
    fn_801C1F94(p->mpUnknown12C,0,0x110);
    DynObjInstance *s=p->mpUnknown12C;DynObjSkeletonRef *skel=p->mpUnknown130;
    fn_8004D498(handle);fn_8004D4B0(handle,"render");
    if(fn_8004D508(handle,"clut"))hasBehavior=fn_8004D5B8(handle,"tideRef",behavior,128);
    if(index!=-1) {s->mpUnknown0=_DynObj_apCaches[index];s->mpUnknown0->mUnknown138++;}
    else {
        _DynObj_apCaches[_DynObj_uNumCaches]=static_cast<DynObjCache *>(fn_801D2B7C(0x174,0,0));
        fn_801C1F94(_DynObj_apCaches[_DynObj_uNumCaches],0,0x174);
        s->mpUnknown0=_DynObj_apCaches[_DynObj_uNumCaches++];s->mpUnknown0->mUnknown138=1;
        strcpy(s->mpUnknown0->mUnknown38,name);s->mpUnknown0->mpUnknown13C=data;
        s->mpUnknown0->mUnknown140=fn_801F0A8C(data,name);
        s->mpUnknown0->mpUnknown0=reinterpret_cast<DynObjAsset *>(fn_801EF390(data,s->mpUnknown0->mUnknown140,1));
        if(s->mpUnknown0->mpUnknown0) {
            TMModelResRelocate(s->mpUnknown0->mpUnknown0);
            TMModelBindModelRes(&s->mpUnknown0->mUnknown4,s->mpUnknown0->mpUnknown0);
            if(!hasBehavior || !strcmp(behavior,"CUSTOM_BEHAVIOR")) {
                s->mpUnknown0->mpUnknown144=static_cast<DynObjTexHeader *>(TMModelResGetChunk(s->mpUnknown0->mpUnknown0,0x54657874,0));
                p->mUnknownFC=0;
            } else {
                p->mUnknownF4=fn_801F0A8C(data,behavior);
                s->mpUnknown0->mpUnknown144=reinterpret_cast<DynObjTexHeader *>(fn_801EF390(data,p->mUnknownF4,1));
                p->mUnknownFC=fn_802372EC(1,s->mpUnknown0->mpUnknown144->mUnknown10);
            }
            if(s->mpUnknown0->mpUnknown144)TMTexLibLoad(&s->mpUnknown0->mUnknown14C,reinterpret_cast<int>(s->mpUnknown0->mpUnknown144));
            s->mpUnknown0->mpUnknown148=TMModelResGetChunk(s->mpUnknown0->mpUnknown0,0x4D61746C,0);
            TMModelRemapMaterials(&s->mpUnknown0->mUnknown4,s->mpUnknown0->mpUnknown148);
        }
    }
    TMTexLibRegistryReset();TMTexLibRegister("model",&s->mpUnknown0->mUnknown14C);
    TMMaterialListAllocDefs(&s->mUnknown4,s->mpUnknown0->mpUnknown148);TMTexLibRegistryReset();
    if(fn_801C310C(p->mUnknown158,"CROWDGROUP"))fn_80234A30(&s->mUnknownC,0x80);else fn_80234A30(&s->mUnknownC,0x40);
    fn_80234CF0(&s->mUnknownC,0,&s->mUnknown4);fn_80234DC0(&s->mUnknownC,8);
    fn_80234A94(&s->mUnknownC,&s->mpUnknown0->mUnknown4);
    if(skel) {
        TMModelRemapClusters(&s->mpUnknown0->mUnknown4,skel->mpUnknown0);
        fn_80233BB8(s->mUnknownFC,0x100,1);fn_80233BDC(s->mUnknownFC,skel->mpUnknown0);
        fn_80234CA4(&s->mUnknownC,s->mUnknownFC);
    } else fn_80233BB8(s->mUnknownFC,0,1);
    fn_8004E090(p,0,0);p->mUnknownE8.mWord=1;
    if(fn_8004D5B8(handle,"tideEnvMapRef",name,256))p->mUnknownE8.mWord=2;
    p->mUnknown14=DynObjDraw;LightTrackerReset(&s->mUnknown108);
}
void DynObjRenderShutdown(DynObj *p)
{
    DynObjInstance *s=p->mpUnknown12C;
    TMMaterialListFree(&s->mUnknown4);fn_80233BD8(s->mUnknownFC);fn_80234A90(&s->mUnknownC);
    if(s->mUnknownC.mpUnknownC->mUnknown1C)TMModelFreeChannels(s->mUnknownC.mpUnknownC);
    s->mpUnknown0->mUnknown138--;
    if(s->mpUnknown0->mUnknown138<=0) {
        TMTexLibUnload(&s->mpUnknown0->mUnknown14C);
        fn_801F010C(s->mpUnknown0->mpUnknown13C,s->mpUnknown0->mUnknown140);
    }
    fn_801D2BD0(s);p->mpUnknown12C=0;
}
void DynObjCacheReset(void) {_DynObj_uNumCaches=0;fn_801C1F94(_DynObj_apCaches,0,sizeof(_DynObj_apCaches));}
void DynObjCacheFree(void)
{
    for(unsigned int i=0;i<_DynObj_uNumCaches;i++)fn_801D2BD0(_DynObj_apCaches[i]);
    fn_801C1F94(_DynObj_apCaches,0,sizeof(_DynObj_apCaches));_DynObj_uNumCaches=0;
}
void DynObjLoadAnimPal(void *data,DynObj *p)
{
    p->mpUnknown100=reinterpret_cast<DynObjTexHeader *>(fn_801EF390(data,p->mUnknownF4,1));
    TexMipmapRelocate(p->mpUnknown100);TMTexLibRegistryReset();
    TMTexLibLoad(&p->mUnknown104,reinterpret_cast<int>(p->mpUnknown100));
    p->mUnknownF8=p->mpUnknown100->mUnknown10;
}
void DynObjFreeAnimPal(DynObj *p)
{
    TMTexLibUnload(&p->mUnknown104);
    fn_801F010C(p->mpUnknownA8,p->mUnknownF4);
}
void DynObjSetAnimPalFrame(DynObj *p,int index)
{
    DynObjInstance *s=p->mpUnknown12C;
    int palette=TMTexLibGetClut(&p->mUnknown104,0xFF000000,index);
    TMMaterialListSelect(&s->mUnknownC.mUnknown10[0x44],0);TMMaterialBindClut(0xFF000000,palette);
}
void DynObjScrollUVs(DynObj *p, void *)
{
    DynObjUVMesh *mesh=&p->mpUnknown12C->mUnknownC.mpUnknown64->mpUnknown8->mUnknown18;
    if(mesh->mUnknown9==4)UVScrollFloat(mesh);else if(mesh->mUnknown9==3)UVScrollFixed(mesh);
    DCFlushRange(mesh->mpUnknown0,mesh->mUnknown4*mesh->mUnknown7);
}
/* Render one child using its owner's shared model preparation, then
   continue through the child chain. */
int DynObjDrawChild(DynObjChild *p,int arg)
{
    DynObjInstance *s=p->mpUnknown50->mpUnknown12C;
    GXColor color={255,255,255,255},copy;unsigned char work[0x90];Mtx44 m1,m2;
    ConGetCurrentContext();DynObjModel *model=s->mUnknownC.mpUnknownC;int value=DynObjSetupLight(&p->mUnknown60,p->mpUnknown58);
    copy=color;GXSetChanMatColor(GX_COLOR0,copy);GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0,GX_ENABLE,GX_SRC_REG,GX_SRC_REG,value,GX_DF_CLAMP,GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0,GX_DISABLE,GX_SRC_REG,GX_SRC_REG,value,GX_DF_NONE,GX_AF_NONE);
    fn_801D0470(VptGetMatrixStack());fn_801D0508();
    fn_801D0C58(&p->mUnknown30);fn_801D0860(&p->mUnknown3C);fn_801D08FC(0x400000);
    fn_801D0C58(&p->mpUnknown50->mUnknownB4);fn_801D09EC(p->mpUnknown50->mUnknownCC);fn_801D0F80(m1);
    fn_801D0544();fn_801D04C4();fn_801D0C58(&p->mUnknown30);fn_801D0860(&p->mUnknown3C);
    fn_801D08FC(0x400000);fn_801D0C58(&p->mpUnknown50->mUnknownB4);fn_801D09EC(p->mpUnknown50->mUnknownCC);fn_801D0F80(m2);
    unsigned int flags=fn_80234D4C(_DynObj_afCullBox,m1,0,0);if(DynObjChildIsFacingAway(p))flags|=0x3F;
    if(!(flags&0x3F)) {
        fn_80234AFC(work);fn_80234DC8(work,flags&0xF2000);fn_80234B1C(work);fn_80234B20(work,m1,0);
        fn_80234B80(work);fn_80234DC4(work,0);s->mUnknownC.mUnknown5C=1;
        unsigned int enabled=fn_8002D060(lbl_803EA368)?(p->mpUnknown50->mUnknownE8.mBytes[3]&4):(p->mpUnknown50->mUnknownE8.mBytes[3]&1);
        if(enabled) {
            if(model->mpUnknown8->mpUnknown0->mUnknown11&8) {
                fn_80234B88(&s->mUnknownC);TMRenderBindMaterialList(s->mUnknownC.mpUnknownE8);
                if(!p->mpUnknown50->mUnknown138) {
                    p->mpUnknown50->mUnknown138=1;
                    if(!s->mUnknownC.mpUnknownC->mUnknown1C)TMModelAllocChannels(s->mUnknownC.mpUnknownC);
                    TMRenderBindModel(reinterpret_cast<Object_8023417C *>(model));TMRenderBindClusterObj(s->mUnknownC.mpUnknownE0);
                    fn_801D04C4();fn_801D0558();fn_802337D4(model,s->mUnknownFC,p->mpUnknown50->mpUnknownDC,0);
                    fn_801D0544();fn_8021126C();GXSetNumTexGens(1);GXSetNumTevStages(1);GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                }
                GXSetCurrentMtx(GX_PNMTX0);GXLoadPosMtxImm(m2,GX_PNMTX0);GXLoadNrmMtxImm(m2,GX_PNMTX0);
                if(p->mpUnknown50->mUnknownE8.mWord&16) {
                    s->mUnknown4.mpUnknown4->mpUnknown0->mpUnknown10->mpUnknown4+=p->mUnknown6C*40;
                    TMRenderBindTexture(0,s->mUnknown4.mpUnknown4->mpUnknown0->mpUnknown10->mUnknown0,s->mUnknown4.mpUnknown4->mpUnknown0->mpUnknown10->mpUnknown4);
                    fn_80211350();
                    s->mUnknown4.mpUnknown4->mpUnknown0->mpUnknown10->mpUnknown4-=p->mUnknown6C*40;
                } else fn_802112DC(s->mUnknownC.mUnknown60,s->mUnknownC.mUnknown5C);
            } else {
                if(!p->mpUnknown50->mUnknown138) {
                    fn_801D06D4(m2);p->mpUnknown50->mUnknown138=1;
                    fn_802337D4(s->mUnknownC.mpUnknownC,s->mUnknownFC,p->mpUnknown50->mpUnknownDC,0);
                }
                fn_80234BF4(work,&s->mUnknownC,0);
            }
        }
    }
    fn_801D0544();if(p->mpUnknown5C)DynObjDrawChild(p->mpUnknown5C,arg);
    GXSetCullMode(GX_CULL_NONE);return 0;
}
}
