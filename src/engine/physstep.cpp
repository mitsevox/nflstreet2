/* Rigid-body physics stepping: the sleep controller that puts resting bodies to sleep and wakes
   them when they move, and the explicit Euler integrator over a system's state. */

#include "engine/rigidbody.h"
#include "engine/TibNew.h"

extern "C" {
float fn_80260B1C(float x);
float fn_801E8DBC(void *pEnd, void *pStart);
}

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
    virtual int AllowStateChange(RigidBody *pBody, int wake) = 0;
};

/* Puts slow bodies to sleep and wakes moving ones. */
class SleepController : public BodyController {
public:
    SleepController(float sleepTime, float maxSpeed, SleepFilter *pFilter);
    virtual void AddBody(RigidBody *pBody);
    virtual void RemoveBody(RigidBody *pBody);
    virtual void UpdateSleepState(RigidBody *pBody, float dt);
    int IsBodyResting(RigidBody *pBody);

    float mSleepTime;
    float mMaxSpeed;
    SleepFilter *mpFilter;
};

SleepController::SleepController(float sleepTime, float maxSpeed, SleepFilter *pFilter)
    : mSleepTime(sleepTime), mMaxSpeed(maxSpeed), mpFilter(pFilter)
{
}

void SleepController::AddBody(RigidBody *pBody)
{
    float time = 0.0f;

    pBody->mUserData = *(int *)&time;
}

void SleepController::RemoveBody(RigidBody *pBody)
{
    pBody->mUserData = 0;
}

/* A body must stay below both motion limits before the sleep timer can advance. */
void SleepController::UpdateSleepState(RigidBody *pBody, float dt)
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
                SetBodyMotionState(pBody, 3);
                time = 0.0f;
            }
        } else {
            speedSq = fn_80227120(&pBody->mAngularVelocity);
            maxSpeed = mMaxSpeed;
            if (speedSq > maxSpeed * maxSpeed) {
                target = maxSpeed * 0.95f;
                float speed = fn_80260B1C(speedSq);
                fn_80227264(&vel, &pBody->mAngularMomentum, target / speed);
                SetBodyAngularMomentum(pBody, &vel);
            }
        }
        pBody->mUserData = *(int *)&time;
    }
    if (state == 3 && !IsBodyResting(pBody) && (!mpFilter || mpFilter->AllowStateChange(pBody, 1))) {
        SetBodyMotionState(pBody, 2);
        time = 0.0f;
        pBody->mUserData = *(int *)&time;
    }
}

int SleepController::IsBodyResting(RigidBody *pBody)
{
    float limit = pBody->mRestLimit;
    float linearSq = fn_80227120(&pBody->mLinearVelocity);
    float angularSq = fn_80227120(&pBody->mAngularVelocity);

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
