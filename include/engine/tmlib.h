#ifndef ENGINE_TMLIB_H
#define ENGINE_TMLIB_H

#include <dolphin/gx/GXStruct.h>

typedef struct Pool_801C750C Pool_801C750C;

#include "game/Object_8020E52C.h"

typedef struct Texture_8020DB34 {
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned char mWrapS;
    unsigned char mWrapT;
    unsigned char mMinFilter;
    unsigned char mMagFilter;
    unsigned int mFormat;
    void *mpImage;
    int mUnknown10;
    void *mpPalette;
    int mUnknown18;
    unsigned char mbDirty;
} Texture_8020DB34;

typedef struct TexInfo_8020E2B0 {
    int mUnknown00;
    unsigned char *mpData;
} TexInfo_8020E2B0;

typedef struct TexHeader_8020E2B0 {
    char maTag[4];
    unsigned short mVersion;
    unsigned short mFlags;
    unsigned char mWrapS;
    unsigned char mWrapT;
    unsigned char mMinFilter;
    unsigned char mMagFilter;
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
    unsigned char mbFixed;
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
    void *mpData;
} Texture_80212234;

typedef struct Clut_80212534 {
    int mType;
    union {
        GXTlutObj maTlut[2];
        GXTexObj mObj;
    } u;
    unsigned int mSize;
} Clut_80212534;

typedef struct TexFilterDesc_80212310 {
    int mMinFilter;
    int mMagFilter;
    float mLodBias;
    int mMaxAniso;
    unsigned char mbBiasClamp;
    unsigned char mbEdgeLod;
} TexFilterDesc_80212310;

typedef struct TexWrapDesc_80212374 {
    int mWrapS;
    int mWrapT;
} TexWrapDesc_80212374;

typedef struct TexNode_802119C4 {
    const char *mpName;
    struct TexLib_802119C4 *mpLib;
    short mTextureIndex;
    short mFirstClut;
    short mNumCluts;
    short mUnknownE;
} TexNode_802119C4;

typedef struct TexLib_802119C4 {
    Registry_8021283C mRegistry;
    int mNumTextures;
    Texture_80212234 *mpTextures;
    int mNumCluts;
    Clut_80212534 *mpCluts;
    int mNumTexNodes;
    TexNode_802119C4 *mpTexNodes;
} TexLib_802119C4;

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

typedef struct SwapAttr_8020ED10 {
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
} SwapAttr_8020ED10;

typedef struct SwapNode_8020ED10 {
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
} SwapNode_8020ED10;

typedef struct SwapPart_8020ED10 {
    SwapNode_8020ED10 *mpNodes;
    unsigned int mNumNodes;
    SwapAttr_8020ED10 *mpAttrs;
    int mNumAttrs;
    unsigned int mFlags;
    void *mpUnknown14;
} SwapPart_8020ED10;

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

typedef struct MaterialParm_8020FAAC {
    Texture_80212234 *mpTexture;
    Clut_80212534 *mpClut;
    int mXForm;
} MaterialParm_8020FAAC;

typedef struct Material_8020FAAC {
    int mRefCount;
    MaterialDef_80213228 *mpDef;
    Shader_80211638 *mpShader;
    int mNumParms;
    MaterialParm_8020FAAC *mpParms;
    void *maUnknown14[4];
} Material_8020FAAC;

typedef struct MaterialList_8020FF34 {
    int mNumMaterials;
    Material_8020FAAC **mppMaterials;
} MaterialList_8020FF34;

typedef struct Model_8020F28C {
    void *mpInfo;
    void *mpExtn;
    SwapPart_8020ED10 *mpGeom;
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
} Model_8020F28C;

/* tmmodelres.c */
void fn_8020EB08(int maxChunkTypes);
void fn_8020EB48(int tag, ChunkRelocFunc_8020EA18 relocate, int version);
void fn_8020EB70(void);
void *fn_8020EB94(void *p, void *pOldBase, void *pNewBase);
void fn_8020EBB0(ModelRes_8020EA18 *pRes);
void *fn_8020EC50(ModelRes_8020EA18 *pRes, int tag, Chunk_8020EA18 **ppChunk);

