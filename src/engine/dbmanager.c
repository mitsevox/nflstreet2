/* Partial source: starts and stops every game-database module and runs the game-mode steps over the database tables. */

#include "engine/TDbCreate.h"
#include "engine/tdbext.h"
#include "engine/dbutil.h"
#include "engine/TDbLoad.h"

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
extern char lbl_802B7128[];
extern char lbl_802B7130[];
extern char lbl_802B7154[];
extern char lbl_802B715C[];
extern DbUserEntry_t _DbUser_aEntries[];
extern Entry_802FB310 lbl_802FB310[];
extern int lbl_802FB3F8[];
extern void *lbl_803A2648[];
extern Table_803E96E8 lbl_803E96E8;
extern int _DbUser_iSize;
extern char *_DbUser_pFileName;
extern int _DbUser_iMode;
extern int _DbUser_iCurrent;
extern unsigned char _DbUser_iCount;
extern Cache_8022F8A8 *lbl_803EC0E0;
extern int lbl_803EC0E4;
extern int lbl_803EC0E8;
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
extern int DbResetGameInfo(void);
extern int fn_8022DBF4(int a);
extern int fn_8022DC38(int a);
extern int DbRunUpdateChain(int a, int b, unsigned char *p, int *pA, int *pB);
extern int DbRunLoadChain(void);
extern int fn_8022E9A4(void);
extern void fn_8022E9C4(void);
extern int fn_8022E9E4(void);
extern int DbEvasModuleInit(void);
extern void DbEvasModuleShutdown(void);
extern int DbTatsCopyAllTables(int a, int b, int c);
extern signed char DbUserFindIndex(int key);
extern int DbUserGetDb(int key);
extern int fn_8022F8A8(int key, Cache_8022F8A8 **ppCache);
extern int fn_80230400(unsigned short id, int a, int b, int c, int d, int e, int f);
extern void ScaleBlockReset(void *p);
extern void fn_80235010(Table_803E96E8 *pTable, void *pEntry);
extern void fn_80236F00(void);

void fn_8023123C(void *p, int mode, unsigned char *pDone);
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

static DbNiomHandlers_t _DbManager_Handlers = { DbManagerShutdown, DbManagerLoad, DbManagerSave };
static int _DbManager_aResultFuncs[3] = { (int)DbManagerResultAccept, (int)DbManagerResultRecord, (int)DbManagerResultFinish };
static int _DbManager_aSaveTables[3] = { 0x45564153, 0x45564153, -1 };
static int _DbManager_aOptionTables[3] = { 0x54504F53, 0x54504F47, -1 };
static DbNiomModeFuncs_t _DbManager_Mode0Funcs = { DbManagerMode0Leave, DbManagerMode0Load, DbManagerMode0Save, DbManagerMode0Finish, DbManagerMode0Abort };
static DbNiomModeFuncs_t _DbManager_Mode1Funcs = { DbManagerMode1Leave, DbManagerMode1Load, DbManagerMode1Save, DbManagerMode1Finish, DbManagerMode1Abort };
static DbNiomModeFuncs_t _DbManager_Mode2Funcs = { DbManagerMode2Leave, DbManagerMode2Load, DbManagerMode2Save, DbManagerMode2Finish, DbManagerMode2Abort };

int DbManagerInitModules(void)
{
    int err;

    if ((err = DbEvasModuleInit()) != 0) {
        return err;
    }
    if ((err = DbOptionsModuleInit()) != 0) {
        return err;
    }
    if ((err = DbOcmtModuleInit()) != 0) {
        return err;
    }
    if ((err = fn_8022E9A4()) != 0) {
        return err;
    }
    if ((err = fn_80229E88()) != 0) {
        return err;
    }
    if ((err = fn_8022B02C(0)) != 0) {
        return err;
    }
    if ((err = fn_8022C214(0)) != 0) {
        return err;
    }
    if ((err = fn_802299FC()) != 0) {
        return err;
    }
    if ((err = fn_8022D6E8()) != 0) {
        return err;
    }
    if ((err = fn_8022D154()) != 0) {
        return err;
    }
    return fn_8022DA90(_DbManager_aResultFuncs);
}

void DbManagerShutdownModules(void)
{
    fn_8022DB08();
    fn_8022D1B8();
    fn_8022D6F0();
    fn_80229A70();
    fn_8022C3C8();
    fn_8022B200();
    fn_8022A304();
    fn_8022E9C4();
    DbOcmtModuleShutdown();
    DbOptionsModuleShutdown();
    DbEvasModuleShutdown();
}

