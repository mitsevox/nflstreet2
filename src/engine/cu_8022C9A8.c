/* Partial source for several game-database modules (player lists, depth charts, game info, conference and division lists) not yet cut into their files. */

#include "engine/dbteams.h"
#include "engine/tdbext.h"
#include "engine/dbutil.h"
#include "engine/TDbLoad.h"
#include "engine/cu_80229270.h"

#include "engine/DbNiomModeFuncs.h"
#include "engine/llmemory.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"
#include "engine/t3db.h"
#include "engine/t3db_cols.h"
#include "game/DbUserSetCurrent.h"

#include <string.h>

struct CardStreamTarget;
struct SaveStreamOps_t;
#include "engine/DbUserEntry.h"
extern char lbl_802B5C8C[];
extern char lbl_803A1C60[];
extern float lbl_803A20A4[][13];
extern char *_DbEvas_pFileName;
extern int _DbEvas_iMode;
extern int _DbEvas_iSize;
extern int _DbUser_iSize;
extern char *_DbUser_pFileName;
extern int _DbUser_iMode;
extern int _DbUser_iCurrent;
extern unsigned char _DbUser_iCount;
extern DbUserEntry_t _DbUser_aEntries[];
extern int TDbSave(int handle, int a, int b);
extern int TDbInsertRow(int db, int tbl, TDbCol_801F9718 *pCols, void *pRes, int a);
extern int TDbLoadFromFile(int db, int file, char *pName, int mode, TDbIODevice_t *pDevice);
extern TDbIODevice_t tdbiofioCallback;
extern int TDbTblDestroy(int db, int tbl);
signed char DbUserFindIndex(int key);

extern const unsigned char lbl_802AEF10[];
extern int fn_802297D8(void *p, int tag);
extern int fn_8022D8F8(int a, int *p, int c);
int fn_8022DB20(void);
extern int DbUserFindIdByDb(int key);
extern int DbUserGetCurrent(void);
extern void fn_80231208(void);
int DbUserGetDb(int key);
extern const int _DbUser_aDbIds[2];
extern char lbl_802B5D64[];
extern char lbl_802B5308[];
extern char lbl_802B54DC[];
extern char lbl_802B5500[];
extern char lbl_802B5564[];
extern const float lbl_802B56EC[];
extern const float lbl_802B56F0[];
extern char lbl_802B56F4[];
extern char lbl_802B5994[];
extern char lbl_802B59A8[];
extern char lbl_802B59F0[];
extern char lbl_802B5744[];
extern char lbl_802B4EA0[];
extern char lbl_802B4EC4[];
extern char lbl_802B37E4[];
extern char lbl_802B3824[];
int fn_8022C0E0(struct QueryCursor cursor, int a);
extern int TDbQryGetCount(int ref, unsigned short *pCount);
extern int fn_80230D8C(int id, int a, int b);
extern char lbl_802B3610[];
extern char lbl_802B3698[];
extern char lbl_802B479C[];
extern char lbl_802B4828[];
extern char lbl_802B5CB4[];
extern char lbl_802B5CF0[];
extern int TDbExists(int db);
extern char lbl_802B3888[];
extern char lbl_802B36C4[];
extern int TDbTblExists(int db, int tbl);
extern int TDbTblColEnum(int db, int tbl, TDbColInfo_801F9AB8 *pCols, unsigned int *pCount);
extern int TDbTblColExists(int db, int tbl, int col);
int DbTatsCopyTblDestroy(int db, int tbl);
extern char lbl_802B5A48[];
extern char lbl_802B5AB0[];
extern char lbl_802B5ACC[];
extern char lbl_802B5B34[];
extern char lbl_802B5B64[];
extern char lbl_802B5BDC[];
extern struct QueryCursor lbl_802FA8B0;
extern unsigned short lbl_803EC060;
extern int *lbl_803EC084;
extern unsigned short lbl_803EC088;
extern int (*lbl_803EC08C)[2];
extern unsigned short lbl_803EC090;
extern int (*lbl_803EC094)[3];
extern unsigned short lbl_803EC098;
extern int lbl_802FAA50[][10][2];
int fn_8022E568(void);
int fn_8022E6CC(void);
int fn_8022E834(void);
int fn_8022E9E4(void);
void fn_8022EA4C(void);

typedef struct Record_8022D5A4 {
    unsigned short mUnknown0;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
} Record_8022D5A4;

typedef struct Record_8022D874 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
} Record_8022D874;

extern Record_8022D874 lbl_802FA8C0[];
extern char lbl_802B48C4[];
extern char lbl_802B4A54[];
extern char lbl_802B4A9C[];
extern char lbl_802B4AE0[];
void fn_8022C9B8(void *pPairs);
void DbAssignPendingNodeIds(void);
int fn_8022D5A4(int key, int mode);
int fn_8022D710(int a, int b, int c, int row, int value);
unsigned short fn_8022D6FC(int index);

#include "engine/DbNiomHandlers.h"

typedef struct Object_8022A59C {
    unsigned short mUnknown0;
    int mUnknown4;
} Object_8022A59C;

typedef struct Node_8022CC6C {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    short mUnknown6;
    unsigned short mUnknown8;
    char mUnknown10[2];
    struct Node_8022CC6C *mpUnknown12;
    struct Node_8022CC6C *mpUnknown16;
} Node_8022CC6C;

void fn_8022CAEC(Node_8022CC6C **ppHead);

extern int fn_8022A624(Object_8022A59C *p, struct QueryCursor cursor, int a, int b);
extern int fn_802303B4(int key, unsigned short *pId);
extern int fn_80230CC8(unsigned short id);
extern int DbLockAcquire(void);
extern int DbLockRelease(void);

extern char lbl_802B2138[];
extern char lbl_802B2178[];
extern char lbl_802B21B8[];
extern char lbl_802B21FC[];
extern char lbl_802B2268[];
extern char lbl_802B231C[];
extern char lbl_802B238C[];
extern char lbl_802B2F64[];
extern char lbl_802B3010[];
extern char lbl_802B30D0[];
extern char lbl_802B3180[];
extern char lbl_802B3524[];
extern char lbl_802B35D4[];
extern char lbl_802B35E4[];
extern char lbl_802B35F8[];
extern char lbl_802B45F0[];
extern char lbl_802B4650[];
extern char lbl_802B5080[];
extern char lbl_802B50A0[];
extern char lbl_802B50C0[];
extern char lbl_802B50E0[];
extern char lbl_802B5100[];
extern char lbl_802B5120[];
extern char lbl_802B519C[];
extern char lbl_802B51BC[];
extern int lbl_802FA600[];
extern unsigned short lbl_802FAA1C[];
typedef struct Entry_803A2390 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
} Entry_803A2390;