/* tmswappart.c */
void fn_8020EFC8(int size);
void fn_8020F00C(void);
void fn_8020F08C(SwapPart_8020ED10 *pPart, void *pOldBase, void *pNewBase);
void fn_8020F178(SwapPart_8020ED10 *pPart, unsigned short *pRemap, int numMaterials);
void fn_8020F1D8(SwapPart_8020ED10 *pPart, int nodeIndex, Extent_802144AC *pExtent);

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
void fn_8021216C(TexLib_802119C4 *pLib, TexFilterDesc_80212310 *pDesc);
void fn_802121D0(TexLib_802119C4 *pLib, TexWrapDesc_80212374 *pDesc);

/* tmtexture.c */
void fn_80212234(Texture_80212234 *pTexture, int minFilter, int magFilter, float lodBias, unsigned char bBiasClamp, unsigned char bEdgeLod, int maxAniso);
void fn_80212310(Texture_80212234 *pTexture, TexFilterDesc_80212310 *pDesc);
void fn_8021234C(Texture_80212234 *pTexture, int wrapS, int wrapT);
void fn_80212374(Texture_80212234 *pTexture, TexWrapDesc_80212374 *pDesc);
void fn_8021239C(Texture_80212234 *pTexture, void *pData, int width, int height, int format, int numMips, void *pBuffer, Clut_80212534 *pClut);
void fn_8021242C(Texture_80212234 *pTexture, void *pData, int width, int height, int format, int numMips, void *pBuffer, Clut_80212534 *pClut);
void fn_80212530(Texture_80212234 *pTexture);
void fn_80212534(Clut_80212534 *pClut, void *pData, int format, int numEntries, unsigned int size);
void fn_80212654(Clut_80212534 *pClut);
void fn_80212658(Texture_80212234 *pTexture);
void fn_802126BC(Texture_80212234 *pTexture, const char *pName);

/* tmname.c */
int fn_802126C0(const char *pName, const char *pOther);
int fn_802126E8(const char *pName, const char *pPattern);
void fn_8021272C(const char *pPath, char *pDir, char *pFile);

/* tmmemory.c */
void *fn_802127D0(int count, int size);
void fn_80212814(void *p);

/* tmregistry.c */
void fn_80212850(Registry_8021283C *pRegistry, int maxEntries, int bFixed, int bPaths);
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
ShaderParmDef_80211638 *fn_80212CB4(ShaderDef_80211638 *pDef, const char *pName, int type);

/* tmshaderstock.c */
void fn_80213160(void);
void fn_802131D8(void);

/* tmshaderparm.c */
int fn_80213214(int type);

/* tmshadercode.c */
void fn_80213224(int code);

/* tmmodel.c */
void fn_8020F28C(Model_8020F28C *pModel);
void fn_8020F2C4(Model_8020F28C *pDst, Model_8020F28C *pSrc);
int fn_8020F330(Model_8020F28C *pModel, ModelRes_8020EA18 *pRes, unsigned int tag);
void fn_8020F4D0(Model_8020F28C *pModel, ModelRes_8020EA18 *pRes);
void fn_8020F5F0(int maxChunkTypes);
void fn_8020F76C(void);
void fn_8020F78C(Model_8020F28C *pModel, MaterialLib_80213228 *pMatLib);
void fn_8020F824(Model_8020F28C *pModel, Skeleton_80215E5C *pSkel);
void fn_8020F89C(Model_8020F28C *pModel);
void fn_8020F8E0(Model_8020F28C *pModel);
void fn_8020F92C(Model_8020F28C *pModel);
void fn_8020F96C(Model_8020F28C *pModel, Extent_802144AC *pExtent, int state, int arg);

/* tmmaterialdef.c */
void fn_80213228(MaterialLib_80213228 *pLib, void *pOldBase, void *pNewBase);
int fn_8021330C(MaterialLib_80213228 *pLib, const char *pName);

/* tmclusterdef.c */
void fn_80213384(ClusterDef_80213384 *pDef, void *pOldBase, void *pNewBase);
void fn_802133B8(ClusterDef_80213384 *pDef, short *pRemap);

/* tmxform.c */
void fn_8020FA38(u32 id, f32 (*pMtx)[4]);
void fn_8020FA8C(u32 id);

/* tmmaterial.c */
int fn_8020FAAC(Material_8020FAAC *pMaterial, const char *pName);
void fn_8020FB14(Material_8020FAAC *pMaterial);
void fn_8020FC1C(int *pPoolSizes);
void fn_8020FCA0(Material_8020FAAC *pMaterial);
void fn_8020FD40(Material_8020FAAC *pMaterial);
void fn_8020FD48(const char *pName, Texture_80212234 *pTexture, Clut_80212534 *pClut);
void fn_8020FDAC(const char *pName, Clut_80212534 *pClut);
void fn_8020FE04(const char *pPath);
void fn_8020FE3C(Shader_80211638 *pShader);
void fn_8020FE78(MaterialDef_80213228 *pDef);

