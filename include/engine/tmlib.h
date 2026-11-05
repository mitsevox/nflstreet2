#ifndef ENGINE_TMLIB_H
#define ENGINE_TMLIB_H

#include <dolphin/gx/GXStruct.h>
#include <dolphin/mtx.h>

typedef struct Pool_801C750C Pool_801C750C;

#include "engine/texfile.h"
#include "engine/texture.h"
#include "engine/tmtexlib.h"


typedef struct TexFileInfo_t {
    int mUnknown00;
    unsigned char *mpData;
} TexFileInfo_t;

typedef struct TexFileHeader_t {
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
    TexFileMaterial_t *mpMaterials;
    TexFileImage_t *mpTextures;
    TexFilePalette_t *mpPalettes;
    char (*mpNames)[16];
    TexFileInfo_t *mpInfo;
} TexFileHeader_t;

/* texture.c */
unsigned short TexGetNumMaterials(TexFileHeader_t *pTex);
unsigned short TexGetNumPalettes(TexFileHeader_t *pTex);
const char *TexGetMaterialNameByIndex(TexFileHeader_t *pTex, unsigned short index);

extern int lbl_803EBEBC;

void fn_801D0F80(Mtx44 mtx);
void fn_801D34D0(void *p, unsigned int size, int c, int d);

Pool_801C750C *fn_801C750C(int a, int count, int size, void *pMemory);
int fn_801C75B8(Pool_801C750C *pPool);
void *fn_801C75F0(Pool_801C750C *pPool);
void fn_801C7650(Pool_801C750C *pPool, void *pElement);

typedef struct TMRegistryEntry_t {
    const char *mpName;
    void *mpData;
} TMRegistryEntry_t;

typedef struct TMRegistry_t {
    int mMaxEntries;
    int mNumEntries;
    TMRegistryEntry_t *mpEntries;
    unsigned char mbAppend;
    unsigned char mbPaths;
} TMRegistry_t;

typedef struct TMShaderParmDef_t {
    char mName[16];
    unsigned char mType;
    unsigned char mUnknown11;
    unsigned short mIndex;
} TMShaderParmDef_t;

typedef struct TMShaderDef_t {
    char mName[16];
    int mbAllocConsts;
    int mUnknown14;
    int mNumParms;
    TMShaderParmDef_t mParms[1];
} TMShaderDef_t;

typedef struct TMShader_t TMShader_t;
typedef void (*TMShaderFunc_t)(TMShader_t *pShader);

struct TMShader_t {
    TMShaderDef_t *mpDef;
    TMShaderFunc_t mBindFunc;
    TMShaderFunc_t mUnbindFunc;
    int mUnknownC;
    int mNumTextures;
    int mNumConsts;
    TMShaderParmDef_t *mpFirstConst;
    int mConstSize;
    void *mpConstData;
};

typedef struct TMTexture_t {
    GXTexObj mObj;
    unsigned short mNumMips;
    unsigned short mUnknown22;
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned int mSize;
} TMTexture_t;

typedef struct TMClut_t {
    int mType;
    union {
        GXTlutObj maTlut[2];
        GXTexObj mObj;
    } u;
    unsigned int mSize;
} TMClut_t;

typedef struct TMTexNode_t {
    const char *mpName;
    struct TMTexLib_t *mpLib;
    short mTextureIndex;
    short mFirstClut;
    short mNumCluts;
    short mUnknownE;
} TMTexNode_t;

struct TMTexLib_t {
    TMRegistry_t mRegistry;
    int mNumTextures;
    TMTexture_t *mpTextures;
    int mNumCluts;
    TMClut_t *mpCluts;
    int mNumTexNodes;
    TMTexNode_t *mpTexNodes;
};

typedef void (*TMChunkRelocFunc_t)(void *pData, void *pOldBase, void *pNewBase);

typedef struct TMChunkDef_t {
    int mTag;
    int mVersion;
    TMChunkRelocFunc_t mRelocate;
} TMChunkDef_t;

typedef struct TMChunk_t {
    int mTag;
    void *mpData;
    int mSize;
    unsigned char mVersion;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mbRelocated;
} TMChunk_t;

typedef struct TMModelRes_t {
    int mUnknown0;
    int mUnknown4;
    unsigned short mNumChunks;
    unsigned short mChunkOffset;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mbRelocated;
} TMModelRes_t;