int DbManagerPushGameDb(void)
{
    return TDbTblDefaultDbPush(0x454D4147, _DbManager_aOptionTables, _DbManager_aSaveTables);
}

int DbManagerPopGameDb(void)
{
    return TDbTblDefaultDbPop();
}

int DbManagerInit(struct Request_802329F0 *p)
{
    int result;
    DbNiomSetHandlers(&_DbManager_Handlers);
    result = DbManagerCreateGameDb((Block_80233588 *)&p->mSize);
    if (result == 0) {
        result = DbManagerPushGameDb();
        if (result == 0) {
            result = DbManagerInitHook();
            if (result == 0) {
                result = fn_80230CEC(1023, 0x54415453, 1, 0x454D4147, 0x04000000, 0);
                if (result == 0) {
                    result = DbNiomBeginMode(&p->mMode);
                    if (result == 0) {
                        result = DbManagerInitModules();
                        if (result == 0) {
                            result = DbManagerEnterMode0();
                        }
                    }
                }
            }
        }
    }
    return result;
}

int DbManagerShutdown(void)
{
    int err;

    DbManagerShutdownModules();
    err = DbManagerPopGameDb();
    if (TDbExists(0x454D4147) == 0) {
        if (err == 0) {
            err = DbManagerDestroyGameDb();
        } else {
            DbManagerDestroyGameDb();
        }
    }
    return err;
}

int DbManagerLoad(void **ppData, void *p)
{
    DbNiomModeFuncs_t funcs;
    int mode;
    int err;

    DbManagerShutdownModules();
    if ((err = DbManagerLoadGameDb(ppData, p)) != 0) {
        return err;
    }
    if ((err = DbManagerInitModules()) != 0) {
        return err;
    }
    mode = 0;
    if ((err = TDbCompilePerformOp(0, "select 'ASCM' into \202 from 'NIOM'\n", &mode)) != 0) {
        return err;
    }
    DbManagerGetModeFuncs(mode, &funcs);
    DbNiomSetModeFuncs(&funcs);
    return DbNiomModeLoad(ppData, p);
}

int DbManagerSave(int a, int b)
{
    struct QueryCursor cursor;
    int mode;
    int id;
    int err = TDbCompilePerformOp(0, "select 'ASCM' into \202 from 'NIOM'\n", &mode);

    if (err == 0) {
        if (mode != 2) {
            cursor.mUnknown0 = 0;
            cursor.mUnknown4 = 0;
            cursor.mUnknown8 = -1;
            cursor.mUnknown12 = 0;
            err = TDbCompilePerformOp(0, "declare \212 cursor for select * from 'LBAT' where ('OIFT' = \202)\n", &cursor, 1);
            if (err == 0) {
                do {
                    err = TDbCompilePerformOp(0, "fetch from \212 'FERT' into \202\n", &cursor, &id);
                    if (err != 0) {
                        break;
                    }
                    err = TDbCompilePerformOp(0, "delete from \214\n", id);
                } while (err == 0);
            }
            if (QUERY_STATUS_ACCEPTED(err) == 1) {
                if (cursor.mUnknown0 != 0) {
                    err = TDbSQLDestroyCursor(&cursor);
                } else {
                    err = 0;
                }
            } else if (cursor.mUnknown0 != 0) {
                TDbSQLDestroyCursor(&cursor);
            }
        }
        if (err == 0) {
            cursor.mUnknown0 = 0;
            cursor.mUnknown4 = 0;
            cursor.mUnknown8 = -1;
            cursor.mUnknown12 = 0;
            err = TDbCompilePerformOp(0, "declare \212 cursor for select * from 'LBAT' where ('EPFT' = \202)\n", &cursor, 0);
            if (err == 0) {
                do {
                    err = TDbCompilePerformOp(0, "fetch from \212 'FERT' into \202\n", &cursor, &id);
                    if (err != 0) {
                        break;
                    }
                    if (TDbTblExists(0, id) == 0) {
                        err = TDbTblInfoSetPersistent(0, id, 0);
                    }
                } while (err == 0);
            }
            if (QUERY_STATUS_ACCEPTED(err) == 1) {
                if (cursor.mUnknown0 != 0) {
                    err = TDbSQLDestroyCursor(&cursor);
                } else {
                    err = 0;
                }
            } else if (cursor.mUnknown0 != 0) {
                TDbSQLDestroyCursor(&cursor);
            }
            if (err == 0) {
                err = DbNiomModeReset(a, b);
            }
        }
    }
    return err;
}

