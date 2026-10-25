#include "game/Class_80148A58.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_802A56E8.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_801D2B7C.h"

class Class_802A1DC8 : public Class_80297BF8 {
public:
    virtual void vfn_07();
    virtual ~Class_802A1DC8() {}
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
    virtual ~Class_802A1E38() {}
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
    unsigned int mUnknown32;
    int mUnknown36;
    int mUnknown40;
};

extern "C" {
void fn_800BC51C(Class_80297BF8 *pObject);
void fn_800BFAB4(Class_80297CE8 *pObject);
void fn_800A039C(Class_80297AB8 *pObject);
void fn_800B9598(Class_80297C60 *pObject);
void fn_800AACB8(Class_80297B90 *pObject);
void fn_80178F20(Class_802A56E8 *pObject);
int fn_80149014(Class_802A2918 *p);
void fn_8016306C(unsigned char value);

void fn_80151A28(Class_802A2918 *p)
{
    fn_8016306C(1);
    if (p->mpUnknown1C->mpUnknown36->mUnknown116 != 0) {
        fn_8007F6F8(19, 1);
    }
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_800AACB8(0);
    if (p->mpUnknown1C->mpUnknown36->mUnknown120 != 0) {
        fn_8007F6F8(14, p->mpUnknown1C->mpUnknown36->mUnknown120);
    }
    fn_80178F20(0);
    if (fn_80149014(p)) {
        fn_801D2BD0(p->mpUnknown1C->mpUnknown36);
    }
    delete p->mpUnknown1C;
    p->mpUnknown1C = 0;
}

int fn_80151B20(Class_802A2918 *p)
{
    if (p->mUnknown40 == 0) {
        Entry_8015005C *pFirst = &p->mpUnknown1C->mpUnknown36->mEntries[0];
        Entry_8015005C *pSecond = pFirst + 1;

        return pFirst->mUnknown10 + pFirst->mUnknown8 * 2 ==
               pSecond->mUnknown10 + pSecond->mUnknown8 * 2;
    } else {
        Table_8015005C *pTable = p->mpUnknown1C->mpUnknown36;
        int lower = 0;
        unsigned int score = pTable->mEntries[0].mUnknown10 + pTable->mEntries[0].mUnknown8 * 2;
        unsigned int i;

        for (i = 1; i < pTable->mCount; i++) {
            if (pTable->mEntries[i].mUnknown10 + pTable->mEntries[i].mUnknown8 * 2 < score) {
                lower = 1;
            }
        }
        return !lower;
    }
}
}
