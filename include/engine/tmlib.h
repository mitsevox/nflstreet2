#ifndef ENGINE_TMLIB_H
#define ENGINE_TMLIB_H

#include <dolphin/gx/GXStruct.h>
#include <dolphin/mtx.h>

typedef struct Pool_801C750C Pool_801C750C;

#include "game/Object_8020E52C.h"
#include "engine/texture.h"
#include "game/fn_8021216C.h"


typedef struct TexInfo_8020E2B0 {
    int mUnknown00;
    unsigned char *mpData;
} TexInfo_8020E2B0;

typedef struct TexHeader_8020E2B0 {
    char maTag[4];
    unsigned short mVersion;
    unsigned short mFlags;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
    unsigned short mNumMaterials;
    unsigned short mNumTextures;
    unsigned short mNumPalettes;
    Object_8020E52C *mpMaterials;
    Object_8020E560 *mpTextures;
    Object_8020E5F8 *mpPalettes;
    char (*mpNames)[16];
    TexInfo_8020E2B0 *mpInfo;
} TexHeader_8020E2B0;

/* texture.c */
unsigned short fn_8020E51C(TexHeader_8020E2B0 *pTex);
unsigned short fn_8020E524(TexHeader_8020E2B0 *pTex);
const char *fn_8020E53C(TexHeader_8020E2B0 *pTex, unsigned short index);

extern int lbl_803EBEBC;

void fn_801D0F80(Mtx44 mtx);
void fn_801D34D0(void *p, unsigned int size, int c, int d);

Pool_801C750C *fn_801C750C(int a, int count, int size, void *pMemory);
int fn_801C75B8(Pool_801C750C *pPool);
void *fn_801C75F0(Pool_801C750C *pPool);
void fn_801C7650(Pool_801C750C *pPool, void *pElement);

typedef struct RegistryEntry_8021283C {
    const char *mpName;
    void *mpData;
} RegistryEntry_8021283C;

typedef struct Registry_8021283C {
    int mMaxEntries;
    int mNumEntries;
    RegistryEntry_8021283C *mpEntries;
    unsigned char mbAppend;
    unsigned char mbPaths;
} Registry_8021283C;

typedef struct ShaderParmDef_80211638 {
    char mName[16];
    unsigned char mType;
    unsigned char mUnknown11;
    unsigned short mIndex;
} ShaderParmDef_80211638;

typedef struct ShaderDef_80211638 {
    char mName[16];
    int mbAllocConsts;
    int mUnknown14;
    int mNumParms;
    ShaderParmDef_80211638 mParms[1];
} ShaderDef_80211638;

typedef struct Shader_80211638 Shader_80211638;
typedef void (*ShaderFunc_80211638)(Shader_80211638 *pShader);

struct Shader_80211638 {
    ShaderDef_80211638 *mpDef;
    ShaderFunc_80211638 mBindFunc;
    ShaderFunc_80211638 mUnbindFunc;
    int mUnknownC;
    int mNumTextures;
    int mNumConsts;
    ShaderParmDef_80211638 *mpFirstConst;
    int mConstSize;
    void *mpConstData;
};

typedef struct Texture_80212234 {
    GXTexObj mObj;
    unsigned short mNumMips;
    unsigned short mUnknown22;
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned int mSize;
} Texture_80212234;

typedef struct Clut_80212534 {
    int mType;
    union {
        GXTlutObj maTlut[2];
        GXTexObj mObj;
    } u;
    unsigned int mSize;
} Clut_80212534;

typedef struct TexNode_802119C4 {
    const char *mpName;
    struct TexLib_802119C4 *mpLib;
    short mTextureIndex;
    short mFirstClut;
    short mNumCluts;
    short mUnknownE;
} TexNode_802119C4;

struct TexLib_802119C4 {
    Registry_8021283C mRegistry;
    int mNumTextures;
    Texture_80212234 *mpTextures;
    int mNumCluts;
    Clut_80212534 *mpCluts;
    int mNumTexNodes;
    TexNode_802119C4 *mpTexNodes;
};