typedef struct Extent_802144AC {
    float mMin[3];
    float mUnknownC;
    float mMax[3];
} Extent_802144AC;

typedef struct TMGeomAttr_t {
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
} TMGeomAttr_t;

typedef struct TMGeomNode_t {
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
} TMGeomNode_t;

typedef struct TMGeom_t {
    TMGeomNode_t *mpNodes;
    unsigned int mNumNodes;
    TMGeomAttr_t *mpAttrs;
    int mNumAttrs;
    unsigned int mFlags;
    void *mpUnknown14;
} TMGeom_t;

typedef struct MaterialDef_80213228 {
    const char *mpName;
    const char *mpShaderName;
    short mNumTextures;
    short mUnknownA;
    const char *mapTextureNames[8];
    void *mpUnknown2C;
} MaterialDef_80213228;

typedef struct MaterialLib_80213228 {
    unsigned int mNumMaterials;
    MaterialDef_80213228 *mpMaterials;
} MaterialLib_80213228;

typedef struct ClusterEntry_80213384 {
    unsigned char mBone;
    unsigned char maUnknown1[3];
} ClusterEntry_80213384;

typedef struct ClusterDef_80213384 {
    ClusterEntry_80213384 *mpEntries;
    int mNumClusters;
} ClusterDef_80213384;

typedef struct SkelBone_80215E5C {
    int maUnknown0[3];
    short mParent;
    short mUnknownE;
} SkelBone_80215E5C;

typedef struct SkelBoneInfo_80215E5C {
    short maUnknown0[3];
} SkelBoneInfo_80215E5C;

typedef struct Skeleton_80215E5C {
    int mNumBones;
    char (*mpNames)[16];
    SkelBone_80215E5C *mpBones;
    SkelBoneInfo_80215E5C *mpInfo;
    void *mpUnknown10;
} Skeleton_80215E5C;

typedef struct SwapState_802160A0 {
    unsigned char maUnknown0[0xC];
    int mNumActive;
    unsigned short mFirstNode;
    unsigned short mNumNodes;
} SwapState_802160A0;

typedef struct SwapSlot_802160A0 {
    unsigned char maUnknown0[0x10];
    unsigned short mFirstState;
    unsigned char mNumStates;
    unsigned char mUnknown13;
} SwapSlot_802160A0;

typedef struct Swap_802160A0 {
    unsigned int mNumSlots;
    SwapSlot_802160A0 *mpSlots;
    SwapState_802160A0 *mpStates;
    unsigned short *mpNodeIndices;
} Swap_802160A0;

typedef struct TMMaterialTexState_t {
    TMTexture_t *mpTexture;
    TMClut_t *mpClut;
    int mXForm;
} TMMaterialTexState_t;

typedef union TMMaterialConst_t {
    GXColor mColor;
    float mFloat;
    unsigned int mWord;
} TMMaterialConst_t;

typedef struct TMMaterial_t {
    int mRefCount;
    MaterialDef_80213228 *mpDef;
    TMShader_t *mpShader;
    int mNumParms;
    TMMaterialTexState_t *mpParms;
    TMMaterialConst_t maConsts[4];
} TMMaterial_t;

typedef struct TMMaterialList_t {
    int mNumMaterials;
    TMMaterial_t **mppMaterials;
} TMMaterialList_t;

typedef struct TMModel_t {
    void *mpInfo;
    void *mpExtn;
    TMGeom_t *mpGeom;
    ClusterDef_80213384 *mpClst;
    Skeleton_80215E5C *mpSkel;
    Swap_802160A0 *mpSwap;
    MaterialLib_80213228 *mpMatl;
    void **mpChannels;
    void *mpTxfm;
    void *mpInst;
    void *mpRint;
    void *mpDInf;
    void *mpFade;
} TMModel_t;

/* tmmodelres.c */
void TMModelResInit(int maxChunkTypes);
void TMModelResAddChunkType(int tag, TMChunkRelocFunc_t relocate, int version);
void TMModelResShutdown(void);
void *TMModelResRelocatePtr(void *p, void *pOldBase, void *pNewBase);
void TMModelResRelocate(TMModelRes_t *pRes);
void *TMModelResGetChunk(TMModelRes_t *pRes, int tag, TMChunk_t **ppChunk);

