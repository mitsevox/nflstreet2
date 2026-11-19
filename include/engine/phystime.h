#ifndef ENGINE_PHYSTIME_H
#define ENGINE_PHYSTIME_H

/* Simulation time of the rigid-body physics: whole ticks and a fraction. */
class PhysicsTime {
public:
    PhysicsTime();
    virtual ~PhysicsTime();
    void fn_801E8D14(float delta);

    unsigned int mIntegral;
    float mFraction;
};

#endif
