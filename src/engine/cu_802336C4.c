/* Partial source for model, level-of-detail and render wrappers over the TM renderer, not yet cut into their files. */

#include "engine/fn_801F8D60.h"
#include "engine/tdbext.h"
#include "engine/dbutil.h"
#include "engine/fn_801F9134.h"

#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>
#include "engine/Funcs_802FB3BC.h"
#include "game/fn_8022F478.h"
#include "game/fn_80233CBC.h"
#include "game/fn_801FCE10.h"
#include "engine/texfile.h"
#include "game/Object_80233EAC.h"
#include "game/Object_80235588.h"
#include "game/QueryStatus.h"

#include "engine/Entry_802FB300.h"

#include "engine/Handlers_802294D8.h"
#include "game/Request_802329F0.h"

typedef struct Block_80233588 {
    int mUnknown0;
    char *mpUnknown4;
    int mUnknown8;
} Block_80233588;

extern Handlers_802294D8 lbl_802FB38C;
int fn_80233588(Block_80233588 *p);
int fn_802336BC(void);

typedef struct Block_802336C4 {
    void *mpUnknown0;
    unsigned int mUnknown4;
    char mUnknown8[8];
    char mUnknown10[0x34];
} Block_802336C4;

typedef struct Model_802337D4 {
    char mUnknown0[12];
    int *mpUnknown12;
    void *mpUnknown16;
} Model_802337D4;

typedef struct Joints_802337D4 {
    int mUnknown0;
    int mUnknown4;
} Joints_802337D4;

typedef struct Values_80233C7C {
    unsigned int mUnknown0[2];
    unsigned char mUnknown8[64];
} Values_80233C7C;

typedef struct List_80233BE4 {
    unsigned int mUnknown0;
} List_80233BE4;

typedef struct Model_80233BE4 {
    char mUnknown0[20];
    List_80233BE4 *mpUnknown20;
} Model_80233BE4;

typedef struct Box_80234070 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    char mUnknown12[4];
    float mUnknown16;
    float mUnknown20;
    char mUnknown24[8];
} Box_80234070;

/* Record updated by 0x8023424C and searched by 0x80234394; partial layout. */
typedef struct Instance_8023424C {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    unsigned int mUnknown20;
    Object_80233EAC *mpUnknown24;
    float *mpUnknown28;
    void *mpUnknown32;
    void *mpUnknown36;
} Instance_8023424C;

typedef struct Desc_802345F8 {
    const char *mpUnknown0;
    char mUnknown4[16];
    void *mpUnknown20;
    struct Resource_802347EC *mpUnknown24;
    void *mpUnknown28;
} Desc_802345F8;

typedef struct Resource_802347EC {
    char mUnknown0[36];
    void *mpUnknown36;
} Resource_802347EC;

typedef struct Entry_8023465C {
    char mUnknown0[8];
    short mUnknown8;
    char mUnknown10[2];
    const char *mpUnknown12;
    char mUnknown16[32];
} Entry_8023465C;

typedef struct List_8023465C {
    int mUnknown0;
    Entry_8023465C *mpUnknown4;
} List_8023465C;

typedef struct Model_8023465C {
    char mUnknown0[24];
    List_8023465C *mpUnknown24;
} Model_8023465C;

typedef struct Object_8023465C {
    unsigned int mUnknown0;
} Object_8023465C;

typedef struct Array_8023491C {
    unsigned int mUnknown0;
    float *mpUnknown4;
    int mUnknown8;
} Array_8023491C;

typedef struct Part_80234A30 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    void *mpUnknown12;
    int mUnknown16;
    Values_80233C7C mUnknown20;
    int mUnknown92;
    short mUnknown96[64];
    void *mpUnknown224;
    void *mpUnknown228;
    void *mpUnknown232[2];
} Part_80234A30;

typedef struct Object_80234B20 {
    char mUnknown0[64];
    Mtx44 mUnknown64;
} Object_80234B20;

typedef struct Header_80234DFC {
    char mUnknown0[8];
    int mUnknown8;
} Header_80234DFC;

typedef struct Sprite_80234DFC {
    char mUnknown0[40];
    void *mpUnknown40;
    void *mpUnknown44;
} Sprite_80234DFC;

typedef struct Holder_80234EEC {
    char mUnknown0[88];
    Sprite_80234DFC *mpUnknown88;
} Holder_80234EEC;

typedef struct Table_803E96E8 {
    char mUnknown0[12];
    struct Group_803E96E8 *mpUnknown12;
} Table_803E96E8;

typedef struct Group_803E96E8 {
    char mUnknown0[12];
    unsigned short *mpUnknown12;
} Group_803E96E8;

typedef struct Range_80216190 {
    char mUnknown0[16];
    unsigned short mUnknown16;
    unsigned short mUnknown18;
} Range_80216190;

typedef struct Source_80235328 {
    char *mpUnknown0;
} Source_80235328;

typedef struct Owner_80235328 {
    char mUnknown0[8];
    Source_80235328 *mpUnknown8;
} Owner_80235328;

typedef struct Cache_8022F8A8 {
    unsigned short mUnknown0;
    char mUnknown2[2];
    int mUnknown4;
    int mUnknown8;
    void *mpUnknown12[2];
    void *mpUnknown20[2];
    void *mpUnknown28[2];
    union {
        int mWord;
        unsigned char mBytes[4];
    } mUnknown36;
    char mUnknown40[56];
    struct Cache_8022F8A8 *mpUnknown96;
    struct Cache_8022F8A8 *mpUnknown100;
} Cache_8022F8A8;

typedef struct Entry_802FB310 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
} Entry_802FB310;

