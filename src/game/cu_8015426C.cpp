#include "game/Class_80148A58.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B50.h"
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

class Class_802A1BC8 : public Class_80297BF8 {
public:
    virtual void vfn_03();
};

class Class_802A1B58 : public Class_80297CE8 {
public:
    virtual void vfn_04(float dt);
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    signed char mUnknown20;
    signed char mUnknown21;
    signed char mUnknown22;
    signed char mUnknown23;
};

class Class_802A1B18 : public Class_80297B50 {
public:
    virtual void vfn_03();
};

class Class_802A1AE0 : public Class_80297AB8 {
public:
    virtual void vfn_03();
    int mUnknown4;
};

class Class_802A1A58 : public Class_80297C60 {
public:
    virtual void vfn_09();
};

class Class_802A1930 : public Class_802A56E8 {
public:
    virtual int vfn_01();
};

class Class_802A19F0 : public Class_80297B90 {
public:
    virtual void vfn_06();
};

struct Score_801531C4 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned int mUnknown12;
    unsigned int mUnknown16;
    unsigned short mUnknown20[2];
    unsigned short mUnknown24[2];
    unsigned short mUnknown28[2];
    unsigned char mUnknown32;
};

struct Rules_801531C4 {
    Class_802A1BC8 mUnknown0;
    Class_802A1B58 mUnknown4;
    Class_802A1B18 mUnknown28;
    Class_802A1AE0 mUnknown32;
    Class_802A1A58 mUnknown40;
    Class_802A1930 mUnknown44;
    Class_802A19F0 mUnknown48;
    Score_801531C4 *mpUnknown52;
};

class Class_802A27F0 : public Class_80148A58 {
public:
    Rules_801531C4 *mpUnknown1C;
    int mUnknown20;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
};

extern "C" {
void fn_800BC51C(Class_80297BF8 *pObject);
void fn_800B3644(Class_80297B50 *pObject);
void fn_800BFAB4(Class_80297CE8 *pObject);
void fn_800A039C(Class_80297AB8 *pObject);
void fn_800B9598(Class_80297C60 *pObject);
void fn_800AACB8(Class_80297B90 *pObject);
void fn_80178F20(Class_802A56E8 *pObject);
int fn_80149014(void);
void *fn_8023816C(void *pHandle);
float fn_80178A2C(void);
void fn_80178E88(float v);

void fn_8015426C(Class_802A27F0 *p)
{
    void *pHandle = 0;
    int allocate = fn_80149014() == 0;
    Score_801531C4 *pScore;

    p->mpUnknown1C = new (0) Rules_801531C4;
    if (allocate) {
        pHandle = fn_80238174(0, (void **)&p->mpUnknown1C->mpUnknown52, sizeof(Score_801531C4), 0, 0x4D474F46);
        pScore = (Score_801531C4 *)fn_8023816C(pHandle);
    } else {
        p->mpUnknown1C->mpUnknown52 = (Score_801531C4 *)fn_801D2B7C(sizeof(Score_801531C4), 0, 0);
        pScore = p->mpUnknown1C->mpUnknown52;
    }
    memset(pScore, 0, sizeof(Score_801531C4));
    pScore->mUnknown8 = 3;
    pScore->mUnknown0 = 3;
    pScore->mUnknown4 = 3;
    pScore->mUnknown16 = pScore->mUnknown12 = p->mUnknown25;
    pScore->mUnknown32 = 2;
    p->mpUnknown1C->mUnknown4.mUnknown4 = 0;
    p->mpUnknown1C->mUnknown4.mUnknown8 = 0;
    p->mpUnknown1C->mUnknown4.mUnknown12 = 0;
    p->mpUnknown1C->mUnknown4.mUnknown16 = 0;
    p->mpUnknown1C->mUnknown4.mUnknown20 = -1;
    p->mpUnknown1C->mUnknown4.mUnknown21 = -1;
    p->mpUnknown1C->mUnknown4.mUnknown22 = -1;
    p->mpUnknown1C->mUnknown4.mUnknown23 = -1;
    if (allocate) {
        fn_802381E0(pHandle);
    }
    fn_800BC51C(&p->mpUnknown1C->mUnknown0);
    fn_800BFAB4(&p->mpUnknown1C->mUnknown4);
    fn_800B3644(&p->mpUnknown1C->mUnknown28);
    fn_800A039C(&p->mpUnknown1C->mUnknown32);
    fn_800B9598(&p->mpUnknown1C->mUnknown40);
    fn_800AACB8(&p->mpUnknown1C->mUnknown48);
    fn_80178F20(&p->mpUnknown1C->mUnknown44);
    fn_80178E88(fn_80178A2C() * 2.0f - 18.0f);
    p->mUnknown20 = fn_8007F828(14);
    fn_8007F6F8(14, 2);
}
}