/* tmgeometry.c */
void TMGeomExtentAddS16Points(Extent_802144AC *pExtent, short *pPoints, int count);
void TMGeomExtentAddF32Points(Extent_802144AC *pExtent, float *pPoints, int count);
void TMGeomInitChannelBuffer(int size);
void TMGeomFreeChannelBuffer(void);
void TMGeomRelocateChunk(TMGeom_t *pPart, void *pOldBase, void *pNewBase);
void TMGeometryRemapMaterials(TMGeom_t *pPart, unsigned short *pRemap, int numMaterials);
void TMGeomAddNodeExtent(TMGeom_t *pPart, int nodeIndex, Extent_802144AC *pExtent);

/* tmshader.c */
void TMShaderNew(TMShader_t *pShader, TMShaderDef_t *pDef);
void TMShaderDelete(TMShader_t *pShader);
void TMShaderSetBindFunc(TMShader_t *pShader, TMShaderFunc_t bindFunc);
void TMShaderSetUnbindFunc(TMShader_t *pShader, TMShaderFunc_t unbindFunc);
void TMShaderSelect(TMShader_t *pShader);

/* tmshaderlib.c */
void TMShaderLibAlloc(TMRegistry_t *pLib, int maxShaders);
void TMShaderLibFree(TMRegistry_t *pLib);
TMShader_t *TMShaderLibAddShader(TMRegistry_t *pLib, TMShaderDef_t *pDef, TMShaderFunc_t bindFunc);
void TMShaderLibRegistryInit(int maxShaders, int maxLibs);
void TMShaderLibRegistryShutdown(void);
void TMShaderLibRegister(const char *pName, TMRegistry_t *pLib);
void TMShaderLibUnregister(const char *pName);
TMShader_t *TMShaderLibGetShader(const char *pPath);
void TMShaderLibSetNullShader(TMShader_t *pShader);

/* tmtexlib.c */
void TMTexLibSetClutData(TMTexLib_t *pLib, TexFilePalette_t *pPalette, int clutIndex, TMClut_t *pClut);
void TMTexLibSetTextureData(TexFileHeader_t *pTex, TMTexLib_t *pLib, int materialIndex, TexFileImage_t *pTexture, int textureIndex, int clutIndex);
void TMTexLibAlloc(TMTexLib_t *pLib, int numTexNodes, int numTextures, int numCluts);
void TMTexLibFree(TMTexLib_t *pLib);
void TMTexLibLoad(TMTexLib_t *pLib, TexFileHeader_t *pTex);
void TMTexLibReplaceTexture(TexFileHeader_t *pTex, TMTexLib_t *pLib, int materialIndex, TexFileImage_t *pTexture, int textureIndex, int clutIndex);
void TMTexLibReplaceClut(TMTexLib_t *pLib, TexFilePalette_t *pPalette, int clutIndex, TMClut_t *pClut);
void TMTexLibUnload(TMTexLib_t *pLib);
void TMTexLibRegistryInit(int maxLibs);
void TMTexLibRegistryShutdown(void);
void TMTexLibRegistryReset(void);
void TMTexLibRegister(const char *pName, TMTexLib_t *pLib);
TMTexture_t *TMTexLibGetTextureByTexNode(TMTexNode_t *pNode);
TMClut_t *TMTexLibGetClutByTexNode(TMTexNode_t *pNode, int index);
TMTexNode_t *TMTexLibGetTexNode(TMTexLib_t *pLib, const char *pName);
TMTexture_t *TMTexLibGetTexture(TMTexLib_t *pLib, const char *pName);
TMClut_t *TMTexLibGetClut(TMTexLib_t *pLib, const char *pName, int index);

/* tmtexture.c */
void TMTextureSetFilter(TMTexture_t *pTexture, int minFilter, int magFilter, float lodBias, unsigned char bBiasClamp, unsigned char bEdgeLod, int maxAniso);
void TMTextureSetFilterParm(TMTexture_t *pTexture, TMTexFilterDesc_t *pDesc);
void TMTextureSetWrap(TMTexture_t *pTexture, int wrapS, int wrapT);
void TMTextureSetWrapParm(TMTexture_t *pTexture, TMTexWrapDesc_t *pDesc);
void TMTextureTexNew(TMTexture_t *pTexture, void *pData, int width, int height, int format, int numMips, unsigned int size, TMClut_t *pClut);
void TMTextureSetTexData(TMTexture_t *pTexture, void *pData, int width, int height, int format, int numMips, unsigned int size, TMClut_t *pClut);
void TMTextureTexDelete(TMTexture_t *pTexture);
void TMTextureClutNew(TMClut_t *pClut, void *pData, int format, int numEntries, unsigned int size);
void TMTextureClutDelete(TMClut_t *pClut);
void TMTextureMakeNullTexture(TMTexture_t *pTexture);
void TMTextureSetTexName(TMTexture_t *pTexture, const char *pName);

