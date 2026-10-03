#include <dolphin/mtx.h>
#include "engine/cu_80227F14.h"

typedef struct Entry_80228474 {
    int mUnknown0;
    int mUnknown4;
    Callback_80228474 mUnknown8;
    Object_80228224 *mUnknown12;
} Entry_80228474;

typedef struct Match_80228474 {
    Object_80228224 *mUnknown0;
    Callback_80228474 mUnknown4;
    int mUnknown8;
} Match_80228474;

extern void *fn_801C68FC(int a, int b, int count, int size, int (*cmp)(void *, void *), int f);
extern void fn_801C69E4(void *pool);
extern void *fn_801C6A20(void *pool);
extern void fn_801C6AA4(void *pool, void *item, int c);
extern void fn_801C6C0C(void *pool, void *item);
extern void fn_801C6D34(void *pool, int b, void *ctx, int d, int (*fn)(void *, void *), int f);
extern int fn_801CAB30(void);
extern void fn_801CE720(void);
extern void fn_801CE774(void);
extern int fn_801CEA14(void);
extern float fn_801CFD28(int angle);
extern void fn_801CEC48(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern int fn_801D0290(int a, int b);
extern int fn_801D0310(int a);
extern void fn_801D0470(int a);
extern void fn_801D0494(void);
extern void fn_801D0F80(Mtx44 m);
extern void fn_801DD140(int handle, int a, int b);
extern void fn_801F7BD4(int err);
extern int fn_801F7C88(void);
extern void fn_801F8768(void);

static unsigned char lbl_803EBF90 = 0;
static void *lbl_803EBF94 = 0;
static void *lbl_803EBF98 = 0;
static unsigned char lbl_803EBF9C = 0;
static Object_80228224 *lbl_803ED66C;
static unsigned char lbl_803ED670;

static int fn_80227F14(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

static int fn_80227F24(void *pItem, void *pContext)
{
    Entry_80228474 *pEntry = pItem;
    Match_80228474 *pMatch = pContext;

    if (pMatch->mUnknown0 == pEntry->mUnknown12) {
        if (pMatch->mUnknown4 == 0 || pMatch->mUnknown4 == pEntry->mUnknown8) {
            fn_801C6C0C(lbl_803EBF98, pEntry);
            return 0;
        }
    }
    return 1;
}

static int fn_80227F84(void *pItem, void *pContext)
{
    Entry_80228474 *pEntry = pItem;
    Match_80228474 *pMatch = pContext;

    if (pMatch->mUnknown0 == pEntry->mUnknown12 && pMatch->mUnknown8 == pEntry->mUnknown4) {
        pEntry->mUnknown8(pMatch->mUnknown0);
    }
    return 1;
}

static void fn_80227FD4(Object_80228224 *pObject, int event)
{
    Match_80228474 match;

    match.mUnknown0 = pObject;
    match.mUnknown8 = event;
    fn_801C6D34(lbl_803EBF98, 0, &match, 0, fn_80227F84, 1);
}

static int fn_80228018(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

static int fn_80228028(void *pItem, void *pContext)
{
    Object_80228224 *pObject = pItem;

    if (!(pObject->mUnknown28 & 8)) {
        lbl_803ED66C = pObject;
        fn_80227FD4(pObject, 0);
        if (!pObject->mUnknown68) {
            fn_80228530(pObject);
        }
        fn_80228B74(pObject);
        fn_80227FD4(pObject, 1);
        fn_80228594(pObject);
        pObject->mUnknown68 = 0;
        fn_80227FD4(pObject, 2);
        lbl_803ED66C = 0;
    }
    return 1;
}

int fn_802280B0(Init_802280B0 *pInit)
{
    int err;

    if (!lbl_803EBF90) {
        if ((lbl_803EBF94 = fn_801C68FC(1, 0, pInit->mUnknown0, sizeof(Object_80228224), fn_80228018, 0)) != 0
            && (lbl_803EBF98 = fn_801C68FC(1, 0, pInit->mUnknown4, sizeof(Entry_80228474), fn_80227F14, 0)) != 0) {
            lbl_803ED670 = pInit->mUnknown10;
            err = fn_801D0290(pInit->mUnknown10, pInit->mUnknown11);
            if (err == 0) {
                err = fn_802288F8(pInit);
            }
        } else {
            err = fn_801F7C88();
        }
        lbl_803ED66C = 0;
        lbl_803EBF90 = 1;
    } else {
        err = 0x80001;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_80228194(void)
{
    int err = 0;

    if (lbl_803EBF90) {
        fn_80228E18();
        if (lbl_803EBF94) {
            fn_801C69E4(lbl_803EBF94);
            lbl_803EBF94 = 0;
        }
        if (lbl_803EBF98) {
            fn_801C69E4(lbl_803EBF98);
            lbl_803EBF98 = 0;
        }
        fn_801D0310(lbl_803ED670);
        err = fn_80228948();
        lbl_803EBF90 = 0;
    } else {
        err = 0x80002;
    }
    fn_801F7BD4(err);
    return err;
}

Object_80228224 *fn_80228224(Desc_80228224 *pDesc)
{
    Object_80228224 *pObject;
    int err = 0;
    int i;

    pObject = fn_801C6A20(lbl_803EBF94);
    if (pObject) {
        pObject->mUnknown0 = pDesc->mUnknown0;
        pObject->mUnknown46 = pObject->mUnknown47 = pDesc->mUnknown3;
        for (i = 0; i < pObject->mUnknown46; i++) {
            pObject->mUnknown48[i] = pDesc->mUnknown4[i];
        }
        pObject->mUnknown4 = 0.0f;
        pObject->mUnknown8 = ((float)fn_801CEA14() - (float)pDesc->mUnknown16) * 0.5f;
        pObject->mUnknown12 = pDesc->mUnknown18;
        pObject->mUnknown16 = pDesc->mUnknown16;
        pObject->mUnknown20 = pDesc->mUnknown18;
        pObject->mUnknown24 = pDesc->mUnknown16;
        pObject->mUnknown28 = 1;
        pObject->mUnknown32 = 0.0f;
        pObject->mUnknown36 = 0.0f;
        pObject->mUnknown40 = 0.0f;
        pObject->mUnknown60 = 0;
        pObject->mUnknown72 = 0;
        pObject->mUnknown68 = 0;
        pObject->mUnknown240 = 1.0f;
        fn_801C6AA4(lbl_803EBF94, pObject, 0);
        err = fn_80228978(pDesc, pObject);
        if (err) {
            fn_801F7BD4(err);
        }
    }
    return pObject;
}

int fn_802283FC(Object_80228224 *pObject)
{
    Match_80228474 match;
    int err;

    err = fn_80228980(pObject);
    if (err) {
        fn_801F7BD4(err);
    }
    match.mUnknown0 = pObject;
    match.mUnknown4 = 0;
    fn_801C6D34(lbl_803EBF98, 0, &match, 0, fn_80227F24, 1);
    fn_801C6C0C(lbl_803EBF94, pObject);
    return err;
}

int fn_80228474(Object_80228224 *pObject, int event, Callback_80228474 fn, int key)
{
    Entry_80228474 *pEntry;
    int err = 0;

    pEntry = fn_801C6A20(lbl_803EBF98);
    if (pEntry) {
        pEntry->mUnknown0 = key;
        pEntry->mUnknown4 = event;
        pEntry->mUnknown8 = fn;
        pEntry->mUnknown12 = pObject;
        fn_801C6AA4(lbl_803EBF98, pEntry, 0);
    } else {
        err = fn_801F7C88();
    }
    return err;
}

void fn_802284EC(Object_80228224 *pObject, Callback_80228474 fn)
{
    Match_80228474 match;

    match.mUnknown0 = pObject;
    match.mUnknown4 = fn;
    fn_801C6D34(lbl_803EBF98, 0, &match, 0, fn_80227F24, 1);
}

void fn_80228530(Object_80228224 *pObject)
{
    if (pObject->mUnknown60) {
        fn_801D0470(lbl_803ED670);
        fn_801D0494();
        pObject->mUnknown60(pObject, pObject->mUnknown64);
        pObject->mUnknown68 = 1;
        fn_80228670(pObject);
    }
}

void fn_80228594(Object_80228224 *pObject)
{
    if (pObject->mUnknown72) {
        fn_801DD140(pObject->mUnknown72, 1, pObject->mUnknown69);
    }
}

void fn_802285CC(void)
{
    fn_801CAB30();
    fn_801F8768();
    if (!lbl_803EBF9C) {
        fn_801CE720();
        lbl_803EBF9C = 1;
        fn_801C6D34(lbl_803EBF94, 0, 0, 0, fn_80228028, 1);
        fn_801CE774();
        fn_80228DD4();
        lbl_803EBF9C = 0;
    }
}

int fn_8022863C(void)
{
    return lbl_803EBF9C;
}

Object_80228224 *fn_80228644(void)
{
    return lbl_803ED66C;
}

void fn_8022864C(Object_80228224 *pObject, float a, float b, float c)
{
    pObject->mUnknown32 = a;
    pObject->mUnknown36 = b;
    pObject->mUnknown40 = c;
}

void fn_8022865C(Object_80228224 *pObject, float a, float b)
{
    pObject->mUnknown4 = a;
    pObject->mUnknown8 = b;
}

int fn_80228668(void)
{
    return lbl_803ED670;
}

void fn_80228670(Object_80228224 *pObject)
{
    fn_801D0470(lbl_803ED670);
    fn_801D0F80(pObject->mUnknown76);
}

void fn_802286A8(Object_80228224 *pObject, Callback_80228224 fn, int arg)
{
    pObject->mUnknown60 = fn;
    pObject->mUnknown64 = arg;
}

int fn_802286B4(Object_80228224 *pObject)
{
    return pObject->mUnknown64;
}

void fn_802286BC(Object_80228224 *pObject)
{
    pObject->mUnknown60 = 0;
    pObject->mUnknown64 = 0;
}

void fn_802286CC(Object_80228224 *pObject, int handle, int b)
{
    pObject->mUnknown72 = handle;
    pObject->mUnknown69 = b;
}

void fn_802286D8(Object_80228224 *pObject, float fovy, float aspect, float n, float f)
{
    float t;

    pObject->mUnknown28 = (pObject->mUnknown28 & ~4) | 2;
    pObject->mUnknown204 = fovy;
    pObject->mUnknown208 = aspect;
    pObject->mUnknown232 = n;
    pObject->mUnknown236 = f;
    t = n * fn_801CFD28((int)(fovy * 46603.379f) / 2);
    pObject->mUnknown228 = -t;
    pObject->mUnknown224 = t;
    pObject->mUnknown216 = -t * aspect;
    pObject->mUnknown220 = t * aspect;
}

void fn_80228780(Object_80228224 *pObject, float a)
{
    pObject->mUnknown240 = a * (fn_801CFD28(0x100000) / (pObject->mUnknown224 / pObject->mUnknown232));
}

void fn_802287D4(Object_80228224 *pObject)
{
    fn_801CEC48((unsigned int)pObject->mUnknown4, (unsigned int)pObject->mUnknown20,
                (unsigned int)pObject->mUnknown8, (unsigned int)pObject->mUnknown24);
}
