#include "engine/Body_801E9538.h"

extern "C" {
float fn_80260B1C(float x);
float fn_801E8DBC(void *p);
}

void *operator new[](unsigned int size, int unknown);

/* State vector of a simulated system (defined in another file). */
class Class_801E8B10 {
public:
    virtual int vfn_01(float *pState) = 0;
    virtual int vfn_02(float *pState) = 0;
    virtual int vfn_03(int a, float *pRate) = 0;
};

/* Integrator over a system's state vector. */
class Class_801E8C3C {
public:
    Class_801E8C3C(Class_801E8B10 *pSystem) : mpSystem(pSystem) {}
    virtual ~Class_801E8C3C() { mpSystem = 0; }
    virtual int vfn_02(int a, void *pStep) = 0;
    virtual void vfn_03() = 0;

    Class_801E8B10 *mpSystem;
};

/* Explicit Euler integrator. */
class Class_801E89D8 : public Class_801E8C3C {
public:
    Class_801E89D8(Class_801E8B10 *pSystem, int count);
    virtual ~Class_801E89D8();
    virtual int vfn_02(int a, void *pStep);
    virtual void vfn_03();

    int mCount;
    float *mpState;
    float *mpNext;
    float *mpRate;
};

/* Decides whether a body may change its sleep state. */
class Class_801E88BC {
public:
    virtual int vfn_01(Body_801E9538 *pBody, int wake) = 0;
};

/* Body controller interface. */
class Class_801E87B8 {
public:
    virtual void vfn_01(Body_801E9538 *pBody) = 0;
    virtual void vfn_02(Body_801E9538 *pBody) = 0;
    virtual void vfn_03(Body_801E9538 *pBody, float dt) = 0;
};

/* Puts slow bodies to sleep and wakes moving ones. */
class Class_801E8798 : public Class_801E87B8 {
public:
    Class_801E8798(float sleepTime, float maxSpeed, Class_801E88BC *pFilter);
    virtual void vfn_01(Body_801E9538 *pBody);
    virtual void vfn_02(Body_801E9538 *pBody);
    virtual void vfn_03(Body_801E9538 *pBody, float dt);
    int fn_801E896C(Body_801E9538 *pBody);

    float mSleepTime;
    float mMaxSpeed;
    Class_801E88BC *mpFilter;
};

Class_801E8798::Class_801E8798(float sleepTime, float maxSpeed, Class_801E88BC *pFilter)
    : mSleepTime(sleepTime), mMaxSpeed(maxSpeed), mpFilter(pFilter)
{
}

void Class_801E8798::vfn_01(Body_801E9538 *pBody)
{
    float time = 0.0f;

    pBody->mUserData = *(int *)&time;
}

void Class_801E8798::vfn_02(Body_801E9538 *pBody)
{
    pBody->mUserData = 0;
}

void Class_801E8798::vfn_03(Body_801E9538 *pBody, float dt)
{
    int state = pBody->mState;
    float time = 0.0f;
    Vec3_801DE1E0 vel;
    float speedSq;
    float maxSpeed;
    float target;

    if (state == 2) {
        if (fn_801E896C(pBody)) {
            time = *(float *)&pBody->mUserData + dt;
            if (time > mSleepTime && (!mpFilter || mpFilter->vfn_01(pBody, 0))) {
                fn_801E9F0C(pBody, 3);
                time = 0.0f;
            }
        } else {
            speedSq = fn_80227120(&pBody->mUnknown114);
            maxSpeed = mMaxSpeed;
            if (speedSq > maxSpeed * maxSpeed) {
                target = maxSpeed * 0.95f;
                fn_80227264(&vel, &pBody->mUnknown07C, target / fn_80260B1C(speedSq));
                fn_801E9C1C(pBody, &vel);
            }
        }
        pBody->mUserData = *(int *)&time;
    }
    if (state == 3 && !fn_801E896C(pBody) && (!mpFilter || mpFilter->vfn_01(pBody, 1))) {
        fn_801E9F0C(pBody, 2);
        time = 0.0f;
        pBody->mUserData = *(int *)&time;
    }
}

int Class_801E8798::fn_801E896C(Body_801E9538 *pBody)
{
    float limit = pBody->mUnknown048;
    float linearSq = fn_80227120(&pBody->mUnknown108);
    float angularSq = fn_80227120(&pBody->mUnknown114);

    if (linearSq <= limit && angularSq <= limit) {
        return 1;
    }
    return 0;
}

Class_801E89D8::Class_801E89D8(Class_801E8B10 *pSystem, int count)
    : Class_801E8C3C(pSystem), mCount(count), mpState(0), mpNext(0), mpRate(0)
{
    if (mCount) {
        mpState = new (0) float[mCount];
        mpNext = new (0) float[mCount];
        mpRate = new (0) float[mCount];
    }
}

Class_801E89D8::~Class_801E89D8()
{
    if (mpState) {
        delete[] mpState;
        mpState = 0;
    }
    if (mpNext) {
        delete[] mpNext;
        mpNext = 0;
    }
    if (mpRate) {
        delete[] mpRate;
        mpRate = 0;
    }
    mCount = 0;
}

int Class_801E89D8::vfn_02(int a, void *pStep)
{
    float dt = fn_801E8DBC(pStep);
    int result = mpSystem->vfn_01(mpState);
    unsigned int count;
    unsigned int i;
    float *pState;
    float *pRate;
    float *pNext;

    if (result) {
        count = mpSystem->vfn_03(a, mpRate);
        pState = mpState;
        pRate = mpRate;
        pNext = mpNext;
        for (i = 0; i < count; i++) {
            *pNext++ = *pRate++ * dt + *pState++;
        }
        mpSystem->vfn_02(mpNext);
    }
    return result;
}

void Class_801E89D8::vfn_03()
{
    mpSystem->vfn_02(mpState);
}
