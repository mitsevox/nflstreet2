#include "engine/cu_80227F14.h"
#include "game/Camera_8013F738.h"
#include "game/EaseVector_8013C9A4.h"
#include "game/cu_80136B1C.h"
#include "game/cu_8013BB18.h"

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

/* Object a camera follows for target kinds 3 to 5 (passed as the target
   reference word). */
struct Target_8013BDC0 {
    char mPad00[4];
    Vector_80039F5C mPos;
    char mPad10[0x14];
    int mUnknown24;
};

/* Per-id handlers returned by fn_80141054. */
struct Handlers_80141054 {
    void (*mUnknown00)(Camera_8013F738 *pCamera, Desc_8013C340 *pDesc);
    void (*mUnknown04)(Camera_8013F738 *pCamera);
};

struct TypeEntry_802DBD7C {
    void *mpType;
    int mSize;
    int mUnknown08;
};

extern "C" {
extern char lbl_802F4884[];
extern char lbl_802F4890[];
extern Type_802DBD24 lbl_802CC83C;
extern char lbl_8031BDD4[];

void fn_8009BD2C(Object_80039F5C *p, int *pRef);
Handlers_80141054 *fn_80141054(int id);
void fn_8014106C(int id, int mode, float *pA, float *pB);
int fn_801486A0(void);
void fn_801527B8(void *p, Vector_80039F5C *pOut);
int fn_801784C4(void);
void fn_801C3918(void *p, Camera_8013F738 *pCamera);
void fn_801C3A10(Camera_8013F738 *pCamera, float value);
void fn_801C3AD8(Camera_8013F738 *pCamera, int a);
void fn_801C3B74(Camera_8013F738 *pCamera);
void fn_801C3B78(Camera_8013F738 *pCamera);
void fn_801C3C4C(void *p, Camera_8013F738 *pCamera);
void fn_801C3C6C(Camera_8013F738 *pCamera, Vector_80039F5C *pTarget);
void fn_801C3C74(Camera_8013F738 *pCamera, int a, int b);
void fn_801C3C80(Camera_8013F738 *pCamera);
void fn_801C3CE8(Camera_8013F738 *pCamera, int a);
void fn_801C3D98(Camera_8013F738 *pCamera);
void fn_801C3D9C(Camera_8013F738 *pCamera);
void fn_801C3E54(Camera_8013F738 *pCamera);
void fn_801C3E84(void *p, Camera_8013F738 *pCamera);
void fn_801C3EA4(Camera_8013F738 *pCamera, float x, float y, float z);
void fn_801C3EC0(Camera_8013F738 *pCamera, float x, float y, float z);
void fn_801C3ED0(Camera_8013F738 *pCamera, int a, int b, int c);
void fn_801C3EEC(Camera_8013F738 *pCamera, int a, int b, int c);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
void fn_801D0470(int a);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D08FC(int angle);
void fn_801D0ADC(int angle);
void fn_801D0C58(Vector_80039F5C *pPos);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_80227CC0(Vector_80039F5C *pOut, Vector_80039F5C *pIn);

void fn_8013CEB8(Interp_8013CC14 *pInterp, int steps);
}

extern "C" {
Type_802DBD24 lbl_802DBD24 = { fn_8013C868, fn_8013C90C, fn_8013C954 };

/* Base camera kind for each camera id. */
int lbl_802DBD30[19] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 4, 4, 0 };

TypeEntry_802DBD7C lbl_802DBD7C[5] = {
    { lbl_802F4890, 0x8C, 0 },
    { lbl_802F4884, 0x94, 0 },
    { &lbl_802DBD24, 0xF58, 0 },
    { &lbl_802CC83C, 0xF60, 0 },
    { 0, 0, 0 },
};
}

static inline void ZeroVector(Vector_80039F5C *pVec)
{
    pVec->mX = pVec->mY = pVec->mZ = 0.0f;
}