int DbManagerEnterMode0(void)
{
    DbNiomSetModeFuncs(&_DbManager_Mode0Funcs);
    return TDbCompilePerformOp(0, "update 'NIOM' set 'ASCM' = \202\n", 0);
}

int DbManagerMode0Leave(void)
{
    int err = TDbCompilePerformOp(0, "update 'NIOM' set 'ASPM' = \202 and 'ASCM' = \202\n", 0, 4);

    if (err == 0) {
        DbNiomClearModeFuncs();
    }
    return err;
}

int DbManagerMode0Load(void)
{
    return 0;
}

int DbManagerMode0Save(void)
{
    return 0;
}

int DbManagerMode0Finish(void)
{
    int err = DbManagerMode0Leave();

    if (err == 0) {
        err = DbManagerEnterMode1();
    }
    return err;
}

int DbManagerMode0Abort(void)
{
    return 0;
}

int DbManagerEnterMode1(void)
{
    DbNiomSetModeFuncs(&_DbManager_Mode1Funcs);
    return TDbCompilePerformOp(0, "update 'NIOM' set 'ASCM' = \202\n", 1);
}

int DbManagerMode1Leave(void)
{
    int err = TDbCompilePerformOp(0, "update 'NIOM' set 'ASPM' = \202 and 'ASCM' = \202\n", 1, 4);

    if (err == 0) {
        DbNiomClearModeFuncs();
    }
    return err;
}

int DbManagerMode1Load(void)
{
    return 0;
}

int DbManagerMode1Save(void)
{
    return 0;
}

int DbManagerMode1Finish(void)
{
    return DbManagerMode1Leave();
}

int DbManagerMode1Abort(void)
{
    int mode;
    int err = TDbCompilePerformOp(0, "select 'ASPM' into \202 from 'NIOM'\n", &mode);

    if (err == 0) {
        if (mode == 4) {
            err = DbNiomEndMode();
        } else {
            err = DbManagerMode1Leave();
            if (err == 0) {
                err = DbManagerEnterMode0();
            }
        }
    }
    return err;
}

int DbManagerEnterMode2(int *pRecord0, int *pRecord1)
{
    unsigned char flag;
    unsigned char result;
    int id0;
    int id1;
    unsigned int i;
    int err;

    DbNiomSetModeFuncs(&_DbManager_Mode2Funcs);
    err = TDbCompilePerformOp(0, "select 'PNIG' into \203 from 'FNIG'\n", &flag);
    if (err == 0) {
        if (flag == 0) {
            err = fn_8022C518(0x07000000);
            if (err == 0) {
                err = fn_8022C410(0x04000000);
                if (err == 0) {
                    err = DbNiomReadOnce(0x07000000, 0x03000000);
                    if (err == 0) {
                        err = fn_8022E9E4();
                    }
                }
            }
            id0 = 0;
            id1 = 0;
            if (err == 0 && (err = TDbCompilePerformOp(0, "select 'DIGT' into \202 from 'MTTS' where ('UNLS' = \202)\n", &id0, 0)) == 0
                && (err = TDbCompilePerformOp(0, "select 'DIGT' into \202 from 'MTTS' where ('UNLS' = \202)\n", &id1, 1)) == 0
                && (err = fn_8022DBF4(id0)) == 0 && (err = fn_8022DC38(id1)) == 0) {
                for (i = 0; i <= 13; i++) {
                    TDbCompilePerformOp(0, "select 'DIGP' into \205 from 'YALP' where 'DIOP' = \205 and 'DIGT' = \205\n", &pRecord0[i], pRecord0[i], id0);
                }
                for (i = 0; i <= 13; i++) {
                    TDbCompilePerformOp(0, "select 'DIGP' into \205 from 'YALP' where 'DIOP' = \205 and 'DIGT' = \205\n", &pRecord1[i], pRecord1[i], id1);
                }
                if (err == 0) {
                    err = DbRunUpdateChain(flag, 0, &result, pRecord0, pRecord1);
                }
            }
        }
        if (err == 0) {
            err = TDbCompilePerformOp(0, "update 'NIOM' set 'ASCM' = \202\n", 2);
        }
    }
    return err;
}

