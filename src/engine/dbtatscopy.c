/* Partial source: holds the 'TATS' template database and copies its tables into another database. */

#include "engine/dbteams.h"
#include "engine/tdbext.h"
#include "engine/dbutil.h"
#include "engine/fn_801F9134.h"
#include "engine/cu_80229270.h"

#include "engine/Funcs_802FB3BC.h"
#include "engine/llmemory.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"
#include "engine/t3db.h"
#include "engine/t3db_cols.h"
#include "game/fn_8022F478.h"

#include <string.h>

struct CardStreamTarget;
struct SaveStreamOps_t;
#include "engine/Entry_802FB300.h"
extern char lbl_802B5C8C[];
extern char lbl_803A1C60[];
extern float lbl_803A20A4[][13];
extern char *lbl_803EC0A4;
extern int lbl_803EC0A8;
extern int lbl_803EC0A0;
extern char *lbl_803EC0B4;
extern int lbl_803EC0B8;
extern int lbl_803EC0B0;
extern int lbl_803EC0C8;
extern char *lbl_803EC0CC;
extern int lbl_803EC0D0;
extern int lbl_803EC0D4;
extern unsigned char lbl_803EC0D8;
extern Entry_802FB300 lbl_802FB300[];
extern int fn_801F91AC(int handle, int a, int b);
extern int fn_801F9718(int db, int tbl, TDbCol_801F9718 *pCols, void *pRes, int a);
extern int fn_801F9064(int db, int file, char *pName, int mode, TDbIODevice_t *pDevice);
extern TDbIODevice_t tdbiofioCallback;
extern int fn_801F967C(int db, int tbl);
int fn_8022F384(int key);

extern const unsigned char lbl_802AEF10[];
extern int fn_802297D8(void *p, int tag);
extern int fn_8022D8F8(int a, int *p, int c);
int fn_8022DB20(void);
extern int fn_8022F428(int key);
extern int fn_8022F4BC(void);
extern void fn_80231208(void);
int fn_8022F3D4(int key);
extern int lbl_803ED6E4[2];
extern char lbl_802B5D64[];
extern char lbl_802B56F4[];
extern char lbl_802B5744[];
extern char lbl_802B4EA0[];
extern char lbl_802B4EC4[];
extern char lbl_802B37E4[];
extern char lbl_802B3824[];
int fn_8022C0E0(struct QueryCursor cursor, int a);
extern int fn_801FA1C0(int ref, unsigned short *pCount);
extern int fn_80230D8C(int id, int a, int b);
extern char lbl_802B3610[];
extern char lbl_802B3698[];
extern char lbl_802B479C[];
extern char lbl_802B4828[];
extern char lbl_802B5CB4[];
extern char lbl_802B5CF0[];
extern int fn_801F9014(int db);
extern char lbl_802B3888[];
extern char lbl_802B36C4[];
extern int fn_801F9A90(int db, int tbl);
extern int fn_801F9AB8(int db, int tbl, TDbColInfo_801F9AB8 *pCols, unsigned int *pCount);
extern int fn_801F9C68(int db, int tbl, int col);
int fn_8022ED30(int db, int tbl);
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
void fn_8022CED8(void);
int fn_8022D5A4(int key, int mode);
int fn_8022D710(int a, int b, int c, int row, int value);
unsigned short fn_8022D6FC(int index);

#include "engine/Handlers_802294D8.h"

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

/* Ends a column list for fn_801F9718. */
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
extern int (*lbl_803EBFD8)(void);
extern void *lbl_803EBFDC;
extern void *lbl_803EBFE0;
extern void (*lbl_803EBFE4)(int);
extern int lbl_803EBFE8;
extern unsigned char lbl_803EBFEC;
extern unsigned char lbl_803EBFED;
extern Object_8022A59C *lbl_803EBFF0;
extern int (*lbl_803EBFF8)(void);
extern int (*lbl_803EBFFC)(void **ppData, void *p);
extern int (*lbl_803EC000)(int a, int b);
extern int (*lbl_803EC004)(void);
extern int (*lbl_803EC008)(void);
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
extern int lbl_803EC06C;
extern int lbl_803EC070;
extern int lbl_803EC074;
extern int lbl_803EC07C;
extern int lbl_803EC080;

int fn_80229674(void);
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































































































































































