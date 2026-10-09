#include <dolphin/mtx.h>
#include "game/cu_801444D8.h"
#include "game/Event_801459F0.h"
#include "game/cu_80136B1C.h"
#include "game/fn_801C68FC.h"
#include "game/Object_80146094.h"
#include "game/fn_801EBC18.h"

/* One 0x44-byte entry of the pool at lbl_803EB254. */
struct Entry_80145EFC {
    Mtx44 mMatrix;
    Object_80144CE0 *mUnknown40;
};

struct Object_803ECA10 {
    char mPad000[0x39C];
    float mUnknown39C;
    float mUnknown3A0;
    float mUnknown3A4;
};

extern "C" {
void fn_80145224(void);
void fn_80146FCC(void);
void fn_80146FD8(void);
void fn_80146FDC(Object_80146094 *pObject);
void fn_801475F4(void);
void fn_801478A8(void);
void *fn_801C6A20(void *pool);
void *fn_801C6B4C(void *pool, void *item);
void fn_801C6C0C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
int fn_801C6D34(void *pool, int b, void *ctx, int d, int (*fn)(void *, void *), int f);
void fn_801D03D0(Mtx44 m);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0BCC(int a, int b, int c);
void fn_801D0C58(void *a);
void fn_801D0F80(Mtx44 m);

extern unsigned char lbl_803EB249;
}

static void *lbl_803EB24C = 0;
static int lbl_803EB250 = 0;
static void *lbl_803EB254 = 0;
static Object_803ECA10 *lbl_803ECA10[2];