typedef void (*ChunkRelocFunc_8020EA18)(void *pData, void *pOldBase, void *pNewBase);

typedef struct ChunkDef_8020EA18 {
    int mTag;
    int mVersion;
    ChunkRelocFunc_8020EA18 mRelocate;
} ChunkDef_8020EA18;

typedef struct Chunk_8020EA18 {
    int mTag;
    void *mpData;
    int mSize;
    unsigned char mVersion;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mbRelocated;
} Chunk_8020EA18;

typedef struct ModelRes_8020EA18 {
    int mUnknown0;
    int mUnknown4;
    unsigned short mNumChunks;
    unsigned short mChunkOffset;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mbRelocated;
} ModelRes_8020EA18;

typedef struct Extent_802144AC {
    float mMin[3];
    float mUnknownC;
    float mMax[3];
} Extent_802144AC;

typedef struct GeomAttr_8020ED10 {
    void *mpData;
    unsigned short mCount;
    unsigned char mType;
    unsigned char mStride;
    unsigned char mCompCount : 8;
    unsigned char mCompType : 8;
    unsigned char mFrac : 8;
    unsigned int mUnknownB : 3;
    unsigned int mbDelta : 1;
    unsigned char mDescType : 4;
} GeomAttr_8020ED10;

typedef struct GeomNode_8020ED10 {
    void *mpData;
    unsigned short mDisplayListSize;
    short mMaterial;
    int mUnknown8;
    short mUnknownC;
    unsigned short mFirstAttr;
    unsigned char mNumAttrs;
    unsigned char mFlags;
    unsigned char mFormatIndex;
    unsigned char mUnknown13;
    unsigned char mNumLods;
    unsigned char maUnknown15[3];
} GeomNode_8020ED10;

typedef struct Geom_8020ED10 {
    GeomNode_8020ED10 *mpNodes;
    unsigned int mNumNodes;
    GeomAttr_8020ED10 *mpAttrs;
    int mNumAttrs;
    unsigned int mFlags;
    void *mpUnknown14;
} Geom_8020ED10;

typedef struct TMMaterialDef_t {
    const char *mpName;
    const char *mpShaderName;
    short mNumTextures;
    short mUnknownA;
    const char *mapTextureNames[8];
    void *mpUnknown2C;
} TMMaterialDef_t;

typedef struct TMMaterialDefList_t {
    unsigned int mNumMaterials;
    TMMaterialDef_t *mpMaterials;
} TMMaterialDefList_t;

typedef struct TMClusterDefEntry_t {
    unsigned char mBone;
    unsigned char maUnknown1[3];
} TMClusterDefEntry_t;

typedef struct TMClusterDef_t {
    TMClusterDefEntry_t *mpEntries;
    int mNumClusters;
} TMClusterDef_t;

typedef struct TMSkelBone_t {
    int maUnknown0[3];
    short mParent;
    short mUnknownE;
} TMSkelBone_t;

typedef struct TMSkelBoneInfo_t {
    short maUnknown0[3];
} TMSkelBoneInfo_t;

typedef struct TMSkeleton_t {
    int mNumBones;
    char (*mpNames)[16];
    TMSkelBone_t *mpBones;
    TMSkelBoneInfo_t *mpInfo;
    void *mpUnknown10;
} TMSkeleton_t;

typedef struct TMSwapState_t {
    unsigned char maUnknown0[0xC];
    int mNumActive;
    unsigned short mFirstNode;
    unsigned short mNumNodes;
} TMSwapState_t;

typedef struct TMSwapSlot_t {
    unsigned char maUnknown0[0x10];
    unsigned short mFirstState;
    unsigned char mNumStates;
    unsigned char mUnknown13;
} TMSwapSlot_t;

typedef struct TMSwapDef_t {
    unsigned int mNumSlots;
    TMSwapSlot_t *mpSlots;
    TMSwapState_t *mpStates;
    unsigned short *mpNodeIndices;
} TMSwapDef_t;

