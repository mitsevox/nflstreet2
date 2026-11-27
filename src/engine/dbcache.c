/* Partial source: the game database's id-remap caches, used when team and player rows are
   copied between databases or deleted. Each cache is keyed by an open database handle and
   keeps, per id column ('DIGT' of the team table, 'DIGP' of the player table), arrays that map
   old ids to new ones (new ids come from the unused-id fill); DbCacheUpdateHandler applies the
   remap while DbCacheCopyRows copies rows. The caches are kept in one linked list. */

#include "engine/TDbCreate.h"
#include "engine/tdbext.h"
#include "engine/dbutil.h"
#include "engine/TDbLoad.h"
#include "engine/t3db_cols.h"
#include "engine/t3db.h"

#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>
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
    int *mpUnknown12[2];
    int *mpUnknown20[2];
    int *mpUnknown28[2];
    int mUnknown36;
    int mUnknown40[2];
    struct CacheRec_8022F8A8 {
        int mUnknown0;
        int mUnknown4;
        int mUnknown8;
        int mUnknown12;
    } mUnknown48[3];
    struct Cache_8022F8A8 *mpUnknown96;
    struct Cache_8022F8A8 *mpUnknown100;
} Cache_8022F8A8;

/* 20-byte entry of the cached-column table 0x802FB340 (two entries: 'DIGT' of 'MAET',
   'DIGP' of 'YALP'). */
typedef struct CacheCol_802FB340 {
    int mCol;
    int mTable;
    int mFill;
    int mUnknown12;
    int (*mpFill)(int key, int table, int *pValues, unsigned short *pCount);
} CacheCol_802FB340;

typedef struct Entry_802FB310 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
} Entry_802FB310;

/* Index column list element passed to TDbIdxCreate (src/engine/t3db.c TDbIdxCol_801F9E84). */
typedef struct DbCacheIdxCol_t {
    int mTable;
    int mCol;
    int mUnknown8;
    unsigned char mIdx;
} DbCacheIdxCol_t;

/* Bit i of the bit set at p, tested and set one byte at a time. */
#define DBCACHE_BIT(i) (1 << ((i) & 7))
#define DBCACHE_BIT_IS_SET(p, i) ((((unsigned char *)(p))[(i) >> 3] & DBCACHE_BIT(i)) == DBCACHE_BIT(i))

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
extern DbUserEntry_t _DbUser_aEntries[];
int DbFindUnusedPlayerIds(int handle, int table, int *pIds, unsigned short *pCount);

static Entry_802FB310 _DbCache_aTables[3] = {
    { 0x54484344, 0x54484344, 0x44494754, 0x31494454 },
    { 0x59414C50, 0x59414C50, 0x44494754, 0x33494454 },
    { 0x4D414554, 0x4D414554, 0x44494754, 0x35494454 },
};
static CacheCol_802FB340 _DbCache_aCachedCols[2] = {
    { 0x44494754, 0x4D414554, 0x3FF, 0x3F1, 0 },
    { 0x44494750, 0x59414C50, 0x7FFF, 0x7F15, DbFindUnusedPlayerIds },
};
extern int lbl_802FB3F8[];
extern void *lbl_803A2648[];
extern Table_803E96E8 lbl_803E96E8;
extern int _DbUser_iSize;
extern char *_DbUser_pFileName;
extern int _DbUser_iMode;
extern int _DbUser_iCurrent;
extern unsigned char _DbUser_iCount;
static Cache_8022F8A8 *_DbCache_pList = 0;
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
extern int TDbTblColExists(int db, int tbl, int col);
extern int TDbTblColEnum(int db, int tbl, TDbColInfo_801F9AB8 *pCols, unsigned int *pCount);
extern int TDbTblColGetInfo(int db, int tbl, int col, TDbColInfo_801F9AB8 *pInfo);
extern int TDbTblDestroy(int db, int tbl);
extern int TDbTblRowCopyTrig(int db, int tbl, int dstDb, int dstTbl, void *pRes, int cb);
extern int TDbIdxExists(int db, int tbl, int idx);
extern int TDbIdxCreate(int db, int tbl, int idx, DbCacheIdxCol_t *pCols, TDbExpr_t *pWhere, int b);
extern int TDbIdxDestroy(int db, int tbl, int idx);
extern int _TDbQrySelect(int db, TDbSQLTableRef_801FDC18 *pTables, TDbExpr_t *pWhere, void *pOrder, int *pCursor,
                         void *pResult);
