/* Partial source for model, level-of-detail and render wrappers over the TM renderer, not yet cut into their files. */

#include "engine/TDbCreate.h"
#include "engine/tdbext.h"
#include "engine/dbutil.h"
#include "engine/TDbLoad.h"

#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <stddef.h>

/* The fill routine is declared with an unsigned long size, as src/engine/PJoyDrvr.c does: the
   type differs from GCC's built-in memset, so constant clears stay ordinary calls (no crclr). */
void *memcpy(void *dest, const void *src, size_t num);
void *memset(void *dest, int ch, unsigned long count);
int strcmp(const char *s1, const char *s2);
#include "engine/DbNiomModeFuncs.h"
#include "game/DbUserSetCurrent.h"
#include "game/fn_80233CBC.h"
#include "game/TDbCompilePerformOp.h"
#include "engine/texfile.h"
#include "game/Object_80233EAC.h"
#include "game/Object_80235588.h"
#include "game/QueryStatus.h"

#include "engine/DbUserEntry.h"

#include "engine/DbNiomHandlers.h"
#include "game/Request_802329F0.h"

typedef struct Block_80233588 {
    int mUnknown0;
    char *mpUnknown4;
    int mUnknown8;
} Block_80233588;

int DbManagerCreateGameDb(Block_80233588 *p);
int DbManagerInitHook(void);

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

/* 16-byte bone record of the skeleton 0x802338D4 walks: position, then the parent index. */
typedef struct Bone_802338D4 {
    float mPos[3];
    short mParent;
    short mUnknown14;
} Bone_802338D4;

typedef struct Skeleton_802338D4 {
    char mUnknown0[6];
    unsigned short mNumBones;
    char mUnknown8[8];
    Bone_802338D4 mBones[1];
} Skeleton_802338D4;

/* Pose block of 0x802338D4 (AnimPose_t's +0x30 angle triples and +0x34 matrices). */
typedef struct Pose_802338D4 {
    char mUnknown0[48];
    short *mpAngles;
    Mtx44 *mpMatrices;
} Pose_802338D4;

