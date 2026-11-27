/* Simulation time of the rigid-body physics: a count of whole seconds plus the fraction of a
   second, set from and advanced by float seconds, and the elapsed time between two of them. The
   game keeps one for the world and steps it once per frame. */

#pragma implementation
#include "engine/phystime.h"

PhysicsTime::PhysicsTime()
{
    mIntegral = 0;
    mFraction = 0.0f;
}

PhysicsTime::PhysicsTime(float time)
{
    mIntegral = (unsigned int)time;
    mFraction = time - (float)mIntegral;
}

void PhysicsTime::SetSeconds(float time)
{
    mIntegral = (unsigned int)time;
    mFraction = time - (float)mIntegral;
}

float PhysicsTime::GetWholeSeconds() const
{
    return (float)mIntegral;
}

void PhysicsTime::AddSeconds(float delta)
{
    unsigned int whole = (unsigned int)delta;

    mIntegral += whole;
    mFraction += delta - (float)whole;
    if (mFraction >= 1.0f) {
        mIntegral++;
        mFraction -= 1.0f;
    }
}

float PhysTimeElapsed(const PhysicsTime *pEnd, const PhysicsTime *pStart)
{
    return (float)(pEnd->mIntegral - pStart->mIntegral) + (pEnd->mFraction - pStart->mFraction);
}