typedef struct Record_8022A304 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    char mUnknownF[1];
    unsigned short mUnknown10;
    unsigned short mUnknown12;
    unsigned short mUnknown14;
    char mUnknown16[2];
} Record_8022A304;

/* Ends a column list for TDbInsertRow. */
static inline void fn_801F9718_SetEnd(TDbCol_801F9718 *pCol)
{
    pCol->mCol = -1;
    pCol->mUnk4 = -1;
    pCol->mUnk0 = 0;
}

extern Record_8022A304 lbl_802FA180[21];
extern Record_8022A304 lbl_802FA378[17];
extern Record_8022A304 lbl_802FA510[10];

typedef struct Callbacks_8022B02C {
    int (*mpUnknown0)(int a, int b, int c, int d);
    int (*mpUnknown4)(int a);
} Callbacks_8022B02C;

typedef struct Callbacks_8022C214 {
    int (*mpUnknown0)(int a);
    int (*mpUnknown4)(int a);
} Callbacks_8022C214;

extern Entry_803A2390 lbl_803A2390[];
extern char lbl_803A23E8[];
extern char lbl_803A2474[];
extern struct QueryCursor lbl_803A25E0;
extern int (*_DbNiom_pEndFunc)(void);
extern void *_DbNiom_pLoadFunc;
extern void *_DbNiom_pResetFunc;
extern void (*_DbNiom_pCallback)(int);
extern int _DbNiom_iCallbackArg;
extern unsigned char _DbNiom_bModeActive;
extern unsigned char _DbNiom_bEnding;
extern Object_8022A59C *_DbNiom_pCursor;
extern int (*_DbNiom_pModeEnd)(void);
extern int (*_DbNiom_pModeLoad)(void **ppData, void *p);
extern int (*_DbNiom_pModeReset)(int a, int b);
extern int (*_DbNiom_pModeResume)(void);
extern int (*_DbNiom_pModeFn16)(void);
extern int lbl_803EC020[2];
extern int *lbl_803EC010[1];
extern unsigned char lbl_803EC014[1];
extern TDbCol_801F9718 **lbl_803EC018[1];
extern unsigned char *lbl_803EC01C[1];
extern TDbCol_801F9718 *lbl_803EC024[1];
extern unsigned char lbl_803ED01C[1];
extern int fn_802311C8(int a);
extern int (*lbl_803EC028)(int a, int b, int c, int d);
extern int (*lbl_803EC02C)(int a);
extern unsigned char lbl_803EC030;
extern int (*lbl_803EC034)(int a);
extern int (*lbl_803EC038)(int a);
extern int (*lbl_803EC048)(int a);
extern int (*lbl_803EC04C)(int a);
extern Node_8022CC6C *lbl_803EC050;
extern Node_8022CC6C *lbl_803EC054;
extern Node_8022CC6C *lbl_803EC058;
extern Record_8022D5A4 *lbl_803EC05C;
extern unsigned short lbl_803EC060;
extern int lbl_803EC064;
extern int lbl_803EC068;
extern int (*lbl_803EC06C)(int a, int b, unsigned char *pFlag);
extern int (*lbl_803EC070)(int a, int b, int c, int d);
extern int (*lbl_803EC074)(int a, int b, int c, int d);
extern unsigned char lbl_803EC078;
extern int lbl_803EC07C;
extern int lbl_803EC080;

int DbNiomCloseCursor(void);
int fn_8022A59C(int a, Object_8022A59C **ppOut);
int fn_8022AB6C(Object_8022A59C *p, int a, int b);
int fn_8022AC80(Object_8022A59C *p);
int fn_8022BF60(void);
int fn_8022BF68(void);
void DbUtilRandomInit(void);
void DbUtilRandomShutdown(void);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void *fn_8022C9A8(void);
void fn_8022C9B4(void *p);
void fn_8022CADC(void);
Node_8022CC6C *fn_8022CC6C(Node_8022CC6C **ppHead, unsigned char key);
void *fn_8022CD30(void);
void fn_8022CD3C(void *p);
void fn_8022CDA0(void);
int fn_8022D14C(int a);
int fn_8022D250(int (*pCallback)(int a));
int fn_8022D25C(int (*pCallback)(int a));































































































































































