#include "game/Class_80148A58.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_802A56E8.h"
#include "game/Object_80039F5C.h"
#include "game/fn_8007F6F8.h"

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
    virtual ~Record_8014F104();

    int mUnknown0;
    unsigned int mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
    char mUnknown12[40];
};

class Block_8014F104 {
public:
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

typedef void (*Callback_800D7604)(int, int, const char *, int, int, int, int);

extern "C" {
void fn_800BC51C(Class_80297BF8 *pObject);
void fn_800BFAB4(Class_80297CE8 *pObject);
void fn_800A039C(Class_80297AB8 *pObject);
void fn_800B9598(Class_80297C60 *pObject);
void fn_800AACB8(Class_80297B90 *pObject);
void fn_80178F20(Class_802A56E8 *pObject);
void fn_800A8738(unsigned char value);
int fn_8005FC7C(void);
void fn_8006088C(int value);
int fn_8014FF34(Class_802A2B68 *p);
int fn_80149014(Class_802A2B68 *p);
void fn_8014DA90(Class_802A2B68 *p);
void fn_800D7604(Callback_800D7604 a);

void fn_8014EFC0(Class_802A2B68 *p)
{
    fn_800A8738(0);
    if (p->mpUnknown1C->mUnknown2C != 1) {
        fn_8007F6F8(14, p->mpUnknown1C->mUnknown2C);
    }
    if (fn_8005FC7C()) {
        fn_8006088C(fn_8014FF34(p));
    }
    if (fn_80149014(p)) {
        fn_8014DA90(p);
    }
    fn_800D7604(0);
    fn_80178F20(0);
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_800AACB8(0);
    delete[] p->mpUnknown1C->mpUnknown34;
    delete p->mpUnknown1C;
    p->mpUnknown1C = 0;
}
}