/* tmname.c */
int TMNameCompareExact(const char *pName, const char *pOther);
int TMNameCompareWildcard(const char *pPattern, const char *pName);
void TMNameSplitPath(const char *pPath, char *pDir, char *pFile);

/* tmmemory.c */
void *TMMemAllocArray(int count, int size);
void TMMemFreeArray(void *p);

/* tmregistry.c */
void TMRegistryAlloc(TMRegistry_t *pRegistry, int maxEntries, int bAppend, int bPaths);
void TMRegistryFree(TMRegistry_t *pRegistry);
void TMRegistryReset(TMRegistry_t *pRegistry);
void TMRegistrySetEntry(TMRegistry_t *pRegistry, int index, const char *pName, void *pData);
void TMRegistryAddEntry(TMRegistry_t *pRegistry, const char *pName, void *pData);
int TMRegistryGetIndexByName(TMRegistry_t *pRegistry, const char *pName);
void TMRegistryRemoveEntryByIndex(TMRegistry_t *pRegistry, int index);
void TMRegistryRemoveEntryByName(TMRegistry_t *pRegistry, const char *pName);
void *TMRegistryGetDataByIndex(TMRegistry_t *pRegistry, int index);
void *TMRegistrySearch(TMRegistry_t *pRegistry, char **ppNames, int depth, int numNames);
void *TMRegistrySearchPath(TMRegistry_t *pRegistry, const char *pPath);
void *TMRegistryGetDataByName(TMRegistry_t *pRegistry, const char *pName);
int TMRegistryGetNumEntries(TMRegistry_t *pRegistry);

/* tmshaderdef.c */
TMShaderParmDef_t *fn_80212CB4(TMShaderDef_t *pDef, const char *pName, int type);

/* tmshaderstock.c */
void fn_80213160(void);
void fn_802131D8(void);

/* tmshaderparm.c */
int fn_80213214(int type);

/* tmshadercode.c */
void fn_80213224(int code);

/* tmmodel.c */
void TMModelReset(TMModel_t *pModel);
void TMModelClone(TMModel_t *pDst, TMModel_t *pSrc);
int TMModelBindModelChunk(TMModel_t *pModel, TMModelRes_t *pRes, unsigned int tag);
void TMModelBindModelRes(TMModel_t *pModel, TMModelRes_t *pRes);
void TMModelInit(int maxChunkTypes);
void TMModelShutdown(void);
void TMModelRemapMaterials(TMModel_t *pModel, MaterialLib_80213228 *pMatLib);
void TMModelRemapClusters(TMModel_t *pModel, void *pOther);
void TMModelResetChannels(TMModel_t *pModel);
void TMModelAllocChannels(TMModel_t *pModel);
void TMModelFreeChannels(TMModel_t *pModel);
void TMModelAddExtent(TMModel_t *pModel, Extent_802144AC *pExtent, int state, int arg);

/* tmmaterialdef.c */
void fn_80213228(MaterialLib_80213228 *pLib, void *pOldBase, void *pNewBase);
int fn_8021330C(MaterialLib_80213228 *pLib, const char *pName);

/* tmclusterdef.c */
void fn_80213384(ClusterDef_80213384 *pDef, void *pOldBase, void *pNewBase);
void fn_802133B8(ClusterDef_80213384 *pDef, short *pRemap);

/* tmxform.c */
void TMXform(u32 id, f32 (*pMtx)[4]);
void TMXformSelect(u32 id);

/* tmmaterial.c */
void TMMaterialInit(int *pPoolSizes);
void TMMaterialReset(TMMaterial_t *pMaterial);
void TMMaterialSelect(TMMaterial_t *pMaterial);
void TMMaterialBindTextureClut(const char *pName, TMTexture_t *pTexture, TMClut_t *pClut);
void TMMaterialBindClut(const char *pName, TMClut_t *pClut);
void TMMaterialBindShaderRef(const char *pPath);
void TMMaterialBindShader(TMShader_t *pShader);
void TMMaterialSetMatDef(MaterialDef_80213228 *pDef);