/* tmmateriallist.c */
Material_8020FAAC *fn_8020FF34(Material_8020FAAC *pMaterial);
void fn_8020FF90(Material_8020FAAC *pMaterial);
void fn_8020FFE4(int maxMaterials);
void fn_80210020(void);
void fn_80210054(MaterialList_8020FF34 *pList, unsigned int numMaterials);
void fn_802100C0(MaterialList_8020FF34 *pList, MaterialLib_80213228 *pLib);
void fn_80210114(MaterialList_8020FF34 *pList);
Material_8020FAAC *fn_80210184(MaterialList_8020FF34 *pList, int index);
void fn_802101B0(MaterialList_8020FF34 *pList, int index);
void fn_80210214(MaterialList_8020FF34 *pList, MaterialLib_80213228 *pLib);

typedef void (*MaterialBindFunc_80210298)(Material_8020FAAC *pMaterial);

typedef struct ClusterObj_80210724 {
    void *mpMatrices;
    void *mpCacheMatrices;
    int mNumMatrices;
} ClusterObj_80210724;

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

typedef struct RenderViewport_80210298 {
    float mLeft;
    float mTop;
    float mWidth;
    float mHeight;
    float mNear;
    float mFar;
} RenderViewport_80210298;

typedef struct RenderState_80210298 {
    SwapPart_8020ED10 *mpGeom;
    ClusterObj_80210724 *mpClusterObj;
    Skeleton_80215E5C *mpSkel;
    Swap_802160A0 *mpSwap;
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

typedef struct ChannelList_8021592C {
    int mCount;
    SwapAttr_8020ED10 *mapAttrs[8];
    void *mapData[8];
    unsigned char maCompType[8];
    unsigned char maStride[8];
    unsigned char maFrac[8];
} ChannelList_8021592C;

typedef void (*RenderHookFunc_80211138)(struct RenderHook_80211138 *pHook, SwapNode_8020ED10 *pNode,
                                        ChannelList_8021592C *pList);

typedef struct RenderHook_80211138 {
    unsigned char maUnknown0[0xC];
    RenderHookFunc_80211138 mFunc;
} RenderHook_80211138;

/* tmrendergeom.c */
void fn_80210D30(SwapNode_8020ED10 *pNode, ChannelList_8021592C *pList);
void fn_80210DCC(RenderState_80210298 *pState, SwapNode_8020ED10 *pNode);
void fn_80211138(RenderState_80210298 *pState, SwapNode_8020ED10 *pNode);
void fn_8021126C(void);
void fn_802112DC(unsigned short *pIndices, unsigned int count);
void fn_80211350(void);
void fn_802113C0(int state, int arg);
void fn_80211424(unsigned short *pIndices, unsigned int count);

/* tmclusterobj.c */
void fn_80213444(int maxMatrices, int numBuffers);
void fn_802134AC(void);
void fn_802134D0(ClusterObj_80210724 *pObj);
void fn_802134E8(void);
void fn_80213504(ClusterObj_80210724 *pObj, int numMatrices);
void fn_8021353C(ClusterObj_80210724 *pObj, Pose_8021353C *pPose, BoneList_8021353C *pBones, short (*pBlend)[3]);

/* tmchannellist.c */
void fn_8021592C(ChannelList_8021592C *pList, SwapNode_8020ED10 *pNode, SwapAttr_8020ED10 *pAttrs, void **ppChannels);
void fn_80215A14(ChannelList_8021592C *pList);
void fn_80215B00(ChannelList_8021592C *pList);

/* tmgeometry.c */
void fn_802160A0(Swap_802160A0 *pSwap, void *pOldBase, void *pNewBase);
SwapSlot_802160A0 *fn_8021616C(Swap_802160A0 *pSwap, int slot);
SwapState_802160A0 *fn_80216190(Swap_802160A0 *pSwap, int slot, int state);
int fn_802161D8(Swap_802160A0 *pSwap, unsigned short *pNodes, int slot, int state);

/* tmskeleton.c */
void fn_80215E5C(Skeleton_80215E5C *pSkel, void *pOldBase, void *pNewBase);
short *fn_80215EE0(Skeleton_80215E5C *pSkel, Skeleton_80215E5C *pOther);
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
    SwapAttr_8020ED10 *mpAttr;
    unsigned char *mpCursor;
    int mSize;
    unsigned char *mpBase;
    int mCapacity;
    unsigned char *mpOutput;
    int mOutputSize;
} BlendChannel_80214D40;

