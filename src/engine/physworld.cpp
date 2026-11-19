/* Rigid-body physics world: keeps the body groups and constraints the simulation steps, and tells
   the collision system and the body controller about every body that joins or leaves it. */

#include "engine/dslist.h"
#include "engine/physworld.h"

/* Pool entry of the group and constraint lists: one pointer. */
struct PhysicsWorldNode {
    void *mpItem;
};

extern "C" {
void *DSNewListNode(void *pool);
void *DSGetListNode(void *pool, void *item);
void DSRemoveListNode(void *pool, void *item);
void DSDelListNode(void *pool, void *item);
void *DSNextListNode(void *pool, void *item);
}

PhysicsWorld::PhysicsWorld(int groupCount, int constraintCount, CollisionSystem *pCollision,
                           BodyController *pController)
    : mpCollision(pCollision), mpController(pController), mpGroups(0), mpConstraints(0)
{
    if (groupCount) {
        mpGroups = DSNewList(1, 0, groupCount, sizeof(PhysicsWorldNode), 0, 0);
    }
    if (constraintCount) {
        mpConstraints = DSNewList(1, 0, constraintCount, sizeof(PhysicsWorldNode), 0, 0);
    }
}

PhysicsWorld::~PhysicsWorld()
{
    if (mpGroups) {
        DSDelList(mpGroups);
    }
    if (mpConstraints) {
        DSDelList(mpConstraints);
    }
    mpGroups = 0;
    mpConstraints = 0;
    mpCollision = 0;
}

int PhysicsWorld::AddGroup(BodyGroup *pGroup)
{
    PhysicsWorldNode *pNode = (PhysicsWorldNode *)DSNewListNode(mpGroups);
    BodyGroupNode *pIter;
    RigidBody *pMember;

    pNode->mpItem = pGroup;
    if (DSAddListNode(mpGroups, pNode, 1) != pNode) {
        DSDelListNode(mpGroups, pNode);
        return 0;
    }
    pIter = pGroup->fn_801E2C3C();
    for (pMember = pGroup->fn_801E2C64(&pIter); pMember;
         pMember = pGroup->fn_801E2C64(&pIter)) {
        NotifyBodyAdded(pMember);
    }
    pGroup->fn_801E279C(this);
    return 1;
}

int PhysicsWorld::RemoveGroup(BodyGroup *pGroup)
{
    PhysicsWorldNode *pNode;
    BodyGroupNode *pIter;
    RigidBody *pMember;

    for (pNode = (PhysicsWorldNode *)DSGetListNode(mpGroups, 0); pNode;
         pNode = (PhysicsWorldNode *)DSNextListNode(mpGroups, pNode)) {
        if (pNode->mpItem == pGroup) {
            break;
        }
    }
    if (pNode) {
        pIter = pGroup->fn_801E2C3C();
        for (pMember = pGroup->fn_801E2C64(&pIter); pMember;
         pMember = pGroup->fn_801E2C64(&pIter)) {
            NotifyBodyRemoved(pMember);
        }
        DSRemoveListNode(mpGroups, pNode);
        DSDelListNode(mpGroups, pNode);
        pGroup->fn_801E279C(0);
        return 1;
    }
    return 0;
}

void PhysicsWorld::OnGroupBodyAdded(BodyGroup *pGroup, RigidBody *pMember)
{
    NotifyBodyAdded(pMember);
}

void PhysicsWorld::OnGroupBodyRemoved(BodyGroup *pGroup, RigidBody *pMember)
{
    NotifyBodyRemoved(pMember);
}

void PhysicsWorld::NotifyBodyAdded(RigidBody *pMember)
{
    if (mpCollision) {
        mpCollision->AddBody(pMember);
    }
    if (mpController) {
        mpController->AddBody(pMember);
    }
}

void PhysicsWorld::NotifyBodyRemoved(RigidBody *pMember)
{
    if (mpCollision) {
        mpCollision->RemoveBody(pMember);
    }
    if (mpController) {
        mpController->RemoveBody(pMember);
    }
}

int PhysicsWorld::AddConstraint(Constraint *pConstraint)
{
    PhysicsWorldNode *pNode = (PhysicsWorldNode *)DSNewListNode(mpConstraints);

    pNode->mpItem = pConstraint;
    if (DSAddListNode(mpConstraints, pNode, 1) != pNode) {
        DSDelListNode(mpConstraints, pNode);
        return 0;
    }
    return 1;
}

int PhysicsWorld::RemoveConstraint(Constraint *pConstraint)
{
    PhysicsWorldNode *pNode;

    for (pNode = (PhysicsWorldNode *)DSGetListNode(mpConstraints, 0); pNode;
         pNode = (PhysicsWorldNode *)DSNextListNode(mpConstraints, pNode)) {
        if (pNode->mpItem == pConstraint) {
            break;
        }
    }
    if (pNode) {
        DSRemoveListNode(mpConstraints, pNode);
        DSDelListNode(mpConstraints, pNode);
        return 1;
    }
    return 0;
}

#if defined(DECOMP_COMPARE)
extern "C" float fn_801E8DBC(void *pEnd, void *pStart);

void PhysicsWorld::Step(PhysicsTime *pStart, PhysicsTime *pEnd)
{
    PhysicsTime end;
    PhysicsTime start;
    int moved = 0;
    // FAKEMATCH: never-set retry flag; stands for a compiled-out retry condition and gives the
    // target loop-back branch on a flag tested once before the first pass
    int repeat = 0;
    float dt;
    float stepDt;
    PhysicsWorldNode *pNode;
    int i;

    start = *pStart;
    end = *pEnd;
    dt = fn_801E8DBC(&end, &start);
    do {
        for (pNode = (PhysicsWorldNode *)DSGetListNode(mpGroups, 0); pNode;
             pNode = (PhysicsWorldNode *)DSNextListNode(mpGroups, pNode)) {
            if (((BodyGroup *)pNode->mpItem)->vfn_05((int)&start, (int)&end)) {
                moved = 1;
            }
        }
        stepDt = fn_801E8DBC(&end, &start);
        if (moved && mpCollision) {
            mpCollision->Update(stepDt);
        }
        i = 10;
        while (i--) {
            for (pNode = (PhysicsWorldNode *)DSGetListNode(mpConstraints, 0); pNode;
                 pNode = (PhysicsWorldNode *)DSNextListNode(mpConstraints, pNode)) {
                ((Constraint *)pNode->mpItem)->Solve(stepDt);
            }
        }
    } while (repeat);
    if (moved && mpController) {
        for (pNode = (PhysicsWorldNode *)DSGetListNode(mpGroups, 0); pNode;
             pNode = (PhysicsWorldNode *)DSNextListNode(mpGroups, pNode)) {
            BodyGroup *pGroup = (BodyGroup *)pNode->mpItem;
            BodyGroupNode *pIter = pGroup->fn_801E2C3C();
            RigidBody *pBody;

            for (pBody = pGroup->fn_801E2C64(&pIter); pBody; pBody = pGroup->fn_801E2C64(&pIter)) {
                mpController->UpdateSleepState(pBody, dt);
            }
        }
    }
}
#endif
