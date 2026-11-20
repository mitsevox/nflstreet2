#ifndef ENGINE_PHYSWORLD_H
#define ENGINE_PHYSWORLD_H

/* The rigid-body physics world (src/engine/physworld.cpp) and the body groups it steps
   (src/engine/physgroup.cpp). */

#include "engine/rigidbody.h"
#include "engine/physconstraint.h"
#include "engine/phystime.h"

class PhysicsWorld;

/* Pool entry of a group: one body pointer. */
struct BodyGroupNode {
    RigidBody *mpMember;
};

/* Steps a system's state vector through time (the interface src/engine/physstep.cpp defines
   for its EulerIntegrator). */
class Integrator {
public:
    virtual ~Integrator();
    virtual int Step(void *pStart, void *pStep) = 0;
    virtual void Restore() = 0;

    IntegrableSystem *mpSystem;
};

/* A system the physics world owns and steps. */
class WorldSystem : public IntegrableSystem {
public:
    WorldSystem();
    virtual ~WorldSystem();
    virtual int Step(int start, int end) = 0;
    virtual void Restore() = 0;
    void SetOwner(PhysicsWorld *pOwner);

    PhysicsWorld *mpOwner;
};

/* A group of rigid bodies stepped as one system by its integrator. */
class BodyGroup : public WorldSystem {
public:
    BodyGroup(int count);
    virtual int GetState(float *pState);
    virtual int SetState(float *pState);
    virtual int GetDerivative(void *pStart, float *pRate);
    virtual ~BodyGroup();
    virtual int Step(int start, int end);
    virtual void Restore();
    virtual void ApplyForces(void *pStart) = 0;
    virtual int AfterStep(int start, int end) = 0;
    void SetIntegrator(Integrator *pIntegrator);
    int AddBody(RigidBody *pMember);
    int RemoveBody(RigidBody *pMember);
    BodyGroupNode *FirstNode();
    RigidBody *NextBody(BodyGroupNode **ppNode);

    Integrator *mpIntegrator;
    void *mpNodes;
    unsigned char mUnknown10;
};

/* Collision system (defined in another file): slot 2 is called for each body that joins the
   world, slot 3 for each body that leaves it. */
class CollisionSystem {
public:
    virtual ~CollisionSystem();
    virtual void AddBody(RigidBody *pBody);
    virtual void RemoveBody(RigidBody *pBody);
    virtual void Update(float dt);
};

/* The physics world: its body groups and constraints, and the collision system and body
   controller told about every body that joins or leaves it. */
class PhysicsWorld {
public:
    PhysicsWorld(int groupCount, int constraintCount, CollisionSystem *pCollision,
                 BodyController *pController);
    virtual ~PhysicsWorld();
    int AddGroup(BodyGroup *pGroup);
    int RemoveGroup(BodyGroup *pGroup);
    void OnGroupBodyAdded(BodyGroup *pGroup, RigidBody *pMember);
    void OnGroupBodyRemoved(BodyGroup *pGroup, RigidBody *pMember);
    void NotifyBodyAdded(RigidBody *pMember);
    void NotifyBodyRemoved(RigidBody *pMember);
    int AddConstraint(Constraint *pConstraint);
    int RemoveConstraint(Constraint *pConstraint);
    void Step(PhysicsTime *pStart, PhysicsTime *pEnd);

    CollisionSystem *mpCollision;
    BodyController *mpController;
    void *mpGroups;
    void *mpConstraints;
};

#endif