/* prototypes of the db functions in 0x80229270-0x8022F428 (dbocmt.c to dbuser.c) */
int DbOcmtRenumber(void);
int DbOcmtModuleInit(void);
void DbOcmtModuleShutdown(void);
int DbOcmtInsert(int a, int b);
int DbOcmtClear(void);
int DbOptionsModuleInit(void);
void DbOptionsModuleShutdown(void);
int DbOptionsSetTpom(int column, int value);
int DbNiomInit(void);
void DbNiomShutdown(void);
void DbNiomSetHandlers(DbNiomHandlers_t *p);
int DbNiomIsModeActive(void);
int DbNiomBeginMode(int *p);
int DbNiomEndMode(void);
int DbNiomRunCallback(void);
int DbNiomOpenCursor(int a);
int DbNiomReadCursor(int a, int b);
int DbNiomCloseCursor(void);
int DbNiomReadOnce(int a, int b);
void DbNiomSetModeFuncs(DbNiomModeFuncs_t *pFuncs);
void DbNiomClearModeFuncs(void);
int DbNiomModeLoad(void **ppData, void *p);
int DbNiomModeReset(int a, int b);
int DbNiomModeResume(void);
int fn_802299FC(void);
int fn_80229A70(void);
float fn_80229C98(int index);
float fn_80229CB0(int index);
float fn_80229CC4(int index, int item);
float fn_80229CE4(int index);
int fn_80229E78(int a, int b, int c, int d);
int fn_80229E80(int a, int b, int c, int d);
void fn_8022A304(void);
int fn_8022A428(int a);
int fn_8022A490(unsigned int count);
int fn_8022A508(int a, int b, int c, int d, int e);
int fn_8022A558(int a, int b, int c, int d);
int fn_8022A59C(int a, Object_8022A59C **ppOut);
int fn_8022AB6C(Object_8022A59C *p, int a, int b);
int fn_8022AC80(Object_8022A59C *p);
int fn_8022ACEC(int key, int unused, int col, int value, int index);
int fn_8022AD64(int db, TDbCol_801F9718 **ppCols, unsigned char *pCount);
int fn_8022AEFC(unsigned int value);
int fn_8022AF54(int a, int b);
int fn_8022AF5C(int key, int unused, int col, int value, int set, int index);
int fn_8022B02C(Callbacks_8022B02C *pCallbacks);
void fn_8022B200(void);
int fn_8022BF60(void);
int fn_8022BF68(void);
int fn_8022C02C(int a, int b, int c, int d);
int fn_8022C098(int a, int b, int c, int d);
int fn_8022C0E0(struct QueryCursor cursor, int a);
int fn_8022C214(Callbacks_8022C214 *pCallbacks);
void fn_8022C3C8(void);
int fn_8022C410(int a);
int fn_8022C518(int a);
int fn_8022C628(int db, int tbl, int *pIds, unsigned short *pCount);
int fn_8022C81C(int a, int b, int c, int d);
int fn_8022C858(int a, int b, int c, int d);
void DbUtilRandomInit(void);
void DbUtilRandomShutdown(void);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void DbUtilSetHeap(int a);
void *DbUtilAlloc(int size, int a);
void DbUtilFree(void *p);
void *fn_8022C9A8(void);
void fn_8022C9B4(void *p);
void fn_8022C9B8(void *pPairs);
void fn_8022CADC(void);
void fn_8022CAEC(Node_8022CC6C **ppHead);
Node_8022CC6C *fn_8022CC6C(Node_8022CC6C **ppHead, unsigned char key);
Node_8022CC6C *fn_8022CC98(Node_8022CC6C **ppHead, unsigned short key);
void fn_8022CCC4(Node_8022CC6C **ppHead, Node_8022CC6C *p);
void fn_8022CD0C(Node_8022CC6C **ppHead, Node_8022CC6C *p);
void *fn_8022CD30(void);
void fn_8022CD3C(void *p);
int fn_8022CD40(int a, int b, int c);
void fn_8022CDA0(void);
void fn_8022CDF8(void);
int fn_8022D14C(int a);
int fn_8022D154(void);
int fn_8022D1B8(void);
int fn_8022D23C(void);
int fn_8022D250(int (*pCallback)(int a));
int fn_8022D25C(int (*pCallback)(int a));
int fn_8022D268(int a, int b, int c, void *pPairs, int action, int mode);
int fn_8022D2F4(int a, int b, int c, void *pPairs, int mode);
int fn_8022D3AC(void);
unsigned short fn_8022D3D4(unsigned char key);
int fn_8022D418(int a, int b, int mode);
int fn_8022D540(void);
int fn_8022D5A4(int key, int mode);
int fn_8022D6E8(void);
void fn_8022D6F0(void);
unsigned short fn_8022D6FC(int index);
int fn_8022D710(int a, int b, int c, int row, int value);
int DbTableLookupByte(int row, int column);
int fn_8022D864(int a, int b, int c, int d);
int fn_8022D86C(int a, int b, int c, int d);
int fn_8022D874(int a, int b, int c, int key);
int fn_8022D8F8(int a, int *p, int tag);
int fn_8022DA44(int a, int *b, int c, int *d, int e);
int fn_8022DA90(void **p);
void fn_8022DB08(void);
int fn_8022DB20(void);
int fn_8022DBF4(int value);
int fn_8022DC38(int value);
int fn_8022DC7C(int value);
int fn_8022DCB0(int value);
int fn_8022DCE4(int value);
int fn_8022DD18(int value);
int fn_8022DD4C(int value);
int fn_8022DD80(int value);
int fn_8022DDB4(int a, void *p);
int DbUpdateSettingsRecord(int a, int *pOutA, int *pOutB);
int fn_8022E21C(int a, int b);
int DbRunUpdateChain(int a, int b, unsigned char *pDone, int *pC, int *pD);
int DbRunLoadChain(void);
int fn_8022E558(void);
int fn_8022E560(void);
int fn_8022E568(void);
void fn_8022E694(void);
int fn_8022E6CC(void);
void fn_8022E7FC(void);
int fn_8022E834(void);
void fn_8022E96C(void);
int fn_8022E9A4(void);
void fn_8022E9C4(void);
int fn_8022E9E4(void);
void fn_8022EA4C(void);
int DbEvasModuleInit(void);
void DbEvasModuleShutdown(void);
int DbEvasInit(int a, const char *pName, int b);
void DbEvasShutdown(void);
int DbEvasLoad(void);
int DbEvasLoadStream(struct CardStreamTarget *pTarget, struct SaveStreamOps_t *pOps);
int DbEvasSaveStream(void *pTarget, struct SaveStreamOps_t *pOps);
int DbEvasUnload(void);
int DbTatsCopyInit(int a, const char *pName, int b);
void DbTatsCopyShutdown(void);
int DbTatsCopyOpen(void);
int DbTatsCopyClose(void);
int DbTatsCopyTable(int a, int b);
int DbTatsCopyTblDestroy(int db, int tbl);
int DbTatsCopyAllTables(int db, int a, int b);
int DbFileInit(const char *pName);
void DbFileShutdown(void);
int DbFileTblLoad(int db, int file);
int DbFileTblDestroy(int db, int tbl);
int DbUserNewId(void);
int DbUserInit(int a, const char *pName, int b);
void DbUserShutdown(void);
int DbUserCreate(void);
void DbUserDelete(int key);
void DbUserReset(int key);
int DbUserGetCount(void);
int DbUserGetId(int index);
signed char DbUserFindIndex(int key);
int DbUserGetDb(int key);

void *fn_8022C9A8(void)
{
    return lbl_803A23E8;
}

void fn_8022C9B4(void *p)
{
}