/* prototypes of the functions defined in the original src/engine/cu_80229270.c */
int fn_80229270(void);
int fn_802293A8(void);
void fn_802293B0(void);
int fn_802293B4(int a, int b);
int fn_802293FC(void);
int fn_8022942C(void);
void fn_80229434(void);
int fn_80229438(int column, int value);
int fn_80229470(void);
void fn_80229494(void);
void fn_802294D8(Handlers_802294D8 *p);
int fn_802294F4(void);
int fn_802294FC(int *p);
int fn_80229554(void);
int fn_802295C0(void);
int fn_802295F8(int a);
int fn_80229644(int a, int b);
int fn_80229674(void);
int fn_802296B4(int a, int b);
void fn_80229718(Funcs_802FB3BC *pFuncs);
void fn_80229744(void);
int fn_80229760(void **ppData, void *p);
int fn_80229788(int a, int b);
int fn_802297B0(void);
int fn_802299FC(void);
int fn_80229A70(void);
float fn_80229C98(int index);
float fn_80229CB0(int index);
float fn_80229CC4(int index, int item);
float fn_80229CE4(int index);
int fn_80229E78(void);
int fn_80229E80(void);
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
int fn_8022C098(int a);
int fn_8022C0E0(struct QueryCursor cursor, int a);
int fn_8022C214(Callbacks_8022C214 *pCallbacks);
void fn_8022C3C8(void);
int fn_8022C410(int a);
int fn_8022C518(int a);
int fn_8022C628(int db, int tbl, int *pIds, unsigned short *pCount);
int fn_8022C81C(int a);
int fn_8022C858(int a);
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
int fn_8022D834(int row, int column);
int fn_8022D864(void);
int fn_8022D86C(void);
int fn_8022D874(int a, int b, int c, int key);
int fn_8022D8F8(int a, int *p, int tag);
int fn_8022DA44(int a, int *b, int c, int *d, int e);
int fn_8022DA90(int *p);
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
int fn_8022E21C(int a, int b);
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
int fn_8022EA74(void);
void fn_8022EA7C(void);
int fn_8022EA80(int a, const char *pName, int b);
void fn_8022EAD8(void);
int fn_8022EB10(void);
int fn_8022EB5C(struct CardStreamTarget *pTarget, struct SaveStreamOps_t *pOps);
int fn_8022EB94(void *pTarget, struct SaveStreamOps_t *pOps);
int fn_8022EBC8(void);
int fn_8022EBF0(int a, const char *pName, int b);
void fn_8022EC48(void);
int fn_8022EC80(void);
int fn_8022ECCC(void);
int fn_8022ECF4(int a, int b);
int fn_8022ED30(int db, int tbl);
int fn_8022ED50(int db, int a, int b);
int DbFileInit(const char *pName);
void DbFileShutdown(void);
int DbFileTblLoad(int db, int file);
int DbFileTblDestroy(int db, int tbl);
int fn_8022EFDC(void);
int fn_8022F028(int a, const char *pName, int b);
void fn_8022F094(void);
int fn_8022F0D4(void);
void fn_8022F1BC(int key);
void fn_8022F294(int key);
int fn_8022F34C(void);
int fn_8022F358(int index);
int fn_8022F384(int key);
int fn_8022F3D4(int key);

int fn_8022EBF0(int a, const char *pName, int b)
{
    lbl_803EC0B4 = DbUtilAlloc(strlen(pName) + 1, 1);
    strcpy(lbl_803EC0B4, pName);
    lbl_803EC0B8 = b;
    return 0;
}

void fn_8022EC48(void)
{
    DbUtilFree(lbl_803EC0B4);
    lbl_803EC0B0 = 0;
    lbl_803EC0B4 = 0;
    lbl_803EC0B8 = -1;
}

int fn_8022EC80(void)
{
    int result = fn_801F8D60(0x54415453, lbl_803EC0B0);
    if (result == 0) {
        result = TDbExtLoadFromResource(0x54415453, lbl_803EC0B4, lbl_803EC0B8, 0);
    }
    return result;
}

int fn_8022ECCC(void)
{
    return fn_801F8EEC(0x54415453);
}

int fn_8022ECF4(int a, int b)
{
    return fn_801FCE10(0, lbl_802B5C8C, a, b, b);
}

int fn_8022ED30(int db, int tbl)
{
    return fn_801F967C(db, tbl);
}

int fn_8022ED50(int db, int a, int b)
{
    struct QueryCursor cursor;
    int tbl;
    int status = 0;
    int opened = 0;

    if (fn_801F9014(0x54415453) != 0) {
        status = fn_8022EC80();
        opened = status == 0;
    }
    if (status == 0) {
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        status = fn_801FCE10(0, lbl_802B5CB4, db, &cursor, a, b, 1);
        while (status == 0) {
            status = fn_801FCE10(0, lbl_802B5CF0, &cursor, &tbl);
            if (status == 0 && fn_801F9A90(db, tbl) != 0) {
                status = fn_8022ECF4(db, tbl);
                if (QUERY_STATUS_ACCEPTED(status) == 1) {
                    status = 0;
                }
            }
        }
        if (QUERY_STATUS_ACCEPTED(status) == 1) {
            if (cursor.mUnknown0 != 0) {
                status = fn_801FCFA0(&cursor);
            } else {
                status = 0;
            }
        } else if (cursor.mUnknown0 != 0) {
            fn_801FCFA0(&cursor);
        }
    }
    if (opened == 1) {
        if (status == 0) {
            status = fn_8022ECCC();
        } else {
            fn_8022ECCC();
        }
    }
    return status;
}
