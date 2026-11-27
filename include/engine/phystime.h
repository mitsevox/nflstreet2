#ifndef ENGINE_PHYSTIME_H
#define ENGINE_PHYSTIME_H

#pragma interface

/* Simulation time of the rigid-body physics: whole seconds and a fraction. */
class PhysicsTime {
public:
    PhysicsTime();
    PhysicsTime(float time);
    virtual ~PhysicsTime() {}
    void SetSeconds(float time);
    float GetWholeSeconds() const;
    void AddSeconds(float delta);

    unsigned int mIntegral;
    float mFraction;
};

float PhysTimeElapsed(const PhysicsTime *pEnd, const PhysicsTime *pStart);

#endif
