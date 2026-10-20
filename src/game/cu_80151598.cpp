#include "game/Class_80148A58.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297C60.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80064864.h"
#include "game/fn_8021D7B8.h"

class Class_802A1C98 : public Class_80297C60 {
};

class Class_802A1C30 : public Class_80297B90 {
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
extern void *lbl_803EB688;
extern const int lbl_802DEA78[];

Table_8015005C *fn_801530FC(void);
Object_80039F5C *fn_8003AC84(int id);
int fn_80177C38(void);
void fn_80177C50(int a);
void fn_80177C44(int value);
void fn_8011DF90(void);
int fn_80178308(void);
void fn_80168A14(int team);
int fn_8005BFD4(void);
void fn_8005BF18(void);
int fn_80178AE0(void);
void fn_800AD910(int a, float b);
void fn_80173B8C(void);
void fn_8009B924(void);
void fn_801735D8(unsigned int mask);
void fn_8009D8CC(int index);
int fn_8005FC7C(void);
unsigned char fn_801529C0(Settings_8031BDD4 *p);
void fn_8006088C(int value);
void fn_800AAD58(void *p, float dt);
void fn_8021956C(void *p, int a, int b, int c);

int fn_80151598(Class_802A1C98 *p)
{
    p->vfn_15();
    return 1;
}

void fn_801515D0(Class_802A1C98 *p)
{
    unsigned char team;

    p->Class_80297C60::vfn_05();
    if (fn_80177C38() == 1 || fn_80177C38() == 3) {
        fn_80177C50(1);
        fn_80177C44(0);
    }
    fn_8011DF90();
    team = fn_80178308();
    fn_80168A14(team);
}

void fn_80151628(Class_802A1C98 *p, float dt)
{
    if (fn_8005BFD4() != 4) {
        fn_8005BF18();
    }
    if (fn_80178AE0() == 2) {
        fn_800AD910(2, dt);
    } else {
        fn_80173B8C();
    }
}

void fn_80151680(Class_802A1C98 *p)
{
}

int fn_80151684(Class_802A1C98 *p)
{
    fn_8009B924();
    return 0;
}

void fn_801516A8(Class_802A1C30 *p, float dt)
{
    unsigned int i;

    fn_801735D8(2048);
    fn_8009D8CC(1);
    for (i = 0; i < 4; i++) {
        fn_8003AC84(fn_801530FC()->mEntries[i].mUnknown0)->mUnknown9[2] = 1;
    }
    fn_80148A58()->vfn_12();
    fn_80148A58()->vfn_16(lbl_802DEA78);
    fn_8021D7B8(lbl_803EB688, 0x8000003A, 0, 0);
    if (fn_8005FC7C()) {
        fn_8006088C(fn_801529C0(&lbl_8031BDD4));
    }
    fn_800AAD58(p, dt);
}

void fn_80151798(Class_802A1C30 *p)
{
    fn_80064EFC(3, 19, -1);
}

void fn_801517C4(Class_802A1C30 *p)
{
    fn_8021956C(lbl_803EB688, 3, 19, 1);
}
}