void fn_8022C9B8(void *pPairs)
{
    unsigned char (*pValues)[2] = pPairs;
    unsigned char i;
    for (i = 0; i <= 6; i++) {
        if (pValues[i][0] > 25) {
            pValues[i][0] = 2;
        }
        lbl_803EC050[i].mUnknown0 = pValues[i][1];
        lbl_803EC050[i].mUnknown1 = pValues[i][0];
        lbl_803EC050[i].mUnknown2 = i;
        lbl_803EC050[i].mUnknown3 = pValues[i][1];
        lbl_803EC050[i].mUnknown4 = pValues[i][0];
        lbl_803EC050[i].mUnknown5 = 0;
        lbl_803EC050[i].mUnknown6 = 0;
        lbl_803EC050[i].mUnknown8 = 32767;
        if (i != 0) {
            lbl_803EC050[i].mpUnknown12 = &lbl_803EC050[i - 1];
        } else {
            lbl_803EC050[i].mpUnknown12 = 0;
        }
        if (i != 6) {
            lbl_803EC050[i].mpUnknown16 = &lbl_803EC050[i + 1];
        } else {
            lbl_803EC050[i].mpUnknown16 = 0;
        }
    }
    lbl_803EC058 = 0;
    lbl_803EC054 = lbl_803EC050;
    fn_8022CAEC(&lbl_803EC054);
}

void fn_8022CADC(void)
{
    lbl_803EC054 = 0;
    lbl_803EC058 = 0;
}

void fn_8022CAEC(Node_8022CC6C **ppHead)
{
    Node_8022CC6C *pA;
    Node_8022CC6C *pB;
    Node_8022CC6C *pTmp;
    int swapped;
    int diff;
    int remA;
    int remB;

    if ((*ppHead)->mpUnknown16 == 0) {
        return;
    }
    do {
        pA = *ppHead;
        swapped = 0;
        for (pB = pA->mpUnknown16; pB != 0; pB = pB->mpUnknown16, pA = pA->mpUnknown16) {
            if (pB->mUnknown6 != pA->mUnknown6) {
                diff = pB->mUnknown6 - pA->mUnknown6;
            } else if (pB->mUnknown0 >= pB->mUnknown3 && pA->mUnknown0 >= pA->mUnknown3) {
                if (pB->mUnknown0 != pA->mUnknown0) {
                    diff = pB->mUnknown0 - pA->mUnknown0;
                } else if (pA->mUnknown4 >= 21 && pA->mUnknown4 <= 25) {
                    if (pB->mUnknown4 >= 21 && pB->mUnknown4 <= 25) {
                        diff = pB->mUnknown2 - pA->mUnknown2;
                    } else {
                        diff = 1;
                    }
                } else if (pB->mUnknown4 >= 21 && pB->mUnknown4 <= 25) {
                    diff = -1;
                } else {
                    diff = pB->mUnknown2 - pA->mUnknown2;
                }
            } else {
                remB = pB->mUnknown0 - pB->mUnknown3;
                remA = pA->mUnknown0 - pA->mUnknown3;
                if (remB == remA) {
                    if (pB->mUnknown0 != pA->mUnknown0) {
                        diff = pB->mUnknown0 - pA->mUnknown0;
                    } else {
                        diff = pB->mUnknown2 - pA->mUnknown2;
                    }
                } else {
                    diff = (remB > remA) ? -1 : 1;
                }
            }
            if (diff < 0) {
                if (pB->mpUnknown12 != 0) {
                    pB->mpUnknown12->mpUnknown16 = pB->mpUnknown16;
                }
                if (pB->mpUnknown16 != 0) {
                    pB->mpUnknown16->mpUnknown12 = pB->mpUnknown12;
                }
                if (pA->mpUnknown12 != 0) {
                    pA->mpUnknown12->mpUnknown16 = pB;
                } else {
                    *ppHead = pB;
                }
                pB->mpUnknown12 = pA->mpUnknown12;
                pA->mpUnknown12 = pB;
                pB->mpUnknown16 = pA;
                swapped = 1;
                pTmp = pA;
                pA = pB;
                pB = pTmp;
            }
        }
    } while (swapped == 1);
}

Node_8022CC6C *fn_8022CC6C(Node_8022CC6C **ppHead, unsigned char key)
{
    Node_8022CC6C *p;

    for (p = *ppHead; p != 0; p = p->mpUnknown16) {
        if (p->mUnknown2 == key) {
            return p;
        }
    }
    return 0;
}

Node_8022CC6C *fn_8022CC98(Node_8022CC6C **ppHead, unsigned short key)
{
    Node_8022CC6C *p;

    for (p = *ppHead; p != 0; p = p->mpUnknown16) {
        if (p->mUnknown8 == key) {
            return p;
        }
    }
    return 0;
}

void fn_8022CCC4(Node_8022CC6C **ppHead, Node_8022CC6C *p)
{
    if (*ppHead == p) {
        *ppHead = p->mpUnknown16;
    }
    if (p->mpUnknown12 != 0) {
        p->mpUnknown12->mpUnknown16 = p->mpUnknown16;
    }
    if (p->mpUnknown16 != 0) {
        p->mpUnknown16->mpUnknown12 = p->mpUnknown12;
    }
    p->mpUnknown12 = p;
    p->mpUnknown16 = p;
}

void fn_8022CD0C(Node_8022CC6C **ppHead, Node_8022CC6C *p)
{
    p->mpUnknown12 = 0;
    p->mpUnknown16 = *ppHead;
    if (p->mpUnknown16 != 0) {
        p->mpUnknown16->mpUnknown12 = p;
    }
    *ppHead = p;
}

void *fn_8022CD30(void)
{
    return lbl_803A2474;
}

void fn_8022CD3C(void *p)
{
}

int fn_8022CD40(int a, int b, int c)
{
    lbl_803A25E0.mUnknown0 = 0;
    lbl_803A25E0.mUnknown4 = 0;
    lbl_803A25E0.mUnknown8 = -1;
    lbl_803A25E0.mUnknown12 = 0;
    return TDbCompilePerformOp(0, lbl_802B45F0, &lbl_803A25E0, a, c, b);
}

void fn_8022CDA0(void)
{
    if (lbl_803A25E0.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&lbl_803A25E0);
        lbl_803A25E0.mUnknown0 = 0;
        lbl_803A25E0.mUnknown4 = 0;
        lbl_803A25E0.mUnknown8 = -1;
        lbl_803A25E0.mUnknown12 = 0;
    }
}

void fn_8022CDF8(void)
{
    int value;
    unsigned char key;
    int err;
    int resultA;
    int resultB;
    Node_8022CC6C *p;

    do {
        err = TDbCompilePerformOp(0, lbl_802B4650, &lbl_803A25E0, &value, &key);
        if (err != 0) {
            break;
        }
        resultA = 0;
        resultB = 0;
        if (lbl_803EC048 != 0) {
            resultA = lbl_803EC048(value);
        }
        if (lbl_803EC04C != 0) {
            resultB = lbl_803EC04C(value);
        }
        if (resultA == 0 && resultB == 0) {
            p = fn_8022CC6C(&lbl_803EC054, key);
            if (p != 0) {
                fn_8022CCC4(&lbl_803EC054, p);
                p->mUnknown8 = value;
                fn_8022CD0C(&lbl_803EC058, p);
            }
        }
    } while (err == 0);
}