extern int TDbQryCreateTbl(int db, int tbl, int cursor, unsigned long long *pKeys, void *pResult);
extern int TDbQryDestroy(int cursor);
extern int TDbQryDeleteRow(int db, TDbSQLTableRef_801FDC18 *pTables, TDbExpr_t *pWhere, void *pResult, int cb);
extern int TDbQryUpdateWithHandler(int db, TDbSQLTableRef_801FDC18 *pTables, TDbExpr_t *pWhere, int tag,
                                   struct CacheRec_8022F8A8 *pRecs, int id, void *pRes, int cb);
extern int TDbTblInfoGetFixedRows(int db, int tbl, unsigned char *pFlag, unsigned short *pValue);
extern int TDbTblInfoGetMaxRows(int db, int tbl, unsigned short *pOut);
extern int MemFill(void *pDst, unsigned int size, int value, unsigned int width);
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
extern int DbCacheCopyRows(unsigned short id, int key, int value, int db, int mode, unsigned int tableMask,
                       unsigned int colMask);
void DbCacheUpdateHandler(int ready, unsigned short id, unsigned char *pDone);
int DbCacheCreateScratchTable(int key, unsigned short index, int db, int *pTable);
int DbCacheDeleteRows(int key, int db, unsigned int tableMask);
extern void ScaleBlockReset(void *p);
struct TMRenderState_t;
struct TMGeomNode_t;
extern void ModelObjEnvMapTexCoords(struct TMRenderState_t *pState, struct TMGeomNode_t *pNode);
extern void fn_80236F00(void);

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

unsigned short DbCacheNewId(void)
{
    unsigned short id;
    Cache_8022F8A8 *pCache;

    for (id = 0; id <= 0xFFFD; id++) {
        for (pCache = _DbCache_pList; pCache != 0 && pCache->mUnknown0 != id; pCache = pCache->mpUnknown100) {
        }
        if (pCache == 0) {
            return id;
        }
    }
    return id;
}

Cache_8022F8A8 *DbCacheFindById(unsigned short id)
{
    Cache_8022F8A8 *pCache;

    for (pCache = _DbCache_pList; pCache != 0 && pCache->mUnknown0 != id; pCache = pCache->mpUnknown100) {
    }
    return pCache;
}

Cache_8022F8A8 *DbCacheFindByDb(int key)
{
    Cache_8022F8A8 *pCache;

    for (pCache = _DbCache_pList; pCache != 0 && pCache->mUnknown4 != key; pCache = pCache->mpUnknown100) {
    }
    return pCache;
}

/* Creates the column cache of key: shares the arrays of an existing cache of the same key,
   otherwise reads each cached column's values into three filled arrays; links the cache
   at the end of the list. */
static inline void _CacheRecInit(struct CacheRec_8022F8A8 *pRec)
{
    pRec->mUnknown8 = -1;
    pRec->mUnknown4 = -1;
    pRec->mUnknown0 = 0;
}

