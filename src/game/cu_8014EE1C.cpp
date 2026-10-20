#include "game/Class_80148A58.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_802A56E8.h"
#include "game/Object_80039F5C.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_8007F828.h"
#include <string.h>

void *operator new(unsigned int size, int unknown);
void *operator new[](unsigned int size, int unknown);

class Class_802A2130 : public Class_802A56E8 {
public:
    virtual int vfn_01();
};

class Class_802A20C8 : public Class_80297BF8 {
public:
    virtual void vfn_07();
};

class Class_802A2058 : public Class_80297CE8 {
public:
    virtual void vfn_04(float dt);
    unsigned char mUnknown4;
};

class Class_802A2020 : public Class_80297AB8 {
public:
    virtual void vfn_03();
    unsigned char mUnknown4;
};

class Class_802A1F90 : public Class_80297C60 {
public:
    Class_802A1F90() : mpUnknown4(0), mpUnknown8(0), mUnknownC(1) {}
    virtual void vfn_03(float dt);
    Object_80039F5C *mpUnknown4;
    Object_80039F5C *mpUnknown8;
    unsigned char mUnknownC;
};

class Class_802A1F10 : public Class_80297B90 {
public:
    virtual void vfn_06();
};

class Record_8014F104 {
public:
    Record_8014F104() : mUnknown0(0), mUnknown4(0), mUnknown8(255)
    {
        memset(mUnknown12, 0, sizeof(mUnknown12));
    }
    virtual ~Record_8014F104();

    int mUnknown0;
    unsigned int mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
    char mUnknown12[40];
};

class Block_8014F104 {
public:
    Block_8014F104() : mUnknown2C(0), mUnknown30(1), mpUnknown34(0), mUnknown38(0), mpUnknown3C(0)
    {
        memset(mUnknown40, 0, sizeof(mUnknown40));
    }
    virtual ~Block_8014F104();

    Class_802A2130 mUnknown0;
    Class_802A20C8 mUnknown4;
    Class_802A2058 mUnknown8;
    Class_802A2020 mUnknown10;
    Class_802A1F90 mUnknown18;
    Class_802A1F10 mUnknown28;
    int mUnknown2C;
    unsigned char mUnknown30;
    Record_8014F104 *mpUnknown34;
    unsigned int mUnknown38;
    Object_80039F5C *mpUnknown3C;
    int mUnknown40[2][7];
};

class Class_802A2B68 : public Class_80148A58 {
public:
    Block_8014F104 *mpUnknown1C;
};

extern "C" {
extern Object_80039F5C *lbl_803EB2E0;

void fn_800BC51C(Class_80297BF8 *pObject);
void fn_800BFAB4(Class_80297CE8 *pObject);
void fn_800A039C(Class_80297AB8 *pObject);
void fn_800B9598(Class_80297C60 *pObject);
void fn_800AACB8(Class_80297B90 *pObject);
void fn_80178F20(Class_802A56E8 *pObject);

void fn_8014EE1C(Class_802A2B68 *p)
{
    Block_8014F104 *pBlock = new (0) Block_8014F104;
    p->mpUnknown1C = pBlock;
    lbl_803EB2E0 = 0;
    pBlock->mpUnknown34 = new (0) Record_8014F104[6];
    fn_80178F20(&p->mpUnknown1C->mUnknown0);
    fn_800BC51C(&p->mpUnknown1C->mUnknown4);
    fn_800BFAB4(&p->mpUnknown1C->mUnknown8);
    fn_800A039C(&p->mpUnknown1C->mUnknown10);
    fn_800B9598(&p->mpUnknown1C->mUnknown18);
    fn_800AACB8(&p->mpUnknown1C->mUnknown28);
    p->mpUnknown1C->mUnknown2C = fn_8007F828(14);
    if (p->mpUnknown1C->mUnknown2C != 1) {
        fn_8007F6F8(14, 1);
    }
}
}