extern "C" {

static int fn_801459F0(void *pItem, void *pContext)
{
    Event_801459F0 *pEvent = (Event_801459F0 *)pItem;

    if (pEvent->mType != 7) {
        switch (pEvent->mType) {
        case 0:
            fn_80145314(pEvent);
            break;
        case 1:
            fn_801455F8(pEvent);
            break;
        case 4:
            fn_801454DC(pEvent);
            break;
        case 2:
            fn_80145798(pEvent);
            break;
        case 5:
            fn_801458C8(pEvent);
            break;
        }
        Object_80144CE0 *pObject = pEvent->mUnknown18;
        if (pObject != 0 && pObject->mUnknown2B4 == 0 && pObject->mUnknown3B8 == 0) {
            fn_80144E38(pObject);
            pEvent->mUnknown18 = 0;
        }
    }
    return 1;
}

static int fn_80145AC0(void *pItem, void *pContext)
{
    Event_801459F0 *pEvent = (Event_801459F0 *)pItem;

    if (pEvent->mType != 7) {
        pEvent->mUnknown04 = 0;
        switch (pEvent->mType) {
        case 0:
        case 2:
        case 4:
        case 5:
            if (pEvent->mUnknown18 != 0) {
                fn_80144E38(pEvent->mUnknown18);
                pEvent->mUnknown18 = 0;
            }
            break;
        }
    }
    return 1;
}

static int fn_80145B40(void *pItem, void *pContext)
{
    Event_801459F0 *pEvent = (Event_801459F0 *)pItem;

    if (pEvent->mType != 7) {
        pEvent->mUnknown04 = 0;
    }
    return 1;
}

static void fn_80145B5C(void)
{
    Object_80137ABC *pBall = fn_801374BC();
    unsigned int i;

    for (i = 0; i < 2; i++) {
        if (lbl_803ECA10[i] != 0) {
            lbl_803ECA10[i]->mUnknown39C = pBall->mState.mUnknown54.mX;
            lbl_803ECA10[i]->mUnknown3A0 = pBall->mState.mUnknown54.mY;
            lbl_803ECA10[i]->mUnknown3A4 = pBall->mState.mUnknown54.mZ;
        }
    }
}

static void fn_80145BC8(void)
{
    Entry_80145EFC *pDone[64];
    unsigned int count = 0;
    unsigned int i;
    Entry_80145EFC *pEntry;

    for (pEntry = (Entry_80145EFC *)fn_801C6B4C(lbl_803EB254, 0); pEntry != 0;
         pEntry = (Entry_80145EFC *)fn_801C6C84(lbl_803EB254, pEntry)) {
        Object_80144CE0 *pObject = pEntry->mUnknown40;
        if (pObject == 0) {
            pDone[count++] = pEntry;
        } else if (pObject->mUnknown2B4 == 0 && pObject->mUnknown3B8 <= 1) {
            fn_80144E38(pObject);
            pDone[count++] = pEntry;
        }
    }
    for (i = 0; i < count; i++) {
        fn_801C6C0C(lbl_803EB254, pDone[i]);
    }
}

void fn_80145C88(void)
{
    unsigned int i;

    for (i = 0; i < 2; i++) {
        lbl_803ECA10[i] = 0;
    }
    lbl_803EB24C = fn_801C68FC(1, 0, 75, sizeof(Event_801459F0), 0, 0);
    lbl_803EB254 = fn_801C68FC(1, 0, 64, sizeof(Entry_80145EFC), 0, 0);
    fn_80146FCC();
    lbl_803EB249 = 1;
}

void fn_80145D0C(void)
{
    if (lbl_803EB24C != 0) {
        fn_801C69E4(lbl_803EB24C);
        lbl_803EB24C = 0;
    }
    if (lbl_803EB254 != 0) {
        fn_801C69E4(lbl_803EB254);
        lbl_803EB254 = 0;
    }
    fn_80146FD8();
    lbl_803EB249 = 0;
}

void fn_80145D64(int type, int a, int b, int c)
{
    Event_801459F0 *pEvent = (Event_801459F0 *)fn_801C6A20(lbl_803EB24C);

    if (pEvent != 0) {
        pEvent->mType = type;
        pEvent->mUnknown04 = 0;
        pEvent->mUnknown08 = a;
        pEvent->mUnknown18 = 0;
        pEvent->mUnknown0C = b;
        pEvent->mUnknown10 = 0;
        pEvent->mUnknown14 = c;
        pEvent->mUnknown1C = 21;
        fn_801C6AA4(lbl_803EB24C, pEvent, 0);
    }
}

void fn_80145DE4(int type, Object_80137ABC *pBall)
{
    Event_801459F0 *pEvent = (Event_801459F0 *)fn_801C6A20(lbl_803EB24C);

    if (pEvent != 0) {
        pEvent->mType = type;
        pEvent->mUnknown04 = 0;
        pEvent->mUnknown08 = (int)pBall->mpUnknown00 + 0x20;
        pEvent->mUnknown18 = 0;
        pEvent->mUnknown0C = 0;
        pEvent->mUnknown10 = pBall;
        pEvent->mUnknown14 = 0;
        pEvent->mUnknown1C = 21;
        fn_801C6AA4(lbl_803EB24C, pEvent, 0);
    }
}

void fn_80145E64(void)
{
    if (lbl_803EB24C != 0) {
        fn_801C6D34(lbl_803EB24C, 0, 0, 0, fn_801459F0, 1);
    }
    fn_80145BC8();
    fn_80145B5C();
    fn_801478A8();
    fn_80145224();
}

void fn_80145EB8(void)
{
    if (lbl_803EB24C != 0) {
        fn_801C6D34(lbl_803EB24C, 0, 0, 0, fn_80145B40, 1);
    }
}

void fn_80145EFC(int a, float *pPos, float *pRot, Source_80144CE0 *pSource)
{
    Args_80144CE0 args;
    Mtx44 m;
    Entry_80145EFC *pEntry;

    if (lbl_803EB254 == 0) {
        return;
    }
    pEntry = (Entry_80145EFC *)fn_801C6A20(lbl_803EB254);
    if (pEntry == 0) {
        return;
    }
    fn_801D03D0(m);
    m[2][3] = m[1][3] = m[0][3] = 0.0f;
    fn_801D0508();
    fn_801D0C58(pPos);
    if (pRot != 0) {
        Angles_801EBC18 v;
        fn_801EBC18(&v, pRot);

        fn_801D0BCC(v.mUnknown8, v.mUnknown4, v.mUnknown0);
    }
    fn_801D0F80(pEntry->mMatrix);
    fn_801D0544();
    args.mUnknown0C = 0;
    args.mUnknown10 = 0;
    args.mUnknown04 = &pEntry->mMatrix;
    args.mUnknown08 = &m;
    args.mUnknown00 = a;
    pEntry->mUnknown40 = fn_80144CE0(&args, 0, pSource);
    fn_801C6AA4(lbl_803EB254, pEntry, 0);
}

void fn_80145FE4(void)
{
    if (lbl_803EB24C != 0) {
        fn_801C6D34(lbl_803EB24C, 0, 0, 0, fn_80145AC0, 1);
    }
    fn_801475F4();
}

void fn_8014602C(void)
{
    fn_80145BC8();
}

void fn_8014604C(void)
{
    if (lbl_803EB24C != 0) {
        fn_801C6D34(lbl_803EB24C, 0, 0, 0, fn_80145AC0, 1);
    }
    fn_801475F4();
}

void fn_80146094(Object_80146094 *pObject)
{
    pObject->mUnknown568 = 0;
    pObject->mUnknown57C = 0;
    pObject->mUnknown5A4 = 0;
    pObject->mUnknown5A8 = 0;
    fn_80146FDC(pObject);
    pObject->mUnknown5A0 = 0;
    pObject->mUnknown580 = 1.0f;
    pObject->mUnknown588 = 1.0f;
    pObject->mUnknown584 = 1.0f;
    pObject->mUnknown590 = 1.0f;
    pObject->mUnknown598 = 1.0f;
    pObject->mUnknown594 = 1.0f;
}

void fn_801460FC(Object_80146094 *pObject, float a, float b, float c)
{
    pObject->mUnknown568 = 1;
    pObject->mUnknown56C = a;
    pObject->mUnknown570 = b;
    pObject->mUnknown574 = c;
}

void fn_80146114(Object_80146094 *pObject)
{
    pObject->mUnknown568 = 0;
    pObject->mUnknown56C = 1.0f;
    pObject->mUnknown570 = 1.0f;
    pObject->mUnknown574 = 1.0f;
}
}