void DbAssignPendingNodeIds(void)
{
    Node_8022CC6C *p;
    int found;
    unsigned short i;
    int resultA;
    int resultB;
    int done;
    unsigned short count;
    int next;

    while (lbl_803EC054 != 0) {
        p = lbl_803EC054;
        found = 0;
        for (i = 0; i < lbl_803EC060 && found == 0; i++) {
            if (p->mUnknown1 == lbl_803EC05C[i].mUnknown2 || p->mUnknown5 != 0) {
                if (p->mUnknown0 == lbl_803EC05C[i].mUnknown3 || p->mUnknown5 != 0) {
                    resultA = 0;
                    resultB = 0;
                    if (lbl_803EC048 != 0 && p->mUnknown5 != 3) {
                        resultA = lbl_803EC048(lbl_803EC05C[i].mUnknown0);
                    }
                    if (lbl_803EC04C != 0 && p->mUnknown5 != 2) {
                        resultB = lbl_803EC04C(lbl_803EC05C[i].mUnknown0);
                    }
                    if (fn_8022CC98(&lbl_803EC058, lbl_803EC05C[i].mUnknown0) == 0 && resultA == 0
                        && resultB == 0) {
                        fn_8022CCC4(&lbl_803EC054, p);
                        found = 1;
                        p->mUnknown8 = lbl_803EC05C[i].mUnknown0;
                        fn_8022CD0C(&lbl_803EC058, p);
                    }
                }
            }
        }
        if (found == 0) {
            done = 0;
            count = fn_8022D6FC(p->mUnknown1);
            if (p->mUnknown0 < p->mUnknown3) {
                if (p->mUnknown0 != 0) {
                    p->mUnknown0--;
                    fn_8022CAEC(&lbl_803EC054);
                } else {
                    done = 1;
                }
            } else {
                p->mUnknown0++;
                if (p->mUnknown0 >= count) {
                    if (p->mUnknown3 != 0) {
                        p->mUnknown0 = p->mUnknown3 - 1;
                    } else {
                        done = 1;
                    }
                }
                fn_8022CAEC(&lbl_803EC054);
            }
            if (done == 1) {
                p->mUnknown6++;
                next = DbTableLookupByte(p->mUnknown4, p->mUnknown6);
                if (next == 31) {
                    if (p->mUnknown3 != 0) {
                        p->mUnknown0 = p->mUnknown3 - 1;
                        p->mUnknown1 = p->mUnknown4;
                        p->mUnknown6 = 0;
                        p->mUnknown3--;
                    } else if (p->mUnknown5 == 0) {
                        p->mUnknown5 = done;
                    } else if (p->mUnknown5 == 1) {
                        p->mUnknown5 = 2;
                    } else {
                        return;
                    }
                } else {
                    p->mUnknown1 = next;
                    p->mUnknown0 = p->mUnknown3;
                    fn_8022CAEC(&lbl_803EC054);
                }
            }
        }
    }
}

int fn_8022D14C(int a)
{
    return 0;
}

int fn_8022D154(void)
{
    lbl_803EC050 = fn_8022C9A8();
    lbl_803EC05C = fn_8022CD30();
    lbl_803A25E0.mUnknown0 = 0;
    lbl_803A25E0.mUnknown4 = 0;
    lbl_803A25E0.mUnknown8 = -1;
    lbl_803A25E0.mUnknown12 = 0;
    fn_8022D250(fn_8022D14C);
    fn_8022D25C(0);
    return 0;
}

int fn_8022D1B8(void)
{
    if (lbl_803EC050 != 0) {
        fn_8022C9B4(lbl_803EC050);
        lbl_803EC050 = 0;
    }
    if (lbl_803EC05C != 0) {
        fn_8022CD3C(lbl_803EC05C);
        lbl_803EC05C = 0;
        lbl_803EC060 = 0;
    }
    fn_8022D250(0);
    fn_8022D25C(0);
    lbl_803A25E0.mUnknown0 = 0;
    lbl_803A25E0.mUnknown4 = 0;
    lbl_803A25E0.mUnknown8 = -1;
    lbl_803A25E0.mUnknown12 = 0;
    return 0;
}

int fn_8022D23C(void)
{
    lbl_803EC048 = fn_8022D14C;
    return 0;
}

int fn_8022D250(int (*pCallback)(int a))
{
    lbl_803EC048 = pCallback;
    return 0;
}

int fn_8022D25C(int (*pCallback)(int a))
{
    lbl_803EC04C = pCallback;
    return 0;
}

int fn_8022D268(int a, int b, int c, void *pPairs, int action, int mode)
{
    switch (action) {
    case 0:
        fn_8022C9B8(pPairs);
        break;
    case 1:
        fn_8022D5A4(a, mode);
        break;
    case 2:
        fn_8022CD40(a, b, c);
        break;
    case 3:
        fn_8022CDF8();
        break;
    case 4:
        DbAssignPendingNodeIds();
        break;
    }
    return 0;
}

int fn_8022D2F4(int a, int b, int c, void *pPairs, int mode)
{
    fn_8022D268(a, b, c, pPairs, 0, mode);
    fn_8022D268(a, b, c, pPairs, 1, mode);
    fn_8022D268(a, b, c, pPairs, 2, mode);
    fn_8022D268(a, b, c, pPairs, 3, mode);
    fn_8022D268(a, b, c, pPairs, 4, mode);
    return 0;
}

int fn_8022D3AC(void)
{
    fn_8022CADC();
    fn_8022CDA0();
    return 0;
}

unsigned short fn_8022D3D4(unsigned char key)
{
    unsigned short value = 32767;
    Node_8022CC6C *p = fn_8022CC6C(&lbl_803EC058, key);

    if (p != 0) {
        value = p->mUnknown8;
    }
    return value;
}