/* tmmateriallist.c */
void TMMaterialListInit(int maxMaterials);
void TMMaterialListShutdown(void);
void TMMaterialListAlloc(TMMaterialList_t *pList, unsigned int numMaterials);
void TMMaterialListAllocDefs(TMMaterialList_t *pList, MaterialLib_80213228 *pLib);
void TMMaterialListFree(TMMaterialList_t *pList);
TMMaterial_t *TMMaterialListGetMaterial(TMMaterialList_t *pList, int index);
void TMMaterialListSelect(TMMaterialList_t *pList, int index);
void TMMaterialListSetMatDefs(TMMaterialList_t *pList, MaterialLib_80213228 *pLib);

typedef void (*TMMaterialBindFunc_t)(TMMaterial_t *pMaterial);

typedef struct TMClusterObj_t {
    void *mpMatrices;
    void *mpCacheMatrices;
    int mNumMatrices;
} TMClusterObj_t;

typedef struct BoneEntry_8021353C {
    unsigned char mIndex;
    unsigned char mParent;
    unsigned short mWeight;
} BoneEntry_8021353C;

typedef struct BoneList_8021353C {
    BoneEntry_8021353C *mpBones;
    unsigned int mNumBones;
} BoneList_8021353C;

typedef struct Pose_8021353C {
    unsigned char maUnknown0[8];
    float (*mpPositions)[4];
    short (*mpRotations)[3];
} Pose_8021353C;

typedef struct TMRenderViewport_t {
    float mLeft;
    float mTop;
    float mWidth;
    float mHeight;
    float mNear;
    float mFar;
} TMRenderViewport_t;

typedef struct TMRenderState_t {
    TMGeom_t *mpGeom;
    TMClusterObj_t *mpClusterObj;
    Skeleton_80215E5C *mpSkel;
    Swap_802160A0 *mpSwap;
    TMMaterialList_t *mpMaterialList;
    TMMaterial_t *mpMaterial;
    TMShader_t *mpShader;
    int mBlendMode;
    void **mpChannels;
    TMRenderViewport_t mViewport;
    int mNumHooks;
    struct RenderHook_80211138 *mapHooks[8];
    int mUnknown60;
    void *mpExtn;
    void *mpInst;
    void *mpRint;
    void *mpFade;
    unsigned char maUnknown74[0x14];
    void *mpTexXForm;
    TMMaterialBindFunc_t mBindFunc;
    unsigned int mLod;
} TMRenderState_t;

extern TMRenderState_t lbl_803E96E8;

/* tmrender.c */
void TMRenderDisable32BitIndirectCluts(void);
void TMRenderInit(void);
void TMRenderShutdown(void);
void TMRenderSetDefaultTexture(TMTexture_t *pTexture);
void TMRenderReset(void);
void TMRenderBeginFrame(void);
void TMRenderBeginViewport(void);
void TMRenderEndFrame(void);
void TMRenderBindModel(TMModel_t *pModel);
void TMRenderBindClusterObj(TMClusterObj_t *pClusterObj);
void TMRenderBindShader(TMShader_t *pShader);
void TMRenderBindTexture(GXTexMapID id, TMTexture_t *pTexture, TMClut_t *pClut);
void TMRenderBindMaterial(TMMaterial_t *pMaterial);
void TMRenderBindMaterialIndex(int index);
void TMRenderBindMaterialList(TMMaterialList_t *pList);
void TMRenderBindTexXformList(void *pTexXForm);
void TMRenderSetBlendMode(unsigned int mode);
void TMRenderSetZRange(float nearZ, float farZ);
void TMRenderSetZMode(GXBool compareEnable, GXCompare func, GXBool updateEnable);

typedef struct ChannelList_8021592C {
    int mCount;
    TMGeomAttr_t *mapAttrs[8];
    void *mapData[8];
    unsigned char maCompType[8];
    unsigned char maStride[8];
    unsigned char maFrac[8];
} ChannelList_8021592C;

typedef void (*RenderHookFunc_80211138)(struct RenderHook_80211138 *pHook, TMGeomNode_t *pNode,
                                        ChannelList_8021592C *pList);

