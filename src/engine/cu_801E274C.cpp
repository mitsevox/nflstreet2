#include "engine/dslist.h"
#include "engine/physworld.h"

extern "C" {
void *DSNewListNode(void *pool);
void *DSGetListNode(void *pool, void *item);
void DSRemoveListNode(void *pool, void *item);
void DSDelListNode(void *pool, void *item);
void *DSNextListNode(void *pool, void *item);
}

Class_801E274C::Class_801E274C() : mpOwner(0)
{
}

Class_801E274C::~Class_801E274C()
{
}

void Class_801E274C::fn_801E279C(PhysicsWorld *pOwner)
{
    mpOwner = pOwner;
}

BodyGroup::BodyGroup(int count) : mpUnknown8(0), mpNodes(0), mUnknown10(1)
{
    mpNodes = DSNewList(1, 0, count, sizeof(BodyGroupNode), 0, 0);
}

BodyGroup::~BodyGroup()
{
    DSDelList(mpNodes);
    mpNodes = 0;
    mpUnknown8 = 0;
}

void BodyGroup::fn_801E2870(Class_801E299C *p)
{
    mpUnknown8 = p;
}

int BodyGroup::fn_801E2878(RigidBody *pMember)
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

int BodyGroup::fn_801E28FC(RigidBody *pMember)
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

int BodyGroup::vfn_05(int a, int b)
{
    int first = mpUnknown8->vfn_02();
    int second = vfn_08(a, b);

    return first || second;
}

int BodyGroup::vfn_06()
{
    return mpUnknown8->vfn_03();
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

    vfn_07();
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

BodyGroupNode *BodyGroup::fn_801E2C3C()
{
    return (BodyGroupNode *)DSGetListNode(mpNodes, 0);
}

RigidBody *BodyGroup::fn_801E2C64(BodyGroupNode **ppNode)
{
    RigidBody *pMember = 0;

    if (*ppNode) {
        pMember = (*ppNode)->mpMember;
        *ppNode = (BodyGroupNode *)DSNextListNode(mpNodes, *ppNode);
    }
    return pMember;
}