int DbCacheCreate(int key, Cache_8022F8A8 **ppCache)
{
    Cache_8022F8A8 *pCache;
    Cache_8022F8A8 *pOther;
    Cache_8022F8A8 *pLast;
    unsigned short count;
    unsigned short size;
    unsigned char flag;
    int err;
    unsigned short i;

    pCache = DbUtilAlloc(sizeof(Cache_8022F8A8), 0);
    err = 0;
    i = 0;
    pCache->mUnknown0 = DbCacheNewId();
    pCache->mUnknown8 = 1023;
    pCache->mUnknown4 = key;
    pCache->mUnknown36 = err;
    pCache->mpUnknown96 = 0;
    pCache->mpUnknown100 = 0;
    for (; i <= 1; i++) {
        pCache->mpUnknown12[i] = 0;
        pCache->mpUnknown20[i] = 0;
        pCache->mpUnknown28[i] = 0;
        _CacheRecInit(&pCache->mUnknown48[i]);
        pCache->mUnknown40[i] = 0;
    }
    pOther = DbCacheFindByDb(key);
    if (pOther != 0) {
        for (i = 0; i <= 1; i++) {
            pCache->mpUnknown12[i] = pOther->mpUnknown12[i];
            pCache->mpUnknown20[i] = pOther->mpUnknown20[i];
            pCache->mpUnknown28[i] = pOther->mpUnknown28[i];
        }
    } else {
        for (i = 0; i <= 1; i++) {
            if (TDbTblExists(key, _DbCache_aCachedCols[i].mTable) == 0) {
                count = 0;
                err = TDbTblInfoGetFixedRows(key, _DbCache_aCachedCols[i].mTable, &flag, &count);
                if (err == 0 && flag == 0) {
                    err = TDbTblInfoGetMaxRows(key, _DbCache_aCachedCols[i].mTable, &count);
                }
                size = count;
                if (err != 0) {
                    break;
                }
                pCache->mpUnknown12[i] = DbUtilAlloc((count + 1) * 4, 0);
                MemFill(pCache->mpUnknown12[i], (count + 1) * 4, _DbCache_aCachedCols[i].mFill, 4);
                pCache->mpUnknown20[i] = DbUtilAlloc((count + 1) * 4, 0);
                MemFill(pCache->mpUnknown20[i], (count + 1) * 4, _DbCache_aCachedCols[i].mFill, 4);
                pCache->mpUnknown28[i] = DbUtilAlloc((count + 1) * 4, 0);
                MemFill(pCache->mpUnknown28[i], (count + 1) * 4, _DbCache_aCachedCols[i].mFill, 4);
                if (_DbCache_aCachedCols[i].mpFill != 0) {
                    // FAKEMATCH: pointer spelling of _DbCache_aCachedCols[i].mpFill, so the call reloads it
                    (_DbCache_aCachedCols + i)->mpFill(key, _DbCache_aCachedCols[i].mTable, pCache->mpUnknown28[i], &size);
                }
                ((unsigned char *)&pCache->mUnknown36)[i >> 3] |= DBCACHE_BIT(i);
            }
            if (err != 0) {
                break;
            }
        }
    }
    if (err == 0) {
        if (_DbCache_pList == 0) {
            _DbCache_pList = pCache;
        } else {
            for (pLast = _DbCache_pList; pLast->mpUnknown100 != 0; pLast = pLast->mpUnknown100) {
            }
            pLast->mpUnknown100 = pCache;
            pCache->mpUnknown96 = pLast;
        }
    }
    if (err != 0) {
        if (pCache != 0) {
            DbCacheDestroy(pCache);
        }
        *ppCache = 0;
    } else {
        *ppCache = pCache;
    }
    return err;
}

int DbCacheDestroy(Cache_8022F8A8 *pCache)
{
    unsigned short i;

    if (pCache->mUnknown36 != 0) {
        for (i = 0; i <= 1; i++) {
            if (DBCACHE_BIT_IS_SET(&pCache->mUnknown36, i)) {
                DbUtilFree(pCache->mpUnknown12[i]);
                DbUtilFree(pCache->mpUnknown20[i]);
                DbUtilFree(pCache->mpUnknown28[i]);
            }
        }
    }
    if (pCache->mpUnknown96 != 0) {
        pCache->mpUnknown96->mpUnknown100 = pCache->mpUnknown100;
    }
    if (pCache->mpUnknown100 != 0) {
        pCache->mpUnknown100->mpUnknown96 = pCache->mpUnknown96;
    }
    if (_DbCache_pList == pCache) {
        if (pCache->mpUnknown100 != 0) {
            _DbCache_pList = pCache->mpUnknown100;
        } else {
            _DbCache_pList = 0;
        }
    }
    DbUtilFree(pCache);
    return 0;
}

