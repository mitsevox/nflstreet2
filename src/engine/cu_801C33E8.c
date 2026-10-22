/* Camera manager: typed cameras in an object pool, attached to viewports, with angle and value easing helpers. */

#include "engine/cu_801C33E8.h"
#include "engine/fn_801F7BD4.h"

typedef struct CamFuncs_801C33E8 {
    void (*mpAdd)(Cam_801C33E8 *pCam);
    void (*mpDelete)(Cam_801C33E8 *pCam);
    void (*mpProcess)(CamViewport_801C33E8 *pViewport, Cam_801C33E8 *pCam);
} CamFuncs_801C33E8;

typedef struct CamType_801C33E8 {
    CamFuncs_801C33E8 *mpFuncs;
    unsigned int mSize;
    void (*mpPreProcess)(Cam_801C33E8 *pCam);
} CamType_801C33E8;

extern unsigned char lbl_803EBBD4;
extern unsigned char lbl_803ECECC;
extern unsigned char lbl_803ECECD;
extern CamType_801C33E8 *lbl_803ECED0;
extern float lbl_803ECED4;

void fn_801D0470(unsigned int index);
void fn_801D0494(void);
void fn_801D08FC(int angle);
void fn_801D09EC(int angle);
void fn_801D0ADC(int angle);
void fn_801D0C58(float *pPos);
int fn_801DCF0C(int type, unsigned int size, int count, void (*pAdd)(Cam_801C33E8 *), void (*pDelete)(Cam_801C33E8 *));
int fn_801DCF8C(int type);
Cam_801C33E8 *fn_801DD168(int type, int a, int b);
void fn_801DD2B8(Cam_801C33E8 *pCam);
int fn_80228668(void);
void fn_802286A8(CamViewport_801C33E8 *pViewport, void (*fn)(CamViewport_801C33E8 *, Cam_801C33E8 *), void *arg);
Cam_801C33E8 *fn_802286B4(CamViewport_801C33E8 *pViewport);
void fn_802286BC(CamViewport_801C33E8 *pViewport);
void fn_802286D8(CamViewport_801C33E8 *pViewport, float fovy, float aspect, float n, float f);
void fn_80228780(CamViewport_801C33E8 *pViewport, float scale);

void fn_801C3990(Cam_801C33E8 *pCam, float fov, float aspect);

static inline int fn_801C33E8_Mul(int a, int b)
{
    return (int)(((long long)a * b) >> 24);
}

static void fn_801C33E8(Cam_801C33E8 *pCam)
{
    lbl_803ECED0[pCam->mType].mpFuncs->mpAdd(pCam);
    pCam->mFov = 45.0f;
    pCam->mAspect = lbl_803ECED4;
    pCam->mpViewport = 0;
}

static void fn_801C3448(Cam_801C33E8 *pCam)
{
    lbl_803ECED0[pCam->mType].mpFuncs->mpDelete(pCam);
}

static void fn_801C3480(CamViewport_801C33E8 *pViewport, Cam_801C33E8 *pCam)
{
    if (lbl_803ECED0[pCam->mType].mpPreProcess) {
        lbl_803ECED0[pCam->mType].mpPreProcess(pCam);
    }
    lbl_803ECED0[pCam->mType].mpFuncs->mpProcess(pViewport, pCam);
}

int fn_801C34F8(int count, int numTypes, CamType_801C33E8 *pTypes, int type)
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
        error = fn_801DCF0C(type, maxSize, count, fn_801C33E8, fn_801C3448);
        lbl_803EBBD4 = 1;
    } else {
        error = 0xB0001;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C35B8(void)
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

Cam_801C33E8 *fn_801C3610(int a, int b)
{
    return fn_801DD168(lbl_803ECECC, a, b);
}

void fn_801C3640(Cam_801C33E8 *pCam)
{
    fn_801DD2B8(pCam);
}

void fn_801C3660(CamViewport_801C33E8 *pViewport, Cam_801C33E8 *pCam)
{
    fn_802286A8(pViewport, fn_801C3480, pCam);
    pCam->mpViewport = pViewport;
    fn_801C3990(pCam, pCam->mFov, pCam->mAspect);
}

void fn_801C36B0(CamViewport_801C33E8 *pViewport, Cam_801C33E8 *pCam)
{
    if (pCam || (pCam = fn_802286B4(pViewport))) {
        if (pCam == fn_802286B4(pViewport)) {
            fn_802286BC(pViewport);
            pCam->mpViewport = 0;
        }
    }
}

int fn_801C370C(int *pAngle, int *pSpeed, int dest, int maxSpeed, int accel)
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
        limit = fn_801C33E8_Mul(diff, maxSpeed);
        if (forward == 1) {
            *pSpeed += fn_801C33E8_Mul(diff, accel);
            if (*pSpeed > limit) {
                *pSpeed = limit;
            }
            *pAngle = (*pAngle + *pSpeed) & 0xFFFFFF;
            if (((dest - *pAngle) & 0xFFFFFF) > 0x800000) {
                done = 1;
            }
        } else {
            *pSpeed -= fn_801C33E8_Mul(diff, accel);
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

int fn_801C384C(float *pValue, float *pSpeed, float dest, float maxSpeed, float accel)
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

void fn_801C3918(void *pUnused, Cam_801C33E8 *pCam)
{
    float pos[3];

    fn_801D0470(fn_80228668());
    fn_801D0494();
    fn_801D08FC(pCam->mAngle[0]);
    fn_801D09EC(pCam->mAngle[1]);
    fn_801D0ADC(pCam->mAngle[2]);
    pos[0] = -pCam->mPos[0];
    pos[1] = -pCam->mPos[1];
    pos[2] = -pCam->mPos[2];
    fn_801D0C58(pos);
}

void fn_801C3990(Cam_801C33E8 *pCam, float fov, float aspect)
{
    pCam->mFov = fov;
    pCam->mAspect = aspect;
    if (pCam->mpViewport) {
        fn_802286D8(pCam->mpViewport, fov, aspect, pCam->mpViewport->mNear, pCam->mpViewport->mFar);
    }
}

void fn_801C39D0(Cam_801C33E8 *pCam, float n)
{
    if (pCam->mpViewport) {
        fn_802286D8(pCam->mpViewport, pCam->mFov, pCam->mAspect, n, pCam->mpViewport->mFar);
    }
}

void fn_801C3A10(Cam_801C33E8 *pCam, float scale)
{
    if (pCam->mpViewport) {
        fn_80228780(pCam->mpViewport, scale);
    }
}

void fn_801C3A3C(float aspect)
{
    lbl_803ECED4 = aspect;
}
