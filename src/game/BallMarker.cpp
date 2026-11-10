/* Ball marker: the flat model drawn on the ground under the ball (or where it will
   land), growing as the ball rises; one marker per ball in the three-ball mode. */

#include <dolphin/gx/GXPixel.h>
#include "engine/viewport.h"
#include "game/Ball.h"
#include "game/ResLoad.h"
#include "game/fn_800B65A0.h"
#include "game/fn_8013AD94.h"

struct BallMarkerObj_t {
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

struct BallMarkerEntry_t {
    Vector_80039F5C mPosition;
    float mScale;
    unsigned char mEnabled;
};

struct BallMarkerTable_t {
    unsigned int mCount;
    BallMarkerEntry_t mEntries[3];
    BallMarkerObj_t *mpObject;
};

extern "C" {
extern BallMarkerTable_t lbl_802E989C;
int fn_800BA6F8(void);
int fn_800BA864(void);
int fn_800C47C4(void);
int BallStateGet(Ball_t *pBall, int *pOut);
int fn_801486A0(void);
int fn_801784C4(void);
int ConGetCurrentContext(void);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D08FC(int a);
void fn_801D0C58(void *p);
void fn_801D0CFC(float a);
int ObjNewType_(int type, int size, int count,
                void (*pCreate)(BallMarkerObj_t *, int *),
                void (*pDestroy)(BallMarkerObj_t *));
int ObjDelType(int type);
void ObjSetListObjFunc(int handle, int type, int a, int (*pCallback)(BallMarkerObj_t *));
int ObjNewInList(int handle, int type, int a, int *pDesc);
void ObjRemoveFromList(int handle, BallMarkerObj_t *pObject);
void ObjSetPriority(int handle, BallMarkerObj_t *pObject, int a);
void TMRenderBindTexture(int a, int b, int c);
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
void BallMarkerObjInit(BallMarkerObj_t *pObject, int *pArgs);
void BallMarkerObjFree(BallMarkerObj_t *pObject);
int BallMarkerObjDraw(BallMarkerObj_t *pObject);

// Refreshes marker entry index from ball index: its position, whether it
// is shown, and a scale that grows with the ball's height.
void BallMarkerUpdateEntry(int index)
{
    BallMarkerEntry_t *pEntry = &lbl_802E989C.mEntries[index];
    Ball_t *pBall;

    pEntry->mEnabled = 0;
    pBall = BallGet(index);
    BallStateGet(pBall, 0);
    if (fn_800BA6F8() != 0 && fn_800BA864() != 0) {
        BallGetPosition(pBall, &pEntry->mPosition);
        pEntry->mEnabled = 1;
    } else if ((fn_801486A0() == 1 || fn_800B65A0(0) != 0xFF || fn_800B65A0(1) != 0xFF)
               && fn_8013AD94(pBall) != 0 && BallGetLandingPoint(pBall, &pEntry->mPosition) != 0) {
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

        BallGetPosition(pBall, &ball);
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

void BallMarkerRegister(int handle)
{
    ObjNewType_(18, sizeof(BallMarkerObj_t), 1, BallMarkerObjInit, BallMarkerObjFree);
    ObjSetListObjFunc(handle, 18, 0, BallMarkerObjDraw);
}

void BallMarkerUnregister(void)
{
    VptFlushObjectTrashSync();
    ObjDelType(18);
}

void BallMarkerCreate(int handle)
{
    int data = fn_800C47C4();
    int desc;

    BallMarkerRegister(handle);
    desc = data;
    if (fn_801486A0() == 1) {
        lbl_802E989C.mCount = 3;
    } else {
        lbl_802E989C.mCount = 1;
    }
    lbl_802E989C.mpObject = (BallMarkerObj_t *)ObjNewInList(handle, 18, 0, &desc);
    ObjSetPriority(handle, lbl_802E989C.mpObject, 3);
}

void BallMarkerDestroy(int handle)
{
    if (lbl_802E989C.mpObject != 0) {
        ObjRemoveFromList(handle, lbl_802E989C.mpObject);
        VptTrashObject((int)lbl_802E989C.mpObject);
        lbl_802E989C.mpObject = 0;
    }
    lbl_802E989C.mCount = 0;
    BallMarkerUnregister();
}

void BallMarkerObjInit(BallMarkerObj_t *pObject, int *pArgs)
{
    pObject->mUnknown0C = pObject->mUnknown08 = pObject->mUnknown04 = 0.0f;
    pObject->mpUnknown14 = (void *)pArgs[0];
    pObject->mUnknownD8 = ResLoad(pObject->mpUnknown14, 10, 1);
    BallMarkerUpdateEntry(0);
    pObject->mUnknown10C = lbl_802E989C.mEntries[0].mEnabled;
    fn_80235DB8(pObject->mUnknownD8);
    fn_80235588(pObject->mUnknown18, 6);
    fn_80235630(pObject->mUnknown18, pObject->mUnknownD8);
    fn_80235C48(pObject->mUnknown18, 3);
    fn_802353D8(pObject->mUnknown18, 0x400008);
    fn_8023570C(pObject->mUnknown18, "Flat");
}

void BallMarkerObjFree(BallMarkerObj_t *pObject)
{
    fn_802355E4(pObject->mUnknown18);
    if (pObject->mUnknownD8 != 0) {
        ResUnLoad(pObject->mpUnknown14, 10);
    }
}

int BallMarkerObjDraw(BallMarkerObj_t *pObject)
{
    if (pObject->mUnknownD8 != 0 && pObject->mUnknown10C != 0) {
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
        TMRenderBindTexture(0, 0, 0);
        for (unsigned int i = 0; i < lbl_802E989C.mCount; i++) {
            if (lbl_802E989C.mEntries[i].mEnabled != 0) {
                if (fn_801486A0() == 1 && BallGetCurrentIndex() == i) {
                    fn_80235C90(pObject->mUnknown18, ConGetCurrentContext(),
                               0.341796875f, 0.0f, 0.0f, 1.0f);
                } else {
                    fn_80235C90(pObject->mUnknown18, ConGetCurrentContext(),
                               0.390625f, 0.19921875f, 0.0f, 1.0f);
                }
                fn_801D0470(VptGetMatrixStack());
                fn_801D04C4();
                fn_801D0C58(&lbl_802E989C.mEntries[i].mPosition);
                fn_801D08FC(0x400000);
                fn_801D0CFC(lbl_802E989C.mEntries[i].mScale);
                fn_80235740(pObject->mUnknown18, ConGetCurrentContext());
                fn_801D0470(VptGetMatrixStack());
                fn_801D0544();
                fn_80235764(pObject->mUnknown18, ConGetCurrentContext());
            }
        }
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    }
    return 0;
}

void BallMarkerUpdate(void)
{
    if (lbl_802E989C.mpObject != 0) {
        lbl_802E989C.mpObject->mUnknown10C = 0;
        for (unsigned int i = 0; i < lbl_802E989C.mCount; i++) {
            BallMarkerUpdateEntry(i);
            lbl_802E989C.mpObject->mUnknown10C |= lbl_802E989C.mEntries[i].mEnabled;
        }
    }
}
}