extern char lbl_802B5D88[];
extern char lbl_802B5DB0[];
extern char lbl_802B6520[];
extern char lbl_802B6E10[];
extern char lbl_802B6E34[];
extern char lbl_802B6E74[];
extern char lbl_802B6E90[];
extern char lbl_802B6EA0[];
extern char lbl_802B6EE0[];
extern char lbl_802B6F00[];
extern char lbl_802B6F30[];
extern char lbl_802B6F54[];
extern char lbl_802B6F78[];
extern char lbl_802B6FB0[];
extern char lbl_802B6FF4[];
extern char lbl_802B7050[];
extern char lbl_802B706C[];
extern char lbl_802B709C[];
extern char lbl_802B70DC[];
extern char lbl_802B70FC[];
extern char lbl_802B7128[];
extern char lbl_802B7130[];
extern char lbl_802B7154[];
extern char lbl_802B715C[];
extern Entry_802FB300 lbl_802FB300[];
extern Entry_802FB310 lbl_802FB310[];
extern int lbl_802FB398[];
extern int lbl_802FB3A4[];
extern int lbl_802FB3B0[];
extern Funcs_802FB3BC lbl_802FB3BC;
extern Funcs_802FB3BC lbl_802FB3D0;
extern Funcs_802FB3BC lbl_802FB3E4;
extern int lbl_802FB3F8[];
extern void *lbl_803A2648[];
extern Table_803E96E8 lbl_803E96E8;
extern int lbl_803EC0C8;
extern char *lbl_803EC0CC;
extern int lbl_803EC0D0;
extern int lbl_803EC0D4;
extern unsigned char lbl_803EC0D8;
extern Cache_8022F8A8 *lbl_803EC0E0;
extern int lbl_803EC0E4;
extern int lbl_803EC0E8;
extern int lbl_803EC0F0;
extern void *lbl_803EC0F4;
extern int lbl_803ED020;
extern int lbl_803ED024;
extern int lbl_803ED6E4[2];

double fabs(double);

extern void MatPush(void);
extern void MatPushUnit(void);
extern void MatPop(void);
extern void MatCat(Mtx44 m);
extern void MatStore(Mtx44 m);
extern void MatLoadSlot(int a);
extern void *fn_801D2B7C(int size, int a, int b);
extern int fn_801D2BD0(void *p);
extern int ResLoad(void *pData, int index, int a);
extern int ResCopyToBuffer(void *pArchive, int id, void *pDest);
extern int ResUnLoad(void *pData, int index);
extern int ResIsLoaded(void *pData, int index);
extern int fn_801F9014(int handle);
extern int fn_801F91AC(int handle, int a, int b);
extern int fn_801F9430(int a, int *pTable4, int *pTable8);
extern int fn_801F9574(void);
extern int fn_801F9980(int handle, int *pTable);
extern int fn_801F9A90(int handle, int table);
extern int fn_801F9D0C(int handle, int table, int a);
extern int fn_801FA68C(void *pCallback, int tag);
extern int fn_801FA740(int tag);
extern void LLTexCopyFlush(void *pDst, void *pSrc, unsigned int size);
extern void TMModelResRelocate(void *p);
extern void *TMModelResGetChunk(void *p, unsigned int tag, void *pOut);
extern void TMModelReset(void *p);
extern void TMModelClone(void *pDst, void *pSrc);
extern void TMModelBindModelRes(void *p, void *pData);
extern void TMModelRemapMaterials(void *p, void *pRef);
extern void TMModelRemapClusters(void *p, void *q);
extern void TMModelResetChannels(void *p);
extern void TMModelAllocChannels(void *p);
extern void TMModelFreeChannels(void *p);
extern void TMModelAddExtent(void *p, void *q, int a, int b);
extern void TMMaterialBindTextureClut(const char *pName, void *pTexture, void *pPalette);
extern void TMMaterialBindShader(int handle);
extern void TMMaterialListAlloc(void *p, int a);
extern void TMMaterialListFree(void *p);
extern void TMMaterialListSelect(void *p, int a);
extern void TMRenderBindModel(void *p);
extern void TMRenderBindClusterObj(void *p);
extern void TMRenderBindMaterialList(void *p);
extern void TMRenderGeomList(short *pValues, int count);
extern void TMRenderGeomListDirect(short *pValues, int count);
extern int TMShaderLibGetShader(const char *pName);
extern void TMTexLibLoad(void *p, int a);
extern void TMTexLibUnload(void *p);
extern void *TMTexLibGetTextureByTexNode(void *p);
extern void *TMTexLibGetClutByTexNode(void *p, int a);
extern void TMClusterObjInitObj(void *p);
extern void TMClusterObjAllocMatrices(Joints_802337D4 *pJoints, int a);
extern void TMClusterObjSynthesizeMatrices(Joints_802337D4 *pJoints, void *p, int *q, void *pPose);
extern void TMClusterObjSynthesizeMatricesSlerp(Joints_802337D4 *pJoints, void *p, int *q, void *pPose, unsigned char *pFlags);
extern void TMTevSetTevOp(int a, int b, int c);
extern void TMClipProjection(int a);
extern void TMClipMatrix(int a);
extern void TMClipMatrixWorld(int a, void *p, void *q);
extern unsigned int TMClipBBox(void *p, void *q, int a);
extern void TMClipResetExtent(void *p);
extern void TMBufferNew(void *p, int a, int b);
extern void TMBufferDelete(void *p);
extern void TMBufferReset(void *p);
extern void TMBlendSetWeights(short *pValues, int count);
extern void TMBlendBegin(void *p);
extern void TMBlendEnd(void);
extern void TMBlendBindModel(void *p);
extern void TMBlendGeomAll(void);
extern Range_80216190 *TMSwapGetState(Group_803E96E8 *pGroup, int a, int key);
extern int TMSwapGetGeomRefs(List_80233BE4 *pList, short *pOut, unsigned int index, int value);
extern int fn_802293A8(void);
extern void fn_802293B0(void);
extern int fn_8022942C(void);
extern void fn_80229434(void);
extern int fn_80229554(void);
extern int fn_802296B4(int a, int b);
extern void fn_80229718(Funcs_802FB3BC *pFuncs);
extern void fn_80229744(void);
extern int fn_80229760(void **ppData, void *p);
extern int fn_80229788(int a, int b);
extern int fn_802299FC(void);
extern int fn_80229A70(void);
extern int fn_80229E88(void);
extern void fn_8022A304(void);
extern int fn_8022B02C(int a);
extern void fn_8022B200(void);
extern int fn_8022C214(int a);
extern void fn_8022C3C8(void);
extern int fn_8022C410(int a);
extern int fn_8022C518(int a);
extern int fn_8022D154(void);
extern int fn_8022D1B8(void);
extern int fn_8022D6E8(void);
extern void fn_8022D6F0(void);
extern int fn_8022DA90(int *p);
extern void fn_8022DB08(void);
extern int fn_8022DB20(void);
extern int fn_8022DBF4(int a);
extern int fn_8022DC38(int a);
extern int fn_8022E28C(int a, int b, unsigned char *p, int *pA, int *pB);
extern int fn_8022E484(void);
extern int fn_8022E9A4(void);
extern void fn_8022E9C4(void);
extern int fn_8022E9E4(void);
extern int fn_8022EA74(void);
extern void fn_8022EA7C(void);
extern int fn_8022ED50(int a, int b, int c);
extern int fn_8022F384(int key);
extern int fn_8022F3D4(int key);
extern int fn_8022F8A8(int key, Cache_8022F8A8 **ppCache);
extern int fn_80230400(unsigned short id, int a, int b, int c, int d, int e, int f);
extern void fn_802349CC(void *p);
extern void fn_80235010(Table_803E96E8 *pTable, void *pEntry);
extern void LLCacheLockedEnable(void);

