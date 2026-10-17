#include "game/Class_80148A58.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Class_802A56E8.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_8007F828.h"

void *operator new(unsigned int size, int unknown);

class Class_802A18C8 : public Class_80297BF8 {
};

class Class_802A17A8 : public Class_802A56E8 {
public:
    unsigned char mUnknown4;
};

class Class_802A1860 : public Class_80297B90 {
};

class Record_8005CE10 {
public:
    virtual ~Record_8005CE10();
    unsigned int mOrdinal;
    int mEvent;
    int mPlayer;
    int mConversion;
    int mOther;
    unsigned char mFlag;
};

class Block_80156400 {
public:
    Block_80156400();
    Class_802A18C8 mObject0;
    Class_802A17A8 mObject4;
    Class_802A1860 mObject12;
    int mUnknown16;
    Record_8005CE10 mRecords[2][3];
    unsigned char mUnknown188;
    unsigned char mUnknown189[2];
};

class Class_802A2A40 : public Class_80148A58 {
public:
    Block_80156400 *mpUnknown1C;
};

extern "C" {
void fn_800BC51C(Class_80297BF8 *pObject);
void fn_800AACB8(Class_80297B90 *pObject);
void fn_80178F20(Class_802A56E8 *pObject);
void fn_8017CAC0(void (*pCallback)(unsigned int, int, int));
void fn_80155588(Class_802A17A8 *p, int team);
void fn_801556D0(unsigned int kind, int value, int flag);

void fn_8015583C(Class_802A2A40 *p)
{
    p->mpUnknown1C = new (0) Block_80156400;
    p->mpUnknown1C->mUnknown188 = 2;
    p->mpUnknown1C->mUnknown189[0] = 0;
    p->mpUnknown1C->mUnknown189[1] = 0;
    p->mpUnknown1C->mUnknown16 = fn_8007F828(14);
    if (p->mpUnknown1C->mUnknown16 != 0) {
        fn_8007F6F8(14, 0);
    }
    fn_800BC51C(&p->mpUnknown1C->mObject0);
    fn_800AACB8(&p->mpUnknown1C->mObject12);
    fn_8017CAC0(fn_801556D0);
    fn_80155588(&p->mpUnknown1C->mObject4, 2);
    fn_80178F20(&p->mpUnknown1C->mObject4);
}

void fn_801558FC(Class_802A2A40 *p)
{
    fn_800BC51C(0);
    fn_800AACB8(0);
    if (p->mpUnknown1C->mUnknown16 != 0) {
        fn_8007F6F8(14, p->mpUnknown1C->mUnknown16);
    }
    fn_80178F20(0);
    fn_8017CAC0(0);
    delete p->mpUnknown1C;
    p->mpUnknown1C = 0;
}
}
