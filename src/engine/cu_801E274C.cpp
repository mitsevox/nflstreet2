#include "engine/dslist.h"
#include "engine/Class_801E27A4.h"

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

void Class_801E274C::fn_801E279C(Class_801E8E04 *pOwner)
{
    mpOwner = pOwner;
}

Class_801E27A4::Class_801E27A4(int count) : mpUnknown8(0), mpNodes(0), mUnknown10(1)
{
    mpNodes = DSNewList(1, 0, count, sizeof(Node_801E2878), 0, 0);
}

Class_801E27A4::~Class_801E27A4()
{
    DSDelList(mpNodes);
    mpNodes = 0;
    mpUnknown8 = 0;
}

void Class_801E27A4::fn_801E2870(Class_801E299C *p)
{
    mpUnknown8 = p;
}

int Class_801E27A4::fn_801E2878(Class_801E2878 *pMember)
{
    Node_801E2878 *pNode = (Node_801E2878 *)DSNewListNode(mpNodes);

    pNode->mpMember = pMember;
    if (DSAddListNode(mpNodes, pNode, 1) != pNode) {
        DSDelListNode(mpNodes, pNode);
        return 0;
    }
    if (mpOwner) {
        mpOwner->fn_801E90A8(this, pMember);
    }
    return 1;
}

int Class_801E27A4::fn_801E28FC(Class_801E2878 *pMember)
{
    Node_801E2878 *pNode;

    for (pNode = (Node_801E2878 *)DSGetListNode(mpNodes, 0); pNode;
         pNode = (Node_801E2878 *)DSNextListNode(mpNodes, pNode)) {
        if (pNode->mpMember == pMember) {
            break;
        }
    }
    if (pNode) {
        DSRemoveListNode(mpNodes, pNode);
        DSDelListNode(mpNodes, pNode);
        if (mpOwner) {
            mpOwner->fn_801E90CC(this, pMember);
        }
        return 1;
    }
    return 0;
}

int Class_801E27A4::vfn_05(int a, int b)
{
    int first = mpUnknown8->vfn_02();
    int second = vfn_08(a, b);

    return first || second;
}

int Class_801E27A4::vfn_06()
{
    return mpUnknown8->vfn_03();
}

int Class_801E27A4::vfn_01(void **ppOut)
{
    Node_801E2878 *pNode;
    int count = 0;
    int n;

    for (pNode = (Node_801E2878 *)DSGetListNode(mpNodes, 0); pNode;
         pNode = (Node_801E2878 *)DSNextListNode(mpNodes, pNode)) {
        if (pNode->mpMember->mType == 2) {
            n = pNode->mpMember->vfn_01(ppOut);
            count += n;
            ppOut += n;
        }
    }
    return count;
}

int Class_801E27A4::vfn_02(void **ppOut)
{
    Node_801E2878 *pNode;
    int count = 0;
    int n;

    for (pNode = (Node_801E2878 *)DSGetListNode(mpNodes, 0); pNode;
         pNode = (Node_801E2878 *)DSNextListNode(mpNodes, pNode)) {
        if (pNode->mpMember->mType == 2) {
            n = pNode->mpMember->vfn_02(ppOut);
            count += n;
            ppOut += n;
        }
    }
    return count;
}

int Class_801E27A4::vfn_03(int a, void **ppOut)
{
    Node_801E2878 *pNode;
    int count = 0;
    int n;

    vfn_07();
    for (pNode = (Node_801E2878 *)DSGetListNode(mpNodes, 0); pNode;
         pNode = (Node_801E2878 *)DSNextListNode(mpNodes, pNode)) {
        if (pNode->mpMember->mType == 2) {
            n = pNode->mpMember->vfn_03(a, ppOut);
            count += n;
            ppOut += n;
        }
    }
    return count;
}

Node_801E2878 *Class_801E27A4::fn_801E2C3C()
{
    return (Node_801E2878 *)DSGetListNode(mpNodes, 0);
}

Class_801E2878 *Class_801E27A4::fn_801E2C64(Node_801E2878 **ppNode)
{
    Class_801E2878 *pMember = 0;

    if (*ppNode) {
        pMember = (*ppNode)->mpMember;
        *ppNode = (Node_801E2878 *)DSNextListNode(mpNodes, *ppNode);
    }
    return pMember;
}