/* 0x90-byte block cleared by 0x802349CC; three floats at +0x80 start at 1. */
typedef struct Block_802349CC {
    char mUnknown0[128];
    float mScale[3];
    char mUnknown140[4];
} Block_802349CC;

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
extern const float lbl_802B7168[];
extern const float lbl_802B7170[];
extern DbUserEntry_t _DbUser_aEntries[];
extern Entry_802FB310 _DbCache_aTables[];
extern unsigned int lbl_802FB3F8[];
extern Box_80234070 lbl_802FB418;
extern unsigned int lbl_803A2628[8];
extern void *lbl_803A2648[];
extern Table_803E96E8 lbl_803E96E8;
extern int _DbUser_iSize;
extern char *_DbUser_pFileName;
extern int _DbUser_iMode;
extern int _DbUser_iCurrent;
extern unsigned char _DbUser_iCount;
extern Cache_8022F8A8 *_DbCache_pList;
extern int _DbOccp_iHandlerTag;
extern int _DbOccp_iDb;
extern int lbl_803EC0F0;
extern void *lbl_803EC0F4;
extern int lbl_803ED020;
extern int lbl_803ED024;
extern const int _DbUser_aDbIds[2];

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
extern int TDbExists(int handle);
extern int TDbSave(int handle, int a, int b);
extern int TDbTblDefaultDbPush(int a, int *pTable4, int *pTable8);
extern int TDbTblDefaultDbPop(void);
extern int TDbTblFindUnusedId(int handle, int *pTable);
extern int TDbTblExists(int handle, int table);
extern int TDbTblInfoSetPersistent(int handle, int table, int a);
extern int TDbRegisterHandler(void *pCallback, int tag);
extern int TDbUnregisterHandler(int tag);
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
extern int DbOcmtModuleInit(void);
extern void DbOcmtModuleShutdown(void);
extern int DbOptionsModuleInit(void);
extern void DbOptionsModuleShutdown(void);
extern int DbNiomEndMode(void);
extern int DbNiomReadOnce(int a, int b);
extern void DbNiomSetModeFuncs(DbNiomModeFuncs_t *pFuncs);
extern void DbNiomClearModeFuncs(void);
extern int DbNiomModeLoad(void **ppData, void *p);
extern int DbNiomModeReset(int a, int b);
extern int DbYalpModuleInit(void);
extern int DbYalpModuleShutdown(void);
extern int DbSplpModuleInit(void);
extern void DbSplpModuleShutdown(void);
extern int fn_8022B02C(int a);
extern void fn_8022B200(void);
extern int DbSrptModuleInit(int a);
extern void DbSrptModuleShutdown(void);
extern int DbSrptDeleteUnflaggedTeams(int a);
extern int DbSrptDeleteUnflaggedTypedTeams(int a);
extern int DbUslpModuleInit(void);
extern int DbUslpModuleShutdown(void);
extern int DbThcdModuleInit(void);
extern void DbThcdModuleShutdown(void);
extern int DbFnigModuleInit(int *p);
extern void DbFnigModuleShutdown(void);
extern int DbResetGameInfo(void);
extern int DbFnigSetHomeTeam(int a);
extern int DbFnigSetAwayTeam(int a);
extern int DbRunUpdateChain(int a, int b, unsigned char *p, int *pA, int *pB);
extern int DbRunLoadChain(void);
extern int DbLeagueModuleInit(void);
extern void DbLeagueModuleShutdown(void);
extern int DbLeagueLoad(void);
extern int DbEvasModuleInit(void);
extern void DbEvasModuleShutdown(void);
extern int DbTatsCopyAllTables(int a, int b, int c);
extern signed char DbUserFindIndex(int key);
extern int DbUserGetDb(int key);
extern int DbCacheCreate(int key, Cache_8022F8A8 **ppCache);
extern int DbCacheCopyRows(unsigned short id, int a, int b, int c, int d, int e, int f);
void ScaleBlockReset(Block_802349CC *pBlock);
struct TMRenderState_t;
struct TMGeomNode_t;
extern void ModelObjEnvMapTexCoords(struct TMRenderState_t *pState, struct TMGeomNode_t *pNode);
extern void LLCacheLockedEnable(void);
extern void _MathSinCos16(int angle, void *pTable, float *pSin, float *pCos);
extern float _Math_Taylor[];

void DbOccpUpdateHandler(void *p, int mode, unsigned char *pDone);
int DbManagerEnterMode0(void);
int DbManagerEnterMode1(void);
int DbManagerMode1Leave(void);
int DbManagerMode2Leave(void);
void DbManagerGetModeFuncs(int mode, DbNiomModeFuncs_t *pFuncs);
int DbManagerLoadGameDb(void **ppData, void *p);
int DbManagerSaveGameDb(int a, int b);
int DbManagerDestroyGameDb(void);
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


































































































































