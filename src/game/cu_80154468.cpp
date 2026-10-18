#include "game/Class_80148A58.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B50.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_802A56E8.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_801D2B7C.h"

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

struct Score_801531C4;

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
int fn_80149014(Class_802A27F0 *p);
void fn_800A8738(unsigned char value);

void fn_80154468(Class_802A27F0 *p)
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800B3644(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_800AACB8(0);
    fn_8007F6F8(14, p->mUnknown20);
    fn_80178F20(0);
    if (fn_80149014(p)) {
        fn_801D2BD0(p->mpUnknown1C->mpUnknown52);
    }
    delete p->mpUnknown1C;
    p->mpUnknown1C = 0;
    fn_800A8738(0);
}
}