void DbCacheUpdateHandler(int ready, unsigned short id, unsigned char *pDone)
{
    Cache_8022F8A8 *pCache;
    unsigned short i;
    unsigned short j;
    unsigned short k;

    if (ready == 0) {
        if (pDone != 0) {
            *pDone = 0;
        }
        return;
    }
    if (pDone == 0) {
        return;
    }
    pCache = DbCacheFindById(id);
    for (i = 0; pCache->mUnknown48[i].mUnknown8 != -1; i++) {
        for (j = 0; j <= 1; j++) {
            if (_DbCache_aCachedCols[j].mCol == pCache->mUnknown48[i].mUnknown8) {
                break;
            }
        }
        if ((unsigned int)pCache->mUnknown48[i].mUnknown0 < (unsigned int)_DbCache_aCachedCols[j].mUnknown12) {
            for (;;) {
                for (k = pCache->mUnknown40[j]; pCache->mpUnknown20[j][k] != _DbCache_aCachedCols[j].mFill; k++) {
                    if (pCache->mpUnknown12[j][k] == pCache->mUnknown8
                        && pCache->mpUnknown20[j][k] == pCache->mUnknown48[i].mUnknown0) {
                        break;
                    }
                }
                if (pCache->mpUnknown20[j][k] != _DbCache_aCachedCols[j].mFill || pCache->mUnknown40[j] == 0) {
                    break;
                }
                pCache->mUnknown40[j] = 0;
            }
            pCache->mUnknown40[j] = k;
            if (pCache->mpUnknown20[j][k] == _DbCache_aCachedCols[j].mFill) {
                pCache->mpUnknown20[j][k] = pCache->mUnknown48[i].mUnknown0;
                pCache->mpUnknown12[j][k] = pCache->mUnknown8;
                if (j == 0) {
                    pCache->mpUnknown28[j][k] = pCache->mUnknown8;
                    pCache->mUnknown48[i].mUnknown0 = pCache->mUnknown8;
                    continue;
                }
            }
            pCache->mUnknown48[i].mUnknown0 = pCache->mpUnknown28[j][k];
        }
    }
    *pDone = 1;
}

/* Writes one 64-bit column key (owner word, column id) per column of pInfo, the 'DIGT'
   column keyed by digtKey instead of key, then the -1 terminator. */
void DbCacheWriteColumnKeys(unsigned int key, unsigned int digtKey, TDbColInfo_801F9AB8 *pInfo,
                 unsigned long long *pKeys, unsigned short count)
{
    unsigned char i;

    for (i = 0; i < count; i++) {
        if (pInfo[i].mCol == 0x44494754) {
            pKeys[i] = ((unsigned long long)digtKey << 32) | (unsigned int)pInfo[i].mCol;
        } else {
            pKeys[i] = ((unsigned long long)key << 32) | (unsigned int)pInfo[i].mCol;
        }
    }
    pKeys[i] = -1;
}

static inline unsigned long long _DbCacheColKey(unsigned int table, unsigned int col)
{
    return ((unsigned long long)table << 32) | col;
}

/* Ends a column list: type 18, no column. */
static inline void _DbCacheSetColEnd(TDbColInfo_801F9AB8 *pCol)
{
    pCol->mCol = -1;
    pCol->mType = 18;
    pCol->mSize = 0;
    pCol->mUnk4 = -1;
}

static inline void _DbCacheSetTable(TDbSQLTableRef_801FDC18 *pRef, unsigned int id, unsigned int join,
                                    TDbExpr_t *pExpr)
{
    pRef->mExpr = pExpr;
    pRef->mId = id;
    pRef->mJoinType = join;
}

static inline void _DbCacheSetIdxCol(DbCacheIdxCol_t *pCol, int table, int col, int flags)
{
    pCol->mTable = table;
    pCol->mCol = col;
    pCol->mUnknown8 = flags;
}

/* column == value */
static inline void _DbCacheSetValueExpr(TDbExpr_t *pExpr, unsigned long long col, int value)
{
    pExpr->mOp = 0x10003;
    pExpr->mLeft.mType = 6;
    pExpr->mLeft.mValue.l = col;
    pExpr->mRight.mType = 3;
    pExpr->mRight.mValue.i = value;
}

/* column == column */
static inline void _DbCacheSetJoinExpr(TDbExpr_t *pExpr, unsigned long long colA, unsigned long long colB)
{
    pExpr->mOp = 0x10003;
    pExpr->mLeft.mType = 6;
    pExpr->mLeft.mValue.l = colA;
    pExpr->mRight.mType = 6;
    pExpr->mRight.mValue.l = colB;
}

