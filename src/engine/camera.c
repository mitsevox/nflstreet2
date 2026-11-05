/* Camera manager: typed cameras in an object pool, attached to viewports, with angle and value easing helpers. */

#include "engine/camera.h"
#include "engine/cu_80227F14.h"
#include "engine/fn_801F7BD4.h"
#include "game/CamAddCameraToViewport.h"
#include "engine/llmatrix.h"

typedef struct CamFuncs_t {
    void (*mpAdd)(Cam_t *pCam);
    void (*mpDelete)(Cam_t *pCam);
    void (*mpProcess)(Object_80228224 *pViewport, Cam_t *pCam);
} CamFuncs_t;

typedef struct CamType_t {
    CamFuncs_t *mpFuncs;
    unsigned int mSize;
    void (*mpPreProcess)(Cam_t *pCam);
} CamType_t;

extern unsigned char lbl_803EBBD4;
extern unsigned char lbl_803ECECC;
extern unsigned char lbl_803ECECD;
extern CamType_t *lbl_803ECED0;
extern float lbl_803ECED4;

int fn_801DCF0C(int type, unsigned int size, int count, void (*pAdd)(Cam_t *), void (*pDelete)(Cam_t *));
int fn_801DCF8C(int type);
Cam_t *fn_801DD168(int type, int a, int b);
void fn_801DD2B8(Cam_t *pCam);

void CamSetFieldOfView(Cam_t *pCam, float fov, float aspect);

static inline int _CamMulFixed24(int a, int b)
{
    return (int)(((long long)a * b) >> 24);
}

static void _CamAddFunc(Cam_t *pCam)
{
    lbl_803ECED0[pCam->mHeader.mType].mpFuncs->mpAdd(pCam);
    pCam->mHeader.mUnknown20 = 45.0f;
    pCam->mHeader.mUnknown24 = lbl_803ECED4;
    pCam->mpViewport = 0;
}

static void _CamDeleteFunc(Cam_t *pCam)
{
    lbl_803ECED0[pCam->mHeader.mType].mpFuncs->mpDelete(pCam);
}

static void _CamProcessFunc(Object_80228224 *pViewport, void *pArg)
{
    Cam_t *pCam = pArg;

    if (lbl_803ECED0[pCam->mHeader.mType].mpPreProcess) {
        lbl_803ECED0[pCam->mHeader.mType].mpPreProcess(pCam);
    }
    lbl_803ECED0[pCam->mHeader.mType].mpFuncs->mpProcess(pViewport, pCam);
}

int CamInit(int count, int numTypes, CamType_t *pTypes, int type)
{
    int error = 0;
    unsigned int maxSize = 0;
    int i;

    if (!lbl_803EBBD4) {
        lbl_803ECECC = type;
        lbl_803ECED4 = 1.3333334f;
        lbl_803ECECD = numTypes;
        lbl_803ECED0 = pTypes;
        for (i = 0; i < numTypes; i++) {
            if (pTypes[i].mSize > maxSize) {
                maxSize = pTypes[i].mSize;
            }
        }
        error = fn_801DCF0C(type, maxSize, count, _CamAddFunc, _CamDeleteFunc);
        lbl_803EBBD4 = 1;
    } else {
        error = 0xB0001;
    }
    fn_801F7BD4(error);
    return error;
}

int CamShutdown(void)
{
    int error = 0;

    if (lbl_803EBBD4) {
        fn_801DCF8C(lbl_803ECECC);
        lbl_803EBBD4 = 0;
    } else {
        error = 0xB0002;
    }
    fn_801F7BD4(error);
    return error;
}

Cam_t *CamCreate(int a, int b)
{
    return fn_801DD168(lbl_803ECECC, a, b);
}

void CamDestroy(Cam_t *pCam)
{
    fn_801DD2B8(pCam);
}

void CamAddCameraToViewport(Object_80228224 *pViewport, void *pArg)
{
    Cam_t *pCam = pArg;

    fn_802286A8(pViewport, _CamProcessFunc, pCam);
    pCam->mpViewport = pViewport;
    CamSetFieldOfView(pCam, pCam->mHeader.mUnknown20, pCam->mHeader.mUnknown24);
}

