#include "game/Class_80148A58.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B50.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_802A56E8.h"
#include "game/Object_8008044C.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_8007F828.h"

void *operator new(unsigned int size, int unknown);

class Class_802A2788 : public Class_80297BF8 {
public:
    virtual void vfn_03();
};

class Class_802A2748 : public Class_80297B50 {
public:
    virtual void vfn_04(float dt);
};

class Class_802A26D8 : public Class_80297CE8 {
public:
    virtual void vfn_04(float dt);
};

class Class_802A26A0 : public Class_80297AB8 {
public:
    virtual void vfn_04(float dt);
};

class Class_802A2618 : public Class_80297C60 {
public:
    virtual void vfn_04(float dt);
};

class Class_802A24F8 : public Class_80297B90 {
public:
    virtual void vfn_06();
};

class Class_802A2560 : public Class_802A56E8 {
public:
    virtual int vfn_01();
};

struct States_802A2DB8 {
    Class_802A2788 mUnknown0;
    Class_802A2748 mUnknown4;
    Class_802A26D8 mUnknown8;
    Class_802A26A0 mUnknownC;
    Class_802A2618 mUnknown10;
    Class_802A24F8 mUnknown14;
    Class_802A2560 mUnknown18;
    int mUnknown1C;
    int mUnknown20[2][3];
    unsigned char mUnknown38;
};

class Class_802A2DB8 : public Class_80148A58 {
public:
    States_802A2DB8 *mpUnknown1C;
};

extern "C" {
void fn_800BC51C(Class_80297BF8 *pObject);
void fn_800B3644(Class_80297B50 *pObject);
void fn_800BFAB4(Class_80297CE8 *pObject);
void fn_800A039C(Class_80297AB8 *pObject);
void fn_800B9598(Class_80297C60 *pObject);
void fn_800AACB8(Class_80297B90 *pObject);
void fn_80178F20(Class_802A56E8 *pObject);
void fn_8014ABE4(void *p, int team);
unsigned char fn_8003B560(int group, int index, int *pValue);
int fn_800809FC(Object_8008044C *pObject, int a, int *pResult);
int fn_800808F8(Object_8008044C *pObject);

void fn_8014B528(Class_802A2DB8 *p)
{
    unsigned int i;
    int id;

    p->mUnknown0 = 13;
    p->mUnknown4 = 12;
    p->mState.mUnknownC = 0;
    p->mpUnknown1C = new (0) States_802A2DB8;
    p->mpUnknown1C->mUnknown1C = fn_8007F828(14);
    if (p->mpUnknown1C->mUnknown1C != 0) {
        fn_8007F6F8(14, 0);
    }
    fn_800BC51C(&p->mpUnknown1C->mUnknown0);
    fn_800B3644(&p->mpUnknown1C->mUnknown4);
    fn_800BFAB4(&p->mpUnknown1C->mUnknown8);
    fn_800A039C(&p->mpUnknown1C->mUnknownC);
    fn_800B9598(&p->mpUnknown1C->mUnknown10);
    fn_800AACB8(&p->mpUnknown1C->mUnknown14);
    fn_8014ABE4(&p->mpUnknown1C->mUnknown18, 2);
    fn_80178F20(&p->mpUnknown1C->mUnknown18);
    p->mpUnknown1C->mUnknown38 = fn_8007F828(19);
    if (p->mpUnknown1C->mUnknown38 != 0) {
        fn_8007F6F8(19, 0);
    }
    id = 0;
    for (i = 0; i < 2; i++) {
        Object_8008044C cursor;
        Desc_8008044C desc;
        desc.mUnknown0 = 0;
        desc.mUnknown4 = 1;
        desc.mUnknown12 = 0;
        desc.mUnknown8 = i;
        fn_8008040C(&cursor, &desc);
        if (fn_8003B560(i, 0, &id)) {
            fn_800809FC(&cursor, id, 0);
            id = fn_800808F8(&cursor);
        }
        p->mpUnknown1C->mUnknown20[i][0] = id;
        if (fn_8003B560(i, 2, &id)) {
            fn_800809FC(&cursor, id, 0);
            id = fn_800808F8(&cursor);
        }
        p->mpUnknown1C->mUnknown20[i][1] = id;
        if (fn_8003B560(i, 3, &id)) {
            fn_800809FC(&cursor, id, 0);
            id = fn_800808F8(&cursor);
        }
        p->mpUnknown1C->mUnknown20[i][2] = id;
        fn_8008056C(&cursor);
    }
}
}
