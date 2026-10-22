#include "game/fn_801C68FC.h"

/* Interface shared by containers and their members. */
class Class_801E2A60 {
public:
    virtual int vfn_01(void **ppOut) = 0;
    virtual int vfn_02(void **ppOut) = 0;
    virtual int vfn_03(int a, void **ppOut) = 0;
};

/* Member object kept by a container (defined in another file). */
class Class_801E2878 : public Class_801E2A60 {
public:
    char mUnknown004[0x138 - 4];
    int mType;
};

/* Pool entry of a container: one member pointer. */
struct Node_801E2878 {
    Class_801E2878 *mpMember;
};

/* Object at +8 of a container (defined in another file). */
class Class_801E299C {
public:
    int mUnknown0;

    virtual void vfn_01();
    virtual int vfn_02();
    virtual int vfn_03();
};

struct Owner_801E90A8;

extern "C" {
void *fn_801C6A20(void *pool);
void *fn_801C6B4C(void *pool, void *item);
void fn_801C6BC0(void *pool, void *item);
void fn_801C6C0C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
}

class Class_801E274C : public Class_801E2A60 {
public:
    Class_801E274C();
    virtual ~Class_801E274C();
    virtual int vfn_05(int a, int b) = 0;
    virtual int vfn_06() = 0;
    void fn_801E279C(Owner_801E90A8 *pOwner);

    Owner_801E90A8 *mpOwner;
};

class Class_801E27A4 : public Class_801E274C {
public:
    Class_801E27A4(int count);
    virtual int vfn_01(void **ppOut);
    virtual int vfn_02(void **ppOut);
    virtual int vfn_03(int a, void **ppOut);
    virtual ~Class_801E27A4();
    virtual int vfn_05(int a, int b);
    virtual int vfn_06();
    virtual void vfn_07() = 0;
    virtual int vfn_08(int a, int b) = 0;
    void fn_801E2870(Class_801E299C *p);
    int fn_801E2878(Class_801E2878 *pMember);
    int fn_801E28FC(Class_801E2878 *pMember);
    Node_801E2878 *fn_801E2C3C();
    Class_801E2878 *fn_801E2C64(Node_801E2878 **ppNode);

    Class_801E299C *mpUnknown8;
    void *mpNodes;
    unsigned char mUnknown10;
};

extern "C" {
void fn_801E90A8(Owner_801E90A8 *pOwner, Class_801E27A4 *pContainer, Class_801E2878 *pMember);
void fn_801E90CC(Owner_801E90A8 *pOwner, Class_801E27A4 *pContainer, Class_801E2878 *pMember);
}

Class_801E274C::Class_801E274C() : mpOwner(0)
{
}

Class_801E274C::~Class_801E274C()
{
}

void Class_801E274C::fn_801E279C(Owner_801E90A8 *pOwner)
{
    mpOwner = pOwner;
}

Class_801E27A4::Class_801E27A4(int count) : mpUnknown8(0), mpNodes(0), mUnknown10(1)
{
    mpNodes = fn_801C68FC(1, 0, count, sizeof(Node_801E2878), 0, 0);
}

Class_801E27A4::~Class_801E27A4()
{
    fn_801C69E4(mpNodes);
    mpNodes = 0;
    mpUnknown8 = 0;
}

void Class_801E27A4::fn_801E2870(Class_801E299C *p)
{
    mpUnknown8 = p;
}

int Class_801E27A4::fn_801E2878(Class_801E2878 *pMember)
{
    Node_801E2878 *pNode = (Node_801E2878 *)fn_801C6A20(mpNodes);

    pNode->mpMember = pMember;
    if (fn_801C6AA4(mpNodes, pNode, 1) != pNode) {
        fn_801C6C0C(mpNodes, pNode);
        return 0;
    }
    if (mpOwner) {
        fn_801E90A8(mpOwner, this, pMember);
    }
    return 1;
}

int Class_801E27A4::fn_801E28FC(Class_801E2878 *pMember)
{
    Node_801E2878 *pNode;

    for (pNode = (Node_801E2878 *)fn_801C6B4C(mpNodes, 0); pNode;
         pNode = (Node_801E2878 *)fn_801C6C84(mpNodes, pNode)) {
        if (pNode->mpMember == pMember) {
            break;
        }
    }
    if (pNode) {
        fn_801C6BC0(mpNodes, pNode);
        fn_801C6C0C(mpNodes, pNode);
        if (mpOwner) {
            fn_801E90CC(mpOwner, this, pMember);
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

    for (pNode = (Node_801E2878 *)fn_801C6B4C(mpNodes, 0); pNode;
         pNode = (Node_801E2878 *)fn_801C6C84(mpNodes, pNode)) {
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

    for (pNode = (Node_801E2878 *)fn_801C6B4C(mpNodes, 0); pNode;
         pNode = (Node_801E2878 *)fn_801C6C84(mpNodes, pNode)) {
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
    for (pNode = (Node_801E2878 *)fn_801C6B4C(mpNodes, 0); pNode;
         pNode = (Node_801E2878 *)fn_801C6C84(mpNodes, pNode)) {
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
    return (Node_801E2878 *)fn_801C6B4C(mpNodes, 0);
}

Class_801E2878 *Class_801E27A4::fn_801E2C64(Node_801E2878 **ppNode)
{
    Class_801E2878 *pMember = 0;

    if (*ppNode) {
        pMember = (*ppNode)->mpMember;
        *ppNode = (Node_801E2878 *)fn_801C6C84(mpNodes, *ppNode);
    }
    return pMember;
}
