#include "game/Class_80148A58.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_802A56E8.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_8007F828.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80238174.h"
#include <string.h>

void *operator new(unsigned int size, int unknown);

class Class_802A1DC8 : public Class_80297BF8 {
public:
    Class_802A1DC8() : mUnknown4(1) {}
    virtual void vfn_07();
    unsigned char mUnknown4;
};

class Class_802A1D58 : public Class_80297CE8 {
public:
    virtual void vfn_04(float dt);
};

class Class_802A1D20 : public Class_80297AB8 {
public:
    virtual void vfn_03();
    unsigned char mUnknown4;
    char mUnknown5[3];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

class Class_802A1C98 : public Class_80297C60 {
public:
    virtual void vfn_05();
};

class Class_802A1C30 : public Class_80297B90 {
public:
    virtual void vfn_06();
};

class Class_802A1E38 : public Class_802A56E8 {
public:
    virtual int vfn_01();
};

struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    char mUnknown12[8];
};

struct Table_8015005C {
    Entry_8015005C mEntries[5];
    char mUnknown100[16];
    unsigned char mUnknown116;
    unsigned char mUnknown117;
    unsigned char mCount;
    unsigned char mUnknown119;
    int mUnknown120;
    unsigned char mUnknown124;
    unsigned char mUnknown125;
    unsigned char mUnknown126;
};

struct Object_8015005C {
    Class_802A1DC8 mUnknown0;
    Class_802A1D58 mUnknown8;
    Class_802A1D20 mUnknown12;
    Class_802A1C98 mUnknown24;
    Class_802A1C30 mUnknown28;
    Class_802A1E38 mUnknown32;
    Table_8015005C *mpUnknown36;
};

class Class_802A2918 : public Class_80148A58 {
public:
    Object_8015005C *mpUnknown1C;
};

extern "C" {
void fn_800BC51C(Class_80297BF8 *pObject);
void fn_800BFAB4(Class_80297CE8 *pObject);
void fn_800A039C(Class_80297AB8 *pObject);
void fn_800B9598(Class_80297C60 *pObject);
void fn_800AACB8(Class_80297B90 *pObject);
void fn_80178F20(Class_802A56E8 *pObject);
int fn_80149014(void);
void *fn_8023816C(void *pHandle);
void fn_8016306C(unsigned char value);

void fn_80151858(Class_802A2918 *p)
{
    void *pHandle = 0;
    int allocate = fn_80149014() == 0;
    Table_8015005C *pTable;

    p->mpUnknown1C = new (0) Object_8015005C;
    if (allocate) {
        pHandle = fn_80238174(0, (void **)&p->mpUnknown1C->mpUnknown36, sizeof(Table_8015005C), 0, 0x4D474A42);
        pTable = (Table_8015005C *)fn_8023816C(pHandle);
    } else {
        p->mpUnknown1C->mpUnknown36 = (Table_8015005C *)fn_801D2B7C(sizeof(Table_8015005C), 0, 0);
        pTable = p->mpUnknown1C->mpUnknown36;
    }
    memset(pTable, 0, sizeof(Table_8015005C));
    pTable->mCount = 4;
    pTable->mUnknown119 = 3;
    pTable->mUnknown125 = 2;
    pTable->mUnknown124 = 0;
    pTable->mUnknown126 = 0;
    pTable->mUnknown120 = fn_8007F828(14);
    if (pTable->mUnknown120 != 0) {
        fn_8007F6F8(14, 0);
    }
    if (allocate) {
        fn_802381E0(pHandle);
    }
    fn_80178F20(&p->mpUnknown1C->mUnknown32);
    fn_800BC51C(&p->mpUnknown1C->mUnknown0);
    fn_800BFAB4(&p->mpUnknown1C->mUnknown8);
    fn_800A039C(&p->mpUnknown1C->mUnknown12);
    fn_800B9598(&p->mpUnknown1C->mUnknown24);
    fn_800AACB8(&p->mpUnknown1C->mUnknown28);
    p->mpUnknown1C->mpUnknown36->mUnknown116 = fn_8007F828(19);
    if (p->mpUnknown1C->mpUnknown36->mUnknown116 != 0) {
        fn_8007F6F8(19, 0);
    }
    fn_8016306C(0);
}
}