typedef struct RenderHook_80211138 {
    unsigned char maUnknown0[0xC];
    RenderHookFunc_80211138 mFunc;
} RenderHook_80211138;

/* tmrendergeom.c */
void fn_80210DCC(TMRenderState_t *pState, TMGeomNode_t *pNode);
void fn_8021126C(void);
void fn_802112DC(unsigned short *pIndices, unsigned int count);
void fn_80211350(void);
void fn_802113C0(int state, int arg);
void fn_80211424(unsigned short *pIndices, unsigned int count);

/* tmclusterobj.c */
void fn_80213444(int maxMatrices, int numBuffers);
void fn_802134AC(void);
void fn_802134D0(TMClusterObj_t *pObj);
void fn_802134E8(void);
void fn_80213504(TMClusterObj_t *pObj, int numMatrices);
void SynthesizeClusterBoneMatrices_8021353C(TMClusterObj_t *pObj, Pose_8021353C *pPose, BoneList_8021353C *pBones, short (*pBlend)[3]);
void SynthesizeFlaggedQuaternionBoneMatrices_80213774(TMClusterObj_t *pObj, Pose_8021353C *pPose, BoneList_8021353C *pBones, short (*pBlend)[3],
                 unsigned char *pFlags);

/* tmchannellist.c */
void fn_8021592C(ChannelList_8021592C *pList, TMGeomNode_t *pNode, TMGeomAttr_t *pAttrs, void **ppChannels);
void fn_80215A14(ChannelList_8021592C *pList);
void fn_80215B00(ChannelList_8021592C *pList);

/* tmswappart.c */
void fn_802160A0(Swap_802160A0 *pSwap, void *pOldBase, void *pNewBase);
SwapSlot_802160A0 *fn_8021616C(Swap_802160A0 *pSwap, int slot);
SwapState_802160A0 *fn_80216190(Swap_802160A0 *pSwap, int slot, int state);
int fn_802161D8(Swap_802160A0 *pSwap, unsigned short *pNodes, int slot, int state);

/* tmskeleton.c */
void fn_80215E5C(Skeleton_80215E5C *pSkel, void *pOldBase, void *pNewBase);
short *fn_80215EE0(Skeleton_80215E5C *pSkel, void *pOther);
void fn_80215F78(Skeleton_80215E5C *pSkel, short *pRemap);

/* tmclip.c */
void fn_802144AC(Extent_802144AC *pExtent);
void fn_802144D8(Extent_802144AC *pExtent, float x, float y, float z);

/* tmtev.c */
void fn_80213A38(GXTevStageID stage, GXTevMode mode, GXTevScale scale);

/* tmbuffer.c */
typedef struct Buffer_80214554 {
    unsigned char *mpData;
    int mUsed;
    int mSize;
    int mAlign;
} Buffer_80214554;

void fn_80214554(Buffer_80214554 *pBuffer, int size, int align);
void fn_802145B0(Buffer_80214554 *pBuffer);
void fn_802145F4(Buffer_80214554 *pBuffer);
int fn_80214600(Buffer_80214554 *pBuffer);
unsigned char *fn_80214610(Buffer_80214554 *pBuffer, int size);
void fn_8021465C(Buffer_80214554 *pBuffer, unsigned char *pEnd);
unsigned char *fn_80214680(Buffer_80214554 *pBuffer, int size);

/* tmlightdef.c */
typedef struct LightDef_802146C8 {
    int mUnknown0;
    void *mpUnknown4;
    int mUnknown8;
    void *mpUnknownC;
} LightDef_802146C8;

void fn_802146C8(LightDef_802146C8 *pDef, void *pOldBase, void *pNewBase);

/* tmblendchannel.c */
typedef struct BlendChannel_80214D40 {
    TMGeomAttr_t *mpAttr;
    unsigned char *mpCursor;
    int mSize;
    unsigned char *mpBase;
    int mCapacity;
    unsigned char *mpOutput;
    int mOutputSize;
} BlendChannel_80214D40;

typedef struct BlendSource_80214E80 {
    int mNumAttrs;
    TMGeomAttr_t *mpAttrs;
    void **mppOutputs;
    void **mppInputs;
} BlendSource_80214E80;