void fn_8023123C(void *p, int mode, unsigned char *pDone);
int fn_80232DE0(void);
int fn_80232EB4(void);
int fn_80232EF4(void);
int fn_802331BC(void);
void fn_802334F0(int mode, Funcs_802FB3BC *pFuncs);
int fn_80233604(void **ppData, void *p);
int fn_80233660(int a, int b);
int fn_80233694(void);
int fn_80233BE4(short *pOut, Model_80233BE4 *pModel, Values_80233C7C *pValues);
void fn_80233C7C(Values_80233C7C *pValues);
float fn_80234070(Box_80234070 *pBox);
unsigned int fn_80234D4C(float *pBox, void *m, void *p, void *q);
extern int TMClipVertex(float *pNdc, float *pClip, float *pPos);
void fn_80234094(Box_80234070 *pBox);
int fn_80234098(Object_80233EAC *pObject, float value);
Desc_802345F8 *fn_802345F8(Desc_802345F8 *pDescs, const char *pName);
void fn_8023472C(void *p, int a, int b, Desc_802345F8 *pA, Desc_802345F8 *pB, int c);
void fn_80234A14(Part_80234A30 *pPart, int mask);
void fn_80234A94(Part_80234A30 *pPart, void *pRecord);
void fn_80234B88(Part_80234A30 *pPart);
void fn_80234DFC(int a, Sprite_80234DFC *pSprite, int c, int d, const char *pName, int e);


































































































































