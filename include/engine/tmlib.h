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
void MemFill(void *p, unsigned int size, int c, int d);

Pool_801C750C *DSNewNodeHandler(int a, int count, int size, void *pMemory);
int DSDelNodeHandler(Pool_801C750C *pPool);
void *DSNewNode(Pool_801C750C *pPool);
void DSDelNode(Pool_801C750C *pPool, void *pElement);

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
    TMMaterialDef_t *mpDef;
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
TMShaderParmDef_t *TMShaderDefGetParmByName(TMShaderDef_t *pDef, const char *pName, int type);

/* tmshaderstock.c */
void TMShaderStockInit(void);
void TMShaderStockShutdown(void);

/* tmshaderparm.c */
int TMShaderParmGetSize(int type);

/* tmshadercode.c */
void TMShaderCodeLoad(int code);

/* tmmodel.c */
void TMModelReset(TMModel_t *pModel);
void TMModelClone(TMModel_t *pDst, TMModel_t *pSrc);
int TMModelBindModelChunk(TMModel_t *pModel, TMModelRes_t *pRes, unsigned int tag);
void TMModelBindModelRes(TMModel_t *pModel, TMModelRes_t *pRes);
void TMModelInit(int maxChunkTypes);
void TMModelShutdown(void);
void TMModelRemapMaterials(TMModel_t *pModel, TMMaterialDefList_t *pMatLib);
void TMModelRemapClusters(TMModel_t *pModel, void *pOther);
void TMModelResetChannels(TMModel_t *pModel);
void TMModelAllocChannels(TMModel_t *pModel);
void TMModelFreeChannels(TMModel_t *pModel);
void TMModelAddExtent(TMModel_t *pModel, Extent_802144AC *pExtent, int state, int arg);

/* tmmaterialdef.c */
void TMMaterialDefRelocateChunk(TMMaterialDefList_t *pLib, void *pOldBase, void *pNewBase);
int TMMaterialDefGetIndexByName(TMMaterialDefList_t *pLib, const char *pName);

/* tmclusterdef.c */
void TMClusterDefRelocateChunk(TMClusterDef_t *pDef, void *pOldBase, void *pNewBase);
void TMClusterDefRemap(TMClusterDef_t *pDef, short *pRemap);

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
void TMMaterialSetMatDef(TMMaterialDef_t *pDef);

/* tmmateriallist.c */
void TMMaterialListInit(int maxMaterials);
void TMMaterialListShutdown(void);
void TMMaterialListAlloc(TMMaterialList_t *pList, unsigned int numMaterials);
void TMMaterialListAllocDefs(TMMaterialList_t *pList, TMMaterialDefList_t *pLib);
void TMMaterialListFree(TMMaterialList_t *pList);
TMMaterial_t *TMMaterialListGetMaterial(TMMaterialList_t *pList, int index);
void TMMaterialListSelect(TMMaterialList_t *pList, int index);
void TMMaterialListSetMatDefs(TMMaterialList_t *pList, TMMaterialDefList_t *pLib);

typedef void (*TMMaterialBindFunc_t)(TMMaterial_t *pMaterial);

typedef struct TMClusterObj_t {
    void *mpMatrices;
    void *mpCacheMatrices;
    int mNumMatrices;
} TMClusterObj_t;

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
    TMSkeleton_t *mpSkel;
    TMSwapDef_t *mpSwap;
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

typedef struct TMChannelList_t {
    int mCount;
    TMGeomAttr_t *mapAttrs[8];
    void *mapData[8];
    unsigned char maCompType[8];
    unsigned char maStride[8];
    unsigned char maFrac[8];
} TMChannelList_t;

typedef void (*RenderHookFunc_80211138)(struct RenderHook_80211138 *pHook, TMGeomNode_t *pNode,
                                        TMChannelList_t *pList);

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
void TMClusterObjInit(int maxMatrices, int numBuffers);
void TMClusterObjShutdown(void);
void TMClusterObjInitObj(TMClusterObj_t *pObj);
void TMClusterObjResetMatrices(void);
void TMClusterObjAllocMatrices(TMClusterObj_t *pObj, int numMatrices);
void TMClusterObjSynthesizeMatrices(TMClusterObj_t *pObj, TMClusterPose_t *pPose, TMClusterBoneList_t *pBones, short (*pBlend)[3]);
void TMClusterObjSynthesizeMatricesSlerp(TMClusterObj_t *pObj, TMClusterPose_t *pPose, TMClusterBoneList_t *pBones, short (*pBlend)[3],
                 unsigned char *pFlags);

/* tmchannellist.c */
void TMChannelListBuild(TMChannelList_t *pList, TMGeomNode_t *pNode, TMGeomAttr_t *pAttrs, void **ppChannels);
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
    TMGeomAttr_t *mpAttr;
    unsigned char *mpCursor;
    int mSize;
    unsigned char *mpBase;
    int mCapacity;
    unsigned char *mpOutput;
    int mOutputSize;
} TMBlendChannel_t;

typedef struct TMBlendChannelSource_t {
    int mNumAttrs;
    TMGeomAttr_t *mpAttrs;
    void **mppOutputs;
    void **mppInputs;
} TMBlendChannelSource_t;

TMBlendChannel_t *TMBlendChannelGetBuffer(int id);
int TMBlendChannelSet(int id, int index);
unsigned char *TMBlendChannelSetMem(int id, unsigned char *pData, int size);
void TMBlendChannelSetChannels(TMGeomAttr_t *pAttrs, void **ppInputs, void **ppOutputs, int numAttrs);
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
    TMGeom_t *mpGeom;
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
void TMBlendBindModel(TMModel_t *pModel);
void TMBlendBindModel2(TMModel_t *pBase, TMModel_t *pModel);
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
