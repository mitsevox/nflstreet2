#include "game/Class_80148A58.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297CE8.h"
#include "game/Object_80039F5C.h"
#include "game/fn_80177FE0.h"

class Class_802A1D20 : public Class_80297AB8 {
public:
    unsigned char mUnknown4;
    char mUnknown5[3];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

class Class_802A1D58 : public Class_80297CE8 {
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
    char mUnknown100[17];
    unsigned char mUnknown117;
    unsigned char mCount;
    char mUnknown119[6];
    unsigned char mUnknown125;
};

struct Settings_8031BDD4 {
    char mUnknown0[32];
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
};

extern "C" {
extern Settings_8031BDD4 lbl_8031BDD4;

Table_8015005C *fn_801530FC(void);
void fn_8003A4DC(void);
void fn_801486A8(void);
void fn_801527E0(Settings_8031BDD4 *p, int value);
Object_80039F5C *fn_8003AC84(int id);
void fn_800AD910(int a, float b);
void fn_800B6474(int index, unsigned char team);
void fn_800B6714(Object_80039F5C *pPlayer, int a);
void fn_800B6658(Object_80039F5C *pPlayer);
void fn_80162780(int a, int b);
void fn_80151010(Class_802A1D20 *p);

void fn_80150848(Class_802A1D58 *p, float dt)
{
    unsigned int i;
    unsigned int count;
    Point_8017886C point;

    fn_8003A4DC();
    count = fn_801530FC()->mCount;
    fn_801486A8();
    p->Class_80297CE8::vfn_04(dt);
    fn_801530FC()->mUnknown117 = 0;
    fn_801527E0(&lbl_8031BDD4, 1);
    point = fn_80177FE0();
    for (i = 0; i < count; i++) {
        Object_80039F5C *pPlayer = fn_8003AC84(fn_801530FC()->mEntries[i].mUnknown0);
        pPlayer->mMotion.mPos.mX = -(float)count * 1.125f + (float)i * 2.25f;
        pPlayer->mMotion.mPos.mY = point.mY + 30.0f;
    }
}

void fn_80150984(Class_802A1D58 *p, float dt)
{
    fn_800AD910(3, dt);
    if (lbl_8031BDD4.mUnknown36 != 0) {
        fn_80148A58()->vfn_15();
    }
}

void fn_801509D4(Class_802A1D58 *p)
{
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        Object_80039F5C *pPlayer = fn_8003AC84(fn_801530FC()->mEntries[i].mUnknown0);
        if (pPlayer) {
            unsigned char value = fn_801530FC()->mEntries[i].mUnknown12[0];
            if (value != 255 && fn_801530FC()->mEntries[i].mUnknown12[1] == 0) {
                fn_800B6474(value, pPlayer->mIdBytes[2]);
                fn_800B6714(pPlayer, value);
            } else {
                fn_800B6658(pPlayer);
            }
        }
    }
}

void fn_80150A70(Class_802A1D58 *p)
{
}

void fn_80150A74(Class_802A1D20 *p)
{
    p->Class_80297AB8::vfn_03();
    fn_80162780(1, 1);
    p->mUnknown8 = 0;
    p->mUnknown9 = 0;
    p->mUnknown4 = 0;
    fn_80151010(p);
}
}