typedef struct MaterialParm_8020FAAC {
    Texture_80212234 *mpTexture;
    Clut_80212534 *mpClut;
    int mXForm;
} MaterialParm_8020FAAC;

typedef union MaterialConst_8020FAAC {
    GXColor mColor;
    float mFloat;
    unsigned int mWord;
} MaterialConst_8020FAAC;

typedef struct Material_8020FAAC {
    int mRefCount;
    TMMaterialDef_t *mpDef;
    Shader_80211638 *mpShader;
    int mNumParms;
    MaterialParm_8020FAAC *mpParms;
    MaterialConst_8020FAAC maConsts[4];
} Material_8020FAAC;

typedef struct MaterialList_8020FF34 {
    int mNumMaterials;
    Material_8020FAAC **mppMaterials;
} MaterialList_8020FF34;

typedef struct Model_8020F28C {
    void *mpInfo;
    void *mpExtn;
    Geom_8020ED10 *mpGeom;
    TMClusterDef_t *mpClst;
    TMSkeleton_t *mpSkel;
    TMSwapDef_t *mpSwap;
    TMMaterialDefList_t *mpMatl;
    void **mpChannels;
    void *mpTxfm;
    void *mpInst;
    void *mpRint;
    void *mpDInf;
    void *mpFade;
} Model_8020F28C;

/* tmmodelres.c */
void fn_8020EB08(int maxChunkTypes);
void fn_8020EB48(int tag, ChunkRelocFunc_8020EA18 relocate, int version);
void fn_8020EB70(void);
void *fn_8020EB94(void *p, void *pOldBase, void *pNewBase);
void fn_8020EBB0(ModelRes_8020EA18 *pRes);
void *fn_8020EC50(ModelRes_8020EA18 *pRes, int tag, Chunk_8020EA18 **ppChunk);

/* tmgeometry.c */
void fn_8020ED10(Extent_802144AC *pExtent, short *pPoints, int count);
void fn_8020EDE4(Extent_802144AC *pExtent, float *pPoints, int count);
void fn_8020EFC8(int size);
void fn_8020F00C(void);
void fn_8020F08C(Geom_8020ED10 *pPart, void *pOldBase, void *pNewBase);
void fn_8020F178(Geom_8020ED10 *pPart, unsigned short *pRemap, int numMaterials);
void fn_8020F1D8(Geom_8020ED10 *pPart, int nodeIndex, Extent_802144AC *pExtent);

/* tmshader.c */
void fn_80211638(Shader_80211638 *pShader, ShaderDef_80211638 *pDef);
void fn_80211730(Shader_80211638 *pShader);
void fn_8021175C(Shader_80211638 *pShader, ShaderFunc_80211638 bindFunc);
void fn_80211764(Shader_80211638 *pShader, ShaderFunc_80211638 unbindFunc);
void fn_8021176C(Shader_80211638 *pShader);

/* tmshaderlib.c */
void fn_802117C8(Registry_8021283C *pLib, int maxShaders);
void fn_802117F0(Registry_8021283C *pLib);
Shader_80211638 *fn_80211860(Registry_8021283C *pLib, ShaderDef_80211638 *pDef, ShaderFunc_80211638 bindFunc);
void fn_8021189C(int maxShaders, int maxLibs);
void fn_802118F0(void);
void fn_80211928(const char *pName, Registry_8021283C *pLib);
void fn_80211958(const char *pName);
Shader_80211638 *fn_80211984(const char *pPath);
void fn_802119BC(Shader_80211638 *pShader);