extern "C" {

unsigned char fn_8013BB18(Camera_8013F738 *pCamera)
{
    return ((pCamera->mUnknown94 >> 3) & 1) ^ fn_801784C4();
}

void fn_8013BB54(Vector_80039F5C *pVec)
{
    pVec->mX = -pVec->mX;
    pVec->mY = -pVec->mY;
}

void fn_8013BB70(int *pAngles)
{
    pAngles[2] = (pAngles[2] - 0x800000) & 0xFFFFFF;
}

void fn_8013BB84(Camera_8013F738 *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
        if (pCamera->mUnknown94 & 4) {
            fn_8013C6F0(pCamera);
            pCamera->mUnknown94 &= ~4;
        } else {
            Vector_80039F5C pos;

            fn_8013BDC0(pCamera->mUnknownA8, pCamera->mUnknownAC, &pCamera->mUnknownB8);
            fn_8013BC4C(pCamera, &pCamera->mUnknownB8, &pos);
            fn_801C3EC0(pCamera, pos.mX, pos.mY, pos.mZ);
        }
        break;
    case 1:
        fn_8013BDC0(pCamera->mUnknownA8, pCamera->mUnknownAC, &pCamera->mUnknownB8);
        fn_801C3C6C(pCamera, &pCamera->mUnknownB8);
        if (pCamera->mUnknown94 & 4) {
            fn_8013C6F0(pCamera);
            pCamera->mUnknown94 &= ~4;
        }
        break;
    }
}

void fn_8013BC4C(Camera_8013F738 *pCamera, Vector_80039F5C *pTarget, Vector_80039F5C *pOut)
{
    Vector_80039F5C offset;
    Vector_80039F5C target;

    offset.mX = pCamera->mUnknownC4;
    offset.mY = pCamera->mUnknownC8;
    offset.mZ = pCamera->mUnknownCC;
    target.mX = pTarget->mX;
    target.mY = pTarget->mY;
    target.mZ = pTarget->mZ;
    if (fn_8013BB18(pCamera)) {
        fn_8013BB54(&offset);
    }
    target.mZ = 0.0f;
    fn_8022765C(pOut, &target, &offset);
    if (pCamera->mUnknown94 & 0x10) {
        float x[2];
        float y[2];

        fn_8014106C(pCamera->mUnknown9C, pCamera->mUnknownA0, x, y);
        pOut->mX = CLAMP(pOut->mX, x[0], x[1]);
        pOut->mY = CLAMP(pOut->mY, y[0], y[1]);
        pOut->mZ = CLAMP(pOut->mZ, 2.5f, 100.0f);
    }
}

void fn_8013BD98(Camera_8013F738 *pCamera, Vector_80039F5C *pOut)
{
    if (pCamera->mUnknown98 == 0) {
        pOut->mX = pCamera->mUnknown2C;
        pOut->mY = pCamera->mUnknown30;
        pOut->mZ = pCamera->mUnknown34;
    }
}

/* Position of a camera target: kind 1 is a ball index, 2 a packed object
   reference, 3 to 5 a Target_8013BDC0 pointer. */
void fn_8013BDC0(int kind, int ref, Vector_80039F5C *pOut)
{
    switch (kind) {
    case 1: {
        Object_80137ABC *pBall = fn_80137ABC(ref);
        Object_80039F5C *pObject = fn_80137AD0(pBall);

        if (pObject == 0) {
            fn_80137D58(pBall, pOut);
        } else {
            pOut->mX = pObject->mMotion.mPos.mX;
            pOut->mY = pObject->mMotion.mPos.mY;
            pOut->mZ = pObject->mMotion.mPos.mZ;
        }
        if (fn_801784C4()) {
            fn_8013BB54(pOut);
        }
        break;
    }
    case 2: {
        Object_80039F5C *pObject = fn_8009BCE8(&ref);

        pOut->mX = pObject->mMotion.mPos.mX;
        pOut->mY = pObject->mMotion.mPos.mY;
        pOut->mZ = pObject->mMotion.mPos.mZ;
        if (fn_801784C4()) {
            fn_8013BB54(pOut);
        }
        break;
    }
    case 3:
        pOut->mX = ((Target_8013BDC0 *)ref)->mPos.mX;
        pOut->mY = ((Target_8013BDC0 *)ref)->mPos.mY;
        pOut->mZ = ((Target_8013BDC0 *)ref)->mPos.mZ;
        break;
    case 4:
    case 5:
        pOut->mX = ((Target_8013BDC0 *)ref)->mPos.mX;
        pOut->mY = ((Target_8013BDC0 *)ref)->mPos.mY;
        pOut->mZ = ((Target_8013BDC0 *)ref)->mPos.mZ;
        break;
    case 0:
        ZeroVector(pOut);
        break;
    case 6:
        break;
    case 7:
        fn_801527B8(lbl_8031BDD4, pOut);
        if (fn_801784C4()) {
            fn_8013BB54(pOut);
        }
        break;
    }
}

