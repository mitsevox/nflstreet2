#include "engine/cu_80229270.h"
/* Partial source for the engine range 0x80229270-0x8022F428 (neutral file name). */

#include "engine/Funcs_802FB3BC.h"
#include "engine/llmemory.h"
#include "game/cu_801CF5BC.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"
#include "engine/t3db.h"
#include "engine/t3db_cols.h"
#include "game/fn_8022F478.h"

#include <string.h>

struct CardStreamTarget;
struct StreamOps_8002ACB4;
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
extern char *lbl_803EC0C0;
extern int lbl_803EC0C8;
extern char *lbl_803EC0CC;
extern int lbl_803EC0D0;
extern int lbl_803EC0D4;
extern unsigned char lbl_803EC0D8;
extern Entry_802FB300 lbl_802FB300[];
extern int fn_801F8D60(int handle, int a);
extern int fn_801F8EEC(int handle);
extern int fn_801F9134(int handle, void **ppData, int a, void *b);
extern int fn_801F91AC(int handle, int a, int b);
extern int fn_801F9718(int db, int tbl, TDbCol_801F9718 *pCols, void *pRes, int a);
extern int fn_801F9064(int db, int file, char *pName, int mode, TDbIODevice_801FC5FC *pDevice);
extern TDbIODevice_801FC5FC lbl_8030199C;
extern int fn_801F967C(int db, int tbl);
extern int fn_8020D2D0(int tag, char *pName, int a, int b);
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
    unsigned short mUnknown6;
    unsigned short mUnknown8;
    char mUnknown10[2];
    struct Node_8022CC6C *mpUnknown12;
    struct Node_8022CC6C *mpUnknown16;
} Node_8022CC6C;

void fn_8022CAEC(Node_8022CC6C **ppHead);

extern unsigned int fn_801CF6D4(void *pStream, unsigned int range);
extern int fn_8022A624(Object_8022A59C *p, struct QueryCursor cursor, int a, int b);
extern int fn_802303B4(int key, unsigned short *pId);
extern int fn_80230CC8(unsigned short id);
extern int fn_80229084(void);
extern int fn_8022908C(void);

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
extern void *lbl_803EC040;
extern int lbl_803EC044;
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
void fn_8022C894(void);
void fn_8022C8C4(void);
int fn_8022C8F0(unsigned int low, unsigned int high);
void *fn_8022C938(int size, int a);
void fn_8022C988(void *p);
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