/* tmtexlib.c */
void fn_80211AFC(TexLib_802119C4 *pLib, Object_8020E5F8 *pPalette, int clutIndex, Clut_80212534 *pClut);
void fn_80211B64(TexHeader_8020E2B0 *pTex, TexLib_802119C4 *pLib, int materialIndex, Object_8020E560 *pTexture, int textureIndex, int clutIndex);
void fn_80211D24(TexLib_802119C4 *pLib, int numTexNodes, int numTextures, int numCluts);
void fn_80211DA8(TexLib_802119C4 *pLib);
void fn_80211E08(TexLib_802119C4 *pLib, TexHeader_8020E2B0 *pTex);
void fn_80211EBC(TexHeader_8020E2B0 *pTex, TexLib_802119C4 *pLib, int materialIndex, Object_8020E560 *pTexture, int textureIndex, int clutIndex);
void fn_80211EDC(TexLib_802119C4 *pLib, Object_8020E5F8 *pPalette, int clutIndex, Clut_80212534 *pClut);
void fn_80211EFC(TexLib_802119C4 *pLib);
void fn_80211F94(int maxLibs);
void fn_80211FC8(void);
void fn_80211FF0(void);
void fn_80212018(const char *pName, TexLib_802119C4 *pLib);
Texture_80212234 *fn_80212050(TexNode_802119C4 *pNode);
Clut_80212534 *fn_80212074(TexNode_802119C4 *pNode, int index);
TexNode_802119C4 *fn_802120AC(TexLib_802119C4 *pLib, const char *pName);
Texture_80212234 *fn_802120E4(TexLib_802119C4 *pLib, const char *pName);
Clut_80212534 *fn_80212124(TexLib_802119C4 *pLib, const char *pName, int index);

/* tmtexture.c */
void fn_80212234(Texture_80212234 *pTexture, int minFilter, int magFilter, float lodBias, unsigned char bBiasClamp, unsigned char bEdgeLod, int maxAniso);
void fn_80212310(Texture_80212234 *pTexture, Desc_802EE9E4 *pDesc);
void fn_8021234C(Texture_80212234 *pTexture, int wrapS, int wrapT);
void fn_80212374(Texture_80212234 *pTexture, TexWrapDesc_80212374 *pDesc);
void fn_8021239C(Texture_80212234 *pTexture, void *pData, int width, int height, int format, int numMips, unsigned int size, Clut_80212534 *pClut);
void fn_8021242C(Texture_80212234 *pTexture, void *pData, int width, int height, int format, int numMips, unsigned int size, Clut_80212534 *pClut);
void fn_80212530(Texture_80212234 *pTexture);
void fn_80212534(Clut_80212534 *pClut, void *pData, int format, int numEntries, unsigned int size);
void fn_80212654(Clut_80212534 *pClut);
void fn_80212658(Texture_80212234 *pTexture);
void fn_802126BC(Texture_80212234 *pTexture, const char *pName);

/* tmname.c */
int fn_802126C0(const char *pName, const char *pOther);
int fn_802126E8(const char *pPattern, const char *pName);
void fn_8021272C(const char *pPath, char *pDir, char *pFile);

/* tmmemory.c */
void *fn_802127D0(int count, int size);
void fn_80212814(void *p);

/* tmregistry.c */
void fn_80212850(Registry_8021283C *pRegistry, int maxEntries, int bAppend, int bPaths);
void fn_802128A8(Registry_8021283C *pRegistry);
void fn_802128DC(Registry_8021283C *pRegistry);
void fn_80212940(Registry_8021283C *pRegistry, int index, const char *pName, void *pData);
void fn_8021295C(Registry_8021283C *pRegistry, const char *pName, void *pData);
int fn_802129B8(Registry_8021283C *pRegistry, const char *pName);
void fn_80212A48(Registry_8021283C *pRegistry, int index);
void fn_80212AB0(Registry_8021283C *pRegistry, const char *pName);
void *fn_80212AEC(Registry_8021283C *pRegistry, int index);
void *fn_80212B1C(Registry_8021283C *pRegistry, char **ppNames, int depth, int numNames);
void *fn_80212BDC(Registry_8021283C *pRegistry, const char *pPath);
void *fn_80212C60(Registry_8021283C *pRegistry, const char *pName);
int fn_80212CAC(Registry_8021283C *pRegistry);

