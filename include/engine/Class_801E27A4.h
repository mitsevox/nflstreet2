#ifndef ENGINE_CLASS_801E27A4_H
#define ENGINE_CLASS_801E27A4_H

/* Member containers (src/engine/cu_801E274C.cpp) and the set that owns them
   (src/engine/cu_801E8E04.cpp). */

class Class_801E8E04;

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

class Class_801E274C : public Class_801E2A60 {
public:
    Class_801E274C();
    virtual ~Class_801E274C();
    virtual int vfn_05(int a, int b) = 0;
    virtual int vfn_06() = 0;
    void fn_801E279C(Class_801E8E04 *pOwner);

    Class_801E8E04 *mpOwner;
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

/* Observer: slot 2 is called for each member of a container added to the set,
   slot 3 for each member of a container removed (defined in another file). */
class Class_801E90F0 {
public:
    virtual void vfn_01(Class_801E2878 *pMember);
    virtual void vfn_02(Class_801E2878 *pMember);
    virtual void vfn_03(Class_801E2878 *pMember);
};

/* Second observer: slots 1 and 2 are called in the same places (defined in
   another file). */
class Class_801E9114 {
public:
    virtual void vfn_01(Class_801E2878 *pMember);
    virtual void vfn_02(Class_801E2878 *pMember);
};

/* Set of member containers and other objects, with two observers. */
class Class_801E8E04 {
public:
    Class_801E8E04(int groupCount, int objectCount, Class_801E90F0 *pObserverA,
                   Class_801E9114 *pObserverB);
    virtual ~Class_801E8E04();
    int fn_801E8F1C(Class_801E27A4 *pGroup);
    int fn_801E8FD4(Class_801E27A4 *pGroup);
    void fn_801E90A8(Class_801E27A4 *pGroup, Class_801E2878 *pMember);
    void fn_801E90CC(Class_801E27A4 *pGroup, Class_801E2878 *pMember);
    void fn_801E90F0(Class_801E2878 *pMember);
    void fn_801E9168(Class_801E2878 *pMember);
    int fn_801E91E0(void *pObject);
    int fn_801E9248(void *pObject);

    Class_801E90F0 *mpObserverA;
    Class_801E9114 *mpObserverB;
    void *mpGroups;
    void *mpObjects;
};

#endif