int fn_80229270(void)
{
    struct QueryCursor cursor;
    int a;
    int b;
    int c;
    unsigned char i;
    int err;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = fn_801FCE10(0, lbl_802B2138, &cursor);
    i = 0;
    if (err == 0) {
        do {
            err = fn_801FCE10(0, lbl_802B2178, &cursor, &a, &b, &c);
            if (err != 0) {
                break;
            }
            if (c != i) {
                err = fn_801FCE10(0, lbl_802B21B8, i, a, b);
            }
            i++;
        } while (err == 0);
    }
    if (QUERY_STATUS_ACCEPTED(err) == 1) {
        if (cursor.mUnknown0 != 0) {
            err = fn_801FCFA0(&cursor);
        } else {
            err = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    return err;
}

int fn_802293A8(void)
{
    return 0;
}

void fn_802293B0(void)
{
}

int fn_802293B4(int a, int b)
{
    int err = fn_801FCE10(0, lbl_802B21FC, a, b, 255);

    if (err == 0) {
        err = fn_80229270();
    }
    return err;
}

int fn_802293FC(void)
{
    return fn_801FCE10(0, lbl_802B2268);
}

int fn_8022942C(void)
{
    return 0;
}

void fn_80229434(void)
{
}

int fn_80229438(int column, int value)
{
    return fn_801FCE10(0, lbl_802B231C, column, value);
}

int fn_80229470(void)
{
    fn_8022C894();
    return 0;
}

void fn_80229494(void)
{
    fn_8022C8C4();
    fn_80229674();
    lbl_803EBFD8 = 0;
    lbl_803EBFDC = 0;
    lbl_803EBFE0 = 0;
    lbl_803EBFE4 = 0;
    lbl_803EBFE8 = -1;
    lbl_803EBFEC = 0;
}

void fn_802294D8(Handlers_802294D8 *p)
{
    lbl_803EBFD8 = p->mpUnknown0;
    lbl_803EBFDC = p->mpUnknown4;
    lbl_803EBFE0 = p->mpUnknown8;
}

int fn_802294F4(void)
{
    return lbl_803EBFEC;
}

int fn_802294FC(int *p)
{
    int err = 0;

    if (lbl_803EBFEC == 0) {
        err = fn_801FCE10(0, lbl_802B238C, *p);
        if (err == 0) {
            lbl_803EBFEC = 1;
        }
    }
    return err;
}

int fn_80229554(void)
{
    int err = 0;

    if (lbl_803EBFEC == 1) {
        lbl_803EBFED = 1;
        err = lbl_803EBFD8();
        if (err == 0) {
            err = fn_80229674();
        } else {
            fn_80229674();
        }
        lbl_803EBFEC = 0;
        lbl_803EBFED = 0;
    }
    return err;
}

int fn_802295C0(void)
{
    if (lbl_803EBFE4 != 0) {
        lbl_803EBFE4(lbl_803EBFE8);
    }
    return 0;
}

int fn_802295F8(int a)
{
    int err = 0;

    if (lbl_803EBFF0 == 0) {
        err = fn_8022A59C(a, &lbl_803EBFF0);
        if (err != 0) {
            fn_80229674();
        }
    }
    return err;
}

int fn_80229644(int a, int b)
{
    return fn_8022AB6C(lbl_803EBFF0, a, b);
}

int fn_80229674(void)
{
    int err = 0;

    if (lbl_803EBFF0 != 0) {
        err = fn_8022AC80(lbl_803EBFF0);
        lbl_803EBFF0 = 0;
    }
    return err;
}

int fn_802296B4(int a, int b)
{
    int err = fn_802295F8(0);

    if (err == 0) {
        err = fn_80229644(a, b);
    }
    if (err == 0) {
        err = fn_80229674();
    } else {
        fn_80229674();
    }
    return err;
}

void fn_80229718(Funcs_802FB3BC *pFuncs)
{
    lbl_803EBFF8 = pFuncs->mpUnknown0;
    lbl_803EBFFC = pFuncs->mpUnknown4;
    lbl_803EC000 = pFuncs->mpUnknown8;
    lbl_803EC004 = pFuncs->mpUnknown12;
    lbl_803EC008 = pFuncs->mpUnknown16;
}

void fn_80229744(void)
{
    lbl_803EBFF8 = 0;
    lbl_803EBFFC = 0;
    lbl_803EC000 = 0;
    lbl_803EC004 = 0;
    lbl_803EC008 = 0;
}

int fn_80229760(void **ppData, void *p)
{
    return lbl_803EBFFC(ppData, p);
}

int fn_80229788(int a, int b)
{
    return lbl_803EC000(a, b);
}

int fn_802297B0(void)
{
    return lbl_803EC004();
}

int fn_802299FC(void)
{
    int result = fn_802297D8(lbl_803A1C60, 0x43524F50);
    if (result == 0) {
        result = fn_802297D8(lbl_803A20A4, 0x524F4250);
    } else {
        fn_802297D8(lbl_803A20A4, 0x524F4250);
    }
    return result;
}

int fn_80229A70(void)
{
    return fn_801D34D0(lbl_803A1C60, 1092, 0, 4);
}

float fn_80229C98(int index)
{
    return lbl_803A20A4[index][1];
}

float fn_80229CB0(int index)
{
    return lbl_803A20A4[index][0];
}

float fn_80229CC4(int index, int item)
{
    return lbl_803A20A4[index][item + 2];
}

float fn_80229CE4(int index)
{
    return lbl_803A20A4[index][12];
}

int fn_80229E78(void)
{
    return 0;
}

int fn_80229E80(void)
{
    return 0;
}

void fn_8022A304(void)
{
    unsigned short i;

    for (i = 0; i < 21; i++) {
        lbl_802FA180[i].mUnknown0 = 31;
        lbl_802FA180[i].mUnknown4 = 31;
        lbl_802FA180[i].mUnknown8 = 7;
        lbl_802FA180[i].mUnknownC = 0;
        lbl_802FA180[i].mUnknownD = 0;
        lbl_802FA180[i].mUnknownE = 0;
        lbl_802FA180[i].mUnknown10 = 0;
        lbl_802FA180[i].mUnknown12 = 0;
        lbl_802FA180[i].mUnknown14 = 0;
    }
    for (i = 0; i < 17; i++) {
        lbl_802FA378[i].mUnknown0 = 31;
        lbl_802FA378[i].mUnknown4 = 31;
        lbl_802FA378[i].mUnknown8 = 7;
        lbl_802FA378[i].mUnknownC = 0;
        lbl_802FA378[i].mUnknownD = 0;
        lbl_802FA378[i].mUnknownE = 0;
        lbl_802FA378[i].mUnknown10 = 0;
        lbl_802FA378[i].mUnknown12 = 0;
        lbl_802FA378[i].mUnknown14 = 0;
    }
    for (i = 0; i < 10; i++) {
        lbl_802FA510[i].mUnknown0 = 31;
        lbl_802FA510[i].mUnknown4 = 31;
        lbl_802FA510[i].mUnknown8 = 7;
        lbl_802FA510[i].mUnknownC = 0;
        lbl_802FA510[i].mUnknownD = 0;
        lbl_802FA510[i].mUnknownE = 0;
        lbl_802FA510[i].mUnknown10 = 0;
        lbl_802FA510[i].mUnknown12 = 0;
        lbl_802FA510[i].mUnknown14 = 0;
    }
}

int fn_8022A428(int a)
{
    return fn_801FCE10(0, lbl_802B2F64, a, 1023, 1023, 31, -1, 3, 15, 7, -1, 0);
}

int fn_8022A490(unsigned int count)
{
    int err = fn_801FCE10(0, lbl_802B3010);

    if (err == 0) {
        int id = 0;
        unsigned short i;

        for (i = 0; i < count; i++) {
            if ((err = fn_8022A428(id)) == 0) {
                id++;
            } else {
                break;
            }
        }
    }
    return err;
}

int fn_8022A508(int a, int b, int c, int d, int e)
{
    return fn_801FCE10(0, lbl_802B30D0, b, c, d, e, a);
}

int fn_8022A558(int a, int b, int c, int d)
{
    return fn_801FCE10(0, lbl_802B3180, b, c, d, a);
}

int fn_8022A59C(int a, Object_8022A59C **ppOut)
{
    int err = fn_80229084();
    Object_8022A59C *p = fn_8022C938(8, 0);

    p->mUnknown4 = a;
    p->mUnknown0 = -1;
    if (err == 0) {
        err = fn_802303B4(0, &p->mUnknown0);
    }
    if (err == 0) {
        *ppOut = p;
    } else {
        fn_8022AC80(p);
        *ppOut = 0;
    }
    return err;
}

int fn_8022AB6C(Object_8022A59C *p, int a, int b)
{
    struct QueryCursor cursor;
    int err;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = fn_801FCE10(0, lbl_802B3524, &cursor);
    if (err == 0) {
        err = fn_8022A624(p, cursor, a, b);
    }
    if (QUERY_STATUS_ACCEPTED(err) == 1) {
        if (cursor.mUnknown0 != 0) {
            err = fn_801FCFA0(&cursor);
        } else {
            err = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    return err;
}

int fn_8022AC80(Object_8022A59C *p)
{
    int err = 0;

    if (p->mUnknown0 != 0xFFFF) {
        err = fn_80230CC8(p->mUnknown0);
    }
    if (err == 0) {
        err = fn_8022908C();
    } else {
        fn_8022908C();
    }
    fn_8022C988(p);
    return err;
}

int fn_8022ACEC(int key, int unused, int col, int value, int index)
{
    TDbCol_801F9718 aCols[4];
    int table;

    table = lbl_803EC020[index];
    aCols[0].mUnk0 = key;
    aCols[0].mUnk4 = table;
    aCols[0].mCol = 0x44494754;
    aCols[1].mCol = col;
    aCols[1].mUnk4 = table;
    aCols[1].mUnk0 = value;
    fn_801F9718_SetEnd(&aCols[2]);
    return fn_801F9718(0, table, aCols, 0, 0);
}


int fn_8022AD64(int db, TDbCol_801F9718 **ppCols, unsigned char *pCount)
{
    TDbColInfo_801F9AB8 aInfo[254];
    unsigned int count;
    int status;
    int hasP;
    int hasT;
    unsigned char n;
    unsigned char i;

    n = 1;
    hasP = fn_801F9C68(0, db, 0x44494750) == 0;
    hasT = fn_801F9C68(0, db, 0x44494754) == 0;
    count = 254;
    status = fn_801F9AB8(0, db, aInfo, &count);
    if (!hasP && !hasT) {
        n = 0;
    }
    if (status == 0) {
        *ppCols = fn_8022C938((count + 1) * 16, 1);
        (*ppCols)[0].mCol = -1;
        for (i = 0; i < count; i++) {
            if (aInfo[i].mCol == 0x44494750 || aInfo[i].mCol == 0x44494754) {
                (*ppCols)[0].mUnk4 = db;
                (*ppCols)[0].mCol = aInfo[i].mCol;
            } else {
                (*ppCols)[n].mUnk4 = db;
                (*ppCols)[n].mCol = aInfo[i].mCol;
                n++;
            }
        }
        fn_801F9718_SetEnd(&(*ppCols)[n]);
    }
    if (status == 0) {
        *pCount = n;
    } else {
        *pCount = 0;
    }
    return status;
}

int fn_8022AEFC(unsigned int value)
{
    int c = value >> 24;
    int result = 255;
    if ((lbl_802AEF10 + 1)[c] & 2) {
        result = 0;
    } else if ((lbl_802AEF10 + 1)[c] & 1) {
        result = 3;
    } else if (c == '0') {
        result = 2;
    } else if (c == '1') {
        result = 1;
    }
    return result;
}

int fn_8022AF54(int a, int b)
{
    return 0;
}

int fn_8022AF5C(int key, int unused, int col, int value, int set, int index)
{
    TDbCol_801F9718 aCols[4];
    int table;
    int err;

    table = lbl_803EC010[set][index];
    aCols[0].mUnk0 = key;
    aCols[0].mUnk4 = table;
    aCols[0].mCol = 0x44494750;
    aCols[1].mCol = col;
    aCols[1].mUnk4 = table;
    aCols[1].mUnk0 = value;
    fn_801F9718_SetEnd(&aCols[2]);
    err = fn_801F9718(0, table, aCols, 0, 0);
    if (err == 19) {
        err = fn_8022AF54(set, index);
        if (err == 0) {
            err = fn_801F9718(0, table, aCols, 0, 0);
        }
    }
    return err;
}


int fn_8022B02C(Callbacks_8022B02C *pCallbacks)
{
    int status = 0;
    int table;
    unsigned char i;
    unsigned char j;
    unsigned char count;

    for (i = 0; i < 1; i++) {
        count = lbl_803EC014[i];
        for (j = 0; j < count; j++) {
            lbl_803EC018[i][j] = 0;
        }
    }
    for (i = 0; i < 1; i++) {
        lbl_803EC024[i] = 0;
    }
    for (i = 0; i < 1; i++) {
        count = lbl_803EC014[i];
        for (j = 0; j < count; j++) {
            table = lbl_803EC010[i][j];
            if (fn_801F9A90(0, table) == 0) {
                status = fn_8022AD64(table, &lbl_803EC018[i][j], &lbl_803EC01C[i][j]);
            } else {
                lbl_803EC018[i][j] = 0;
                lbl_803EC01C[i][j] = 0;
            }
            if (status != 0) {
                break;
            }
        }
        if (status != 0) {
            break;
        }
    }
    for (i = 0; i < 1 && status == 0; i++) {
        table = lbl_803EC020[i];
        if (fn_801F9A90(0, table) == 0) {
            status = fn_8022AD64(table, &lbl_803EC024[i], &lbl_803ED01C[i]);
        } else {
            lbl_803ED01C[i] = 0;
        }
    }
    if (status == 0) {
        if (pCallbacks != 0) {
            lbl_803EC028 = pCallbacks->mpUnknown0;
            lbl_803EC02C = pCallbacks->mpUnknown4;
        }
        status = fn_802311C8(0);
    }
    return status;
}

void fn_8022B200(void)
{
    unsigned char i;
    unsigned char j;
    unsigned char count;

    fn_80231208();
    for (i = 0; i < 1; i++) {
        count = lbl_803EC014[i];
        for (j = 0; j < count; j++) {
            if (lbl_803EC018[i][j] != 0) {
                fn_8022C988(lbl_803EC018[i][j]);
                lbl_803EC018[i][j] = 0;
            }
        }
    }
    for (i = 0; i < 1; i++) {
        if (lbl_803EC024[i] != 0) {
            fn_8022C988(lbl_803EC024[i]);
            lbl_803EC024[i] = 0;
        }
    }
    lbl_803EC028 = 0;
    lbl_803EC02C = 0;
}

int fn_8022BF60(void)
{
    return 0;
}

int fn_8022BF68(void)
{
    int err = 0;
    unsigned char i;

    for (i = 0; i <= 4; i++) {
        err = fn_801FCE10(0, lbl_802B35D4, lbl_802FA600[i]);
        if (err != 0) {
            break;
        }
    }
    if (err == 0) {
        err = fn_801FCE10(0, lbl_802B35D4, lbl_803EC020[0]);
    }
    if (err == 0) {
        err = fn_801FCE10(0, lbl_802B35E4);
    }
    if (err == 0) {
        err = fn_801FCE10(0, lbl_802B35F8);
    }
    return err;
}

int fn_8022C02C(int a, int b, int c, int d)
{
    int err = 0;

    if (c == 0) {
        err = fn_8022BF68();
    }
    if (err == 0 && lbl_803EC028 != 0) {
        err = lbl_803EC028(a, b, c, d);
    }
    return err;
}

int fn_8022C098(int a)
{
    int err = 0;

    if (lbl_803EC02C != 0) {
        err = lbl_803EC02C(a);
    }
    if (err == 0) {
        err = fn_8022BF60();
    }
    return err;
}

int fn_8022C0E0(struct QueryCursor cursor, int a)
{
    unsigned short total;
    int *pIds;
    int id;
    int status;
    unsigned short count;
    unsigned short i;

    pIds = 0;
    status = fn_801FA1C0(cursor.mUnknown0, &total);
    if (status == 0) {
        pIds = fn_8022C938(total * 4, 0);
    }
    count = 0;
    if (status == 0) {
        while (status == 0) {
            status = fn_801FCE10(0, lbl_802B3610, &cursor, &id);
            if (status == 0) {
                pIds[count] = id;
                count++;
            }
        }
        if (QUERY_STATUS_ACCEPTED(status) == 1) {
            status = 0;
        }
        if (status == 0) {
            for (i = 0; i < count; i++) {
                status = fn_80230D8C(pIds[i], 0, a);
                if (status != 0) {
                    break;
                }
            }
        }
    }
    if (pIds != 0) {
        fn_8022C988(pIds);
    }
    return status;
}

int fn_8022C214(Callbacks_8022C214 *pCallbacks)
{
    struct QueryCursor cursor;
    int status = 0;
    int index;
    unsigned short a;
    unsigned short b;
    unsigned short c;
    unsigned short d;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = fn_801FCE10(0, lbl_802B3698, &cursor);
    while (status == 0) {
        status = fn_801FCE10(0, lbl_802B36C4, &cursor, &index, &a, &b, &c, &d);
        if (status == 0) {
            lbl_803A2390[index].mUnknown0 = a;
            lbl_803A2390[index].mUnknown2 = b;
            lbl_803A2390[index].mUnknown4 = c;
            lbl_803A2390[index].mUnknown6 = d;
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
    if (status == 0) {
        status = fn_8022ED30(0, 0x53525054);
    } else {
        fn_8022ED30(0, 0x53525054);
    }
    lbl_803EC030 = 0;
    if (status == 0) {
        lbl_803EC030 = fn_801F9A90(0, 0x53525054) == 0;
        if (pCallbacks != 0) {
            lbl_803EC034 = pCallbacks->mpUnknown0;
            lbl_803EC038 = pCallbacks->mpUnknown4;
        }
    }
    return status;
}

void fn_8022C3C8(void)
{
    fn_801D34D0((char *)lbl_803A2390, 88, 0, 4);
    lbl_803EC030 = 0;
    lbl_803EC034 = 0;
    lbl_803EC038 = 0;
}

int fn_8022C410(int a)
{
    struct QueryCursor cursor;
    int status = 0;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = fn_801FCE10(0, lbl_802B37E4, &cursor, 0);
    if (status == 0) {
        status = fn_8022C0E0(cursor, a);
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
    return status;
}

int fn_8022C518(int a)
{
    struct QueryCursor cursor;
    int status = 0;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = fn_801FCE10(0, lbl_802B3824, &cursor, 0, 5, 1);
    if (status == 0) {
        status = fn_8022C0E0(cursor, a);
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
    return status;
}

int fn_8022C628(int db, int tbl, int *pIds, unsigned short *pCount)
{
    struct QueryCursor cursor;
    int status = 0;
    int id;
    int prev;
    int next;
    int last;
    unsigned short count;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = fn_801FCE10(0, lbl_802B3888, db, &cursor, tbl);
    prev = -1;
    next = -1;
    last = 1023;
    count = 0;
    while (status == 0 && count < *pCount) {
        status = fn_801FCE10(0, lbl_802B3610, &cursor, &id);
        if (status == 0) {
            if (id > prev + 1) {
                next = prev + 1;
                while (status == 0 && next < id && count < *pCount && next <= 1008) {
                    pIds[count] = next;
                    count++;
                    next++;
                }
            }
            last = (next > id) ? next : id;
            prev = id;
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
    if (status == 0 && count < *pCount) {
        next = last + 1;
        if (last == 1023) {
            next = 0;
        }
        while (count < *pCount && next <= 1008) {
            pIds[count] = next;
            count++;
            next++;
        }
    }
    *pCount = count;
    return status;
}

int fn_8022C81C(int a)
{
    if (lbl_803EC034 != 0) {
        return lbl_803EC034(a);
    }
    return 0;
}

int fn_8022C858(int a)
{
    if (lbl_803EC038 != 0) {
        return lbl_803EC038(a);
    }
    return 0;
}

void fn_8022C894(void)
{
    lbl_803EC040 = fn_801CF5BC(0, fn_801CF7AC());
}

void fn_8022C8C4(void)
{
    fn_801CF67C(lbl_803EC040);
    lbl_803EC040 = 0;
}

int fn_8022C8F0(unsigned int low, unsigned int high)
{
    if (low < high) {
        return low + fn_801CF6D4(lbl_803EC040, high - low);
    }
    return low;
}

void fn_8022C930(int a)
{
    lbl_803EC044 = a;
}

void *fn_8022C938(int size, int a)
{
    void *p;

    if (a != 0) {
        p = fn_801D2BB0(lbl_803EC044, size, 0, 0);
    } else {
        p = fn_801D2B7C(size, 0, 0);
    }
    return p;
}

void fn_8022C988(void *p)
{
    fn_801D2BD0(p);
}

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
    return fn_801FCE10(0, lbl_802B45F0, &lbl_803A25E0, a, c, b);
}

void fn_8022CDA0(void)
{
    if (lbl_803A25E0.mUnknown0 != 0) {
        fn_801FCFA0(&lbl_803A25E0);
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
        err = fn_801FCE10(0, lbl_802B4650, &lbl_803A25E0, &value, &key);
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
        fn_8022CED8();
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
        status = fn_801FCE10(0, lbl_802B479C, &lbl_802FA8B0, tblA, tblB, tblB, tblA, tblA, 0, tblB, tblB);
    } else {
        status = fn_801FCE10(0, lbl_802B4828, &lbl_802FA8B0, tblA, tblB, tblB, tblA, tblA, (a != 1023) ? a : b,
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
        result = fn_801FCFA0(&lbl_802FA8B0);
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
        result = fn_801FCE10(0, lbl_802B48C4, &lbl_802FA8B0, tag, &a, tag, &b, tag, &c, tag, &d);
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
        result = fn_801FCE10(0, lbl_802B4A54, &found, a, b, row);
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
        result = fn_801FCE10(0, lbl_802B4A9C, a, b, row, value);
        if (result == 0) {
            result = fn_801FCE10(0, lbl_802B4AE0, a, b, c, row, value);
        }
    }
    return result;
}

int fn_8022D834(int row, int column)
{
    if ((unsigned short)column <= 9) {
        return lbl_802FAA50[row][column][0];
    }
    return 31;
}

int fn_8022D864(void)
{
    return 0;
}

int fn_8022D86C(void)
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

int fn_8022DA90(int *p)
{
    unsigned char found;
    int result = fn_801FCE10(0, lbl_802B4EA0, &found);
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

    result = fn_801FCE10(0, lbl_802B4EC4, 999.99f, 999.99f, 15, 2047, 15, 127, 127, 127, -1, 1023, 63, 63, 4, 3,
                         255, 1023, 63, 63, 4, 3, 255, 1023, -1, 15, 1023, 15, 0, 0);
    lbl_803EC07C = 1023;
    lbl_803EC080 = 1023;
    return result;
}

int fn_8022DBF4(int value)
{
    int err = fn_801FCE10(0, lbl_802B5080, value);

    lbl_803EC07C = value;
    return err;
}

int fn_8022DC38(int value)
{
    int err = fn_801FCE10(0, lbl_802B50A0, value);

    lbl_803EC080 = value;
    return err;
}

int fn_8022DC7C(int value)
{
    return fn_801FCE10(0, lbl_802B50C0, value);
}

int fn_8022DCB0(int value)
{
    return fn_801FCE10(0, lbl_802B50E0, value);
}

int fn_8022DCE4(int value)
{
    return fn_801FCE10(0, lbl_802B5100, value);
}

int fn_8022DD18(int value)
{
    return fn_801FCE10(0, lbl_802B5120, value);
}

int fn_8022DD4C(int value)
{
    return fn_801FCE10(0, lbl_802B519C, value);
}

int fn_8022DD80(int value)
{
    return fn_801FCE10(0, lbl_802B51BC, value);
}

int fn_8022DDB4(int a, void *p)
{
    return 0;
}
int fn_8022E21C(int a, int b)
{
    if (a != 1023 && b != 1023) {
        return fn_801FCE10(0, lbl_802B56F4, a, b);
    } else {
        int value = b;
        if (a != 1023) {
            value = a;
        }
        return fn_801FCE10(0, lbl_802B5744, value);
    }
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
    status = fn_801FCE10(&result, lbl_802B5A48, &cursor, 0, 1);
    lbl_803EC088 = result.mUnknown0;
    if (status == 0 && lbl_803EC088 != 0) {
        lbl_803EC084 = fn_8022C938(lbl_803EC088 * 4, 1);
        i = 0;
        do {
            status = fn_801FCE10(0, lbl_802B5AB0, &cursor, &lbl_803EC084[i]);
            i++;
        } while (status == 0);
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
    return status;
}

void fn_8022E694(void)
{
    if (lbl_803EC084 != 0) {
        fn_8022C988(lbl_803EC084);
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
    status = fn_801FCE10(&result, lbl_802B5ACC, &cursor, 0, 7);
    lbl_803EC090 = result.mUnknown0;
    if (status == 0 && lbl_803EC090 != 0) {
        lbl_803EC08C = fn_8022C938(lbl_803EC090 * 8, 1);
        i = 0;
        do {
            status = fn_801FCE10(0, lbl_802B5B34, &cursor, &lbl_803EC08C[i][0], &lbl_803EC08C[i][1]);
            i++;
        } while (status == 0);
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
    return status;
}

void fn_8022E7FC(void)
{
    if (lbl_803EC08C != 0) {
        fn_8022C988(lbl_803EC08C);
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
    status = fn_801FCE10(&result, lbl_802B5B64, &cursor, 0, 8, 1);
    lbl_803EC098 = result.mUnknown0;
    if (status == 0 && lbl_803EC098 != 0) {
        lbl_803EC094 = fn_8022C938(lbl_803EC098 * 12, 1);
        i = 0;
        do {
            status = fn_801FCE10(0, lbl_802B5BDC, &cursor, &lbl_803EC094[i][0], &lbl_803EC094[i][1], &lbl_803EC094[i][2]);
            i++;
        } while (status == 0);
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
    return status;
}

void fn_8022E96C(void)
{
    if (lbl_803EC094 != 0) {
        fn_8022C988(lbl_803EC094);
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

int fn_8022EA74(void)
{
    return 0;
}

void fn_8022EA7C(void)
{
}

int fn_8022EA80(int a, const char *pName, int b)
{
    lbl_803EC0A4 = fn_8022C938(strlen(pName) + 1, 1);
    strcpy(lbl_803EC0A4, pName);
    lbl_803EC0A8 = b;
    return 0;
}

void fn_8022EAD8(void)
{
    fn_8022C988(lbl_803EC0A4);
    lbl_803EC0A0 = 0;
    lbl_803EC0A4 = 0;
    lbl_803EC0A8 = -1;
}

int fn_8022EB10(void)
{
    int result = fn_801F8D60(0x45564153, lbl_803EC0A0);
    if (result == 0) {
        result = fn_8020D2D0(0x45564153, lbl_803EC0A4, lbl_803EC0A8, 0);
    }
    return result;
}

int fn_8022EB5C(struct CardStreamTarget *pTarget, struct StreamOps_8002ACB4 *pOps)
{
    return fn_801F9134(0x45564153, (void **)pTarget, 0, pOps);
}

int fn_8022EB94(void *pTarget, struct StreamOps_8002ACB4 *pOps)
{
    return fn_801F91AC(0x45564153, (int)pTarget, (int)pOps);
}

int fn_8022EBC8(void)
{
    return fn_801F8EEC(0x45564153);
}

int fn_8022EBF0(int a, const char *pName, int b)
{
    lbl_803EC0B4 = fn_8022C938(strlen(pName) + 1, 1);
    strcpy(lbl_803EC0B4, pName);
    lbl_803EC0B8 = b;
    return 0;
}

void fn_8022EC48(void)
{
    fn_8022C988(lbl_803EC0B4);
    lbl_803EC0B0 = 0;
    lbl_803EC0B4 = 0;
    lbl_803EC0B8 = -1;
}

int fn_8022EC80(void)
{
    int result = fn_801F8D60(0x54415453, lbl_803EC0B0);
    if (result == 0) {
        result = fn_8020D2D0(0x54415453, lbl_803EC0B4, lbl_803EC0B8, 0);
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

int fn_8022EF14(const char *pName)
{
    lbl_803EC0C0 = fn_8022C938(strlen(pName) + 1, 1);
    strcpy(lbl_803EC0C0, pName);
    return 0;
}

void fn_8022EF60(void)
{
    fn_8022C988(lbl_803EC0C0);
    lbl_803EC0C0 = 0;
}

int fn_8022EF8C(int db, int file)
{
    return fn_801F9064(db, file, lbl_803EC0C0, 3, &lbl_8030199C);
}

int fn_8022EFBC(int db, int tbl)
{
    return fn_801F967C(db, tbl);
}

int fn_8022EFDC(void)
{
    int key;
    do {
        key = fn_8022C8F0(0, 0x7FFFFFFA) & 0x7FFFFFFF;
    } while (fn_8022F384(key) != -1);
    return key;
}

int fn_8022F028(int a, const char *pName, int b)
{
    lbl_803EC0C8 = a;
    lbl_803EC0CC = fn_8022C938(strlen(pName) + 1, 1);
    strcpy(lbl_803EC0CC, pName);
    lbl_803EC0D0 = b;
    lbl_803EC0D4 = -1;
    lbl_803EC0D8 = 0;
    return 0;
}

void fn_8022F094(void)
{
    fn_8022C988(lbl_803EC0CC);
    lbl_803EC0C8 = 0;
    lbl_803EC0CC = 0;
    lbl_803EC0D0 = -1;
    lbl_803EC0D4 = -1;
    lbl_803EC0D8 = 0;
}

int fn_8022F0D4(void)
{
    unsigned char i;
    int id;
    int key;
    int old;

    id = -1;
    if ((signed char)lbl_803EC0D8 <= 1) {
        for (i = 0; fn_8022F428(key = lbl_803ED6E4[i]) != -1; i++) {
        }
        id = fn_8022EFDC();
        lbl_802FB300[(signed char)lbl_803EC0D8].mUnknown0 = id;
        lbl_802FB300[(signed char)lbl_803EC0D8].mUnknown4 = key;
        fn_8020D2D0(key, lbl_803EC0CC, lbl_803EC0D0, 0);
        lbl_803EC0D8++;
        old = fn_8022F478(id);
        fn_801FCE10(0, lbl_802B5D64, fn_8022F3D4(fn_8022F4BC()), id);
        fn_8022F478(old);
    }
    return id;
}

void fn_8022F1BC(int key)
{
    signed char index;

    if (key != -1) {
        index = fn_8022F384(key);
        if (index != -1) {
            lbl_803EC0D8--;
            fn_8020D2D0(lbl_802FB300[index].mUnknown4, lbl_803EC0CC, lbl_803EC0D0, 0);
            for (; index < (signed char)lbl_803EC0D8; index++) {
                lbl_802FB300[index] = lbl_802FB300[index + 1];
            }
            lbl_802FB300[(signed char)lbl_803EC0D8].mUnknown0 = -1;
            lbl_802FB300[(signed char)lbl_803EC0D8].mUnknown4 = -1;
        }
    }
}

void fn_8022F294(int key)
{
    int index;
    int id;
    int old;

    if (key != -1) {
        index = fn_8022F384(key);
        if (index != -1) {
            fn_8020D2D0(lbl_802FB300[index].mUnknown4, lbl_803EC0CC, lbl_803EC0D0, 0);
            id = fn_8022EFDC();
            old = fn_8022F478(key);
            fn_801FCE10(0, lbl_802B5D64, fn_8022F3D4(fn_8022F4BC()), id);
            lbl_802FB300[index].mUnknown0 = id;
            if (old == key) {
                fn_8022F478(id);
            } else {
                fn_8022F478(old);
            }
        }
    }
}

int fn_8022F34C(void)
{
    return (signed char)lbl_803EC0D8;
}

int fn_8022F358(int index)
{
    int value = -1;
    if (index < (signed char)lbl_803EC0D8) {
        value = lbl_802FB300[index].mUnknown0;
    }
    return value;
}

int fn_8022F384(int key)
{
    signed char i;
    for (i = 0; i < (signed char)lbl_803EC0D8; i++) {
        if (key == lbl_802FB300[i].mUnknown0) {
            return i;
        }
    }
    return -1;
}

int fn_8022F3D4(int key)
{
    int value = -1;
    if (key != -1) {
        int index = fn_8022F384(key);
        if (index != -1) {
            value = lbl_802FB300[index].mUnknown4;
        }
    }
    return value;
}