/* tmshaderdef.c */
ShaderParmDef_80211638 *TMShaderDefGetParmByName(ShaderDef_80211638 *pDef, const char *pName, int type);

/* tmshaderstock.c */
void TMShaderStockInit(void);
void TMShaderStockShutdown(void);

/* tmshaderparm.c */
int TMShaderParmGetSize(int type);

/* tmshadercode.c */
void TMShaderCodeLoad(int code);

/* tmmodel.c */
void fn_8020F28C(Model_8020F28C *pModel);
void fn_8020F2C4(Model_8020F28C *pDst, Model_8020F28C *pSrc);
int fn_8020F330(Model_8020F28C *pModel, ModelRes_8020EA18 *pRes, unsigned int tag);
void fn_8020F4D0(Model_8020F28C *pModel, ModelRes_8020EA18 *pRes);
void fn_8020F5F0(int maxChunkTypes);
void fn_8020F76C(void);
void fn_8020F78C(Model_8020F28C *pModel, TMMaterialDefList_t *pMatLib);
void fn_8020F824(Model_8020F28C *pModel, void *pOther);
void fn_8020F89C(Model_8020F28C *pModel);
void fn_8020F8E0(Model_8020F28C *pModel);
void fn_8020F92C(Model_8020F28C *pModel);
void fn_8020F96C(Model_8020F28C *pModel, Extent_802144AC *pExtent, int state, int arg);

/* tmmaterialdef.c */
void TMMaterialDefRelocateChunk(TMMaterialDefList_t *pLib, void *pOldBase, void *pNewBase);
int TMMaterialDefGetIndexByName(TMMaterialDefList_t *pLib, const char *pName);

/* tmclusterdef.c */
void TMClusterDefRelocateChunk(TMClusterDef_t *pDef, void *pOldBase, void *pNewBase);
void TMClusterDefRemap(TMClusterDef_t *pDef, short *pRemap);

/* tmxform.c */
void fn_8020FA38(u32 id, f32 (*pMtx)[4]);
void fn_8020FA8C(u32 id);

/* tmmaterial.c */
void fn_8020FC1C(int *pPoolSizes);
void fn_8020FCA0(Material_8020FAAC *pMaterial);
void fn_8020FD40(Material_8020FAAC *pMaterial);
void fn_8020FD48(const char *pName, Texture_80212234 *pTexture, Clut_80212534 *pClut);
void fn_8020FDAC(const char *pName, Clut_80212534 *pClut);
void fn_8020FE04(const char *pPath);
void fn_8020FE3C(Shader_80211638 *pShader);
void fn_8020FE78(TMMaterialDef_t *pDef);

/* tmmateriallist.c */
void fn_8020FFE4(int maxMaterials);
void fn_80210020(void);
void fn_80210054(MaterialList_8020FF34 *pList, unsigned int numMaterials);
void fn_802100C0(MaterialList_8020FF34 *pList, TMMaterialDefList_t *pLib);
void fn_80210114(MaterialList_8020FF34 *pList);
Material_8020FAAC *fn_80210184(MaterialList_8020FF34 *pList, int index);
void fn_802101B0(MaterialList_8020FF34 *pList, int index);
void fn_80210214(MaterialList_8020FF34 *pList, TMMaterialDefList_t *pLib);

typedef void (*MaterialBindFunc_80210298)(Material_8020FAAC *pMaterial);

typedef struct ClusterObj_80210724 {
    void *mpMatrices;
    void *mpCacheMatrices;
    int mNumMatrices;
} ClusterObj_80210724;

typedef struct TMClusterBone_t {
    unsigned char mIndex;
    unsigned char mParent;
    unsigned short mWeight;
} TMClusterBone_t;

typedef struct TMClusterBoneList_t {
    TMClusterBone_t *mpBones;
    unsigned int mNumBones;
} TMClusterBoneList_t;

typedef struct TMClusterPose_t {
    unsigned char maUnknown0[8];
    float (*mpPositions)[4];
    short (*mpRotations)[3];
} TMClusterPose_t;

