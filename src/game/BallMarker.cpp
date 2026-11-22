/* Ball marker: the flat model drawn on the ground under the ball (or where it will
   land), growing as the ball rises; one marker per ball in the three-ball mode. */

#include <dolphin/gx/GXPixel.h>
#include "engine/viewport.h"
#include "game/Ball.h"
#include "game/ResLoad.h"
#include "game/fn_800B65A0.h"
#include "game/BallPhysics.h"

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

static BallMarkerTable_t _BallMarker_Table = {0};

extern "C" {
int fn_800BA6F8(void);
int fn_800BA864(void);
int fn_800C47C4(void);
int BallStateGet(Ball_t *pBall, int *pOut);
int fn_801486A0(void);
int fn_801784C4(void);
int ConGetCurrentContext(void);
void MatSetStack(int a);
void MatPush(void);
void MatPop(void);
void MatRotX(int a);
void MatTranslate(void *p);
void MatScale(float a);
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
void ModelObjReset(void *p);
void ModelObjSetModel(void *p, int a);
void ModelObjSetShader(void *p, const char *pName);
void ModelObjStoreMatrix(void *p, int a);
void ModelObjDraw(void *p, int a);
void ModelObjSetParamNop(void *p, int a);
void ModelObjSetAmbientColor(void *p, int a, float b, float c, float d, float e);
void ModelObjRelocateModelRes(int a);
void BallMarkerObjInit(BallMarkerObj_t *pObject, int *pArgs);
void BallMarkerObjFree(BallMarkerObj_t *pObject);
int BallMarkerObjDraw(BallMarkerObj_t *pObject);

// Refreshes marker entry index from ball index: its position, whether it
// is shown, and a scale that grows with the ball's height.
void BallMarkerUpdateEntry(int index)
{
    BallMarkerEntry_t *pEntry = &_BallMarker_Table.mEntries[index];
    Ball_t *pBall;

    pEntry->mEnabled = 0;
    pBall = BallGet(index);
    BallStateGet(pBall, 0);
    if (fn_800BA6F8() != 0 && fn_800BA864() != 0) {
        BallGetPosition(pBall, &pEntry->mPosition);
        pEntry->mEnabled = 1;
    } else if ((fn_801486A0() == 1 || fn_800B65A0(0) != 0xFF || fn_800B65A0(1) != 0xFF)
               && BallGetSpinMode(pBall) != 0 && BallGetLandingPoint(pBall, &pEntry->mPosition) != 0) {
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
        _BallMarker_Table.mCount = 3;
    } else {
        _BallMarker_Table.mCount = 1;
    }
    _BallMarker_Table.mpObject = (BallMarkerObj_t *)ObjNewInList(handle, 18, 0, &desc);
    ObjSetPriority(handle, _BallMarker_Table.mpObject, 3);
}

void BallMarkerDestroy(int handle)
{
    if (_BallMarker_Table.mpObject != 0) {
        ObjRemoveFromList(handle, _BallMarker_Table.mpObject);
        VptTrashObject((int)_BallMarker_Table.mpObject);
        _BallMarker_Table.mpObject = 0;
    }
    _BallMarker_Table.mCount = 0;
    BallMarkerUnregister();
}

void BallMarkerObjInit(BallMarkerObj_t *pObject, int *pArgs)
{
    pObject->mUnknown0C = pObject->mUnknown08 = pObject->mUnknown04 = 0.0f;
    pObject->mpUnknown14 = (void *)pArgs[0];
    pObject->mUnknownD8 = ResLoad(pObject->mpUnknown14, 10, 1);
    BallMarkerUpdateEntry(0);
    pObject->mUnknown10C = _BallMarker_Table.mEntries[0].mEnabled;
    ModelObjRelocateModelRes(pObject->mUnknownD8);
    fn_80235588(pObject->mUnknown18, 6);
    ModelObjSetModel(pObject->mUnknown18, pObject->mUnknownD8);
    ModelObjSetParamNop(pObject->mUnknown18, 3);
    fn_802353D8(pObject->mUnknown18, 0x400008);
    ModelObjSetShader(pObject->mUnknown18, "Flat");
}

void BallMarkerObjFree(BallMarkerObj_t *pObject)
{
    ModelObjReset(pObject->mUnknown18);
    if (pObject->mUnknownD8 != 0) {
        ResUnLoad(pObject->mpUnknown14, 10);
    }
}

int BallMarkerObjDraw(BallMarkerObj_t *pObject)
{
    if (pObject->mUnknownD8 != 0 && pObject->mUnknown10C != 0) {
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
        TMRenderBindTexture(0, 0, 0);
        for (unsigned int i = 0; i < _BallMarker_Table.mCount; i++) {
            if (_BallMarker_Table.mEntries[i].mEnabled != 0) {
                if (fn_801486A0() == 1 && BallGetCurrentIndex() == i) {
                    ModelObjSetAmbientColor(pObject->mUnknown18, ConGetCurrentContext(),
                               0.341796875f, 0.0f, 0.0f, 1.0f);
                } else {
                    ModelObjSetAmbientColor(pObject->mUnknown18, ConGetCurrentContext(),
                               0.390625f, 0.19921875f, 0.0f, 1.0f);
                }
                MatSetStack(VptGetMatrixStack());
                MatPush();
                MatTranslate(&_BallMarker_Table.mEntries[i].mPosition);
                MatRotX(0x400000);
                MatScale(_BallMarker_Table.mEntries[i].mScale);
                ModelObjStoreMatrix(pObject->mUnknown18, ConGetCurrentContext());
                MatSetStack(VptGetMatrixStack());
                MatPop();
                ModelObjDraw(pObject->mUnknown18, ConGetCurrentContext());
            }
        }
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    }
    return 0;
}

void BallMarkerUpdate(void)
{
    if (_BallMarker_Table.mpObject != 0) {
        _BallMarker_Table.mpObject->mUnknown10C = 0;
        for (unsigned int i = 0; i < _BallMarker_Table.mCount; i++) {
            BallMarkerUpdateEntry(i);
            _BallMarker_Table.mpObject->mUnknown10C |= _BallMarker_Table.mEntries[i].mEnabled;
        }
    }
}
}
