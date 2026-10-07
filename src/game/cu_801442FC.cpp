#include "game/Object_80039F5C.h"

struct Tracker_801442FC {
    int mId;
    unsigned char mCount;
};

struct Source_80144310 {
    char mUnknown0[28];
    int mId;
};

struct Object_8005438C {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12;
};

extern "C" {
Object_8005438C *fn_8005438C(int id);
int fn_80228668(void);
void fn_801D0470(int a);
void fn_802271F0(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void fn_80227C2C(Vector_80039F5C *pOut, Vector_80039F5C *pIn);

void fn_801442FC(Tracker_801442FC *pTracker);
int fn_80144310(Tracker_801442FC *pTracker, Source_80144310 *pSource, Vector_80039F5C *pDirection, Vector_80039F5C *pScaled);
void fn_801444A0(Tracker_801442FC *pTracker, Source_80144310 *pSource);
}

extern "C" {

void fn_801442FC(Tracker_801442FC *pTracker)
{
    pTracker->mId = -1;
    pTracker->mCount = 0;
}

int fn_80144310(Tracker_801442FC *pTracker, Source_80144310 *pSource, Vector_80039F5C *pDirection, Vector_80039F5C *pScaled)
{
    if (pSource != 0 && pSource->mId != -1) {
        pTracker->mId = pSource->mId;
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
        fn_802271F0(&direction, &direction);
        direction.mX = -direction.mX;
        direction.mY = -direction.mY;
        direction.mZ = -direction.mZ;
        fn_80227C2C(&direction, &direction);
        pDirection->mX = direction.mX;
        pDirection->mY = direction.mY;
        pDirection->mZ = direction.mZ;
        pScaled->mX = pObject->mUnknown0.mX * scale;
        pScaled->mY = pObject->mUnknown0.mY * scale;
        pScaled->mZ = pObject->mUnknown0.mZ * scale;
    }
    return pTracker->mId != -1;
}

void fn_801444A0(Tracker_801442FC *pTracker, Source_80144310 *pSource)
{
    if (pSource != 0 && pSource->mId != -1) {
        pTracker->mId = pSource->mId;
        pTracker->mCount = 9;
    } else {
        pTracker->mId = -1;
        pTracker->mCount = 0;
    }
}

}