void fn_8013BEE0(int kind, int ref, int *pAngles)
{
    pAngles[0] = pAngles[1] = pAngles[2] = 0;
    switch (kind) {
    case 1:
        break;
    case 2:
        fn_8009BCE8(&ref);
        break;
    case 3:
        pAngles[2] = ((Target_8013BDC0 *)ref)->mUnknown24;
        break;
    case 4:
    case 5:
        break;
    }
}

void fn_8013BF40(Camera_8013F738 *pCamera, int *pAngles)
{
    Vector_80039F5C from;
    Vector_80039F5C to;
    int angles[3];
    float dz;
    float c;

    if ((pCamera->mUnknown94 & 0x20) || pCamera->mUnknownA8 == 0) {
        pAngles[0] = pCamera->mUnknownD0;
        pAngles[1] = pCamera->mUnknownD4;
        pAngles[2] = pCamera->mUnknownD8;
        if (fn_8013BB18(pCamera)) {
            if (pCamera->mUnknown98 == 0) {
                fn_8013BB70(pAngles);
            } else {
                pAngles[1] += 0x800000;
            }
        }
        return;
    }
    if (pCamera->mUnknown98 == 0) {
        fn_8013BD98(pCamera, &from);
        fn_8013BDC0(pCamera->mUnknownA8, pCamera->mUnknownAC, &to);
        pAngles[2] = fn_801CFE40(to.mX - from.mX, to.mY - from.mY);
        pAngles[2] += pCamera->mUnknownD8;
        pAngles[1] = 0;
        pAngles[1] += pCamera->mUnknownD4;
        dz = to.mZ - from.mZ;
        c = fn_801CFB94(pAngles[2]);
        pAngles[0] = fn_801CFE40(dz, c * (to.mY - from.mY) + fn_801CFB18(pAngles[2]) * (to.mX - from.mX));
        pAngles[0] += pCamera->mUnknownD0;
    } else {
        angles[0] = angles[1] = angles[2] = 0;
        fn_8013BEE0(pCamera->mUnknownA8, pCamera->mUnknownAC, angles);
        pAngles[0] = angles[0];
        pAngles[1] = angles[2];
        if (fn_8013BB18(pCamera)) {
            pAngles[0] += pCamera->mUnknownD0;
            pAngles[1] -= pCamera->mUnknownD4;
        } else {
            pAngles[0] += pCamera->mUnknownD0;
            pAngles[1] += pCamera->mUnknownD4;
        }
    }
    pAngles[0] &= 0xFFFFFF;
}

void fn_8013C120(Camera_8013F738 *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
    case 4:
        fn_801C3CE8(pCamera, 0);
        pCamera->mUnknown5C = pCamera->mUnknown60 = pCamera->mUnknown64 = 0.1f;
        pCamera->mUnknown68 = pCamera->mUnknown6C = pCamera->mUnknown70 = 0.05f;
        pCamera->mUnknown80 = pCamera->mUnknown84 = pCamera->mUnknown88 = 0x200000;
        pCamera->mUnknown74 = pCamera->mUnknown78 = pCamera->mUnknown7C = 0x400000;
        break;
    case 1:
        fn_801C3AD8(pCamera, 0);
        break;
    }
}

void fn_8013C1C8(Camera_8013F738 *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
        fn_801C3D98(pCamera);
        break;
    case 1:
        fn_801C3B74(pCamera);
        break;
    case 4:
        break;
    }
}