/* a && b */
static inline void _DbCacheSetAndExpr(TDbExpr_t *pExpr, TDbExpr_t *pA, TDbExpr_t *pB)
{
    pExpr->mOp = 0x20009;
    pExpr->mLeft.mType = 11;
    pExpr->mLeft.mValue.p = pA;
    pExpr->mRight.mType = 11;
    pExpr->mRight.mValue.p = pB;
}

int DbCacheCreateScratchTable(int key, unsigned short index, int db, int *pTable)
{
    TDbColInfo_801F9AB8 aCols[254];
    unsigned long long aKeys[254];
    TDbSQLTableRef_801FDC18 aTables[3];
    TDbExpr_t where;
    TDbExpr_t join;
    TDbExpr_t match;
    int table;
    unsigned int count;
    int cursor;
    int hasTeam;
    int found;
    int ok;
    int err;

    cursor = 0;
    hasTeam = TDbTblColExists(db, _DbCache_aTables[index].mUnknown0, 0x44494754) == 0;
    err = TDbTblFindUnusedId(db, &table);
    count = 0;
    if (err == 0) {
        count = 254;
        err = TDbTblColEnum(db, _DbCache_aTables[index].mUnknown0, aCols, &count);
        if (err == 0 && key != 1023 && hasTeam == 0) {
            err = TDbTblColGetInfo(db, 0x4D414554, 0x44494754, &aCols[count]);
            count++;
        }
    }
    _DbCacheSetColEnd(&aCols[count]);
    if (err == 0) {
        DbCacheWriteColumnKeys(_DbCache_aTables[index].mUnknown0, _DbCache_aTables[index].mUnknown4, aCols, aKeys,
                               count);
        if (key == 1023) {
            _DbCacheSetTable(&aTables[0], _DbCache_aTables[index].mUnknown0, 2, 0);
            _DbCacheSetTable(&aTables[1], -1, 2, 0);
        } else if (hasTeam == 1) {
            _DbCacheSetValueExpr(&where, _DbCacheColKey(_DbCache_aTables[index].mUnknown0, 0x44494754), key);
            _DbCacheSetTable(&aTables[0], _DbCache_aTables[index].mUnknown0, 2, &where);
            _DbCacheSetTable(&aTables[1], -1, 2, 0);
        } else {
            _DbCacheSetAndExpr(&where, &join, &match);
            _DbCacheSetJoinExpr(&join, _DbCacheColKey(_DbCache_aTables[index].mUnknown0, _DbCache_aTables[index].mUnknown8),
                                _DbCacheColKey(_DbCache_aTables[index].mUnknown4, _DbCache_aTables[index].mUnknown8));
            _DbCacheSetValueExpr(&match, _DbCacheColKey(_DbCache_aTables[index].mUnknown4, 0x44494754), key);
            _DbCacheSetTable(&aTables[0], _DbCache_aTables[index].mUnknown0, 2, 0);
            _DbCacheSetTable(&aTables[1], _DbCache_aTables[index].mUnknown4, 0, &where);
            _DbCacheSetTable(&aTables[2], -1, 2, 0);
        }
    }
    found = 0;
    if (err == 0) {
        err = _TDbQrySelect(db, aTables, 0, 0, &cursor, 0);
        ok = 0;
        if (err == 0 || err == 23 || err == 21 || err == 20) {
            ok = 1;
        }
        if (ok == 1) {
            found = 1;
        }
    }
    if (found == 1) {
        err = TDbQryCreateTbl(db, table, cursor, aKeys, 0);
        /* Redundant (found is already 1): kept for the target's dead 0/23 test at 0x8023031C/20
           (holdout, see its HOLDOUT row). */
        if (err == 0 || err == 23) {
            found = 1;
        }
    }
    if (found == 1) {
        ok = 0;
        if (err == 0 || err == 23 || err == 21 || err == 20) {
            ok = 1;
        }
        if (ok == 1) {
            err = TDbQryDestroy(cursor);
        } else {
            TDbQryDestroy(cursor);
        }
    }
    *pTable = err == 0 ? table : -1;
    return err;
}

int DbCacheGetTableId(int index)
{
    return _DbCache_aTables[index].mUnknown0;
}

