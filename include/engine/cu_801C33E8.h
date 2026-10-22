#ifndef ENGINE_CU_801C33E8_H
#define ENGINE_CU_801C33E8_H

typedef struct CamViewport_801C33E8 {
    unsigned char mUnk0[0xE8];
    float mNear;
    float mFar;
} CamViewport_801C33E8;

/* Common camera header; each camera type extends it. */
typedef struct Cam_801C33E8 {
    unsigned char mUnk0;
    unsigned char mType;
    unsigned char mUnk2[2];
    float mPos[3];
    unsigned char mUnk10[4];
    int mAngle[3];
    float mFov;
    float mAspect;
    CamViewport_801C33E8 *mpViewport;
} Cam_801C33E8;

int fn_801C370C(int *pAngle, int *pSpeed, int dest, int maxSpeed, int accel);
int fn_801C384C(float *pValue, float *pSpeed, float dest, float maxSpeed, float accel);
void fn_801C3918(void *pUnused, Cam_801C33E8 *pCam);

#endif