/* prototypes of the functions defined in the original src/engine/cu_8022F428.c */
int fn_8022F428(int key);
int fn_8022F478(int value);
int fn_8022F488(int value);
int fn_8022F4BC(void);
int fn_8022F4C4(void);
int fn_8022F53C(int a);
int fn_8022F744(void);
int fn_8022F794(int value, char *pName);
unsigned short fn_8022F80C(void);
Cache_8022F8A8 *fn_8022F858(unsigned short id);
Cache_8022F8A8 *fn_8022F880(int key);
int fn_8022FBAC(Cache_8022F8A8 *pCache);
int fn_802303A0(int index);
int fn_802303B4(int key, unsigned short *pId);
int fn_80230CC8(unsigned short id);
int fn_80230CEC(int a, int b, int c, int key, int e, int f);
int fn_802311C8(int handle);
void fn_80231208(void);
int fn_80231A84(void);
int fn_80231A8C(const char *pWhere, int b, int c, int d, int e, struct QueryCursor *pCursor);
int fn_802328A8(void);
void fn_80232950(void);
int fn_80232998(void);
int fn_802329D0(void);
int fn_802329F0(struct Request_802329F0 *p);
int fn_80232A98(void);
int fn_80232AF8(void **ppData, void *p);
int fn_80232B8C(int a, int b);
int fn_80232DE0(void);
int fn_80232E20(void);
int fn_80232E70(void);
int fn_80232E78(void);
int fn_80232E80(void);
int fn_80232EAC(void);
int fn_80232EB4(void);
int fn_80232EF4(void);
int fn_80232F44(void);
int fn_80232F4C(void);
int fn_80232F54(void);
int fn_80232F74(void);
int fn_80232FD4(int *pRecord0, int *pRecord1);
int fn_802331BC(void);
int fn_80233344(void);
int fn_8023334C(int a, int b);
int fn_80233454(void);
int fn_802334C4(void);
void fn_802334F0(int mode, Funcs_802FB3BC *pFuncs);
int fn_80233568(int a, int b, unsigned char *pDone);
int fn_80233578(void);
int fn_80233580(void);
int fn_80233588(Block_80233588 *p);
int fn_80233604(void **ppData, void *p);
int fn_80233660(int a, int b);
int fn_80233694(void);
int fn_802336BC(void);
void fn_802336C4(Block_802336C4 *pBlock, void *pSource, int a);
void fn_80233728(Block_802336C4 *pBlock);
void fn_80233760(Block_802336C4 *pBlock, short *pValues, int count);
void fn_802337D4(Model_802337D4 *pModel, Joints_802337D4 *pJoints, void *pPose, unsigned int mask);
void fn_80233850(Model_802337D4 *pModel, Joints_802337D4 *pJoints, void *pPose, unsigned int mask, unsigned char *pFlags);
void fn_80233BB8(void *pJoints, int a, int b);
void fn_80233BD8(void *pJoints);
void fn_80233BDC(void *pJoints, void *pSkeleton);
void fn_80233BE0(void);
int fn_80233BE4(short *pOut, Model_80233BE4 *pModel, Values_80233C7C *pValues);
void fn_80233C7C(Values_80233C7C *pValues);
void fn_80233CBC(void *p, int index, int value);
void fn_80233CF0(ModelLod_802DF190 *pLod, void *pData, void *p);
void fn_80233D64(Object_80233EAC *pObject, ModelLod_802DF190 *pLods, const char *pName, int a, void *pData, void *p);
void fn_80233EAC(Object_80233EAC *pObject, ModelLod_802DF190 *pLods, const char *pName, int a, void *pArchive, AnimSkeleton_t *pSkeleton, void **ppData, int load);
void fn_80233FCC(Object_80233EAC *pObject);
float fn_80234070(Box_80234070 *pBox);
void fn_80234094(Box_80234070 *pBox);
int fn_80234098(Object_80233EAC *pObject, float value);
int fn_80234144(Object_80233EAC *pObject, void *pBox);
Object_8023417C *fn_8023417C(Object_80233EAC *pObject, int index);
void fn_802341AC(void);
void fn_802341B8(void);
void fn_802341C4(void *p);
void fn_802341E8(void *p);
void fn_8023424C(Instance_8023424C *p, int *pCounts, Box_80234070 *pClip);
int fn_80234394(Instance_8023424C **ppList, unsigned int count, int key);
void fn_802345BC(void *p);
void fn_802345C4(void *pSource, int count);
Desc_802345F8 *fn_802345F8(Desc_802345F8 *pDescs, const char *pName);
void fn_8023465C(Object_8023465C *pObject, Model_8023465C *pModel, Desc_802345F8 *pDescs);
void fn_8023472C(void *p, int a, int b, Desc_802345F8 *pA, Desc_802345F8 *pB, int c);
void fn_802347EC(void *pData, Desc_802345F8 *pDesc, int a, int b);
void fn_80234844(Desc_802345F8 *pDesc);
void fn_8023488C(void *p, int a);
void fn_802348AC(void *p);
void fn_802348CC(int a);
void fn_80234908(void);
void fn_80234994(Array_8023491C *pArray);
void fn_802349B8(Array_8023491C *pArray, int value);
void fn_80234A14(Part_80234A30 *pPart, int mask);
void fn_80234A30(Part_80234A30 *pPart, int a);
void fn_80234A90(Part_80234A30 *pPart);
void fn_80234A94(Part_80234A30 *pPart, void *pRecord);
void fn_80234AD8(Part_80234A30 *pPart, Block_802336C4 *pBlock);
void fn_80234AFC(void *p);
void fn_80234B1C(void *p);
void fn_80234B20(Object_80234B20 *pObject, Mtx44 a, Mtx44 b);
int fn_80234B80(void *p);
void fn_80234B88(Part_80234A30 *pPart);
void fn_80234BF4(int a, Part_80234A30 *pPart, int mode);
void fn_80234CA4(Part_80234A30 *pPart, void *p);
void fn_80234CAC(Part_80234A30 *pPart, void *p);
void fn_80234CF0(Part_80234A30 *pPart, int index, void *p);
void fn_80234D00(void *pIn, void *pOut);
unsigned int fn_80234D4C(float *pBox, void *m, void *p, void *q);
void fn_80234DC0(void *p, int a);
void fn_80234DC4(void *p, int a);
void fn_80234DC8(void *p, unsigned int a);
void fn_80234DCC(int a, Sprite_80234DFC *pSprite, const char *pName, int b);
void fn_80234DFC(int a, Sprite_80234DFC *pSprite, int c, int d, const char *pName, int e);
void fn_80234EA0(Sprite_80234DFC *pSprite, int keep);
void fn_80234EEC(Holder_80234EEC *pHolder, int index, void *pData, unsigned char sourceIndex);
void fn_80234F74(Sprite_80234DFC *pSprite, int index, void *pData, unsigned char sourceIndex, int offset);
void fn_80235328(Owner_80235328 *pOwner, int key);
void fn_802353CC(void *p);
void fn_802353D0(void *p);
void fn_802353D4(Object_80235588 *p, int flags);
void fn_802353D8(Object_80235588 *p, int flags);
void fn_802353E8(Object_80235588 *p, int flags);
void fn_802353F8(Object_80235588 *p, int flags);
void fn_80235510(Object_80235588 *p, int mode);
void fn_80235588(Object_80235588 *p, int a);

void fn_802336C4(Block_802336C4 *pBlock, void *pSource, int a)
{
    TMBufferNew(pBlock, a, 32);
    if (pSource != 0) {
        TMModelClone(pBlock->mUnknown10, pSource);
        TMModelAllocChannels(pBlock->mUnknown10);
    } else {
        TMModelReset(pBlock->mUnknown10);
    }
}

void fn_80233728(Block_802336C4 *pBlock)
{
    TMModelFreeChannels(pBlock->mUnknown10);
    TMBufferDelete(pBlock);
}

void fn_80233760(Block_802336C4 *pBlock, short *pValues, int count)
{
    TMModelResetChannels(pBlock->mUnknown10);
    TMBufferReset(pBlock);
    TMBlendBegin(pBlock);
    TMBlendBindModel(pBlock->mUnknown10);
    TMBlendSetWeights(pValues, count);
    TMBlendGeomAll();
    TMBlendEnd();
    DCFlushRange(pBlock->mpUnknown0, pBlock->mUnknown4);
}

void fn_802337D4(Model_802337D4 *pModel, Joints_802337D4 *pJoints, void *pPose, unsigned int mask)
{
    int *pSkeleton;
    void *pBones;

    if (pModel != 0) {
        pSkeleton = pModel->mpUnknown12;
        pBones = pModel->mpUnknown16;
        if (pSkeleton != 0 && pBones != 0) {
            if (pJoints->mUnknown4 != 0) {
                LLCacheLockedEnable();
            }
            TMClusterObjAllocMatrices(pJoints, pSkeleton[1]);
            TMClusterObjSynthesizeMatrices(pJoints, pBones, pSkeleton, pPose);
        }
    }
}

void fn_80233850(Model_802337D4 *pModel, Joints_802337D4 *pJoints, void *pPose, unsigned int mask,
                 unsigned char *pFlags)
{
    int *pSkeleton;
    void *pBones;

    if (pModel != 0) {
        pSkeleton = pModel->mpUnknown12;
        pBones = pModel->mpUnknown16;
        if (pSkeleton != 0 && pBones != 0) {
            if (pJoints->mUnknown4 != 0) {
                LLCacheLockedEnable();
            }
            TMClusterObjAllocMatrices(pJoints, pSkeleton[1]);
            TMClusterObjSynthesizeMatricesSlerp(pJoints, pBones, pSkeleton, pPose, pFlags);
        }
    }
}

