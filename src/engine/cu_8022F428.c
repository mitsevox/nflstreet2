/* Partial source for the engine range 0x8022F428-0x802355E4 (neutral file name). */

#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>
#include "engine/Render_802353F8.h"
#include "game/fn_8022F478.h"
#include "game/fn_80233CBC.h"
#include "game/fn_801FCE10.h"
#include "game/Object_8020E52C.h"
#include "game/Object_80233EAC.h"
#include "game/QueryStatus.h"

typedef struct Entry_802FB300 {
    int mUnknown0;
    int mUnknown4;
} Entry_802FB300;

typedef struct Funcs_802FB3BC {
    int mUnknown0[5];
} Funcs_802FB3BC;

typedef struct Block_80233588 {
    int mUnknown0;
    char *mpUnknown4;
    int mUnknown8;
} Block_80233588;

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
    char mUnknown8[8];
    float mUnknown16;
    float mUnknown20;
} Box_80234070;

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

extern void fn_801D04C4(void);
extern void fn_801D0508(void);
extern void fn_801D0544(void);
extern void fn_801D0664(Mtx44 m);
extern void fn_801D0F80(Mtx44 m);
extern void fn_801D12BC(int a);
extern void *fn_801D2B7C(int size, int a, int b);
extern int fn_801D2BD0(void *p);
extern int fn_801EF390(void *pData, int index, int a);
extern int fn_801EFF80(void *pArchive, int id, void *pDest);
extern int fn_801F010C(void *pData, int index);
extern int fn_801F0DB8(void *pData, int index);
extern int fn_801F8D60(int handle, int a);
extern int fn_801F8EEC(int handle);
extern int fn_801F9014(int handle);
extern int fn_801F9134(int handle, void **ppData, int a, void *b);
extern int fn_801F91AC(int handle, int a, int b);
extern int fn_801F9430(int a, int *pTable4, int *pTable8);
extern int fn_801F9574(void);
extern int fn_801F9980(int handle, int *pTable);
extern int fn_801F9A90(int handle, int table);
extern int fn_801F9D0C(int handle, int table, int a);
extern int fn_801FA68C(void *pCallback, int tag);
extern int fn_801FA740(int tag);
extern int fn_8020D2D0(int tag, char *pName, int a, int b);
extern void fn_8020E9D0(void *pDst, void *pSrc, unsigned int size);
extern void fn_8020EBB0(void *p);
extern void *fn_8020EC50(void *p, unsigned int tag, void *pOut);
extern void fn_8020F28C(void *p);
extern void fn_8020F2C4(void *pDst, void *pSrc);
extern void fn_8020F4D0(void *p, void *pData);
extern void fn_8020F78C(void *p, void *pRef);
extern void fn_8020F824(void *p, void *q);
extern void fn_8020F89C(void *p);
extern void fn_8020F8E0(void *p);
extern void fn_8020F92C(void *p);
extern void fn_8020F96C(void *p, void *q, int a, int b);
extern void fn_8020FD48(const char *pName, void *pTexture, void *pPalette);
extern void fn_8020FE3C(int handle);
extern void fn_80210054(void *p, int a);
extern void fn_80210114(void *p);
extern void fn_802101B0(void *p, int a);
extern void fn_80210654(void *p);
extern void fn_80210724(void *p);
extern void fn_80210BA4(void *p);
extern void fn_802112DC(short *pValues, int count);
extern void fn_80211424(short *pValues, int count);
extern int fn_80211984(const char *pName);
extern void fn_80211E08(void *p, int a);
extern void fn_80211EFC(void *p);
extern void *fn_80212050(void *p);
extern void *fn_80212074(void *p, int a);
extern void fn_802134D0(void *p);
extern void fn_80213504(Joints_802337D4 *pJoints, int a);
extern void fn_8021353C(Joints_802337D4 *pJoints, void *p, int *q, void *pPose);
extern void fn_80213774(Joints_802337D4 *pJoints, void *p, int *q, void *pPose, unsigned char *pFlags);
extern void fn_80213A38(int a, int b, int c);
extern void fn_80214140(int a);
extern void fn_80214184(int a);
extern void fn_802141C4(int a, void *p, void *q);
extern unsigned int fn_8021445C(void *p, void *q, int a);
extern void fn_802144AC(void *p);
extern void fn_80214554(void *p, int a, int b);
extern void fn_802145B0(void *p);
extern void fn_802145F4(void *p);
extern void fn_802149D4(short *pValues, int count);
extern void fn_80214A7C(void *p);
extern void fn_80214B20(void);
extern void fn_80214B44(void *p);
extern void fn_80214CB4(void);
extern Range_80216190 *fn_80216190(Group_803E96E8 *pGroup, int a, int key);
extern int fn_802161D8(List_80233BE4 *pList, short *pOut, unsigned int index, int value);
extern int fn_802293A8(void);
extern void fn_802293B0(void);
extern int fn_8022942C(void);
extern void fn_80229434(void);
extern int fn_80229554(void);
extern int fn_802296B4(int a, int b);
extern int fn_80229718(Funcs_802FB3BC *pFuncs);
extern int fn_80229744(void);
extern int fn_80229760(void **ppData, void *p);
extern int fn_80229788(int a, int b);
extern int fn_802299FC(void);
extern void fn_80229A70(void);
extern int fn_80229E88(void);
extern void fn_8022A304(void);
extern int fn_8022B02C(int a);
extern void fn_8022B200(void);
extern int fn_8022C214(int a);
extern void fn_8022C3C8(void);
extern int fn_8022C410(int a);
extern int fn_8022C518(int a);
extern void fn_8022C988(void *p);
extern int fn_8022D154(void);
extern void fn_8022D1B8(void);
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
extern void fn_80236F00(void);

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
void fn_80234094(Box_80234070 *pBox);
int fn_80234098(Object_80233EAC *pObject, float value);
Desc_802345F8 *fn_802345F8(Desc_802345F8 *pDescs, const char *pName);
void fn_8023472C(void *p, int a, int b, Desc_802345F8 *pA, Desc_802345F8 *pB, int c);
void fn_80234A14(Part_80234A30 *pPart, int mask);
void fn_80234A94(Part_80234A30 *pPart, void *pRecord);
void fn_80234B88(Part_80234A30 *pPart);
void fn_80234DFC(int a, Sprite_80234DFC *pSprite, int c, int d, const char *pName, int e);