BlendChannel_80214D40 *fn_80214DB8(int id);
int fn_80214DCC(int id, int index);
unsigned char *fn_80214E3C(int id, unsigned char *pData, int size);
void fn_80214E80(TMGeomAttr_t *pAttrs, void **ppInputs, void **ppOutputs, int numAttrs);
void fn_80214EB4(int index, void *pOutput);
void fn_80214ED0(void);
void fn_80214F54(void);

/* tmblend.c */
typedef struct BlendItem_80214718 {
    short mIndex;
    short mWeight;
    short mFirstAttr;
    short mNumAttrs;
} BlendItem_80214718;

typedef struct BlendState_80214718 {
    TMGeom_t *mpGeom;
    Buffer_80214554 *mpBuffer;
    int mFlushed;
    unsigned int mNumWeights;
    short *mpWeights;
    int mBaseIndex;
    unsigned int mMaxItems;
    short maWeights[128];
} BlendState_80214718;

void fn_802149D4(short *pWeights, unsigned int numWeights);
int fn_802149E8(float *pWeights, unsigned int numWeights);
void fn_80214A7C(Buffer_80214554 *pBuffer);
void fn_80214AC8(void);
void fn_80214B20(void);
void fn_80214B44(TMModel_t *pModel);
void fn_80214B6C(TMModel_t *pBase, TMModel_t *pModel);
void fn_80214C04(unsigned int maxItems);
int fn_80214C10(int nodeIndex);
int fn_80214CB4(void);

/* tmblendop.c */
unsigned int fn_80215554(int dstId, int srcId, int weight);
void fn_80215694(int dstId, int srcId);
void fn_8021574C(int dstId, int srcId);

/* tmextentsdef.c */
typedef struct ExtentsDef_80215804 {
    int mUnknown0;
    void *mpExtents;
} ExtentsDef_80215804;

void fn_80215804(ExtentsDef_80215804 *pDef, void *pOldBase, void *pNewBase);

/* TMTexXForm.c */
typedef struct TexXFormEntry_80215838 {
    const char *mpName;
    unsigned char maUnknown4[0x14];
} TexXFormEntry_80215838;

typedef struct TexXFormDef_80215838 {
    unsigned int mNumEntries;
    TexXFormEntry_80215838 maEntries[1];
} TexXFormDef_80215838;

void fn_80215838(TexXFormDef_80215838 *pDef, void *pOldBase, void *pNewBase);
int fn_802158A4(const char *pName);

/* lltmviewport.c, tmprof.c */
void fn_80215B6C(int unknown);
void fn_80215B70(void);
void fn_80215B74(void);
void fn_80215B78(void);

/* tmdebuginfo.c */
typedef struct DebugInfo_80215B7C {
    void *mpNames;
    int mNumNames;
    void *mpStrings;
    int mNumStrings;
} DebugInfo_80215B7C;

void fn_80215B7C(DebugInfo_80215B7C *pInfo, void *pOldBase, void *pNewBase);

/* TmInstance.c */
typedef struct InstanceTarget_80215C14 {
    int mUnknown0;
    void *mpData;
} InstanceTarget_80215C14;

typedef struct Instance_80215C14 {
    int mUnknown0;
    void *mpUnknown4;
    void *mpUnknown8;
    InstanceTarget_80215C14 *mpTarget;
    Skeleton_80215E5C *mpSkel;
} Instance_80215C14;

typedef struct RenderInstEntry_80215CB0 {
    unsigned char maUnknown0[0x20];
    int maUsed[4];
    void *mapData[4];
} RenderInstEntry_80215CB0;

typedef struct RenderInst_80215CB0 {
    int mNumEntries;
    RenderInstEntry_80215CB0 *mpEntries;
    int mNumPointers;
    void *mapPointers[1];
} RenderInst_80215CB0;

void fn_80215C14(Instance_80215C14 *pInst, void *pOldBase, void *pNewBase);
void fn_80215CB0(RenderInst_80215CB0 *pInst, void *pOldBase, void *pNewBase);

/* TMMorphAnim.c */
typedef struct MorphTarget_80215DA4 {
    int mNumData;
    void *mapData[1];
} MorphTarget_80215DA4;

typedef struct MorphAnim_80215DA4 {
    int mNumTargets;
    MorphTarget_80215DA4 *mapTargets[1];
} MorphAnim_80215DA4;

void *fn_80215DA4(void *p, void *pOldBase, void *pNewBase);
void fn_80215DC0(MorphAnim_80215DA4 *pAnim, void *pOldBase, void *pNewBase);

#endif