void fn_80233BB8(void *pJoints, int a, int b)
{
    TMClusterObjInitObj(pJoints);
}

void fn_80233BD8(void *pJoints)
{
}

void fn_80233BDC(void *pJoints, void *pSkeleton)
{
}

void fn_80233BE0(void)
{
}

int fn_80233BE4(short *pOut, Model_80233BE4 *pModel, Values_80233C7C *pValues)
{
    int total = 0;
    List_80233BE4 *pList;
    unsigned int count;
    unsigned int i;

    if (pModel != 0) {
        pList = pModel->mpUnknown20;
        count = 0;
        if (pList != 0) {
            count = pList->mUnknown0;
        }
        if (count >= 64) {
            count = 64;
        }
        for (i = 0; i < count; i++) {
            if (pValues->mUnknown8[i] != 255) {
                total += TMSwapGetGeomRefs(pList, &pOut[total], i, pValues->mUnknown8[i]);
            }
        }
    }
    return total;
}

void fn_80233C7C(Values_80233C7C *pValues)
{
    unsigned int i;

    for (i = 0; i < 64; i++) {
        pValues->mUnknown8[i] = 255;
        pValues->mUnknown0[i >> 5] |= 1 << (i & 3);
    }
}

void fn_80233CBC(void *p, int index, int value)
{
    Values_80233C7C *pValues = p;

    if (pValues->mUnknown8[index] != value) {
        pValues->mUnknown8[index] = value;
        pValues->mUnknown0[(unsigned int)index >> 5] |= 1 << (index & 3);
    }
}

void fn_80233CF0(ModelLod_802DF190 *pLod, void *pData, void *p)
{
    Object_8023417C *pRecord = &pLod->mUnknown1C;

    pLod->mpUnknown18 = pData;
    TMModelReset(pRecord);
    pLod->mpUnknown10 = pRecord;
    TMModelResRelocate(pLod->mpUnknown18);
    TMModelBindModelRes(pRecord, pLod->mpUnknown18);
    TMModelRemapMaterials(pRecord, lbl_803EC0F4);
    if (p != 0) {
        TMModelRemapClusters(pRecord, p);
    }
}

void fn_80233D64(Object_80233EAC *pObject, ModelLod_802DF190 *pLods, const char *pName, int a, void *pData,
                 void *p)
{
    int fresh = 1;

    pObject->mUnknownC = 0;
    pObject->mpUnknown0 = pName;
    pObject->mUnknown4 = a;
    pObject->mpUnknown10 = pLods;
    pObject->mpUnknown8 = pData;
    for (; pLods->mId != 0xFFFF; pLods++) {
        if (pLods->mId != 0) {
            if (ResIsLoaded(pData, pLods->mId) != 0) {
                fresh = 0;
            }
            pLods->mpUnknown18 = (void *)ResLoad(pData, pLods->mId, 1);
            TMModelReset(&pLods->mUnknown1C);
            pLods->mpUnknown10 = &pLods->mUnknown1C;
            if (pLods->mpUnknown18 != 0) {
                TMModelResRelocate(pLods->mpUnknown18);
                TMModelBindModelRes(&pLods->mUnknown1C, pLods->mpUnknown18);
                if (lbl_803EC0F4 != 0) {
                    if (fresh) {
                        TMModelRemapMaterials(&pLods->mUnknown1C, lbl_803EC0F4);
                    } else {
                        pLods->mUnknown1C.mpUnknown18 = lbl_803EC0F4;
                    }
                }
                if (p != 0) {
                    TMModelRemapClusters(&pLods->mUnknown1C, p);
                }
            }
        } else {
            TMModelReset(&pLods->mUnknown1C);
            pLods->mpUnknown10 = 0;
        }
        pObject->mUnknownC++;
    }
}

void fn_80233EAC(Object_80233EAC *pObject, ModelLod_802DF190 *pLods, const char *pName, int a, void *pArchive,
                 AnimSkeleton_t *pSkeleton, void **ppData, int load)
{
    int n = 0;

    pObject->mUnknownC = 0;
    pObject->mpUnknown0 = pName;
    pObject->mUnknown4 = a;
    pObject->mpUnknown10 = pLods;
    pObject->mpUnknown8 = pArchive;
    for (; pLods->mId != 0xFFFF; pLods++) {
        if (pLods->mId != 0) {
            if (load != 0) {
                ResCopyToBuffer(pArchive, pLods->mId, ppData[n]);
            }
            pLods->mpUnknown18 = ppData[n];
            TMModelReset(&pLods->mUnknown1C);
            pLods->mpUnknown10 = &pLods->mUnknown1C;
            if (pLods->mpUnknown18 != 0) {
                TMModelResRelocate(pLods->mpUnknown18);
                TMModelBindModelRes(&pLods->mUnknown1C, pLods->mpUnknown18);
                if (lbl_803EC0F4 != 0) {
                    TMModelRemapMaterials(&pLods->mUnknown1C, lbl_803EC0F4);
                }
                if (pSkeleton != 0) {
                    TMModelRemapClusters(&pLods->mUnknown1C, pSkeleton);
                }
            }
            n++;
        } else {
            pLods->mpUnknown10 = 0;
        }
        pObject->mUnknownC++;
    }
}

void fn_80233FCC(Object_80233EAC *pObject)
{
    unsigned int count = pObject->mUnknownC;
    ModelLod_802DF190 *pLods = pObject->mpUnknown10;
    unsigned int i;

    for (i = 0; i < count; i++) {
        ModelLod_802DF190 *pLod = &pLods[i];

        if (pLod->mId != 0) {
            ResUnLoad(pObject->mpUnknown8, pLod->mId);
            pLod->mpUnknown18 = 0;
            pLod->mpUnknown10 = 0;
            if (pLod->mUnknown1C.mUnknown1C != 0) {
                TMModelFreeChannels(&pLods[i].mUnknown1C);
            }
            TMModelReset(&pLod->mUnknown1C);
        }
    }
    pObject->mpUnknown10 = 0;
    pObject->mUnknownC = 0;
}