int DbManagerMode2Leave(void)
{
    struct QueryCursor cursor;
    int id;
    int err = TDbCompilePerformOp(0, "use 'TATS' declare \212 cursor for select 'DIGT' from 'MAET' where 'PYTT' = \202 or 'PYTT' = \202\n", &cursor, 6, 5);

    if (err == 0) {
        int *pId = &id;
        for (;;) {
            err = TDbCompilePerformOp(0, "fetch from \212 'DIGT' into \205\n", &cursor, pId);
            if (err != 0) {
                break;
            }
            err = TDbCompilePerformOp(0, "use 'TATS' delete from 'YALP' where 'DIGT' = \202\n", id);
            if (err != 0) {
                break;
            }
        }
    }
    if (QUERY_STATUS_ACCEPTED(err) == 1) {
        if (cursor.mUnknown0 != 0) {
            err = TDbSQLDestroyCursor(&cursor);
        } else {
            err = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    if (err == 0) {
        err = TDbCompilePerformOp(0, "use 'TATS' delete from 'MAET' where 'PYTT' = \202 or 'PYTT' = \202\n", 6, 5);
        if (QUERY_STATUS_ACCEPTED(err) == 1) {
            err = 0;
        }
        if (err == 0) {
            err = TDbCompilePerformOp(0, "update 'NIOM' set 'ASPM' = \202 and 'ASCM' = \202\n", 2, 4);
            if (err == 0) {
                DbNiomClearModeFuncs();
            }
        }
    }
    return err;
}

int DbManagerMode2Load(void)
{
    return 0;
}

int DbManagerMode2Save(int a, int b)
{
    int err = TDbCompilePerformOp(0, "update 'NIOM' set 'ASPM' = \202 and 'ASCM' = \202\n", 4, 1);

    if (err == 0) {
        err = TDbCompilePerformOp(0, "update 'FNIG' set 'PNIG' = \203\n", 1);
    }
    if (err == 0) {
        err = DbManagerSaveGameDb(a, b);
    }
    if (err == 0) {
        err = TDbCompilePerformOp(0, "update 'NIOM' set 'ASPM' = \202 and 'ASCM' = \202\n", 1, 2);
    } else {
        TDbCompilePerformOp(0, "update 'NIOM' set 'ASPM' = \202 and 'ASCM' = \202\n", 1, 2);
    }
    if (err == 0) {
        err = TDbCompilePerformOp(0, "update 'FNIG' set 'PNIG' = \203\n", 0);
    } else {
        TDbCompilePerformOp(0, "update 'FNIG' set 'PNIG' = \203\n", 0);
    }
    return err;
}

int DbManagerMode2Finish(void)
{
    int mode;
    int err = TDbCompilePerformOp(0, "select 'RTQG' into \202 from 'FNIG'\n", &mode);

    if (err == 0) {
        if (mode == 6) {
            err = DbRunLoadChain();
        }
        if (err == 0) {
            err = DbResetGameInfo();
            if (err == 0) {
                err = DbManagerMode2Leave();
                if (err == 0) {
                    err = DbManagerEnterMode0();
                }
            }
        }
    }
    return err;
}

int DbManagerMode2Abort(void)
{
    int err = DbManagerMode2Leave();

    if (err == 0) {
        err = DbManagerEnterMode0();
    }
    return err;
}

void DbManagerGetModeFuncs(int mode, DbNiomModeFuncs_t *pFuncs)
{
    switch (mode) {
    case 0:
        *pFuncs = _DbManager_Mode0Funcs;
        break;
    case 1:
        *pFuncs = _DbManager_Mode1Funcs;
        break;
    case 2:
        *pFuncs = _DbManager_Mode2Funcs;
        break;
    }
}

int DbManagerResultAccept(int a, int b, unsigned char *pDone)
{
    *pDone = 1;
    return 0;
}

int DbManagerResultRecord(void)
{
    return 0;
}

int DbManagerResultFinish(void)
{
    return 0;
}

int DbManagerCreateGameDb(Block_80233588 *p)
{
    int err = TDbCreate(0x454D4147, p->mUnknown0);

    if (err != 0) {
        return err;
    }
    err = TDbExtLoadFromResource(0x454D4147, p->mpUnknown4, p->mUnknown8, 3);
    if (err != 0) {
        return err;
    }
    return DbTatsCopyAllTables(0x454D4147, 0x4C424154, 0x534C4654);
}

int DbManagerLoadGameDb(void **ppData, void *p)
{
    int err = TDbLoad(0x454D4147, (int)ppData, 3, (int)p);

    if (err != 0) {
        return err;
    }
    return DbTatsCopyAllTables(0x454D4147, 0x4C424154, 0x534C4654);
}

int DbManagerSaveGameDb(int a, int b)
{
    return TDbSave(0x454D4147, a, b);
}

int DbManagerDestroyGameDb(void)
{
    return TDbDestroy(0x454D4147);
}

int DbManagerInitHook(void)
{
    return 0;
}
