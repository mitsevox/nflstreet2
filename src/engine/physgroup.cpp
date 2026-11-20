/* Body groups of the rigid-body physics world: a group keeps its bodies in a pool list, tells
   the world when a body joins or leaves, and is stepped as one integrable system, its state and
   derivative being those of its awake bodies one after another. */

#include "engine/dslist.h"
#include "engine/physworld.h"

extern "C" {
void *DSNewListNode(void *pool);
void *DSGetListNode(void *pool, void *item);
void DSRemoveListNode(void *pool, void *item);
void DSDelListNode(void *pool, void *item);
void *DSNextListNode(void *pool, void *item);
}

WorldSystem::WorldSystem() : mpOwner(0)
{
}

WorldSystem::~WorldSystem()
{
}

void WorldSystem::SetOwner(PhysicsWorld *pOwner)
{
    mpOwner = pOwner;
}

BodyGroup::BodyGroup(int count) : mpIntegrator(0), mpNodes(0), mUnknown10(1)
{
    mpNodes = DSNewList(1, 0, count, sizeof(BodyGroupNode), 0, 0);
}

BodyGroup::~BodyGroup()
{
    DSDelList(mpNodes);
    mpNodes = 0;
    mpIntegrator = 0;
}

void BodyGroup::SetIntegrator(Integrator *pIntegrator)
{
    mpIntegrator = pIntegrator;
}

int BodyGroup::AddBody(RigidBody *pMember)
{
    BodyGroupNode *pNode = (BodyGroupNode *)DSNewListNode(mpNodes);

    pNode->mpMember = pMember;
    if (DSAddListNode(mpNodes, pNode, 1) != pNode) {
        DSDelListNode(mpNodes, pNode);
        return 0;
    }
    if (mpOwner) {
        mpOwner->OnGroupBodyAdded(this, pMember);
    }
    return 1;
}

int BodyGroup::RemoveBody(RigidBody *pMember)
{
    BodyGroupNode *pNode;

    for (pNode = (BodyGroupNode *)DSGetListNode(mpNodes, 0); pNode;
         pNode = (BodyGroupNode *)DSNextListNode(mpNodes, pNode)) {
        if (pNode->mpMember == pMember) {
            break;
        }
    }
    if (pNode) {
        DSRemoveListNode(mpNodes, pNode);
        DSDelListNode(mpNodes, pNode);
        if (mpOwner) {
            mpOwner->OnGroupBodyRemoved(this, pMember);
        }
        return 1;
    }
    return 0;
}

int BodyGroup::Step(int start, int end)
{
    int stepped = mpIntegrator->Step((void *)start, (void *)end);
    int after = AfterStep(start, end);

    return stepped || after;
}

void BodyGroup::Restore()
{
    mpIntegrator->Restore();
}

int BodyGroup::GetState(float *pState)
{
    BodyGroupNode *pNode;
    int count = 0;
    int n;

    for (pNode = (BodyGroupNode *)DSGetListNode(mpNodes, 0); pNode;
         pNode = (BodyGroupNode *)DSNextListNode(mpNodes, pNode)) {
        if (pNode->mpMember->mState == 2) {
            n = pNode->mpMember->GetState(pState);
            count += n;
            pState += n;
        }
    }
    return count;
}

int BodyGroup::SetState(float *pState)
{
    BodyGroupNode *pNode;
    int count = 0;
    int n;

    for (pNode = (BodyGroupNode *)DSGetListNode(mpNodes, 0); pNode;
         pNode = (BodyGroupNode *)DSNextListNode(mpNodes, pNode)) {
        if (pNode->mpMember->mState == 2) {
            n = pNode->mpMember->SetState(pState);
            count += n;
            pState += n;
        }
    }
    return count;
}

int BodyGroup::GetDerivative(void *pStart, float *pRate)
{
    BodyGroupNode *pNode;
    int count = 0;
    int n;

    ApplyForces(pStart);
    for (pNode = (BodyGroupNode *)DSGetListNode(mpNodes, 0); pNode;
         pNode = (BodyGroupNode *)DSNextListNode(mpNodes, pNode)) {
        if (pNode->mpMember->mState == 2) {
            n = pNode->mpMember->GetDerivative(pStart, pRate);
            count += n;
            pRate += n;
        }
    }
    return count;
}

BodyGroupNode *BodyGroup::FirstNode()
{
    return (BodyGroupNode *)DSGetListNode(mpNodes, 0);
}

RigidBody *BodyGroup::NextBody(BodyGroupNode **ppNode)
{
    RigidBody *pMember = 0;

    if (*ppNode) {
        pMember = (*ppNode)->mpMember;
        *ppNode = (BodyGroupNode *)DSNextListNode(mpNodes, *ppNode);
    }
    return pMember;
}