typedef struct RenderViewport_80210298 {
    float mLeft;
    float mTop;
    float mWidth;
    float mHeight;
    float mNear;
    float mFar;
} RenderViewport_80210298;

typedef struct RenderState_80210298 {
    Geom_8020ED10 *mpGeom;
    ClusterObj_80210724 *mpClusterObj;
    TMSkeleton_t *mpSkel;
    TMSwapDef_t *mpSwap;
    MaterialList_8020FF34 *mpMaterialList;
    Material_8020FAAC *mpMaterial;
    Shader_80211638 *mpShader;
    int mBlendMode;
    void **mpChannels;
    RenderViewport_80210298 mViewport;
    int mNumHooks;
    struct RenderHook_80211138 *mapHooks[8];
    int mUnknown60;
    void *mpExtn;
    void *mpInst;
    void *mpRint;
    void *mpFade;
    unsigned char maUnknown74[0x14];
    void *mpTexXForm;
    MaterialBindFunc_80210298 mBindFunc;
    unsigned int mLod;
} RenderState_80210298;

extern RenderState_80210298 lbl_803E96E8;

/* tmrender.c */
void fn_80210298(void);
void fn_802102E8(void);
void fn_8021032C(void);
void fn_80210368(Texture_80212234 *pTexture);
void fn_80210388(void);
void fn_802103DC(void);
void fn_80210608(void);
void fn_80210634(void);
void fn_80210654(Model_8020F28C *pModel);
void fn_80210724(ClusterObj_80210724 *pClusterObj);
void fn_8021077C(Shader_80211638 *pShader);
void fn_80210814(GXTexMapID id, Texture_80212234 *pTexture, Clut_80212534 *pClut);
void fn_80210970(Material_8020FAAC *pMaterial);
void fn_80210B6C(int index);
void fn_80210BA4(MaterialList_8020FF34 *pList);
void fn_80210BB0(void *pTexXForm);
void fn_80210BD8(unsigned int mode);
void fn_80210CC4(float nearZ, float farZ);
void fn_80210D10(GXBool compareEnable, GXCompare func, GXBool updateEnable);

typedef struct TMChannelList_t {
    int mCount;
    GeomAttr_8020ED10 *mapAttrs[8];
    void *mapData[8];
    unsigned char maCompType[8];
    unsigned char maStride[8];
    unsigned char maFrac[8];
} TMChannelList_t;

typedef void (*RenderHookFunc_80211138)(struct RenderHook_80211138 *pHook, GeomNode_8020ED10 *pNode,
                                        TMChannelList_t *pList);

typedef struct RenderHook_80211138 {
    unsigned char maUnknown0[0xC];
    RenderHookFunc_80211138 mFunc;
} RenderHook_80211138;

/* tmrendergeom.c */
void fn_80210DCC(RenderState_80210298 *pState, GeomNode_8020ED10 *pNode);
void fn_8021126C(void);
void fn_802112DC(unsigned short *pIndices, unsigned int count);
void fn_80211350(void);
void fn_802113C0(int state, int arg);
void fn_80211424(unsigned short *pIndices, unsigned int count);

/* tmclusterobj.c */
void TMClusterObjInit(int maxMatrices, int numBuffers);
void TMClusterObjShutdown(void);
void TMClusterObjInitObj(ClusterObj_80210724 *pObj);
void TMClusterObjResetMatrices(void);
void TMClusterObjAllocMatrices(ClusterObj_80210724 *pObj, int numMatrices);
void TMClusterObjSynthesizeMatrices(ClusterObj_80210724 *pObj, TMClusterPose_t *pPose, TMClusterBoneList_t *pBones, short (*pBlend)[3]);
void TMClusterObjSynthesizeMatricesSlerp(ClusterObj_80210724 *pObj, TMClusterPose_t *pPose, TMClusterBoneList_t *pBones, short (*pBlend)[3],
                 unsigned char *pFlags);