typedef struct BlendSource_80214E80 {
    int mNumAttrs;
    SwapAttr_8020ED10 *mpAttrs;
    void **mppOutputs;
    void **mppInputs;
} BlendSource_80214E80;

void *fn_80214D40(SwapAttr_8020ED10 *pAttr, int index);
unsigned char *fn_80214D6C(int id, unsigned char *pData, int capacity);
BlendChannel_80214D40 *fn_80214DB8(int id);
int fn_80214DCC(int id, int index);
unsigned char *fn_80214E3C(int id, unsigned char *pData, int size);
void fn_80214E80(SwapAttr_8020ED10 *pAttrs, void **ppInputs, void **ppOutputs, int numAttrs);
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
    SwapPart_8020ED10 *mpGeom;
    Buffer_80214554 *mpBuffer;
    int mFlushed;
    unsigned int mNumWeights;
    short *mpWeights;
    int mBaseIndex;
    unsigned int mMaxItems;
    short maWeights[128];
} BlendState_80214718;

unsigned int fn_80214718(SwapNode_8020ED10 *pNode, int baseIndex, short *pWeights, unsigned int numWeights, BlendItem_80214718 *pItems, unsigned int maxItems);
unsigned int fn_80214814(BlendItem_80214718 *pItems, unsigned int numItems, unsigned int maxItems);
void fn_80214890(void);
unsigned int fn_802148BC(Buffer_80214554 *pBuffer, BlendItem_80214718 *pItems, unsigned int numItems);
void fn_802149D4(short *pWeights, unsigned int numWeights);
int fn_802149E8(float *pWeights, unsigned int numWeights);
void fn_80214A7C(Buffer_80214554 *pBuffer);
void fn_80214AC8(void);
void fn_80214B20(void);
void fn_80214B44(Model_8020F28C *pModel);
void fn_80214B6C(Model_8020F28C *pBase, Model_8020F28C *pModel);
void fn_80214C04(unsigned int maxItems);
int fn_80214C10(int nodeIndex);
int fn_80214CB4(void);

/* tmblendop.c */
void fn_80214F58(int *pAccum, short *pSrc, unsigned int count, int weight, int frac);
void fn_80214FB8(int *pAccum, short *pSrc, unsigned int count, int weight, int frac);
void fn_80215020(int *pAccum, short *pSrc, unsigned int count);
void fn_802150AC(int *pDst, short *pSrc, unsigned int count, int frac);
void fn_802150F0(int *pDst, float *pSrc, unsigned int count, int frac);
void fn_80215190(float *pDst, int *pSrc, unsigned int count, int frac);
void fn_80215258(short *pDst, int *pSrc, unsigned int count, int frac);
void fn_802152F0(int *pAccum, signed char *pSrc, unsigned int count, int weight, int frac);
void fn_8021535C(int *pAccum, signed char *pSrc, unsigned int count, int weight, int frac);
void fn_802153D0(int *pAccum, signed char *pSrc, unsigned int count);
void fn_8021546C(int *pDst, signed char *pSrc, unsigned int count, int frac);
void fn_802154BC(signed char *pDst, int *pSrc, unsigned int count, int frac);
unsigned int fn_80215554(int dstId, int srcId, int weight);
void fn_80215694(int dstId, int srcId);
void fn_8021574C(int dstId, int srcId);

/* tmextentsdef.c */
typedef struct ExtentsDef_80215804 {
    int mUnknown0;
    void *mpExtents;
} ExtentsDef_80215804;

void fn_80215804(ExtentsDef_80215804 *pDef, void *pOldBase, void *pNewBase);

/* tmtexxform.c */
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
void fn_80215B6C(void);
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

/* tminstance.c */
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

/* tmmorphanim.c */
typedef struct MorphTarget_80215DA4 {
    int mNumData;
    void *mapData[1];
} MorphTarget_80215DA4;

typedef struct MorphAnim_80215DA4 {
    int mNumTargets;
    MorphTarget_80215DA4 *mapTargets[1];
} MorphAnim_80215DA4;

void fn_80215DC0(MorphAnim_80215DA4 *pAnim, void *pOldBase, void *pNewBase);

#endif