/* prototypes of the db functions in 0x8022F428-0x802355E4 (dbuser.c to cu_802336C4.c) */
int DbUserFindIdByDb(int key);
int DbUserSetCurrent(int value);
int DbUserSelect(int value);
int DbUserGetCurrent(void);
int DbUserOpenDatabases(void);
int DbUserPostLoad(int a);
int DbUserCloseDatabases(void);
int DbUserSetName(int value, char *pName);
unsigned short DbCacheNewId(void);
Cache_8022F8A8 *DbCacheFindById(unsigned short id);
Cache_8022F8A8 *DbCacheFindByDb(int key);
int DbCacheDestroy(Cache_8022F8A8 *pCache);
int DbCacheGetTableId(int index);
int DbCacheOpen(int key, unsigned short *pId);
int DbCacheClose(unsigned short id);
int DbCacheCopy(int a, int b, int c, int key, int e, int f);
int DbOccpModuleInit(int handle);
void DbOccpModuleShutdown(void);
int DbOccpQueryNone(void);
int DbOccpQueryBlocking(const char *pWhere, int b, int c, int d, int e, struct QueryCursor *pCursor);
int DbManagerInitModules(void);
void DbManagerShutdownModules(void);
int DbManagerPushGameDb(void);
int DbManagerPopGameDb(void);
int DbManagerInit(struct Request_802329F0 *p);
int DbManagerShutdown(void);
int DbManagerLoad(void **ppData, void *p);
int DbManagerSave(int a, int b);
int DbManagerEnterMode0(void);
int DbManagerMode0Leave(void);
int DbManagerMode0Load(void);
int DbManagerMode0Save(void);
int DbManagerMode0Finish(void);
int DbManagerMode0Abort(void);
int DbManagerEnterMode1(void);
int DbManagerMode1Leave(void);
int DbManagerMode1Load(void);
int DbManagerMode1Save(void);
int DbManagerMode1Finish(void);
int DbManagerMode1Abort(void);
int DbManagerEnterMode2(int *pRecord0, int *pRecord1);
int DbManagerMode2Leave(void);
int DbManagerMode2Load(void);
int DbManagerMode2Save(int a, int b);
int DbManagerMode2Finish(void);
int DbManagerMode2Abort(void);
void DbManagerGetModeFuncs(int mode, DbNiomModeFuncs_t *pFuncs);
int DbManagerResultAccept(int a, int b, unsigned char *pDone);
int DbManagerResultRecord(void);
int DbManagerResultFinish(void);
int DbManagerCreateGameDb(Block_80233588 *p);
int DbManagerLoadGameDb(void **ppData, void *p);
int DbManagerSaveGameDb(int a, int b);
int DbManagerDestroyGameDb(void);
int DbManagerInitHook(void);
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
void fn_8023424C(Instance_8023424C *p, unsigned int *pCounts, Box_80234070 *pClip);
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
void ModelPassShadersClear(void);
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

/* Builds the local matrix of one bone from its three angles and position and
   concatenates it with the parent's matrix (as in src/engine/tmclusterobj.c). */
static inline void _BuildBoneMatrix(Mtx44 *pParent, Mtx44 *pOut, int rx, int ry, int rz,
                                    float *pPos)
{
    float sx, cx, sy, cy, sz, cz;
    float sxsy, cxsy;
    Mtx44 mtx;

    _MathSinCos16(rx, _Math_Taylor, &sx, &cx);
    _MathSinCos16(ry, _Math_Taylor, &sy, &cy);
    _MathSinCos16(rz, _Math_Taylor, &sz, &cz);
    cxsy = cx * sy;
    sxsy = sx * sy;
    mtx[0][3] = pPos[0];
    mtx[1][3] = pPos[1];
    mtx[2][3] = pPos[2];
    mtx[0][0] = cz * cy;
    mtx[1][0] = sz * cy;
    mtx[2][0] = -sy;
    mtx[0][1] = -sz * cx + cz * sxsy;
    mtx[1][1] = cz * cx + sz * sxsy;
    mtx[2][1] = cy * sx;
    mtx[0][2] = sz * sx + cz * cxsy;
    mtx[1][2] = -cz * sx + sz * cxsy;
    mtx[2][2] = cy * cx;
    PSMTXConcat(*pParent, mtx, *pOut);
}

/* Builds every bone matrix of pPose under the current matrix, into the locked-cache buffer
   pCache when given (then copied to the pose's matrices) or into the pose's matrices. */
