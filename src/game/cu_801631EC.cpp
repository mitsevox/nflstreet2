#include <dolphin/gx/GXPixel.h>
#include "engine/cu_80227F14.h"
#include "game/cu_80136B1C.h"
#include "game/fn_801EF390.h"

struct Object_80163358 {
    unsigned char mUnknown00[4];
    float mUnknown04;
    float mUnknown08;
    float mUnknown0C;
    unsigned char mUnknown10[4];
    void *mpUnknown14;
    unsigned char mUnknown18[192];
    int mUnknownD8;
    unsigned char mUnknownDC[48];
    unsigned char mUnknown10C;
};

struct Entry_802E98A0 {
    Vector_80039F5C mPosition;
    float mScale;
    unsigned char mEnabled;
};

struct State_802E989C {
    unsigned int mCount;
    Entry_802E98A0 mEntries[3];
    Object_80163358 *mpObject;
};

extern "C" {
extern State_802E989C lbl_802E989C;
int fn_800B65A0(int side);
int fn_800BA6F8(void);
int fn_800BA864(void);
int fn_800C47C4(void);
int fn_8013AD94(Object_80137ABC *pBall);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_801486A0(void);
int fn_801784C4(void);
int fn_801C657C(void);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D08FC(int a);
void fn_801D0C58(void *p);
void fn_801D0CFC(float a);
int fn_801DCF0C(int type, int size, int count,
                void (*pCreate)(Object_80163358 *, int *),
                void (*pDestroy)(Object_80163358 *));
void fn_801DCF8C(int type);
void fn_801DD0C8(int handle, int type, int a, int (*pCallback)(Object_80163358 *));
int fn_801DD268(int handle, int type, int a, int *pDesc);
void fn_801DD320(int handle, Object_80163358 *pObject);
void fn_801DD3AC(int handle, Object_80163358 *pObject, int a);
void fn_80210814(int a, int b, int c);
void fn_802353D8(void *p, int flags);
void fn_80235588(void *p, int a);
void fn_802355E4(void *p);
void fn_80235630(void *p, int a);
void fn_8023570C(void *p, const char *pName);
void fn_80235740(void *p, int a);
void fn_80235764(void *p, int a);
void fn_80235C48(void *p, int a);
void fn_80235C90(void *p, int a, float b, float c, float d, float e);
void fn_80235DB8(int a);
void fn_80163358(Object_80163358 *pObject, int *pArgs);
void fn_80163414(Object_80163358 *pObject);
int fn_8016345C(Object_80163358 *pObject);

// Refreshes marker entry index from ball index: its position, whether it
// is shown, and a scale that grows with the ball's height.
void fn_80163074(int index)
{
    Entry_802E98A0 *pEntry = &lbl_802E989C.mEntries[index];
    Object_80137ABC *pBall;

    pEntry->mEnabled = 0;
    pBall = fn_80137ABC(index);
    fn_8013BA58(pBall, 0);
    if (fn_800BA6F8() != 0 && fn_800BA864() != 0) {
        fn_80137D58(pBall, &pEntry->mPosition);
        pEntry->mEnabled = 1;
    } else if ((fn_801486A0() == 1 || fn_800B65A0(0) != 0xFF || fn_800B65A0(1) != 0xFF)
               && fn_8013AD94(pBall) != 0 && fn_80138064(pBall, &pEntry->mPosition) != 0) {
        pEntry->mEnabled = 1;
    }
    pEntry->mPosition.mZ = 0.0f;
    if (fn_801784C4() != 0) {
        pEntry->mPosition.mX = -pEntry->mPosition.mX;
        pEntry->mPosition.mY = -pEntry->mPosition.mY;
    }
    if (pEntry->mEnabled != 0) {
        Vector_80039F5C ball;
        float height;

        fn_80137D58(pBall, &ball);
        height = ball.mZ;
        if (height <= 3.0f) {
            pEntry->mScale = 1.0f;
        } else if (height >= 14.0f) {
            pEntry->mScale = 5.25f;
        } else {
            float t = (height - 3.0f) / 11.0f;

            pEntry->mScale = t * 4.25f + 1.0f;
        }
    }
}

void fn_801631EC(int handle)
{
    fn_801DCF0C(18, sizeof(Object_80163358), 1, fn_80163358, fn_80163414);
    fn_801DD0C8(handle, 18, 0, fn_8016345C);
}

void fn_8016324C(void)
{
    fn_80228E18();
    fn_801DCF8C(18);
}

void fn_80163274(int handle)
{
    int data = fn_800C47C4();
    int desc;

    fn_801631EC(handle);
    desc = data;
    if (fn_801486A0() == 1) {
        lbl_802E989C.mCount = 3;
    } else {
        lbl_802E989C.mCount = 1;
    }
    lbl_802E989C.mpObject = (Object_80163358 *)fn_801DD268(handle, 18, 0, &desc);
    fn_801DD3AC(handle, lbl_802E989C.mpObject, 3);
}

void fn_80163300(int handle)
{
    if (lbl_802E989C.mpObject != 0) {
        fn_801DD320(handle, lbl_802E989C.mpObject);
        fn_80228D58((int)lbl_802E989C.mpObject);
        lbl_802E989C.mpObject = 0;
    }
    lbl_802E989C.mCount = 0;
    fn_8016324C();
}

void fn_80163358(Object_80163358 *pObject, int *pArgs)
{
    pObject->mUnknown0C = pObject->mUnknown08 = pObject->mUnknown04 = 0.0f;
    pObject->mpUnknown14 = (void *)pArgs[0];
    pObject->mUnknownD8 = fn_801EF390(pObject->mpUnknown14, 10, 1);
    fn_80163074(0);
    pObject->mUnknown10C = lbl_802E989C.mEntries[0].mEnabled;
    fn_80235DB8(pObject->mUnknownD8);
    fn_80235588(pObject->mUnknown18, 6);
    fn_80235630(pObject->mUnknown18, pObject->mUnknownD8);
    fn_80235C48(pObject->mUnknown18, 3);
    fn_802353D8(pObject->mUnknown18, 0x400008);
    fn_8023570C(pObject->mUnknown18, "Flat");
}

void fn_80163414(Object_80163358 *pObject)
{
    fn_802355E4(pObject->mUnknown18);
    if (pObject->mUnknownD8 != 0) {
        fn_801F010C(pObject->mpUnknown14, 10);
    }
}

int fn_8016345C(Object_80163358 *pObject)
{
    if (pObject->mUnknownD8 != 0 && pObject->mUnknown10C != 0) {
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
        fn_80210814(0, 0, 0);
        for (unsigned int i = 0; i < lbl_802E989C.mCount; i++) {
            if (lbl_802E989C.mEntries[i].mEnabled != 0) {
                if (fn_801486A0() == 1 && fn_801374D4() == i) {
                    fn_80235C90(pObject->mUnknown18, fn_801C657C(),
                               0.341796875f, 0.0f, 0.0f, 1.0f);
                } else {
                    fn_80235C90(pObject->mUnknown18, fn_801C657C(),
                               0.390625f, 0.19921875f, 0.0f, 1.0f);
                }
                fn_801D0470(fn_80228668());
                fn_801D04C4();
                fn_801D0C58(&lbl_802E989C.mEntries[i].mPosition);
                fn_801D08FC(0x400000);
                fn_801D0CFC(lbl_802E989C.mEntries[i].mScale);
                fn_80235740(pObject->mUnknown18, fn_801C657C());
                fn_801D0470(fn_80228668());
                fn_801D0544();
                fn_80235764(pObject->mUnknown18, fn_801C657C());
            }
        }
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    }
    return 0;
}

void fn_801635E8(void)
{
    if (lbl_802E989C.mpObject != 0) {
        lbl_802E989C.mpObject->mUnknown10C = 0;
        for (unsigned int i = 0; i < lbl_802E989C.mCount; i++) {
            fn_80163074(i);
            lbl_802E989C.mpObject->mUnknown10C |= lbl_802E989C.mEntries[i].mEnabled;
        }
    }
}
}