float fn_80234070(Box_80234070 *pBox)
{
    return fabs((pBox->mUnknown16 - pBox->mUnknown0) * (pBox->mUnknown20 - pBox->mUnknown4));
}

void fn_80234094(Box_80234070 *pBox)
{
}

int fn_80234098(Object_80233EAC *pObject, float value)
{
    int count = pObject->mUnknownC;
    ModelLod_802DF190 *pLods = pObject->mpUnknown10;
    int i;

    for (i = 0; i < count; i++) {
        if (pLods[i].mpUnknown10 != 0 && value > pLods[i].mUnknown0) {
            break;
        }
    }
    while (i > 0 && pLods[i].mId == 0xFFFF) {
        i--;
    }
    return i;
}

int fn_80234144(Object_80233EAC *pObject, void *pBox)
{
    return fn_80234098(pObject, fn_80234070(pBox));
}

Object_8023417C *fn_8023417C(Object_80233EAC *pObject, int index)
{
    Object_8023417C *pRecord = 0;

    if (index >= 0 && index < pObject->mUnknownC) {
        pRecord = &pObject->mpUnknown10[index].mUnknown1C;
    }
    return pRecord;
}

void fn_802341AC(void)
{
    lbl_803EC0F0 = 0;
}

void fn_802341B8(void)
{
    lbl_803EC0F0 = 0;
}

void fn_802341C4(void *p)
{
    lbl_803A2648[lbl_803EC0F0++] = p;
}

void fn_802341E8(void *p)
{
    unsigned int i;

    for (i = 0; i < lbl_803EC0F0; i++) {
        void *pEntry = lbl_803A2648[i];

        if (pEntry == p) {
            lbl_803EC0F0--;
            lbl_803A2648[i] = lbl_803A2648[lbl_803EC0F0];
            lbl_803A2648[lbl_803EC0F0] = pEntry;
            break;
        }
    }
}

void fn_8023424C(Instance_8023424C *p, int *pCounts, Box_80234070 *pClip)
{
    Box_80234070 box;
    float ndc[3];

    p->mUnknown4 = 0.0f;
    p->mUnknown12 = 0.0f;
    if (p->mpUnknown28 != 0 && p->mpUnknown32 != 0) {
        p->mUnknown20 = fn_80234D4C(p->mpUnknown28, p->mpUnknown32, p->mpUnknown36, &box);
        TMClipVertex(ndc, 0, 0);
        p->mUnknown16 = ndc[2];
        if (pClip != 0
            && (box.mUnknown0 > pClip->mUnknown16 || box.mUnknown16 < pClip->mUnknown0
                || box.mUnknown4 > pClip->mUnknown20 || box.mUnknown20 < pClip->mUnknown4)) {
            p->mUnknown20 |= 0x3F;
        }
        if ((p->mUnknown20 & 0x3F) == 0) {
            p->mUnknown4 = fn_80234070(&box);
            fn_80234094(&box);
            p->mUnknown12 = fn_80234070(&box);
        } else {
            p->mUnknown4 = 0.0f;
        }
        p->mUnknown8 = -box.mUnknown8;
    }
    if (p->mpUnknown24 != 0) {
        p->mUnknown0 = fn_80234098(p->mpUnknown24, p->mUnknown4);
        pCounts[p->mUnknown0]++;
    }
}

int fn_80234394(Instance_8023424C **ppList, unsigned int count, int key)
{
    unsigned int i;
    int best = -1;
    float bestValue = 10000.0f;

    for (i = 0; i < count; i++) {
        Instance_8023424C *p = ppList[i];

        if (p->mpUnknown24 != 0 && p->mUnknown0 == key && p->mUnknown4 < bestValue) {
            bestValue = p->mUnknown4;
            best = i;
        }
    }
    if (best >= 0) {
        ppList[best]->mUnknown0++;
        return 1;
    }
    return 0;
}

void fn_802345BC(void *p)
{
    lbl_803EC0F4 = p;
}

void fn_802345C4(void *pSource, int count)
{
    memcpy(lbl_802FB3F8, pSource, count * 4);
}

Desc_802345F8 *fn_802345F8(Desc_802345F8 *pDescs, const char *pName)
{
    for (; pDescs->mpUnknown0 != 0; pDescs++) {
        if (strcmp(pDescs->mpUnknown0, pName) == 0) {
            return pDescs;
        }
    }
    return 0;
}

void fn_8023465C(Object_8023465C *pObject, Model_8023465C *pModel, Desc_802345F8 *pDescs)
{
    List_8023465C *pList = pModel->mpUnknown24;
    int count;
    int i;

    if (pList != 0) {
        count = pList->mUnknown0;
        if (count > pObject->mUnknown0) {
            count = pObject->mUnknown0;
        }
        for (i = 0; i < count; i++) {
            Entry_8023465C *pEntry = &pList->mpUnknown4[i];

            if (pEntry != 0 && pEntry->mUnknown8 > 0) {
                Desc_802345F8 *pDesc = fn_802345F8(pDescs, pEntry->mpUnknown12);

                if (pDesc != 0) {
                    fn_8023472C(pObject, i, 0, pDesc, pDesc, 0);
                    fn_8023472C(pObject, i, 1, 0, 0, 0);
                }
            }
        }
    }
}

void fn_8023472C(void *p, int a, int b, Desc_802345F8 *pA, Desc_802345F8 *pB, int c)
{
    void *pTexture = 0;
    void *pPalette = 0;

    if (pA != 0) {
        pTexture = TMTexLibGetTextureByTexNode(pA->mpUnknown20);
    }
    if (pB != 0) {
        pPalette = TMTexLibGetClutByTexNode(pB->mpUnknown20, c);
    }
    TMMaterialListSelect(p, a);
    if (b == 0) {
        TMMaterialBindTextureClut(lbl_802B7128, pTexture, pPalette);
    } else if (pTexture != 0) {
        TMMaterialBindShader(lbl_803ED024);
        TMMaterialBindTextureClut(lbl_802B7130, pTexture, pPalette);
    } else {
        TMMaterialBindShader(lbl_803ED020);
    }
}

