#include "game/fn_801C68FC.h"

/* Member object of a group (defined in another file). */
struct Member_801E8E04;

/* Pool entry: one pointer. */
struct Node_801E8E04 {
    void *mpItem;
};

/* Group of members (defined in another file). */
struct Group_801E8E04;

/* Observer told when members enter or leave the world (defined in another file). */
class Class_801E90F0 {
public:
    virtual void vfn_01(Member_801E8E04 *pMember);
    virtual void vfn_02(Member_801E8E04 *pMember);
    virtual void vfn_03(Member_801E8E04 *pMember);
};

/* Second observer (defined in another file). */
class Class_801E9114 {
public:
    virtual void vfn_01(Member_801E8E04 *pMember);
    virtual void vfn_02(Member_801E8E04 *pMember);
};

extern "C" {
void *fn_801C6A20(void *pool);
void *fn_801C6B4C(void *pool, void *item);
void fn_801C6BC0(void *pool, void *item);
void fn_801C6C0C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
void fn_801E279C(Group_801E8E04 *pGroup, void *pOwner);
Node_801E8E04 *fn_801E2C3C(Group_801E8E04 *pGroup);
Member_801E8E04 *fn_801E2C64(Group_801E8E04 *pGroup, Node_801E8E04 **ppNode);
}

/* Set of member groups and other objects, with two observers. */
class Class_801E8E04 {
public:
    Class_801E8E04(int groupCount, int objectCount, Class_801E90F0 *pObserverA,
                   Class_801E9114 *pObserverB);
    virtual ~Class_801E8E04();
    int fn_801E8F1C(Group_801E8E04 *pGroup);
    int fn_801E8FD4(Group_801E8E04 *pGroup);
    void fn_801E90A8(Group_801E8E04 *pGroup, Member_801E8E04 *pMember);
    void fn_801E90CC(Group_801E8E04 *pGroup, Member_801E8E04 *pMember);
    void fn_801E90F0(Member_801E8E04 *pMember);
    void fn_801E9168(Member_801E8E04 *pMember);
    int fn_801E91E0(void *pObject);
    int fn_801E9248(void *pObject);

    Class_801E90F0 *mpObserverA;
    Class_801E9114 *mpObserverB;
    void *mpGroups;
    void *mpObjects;
};

Class_801E8E04::Class_801E8E04(int groupCount, int objectCount, Class_801E90F0 *pObserverA,
                               Class_801E9114 *pObserverB)
    : mpObserverA(pObserverA), mpObserverB(pObserverB), mpGroups(0), mpObjects(0)
{
    if (groupCount) {
        mpGroups = fn_801C68FC(1, 0, groupCount, sizeof(Node_801E8E04), 0, 0);
    }
    if (objectCount) {
        mpObjects = fn_801C68FC(1, 0, objectCount, sizeof(Node_801E8E04), 0, 0);
    }
}

Class_801E8E04::~Class_801E8E04()
{
    if (mpGroups) {
        fn_801C69E4(mpGroups);
    }
    if (mpObjects) {
        fn_801C69E4(mpObjects);
    }
    mpGroups = 0;
    mpObjects = 0;
    mpObserverA = 0;
}

int Class_801E8E04::fn_801E8F1C(Group_801E8E04 *pGroup)
{
    Node_801E8E04 *pNode = (Node_801E8E04 *)fn_801C6A20(mpGroups);
    Node_801E8E04 *pIter;
    Member_801E8E04 *pMember;

    pNode->mpItem = pGroup;
    if (fn_801C6AA4(mpGroups, pNode, 1) != pNode) {
        fn_801C6C0C(mpGroups, pNode);
        return 0;
    }
    pIter = fn_801E2C3C(pGroup);
    for (pMember = fn_801E2C64(pGroup, &pIter); pMember;
         pMember = fn_801E2C64(pGroup, &pIter)) {
        fn_801E90F0(pMember);
    }
    fn_801E279C(pGroup, this);
    return 1;
}

int Class_801E8E04::fn_801E8FD4(Group_801E8E04 *pGroup)
{
    Node_801E8E04 *pNode;
    Node_801E8E04 *pIter;
    Member_801E8E04 *pMember;

    for (pNode = (Node_801E8E04 *)fn_801C6B4C(mpGroups, 0); pNode;
         pNode = (Node_801E8E04 *)fn_801C6C84(mpGroups, pNode)) {
        if (pNode->mpItem == pGroup) {
            break;
        }
    }
    if (pNode) {
        pIter = fn_801E2C3C(pGroup);
        for (pMember = fn_801E2C64(pGroup, &pIter); pMember;
         pMember = fn_801E2C64(pGroup, &pIter)) {
            fn_801E9168(pMember);
        }
        fn_801C6BC0(mpGroups, pNode);
        fn_801C6C0C(mpGroups, pNode);
        fn_801E279C(pGroup, 0);
        return 1;
    }
    return 0;
}

void Class_801E8E04::fn_801E90A8(Group_801E8E04 *pGroup, Member_801E8E04 *pMember)
{
    fn_801E90F0(pMember);
}

void Class_801E8E04::fn_801E90CC(Group_801E8E04 *pGroup, Member_801E8E04 *pMember)
{
    fn_801E9168(pMember);
}

void Class_801E8E04::fn_801E90F0(Member_801E8E04 *pMember)
{
    if (mpObserverA) {
        mpObserverA->vfn_02(pMember);
    }
    if (mpObserverB) {
        mpObserverB->vfn_01(pMember);
    }
}

void Class_801E8E04::fn_801E9168(Member_801E8E04 *pMember)
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
    Node_801E8E04 *pNode = (Node_801E8E04 *)fn_801C6A20(mpObjects);

    pNode->mpItem = pObject;
    if (fn_801C6AA4(mpObjects, pNode, 1) != pNode) {
        fn_801C6C0C(mpObjects, pNode);
        return 0;
    }
    return 1;
}

int Class_801E8E04::fn_801E9248(void *pObject)
{
    Node_801E8E04 *pNode;

    for (pNode = (Node_801E8E04 *)fn_801C6B4C(mpObjects, 0); pNode;
         pNode = (Node_801E8E04 *)fn_801C6C84(mpObjects, pNode)) {
        if (pNode->mpItem == pObject) {
            break;
        }
    }
    if (pNode) {
        fn_801C6BC0(mpObjects, pNode);
        fn_801C6C0C(mpObjects, pNode);
        return 1;
    }
    return 0;
}
