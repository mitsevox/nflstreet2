/* Free-floating camera: eases its position and angles toward a destination. */

#include "engine/cu_801C33E8.h"

typedef struct CamFree_801C3CE8 {
    Cam_801C33E8 mCam;
    float mDestPos[3];
    int mDestAngle[3];
    float mPosSpeed[3];
    int mAngleSpeed[3];
    float mMaxSpeed[3];
    float mAccel[3];
    int mMaxAngleSpeed[3];
    int mAngleAccel[3];
} CamFree_801C3CE8;


void fn_801C3E54(CamFree_801C3CE8 *pCam);

static inline void fn_801C3CE8_ZeroF(float *pVec)
{
    pVec[2] = 0.0f;
    pVec[1] = 0.0f;
    pVec[0] = 0.0f;
}

static inline void fn_801C3CE8_ZeroI(int *pVec)
{
    pVec[2] = 0;
    pVec[1] = 0;
    pVec[0] = 0;
}

void fn_801C3CE8(CamFree_801C3CE8 *pCam)
{
    pCam->mCam.mPos[0] = pCam->mCam.mPos[1] = pCam->mCam.mPos[2] = 0.0f;
    pCam->mCam.mAngle[0] = pCam->mCam.mAngle[1] = pCam->mCam.mAngle[2] = 0;
    pCam->mDestPos[0] = pCam->mDestPos[1] = pCam->mDestPos[2] = 0.0f;
    pCam->mDestAngle[0] = pCam->mDestAngle[1] = pCam->mDestAngle[2] = 0;
    pCam->mMaxSpeed[0] = pCam->mMaxSpeed[1] = pCam->mMaxSpeed[2] = 0.2f;
    pCam->mAccel[0] = pCam->mAccel[1] = pCam->mAccel[2] = 0.1f;
    pCam->mMaxAngleSpeed[0] = pCam->mMaxAngleSpeed[1] = pCam->mMaxAngleSpeed[2] = 0x199999;
    pCam->mAngleAccel[0] = pCam->mAngleAccel[1] = pCam->mAngleAccel[2] = 0xCCCCC;
    fn_801C3E54(pCam);
}

void fn_801C3D98(CamFree_801C3CE8 *pCam)
{
}

void fn_801C3D9C(CamFree_801C3CE8 *pCam)
{
    fn_801C384C(&pCam->mCam.mPos[0], &pCam->mPosSpeed[0], pCam->mDestPos[0], pCam->mMaxSpeed[0], pCam->mAccel[0]);
    fn_801C384C(&pCam->mCam.mPos[1], &pCam->mPosSpeed[1], pCam->mDestPos[1], pCam->mMaxSpeed[1], pCam->mAccel[1]);
    fn_801C384C(&pCam->mCam.mPos[2], &pCam->mPosSpeed[2], pCam->mDestPos[2], pCam->mMaxSpeed[2], pCam->mAccel[2]);
    fn_801C370C(&pCam->mCam.mAngle[0], &pCam->mAngleSpeed[0], pCam->mDestAngle[0], pCam->mMaxAngleSpeed[0],
                pCam->mAngleAccel[0]);
    fn_801C370C(&pCam->mCam.mAngle[1], &pCam->mAngleSpeed[1], pCam->mDestAngle[1], pCam->mMaxAngleSpeed[1],
                pCam->mAngleAccel[1]);
    fn_801C370C(&pCam->mCam.mAngle[2], &pCam->mAngleSpeed[2], pCam->mDestAngle[2], pCam->mMaxAngleSpeed[2],
                pCam->mAngleAccel[2]);
}

void fn_801C3E54(CamFree_801C3CE8 *pCam)
{
    fn_801C3CE8_ZeroF(pCam->mPosSpeed);
    fn_801C3CE8_ZeroI(pCam->mAngleSpeed);
}

void fn_801C3E84(void *pViewport, CamFree_801C3CE8 *pCam)
{
    fn_801C3918(pViewport, &pCam->mCam);
}

void fn_801C3EA4(CamFree_801C3CE8 *pCam, float x, float y, float z)
{
    pCam->mCam.mPos[0] = x;
    pCam->mCam.mPos[1] = y;
    pCam->mCam.mPos[2] = z;
    pCam->mDestPos[0] = x;
    pCam->mDestPos[1] = y;
    pCam->mDestPos[2] = z;
}

void fn_801C3EC0(CamFree_801C3CE8 *pCam, float x, float y, float z)
{
    pCam->mDestPos[0] = x;
    pCam->mDestPos[1] = y;
    pCam->mDestPos[2] = z;
}

void fn_801C3ED0(CamFree_801C3CE8 *pCam, int x, int y, int z)
{
    pCam->mCam.mAngle[0] = x;
    pCam->mCam.mAngle[1] = y;
    pCam->mCam.mAngle[2] = z;
    pCam->mDestAngle[0] = x;
    pCam->mDestAngle[1] = y;
    pCam->mDestAngle[2] = z;
}

void fn_801C3EEC(CamFree_801C3CE8 *pCam, int x, int y, int z)
{
    pCam->mDestAngle[0] = x;
    pCam->mDestAngle[1] = y;
    pCam->mDestAngle[2] = z;
}
