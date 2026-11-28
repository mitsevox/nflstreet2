/* Play art drawing: draws the small play diagrams of the play-select screen (field, player
   icons and letters, routes and route ends) from the play-art textures, which it also loads
   and frees. */

#include "game/Vec2Distance.h"
#include "game/ScrmGetBallSpot.h"
#include "game/PlayArtState.h"
#include "game/ScrmPlayResult.h"
#include "game/Object_80039F5C.h"
#include "game/ScrmGetTeamPlayerCount.h"
#include "game/ResLoad.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXTev.h>

struct PlayArtQuadPoint_t { float mX, mY; char mUnknown8[8]; };
struct PlayArtTexLib_t { char mUnknown0[40]; };
struct PlayArtClut_t { char mUnknown0[4]; GXTlutObj mUnknown4; };
struct PlayArtTexEntry_t { GXTexObj *mpTexture; PlayArtClut_t *mpPalette; };
struct PlayArtTexNode_t { char mUnknown0[12]; short mUnknownC; };

static const char *_PlayArtRender_apTexNames[8] = {"PLYR", "PLTR", "TBAR", "ARRW", "ZONE", "TILE", "DASH", "FLD"};
static PlayArtTexLib_t _PlayArtRender_TexLib;
static PlayArtTexEntry_t _PlayArtRender_aTextures[8];