int fn_8022D418(int a, int b, int mode)
{
    int tblA;
    int tblB;
    int status;

    if (mode == 1) {
        tblA = 0x41474C50;
        tblB = 0x41474344;
    } else {
        tblA = 0x59414C50;
        tblB = 0x54484344;
    }
    lbl_802FA8B0.mUnknown0 = 0;
    lbl_802FA8B0.mUnknown4 = 0;
    lbl_802FA8B0.mUnknown8 = -1;
    lbl_802FA8B0.mUnknown12 = 0;
    if (a != 1023 && b != 1023) {
        status = TDbCompilePerformOp(0, lbl_802B479C, &lbl_802FA8B0, tblA, tblB, tblB, tblA, tblA, 0, tblB, tblB);
    } else {
        status = TDbCompilePerformOp(0, lbl_802B4828, &lbl_802FA8B0, tblA, tblB, tblB, tblA, tblA, (a != 1023) ? a : b,
                             tblA, 0, tblB, tblB);
    }
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        status = 0;
    }
    return status;
}

int fn_8022D540(void)
{
    int result;
    if (lbl_802FA8B0.mUnknown0 != 0) {
        result = TDbSQLDestroyCursor(&lbl_802FA8B0);
    } else {
        result = 0;
    }
    if (result == 0) {
        lbl_802FA8B0.mUnknown0 = 0;
        lbl_802FA8B0.mUnknown4 = 0;
        lbl_802FA8B0.mUnknown8 = -1;
        lbl_802FA8B0.mUnknown12 = 0;
        lbl_803EC060 = 0;
    }
    return result;
}

int fn_8022D5A4(int key, int mode)
{
    int tag = 0x54484344;
    int a, b, c, d;
    int result;
    unsigned int count = 0;
    if (mode == 1) {
        tag = 0x41474344;
    }
    lbl_802FA8B0.mUnknown4 = 0;
    do {
        result = TDbCompilePerformOp(0, lbl_802B48C4, &lbl_802FA8B0, tag, &a, tag, &b, tag, &c, tag, &d);
        if (result == 0) {
            if (a == key && (unsigned int)d < fn_8022D6FC(c) && count <= 90) {
                lbl_803EC05C[count].mUnknown0 = b;
                lbl_803EC05C[count].mUnknown2 = c;
                lbl_803EC05C[count].mUnknown3 = d;
                count++;
            }
        }
    } while (result == 0);
    if (QUERY_STATUS_ACCEPTED(result) == 1) {
        lbl_803EC060 = count;
        result = 0;
    }
    return result;
}

int fn_8022D6E8(void)
{
    return 0;
}

void fn_8022D6F0(void)
{
    lbl_803EC064 = 0;
}

unsigned short fn_8022D6FC(int index)
{
    return lbl_802FAA1C[index];
}

int fn_8022D710(int a, int b, int c, int row, int value)
{
    unsigned char found;
    int result = 0;
    if (value == 31) {
        result = TDbCompilePerformOp(0, lbl_802B4A54, &found, a, b, row);
        if (QUERY_STATUS_ACCEPTED(result) == 1) {
            if (result == 0) {
                value = found + 1;
            } else {
                value = 0;
            }
            result = 0;
        }
    }
    if (result == 0 && (unsigned int)value < lbl_802FAA1C[row]) {
        result = TDbCompilePerformOp(0, lbl_802B4A9C, a, b, row, value);
        if (result == 0) {
            result = TDbCompilePerformOp(0, lbl_802B4AE0, a, b, c, row, value);
        }
    }
    return result;
}

int DbTableLookupByte(int row, int column)
{
    if ((unsigned short)column > 9) {
        return 31;
    }
    return lbl_802FAA50[row][column][0];
}

int fn_8022D864(int a, int b, int c, int d)
{
    return 0;
}

int fn_8022D86C(int a, int b, int c, int d)
{
    return 0;
}

int fn_8022D874(int a, int b, int c, int key)
{
    unsigned char i = 0;
    int value;
    int result = 0;
    do {
        value = lbl_802FA8C0[i].mUnknown0;
        if (value == key) {
            result = fn_8022D710(a, b, c, lbl_802FA8C0[i].mUnknown4, lbl_802FA8C0[i].mUnknown8);
        }
        i++;
    } while (value != 14);
    return result;
}

int fn_8022D8F8(int a, int *p, int tag)
{
    fn_8022D874(tag, a, p[0], 0);
    fn_8022D874(tag, a, p[1], 1);
    fn_8022D874(tag, a, p[2], 2);
    fn_8022D874(tag, a, p[3], 3);
    fn_8022D874(tag, a, p[4], 4);
    fn_8022D874(tag, a, p[5], 5);
    fn_8022D874(tag, a, p[6], 6);
    fn_8022D874(tag, a, p[7], 7);
    fn_8022D874(tag, a, p[8], 8);
    fn_8022D874(tag, a, p[9], 9);
    fn_8022D874(tag, a, p[10], 10);
    fn_8022D874(tag, a, p[11], 11);
    fn_8022D874(tag, a, p[12], 12);
    fn_8022D874(tag, a, p[13], 13);
    return 0;
}

int fn_8022DA44(int a, int *b, int c, int *d, int e)
{
    fn_8022D8F8(a, b, e);
    fn_8022D8F8(c, d, e);
    return 0;
}

int fn_8022DA90(void **p)
{
    unsigned char found;
    int result = TDbCompilePerformOp(0, lbl_802B4EA0, &found);
    if (found == 0) {
        result = fn_8022DB20();
    }
    if (result == 0 && p != 0) {
        lbl_803EC06C = p[0];
        lbl_803EC070 = p[1];
        lbl_803EC074 = p[2];
    }
    return result;
}

void fn_8022DB08(void)
{
    lbl_803EC068 = 0;
    lbl_803EC06C = 0;
    lbl_803EC070 = 0;
    lbl_803EC074 = 0;
}

int fn_8022DB20(void)
{
    int result;

    result = TDbCompilePerformOp(0, lbl_802B4EC4, 999.99f, 999.99f, 15, 2047, 15, 127, 127, 127, -1, 1023, 63, 63, 4, 3,
                         255, 1023, 63, 63, 4, 3, 255, 1023, -1, 15, 1023, 15, 0, 0);
    lbl_803EC07C = 1023;
    lbl_803EC080 = 1023;
    return result;
}

int fn_8022DBF4(int value)
{
    int err = TDbCompilePerformOp(0, lbl_802B5080, value);

    lbl_803EC07C = value;
    return err;
}

int fn_8022DC38(int value)
{
    int err = TDbCompilePerformOp(0, lbl_802B50A0, value);

    lbl_803EC080 = value;
    return err;
}