int fn_8022F428(int key)
{
    unsigned char i = lbl_803EC0D8;

    while (--i != 255) {
        if (lbl_802FB300[i].mUnknown4 == key) {
            return lbl_802FB300[i].mUnknown0;
        }
    }
    return -1;
}

int fn_8022F478(int value)
{
    int old = lbl_803EC0D4;

    lbl_803EC0D4 = value;
    return old;
}

int fn_8022F488(int value)
{
    fn_8022F478(value);
    return fn_8022F3D4(value);
}

int fn_8022F4BC(void)
{
    return lbl_803EC0D4;
}

int fn_8022F4C4(void)
{
    int err = 0;
    unsigned int i;
    int *p = lbl_803ED6E4;

    for (i = 0; i <= 1; i++) {
        int handle = *p++;

        err = fn_801F8D60(handle, lbl_803EC0C8);
        if (err != 0) {
            break;
        }
        err = fn_8020D2D0(handle, lbl_803EC0CC, lbl_803EC0D0, 0);
        if (err != 0) {
            break;
        }
    }
    return err;
}

int fn_8022F53C(int a)
{
    int key;
    int err;

    if (a == 0) {
        err = fn_801FCE10(0, lbl_802B5D88, fn_8022F3D4(fn_8022F4BC()), &key);
        if (key != fn_8022F4BC()) {
            if (fn_8022F384(key) == -1) {
                lbl_802FB300[fn_8022F384(fn_8022F4BC())].mUnknown0 = key;
                lbl_803EC0D4 = key;
            } else {
                err = 1;
            }
        }
    } else {
        err = 36;
    }
    return err;
}

int fn_8022F744(void)
{
    int err = 0;
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        err = fn_801F8EEC(lbl_803ED6E4[i]);
        if (err != 0) {
            break;
        }
    }
    return err;
}

