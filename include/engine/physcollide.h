#ifndef ENGINE_PHYSCOLLIDE_H
#define ENGINE_PHYSCOLLIDE_H

/* The collision system of the rigid-body physics world (src/engine/physcollide.cpp) and the
   handler interface the game implements to inspect its contacts. */

#include "engine/physworld.h"

class BroadPhase;

/* One contact between two bodies: the shape indices in each body's collection and the point. */
struct BodyContact {
    unsigned int mShapeA;
    unsigned int mShapeB;
    Vec3_801DE1E0 mPoint;
};

/* The game's collision handler: slot 1 vetoes a body pair, slot 2 sees the pair's contacts
   and chooses how they are resolved (3 skips the resolution). */
class CollisionHandler {
public:
    virtual int IgnorePair(RigidBody *pA, RigidBody *pB) = 0;
    virtual int OnContacts(float dt, RigidBody *pA, RigidBody *pB, unsigned int count,
                           BodyContact *pContacts) = 0;
    virtual void OnImpulse(RigidBody *pA, unsigned int shapeA, RigidBody *pB, unsigned int shapeB,
                           Vec3_801DE1E0 *pPointA, Vec3_801DE1E0 *pPointB,
                           Vec3_801DE1E0 *pImpulse) = 0;
};

/* The world's collision system: it keeps the broad phase, the contact buffer and its size, the
   depth limit and minimum test length, the game's collision handler and the position-correction
   limits. */
class ContactSystem : public CollisionSystem {
public:
    ContactSystem(unsigned int maxBodies, unsigned int maxContacts, float depthLimit,
                  float minTestLength, CollisionHandler *pHandler);
    virtual ~ContactSystem();
    virtual void AddBody(RigidBody *pBody);
    virtual void RemoveBody(RigidBody *pBody);
    virtual int Update(float dt);
    int CollidePair(RigidBody *pA, RigidBody *pB, float dt);
    void Respond(float dt, RigidBody *pA, RigidBody *pB, unsigned int count,
                 BodyContact *pContacts, int mode);
    void ApplyRollingFriction(RigidBody *pBody, float dt, Vec3_801DE1E0 *pPoint,
                              Vec3_801DE1E0 *pDirection);
    void SetCorrectionLimits(Vec3_801DE1E0 *pMin, Vec3_801DE1E0 *pMax);
    int ResolveContact(float dt, RigidBody *pA, RigidBody *pB, BodyContact *pContact,
                       Vec3_801DE1E0 *pImpulse, Vec3_801DE1E0 *pFriction,
                       Vec3_801DE1E0 *pCorrection, Vec3_801DE1E0 *pPointA,
                       Vec3_801DE1E0 *pPointB, Vec3_801DE1E0 *pNormal);

    BroadPhase *mpBroadPhase;
    unsigned int mMaxContacts;
    BodyContact *mpContacts;
    float mDepthLimit;
    float mMinTestLength;
    CollisionHandler *mpHandler;
    Vec3_801DE1E0 mCorrectionMin;
    Vec3_801DE1E0 mCorrectionMax;
};

#endif