void fn_802347EC(void *pData, Desc_802345F8 *pDesc, int a, int b)
{
    pDesc->mpUnknown28 = pData;
    pDesc->mpUnknown24 = fn_801D2B7C(40, 0, 0);
    TMTexLibLoad(pDesc->mpUnknown24, (int)pDesc->mpUnknown28);
    pDesc->mpUnknown20 = pDesc->mpUnknown24->mpUnknown36;
}

void fn_80234844(Desc_802345F8 *pDesc)
{
    if (pDesc->mpUnknown24 != 0) {
        TMTexLibUnload(pDesc->mpUnknown24);
        fn_801D2BD0(pDesc->mpUnknown24);
        pDesc->mpUnknown24 = 0;
    }
}

void fn_8023488C(void *p, int a)
{
    TMMaterialListAlloc(p, a);
}

void fn_802348AC(void *p)
{
    TMMaterialListFree(p);
}

void fn_802348CC(int a)
{
    lbl_803ED020 = TMShaderLibGetShader(lbl_802B7154);
    lbl_803ED024 = TMShaderLibGetShader(lbl_802B715C);
}

void fn_80234908(void)
{
    lbl_803ED024 = 0;
    lbl_803ED020 = 0;
}

void fn_80234994(Array_8023491C *pArray)
{
    fn_801D2BD0(pArray->mpUnknown4);
}

void fn_802349B8(Array_8023491C *pArray, int value)
{
    if (pArray->mUnknown8 != value) {
        pArray->mUnknown8 = value;
    }
}

void fn_80234A14(Part_80234A30 *pPart, int mask)
{
    pPart->mUnknown4 |= mask;
    pPart->mUnknown8 |= mask;
}

void fn_80234A30(Part_80234A30 *pPart, int a)
{
    pPart->mUnknown0 = 1;
    pPart->mpUnknown12 = 0;
    pPart->mUnknown16 = 0;
    pPart->mpUnknown232[0] = 0;
    pPart->mpUnknown232[1] = 0;
    pPart->mpUnknown224 = 0;
    pPart->mpUnknown228 = 0;
    fn_80233C7C(&pPart->mUnknown20);
    fn_80234A14(pPart, 0x411);
}

void fn_80234A90(Part_80234A30 *pPart)
{
}

void fn_80234A94(Part_80234A30 *pPart, void *pRecord)
{
    if (pPart->mpUnknown12 != pRecord) {
        pPart->mpUnknown12 = pRecord;
        pPart->mUnknown20.mUnknown0[0] = -1;
        pPart->mUnknown20.mUnknown0[1] = -1;
        fn_80234A14(pPart, 0x411);
    }
}

void fn_80234AD8(Part_80234A30 *pPart, Block_802336C4 *pBlock)
{
    fn_80234A94(pPart, pBlock->mUnknown10);
}

void fn_80234AFC(void *p)
{
    fn_802349CC(p);
}

void fn_80234B1C(void *p)
{
}

void fn_80234B20(Object_80234B20 *pObject, Mtx44 a, Mtx44 b)
{
    MatPush();
    if (b != 0) {
        MatCat(b);
    }
    if (a != 0) {
        MatCat(a);
    }
    MatStore(pObject->mUnknown64);
    MatPop();
}

int fn_80234B80(void *p)
{
    return 0;
}

void fn_80234B88(Part_80234A30 *pPart)
{
    if (pPart->mpUnknown12 != 0 && (pPart->mUnknown20.mUnknown0[0] | pPart->mUnknown20.mUnknown0[1]) != 0) {
        pPart->mUnknown92 = fn_80233BE4(pPart->mUnknown96, pPart->mpUnknown12, &pPart->mUnknown20);
        fn_80234A14(pPart, 1);
        pPart->mUnknown20.mUnknown0[0] = 0;
        pPart->mUnknown20.mUnknown0[1] = 0;
    }
}

void fn_80234BF4(int a, Part_80234A30 *pPart, int mode)
{
    fn_80234B88(pPart);
    TMRenderBindModel(pPart->mpUnknown12);
    TMRenderBindMaterialList(pPart->mpUnknown232[0]);
    TMRenderBindClusterObj(pPart->mpUnknown224);
    switch (mode) {
    case 0:
        TMRenderGeomList(pPart->mUnknown96, pPart->mUnknown92);
        break;
    case 1:
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        TMTevSetTevOp(0, 0, 1);
        TMRenderGeomListDirect(pPart->mUnknown96, pPart->mUnknown92);
        break;
    }
}

void fn_80234CA4(Part_80234A30 *pPart, void *p)
{
    pPart->mpUnknown224 = p;
}

void fn_80234CAC(Part_80234A30 *pPart, void *p)
{
    if (p != pPart->mpUnknown228) {
        fn_80234A14(pPart, 1);
        pPart->mpUnknown228 = p;
    }
}

void fn_80234CF0(Part_80234A30 *pPart, int index, void *p)
{
    pPart->mpUnknown232[index] = p;
}

void fn_80234D00(void *pIn, void *pOut)
{
    TMClipProjection(0);
    TMClipMatrix(0);
    TMClipBBox(pIn, pOut, 0);
}

unsigned int fn_80234D4C(float *pBox, void *m, void *p, void *q)
{
    unsigned int result;

    MatPushUnit();
    MatLoadSlot(3);
    TMClipProjection(0);
    TMClipMatrixWorld(0, p, m);
    result = TMClipBBox(pBox, q, 0);
    MatPop();
    return result;
}

void fn_80234DC0(void *p, int a)
{
}

void fn_80234DC4(void *p, int a)
{
}

void fn_80234DC8(void *p, unsigned int a)
{
}

void fn_80234DCC(int a, Sprite_80234DFC *pSprite, const char *pName, int b)
{
    fn_80234DFC(a, pSprite, 0, 0, pName, b);
}