int DbCacheOpen(int key, unsigned short *pId)
{
    Cache_8022F8A8 *pCache;
    int err = DbCacheCreate(key, &pCache);

    if (err == 0) {
        *pId = pCache->mUnknown0;
    } else {
        *pId = 0xFFFF;
    }
    return err;
}

int DbCacheCopyRows(unsigned short id, int key, int value, int db, int mode, unsigned int tableMask,
                unsigned int colMask)
{
    int aNew[3];
    TDbSQLTableRef_801FDC18 aTables[2];
    DbCacheIdxCol_t aCols[2];
    TDbExpr_t where;
    int aCreated[3];
    unsigned int aColMask[3];
    Cache_8022F8A8 *pCache;
    unsigned short i;
    unsigned short j;
    unsigned short n;
    int tag;
    int registered;
    int ok;
    int err;

    err = 0;
    i = 0;
    pCache = DbCacheFindById(id);
    pCache->mUnknown8 = value;
    for (; i <= 2; i++) {
        if (DBCACHE_BIT_IS_SET(&tableMask, i)) {
            if (TDbTblExists(db, _DbCache_aTables[i].mUnknown0) != 0
                || TDbTblExists(pCache->mUnknown4, _DbCache_aTables[i].mUnknown0) != 0) {
                ((unsigned char *)&tableMask)[i >> 3] &= ~DBCACHE_BIT(i);
            }
        }
    }
    if (tableMask != 0) {
        if (key != 1023) {
            for (i = 0; i <= 2; i++) {
                aCreated[i] = 0;
                if (err == 0 && DBCACHE_BIT_IS_SET(&tableMask, i)
                    && TDbTblExists(db, _DbCache_aTables[i].mUnknown4) == 0
                    && TDbIdxExists(db, _DbCache_aTables[i].mUnknown4, _DbCache_aTables[i].mUnknown12) == 13) {
                    _DbCacheSetIdxCol(&aCols[0], _DbCache_aTables[i].mUnknown4, 0x44494754, err);
                    n = 1;
                    if (TDbTblColExists(db, _DbCache_aTables[i].mUnknown4, 0x44494750) == 0) {
                        n = 2;
                        _DbCacheSetIdxCol(&aCols[1], _DbCache_aTables[i].mUnknown4, 0x44494750, err);
                    }
                    _DbCacheSetIdxCol(&aCols[n], -1, -1, 3);
                    _DbCacheSetValueExpr(&where, _DbCacheColKey(_DbCache_aTables[i].mUnknown4, 0x44494754), key);
                    err = TDbIdxCreate(db, _DbCache_aTables[i].mUnknown4, _DbCache_aTables[i].mUnknown12, aCols,
                                       &where, 0);
                    if (err == 0) {
                        aCreated[i] = 1;
                    }
                }
            }
        }
        if (err == 0 && colMask != 0) {
            for (j = 0; j <= 1; j++) {
                if (DBCACHE_BIT_IS_SET(&colMask, j)
                    && TDbTblExists(pCache->mUnknown4, _DbCache_aCachedCols[j].mTable) != 0) {
                    ((unsigned char *)&colMask)[j >> 3] &= ~DBCACHE_BIT(j);
                }
            }
            for (i = 0; i <= 2; i++) {
                aColMask[i] = 0;
                if (DBCACHE_BIT_IS_SET(&tableMask, i)) {
                    for (j = 0; j <= 1; j++) {
                        if (DBCACHE_BIT_IS_SET(&colMask, j)
                            && TDbTblColExists(db, _DbCache_aTables[i].mUnknown0, _DbCache_aCachedCols[j].mCol) == 0) {
                            ((unsigned char *)&aColMask[i])[j >> 3] |= DBCACHE_BIT(j);
                        }
                    }
                }
            }
        }
        MemFill(aNew, sizeof(aNew), -1, 4);
        if (err == 0) {
            if (key != 1023) {
                for (i = 0; i <= 2; i++) {
                    if (DBCACHE_BIT_IS_SET(&tableMask, i)) {
                        err = DbCacheCreateScratchTable(key, i, db, &aNew[i]);
                        if (err != 0) {
                            goto cleanup;
                        }
                    }
                }
            }
            if (err != 0) {
                goto cleanup;
            }
            if (colMask != 0 && mode == 1) {
                for (i = 0; i <= 2; i++) {
                    if (DBCACHE_BIT_IS_SET(&tableMask, i) && aNew[i] == -1 && aColMask[i] != 0) {
                        err = DbCacheCreateScratchTable(key, i, db, &aNew[i]);
                        if (err != 0) {
                            goto cleanup;
                        }
                    }
                }
            }
            if (err == 0) {
                for (i = 0; i <= 2; i++) {
                    if (DBCACHE_BIT_IS_SET(&tableMask, i) && aNew[i] == -1) {
                        aNew[i] = _DbCache_aTables[i].mUnknown0;
                    }
                }
            }
            if (err != 0) {
                goto cleanup;
            }
            if (colMask != 0) {
                tag = ((pCache->mUnknown0 > 9 ? pCache->mUnknown0 % 10 + '0' : pCache->mUnknown0 + '0') << 24)
                    | ((pCache->mUnknown0 > 9 ? pCache->mUnknown0 / 10 + '0' : '0') << 16) | ('D' << 8) | 'T';
                err = TDbRegisterHandler(DbCacheUpdateHandler, tag);
                registered = err == 0;
                if (err == 0) {
                    for (i = 0; i <= 2; i++) {
                        if (aColMask[i] != 0) {
                            _DbCacheSetTable(&aTables[0], aNew[i], 2, 0);
                            _DbCacheSetTable(&aTables[1], -1, 2, 0);
                            n = 0;
                            for (j = 0; j <= 1; j++) {
                                if (DBCACHE_BIT_IS_SET(&aColMask[i], j)) {
                                    pCache->mUnknown48[n].mUnknown8 = _DbCache_aCachedCols[j].mCol;
                                    pCache->mUnknown48[n].mUnknown4 = aNew[i];
                                    n++;
                                }
                            }
                            pCache->mUnknown48[n].mUnknown0 = 0;
                            pCache->mUnknown48[n].mUnknown8 = -1;
                            pCache->mUnknown48[n].mUnknown4 = -1;
                            err = TDbQryUpdateWithHandler(db, aTables, 0, tag, pCache->mUnknown48, pCache->mUnknown0, 0,
                                                          0);
                            ok = 0;
                            if (err == 0 || err == 23 || err == 21 || err == 20) {
                                ok = 1;
                            }
                            if (ok == 1) {
                                err = 0;
                            }
                        }
                        if (err != 0) {
                            break;
                        }
                    }
                }
                if (registered == 1) {
                    if (err == 0) {
                        err = TDbUnregisterHandler(tag);
                    } else {
                        TDbUnregisterHandler(tag);
                    }
                }
            }
            if (err == 0) {
                for (i = 0; i <= 2; i++) {
                    if (DBCACHE_BIT_IS_SET(&tableMask, i)) {
                        err = TDbTblRowCopyTrig(db, aNew[i], pCache->mUnknown4, _DbCache_aTables[i].mUnknown0, 0, 0);
                        ok = 0;
                        if (err == 0 || err == 23 || err == 21 || err == 20) {
                            ok = 1;
                        }
                        if (ok != 1) {
                            break;
                        }
                        err = 0;
                    }
                }
            }
        }
cleanup:
        for (i = 0; i <= 2; i++) {
            if (aNew[i] != -1 && aNew[i] != _DbCache_aTables[i].mUnknown0) {
                if (err == 0) {
                    err = TDbTblDestroy(db, aNew[i]);
                } else {
                    TDbTblDestroy(db, aNew[i]);
                }
            }
        }
        if (key != 1023) {
            for (i = 0; i <= 2; i++) {
                if (aCreated[i] == 1) {
                    if (err == 0) {
                        err = TDbIdxDestroy(db, _DbCache_aTables[i].mUnknown4, _DbCache_aTables[i].mUnknown12);
                    } else {
                        TDbIdxDestroy(db, _DbCache_aTables[i].mUnknown4, _DbCache_aTables[i].mUnknown12);
                    }
                }
            }
        }
        pCache->mUnknown8 = 1023;
    }
    return err;
}