static PlayArtVertex_t _PlayArtRender_aRouteEndUVs[4] = {
    {0.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},
};
static PlayArtVertex_t _PlayArtRender_aaIconUVs[4][4] = {
    {{0.0f, 0.5f}, {0.5f, 0.5f}, {0.0f, 0.0f}, {0.5f, 0.0f}},
    {{0.5f, 0.5f}, {1.0f, 0.5f}, {0.5f, 0.0f}, {1.0f, 0.0f}},
    {{0.0f, 1.0f}, {0.5f, 1.0f}, {0.0f, 5.0f}, {0.5f, 5.0f}},
    {{0.5f, 0.5f}, {1.0f, 0.5f}, {0.0f, 0.0f}, {0.5f, 0.0f}},
};
static PlayArtVertex_t _PlayArtRender_aaLetterUVs[5][4] = {
    {{0.0f, 0.0f}, {0.0f, 0.5f}, {0.25f, 0.0f}, {0.25f, 0.5f}},
    {{0.25f, 0.0f}, {0.25f, 0.5f}, {0.5f, 0.0f}, {0.5f, 0.5f}},
    {{0.5f, 0.0f}, {0.5f, 0.5f}, {0.75f, 0.0f}, {0.75f, 0.5f}},
    {{0.75f, 0.0f}, {0.75f, 0.5f}, {1.0f, 0.0f}, {1.0f, 0.5f}},
    {{0.0f, 0.5f}, {0.0f, 1.0f}, {0.25f, 0.5f}, {0.25f, 1.0f}},
};
static PlayArtQuadPoint_t _PlayArtRender_aRouteUVs[4] = {
    {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f},
};
static PlayArtVertex_t _PlayArtRender_aUnusedUVs[4] = {
    {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f},
};
static Mtx44 _PlayArtRender_MirrorMtx = {
    {-1.0f, 0.0f, 0.0f, 120.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
};

static int _PlayArtRender_iUnused = 0;
static unsigned char _PlayArtRender_aIconRows[6] = {2, 3, 0, 0, 1, 0};

extern "C" {
int fn_800BA6F8(void);
int FELoopIsMainFEActive(void);
int ScrmGetDown(void);
float ScrmGetLineToGain(void);
float ScrmGetGoalLineY(void);
int ScrmGetOffenseTeam(void);
int ScrmGetDefenseTeam(void);
void MatSetStack(int);
void MatPush(void);
void MatPop(void);
void MatCat(Mtx44);
void MatTranslate(float *);
void MatScaleCol(float, float, float);
void MatStore(Mtx44);
void TMRenderReset(void);
void TMTexLibLoad(PlayArtTexLib_t *, int);
void TMTexLibUnload(PlayArtTexLib_t *);
PlayArtTexNode_t *TMTexLibGetTexNode(PlayArtTexLib_t *, const char *);
PlayArtClut_t *TMTexLibGetClutByTexNode(PlayArtTexNode_t *, int);
GXTexObj *TMTexLibGetTextureByTexNode(PlayArtTexNode_t *);
int VptGetMatrixStack(void);
void GXSetNumChans(int);
void GXSetChanCtrl(int, int, int, int, int, int, int);
void GXSetChanAmbColor(int, GXColor);
void GXSetCullMode(int);
void GXSetZCompLoc(int);
void GXSetZMode(int, int, int);
extern "C" void GXInitTexObjTlut(GXTexObj *, int);
extern "C" void GXLoadTlut(GXTlutObj *, int);
extern "C" void GXLoadTexObj(GXTexObj *, int);
void GXLoadPosMtxImm(Mtx44, int);
void GXSetBlendMode(int, int, int, int);
}

extern "C" int PlayArtRenderBindTextures(int)
{
    GXSetNumTevStages(1);
    PlayArtTexEntry_t *p = _PlayArtRender_aTextures;
    for (unsigned int i = 0; i <= 7; ++i, ++p) {
        if (p->mpPalette) { GXInitTexObjTlut(p->mpTexture, i); GXLoadTlut(&p->mpPalette->mUnknown4, i); }
        GXLoadTexObj(p->mpTexture, i);
    }
    return 0;
}
extern "C" int PlayArtRenderLineQuad(int, PlayArtVertex_t *p, PlayArtQuadPoint_t *uv, GXColor *c)
{
    float z = 0.0f;
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    GXPosition3f32(p[0].mX, p[0].mY, z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[0].mX,uv[0].mY);
    GXPosition3f32(p[1].mX, p[1].mY, z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[1].mX,uv[1].mY);
    GXPosition3f32(p[2].mX, p[2].mY, z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[2].mX,uv[2].mY);
    GXPosition3f32(p[3].mX, p[3].mY, z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[3].mX,uv[3].mY);
    return 0;
}
extern "C" int PlayArtRenderDashQuad(int, PlayArtVertex_t *p, PlayArtQuadPoint_t *uv, GXColor *c)
{
    float z = 0.0f;
    PlayArtVertex_t *p2 = &p[2];
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    GXPosition3f32(p[0].mX,p[0].mY,z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[0].mX,z);
    GXPosition3f32(p[1].mX,p[1].mY,z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[1].mX,z);
    float length = Vec2Distance(p,p2) * 0.09f;
    GXPosition3f32(p2->mX,p2->mY,z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[2].mX,length);
    GXPosition3f32(p[3].mX,p[3].mY,z); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[3].mX,length);
    return 0;
}
extern "C" int PlayArtRenderLineStrip(int, PlayArtVertex_t *p, PlayArtQuadPoint_t *uv, unsigned int count, GXColor *c)
{
    unsigned int i = 0;
    while (i < count) {
        if (i > 1) i -= 2;
        int n = count - i; if (n > 16) n = 16;
        GXBegin(GX_TRIANGLESTRIP,GX_VTXFMT0,(unsigned short)n);
        while (n > 0) {
            PlayArtVertex_t *current = &p[i];
            PlayArtQuadPoint_t *t = &uv[i & 3];
            GXPosition3f32(current->mX,current->mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(t->mX,t->mY);
            ++i; --n;
        }
    }
    return 0;
}
extern "C" int PlayArtRenderDashStrip(int, PlayArtVertex_t *p, PlayArtQuadPoint_t *uv, unsigned int count, GXColor *c)
{
    float length = 0.0f; unsigned int i = 0;
    while (i < count) {
        if (i > 1) i -= 2;
        int n = count - i; if (n > 16) n = 16;
        GXBegin(GX_TRIANGLESTRIP,GX_VTXFMT0,(unsigned short)n);
        while (n > 0) {
            PlayArtVertex_t *current = &p[i];
            PlayArtQuadPoint_t *t = &uv[i & 3];
            if ((i & 3) == 2) length += Vec2Distance(&p[i-2],current) * 0.09f;
            GXPosition3f32(current->mX,current->mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(t->mX,length);
            ++i; --n;
        }
    }
    return 0;
}
extern "C" int PlayArtRenderTexQuad(int, PlayArtQuadPoint_t *p, PlayArtVertex_t *uv, GXColor *c, int texture)
{
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, (GXTexMapID)texture, GX_COLOR0A0);
    GXBegin(GX_TRIANGLESTRIP,GX_VTXFMT0,4);
    GXPosition3f32(p[0].mX,p[0].mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[0].mX,uv[0].mY);
    GXPosition3f32(p[1].mX,p[1].mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[1].mX,uv[1].mY);
    GXPosition3f32(p[2].mX,p[2].mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[2].mX,uv[2].mY);
    GXPosition3f32(p[3].mX,p[3].mY,0.0f); GXColor4u8(c->r,c->g,c->b,c->a); GXTexCoord2f32(uv[3].mX,uv[3].mY);
    return 0;
}
extern "C" int PlayArtRenderSprite(int a,PlayArtQuadPoint_t *p,PlayArtVertex_t *uv,GXColor *c,int texture)
{
    return PlayArtRenderTexQuad(a,p,uv,c,texture);
}
extern "C" int PlayArtRenderField(int a,FieldPoint_t *)
{
    PlayArtQuadPoint_t p[4];
    PlayArtVertex_t uv[4];
    uv[0].mX=0.0f;uv[0].mY=0.0f;uv[1].mX=0.0f;uv[1].mY=1.0f;
    uv[2].mX=1.0f;uv[2].mY=0.0f;uv[3].mX=1.0f;uv[3].mY=1.0f;
    p[0].mX = 0.0f; p[0].mY = 0.0f;
    p[1].mX = 0.0f; p[1].mY = 100.0f;
    p[2].mX = 120.0f; p[2].mY = 0.0f;
    p[3].mX = 120.0f; p[3].mY = 100.0f;
    GXColor c; c.r=255;c.g=255;c.b=255;c.a=255;
    return PlayArtRenderSprite(a,p,uv,&c,7);
}
extern "C" int PlayArtRenderRouteEnds(int a,PlayArtState_t *s,int)
{
    int count;
    if (s->mUnknown2083) count = ScrmGetActivePlayerCount(ScrmGetOffenseTeam()); else count = ScrmGetActivePlayerCount(ScrmGetDefenseTeam());
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j <= 11; ++j) {
            int kind = s->mUnknown19F0[i][j];
            if (kind) {
                int texture;
                switch (kind) {case 1:texture=2;break;case 2:texture=3;break;case 3:case 4:case 5:texture=4;break;default:texture=3;break;}
                PlayArtQuadPoint_t p[4];
                for (signed char k = 0; k <= 3; ++k) {p[k].mX = s->mUnknown970[i][j][k].mX;p[k].mY = s->mUnknown970[i][j][k].mY;}
                a = PlayArtRenderTexQuad(a,p,_PlayArtRender_aRouteEndUVs,&s->mUnknown2020[i],texture);
            }
        }
    }
    return a;
}
extern "C" int PlayArtRenderPlayerIcons(int a,PlayArtState_t *s,int mirror)
{
    int count;
    if (s->mUnknown2083) count = ScrmGetActivePlayerCount(ScrmGetOffenseTeam()); else count = ScrmGetActivePlayerCount(ScrmGetDefenseTeam());
    for (int i = 0; i < count; ++i) {
        if (s->mUnknown2134[i] <= 5) {
            PlayArtQuadPoint_t p[4];
            float r[4];
            if (mirror) {r[0]=120.0f-s->mUnknown2084[i][0];r[2]=120.0f-s->mUnknown2084[i][2];}
            else {r[0]=s->mUnknown2084[i][0];r[2]=s->mUnknown2084[i][2];}
            r[1]=s->mUnknown2084[i][1];r[3]=s->mUnknown2084[i][3];
            p[0].mX=r[0];p[0].mY=r[1];p[1].mX=r[0];p[1].mY=r[3];p[2].mX=r[2];p[2].mY=r[1];p[3].mX=r[2];p[3].mY=r[3];
            a=PlayArtRenderTexQuad(a,p,_PlayArtRender_aaIconUVs[_PlayArtRender_aIconRows[s->mUnknown2134[i]]],&s->mUnknown204C[i],0);
        }
    }
    return a;
}
extern "C" void PlayArtRenderPlayerLetters(int a,PlayArtState_t *s,int mirror)
{
    for (int i=0;i<s->mUnknown2160;++i) {
        int flag=s->mUnknown21C8[i]; unsigned int kind=s->mUnknown2164[i];
        if (!(flag&0x80)) {
            PlayArtQuadPoint_t p[4];float r[4];
            if (mirror) {r[0]=120.0f-s->mUnknown2178[i][2];r[2]=120.0f-s->mUnknown2178[i][0];}
            else {r[0]=s->mUnknown2178[i][0];r[2]=s->mUnknown2178[i][2];}
            int texture;switch(kind){case 0:texture=0;break;case 1:texture=1;break;case 2:texture=2;break;case 3:texture=3;break;default:texture=4;break;}
            r[3]=s->mUnknown2178[i][3];r[1]=s->mUnknown2178[i][1];
            p[0].mX=r[0];p[0].mY=r[1];p[1].mX=r[0];p[1].mY=r[3];p[2].mX=r[2];p[2].mY=r[1];p[3].mX=r[2];p[3].mY=r[3];
            a=PlayArtRenderSprite(a,p,_PlayArtRender_aaLetterUVs[texture],&s->mUnknown204C[flag],1);
        }
    }
}
extern "C" int PlayArtRenderRoutes(int a,PlayArtState_t *s,int)
{
    int tiled=0;
    int count;
    if (s->mUnknown2083) count = ScrmGetActivePlayerCount(ScrmGetOffenseTeam()); else count = ScrmGetActivePlayerCount(ScrmGetDefenseTeam());
    int mode=-1;
    for (int i=0;i<count;++i) {
        int start=s->mUnknown940[i];int n=s->mUnknown940[i+1]-start;
        if (n) {
            int next=s->mUnknown1E10[i][0];
            if(mode!=next){mode=next;if(!mode){tiled=0;GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP5, GX_COLOR0A0);}else{tiled=1;GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP6, GX_COLOR0A0);}}
            if(n==4){if(tiled)a=PlayArtRenderDashQuad(a,(PlayArtVertex_t *)s+start,_PlayArtRender_aRouteUVs,&s->mUnknown2020[i]);else a=PlayArtRenderLineQuad(a,(PlayArtVertex_t *)s+start,_PlayArtRender_aRouteUVs,&s->mUnknown2020[i]);}
            else {if(tiled)a=PlayArtRenderDashStrip(a,(PlayArtVertex_t *)s+start,_PlayArtRender_aRouteUVs,n,&s->mUnknown2020[i]);else a=PlayArtRenderLineStrip(a,(PlayArtVertex_t *)s+start,_PlayArtRender_aRouteUVs,n,&s->mUnknown2020[i]);}
        }
    }
    return a;
}
extern "C" void PlayArtRenderSetup(void)
{
    GXColor c={255,255,255,255};
    TMRenderReset();GXClearVtxDesc();GXSetVtxDesc(GX_VA_POS, GX_DIRECT);GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);GXSetNumChans(1);
    GXSetChanCtrl(0,1,0,1,0,0,2);GXSetChanCtrl(2,0,0,1,0,0,2);GXSetChanAmbColor(0,c);
    GXSetNumTevStages(1);GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);GXSetNumTexGens(1);GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);GXSetCullMode(0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);GXSetZCompLoc(1);GXSetZMode(0,7,0);GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);PlayArtRenderBindTextures(0);
}
extern "C" void PlayArtRenderDiagram(int a,PlayArtState_t *s,unsigned char mirror)
{
    Mtx44 m;MatPush();if(mirror)MatCat(_PlayArtRender_MirrorMtx);MatStore(m);GXLoadPosMtxImm(m,0);
    a=PlayArtRenderPlayerIcons(a,s,0);a=PlayArtRenderRoutes(a,s,0);a=PlayArtRenderRouteEnds(a,s,0);
    MatPop();MatStore(m);GXLoadPosMtxImm(m,0);PlayArtRenderPlayerLetters(a,s,mirror);
}
extern "C" void PlayArtRenderAt(float x,float y,void *input,unsigned char mirror)
{
    PlayArtState_t *s=(PlayArtState_t *)input;GXColor c={255,255,255,255};float pos[3];pos[0]=x;pos[1]=y;pos[2]=0.0f;Mtx44 m;FieldPoint_t point;
    PlayArtRenderSetup();point=ScrmGetBallSpot();FieldPoint_t *pPoint=&point;
    if(ScrmGetDown()!=0&&ScrmGetDown()!=6){float v=ScrmGetLineToGain();if(v<ScrmGetGoalLineY()&&!fn_800BA6F8()&&!FELoopIsMainFEActive())ScrmGetLineToGain();}
    GXSetChanAmbColor(4,c);MatSetStack(VptGetMatrixStack());MatPush();MatScaleCol(1.0f,1.0f,0.0f);MatTranslate(pos);MatStore(m);GXLoadPosMtxImm(m,0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);GXSetBlendMode(0,0,0,5);int a=PlayArtRenderField(0,pPoint);GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);GXSetBlendMode(1,4,5,5);
    MatStore(m);GXLoadPosMtxImm(m,0);GXSetChanAmbColor(4,c);PlayArtRenderDiagram(a,s,mirror);GXSetBlendMode(0,0,0,5);MatPop();MatStore(m);GXLoadPosMtxImm(m,0);
}
extern "C" void PlayArtRenderLoadTextures(int resource)
{
    TMTexLibLoad(&_PlayArtRender_TexLib,ResLoad((void *)resource,0,1));
    for(unsigned int i=0;i<=7;++i){PlayArtTexNode_t *d=TMTexLibGetTexNode(&_PlayArtRender_TexLib,_PlayArtRender_apTexNames[i]);if(d->mUnknownC)_PlayArtRender_aTextures[i].mpPalette=TMTexLibGetClutByTexNode(d,0);else _PlayArtRender_aTextures[i].mpPalette=0;_PlayArtRender_aTextures[i].mpTexture=TMTexLibGetTextureByTexNode(d);}
}
extern "C" void PlayArtRenderUnloadTextures(void)
{
    TMTexLibUnload(&_PlayArtRender_TexLib);
    for(int i=7;i>=0;--i){_PlayArtRender_aTextures[i].mpTexture=0;_PlayArtRender_aTextures[i].mpPalette=0;}
}