int fn_8022DC7C(int value)
{
    return TDbCompilePerformOp(0, lbl_802B50C0, value);
}

int fn_8022DCB0(int value)
{
    return TDbCompilePerformOp(0, lbl_802B50E0, value);
}

int fn_8022DCE4(int value)
{
    return TDbCompilePerformOp(0, lbl_802B5100, value);
}

int fn_8022DD18(int value)
{
    return TDbCompilePerformOp(0, lbl_802B5120, value);
}

int fn_8022DD4C(int value)
{
    return TDbCompilePerformOp(0, lbl_802B519C, value);
}

int fn_8022DD80(int value)
{
    return TDbCompilePerformOp(0, lbl_802B51BC, value);
}

int fn_8022DDB4(int a, void *p)
{
    return 0;
}

typedef struct Record_8022DDBC {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown2C;
    int mUnknown30;
    int mUnknown34;
    int mUnknown38;
    int mUnknown3C;
    int mUnknown40;
    int mUnknown44;
    int mUnknown48;
    int mUnknown4C;
    int mUnknown50;
    int mUnknown54;
    int mUnknown58;
    int mUnknown5C;
    int mUnknown60;
    float mUnknown64;
    int mUnknown68;
    int mUnknown6C;
} Record_8022DDBC;

int DbUpdateSettingsRecord(int a, int *pOutA, int *pOutB)
{
    Record_8022DDBC rec;
    int v200;
    int v204;
    int err;

    *pOutA = 1023;
    *pOutB = 1023;
    err = TDbCompilePerformOp(0, lbl_802B5308, &rec.mUnknown64, &rec.mUnknown0, &rec.mUnknown4, &rec.mUnknown8, &rec.mUnknownC, &rec.mUnknown10, &rec.mUnknown14, &rec.mUnknown18, &rec.mUnknown1C, &rec.mUnknown20, &rec.mUnknown24,
                      &rec.mUnknown28, &rec.mUnknown2C, &rec.mUnknown30, &rec.mUnknown34, &rec.mUnknown38, &rec.mUnknown3C, &rec.mUnknown40, &rec.mUnknown44, &rec.mUnknown48, &rec.mUnknown50, &rec.mUnknown54, &rec.mUnknown58, &rec.mUnknown5C,
                      &rec.mUnknown68);
    rec.mUnknown0 = a;
    if (err == 0) {
        if (a == 0) {
            if (rec.mUnknown4 == 2047) {
                rec.mUnknown4 = 780;
            }
            if (rec.mUnknown8 == 15) {
                rec.mUnknown8 = 0;
            }
            if (rec.mUnknownC == 127) {
                rec.mUnknownC = 0;
            }
            if (rec.mUnknown10 == 127) {
                rec.mUnknown10 = 78;
            }
            if (rec.mUnknown14 == 127) {
                rec.mUnknown14 = 0;
            }
            if (rec.mUnknown18 == -1) {
                rec.mUnknown18 = 0x1680000;
            }
            if (rec.mUnknown28 == 4) {
                rec.mUnknown28 = 3;
            }
            if (rec.mUnknown40 == 4) {
                rec.mUnknown40 = 3;
            }
            if (rec.mUnknown2C == 3) {
                rec.mUnknown2C = 2;
            }
            if (rec.mUnknown44 == 3) {
                rec.mUnknown44 = 2;
            }
            if (err == 0) {
                if (rec.mUnknown30 == 255) {
                    rec.mUnknown30 = 0;
                }
                if (rec.mUnknown48 == 255) {
                    rec.mUnknown48 = 0;
                }
                if (rec.mUnknown50 == -1) {
                    rec.mUnknown50 = 0;
                }
                if (rec.mUnknown54 == 15) {
                    rec.mUnknown54 = 0;
                }
                if (rec.mUnknown54 == 1023) {
                    err = TDbCompilePerformOp(0, lbl_802B54DC, &rec.mUnknown54);
                }
                if (err == 0) {
                    if (rec.mUnknown5C == 15) {
                        rec.mUnknown5C = 0;
                    }
                    if (rec.mUnknown64 == lbl_802B56EC[0]) {
                        rec.mUnknown64 = lbl_802B56F0[0];
                    }
                    if (rec.mUnknown68 == 255) {
                        rec.mUnknown68 = 0;
                    }
                }
            }
        }
        if (err == 0) {
            if (rec.mUnknown20 == 63 || rec.mUnknown24 == 63) {
                err = TDbCompilePerformOp(0, lbl_802B5500, &v200, &v204, rec.mUnknown1C);
                if (err == 0) {
                    if (rec.mUnknown20 == 63) {
                        rec.mUnknown20 = v200;
                    }
                    if (rec.mUnknown24 == 63) {
                        rec.mUnknown24 = v204;
                    }
                }
            }
            if (err == 0) {
                if (rec.mUnknown38 == 63 || rec.mUnknown3C == 63) {
                    err = TDbCompilePerformOp(0, lbl_802B5500, &v200, &v204, rec.mUnknown34);
                    if (err == 0) {
                        if (rec.mUnknown38 == 63) {
                            rec.mUnknown38 = v200;
                        }
                        if (rec.mUnknown3C == 63) {
                            rec.mUnknown3C = v204;
                        }
                    }
                }
                if (err == 0) {
                    err = TDbCompilePerformOp(0, lbl_802B5564, rec.mUnknown64, rec.mUnknown0, rec.mUnknown4, rec.mUnknown8, rec.mUnknownC, rec.mUnknown10, rec.mUnknown14, rec.mUnknown18, rec.mUnknown1C, rec.mUnknown20,
                                      rec.mUnknown24, rec.mUnknown28, rec.mUnknown2C, rec.mUnknown30, rec.mUnknown34, rec.mUnknown38, rec.mUnknown3C, rec.mUnknown40, rec.mUnknown44, rec.mUnknown48, rec.mUnknown50, rec.mUnknown54,
                                      rec.mUnknown58, rec.mUnknown5C, rec.mUnknown68);
                    lbl_803EC07C = rec.mUnknown1C;
                    lbl_803EC080 = rec.mUnknown34;
                    if (err == 0) {
                        if (pOutA != 0) {
                            *pOutA = rec.mUnknown1C;
                        }
                        if (pOutB != 0) {
                            *pOutB = rec.mUnknown34;
                        }
                    }
                }
            }
        }
    }
    return err;
}