void CamRemoveCameraFromViewport(Object_80228224 *pViewport, Cam_t *pCam)
{
    if (pCam || (pCam = fn_802286B4(pViewport))) {
        if (pCam == fn_802286B4(pViewport)) {
            fn_802286BC(pViewport);
            pCam->mpViewport = 0;
        }
    }
}

int CamRLerp(int *pAngle, int *pSpeed, int dest, int maxSpeed, int accel)
{
    int done = 0;
    int forward = 1;
    int diff;
    int limit;

    dest &= 0xFFFFFF;
    *pAngle &= 0xFFFFFF;
    diff = (dest - *pAngle) & 0xFFFFFF;
    if (diff > 0x800000) {
        forward = 0;
        diff = 0x1000000 - diff;
    }
    if (diff > 0) {
        limit = _CamMulFixed24(diff, maxSpeed);
        if (forward == 1) {
            *pSpeed += _CamMulFixed24(diff, accel);
            if (*pSpeed > limit) {
                *pSpeed = limit;
            }
            *pAngle = (*pAngle + *pSpeed) & 0xFFFFFF;
            if (((dest - *pAngle) & 0xFFFFFF) > 0x800000) {
                done = 1;
            }
        } else {
            *pSpeed -= _CamMulFixed24(diff, accel);
            if (*pSpeed < -limit) {
                *pSpeed = -limit;
            }
            *pAngle = (*pAngle + *pSpeed) & 0xFFFFFF;
            if (((dest - *pAngle) & 0xFFFFFF) <= 0x800000) {
                done = 1;
            }
        }
    } else {
        done = 1;
    }
    if (done == 1) {
        *pAngle = dest;
        *pSpeed = 0;
        return 1;
    }
    return 0;
}

int CamLerp(float *pValue, float *pSpeed, float dest, float maxSpeed, float accel)
{
    int done = 0;
    float diff = dest - *pValue;
    float limit = (float)__builtin_fabs(diff) * maxSpeed;

    if (!(diff < 0.0f)) {
        *pSpeed += limit * accel;
        if (!(*pSpeed <= limit)) {
            *pSpeed = limit;
        }
        *pValue += *pSpeed;
        if (!(*pValue <= dest)) {
            done = 1;
        }
    } else {
        *pSpeed -= limit * accel;
        if (!(*pSpeed >= -limit)) {
            *pSpeed = -limit;
        }
        *pValue += *pSpeed;
        if (!(*pValue >= dest)) {
            done = 1;
        }
    }
    if (done == 1) {
        *pValue = dest;
        *pSpeed = 0.0f;
        return 1;
    }
    return 0;
}

void CamConvertHdrToMatrix(void *pUnused, Cam_t *pCam)
{
    float pos[3];

    fn_801D0470(fn_80228668());
    fn_801D0494();
    fn_801D08FC(pCam->mHeader.mUnknown14[0]);
    fn_801D09EC(pCam->mHeader.mUnknown14[1]);
    fn_801D0ADC(pCam->mHeader.mUnknown14[2]);
    pos[0] = -pCam->mHeader.mUnknown04[0];
    pos[1] = -pCam->mHeader.mUnknown04[1];
    pos[2] = -pCam->mHeader.mUnknown04[2];
    fn_801D0C58(pos);
}

void CamSetFieldOfView(Cam_t *pCam, float fov, float aspect)
{
    pCam->mHeader.mUnknown20 = fov;
    pCam->mHeader.mUnknown24 = aspect;
    if (pCam->mpViewport) {
        fn_802286D8(pCam->mpViewport, fov, aspect, pCam->mpViewport->mUnknown232, pCam->mpViewport->mUnknown236);
    }
}

void CamSetNearPlane(Cam_t *pCam, float n)
{
    if (pCam->mpViewport) {
        fn_802286D8(pCam->mpViewport, pCam->mHeader.mUnknown20, pCam->mHeader.mUnknown24, n, pCam->mpViewport->mUnknown236);
    }
}

void CamSetZScale(Cam_t *pCam, float scale)
{
    if (pCam->mpViewport) {
        fn_80228780(pCam->mpViewport, scale);
    }
}

void CamSetDefaultAspect(float aspect)
{
    lbl_803ECED4 = aspect;
}
