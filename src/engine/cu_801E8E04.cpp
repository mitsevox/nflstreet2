#include "engine/dslist.h"
#include "engine/Class_801E27A4.h"

/* Pool entry: one pointer. */
struct Node_801E8E04 {
    void *mpItem;
};

extern "C" {
void *DSNewListNode(void *pool);
void *DSGetListNode(void *pool, void *item);
void DSRemoveListNode(void *pool, void *item);
void DSDelListNode(void *pool, void *item);
void *DSNextListNode(void *pool, void *item);
}

Class_801E8E04::Class_801E8E04(int groupCount, int objectCount, Class_801E90F0 *pObserverA,
                               Class_801E9114 *pObserverB)
    : mpObserverA(pObserverA), mpObserverB(pObserverB), mpGroups(0), mpObjects(0)
{
    if (groupCount) {
        mpGroups = DSNewList(1, 0, groupCount, sizeof(Node_801E8E04), 0, 0);
    }
    if (objectCount) {
        mpObjects = DSNewList(1, 0, objectCount, sizeof(Node_801E8E04), 0, 0);
    }
}

Class_801E8E04::~Class_801E8E04()
{
    if (mpGroups) {
        DSDelList(mpGroups);
    }
    if (mpObjects) {
        DSDelList(mpObjects);
    }
    mpGroups = 0;
    mpObjects = 0;
    mpObserverA = 0;
}

int Class_801E8E04::fn_801E8F1C(Class_801E27A4 *pGroup)
{
    Node_801E8E04 *pNode = (Node_801E8E04 *)DSNewListNode(mpGroups);
    Node_801E2878 *pIter;
    Class_801E2878 *pMember;

    pNode->mpItem = pGroup;
    if (DSAddListNode(mpGroups, pNode, 1) != pNode) {
        DSDelListNode(mpGroups, pNode);
        return 0;
    }
    pIter = pGroup->fn_801E2C3C();
    for (pMember = pGroup->fn_801E2C64(&pIter); pMember;
         pMember = pGroup->fn_801E2C64(&pIter)) {
        fn_801E90F0(pMember);
    }
    pGroup->fn_801E279C(this);
    return 1;
}

int Class_801E8E04::fn_801E8FD4(Class_801E27A4 *pGroup)
{
    Node_801E8E04 *pNode;
    Node_801E2878 *pIter;
    Class_801E2878 *pMember;

    for (pNode = (Node_801E8E04 *)DSGetListNode(mpGroups, 0); pNode;
         pNode = (Node_801E8E04 *)DSNextListNode(mpGroups, pNode)) {
        if (pNode->mpItem == pGroup) {
            break;
        }
    }
    if (pNode) {
        pIter = pGroup->fn_801E2C3C();
        for (pMember = pGroup->fn_801E2C64(&pIter); pMember;
         pMember = pGroup->fn_801E2C64(&pIter)) {
            fn_801E9168(pMember);
        }
        DSRemoveListNode(mpGroups, pNode);
        DSDelListNode(mpGroups, pNode);
        pGroup->fn_801E279C(0);
        return 1;
    }
    return 0;
}

void Class_801E8E04::fn_801E90A8(Class_801E27A4 *pGroup, Class_801E2878 *pMember)
{
    fn_801E90F0(pMember);
}

void Class_801E8E04::fn_801E90CC(Class_801E27A4 *pGroup, Class_801E2878 *pMember)
{
    fn_801E9168(pMember);
}

void Class_801E8E04::fn_801E90F0(Class_801E2878 *pMember)
{
    if (mpObserverA) {
        mpObserverA->vfn_02(pMember);
    }
    if (mpObserverB) {
        mpObserverB->vfn_01(pMember);
    }
}

void Class_801E8E04::fn_801E9168(Class_801E2878 *pMember)
{
    if (mpObserverA) {
        mpObserverA->vfn_03(pMember);
    }
    if (mpObserverB) {
        mpObserverB->vfn_02(pMember);
    }
}

int Class_801E8E04::fn_801E91E0(void *pObject)
{
    Node_801E8E04 *pNode = (Node_801E8E04 *)DSNewListNode(mpObjects);

    pNode->mpItem = pObject;
    if (DSAddListNode(mpObjects, pNode, 1) != pNode) {
        DSDelListNode(mpObjects, pNode);
        return 0;
    }
    return 1;
}

int Class_801E8E04::fn_801E9248(void *pObject)
{
    Node_801E8E04 *pNode;

    for (pNode = (Node_801E8E04 *)DSGetListNode(mpObjects, 0); pNode;
         pNode = (Node_801E8E04 *)DSNextListNode(mpObjects, pNode)) {
        if (pNode->mpItem == pObject) {
            break;
        }
    }
    if (pNode) {
        DSRemoveListNode(mpObjects, pNode);
        DSDelListNode(mpObjects, pNode);
        return 1;
    }
    return 0;
}
