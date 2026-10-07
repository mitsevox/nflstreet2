#include "engine/cu_80227F14.h"
#include "game/Object_80039F5C.h"
#include "game/cu_801442FC.h"

struct Object_8005438C {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12;
};

extern "C" {
Object_8005438C *fn_8005438C(int id);
void fn_801D0470(int a);
void fn_802271F0(float *pOut, float *pIn);
void fn_80227C2C(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
}

extern "C" {

void fn_801442FC(Tracker_801442FC *pTracker)
{
    pTracker->mId = -1;
    pTracker->mCount = 0;
}

int fn_80144310(Tracker_801442FC *pTracker, Object_80144310 *pSource, float *pDirection, float *pScaled)
{
    if (pSource != 0 && pSource->mUnknown1C != -1) {
        pTracker->mId = pSource->mUnknown1C;
        if (pTracker->mCount <= 8) {
            pTracker->mCount++;
        }
    } else if (pTracker->mCount != 0) {
        pTracker->mCount--;
        if (pTracker->mCount == 0) {
            pTracker->mId = -1;
        }
    }
    if (pTracker->mId != -1) {
        Object_8005438C *pObject = fn_8005438C(pTracker->mId);
        Vector_80039F5C direction;
        float scale;
        unsigned int count = pTracker->mCount;

        scale = count / 9.0f;
        scale *= 255.0f;
        direction.mX = pObject->mUnknown12.mX;
        direction.mY = -pObject->mUnknown12.mZ;
        direction.mZ = pObject->mUnknown12.mY;
        fn_801D0470(fn_80228668());
        fn_802271F0(&direction.mX, &direction.mX);
        direction.mX = -direction.mX;
        direction.mY = -direction.mY;
        direction.mZ = -direction.mZ;
        fn_80227C2C(&direction, &direction);
        pDirection[0] = direction.mX;
        pDirection[1] = direction.mY;
        pDirection[2] = direction.mZ;
        pScaled[0] = pObject->mUnknown0.mX * scale;
        pScaled[1] = pObject->mUnknown0.mY * scale;
        pScaled[2] = pObject->mUnknown0.mZ * scale;
    }
    return pTracker->mId != -1;
}

void fn_801444A0(Tracker_801442FC *pTracker, Object_80144310 *pSource)
{
    if (pSource != 0 && pSource->mUnknown1C != -1) {
        pTracker->mId = pSource->mUnknown1C;
        pTracker->mCount = 9;
    } else {
        pTracker->mId = -1;
        pTracker->mCount = 0;
    }
}

}
