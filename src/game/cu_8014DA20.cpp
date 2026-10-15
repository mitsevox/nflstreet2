#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/fn_8009D990.h"
#include "game/fn_8021D7B8.h"
#include "game/cu_80064864.h"
#include "game/fn_801C1F94.h"

struct Record_8014F104 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
    char mUnknown12[40];
    char mUnknown52[4];
};

struct Block_8014F104 {
    char mUnknown0[0x34];
    Record_8014F104 *mpUnknown34;
    char mUnknown38[8];
    int mUnknown40[2][7];
};

extern "C" {
extern int lbl_803EB2DC;
extern int lbl_803EB2E0;
extern void *lbl_803EB688;
extern const int lbl_802DE9CC[];

Block_8014F104 *fn_8014F104(Class_80148A58 *p);
void fn_80149040(Object_80039F5C *p);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
Object_80039F5C *fn_8003AC84(int id);
void fn_801488D4(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_801735D8(unsigned int mask);
void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);
void fn_800AAD58(void *p, float dt);
void fn_8021956C(void *p, int a, int b, int c);
int fn_8014EDBC(void);
void fn_80177768(void *p, int team);
void fn_8017767C(void);
void fn_80178CD8(int a);
void fn_8014D024(unsigned short index);

void fn_8014DA20(void)
{
    for (unsigned char team = 0; team <= 1; team++) {
        for (unsigned short i = 0; i <= 6; i++) {
            Object_80039F5C *pPlayer = fn_80039F5C(team, i);
            fn_80149040(pPlayer);
            fn_800EFE60(0, pPlayer->mpState, pPlayer);
        }
    }
}

void fn_8014DA90(void)
{
    Block_8014F104 *pBlock = fn_8014F104(fn_80148A58());
    for (unsigned int team = 0; team <= 1; team++) {
        for (unsigned int i = 0; i <= 6; i++) {
            Object_80039F5C *pPlayer = fn_80039F5C((unsigned char)team, i);
            int id = pBlock->mUnknown40[team][i];
            if (id != pPlayer->mUnknown2908) {
                fn_801488D4(pPlayer, fn_8003AC84(id));
            }
        }
    }
}

void fn_8014DB24(void *p, float dt)
{
    fn_801735D8(2048);
    fn_8009D8CC(1);
    fn_8021D7B8(lbl_803EB688, 0x8000003A, 0, 0);
    fn_80148A58()->vfn_12();
    fn_80148A58()->vfn_16(lbl_802DE9CC);
    fn_800AAD58(p, dt);
}

void fn_8014DBCC(void)
{
    fn_80064EFC(3, 18, -1);
}

void fn_8014DBF8(void)
{
    fn_8021956C(lbl_803EB688, 3, 18, 1);
}

int fn_8014DC28(void)
{
    if (fn_8009D990(1) == 0) {
        return 1;
    }
    return 2;
}

int fn_8014DC5C(void)
{
    return fn_8014EDBC();
}

void fn_8014DC7C(void *p)
{
    fn_80177768(p, 2);
    for (unsigned char i = 0; i <= 5; i++) {
        fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown4 = 0;
        fn_801C1F94(fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown12, 0, 40);
    }
    lbl_803EB2DC = 0;
    lbl_803EB2E0 = 0;
}

void fn_8014DD04(void)
{
    fn_8017767C();
    fn_80178CD8(0);
}

void fn_8014DD2C(void)
{
    int pad = fn_80065650();
    unsigned short i;
    int value = fn_8014F104(fn_80148A58())->mpUnknown34[0].mUnknown4 + 1;
    for (i = 0; i <= 5; i++) {
        if (fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown8 == pad) {
            fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown4 = value;
            break;
        }
    }
    fn_8014D024(i);
    fn_8009D964(1, 0);
}
}