int fn_8022F794(int value, char *pName)
{
    int err = 0;
    int old = fn_8022F478(value);

    if (fn_8022F3D4(fn_8022F4BC()) != -1) {
        err = fn_801FCE10(0, lbl_802B5DB0, fn_8022F3D4(fn_8022F4BC()), pName);
    }
    fn_8022F478(old);
    return err;
}

unsigned short fn_8022F80C(void)
{
    unsigned short id;
    Cache_8022F8A8 *pCache;

    for (id = 0; id <= 0xFFFD; id++) {
        for (pCache = lbl_803EC0E0; pCache != 0 && pCache->mUnknown0 != id; pCache = pCache->mpUnknown100) {
        }
        if (pCache == 0) {
            return id;
        }
    }
    return id;
}

Cache_8022F8A8 *fn_8022F858(unsigned short id)
{
    Cache_8022F8A8 *pCache;

    for (pCache = lbl_803EC0E0; pCache != 0 && pCache->mUnknown0 != id; pCache = pCache->mpUnknown100) {
    }
    return pCache;
}

Cache_8022F8A8 *fn_8022F880(int key)
{
    Cache_8022F8A8 *pCache;

    for (pCache = lbl_803EC0E0; pCache != 0 && pCache->mUnknown4 != key; pCache = pCache->mpUnknown100) {
    }
    return pCache;
}

int fn_8022FBAC(Cache_8022F8A8 *pCache)
{
    unsigned short i;

    if (pCache->mUnknown36.mWord != 0) {
        for (i = 0; i <= 1; i++) {
            if ((pCache->mUnknown36.mBytes[i >> 3] & (1 << (i & 7))) == (1 << (i & 7))) {
                fn_8022C988(pCache->mpUnknown12[i]);
                fn_8022C988(pCache->mpUnknown20[i]);
                fn_8022C988(pCache->mpUnknown28[i]);
            }
        }
    }
    if (pCache->mpUnknown96 != 0) {
        pCache->mpUnknown96->mpUnknown100 = pCache->mpUnknown100;
    }
    if (pCache->mpUnknown100 != 0) {
        pCache->mpUnknown100->mpUnknown96 = pCache->mpUnknown96;
    }
    if (lbl_803EC0E0 == pCache) {
        lbl_803EC0E0 = pCache->mpUnknown100;
    }
    fn_8022C988(pCache);
    return 0;
}

int fn_802303A0(int index)
{
    return lbl_802FB310[index].mUnknown0;
}

int fn_802303B4(int key, unsigned short *pId)
{
    Cache_8022F8A8 *pCache;
    int err = fn_8022F8A8(key, &pCache);

    if (err == 0) {
        *pId = pCache->mUnknown0;
    } else {
        *pId = 0xFFFF;
    }
    return err;
}

int fn_80230CC8(unsigned short id)
{
    return fn_8022FBAC(fn_8022F858(id));
}

int fn_80230CEC(int a, int b, int c, int key, int e, int f)
{
    unsigned short id;
    int err = fn_802303B4(key, &id);

    if (err == 0) {
        err = fn_80230400(id, a, a, b, c, e, f);
    }
    if (id != 0xFFFF) {
        if (err == 0) {
            err = fn_80230CC8(id);
        } else {
            fn_80230CC8(id);
        }
    }
    return err;
}

void fn_802311C8(int handle)
{
    lbl_803EC0E8 = handle;
    lbl_803EC0E4 = 0x4F434350;
    fn_801FA68C(fn_8023123C, 0x4F434350);
}

void fn_80231208(void)
{
    lbl_803EC0E8 = -1;
    fn_801FA740(lbl_803EC0E4);
    lbl_803EC0E4 = 0;
}

int fn_80231A84(void)
{
    return 3;
}

int fn_80231A8C(const char *pWhere, int b, int c, int d, int e, struct QueryCursor *pCursor)
{
    int table;

    fn_801F9980(lbl_803EC0E8, &table);
    return fn_801FCE10(0, lbl_802B6520, pCursor, table, pWhere, c, d, e);
}

