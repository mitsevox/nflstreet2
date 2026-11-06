/* Rigid-body physics stepping: the sleep controller that puts resting bodies to sleep and wakes
   them when they move, and the explicit Euler integrator over a system's state. */

#include "engine/rigidbody.h"
#include "engine/TibNew.h"

extern "C" {
float fn_80260B1C(float x);
float fn_801E8DBC(void *pEnd, void *pStart);
}

/* A simulated system seen as a state vector (implemented in another file). */
class IntegrableSystem {
public:
    virtual int GetState(float *pState) = 0;
    virtual void SetState(float *pState) = 0;
    virtual int GetDerivative(void *pStart, float *pRate) = 0;
};

/* Steps a system's state vector through time. */
class Integrator {
public:
    Integrator(IntegrableSystem *pSystem) : mpSystem(pSystem) {}
    virtual ~Integrator() { mpSystem = 0; }
    virtual int Step(void *pStart, void *pStep) = 0;
    virtual void Restore() = 0;

    IntegrableSystem *mpSystem;
};

/* Explicit Euler integrator. */
class EulerIntegrator : public Integrator {
public:
    EulerIntegrator(IntegrableSystem *pSystem, int count);
    virtual ~EulerIntegrator();
    virtual int Step(void *pStart, void *pStep);
    virtual void Restore();

    int mCount;
    float *mpState;
    float *mpNext;
    float *mpRate;
};

/* Decides whether a body may change its sleep state. */
class SleepFilter {
public:
    virtual int AllowStateChange(RigidBody_t *pBody, int wake) = 0;
};

/* Per-body hooks a body set calls on add, remove and each step. */
class BodyController {
public:
    virtual void AddBody(RigidBody_t *pBody) = 0;
    virtual void RemoveBody(RigidBody_t *pBody) = 0;
    virtual void UpdateSleepState(RigidBody_t *pBody, float dt) = 0;
};

/* Puts slow bodies to sleep and wakes moving ones. */
class SleepController : public BodyController {
public:
    SleepController(float sleepTime, float maxSpeed, SleepFilter *pFilter);
    virtual void AddBody(RigidBody_t *pBody);
    virtual void RemoveBody(RigidBody_t *pBody);
    virtual void UpdateSleepState(RigidBody_t *pBody, float dt);
    int IsBodyResting(RigidBody_t *pBody);

    float mSleepTime;
    float mMaxSpeed;
    SleepFilter *mpFilter;
};

SleepController::SleepController(float sleepTime, float maxSpeed, SleepFilter *pFilter)
    : mSleepTime(sleepTime), mMaxSpeed(maxSpeed), mpFilter(pFilter)
{
}

void SleepController::AddBody(RigidBody_t *pBody)
{
    float time = 0.0f;

    pBody->mUserData = *(int *)&time;
}

void SleepController::RemoveBody(RigidBody_t *pBody)
{
    pBody->mUserData = 0;
}

/* A body must stay below both motion limits before the sleep timer can advance. */
void SleepController::UpdateSleepState(RigidBody_t *pBody, float dt)
{
    int state = pBody->mState;
    float time = 0.0f;
    Vec3_801DE1E0 vel;
    float speedSq;
    float maxSpeed;
    float target;

    if (state == 2) {
        if (IsBodyResting(pBody)) {
            time = *(float *)&pBody->mUserData + dt;
            if (time > mSleepTime && (!mpFilter || mpFilter->AllowStateChange(pBody, 0))) {
                fn_801E9F0C(pBody, 3);
                time = 0.0f;
            }
        } else {
            speedSq = fn_80227120(&pBody->mUnknown114);
            maxSpeed = mMaxSpeed;
            if (speedSq > maxSpeed * maxSpeed) {
                target = maxSpeed * 0.95f;
                float speed = fn_80260B1C(speedSq);
                fn_80227264(&vel, &pBody->mUnknown07C, target / speed);
                fn_801E9C1C(pBody, &vel);
            }
        }
        pBody->mUserData = *(int *)&time;
    }
    if (state == 3 && !IsBodyResting(pBody) && (!mpFilter || mpFilter->AllowStateChange(pBody, 1))) {
        fn_801E9F0C(pBody, 2);
        time = 0.0f;
        pBody->mUserData = *(int *)&time;
    }
}

int SleepController::IsBodyResting(RigidBody_t *pBody)
{
    float limit = pBody->mUnknown048;
    float linearSq = fn_80227120(&pBody->mUnknown108);
    float angularSq = fn_80227120(&pBody->mUnknown114);

    if (linearSq <= limit && angularSq <= limit) {
        return 1;
    }
    return 0;
}

EulerIntegrator::EulerIntegrator(IntegrableSystem *pSystem, int count)
    : Integrator(pSystem), mCount(count), mpState(0), mpNext(0), mpRate(0)
{
    if (mCount) {
        mpState = new (0) float[mCount];
        mpNext = new (0) float[mCount];
        mpRate = new (0) float[mCount];
    }
}

EulerIntegrator::~EulerIntegrator()
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

int EulerIntegrator::Step(void *pStart, void *pStep)
{
    float dt = fn_801E8DBC(pStep, pStart);
    int result = mpSystem->GetState(mpState);
    unsigned int count;
    unsigned int i;
    float *pState;
    float *pRate;
    float *pNext;

    if (result) {
        count = mpSystem->GetDerivative(pStart, mpRate);
        pState = mpState;
        pRate = mpRate;
        pNext = mpNext;
        for (i = 0; i < count; i++) {
            *pNext++ = *pRate++ * dt + *pState++;
        }
        mpSystem->SetState(mpNext);
    }
    return result;
}

void EulerIntegrator::Restore()
{
    mpSystem->SetState(mpState);
}