int fn_8022E21C(int a, int b)
{
    if (a != 1023 && b != 1023) {
        return TDbCompilePerformOp(0, lbl_802B56F4, a, b);
    } else {
        int value = b;
        if (a != 1023) {
            value = a;
        }
        return TDbCompilePerformOp(0, lbl_802B5744, value);
    }
}

int DbRunUpdateChain(int a, int b, unsigned char *pDone, int *pC, int *pD)
{
    int keyA;
    int keyB;
    unsigned char flag;
    int err;

    keyA = 0;
    keyB = 0;
    err = 0;
    flag = 1;
    if (a == 0) {
        err = DbUpdateSettingsRecord(b, &keyA, &keyB);
        if (err == 0 && lbl_803EC078 == 1 && lbl_803EC06C != 0) {
            err = lbl_803EC06C(keyA, keyB, &flag);
        }
        if (err == 0 && flag == 1) {
            err = TDbCompilePerformOp(0, lbl_802B5994);
            if (err == 0) {
                err = TDbCompilePerformOp(0, lbl_802B59A8);
                if (err == 0) {
                    err = fn_8022E21C(keyA, keyB);
                }
            }
            fn_8022DA44(keyA, pC, keyB, pD, 0x41474344);
            lbl_803EC078 = 1;
        }
        if (err != 0) {
            flag = 0;
        }
    }
    if (err == 0 && flag == 1) {
        if (lbl_803EC070 != 0) {
            err = lbl_803EC070(keyA, keyB, a, b);
        }
        if (err == 0) {
            err = fn_8022C02C(keyA, keyB, a, b);
            if (err == 0) {
                err = fn_80229E78(keyA, keyB, a, b);
                if (err == 0) {
                    err = fn_8022C81C(keyA, keyB, a, b);
                    if (err == 0) {
                        err = fn_8022D864(keyA, keyB, a, b);
                    }
                }
            }
        }
    }
    *pDone = (err == 0) ? flag : 0;
    return err;
}

int DbRunLoadChain(void)
{
    int a;
    int b;
    int c;
    int d;
    int err;

    err = TDbCompilePerformOp(0, lbl_802B59F0, &a, &b, &c, &d);
    if (lbl_803EC074 != 0) {
        err = lbl_803EC074(a, b, c, d);
    }
    if (err == 0) {
        err = fn_8022D86C(a, b, c, d);
        if (err == 0) {
            err = fn_8022C858(a, b, c, d);
            if (err == 0) {
                err = fn_80229E80(a, b, c, d);
                if (err == 0) {
                    err = fn_8022C098(a, b, c, d);
                }
            }
        }
    }
    return err;
}

int fn_8022E558(void)
{
    return lbl_803EC07C;
}

int fn_8022E560(void)
{
    return lbl_803EC080;
}

int fn_8022E568(void)
{
    struct QueryCursor cursor;
    struct QueryResult result;
    unsigned short i;
    int status;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(&result, lbl_802B5A48, &cursor, 0, 1);
    lbl_803EC088 = result.mUnknown0;
    if (status == 0 && lbl_803EC088 != 0) {
        lbl_803EC084 = DbUtilAlloc(lbl_803EC088 * 4, 1);
        i = 0;
        do {
            status = TDbCompilePerformOp(0, lbl_802B5AB0, &cursor, &lbl_803EC084[i]);
            i++;
        } while (status == 0);
    }
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        if (cursor.mUnknown0 != 0) {
            status = TDbSQLDestroyCursor(&cursor);
        } else {
            status = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return status;
}

void fn_8022E694(void)
{
    if (lbl_803EC084 != 0) {
        DbUtilFree(lbl_803EC084);
        lbl_803EC084 = 0;
        lbl_803EC088 = 0;
    }
}

int fn_8022E6CC(void)
{
    struct QueryCursor cursor;
    struct QueryResult result;
    unsigned short i;
    int status;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(&result, lbl_802B5ACC, &cursor, 0, 7);
    lbl_803EC090 = result.mUnknown0;
    if (status == 0 && lbl_803EC090 != 0) {
        lbl_803EC08C = DbUtilAlloc(lbl_803EC090 * 8, 1);
        i = 0;
        do {
            status = TDbCompilePerformOp(0, lbl_802B5B34, &cursor, &lbl_803EC08C[i][0], &lbl_803EC08C[i][1]);
            i++;
        } while (status == 0);
    }
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        if (cursor.mUnknown0 != 0) {
            status = TDbSQLDestroyCursor(&cursor);
        } else {
            status = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return status;
}

void fn_8022E7FC(void)
{
    if (lbl_803EC08C != 0) {
        DbUtilFree(lbl_803EC08C);
        lbl_803EC08C = 0;
        lbl_803EC090 = 0;
    }
}

int fn_8022E834(void)
{
    struct QueryCursor cursor;
    struct QueryResult result;
    unsigned short i;
    int status;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(&result, lbl_802B5B64, &cursor, 0, 8, 1);
    lbl_803EC098 = result.mUnknown0;
    if (status == 0 && lbl_803EC098 != 0) {
        lbl_803EC094 = DbUtilAlloc(lbl_803EC098 * 12, 1);
        i = 0;
        do {
            status = TDbCompilePerformOp(0, lbl_802B5BDC, &cursor, &lbl_803EC094[i][0], &lbl_803EC094[i][1], &lbl_803EC094[i][2]);
            i++;
        } while (status == 0);
    }
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        if (cursor.mUnknown0 != 0) {
            status = TDbSQLDestroyCursor(&cursor);
        } else {
            status = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return status;
}

void fn_8022E96C(void)
{
    if (lbl_803EC094 != 0) {
        DbUtilFree(lbl_803EC094);
        lbl_803EC094 = 0;
        lbl_803EC098 = 0;
    }
}

int fn_8022E9A4(void)
{
    return fn_8022E9E4();
}

void fn_8022E9C4(void)
{
    fn_8022EA4C();
}

int fn_8022E9E4(void)
{
    int result;
    if (lbl_803EC084 != 0) {
        fn_8022E694();
    }
    if (lbl_803EC08C != 0) {
        fn_8022E7FC();
    }
    if (lbl_803EC094 != 0) {
        fn_8022E96C();
    }
    result = fn_8022E568();
    if (result == 0) {
        result = fn_8022E6CC();
        if (result == 0) {
            result = fn_8022E834();
        }
    }
    return result;
}

void fn_8022EA4C(void)
{
    fn_8022E96C();
    fn_8022E7FC();
    fn_8022E694();
}