void fn_8013C204(Camera_8013F738 *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
        fn_801C3D9C(pCamera);
        break;
    case 1:
        fn_801C3B78(pCamera);
        break;
    case 4:
        break;
    }
    fn_801C3A10(pCamera, 4.0f);
}

void fn_8013C260(Camera_8013F738 *pCamera, int *pAngles)
{
    switch (pCamera->mUnknown98) {
    case 0:
        fn_801C3EEC(pCamera, pAngles[0], pAngles[1], pAngles[2]);
        break;
    case 1:
        fn_801C3C74(pCamera, pAngles[0], pAngles[1]);
        break;
    case 4:
        break;
    }
}

void fn_8013C2B4(Camera_8013F738 *pCamera, int a, int b, int c)
{
    if (pCamera->mUnknown98 == 0 || pCamera->mUnknown98 == 1) {
        fn_8013BB84(pCamera);
    }
    fn_8013C824(pCamera, 3, 0);
    if (pCamera->mUnknown98 == 0 || pCamera->mUnknown98 == 1) {
        int angles[3];

        fn_8013BF40(pCamera, angles);
        fn_8013C260(pCamera, angles);
    }
    fn_8013C204(pCamera);
}

void fn_8013C328(Camera_8013F738 *pCamera, int kind, int ref)
{
    pCamera->mUnknownA8 = kind;
    pCamera->mUnknownAC = ref;
    pCamera->mUnknown94 |= 2;
}

void fn_8013C340(Desc_8013C340 *pDesc)
{
    pDesc->mUnknown00 = 0;
    pDesc->mUnknown04 = 0;
    fn_8009BD2C(0, &pDesc->mUnknown08);
    pDesc->mUnknown0C = 0;
}

void fn_8013C384(Camera_8013F738 *pCamera, unsigned int kind, int ref, int arg)
{
    if (fn_801486A0() == 1 && (kind == 1 || kind == 4)) {
        kind = 7;
    }
    pCamera->mUnknownA8 = kind;
    switch (kind) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
        pCamera->mUnknown94 |= 1;
        pCamera->mUnknownB0 = ref;
        pCamera->mUnknownB4 = arg;
        fn_8013C328(pCamera, kind, ref);
        break;
    case 0:
        pCamera->mUnknown94 &= ~1;
        pCamera->mUnknownB0 = 0;
        pCamera->mUnknownB4 = 0;
        break;
    }
}

void fn_8013C438(Camera_8013F738 *pCamera)
{
    fn_8013C384(pCamera, 1, fn_801374D4(), 0);
}

void fn_8013C478(Camera_8013F738 *pCamera, Vector_80039F5C *pOffset)
{
    switch (pCamera->mUnknown98) {
    case 0:
    case 4:
        pCamera->mUnknownC4 = pOffset->mX;
        pCamera->mUnknownC8 = pOffset->mY;
        pCamera->mUnknownCC = pOffset->mZ;
        break;
    case 1:
        pCamera->mUnknown30 = pOffset->mX;
        break;
    }
}

void fn_8013C4BC(Camera_8013F738 *pCamera, int *pAngles, int bit)
{
    pCamera->mUnknown94 = (pCamera->mUnknown94 & ~0x60) | (1 << bit);
    switch (pCamera->mUnknown98) {
    case 0:
    case 4:
        pCamera->mUnknownD0 = pAngles[0];
        pCamera->mUnknownD4 = pAngles[1];
        pCamera->mUnknownD8 = pAngles[2];
        pCamera->mUnknownD0 &= 0xFFFFFF;
        pCamera->mUnknownD4 &= 0xFFFFFF;
        pCamera->mUnknownD8 &= 0xFFFFFF;
        break;
    case 1:
        pCamera->mUnknownD0 = pAngles[0];
        pCamera->mUnknownD4 = pAngles[1];
        pCamera->mUnknownD0 &= 0xFFFFFF;
        pCamera->mUnknownD4 &= 0xFFFFFF;
        break;
    }
}