int fn_802328A8(void)
{
    int err;

    if ((err = fn_8022EA74()) != 0) {
        return err;
    }
    if ((err = fn_8022942C()) != 0) {
        return err;
    }
    if ((err = fn_802293A8()) != 0) {
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
    return fn_8022DA90(lbl_802FB398);
}

void fn_80232950(void)
{
    fn_8022DB08();
    fn_8022D1B8();
    fn_8022D6F0();
    fn_80229A70();
    fn_8022C3C8();
    fn_8022B200();
    fn_8022A304();
    fn_8022E9C4();
    fn_802293B0();
    fn_80229434();
    fn_8022EA7C();
}

int fn_80232998(void)
{
    return fn_801F9430(0x454D4147, lbl_802FB3B0, lbl_802FB3A4);
}

int fn_802329D0(void)
{
    return fn_801F9574();
}

int fn_80232A98(void)
{
    int err;

    fn_80232950();
    err = fn_802329D0();
    if (fn_801F9014(0x454D4147) == 0) {
        if (err == 0) {
            err = fn_80233694();
        } else {
            fn_80233694();
        }
    }
    return err;
}

int fn_80232AF8(void **ppData, void *p)
{
    Funcs_802FB3BC funcs;
    int mode;
    int err;

    fn_80232950();
    if ((err = fn_80233604(ppData, p)) != 0) {
        return err;
    }
    if ((err = fn_802328A8()) != 0) {
        return err;
    }
    mode = 0;
    if ((err = fn_801FCE10(0, lbl_802B6E10, &mode)) != 0) {
        return err;
    }
    fn_802334F0(mode, &funcs);
    fn_80229718(&funcs);
    return fn_80229760(ppData, p);
}

int fn_80232B8C(int a, int b)
{
    struct QueryCursor cursor;
    int mode;
    int id;
    int err = fn_801FCE10(0, lbl_802B6E10, &mode);

    if (err == 0) {
        if (mode != 2) {
            cursor.mUnknown0 = 0;
            cursor.mUnknown4 = 0;
            cursor.mUnknown8 = -1;
            cursor.mUnknown12 = 0;
            err = fn_801FCE10(0, lbl_802B6E34, &cursor, 1);
            if (err == 0) {
                do {
                    err = fn_801FCE10(0, lbl_802B6E74, &cursor, &id);
                    if (err != 0) {
                        break;
                    }
                    err = fn_801FCE10(0, lbl_802B6E90, id);
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
        }
        if (err == 0) {
            cursor.mUnknown0 = 0;
            cursor.mUnknown4 = 0;
            cursor.mUnknown8 = -1;
            cursor.mUnknown12 = 0;
            err = fn_801FCE10(0, lbl_802B6EA0, &cursor, 0);
            if (err == 0) {
                do {
                    err = fn_801FCE10(0, lbl_802B6E74, &cursor, &id);
                    if (err != 0) {
                        break;
                    }
                    if (fn_801F9A90(0, id) == 0) {
                        err = fn_801F9D0C(0, id, 0);
                    }
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
            if (err == 0) {
                err = fn_80229788(a, b);
            }
        }
    }
    return err;
}

int fn_80232DE0(void)
{
    fn_80229718(&lbl_802FB3BC);
    return fn_801FCE10(0, lbl_802B6EE0, 0);
}

int fn_80232E20(void)
{
    int err = fn_801FCE10(0, lbl_802B6F00, 0, 4);

    if (err == 0) {
        fn_80229744();
    }
    return err;
}

int fn_80232E70(void)
{
    return 0;
}

int fn_80232E78(void)
{
    return 0;
}

int fn_80232E80(void)
{
    int err = fn_80232E20();

    if (err == 0) {
        err = fn_80232EB4();
    }
    return err;
}

int fn_80232EAC(void)
{
    return 0;
}

int fn_80232EB4(void)
{
    fn_80229718(&lbl_802FB3D0);
    return fn_801FCE10(0, lbl_802B6EE0, 1);
}

int fn_80232EF4(void)
{
    int err = fn_801FCE10(0, lbl_802B6F00, 1, 4);

    if (err == 0) {
        fn_80229744();
    }
    return err;
}

int fn_80232F44(void)
{
    return 0;
}

int fn_80232F4C(void)
{
    return 0;
}

int fn_80232F54(void)
{
    return fn_80232EF4();
}

int fn_80232F74(void)
{
    int mode;
    int err = fn_801FCE10(0, lbl_802B6F30, &mode);

    if (err == 0) {
        if (mode == 4) {
            err = fn_80229554();
        } else {
            err = fn_80232EF4();
            if (err == 0) {
                err = fn_80232DE0();
            }
        }
    }
    return err;
}

int fn_80232FD4(int *pRecord0, int *pRecord1)
{
    unsigned char flag;
    unsigned char result;
    int id0;
    int id1;
    unsigned int i;
    int err;

    fn_80229718(&lbl_802FB3E4);
    err = fn_801FCE10(0, lbl_802B6F54, &flag);
    if (err == 0) {
        if (flag == 0) {
            err = fn_8022C518(0x07000000);
            if (err == 0) {
                err = fn_8022C410(0x04000000);
                if (err == 0) {
                    err = fn_802296B4(0x07000000, 0x03000000);
                    if (err == 0) {
                        err = fn_8022E9E4();
                    }
                }
            }
            id0 = 0;
            id1 = 0;
            if (err == 0 && (err = fn_801FCE10(0, lbl_802B6F78, &id0, 0)) == 0
                && (err = fn_801FCE10(0, lbl_802B6F78, &id1, 1)) == 0
                && (err = fn_8022DBF4(id0)) == 0 && (err = fn_8022DC38(id1)) == 0) {
                for (i = 0; i <= 13; i++) {
                    fn_801FCE10(0, lbl_802B6FB0, &pRecord0[i], pRecord0[i], id0);
                }
                for (i = 0; i <= 13; i++) {
                    fn_801FCE10(0, lbl_802B6FB0, &pRecord1[i], pRecord1[i], id1);
                }
                if (err == 0) {
                    err = fn_8022E28C(flag, 0, &result, pRecord0, pRecord1);
                }
            }
        }
        if (err == 0) {
            err = fn_801FCE10(0, lbl_802B6EE0, 2);
        }
    }
    return err;
}

int fn_802331BC(void)
{
    struct QueryCursor cursor;
    int id;
    int err = fn_801FCE10(0, lbl_802B6FF4, &cursor, 6, 5);

    if (err == 0) {
        for (;;) {
            err = fn_801FCE10(0, lbl_802B7050, &cursor, &id);
            if (err != 0) {
                break;
            }
            err = fn_801FCE10(0, lbl_802B706C, id);
            if (err != 0) {
                break;
            }
        }
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
    if (err == 0) {
        err = fn_801FCE10(0, lbl_802B709C, 6, 5);
        if (QUERY_STATUS_ACCEPTED(err) == 1) {
            err = 0;
        }
        if (err == 0) {
            err = fn_801FCE10(0, lbl_802B6F00, 2, 4);
            if (err == 0) {
                fn_80229744();
            }
        }
    }
    return err;
}

int fn_80233344(void)
{
    return 0;
}

int fn_8023334C(int a, int b)
{
    int err = fn_801FCE10(0, lbl_802B6F00, 4, 1);

    if (err == 0) {
        err = fn_801FCE10(0, lbl_802B70DC, 1);
    }
    if (err == 0) {
        err = fn_80233660(a, b);
    }
    if (err == 0) {
        err = fn_801FCE10(0, lbl_802B6F00, 1, 2);
    } else {
        fn_801FCE10(0, lbl_802B6F00, 1, 2);
    }
    if (err == 0) {
        err = fn_801FCE10(0, lbl_802B70DC, 0);
    } else {
        fn_801FCE10(0, lbl_802B70DC, 0);
    }
    return err;
}

int fn_80233454(void)
{
    int mode;
    int err = fn_801FCE10(0, lbl_802B70FC, &mode);

    if (err == 0) {
        if (mode == 6) {
            err = fn_8022E484();
        }
        if (err == 0) {
            err = fn_8022DB20();
            if (err == 0) {
                err = fn_802331BC();
                if (err == 0) {
                    err = fn_80232DE0();
                }
            }
        }
    }
    return err;
}

int fn_802334C4(void)
{
    int err = fn_802331BC();

    if (err == 0) {
        err = fn_80232DE0();
    }
    return err;
}

void fn_802334F0(int mode, Funcs_802FB3BC *pFuncs)
{
    switch (mode) {
    case 0:
        *pFuncs = lbl_802FB3BC;
        break;
    case 1:
        *pFuncs = lbl_802FB3D0;
        break;
    case 2:
        *pFuncs = lbl_802FB3E4;
        break;
    }
}

int fn_80233568(int a, int b, unsigned char *pDone)
{
    *pDone = 1;
    return 0;
}

int fn_80233578(void)
{
    return 0;
}

int fn_80233580(void)
{
    return 0;
}

int fn_80233588(Block_80233588 *p)
{
    int err = fn_801F8D60(0x454D4147, p->mUnknown0);

    if (err != 0) {
        return err;
    }
    err = fn_8020D2D0(0x454D4147, p->mpUnknown4, p->mUnknown8, 3);
    if (err != 0) {
        return err;
    }
    return fn_8022ED50(0x454D4147, 0x4C424154, 0x534C4654);
}

int fn_80233604(void **ppData, void *p)
{
    int err = fn_801F9134(0x454D4147, ppData, 3, p);

    if (err != 0) {
        return err;
    }
    return fn_8022ED50(0x454D4147, 0x4C424154, 0x534C4654);
}

int fn_80233660(int a, int b)
{
    return fn_801F91AC(0x454D4147, a, b);
}

int fn_80233694(void)
{
    return fn_801F8EEC(0x454D4147);
}

int fn_802336BC(void)
{
    return 0;
}

void fn_802336C4(Block_802336C4 *pBlock, void *pSource, int a)
{
    fn_80214554(pBlock, a, 32);
    if (pSource != 0) {
        fn_8020F2C4(pBlock->mUnknown10, pSource);
        fn_8020F8E0(pBlock->mUnknown10);
    } else {
        fn_8020F28C(pBlock->mUnknown10);
    }
}

void fn_80233728(Block_802336C4 *pBlock)
{
    fn_8020F92C(pBlock->mUnknown10);
    fn_802145B0(pBlock);
}

void fn_80233760(Block_802336C4 *pBlock, short *pValues, int count)
{
    fn_8020F89C(pBlock->mUnknown10);
    fn_802145F4(pBlock);
    fn_80214A7C(pBlock);
    fn_80214B44(pBlock->mUnknown10);
    fn_802149D4(pValues, count);
    fn_80214CB4();
    fn_80214B20();
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
                fn_80236F00();
            }
            fn_80213504(pJoints, pSkeleton[1]);
            fn_8021353C(pJoints, pBones, pSkeleton, pPose);
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
                fn_80236F00();
            }
            fn_80213504(pJoints, pSkeleton[1]);
            fn_80213774(pJoints, pBones, pSkeleton, pPose, pFlags);
        }
    }
}

void fn_80233BB8(void *pJoints, int a, int b)
{
    fn_802134D0(pJoints);
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
                total += fn_802161D8(pList, &pOut[total], i, pValues->mUnknown8[i]);
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
    fn_8020F28C(pRecord);
    pLod->mpUnknown10 = pRecord;
    fn_8020EBB0(pLod->mpUnknown18);
    fn_8020F4D0(pRecord, pLod->mpUnknown18);
    fn_8020F78C(pRecord, lbl_803EC0F4);
    if (p != 0) {
        fn_8020F824(pRecord, p);
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
            if (fn_801F0DB8(pData, pLods->mId) != 0) {
                fresh = 0;
            }
            pLods->mpUnknown18 = (void *)fn_801EF390(pData, pLods->mId, 1);
            fn_8020F28C(&pLods->mUnknown1C);
            pLods->mpUnknown10 = &pLods->mUnknown1C;
            if (pLods->mpUnknown18 != 0) {
                fn_8020EBB0(pLods->mpUnknown18);
                fn_8020F4D0(&pLods->mUnknown1C, pLods->mpUnknown18);
                if (lbl_803EC0F4 != 0) {
                    if (fresh) {
                        fn_8020F78C(&pLods->mUnknown1C, lbl_803EC0F4);
                    } else {
                        pLods->mUnknown1C.mpUnknown18 = lbl_803EC0F4;
                    }
                }
                if (p != 0) {
                    fn_8020F824(&pLods->mUnknown1C, p);
                }
            }
        } else {
            fn_8020F28C(&pLods->mUnknown1C);
            pLods->mpUnknown10 = 0;
        }
        pObject->mUnknownC++;
    }
}

void fn_80233EAC(Object_80233EAC *pObject, ModelLod_802DF190 *pLods, const char *pName, int a, void *pArchive,
                 Skeleton_80041930 *pSkeleton, void **ppData, int load)
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
                fn_801EFF80(pArchive, pLods->mId, ppData[n]);
            }
            pLods->mpUnknown18 = ppData[n];
            fn_8020F28C(&pLods->mUnknown1C);
            pLods->mpUnknown10 = &pLods->mUnknown1C;
            if (pLods->mpUnknown18 != 0) {
                fn_8020EBB0(pLods->mpUnknown18);
                fn_8020F4D0(&pLods->mUnknown1C, pLods->mpUnknown18);
                if (lbl_803EC0F4 != 0) {
                    fn_8020F78C(&pLods->mUnknown1C, lbl_803EC0F4);
                }
                if (pSkeleton != 0) {
                    fn_8020F824(&pLods->mUnknown1C, pSkeleton);
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
            fn_801F010C(pObject->mpUnknown8, pLod->mId);
            pLod->mpUnknown18 = 0;
            pLod->mpUnknown10 = 0;
            if (pLod->mUnknown1C.mUnknown1C != 0) {
                fn_8020F92C(&pLods[i].mUnknown1C);
            }
            fn_8020F28C(&pLod->mUnknown1C);
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
        pTexture = fn_80212050(pA->mpUnknown20);
    }
    if (pB != 0) {
        pPalette = fn_80212074(pB->mpUnknown20, c);
    }
    fn_802101B0(p, a);
    if (b == 0) {
        fn_8020FD48(lbl_802B7128, pTexture, pPalette);
    } else if (pTexture != 0) {
        fn_8020FE3C(lbl_803ED024);
        fn_8020FD48(lbl_802B7130, pTexture, pPalette);
    } else {
        fn_8020FE3C(lbl_803ED020);
    }
}

