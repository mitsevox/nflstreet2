#ifndef ENGINE_PHYSWORLD_H
#define ENGINE_PHYSWORLD_H

/* The rigid-body physics world (src/engine/physworld.cpp) and the body groups it steps
   (src/engine/cu_801E274C.cpp). */

#include "engine/rigidbody.h"
#include "engine/physconstraint.h"
#include "engine/phystime.h"

class PhysicsWorld;

/* Pool entry of a group: one body pointer. */
struct BodyGroupNode {
    RigidBody *mpMember;
};

/* Object at +8 of a group (defined in another file). */
class Class_801E299C {
public:
    int mUnknown0;

    virtual void vfn_01();
    virtual int vfn_02();
    virtual int vfn_03();
};

class Class_801E274C : public IntegrableSystem {
public:
    Class_801E274C();
    virtual ~Class_801E274C();
    virtual int vfn_05(int a, int b) = 0;
    virtual int vfn_06() = 0;
    void fn_801E279C(PhysicsWorld *pOwner);

    PhysicsWorld *mpOwner;
};

class BodyGroup : public Class_801E274C {
public:
    BodyGroup(int count);
    virtual int GetState(float *pState);
    virtual int SetState(float *pState);
    virtual int GetDerivative(void *pStart, float *pRate);
    virtual ~BodyGroup();
    virtual int vfn_05(int a, int b);
    virtual int vfn_06();
    virtual void vfn_07() = 0;
    virtual int vfn_08(int a, int b) = 0;
    void fn_801E2870(Class_801E299C *p);
    int fn_801E2878(RigidBody *pMember);
    int fn_801E28FC(RigidBody *pMember);
    BodyGroupNode *fn_801E2C3C();
    RigidBody *fn_801E2C64(BodyGroupNode **ppNode);

    Class_801E299C *mpUnknown8;
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