void fn_8013C540(Camera_8013F738 *pCamera, int angle)
{
    switch (pCamera->mUnknown98) {
    case 0:
    case 4:
        pCamera->mUnknownD8 += angle;
        break;
    case 1:
        pCamera->mUnknownD4 += angle;
        break;
    }
}

void fn_8013C57C(Camera_8013F738 *pCamera, int angle)
{
    switch (pCamera->mUnknown98) {
    case 0:
    case 4:
        pCamera->mUnknownD0 += angle;
        if (pCamera->mUnknown94 & 0x20) {
            pCamera->mUnknownD0 = CLAMP(pCamera->mUnknownD0, 0x805B06, 0xFFA4FB);
        } else {
            pCamera->mUnknownD0 &= 0xFFFFFF;
        }
        break;
    case 1:
        pCamera->mUnknownD0 += angle;
        if (pCamera->mUnknown94 & 0x20) {
            pCamera->mUnknownD0 = CLAMP(pCamera->mUnknownD0, 0x805B06, 0xFFA4FB);
        } else {
            pCamera->mUnknownD0 &= 0xFFFFFF;
        }
        break;
    }
}

void fn_8013C624(Camera_8013F738 *pCamera, int id, int a, int b)
{
    fn_8013C824(pCamera, 0, 0);
    pCamera->mUnknownA4 = pCamera->mUnknownA0;
    pCamera->mUnknownA0 = id;
    fn_8013C824(pCamera, 1, 0);
}

int fn_8013C678(Camera_8013F738 *pCamera)
{
    return pCamera->mUnknownA0;
}

void fn_8013C680(Camera_8013F738 *pCamera, int on, int a, int b)
{
    if (on) {
        if (pCamera->mUnknown94 & 8) {
            fn_8013C824(pCamera, 5, 0);
            pCamera->mUnknown94 &= ~8;
        }
    } else {
        fn_8013C824(pCamera, 2, 0);
        pCamera->mUnknown94 ^= 8;
    }
}

void fn_8013C6F0(Camera_8013F738 *pCamera)
{
    Vector_80039F5C pos;
    int angles[3];

    switch (pCamera->mUnknown98) {
    case 0:
        fn_8013BDC0(pCamera->mUnknownA8, pCamera->mUnknownAC, &pCamera->mUnknownB8);
        fn_8013BC4C(pCamera, &pCamera->mUnknownB8, &pos);
        fn_801C3EA4(pCamera, pos.mX, pos.mY, pos.mZ);
        fn_8013BF40(pCamera, angles);
        fn_801C3ED0(pCamera, angles[0], angles[1], angles[2]);
        fn_801C3E54(pCamera);
        fn_8013C824(pCamera, 11, 0);
        break;
    case 1:
        fn_8013BF40(pCamera, angles);
        fn_801C3C74(pCamera, angles[0], angles[1]);
        fn_801C3C80(pCamera);
        break;
    case 4:
        break;
    }
}

void fn_8013C7C4(Camera_8013F738 *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
        fn_801C3E54(pCamera);
        break;
    case 1: {
        CameraType1_802F4884 *pBase = (CameraType1_802F4884 *)pCamera;

        ZeroVector(&pBase->mUnknown4C);
        pBase->mUnknown58 = 0.0f;
        pBase->mUnknown5C = 0;
        pBase->mUnknown60 = 0;
        break;
    }
    case 4:
        break;
    }
}

void fn_8013C824(Camera_8013F738 *pCamera, int msg, int arg)
{
    if (pCamera->mUnknownDC) {
        pCamera->mUnknownDC(pCamera, msg, arg);
    }
}

int fn_8013C854(int id)
{
    return lbl_802DBD30[id];
}

void fn_8013C868(Camera_8013F738 *pCamera, Desc_8013C340 *pDesc)
{
    pCamera->mUnknown98 = pDesc->mUnknown00;
    fn_8013C120(pCamera);
    pCamera->mUnknown94 = 0;
    pCamera->mUnknown9C = pDesc->mUnknown04;
    pCamera->mUnknownA0 = -1;
    pCamera->mUnknownDC = 0;
    fn_80141054(pCamera->mUnknown9C)->mUnknown00(pCamera, pDesc);
    fn_8013C624(pCamera, 1, 0, 0);
    fn_8013C384(pCamera, 0, 0, 0);
    pCamera->mUnknown94 |= 4;
}