void fn_80234DFC(int a, Sprite_80234DFC *pSprite, int c, int d, const char *pName, int e)
{
    Header_80234DFC *pHeader;
    void *pText = TMModelResGetChunk((void *)a, 0x54657874, &pHeader);

    if (pText != 0) {
        if (e == 0) {
            pSprite->mpUnknown40 = fn_801D2B7C(pHeader->mUnknown8, 0, 0);
            LLTexCopyFlush(pSprite->mpUnknown40, pText, pHeader->mUnknown8);
        } else {
            pSprite->mpUnknown40 = pText;
        }
        TMTexLibLoad(pSprite, (int)pSprite->mpUnknown40);
    }
    pSprite->mpUnknown44 = TMModelResGetChunk((void *)a, 0x4D61746C, 0);
}

void fn_80234EA0(Sprite_80234DFC *pSprite, int keep)
{
    if (pSprite->mpUnknown40 != 0) {
        TMTexLibUnload(pSprite);
        if (keep == 0) {
            fn_801D2BD0(pSprite->mpUnknown40);
        }
    }
}

void fn_80234EEC(Holder_80234EEC *pHolder, int index, void *pData, unsigned char sourceIndex)
{
    Sprite_80234DFC *pSprite = pHolder->mpUnknown88;
    TexFileMaterial_t *pDst;
    TexFileMaterial_t *pSrc;
    TexFileImage_t *pDstImage;
    TexFileImage_t *pSrcImage;

    TexMipmapRelocate(pData);
    pDst = TexGetMaterialByIndex(pSprite->mpUnknown40, index);
    pSrc = TexGetMaterialByIndex(pData, sourceIndex);
    pDstImage = TexGetTextureByIndex(pSprite->mpUnknown40, pDst->mUnknown4);
    pSrcImage = TexGetTextureByIndex(pData, pSrc->mUnknown4);
    LLTexCopyFlush(pDstImage->mpUnknownC, pSrcImage->mpUnknownC, pDstImage->mUnknown8);
}

void fn_80234F74(Sprite_80234DFC *pSprite, int index, void *pData, unsigned char sourceIndex, int offset)
{
    TexFileMaterial_t *pDst;
    TexFileMaterial_t *pSrc;
    TexFilePalette_t *pDstImage;
    TexFilePalette_t *pSrcImage;

    TexMipmapRelocate(pData);
    pDst = TexGetMaterialByIndex(pSprite->mpUnknown40, index);
    pSrc = TexGetMaterialByIndex(pData, sourceIndex);
    pDstImage = TexGetPaletteByIndex(pSprite->mpUnknown40, pDst->mUnknown8 + offset);
    pSrcImage = TexGetPaletteByIndex(pData, pSrc->mUnknown8 + offset);
    LLTexCopyFlush(pDstImage->mpUnknown8, pSrcImage->mpUnknown8, pDstImage->mUnknown4);
}

void fn_80235328(Owner_80235328 *pOwner, int key)
{
    Source_80235328 *pSource = pOwner->mpUnknown8;
    Table_803E96E8 *pTable = &lbl_803E96E8;
    Group_803E96E8 *pGroup = pTable->mpUnknown12;
    Range_80216190 *pRange;
    unsigned short *pIndex;
    int i;

    if (pGroup != 0) {
        pRange = TMSwapGetState(pGroup, 0, key);
        if (pRange != 0) {
            pIndex = &pGroup->mpUnknown12[pRange->mUnknown16];
            for (i = 0; i < pRange->mUnknown18; i++) {
                fn_80235010(pTable, pSource->mpUnknown0 + pIndex[i] * 24);
            }
        }
    }
}

void fn_802353CC(void *p)
{
}

void fn_802353D0(void *p)
{
}

void fn_802353D4(Object_80235588 *p, int flags)
{
}

void fn_802353D8(Object_80235588 *p, int flags)
{
    p->mUnknown0 |= flags;
}

void fn_802353E8(Object_80235588 *p, int flags)
{
    p->mUnknown0 &= ~flags;
}

void fn_802353F8(Object_80235588 *p, int flags)
{
    int old = p->mUnknown4;

    p->mUnknown4 = 0;
    if (flags & 0xC000) {
        p->mUnknown4 = 1;
    }
    if (flags & 1) {
        p->mUnknown4 = 4;
    }
    if (flags == 0x02000000) {
        p->mUnknown4 = 2;
    }
    if (flags == 0x04000000) {
        p->mUnknown4 = 3;
    }
    if (flags & 0x10000000) {
        p->mUnknown4 = 5;
    }
    if (flags & 0x20000000) {
        p->mUnknown4 = 6;
    }
    if (flags & 0x2000) {
        p->mUnknown4 = 17;
    }
    if (flags & 0x200) {
        p->mUnknown4 = 18;
    }
    if (flags & 0x400) {
        p->mUnknown4 = 19;
    }
    if (old != p->mUnknown4) {
        TMClipResetExtent(p->mUnknown152);
        if (p->mUnknown4 == -1) {
            TMModelAddExtent(&p->mUnknown100, p->mUnknown152, -1, -1);
        } else {
            TMModelAddExtent(&p->mUnknown100, p->mUnknown152, 0, p->mUnknown4);
        }
    }
}

void fn_80235510(Object_80235588 *p, int mode)
{
    int old = p->mUnknown4;

    p->mUnknown4 = mode;
    if (old != mode) {
        TMClipResetExtent(p->mUnknown152);
        if (p->mUnknown4 == -1) {
            TMModelAddExtent(&p->mUnknown100, p->mUnknown152, -1, -1);
        } else {
            TMModelAddExtent(&p->mUnknown100, p->mUnknown152, 0, p->mUnknown4);
        }
    }
}

void fn_80235588(Object_80235588 *p, int a)
{
    p->mUnknown0 = 0x4000;
    p->mUnknown4 = -1;
    p->mpUnknown88 = 0;
    p->mpUnknown84 = 0;
    p->mUnknown184 = 0;
    TMModelReset(&p->mUnknown100);
    TMMaterialListAlloc(p->mUnknown92, 0);
}