/* tmchannellist.c */
void TMChannelListBuild(TMChannelList_t *pList, GeomNode_8020ED10 *pNode, GeomAttr_8020ED10 *pAttrs, void **ppChannels);
void TMChannelListSubmit_DFA(TMChannelList_t *pList);
void TMChannelListSubmit_A(TMChannelList_t *pList);

/* tmswappart.c */
void TMSwapRelocateChunk(TMSwapDef_t *pSwap, void *pOldBase, void *pNewBase);
TMSwapSlot_t *TMSwapGetNode(TMSwapDef_t *pSwap, int slot);
TMSwapState_t *TMSwapGetState(TMSwapDef_t *pSwap, int slot, int state);
int TMSwapGetGeomRefs(TMSwapDef_t *pSwap, unsigned short *pNodes, int slot, int state);

/* tmskeleton.c */
void TMSkelRelocateChunk(TMSkeleton_t *pSkel, void *pOldBase, void *pNewBase);
short *TMSkelBuildRemapTable(TMSkeleton_t *pSkel, void *pOther);
void TMSkelRemapNodes(TMSkeleton_t *pSkel, short *pRemap);

/* tmclip.c */
void fn_802144AC(Extent_802144AC *pExtent);
void fn_802144D8(Extent_802144AC *pExtent, float x, float y, float z);

/* tmtev.c */
void TMTevSetTevOp(GXTevStageID stage, GXTevMode mode, GXTevScale scale);

/* tmbuffer.c */
typedef struct TMBuffer_t {
    unsigned char *mpData;
    int mUsed;
    int mSize;
    int mAlign;
} TMBuffer_t;

void TMBufferNew(TMBuffer_t *pBuffer, int size, int align);
void TMBufferDelete(TMBuffer_t *pBuffer);
void TMBufferReset(TMBuffer_t *pBuffer);
int TMBufferGetFreeSpace(TMBuffer_t *pBuffer);
unsigned char *TMBufferOpen(TMBuffer_t *pBuffer, int size);
void TMBufferClose(TMBuffer_t *pBuffer, unsigned char *pEnd);
unsigned char *TMBufferAlloc(TMBuffer_t *pBuffer, int size);

/* tmlightdef.c */
typedef struct TMLightDef_t {
    int mUnknown0;
    void *mpUnknown4;
    int mUnknown8;
    void *mpUnknownC;
} TMLightDef_t;

void TMLightDefRelocateChunk(TMLightDef_t *pDef, void *pOldBase, void *pNewBase);

/* tmblendchannel.c */
typedef struct TMBlendChannel_t {
    GeomAttr_8020ED10 *mpAttr;
    unsigned char *mpCursor;
    int mSize;
    unsigned char *mpBase;
    int mCapacity;
    unsigned char *mpOutput;
    int mOutputSize;
} TMBlendChannel_t;

typedef struct TMBlendChannelSource_t {
    int mNumAttrs;
    GeomAttr_8020ED10 *mpAttrs;
    void **mppOutputs;
    void **mppInputs;
} TMBlendChannelSource_t;

TMBlendChannel_t *TMBlendChannelGetBuffer(int id);
int TMBlendChannelSet(int id, int index);
unsigned char *TMBlendChannelSetMem(int id, unsigned char *pData, int size);
void TMBlendChannelSetChannels(GeomAttr_8020ED10 *pAttrs, void **ppInputs, void **ppOutputs, int numAttrs);
void TMBlendChannelSetOverride(int index, void *pOutput);
void TMBlendChannelBegin(void);
void TMBlendChannelEnd(void);

/* tmblend.c */
typedef struct TMBlendTarget_t {
    short mIndex;
    short mWeight;
    short mFirstAttr;
    short mNumAttrs;
} TMBlendTarget_t;

typedef struct TMBlendState_t {
    Geom_8020ED10 *mpGeom;
    TMBuffer_t *mpBuffer;
    int mFlushed;
    unsigned int mNumWeights;
    short *mpWeights;
    int mBaseIndex;
    unsigned int mMaxItems;
    short maWeights[128];
} TMBlendState_t;