void fn_802338D4(Pose_802338D4 *pPose, Skeleton_802338D4 *pSkeleton, Mtx44 *pCache)
{
    Mtx44 *pMatrices = pCache;
    short *pAngles;
    Mtx44 root;
    unsigned int i;

    if (pMatrices == 0) {
        pMatrices = pPose->mpMatrices;
    }
    pAngles = pPose->mpAngles;
    if (pCache != 0) {
        LLCacheLockedEnable();
        if (LCQueueLength() != 0) {
            LCQueueWait(0);
        }
    }
    MatStore(root);
    _BuildBoneMatrix(&root, &pMatrices[0], pAngles[0], pAngles[1], pAngles[2],
                     pSkeleton->mBones[0].mPos);
    for (i = 1; i < pSkeleton->mNumBones; i++) {
        _BuildBoneMatrix(&pMatrices[pSkeleton->mBones[i].mParent], &pMatrices[i], pAngles[i * 3],
                         pAngles[i * 3 + 1], pAngles[i * 3 + 2], pSkeleton->mBones[i].mPos);
    }
    if (pCache != 0) {
        DCFlushRange(pPose->mpMatrices, i * sizeof(Mtx44));
        LCStoreData(pPose->mpMatrices, pCache, i * sizeof(Mtx44));
    } else {
        DCStoreRange(pMatrices, i * sizeof(Mtx44));
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

void fn_8023424C(Instance_8023424C *p, unsigned int *pCounts, Box_80234070 *pClip)
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

/* Rates every registered instance (clipped to the screen box when mode is 1), then moves
   instances down one detail level while a level holds more than its budget plus what the
   level above left unused. */
void ModelLodBalance(int mode)
{
    Box_80234070 *pClip;
    unsigned int i;
    unsigned int level;

    if (mode == 1) {
        pClip = &lbl_802FB418;
    } else {
        pClip = 0;
    }
    memset(lbl_803A2628, 0, sizeof(lbl_803A2628));
    for (i = 0; i < lbl_803EC0F0; i++) {
        fn_8023424C(lbl_803A2648[i], lbl_803A2628, pClip);
    }
    for (level = 0; level <= 6; level++) {
        if (level == 0) {
            if (lbl_803A2628[level] > lbl_802FB3F8[level]) {
                do {
                    if (!fn_80234394((Instance_8023424C **)lbl_803A2648, lbl_803EC0F0, level)) {
                        break;
                    }
                    lbl_803A2628[level]--;
                    lbl_803A2628[level + 1]++;
                } while (lbl_803A2628[level] > lbl_802FB3F8[level]);
            }
        } else {
            while (lbl_803A2628[level] > lbl_802FB3F8[level]
                                             + (lbl_802FB3F8[level - 1] - lbl_803A2628[level - 1])) {
                if (!fn_80234394((Instance_8023424C **)lbl_803A2648, lbl_803EC0F0, level)) {
                    break;
                }
                lbl_803A2628[level]--;
                lbl_803A2628[level + 1]++;
            }
        }
    }
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

void ModelPassShadersClear(void)
{
    /* FAKEMATCH: the volatile store keeps the address in r9 (addi r9,r13 / stw 0(r9)). */
    *(volatile int *)&lbl_803ED024 = 0;
    lbl_803ED020 = 0;
}

/* Allocates count zeroed floats for pArray. */
void FloatArrayAlloc(Array_8023491C *pArray, unsigned int count)
{
    unsigned int i;

    pArray->mUnknown0 = count;
    pArray->mpUnknown4 = fn_801D2B7C(count * sizeof(float), 0, 0);
    for (i = 0; i < pArray->mUnknown0; i++) {
        pArray->mpUnknown4[i] = lbl_802B7168[0];
    }
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

/* Clears the 0x90-byte block and sets its three scale floats +0x80..+0x88 to 1. */
void ScaleBlockReset(Block_802349CC *pBlock)
{
    memset(pBlock, 0, sizeof(Block_802349CC));
    pBlock->mScale[0] = lbl_802B7170[0];
    pBlock->mScale[1] = lbl_802B7170[0];
    pBlock->mScale[2] = lbl_802B7170[0];
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
    ScaleBlockReset(p);
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
