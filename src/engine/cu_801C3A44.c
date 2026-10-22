/* Focus camera: orbits a target point at an eased distance and eased angles. */

#include "engine/cu_801C33E8.h"
#include "engine/cu_801D03D0.h"
#include "engine/cu_80227F14.h"

typedef struct CamFocus_801C3A44 {
    Cam_801C33E8 mCam;
    float *mpTarget;
    float mDist;
    int mDestAngle[2];
    float mFocus[3];
    float mCurDist;
    float mFocusSpeed[3];
    float mDistSpeed;
    int mAngleSpeed[2];
    float mMaxSpeed[4];
    float mAccel[4];
    int mMaxAngleSpeed[2];
    int mAngleAccel[2];
} CamFocus_801C3A44;

void fn_80227CC0(float *pOut, float *p);

static inline void fn_801C3A44_ZeroF(float *pVec)
{
    pVec[2] = 0.0f;
    pVec[1] = 0.0f;
    pVec[0] = 0.0f;
}

static inline void fn_801C3A44_ZeroI(int *pVec)
{
    pVec[2] = 0;
    pVec[1] = 0;
    pVec[0] = 0;
}

static inline void fn_801C3A44_ZeroI2(int *pVec)
{
    pVec[1] = 0;
    pVec[0] = 0;
}

static void fn_801C3A44(CamFocus_801C3A44 *pCam)
{
    float offset[3];
    float focus[3];

    fn_801D0470(fn_80228668());
    fn_801D0508();
    focus[0] = pCam->mFocus[0];
    focus[1] = pCam->mFocus[1];
    focus[2] = pCam->mFocus[2];
    fn_801D0C58(focus);
    fn_801D0ADC(-pCam->mCam.mHeader.mUnknown14[2]);
    fn_801D08FC(-pCam->mCam.mHeader.mUnknown14[0]);
    offset[0] = 0.0f;
    offset[1] = 0.0f;
    offset[2] = pCam->mCurDist;
    fn_80227CC0(pCam->mCam.mHeader.mUnknown04, offset);
    fn_801D0544();
}

void fn_801C3AD8(CamFocus_801C3A44 *pCam)
{
    fn_801C3A44_ZeroF(pCam->mCam.mHeader.mUnknown04);
    fn_801C3A44_ZeroI(pCam->mCam.mHeader.mUnknown14);
    pCam->mDist = pCam->mCurDist = 4.0f;
    fn_801C3A44_ZeroI2(pCam->mDestAngle);
    pCam->mMaxSpeed[3] = pCam->mMaxSpeed[2] = pCam->mMaxSpeed[1] = pCam->mMaxSpeed[0] = 0.2f;
    pCam->mAccel[3] = pCam->mAccel[2] = pCam->mAccel[1] = pCam->mAccel[0] = 0.1f;
    pCam->mMaxAngleSpeed[0] = pCam->mMaxAngleSpeed[1] = 0x199999;
    pCam->mAngleAccel[0] = pCam->mAngleAccel[1] = 0xCCCCC;
}

void fn_801C3B74(CamFocus_801C3A44 *pCam)
{
}

void fn_801C3B78(CamFocus_801C3A44 *pCam)
{
    if (pCam->mpTarget) {
        fn_801C384C(&pCam->mFocus[0], &pCam->mFocusSpeed[0], pCam->mpTarget[0], pCam->mMaxSpeed[0], pCam->mAccel[0]);
        fn_801C384C(&pCam->mFocus[1], &pCam->mFocusSpeed[1], pCam->mpTarget[1], pCam->mMaxSpeed[1], pCam->mAccel[1]);
        fn_801C384C(&pCam->mFocus[2], &pCam->mFocusSpeed[2], pCam->mpTarget[2], pCam->mMaxSpeed[2], pCam->mAccel[2]);
        fn_801C384C(&pCam->mCurDist, &pCam->mDistSpeed, pCam->mDist, pCam->mMaxSpeed[3], pCam->mAccel[3]);
        fn_801C370C(&pCam->mCam.mHeader.mUnknown14[0], &pCam->mAngleSpeed[0], pCam->mDestAngle[0], pCam->mMaxAngleSpeed[0],
                    pCam->mAngleAccel[0]);
        fn_801C370C(&pCam->mCam.mHeader.mUnknown14[2], &pCam->mAngleSpeed[1], pCam->mDestAngle[1], pCam->mMaxAngleSpeed[1],
                    pCam->mAngleAccel[1]);
        fn_801C3A44(pCam);
    }
}

void fn_801C3C4C(void *pViewport, CamFocus_801C3A44 *pCam)
{
    fn_801C3918(pViewport, &pCam->mCam);
}

void fn_801C3C6C(CamFocus_801C3A44 *pCam, float *pTarget)
{
    pCam->mpTarget = pTarget;
}

void fn_801C3C74(CamFocus_801C3A44 *pCam, int angleX, int angleZ)
{
    pCam->mDestAngle[0] = angleX;
    pCam->mDestAngle[1] = angleZ;
}

void fn_801C3C80(CamFocus_801C3A44 *pCam)
{
    if (pCam->mpTarget) {
        pCam->mFocus[0] = pCam->mpTarget[0];
        pCam->mFocus[1] = pCam->mpTarget[1];
        pCam->mFocus[2] = pCam->mpTarget[2];
        pCam->mCurDist = pCam->mDist;
        pCam->mCam.mHeader.mUnknown14[0] = pCam->mDestAngle[0];
        pCam->mCam.mHeader.mUnknown14[2] = pCam->mDestAngle[1];
        fn_801C3A44_ZeroF(pCam->mFocusSpeed);
        pCam->mDistSpeed = 0.0f;
        fn_801C3A44_ZeroI2(pCam->mAngleSpeed);
    }
}
