/* Free-floating camera: eases its position and angles toward a destination. */

#include "engine/camera.h"

typedef struct CamFree_t {
    Cam_t mCam;
    float mDestPos[3];
    int mDestAngle[3];
    float mPosSpeed[3];
    int mAngleSpeed[3];
    float mMaxSpeed[3];
    float mAccel[3];
    int mMaxAngleSpeed[3];
    int mAngleAccel[3];
} CamFree_t;


void CamFreeClearVelocity(CamFree_t *pCam);

static inline void _CamFreeZeroVec3f(float *pVec)
{
    pVec[2] = 0.0f;
    pVec[1] = 0.0f;
    pVec[0] = 0.0f;
}

static inline void _CamFreeZeroVec3i(int *pVec)
{
    pVec[2] = 0;
    pVec[1] = 0;
    pVec[0] = 0;
}

void CamFreeFloatAdd(CamFree_t *pCam)
{
    pCam->mCam.mHeader.mUnknown04[0] = pCam->mCam.mHeader.mUnknown04[1] = pCam->mCam.mHeader.mUnknown04[2] = 0.0f;
    pCam->mCam.mHeader.mUnknown14[0] = pCam->mCam.mHeader.mUnknown14[1] = pCam->mCam.mHeader.mUnknown14[2] = 0;
    pCam->mDestPos[0] = pCam->mDestPos[1] = pCam->mDestPos[2] = 0.0f;
    pCam->mDestAngle[0] = pCam->mDestAngle[1] = pCam->mDestAngle[2] = 0;
    pCam->mMaxSpeed[0] = pCam->mMaxSpeed[1] = pCam->mMaxSpeed[2] = 0.2f;
    pCam->mAccel[0] = pCam->mAccel[1] = pCam->mAccel[2] = 0.1f;
    pCam->mMaxAngleSpeed[0] = pCam->mMaxAngleSpeed[1] = pCam->mMaxAngleSpeed[2] = 0x199999;
    pCam->mAngleAccel[0] = pCam->mAngleAccel[1] = pCam->mAngleAccel[2] = 0xCCCCC;
    CamFreeClearVelocity(pCam);
}

void CamFreeFloatDelete(CamFree_t *pCam)
{
}

void CamFreeFloatProcess(CamFree_t *pCam)
{
    CamLerp(&pCam->mCam.mHeader.mUnknown04[0], &pCam->mPosSpeed[0], pCam->mDestPos[0], pCam->mMaxSpeed[0], pCam->mAccel[0]);
    CamLerp(&pCam->mCam.mHeader.mUnknown04[1], &pCam->mPosSpeed[1], pCam->mDestPos[1], pCam->mMaxSpeed[1], pCam->mAccel[1]);
    CamLerp(&pCam->mCam.mHeader.mUnknown04[2], &pCam->mPosSpeed[2], pCam->mDestPos[2], pCam->mMaxSpeed[2], pCam->mAccel[2]);
    CamRLerp(&pCam->mCam.mHeader.mUnknown14[0], &pCam->mAngleSpeed[0], pCam->mDestAngle[0], pCam->mMaxAngleSpeed[0],
                pCam->mAngleAccel[0]);
    CamRLerp(&pCam->mCam.mHeader.mUnknown14[1], &pCam->mAngleSpeed[1], pCam->mDestAngle[1], pCam->mMaxAngleSpeed[1],
                pCam->mAngleAccel[1]);
    CamRLerp(&pCam->mCam.mHeader.mUnknown14[2], &pCam->mAngleSpeed[2], pCam->mDestAngle[2], pCam->mMaxAngleSpeed[2],
                pCam->mAngleAccel[2]);
}

void CamFreeClearVelocity(CamFree_t *pCam)
{
    _CamFreeZeroVec3f(pCam->mPosSpeed);
    _CamFreeZeroVec3i(pCam->mAngleSpeed);
}

void CamFreeFloatUpdate(void *pViewport, CamFree_t *pCam)
{
    CamConvertHdrToMatrix(pViewport, &pCam->mCam);
}

void CamFreeSetPos(CamFree_t *pCam, float x, float y, float z)
{
    pCam->mCam.mHeader.mUnknown04[0] = x;
    pCam->mCam.mHeader.mUnknown04[1] = y;
    pCam->mCam.mHeader.mUnknown04[2] = z;
    pCam->mDestPos[0] = x;
    pCam->mDestPos[1] = y;
    pCam->mDestPos[2] = z;
}

void CamFreeMovePos(CamFree_t *pCam, float x, float y, float z)
{
    pCam->mDestPos[0] = x;
    pCam->mDestPos[1] = y;
    pCam->mDestPos[2] = z;
}

void CamFreeSetAngle(CamFree_t *pCam, int x, int y, int z)
{
    pCam->mCam.mHeader.mUnknown14[0] = x;
    pCam->mCam.mHeader.mUnknown14[1] = y;
    pCam->mCam.mHeader.mUnknown14[2] = z;
    pCam->mDestAngle[0] = x;
    pCam->mDestAngle[1] = y;
    pCam->mDestAngle[2] = z;
}

void CamFreeMoveAngle(CamFree_t *pCam, int x, int y, int z)
{
    pCam->mDestAngle[0] = x;
    pCam->mDestAngle[1] = y;
    pCam->mDestAngle[2] = z;
}