void fn_802347EC(void *pData, Desc_802345F8 *pDesc, int a, int b)
{
    pDesc->mpUnknown28 = pData;
    pDesc->mpUnknown24 = fn_801D2B7C(40, 0, 0);
    fn_80211E08(pDesc->mpUnknown24, (int)pDesc->mpUnknown28);
    pDesc->mpUnknown20 = pDesc->mpUnknown24->mpUnknown36;
}

void fn_80234844(Desc_802345F8 *pDesc)
{
    if (pDesc->mpUnknown24 != 0) {
        fn_80211EFC(pDesc->mpUnknown24);
        fn_801D2BD0(pDesc->mpUnknown24);
        pDesc->mpUnknown24 = 0;
    }
}

void fn_8023488C(void *p, int a)
{
    fn_80210054(p, a);
}

void fn_802348AC(void *p)
{
    fn_80210114(p);
}

void fn_802348CC(int a)
{
    lbl_803ED020 = fn_80211984(lbl_802B7154);
    lbl_803ED024 = fn_80211984(lbl_802B715C);
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
    fn_801D04C4();
    if (b != 0) {
        fn_801D0664(b);
    }
    if (a != 0) {
        fn_801D0664(a);
    }
    fn_801D0F80(pObject->mUnknown64);
    fn_801D0544();
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
    fn_80210654(pPart->mpUnknown12);
    fn_80210BA4(pPart->mpUnknown232[0]);
    fn_80210724(pPart->mpUnknown224);
    switch (mode) {
    case 0:
        fn_802112DC(pPart->mUnknown96, pPart->mUnknown92);
        break;
    case 1:
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        fn_80213A38(0, 0, 1);
        fn_80211424(pPart->mUnknown96, pPart->mUnknown92);
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
    fn_80214140(0);
    fn_80214184(0);
    fn_8021445C(pIn, pOut, 0);
}

unsigned int fn_80234D4C(float *pBox, void *m, void *p, void *q)
{
    unsigned int result;

    fn_801D0508();
    fn_801D12BC(3);
    fn_80214140(0);
    fn_802141C4(0, p, m);
    result = fn_8021445C(pBox, q, 0);
    fn_801D0544();
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
    void *pText = fn_8020EC50((void *)a, 0x54657874, &pHeader);

    if (pText != 0) {
        if (e == 0) {
            pSprite->mpUnknown40 = fn_801D2B7C(pHeader->mUnknown8, 0, 0);
            fn_8020E9D0(pSprite->mpUnknown40, pText, pHeader->mUnknown8);
        } else {
            pSprite->mpUnknown40 = pText;
        }
        fn_80211E08(pSprite, (int)pSprite->mpUnknown40);
    }
    pSprite->mpUnknown44 = fn_8020EC50((void *)a, 0x4D61746C, 0);
}

void fn_80234EA0(Sprite_80234DFC *pSprite, int keep)
{
    if (pSprite->mpUnknown40 != 0) {
        fn_80211EFC(pSprite);
        if (keep == 0) {
            fn_801D2BD0(pSprite->mpUnknown40);
        }
    }
}

void fn_80234EEC(Holder_80234EEC *pHolder, int index, void *pData, unsigned char sourceIndex)
{
    Sprite_80234DFC *pSprite = pHolder->mpUnknown88;
    Object_8020E52C *pDst;
    Object_8020E52C *pSrc;
    Object_8020E560 *pDstImage;
    Object_8020E560 *pSrcImage;

    fn_8020E2B0(pData);
    pDst = fn_8020E52C(pSprite->mpUnknown40, index);
    pSrc = fn_8020E52C(pData, sourceIndex);
    pDstImage = fn_8020E560(pSprite->mpUnknown40, pDst->mUnknown4);
    pSrcImage = fn_8020E560(pData, pSrc->mUnknown4);
    fn_8020E9D0(pDstImage->mpUnknownC, pSrcImage->mpUnknownC, pDstImage->mUnknown8);
}

void fn_80234F74(Sprite_80234DFC *pSprite, int index, void *pData, unsigned char sourceIndex, int offset)
{
    Object_8020E52C *pDst;
    Object_8020E52C *pSrc;
    Object_8020E5F8 *pDstImage;
    Object_8020E5F8 *pSrcImage;

    fn_8020E2B0(pData);
    pDst = fn_8020E52C(pSprite->mpUnknown40, index);
    pSrc = fn_8020E52C(pData, sourceIndex);
    pDstImage = fn_8020E5F8(pSprite->mpUnknown40, pDst->mUnknown8 + offset);
    pSrcImage = fn_8020E5F8(pData, pSrc->mUnknown8 + offset);
    fn_8020E9D0(pDstImage->mpUnknown8, pSrcImage->mpUnknown8, pDstImage->mUnknown4);
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
        pRange = fn_80216190(pGroup, 0, key);
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

void fn_802353D4(Render_802353F8 *p, int flags)
{
}

void fn_802353D8(Render_802353F8 *p, int flags)
{
    p->mUnknown0 |= flags;
}

void fn_802353E8(Render_802353F8 *p, int flags)
{
    p->mUnknown0 &= ~flags;
}

void fn_802353F8(Render_802353F8 *p, int flags)
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
        fn_802144AC(p->mUnknown152);
        if (p->mUnknown4 == -1) {
            fn_8020F96C(p->mUnknown100, p->mUnknown152, -1, -1);
        } else {
            fn_8020F96C(p->mUnknown100, p->mUnknown152, 0, p->mUnknown4);
        }
    }
}

void fn_80235510(Render_802353F8 *p, int mode)
{
    int old = p->mUnknown4;

    p->mUnknown4 = mode;
    if (old != mode) {
        fn_802144AC(p->mUnknown152);
        if (p->mUnknown4 == -1) {
            fn_8020F96C(p->mUnknown100, p->mUnknown152, -1, -1);
        } else {
            fn_8020F96C(p->mUnknown100, p->mUnknown152, 0, p->mUnknown4);
        }
    }
}

void fn_80235588(Render_802353F8 *p, int a)
{
    p->mUnknown0 = 0x4000;
    p->mUnknown4 = -1;
    p->mpUnknown88 = 0;
    p->mpUnknown84 = 0;
    p->mUnknown184 = 0;
    fn_8020F28C(p->mUnknown100);
    fn_80210054(p->mUnknown92, 0);
}