void fn_8013C90C(Camera_8013F738 *pCamera)
{
    fn_80141054(pCamera->mUnknown9C)->mUnknown04(pCamera);
    fn_8013C1C8(pCamera);
}

void fn_8013C954(void *p, Camera_8013F738 *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
        fn_801C3E84(p, pCamera);
        break;
    case 1:
        fn_801C3C4C(p, pCamera);
        break;
    case 4:
        fn_801C3918(p, pCamera);
        break;
    }
}

void fn_8013C9A4(EaseVector_8013C9A4 *pEase, Vector_80039F5C *pBase, Vector_80039F5C *pFrom,
                 Vector_80039F5C *pTo, InterpFunc_8013CC14 update, float fromScale, float toScale,
                 float time)
{
    pEase->mBase.mX = pBase->mX;
    pEase->mBase.mY = pBase->mY;
    pEase->mBase.mZ = pBase->mZ;
    fn_8013CC14(&pEase->mX, pFrom->mX);
    fn_8013CC40(&pEase->mX, update, pTo->mX, time);
    fn_8013CC14(&pEase->mY, pFrom->mY);
    fn_8013CC40(&pEase->mY, update, pTo->mY, time);
    fn_8013CC14(&pEase->mZ, pFrom->mZ);
    fn_8013CC40(&pEase->mZ, update, pTo->mZ, time);
    fn_8013CC14(&pEase->mScale, fromScale);
    fn_8013CC40(&pEase->mScale, update, toScale, time);
}

void fn_8013CAA4(EaseVector_8013C9A4 *pEase, int steps)
{
    Vector_80039F5C offset;
    int angles[3];

    pEase->mX.mUpdate(&pEase->mX, steps);
    pEase->mY.mUpdate(&pEase->mY, steps);
    pEase->mZ.mUpdate(&pEase->mZ, steps);
    pEase->mScale.mUpdate(&pEase->mScale, steps);
    angles[0] = (int)(pEase->mX.mValue * 46603.37890625f);
    angles[1] = (int)(pEase->mY.mValue * 46603.37890625f);
    angles[2] = (int)(pEase->mZ.mValue * 46603.37890625f);
    fn_801D0470(fn_80228668());
    fn_801D0508();
    fn_801D0C58(&pEase->mBase);
    fn_801D0ADC(-angles[2]);
    fn_801D08FC(-angles[0]);
    offset.mX = 0.0f;
    offset.mY = 0.0f;
    offset.mZ = pEase->mScale.mValue;
    fn_80227CC0(&pEase->mResult, &offset);
    fn_801D0544();
}

/* Negates the base x and y and turns the z angle by 180 degrees. */
void fn_8013CBC4(EaseVector_8013C9A4 *pEase)
{
    if (pEase) {
        pEase->mZ.mValue += 180.0f;
        pEase->mZ.mTarget += 180.0f;
        pEase->mZ.mStart += 180.0f;
        pEase->mBase.mX = -pEase->mBase.mX;
        pEase->mBase.mY = -pEase->mBase.mY;
    }
}

void fn_8013CC14(Interp_8013CC14 *pInterp, float value)
{
    pInterp->mStart = pInterp->mValue = pInterp->mTarget = value;
    pInterp->mTime = pInterp->mRate = 0.0f;
    pInterp->mUpdate = fn_8013CEB8;
}

void fn_8013CC40(Interp_8013CC14 *pInterp, InterpFunc_8013CC14 update, float target, float time)
{
    if (target != pInterp->mStart) {
        pInterp->mUpdate = update;
        pInterp->mStart = pInterp->mValue;
        pInterp->mTarget = target;
        pInterp->mTime = 0.0f;
        pInterp->mRate = 1.0f / time;
    }
}
}