int DbCacheClose(unsigned short id)
{
    return DbCacheDestroy(DbCacheFindById(id));
}

int DbCacheCopy(int a, int b, int c, int key, int e, int f)
{
    unsigned short id;
    int err = DbCacheOpen(key, &id);

    if (err == 0) {
        err = DbCacheCopyRows(id, a, a, b, c, e, f);
    }
    if (id != 0xFFFF) {
        if (err == 0) {
            err = DbCacheClose(id);
        } else {
            DbCacheClose(id);
        }
    }
    return err;
}

int DbCacheDeleteRows(int key, int db, unsigned int tableMask)
{
    TDbSQLTableRef_801FDC18 aTables[3];
    TDbExpr_t where;
    TDbExpr_t match;
    TDbExpr_t join;
    DbCacheIdxCol_t aCols[2];
    int aCreated[3];
    unsigned int *pMask = &tableMask;
    unsigned short i;
    int err;

    err = 0;
    if (key != 1023) {
        for (i = 0; i <= 2; i++) {
            aCreated[i] = 0;
            if (err == 0 && DBCACHE_BIT_IS_SET(pMask, i) && TDbTblExists(db, _DbCache_aTables[i].mUnknown4) == 0
                && TDbIdxExists(db, _DbCache_aTables[i].mUnknown4, _DbCache_aTables[i].mUnknown12) == 13) {
                _DbCacheSetIdxCol(&aCols[0], _DbCache_aTables[i].mUnknown4, 0x44494754, err);
                _DbCacheSetIdxCol(&aCols[1], -1, -1, 3);
                _DbCacheSetValueExpr(&where, _DbCacheColKey(_DbCache_aTables[i].mUnknown4, 0x44494754), key);
                err = TDbIdxCreate(db, _DbCache_aTables[i].mUnknown4, _DbCache_aTables[i].mUnknown12, aCols, &where, 0);
                if (err == 0) {
                    aCreated[i] = 1;
                }
            }
        }
    }
    for (i = 0; i <= 2; i++) {
        if (DBCACHE_BIT_IS_SET(pMask, i) && TDbTblExists(db, _DbCache_aTables[i].mUnknown0) == 0) {
            if (key == 1023) {
                _DbCacheSetTable(&aTables[0], _DbCache_aTables[i].mUnknown0, 2, 0);
                _DbCacheSetTable(&aTables[1], -1, 2, 0);
            } else if (TDbTblColExists(db, _DbCache_aTables[i].mUnknown0, 0x44494754) == 0) {
                _DbCacheSetValueExpr(&where, _DbCacheColKey(_DbCache_aTables[i].mUnknown0, 0x44494754), key);
                _DbCacheSetTable(&aTables[0], _DbCache_aTables[i].mUnknown0, 2, &where);
                _DbCacheSetTable(&aTables[1], -1, 2, 0);
            } else {
                _DbCacheSetAndExpr(&where, &match, &join);
                _DbCacheSetValueExpr(&match, _DbCacheColKey(_DbCache_aTables[i].mUnknown4, 0x44494754), key);
                _DbCacheSetJoinExpr(&join, _DbCacheColKey(_DbCache_aTables[i].mUnknown0, _DbCache_aTables[i].mUnknown8),
                                    _DbCacheColKey(_DbCache_aTables[i].mUnknown4, _DbCache_aTables[i].mUnknown8));
                _DbCacheSetTable(&aTables[0], _DbCache_aTables[i].mUnknown0, 2, 0);
                _DbCacheSetTable(&aTables[1], _DbCache_aTables[i].mUnknown4, 0, &where);
                _DbCacheSetTable(&aTables[2], -1, 2, 0);
            }
            if (err == 0) {
                err = TDbQryDeleteRow(db, aTables, 0, 0, 0);
            } else {
                TDbQryDeleteRow(db, aTables, 0, 0, 0);
            }
        }
    }
    if (key != 1023) {
        for (i = 0; i <= 2; i++) {
            if (aCreated[i] == 1) {
                if (err == 0) {
                    err = TDbIdxDestroy(db, _DbCache_aTables[i].mUnknown4, _DbCache_aTables[i].mUnknown12);
                } else {
                    TDbIdxDestroy(db, _DbCache_aTables[i].mUnknown4, _DbCache_aTables[i].mUnknown12);
                }
            }
        }
    }
    return err;
}