void TMBlendSetWeights(short *pWeights, unsigned int numWeights);
int TMBlendSetWeightsFloat(float *pWeights, unsigned int numWeights);
void TMBlendBegin(TMBuffer_t *pBuffer);
void TMBlendFlushBuffer(void);
void TMBlendEnd(void);
void TMBlendBindModel(Model_8020F28C *pModel);
void TMBlendBindModel2(Model_8020F28C *pBase, Model_8020F28C *pModel);
void TMBlendSetMaxActiveTargets(unsigned int maxItems);
int TMBlendGeom(int nodeIndex);
int TMBlendGeomAll(void);

/* tmblendop.c */
unsigned int TMBlendOpAccumulate(int dstId, int srcId, int weight);
void TMBlendOpExtract(int dstId, int srcId);
void TMBlendOpIntract(int dstId, int srcId);

/* tmextentsdef.c */
typedef struct TMExtentsDef_t {
    int mUnknown0;
    void *mpExtents;
} TMExtentsDef_t;

void TMExtentsDefRelocateChunk(TMExtentsDef_t *pDef, void *pOldBase, void *pNewBase);

/* TMTexXForm.c */
typedef struct TMTexXformEntry_t {
    const char *mpName;
    unsigned char maUnknown4[0x14];
} TMTexXformEntry_t;

typedef struct TMTexXformDef_t {
    unsigned int mNumEntries;
    TMTexXformEntry_t maEntries[1];
} TMTexXformDef_t;

void TMTexXformRelocateChunk(TMTexXformDef_t *pDef, void *pOldBase, void *pNewBase);
int TMTexXformFind(const char *pName);

/* lltmviewport.c, tmprof.c */
void TMViewportLLNew(int unknown);
void TMViewportLLDelete(void);
void TMProfBeginFrame(void);
void TMProfEndFrame(void);

/* tmdebuginfo.c */
typedef struct TMDebugInfo_t {
    void *mpNames;
    int mNumNames;
    void *mpStrings;
    int mNumStrings;
} TMDebugInfo_t;

void TMDebugInfoRelocateChunk(TMDebugInfo_t *pInfo, void *pOldBase, void *pNewBase);

/* TmInstance.c */
typedef struct TMInstanceTarget_t {
    int mUnknown0;
    void *mpData;
} TMInstanceTarget_t;

typedef struct TMInstanceDef_t {
    int mUnknown0;
    void *mpUnknown4;
    void *mpUnknown8;
    TMInstanceTarget_t *mpTarget;
    TMSkeleton_t *mpSkel;
} TMInstanceDef_t;

typedef struct TMInstanceRegionEntry_t {
    unsigned char maUnknown0[0x20];
    int maUsed[4];
    void *mapData[4];
} TMInstanceRegionEntry_t;

typedef struct TMInstanceRegionDef_t {
    int mNumEntries;
    TMInstanceRegionEntry_t *mpEntries;
    int mNumPointers;
    void *mapPointers[1];
} TMInstanceRegionDef_t;

void TMInstanceDefRelocateChunk(TMInstanceDef_t *pInst, void *pOldBase, void *pNewBase);
void TMInstanceRegionDefRelocateChunk(TMInstanceRegionDef_t *pInst, void *pOldBase, void *pNewBase);

/* TMMorphAnim.c */
typedef struct TMMorphTarget_t {
    int mNumData;
    void *mapData[1];
} TMMorphTarget_t;

typedef struct TMMorphAnim_t {
    int mNumTargets;
    TMMorphTarget_t *mapTargets[1];
} TMMorphAnim_t;

void *TMMorphAnimResRelocatePtr(void *p, void *pOldBase, void *pNewBase);
void TMMorphAnimRelocate(TMMorphAnim_t *pAnim, void *pOldBase, void *pNewBase);

#endif
